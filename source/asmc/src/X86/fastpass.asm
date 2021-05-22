; FASTPASS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  implements the "fastpass" handling.
;       "fastpass" is an optimization which increases
;       assembly time speed by storing preprocessed lines
;       in memory during the first pass. In further passes,
;       those lines are "read" instead of the original assembly
;       source files.
;       Speed increase is significant if there's a large include
;       file at the top of an assembly source which contains
;       just equates and type definitions, because there's no need
;       to save such lines during pass one.
;

include stdio.inc
include string.inc
include malloc.inc

include asmc.inc
include fastpass.inc
include memalloc.inc
include listing.inc
include input.inc
include segment.inc

;
; current LST file position
;
externdef list_pos:DWORD

    .data?
    LineStore       qdesc <>
    LineStoreCurr   line_t ?        ; must be global!
    StoreState      int_t ?
    UseSavedState   int_t ?
    modstate        mod_state <>    ; struct to store assembly status

    .data
    NoLineStore     int_t 0

    .code

;
; save the current status (happens in pass one only) and
; switch to "save precompiled lines" mode.
; the status is then restored in further passes,
; and the precompiled lines are used for assembly then.
;
SaveState PROC
    xor eax,eax
    mov modstate.head,eax
    mov modstate.tail,eax
    inc eax
    mov StoreState,eax
    mov UseSavedState,eax
    mov modstate.init,eax
    mov edx,edi
    mov eax,esi
    mov ecx,sizeof(modstate.modinfo)
    lea esi,ModuleInfo.proc_prologue
    lea edi,modstate.modinfo
    rep movsb
    mov esi,eax
    mov edi,edx
    SegmentSaveState()
    AssumeSaveState()
    ContextSaveState()  ; save pushcontext/popcontext stack
    ret
SaveState ENDP

StoreLine PROC USES esi edi ebx sline:string_t, flags:int_t, lst_position:uint_t

    xor eax,eax
    .return .if ( eax != NoLineStore )

    ; don't store generated lines!

    .if ModuleInfo.GeneratedCode == eax
        .if StoreState == eax   ; line store already started?
            SaveState()
        .endif
        mov ebx,strlen(sline)
        xor eax,eax
        .if flags == 1 && ModuleInfo.CurrComment != eax
            strlen( ModuleInfo.CurrComment )
        .endif
        mov edi,eax
        LclAlloc( &[eax+ebx+line_item] )
        mov ecx,LineStoreCurr
        mov LineStoreCurr,eax
        mov esi,eax
        mov [esi].line_item.prev,ecx
        mov [esi].line_item.next,0
        GetLineNumber()
        mov [esi].line_item.lineno,eax

        get_curr_srcfile()
        mov [esi].line_item.srcfile,eax
        mov [esi].line_item.macro_level,MacroLevel
        mov eax,lst_position
        .if !eax
            mov eax,list_pos
        .endif
        mov [esi].line_item.list_pos,eax
        .if edi
            memcpy( &[esi].line_item.line, sline, ebx )
            inc edi
            add eax,ebx
            memcpy( eax, ModuleInfo.CurrComment, edi )
        .else
            inc ebx
            memcpy( &[esi].line_item.line, sline, ebx )
        .endif
        lea ecx,[esi].line_item.line
        ;
        ; v2.08: don't store % operator at pos 0
        ;
        .while islspace( [ecx] )
            inc ecx
        .endw

        .if ( al == '%' )

            mov edx,[ecx+1]
            and edx,0xFFFFFF
            or  edx,0x202020
            .if ( edx != 'tuo' || is_valid_id_char( [ecx+4] ) )
                mov byte ptr [ecx],' '
            .endif
        .endif

        .if LineStore.head
            mov eax,LineStore.tail
            mov [eax].line_item.next,esi
        .else
            mov LineStore.head,esi
        .endif
        mov LineStore.tail,esi
    .endif
    ret

StoreLine ENDP

; an error has been detected in pass one. it should be
; reported in pass 2, so ensure that a full source scan is done then
;
SkipSavedState PROC
    mov UseSavedState,0
    ret
SkipSavedState ENDP

; for FASTPASS, just pass 1 is a full pass, the other passes
; don't start from scratch and they just assemble the preprocessed
; source. To be able to restart the assembly process from a certain
; location within the source, it's necessary to save the value of
; assembly time variables.
; However, to reduce the number of variables that are saved, an
; assembly-time variable is only saved when
; - it is changed
; - it was defined when StoreState() is called
;
SaveVariableState PROC USES esi edi sym:asym_t

    mov esi,sym
    or  [esi].asym.flag1,S_ISSAVED
    mov edi,LclAlloc(equ_item)
    mov [edi].equ_item.next,0
    mov [edi].equ_item.sym,esi
    mov [edi].equ_item.isdefined,0
    .if [esi].asym.flags & S_ISDEFINED
        inc [edi].equ_item.isdefined
    .endif
    mov [edi].equ_item.lvalue,[esi].asym.value
    mov [edi].equ_item.hvalue,[esi].asym.value3264
    mov [edi].equ_item.mem_type,[esi].asym.mem_type
    .if ( modstate.tail )
        mov eax,modstate.tail
        mov [eax].equ_item.next,edi
        mov modstate.tail,edi
    .else
        mov modstate.head,edi
        mov modstate.tail,edi
    .endif
    ret
SaveVariableState ENDP

RestoreState PROC

    .if modstate.init

        ; restore values of assembly time variables

        mov edx,modstate.head
        .while edx
            mov ecx,[edx].equ_item.sym
            mov [ecx].asym.value,[edx].equ_item.lvalue
            mov [ecx].asym.value3264,[edx].equ_item.hvalue
            and [ecx].asym.flags,not S_ISDEFINED
            .if [edx].equ_item.isdefined
                and [ecx].asym.flags,not S_ISDEFINED
            .endif
            mov edx,[edx].equ_item.next
        .endw

        ; fields in module_vars are not to be restored.
        ; v2.10: the module_vars fields are not saved either.

        ; v2.23: save L"Unicode" flag

        push esi
        mov edx,edi
        mov al,ModuleInfo.xflag
        mov ecx,sizeof(modstate.modinfo)
        lea esi,modstate.modinfo
        lea edi,ModuleInfo.proc_prologue
        rep movsb
        mov edi,edx
        pop esi
        and al,OPT_LSTRING
        or  ModuleInfo.xflag,al
        SetOfssize()
        SymSetCmpFunc()
    .endif
    mov eax,LineStore.head
    ret

RestoreState ENDP

FastpassInit PROC

    xor eax,eax
    mov StoreState,eax
    mov modstate.init,eax
    mov LineStore.head,eax
    mov LineStore.tail,eax
    mov UseSavedState,eax
    ret

FastpassInit ENDP

    END

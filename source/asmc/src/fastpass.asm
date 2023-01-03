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
externdef list_pos:uint_t

    .data?
    LineStore       qdesc <>
    LineStoreCurr   ptr line_item ? ; must be global!
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
SaveState proc __ccall private uses rsi rdi

    mov modstate.head,NULL
    mov modstate.tail,NULL
    mov StoreState,1
    mov UseSavedState,1
    mov modstate.init,1
    mov ecx,sizeof(modstate.modinfo)
    lea rsi,ModuleInfo.proc_prologue
    lea rdi,modstate.modinfo
    rep movsb
    SegmentSaveState()
    AssumeSaveState()
    ContextSaveState()  ; save pushcontext/popcontext stack
    ret

SaveState endp


StoreLine proc __ccall uses rsi rdi rbx sline:string_t, flags:int_t, lst_position:uint_t

    xor eax,eax
    .return .if ( eax != NoLineStore )

    ; don't store generated lines!

    .if ( ModuleInfo.GeneratedCode == eax )

        .if StoreState == eax   ; line store already started?
            SaveState()
        .endif
        mov ebx,tstrlen(sline)
        xor eax,eax
        .if ( flags == 1 && ModuleInfo.CurrComment != rax )
            tstrlen( ModuleInfo.CurrComment )
        .endif
        mov edi,eax
        LclAlloc( &[rax+rbx+line_item] )
        mov rcx,LineStoreCurr
        mov LineStoreCurr,rax
        mov rsi,rax
        mov [rsi].line_item.prev,rcx
        mov [rsi].line_item.next,0
        GetLineNumber()
        mov [rsi].line_item.lineno,eax

        get_curr_srcfile()
        mov [rsi].line_item.srcfile,eax
        mov [rsi].line_item.macro_level,MacroLevel
        mov eax,lst_position
        .if !eax
            mov eax,list_pos
        .endif
        mov [rsi].line_item.list_pos,eax
        .if edi
            tmemcpy( &[rsi].line_item.line, sline, ebx )
            inc edi
            add rax,rbx
            tmemcpy( rax, ModuleInfo.CurrComment, edi )
        .else
            inc ebx
            tmemcpy( &[rsi].line_item.line, sline, ebx )
        .endif
        lea rcx,[rsi].line_item.line
        ;
        ; v2.08: don't store % operator at pos 0
        ;
        .while islspace( [rcx] )
            inc rcx
        .endw

        .if ( al == '%' )

            mov edx,[rcx+1]
            and edx,0xFFFFFF
            or  edx,0x202020
            .if ( edx != 'tuo' || islabel( [rcx+4] ) )
                mov byte ptr [rcx],' '
            .endif
        .endif

        .if ( LineStore.head )
            mov rax,LineStore.tail
            mov [rax].line_item.next,rsi
        .else
            mov LineStore.head,rsi
        .endif
        mov LineStore.tail,rsi
    .endif
    ret

StoreLine endp


; an error has been detected in pass one. it should be
; reported in pass 2, so ensure that a full source scan is done then
;
SkipSavedState proc

    mov UseSavedState,0
    ret

SkipSavedState endp


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
SaveVariableState proc fastcall uses rsi rdi _sym:asym_t

    mov rsi,rcx
    or  [rsi].asym.flag1,S_ISSAVED
    mov rdi,LclAlloc(equ_item)
    mov [rdi].equ_item.next,0
    mov [rdi].equ_item.sym,rsi
    mov [rdi].equ_item.isdefined,0
    .if [rsi].asym.flags & S_ISDEFINED
        inc [rdi].equ_item.isdefined
    .endif
    mov [rdi].equ_item.lvalue,[rsi].asym.value
    mov [rdi].equ_item.hvalue,[rsi].asym.value3264
    mov [rdi].equ_item.mem_type,[rsi].asym.mem_type
    .if ( modstate.tail )
        mov rax,modstate.tail
        mov [rax].equ_item.next,rdi
        mov modstate.tail,rdi
    .else
        mov modstate.head,rdi
        mov modstate.tail,rdi
    .endif
    ret

SaveVariableState endp


RestoreState proc

    .if ( modstate.init )

        ; restore values of assembly time variables

        mov rdx,modstate.head
        .while rdx
            mov rcx,[rdx].equ_item.sym
            mov [rcx].asym.value,[rdx].equ_item.lvalue
            mov [rcx].asym.value3264,[rdx].equ_item.hvalue
            and [rcx].asym.flags,not S_ISDEFINED
            .if [rdx].equ_item.isdefined
                and [rcx].asym.flags,not S_ISDEFINED
            .endif
            mov rdx,[rdx].equ_item.next
        .endw

        ; fields in module_vars are not to be restored.
        ; v2.10: the module_vars fields are not saved either.

        ; v2.23: save L"Unicode" flag

        push    rsi
        mov     rdx,rdi
        mov     al,ModuleInfo.xflag
        mov     ecx,sizeof(modstate.modinfo)
        lea     rsi,modstate.modinfo
        lea     rdi,ModuleInfo.proc_prologue
        rep     movsb
        mov     rdi,rdx
        pop     rsi
        and     al,OPT_LSTRING
        or      ModuleInfo.xflag,al

        SetOfssize()
        SymSetCmpFunc()
    .endif
    .return( LineStore.head )

RestoreState endp


FastpassInit proc

    mov StoreState,0
    mov modstate.init,0
    mov LineStore.head,NULL
    mov LineStore.tail,NULL
    mov UseSavedState,0
    ret

FastpassInit endp

    END

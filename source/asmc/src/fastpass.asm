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

include asmc.inc
include memalloc.inc
include fastpass.inc
include segment.inc

; current LST file position

externdef list_pos:uint_t

    .data?
    LineStore       qdesc <>
    LineStoreCurr   ptr line_item ? ; must be global!
    StoreState      int_t ?
    UseSavedState   int_t ?
    modstate        mod_state <>    ; struct to store assembly status
    ReqSavedState   int_t ? ; v2.19

    .data
    NoLineStore     int_t 0

    .code

; save the current status (happens in pass one only) and
; switch to "save precompiled lines" mode.
; the status is then restored in further passes,
; and the precompiled lines are used for assembly then.

SaveState proc __ccall private uses rsi rdi

    mov modstate.head,NULL
    mov modstate.tail,NULL
    mov StoreState,1
    mov UseSavedState,1
    mov modstate.init,1
    mov ecx,sizeof(modstate.modinfo)
    lea rsi,ModuleInfo
    lea rdi,modstate.modinfo
    rep movsb
    GetInputState(&modstate.state)
    SegmentSaveState()
    AssumeSaveState()
    ContextSaveState()  ; save pushcontext/popcontext stack
    ret

SaveState endp


StoreLine proc __ccall uses rsi rdi rbx sline:string_t

    xor eax,eax
    .return .if ( eax != NoLineStore )

    ; don't store generated lines!

    .if ( eax == MODULE.GeneratedCode )

        .if ( eax == StoreState ) ; line store already started?
            SaveState()
        .endif
        mov ebx,tstrlen(sline)
        LclAlloc( &[rbx+line_item] )
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
        mov [rsi].line_item.list_pos,list_pos
        inc ebx
        tmemcpy( &[rsi].line_item.line, sline, ebx )
        lea rcx,[rsi].line_item.line

        ; v2.08: don't store % operator at pos 0

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

SkipSavedState proc

    mov ReqSavedState,0
    ret

SkipSavedState endp

DefSavedState proc

    mov eax,StoreState
    and eax,ReqSavedState
    mov UseSavedState,eax
    mov StoreState,FALSE
    ret

DefSavedState endp


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
    mov [rsi].asym.issaved,1
    mov rdi,LclAlloc(equ_item)
    ;mov [rdi].equ_item.next,0
    mov [rdi].equ_item.sym,rsi
    ;mov [rdi].equ_item.isdefined,0
    .if ( [rsi].asym.isdefined )
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
            mov [rcx].asym.isdefined,0
            .if [rdx].equ_item.isdefined
                mov [rcx].asym.isdefined,1
            .endif
            mov rdx,[rdx].equ_item.next
        .endw

        ; fields in module_vars are not to be restored.
        ; v2.10: the module_vars fields are not saved either.

        ; v2.23: save L"Unicode" flag

        test MODULE.lstring,1
        mov rax,rsi
        mov rdx,rdi
        mov ecx,sizeof(modstate.modinfo)
        lea rsi,modstate.modinfo
        lea rdi,ModuleInfo
        rep movsb
        mov rdi,rdx
        mov rsi,rax
        .ifnz
            mov MODULE.lstring,1
        .endif
        SetInputState(&modstate.state)
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
    mov ReqSavedState,TRUE
    ret

FastpassInit endp

    END

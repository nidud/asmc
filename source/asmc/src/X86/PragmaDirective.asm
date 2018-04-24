; PRAGMADIRECTIVE.ASM--
; Copyright (C) 2018 Asmc Developers
;
; Change history:
; 2018-03-24 - .pragma(init(<proc>, <priority>))
;              .pragma(exit(<proc>, <priority>))
; 2018-04-22 - .pragma(pack(push, <alignment>))
;              .pragma(pack(pop))
;
include asmc.inc
include hll.inc

MAXFIELDSTACK equ 60

    .data
    PushCount  dd 0
    FieldStack db MAXFIELDSTACK dup(?)

    .code

    assume ebx:ptr asm_tok

PragmaDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asm_tok

  local rc:SINT

    mov rc,NOT_ERROR

    inc i
    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
        add ebx,16
    .endif

    .repeat

        mov esi,[ebx].string_ptr
        mov eax,[esi]
        or  eax,0x20202020
        add ebx,16
        .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
            add ebx,16
        .endif

        .switch eax
        .case "tini"
        .case "tixe"
            mov edi,@CStr("dw")
            .if ModuleInfo.Ofssize == USE32
                mov edi,@CStr("dd")
            .endif
            .if ModuleInfo.Ofssize == USE64
                mov edi,@CStr("dq")
            .endif
            lea edx,@CStr("EXIT")
            .if eax == "tini"
                lea edx,@CStr("INIT")
            .endif
            push edx
            AddLineQueueX( "_%s segment PARA FLAT PUBLIC '%s'", edx, edx )
            AddLineQueueX( " %s %s", edi, [ebx].string_ptr )
            add ebx,16
            .if [ebx].token == T_COMMA
                add ebx,16
            .endif
            AddLineQueueX( " %s %s", edi, [ebx].string_ptr )
            pop edx
            AddLineQueueX( "_%s ends", edx )
            .endc

        .case "kcap"

            ; .pragma(pack(push, <alignment>))

            mov esi,[ebx].string_ptr
            mov eax,[esi]
            or  eax,0x202020
            and eax,0xFFFFFF

            .if eax == "pop"

                .endc .if !PushCount
                dec PushCount
                mov eax,PushCount
                mov al,FieldStack[eax]
                mov ModuleInfo.fieldalign,al
                .endc
            .endif

            .endc .if eax != "sup"
            .endc .if PushCount >= MAXFIELDSTACK

            mov edx,PushCount
            inc PushCount
            mov al,ModuleInfo.fieldalign
            mov FieldStack[edx],al
            add ebx,16
            .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
                add ebx,16
            .endif
            AddLineQueueX( "OPTION FIELDALIGN: %s", [ebx].string_ptr )
            .endc
        .endsw

        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
        .if ModuleInfo.line_queue.head
            RunLineQueue()
        .endif
        mov eax,rc
    .until 1
    ret

PragmaDirective endp

    END


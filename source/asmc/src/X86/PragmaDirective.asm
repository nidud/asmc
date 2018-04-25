; PRAGMADIRECTIVE.ASM--
; Copyright (C) 2018 Asmc Developers
;
; Change history:
; 2018-04-24 - .pragma(list(push, <0|1>))
;              .pragma(list(pop))
; 2018-04-22 - .pragma(pack(push, <alignment>))
;              .pragma(pack(pop))
; 2018-03-24 - .pragma(init(<proc>, <priority>))
;              .pragma(exit(<proc>, <priority>))
;
include asmc.inc
include hll.inc
include token.inc

MAXFIELDSTACK equ 20
MAXLISTSTACK  equ 20

    .data

    ListCount  dd 0
    FieldCount dd 0

    FieldStack db MAXFIELDSTACK dup(0)
    ListStack  db MAXLISTSTACK dup(0)

    .code

    assume ebx:ptr asm_tok

PragmaDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asm_tok

  local rc:SINT, list_directive:SINT
  local opndx:expr

    mov rc,NOT_ERROR
    mov list_directive,0

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
            add ebx,16
            .endc

        .case "kcap"

            ; .pragma(pack(push, <alignment>))
            ; .pragma(pack(pop))

            .if [ebx].tokval == T_POP

                add ebx,16
                .endc .if !FieldCount

                dec FieldCount
                mov eax,FieldCount
                mov al,FieldStack[eax]
                mov ModuleInfo.fieldalign,al
                .endc
            .endif

            .endc .if [ebx].tokval != T_PUSH
            .endc .if FieldCount >= MAXFIELDSTACK

            mov edx,FieldCount
            inc FieldCount
            mov al,ModuleInfo.fieldalign
            mov FieldStack[edx],al
            add ebx,16
            .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
                add ebx,16
            .endif
            AddLineQueueX( "OPTION FIELDALIGN: %s", [ebx].string_ptr )
            add ebx,16
            .endc

        .case "tsil"

            ; .pragma(list(push, 0|1))
            ; .pragma(list(pop))

            inc list_directive

            .repeat

                .if [ebx].tokval == T_POP

                    .endc .if !ListCount ; this gives an error if nothing pushed

                    dec ListCount
                    mov eax,ListCount
                    mov al,ListStack[eax]
                    .break
                .endif

                .endc .if [ebx].tokval != T_PUSH
                .endc .if ListCount >= MAXLISTSTACK

                mov edx,ListCount
                inc ListCount
                mov al,ModuleInfo.list
                mov ListStack[edx],al
                add ebx,16
                .if [ebx].token == T_COMMA
                    add ebx,16
                .endif
                mov eax,ebx
                sub eax,tokenarray
                shr eax,4
                mov i,eax
                .endc .if EvalOperand( &i, tokenarray,
                    ModuleInfo.token_count, &opndx, EXPF_NOUNDEF ) == ERROR
                .if opndx.kind != EXPR_CONST
                    asmerr( 2026 )
                    .endc
                .endif
                mov eax,opndx.uvalue
                .if eax > 1
                    asmerr( 2084 )
                    .endc
                .endif
            .until 1

            mov ModuleInfo.list,al
            .if al
                or ModuleInfo.line_flags,LOF_LISTED
            .endif
            add ebx,16
            .endc

        .endsw

        .while [ebx].token == T_CL_BRACKET
            add ebx,16
        .endw
        .if [ebx].token != T_FINAL
            mov rc,asmerr( 2008, [ebx].tokpos )
        .endif

        .if !list_directive
            .if ModuleInfo.list
                LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
            .endif
            .if ModuleInfo.line_queue.head
                RunLineQueue()
            .endif
        .endif
        mov eax,rc
    .until 1
    ret

PragmaDirective endp

PragmaInit proc

    mov ListCount,0
    mov FieldCount,0
    ret

PragmaInit endp

PragmaCheckOpen proc

    .if ListCount || FieldCount

        asmerr( 1010, ".pragma-push-pop" )
    .endif
    ret

PragmaCheckOpen endp

    END


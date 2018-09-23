; PRAGMADIRECTIVE.ASM--
; Copyright (C) 2018 Asmc Developers
;
; Change history:
; 2018-05-04 - .pragma(cref(push, <0|1>))
;              .pragma(cref(pop))
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

MAXSTACK equ 16

    .data

    ListCount dd 0
    PackCount dd 0
    CrefCount dd 0

    PackStack db MAXSTACK dup(0)
    ListStack db MAXSTACK dup(0)
    CrefStack db MAXSTACK dup(0)

    .code

    assume ebx:ptr asmtok

PragmaDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asmtok

  local rc:SINT, list_directive:SINT
  local opndx:expr

    mov rc,NOT_ERROR
    mov list_directive,0

    inc i
    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
        inc i
        add ebx,16
    .endif

    .repeat

        mov esi,[ebx].string_ptr
        mov eax,[esi]
        or  eax,0x20202020
        inc i
        add ebx,16
        .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
            inc i
            add ebx,16
        .endif

        bswap   eax
        .switch eax

        .case "init"
        .case "exit"

            ; .pragma(init(<proc>, <priority>))
            ; .pragma(exit(<proc>, <priority>))

            mov edi,@CStr("dw")
            .if ModuleInfo.Ofssize == USE32
                mov edi,@CStr("dd")
            .endif
            .if ModuleInfo.Ofssize == USE64
                mov edi,@CStr("dq")
            .endif
            lea edx,@CStr("EXIT")
            .if eax == "init"
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
            .if [ebx].token == T_CL_BRACKET
                add ebx,16
            .endif
            .endc

        .case "pack"

            ; .pragma(pack(push, <alignment>))
            ; .pragma(pack(pop))

            .if [ebx].tokval == T_POP

                add ebx,16
                .if [ebx].token == T_CL_BRACKET
                    add ebx,16
                .endif
                .endc .if !PackCount

                dec PackCount
                mov eax,PackCount
                mov al,PackStack[eax]
                mov ModuleInfo.fieldalign,al
                .endc
            .endif

            .endc .if [ebx].tokval != T_PUSH
            .endc .if PackCount >= MAXSTACK

            mov edx,PackCount
            inc PackCount
            mov al,ModuleInfo.fieldalign
            mov PackStack[edx],al
            add ebx,16
            .if [ebx].token == T_OP_BRACKET || [ebx].token == T_COMMA
                add ebx,16
            .endif
            AddLineQueueX( "OPTION FIELDALIGN: %s", [ebx].string_ptr )
            add ebx,16
            .if [ebx].token == T_CL_BRACKET
                add ebx,16
            .endif
            .endc

        .case "list"

            ; .pragma(list(push, 0|1))
            ; .pragma(list(pop))

            inc list_directive

            lea ecx,ListCount
            lea edx,ListStack
            lea edi,ModuleInfo.list

            .if [ebx].tokval == T_POP

                .gotosw(T_POP)
            .endif
            .gotosw(T_PUSH)

        .case "cref"

            ; .pragma(cref(push, 0|1))
            ; .pragma(cref(pop))

            inc list_directive

            lea ecx,CrefCount
            lea edx,CrefStack
            lea edi,ModuleInfo.cref

            .if [ebx].tokval == T_POP

                .gotosw(T_POP)
            .endif

        .case T_PUSH

            .endc .if [ebx].tokval != T_PUSH

            mov eax,[ecx]
            inc eax
            .endc .if eax >= MAXSTACK

            mov [ecx],eax
            mov cl,[edi]
            mov [edx+eax-1],cl

            inc i
            .if [ebx+16].token == T_COMMA

                inc i
            .endif
            .endc .if EvalOperand(
                    &i,
                    tokenarray,
                    ModuleInfo.token_count,
                    &opndx,
                    EXPF_NOUNDEF ) == ERROR

            mov ebx,i
            shl ebx,4
            add ebx,tokenarray
            .if opndx.kind != EXPR_CONST

                asmerr( 2026 )
                .endc
            .endif

            mov eax,opndx.uvalue
            .if eax > 1

                asmerr( 2084 )
                .endc
            .endif

            mov [edi],al
            .if al && list_directive

                or ModuleInfo.line_flags,LOF_LISTED
            .endif
            add ebx,16
            .if [ebx].token == T_CL_BRACKET
                add ebx,16
            .endif
            .endc

        .case T_POP

            mov eax,[ecx]
            .endc .if !eax ; gives an error if nothing pushed
            dec eax
            mov [ecx],eax
            mov al,[edx+eax]
            mov [edi],al

            .if al && list_directive

                or ModuleInfo.line_flags,LOF_LISTED
            .endif
            add ebx,16
            .if [ebx].token == T_CL_BRACKET
                add ebx,16
            .endif
            .endc

        .endsw

        .if [ebx].token == T_CL_BRACKET
            add ebx,16
        .endif
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
    mov PackCount,0
    mov CrefCount,0
    ret

PragmaInit endp

PragmaCheckOpen proc

    .if ListCount || PackCount || CrefCount

        asmerr( 1010, ".pragma-push-pop" )
    .endif
    ret

PragmaCheckOpen endp

    END


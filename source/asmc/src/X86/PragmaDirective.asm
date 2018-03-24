include asmc.inc
include hll.inc

    .code

    assume ebx:ptr asm_tok

PragmaDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asm_tok

  local rc:SINT

    mov rc,NOT_ERROR

    inc i
    mov ebx,i
    shl ebx,4
    add ebx,tokenarray

    .repeat

        mov esi,[ebx].string_ptr
        mov eax,[esi]
        or  eax,0x20202020
        add ebx,16
        .if [ebx].token == T_OP_BRACKET
            add ebx,16
        .endif

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


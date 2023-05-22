; FPUTWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc

    .code

fputws proc uses rsi rdi rbx string:LPWSTR, fp:LPFILE

    ldr rsi,string
    ldr rdi,fp

    mov ebx,wcslen(rsi)

    .new retval:int_t = 0
    .new stb:int_t = _stbuf(rdi)

    .while ebx

        movzx eax,word ptr [rsi]
        mov rcx,[rdi]._iobuf._ptr
        sub [rdi]._iobuf._cnt,2
        .ifl
            .ifd ( _flswbuf(eax, rdi) == -1 )
                mov retval,eax
               .break
            .endif
        .else
            add [rdi]._iobuf._ptr,2
            mov [rcx],ax
        .endif
        dec ebx
        add rsi,2
    .endw
    _ftbuf(stb, rdi)
    .return( retval )

fputws endp

    end

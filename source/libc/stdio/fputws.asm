; FPUTWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include string.inc

    .code

fputws proc uses rbx string:LPWSTR, fp:LPFILE

    ldr rbx,fp

    .new len:int_t = wcslen(string)
    .new retval:size_t = 0
    .new stb:int_t = _stbuf(rbx)

    .while len

        mov rdx,string
        movzx eax,word ptr [rdx]
        mov rcx,[rbx]._iobuf._ptr
        sub [rbx]._iobuf._cnt,2
        .ifl
            .ifd ( _flswbuf(eax, rbx) == -1 )
                mov retval,rax
               .break
            .endif
        .else
            add [rbx]._iobuf._ptr,2
            mov [rcx],ax
        .endif
        dec len
        add string,2
    .endw
    _ftbuf(stb, rbx)
    .return( retval )

fputws endp

    end

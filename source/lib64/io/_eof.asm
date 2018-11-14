; _EOF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

_eof proc uses rsi handle:SINT

    .if _lseeki64(ecx, 0, SEEK_CUR) != -1

        mov rsi,rax
        .if _lseeki64(handle, 0, SEEK_END) != -1

            .if rax != rsi

                _lseeki64(handle, rsi, SEEK_SET)
                xor eax,eax
            .else
                mov eax,1
            .endif
        .endif
    .endif
    ret

_eof endp

    end

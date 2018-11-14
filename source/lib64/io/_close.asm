; _CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

option win64:rsp nosave

.code

_close proc handle:SINT

    lea rax,_osfile
    .if ecx < 3 || ecx >= _nfile || !(byte ptr [rax+rcx] & FH_OPEN)

        xor eax,eax
        mov errno,EBADF
        mov oserrno,eax
    .else

        mov byte ptr [rax+rcx],0
        lea rax,_osfhnd
        mov rcx,[rax+rcx*8]

        .if !CloseHandle(rcx)

            osmaperr()
        .else
            xor eax,eax
        .endif
    .endif
    ret

_close endp

    end

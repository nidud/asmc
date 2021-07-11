; _LSEEKI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdlib.inc
include crtl.inc
include winbase.inc

    .code

_lseeki64 proc handle:SINT, offs:QWORD, pos:UINT

  local lpNewFilePointer:QWORD

    mov r9,r8
    .ifd getosfhnd(ecx) != -1

        .ifd !SetFilePointerEx(rax, rdx, &lpNewFilePointer, r9d)

            _dosmaperr(GetLastError())
        .else
            mov rax,lpNewFilePointer
        .endif
    .endif
    ret
_lseeki64 endp

    end

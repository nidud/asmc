include io.inc
include errno.inc
include stdlib.inc
include crtl.inc
include winbase.inc

    .code

_lseeki64 PROC handle:SINT, offs:QWORD, pos:UINT

    local lpNewFilePointer:QWORD

    mov r9,r8
    .ifd getosfhnd(ecx) != -1

        .ifd !SetFilePointerEx(rax, rdx, &lpNewFilePointer, r9d)

            osmaperr()
        .else
            mov rax,lpNewFilePointer
        .endif
    .endif
    ret
_lseeki64 ENDP

    END

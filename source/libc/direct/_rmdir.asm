include direct.inc
include errno.inc
include winbase.inc

    .code

_rmdir proc directory:LPSTR

    .if !RemoveDirectoryA(directory)

        RemoveDirectoryW(__allocwpath(directory))
    .endif

    .if !eax
        osmaperr()
    .else
        xor eax,eax
    .endif
    ret

_rmdir endp

    END

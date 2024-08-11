include libc.inc
include sys/syscall.inc

    .code

_start proc

    sys_write(1, "Press any key to continue . . .\n", sizeof(DS0000)-1)
    sys_read(0, &DS0000, 1)
    sys_exit(0)

_start endp

    end

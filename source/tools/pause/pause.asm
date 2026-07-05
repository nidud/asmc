include libc.inc
include sys/syscall.inc

    .code

_start proc
    sys_write(1, "Press any key to continue . . .", sizeof(D$0000)-1)
    sys_read(0, &D$0000, 1)
    sys_write(1, "\n", 1)
    sys_exit(0)
    endp
    end

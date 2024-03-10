include libc.inc
include sys/syscall.inc

    .code

_start proc

    sys_write(1, "Hello world!\n", sizeof(DS0000))
    sys_exit(0)

_start endp

    end

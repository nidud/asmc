include libc.inc
include sys/syscall.inc

.data
 msg char_t "Press any key to continue . . .",0

.code

_start proc
    sys_write(1, &msg, sizeof(msg)-1)
    sys_read(0, &msg, 1)
    sys_write(1, "\n", 1)
    sys_exit(0)
    endp
    end

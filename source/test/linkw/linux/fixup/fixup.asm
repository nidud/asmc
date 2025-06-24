
; LINKW 2.10 - fixup adjustment for elf64

include libc.inc
include sys/syscall.inc

.data
        db "-3 "
DS0003  db "hello "
        db "world!",10

.code

_start proc

    sys_write( 1, addr DS0003-3, 3 )
    sys_write( 1, addr DS0003,   6 )
    sys_write( 1, addr DS0003+6, 7 )
    sys_exit ( 0 )

_start endp

    end

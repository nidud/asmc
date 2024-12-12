; TCSETATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include termios.inc
include sys/syscall.inc
include sys/ioctl.inc

    .code

tcsetattr proc fd:int_t, cmd:int_t, termios_p:ptr termios

    ldr eax,cmd
    ldr rdx,termios_p

    .if ( rdx == NULL )

        .return( _set_errno( EINVAL ) )
    .endif
    .switch eax
    .case TCSANOW
        mov eax,TCSETS
       .endc
    .case TCSADRAIN
        mov eax,TCSETSW
       .endc
    .case TCSAFLUSH
        mov eax,TCSETSF
       .endc
    .default
       .return( _set_errno( EINVAL ) )
    .endsw
    ioctl( ldr(fd), eax, rdx )
    ret

tcsetattr endp

    end

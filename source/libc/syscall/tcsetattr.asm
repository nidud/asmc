; TCSETATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
ifdef __UNIX__
include termios.inc
include sys/syscall.inc
endif

    .code

ifdef __UNIX__
tcsetattr proc uses rsi rdi fd:int_t, cmd:int_t, termios_p:ptr termios

    ldr edi,fd
    ldr esi,cmd
    ldr rdx,termios_p

    .ifs ( edi < 0 )

        .return( _set_errno( EBADF ) )
    .endif
    .if ( rdx == NULL )

        .return( _set_errno( EINVAL ) )
    .endif

    .switch (esi)
    .case TCSANOW
        mov esi,TCSETS
       .endc
    .case TCSADRAIN
        mov esi,TCSETSW
       .endc
    .case TCSAFLUSH
        mov esi,TCSETSF
       .endc
    .default
       .return( _set_errno( EINVAL ) )
    .endsw

    .ifsd ( sys_ioctl(edi, esi, rdx) < 0 )

        neg eax
        _set_errno(eax)
    .endif
    ret

tcsetattr endp
endif
    end

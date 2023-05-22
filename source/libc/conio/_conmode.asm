; _CONMODE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; default (Ubuntu):
;  c_iflag 4500 - IXON|ICRNL|IUTF8
;  c_oflag 0005 - OPOST|ONLCR
;  c_lflag 8A3B - ISIG|ICANON|ECHO|ECHOE|ECHOK|ECHOKE|ECHOCTL|IEXTEN
;
include io.inc
include errno.inc
include conio.inc

.data
 _modein    int_t -1
 _modeout   int_t -1
 _msinput   int_t 0
ifndef __UNIX__
 _concp     int_t 0
 _conoutcp  int_t 0
endif

.code

_consetmode proc uses rbx fd:int_t, mode:uint_t

    ldr ebx,fd
    .if ( ebx != _conout && ebx != _conin )

        _set_errno(EINVAL)
        .return( 0 )
    .endif

ifdef __UNIX__

    .new term:termios

    .if ( ebx == _conout )

        .return( 1 )
    .endif

    .ifsd ( tcgetattr(ebx, &term) < 0 )

        .return( 0 )
    .endif

    mov ebx,mode
    .if ( ebx & ENABLE_MOUSE_INPUT )

        .if ( !_msinput )

            _cwrite(SET_ANY_EVENT_MOUSE)
        .endif
        inc _msinput

    .elseif ( _msinput )

        dec _msinput
        .ifz
            _cwrite(RST_ANY_EVENT_MOUSE)
        .endif
    .endif

    and term.c_iflag, not IUTF8
    and term.c_oflag, not OPOST
    and term.c_lflag, not (_ECHO or ICANON or ISIG)

    .if ( ebx & ENABLE_LINE_INPUT )
        or term.c_lflag,ICANON
    .endif
    .if ( ebx & ENABLE_ECHO_INPUT )
        or term.c_lflag,_ECHO
    .endif
    .if ( ebx & ENABLE_WINDOW_INPUT )
        or term.c_lflag,ISIG
    .endif
    .if ( ebx & ENABLE_IUTF8_INPUT )
        or term.c_iflag,IUTF8
    .endif
    .if ( ebx & ENABLE_VIRTUAL_TERMINAL_INPUT )
        or term.c_oflag,OPOST
    .endif
 if 0
    .if ( ebx == 0 ) ; Raw mode..

        and term.c_iflag, not (IGNBRK or BRKINT or PARMRK or ISTRIP or INLCR or IGNCR or ICRNL or IXON)
        and term.c_oflag, not OPOST
        and term.c_lflag, not (_ECHO or ECHONL or ICANON or ISIG or IEXTEN)
        and term.c_cflag, not (CSIZE or PARENB)
        or  term.c_cflag, CS8
    .endif
 endif

    .ifsd ( tcsetattr(fd, TCSANOW, &term) < 0 )

        .return( 0 )
    .endif
else

    lea rdx,_textmode
    mov cl,[rdx+rbx]

    .if ( mode & ENABLE_IUTF8_INPUT )

        mov byte ptr [rdx+rbx],__IOINFO_TM_UTF8
        .if ( cl != __IOINFO_TM_UTF8 )

            SetConsoleCP(65001)
            SetConsoleOutputCP(65001)
        .endif
    .else
        mov byte ptr [rdx+rbx],__IOINFO_TM_ANSI
        .if ( cl != __IOINFO_TM_ANSI )

            SetConsoleCP(_concp)
            SetConsoleOutputCP(_conoutcp)
        .endif
    .endif

    .if ( mode & ENABLE_MOUSE_INPUT )

        .if ( !_msinput )

            _cwrite(SET_ANY_EVENT_MOUSE)
        .endif
        inc _msinput

    .elseif ( _msinput )

        dec _msinput
        .ifz
            _cwrite(RST_ANY_EVENT_MOUSE)
        .endif
    .endif

    lea rax,_osfhnd
    mov rcx,[rax+rbx*size_t]
    mov edx,mode
    and edx,0x03FF

    .if ( SetConsoleMode(rcx, edx) == 0 )

        _dosmaperr( GetLastError() )
        .return( 0 )
    .endif

endif
   .return( 1 )

_consetmode endp


_congetmode proc uses rbx fd:int_t, mptr:ptr uint_t

    ldr ebx,fd
    .if ( ebx != _conout && ebx != _conin )

        _set_errno(EINVAL)
        .return( 0 )
    .endif

ifdef __UNIX__

    .new term:termios

    .ifsd ( tcgetattr(ebx, &term) < 0 )

        .return( 0 )
    .endif

    xor eax,eax
    .if ( ebx == _conout )

        .if ( term.c_oflag & OPOST )

            mov eax,ENABLE_PROCESSED_OUTPUT or ENABLE_VIRTUAL_TERMINAL_PROCESSING
        .endif
    .else
        .if ( term.c_lflag & ICANON )
            or eax,ENABLE_LINE_INPUT
        .endif
        .if ( term.c_lflag & _ECHO )
            or eax,ENABLE_ECHO_INPUT
        .endif
        .if ( term.c_lflag & ISIG )
            or eax,ENABLE_WINDOW_INPUT
        .endif
        .if ( _msinput )
            or eax,ENABLE_MOUSE_INPUT
        .endif
        .if ( term.c_iflag & IUTF8 )
            or eax,ENABLE_IUTF8_INPUT
        .endif
        .if ( term.c_oflag & OPOST && !( eax & ENABLE_ECHO_INPUT ) )
            or eax,ENABLE_VIRTUAL_TERMINAL_INPUT
        .endif
    .endif

else

   .new mode:uint_t

    lea rax,_osfhnd
    mov rcx,[rax+rbx*size_t]
    .if !GetConsoleMode(rcx, &mode)

        _set_errno(EINVAL)
        .return( 0 )
    .endif

    mov eax,mode
    lea rdx,_textmode
    mov cl,[rdx+rbx]
    .if ( cl == __IOINFO_TM_UTF8 )
        or eax,ENABLE_IUTF8_INPUT
    .endif
    .if ( ebx == _conin && _msinput )
        or eax,ENABLE_MOUSE_INPUT
    .endif
endif
    mov rcx,mptr
    mov [rcx],eax
   .return( 1 )

_congetmode endp


__initmode proc private

    .if ( _conout > 0 )

        _congetmode(_conout, &_modeout)
    .endif
    .if ( _conin > 0 )

        _congetmode(_conin, &_modein)
    .endif
ifndef __UNIX__
    mov _concp,GetConsoleCP()
    mov _conoutcp,GetConsoleOutputCP()
endif
    ret

__initmode endp

__termmode proc private

    .if ( _modeout != -1 )

        .if ( _msinput )
            mov _msinput,1
        .endif
        _consetmode(_conout, _modeout)
    .endif
    .if ( _modein != -1 )

        _consetmode(_conin, _modein)
ifndef __UNIX__
        lea rax,_osfhnd
        mov ecx,_conin
        mov rcx,[rax+rcx*size_t]
        FlushConsoleInputBuffer(rcx)
endif
    .endif
ifndef __UNIX__
    SetConsoleCP(_concp)
    SetConsoleOutputCP(_conoutcp)
endif
    ret

__termmode endp

.pragma init(__initmode, 30)
.pragma exit(__termmode, 10)

    end

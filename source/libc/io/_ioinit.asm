; _IOINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include crtl.inc
ifndef __UNIX__
include winbase.inc
endif

    .data
    _nfile  dd _NFILE_
    _osfile db 3 dup(FOPEN or FDEV or FTEXT)
            db _NFILE_ - 3 dup(0)
ifndef __UNIX__
    _osfhnd HANDLE _NFILE_ dup(-1)
    _ermode dd 5

    .code

_ioinit proc private

    mov _osfhnd[0*HANDLE],GetStdHandle(STD_INPUT_HANDLE)
    mov _osfhnd[1*HANDLE],GetStdHandle(STD_OUTPUT_HANDLE)
    mov _osfhnd[2*HANDLE],GetStdHandle(STD_ERROR_HANDLE)
    mov _ermode,SetErrorMode(SEM_FAILCRITICALERRORS)
    ret

_ioinit endp

else
    .code
endif

_ioexit proc private uses rbx

    .for ( ebx = 3 : ebx < _NFILE_ : ebx++ )

        lea rdx,_osfile
        .if ( BYTE PTR [rdx+rbx] & FOPEN )

            _close( ebx )
        .endif
    .endf
ifndef __UNIX__
    SetErrorMode( _ermode )
endif
    ret

_ioexit endp

ifndef __UNIX__
.pragma init(_ioinit, 1)
endif
.pragma exit(_ioexit, 100)

    end

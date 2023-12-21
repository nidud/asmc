; _IOINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdlib.inc
ifndef __UNIX__
include winbase.inc
endif

    .data
     _nfile     dd _NFILE_
     _ermode    dd 5
     __pioinfo  pioinfo 0

    .code

    assume rbx:pioinfo

_ioinit proc uses rbx

    .if malloc(_NFILE_ * ioinfo)

        mov __pioinfo,rax
        mov rbx,rax

        mov ecx,_NFILE_ * ioinfo
        mov rdx,rdi
        mov rdi,rbx
        xor eax,eax
        rep stosb
        mov rdi,rdx

ifndef __UNIX__
        .for ( rdx = rbx, ecx = 0: ecx < _NFILE_: ecx++, rbx += ioinfo )

            mov [rbx].pipech,10         ; linefeed/newline char
            mov [rbx].pipech2[0],10
            mov [rbx].pipech2[1],10
            dec [rbx].osfhnd
        .endf
        mov rbx,rdx
endif
        mov [rbx].osfile,FOPEN or FDEV or FTEXT
ifndef __UNIX__
        mov [rbx].osfhnd,GetStdHandle(STD_INPUT_HANDLE)
endif
        mov [rbx+ioinfo].osfile,FOPEN or FDEV or FTEXT
ifndef __UNIX__
        mov [rbx+ioinfo].osfhnd,GetStdHandle(STD_OUTPUT_HANDLE)
endif
        mov [rbx+ioinfo*2].osfile,FOPEN or FDEV or FTEXT
ifndef __UNIX__
        mov [rbx+ioinfo*2].osfhnd,GetStdHandle(STD_ERROR_HANDLE)
        mov _ermode,SetErrorMode(SEM_FAILCRITICALERRORS)
endif
    .endif
    ret

_ioinit endp

_ioexit proc uses rbx

    .if ( __pioinfo  )

        .for ( ebx = 3 : ebx < _NFILE_ : ebx++ )
            .if ( _osfile(ebx) & FOPEN )
                _close( ebx )
            .endif
        .endf
        free(__pioinfo)
        mov __pioinfo,0
ifndef __UNIX__
        SetErrorMode( _ermode )
endif
    .endif
    ret

_ioexit endp

.pragma init(_ioinit, 1)
.pragma exit(_ioexit, 100)

    end

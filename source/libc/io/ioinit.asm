; IOINIT.ASM--
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
     _ermode    dd 5
     __pioinfo  pioinfo NULL

    .code

    assume rbx:pioinfo

_ioinit proc uses rbx

    imul ebx,_nfile,ioinfo
    .if malloc(ebx)

        mov __pioinfo,rax
        mov ecx,ebx
        mov rbx,rax
        mov rdx,rdi
        mov rdi,rbx
        xor eax,eax
        rep stosb
        mov rdi,rdx

ifndef __UNIX__
        .for ( rdx = rbx, ecx = 0: ecx < _nfile: ecx++, rbx += ioinfo )

            mov [rbx].pipech,10         ; linefeed/newline char
            mov [rbx].pipech2[0],10
            mov [rbx].pipech2[1],10
            dec [rbx].osfhnd
        .endf
        mov rbx,rdx
        mov [rbx].osfhnd,GetStdHandle(STD_INPUT_HANDLE)
        mov [rbx+ioinfo].osfhnd,GetStdHandle(STD_OUTPUT_HANDLE)
        mov [rbx+ioinfo*2].osfhnd,GetStdHandle(STD_ERROR_HANDLE)
        mov _ermode,SetErrorMode(SEM_FAILCRITICALERRORS)
endif
        mov [rbx].osfile,FOPEN or FDEV or FTEXT
        mov [rbx+ioinfo].osfile,FOPEN or FDEV or FTEXT
        mov [rbx+ioinfo*2].osfile,FOPEN or FDEV or FTEXT
    .endif
    ret

_ioinit endp

_ioexit proc uses rbx

    .if ( __pioinfo  )

        .for ( ebx = 3 : ebx < _nfile : ebx++ )
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

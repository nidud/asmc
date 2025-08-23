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

define _NO_CONSOLE_FILENO (-2)

    .data
     _ermode    dd 5
     __pioinfo  pioinfo NULL

    .code

    assume rbx:pioinfo

ifndef __UNIX__

_init_stdhnd proc private uses rsi rbx pio:pioinfo, stdhnd:dword

    ldr rbx,pio
    ldr ecx,stdhnd

    mov rax,[rbx].osfhnd
    .if ( rax == INVALID_HANDLE_VALUE || rax == _NO_CONSOLE_FILENO )

        ; mark the handle as open in text mode.

        mov [rbx].osfile,FOPEN or FTEXT
        mov rsi,GetStdHandle( ecx )
        GetFileType( rax )

        .if ( rsi != INVALID_HANDLE_VALUE && rsi != NULL && eax != FILE_TYPE_UNKNOWN )

            ; obtained a valid HANDLE from GetStdHandle

            mov [rbx].osfhnd,rsi

            ; finish setting osfile: determine if it is a character
            ; device or pipe.

            .if ( al == FILE_TYPE_CHAR )
                or [rbx].osfile,FDEV
            .elseif ( al == FILE_TYPE_PIPE )
                or [rbx].osfile,FPIPE
            .endif

            ; Allocate the lock for this handle.

        .else

            ; For stdin, stdout & stderr, if there is no valid HANDLE,
            ; treat the CRT handle as being open in text mode on a
            ; device with _NO_CONSOLE_FILENO underlying it. We use this
            ; value different from _INVALID_HANDLE_VALUE to distinguish
            ; between a failure in opening a file & a program run
            ; without a console.

            or  [rbx].osfile,FDEV
            mov [rbx].osfhnd,_NO_CONSOLE_FILENO

            ; Also update the corresponding standard IO stream.
            ; Unless stdio was terminated already in __endstdio,
            ; __piob should be statically initialized in __initstdio.

        .endif

    .else

        ; handle was passed to us by parent process. make
        ; sure it is text mode.

        or [rbx].osfile,FTEXT
    .endif
    ret

_init_stdhnd endp

endif

_ioinit proc uses rsi rdi rbx

ifndef __UNIX__

   .new fh:int_t
   .new cfi_len:int_t
   .new StartupInfo:STARTUPINFOW

endif

    imul ebx,_nfile,ioinfo

    .if malloc(ebx)

        mov __pioinfo,rax
        mov ecx,ebx
        mov rbx,rax
        mov rdi,rax
        xor eax,eax
        rep stosb

ifndef __UNIX__

        .for ( rdx = rbx, ecx = 0: ecx < _nfile: ecx++, rbx += ioinfo )

            mov [rbx].pipech,10         ; linefeed/newline char
            mov [rbx].pipech2[0],10
            mov [rbx].pipech2[1],10
            dec [rbx].osfhnd
        .endf
        mov rbx,rdx

        ; Process inherited file handle information, if any

        GetStartupInfoW( &StartupInfo )
        mov rsi,StartupInfo.lpReserved2

        .if ( StartupInfo.cbReserved2 != 0 && rsi != NULL )

            ; Get the number of handles inherited.

            lodsd
            lea rdi,[rsi+rax]
            .if ( eax > _nfile )
                mov eax,_nfile
            .endif
            mov cfi_len,eax

            ; Validate and copy the passed file information

            .for ( fh = 0 : fh < cfi_len : fh++, rsi++, rdi+=intptr_t )
                ;
                ; Copy the passed file info iff it appears to describe
                ; an open, valid file or device.
                ;
                ; Note that GetFileType cannot be called for pipe handles
                ; since it may 'hang' if there is blocked read pending on
                ; the pipe in the parent.
                ;
                mov rcx,[rdi]
                mov al,[rsi]
                .if ( rcx != INVALID_HANDLE_VALUE && rcx != _NO_CONSOLE_FILENO && al & FOPEN )

                    .if ( al & FPIPE )
                        mov eax,1
                    .elseifd ( GetFileType( rcx ) != FILE_TYPE_UNKNOWN )
                        mov eax,1
                    .else
                        xor eax,eax
                    .endif
                    .if ( eax )

                        imul edx,fh,ioinfo
                        mov [rbx+rdx].osfile,[rsi]
                        mov [rbx+rdx].osfhnd,[rdi]
                    .endif
                .endif
            .endf
        .endif
        _init_stdhnd(rbx, STD_INPUT_HANDLE)
        _init_stdhnd(&[rbx+ioinfo], STD_OUTPUT_HANDLE)
        _init_stdhnd(&[rbx+ioinfo*2], STD_ERROR_HANDLE)
        mov _ermode,SetErrorMode(SEM_FAILCRITICALERRORS)
else
        mov [rbx].osfile,FOPEN or FDEV or FTEXT
        mov [rbx+ioinfo].osfile,FOPEN or FDEV or FTEXT
        mov [rbx+ioinfo*2].osfile,FOPEN or FDEV or FTEXT
endif
    .endif
    ret

_ioinit endp


_ioterm proc uses rbx

    .if ( __pioinfo )

        .for ( ebx = 3 : ebx < _nfile : ebx++ )
            .if ( _osfile(ebx) & FOPEN )
                _close( ebx )
            .endif
        .endf
        free(__pioinfo)
        mov __pioinfo,NULL
ifndef __UNIX__
        SetErrorMode( _ermode )
endif
    .endif
    ret

_ioterm endp

.pragma init(_ioinit, 2)
.pragma exit(_ioterm, 100)

    end

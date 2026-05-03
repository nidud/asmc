; POPEN.ASM--
;
; Executes a given program, converting all
; output to upper case.
;

include stdio.inc
include stdlib.inc
include string.inc
include ctype.inc
include tchar.inc

.data
 buffer tchar_t 256 dup(0)

.code

_tmain proc argc:int_t, argv:array_t

    .new fp:LPFILE

    .for ( ebx = 1 : ebx < argc : ebx++ )

        mov rcx,argv
        _tcscat( &buffer, [rcx+rbx*size_t] )
        _tcscat( &buffer, " " )
    .endf

    mov fp,_tpopen( &buffer, "r" )

    .if ( rax == NULL )

        _tperror( "_tpopen" )
        exit( 1 )
    .endif

    .whiled ( getc(fp) != EOF )

        mov ebx,eax
        .ifd islower( ebx )
            mov ebx,toupper( ebx )
        .endif
        fputc( ebx, stdout )
    .endw
    _pclose( fp )
    .return( 0 )

_tmain endp

    end _tstart

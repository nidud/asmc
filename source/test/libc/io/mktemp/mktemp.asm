; MKTEMP.ASM--
;
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/mktemp-wmktemp?view=msvc-170
;

include io.inc
include stdio.inc
include string.inc
include errno.inc
include tchar.inc

.code

_tmain proc

    .new template:tstring_t = "fnXXXXXX"
    .new result:tstring_t
    .new names[27*9]:tchar_t
    .new fp:LPFILE

    .for ( ebx = 0 : ebx < 27 : ebx++ )

        imul ecx,ebx,9*tchar_t
        _tcscpy_s( &names[rcx], 9, template )

        ; Attempt to find a unique filename:

        imul ecx,ebx,9*tchar_t
        mov result,_tmktemp( &names[rcx] ) ; C4996

        ; Note: _mktemp is deprecated; consider using _mktemp_s instead

        .if ( rax == NULL )

            _tprintf( "Problem creating the template\n" )
            .ifd ( _get_errno(NULL) == EINVAL )

                _tprintf( "Bad parameter\n" )
            .elseif ( errno == EEXIST )
                _tprintf( "Out of unique filenames\n" )
            .endif

        .else

            _tfopen_s( &fp, result, "w" );
            .if( fp != NULL )
                _tprintf( "Unique filename is %s\n", result )
            .else
                _tprintf( "Cannot open %s\n", result )
            .endif
            fclose( fp )
        .endif
    .endf
    .return( 0 )

_tmain endp

    end _tstart

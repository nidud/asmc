; SEARCHENV.ASM -- https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/searchenv-wsearchenv?view=msvc-170
;
; This program searches for a file in
; a directory that's specified by an environment variable.;
;
include stdio.inc
include stdlib.inc
include tchar.inc
ifdef __UNIX__
define SFILE <"gcc">
else
define SFILE <"CL.EXE">
endif
.code

_tmain proc argc:int_t, argv:array_t

   .new pathbuffer[_MAX_PATH]:tchar_t
   .new searchfile:tstring_t = SFILE
   .new envvar:tstring_t = "PATH"

    ; Search for file in PATH environment variable:

    _tsearchenv( searchfile, envvar, &pathbuffer ) ; C4996

    ; Note: _searchenv is deprecated; consider using _searchenv_s

    .if ( pathbuffer != 0 )
        _tprintf( "Path for %s:\n%s\n", searchfile, &pathbuffer )
    .else
        _tprintf( "%s not found\n", searchfile )
    .endif
    .return( 0 )

_tmain endp

    end _tstart

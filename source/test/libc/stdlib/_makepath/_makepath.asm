; _MAKEPATH.ASM--
;
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/
;  makepath-wmakepath?view=msvc-170
;

include stdio.inc
include stdlib.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

   .new path_buffer[_MAX_PATH]:char_t
   .new drive[_MAX_DRIVE]:char_t
   .new dir[_MAX_DIR]:char_t
   .new fname[_MAX_FNAME]:char_t
   .new ext[_MAX_EXT]:char_t

    _makepath( &path_buffer, "c", "\\sample\\crt\\", "makepath", "c" )

    printf( "Path created with _makepath: %s\n\n", &path_buffer )

    _splitpath( &path_buffer, &drive, &dir, &fname, &ext )

    printf( "Path extracted with _splitpath:\n" )
    printf( "   Drive: %s\n", &drive )
    printf( "   Dir: %s\n", &dir )
    printf( "   Filename: %s\n", &fname )
    printf( "   Ext: %s\n", &ext )

    xor eax,eax
    ret

_tmain endp

    end _tstart

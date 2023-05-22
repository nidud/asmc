; GETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include winbase.inc
include malloc.inc

    .code

getfattr proc uses rsi rdi lpFilename:string_t

   .new wpath:wstring_t

    ldr rdi,lpFilename

    .ifd ( GetFileAttributesA( rdi ) == -1 )

        .ifd ( __copy_path_to_wide_string( rdi, &wpath ) == true )

            mov edi,GetFileAttributesW( wpath )
            free( wpath )
           .return( edi )
        .endif
        dec rax
    .endif
    ret

getfattr endp

    end


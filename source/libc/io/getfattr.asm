; GETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winbase.inc
include errno.inc

    .code

getfattr proc uses rbx lpFilename:string_t
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov rax,-1
else
   .new wpath:wstring_t

    ldr rbx,lpFilename

    .ifd ( GetFileAttributesA( rbx ) == -1 )

        .ifd ( _pathtow( rbx, &wpath ) == true )

            mov ebx,GetFileAttributesW( wpath )
            free( wpath )
           .return( ebx )
        .endif
        dec rax
    .endif
endif
    ret

getfattr endp

    end


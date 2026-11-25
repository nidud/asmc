; COMMIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

.code

_commit proc fd:int_t
    ldr ecx,fd
    mov rax,_pioinfo( ecx )
    .ifs ( ecx < 0 || ecx >= _nfile || !( [rax].ioinfo.osfile & FOPEN ) )
        .return( _set_errno( EBADF ) )
    .endif
  ifndef __UNIX__
    mov rcx,[rax].ioinfo.osfhnd
  endif
    .ifd ( FlushFileBuffers( rcx ) == 0 )
        .return( _dosmaperr( GetLastError() ) )
    .endif
    .return( 0 )
    endp

    end

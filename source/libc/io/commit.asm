; COMMIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include unistd.inc
include sys/syscall.inc
else
include winbase.inc
endif

.code

_commit proc fd:int_t
ifdef __UNIX__
    .return( _set_errno( ENOSYS ) )
else
    ldr ecx,fd
    mov rdx,_pioinfo( ecx )

    .ifs ( ecx < 0 || edx >= _nfile || !( [rdx].ioinfo.osfile & FOPEN ) )
        .return( _set_errno( EBADF ) )
    .endif
    .ifd ( FlushFileBuffers( [rdx].ioinfo.osfhnd ) == 0 )
        .return( _dosmaperr( GetLastError() ) )
    .endif
    .return( 0 )
endif
_commit endp

    end

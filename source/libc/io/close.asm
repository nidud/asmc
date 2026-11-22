; CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdlib.inc
include winbase.inc

.code

_close proc handle:int_t
    ldr ecx,handle
    .if ( ecx >= 3 && ecx < _nfile )
        _pioinfo(ecx)
        .if ( [rax].ioinfo.osfile & FOPEN )
            mov [rax].ioinfo.osfile,0
            mov [rax].ioinfo.textmode,__IOINFO_TM_ANSI
          ifndef __UNIX__
            mov rcx,[rax].ioinfo.osfhnd
          endif
            .ifd CloseHandle( rcx )
                .return( 0 )
            .endif
            .return( _dosmaperr( GetLastError() ) )
        .endif
    .endif
    _set_errno( EBADF )
    _set_doserrno( 0 )
    .return( 0 )
    endp

    end

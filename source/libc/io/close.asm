; CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdlib.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
endif

    .code

    assume rax:pioinfo

_close proc handle:int_t

    ldr ecx,handle

    .if ( ecx < 3 || ecx >= _nfile )
@@:
        _set_errno( EBADF )
ifndef __UNIX__
        _set_doserrno( 0 )
endif
        .return( 0 )
    .endif

    _pioinfo(ecx)
    test [rax].osfile,FOPEN
    jz @B
    mov [rax].osfile,0
    mov [rax].textmode,__IOINFO_TM_ANSI
ifdef __UNIX__
    .ifsd ( sys_close(ecx) < 0 )

        neg eax
        _set_errno( eax )
else
    .ifd !CloseHandle( [rax].osfhnd )

        _dosmaperr( GetLastError() )
endif
    .else
        xor eax,eax
    .endif
    ret

_close endp

    end

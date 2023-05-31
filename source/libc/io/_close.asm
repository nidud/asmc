; _CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdlib.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc
endif

    .code

_close proc handle:int_t

    ldr ecx,handle
    lea rax,_osfile

    .if ( ecx < 3 || ecx >= _nfile || !( byte ptr [rax+rcx] & FOPEN ) )

        _set_errno( EBADF )
ifndef __UNIX__
        _set_doserrno( 0 )
endif
        xor eax,eax

    .else

        mov byte ptr [rax+rcx],0
ifdef __UNIX__
        .ifsd ( sys_close(ecx) < 0 )

            neg eax
            _set_errno( eax )
            mov rax,-1
else
        lea rax,_osfhnd
        mov rcx,[rax+rcx*size_t]
        .ifd !CloseHandle( rcx )

            _dosmaperr( GetLastError() )
endif
        .else
            xor eax,eax
        .endif
    .endif
    ret

_close endp

    end

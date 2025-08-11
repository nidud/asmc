; SETOSFHND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifndef __UNIX__
include winbase.inc
endif

.code

_set_osfhnd proc fh:int_t, value:intptr_t
ifndef __UNIX__

    ldr ecx,fh
    ldr rdx,value

    _pioinfo(ecx)

    .if ( sdword ptr ecx >= 0 && ecx < _nfile && [rax].ioinfo.osfhnd == INVALID_HANDLE_VALUE )

        mov [rax].ioinfo.osfhnd,rdx
;       .if ( __app_type == _CONSOLE_APP )
            .switch ecx
            .case 0
                SetStdHandle( STD_INPUT_HANDLE, rdx )
               .endc
            .case 1
                SetStdHandle( STD_OUTPUT_HANDLE, rdx )
               .endc
            .case 2
                SetStdHandle( STD_ERROR_HANDLE, rdx )
               .endc
            .endsw
;       .endif
        xor eax,eax
    .else
        _set_doserrno( 0 )
endif
        _set_errno( EBADF )
ifndef __UNIX__
    .endif
endif
    ret

_set_osfhnd endp

    end

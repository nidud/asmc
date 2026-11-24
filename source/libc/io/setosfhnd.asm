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
    .ifs ( ecx >= 0 && ecx < _nfile && [rax].ioinfo.osfhnd == INVALID_HANDLE_VALUE )
        mov [rax].ioinfo.osfhnd,rdx
        mov eax,ecx
        xor ecx,ecx
        .switch pascal eax
        .case 0: mov ecx,STD_INPUT_HANDLE
        .case 1: mov ecx,STD_OUTPUT_HANDLE
        .case 2: mov ecx,STD_ERROR_HANDLE
        .endsw
        .if ( ecx )
            SetStdHandle( ecx, rdx )
        .endif
        xor eax,eax
    .else
        mov _doserrno,0
endif
        _set_errno( EBADF )
ifndef __UNIX__
    .endif
endif
    ret
    endp

    end

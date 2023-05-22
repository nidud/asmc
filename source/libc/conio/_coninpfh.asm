; _CONINPFH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
    _coninpfh intptr_t -2

    .code

ifndef __UNIX__

__initconin proc

    mov _coninpfh,CreateFileW(L"CONIN$", GENERIC_READ or GENERIC_WRITE,
		FILE_SHARE_READ or FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL)
    ret

__initconin endp

__termconin proc

    .if ( _coninpfh > 0 )

	CloseHandle(_coninpfh)
    .endif
    ret

__termconin endp

.pragma init(__initconin, 20)
.pragma exit(__termconin, 100)

endif

    end

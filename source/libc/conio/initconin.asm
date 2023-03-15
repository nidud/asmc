; INITCONIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
    _coninpfh intptr_t -2

    .code

__initconin proc

    CreateFileW(L"CONIN$",
	GENERIC_READ or GENERIC_WRITE,
	FILE_SHARE_READ or FILE_SHARE_WRITE,
	NULL,
	OPEN_EXISTING,
	0,
	NULL)

    mov _coninpfh,rax
    ret

__initconin endp

__termconin proc

    xor eax,eax
    .if _coninpfh > rax

	CloseHandle(_coninpfh)
    .endif
    ret

__termconin endp

.pragma(init(__initconin, 1))
.pragma(exit(__termconin, 2))

    end

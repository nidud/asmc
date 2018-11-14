; INITCON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
    _confh intptr_t -2

    .code

__initconout proc

    CreateFileW(L"CONOUT$",
	GENERIC_WRITE,
	FILE_SHARE_READ or FILE_SHARE_WRITE,
	NULL,
	OPEN_EXISTING,
	0,
	NULL
    )
    mov _confh,rax
    ret

__initconout endp

__termconout proc

    xor eax,eax
    .if _confh > rax

	CloseHandle(_confh)
    .endif
    ret

__termconout endp

	end

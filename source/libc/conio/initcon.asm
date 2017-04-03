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
    mov _confh,eax
    ret

__initconout endp

__termconout proc

    .if _confh != -1 && _confh != -2

	CloseHandle(_confh)
    .endif
    ret

__termconout endp

	END

; _CONFH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
    _confh intptr_t -2

    .code

ifndef __UNIX__

__initconout proc private

    mov _confh,CreateFileW(L"CONOUT$", GENERIC_READ or GENERIC_WRITE, FILE_SHARE_READ or FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL)
    ret

__initconout endp

__termconout proc private

    .if ( _confh > 0 )

	CloseHandle(_confh)
    .endif
    ret

__termconout endp

.pragma init(__initconout, 21)
.pragma exit(__termconout, 100)

endif

    end

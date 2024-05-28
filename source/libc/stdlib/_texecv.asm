; _TEXECV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _execv(char *cmdname, char **argv);
; intptr_t _wexecv(wchar_t *cmdname, wchar_t **argv);
;
include process.inc
include tchar.inc

.code

_texecv proc file:tstring_t, argv:tarray_t
ifdef _WIN64
ifdef __UNIX__
    _texecve( rdi, rsi, _tenviron )
else
    _texecve( rcx, rdx, _tenviron )
endif
else
    _texecve( file, argv, _tenviron )
endif
    ret

_texecv endp

    end

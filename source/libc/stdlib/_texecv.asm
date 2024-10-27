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

if not defined(_UNICODE) and not defined(__UNIX__)
undef execv
ALIAS <execv>=<_execv>
endif

.code

_texecv proc file:tstring_t, argv:tarray_t

    _texecve( ldr(file), ldr(argv), _tenviron )
    ret

_texecv endp

    end

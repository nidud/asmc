; _TEXECVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _execvp(char *cmdname, char **argv);
; intptr_t _wexecvp(wchar_t *cmdname, wchar_t **argv);
;
include process.inc
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef execvp
ALIAS <execvp>=<_execvp>
endif

.code

_texecvp proc file:tstring_t, argv:tarray_t

    _texecvpe( ldr(file), ldr(argv), _tenviron )
    ret

_texecvp endp

    end

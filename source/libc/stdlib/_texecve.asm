; _TEXECVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _execve(char *cmdname, char **argv, char **envp);
; intptr_t _wexecve(wchar_t *cmdname, wchar_t **argv, wchar_t **envp);
;
include process.inc
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef execve
ALIAS <execve>=<_execve>
endif

.code

_texecve proc name:tstring_t, argv:tarray_t, envp:tarray_t

    _tspawnve( _P_OVERLAY, ldr(name), ldr(argv), ldr(envp) )
    ret

_texecve endp

    end

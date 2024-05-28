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

.code

_texecve proc name:tstring_t, argv:tarray_t, envp:tarray_t
ifdef _WIN64
ifdef __UNIX__
    _tspawnve( _P_OVERLAY, rdi, rsi, rdx )
else
    _tspawnve( _P_OVERLAY, rcx, rdx, r8 )
endif
else
    _tspawnve( _P_OVERLAY, name, argv, envp )
endif
    ret
_texecve endp

    end

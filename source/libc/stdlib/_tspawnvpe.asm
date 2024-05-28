; _TSPAWNVPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _spawnvpe(int mode, char *cmdname, char **argv, char **envp);
; intptr_t _wspawnvpe(int mode, wchar_t *cmdname, wchar_t **argv, wchar_t **envp);
;
include process.inc
include errno.inc
include tchar.inc

.code

_tspawnvpe proc mode:int_t, name:tstring_t, argv:tarray_t, envp:tarray_t
ifdef _WIN64
ifdef __UNIX__
    _tspawnve( edi, rsi, rdx, rcx )
else
    _tspawnve( ecx, rdx, r8, r9 )
endif
else
    _tspawnve( mode, name, argv, envp )
endif
    ret

_tspawnvpe endp

    end

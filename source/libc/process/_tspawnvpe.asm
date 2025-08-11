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

if not defined(_UNICODE) and not defined(__UNIX__)
undef spawnvpe
ALIAS <spawnvpe>=<_spawnvpe>
endif

.code

_tspawnvpe proc mode:int_t, name:tstring_t, argv:tarray_t, envp:tarray_t

    _tspawnve( ldr(mode), ldr(name), ldr(argv), ldr(envp) )
    ret

_tspawnvpe endp

    end

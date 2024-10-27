; _TSPAWNV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _spawnv(int mode, char *cmdname, char **argv);
; intptr_t _wspawnv(int mode, wchar_t *cmdname, wchar_t **argv);
;
include process.inc
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef spawnv
ALIAS <spawnv>=<_spawnv>
endif

.code

_tspawnv proc mode:int_t, name:tstring_t, argv:tarray_t

    _tspawnve( ldr(mode), ldr(name), ldr(argv), _tenviron )
    ret

_tspawnv endp

    end

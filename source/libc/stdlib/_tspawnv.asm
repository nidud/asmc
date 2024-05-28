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

.code

_tspawnv proc mode:int_t, name:tstring_t, argv:tarray_t
ifdef _WIN64
ifdef __UNIX__
    _tspawnve( edi, rsi, rdx, _tenviron )
else
    _tspawnve( ecx, rdx, r8, _tenviron )
endif
else
    _tspawnve( mode, name, argv, _tenviron )
endif
    ret

_tspawnv endp

    end

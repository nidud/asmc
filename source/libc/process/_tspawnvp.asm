; _TSPAWNVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _spawnvp(int mode, char *cmdname, char **argv);
; intptr_t _wspawnvp(int mode, wchar_t *cmdname, wchar_t **argv);
;
include process.inc
include errno.inc
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef spawnvp
ALIAS <spawnvp>=<_spawnvp>
endif

.code

_tspawnvp proc mode:int_t, name:tstring_t, argv:tarray_t

    ldr rax,name
    .if ( !rax || tchar_t ptr [rax] == 0 )
        .return( _set_errno(EINVAL) )
    .endif
    _tspawnvpe( ldr(mode), ldr(name), ldr(argv), _tenviron )
    ret

_tspawnvp endp

    end

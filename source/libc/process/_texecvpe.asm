; _TEXECVPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _execvpe(char *cmdname, char **argv, char **envp);
; intptr_t _wexecvpe(wchar_t *cmdname, wchar_t **argv, wchar_t **envp);
;
include process.inc
include errno.inc
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef execvpe
ALIAS <execvpe>=<_execvpe>
endif

.code

_texecvpe proc path:tstring_t, argv:tarray_t, envp:tarray_t

    _texecve( ldr(path), ldr(argv), ldr(envp) )

if 0
   .new retval:int_t = eax
    _get_errno(NULL)
    .if ( retval != -1 || eax != ENOENT && eax != EINVAL )

        .return( retval )
    .endif
    ; ...
endif
    ret

_texecvpe endp

    end

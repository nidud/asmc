; __MKTEMPCMD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *__mktempcmd(char *cmd, int call_cmd);
;
include io.inc
include stdlib.inc
include string.inc
include crtl.inc
include fcntl.inc
include stat.inc
include consx.inc

    .code

__mktempcmd proc cmd:string_t, call_cmd:int_t

  local handle:int_t, batch[_MAX_PATH]:char_t

    .if _open(__mktempname(&batch, "bat"), O_WRONLY or O_CREAT or O_TRUNC, S_IWRITE) == -1

        .return NULL
    .endif
    mov handle,eax

    _write(eax, "@echo off\n", 10)
    .if call_cmd

        _write(handle, "call ", 5)
    .endif
    _write(handle, cmd, strlen(cmd))
    _write(handle, "\n", 1)
    _close(handle)

    strcpy(cmd, &batch)
    ret

__mktempcmd endp

    end

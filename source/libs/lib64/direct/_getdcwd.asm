; _GETDCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include string.inc
include errno.inc
include malloc.inc
include winbase.inc

    .code

_getdcwd proc uses rdi drive:SINT, buffer:LPSTR, maxlen:SINT

  local dirbuf[_MAX_PATH*2]

    lea rdi,dirbuf
    ;
    ; GetCurrentDirectory only works for the default drive
    ;
    .if !drive ; 0 = default, 1 = 'a:', 2 = 'b:', etc.

        GetCurrentDirectory( sizeof(dirbuf), rdi )
    .else
        ;
        ; Not the default drive - make sure it's valid.
        ;
        GetLogicalDrives()
        mov ecx,drive
        shr eax,cl
        .ifnc

            _set_doserrno(ERROR_INVALID_DRIVE)
            _set_errno(EACCES)
            .return 0
        .endif
        ;
        ; Get the current directory string on that drive and its length
        ;
        lea rax,[rcx+0x002E3A40] ; 'X:.'
        lea rcx,drive
        mov [rcx],eax
        GetFullPathName(rcx, sizeof(dirbuf), rdi, 0)
    .endif
    ;
    ; API call failed, or buffer not large enough
    ;
    .if ( eax > maxlen )

        _set_errno(ERANGE)
        .return 0

    .elseif eax

        mov rcx,buffer
        .if !rcx

            inc eax
            .return .if !malloc(eax)
            mov rcx,rax
        .endif
        strcpy(rcx, rdi)
    .endif
    ret

_getdcwd endp

    end

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

    option cstack:on

_getdcwd proc uses rdi drive:SINT, buffer:LPSTR, maxlen:SINT

    mov rdi,alloca(r8d)

    .repeat
        ;
        ; GetCurrentDirectory only works for the default drive
        ;
        .if !drive ; 0 = default, 1 = 'a:', 2 = 'b:', etc.

            GetCurrentDirectory( maxlen, rdi )
        .else
            ;
            ; Not the default drive - make sure it's valid.
            ;
            GetLogicalDrives()
            mov ecx,drive
            shr eax,cl
            .ifnc

                mov _doserrno,ERROR_INVALID_DRIVE
                mov errno,EACCES
                xor eax,eax
                .break
            .endif
            ;
            ; Get the current directory string on that drive and its length
            ;
            lea rax,[rcx+0x002E3A40] ; 'X:.'
            lea rcx,drive
            mov [rcx],eax
            GetFullPathName( rcx, maxlen, rdi, 0 )
        .endif
        ;
        ; API call failed, or buffer not large enough
        ;
        .if eax > maxlen

            mov errno,ERANGE
            xor eax,eax
            .break

        .elseif eax

            mov rcx,buffer
            .if !rcx

                inc eax
                .break .if !malloc( eax )
                mov rcx,rax

            .endif

            strcpy(rcx, rdi)
        .endif
    .until 1
    ret

_getdcwd endp

    end

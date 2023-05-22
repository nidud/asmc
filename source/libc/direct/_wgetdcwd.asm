; _WGETDCWD.ASM--
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

_wgetdcwd proc uses rdi drive:int_t, buffer:ptr wchar_t, maxlen:int_t

    ldr eax,maxlen
    imul ecx,eax,wchar_t
    mov rdi,malloc( ecx )
    ;
    ; GetCurrentDirectory only works for the default drive
    ;
    .if ( drive == 0 ) ; 0 = default, 1 = 'a:', 2 = 'b:', etc.

        GetCurrentDirectoryW( maxlen, rdi )
    .else
        ;
        ; Not the default drive - make sure it's valid.
        ;
        GetLogicalDrives()
        mov ecx,drive
        shr eax,cl
        .ifnc

            free( rdi )
            _set_doserrno(ERROR_INVALID_DRIVE)
            _set_errno(EACCES)
           .return 0
        .endif
        ;
        ; Get the current directory string on that drive and its length
        ;
       .new path[4]:wchar_t

        add cl,'A'-1
        mov path[0],cx
        mov path[2],':'
        mov path[4],'.'
        mov path[6],0

        GetFullPathNameW( &path, maxlen, rdi, 0 )
    .endif
    ;
    ; API call failed, or buffer not large enough
    ;
    .if ( eax > maxlen )

        free( rdi )
        _set_errno( ERANGE )
        .return 0

    .elseif ( eax )

        mov rax,rdi
        mov rcx,buffer

        .if ( rcx )

            wcscpy( rcx, rdi )
            free( rdi )
            mov rax,buffer
        .endif
    .endif
    ret

_wgetdcwd endp

    end

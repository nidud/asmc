; _GETDCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
ifndef __UNIX__
include string.inc
include malloc.inc
include winbase.inc
endif
    .code

_getdcwd proc uses rbx drive:SINT, buffer:LPSTR, maxlen:SINT

ifdef __UNIX__
    _set_errno( ENOSYS )
    xor eax,eax
else
    mov rbx,malloc( maxlen )
    ;
    ; GetCurrentDirectory only works for the default drive
    ;
    .if ( drive == 0 ) ; 0 = default, 1 = 'a:', 2 = 'b:', etc.

        GetCurrentDirectoryA( maxlen, rbx )
    .else
        ;
        ; Not the default drive - make sure it's valid.
        ;
        GetLogicalDrives()
        mov ecx,drive
        shr eax,cl
        .ifnc

            free( rbx )
            _set_doserrno(ERROR_INVALID_DRIVE)
            _set_errno(EACCES)
           .return 0
        .endif
        ;
        ; Get the current directory string on that drive and its length
        ;
       .new path[4]:char_t

        add cl,'A'-1
        mov path[0],cl
        mov path[1],':'
        mov path[2],'.'
        mov path[3],0

        GetFullPathNameA( &path, maxlen, rbx, 0 )
    .endif
    ;
    ; API call failed, or buffer not large enough
    ;
    .if ( eax > maxlen )

        free( rbx )
        _set_errno( ERANGE )
        .return 0

    .elseif ( eax )

        mov rax,rbx
        mov rcx,buffer

        .if ( rcx )

            strcpy( rcx, rbx )
            free( rbx )
            mov rax,buffer
        .endif
    .endif
endif
    ret

_getdcwd endp

    end

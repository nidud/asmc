; _TGETDCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
ifndef __UNIX__
include malloc.inc
include string.inc
include winbase.inc
endif
include tchar.inc

    .code

_tgetdcwd proc uses rbx drive:int_t, buffer:tstring_t, maxlen:int_t
ifdef __UNIX__
    _set_errno( ENOSYS )
    xor eax,eax
else

    ldr eax,maxlen
    imul ecx,eax,tchar_t
    mov rbx,malloc( ecx )
    ;
    ; GetCurrentDirectory only works for the default drive
    ;
    .if ( drive == 0 ) ; 0 = default, 1 = 'a:', 2 = 'b:', etc.

        GetCurrentDirectory( maxlen, rbx )
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
       .new path[4]:tchar_t

        add cl,'A'-1
ifdef _UNICODE
        mov path[tchar_t*0],cx
else
        mov path[tchar_t*0],cl
endif
        mov path[tchar_t*1],':'
        mov path[tchar_t*2],'.'
        mov path[tchar_t*3],0

        GetFullPathName( &path, maxlen, rbx, 0 )
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

            _tcscpy( rcx, rbx )
            free( rbx )
            mov rax,buffer
        .endif
    .endif
endif
    ret

_tgetdcwd endp

    end

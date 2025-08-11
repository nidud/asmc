; DUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include unistd.inc
include sys/syscall.inc
else
include winbase.inc
endif

.code

_dup proc uses rbx fd:int_t

    mov rbx,_pioinfo( ldr(fd) )

    .if ( !( [rbx].ioinfo.osfile & FOPEN ) )
        .return( -1 )
    .endif

ifdef __UNIX__

    .ifsd ( sys_dup( ldr(fd) ) < 0 )

        neg eax
       .return( _set_errno( eax ) )
    .endif
    imul ecx,eax,ioinfo
    add rcx,__pioinfo

else

   .new new_osfhandle:intptr_t

    mov rcx,GetCurrentProcess()
    .ifd ( DuplicateHandle(rcx, [rbx].ioinfo.osfhnd, rcx, &new_osfhandle, 0, TRUE, DUPLICATE_SAME_ACCESS) == 0 )
        .return( _dosmaperr( GetLastError() ) )
    .endif

    .ifd ( _alloc_osfhnd() == -1 )

        CloseHandle( new_osfhandle )
        _set_doserrno( 0 )
        .return( _set_errno( EMFILE ) )
    .endif
    mov rdx,new_osfhandle
    mov [rcx].ioinfo.osfhnd,rdx
    mov dl,[rbx].ioinfo.unicode
    mov [rcx].ioinfo.unicode,dl
endif
    mov dl,[rbx].ioinfo.textmode
    mov [rcx].ioinfo.textmode,dl
    mov dl,[rbx].ioinfo.osfile
    and dl,not FNOINHERIT
    mov [rcx].ioinfo.osfile,dl
    ret

_dup endp

    end

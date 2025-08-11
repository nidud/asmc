; DUP2.ASM--
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

_dup2 proc uses rbx fd:int_t, newfd:int_t

    ldr ecx,fd
    ldr edx,newfd

    mov rbx,_pioinfo( ecx )
    .if ( !( [rbx].ioinfo.osfile & FOPEN ) )
        .return( _set_errno( EBADF ) )
    .endif
    .if ( ecx == edx )
        ;
        ; Since fh1 is known to be open, return 0 indicating success.
        ; This is in conformance with the POSIX specification for dup2.
        ;
        .return( 0 )
    .endif
    .if ( _osfile(edx) & FOPEN )
        ;
        ; close the handle. ignore the possibility of an error - an
        ; error simply means that an OS handle value may remain bound
        ; for the duration of the process.
        ;
        _close( edx )
    .endif

ifdef __UNIX__
    .ifsd ( sys_dup2( fd, newfd ) < 0 )

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
    mov rcx,_pioinfo( newfd )
    mov [rcx].ioinfo.osfhnd,new_osfhandle
    mov [rcx].ioinfo.unicode,[rbx].ioinfo.unicode
endif
    mov [rcx].ioinfo.textmode,[rbx].ioinfo.textmode
    mov al,[rbx].ioinfo.osfile
    and al,not FNOINHERIT
    mov [rcx].ioinfo.osfile,al
    xor eax,eax
    ret

_dup2 endp

    end

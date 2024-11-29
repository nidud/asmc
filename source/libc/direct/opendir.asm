; OPENDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
ifdef __UNIX__
include io.inc
include malloc.inc
include errno.inc
include fcntl.inc
include sys/syscall.inc

define MAXDBUF 1024

.template DIRINF
    fd  int_t ?
    cnt int_t ?
    pos int_t ?
    buf char_t MAXDBUF dup(?)
   .ends

endif

.code

ifdef __UNIX__

    assume rbx:ptr DIRINF

readblk proc private uses rbx dirp:ptr DIR

    ldr rbx,dirp
    .ifsd ( sys_getdents64( [rbx].fd, &[rbx].buf, MAXDBUF ) < 0 )

        neg eax
        _set_errno(eax)
        xor eax,eax

    .elseif ( eax )

        mov [rbx].cnt,eax
        mov [rbx].pos,0
    .endif
    ret

readblk endp


opendir proc uses rbx name:LPSTR

   .new fd:int_t

    ldr rcx,name

    .if ( !rcx || byte ptr [rcx] == 0 )

        _set_errno(ENOENT)
        .return( NULL )
    .endif

    mov fd,_open(rcx, O_RDONLY or O_NONBLOCK or O_DIRECTORY)
    .ifs ( eax < 0 )

       .return( NULL )
    .endif

    .if ( malloc(DIRINF) == 0 )

        _close( fd )
       .return( NULL )
    .endif

    mov rbx,rax
    mov [rbx].fd,fd
    .if ( !readblk(rbx) )

       .return( closedir(rbx) )
    .endif
    mov rax,rbx
    ret

opendir endp


closedir proc uses rbx dirp:ptr DIR

    ldr rbx,dirp
    _close( [rbx].fd )
    free(rbx)
    xor eax,eax
    ret

closedir endp


readdir proc uses rbx dirp:ptr DIR

    ldr rbx,dirp

    mov eax,[rbx].pos

    .if ( [rbx].cnt > eax )

        lea rdx,[rbx].buf
        add rax,rdx

    .else

        .if ( !readblk(rbx) )

            .return
        .endif
        lea rax,[rbx].buf
    .endif
    movzx ecx,[rax].dirent.d_reclen
    add [rbx].pos,ecx
    ret

readdir endp

endif

    end

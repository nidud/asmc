; TTYNAME.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include unistd.inc
include stdio.inc
include string.inc
include termios.inc
include sys/ioctl.inc
include errno.inc

.data?
 ttyname_buf char_t 256 dup(?)

.code
 ttyname proc uses rbx fd:int_t
    .new link_path[256]:char_t
    .new tio:termios
    .ifsd ( ioctl(fd, TCGETS, &tio) < 0 )
        .return( NULL )
    .endif
    sprintf(&link_path, "/proc/self/fd/%d", fd)
    lea rbx,ttyname_buf
    .ifsd ( readlink(&link_path, rbx, 255) < 0 )
        .return( NULL )
    .endif
    mov byte ptr [rbx+rax],0
    .return( rbx )
    endp

    end

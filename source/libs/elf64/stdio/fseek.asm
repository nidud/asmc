; FSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include errno.inc

    .code

    assume rbx:ptr FILE

fseek proc uses rbx r12 r13 fp:ptr FILE, offs:size_t, whence:size_t

    mov rbx,fp
    mov r12,offs
    mov r13,whence

    mov eax,[rbx]._flag
    .if ( whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END &&
          !( eax & _IOREAD or _IOWRT or _IORW ) )

        _set_errno(EINVAL)
        .return -1
    .endif

    and eax,not _IOEOF
    mov [rbx]._flag,eax

    .if ( whence == SEEK_CUR )

        add r12,ftell(rbx)
        mov r13,SEEK_SET
    .endif
    fflush(rbx)

    mov eax,[rbx]._flag
    .if ( eax & _IORW )
        and eax,not (_IOWRT or _IOREAD)
        mov [rbx]._flag,eax
    .elseif ( eax & _IOREAD && eax & _IOMYBUF && !( eax & _IOSETVBUF ) )
        mov [rbx]._bufsiz,_MINIOBUF
    .endif
    .if ( lseek([rbx]._file, r12, r13d) != -1 )
        xor eax,eax
    .endif
    ret

fseek endp

    end

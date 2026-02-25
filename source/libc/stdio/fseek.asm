; FSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdio.inc

    .code

fseek proc uses rbx fp:LPFILE, offs:size_t, whence:int_t

    ldr rbx,fp
    ldr edx,whence

    .if ( edx > SEEK_END || rbx == NULL || !( [rbx].FILE._flag & ( _IOREAD or _IOWRT or _IORW ) ) )
        .return( _set_errno( EINVAL ) )
    .endif
    and [rbx].FILE._flag,not _IOEOF
    .if ( edx == SEEK_CUR )
        add offs,ftell( rbx )
        mov whence,SEEK_SET
    .endif
    fflush( rbx )
    mov eax,[rbx].FILE._flag
    .if ( eax & _IORW )
        and eax,not (_IOWRT or _IOREAD)
        mov [rbx].FILE._flag,eax
    .elseif ( eax & _IOREAD && eax & _IOMYBUF && !( eax & _IOSETVBUF ) )
        mov [rbx].FILE._bufsiz,_MINIOBUF
    .endif
    .if ( _lseek( [rbx].FILE._file, offs, whence ) != -1 )
        xor eax,eax
    .endif
    ret
    endp

    end

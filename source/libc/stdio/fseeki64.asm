; _FSEEKI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdio.inc

    .code

    assume rbx:LPFILE

_fseeki64 proc uses rbx fp:LPFILE, offs:int64_t, whence:int_t

    ldr rbx,fp
    ldr edx,whence

    .if ( edx > SEEK_END || rbx == NULL || !( [rbx]._flag & ( _IOREAD or _IOWRT or _IORW ) ) )
        .return( _set_errno( EINVAL ) )
    .endif

    and [rbx]._flag,not _IOEOF
    .if ( edx == SEEK_CUR )

        _ftelli64( rbx )
        add size_t ptr offs,rax
        mov whence,SEEK_SET
    .endif

    fflush( rbx )
    mov eax,[rbx]._flag
    .if ( eax & _IORW )
        and eax,not (_IOWRT or _IOREAD)
        mov [rbx]._flag,eax
    .elseif ( eax & _IOREAD && eax & _IOMYBUF && !( eax & _IOSETVBUF ) )
        mov [rbx]._bufsiz,_MINIOBUF
    .endif

    .if ( _lseeki64( [rbx]._file, offs, whence ) != -1 )
        xor eax,eax
    .endif
    ret

_fseeki64 endp

    end

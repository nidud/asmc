; FSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include errno.inc
include winbase.inc

    .code

    assume rbx:LPFILE

fseek proc uses rbx fp:LPFILE, offs:size_t, whence:size_t

    ldr rbx,fp
    ldr rdx,whence

    mov eax,[rbx]._flag
    .if ( edx != SEEK_SET && edx != SEEK_CUR && edx != SEEK_END &&
          !( eax & _IOREAD or _IOWRT or _IORW ) )

        _set_errno( EINVAL )
        .return( -1 )
    .endif

    and eax,not _IOEOF
    mov [rbx]._flag,eax

    .if ( edx == SEEK_CUR )

        add offs,ftell( rbx )
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
    mov rcx,whence
    .ifd ( _lseek( [rbx]._file, offs, ecx ) != -1 )
        xor eax,eax
    .endif
    ret

fseek endp

    end

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

fseek proc uses rsi rdi rbx fp:LPFILE, offs:size_t, whence:size_t

    ldr rbx,fp
    ldr rsi,offs
    ldr rdi,whence

    mov eax,[rbx]._flag
    .if ( edi != SEEK_SET && edi != SEEK_CUR && edi != SEEK_END &&
          !( eax & _IOREAD or _IOWRT or _IORW ) )

        _set_errno( EINVAL )
        .return( -1 )
    .endif

    and eax,not _IOEOF
    mov [rbx]._flag,eax

    .if ( edi == SEEK_CUR )

        add rsi,ftell( rbx )
        mov edi,SEEK_SET
    .endif

    fflush( rbx )

    mov eax,[rbx]._flag
    .if ( eax & _IORW )

        and eax,not (_IOWRT or _IOREAD)
        mov [rbx]._flag,eax

    .elseif ( eax & _IOREAD && eax & _IOMYBUF && !( eax & _IOSETVBUF ) )

        mov [rbx]._bufsiz,_MINIOBUF
    .endif

    mov eax,[rbx]._file
    lea rcx,_osfhnd
    mov rcx,[rcx+rax*size_t]

    .ifd ( SetFilePointer( rcx, esi, 0, edi ) == -1 )

        .return _dosmaperr( GetLastError() )
    .endif
    .return( 0 )

fseek endp

    end

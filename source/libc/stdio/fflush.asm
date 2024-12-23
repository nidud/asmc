; FFLUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include stdio.inc

    .code

    assume rbx:LPFILE

fflush proc uses rbx fp:LPFILE

   .new size:uint_t
   .new retval:size_t = 0

    ldr rbx,fp

    mov eax,[rbx]._flag

ifdef STDZIP
    .if !( eax & _IOMEMBUF )
endif
        and eax,_IOREAD or _IOWRT
        .if ( eax == _IOWRT && [rbx]._flag & _IOMYBUF or _IOYOURBUF )

            mov rax,[rbx]._ptr
            sub rax,[rbx]._base
            mov size,eax
            .ifg
                .ifd ( _write( [rbx]._file, [rbx]._base, eax ) == size )

                    .if ( [rbx]._flag & _IORW )
                        and [rbx]._flag,not _IOWRT
                    .endif
ifdef STDZIP
                    .if ( [rbx]._flag & _IOCRC32 )
                        _crc32( [rbx]._crc32, [rbx]._base, size )
                        mov [rbx]._crc32,eax
                    .endif
endif
                .else
                    or [rbx]._flag,_IOERR
                    dec retval
                .endif
            .endif
        .endif
        mov [rbx]._ptr,[rbx]._base
        mov [rbx]._cnt,0
ifdef STDZIP
    .endif
endif
    .return( retval )

fflush endp

    end

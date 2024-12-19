; _TFILWBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include tchar.inc

    .code

    assume rbx:LPFILE

_tfilbuf proc uses rbx fp:LPFILE

ifdef _UNICODE

   .new is_split_character:int_t = 0
   .new leftover_low_order_byte:byte = 0

endif

    ldr rbx,fp
    mov edx,[rbx]._flag
    xor eax,eax
    dec rax

    .if ( !( edx & _IOREAD or _IOWRT or _IORW ) || edx & _IOSTRG )
        .return
    .endif

    .if ( edx & _IOWRT )
        or [rbx]._flag,_IOERR
       .return
    .endif

    or  edx,_IOREAD
    mov [rbx]._flag,edx
    .if ( !( edx & _IOMYBUF or _IONBF or _IOYOURBUF ) )
        _getbuf(rbx)
    .else
        mov rcx,[rbx]._base
ifdef _UNICODE
        .if ( [rbx]._cnt == 1 )
            mov is_split_character,1
            mov al,[rcx]
            mov leftover_low_order_byte,al
        .endif
endif
        mov [rbx]._ptr,rcx
    .endif

    _read([rbx]._file, [rbx]._base, [rbx]._bufsiz)
    mov [rbx]._cnt,eax

    .ifs ( eax < TCHAR )
        .if ( eax )
            mov eax,_IOERR
        .else
            mov eax,_IOEOF
        .endif
        or  [rbx]._flag,eax
        xor eax,eax
        mov [rbx]._cnt,eax
        dec rax
       .return
    .endif
ifndef NOSTDCRC
    .if ( [rbx]._flag & _IOCRC32 )

        _crc32( [rbx]._crc32, [rbx]._base, eax )
        mov [rbx]._crc32,eax
    .endif
endif
    mov edx,[rbx]._flag
    .if ( !( edx & _IOWRT or _IORW ) )

        mov al,_osfile([rbx]._file)
        and al,FTEXT or FEOFLAG
        .if ( al == FTEXT or FEOFLAG)
            or [rbx]._flag,_IOCTRLZ
        .endif
    .endif

    mov eax,[rbx]._bufsiz
    .if ( eax == _MINIOBUF && edx & _IOMYBUF && !( edx & _IOSETVBUF ) )
        mov [rbx]._bufsiz,_INTIOBUF
    .endif

    mov rcx,[rbx]._ptr
ifdef _UNICODE
    .if ( is_split_character )

        ; If the character was split across buffers, we read only one byte
        ; from the new buffer and or it with the leftover byte from the old
        ; buffer.

        movzx eax,leftover_low_order_byte
        mov ah,[rcx]
        dec [rbx]._cnt
        inc [rbx]._ptr

    .else
endif
        sub [rbx]._cnt,TCHAR
        add [rbx]._ptr,TCHAR
        movzx eax,TCHAR ptr [rcx]
ifdef _UNICODE
    .endif
endif
    ret

_tfilbuf endp

    end

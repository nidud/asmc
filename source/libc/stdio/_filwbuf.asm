; _FILWBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

    assume rbx:LPFILE

_filwbuf proc uses rbx fp:LPFILE

   .new is_split_character:int_t = 0
   .new leftover_low_order_byte:byte = 0

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
        .if ( [rbx]._cnt == 1 )
            mov is_split_character,1
            mov al,[rcx]
            mov leftover_low_order_byte,al
        .endif
        mov [rbx]._ptr,rcx
    .endif

    _read([rbx]._file, [rbx]._base, [rbx]._bufsiz)
    mov [rbx]._cnt,eax

    .ifs ( eax < 2 )
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
    .if ( is_split_character )

        ; If the character was split across buffers, we read only one byte
        ; from the new buffer and or it with the leftover byte from the old
        ; buffer.

        movzx eax,leftover_low_order_byte
        mov ah,[rcx]
        dec [rbx]._cnt
        inc [rbx]._ptr

    .else

        sub [rbx]._cnt,2
        add [rbx]._ptr,2
        movzx eax,word ptr [rcx]
    .endif
    ret

_filwbuf endp

    end

; _FILWBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

    assume rsi:LPFILE

_filwbuf proc uses rsi rdi fp:LPFILE

   .new is_split_character:int_t = 0
   .new leftover_low_order_byte:byte = 0

    mov rsi,rcx
    mov edi,[rsi]._flag
    xor eax,eax
    dec rax

    .return .if !(edi & _IOREAD or _IOWRT or _IORW) || edi & _IOSTRG

    .if ( edi & _IOWRT )

        or [rsi]._flag,_IOERR
        .return
    .endif

    or  edi,_IOREAD
    mov [rsi]._flag,edi

    .if !( edi & _IOMYBUF or _IONBF or _IOYOURBUF )

        _getbuf(rsi)
        mov edi,[rsi]._flag
    .else
        mov rcx,[rsi]._base
        .if ( [rsi]._cnt == 1 )
            mov is_split_character,1
            mov al,[rcx]
            mov leftover_low_order_byte,al
        .endif
        mov [rsi]._ptr,rcx
    .endif

    _read([rsi]._file, [rsi]._base, [rsi]._bufsiz)
    mov [rsi]._cnt,eax

    .ifs eax < 2
        .if eax
            mov eax,_IOERR
        .else
            mov eax,_IOEOF
        .endif
        or  [rsi]._flag,eax
        xor eax,eax
        mov [rsi]._cnt,eax
        dec rax
        .return
    .endif

    .if !( edi & _IOWRT or _IORW )

        lea rcx,_osfile
        mov eax,[rsi]._file
        mov al,[rcx+rax]
        and al,FH_TEXT or FH_EOF
        .if al == FH_TEXT or FH_EOF
            or [rsi]._flag,_IOCTRLZ
        .endif
    .endif

    mov eax,[rsi]._bufsiz
    .if ( eax == _MINIOBUF && edi & _IOMYBUF && !( edi & _IOSETVBUF ) )
        mov [rsi]._bufsiz,_INTIOBUF
    .endif

    mov rcx,[rsi]._ptr
    .if ( is_split_character )

        ; If the character was split across buffers, we read only one byte
        ; from the new buffer and or it with the leftover byte from the old
        ; buffer.

        movzx eax,leftover_low_order_byte
        mov ah,[rcx]
        dec [rsi]._cnt
        inc [rsi]._ptr

    .else

        sub [rsi]._cnt,2
        add [rsi]._ptr,2
        movzx eax,word ptr [rcx]
    .endif
    ret

_filwbuf endp

    END

include io.inc
include errno.inc

    .code

_chsize proc uses edi esi handle:SINT, new_size

  local zbuf[512]:byte, offs, count

    .repeat
        ;
        ; save current offset
        ;
        mov offs,_lseek(handle, 0, SEEK_CUR)
        .break .if eax == -1
        ;
        ; seek to end of file
        ;
        .break .if _lseek(handle, 0, SEEK_END) == -1

        .if eax > new_size

            .break .if _lseek(handle, new_size, SEEK_SET) == -1
            ;
            ; Write zero byte at current file position
            ;
            oswrite( handle, addr zbuf, 0 )
        .elseif !ZERO?

            push    eax
            lea edi,zbuf
            sub eax,eax
            mov ecx,512/4
            rep stosd
            pop eax
            mov edi,new_size
            sub edi,eax

            .while  1
                mov count,512
                .if edi < count

                    mov count,edi
                    .break .if !edi
                .endif
                sub edi,count
                .if oswrite(handle, addr zbuf, count) != count

                    mov errno,ERROR_DISK_FULL
                    mov eax,-1

                    .break(1)
                .endif
            .endw
        .endif
        .break .if _lseek(handle, offs, SEEK_SET) == -1

        xor eax,eax
    .until  1
    ret

_chsize endp

    END

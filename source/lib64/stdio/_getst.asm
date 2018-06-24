include stdio.inc

    .code

    option win64:noauto

_getst proc

    .for r11 = &_iob,
         r10 = &[r11+(_NSTREAM_ * sizeof(_iobuf))],
         eax = 0: r11 < r10: r11 += sizeof(_iobuf)

        .if !( [r11]._iobuf._flag & _IOREAD or _IOWRT or _IORW )

            mov [r11]._iobuf._cnt,eax
            mov [r11]._iobuf._flag,eax
            mov [r11]._iobuf._ptr,rax
            mov [r11]._iobuf._base,rax
            dec eax
            mov [r11]._iobuf._file,eax
            mov rax,r11
            .break
        .endif
    .endf
    ret

_getst endp

    END

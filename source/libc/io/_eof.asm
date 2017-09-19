include io.inc

.code

_eof proc uses esi edi handle:SINT

    _lseeki64(handle, 0, SEEK_CUR)

    .if !(eax == -1 && edx == -1)

        mov esi,edx
        mov edi,eax
        _lseeki64(handle, 0, SEEK_END)

        .if !(eax == -1 && edx == -1)

            .if eax == edi && edx == esi

                mov eax,1
            .else

                _lseeki64(handle, esi::edi, SEEK_SET)
                xor eax,eax
            .endif
        .endif
    .endif
    ret

_eof endp

    end


    .code
    option win64:nosave

if ( _CHAR eq 2 )
    reg equ <ax>
else
    reg equ <al>
endif

_FUNC_PROLOGUE
_FUNC_NAME proc _DEST:ptr _CHAR, _SIZE:size_t, _SRC:ptr _CHAR

    .repeat

        _VALIDATE_STRING(rcx, rdx)
        _VALIDATE_POINTER_RESET_STRING(r8, rcx, rdx)

        .fors( --rdx : rdx > 0 : rdx--, rcx += _CHAR, r8 += _CHAR )

            mov reg,[r8]
            mov [rcx],reg
            .break .if !reg
        .endf

        .if (rdx == 0)

            _RESET_STRING(_DEST, _SIZE)
            _RETURN_BUFFER_TOO_SMALL(_DEST, _SIZE)
        .endif
if _SECURECRT_FILL_BUFFER
        mov r8,_SIZE
        sub r8,rdx
        inc r8
        _FILL_STRING(_DEST, _SIZE, r8)
endif
        xor eax,eax

    .until 1
    ret

_FUNC_NAME endp

    end

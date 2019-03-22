
    .code

    option win64:nosave

if ( _CHAR eq 2 )
    reg equ <ax>
else
    reg equ <al>
endif

_FUNC_PROLOGUE
_FUNC_NAME proc frame _DEST:ptr _CHAR, _SIZE:size_t, _SRC:ptr _CHAR

    .repeat

        _VALIDATE_STRING(rcx, rdx)
        _VALIDATE_POINTER_RESET_STRING(r8, rcx, rdx)

        .fors( r10 = rcx,
               r11 = rdx : r11 > 0 && byte ptr [r10] : r11--, r10 += _CHAR )
        .endf

        .if (r11 == 0)

            _RESET_STRING(rcx, rdx)
            _RETURN_DEST_NOT_NULL_TERMINATED(_DEST, _SIZE)
        .endif

        .fors( reg = [r8], [r10] = reg, --r11 : r11 > 0 && reg : r11--,
                r8 += _CHAR, r10 += _CHAR, reg = [r8], [r10] = reg )
        .endf

        .if (r11 == 0)

            _RESET_STRING(rcx, rdx)
            _RETURN_BUFFER_TOO_SMALL(rcx, rdx)
        .endif

if _SECURECRT_FILL_BUFFER
        mov r8,rdx
        sub r8,r11
        inc r8
        _FILL_STRING(rcx, rdx, r8)
endif
        xor eax,eax

    .until 1
    ret

_FUNC_NAME endp

    end

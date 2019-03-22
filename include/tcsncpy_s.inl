
    .code

if ( _CHAR eq 2 )
    reg equ <ax>
else
    reg equ <al>
endif

_FUNC_PROLOGUE
_FUNC_NAME proc frame _DEST:ptr _CHAR, _SIZE:size_t, _SRC:ptr _CHAR, _COUNT:size_t

    .repeat

        .if (r9 == 0 && rcx == NULL && rdx == 0)

            ;; this case is allowed; nothing to do
            _RETURN_NO_ERROR()
        .endif

        ;; validation section
        _VALIDATE_STRING(rcx, rdx)
        .if (r9 == 0)

            ;; notice that the source string pointer can be NULL in this case
            _RESET_STRING(rcx, rdx)
            _RETURN_NO_ERROR()
        .endif
        _VALIDATE_POINTER_RESET_STRING(r8, rcx, rdx)

        ;p = _DEST;
        ;available = _SIZE;
        .if (r9 == _TRUNCATE)

            .fors( --rdx : rdx > 0 : rdx--, rcx += _CHAR, r8 += _CHAR )

                mov reg,[r8]
                mov [rcx],reg
                .break .if !reg
            .endf

        .else

            .ASSERT((!_CrtGetCheckCount() || _COUNT < _SIZE), L"Buffer is too small")

            .fors( --r9, --rdx : rdx > 0 && r9 >  0 : rdx--, r9--, rcx += _CHAR, r8 += _CHAR )

                mov reg,[r8]
                mov [rcx],reg
                .break .if !reg

            .endf

            .if (r9 == 0)

                xor reg,reg
                mov [rcx],reg
            .endif
        .endif

        mov rcx,_DEST
        mov r10,_SIZE

        .if (rdx == 0)

            .if (r9 == _TRUNCATE)

                xor reg,reg
                mov [rcx+r10-_CHAR],reg
                _RETURN_TRUNCATE()
            .endif
            _RESET_STRING(rcx, r10)
            _RETURN_BUFFER_TOO_SMALL(rcx, r10)
        .endif

if _SECURECRT_FILL_BUFFER
        mov r8,r10
        sub r8,rdx
        inc r8
        _FILL_STRING(rcx, r10, r8)
endif
        ;_RETURN_NO_ERROR()
        xor eax,eax

    .until 1
    ret

_FUNC_NAME endp

    end

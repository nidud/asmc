
    .code

if ( _CHAR eq 2 )
    reg equ <ax>
else
    reg equ <al>
endif

_FUNC_PROLOGUE
_FUNC_NAME proc uses rsi rdi rbx _DEST:ptr _CHAR, _SIZE:size_t, _SRC:ptr _CHAR, _COUNT:size_t
ifdef _WIN64
    mov rsi,r8
    mov rdi,rcx
    mov rbx,rdx
else
    mov esi,_SRC
    mov edi,_DEST
    mov ebx,_SIZE
endif
    .repeat

        .if ( _COUNT == 0 && rdi == NULL && rbx == 0 )

            ; this case is allowed; nothing to do
            _RETURN_NO_ERROR()
        .endif

        ; validation section
        _VALIDATE_STRING( rdi, rbx )
        .if ( _COUNT == 0 )

            ; notice that the source string pointer can be NULL in this case
            _RESET_STRING( rdi, rbx )
            _RETURN_NO_ERROR()
        .endif
        _VALIDATE_POINTER_RESET_STRING( rsi, rdi, rbx )

        ;p = _DEST;
        ;available = _SIZE;
        .if ( _COUNT == _TRUNCATE )

            .fors ( --rbx : rbx > 0 : rbx--, rdi += _CHAR, rsi += _CHAR )

                mov reg,[rsi]
                mov [rdi],reg
                .break .if !reg
            .endf

        .else

            .ASSERT((!_CrtGetCheckCount() || _COUNT < _SIZE), L"Buffer is too small")

            .fors( --_COUNT, --rbx : rbx > 0 && _COUNT >  0 : rbx--, _COUNT--, rdi += _CHAR, rsi += _CHAR )

                mov reg,[rsi]
                mov [rdi],reg
                .break .if !reg

            .endf

            .if ( _COUNT == 0 )

                xor reg,reg
                mov [rdi],reg
            .endif
        .endif

        mov rdi,_DEST
        mov rsi,_SIZE

        .if ( rbx == 0 )

            .if ( _COUNT == _TRUNCATE )

                xor reg,reg
                mov [rdi+rsi-_CHAR],reg
                _RETURN_TRUNCATE()
            .endif
            _RESET_STRING( rdi, rsi )
            _RETURN_BUFFER_TOO_SMALL( rdi, rsi )
        .endif

if _SECURECRT_FILL_BUFFER
        mov rcx,rsi
        sub rcx,rbx
        inc rcx
        _FILL_STRING( rdi, rsi, rcx )
endif
        ;_RETURN_NO_ERROR()
        xor eax,eax

    .until 1
    ret

_FUNC_NAME endp

    end

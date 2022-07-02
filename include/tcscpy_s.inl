
    .code

if ( _CHAR eq 2 )
    reg equ <ax>
else
    reg equ <al>
endif

_FUNC_PROLOGUE
_FUNC_NAME proc uses rsi rdi rbx _DEST:ptr _CHAR, _SIZE:size_t, _SRC:ptr _CHAR

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

        _VALIDATE_STRING( rdi, rbx )
        _VALIDATE_POINTER_RESET_STRING( rsi, rdi, rbx )

        .fors ( --rbx : rbx > 0 : rbx--, rdi+=_CHAR, rsi+=_CHAR )

            mov reg,[rsi]
            mov [rdi],reg
            .break .if !reg
        .endf

        .if ( rbx == 0 )

            _RESET_STRING(_DEST, _SIZE)
            _RETURN_BUFFER_TOO_SMALL(_DEST, _SIZE)
        .endif
if _SECURECRT_FILL_BUFFER
        mov rcx,_SIZE
        sub rcx,rbx
        inc rcx
        _FILL_STRING(_DEST, _SIZE, rcx)
endif
        xor eax,eax

    .until 1
    ret

_FUNC_NAME endp

    end


    .code

if ( _CHAR eq 2 )
    reg equ <ax>
else
    reg equ <al>
endif

_FUNC_PROLOGUE
_FUNC_NAME proc uses rsi rdi rbx _DEST:ptr _CHAR, _SIZE:size_t, _SRC:ptr _CHAR

ifdef _WIN64
 ifdef __UNIX__
    mov rbx,rsi
    mov rsi,rdx
 else
    mov rsi,r8
    mov rdi,rcx
    mov rbx,rdx
 endif
else
    mov esi,_SRC
    mov edi,_DEST
    mov ebx,_SIZE
endif

    _VALIDATE_STRING( rdi, rbx )
    _VALIDATE_POINTER_RESET_STRING( rsi, rdi, rbx )

    .fors( rcx = rdi,
           rdx = rbx
           : rdx > 0 && _CHAR ptr [rcx]
           : rdx--, rcx+=_CHAR )
    .endf

    .if ( rdx == 0 )

        _RESET_STRING( rdi, rbx )
        _RETURN_DEST_NOT_NULL_TERMINATED(_DEST, _SIZE)
    .endif

    .fors( reg = [rsi],
           [rcx] = reg,
           --rdx
           : rdx > 0 && reg
           : rdx--,
             rsi += _CHAR,
             rcx += _CHAR,
             reg = [rsi],
             [rcx] = reg
         )
    .endf

    .if ( rdx == 0 )

        _RESET_STRING( rdi, rbx )
        _RETURN_BUFFER_TOO_SMALL( rdi, rbx )
    .endif

if _SECURECRT_FILL_BUFFER
    mov rcx,rbx
    sub rcx,rdx
    inc rcx
    _FILL_STRING( rdi, rbx, rcx )
endif
    xor eax,eax
    ret

_FUNC_NAME endp

    end

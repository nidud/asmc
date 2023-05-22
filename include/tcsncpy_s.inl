
    .code

if ( _CHAR eq 2 )
    reg equ <ax>
else
    reg equ <al>
endif

_FUNC_PROLOGUE
_FUNC_NAME proc uses rsi rbx _DEST:ptr _CHAR, _SIZE:size_t, _SRC:ptr _CHAR, _COUNT:size_t
ifdef _WIN64
 ifdef __UNIX__
    mov rbx,rdi
    mov rax,rcx
    mov rcx,rsi
 else
    mov rbx,rcx
    mov rcx,rdx
    mov rdx,r8
    mov rax,r9
 endif
else
    mov edx,_SRC
    mov ebx,_DEST
    mov ecx,_SIZE
    mov eax,_COUNT
endif

    .if ( rax == 0 && rbx == NULL && rcx == 0 )
        .return
    .endif

    _VALIDATE_STRING( rbx, rcx )

    .if ( rax == 0 )

        ; notice that the source string pointer can be NULL in this case

        mov [rbx],reg
       .return
    .endif

    _VALIDATE_POINTER_RESET_STRING( rdx, rbx, rcx )

    mov rsi,rax
    .if ( rax == _TRUNCATE )

        .fors ( --rcx : rcx > 0 : rcx--, rbx+=_CHAR, rdx+=_CHAR )

            mov reg,[rdx]
            mov [rbx],reg
            .break .if !reg
        .endf

    .else

        .fors ( --rsi, --rcx : rcx > 0 && rsi >  0 : rcx--, rsi--, rbx+=_CHAR, rdx+=_CHAR )

            mov reg,[rdx]
            mov [rbx],reg
            .break .if !reg
        .endf

        .if ( rsi == 0 )

            xor reg,reg
            mov [rbx],reg
        .endif
    .endif

    mov rbx,_DEST
    mov rdx,_SIZE

    .if ( rcx == 0 )

        .if ( rsi == _TRUNCATE )

            xor reg,reg
            mov [rbx+rdx-_CHAR],reg
            _RETURN_TRUNCATE()
        .endif
        _RESET_STRING( rbx, rdx )
        _RETURN_BUFFER_TOO_SMALL( rbx, rdx )
    .endif

if _SECURECRT_FILL_BUFFER
    mov rax,rdx
    sub rax,rcx
    inc rax
    _FILL_STRING( rbx, rdx, rax )
endif
    xor eax,eax
    ret

_FUNC_NAME endp

    end

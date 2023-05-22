
    .code

if ( _CHAR eq 2 )
    reg equ <ax>
else
    reg equ <al>
endif

_LOAD_DEST_SIZE macro
if defined(_WIN64) and defined(__UNIX__)
    mov rbx,rdi
ifdef _DEBUG
    mov rcx,rsi
endif
else
    mov rbx,_DEST
ifdef _DEBUG
    mov rcx,_SIZE
endif
endif
exitm<>
endm

_FUNC_PROLOGUE
_FUNC_NAME proc uses rbx _DEST:ptr _CHAR, _SIZE:size_t, _SRC:ptr _CHAR
ifdef _WIN64
 ifdef __UNIX__
    mov rbx,rdi
    mov rcx,rsi
 else
    mov rbx,rcx
    mov rcx,rdx
    mov rdx,r8
 endif
else
    mov edx,_SRC
    mov ebx,_DEST
    mov ecx,_SIZE
endif

    _VALIDATE_STRING( rbx, rcx )
    _VALIDATE_POINTER_RESET_STRING( rdx, rbx, rcx )

    .fors ( --rcx : rcx > 0 : rcx--, rbx+=_CHAR, rdx+=_CHAR )

        mov reg,[rdx]
        mov [rbx],reg
        .break .if !reg
    .endf

    .if ( rcx == 0 )

        _LOAD_DEST_SIZE()
        _RESET_STRING(rbx, rcx)
        _RETURN_BUFFER_TOO_SMALL(rbx, rcx)
    .endif
if _SECURECRT_FILL_BUFFER
    mov rdx,rcx
    _LOAD_DEST_SIZE()
    mov rax,rcx
    sub rax,rdx
    inc rax
    _FILL_STRING(rbx, rcx, rax)
endif
    xor eax,eax
    ret

_FUNC_NAME endp

    end

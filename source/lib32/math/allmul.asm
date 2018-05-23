    .486
    .model flat, c
    .code

_U8M proto

__llmul:: ; PellesC
_allmul::

    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    _U8M
    pop     ebx
    ret     16

    END

; _ndtoa() - Converts an unsigned integer to a string
;
include intn.inc
include string.inc
include alloc.inc

option cstack:on

    .code

_ndtoa proc uses rsi rdi rbx number:ptr, string:ptr, radix:dword, n:dword

local nul:ptr, divisor:ptr

    mov ebx,n
    shl ebx,5
    mov rdi,alloca(ebx)
    mov ecx,n
    mov rsi,number
    mov number,rax
    rep movsq

    xor eax,eax
    mov ecx,n
    mov edx,radix
    mov divisor,rdi
    mov rbx,rdi
    rep stosq
    mov [rbx],dl

    mov ecx,n
    mov nul,rdi
    lea rbx,[rdi+rcx*8]
    add ecx,ecx
    rep stosq

    mov rsi,number
    mov rdi,string

    .while 1

        _divnd(rsi, divisor, rbx, n)

        mov al,[rbx]
        add al,'0'
        cmp al,'9' + 1
        cmc
        sbb cl,cl
        and cl,7
        add al,cl
        stosb

        .break .if !_cmpnd(rsi, nul, n)
    .endw
    xor eax,eax
    mov [rdi],al
    dec rdi
    .while rdi > string && byte ptr [rdi] == '0'
        mov [rdi],al
        dec rdi
    .endw

    _strrev(string)
    ret

_ndtoa endp

    end

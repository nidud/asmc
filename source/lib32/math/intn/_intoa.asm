; _ndtoa() - Converts an signed integer to a string
;
include intn.inc
include string.inc
include malloc.inc

    .code

_intoa proc uses esi edi ebx number:ptr, string:ptr, radix:dword, n:dword

local nul, sign

    mov ebx,n
    shl ebx,4
    mov edi,alloca(ebx)
    mov ecx,n
    mov esi,number
    mov number,eax
    rep movsd

    xor eax,eax
    mov sign,eax
    .if byte ptr [edi-1] & 0x80
        inc sign
    .endif
    mov ecx,n
    mov edx,radix
    mov radix,edi
    mov ebx,edi
    rep stosd
    mov [ebx],edx

    mov ecx,n
    mov nul,edi
    lea ebx,[edi+ecx*4]
    add ecx,ecx
    rep stosd

    mov esi,number
    mov edi,string
    .if sign
        mov byte ptr [edi],'-'
        inc edi
        mov string,edi
        _negnd(esi, n)
    .endif

    .while 1

        _divnd(esi, radix, ebx, n)

        mov al,[ebx]
        add al,'0'
        cmp al,'9' + 1
        cmc
        sbb cl,cl
        and cl,7
        add al,cl
        stosb

        .break .if !_cmpnd(esi, nul, n)
    .endw
    xor eax,eax
    mov [edi],al
    dec edi
    .while edi > string && byte ptr [edi] == '0'
        mov [edi],al
        dec edi
    .endw

    _strrev(string)
    .if sign
        dec eax
    .endif
    ret

_intoa endp

    end

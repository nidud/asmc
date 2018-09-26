; _atond() - Converts a string to integer
;
include intn.inc

    .code

_atond proc uses esi edi ebx number:ptr, string:ptr, radix:dword, n:dword

    mov edi,number
    mov ecx,n
    xor eax,eax
    rep stosd

    mov edi,number
    mov esi,string
    mov al,[esi]
    .if al == '+' || al == '-'
        inc esi
    .endif
    push eax

    .for ( ebx = radix, ecx = n, ecx += ecx, n = ecx :: edi = number, esi++ )

        mov al,[esi]
        .break .if !al
        and eax,not 30h
        bt  eax,6
        sbb ecx,ecx

        .for ( ecx &= 55, eax -= ecx, ecx = n: ecx: ecx--,
               eax += edx, [edi] = ax, edi += 2, eax >>= 16 )

            movzx edx,word ptr [edi]
            imul  edx,ebx
        .endf
    .endf

    pop eax
    .if al == '-'
        mov eax,n
        shr eax,1
        _negnd(number, eax)
    .endif
    mov eax,number
    ret

_atond endp

    end

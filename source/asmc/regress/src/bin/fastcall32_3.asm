
    ; v2.34.69 - register param not equal to param index..

    .486
    .model flat, fastcall
    .code

foo proc a1:dword, a2:real4, a3:dword

    add ecx,a1  ; add ecx,ecx
    add edx,a3  ; add edx,edx
    ret         ; ret 4

foo endp

bar proc

;   mov     edx, 3
;   push    0x40000000
;   mov     ecx, 1

    invoke foo, 1, 2.0, 3

;   push    dword ptr [ebx]

    invoke foo, ecx, [ebx], edx
    ret

bar endp

end

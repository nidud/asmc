
    ; watcall( [reg] )

    .486
    .model flat, c
    .code

foo proc watcall a64_l:dword, a64_h:dword, b64_l:dword, b64_h:dword
    ret
foo endp

bar proc
    foo(
        [edi],     ; mov eax, edi      * --> [edi]
        [edi+4],   ; mov edx, [edi+4H]
        [esi],     ; mov ebx, esi      * --> [esi]
        [esi+4]    ; mov ecx, [esi+4H]
       )
    ret
bar endp

    end

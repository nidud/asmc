
    ; 2.32.60 watcall( [reg] )

.code

foo proc watcall a64_l:dword, a64_h:dword, b64_l:dword, b64_h:dword
    ret
    endp

bar proc
    foo(
        [rdi],     ; mov eax, edi      * --> [edi]
        [rdi+4],   ; mov edx, [edi+4H]
        [rsi],     ; mov ebx, esi      * --> [esi]
        [rsi+4]    ; mov ecx, [esi+4H]
       )
    ret
    endp

    end

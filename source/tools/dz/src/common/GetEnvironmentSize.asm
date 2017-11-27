include stdlib.inc

    .code

GetEnvironmentSize proc EnvironmentStrings:LPSTR
    mov edx,edi
    mov edi,EnvironmentStrings
    xor eax,eax
    mov ecx,-1
    .while al != [edi]
	repnz scasb
    .endw
    mov edi,edx
    sub eax,ecx
    ret
GetEnvironmentSize endp

    END

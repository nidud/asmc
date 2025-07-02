; _TTOI128.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_ttoi128 proc string:tstring_t, retval:ptr int128_t

ifdef _WIN64

    ldr r10,string
    .repeat

        movzx eax,tchar_t ptr [r10]
        add r10,tchar_t
    .until eax != ' '

    mov r11d,eax
    .if ( eax == '-' || eax == '+' )
        movzx eax,tchar_t ptr [r10]
        add r10,tchar_t
    .endif

    mov ecx,eax
    xor eax,eax
    xor edx,edx

    .while 1

        sub ecx,'0'

        .break .ifc
        .break .if ecx > 9

        mov     r9,rdx
        mov     r8,rax
        shld    rdx,rax,3
        shl     rax,3
        add     rax,r8
        adc     rdx,r9
        add     rax,r8
        adc     rdx,r9
        add     rax,rcx
        adc     rdx,0
        movzx   ecx,tchar_t ptr [r10]
        add     r10,tchar_t
    .endw

    .if ( r11d == '-' )

        neg rdx
        neg rax
        sbb rdx,0
    .endif
    mov rcx,retval
    .if ( rcx )
        mov [rcx],rax
        mov [rcx+8],rdx
    .endif

else

    push esi
    push edi
    push ebx

    mov esi,string
    .repeat
        movzx eax,tchar_t ptr [esi]
        add esi,tchar_t
    .until eax != ' '

    push eax
    .if ( eax == '-' || eax == '+' )

        movzx eax,tchar_t ptr [esi]
        add esi,tchar_t
    .endif

    mov ecx,eax
    xor eax,eax
    xor edx,edx
    xor ebx,ebx
    xor edi,edi

    .while 1

        sub ecx,'0'

        .break .ifc
        .break .if ecx > 9

        .new hh:dword = edi
        .new hl:dword = ebx
        .new lh:dword = edx
        .new ll:dword = eax

        shld    edi,ebx,3
        shld    ebx,edx,3
        shld    edx,eax,3
        shl     eax,3
        add     eax,ll
        adc     edx,lh
        adc     ebx,hl
        adc     edi,hh
        add     eax,ll
        adc     edx,lh
        adc     ebx,hl
        adc     edi,hh
        add     eax,ecx
        adc     edx,0
        adc     ebx,0
        adc     edi,0
        movzx   ecx,tchar_t ptr [esi]
        add     esi,tchar_t
    .endw

    pop ecx
    .if ( ecx == '-' )

        neg edi
        neg ebx
        sbb edi,0
        neg edx
        sbb ebx,0
        neg eax
        sbb edx,0
    .endif

    mov ecx,retval
    .if ( ecx )
        mov [ecx+0x0],eax
        mov [ecx+0x4],edx
        mov [ecx+0x8],ebx
        mov [ecx+0xC],edi
    .endif

    pop ebx
    pop edi
    pop esi
endif
    ret

_ttoi128 endp

    end

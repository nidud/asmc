; _ATOI128.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_atoi128 proc string:string_t, retval:ptr int128_t

ifdef _WIN64

    ldr r10,string
    xor ecx,ecx
    .repeat

        mov al,[r10]
        inc r10
    .until al != ' '

    mov r11b,al
    .if ( al == '-' || al == '+' )
        mov al,[r10]
        inc r10
    .endif

    mov cl,al
    xor eax,eax
    xor edx,edx

    .while 1

        sub cl,'0'

        .break .ifc
        .break .if cl > 9

        mov r9,rdx
        mov r8,rax
        shld rdx,rax,3
        shl rax,3
        add rax,r8
        adc rdx,r9
        add rax,r8
        adc rdx,r9
        add rax,rcx
        adc rdx,0
        mov cl,[r10]
        inc r10
    .endw

    .if ( r11b == '-' )

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
    xor ecx,ecx

    .repeat
        mov al,[esi]
        inc esi
    .until al != ' '

    push eax

    .if ( al == '-' || al == '+' )
        mov al,[esi]
        inc esi
    .endif

    mov cl,al
    xor eax,eax
    xor edx,edx
    xor ebx,ebx
    xor edi,edi

    .while 1

        sub cl,'0'

        .break .ifc
        .break .if cl > 9

        .new hh:dword = edi
        .new hl:dword = ebx
        .new lh:dword = edx
        .new ll:dword = eax

        shld edi,ebx,3
        shld ebx,edx,3
        shld edx,eax,3
        shl eax,3

        add eax,ll
        adc edx,lh
        adc ebx,hl
        adc edi,hh

        add eax,ll
        adc edx,lh
        adc ebx,hl
        adc edi,hh

        add eax,ecx
        adc edx,0
        adc ebx,0
        adc edi,0

        mov cl,[esi]
        inc esi
    .endw

    pop ecx

    .if ( cl == '-' )

        neg edi
        neg ebx
        sbb edi,0
        neg edx
        sbb ebx,0
        neg eax
        sbb edx,0
    .endif

    mov ecx,retval
    .if ( ecx ) ; ?
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

_atoi128 endp

    end

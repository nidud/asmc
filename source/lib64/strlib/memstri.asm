; MEMSTRI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

memstri::

    mov     r10,rcx ; s1
    mov     rcx,rdx ; l1

    movzx   eax,BYTE PTR [r8] ; toupper() and tolower() * 16
    sub     al,'A'
    cmp     al,'Z'-'A'+1
    sbb     dl,dl
    and     dl,'a'-'A'
    add     al,dl
    add     al,'A'
    imul    eax,eax,0x01010101
    movd    xmm1,eax
    pshufd  xmm1,xmm1,0

    movzx   eax,al
    sub     al,'a'
    cmp     al,'z'-'a'+1
    sbb     dl,dl
    and     dl,'a'-'A'
    sub     al,dl
    add     al,'a'
    imul    eax,eax,0x01010101
    movd    xmm2,eax
    pshufd  xmm2,xmm2,0

    lea     r11,[r10+rcx]   ; limit

    .repeat

        .while 1

            mov ecx,r10d    ; align back and read 16 bytes
            and ecx,16-1
            sub r10,rcx     ; find upper/lower first char

            movaps   xmm0,[r10]
            movaps   xmm4,xmm0
            pcmpeqb  xmm0,xmm1
            pmovmskb eax,xmm0
            pcmpeqb  xmm4,xmm2
            pmovmskb edx,xmm4

            add r10,16
            or  eax,edx     ; mask out aligned bytes
            or  edx,-1
            shl edx,cl
            and eax,edx

            .ifz
                .repeat     ; scan aligned blocks

                    .break(1) .if r10 > r11

                    movaps   xmm0,[r10]
                    movaps   xmm4,xmm0
                    pcmpeqb  xmm0,xmm1
                    pmovmskb eax,xmm0
                    pcmpeqb  xmm4,xmm2
                    pmovmskb ecx,xmm4
                    add      r10,16
                    or       eax,ecx

                .untilnz
            .endif

            mov ecx,r9d     ; compare string
            bsf eax,eax
            lea r10,[r10+rax-16]
            lea rax,[r10+rcx-1]
            .break .if rax >= r11

            inc r10
            .repeat

                dec ecx     ; ,match if ecx zero..

                lea rax,[r10-1]
                .break(2) .ifz

                mov al,[r8+rcx]
                .continue(0) .if al == [r10+rcx-1]

                mov dl,[r10+rcx-1]
                mov ah,dl
                sub ax,'AA'
                cmp al,'Z'-'A' + 1
                sbb dl,dl
                and dl,'a'-'A'
                cmp ah,'Z'-'A' + 1
                sbb dh,dh
                and dh,'a'-'A'
                add ax,dx
                add ax,'AA'
            .until al != ah
        .endw
        xor eax,eax
    .until 1
    ret

    end

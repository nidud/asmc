include asmc.inc

    .code

_atoow proc uses esi edi ebx dst:string_t, src:string_t, radix:int_t, bsize:int_t

    mov esi,src
    mov edx,dst
    mov ebx,radix
    mov edi,bsize

ifdef CHEXPREFIX
    movzx eax,word ptr [esi]
    or eax,0x2000
    .if eax == 'x0'
        add esi,2
        sub edi,2
    .endif
endif

    xor eax,eax
    mov [edx],eax
    mov [edx+4],eax
    mov [edx+8],eax
    mov [edx+12],eax

    .repeat

        .if ebx == 16 && edi <= 16

            ; hex value <= qword

            xor ecx,ecx

            .if edi <= 8

                ; 32-bit value

                .repeat
                    mov al,[esi]
                    add esi,1
                    and eax,not 0x30    ; 'a' (0x61) --> 'A' (0x41)
                    bt  eax,6           ; digit ?
                    sbb ebx,ebx         ; -1 : 0
                    and ebx,0x37        ; 10 = 0x41 - 0x37
                    sub eax,ebx
                    shl ecx,4
                    add ecx,eax
                    dec edi
                .untilz

                mov [edx],ecx
                mov eax,edx
                .break
            .endif

            ; 64-bit value

            xor edx,edx

            .repeat
                mov  al,[esi]
                add  esi,1
                and  eax,not 0x30
                bt   eax,6
                sbb  ebx,ebx
                and  ebx,0x37
                sub  eax,ebx
                shld edx,ecx,4
                shl  ecx,4
                add  ecx,eax
                adc  edx,0
                dec  edi
            .untilz

            mov eax,dst
            mov [eax],ecx
            mov [eax+4],edx
            .break

        .elseif ebx == 10 && edi <= 20

            xor ecx,ecx

            mov cl,[esi]
            add esi,1
            sub cl,'0'

            .if edi < 10

                .while 1

                    ; FFFFFFFF - 4294967295 = 10

                    dec edi
                    .break .ifz

                    mov al,[esi]
                    add esi,1
                    sub al,'0'
                    lea ebx,[ecx*8+eax]
                    lea ecx,[ecx*2+ebx]
                .endw

                mov [edx],ecx
                mov eax,edx
                .break

            .endif

            xor edx,edx

            .while 1

                ; FFFFFFFFFFFFFFFF - 18446744073709551615 = 20

                dec edi
                .break .ifz

                mov  al,[esi]
                add  esi,1
                sub  al,'0'
                mov  ebx,edx
                mov  bsize,ecx
                shld edx,ecx,3
                shl  ecx,3
                add  ecx,bsize
                adc  edx,ebx
                add  ecx,bsize
                adc  edx,ebx
                add  ecx,eax
                adc  edx,0
            .endw

            mov eax,dst
            mov [eax],ecx
            mov [eax+4],edx

        .else

            mov bsize,edi
            mov edi,edx
            .repeat
                mov al,[esi]
                and eax,not 0x30
                bt  eax,6
                sbb ecx,ecx
                and ecx,0x37
                sub eax,ecx
                mov ecx,8
                .repeat
                    movzx edx,word ptr [edi]
                    imul  edx,ebx
                    add   eax,edx
                    mov   [edi],ax
                    add   edi,2
                    shr   eax,16
                .untilcxz
                sub edi,16
                add esi,1
                dec bsize
            .untilz
            mov eax,dst
        .endif
    .until 1
    ret

_atoow endp

    END

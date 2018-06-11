;
; void _atoow( void *dst, const char *src, int radix, int size );
;
    .code

_atoow::

    movzx eax,word ptr [rdx]
    or eax,0x2000
    .if eax == 'x0'
        add rdx,2
        sub r9d,2
    .endif

    xor eax,eax
    mov [rcx],rax
    mov [rcx+8],rax

    .if r8d == 16 && r9d <= 16

        ; hex value <= qword

        xor r10d,r10d

        .repeat
            mov al,[rdx]
            inc rdx
            and eax,not 0x30    ; 'a' (0x61) --> 'A' (0x41)
            bt  eax,6           ; digit ?
            sbb r11d,r11d       ; -1 : 0
            and r11d,0x37       ; 10 = 0x41 - 0x37
            sub eax,r11d
            shl r10,4
            add r10,rax
            dec r9d
        .untilz

        mov [rcx],r10
        ret
    .endif

    .if r8d == 10 && r9d <= 20

        xor r10d,r10d
        mov r10b,[rdx]
        inc rdx
        sub r10b,'0'

        .while 1

            dec r9d
            .break .ifz

            mov al,[rdx]
            inc rdx
            sub al,'0'
            lea r8,[r10*8+rax]
            lea r10,[r10*2+r8]
        .endw

        mov [rcx],r10
        ret

    .endif

    mov r10,rcx
    .repeat
        mov al,[rdx]
        and eax,not 0x30
        bt  eax,6
        sbb ecx,ecx
        and ecx,0x37
        sub eax,ecx
        mov ecx,8
        .repeat
            movzx r11d,word ptr [r10]
            imul  r11d,r8d
            add   eax,r11d
            mov   [r10],ax
            add   r10,2
            shr   eax,16
        .untilcxz
        sub r10,16
        inc rdx
        dec r9d
    .untilz
    ret

    end

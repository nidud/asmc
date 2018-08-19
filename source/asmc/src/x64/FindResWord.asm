include asmc.inc

HASH_TABITEMS   equ 1024

ReservedWord    STRUC 8
next            dw ?    ; index next entry (used for hash table)
len             db ?    ; length of reserved word, i.e. 'AX' = 2
flags           db ?    ; see enum reservedword_flags
_name           LPSTR ? ; reserved word (char[])
ReservedWord    ENDS

externdef ResWordTable:ReservedWord
externdef resw_table:word

    .code

FindResWord::

    lea r8,resw_table
    lea r9,ResWordTable

    assume r9:ptr ReservedWord

    movzx eax,BYTE PTR [rcx]
    or al,0x20

    .if edx < 8

        option switch:table;, switch:regax

        .switch notest rdx

          .case 0
            xor eax,eax
            ret

          .case 1
            mov cl,al
            movzx eax,word ptr [r8+rax*2]
            .if eax
                .repeat
                    lea r8,[rax*2]
                    .if [r9+r8*8].len == 1
                        mov rdx,[r9+r8*8]._name
                        .break .if cl == [rdx]
                    .endif
                    movzx eax,[r9+r8*8].next
                .until !eax
            .endif
            ret

          .case 2
            movzx   edx,BYTE PTR [rcx+1]
            or      edx,0x20
            lea     rax,[rdx+rax*8]
            and     eax,HASH_TABITEMS - 1
            movzx   eax,word ptr [r8+rax*2]
            movzx   ecx,word ptr [rcx]
            or      ecx,0x2020
            .if eax
                .repeat
                    lea r8,[rax*2]
                    .if [r9+r8*8].len == 2
                        mov rdx,[r9+r8*8]._name
                        .break .if cx == [rdx]
                    .endif
                    movzx eax,[r9+r8*8].next
                .until !eax
            .endif
            ret

          .case 3
            movzx   edx,BYTE PTR [rcx+1]
            or      edx,0x20
            lea     rax,[rdx+rax*8]
            movzx   edx,BYTE PTR [rcx+2]
            or      edx,0x20
            lea     rax,[rdx+rax*8]
            mov     edx,eax
            and     edx,not 0x1FFF
            xor     eax,edx
            shr     edx,13
            xor     eax,edx
            and     eax,HASH_TABITEMS - 1
            movzx   eax,word ptr [r8+rax*2]
            mov     ecx,[rcx]
            or      ecx,0x202020
            and     ecx,0xFFFFFF
            .if eax
                .repeat
                    lea r8,[rax*2]
                    .if [r9+r8*8].len == 3
                        mov rdx,[r9+r8*8]._name
                        mov edx,[rdx]
                        and edx,0xFFFFFF
                        .break .if ecx == edx
                    .endif
                    movzx eax,[r9+r8*8].next
                .until !eax
            .endif
            ret

          .case 4
            movzx   edx,BYTE PTR [rcx+1]
            or      dl,0x20
            lea     rax,[rdx+rax*8]
            mov     dl,[rcx+2]
            or      dl,0x20
            lea     rax,[rdx+rax*8]
            mov     edx,eax
            and     edx,not 0x1FFF
            xor     eax,edx
            shr     edx,13
            xor     eax,edx
            movzx   edx,BYTE PTR [rcx+3]
            or      dl,0x20
            lea     rax,[rdx+rax*8]
            mov     edx,eax
            and     edx,not 0x1FFF
            xor     eax,edx
            shr     edx,13
            xor     eax,edx
            and     eax,HASH_TABITEMS - 1
            movzx   eax,word ptr [r8+rax*2]
            mov     ecx,[rcx]
            or      ecx,0x20202020
            .if eax
                .repeat
                    lea r8,[rax*2]
                    .if [r9+r8*8].len == 4
                        mov rdx,[r9+r8*8]._name
                        .break .if ecx == [rdx]
                    .endif
                    movzx eax,[r9+r8*8].next
                .until !eax
            .endif
            ret

          .case 5
          .case 6
          .case 7
            mov r10d,edx
            mov r11,rcx
            mov ecx,1
            .repeat
                movzx edx,BYTE PTR [rcx+r11]
                or  edx,0x20
                lea rax,[rdx+rax*8]
                mov edx,eax
                and edx,not 0x00001FFF
                xor eax,edx
                shr edx,13
                xor eax,edx
                add ecx,1
                cmp ecx,r10d
            .untilnl

            and    eax,HASH_TABITEMS - 1
            movzx  eax,word ptr [r8+rax*2]

            .if eax
                .repeat
                    lea r8,[rax*2]
                    .if [r9+r8*8].len == r10b
                        mov rdx,[r9+r8*8]._name
                        mov ecx,[r11]
                        or  ecx,0x20202020
                        .if ecx == [rdx]
                            mov cl,[r11+4]
                            or  cl,0x20
                            .if cl == [rdx+4]
                                .break .if r10d == 5
                                mov cl,[r11+5]
                                or  cl,0x20
                                .if cl == [rdx+5]
                                    .break .if r10d == 6
                                    mov cl,[r11+6]
                                    or  cl,0x20
                                    .break .if cl == [rdx+6]
                                .endif
                            .endif
                        .endif
                    .endif
                    movzx eax,[r9+r8*8].next
                .until !eax
            .endif
            ret
        .endsw
    .endif

    mov r10d,edx
    mov r11,rcx
    mov ecx,[rcx+1]
    or  ecx,0x20202020

    movzx edx,cl
    lea rax,[rdx+rax*8]
    mov r8d,eax
    and r8d,not 0x1FFF
    xor eax,r8d
    shr r8d,13
    xor eax,r8d

    mov dl,ch
    lea rax,[rdx+rax*8]
    mov r8d,eax
    and r8d,not 0x1FFF
    xor eax,r8d
    shr r8d,13
    xor eax,r8d

    shr ecx,16
    mov dl,cl
    lea rax,[rdx+rax*8]
    mov r8d,eax
    and r8d,not 0x1FFF
    xor eax,r8d
    shr r8d,13
    xor eax,r8d

    mov dl,ch
    lea rax,[rdx+rax*8]
    mov r8d,eax
    and r8d,not 0x1FFF
    xor eax,r8d
    shr r8d,13
    xor eax,r8d

    mov dl,[r11+5]
    or  dl,0x20
    lea rax,[rdx+rax*8]
    mov r8d,eax
    and r8d,not 0x1FFF
    xor eax,r8d
    shr r8d,13
    xor eax,r8d

    mov dl,[r11+6]
    or  dl,0x20
    lea rax,[rdx+rax*8]
    mov r8d,eax
    and r8d,not 0x1FFF
    xor eax,r8d
    shr r8d,13
    xor eax,r8d
    mov ecx,7

    .repeat
        movzx edx,BYTE PTR [rcx+r11]
        or  edx,0x20
        lea rax,[rdx+rax*8]
        mov edx,eax
        and edx,not 0x1FFF
        xor eax,edx
        shr edx,13
        xor eax,edx
        add ecx,1
        cmp ecx,r10d
    .untilnl

    lea r8,resw_table
    and eax,HASH_TABITEMS - 1
    movzx eax,word ptr [r8+rax*2]

    .if eax
        .repeat
            add rax,rax
            .if [r9+rax*8].len == r10b

                mov r8,[r9+rax*8]._name
                mov rcx,0x2020202020202020
                or  rcx,[r11]

                .if rcx == [r8]

                    mov edx,r10d
                    .repeat
                        .break(1) .if edx == 8
                        sub edx,1
                        mov cl,[r11+rdx]
                        or  cl,0x20
                    .until cl != [r8+rdx]
                .endif
            .endif
            movzx eax,[r9+rax*8].next
        .until !eax
    .endif
    shr eax,1
    ret

    end

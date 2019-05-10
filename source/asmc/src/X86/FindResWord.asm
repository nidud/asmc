include string.inc
include asmc.inc
include token.inc

.pragma warning(disable: 6004)

HASH_TABITEMS   equ 1024

ReservedWord    STRUC
next            dw ?    ; index next entry (used for hash table)
len             db ?    ; length of reserved word, i.e. 'AX' = 2
flags           db ?    ; see enum reservedword_flags
_name           dd ?    ; reserved word (char[])
ReservedWord    ENDS

externdef ResWordTable:ReservedWord
externdef resw_table:word

    .code

FindResWord proc fastcall w_name:string_t, w_size:int_t

    movzx eax,BYTE PTR [ecx]
    or al,0x20

    .if edx < 8

        option switch:table

        .switch notest edx

          .case 0
            xor eax,eax
            ret

          .case 1
            mov cl,al
            movzx eax,resw_table[eax*2]
            .if eax
                .repeat
                    .if ResWordTable[eax*8].len == 1
                        mov edx,ResWordTable[eax*8]._name
                        .break .if cl == [edx]
                    .endif
                    movzx eax,ResWordTable[eax*8].next
                .until !eax
            .endif
            ret

          .case 2
            movzx   edx,BYTE PTR [ecx+1]
            or      edx,0x20
            lea     eax,[edx+eax*8]
            and     eax,HASH_TABITEMS - 1
            movzx   eax,resw_table[eax*2]
            movzx   ecx,WORD PTR [ecx]
            or      ecx,0x2020
            .if eax
                .repeat
                    .if ResWordTable[eax*8].len == 2
                        mov edx,ResWordTable[eax*8]._name
                        .break .if cx == [edx]
                    .endif
                    movzx eax,ResWordTable[eax*8].next
                .until !eax
            .endif
            ret

          .case 3

            movzx   edx,BYTE PTR [ecx+1]
            or      edx,0x20
            lea     eax,[edx+eax*8]
            movzx   edx,BYTE PTR [ecx+2]
            or      edx,0x20
            lea     eax,[edx+eax*8]
            mov     edx,eax
            and     edx,not 0x1FFF
            xor     eax,edx
            shr     edx,13
            xor     eax,edx
            and     eax,HASH_TABITEMS - 1
            movzx   eax,resw_table[eax*2]
            mov     ecx,[ecx]
            or      ecx,0x202020
            and     ecx,0xFFFFFF
            .if eax
                .repeat
                    .if ResWordTable[eax*8].len == 3
                        mov edx,ResWordTable[eax*8]._name
                        mov edx,[edx]
                        and edx,0xFFFFFF
                        .break .if ecx == edx
                    .endif
                    movzx eax,ResWordTable[eax*8].next
                .until !eax
            .endif
            ret

          .case 4
            movzx   edx,BYTE PTR [ecx+1]
            or      dl,0x20
            lea     eax,[edx+eax*8]
            mov     dl,[ecx+2]
            or      dl,0x20
            lea     eax,[edx+eax*8]
            mov     edx,eax
            and     edx,not 0x1FFF
            xor     eax,edx
            shr     edx,13
            xor     eax,edx
            movzx   edx,BYTE PTR [ecx+3]
            or      dl,0x20
            lea     eax,[edx+eax*8]
            mov     edx,eax
            and     edx,not 0x1FFF
            xor     eax,edx
            shr     edx,13
            xor     eax,edx
            and     eax,HASH_TABITEMS - 1
            movzx   eax,resw_table[eax*2]
            mov     ecx,[ecx]
            or      ecx,0x20202020
            .if eax
                .repeat
                    .if ResWordTable[eax*8].len == 4
                        mov edx,ResWordTable[eax*8]._name
                        .break .if ecx == [edx]
                    .endif
                    movzx eax,ResWordTable[eax*8].next
                .until !eax
            .endif
            ret

          .case 5
          .case 6
          .case 7
            push    edi
            push    ebx
            mov     ebx,edx
            mov     edi,ecx
            mov ecx,1
            .repeat
                movzx edx,BYTE PTR [ecx+edi]
                or  edx,0x20
                lea eax,[edx+eax*8]
                mov edx,eax
                and edx,not 0x00001FFF
                xor eax,edx
                shr edx,13
                xor eax,edx
                add ecx,1
                cmp ecx,ebx
            .untilnl
            and    eax,HASH_TABITEMS - 1
            movzx  eax,resw_table[eax*2]
            .if eax
                .repeat
                    .if ResWordTable[eax*8].len == bl
                        mov edx,ResWordTable[eax*8]._name
                        mov ecx,[edi]
                        or  ecx,0x20202020
                        .if ecx == [edx]
                            mov cl,[edi+4]
                            or  cl,0x20
                            .if cl == [edx+4]
                                .break .if ebx == 5
                                mov cl,[edi+5]
                                or  cl,0x20
                                .if cl == [edx+5]
                                    .break .if ebx == 6
                                    mov cl,[edi+6]
                                    or  cl,0x20
                                    .break .if cl == [edx+6]
                                .endif
                            .endif
                        .endif
                    .endif
                    movzx eax,ResWordTable[eax*8].next
                .until !eax
            .endif
            pop ebx
            pop edi
            ret
        .endsw
    .endif

    push esi
    push edi
    push ebx

    mov ebx,edx
    mov edi,ecx

    mov ecx,[edi+1]
    or  ecx,0x20202020

    movzx edx,cl
    lea eax,[edx+eax*8]
    mov esi,eax
    and esi,not 0x1FFF
    xor eax,esi
    shr esi,13
    xor eax,esi

    mov dl,ch
    lea eax,[edx+eax*8]
    mov esi,eax
    and esi,not 0x1FFF
    xor eax,esi
    shr esi,13
    xor eax,esi

    shr ecx,16
    mov dl,cl
    lea eax,[edx+eax*8]
    mov esi,eax
    and esi,not 0x1FFF
    xor eax,esi
    shr esi,13
    xor eax,esi

    mov dl,ch
    lea eax,[edx+eax*8]
    mov esi,eax
    and esi,not 0x1FFF
    xor eax,esi
    shr esi,13
    xor eax,esi

    mov dl,[edi+5]
    or  dl,0x20
    lea eax,[edx+eax*8]
    mov esi,eax
    and esi,not 0x1FFF
    xor eax,esi
    shr esi,13
    xor eax,esi

    mov dl,[edi+6]
    or  dl,0x20
    lea eax,[edx+eax*8]
    mov esi,eax
    and esi,not 0x1FFF
    xor eax,esi
    shr esi,13
    xor eax,esi
    mov ecx,7

    .repeat
        movzx edx,BYTE PTR [ecx+edi]
        or  edx,0x20
        lea eax,[edx+eax*8]
        mov edx,eax
        and edx,not 0x1FFF
        xor eax,edx
        shr edx,13
        xor eax,edx
        add ecx,1
        cmp ecx,ebx
    .untilnl
    and eax,HASH_TABITEMS - 1
    movzx eax,resw_table[eax*2]

    .if eax
        .repeat
            .if ResWordTable[eax*8].len == bl
                mov esi,ResWordTable[eax*8]._name
                mov ecx,[edi]
                or  ecx,0x20202020
                .if ecx == [esi]
                    mov ecx,[edi+4]
                    or  ecx,0x20202020
                    .if ecx == [esi+4]
                        mov edx,ebx
                        .repeat
                            .break(1) .if edx == 8
                            sub edx,1
                            mov cl,[edi+edx]
                            or  cl,0x20
                        .until cl != [esi+edx]
                    .endif
                .endif
            .endif
            mov ax,ResWordTable[eax*8].next
        .until !eax
    .endif
    pop ebx
    pop edi
    pop esi
    ret

FindResWord endp

    end

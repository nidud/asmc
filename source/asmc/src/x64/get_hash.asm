
    .code

get_hash::

HASH_TABITEMS   equ 1024

    xor eax,eax
    and edx,0xFF
    .ifnz
        .repeat
            movzx r8d,byte ptr [rcx]
            inc rcx
            or  r8d,0x20
            lea rax,[r8+rax*8]
            mov r8,rax
            and r8d,not 0x1FFF
            xor eax,r8d
            shr r8d,13
            xor eax,r8d
            add dl,-1
        .untilz
    .endif
    and eax,( HASH_TABITEMS - 1 )
    ret

    END

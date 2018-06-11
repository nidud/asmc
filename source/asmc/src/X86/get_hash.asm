    .486
    .model flat
    .code

@get_hash@8::

HASH_TABITEMS   equ 1024

    xor eax,eax
    and edx,0xFF
    .ifnz
        push ebx
        .repeat
            movzx ebx,byte ptr [ecx]
            inc ecx
            or  ebx,0x20
            lea eax,[ebx+eax*8]
            mov ebx,eax
            and ebx,not 0x1FFF
            xor eax,ebx
            shr ebx,13
            xor eax,ebx
            add dl,-1
        .untilz
        pop ebx
    .endif
    and eax,( HASH_TABITEMS - 1 )
    ret

    end

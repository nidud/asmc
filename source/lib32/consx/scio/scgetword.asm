include consx.inc

    .data
    ;
    ; These are characters used as valid identifiers
    ;
    idchars db '0123456789_?@abcdefghijklmnopqrstuvwxyz',0

    .code

scgetword proc uses esi edi ebx linebuf:LPSTR

    mov edi,_wherex()       ; get cursor x,y pos
    mov ebx,edx
    inc edi                 ; to start of line..

    .repeat

        dec edi             ; moving left seeking a valid character
        .break .ifz

        getxyc(edi, ebx)
        idtestal()
        .continue .ifz

        getxyc(&[edi-1], ebx)
        idtestal()
    .untilz

    mov esi,linebuf
    mov ecx,32
    xor eax,eax

    .repeat

        getxyc(edi, ebx)
        inc edi
        idtestal()
        .break .ifz

        mov [esi],al
        inc esi
    .untilcxz

    mov byte ptr [esi],0
    mov edx,linebuf
    sub eax,eax
    .if al != [edx]

        mov eax,edx
    .endif
    ret

idtestal:

    push edi
    push ecx
    push eax

    .if al >= 'A' && al <= 'Z'

        or al,0x20
    .endif
    mov   edi,offset idchars
    mov   ecx,sizeof idchars
    repne scasb
    cmp   byte ptr [edi-1],0
    pop   eax
    pop   ecx
    pop   edi
    retn

scgetword endp

    END

include consx.inc

    .code

wcputs proc uses ecx edx esi edi p:PVOID, l, m, string:LPSTR

    mov   edi,p
    movzx edx,byte ptr l
    add   edx,edx
    movzx ecx,word ptr m
    mov   ah,ch
    mov   ch,[edi+1]
    and   ch,0xF0

    .if ch == at_background[B_Menus]
        or  ch,at_foreground[F_MenusKey]
    .elseif ch == at_background[B_Dialog]
        or  ch,at_foreground[F_DialogKey]
    .else
        xor ch,ch
    .endif

    mov esi,string
    __wputs()
    ret

wcputs endp

    END

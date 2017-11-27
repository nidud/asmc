; _ldtoqf() - long double to Quadruple float
;
include intn.inc

.code

_ldtoqf proc p:ptr, ld:ptr

    mov eax,p
    mov ecx,ld
    mov dx,[ecx+8]
    mov [eax+14],dx
    mov edx,[ecx+4]
    mov ecx,[ecx]
    shl ecx,1
    rcl edx,1
    mov [eax+6],ecx
    mov [eax+10],edx
    xor ecx,ecx
    mov [eax],ecx
    mov [eax+4],cx
    ret

_ldtoqf endp

    end

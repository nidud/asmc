include conio.inc

public char_avail
public ungot_char

.data
char_avail dd 0
ungot_char dd 0

.code
_ungetch proc i:UINT

    mov eax,i
    .if char_avail
        mov eax,-1
    .else
        mov ungot_char,eax
        mov char_avail,1
    .endif
    ret

_ungetch endp

    end

; RCMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

rcmove proc uses rbx pRECT:ptr TRECT, p:PCHAR_INFO, flag:int_t, x:int_t, y:int_t

    ldr rbx,pRECT

    .ifd rchide([rbx], flag, p)

        mov al,byte ptr x
        mov ah,byte ptr y
        mov [rbx],ax
        mov edx,flag
        and edx,not W_VISIBLE
        rcshow([rbx], edx, p)
    .endif
    mov eax,[rbx]
    ret

rcmove endp

    end

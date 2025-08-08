;
; v2.37.18 - use unsigned divide
;
    .486
    .model flat

    S equ (-1)
    U equ 0FFFFFFFFh

    .code

    mov eax,S / 16
    mov eax,U / 16
    mov eax,U / -16
    mov eax,U / 0FFFFFFF0h

    end


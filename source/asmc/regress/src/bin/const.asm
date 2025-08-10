;
; v2.37.18/19/20 - const divide
;
    .486
    .model flat

    S equ (-1)
    U equ 0FFFFFFFFh

    .code

    mov eax,S / 16              ; 00000000
    mov eax,U / 16              ; 0FFFFFFF
    mov eax,U / -16             ; F0000001
    mov eax,U / -15             ; EEEEEEEF
    mov eax,U / 0FFFFFFF0h      ; 00000001

    mov ecx,S mod 16            ; FFFFFFFF
    mov ecx,U mod 16            ; 0000000F
    mov ecx,U mod -16           ; FFFFFFF1
    mov ecx,U mod -15           ; 00000000
    mov ecx,U mod 0FFFFFFF0h    ; 0000000F

    end


    ; define

    .x64
    .model flat, fastcall

define a 1
define b 0
define r 1.0
define d 0x1000000 / 5
define e d + a

    .code

main proc

    mov eax,a
    mov eax,b
    mov eax,r
    mov eax,d
    mov eax,e
    ret

main endp

    end

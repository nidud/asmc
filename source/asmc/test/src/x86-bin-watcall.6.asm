
;--- INVOKE with WATCALL, 16-bit (INVOKE18.ASM)

    .286
    .model small, watcall

    .data

b1  db 0
w1  dw 0

    .code

fast1 proc a1:word
    mov ax,a1
    ret
fast1 endp

fast2 proc a1:word, a2:word
    mov ax,a1
    add ax,a2
    ret
fast2 endp

fast3 proc a1:word, a2:byte, a3:word
    mov ax,a1
    add al,a2
    add ax,a3
    ret
fast3 endp

fast4 proc a1:word, a2:word, a3:word, a4:word
    mov ax,a1
    add ax,a2
    add ax,a3
    add ax,a4
    ret
fast4 endp

fast5 proc a1:word, a2:byte, a3:word, a4:word, a5:word
    mov ax,a1
    add al,a2
    add ax,a3
    add ax,a4
    add ax,a5
    ret ; 2
fast5 endp

start proc

    invoke fast1, 1
    invoke fast2, 1, 2
    invoke fast3, ax, b1, 3
    invoke fast4, ax, w1, 3, 4

    ; no stack cleanup..

    invoke fast5, 1, 2, 3, 4, w1
    ret

start endp
end

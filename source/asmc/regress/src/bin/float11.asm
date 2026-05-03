;
; v2.28: added REAL2 - binary16 -- half
;
; limits: -65504.0 - 65504.0
;
    .386
    .model small
    .data

    real2  0.0
    real2  -65504.0
    real2  65504.0

    real2 3C00r

    .code

    mov ax,1.0          ; 3C00
    mov ax,-65504.0     ; FBFF  Min
    mov ax,65504.0      ; 7BFF  Max
    mov ax,0.0          ; 0000  zero
    mov ax,-0.0         ; 8000 -zero
    mov ax,1.0/0.0      ; 7C00  Inf  1/zero
    mov ax,-1.0/0.0     ; FC00 -Inf  -1/zero
    mov ax,0.0/0.0      ; FFFF  NaN  zero/zero
    mov ax,0.3333333333 ; 3555  1/3

    end

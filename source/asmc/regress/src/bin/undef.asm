    .386
    .model flat
    .data

e1  equ 1
m1  macro
    db e1
    endm

    m1
    undef e1
    undef m1

e1  equ 2
m1  macro a, b
    db e1,a,b
    endm

    m1 3, 4

    end




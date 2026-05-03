
    ; 2.31.49 - if float eq

ifndef __ASMC64__
    .x64
    .model flat
endif
    .code

    f0 equ 0.0
    f1 equ 1.0
    s0 equ -0.0
    s1 equ -1.0

    true macro expr:vararg
        if expr
           mov eax,1
        else
           mov eax,0
        endif
        exitm<>
        endm

    true(-1 shr 63 eq 1)
    true(-1 sar 63 eq -1)

    true(f0 eq f0)
    true(f1 eq f1)
    true(f0 eq f1+s1)

    true(f0 ne f1)
    true(f0 ne s0)

    true(f0 gt s0)
    true(f0 gt s1)

    true(f0 lt f1)
    true(s0 lt f0)
    true(s1 lt f1)

    true(s0 le f0)
    true(f0 ge s0)

    end

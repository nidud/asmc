;; https://msdn.microsoft.com/en-us/library/82cxdw50.aspx
;; mul128.c
;; processor: x64
include stdio.inc
include intrin.inc

.code

main proc

  local a:SQWORD, b:SQWORD, q:SQWORD, d:SQWORD

    mov rax,0x0fffffffffffffff
    mov a,rax
    mov b,0xf0000000

    mov d,_mul128(a, b, &q)

    printf("%#I64x * %#I64x = %#I64x%I64x\n", a, b, q, d)
    ret

main endp

    end main

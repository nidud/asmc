;; https://msdn.microsoft.com/en-us/library/wds0z27f.aspx
;; ull_rshift.cpp
;; compile with: /EHsc
;; processor: x86, x64
include stdio.inc
include intrin.inc

.code

main proc

  local __mask:QWORD, nBit:SINT

    mov __mask,0x100
    mov nBit,8
    mov __mask,__ull_rshift(__mask, nBit)

    printf("%#I64d\n", __mask)
    ret

main endp

    end main

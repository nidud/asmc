;; https://msdn.microsoft.com/en-us/library/d2s81xt0.aspx
;; emul.cpp
;; compile with: /EHsc
;; processor: x86, x64
include stdio.inc
include intrin.inc

.code

main proc

  local a:SINT, b:SINT, result:SQWORD
  local ua:UINT, ub:UINT, uresult:QWORD

    mov a,-268435456
    mov b,2

    mov result,__emul(a, b)

    printf("%d * %d = %I64d\n", a, b, result)

    mov ua,0xFFFFFFFF   ;; Dec value: 4294967295
    mov ub,0xF000000    ;; Dec value: 251658240

    mov uresult,__emulu(ua, ub)

    printf("%u * %u = %I64u\n", ua, ub, uresult)
    ret

main endp

    end main

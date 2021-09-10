;;
;; https://msdn.microsoft.com/en-us/library/82cxdw50.aspx
;; mul128.c
;; processor: x64
;;

include stdio.inc
include intrin.inc
include tchar.inc

.code

main proc

  local a:int64_t, b:int64_t, c:int64_t, d:int64_t

    mov rax,0x0fffffffffffffff
    mov a,rax
    mov b,0xf0000000

    mov d,_mul128(a, b, &c)

    printf("%#llx * %#llx = %#llx%llx\n", a, b, c, d)
    ret

main endp

    end _tstart

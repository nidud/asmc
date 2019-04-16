;; https://msdn.microsoft.com/en-us/library/ywwcatsa.aspx
;; stosb.c
;; processor: x86, x64
include stdio.inc
include intrin.inc
include tchar.inc

.data
s db "*********************************",0
.code

main proc

  local x:BYTE

    mov x,0x40; ;; '@' character

    printf("%s\n", &s)
    __stosb(&s[1], x, 6)
    printf("%s\n", &s)
    ret

main endp

    end _tstart

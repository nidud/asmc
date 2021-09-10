;; https://docs.microsoft.com/nb-no/cpp/intrinsics/movsb
;; movsb.cpp
;; processor: x86, x64
include stdio.inc
include intrin.inc
include tchar.inc

.data
s2 db "A big black dog."
   db 100 dup(0)
.code

main proc

  local s1[100]:SBYTE

    __movsb(&s1, &s2, 100)
    printf("%s %s\n", &s1, &s2)
    ret

main endp

    end _tstart

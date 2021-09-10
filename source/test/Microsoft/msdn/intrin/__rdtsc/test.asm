;; https://docs.microsoft.com/nb-no/cpp/intrinsics/rdtsc
include stdio.inc
include intrin.inc
include tchar.inc

.code

main proc

  local i:QWORD

    mov i,__rdtsc()
    printf("%I64d ticks\n", i)
    ret

main endp

    end _tstart

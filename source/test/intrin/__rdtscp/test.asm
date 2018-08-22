;; https://docs.microsoft.com/nb-no/cpp/intrinsics/rdtscp
include stdio.inc
include intrin.inc

.code

main proc

  local i:QWORD
  local ui:UINT

    mov i,__rdtscp(&ui)
    printf("%I64d ticks\n", i)
    printf("TSC_AUX was %x\n", ui)
    ret

main endp

    end main

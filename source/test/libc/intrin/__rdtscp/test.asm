;; https://docs.microsoft.com/nb-no/cpp/intrinsics/rdtscp
include stdio.inc
include intrin.inc
include tchar.inc

    .code

main proc

  local i:QWORD
  local ui:UINT

    mov i,__rdtscp(&ui)
    printf("%I64d ticks\n", i)
    printf("TSC_AUX was %x\n", ui)
    xor eax,eax
    ret

main endp

    end _tstart

;; https://docs.microsoft.com/en-us/cpp/intrinsics/interlockedand-intrinsic-functions
include stdio.inc
include intrin.inc
.code
main proc

  local data1:dword
  local data2:dword
  local retval:dword

    mov data1,0xFF00FF00
    mov data2,0x00FFFF00
    lea rcx,data1
    mov retval,_InterlockedAnd(rcx, data2)
    printf("0x%x 0x%x 0x%x\n", data1, data2, retval)
    ret

main endp

    end

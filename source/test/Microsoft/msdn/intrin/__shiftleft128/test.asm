;; https://msdn.microsoft.com/en-us/library/szzkhewe.aspx
;; shiftleft128.c
;; processor: IPF, x64
include stdio.inc
include intrin.inc
include tchar.inc

.code

main proc

  local i:QWORD
  local j:QWORD
  local ResultLowPart:QWORD
  local ResultHighPart:QWORD

    mov i,0x1
    mov j,0x10

    mov ResultLowPart,1 shl 1
    mov ResultHighPart,__shiftleft128(i, j, 1)

    ;; concatenate the low and high parts padded with 0's
    ;; to display correct hexadecimal 128 bit values
    printf("0x%02I64x%016I64x << 1 = 0x%02I64x%016I64x\n",
             j, i, ResultHighPart, ResultLowPart)

    mov ResultHighPart,0x10 shr 1
    mov ResultLowPart,__shiftright128(i, j, 1)

    printf("0x%02I64x%016I64x >> 1 = 0x%02I64x%016I64x\n",
             j, i, ResultHighPart, ResultLowPart)
    ret

main endp

    end _tstart

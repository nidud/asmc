;; https://msdn.microsoft.com/en-us/library/h65k4tze.aspx
;; bittest.cpp
;; processor: x86, ARM, x64

include stdio.inc
include intrin.inc
include tchar.inc
.data
num sdword 78002
.code
main proc

  local bits[32]:byte

    printf("Number: %d\n", num)

    .for (rcx=&num, ebx = 0: ebx < 31: ebx++)

        _bittest(rcx, ebx)
        mov bits[rbx],al
    .endf

    printf("Binary representation:\n")
    .while (ebx)

        .if (bits[rbx])
            printf("1")
        .else
            printf("0")
        .endif
        dec ebx
    .endw
    printf("\n")
    ret
main endp

    end _tstart

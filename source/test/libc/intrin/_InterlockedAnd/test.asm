;
; https://docs.microsoft.com/en-us/cpp/intrinsics/interlockedand-intrinsic-functions
;
include stdio.inc
include intrin.inc
include tchar.inc

.code

main proc

   .new data1:uint_t = 0xFF00FF00
   .new data2:uint_t = 0x00FFFF00
   .new retval:uint_t

    lea rcx,data1
    mov retval,_InterlockedAnd(rcx, data2)
    printf("0x%x 0x%x 0x%x\n", data1, data2, retval)
    xor eax,eax
    ret

main endp

    end _tstart

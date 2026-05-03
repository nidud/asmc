; _ATODBL.ASM--
;
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/
;   atodbl-atodbl-l-atoldbl-atoldbl-l-atoflt-atoflt-l?view=msvc-170
;

include stdio.inc
include stdlib.inc
include tchar.inc
ifdef __PE__
define INFO <"MSVCRT">
elseifdef _WIN64
define INFO <"LIBC64">
else
define INFO <"LIBC32">
endif

.code

_tmain proc argc:int_t, argv:array_t

   .new str1:string_t = "3.141592654"
   .new abc:string_t = "abc"
   .new oflow:string_t = "1.0E+5000"
   .new dblval:real8
   .new fltval:real4
   .new retval:int_t

    printf(INFO "\n")

    mov retval,_atodbl(&dblval, str1)
    printf("Double value: %f, Return value: %d\n", dblval, retval)

    ; A non-floating point value: returns 0.

    mov retval,_atodbl(&dblval, abc)
    printf("Double value: %f, Return value: %d\n", dblval, retval)

    ; Overflow.

    mov retval,_atodbl(&dblval, oflow)
    printf("Double value: %f, Return value: %d\n", dblval, retval)

if not defined(__PE__) and defined(__SSE__)

    mov retval,_atoflt(&fltval, str1)
    cvtss2sd xmm0,fltval
    movsd dblval,xmm0
    printf("Float value: %f, Return value: %d\n", dblval, retval)

    ; A non-floating point value: returns 0.

    mov retval,_atoflt(&fltval, abc)
    cvtss2sd xmm1,fltval
    movsd dblval,xmm0
    printf("Float value: %f, Return value: %d\n", dblval, retval)

    ; Overflow.

    mov retval,_atoflt(&fltval, oflow)
    cvtss2sd xmm1,fltval
    movsd dblval,xmm0
    printf("Float value: %f, Return value: %d\n", dblval, retval)
endif
   .return(0)

_tmain endp

    end _tstart

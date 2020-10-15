; DAYSINMONTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

DaysInMonth proc year, month

    mov ecx,month
    mov eax,31

    .switch ecx

      .case 2
        mov eax,year
        DaysInFebruary(eax)
        .endc

      .case 4,6,9,11
        sub eax,1
        .endc
    .endsw
    ret

DaysInMonth endp

    END

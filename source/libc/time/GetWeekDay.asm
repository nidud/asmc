; GETWEEKDAY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

DaysInFebruary proc year:uint_t
    ldr eax,year
    .while 1
        .break .if !eax
        .if !( eax & 3 )
            mov ecx,100
            xor edx,edx
            div ecx
            .break .if edx
            mov eax,year
        .endif
        mov ecx,400
        xor edx,edx
        div ecx
        .break .if !edx
        .return( 28 )
    .endw
    .return( 29 )
    endp


DaysInMonth proc year:uint_t, month:uint_t
    ldr ecx,year
    ldr edx,month
    mov eax,31
    .switch edx
      .case 2
        DaysInFebruary(ecx)
       .endc
      .case 4,6,9,11
        sub eax,1
       .endc
    .endsw
    ret
    endp


GetWeekDay proc uses rbx year:uint_t, month:uint_t, day:uint_t

   .new m:uint_t
   .new y:uint_t

    ldr eax,year
    mov ebx,eax
    shr eax,2
    mov ecx,365 * 4 + 1
    mul ecx
    mov y,eax
    .while ( ebx & 3 )
        DaysInFebruary(ebx)
        add eax,365-28
        add y,eax
        sub ebx,1
    .endw
    mov ebx,year
    .if ebx
        DaysInFebruary(ebx)
        add eax,365-28
        sub y,eax
    .endif
    mov m,month
    .while ( m > 1 )
        sub m,1
        DaysInMonth(ebx, m)
        add y,eax
    .endw
    mov eax,day
    add eax,y
    dec eax
    mov ecx,7
    xor edx,edx
    div ecx
    mov eax,edx
    ret
    endp

    end

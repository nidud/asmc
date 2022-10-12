; GETWEEKDAY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

DaysInFebruary proc year:uint_t

    mov eax,year

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

DaysInFebruary endp


DaysInMonth proc year:uint_t, month:uint_t

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


GetWeekDay proc uses rsi rdi rbx year:uint_t, month:uint_t, day:uint_t

    mov eax,year
    mov ebx,eax
    shr eax,2
    mov ecx,365 * 4 + 1
    mul ecx
    mov esi,eax

    .while ( ebx & 3 )

        DaysInFebruary(ebx)
        add eax,365-28
        add esi,eax
        sub ebx,1
    .endw

    mov ebx,year
    .if ebx

        DaysInFebruary(ebx)
        add eax,365-28
        sub esi,eax
    .endif

    mov edi,month
    .while ( edi > 1 )

        sub edi,1
        DaysInMonth(ebx, edi)
        add esi,eax
    .endw

    mov eax,day
    add eax,esi
    dec eax
    mov ecx,7
    xor edx,edx
    div ecx
    mov eax,edx
    ret

GetWeekDay endp

    end

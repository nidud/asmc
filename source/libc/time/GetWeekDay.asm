include time.inc

    .code

GetWeekDay proc uses esi edi ebx year, month, day
    mov eax,year
    mov ebx,eax
    shr eax,2
    mov ecx,365 * 4 + 1
    mul ecx
    mov esi,eax
    .while  ebx & 3
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
    .while  edi > 1
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

    END

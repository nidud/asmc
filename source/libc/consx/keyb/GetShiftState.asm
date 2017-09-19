include consx.inc

    .code

GetShiftState proc

    mov eax,keyshift
    mov eax,[eax]
    and eax,SHIFT_KEYSPRESSED or SHIFT_LEFT or SHIFT_RIGHT
    ret

GetShiftState endp

    END

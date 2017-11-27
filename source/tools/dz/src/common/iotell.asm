include iost.inc

    .code

iotell proc io:ptr S_IOST

    mov edx,io
    mov eax,dword ptr [edx].S_IOST.ios_total
    add eax,[edx].S_IOST.ios_i
    mov edx,dword ptr [edx].S_IOST.ios_total[4]
    adc edx,0
    ret

iotell endp

    END

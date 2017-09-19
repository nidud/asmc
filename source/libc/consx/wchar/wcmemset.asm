include consx.inc

    .code

wcmemset proc uses edi string:PVOID, val, count
    mov ecx,count
    mov edi,string
    mov eax,val
    rep stosw
    ret
wcmemset endp

    END

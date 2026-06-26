
;--- 64-bit dll

    .CODE

Export1 proc export
    mov eax,12345678h
    ret
    endp

Export2 proc export pParm:ptr DWORD
    mov rcx, pParm
    mov dword ptr [rcx], 87654321h
    mov eax,1
    ret
    endp

_DllMainCRTStartup proc hModule:ptr, dwReason:dword, dwReserved:ptr
    mov eax,1
    ret
    endp

    END


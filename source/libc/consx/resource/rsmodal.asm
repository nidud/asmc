include consx.inc

    .code

rsmodal proc robj:PTR S_ROBJ
    .if rsopen(robj)
        push eax
        rsevent(robj, eax)
        pop ecx
        push eax
        dlclose(ecx)
        pop eax
    .endif
    ret
rsmodal ENDP

    END

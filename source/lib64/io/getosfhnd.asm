include io.inc

    .code

    option win64:rsp noauto nosave

getosfhnd PROC handle:SINT
    or eax,-1
    .if ecx < _nfile
        lea rax,_osfile
        .if byte ptr [rax+rcx] & FH_OPEN
            lea rax,_osfhnd
            mov rax,[rax+rcx*8]
        .else
            mov eax,-1
        .endif
    .endif
    ret
getosfhnd ENDP

    END

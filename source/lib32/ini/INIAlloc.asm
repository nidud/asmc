include malloc.inc
include ini.inc

    .code

INIAlloc proc

    .if malloc(sizeof(S_INI))

        mov ecx,0
        mov [eax].S_INI.flags,ecx
        mov [eax].S_INI.entry,ecx
        mov [eax].S_INI.value,ecx
        mov [eax].S_INI.next,ecx
    .endif
    ret

INIAlloc endp

    END

include stdlib.inc
include string.inc

    .code

_wgetenv PROC USES esi edi ecx enval:LPWSTR

    .if wcslen(enval)

        mov edi,eax
        mov esi,_wenviron
        lodsd

        .while eax

            .if !_wcsnicmp(eax, enval, edi)

                mov eax,[esi-4]
                add eax,edi
                .if word ptr [eax] == '='
                    add eax,2
                    .break
                .endif
            .endif
            lodsd
        .endw
    .endif
    ret
_wgetenv ENDP

    END

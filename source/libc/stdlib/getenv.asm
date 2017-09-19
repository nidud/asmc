include stdlib.inc
include string.inc

    .code

getenv proc uses esi edi ecx enval:LPSTR

    .if strlen(enval)

        mov edi,eax
        mov esi,_environ
        lodsd

        .while eax

            .if !_strnicmp(eax, enval, edi)

                mov eax,[esi-4]
                add eax,edi
                .if byte ptr [eax] == '='
                    inc eax
                    .break
                .endif
            .endif
            lodsd
        .endw
    .endif
    ret
getenv endp

    END

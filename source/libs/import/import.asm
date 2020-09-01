; IMPORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include stdio.inc
include tchar.inc

    .code

main proc

  local lbuf[256]:byte

    .if ecx == 2 ; import <lib-name>

        mov edi,[edx+4]

        .if fopen(edi, "rt")            ; def\<lib-name>.def

            mov ebx,eax

            .if strrchr(edi, '\')
                lea edi,[eax+1]         ; <lib-name>.def
            .endif
            .if strrchr(edi, '.')
                mov byte ptr [eax],0    ; <lib-name>
            .endif

            .if fopen(strcat(edi, ".lbc"), "wt")

                mov esi,eax
                mov byte ptr [strrchr(edi, '.')],0
                _strupr(edi)

                .while fgets(addr lbuf, 256, ebx)

                    .if strrchr(eax, 10)

                        mov byte ptr [eax],0
                        .if lbuf

                            fprintf(esi, "++_%s.\'%s.dll\'\n", addr lbuf, edi)
                        .endif
                    .endif
                .endw
                fclose(esi)
            .else
                perror(edi)
            .endif
        .else
            perror(edi)
        .endif
    .else
        printf("\nUsage: IMPORT def\<dll-name>.def\n")
    .endif

    xor eax,eax
    ret

main endp

    end _tstart

include stdio.inc
include stdlib.inc
include string.inc
include winnls.inc
include tchar.inc

.code

_tmain proc argc:UINT, argv:ptr
local b[256]:sbyte

    .if argc == 2
        mov edx,argv
        mov eax,[edx+4]
        .if fopen(eax, "rt")
            mov esi,eax
            lea edi,b
            .if fgets(edi, 256, esi)
                fclose(esi)
                mov edx,argv
                mov eax,[edx+4]
                .if fopen(eax, "wt")
                    mov esi,eax
                    ;
                    ; convert the the file
                    ;
                    add edi,16
                    fprintf(esi, "include ..\\..\\lib32%s", edi)
                .endif
            .endif
            fclose(esi)
        .endif
    .endif
    xor eax,eax
    ret
_tmain endp

    end _tstart

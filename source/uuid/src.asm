; SRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc

.code

main proc

  local fp:LPFILE
  local file[512]:byte
  local line[512]:byte

    .if fopen("list.txt", "rt")

        mov fp,eax
        lea esi,line
        .while fgets(esi, 512, fp)

            .continue .if !strstr(esi, " GUID")

            mov ebx,eax
            mov byte ptr [ebx],0
            lea edi,file
            sprintf(edi, "src\\%s.asm", esi)
            .if fopen(edi, "wt")

                mov edi,eax
                fprintf(edi, "include guiddef.inc\n\npublic %s\n\n", esi)
                mov byte ptr [ebx],' '
                fprintf(edi, "    .data\n    %s\n    end\n", esi)
                fclose(edi)
            .endif
        .endw
        fclose(fp)
    .endif
    ret

main endp

    end main

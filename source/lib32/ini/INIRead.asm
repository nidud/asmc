; INIREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc
include strlib.inc
include ini.inc

    .code

INIRead proc uses esi edi ebx ini:LPINI, file:LPSTR

  local fp, buffer[256]:sbyte

    .if fopen(file, "rt")

        mov fp,eax
        .if !ini

            mov ini,INIAlloc()
        .endif
        mov ebx,ini
        lea esi,buffer

        .while fgets(esi, 256, fp)

            .continue .if !strtrim(esi)
            .if byte ptr [esi] == '['

                .if strchr(esi, ']')

                    mov byte ptr [eax],0
                    lea eax,[esi+1]
                    .break .if !INIAddSection(ebx, esi)
                    mov ebx,eax
                .endif
            .else
                INIAddEntry(ebx, esi)
            .endif
        .endw
        fclose(fp)
        mov eax,ini
    .endif
    ret
INIRead endp

    END

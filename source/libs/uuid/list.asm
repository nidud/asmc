
;
; Create source[.u] file for each guid from list.txt
;

include stdio.inc
include string.inc

.code

main proc

  local fp:LPFILE, file[512]:byte, line[512]:byte

    .return 1 .if !fopen("list.txt", "rt")

    mov fp,eax
    lea esi,line

    .while fgets(esi, 512, fp)

        .if !strstr(esi, " GUID")
            strstr(esi, " PROPERTYKEY")
        .endif
        .continue .if !eax

        ; name GUID {0x0000010b,0,0,{0xC0,0,0,0,0,0,0,0x46}}
        ; name PROPERTYKEY {{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}},pid}

        mov ebx,eax
        mov byte ptr [ebx],0
        lea edi,file
        sprintf(edi, "%s.u", esi)

        .if fopen(edi, "wt")

            mov edi,eax

            fprintf(edi,
                "include guiddef.inc\n"
                "PROPERTYKEY STRUC\n"
                "fmtid   GUID <>\n"
                "pid     dd ?\n"
                "PROPERTYKEY ENDS\n"
                "\n"
                "public %s\n"
                "\n", esi)

            mov byte ptr [ebx],' '

            fprintf(edi,
                "    .data\n"
                "    %s\n"
                "    end\n", esi)

            fclose(edi)

        .endif
    .endw

    fclose(fp)
    xor eax,eax
    ret

main endp

    end main

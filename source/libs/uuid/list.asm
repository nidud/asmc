
;
; Create source[.u] file for each guid from list.txt
;

include stdio.inc
include string.inc
include tchar.inc

.code

main proc

  local fp:LPFILE, file[512]:byte, line[512]:byte

    .return 1 .if !fopen("list.txt", "rt")

    mov fp,rax
    lea rsi,line

    .while fgets(rsi, 512, fp)

        .if !strstr(rsi, " GUID")
            strstr(rsi, " PROPERTYKEY")
        .endif
        .continue .if !rax

        ; name GUID {0x0000010b,0,0,{0xC0,0,0,0,0,0,0,0x46}}
        ; name PROPERTYKEY {{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}},pid}

        mov rbx,rax
        mov byte ptr [rbx],0
        lea rdi,file
        sprintf(rdi, "%s.u", rsi)

        .if fopen(rdi, "wt")

            mov rdi,rax

            fprintf(rdi,
                "include libc.inc\n"
                "include guiddef.inc\n"
                "PROPERTYKEY STRUC\n"
                "fmtid   GUID <>\n"
                "pid     dd ?\n"
                "PROPERTYKEY ENDS\n"
                "\n"
                "public %s\n"
                "\n", rsi)

            mov byte ptr [rbx],' '

            fprintf(rdi,
                "    .data\n"
                "    %s\n"
                "    end\n", rsi)

            fclose(rdi)
        .endif
    .endw
    fclose(fp)
    xor eax,eax
    ret

main endp

    end _tstart

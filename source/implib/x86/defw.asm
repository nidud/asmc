include string.inc
include stdio.inc
include tchar.inc

    .code

main proc
    local lbuf[256]:byte
    .if ecx == 2
        mov edi,[edx+4]
        .if fopen(edi,"rt")
            mov ebx,eax
            .if strrchr(edi,'\')
                lea edi,[eax+1]
            .endif
            .if strrchr(edi,'.')
                mov byte ptr [eax],0
            .endif
            strcat(edi,".lbc")
            .if fopen(edi,"wt")
                mov esi,eax
                mov byte ptr [strrchr(edi,'.')],0
                _strupr(edi)
                .while fgets(addr lbuf, 256, ebx)
                    .if strrchr(eax,10)
                        mov byte ptr [eax],0
                        .if lbuf
                            fprintf(esi,"++_%s.\'%s.dll\'\n",addr lbuf,edi)
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
        printf("\nUsage: DEFW <dllname>.def\n")
    .endif
    xor eax,eax
    ret
main endp

    end _tstart

include stdio.inc
include stdlib.inc
include string.inc
include process.inc
include winbase.inc

    .code

main proc argc:dword, argv:ptr

  local cmd[_MAX_PATH]:byte
  local com[_MAX_PATH]:byte

    mov edi,argc
    mov esi,argv

    .if edi > 1

        lea ebx,cmd
        lodsd
        lodsd
        strcpy(ebx, eax)

        .for ( edi -= 2: edi: edi-- )

            strcat(ebx, " ")
            lodsd
            strcat(ebx, eax)
        .endf

        mov edi,GetTickCount()
        system(ebx)
        sub GetTickCount(),edi
        printf("%5d ClockTicks: %s\n", eax, ebx)
        xor eax,eax
    .else
        printf("TimeIt Version 1.02 Public Domain\n"
               "USAGE: TI <command> <args>\n\n")
    .endif
    ret

main endp

    end

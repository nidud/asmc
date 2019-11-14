;
; asmc -q -bin ?.asm
; asmc -q -pe -Cs %0
; %~n0.exe
; del %~n0.exe
; del *.bin
; exit /b %errorlevel%
;

procs equ <for x,<0,1,2,3,4>> ; add functions to test...
args_x macro
    lea eax,str_1+size_s
    sub eax,step_x
    push eax
    exitm<>
    endm

include ../timeit.inc

size_s  equ 4096 ; maximum data size

.data?
str_1   db size_s dup(?)
        dd ?

    .data

info_0  db "msvcrt.strlen()",0
info_1  db "SSE 16",0
info_2  db "SSE 32",0
info_3  db "SSE Intel Silvermont",0
info_4  db "SSE Intel Atom",0
info_5  db "5.asm",0
info_6  db "6.asm",0
info_7  db "7.asm",0
info_8  db "8.asm",0
info_9  db "9.asm",0

    .code

;-------------------------------------------------------------------------------
; test if the algo actually works..
;-------------------------------------------------------------------------------

TEST_OVERLAP equ 1

validate_x proc uses esi edi ebx x:dword

    mov ecx,x
    mov esi,proc_p[ecx*4]

    .if !esi

        .if ReadProc(ecx)

            mov esi,proc_x
        .endif
    .endif

    .if esi

        .for ebx = esp, edi = 0: edi < 200: edi++

            lea  eax,str_1[size_s]
            sub  eax,edi
            push eax
            call esi
            mov  esp,ebx

            .if eax != edi

                printf("error: eax = %d (%d) proc_%d\n", eax, edi, x)
                inc nerror
            .endif
        .endf

ifdef TEST_OVERLAP

        .if VirtualAlloc(0, 4096, MEM_COMMIT, PAGE_READWRITE)

            mov ebx,eax
            mov edi,eax
            mov ecx,4096
            mov eax,'x'
            rep stosb
            mov edi,4096-15
            add ebx,15
            .repeat
                dec edi
                mov byte ptr [ebx+edi],0
                push ebx
                call esi
                mov esp,ebp
            .until edi == 4096 - 33 - 15
            sub ebx,15
            VirtualFree(ebx, 0, MEM_RELEASE)
        .endif
endif

    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret

validate_x ENDP

main proc

    lea edi,str_1
    mov ecx,size_s
    mov al,'x'
    rep stosb
    xor eax,eax
    stosd

    .if GetModuleHandleA("msvcrt")
        .if GetProcAddress( eax, "strlen" )
            mov proc_p,eax
        .endif
    .endif

    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return 1
        .endif
        endm

    GetCycleCount(0, 40, 8, 8000)
    GetCycleCount(41, 80, 7, 5000)
    GetCycleCount(600, 1000, 100, 1000)
    ret

main endp

    end start

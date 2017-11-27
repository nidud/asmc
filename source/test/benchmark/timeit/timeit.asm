.686
.xmm
.model flat, stdcall

option dllimport:<msvcrt>
printf proto c :ptr byte, :vararg
exit proto c :dword
strlen proto c :ptr
_getch proto c
__getmainargs proto c :ptr, :ptr, :ptr, :ptr, :ptr
option  dllimport:<kernel32>
GetCurrentProcess proto
CreateFileA proto :ptr, :dword, :dword, :ptr, :dword, :dword, :ptr
ReadFile proto :ptr, :ptr, :ptr, :ptr, :ptr
CloseHandle proto :ptr
FlushInstructionCache proto :ptr, :ptr, :ptr
VirtualProtect proto :ptr, :ptr, :ptr, :ptr
SetPriorityClass proto :ptr, :dword
Sleep proto :ptr
option dllimport:none

.data

procs   equ <for x,<0,1>> ; add functions to test...

info_0  db "0.asm",0
info_1  db "1.asm",0
info_2  db "2.asm",0
info_3  db "3.asm",0
info_4  db "4.asm",0
info_5  db "5.asm",0
info_6  db "6.asm",0
info_7  db "7.asm",0
info_8  db "8.asm",0
info_9  db "9.asm",0

ALIGN   8
p_size  dd 10 dup(0)    ; proc size
result  dd 10 dup(0)    ; time
total   dd 10 dup(0)    ; time total
proc_p  dd 10 dup(0)    ; test proc's
info_p  dd info_0,info_1,info_2,info_3,info_4
        dd info_5,info_6,info_7,info_8,info_9
nerror  dd 0            ; error count

arg_1   dd 0
arg_2   dd 0
arg_3   dd 0
proc_x  dd proc_b

.code

size_p  equ 1024        ; Max proc size
align   16
proc_b  db size_p dup(0)

;-------------------------------------------------------------------------------
; Read binary file
;-------------------------------------------------------------------------------

ReadProc proc uses ebx esi edi ID
local file_name[2], read_size

    mov eax,ID
    add eax,69622E30h
    mov file_name,eax
    mov eax,'n'
    mov file_name[4],eax
    mov edi,proc_x

    FlushInstructionCache(GetCurrentProcess(), edi, size_p)

    xor eax,eax
    mov ecx,size_p/4
    rep stosd
    xor edi,edi
    .if CreateFileA(addr file_name, 80000000h, edi, edi, 3, edi, edi) != -1
        mov ebx,eax
        .if ReadFile(ebx, proc_x, size_p, addr read_size, 0)
            mov edi,read_size
        .endif
        CloseHandle(ebx)
    .endif
    .if !edi
        printf("error reading: %s\n", addr file_name)
    .endif
    mov eax,edi
    ret
ReadProc endp

TestProc proc uses esi edi ebx count, proc_id

local p

    mov ecx,count
    mov edx,proc_id

    mov esi,edx         ; proc id 0..9
    xor eax,eax
    lea ebx,p_size
    lea ebx,[ebx+edx*8]
    mov [ebx],eax       ; proc size

    lea eax,proc_p
    mov eax,[eax+edx*8] ; proc
    .if !eax

        ReadProc(edx)
        mov [ebx],eax
        test eax,eax
        mov eax,proc_x
        jz toend
    .endif
    mov p,eax
    Sleep(0)

    ;
    ; MichaelW's macros
    ;

    HIGH_PRIORITY_CLASS     equ 80h
    NORMAL_PRIORITY_CLASS   equ 20h
    PAGE_EXECUTE_READ       equ 20h
    PAGE_EXECUTE_READWRITE  equ 40h

    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)

    xor eax,eax
    cpuid
    rdtsc
    mov edi,eax
    xor eax,eax
    cpuid
    mov ecx,count
    shl ecx,10
    .while ecx
        sub ecx,1
    .endw
    xor eax,eax
    cpuid
    rdtsc
    sub eax,edi
    mov edi,eax
    xor eax,eax
    cpuid
    rdtsc
    mov esi,eax
    xor eax,eax
    cpuid

    mov ebx,count
    shl ebx,10
    .while ebx
        mov ecx,arg_1
        call p
        dec ebx
    .endw

    xor eax,eax
    cpuid
    rdtsc
    sub eax,edi
    sub eax,esi
    mov edi,eax

    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS)

    shr edi,10
    mov esi,proc_id
    lea ecx,result
    add [ecx+esi*8],edi
    lea edx,p_size
    mov edx,[edx+esi*8]
    lea eax,info_p
    mov eax,[eax+esi*8]
    printf("%9i cycles, rep(%i), code(%3i) %i.asm: %s\n", edi, count, edx, esi, eax)
    mov eax,1
toend:
    ret
TestProc endp

;-------------------------------------------------------------------------------
; test if the algo actually works..
;-------------------------------------------------------------------------------

validate_x PROC USES esi edi ebx x

    mov ecx,x
    lea eax,proc_p
    mov esi,[eax+ecx*8]
    .if !esi
        .if ReadProc(ecx)
            mov esi,proc_x
        .endif
    .endif
    .if esi
        mov ecx,arg_1
        xor ebx,ebx
        call esi
        .if eax != ebx
            printf( "error: eax = %i (%i) %u.asm\n", eax, ebx, x )
            inc nerror
        .endif
    .else
        printf( "error load: %d.asm\n", x )
        inc nerror
    .endif
    ret
validate_x ENDP

GetCycleCount proc uses esi edi ebx l1, l2, step, count

    mov ebx,l1
    mov edi,l2

    .while edi >= ebx

        printf("-- proc(%i)\n", ebx)
        procs
            TestProc( count, x )
        endm
        add ebx,step
    .endw

    lea esi,result
    lea edi,total

    .while  1
        xor ebx,ebx
        xor edx,edx
        xor ecx,ecx
        dec edx
        .repeat
            mov eax,[esi+ecx*8]
            .if eax && eax < edx
                mov edx,eax
                mov ebx,ecx
            .endif
            inc ecx
        .until  ecx == 10
        mov eax,[esi+ebx*8]
        .break .if !eax
        add [edi+ebx*8],eax
        xor eax,eax
        mov [esi+ebx*8],eax
    .endw

    printf("\ntotal [%i .. %i], %i++\n", l1, l2, step)

    .while 1
        xor ebx,ebx
        xor edx,edx
        xor ecx,ecx
        dec edx
        .repeat
            mov eax,[edi+ecx*8]
            .if eax && eax < edx
                mov edx,eax
                mov ebx,ecx
            .endif
            inc ecx
        .until ecx == 10
        mov edx,[edi+ebx*8]
        .break .if !edx
        xor eax,eax
        mov [edi+ebx*8],eax
        lea ecx,info_p
        mov esi,[ecx+ebx*8]
        printf("%9i cycles %i.asm: %s\n", edx, ebx, esi)
    .endw

    printf("hit any key to continue...\n")
    _getch()
    ret
GetCycleCount endp

main proc argc:dword, argv:dword, environ:dword

    procs
        validate_x(x)
        cmp nerror,0
        jne error
    endm

    GetCycleCount(1, 2, 1, 3000)
    xor eax,eax

toend:
    ret
error:
    printf("hit any key to continue...\n")
    _getch()
    jmp toend
main endp

;-------------------------------------------------------------------------------
; Startup and CPU detection
;-------------------------------------------------------------------------------

SSE_MMX         equ 0001h
SSE_SSE         equ 0002h
SSE_SSE2        equ 0004h
SSE_SSE3        equ 0008h
SSE_SSSE3       equ 0010h
SSE_SSE41       equ 0020h
SSE_SSE42       equ 0040h
SSE_XGETBV      equ 0080h
SSE_AVX         equ 0100h
SSE_AVX2        equ 0200h
SSE_AVXOS       equ 0400h

mainCRTStartup proc
local argc:dword, argv:dword, environ:dword,
    lpflOldProtect:dword, sselevel:dword, cpustring[80]:byte

    lea eax,cpustring
    __getmainargs(&argc, &argv, &environ, eax, eax)

    pushfd
    pop     eax
    mov     ecx,200000h
    mov     edx,eax
    xor     eax,ecx
    push    eax
    popfd
    pushfd
    pop     eax
    xor     eax,edx
    and     eax,ecx

    .if !ZERO?

        xor eax,eax
        cpuid
        .if eax
            .if ah == 5
                xor     eax,eax
            .else
                mov     eax,7
                xor     ecx,ecx
                cpuid                   ; check AVX2 support
                xor     eax,eax
                bt      ebx,5           ; AVX2
                rcl     eax,1           ; into bit 9
                push    eax
                mov     eax,1
                cpuid
                pop     eax
                bt      ecx,28          ; AVX support by CPU
                rcl     eax,1           ; into bit 8
                bt      ecx,27          ; XGETBV supported
                rcl     eax,1           ; into bit 7
                bt      ecx,20          ; SSE4.2
                rcl     eax,1           ; into bit 6
                bt      ecx,19          ; SSE4.1
                rcl     eax,1           ; into bit 5
                bt      ecx,9           ; SSSE3
                rcl     eax,1           ; into bit 4
                bt      ecx,0           ; SSE3
                rcl     eax,1           ; into bit 3
                bt      edx,26          ; SSE2
                rcl     eax,1           ; into bit 2
                bt      edx,25          ; SSE
                rcl     eax,1           ; into bit 1
                bt      ecx,0           ; MMX
                rcl     eax,1           ; into bit 0
                mov     sselevel,eax
            .endif
        .endif
    .endif

    .if eax & SSE_XGETBV
        push eax
        xor ecx,ecx
        xgetbv
        and eax,6               ; AVX support by OS?
        pop eax
        .if !ZERO?
            or sselevel,SSE_AVXOS
        .endif
    .endif
    .if !( eax & SSE_SSE2 )
        printf("CPU error: Need SSE2 level\n")
        exit(0)
    .endif

    lea edi,cpustring
    xor esi,esi
    .repeat
        lea eax,[esi+80000002h]
        cpuid
        mov [edi],eax
        mov [edi+4],ebx
        mov [edi+8],ecx
        mov [edi+12],edx
        add edi,16
        inc esi
    .until esi == 3

    .for eax=&cpustring: BYTE PTR [eax] == ' ' : eax++
    .endf
    printf("%s ( ", eax)
    mov eax,sselevel
    .switch
      .case eax & SSE_AVX2:  printf("AVX2 ")
      .case eax & SSE_AVX:   printf("AVX ")
      .case eax & SSE_SSE42: printf("SSE4.2 ")
      .case eax & SSE_SSE41: printf("SSE4.1 ")
      .case eax & SSE_SSSE3: printf("SSSE3 ")
      .case eax & SSE_SSE3:  printf("SSE3 ")
      .default
        printf("SSE2 ")
    .endsw

    printf( ")\n----------------------------------------------\n" )
    mov proc_x,offset proc_b
    .if !VirtualProtect(proc_x, size_p, PAGE_EXECUTE_READWRITE, &lpflOldProtect)
        printf("VirtualProtect error..\n")
        exit(1)
    .endif
    exit(main(argc, argv, environ))

mainCRTStartup endp

    end mainCRTStartup


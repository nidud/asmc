
    option  win64:save auto

    option  dllimport:<msvcrt>
    printf  proto :ptr byte, :vararg
    exit    proto :dword
    _getch  proto

    option  dllimport:<kernel32>
    GetCurrentProcess proto
    CreateFileA proto :ptr, :dword, :dword, :ptr, :dword, :dword, :ptr
    ReadFile proto :ptr, :ptr, :ptr, :ptr, :ptr
    CloseHandle proto :ptr
    FlushInstructionCache proto :ptr, :ptr, :ptr
    VirtualProtect proto :ptr, :ptr, :ptr, :ptr
    SetPriorityClass proto :ptr, :dword
    Sleep proto :ptr
    option dllimport:NONE

.data

size_p  equ 4096        ; max proc size
p_size  dq 10 dup(0)    ; proc size
result  dq 10 dup(0)    ; time
total   dq 10 dup(0)    ; time total
proc_p  dq 10 dup(0)    ; test proc's
info_p  dq info_0,info_1,info_2,info_3,info_4
        dq info_5,info_6,info_7,info_8,info_9
proc_x  dq proc_b
step_x  dd 0
nerror  dd 0

.code

align   16
proc_b  db size_p dup(0)

;-------------------------------------------------------------------------------
; Read binary file
;-------------------------------------------------------------------------------

ReadProc proc uses rbx rsi rdi ID       ; 0..9

  local file_name:qword, read_size:qword

    mov rax,0x6E69622E30 ; 0.bin
    or  al,cl
    mov file_name,rax
    mov rdi,proc_x

    FlushInstructionCache(GetCurrentProcess(), rdi, size_p)

    xor rax,rax
    mov rcx,size_p/8
    rep stosq

    xor rdi,rdi
    .if CreateFileA(addr file_name, 80000000h, edi, rdi, 3, edi, rdi) != -1
        mov rbx,rax
        .if ReadFile(rbx, proc_x, size_p, addr read_size, 0)
            mov rdi,read_size
        .endif
        CloseHandle(rbx)
    .endif
    .if !rdi
        printf("error reading: %s\n", addr file_name)
    .endif
    mov rax,rdi
    ret

ReadProc endp

TestProc proc uses rsi rdi rbx r12 count:QWORD, proc_id:QWORD

    mov count,rcx
    mov proc_id,rdx

    mov rsi,rdx         ; proc id 0..9
    xor rax,rax
    lea rbx,p_size
    lea rbx,[rbx+rdx*8]
    mov [rbx],eax       ; proc size
    lea rax,proc_p
    mov rax,[rax+rdx*8] ; proc

    .repeat

        .if !rax

            ReadProc( edx )
            mov [rbx],eax
            test eax,eax
            mov rax,proc_x
            .break .ifz
        .endif
        mov r12,rax
        ;
        ; spin up..
        ;
        mov ebx,4
        .while rbx
            args_x()
            call r12
            dec ebx
        .endw
        ;
        ; x64-Version of MichaelW's macros
        ;
        HIGH_PRIORITY_CLASS     equ 0x80
        NORMAL_PRIORITY_CLASS   equ 0x20
        PAGE_EXECUTE_READ       equ 0x20
        PAGE_EXECUTE_READWRITE  equ 0x40

        SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)

        xor eax,eax
        cpuid
        rdtsc
        mov edi,eax
        xor eax,eax
        cpuid
        mov rcx,count
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
        xor rax,rax
        cpuid

        mov rbx,count
        shl rbx,10
        .while rbx
            args_x()
            call r12
            dec rbx
        .endw

        xor eax,eax
        cpuid
        rdtsc
        sub eax,edi
        sub eax,esi
        mov edi,eax

        SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS)

        shr edi,10
        mov rsi,proc_id
        lea rcx,result
        add [rcx+rsi*8],edi
        lea r9,p_size
        mov r9,[r9+rsi*8]
        lea rax,info_p
        mov rax,[rax+rsi*8]
        printf("%9i cycles, rep(%i), code(%3i) %i.asm: %s\n", edi, count, r9, esi, rax)
        mov eax,1
    .until 1
    ret

TestProc endp

GetCycleCount proc uses rsi rdi rbx l1, l2, step, count

    mov l1,ecx
    mov l2,edx
    mov step,r8d
    mov count,r9d

    mov rbx,rcx
    mov rdi,rdx

    .while edi >= ebx

        mov step_x,ebx
        printf("-- test(%i)\n", ebx)
        procs
            TestProc( count, x )
        endm
        add ebx,step
    .endw

    lea rsi,result
    lea rdi,total

    .while  1
        xor ebx,ebx
        xor edx,edx
        xor ecx,ecx
        dec rdx
        .repeat
            mov rax,[rsi+rcx*8]
            .if eax && eax < edx
                mov rdx,rax
                mov rbx,rcx
            .endif
            inc rcx
        .until  ecx == 10
        mov eax,[rsi+rbx*8]
        .break .if !eax
        add [rdi+rbx*8],eax
        xor eax,eax
        mov [rsi+rbx*8],eax
    .endw

    printf("\ntotal [%i .. %i], %i++\n", l1, l2, step)

    .while 1
        xor r8,r8
        xor rdx,rdx
        xor rcx,rcx
        dec rdx
        .repeat
            mov eax,[rdi+rcx*8]
            .if eax && eax < edx
                mov rdx,rax
                mov r8,rcx
            .endif
            inc ecx
        .until ecx == 10

        mov edx,[rdi+r8*8]
        .break .if !edx
        xor eax,eax
        mov [rdi+r8*8],eax
        lea rcx,info_p
        mov r9,[rcx+r8*8]
        printf("%9i cycles %i.asm: %s\n", edx, r8d, r9)
    .endw

    printf("hit any key to continue...\r")
    _getch()
    ret

GetCycleCount endp

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

main proto

start proc

  local lpflOldProtect:qword, sselevel:dword, cpustring[80]:byte

    pushfq
    pop     rax
    mov     rcx,200000h
    mov     rdx,rax
    xor     rax,rcx
    push    rax
    popfq
    pushfq
    pop     rax
    xor     rax,rdx
    and     rax,rcx

    .ifnz

        xor rax,rax
        cpuid
        .if rax
            .if ah == 5
                xor     eax,eax
            .else
                mov     rax,7
                xor     rcx,rcx
                cpuid                   ; check AVX2 support
                xor     eax,eax
                bt      ebx,5           ; AVX2
                rcl     eax,1           ; into bit 9
                push    rax
                mov     eax,1
                cpuid
                pop     rax
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
        push rax
        xor rcx,rcx
        xgetbv
        and rax,6 ; AVX support by OS?
        pop rax
        .ifnz
            or sselevel,SSE_AVXOS
        .endif
    .endif

    .if !( eax & SSE_SSE2 )

        printf("CPU error: Need SSE2 level\n")
        exit(0)
    .endif

    lea r8,cpustring
    xor r9d,r9d
    .repeat
        lea rax,[r9+0x80000002]
        cpuid
        mov [r8],eax
        mov [r8+4],ebx
        mov [r8+8],ecx
        mov [r8+12],edx
        add r8,16
        inc r9d
    .until r9d == 3

    .for rax=&cpustring: BYTE PTR [rax] == ' ' : rax++

    .endf

    printf("%s (", rax)
    mov eax,sselevel

    .switch
      .case eax & SSE_AVX2:  printf("AVX2")   : .endc
      .case eax & SSE_AVX:   printf("AVX")    : .endc
      .case eax & SSE_SSE42: printf("SSE4.2") : .endc
      .case eax & SSE_SSE41: printf("SSE4.1") : .endc
      .case eax & SSE_SSSE3: printf("SSSE3")  : .endc
      .case eax & SSE_SSE3:  printf("SSE3")   : .endc
      .default
        printf( "SSE2" )
    .endsw

    printf( ")\n----------------------------------------------\n" )

    lea rax,proc_b
    and rax,-64
    mov proc_x,rax

    .if !VirtualProtect(proc_x, size_p, PAGE_EXECUTE_READWRITE, &lpflOldProtect)

        printf("VirtualProtect error..\n")
        exit(1)
    .endif
    exit(main())
    ret

start endp

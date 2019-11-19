
    option  win64:3

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
    PCOUNT = 0
    procs
    if x gt PCOUNT
        PCOUNT = x
    endif
    endm
    PCOUNT = PCOUNT + 1

    size_p  equ 4096         ; max proc size
    p_size  dq PCOUNT dup(0) ; proc size
    result  dq PCOUNT dup(0) ; time
    total   dq PCOUNT dup(0) ; time total
    proc_p  dq PCOUNT dup(0) ; test proc's
    proc_x  dq proc_b
    step_x  dd 0
    nerror  dd 0
    sselev  dd 0
    info_p  label qword
    INFOID = 0
    while INFOID lt PCOUNT
      if INFOID lt 10
        %dq @CatStr(<info_>, %INFOID)
      else
        dq @CatStr(<info_>, @SubStr(<abcdefghijklmnopqrstuvwxyz>, INFOID-9, 1))
      endif
      INFOID = INFOID + 1
    endm

    .code

    align   16
    proc_b  db size_p dup(0)

;-------------------------------------------------------------------------------
; Read binary file
;-------------------------------------------------------------------------------

ReadProc proc uses rbx rsi rdi ID

  local file_name:qword, read_size:qword

    mov rax,0x6E69622E30 ; 0.bin
    or  al,cl
    .if cl >9
        add al,7
    .endif
    mov file_name,rax
    mov rdi,proc_x

    FlushInstructionCache( GetCurrentProcess(), rdi, size_p )

    xor eax,eax
    mov ecx,size_p/8
    rep stosq

    xor edi,edi
    .ifd CreateFileA( &file_name, 0x80000000, edi, rdi, 3, edi, rdi ) != -1

        mov rbx,rax
        .ifd ReadFile( rbx, proc_x, size_p, &read_size, 0 )

            mov rdi,read_size
        .endif
        CloseHandle(rbx)
    .endif

    .if !rdi

        printf("error reading: %s\n", &file_name)
    .endif
    mov rax,rdi
    ret

ReadProc endp


TestProc proc uses rsi rdi rbx r12 count, proc_id

    mov esi,edx         ; proc id 0..9
    xor eax,eax

    lea rbx,p_size
    lea rbx,[rbx+rdx*8]
    mov [rbx],eax       ; proc size

    lea rax,proc_p
    mov rax,[rax+rdx*8] ; proc

    .if !rax

        ReadProc(edx)
        mov [rbx],eax
        mov ecx,eax
        mov rax,proc_x
        .return .if !ecx
    .endif

    ; spin up..

    .for r12 = rax, ebx = 4 : ebx : ebx--

        args_x()
        call r12
    .endf

    ; x64-Version of MichaelW's macros

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
    .for ecx = count, ecx <<= 10 : ecx : ecx -= 1
    .endf

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

    .for ebx = count, ebx <<= 10 : ebx : ebx--

        args_x()
        call r12
    .endf

    xor eax,eax
    cpuid
    rdtsc
    sub eax,edi
    sub eax,esi
    mov edi,eax

    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS)

    shr edi,10
    mov esi,proc_id
    lea rcx,result
    add [rcx+rsi*8],edi
    lea r9,p_size
    mov r9,[r9+rsi*8]
    lea rax,info_p
    mov rax,[rax+rsi*8]

    .if esi > 9
        add esi,7+'a'-'A'
    .endif
    add esi,'0'
    printf("%9i cycles, rep(%i), code(%3i) %c.asm: %s\n", edi, count, r9, esi, rax)
    mov eax,1
    ret

TestProc endp

GetCycleCount proc uses rsi rdi rbx l1, l2, step, count

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

    .while 1

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
        .until ecx == PCOUNT

        mov eax,[rsi+rbx*8]
        .break .if !eax

        add [rdi+rbx*8],eax
        xor eax,eax
        mov [rsi+rbx*8],eax
    .endw

    printf("\ntotal [%i .. %i], %i++\n", l1, l2, step)

    .while 1

        xor r8d,r8d
        xor edx,edx
        xor ecx,ecx
        dec rdx

        .repeat
            mov eax,[rdi+rcx*8]
            .if eax && eax < edx
                mov edx,eax
                mov r8d,ecx
            .endif
            inc ecx
        .until ecx == PCOUNT

        mov edx,[rdi+r8*8]
        .break .if !edx

        xor eax,eax
        mov [rdi+r8*8],eax

        lea rcx,info_p
        mov r9,[rcx+r8*8]
        .if r8d > 9
            add r8d,7+'a'-'A'
        .endif
        add r8d,'0'
        printf("%9i cycles %c.asm: %s\n", edx, r8d, r9)
    .endw

    printf("hit any key to continue...\r")
    _getch()
    ret

GetCycleCount endp

;-------------------------------------------------------------------------------
; Startup and CPU detection
;-------------------------------------------------------------------------------

SSE_MMX                 equ 0x00000001
SSE_SSE                 equ 0x00000002
SSE_SSE2                equ 0x00000004
SSE_SSE3                equ 0x00000008
SSE_SSSE3               equ 0x00000010
SSE_SSE41               equ 0x00000020
SSE_SSE42               equ 0x00000040
SSE_XGETBV              equ 0x00000080
SSE_AVX                 equ 0x00000100
SSE_AVX2                equ 0x00000200
SSE_AVX512F             equ 0x00000400
SSE_AVX512PF            equ 0x00000800
SSE_AVX512ER            equ 0x00001000
SSE_AVX512CD            equ 0x00002000
SSE_AVX512VBMI2         equ 0x00004000
SSE_AVX512PGFNI         equ 0x00008000
SSE_AVX512PVAES         equ 0x00010000
SSE_AVX512PVPCLMULQDQ   equ 0x00020000
SSE_AVX512VNNI          equ 0x00040000
SSE_AVX512BITALG        equ 0x00080000
SSE_AVX512VPOPCNTDQ     equ 0x00100000
SSE_AVX512VP2INTERSECT  equ 0x00200000
SSE_AVX512DQ            equ 0x00400000
SSE_AVX512IFMA          equ 0x00800000
SSE_AVX5124FMAPS        equ 0x01000000
SSE_AVX5124VNNIW        equ 0x02000000
SSE_AVX512VL            equ 0x04000000
SSE_AVX512VBMI          equ 0x08000000
SSE_AVX512BW            equ 0x10000000
SSE_AVX512BF16          equ 0x20000000
SSE_AVXOS               equ 0x40000000

setsselevel proc uses rbx

    pushfq
    pop     rax
    mov     ecx,0x200000
    mov     rdx,rax
    xor     rax,rcx
    push    rax
    popfq
    pushfq
    pop     rax
    xor     rax,rdx
    and     rax,rcx

    .ifnz

        xor eax,eax
        cpuid
        .if rax
            .if ah == 5
                xor     eax,eax
            .else
                mov     eax,7
                xor     ecx,ecx
                cpuid               ; check AVX2 support
                xor     eax,eax
                bt      ebx,5       ; AVX2
                adc     eax,eax     ; into bit 9
                push    rax
                mov     eax,1
                cpuid
                pop     rax
                bt      ecx,28      ; AVX support by CPU
                adc     eax,eax     ; into bit 8
                bt      ecx,27      ; XGETBV supported
                adc     eax,eax     ; into bit 7
                bt      ecx,20      ; SSE4.2
                adc     eax,eax     ; into bit 6
                bt      ecx,19      ; SSE4.1
                adc     eax,eax     ; into bit 5
                bt      ecx,9       ; SSSE3
                adc     eax,eax     ; into bit 4
                bt      ecx,0       ; SSE3
                adc     eax,eax     ; into bit 3
                bt      edx,26      ; SSE2
                adc     eax,eax     ; into bit 2
                bt      edx,25      ; SSE
                adc     eax,eax     ; into bit 1
                bt      ecx,0       ; MMX
                adc     eax,eax     ; into bit 0
                mov     sselev,eax
            .endif
        .endif
    .endif

    .if eax & SSE_XGETBV

        xor ecx,ecx
        xgetbv
        .if eax & 6 ; AVX support by OS?
            or sselev,SSE_AVXOS
        .endif

        and eax,0xE0
        .if eax == 0xE0

            xor ecx,ecx
            mov eax,7
            cpuid

            .if ebx & 1 shl 16      ; SSE_AVX512F ?

                xor eax,eax
                bt  ebx,30          ; SSE_AVX512BW
                adc eax,eax         ; into bit 28
                bt  ecx,1           ; SSE_AVX512VBMI
                adc eax,eax         ; into bit 27
                bt  ebx,31          ; SSE_AVX512VL
                adc eax,eax         ; into bit 26
                bt  edx,2           ; SSE_AVX5124VNNIW
                adc eax,eax         ; into bit 25
                bt  edx,3           ; SSE_AVX5124FMAPS
                adc eax,eax         ; into bit 24
                bt  ebx,21          ; SSE_AVX512IFMA
                adc eax,eax         ; into bit 23
                bt  ebx,17          ; SSE_AVX512DQ
                adc eax,eax         ; into bit 22
                bt  edx,8           ; SSE_AVX512VP2INTERSECT
                adc eax,eax         ; into bit 21
                bt  ecx,14          ; SSE_AVX512VPOPCNTDQ
                adc eax,eax         ; into bit 20
                bt  ecx,12          ; SSE_AVX512BITALG
                adc eax,eax         ; into bit 19
                bt  ecx,11          ; SSE_AVX512VNNI
                adc eax,eax         ; into bit 18
                bt  ecx,10          ; SSE_AVX512PVPCLMULQDQ
                adc eax,eax         ; into bit 17
                bt  ecx,9           ; SSE_AVX512PVAES
                adc eax,eax         ; into bit 16
                bt  ecx,8           ; SSE_AVX512PGFNI
                adc eax,eax         ; into bit 15
                bt  ecx,6           ; SSE_AVX512VBMI2
                adc eax,eax         ; into bit 14
                bt  ebx,28          ; SSE_AVX512CD
                adc eax,eax         ; into bit 13
                bt  ebx,27          ; SSE_AVX512ER
                adc eax,eax         ; into bit 12
                bt  ebx,26          ; SSE_AVX512PF
                adc eax,eax         ; into bit 11
                shl eax,11
                or  eax,SSE_AVX512F ; into bit 10
                or  sselev,eax

                mov ecx,1
                mov eax,7
                cpuid
                .if ebx & 1 shl 5
                    or sselev,SSE_AVX512BF16
                .endif
            .endif
        .endif
    .endif
    mov eax,sselev
    ret

setsselevel endp


main proto

start proc

  local lpflOldProtect:qword, cpustring[80]:byte

    .ifd !( setsselevel() & SSE_SSE2 )

        printf("CPU error: Need SSE2 level\n")
        exit(0)
    .endif

    .for ( r8 = &cpustring, r9d = 0 : r9d < 3 : r9d++, r8 += 16 )

        lea rax,[r9+0x80000002]
        cpuid

        mov [r8+0x00],eax
        mov [r8+0x04],ebx
        mov [r8+0x08],ecx
        mov [r8+0x0C],edx
    .endf

    .for rax = &cpustring: byte ptr [rax] == ' ' : rax++
    .endf
    printf("%s (", rax)

    mov eax,sselev
    .switch
    .case eax & SSE_AVX512F: printf("AVX512") : .endc
    .case eax & SSE_AVX2:    printf("AVX2")   : .endc
    .case eax & SSE_AVX:     printf("AVX")    : .endc
    .case eax & SSE_SSE42:   printf("SSE4.2") : .endc
    .case eax & SSE_SSE41:   printf("SSE4.1") : .endc
    .case eax & SSE_SSSE3:   printf("SSSE3")  : .endc
    .case eax & SSE_SSE3:    printf("SSE3")   : .endc
    .default
        printf( "SSE2" )
    .endsw
    printf( ")\n----------------------------------------------\n" )

    lea rax,proc_b
    and rax,-64
    mov proc_x,rax

    .ifd !VirtualProtect(proc_x, size_p, PAGE_EXECUTE_READWRITE, &lpflOldProtect)

        printf("VirtualProtect error..\n")
        exit(1)
    .endif
    exit(main())
    ret

start endp

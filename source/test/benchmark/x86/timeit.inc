
    .686
    .xmm
    .model flat, c

    option  dllimport:<msvcrt>
    printf  proto :ptr byte, :vararg
    exit    proto :dword
    _getch  proto

    option  dllimport:<kernel32>
    GetCurrentProcess proto stdcall
    CreateFileA proto stdcall :ptr, :dword, :dword, :ptr, :dword, :dword, :ptr
    ReadFile proto stdcall :ptr, :ptr, :ptr, :ptr, :ptr
    CloseHandle proto stdcall :ptr
    FlushInstructionCache proto stdcall :ptr, :ptr, :ptr
    VirtualProtect proto stdcall :ptr, :ptr, :ptr, :ptr
    SetPriorityClass proto stdcall :ptr, :dword
    Sleep proto stdcall :ptr
    GetModuleHandleA proto stdcall :ptr
    GetProcAddress proto stdcall :dword, :ptr
    MEM_COMMIT equ 0x1000
    MEM_RELEASE equ 0x8000
    PAGE_READWRITE equ 0x04
    VirtualAlloc proto stdcall :dword, :dword, :dword, :dword
    VirtualFree proto stdcall :dword, :dword, :dword
    option dllimport:NONE

.data

size_p  equ 4096        ; max proc size
p_size  dd 10 dup(0)    ; proc size
result  dd 10 dup(0)    ; time
total   dd 10 dup(0)    ; time total
proc_p  dd 10 dup(0)    ; test proc's
info_p  dd info_0,info_1,info_2,info_3,info_4
        dd info_5,info_6,info_7,info_8,info_9
proc_x  dd proc_b
step_x  dd 0
nerror  dd 0
sselevel dd 0

.code

align   16
proc_b  db size_p dup(0)

;-------------------------------------------------------------------------------
; Read binary file
;-------------------------------------------------------------------------------

ReadProc proc uses ebx esi edi ID       ; 0..9

  local file_name:qword, read_size:dword

    mov eax,0x69622E30 ; 0.bin
    or  al,byte ptr ID
    mov dword ptr file_name,eax
    mov eax,'n'
    mov dword ptr file_name[4],eax
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

TestProc proc uses esi edi ebx count:DWORD, proc_id:DWORD, print:DWORD

  local p,s

    mov esi,proc_id     ; proc id 0..9
    xor eax,eax
    lea ebx,p_size
    lea ebx,[ebx+esi*4]
    mov [ebx],eax       ; proc size
    lea eax,proc_p
    mov eax,[eax+esi*4] ; proc

    .repeat

        mov s,esp
        .if !eax

            ReadProc( esi )
            mov [ebx],eax
            test eax,eax
            mov eax,proc_x
            .break .ifz
        .endif
        mov p,eax
        ;
        ; spin up..
        ;
        mov ebx,10
        .while ebx
            args_x()
            call p
            mov esp,s
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
            args_x()
            call p
            mov esp,s
            dec ebx
        .endw

        xor eax,eax
        cpuid
        rdtsc
        sub eax,edi
        sub eax,esi
        mov edi,eax

        SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS)

        .if print
            shr edi,10
            mov esi,proc_id
            lea ecx,result
            add [ecx+esi*4],edi
            lea ebx,p_size
            mov ebx,[ebx+esi*4]
            lea eax,info_p
            mov eax,[eax+esi*4]
            printf("%9i cycles, rep(%i), code(%3i) %i.asm: %s\n", edi, count, ebx, esi, eax)
        .endif
        mov eax,1
    .until 1
    ret

TestProc endp

GetCycleCount proc uses esi edi ebx l1, l2, step, count

    procs
        TestProc( count, x, 0 )
    endm

    mov ebx,l1
    mov edi,l2

    .while edi >= ebx

        mov step_x,ebx
        printf("-- test(%i)\n", ebx)
        procs
            TestProc( count, x, 1 )
        endm
        add ebx,step
    .endw

    lea esi,result
    lea edi,total

    .while 1
        xor ebx,ebx
        xor edx,edx
        xor ecx,ecx
        dec edx
        .repeat
            mov eax,[esi+ecx*4]
            .if eax && eax < edx
                mov edx,eax
                mov ebx,ecx
            .endif
            inc ecx
        .until  ecx == 10
        mov eax,[esi+ebx*4]
        .break .if !eax
        add [edi+ebx*4],eax
        xor eax,eax
        mov [esi+ebx*4],eax
    .endw

    printf("\ntotal [%i .. %i], %i++\n", l1, l2, step)

    .while 1
        xor ebx,ebx
        xor edx,edx
        xor ecx,ecx
        dec edx
        .repeat
            mov eax,[edi+ecx*4]
            .if eax && eax < edx
                mov edx,eax
                mov ebx,ecx
            .endif
            inc ecx
        .until ecx == 10

        mov edx,[edi+ebx*4]
        .break .if !edx
        xor eax,eax
        mov [edi+ebx*4],eax
        lea ecx,info_p
        mov eax,[ecx+ebx*4]
        printf("%9i cycles %i.asm: %s\n", edx, ebx, eax)
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

setsselevel proc uses ebx

    pushfd
    pop     eax
    mov     ecx,0x200000
    mov     edx,eax
    xor     eax,ecx
    push    eax
    popfd
    pushfd
    pop     eax
    xor     eax,edx
    and     eax,ecx

    .ifnz

        xor eax,eax
        cpuid
        .if eax
            .if ah == 5
                xor     eax,eax
            .else
                mov     eax,7
                xor     ecx,ecx
                cpuid               ; check AVX2 support
                xor     eax,eax
                bt      ebx,5       ; AVX2
                adc     eax,eax     ; into bit 9
                push    eax
                mov     eax,1
                cpuid
                pop     eax
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
                mov     sselevel,eax
            .endif
        .endif
    .endif

    .if eax & SSE_XGETBV

        xor ecx,ecx
        xgetbv
        .if eax & 6 ; AVX support by OS?
            or sselevel,SSE_AVXOS
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
                or  sselevel,eax

                mov ecx,1
                mov eax,7
                cpuid
                .if ebx & 1 shl 5
                    or sselevel,SSE_AVX512BF16
                .endif
            .endif
        .endif
    .endif
    ret

setsselevel endp

main proto

start proc uses esi edi ebx

  local lpflOldProtect:qword, cpustring[80]:byte

    setsselevel()

    .if !( sselevel & SSE_SSE2 )

        printf("CPU error: Need SSE2 level\n")
        exit(0)
    .endif

    lea edi,cpustring
    xor esi,esi
    .repeat
        lea eax,[esi+0x80000002]
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

    printf("%s (", eax)
    mov eax,sselevel

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

    lea eax,proc_b
    mov proc_x,eax

    .if !VirtualProtect(proc_x, size_p, PAGE_EXECUTE_READWRITE, &lpflOldProtect)

        printf("VirtualProtect error..\n")
        exit(1)
    .endif
    exit(main())
    ret

start endp


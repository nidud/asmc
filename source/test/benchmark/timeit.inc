ifdef _WIN64
option win64:3
size_t typedef qword
define WINAPI <>
else
.686
.xmm
.model flat, c
size_t typedef dword
define rax <eax>
define rdx <edx>
define rbx <ebx>
define rcx <ecx>
define rdi <edi>
define rsi <esi>
define rbp <ebp>
define rsp <esp>
define WINAPI <stdcall>
endif

.pragma comment(lib, msvcrt)
printf  proto :ptr byte, :vararg
fprintf proto :ptr, :ptr byte, :vararg
fopen   proto :ptr, :ptr
fclose  proto :ptr
fread   proto :ptr, :sdword, :sdword, :ptr
exit    proto :dword
_getch  proto

ifndef __UNIX__
.pragma comment(lib, kernel32)
GetCurrentProcess proto WINAPI
FlushInstructionCache proto WINAPI :ptr, :ptr, :ptr
VirtualProtect proto WINAPI :ptr, :ptr, :ptr, :ptr
SetPriorityClass proto WINAPI :ptr, :dword
define MEM_COMMIT 0x1000
define MEM_RELEASE 0x8000
define PAGE_READWRITE 0x04
VirtualAlloc proto WINAPI :dword, :dword, :dword, :dword
VirtualFree proto WINAPI :ptr, :dword, :dword
SetUnhandledExceptionFilter proto WINAPI :ptr
option dllimport:NONE
endif

ptr_t typedef ptr

main proto

.data
 PCOUNT = 0
 procs
    if x gt PCOUNT
        PCOUNT = x
    endif
    endm
 PCOUNT = PCOUNT + 1
 size_p  equ 4096         ; max proc size
 p_size  ptr_t PCOUNT dup(0) ; proc size
 result  ptr_t PCOUNT dup(0) ; time
 total   ptr_t PCOUNT dup(0) ; time total
 proc_p  ptr_t PCOUNT dup(0) ; test proc's
 proc_x  ptr_t proc_b
 m_4096  ptr_t 0
 m_endp  ptr_t 0
 fp      ptr_t 0
 file_x  dd 0
 step_x  dd 0
 nerror  dd 0
 sselev  dd 0
 info_p  label ptr_t
 INFOID = 0
 while INFOID lt PCOUNT
    if INFOID lt 10
      %ptr_t @CatStr(<info_>, %INFOID)
    else
      ptr_t @CatStr(<info_>, @SubStr(<abcdefghijklmnopqrstuvwxyz>, INFOID-9, 1))
    endif
    INFOID = INFOID + 1
    endm

.data?
 align 16
 proc_b db size_p dup(?)

.code

;-------------------------------------------------------------------------------
; Read binary file
;-------------------------------------------------------------------------------

ReadProc proc uses rdi rbx ID:dword

   .new file_name[8]:sbyte
   .new read_size:sdword = 0

    ldr ecx,ID
    mov file_x,ecx
    mov eax,0x69622E30 ; 0.bin
    or  al,cl
    mov dword ptr file_name,eax
    mov eax,'n'
    mov dword ptr file_name[4],eax
ifndef __UNIX__
    FlushInstructionCache( GetCurrentProcess(), proc_x, size_p )
endif
    lea rdi,proc_b
    xor eax,eax
    mov ecx,size_p/4
    rep stosd
    .if fopen(&file_name, "rb")
        mov rbx,rax
        mov read_size,fread(&proc_b, 1, size_p, rbx)
        fclose(rbx)
    .endif
    .if ( read_size <= 0 )
        printf("error reading: %s\n", &file_name)
    .endif
    mov eax,read_size
    ret
    endp

CallProc macro p
    args_x()
    call p
ifndef _WIN64
    mov esp,s
endif
    exitm<>
    endm

TestProc proc uses rsi rdi rbx count, proc_id

   .new p:ptr_t
ifndef _WIN64
   .new s:ptr_t = esp
endif
    mov esi,proc_id             ; proc id 0..9
    xor eax,eax
    lea rbx,p_size
    lea rbx,[rbx+rsi*size_t]
    mov [rbx],eax               ; proc size
    lea rax,proc_p
    mov rax,[rax+rsi*size_t]    ; proc
    .if !rax
        ReadProc(esi)
        mov [rbx],eax
        mov ecx,eax
        mov rax,proc_x
       .return .if !ecx
    .endif
    mov p,rax

    ; spin up..

    .for ( ebx = 4 : ebx : ebx-- )
        CallProc(p)
    .endf
ifndef __UNIX__
    HIGH_PRIORITY_CLASS     equ 0x80
    NORMAL_PRIORITY_CLASS   equ 0x20
    PAGE_EXECUTE_READ       equ 0x20
    PAGE_EXECUTE_READWRITE  equ 0x40
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)
endif
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
        CallProc(p)
    .endf
    xor eax,eax
    cpuid
    rdtsc
    sub eax,edi
    sub eax,esi
    mov edi,eax
ifndef __UNIX__
    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS)
endif
    shr edi,10
    mov esi,proc_id
    lea rcx,result
    add [rcx+rsi*size_t],edi
    lea rcx,p_size
    mov rcx,[rcx+rsi*size_t]
    lea rax,info_p
    mov rax,[rax+rsi*size_t]
    .if esi > 9
        add esi,7+'a'-'A'
    .endif
    add esi,'0'
    printf("%9i cycles, rep(%i), code(%3i) %c.asm: %s\n", edi, count, rcx, esi, rax)
    mov eax,1
    ret
    endp

GetCycleCount proc uses rsi rdi rbx l1, l2, step, count

    ldr ebx,l1
    ldr edi,l2

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
            mov rax,[rsi+rcx*size_t]
            .if eax && eax < edx
                mov rdx,rax
                mov rbx,rcx
            .endif
            inc rcx
        .until ecx == PCOUNT
        mov eax,[rsi+rbx*size_t]
        .break .if !eax
        add [rdi+rbx*size_t],eax
        xor eax,eax
        mov [rsi+rbx*size_t],eax
    .endw
    printf("\n")
    fprintf(fp, "total [%i .. %i], %i++\n", l1, l2, step)
    .while 1
        xor ebx,ebx
        xor edx,edx
        xor ecx,ecx
        dec rdx
        .repeat
            mov eax,[rdi+rcx*size_t]
            .if eax && eax < edx
                mov edx,eax
                mov ebx,ecx
            .endif
            inc ecx
        .until ecx == PCOUNT
        mov edx,[rdi+rbx*size_t]
        .break .if !edx
        xor eax,eax
        mov [rdi+rbx*size_t],eax
        lea rcx,info_p
        mov rax,[rcx+rbx*size_t]
        lea rcx,p_size
        mov rcx,[rcx+rbx*size_t]
        .if ebx > 9
            add ebx,7+'a'-'A'
        .endif
        add ebx,'0'
        fprintf(fp, "%9i cycles %c.asm(%3d): %s\n", edx, ebx, ecx, rax)
    .endw
if 0
    printf("hit any key to continue...\r")
    _getch()
endif
    printf("\n")
    ret
    endp

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
ifdef _WIN64
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
else
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
endif
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
    endp

ifndef __UNIX__
ifdef _WIN64
define BITS <"Win64">
else
define BITS <"Win32">
endif
ExceptionHandler proc ExceptionRecord:ptr, EstablisherFrame:ptr, ContextRecord:ptr, DispatcherContext:ptr
    ldr rcx,ExceptionRecord
ifdef _WIN64
    .enumt REGS : qword {
        _Rax, _Rcx, _Rdx, _Rbx, _Rsp, _Rbp, _Rsi, _Rdi, _R8, _R9, _R10, _R11, _R12, _R13, _R14, _R15, _Rip }
    assume r8:ptr qword
    add r8,8*15
    lea rdx,info_p
    mov eax,file_x
    mov rdx,[rdx+rax*size_t]
    mov rax,[r8+_Rip]
    sub rax,proc_x
    printf( "Exception%d:   %d.bin %s\n"
            "\tCode: \t     %08X\n"
            "\tFlags:\t     %08X\n"
            "\tRAX: %p R8:  %p\n"
            "\tRBX: %p R9:  %p\n"
            "\tRCX: %p R10: %p\n"
            "\tRDX: %p R11: %p\n"
            "\tRSI: %p R12: %p\n"
            "\tRDI: %p R13: %p\n"
            "\tRBP: %p R14: %p\n"
            "\tRSP: %p R15: %p\n"
            "\tRIP: %p:\n", size_t*8, file_x, rdx, [rcx], [rcx+4],
            [r8+_Rax], [r8+_R8],
            [r8+_Rbx], [r8+_R9],
            [r8+_Rcx], [r8+_R10],
            [r8+_Rdx], [r8+_R11],
            [r8+_Rsi], [r8+_R12],
            [r8+_Rdi], [r8+_R13],
            [r8+_Rbp], [r8+_R14],
            [r8+_Rsp], [r8+_R15], rax)
    assume r8:nothing
else
    .enumt REGS : dword { _Edi, _Esi, _Ebx, _Edx, _Ecx, _Eax, _Ebp, _Eip, SegCs, EFlags, _Esp }
    mov edx,[ecx+4]
    mov ecx,[ecx]
    add edx,0x9C
    mov eax,[edx+_Eip]
    sub eax,proc_x
    mov ebx,file_x
    mov rbx,info_p[rbx*size_t]
    assume edx:ptr dword
    printf( "Exception%d:   %d.bin %s\n"
            "\tCode: \t     %08X\n"
            "\tFlags:\t     %08X\n"
            "\tEAX: %p EDX: %p\n"
            "\tEBX: %p ECX: %p\n"
            "\tESI: %p EDI: %p\n"
            "\tESP: %p EBP: %p\n"
            "\tEIP: %p\n\n", size_t*8, file_x, ebx, [ecx], [ecx+4],
            [edx+_Eax], [edx+_Edx],
            [edx+_Ebx], [edx+_Ecx],
            [edx+_Esi], [edx+_Edi],
            [edx+_Esp], [edx+_Ebp], eax)
    assume edx:nothing
endif
    exit( 1 )
    endp
endif

ifdef _WIN64
OPTION FRAME:AUTO
start proc frame:ExceptionHandler
else
start proc
endif
  local lpflOldProtect:ptr_t, cpustring[80]:byte, retval:dword
    .ifd !( setsselevel() & SSE_SSE2 )
        printf("CPU error: Need SSE2 level\n")
        exit(1)
    .endif
    .if ( fopen("result.txt", "a") == 0 )
        printf("IO error: failed to open result.txt\n")
        exit(1)
    .endif
    mov fp,rax
    fprintf(fp, "----------------------------------------------------\n" )
ifdef _WIN64
    fprintf(fp, "x64: ")
else
    fprintf(fp, "x86: ")
endif
    .for ( rdi = &cpustring, esi = 0 : esi < 3 : esi++, rdi += 16 )
        lea rax,[rsi+0x80000002]
        cpuid
        mov [rdi+0x00],eax
        mov [rdi+0x04],ebx
        mov [rdi+0x08],ecx
        mov [rdi+0x0C],edx
    .endf
    .for rax = &cpustring: byte ptr [rax] == ' ' : rax++
    .endf
    fprintf(fp, "%s (", rax)
    mov eax,sselev
    lea rcx,@CStr("SSE2")
    .switch
    .case eax & SSE_AVX512F: lea rcx,@CStr("AVX512") : .endc
    .case eax & SSE_AVX2:    lea rcx,@CStr("AVX2")   : .endc
    .case eax & SSE_AVX:     lea rcx,@CStr("AVX")    : .endc
    .case eax & SSE_SSE42:   lea rcx,@CStr("SSE4.2") : .endc
    .case eax & SSE_SSE41:   lea rcx,@CStr("SSE4.1") : .endc
    .case eax & SSE_SSSE3:   lea rcx,@CStr("SSSE3")  : .endc
    .case eax & SSE_SSE3:    lea rcx,@CStr("SSE3")   : .endc
    .endsw
    fprintf(fp, "%s)\n----------------------------------------------------\n", rcx)
    lea rax,proc_b
    and rax,-64
    mov proc_x,rax
ifndef __UNIX__
    .ifd !VirtualProtect(proc_x, size_p, PAGE_EXECUTE_READWRITE, &lpflOldProtect)
        printf("VirtualProtect error..\n")
        exit(1)
    .endif
    .if !VirtualAlloc(0, 4096, MEM_COMMIT, PAGE_READWRITE)
        printf("VirtualAlloc error..\n")
        exit(1)
    .endif
    mov m_4096,rax
    add rax,4096
    mov m_endp,rax
ifndef _WIN64
    SetUnhandledExceptionFilter(&ExceptionHandler)
endif
endif
    mov retval,main()
    fclose(fp)
ifndef __UNIX__
    VirtualFree(m_4096, 0, MEM_RELEASE)
endif
    exit(retval)
    ret
    endp

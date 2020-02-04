;; https://msdn.microsoft.com/en-us/library/hskdteyh.aspx
;; InstructionSet.cpp
;; Compile by using: cl /EHsc /W4 InstructionSet.cpp
;; processor: x86, x64
;; Uses the __cpuid intrinsic to get information about
;; CPU extended instruction set support.

include string.inc
include intrin.inc
include malloc.inc
include stdio.inc
include tchar.inc

.class InstructionSet_Internal

    nIds_       SINT ?
    nExIds_     SINT ?
    vendor_     LPSTR ?
    brand_      LPSTR ?
    isIntel_    SINT ?
    isAMD_      SINT ?
    f_1_ECX_    dd ?
    f_1_EDX_    dd ?
    f_7_EBX_    dd ?
    f_7_ECX_    dd ?
    f_81_ECX_   dd ?
    f_81_EDX_   dd ?

    Release     proc
    .ends

.class InstructionSet

    CPU_Rep LPINSTRUCTIONSET_INTERNAL ?

    Release        proc
    ;;
    ;; getters
    ;;
    GetVendor      proc
    GetBrand       proc

    GetSSE3        proc
    GetPCLMULQDQ   proc
    GetMONITOR     proc
    GetSSSE3       proc
    GetFMA         proc
    GetCMPXCHG16B  proc
    GetSSE41       proc
    GetSSE42       proc
    GetMOVBE       proc
    GetPOPCNT      proc
    GetAES         proc
    GetXSAVE       proc
    GetOSXSAVE     proc
    GetAVX         proc
    GetF16C        proc
    GetRDRAND      proc

    GetMSR         proc
    GetCX8         proc
    GetSEP         proc
    GetCMOV        proc
    GetCLFSH       proc
    GetMMX         proc
    GetFXSR        proc
    GetSSE         proc
    GetSSE2        proc

    GetFSGSBASE    proc
    GetBMI1        proc
    GetHLE         proc
    GetAVX2        proc
    GetBMI2        proc
    GetERMS        proc
    GetINVPCID     proc
    GetRTM         proc
    GetAVX512F     proc
    GetRDSEED      proc
    GetADX         proc
    GetAVX512PF    proc
    GetAVX512ER    proc
    GetAVX512CD    proc
    GetSHA         proc

    GetPREFETCHWT1 proc

    GetLAHF        proc
    GetLZCNT       proc
    GetABM         proc
    GetSSE4a       proc
    GetXOP         proc
    GetTBM         proc

    GetSYSCALL     proc
    GetMMXEXT      proc
    GetRDTSCP      proc
    Get3DNOWEXT    proc
    Get3DNOW       proc

    .ends

.data

    InstructionSet_vtable InstructionSetVtbl { \
        InstructionSet_Release,
        InstructionSet_GetVendor,
        InstructionSet_GetBrand,
        InstructionSet_GetSSE3,
        InstructionSet_GetPCLMULQDQ,
        InstructionSet_GetMONITOR,
        InstructionSet_GetSSSE3,
        InstructionSet_GetFMA,
        InstructionSet_GetCMPXCHG16B,
        InstructionSet_GetSSE41,
        InstructionSet_GetSSE42,
        InstructionSet_GetMOVBE,
        InstructionSet_GetPOPCNT,
        InstructionSet_GetAES,
        InstructionSet_GetXSAVE,
        InstructionSet_GetOSXSAVE,
        InstructionSet_GetAVX,
        InstructionSet_GetF16C,
        InstructionSet_GetRDRAND,
        InstructionSet_GetMSR,
        InstructionSet_GetCX8,
        InstructionSet_GetSEP,
        InstructionSet_GetCMOV,
        InstructionSet_GetCLFSH,
        InstructionSet_GetMMX,
        InstructionSet_GetFXSR,
        InstructionSet_GetSSE,
        InstructionSet_GetSSE2,
        InstructionSet_GetFSGSBASE,
        InstructionSet_GetBMI1,
        InstructionSet_GetHLE,
        InstructionSet_GetAVX2,
        InstructionSet_GetBMI2,
        InstructionSet_GetERMS,
        InstructionSet_GetINVPCID,
        InstructionSet_GetRTM,
        InstructionSet_GetAVX512F,
        InstructionSet_GetRDSEED,
        InstructionSet_GetADX,
        InstructionSet_GetAVX512PF,
        InstructionSet_GetAVX512ER,
        InstructionSet_GetAVX512CD,
        InstructionSet_GetSHA,
        InstructionSet_GetPREFETCHWT1,
        InstructionSet_GetLAHF,
        InstructionSet_GetLZCNT,
        InstructionSet_GetABM,
        InstructionSet_GetSSE4a,
        InstructionSet_GetXOP,
        InstructionSet_GetTBM,
        InstructionSet_GetSYSCALL,
        InstructionSet_GetMMXEXT,
        InstructionSet_GetRDTSCP,
        InstructionSet_Get3DNOWEXT,
        InstructionSet_Get3DNOW }

;;
;; Initialize static member data
;:
cpu LPINSTRUCTIONSET 0

.code

__this32 macro
ifndef _WIN64
    mov ecx,this
endif
    retm<rcx>
    endm

    assume rsi:ptr InstructionSet_Internal

InstructionSet_Internal::Release proc uses rsi

    __this32()
    mov rsi,rcx
    free([rsi].vendor_)
    free([rsi].brand_)
    free(rsi)
    ret

InstructionSet_Internal::Release endp

InstructionSet_Internal::InstructionSet_Internal proc uses rsi rdi rbx

  local cpui[4]:SINT
  local vendor[0x20]:SBYTE
  local brand[0x40]:SBYTE
  local cpustring[512]:SBYTE

    .if malloc( InstructionSet_Internal + InstructionSet_InternalVtbl )

        mov rsi,rax
        mov rdi,rax
        xor eax,eax
        mov ecx,InstructionSet_Internal
        rep stosb
        mov [rsi],rdi
        lea rax,InstructionSet_Internal_Release
        mov [rdi],rax
        ;;
        ;; Calling __cpuid with 0x0 as the function_id argument
        ;; gets the number of the highest valid function ID.
        ;;
        mov [rsi].nIds_,__cpuid(&cpui, 0)

        .for (rdi = &cpustring, ebx = 0: ebx <= [rsi].nIds_: ++ebx)

            __cpuidex(&cpui, ebx, 0)
            stosd
            mov eax,cpui[4]
            stosd
            mov eax,ecx
            stosd
            mov eax,edx
            stosd
        .endf
        ;;
        ;; Capture vendor string
        ;;
        memset(&vendor, 0, sizeof(vendor))
        mov ecx,dword ptr cpustring[0x04]
        mov [rax],ecx
        mov ecx,dword ptr cpustring[0x0C]
        mov [rax+4],ecx
        mov ecx,dword ptr cpustring[0x08]
        mov [rax+8],ecx
        mov [rsi].vendor_,_strdup(rax)

        .if ( !strcmp(rax, "GenuineIntel") )
            mov [rsi].isIntel_,TRUE
        .elseif ( !strcmp([rsi].vendor_, "AuthenticAMD") )
            mov [rsi].isAMD_,TRUE
        .endif
        ;;
        ;; load bitset with flags for function 0x00000001
        ;;
        .if ([rsi].nIds_ >= 1)

            mov eax,dword ptr cpustring[0x10][0x8]
            mov edx,dword ptr cpustring[0x10][0xC]
            mov [rsi].f_1_ECX_,eax
            mov [rsi].f_1_EDX_,edx
        .endif
        ;;
        ;; load bitset with flags for function 0x00000007
        ;;
        .if ([rsi].nIds_ >= 7)

            mov eax,dword ptr cpustring[0x70][0x4]
            mov edx,dword ptr cpustring[0x70][0x8]
            mov [rsi].f_7_EBX_,eax
            mov [rsi].f_7_ECX_,edx
        .endif
        ;;
        ;; Calling __cpuid with 0x80000000 as the function_id argument
        ;; gets the number of the highest valid extended ID.
        ;;
        __cpuid(&cpui, 0x80000000)
        mov [rsi].nExIds_,eax
        .fors (rdi = &cpustring, ebx = 0x80000000: ebx <= [rsi].nExIds_: ++ebx)

            __cpuidex(&cpui, ebx, 0)
            stosd
            mov eax,cpui[4]
            stosd
            mov eax,ecx
            stosd
            mov eax,edx
            stosd
        .endf

        memset(&brand, 0, sizeof(brand))
        ;;
        ;; load bitset with flags for function 0x80000001
        ;;
        .if ([rsi].nExIds_ >= 0x80000001)

            mov eax,dword ptr cpustring[0x10][0x8]
            mov edx,dword ptr cpustring[0x10][0xC]
            mov [rsi].f_81_ECX_,eax
            mov [rsi].f_81_EDX_,edx
        .endif

        ;;
        ;; Interpret CPU brand string if reported
        ;;
        .if ([rsi].nExIds_ >= 0x80000004)

            memcpy(&brand, &cpustring[0x20], sizeof(cpui))
            memcpy(&brand[16], &cpustring[0x30], sizeof(cpui))
            memcpy(&brand[32], &cpustring[0x40], sizeof(cpui))
            mov [rsi].brand_,_strdup(&brand)
        .endif
        mov rax,rsi
        mov rcx,this
        .if rcx
            mov [rcx],rax
        .endif
    .endif
    ret

InstructionSet_Internal::InstructionSet_Internal endp

    assume rsi:nothing
    assume rcx:ptr InstructionSet
    assume rdx:ptr InstructionSet_Internal

InstructionSet::Release proc

    __this32()
    mov rdx,[rcx].CPU_Rep
    [rdx].Release()
    free( this )
    ret

InstructionSet::Release endp

InstructionSet::InstructionSet proc uses rsi rdi

    .if malloc( sizeof(InstructionSet) )

        mov rsi,rax
        lea rax,InstructionSet_vtable
        mov [rsi],rax

        InstructionSet_Internal::InstructionSet_Internal(&[rsi].InstructionSet.CPU_Rep)
        mov rax,rsi
        mov rdx,this
        .if rdx
            mov [rdx],rax
        .endif
    .endif
    ret

InstructionSet::InstructionSet endp

    option win64:rsp nosave noauto

InstructionSet::GetVendor proc
    __this32()
    mov rdx,[rcx].CPU_Rep
    mov rax,[rdx].vendor_
    ret
InstructionSet::GetVendor endp
InstructionSet::GetBrand proc
    __this32()
    mov rdx,[rcx].CPU_Rep
    mov rax,[rdx].brand_
    ret
InstructionSet::GetBrand endp

__declget macro method, reg, bit
InstructionSet::Get&method& proc
    __this32()
    mov rdx,[rcx].CPU_Rep
    mov eax,[rdx].reg
    and eax,1 shl bit
    ret
InstructionSet::Get&method& endp
    endm

__declge2 macro method, reg, bit, is
InstructionSet::Get&method& proc
    __this32()
    mov rdx,[rcx].CPU_Rep
    bt [rdx].is,0
    sbb eax,eax
    and eax,[rdx].reg
    and eax,1 shl bit
    ret
InstructionSet::Get&method& endp
    endm

__declget SSE3,         f_1_ECX_, 0
__declget PCLMULQDQ,    f_1_ECX_, 1
__declget MONITOR,      f_1_ECX_, 3
__declget SSSE3,        f_1_ECX_, 9
__declget FMA,          f_1_ECX_, 12
__declget CMPXCHG16B,   f_1_ECX_, 13
__declget SSE41,        f_1_ECX_, 19
__declget SSE42,        f_1_ECX_, 20
__declget MOVBE,        f_1_ECX_, 22
__declget POPCNT,       f_1_ECX_, 23
__declget AES,          f_1_ECX_, 25
__declget XSAVE,        f_1_ECX_, 26
__declget OSXSAVE,      f_1_ECX_, 27
__declget AVX,          f_1_ECX_, 28
__declget F16C,         f_1_ECX_, 29
__declget RDRAND,       f_1_ECX_, 30
__declget MSR,          f_1_EDX_, 5
__declget CX8,          f_1_EDX_, 8
__declget SEP,          f_1_EDX_, 11
__declget CMOV,         f_1_EDX_, 15
__declget CLFSH,        f_1_EDX_, 19
__declget MMX,          f_1_EDX_, 23
__declget FXSR,         f_1_EDX_, 24
__declget SSE,          f_1_EDX_, 25
__declget SSE2,         f_1_EDX_, 26
__declget FSGSBASE,     f_7_EBX_, 0
__declget BMI1,         f_7_EBX_, 3
__declge2 HLE,          f_7_EBX_, 4, isIntel_
__declget AVX2,         f_7_EBX_, 5
__declget BMI2,         f_7_EBX_, 8
__declget ERMS,         f_7_EBX_, 9
__declget INVPCID,      f_7_EBX_, 10
__declge2 RTM,          f_7_EBX_, 11, isIntel_
__declget AVX512F,      f_7_EBX_, 16
__declget RDSEED,       f_7_EBX_, 18
__declget ADX,          f_7_EBX_, 19
__declget AVX512PF,     f_7_EBX_, 26
__declget AVX512ER,     f_7_EBX_, 27
__declget AVX512CD,     f_7_EBX_, 28
__declget SHA,          f_7_EBX_, 29
__declget PREFETCHWT1,  f_7_ECX_, 0
__declget LAHF,         f_81_ECX_, 0
__declge2 LZCNT,        f_81_ECX_, 5, isIntel_
__declge2 ABM,          f_81_ECX_, 5, isAMD_
__declge2 SSE4a,        f_81_ECX_, 6, isAMD_
__declge2 XOP,          f_81_ECX_, 11, isAMD_
__declge2 TBM,          f_81_ECX_, 21, isAMD_
__declge2 SYSCALL,      f_81_EDX_, 11, isIntel_
__declge2 MMXEXT,       f_81_EDX_, 22, isAMD_
__declge2 RDTSCP,       f_81_EDX_, 27, isIntel_
__declge2 3DNOWEXT,     f_81_EDX_, 30, isAMD_
__declge2 3DNOW,        f_81_EDX_, 31, isAMD_

    assume rcx:nothing
    assume rdx:nothing
    option win64:rbp save auto

;;
;; Print out supported instruction set extensions
;;
main proc

    InstructionSet::InstructionSet(&cpu)
    support_message macro isa_feature, is_supported
        printf( "%-15s", isa_feature )
        .if is_supported
            printf( " [x]\n" )
        .else
            printf( " [ ]\n" )
        .endif
        retm<>
        endm

    printf( "%s\n", cpu.GetVendor() )
    printf( "%s\n", cpu.GetBrand() )

    support_message("3DNOW",       cpu.Get3DNOW())
    support_message("3DNOWEXT",    cpu.Get3DNOWEXT())
    support_message("ABM",         cpu.GetABM())
    support_message("ADX",         cpu.GetADX())
    support_message("AES",         cpu.GetAES())
    support_message("AVX",         cpu.GetAVX())
    support_message("AVX2",        cpu.GetAVX2())
    support_message("AVX512CD",    cpu.GetAVX512CD())
    support_message("AVX512ER",    cpu.GetAVX512ER())
    support_message("AVX512F",     cpu.GetAVX512F())
    support_message("AVX512PF",    cpu.GetAVX512PF())
    support_message("BMI1",        cpu.GetBMI1())
    support_message("BMI2",        cpu.GetBMI2())
    support_message("CLFSH",       cpu.GetCLFSH())
    support_message("CMPXCHG16B",  cpu.GetCMPXCHG16B())
    support_message("CX8",         cpu.GetCX8())
    support_message("ERMS",        cpu.GetERMS())
    support_message("F16C",        cpu.GetF16C())
    support_message("FMA",         cpu.GetFMA())
    support_message("FSGSBASE",    cpu.GetFSGSBASE())
    support_message("FXSR",        cpu.GetFXSR())
    support_message("HLE",         cpu.GetHLE())
    support_message("INVPCID",     cpu.GetINVPCID())
    support_message("LAHF",        cpu.GetLAHF())
    support_message("LZCNT",       cpu.GetLZCNT())
    support_message("MMX",         cpu.GetMMX())
    support_message("MMXEXT",      cpu.GetMMXEXT())
    support_message("MONITOR",     cpu.GetMONITOR())
    support_message("MOVBE",       cpu.GetMOVBE())
    support_message("MSR",         cpu.GetMSR())
    support_message("OSXSAVE",     cpu.GetOSXSAVE())
    support_message("PCLMULQDQ",   cpu.GetPCLMULQDQ())
    support_message("POPCNT",      cpu.GetPOPCNT())
    support_message("PREFETCHWT1", cpu.GetPREFETCHWT1())
    support_message("RDRAND",      cpu.GetRDRAND())
    support_message("RDSEED",      cpu.GetRDSEED())
    support_message("RDTSCP",      cpu.GetRDTSCP())
    support_message("RTM",         cpu.GetRTM())
    support_message("SEP",         cpu.GetSEP())
    support_message("SHA",         cpu.GetSHA())
    support_message("SSE",         cpu.GetSSE())
    support_message("SSE2",        cpu.GetSSE2())
    support_message("SSE3",        cpu.GetSSE3())
    support_message("SSE4.1",      cpu.GetSSE41())
    support_message("SSE4.2",      cpu.GetSSE42())
    support_message("SSE4a",       cpu.GetSSE4a())
    support_message("SSSE3",       cpu.GetSSSE3())
    support_message("SYSCALL",     cpu.GetSYSCALL())
    support_message("TBM",         cpu.GetTBM())
    support_message("XOP",         cpu.GetXOP())
    support_message("XSAVE",       cpu.GetXSAVE())
    cpu.Release()
    ret

main endp

    end _tstart

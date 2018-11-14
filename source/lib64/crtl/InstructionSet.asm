; INSTRUCTIONSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include malloc.inc
include intrin.inc
include InstructionSet.inc

    .code

    option proc:private
    option win64:rsp nosave noauto
    assume rcx:ptr InstructionSet

InstructionSet::GetVendor proc
    mov rax,[rcx].vendor
    ret
InstructionSet::GetVendor endp

InstructionSet::GetBrand proc
    mov rax,[rcx].brand
    ret
InstructionSet::GetBrand endp

__declget macro method, reg, bit
InstructionSet::Get&method& proc
    mov eax,[rcx].reg
    and eax,1 shl bit
    ret
InstructionSet::Get&method& endp
    endm

__declge2 macro method, reg, bit, is
InstructionSet::Get&method& proc
    bt [rcx].is,0
    sbb eax,eax
    and eax,[rcx].reg
    and eax,1 shl bit
    ret
InstructionSet::Get&method& endp
    endm

__declget SSE3,         f_1_ECX, 0
__declget PCLMULQDQ,    f_1_ECX, 1
__declget MONITOR,      f_1_ECX, 3
__declget SSSE3,        f_1_ECX, 9
__declget FMA,          f_1_ECX, 12
__declget CMPXCHG16B,   f_1_ECX, 13
__declget SSE41,        f_1_ECX, 19
__declget SSE42,        f_1_ECX, 20
__declget MOVBE,        f_1_ECX, 22
__declget POPCNT,       f_1_ECX, 23
__declget AES,          f_1_ECX, 25
__declget XSAVE,        f_1_ECX, 26
__declget OSXSAVE,      f_1_ECX, 27
__declget AVX,          f_1_ECX, 28
__declget F16C,         f_1_ECX, 29
__declget RDRAND,       f_1_ECX, 30
__declget MSR,          f_1_EDX, 5
__declget CX8,          f_1_EDX, 8
__declget SEP,          f_1_EDX, 11
__declget CMOV,         f_1_EDX, 15
__declget CLFSH,        f_1_EDX, 19
__declget MMX,          f_1_EDX, 23
__declget FXSR,         f_1_EDX, 24
__declget SSE,          f_1_EDX, 25
__declget SSE2,         f_1_EDX, 26
__declget FSGSBASE,     f_7_EBX, 0
__declget BMI1,         f_7_EBX, 3
__declge2 HLE,          f_7_EBX, 4, isIntel
__declget AVX2,         f_7_EBX, 5
__declget BMI2,         f_7_EBX, 8
__declget ERMS,         f_7_EBX, 9
__declget INVPCID,      f_7_EBX, 10
__declge2 RTM,          f_7_EBX, 11, isIntel
__declget AVX512F,      f_7_EBX, 16
__declget RDSEED,       f_7_EBX, 18
__declget ADX,          f_7_EBX, 19
__declget AVX512PF,     f_7_EBX, 26
__declget AVX512ER,     f_7_EBX, 27
__declget AVX512CD,     f_7_EBX, 28
__declget SHA,          f_7_EBX, 29
__declget PREFETCHWT1,  f_7_ECX, 0
__declget LAHF,         f_81_ECX, 0
__declge2 LZCNT,        f_81_ECX, 5, isIntel
__declge2 ABM,          f_81_ECX, 5, isAMD
__declge2 SSE4a,        f_81_ECX, 6, isAMD
__declge2 XOP,          f_81_ECX, 11, isAMD
__declge2 TBM,          f_81_ECX, 21, isAMD
__declge2 SYSCALL,      f_81_EDX, 11, isIntel
__declge2 MMXEXT,       f_81_EDX, 22, isAMD
__declge2 RDTSCP,       f_81_EDX, 27, isIntel
__declge2 3DNOWEXT,     f_81_EDX, 30, isAMD
__declge2 3DNOW,        f_81_EDX, 31, isAMD

    assume rcx:nothing
    assume rsi:ptr InstructionSet
    option win64:rbp save auto

InstructionSet::Release proc uses rsi

    mov rsi,rcx
    free([rsi].vendor)
    free([rsi].brand)
    free(rsi)
    ret

InstructionSet::Release endp

    option proc:public

InstructionSet::InstructionSet proc uses rsi rdi rbx

  local cpui[4]:SINT
  local vendor[0x20]:SBYTE
  local brand[0x40]:SBYTE
  local cpustring[512]:SBYTE

    .if malloc( sizeof(InstructionSet) + sizeof(InstructionSetVtbl) )

        mov rsi,rax
        mov rdi,rax
        xor eax,eax
        mov ecx,sizeof(InstructionSet)
        rep stosb
        mov [rsi],rdi
        lea rax,InstructionSet_Release
        stosq
        for q,<Vendor,Brand,SSE3,PCLMULQDQ,MONITOR,SSSE3,FMA,CMPXCHG16B,SSE41,SSE42,MOVBE,POPCNT,\
            AES,XSAVE,OSXSAVE,AVX,F16C,RDRAND,MSR,CX8,SEP,CMOV,CLFSH,MMX,FXSR,SSE,SSE2,FSGSBASE,BMI1,\
            HLE,AVX2,BMI2,ERMS,INVPCID,RTM,AVX512F,RDSEED,ADX,AVX512PF,AVX512ER,AVX512CD,SHA,\
            PREFETCHWT1,LAHF,LZCNT,ABM,SSE4a,XOP,TBM,SYSCALL,MMXEXT,RDTSCP,3DNOWEXT,3DNOW>
            lea rax,InstructionSet_Get&q&
            stosq
            endm

        ;;
        ;; Calling __cpuid with 0x0 as the function_id argument
        ;; gets the number of the highest valid function ID.
        ;;
        mov [rsi].nIds,__cpuid(&cpui, 0)

        .for (rdi = &cpustring, ebx = 0: ebx <= [rsi].nIds: ++ebx)

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
        lea rdi,brand
        xor eax,eax
        mov ecx,sizeof(brand) + sizeof(vendor)
        rep stosb
        lea rax,vendor
        mov ecx,dword ptr cpustring[0x04]
        mov [rax],ecx
        mov ecx,dword ptr cpustring[0x0C]
        mov [rax+4],ecx
        mov ecx,dword ptr cpustring[0x08]
        mov [rax+8],ecx
        mov [rsi].vendor,_strdup(rax)

        .if ( !strcmp(rax, "GenuineIntel") )
            mov [rsi].isIntel,TRUE
        .elseif ( !strcmp([rsi].vendor, "AuthenticAMD") )
            mov [rsi].isAMD,TRUE
        .endif
        ;;
        ;; load bitset with flags for function 0x00000001
        ;;
        .if ([rsi].nIds >= 1)

            mov eax,dword ptr cpustring[0x10][0x8]
            mov edx,dword ptr cpustring[0x10][0xC]
            mov [rsi].f_1_ECX,eax
            mov [rsi].f_1_EDX,edx
        .endif
        ;;
        ;; load bitset with flags for function 0x00000007
        ;;
        .if ([rsi].nIds >= 7)

            mov eax,dword ptr cpustring[0x70][0x4]
            mov edx,dword ptr cpustring[0x70][0x8]
            mov [rsi].f_7_EBX,eax
            mov [rsi].f_7_ECX,edx
        .endif
        ;;
        ;; Calling __cpuid with 0x80000000 as the function_id argument
        ;; gets the number of the highest valid extended ID.
        ;;
        mov [rsi].nExIds,__cpuid(&cpui, 0x80000000)

        .fors (rdi = &cpustring, ebx = 0x80000000: ebx <= [rsi].nExIds: ++ebx)

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
        ;; load bitset with flags for function 0x80000001
        ;;
        .if ([rsi].nExIds >= 0x80000001)

            mov eax,dword ptr cpustring[0x10][0x8]
            mov edx,dword ptr cpustring[0x10][0xC]
            mov [rsi].f_81_ECX,eax
            mov [rsi].f_81_EDX,edx
        .endif

        ;;
        ;; Interpret CPU brand string if reported
        ;;

        .if ([rsi].nExIds >= 0x80000004)

            mov rdx,rsi
            lea rdi,brand
            lea rsi,cpustring[0x20]
            mov ecx,(sizeof(cpui) * 3) / 8
            rep movsq
            mov rsi,rdx
            mov [rsi].brand,_strdup(&brand)
        .endif

        mov rax,rsi
        mov rcx,_this
        .if rcx
            mov [rcx],rax
        .endif
    .endif
    ret

InstructionSet::InstructionSet endp

    end

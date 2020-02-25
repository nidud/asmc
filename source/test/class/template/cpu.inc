; CPU.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __CPU_INC
__CPU_INC equ <>

include malloc.inc

MAXCPUSTRING equ 512

.template CPU

    isAMD       uint_t ?
    isIntel     uint_t ?

    f_1_ECX     uint_t ?
    f_1_EDX     uint_t ?
    f_7_EBX     uint_t ?
    f_7_ECX     uint_t ?
    f_81_ECX    uint_t ?
    f_81_EDX    uint_t ?

    .operator Release {
        exitm<free(this)>
        }
    .operator CPU {

      .new brand[64]:char_t
      .new vendor[4]:uint_t ; add to local stack

        mov rbx,st_pushregs(MAXCPUSTRING)
        .if this == NULL
            mov this,malloc(CPU)
        .endif
        mov rdi,this
        mov r10,this
        xor eax,eax
        mov ecx,CPU
        rep stosb
        mov rdi,rbx
        xor r8d,r8d
        mov vendor[0x0C],eax
        cpuid
        mov esi,eax
        mov vendor[0x00],ebx ; Capture vendor string
        mov vendor[0x04],edx
        mov vendor[0x08],ecx

        .fors ( r9 = rdi : r8d <= esi : r8d++, r9 += 16 )

            mov eax,r8d
            xor ecx,ecx
            cpuid
            mov [r9+0x00],eax
            mov [r9+0x04],ebx
            mov [r9+0x08],ecx
            mov [r9+0x0C],edx
        .endf

        assume rbx:ptr CPU
        mov rbx,r10

        lea rcx,vendor
        mov rax,"IeniuneG"
        mov rdx,"letn"
        .if ( rax == [rcx] && rdx == [rcx+8] )
            inc [rbx].isIntel
        .else
            mov rax,"itnehtuA"
            mov rdx,"DMAc"
            .if ( rax == [rcx] && rdx == [rcx+8] )
                inc [rbx].isAMD
            .endif
        .endif

        ; load bitset with flags for function 0x00000001

        .if ( esi >= 1 )

            mov [rbx].f_1_ECX,[rdi+0x10][0x8]
            mov [rbx].f_1_EDX,[rdi+0x10][0xC]
        .endif

        ; load bitset with flags for function 0x00000007

        .if ( esi >= 7 )

            mov [rbx].f_7_EBX,[rdi+0x70][0x4]
            mov [rbx].f_7_ECX,[rdi+0x70][0x8]
        .endif

        ; get the number of the highest valid extended ID.

        mov r8d,0x80000000
        mov eax,r8d
        xor ecx,ecx
        cpuid
        mov esi,eax

        .fors ( r9 = rdi: r8d <= esi: r8d++, r9 += 16 )

            mov eax,r8d
            xor ecx,ecx
            cpuid
            mov [r9+0x00],eax
            mov [r9+0x04],ebx
            mov [r9+0x08],ecx
            mov [r9+0x0C],edx
        .endf

        mov rbx,r10

        ; load bitset with flags for function 0x80000001

        .if ( esi >= 0x80000001 )

            mov [rbx].f_81_ECX,[rdi+0x10][0x8]
            mov [rbx].f_81_EDX,[rdi+0x10][0xC]
        .endif

        ; Interpret CPU brand string if reported

        .if ( esi >= 0x80000004 )

            lea rsi,[rdi+0x20]
            lea rdi,brand
            mov ecx,3*16
            rep movsb
        .endif
        st_popregs(MAXCPUSTRING)
        mov rax,rbx
        retm <rax>
        }

    .operator GetVendor {
        lea     rax,vendor
        retm    <rax>
        }
    .operator GetBrand {
        lea     rax,brand
        retm    <rax>
        }

    Operator macro name, reg, bit, condition
        .operator Get&name& {
            ifnb <condition>
                bt  [this].CPU.condition,0
                sbb eax,eax
                and eax,[this].CPU.reg
                and eax,1 shl bit
            else
                mov eax,[this].CPU.reg
                and eax,1 shl bit
            endif
            retm<eax>
            }
        endm
        Operator(SSE3,          f_1_ECX,     0)
        Operator(PCLMULQDQ,     f_1_ECX,     1)
        Operator(MONITOR,       f_1_ECX,     3)
        Operator(SSSE3,         f_1_ECX,     9)
        Operator(FMA,           f_1_ECX,    12)
        Operator(CMPXCHG16B,    f_1_ECX,    13)
        Operator(SSE41,         f_1_ECX,    19)
        Operator(SSE42,         f_1_ECX,    20)
        Operator(MOVBE,         f_1_ECX,    22)
        Operator(POPCNT,        f_1_ECX,    23)
        Operator(AES,           f_1_ECX,    25)
        Operator(XSAVE,         f_1_ECX,    26)
        Operator(OSXSAVE,       f_1_ECX,    27)
        Operator(AVX,           f_1_ECX,    28)
        Operator(F16C,          f_1_ECX,    29)
        Operator(RDRAND,        f_1_ECX,    30)
        Operator(MSR,           f_1_EDX,     5)
        Operator(CX8,           f_1_EDX,     8)
        Operator(SEP,           f_1_EDX,    11)
        Operator(CMOV,          f_1_EDX,    15)
        Operator(CLFSH,         f_1_EDX,    19)
        Operator(MMX,           f_1_EDX,    23)
        Operator(FXSR,          f_1_EDX,    24)
        Operator(SSE,           f_1_EDX,    25)
        Operator(SSE2,          f_1_EDX,    26)
        Operator(FSGSBASE,      f_7_EBX,     0)
        Operator(BMI1,          f_7_EBX,     3)
        Operator(HLE,           f_7_EBX,     4, isIntel)
        Operator(AVX2,          f_7_EBX,     5)
        Operator(BMI2,          f_7_EBX,     8)
        Operator(ERMS,          f_7_EBX,     9)
        Operator(INVPCID,       f_7_EBX,    10)
        Operator(RTM,           f_7_EBX,    11, isIntel)
        Operator(AVX512F,       f_7_EBX,    16)
        Operator(RDSEED,        f_7_EBX,    18)
        Operator(ADX,           f_7_EBX,    19)
        Operator(AVX512PF,      f_7_EBX,    26)
        Operator(AVX512ER,      f_7_EBX,    27)
        Operator(AVX512CD,      f_7_EBX,    28)
        Operator(SHA,           f_7_EBX,    29)
        Operator(PREFETCHWT1,   f_7_ECX,     0)
        Operator(LAHF,          f_81_ECX,    0)
        Operator(LZCNT,         f_81_ECX,    5, isIntel)
        Operator(ABM,           f_81_ECX,    5, isAMD)
        Operator(SSE4a,         f_81_ECX,    6, isAMD)
        Operator(XOP,           f_81_ECX,   11, isAMD)
        Operator(TBM,           f_81_ECX,   21, isAMD)
        Operator(SYSCALL,       f_81_EDX,   11, isIntel)
        Operator(MMXEXT,        f_81_EDX,   22, isAMD)
        Operator(RDTSCP,        f_81_EDX,   27, isIntel)
        Operator(3DNOWEXT,      f_81_EDX,   30, isAMD)
        Operator(3DNOW,         f_81_EDX,   31, isAMD)

    .ends

endif


include string.inc
include stdio.inc
include stdlib.inc
include sselevel.inc

    .code

main proc

    .new cpustring[80]:char_t

    .if ( sselevel & SSE_SSE2 )

        .for ( rdi = &cpustring, esi = 0 : esi < 3 : esi++, rdi+=16 )

            lea eax,[rsi+0x80000002]
            cpuid

            mov [rdi+0x00],eax
            mov [rdi+0x04],ebx
            mov [rdi+0x08],ecx
            mov [rdi+0x0C],edx
        .endf
        .for ( rax = &cpustring: byte ptr [rax] == ' ' : rax++ )
        .endf
    .else
        strcpy(&cpustring, "Unknown")
    .endif
    printf( "%s\n", rax )

    support_message macro isa_feature, flags
        .if ( sselevel & flags )
            printf( " - %s\n", isa_feature )
        .endif
        retm<>
        endm

    support_message("MMX",          SSE_MMX)
    support_message("SSE",          SSE_SSE)
    support_message("SSE2",         SSE_SSE2)
    support_message("SSE3",         SSE_SSE3)
    support_message("SSE4.1",       SSE_SSE41)
    support_message("SSE4.2",       SSE_SSE42)
    support_message("SSSE3",        SSE_SSSE3)
    support_message("AVX",          SSE_AVX)
    support_message("AVX2",         SSE_AVX2)
    support_message("AVX support by OS", SSE_AVXOS)
    support_message("XGETBV",       SSE_XGETBV)
    support_message("AVX512CD",     SSE_AVX512CD)
    support_message("AVX512ER",     SSE_AVX512ER)
    support_message("AVX512F",      SSE_AVX512F)
    support_message("AVX512PF",     SSE_AVX512PF)
    support_message("AVX512VBMI2",  SSE_AVX512VBMI2)
    support_message("AVX512PGFNI",  SSE_AVX512PGFNI)
    support_message("AVX512PVAES",  SSE_AVX512PVAES)
    support_message("AVX512PVPCLMULQDQ", SSE_AVX512PVPCLMULQDQ)
    support_message("AVX512VNNI",   SSE_AVX512VNNI)
    support_message("AVX512BITALG", SSE_AVX512BITALG)
    support_message("AVX512VPOPCNTDQ", SSE_AVX512VPOPCNTDQ)
    support_message("AVX512BF16",   SSE_AVX512BF16)
    support_message("AVX512VP2INTERSECT", SSE_AVX512VP2INTERSECT)
    support_message("AVX512DQ",     SSE_AVX512DQ)
    support_message("AVX512IFMA",   SSE_AVX512IFMA)
    support_message("AVX5124FMAPS", SSE_AVX5124FMAPS)
    support_message("AVX5124VNNIW", SSE_AVX5124VNNIW)
    support_message("AVX512VL",     SSE_AVX512VL)
    support_message("AVX512VBMI",   SSE_AVX512VBMI)
    support_message("AVX512BW",     SSE_AVX512BW)
    xor eax,eax
    ret

main endp

    end

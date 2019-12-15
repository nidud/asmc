include stdio.inc
include tchar.inc

include InstructionSet.inc

    .data
    count int_t 0

    .code

support_message proc isa_feature:string_t, is_supported:int_t

    .if is_supported

        printf( "%-16s", isa_feature )
        inc count
    .endif

    .if count == 4

        mov count,0
        printf( "\n\t" )
    .endif
    ret

support_message endp

main proc

    .new cpu:InstructionSet()

    printf(
        "\n"
        "CPU Information\n"
        "\n"
        " Vendor: %s\n", cpu.GetVendor() )
    printf(
        " Brand:  %s\n"
        "\n"
        " Supported features:\n"
        "\n\t", cpu.GetBrand() )

    support_message("MMX",         cpu.GetMMX())
    support_message("SSE",         cpu.GetSSE())
    support_message("SSE2",        cpu.GetSSE2())
    support_message("SSE3",        cpu.GetSSE3())
    support_message("SSE4.1",      cpu.GetSSE41())
    support_message("SSE4.2",      cpu.GetSSE42())
    support_message("SSE4a",       cpu.GetSSE4a())
    support_message("SSSE3",       cpu.GetSSSE3())
    support_message("AVX",         cpu.GetAVX())
    support_message("AVX2",        cpu.GetAVX2())
    support_message("AVX512CD",    cpu.GetAVX512CD())
    support_message("AVX512ER",    cpu.GetAVX512ER())
    support_message("AVX512F",     cpu.GetAVX512F())
    support_message("AVX512PF",    cpu.GetAVX512PF())
    support_message("3DNOW",       cpu.Get3DNOW())
    support_message("3DNOWEXT",    cpu.Get3DNOWEXT())
    support_message("ABM",         cpu.GetABM())
    support_message("ADX",         cpu.GetADX())
    support_message("AES",         cpu.GetAES())
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
    support_message("SYSCALL",     cpu.GetSYSCALL())
    support_message("TBM",         cpu.GetTBM())
    support_message("XOP",         cpu.GetXOP())
    support_message("XSAVE",       cpu.GetXSAVE())
    printf( "\n\n" )
    ret

main endp

    end _tstart

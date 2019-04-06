ifndef __INSTRUCTIONSET_INC
__INSTRUCTIONSET_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif

.classdef InstructionSet

    nIds            SINT ?
    nExIds          SINT ?
    vendor          LPSTR ?
    brand           LPSTR ?
    isIntel         SINT ?
    isAMD           SINT ?
    f_1_ECX         dd ?
    f_1_EDX         dd ?
    f_7_EBX         dd ?
    f_7_ECX         dd ?
    f_81_ECX        dd ?
    f_81_EDX        dd ?

    GetVendor       proc
    GetBrand        proc
    GetSSE3         proc
    GetPCLMULQDQ    proc
    GetMONITOR      proc
    GetSSSE3        proc
    GetFMA          proc
    GetCMPXCHG16B   proc
    GetSSE41        proc
    GetSSE42        proc
    GetMOVBE        proc
    GetPOPCNT       proc
    GetAES          proc
    GetXSAVE        proc
    GetOSXSAVE      proc
    GetAVX          proc
    GetF16C         proc
    GetRDRAND       proc
    GetMSR          proc
    GetCX8          proc
    GetSEP          proc
    GetCMOV         proc
    GetCLFSH        proc
    GetMMX          proc
    GetFXSR         proc
    GetSSE          proc
    GetSSE2         proc
    GetFSGSBASE     proc
    GetBMI1         proc
    GetHLE          proc
    GetAVX2         proc
    GetBMI2         proc
    GetERMS         proc
    GetINVPCID      proc
    GetRTM          proc
    GetAVX512F      proc
    GetRDSEED       proc
    GetADX          proc
    GetAVX512PF     proc
    GetAVX512ER     proc
    GetAVX512CD     proc
    GetSHA          proc
    GetPREFETCHWT1  proc
    GetLAHF         proc
    GetLZCNT        proc
    GetABM          proc
    GetSSE4a        proc
    GetXOP          proc
    GetTBM          proc
    GetSYSCALL      proc
    GetMMXEXT       proc
    GetRDTSCP       proc
    Get3DNOWEXT     proc
    Get3DNOW        proc

    .ends

endif

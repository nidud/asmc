; CPUID.ASM--
;
; https://msdn.microsoft.com/en-us/library/hskdteyh.aspx
;

include string.inc
include intrin.inc
include malloc.inc
include stdio.inc
include tchar.inc

.template InstructionSet

    nIds        int_t ?
    nExIds      int_t ?
    vendor      char_t 0x20 dup(?)
    brand       char_t 0x30 dup(?)
    isIntel     int_t ?
    isAMD       int_t ?
    f_1_ECX     uint_t ?
    f_1_EDX     uint_t ?
    f_7_EBX     uint_t ?
    f_7_ECX     uint_t ?
    f_81_ECX    uint_t ?
    f_81_EDX    uint_t ?

    .static InstructionSet {

        push    rsi
        push    rdi
        push    rbx
        sub     rsp,512
        mov     rsi,rsp
        lea     rdi,this
        mov     ecx,sizeof(this)
        xor     eax,eax
        rep     stosb

        ;;
        ;; Calling __cpuid with 0x0 as the function_id argument
        ;; gets the number of the highest valid function ID.
        ;;
        cpuid
        mov this.nIds,eax
        .for ( rdi = rsi, ebx = 0 : ebx <= this.nIds : ebx++, rdi+=16 )

            __cpuidex(rdi, ebx, 0)
        .endf
        ;;
        ;; Capture vendor string
        ;;
        lea rdi,this.vendor
        mov eax,[rsi+0x04]
        stosd
        mov eax,[rsi+0x0C]
        stosd
        mov eax,[rsi+0x08]
        stosd
        ;;
        ;; load bitset with flags for function 0x00000001
        ;;
        .if ( this.nIds >= 1 )

            mov this.f_1_ECX,[rsi+0x10][0x8]
            mov this.f_1_EDX,[rsi+0x10][0xC]
        .endif
        ;;
        ;; load bitset with flags for function 0x00000007
        ;;
        .if ( this.nIds >= 7 )

            mov this.f_7_EBX,[rsi+0x70][0x4]
            mov this.f_7_ECX,[rsi+0x70][0x8]
        .endif
        ;;
        ;; Calling __cpuid with 0x80000000 as the function_id argument
        ;; gets the number of the highest valid extended ID.
        ;;
        xor ecx,ecx
        mov eax,0x80000000
        cpuid
        mov this.nExIds,eax
        .for ( rdi = rsi, ebx = 0x80000000 : ebx <= this.nExIds : ebx++, rdi+=16 )

            __cpuidex(rdi, ebx, 0)
        .endf

        ;;
        ;; load bitset with flags for function 0x80000001
        ;;
        .if ( this.nExIds >= 0x80000001 )

            mov this.f_81_ECX,[rsi+0x10][0x8]
            mov this.f_81_EDX,[rsi+0x10][0xC]
        .endif

        ;;
        ;; Interpret CPU brand string if reported
        ;;
        .if ( this.nExIds >= 0x80000004 )

            lea rdi,this.brand
            add rsi,0x20
            mov ecx,3*16
            rep movsb
        .endif

        add rsp,512
        pop rbx
        pop rdi
        pop rsi

        mov this.isIntel,FALSE
        mov this.isAMD,FALSE
        .if ( !strcmp(addr this.vendor, "GenuineIntel") )
            mov this.isIntel,TRUE
        .elseif ( !strcmp(addr this.vendor, "AuthenticAMD") )
            mov this.isAMD,TRUE
        .endif
        }


    .static GetVendor {
        lea rax,this.vendor
        }
    .static GetBrand {
        lea rax,this.brand
        }

    .static GetSSE3 {
        bt  this.f_1_ECX,0
        sbb eax,eax
        and eax,1
        }
    .static GetPCLMULQDQ {
        bt  this.f_1_ECX,1
        sbb eax,eax
        and eax,1
        }
    .static GetMONITOR {
        bt  this.f_1_ECX,3
        sbb eax,eax
        and eax,1
        }
    .static GetSSSE3 {
        bt  this.f_1_ECX,9
        sbb eax,eax
        and eax,1
        }
    .static GetFMA {
        bt  this.f_1_ECX,12
        sbb eax,eax
        and eax,1
        }
    .static GetCMPXCHG16B {
        bt  this.f_1_ECX,13
        sbb eax,eax
        and eax,1
        }
    .static GetSSE41 {
        bt  this.f_1_ECX,19
        sbb eax,eax
        and eax,1
        }
    .static GetSSE42 {
        bt  this.f_1_ECX,20
        sbb eax,eax
        and eax,1
        }
    .static GetMOVBE {
        bt  this.f_1_ECX,22
        sbb eax,eax
        and eax,1
        }
    .static GetPOPCNT {
        bt  this.f_1_ECX,23
        sbb eax,eax
        and eax,1
        }
    .static GetAES {
        bt  this.f_1_ECX,25
        sbb eax,eax
        and eax,1
        }
    .static GetXSAVE {
        bt  this.f_1_ECX,26
        sbb eax,eax
        and eax,1
        }
    .static GetOSXSAVE {
        bt  this.f_1_ECX,27
        sbb eax,eax
        and eax,1
        }
    .static GetAVX {
        bt  this.f_1_ECX,28
        sbb eax,eax
        and eax,1
        }
    .static GetF16C {
        bt  this.f_1_ECX,29
        sbb eax,eax
        and eax,1
        }
    .static GetRDRAND {
        bt  this.f_1_ECX,30
        sbb eax,eax
        and eax,1
        }

    .static GetMSR {
        bt  this.f_1_EDX,5
        sbb eax,eax
        and eax,1
        }
    .static GetCX8 {
        bt  this.f_1_EDX,8
        sbb eax,eax
        and eax,1
        }
    .static GetSEP {
        bt  this.f_1_EDX,11
        sbb eax,eax
        and eax,1
        }
    .static GetCMOV {
        bt  this.f_1_EDX,15
        sbb eax,eax
        and eax,1
        }
    .static GetCLFSH {
        bt  this.f_1_EDX,19
        sbb eax,eax
        and eax,1
        }
    .static GetMMX {
        bt  this.f_1_EDX,23
        sbb eax,eax
        and eax,1
        }
    .static GetFXSR {
        bt  this.f_1_EDX,24
        sbb eax,eax
        and eax,1
        }
    .static GetSSE {
        bt  this.f_1_EDX,25
        sbb eax,eax
        and eax,1
        }
    .static GetSSE2 {
        bt  this.f_1_EDX,26
        sbb eax,eax
        and eax,1
        }

    .static GetFSGSBASE {
        bt  this.f_7_EBX,0
        sbb eax,eax
        and eax,1
        }
    .static GetBMI1 {
        bt  this.f_7_EBX,3
        sbb eax,eax
        and eax,1
        }
    .static GetHLE {
        bt  this.isIntel,0
        sbb eax,eax
        and eax,this.f_7_EBX
        bt  eax,4
        sbb eax,eax
        and eax,1
        }
    .static GetAVX2 {
        bt  this.f_7_EBX,5
        sbb eax,eax
        and eax,1
        }
    .static GetBMI2 {
        bt  this.f_7_EBX,8
        sbb eax,eax
        and eax,1
        }
    .static GetERMS {
        bt  this.f_7_EBX,9
        sbb eax,eax
        and eax,1
        }
    .static GetINVPCID {
        bt  this.f_7_EBX,10
        sbb eax,eax
        and eax,1
        }
    .static GetRTM {
        bt  this.isIntel,0
        sbb eax,eax
        and eax,this.f_7_EBX
        bt  eax,11
        sbb eax,eax
        and eax,1
        }
    .static GetAVX512F {
        bt  this.f_7_EBX,16
        sbb eax,eax
        and eax,1
        }
    .static GetRDSEED {
        bt  this.f_7_EBX,18
        sbb eax,eax
        and eax,1
        }
    .static GetADX {
        bt  this.f_7_EBX,19
        sbb eax,eax
        and eax,1
        }
    .static GetAVX512PF {
        bt  this.f_7_EBX,26
        sbb eax,eax
        and eax,1
        }
    .static GetAVX512ER {
        bt  this.f_7_EBX,27
        sbb eax,eax
        and eax,1
        }
    .static GetAVX512CD {
        bt  this.f_7_EBX,28
        sbb eax,eax
        and eax,1
        }
    .static GetSHA {
        bt  this.f_7_EBX,29
        sbb eax,eax
        and eax,1
        }

    .static GetPREFETCHWT1 {
        bt  this.f_7_ECX,0
        sbb eax,eax
        and eax,1
        }

    .static GetLAHF {
        bt  this.f_81_ECX,0
        sbb eax,eax
        and eax,1
        }
    .static GetLZCNT {
        bt  this.isIntel,0
        sbb eax,eax
        and eax,this.f_81_ECX
        bt  eax,5
        sbb eax,eax
        and eax,1
        }
    .static GetABM {
        bt  this.isAMD,0
        sbb eax,eax
        and eax,this.f_81_ECX
        bt  eax,5
        sbb eax,eax
        and eax,1
        }
    .static GetSSE4a {
        bt  this.isAMD,0
        sbb eax,eax
        and eax,this.f_81_ECX
        bt  eax,6
        sbb eax,eax
        and eax,1
        }
    .static GetXOP {
        bt  this.isAMD,0
        sbb eax,eax
        and eax,this.f_81_ECX
        bt  eax,11
        sbb eax,eax
        and eax,1
        }
    .static GetTBM {
        bt  this.isAMD,0
        sbb eax,eax
        and eax,this.f_81_ECX
        bt  eax,21
        sbb eax,eax
        and eax,1
        }

    .static GetSYSCALL {
        bt  this.isIntel,0
        sbb eax,eax
        and eax,this.f_81_EDX
        bt  eax,11
        sbb eax,eax
        and eax,1
        }
    .static GetMMXEXT {
        bt  this.isAMD,0
        sbb eax,eax
        and eax,this.f_81_EDX
        bt  eax,22
        sbb eax,eax
        and eax,1
        }
    .static GetRDTSCP {
        bt  this.isIntel,0
        sbb eax,eax
        and eax,this.f_81_EDX
        bt  eax,27
        sbb eax,eax
        and eax,1
        }
    .static Get3DNOWEXT {
        bt  this.isAMD,0
        sbb eax,eax
        and eax,this.f_81_EDX
        bt  eax,30
        sbb eax,eax
        and eax,1
        }
    .static Get3DNOW {
        bt  this.isAMD,0
        sbb eax,eax
        and eax,this.f_81_EDX
        bt  eax,31
        sbb eax,eax
        and eax,1
        }
    .ends

.code

;;
;; Print out supported instruction set extensions
;;
main proc

   .new cpu:InstructionSet()
   .new sup[2]:char_t = { ' ', 'x' }

    printf( "%s\n", cpu.GetVendor() )
    printf( "%s\n", cpu.GetBrand() )

    printf( "[%c] 3DNOW\t",     sup[ cpu.Get3DNOW() ] )
    printf( "[%c] 3DNOWEXT\t",  sup[ cpu.Get3DNOWEXT() ] )
    printf( "[%c] ABM\n",       sup[ cpu.GetABM() ] )
    printf( "[%c] ADX\t\t",     sup[ cpu.GetADX() ] )
    printf( "[%c] AES\t\t",     sup[ cpu.GetAES() ] )
    printf( "[%c] AVX\n",       sup[ cpu.GetAVX() ] )
    printf( "[%c] AVX2\t",      sup[ cpu.GetAVX2() ] )
    printf( "[%c] AVX512CD\t",  sup[ cpu.GetAVX512CD() ] )
    printf( "[%c] AVX512ER\n",  sup[ cpu.GetAVX512ER() ] )
    printf( "[%c] AVX512F\t",   sup[ cpu.GetAVX512F() ] )
    printf( "[%c] AVX512PF\t",  sup[ cpu.GetAVX512PF() ] )
    printf( "[%c] BMI1\n",      sup[ cpu.GetBMI1() ] )
    printf( "[%c] BMI2\t",      sup[ cpu.GetBMI2() ] )
    printf( "[%c] CLFSH\t",     sup[ cpu.GetCLFSH() ] )
    printf( "[%c] CMPXCHG16B\n",sup[ cpu.GetCMPXCHG16B() ] )
    printf( "[%c] CX8\t\t",     sup[ cpu.GetCX8() ] )
    printf( "[%c] ERMS\t",      sup[ cpu.GetERMS() ] )
    printf( "[%c] F16C\n",      sup[ cpu.GetF16C() ] )
    printf( "[%c] FMA\t\t",     sup[ cpu.GetFMA() ] )
    printf( "[%c] FSGSBASE\t",  sup[ cpu.GetFSGSBASE() ] )
    printf( "[%c] FXSR\n",      sup[ cpu.GetFXSR() ] )
    printf( "[%c] HLE\t\t",     sup[ cpu.GetHLE() ] )
    printf( "[%c] INVPCID\t",   sup[ cpu.GetINVPCID() ] )
    printf( "[%c] LAHF\n",      sup[ cpu.GetLAHF() ] )
    printf( "[%c] LZCNT\t",     sup[ cpu.GetLZCNT() ] )
    printf( "[%c] MMX\t\t",     sup[ cpu.GetMMX() ] )
    printf( "[%c] MMXEXT\n",    sup[ cpu.GetMMXEXT() ] )
    printf( "[%c] MONITOR\t",   sup[ cpu.GetMONITOR() ] )
    printf( "[%c] MOVBE\t",     sup[ cpu.GetMOVBE() ] )
    printf( "[%c] MSR\n",       sup[ cpu.GetMSR() ] )
    printf( "[%c] OSXSAVE\t",   sup[ cpu.GetOSXSAVE() ] )
    printf( "[%c] PCLMULQDQ\t", sup[ cpu.GetPCLMULQDQ() ] )
    printf( "[%c] POPCNT\n",    sup[ cpu.GetPOPCNT() ] )
    printf( "[%c] PREFETCHWT1\t", sup[ cpu.GetPREFETCHWT1() ] )
    printf( "[%c] RDRAND\t",    sup[ cpu.GetRDRAND() ] )
    printf( "[%c] RDSEED\n",    sup[ cpu.GetRDSEED() ] )
    printf( "[%c] RDTSCP\t",    sup[ cpu.GetRDTSCP() ] )
    printf( "[%c] RTM\t\t",     sup[ cpu.GetRTM() ] )
    printf( "[%c] SEP\n",       sup[ cpu.GetSEP() ] )
    printf( "[%c] SHA\t\t",     sup[ cpu.GetSHA() ] )
    printf( "[%c] SSE\t\t",     sup[ cpu.GetSSE() ] )
    printf( "[%c] SSE2\n",      sup[ cpu.GetSSE2() ] )
    printf( "[%c] SSE3\t",      sup[ cpu.GetSSE3() ] )
    printf( "[%c] SSE4.1\t",    sup[ cpu.GetSSE41() ] )
    printf( "[%c] SSE4.2\n",    sup[ cpu.GetSSE42() ] )
    printf( "[%c] SSE4a\t",     sup[ cpu.GetSSE4a() ] )
    printf( "[%c] SSSE3\t",     sup[ cpu.GetSSSE3() ] )
    printf( "[%c] SYSCALL\n",   sup[ cpu.GetSYSCALL() ] )
    printf( "[%c] TBM\t\t",     sup[ cpu.GetTBM() ] )
    printf( "[%c] XOP\t\t",     sup[ cpu.GetXOP() ] )
    printf( "[%c] XSAVE\n",     sup[ cpu.GetXSAVE() ] )
    xor eax,eax
    ret

main endp

    end _tstart

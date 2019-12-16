; INSTRUCTIONSET.INC--
;
; Inline class methods
;
include intrin.inc

MAXCPUSTRING    equ 512

.class InstructionSet_Internal

    nIds        int_t ?
    nExIds      int_t ?
    isIntel     int_t ?
    isAMD       int_t ?
    union
     struct
      f_1_ECX   uint_t ?
      f_1_EDX   uint_t ?
     ends
     f_1_RAX    uint64_t ?
    ends
    union
     struct
      f_7_EBX   uint_t ?
      f_7_ECX   uint_t ?
     ends
     f_7_RAX    uint64_t ?
    ends
    union
     struct
      f_81_ECX  uint_t ?
      f_81_EDX  uint_t ?
     ends
     f_81_RAX   uint64_t ?
    ends

    .ends


.class InstructionSet : public InstructionSet_Internal

    GetVendor      proc ; getters
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

undef InstructionSet_InstructionSet ; flip the PROTO to a MACRO

InstructionSet_InstructionSet macro this ; .NEW cpu : InstructionSet()

  .new vendor[16]:char_t ; add to local stack
  .new brand[64]:char_t

    ifidn @SubStr(this,1,1),<&>
        lea rax,@SubStr(this,2)
    else
        mov rax,this
    endif
    lea     rdx,vendor

    ; new stack frame

    push    rsi
    push    rdi
    push    rbx
    push    rbp
    mov     rbp,rsp
    sub     rsp,MAXCPUSTRING+16+8
    mov     [rbp-24],rdx
    mov     rsi,rax
    assume  rsi: ptr InstructionSet

    ; get the number of the highest valid function ID.

    mov rdi,rsp
    xor r8d,r8d
    xor eax,eax
    xor ecx,ecx
    cpuid
    mov [rsi].nIds,eax

    .fors ( r9 = rdi: r8d <= [rsi].nIds: r8d++, r9 += 16 )

        mov eax,r8d
        xor ecx,ecx
        cpuid
        mov [r9+0x00],eax
        mov [r9+0x04],ebx
        mov [r9+0x08],ecx
        mov [r9+0x0C],edx
    .endf

    ; Capture vendor string

    mov rdx,[rbp-24]
    mov dword ptr [rdx+0x00],[rdi+0x04]
    mov dword ptr [rdx+0x04],[rdi+0x0C]
    mov dword ptr [rdx+0x08],[rdi+0x08]
    mov dword ptr [rdx+0x0C],0
    mov rax,[rdx]
    mov rdx,[rdx+8]
    mov rcx,"IeniuneG"
    mov rbx,"letn"
    .if ( rax == rcx && rdx == rbx )

        mov [rsi].isIntel,TRUE
    .else
        mov rcx,"itnehtuA"
        mov rbx,"DMAc"
        .if ( rax == rcx && rdx == rbx )

            mov [rsi].isAMD,TRUE
        .endif
    .endif

    ; load bitset with flags for function 0x00000001

    .if ( [rsi].nIds >= 1 )

        mov [rsi].f_1_RAX,[rdi+0x10][0x8]
    .endif

    ; load bitset with flags for function 0x00000007

    .if ( [rsi].nIds >= 7 )

        mov [rsi].f_7_RAX,[rdi+0x70][0x4]
    .endif

    ; get the number of the highest valid extended ID.

    mov r8d,0x80000000
    mov eax,r8d
    xor ecx,ecx
    cpuid
    mov [rsi].nExIds,eax

    .fors ( r9 = rdi: r8d <= [rsi].nExIds: r8d++, r9 += 16 )

        mov eax,r8d
        xor ecx,ecx
        cpuid
        mov [r9+0x00],eax
        mov [r9+0x04],ebx
        mov [r9+0x08],ecx
        mov [r9+0x0C],edx
    .endf

    ; load bitset with flags for function 0x80000001

    .if ( [rsi].nExIds >= 0x80000001 )

        mov [rsi].f_81_RAX,[rdi+0x10][0x8]
    .endif

    ; Interpret CPU brand string if reported

    .if ( [rsi].nExIds >= 0x80000004 )

        lea rsi,[rdi+0x20]
        mov rdi,[rbp-24]
        sub rdi,64
        mov ecx,3*16
        rep movsb
    .endif

    assume rsi: nothing

    leave
    pop rbx
    pop rdi
    pop rsi

    exitm<>
    endm

InstructionSet_GetVendor macro this
    lea rax,vendor
    exitm<>
    endm

InstructionSet_GetBrand macro this
    lea rax,brand
    exitm<>
    endm


InstructionSetInline macro name, reg, bit, condition
 InstructionSet_Get&name& macro this
 ifnb <condition>
     bt  [this].InstructionSet.condition,0
     sbb eax,eax
     and eax,[this].InstructionSet.reg
     and eax,1 shl bit
 else
     mov eax,[this].InstructionSet.reg
     and eax,1 shl bit
 endif
     exitm<>
     endm
    endm

InstructionSetInline SSE3,          f_1_ECX,     0
InstructionSetInline PCLMULQDQ,     f_1_ECX,     1
InstructionSetInline MONITOR,       f_1_ECX,     3
InstructionSetInline SSSE3,         f_1_ECX,     9
InstructionSetInline FMA,           f_1_ECX,    12
InstructionSetInline CMPXCHG16B,    f_1_ECX,    13
InstructionSetInline SSE41,         f_1_ECX,    19
InstructionSetInline SSE42,         f_1_ECX,    20
InstructionSetInline MOVBE,         f_1_ECX,    22
InstructionSetInline POPCNT,        f_1_ECX,    23
InstructionSetInline AES,           f_1_ECX,    25
InstructionSetInline XSAVE,         f_1_ECX,    26
InstructionSetInline OSXSAVE,       f_1_ECX,    27
InstructionSetInline AVX,           f_1_ECX,    28
InstructionSetInline F16C,          f_1_ECX,    29
InstructionSetInline RDRAND,        f_1_ECX,    30
InstructionSetInline MSR,           f_1_EDX,     5
InstructionSetInline CX8,           f_1_EDX,     8
InstructionSetInline SEP,           f_1_EDX,    11
InstructionSetInline CMOV,          f_1_EDX,    15
InstructionSetInline CLFSH,         f_1_EDX,    19
InstructionSetInline MMX,           f_1_EDX,    23
InstructionSetInline FXSR,          f_1_EDX,    24
InstructionSetInline SSE,           f_1_EDX,    25
InstructionSetInline SSE2,          f_1_EDX,    26
InstructionSetInline FSGSBASE,      f_7_EBX,     0
InstructionSetInline BMI1,          f_7_EBX,     3
InstructionSetInline HLE,           f_7_EBX,     4, isIntel
InstructionSetInline AVX2,          f_7_EBX,     5
InstructionSetInline BMI2,          f_7_EBX,     8
InstructionSetInline ERMS,          f_7_EBX,     9
InstructionSetInline INVPCID,       f_7_EBX,    10
InstructionSetInline RTM,           f_7_EBX,    11, isIntel
InstructionSetInline AVX512F,       f_7_EBX,    16
InstructionSetInline RDSEED,        f_7_EBX,    18
InstructionSetInline ADX,           f_7_EBX,    19
InstructionSetInline AVX512PF,      f_7_EBX,    26
InstructionSetInline AVX512ER,      f_7_EBX,    27
InstructionSetInline AVX512CD,      f_7_EBX,    28
InstructionSetInline SHA,           f_7_EBX,    29
InstructionSetInline PREFETCHWT1,   f_7_ECX,     0
InstructionSetInline LAHF,          f_81_ECX,    0
InstructionSetInline LZCNT,         f_81_ECX,    5, isIntel
InstructionSetInline ABM,           f_81_ECX,    5, isAMD
InstructionSetInline SSE4a,         f_81_ECX,    6, isAMD
InstructionSetInline XOP,           f_81_ECX,   11, isAMD
InstructionSetInline TBM,           f_81_ECX,   21, isAMD
InstructionSetInline SYSCALL,       f_81_EDX,   11, isIntel
InstructionSetInline MMXEXT,        f_81_EDX,   22, isAMD
InstructionSetInline RDTSCP,        f_81_EDX,   27, isIntel
InstructionSetInline 3DNOWEXT,      f_81_EDX,   30, isAMD
InstructionSetInline 3DNOW,         f_81_EDX,   31, isAMD


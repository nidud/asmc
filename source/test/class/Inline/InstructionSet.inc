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
    f_1_ECX     uint_t ?
    f_1_EDX     uint_t ?
    f_7_EBX     uint_t ?
    f_7_ECX     uint_t ?
    f_81_ECX    uint_t ?
    f_81_EDX    uint_t ?

    .ends


.class InstructionSet : public InstructionSet_Internal

    ; getters

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

undef InstructionSet_InstructionSet

InstructionSet_InstructionSet macro this

  .new vendor[16]:char_t
  .new brand[64]:char_t

    ifidn @SubStr(this,1,1),<&>
        lea rax,@SubStr(this,2)
    else
        mov rax,this
    endif
    lea     rdx,vendor
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

    mov [rsi].nIds,__cpuid(&[rbp-16], 0)

    .for (rdi = rsp, ebx = 0: ebx <= [rsi].nIds: ++ebx)

        __cpuidex(&[rbp-16], ebx, 0)
        stosd
        mov eax,[rbp-12]
        stosd
        mov eax,ecx
        stosd
        mov eax,edx
        stosd
    .endf
    mov rdi,rsp

    ; Capture vendor string

    mov rax,[rbp-24]
    mov ecx,[rdi+0x04]
    mov [rax],ecx
    mov ecx,[rdi+0x0C]
    mov [rax+4],ecx
    mov ecx,[rdi+0x08]
    mov [rax+8],ecx
    xor ecx,ecx
    mov [rax+12],ecx

    mov rdx,[rax+8]
    mov rax,[rax]
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

        mov eax,[rdi+0x10][0x8]
        mov edx,[rdi+0x10][0xC]
        mov [rsi].f_1_ECX,eax
        mov [rsi].f_1_EDX,edx
    .endif

    ; load bitset with flags for function 0x00000007

    .if ( [rsi].nIds >= 7 )

        mov eax,[rdi+0x70][0x4]
        mov edx,[rdi+0x70][0x8]
        mov [rsi].f_7_EBX,eax
        mov [rsi].f_7_ECX,edx
    .endif

    ; get the number of the highest valid extended ID.

    __cpuid(&[rbp-16], 0x80000000)
    mov [rsi].nExIds,eax

    .fors ( ebx = 0x80000000: ebx <= [rsi].nExIds: ++ebx )

        __cpuidex(&[rbp-16], ebx, 0)
        stosd
        mov eax,[rbp-12]
        stosd
        mov eax,ecx
        stosd
        mov eax,edx
        stosd
    .endf
    mov rdi,rsp

    ; load bitset with flags for function 0x80000001

    .if ( [rsi].nExIds >= 0x80000001 )

        mov eax,[rdi+0x10][0x8]
        mov edx,[rdi+0x10][0xC]
        mov [rsi].f_81_ECX,eax
        mov [rsi].f_81_EDX,edx
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


InstructionSet_GetSSE3 macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 0
    exitm<>
    endm

InstructionSet_GetPCLMULQDQ macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 1
    exitm<>
    endm

InstructionSet_GetMONITOR macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 3
    exitm<>
    endm

InstructionSet_GetSSSE3 macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 9
    exitm<>
    endm

InstructionSet_GetFMA macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 12
    exitm<>
    endm

InstructionSet_GetCMPXCHG16B macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 13
    exitm<>
    endm

InstructionSet_GetSSE41 macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 19
    exitm<>
    endm

InstructionSet_GetSSE42 macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 20
    exitm<>
    endm

InstructionSet_GetMOVBE macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 22
    exitm<>
    endm

InstructionSet_GetPOPCNT macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 23
    exitm<>
    endm

InstructionSet_GetAES macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 25
    exitm<>
    endm

InstructionSet_GetXSAVE macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 26
    exitm<>
    endm

InstructionSet_GetOSXSAVE macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 27
    exitm<>
    endm

InstructionSet_GetAVX macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 28
    exitm<>
    endm

InstructionSet_GetF16C macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 29
    exitm<>
    endm

InstructionSet_GetRDRAND macro this
    mov eax,[this].InstructionSet.f_1_ECX
    and eax,1 shl 30
    exitm<>
    endm


InstructionSet_GetMSR macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 5
    exitm<>
    endm

InstructionSet_GetCX8 macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 8
    exitm<>
    endm

InstructionSet_GetSEP macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 11
    exitm<>
    endm

InstructionSet_GetCMOV macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 15
    exitm<>
    endm

InstructionSet_GetCLFSH macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 19
    exitm<>
    endm

InstructionSet_GetMMX macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 23
    exitm<>
    endm

InstructionSet_GetFXSR macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 24
    exitm<>
    endm

InstructionSet_GetSSE macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 25
    exitm<>
    endm

InstructionSet_GetSSE2 macro this
    mov eax,[this].InstructionSet.f_1_EDX
    and eax,1 shl 26
    exitm<>
    endm


InstructionSet_GetFSGSBASE macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 0
    exitm<>
    endm

InstructionSet_GetBMI1 macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 3
    exitm<>
    endm

InstructionSet_GetHLE macro this
    bt  [this].InstructionSet.isIntel,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 4
    exitm<>
    endm

InstructionSet_GetAVX2 macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 5
    exitm<>
    endm

InstructionSet_GetBMI2 macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 8
    exitm<>
    endm

InstructionSet_GetERMS macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 9
    exitm<>
    endm

InstructionSet_GetINVPCID macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 10
    exitm<>
    endm

InstructionSet_GetRTM macro this
    bt  [this].InstructionSet.isIntel,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 11
    exitm<>
    endm

InstructionSet_GetAVX512F macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 16
    exitm<>
    endm

InstructionSet_GetRDSEED macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 18
    exitm<>
    endm

InstructionSet_GetADX macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 19
    exitm<>
    endm

InstructionSet_GetAVX512PF macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 26
    exitm<>
    endm

InstructionSet_GetAVX512ER macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 27
    exitm<>
    endm

InstructionSet_GetAVX512CD macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 28
    exitm<>
    endm

InstructionSet_GetSHA macro this
    mov eax,[this].InstructionSet.f_7_EBX
    and eax,1 shl 19
    exitm<>
    endm


InstructionSet_GetPREFETCHWT1 macro this
    mov eax,[this].InstructionSet.f_7_ECX
    and eax,1 shl 0
    exitm<>
    endm


InstructionSet_GetLAHF macro this
    mov eax,[this].InstructionSet.f_81_ECX
    and eax,1 shl 0
    exitm<>
    endm

InstructionSet_GetLZCNT macro this
    bt  [this].InstructionSet.isIntel,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_ECX
    and eax,1 shl 5
    exitm<>
    endm

InstructionSet_GetABM macro this
    bt  [this].InstructionSet.isAMD,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_ECX
    and eax,1 shl 5
    exitm<>
    endm

InstructionSet_GetSSE4a macro this
    bt  [this].InstructionSet.isAMD,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_ECX
    and eax,1 shl 6
    exitm<>
    endm

InstructionSet_GetXOP macro this
    bt  [this].InstructionSet.isAMD,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_ECX
    and eax,1 shl 11
    exitm<>
    endm

InstructionSet_GetTBM macro this
    bt  [this].InstructionSet.isAMD,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_ECX
    and eax,1 shl 21
    exitm<>
    endm


InstructionSet_GetSYSCALL macro this
    bt  [this].InstructionSet.isIntel,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_EDX
    and eax,1 shl 11
    exitm<>
    endm

InstructionSet_GetMMXEXT macro this
    bt  [this].InstructionSet.isAMD,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_EDX
    and eax,1 shl 22
    exitm<>
    endm

InstructionSet_GetRDTSCP macro this
    bt  [this].InstructionSet.isIntel,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_EDX
    and eax,1 shl 27
    exitm<>
    endm

InstructionSet_Get3DNOWEXT macro this
    bt  [this].InstructionSet.isAMD,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_EDX
    and eax,1 shl 30
    exitm<>
    endm

InstructionSet_Get3DNOW macro this
    bt  [this].InstructionSet.isAMD,0
    sbb eax,eax
    and eax,[this].InstructionSet.f_81_EDX
    and eax,1 shl 31
    exitm<>
    endm

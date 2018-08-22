ifndef __INTRIN_H_
__INTRIN_H_ equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif

include intrin0.inc
include vcruntime.inc
if (defined(_M_IX86) OR defined(_M_X64)) AND NOT defined(_CHPE_ONLY_)
include immintrin.inc
include ammintrin.inc
endif
if defined (_M_IX86) AND NOT defined(_CHPE_ONLY_)
include mm3dnow.inc
endif

;
; Note: This assumes a standard stack frame.
;
_AddressOfReturnAddress macro
    lea rax,[rbp+size_t]
    retm<rax>
    endm

_ReturnAddress macro
    mov rax,[rbp+size_t]
    retm<rax>
    endm

__nop macro
    nop
    retm<>
    endm

__debugbreak macro
    int 3
    retm<>
    endm

_mm_loadreg macro reg, arg
    ifidn @SubStr(arg,1,1),<&>
        lea reg,@SubStr(arg,2)
    elseifdif <arg>,<reg>
        mov reg,arg
    endif
    retm<reg>
    endm

_mm_storereg macro lp, reg, tmp:=<rcx>
    ifidn @SubStr(lp,1,1),<&>
        mov @SubStr(lp,2),reg
    elseif (opattr lp) eq 48
        mov [lp],reg
    else
        mov tmp,lp
        mov [tmp],reg
    endif
    retm<>
    endm

_BitScanForward macro lpIndex, dwMask
    bsf eax,_mm_loadreg(eax, dwMask)
    _mm_storereg(lpIndex, eax)
    retm<al>
    endm

_BitScanReverse macro lpIndex, dwMask
    bsr eax,_mm_loadreg(eax, dwMask)
    _mm_storereg(lpIndex, eax)
    retm<al>
    endm

ifdef __MACHINEX64
_BitScanForward64 macro lpIndex, dwMask
    bsf rax,_mm_loadreg(rax, dwMask)
    _mm_storereg(lpIndex, eax)
    retm<al>
    endm
_BitScanReverse64 macro lpIndex, dwMask
    bsr rax,_mm_loadreg(rax, dwMask)
    _mm_storereg(lpIndex, eax)
    retm<al>
    endm
endif

_InterlockedCompareExchange macro Destination, Exchange, Comparand
    _mm_loadreg(rcx, Destination)
    _mm_loadreg(edx, Exchange)
    _mm_loadreg(eax, Comparand)
    push [rcx]
    lock cmpxchg dword ptr [rcx],edx
    pop rax
    retm<eax>
    endm

_InterlockedCompareExchange8 macro Destination, Exchange, Comparand
    _mm_loadreg(rcx, Destination)
    _mm_loadreg(dl, Exchange)
    _mm_loadreg(al, Comparand)
    push [rcx]
    lock cmpxchg byte ptr [rcx],dl
    pop rax
    retm<al>
    endm

_InterlockedCompareExchange16 macro Destination, Exchange, Comparand
    _mm_loadreg(rcx, Destination)
    _mm_loadreg(dx, Exchange)
    _mm_loadreg(ax, Comparand)
    push [rcx]
    lock cmpxchg word ptr [rcx],dl
    pop rax
    retm<ax>
    endm

_InterlockedCompareExchange64 macro Destination, Exchange, Comparand
    _mm_loadreg(rcx, Destination)
    _mm_loadreg(rdx, Exchange)
    _mm_loadreg(rax, Comparand)
    push [rcx]
    lock cmpxchg size_t ptr [rcx],rdx
    pop rax
    retm<rax>
    endm

_InterlockedCompareExchangePointer equ <_InterlockedCompareExchange64>

_InterlockedDecrement16 macro lpAddend
    _mm_loadreg(rcx, lpAddend)
    lock dec word ptr [rcx]
    mov ax,[rcx]
    retm<ax>
    endm

_InterlockedDecrement macro lpAddend
    _mm_loadreg(rcx, lpAddend)
    lock dec dword ptr [rcx]
    mov eax,[rcx]
    retm<eax>
    endm

ifdef __MACHINEX64
_InterlockedDecrement64 macro lpAddend
    _mm_loadreg(rcx, lpAddend)
    lock dec qword ptr [rcx]
    mov rax,[rcx]
    retm<rax>
    endm
endif

_InterlockedIncrement16 macro lpAddend
    _mm_loadreg(rcx, lpAddend)
    lock inc word ptr [rcx]
    mov ax,[rcx]
    retm<ax>
    endm

_InterlockedIncrement macro lpAddend
    _mm_loadreg(rcx, lpAddend)
    lock inc dword ptr [rcx]
    mov eax,[rcx]
    retm<eax>
    endm

ifdef __MACHINEX64
_InterlockedIncrement64 macro lpAddend
    _mm_loadreg(rcx, lpAddend)
    lock inc qword ptr [rcx]
    mov rax,[rcx]
    retm<rax>
    endm
endif

_InterlockedExchangePointer macro Target, Value
    _mm_loadreg(rcx, Target)
    _mm_loadreg(rdx, Value)
    mov rax,[rcx]
    xchg [rcx],rdx
    retm<rax>
    endm

__fastfail macro code
    mov ecx,code
    int 0x29
    retm<>
    endm

_bittest macro lp, imm
    if (opattr lp) eq 48
        bt dword ptr [lp],imm
    else
        mov rcx,lp
        bt dword ptr [rcx],imm
    endif
    setb al
    retm<al>
    endm

_bittestandcomplement macro lp, imm
    if (opattr lp) eq 48
        btc dword ptr [lp],imm
    else
        mov rcx,lp
        btc dword ptr [rcx],imm
    endif
    setb al
    retm<al>
    endm

_bittestandreset macro lp, imm
    if (opattr lp) eq 48
        btr dword ptr [lp],imm
    else
        mov rcx,lp
        btr dword ptr [rcx],imm
    endif
    setb al
    retm<al>
    endm

_bittestandset macro lp, imm
    if (opattr lp) eq 48
        bts dword ptr [lp],imm
    else
        mov rcx,lp
        bts dword ptr [rcx],imm
    endif
    setb al
    retm<al>
    endm

_interlockedbittestandreset macro lp, imm
    if (opattr lp) eq 48
        lock btr dword ptr [lp],imm
    else
        mov rcx,lp
        lock btr dword ptr [rcx],imm
    endif
    setb al
    retm<al>
    endm

_byteswap_ulong macro val
    _mm_loadreg(eax, val)
    bswap eax
    retm<eax>
    endm

_byteswap_uint64 macro val
    _mm_loadreg(rax, val)
    bswap rax
    retm<rax>
    endm

_byteswap_ushort macro val
    _mm_loadreg(ax, val)
    ror ax,8
    retm<ax>
    endm

_disable macro
    cli
    retm<>
    endm

_enable macro
    sti
    retm<>
    endm

_mm_rotl macro reg, val, cnt
    _mm_loadreg(reg, val)
    rol reg,cnt
    retm<reg>
    endm

_mm_rotr macro reg, val, cnt
    _mm_loadreg(reg, val)
    ror reg,cnt
    retm<reg>
    endm

_rotl macro val, cnt
    exitm<_mm_rotl(eax, val, cnt)>
    endm
_rotr macro val, cnt
    exitm<_mm_rotr(eax, val, cnt)>
    endm
_lrotl  equ <_rotl>
_lrotr  equ <_rotr>
_rotl16 macro val, cnt
    exitm<_mm_rotl(ax, val, cnt)>
    endm
_rotl64 macro val, cnt
    exitm<_mm_rotl(rax, val, cnt)>
    endm
_rotl8 macro val, cnt
    exitm<_mm_rotl(al, val, cnt)>
    endm
_rotr16 macro val, cnt
    exitm<_mm_rotr(ax, val, cnt)>
    endm
_rotr64 macro val, cnt
    exitm<_mm_rotr(rax, val, cnt)>
    endm
_rotr8 macro val, cnt
    exitm<_mm_rotr(al, val, cnt)>
    endm

ifdef __MACHINEX86
_InterlockedAddLargeStatistic macro lpAddend, dwValue
    _mm_loadreg(ecx, lpAddend)
    _mm_loadreg(eax, dwValue)
    lock add [ecx],eax
    .ifc
        lock add [ecx+4],0
    .endif
    retm<eax>
    endm
endif

ifdef __MACHINEX64

_InterlockedAnd macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(edx, dwMask)
    mov eax,[rcx]
    lock and [rcx],edx
    retm<eax>
    endm

_InterlockedAnd8 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(dl, dwMask)
    movzx eax,byte ptr [rcx]
    lock and [rcx],dl
    retm<eax>
    endm

_InterlockedAnd16 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(dx, dwMask)
    movzx eax,word ptr [rcx]
    lock and [rcx],dx
    retm<eax>
    endm

_InterlockedAnd64 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(rdx, dwMask)
    mov rax,[rcx]
    lock and [rcx],rdx
    retm<rax>
    endm

_InterlockedOr macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(edx, dwMask)
    mov eax,[rcx]
    lock or [rcx],edx
    retm<eax>
    endm

_InterlockedOr8 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(dl, dwMask)
    movzx eax,byte ptr [rcx]
    lock or [rcx],dl
    retm<eax>
    endm

_InterlockedOr16 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(dx, dwMask)
    movzx eax,word ptr [rcx]
    lock or [rcx],dx
    retm<eax>
    endm

_InterlockedOr64 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(rdx, dwMask)
    mov rax,[rcx]
    lock or [rcx],rdx
    retm<rax>
    endm

_InterlockedXor macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(edx, dwMask)
    mov eax,[rcx]
    lock or [rcx],edx
    retm<eax>
    endm

_InterlockedXor8 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(dl, dwMask)
    movzx eax,byte ptr [rcx]
    lock xor [rcx],dl
    retm<eax>
    endm

_InterlockedXor16 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(dx, dwMask)
    movzx eax,word ptr [rcx]
    lock xor [rcx],dx
    retm<eax>
    endm

_InterlockedXor64 macro lpValue, dwMask
    _mm_loadreg(rcx, lpValue)
    _mm_loadreg(rdx, dwMask)
    mov rax,[rcx]
    lock xor [rcx],rdx
    retm<rax>
    endm

_InterlockedAnd_np      equ <_InterlockedAnd>
_InterlockedAnd8_np     equ <_InterlockedAnd8>
_InterlockedAnd16_np    equ <_InterlockedAnd16>
_InterlockedAnd64_np    equ <_InterlockedAnd64>

_InterlockedOr_np       equ <_InterlockedOr>
_InterlockedOr8_np      equ <_InterlockedOr8>
_InterlockedOr16_np     equ <_InterlockedOr16>
_InterlockedOr64_np     equ <_InterlockedOr64>

_InterlockedXor_np      equ <_InterlockedXor>
_InterlockedXor8_np     equ <_InterlockedXor8>
_InterlockedXor16_np    equ <_InterlockedXor16>
_InterlockedXor64_np    equ <_InterlockedXor64>

_InterlockedCompareExchange128_np       equ <_InterlockedCompareExchange128>
_InterlockedCompareExchange16_np        equ <_InterlockedCompareExchange16>
_InterlockedCompareExchange64_np        equ <_InterlockedCompareExchange64>
_InterlockedCompareExchangePointer_np   equ <_InterlockedCompareExchangePointer>
_InterlockedCompareExchange_np          equ <_InterlockedCompareExchange>

endif ;; __MACHINEX64

ifdef __MACHINEX86
__addfsbyte macro offs, b
    assume fs:nothing
    add byte ptr fs:[offs],b
    assume fs:error
    retm<>
    endm
__addfsdword macro offs, w
    assume fs:nothing
    add word ptr fs:[offs],w
    assume fs:error
    retm<>
    endm
__addfsword macro offs, l
    assume fs:nothing
    add dword ptr fs:[offs],l
    assume fs:error
    retm<>
    endm
endif

ifdef __MACHINEX64
__addgsbyte macro offs, v
    add byte ptr gs:[offs],v
    retm<>
    endm
__addgsword macro offs, v
    add word ptr gs:[offs],v
    retm<>
    endm
__addgsdword macro offs, v
    add dword ptr gs:[offs],v
    retm<>
    endm
__addgsqword macro offs, v
    add qword ptr gs:[offs],v
    retm<>
    endm
__incgsbyte macro offs
    inc byte ptr gs:[offs]
    retm<>
    endm
__incgsdword macro offs
    inc dword ptr gs:[offs]
    retm<>
    endm
__incgsqword macro offs
    inc qword ptr gs:[offs]
    retm<>
    endm
__incgsword macro offs
    inc word ptr gs:[offs]
    retm<>
    endm
endif

ifdef __MACHINEX86
__incfsbyte macro offs
    assume fs:nothing
    inc byte ptr fs:[offs]
    assume fs:error
    retm<>
    endm
__incfsdword macro offs
    assume fs:nothing
    inc dword ptr fs:[offs]
    assume fs:error
    retm<>
    endm
__incfsword macro offs
    assume fs:nothing
    inc word ptr fs:[offs]
    assume fs:error
    retm<>
    endm
endif

ifdef __MACHINEX86_X64

__clts macro
    exitm<clts>
    endm

__cpuid macro cpuInfo, function_id
    push rsi
    push rbx
    _mm_loadreg(rsi, cpuInfo)
    _mm_loadreg(eax, function_id)
    xor ecx,ecx
    cpuid
    mov [rsi],eax
    mov [rsi+4],ebx
    mov [rsi+8],ecx
    mov [rsi+12],edx
    pop rbx
    pop rsi
    retm<eax>
    endm

__cpuidex macro cpuInfo, function_id, subfunction_id
    push rsi
    push rbx
    _mm_loadreg(rsi, cpuInfo)
    _mm_loadreg(eax, function_id)
    _mm_loadreg(ecx, subfunction_id)
    cpuid
    mov [rsi],eax
    mov [rsi+4],ebx
    mov [rsi+8],ecx
    mov [rsi+12],edx
    pop rbx
    pop rsi
    retm<eax>
    endm

__emul macro a, b
    _mm_loadreg(ecx, a)
    _mm_loadreg(edx, b)
    movsxd r8,ecx
    movsxd rax,edx
    imul r8
    retm<rax>
    endm

__emulu macro a, b
    _mm_loadreg(ecx, a)
    _mm_loadreg(eax, b)
    mul rcx
    retm<rax>
    endm

endif

ifdef __MACHINEX64
_mul128 macro Multiplier, Multiplicand, HighProduct
    _mm_loadreg(rcx, Multiplier)
    _mm_loadreg(rdx, Multiplicand)
    mov rax,rdx
    imul rcx
    _mm_storereg(HighProduct, rdx)
    retm<rax>
    endm

_umul128 macro Multiplier, Multiplicand, HighProduct
    _mm_loadreg(rcx, Multiplier)
    _mm_loadreg(rdx, Multiplicand)
    mov rax,rdx
    mul rcx
    _mm_storereg(HighProduct, rdx)
    retm<rax>
    endm
endif

ifdef __MACHINEX86_X64
__ll_lshift macro __mask, nBit
    _mm_loadreg(rax, __mask)
    _mm_loadreg(ecx, nBit)
    shl rax,cl
    retm<rax>
    endm

__ll_rshift macro __mask, nBit
    _mm_loadreg(rax, __mask)
    _mm_loadreg(ecx, nBit)
    sar rax,cl
    retm<rax>
    endm

__ull_rshift macro __mask, nBit
    _mm_loadreg(rax, __mask)
    _mm_loadreg(ecx, nBit)
    shr rax,cl
    retm<rax>
    endm
endif

ifdef __MACHINEX64
__faststorefence macro
    lock or dword ptr [rsp],0
    retm<>
    endm
endif

ifdef __MACHINEX86_X64
__getcallerseflags macro
    pushfq
    pop rax
    retm<eax>
    endm

__halt macro
    hlt
    retm<>
    endm

__inbyte macro Port
    _mm_loadreg(edx, Port)
    in al,dx
    retm<al>
    endm

__inword macro Port
    _mm_loadreg(edx, Port)
    in ax,dx
    retm<ax>
    endm

__indword macro Port
    _mm_loadreg(edx, Port)
    in eax,dx
    retm<eax>
    endm

__inbytestring macro Port, Buffer, Count
    push rdi
    _mm_loadreg(rdi, Buffer)
    _mm_loadreg(edx, Port)
    _mm_loadreg(ecx, Count)
    rep insb
    pop rdi
    retm<>
    endm

__indwordstring macro Port, Buffer, Count
    push rdi
    _mm_loadreg(rdi, Buffer)
    _mm_loadreg(edx, Port)
    _mm_loadreg(ecx, Count)
    rep insw
    pop rdi
    retm<>
    endm

__int2c macro
    int 0x2c
    retm<>
    endm

__invlpg macro Address
    _mm_loadreg(rcx, Address)
    invlpg byte ptr [rcx]
    retm<>
    endm

__lidt macro Address
    _mm_loadreg(rcx, Address)
    lidt byte ptr [rcx]
    retm<>
    endm
if 0
__lzcnt macro value
    lzcnt eax,value
    retm<eax>
    endm

__lzcnt16 macro value
    lzcnt eax,value
    retm<eax>
    endm
endif
endif

ifdef __MACHINEX64
if 0
__lzcnt64 macro value
    lzcnt eax,value
    retm<eax>
    endm

endif
endif

ifdef __MACHINEX86_X64

__movs macro x, Destination, Source, Count
    push rsi
    push rdi
    _mm_loadreg(rdi, Destination)
    _mm_loadreg(rsi, Source)
    _mm_loadreg(ecx, Count)
    rep movs&x&
    pop rdi
    pop rsi
    retm<>
    endm

__movsb macro Destination, Source, Count
    exitm<__movs(b, Destination, Source, Count)>
    endm

__movsd macro Destination, Source, Count
    exitm<__movs(d, Destination, Source, Count)>
    endm

__movsw macro Destination, Source, Count
    exitm<__movs(w, Destination, Source, Count)>
    endm

endif

ifdef __MACHINEX64
__movsq macro Destination, Source, Count
    exitm<__movs(q, Destination, Source, Count)>
    endm
endif

ifdef __MACHINEX86_X64
__nvreg_restore_fence macro
    endm
__nvreg_save_fence macro
    endm
endif

ifdef __MACHINEX86_X64
__outbyte macro Port, val
    _mm_loadreg(edx, Port)
    _mm_loadreg(al, val)
    out dx,al
    retm<>
    endm
__outword macro Port, val
    _mm_loadreg(edx, Port)
    _mm_loadreg(ax, val)
    out dx,ax
    retm<>
    endm
__outdword macro Port, val
    _mm_loadreg(edx, Port)
    _mm_loadreg(eax, val)
    out dx,eax
    retm<>
    endm

__outbytestring macro Port, Buffer, Count
    push rdi
    _mm_loadreg(rdi, Buffer)
    _mm_loadreg(edx, Port)
    _mm_loadreg(ecx, Count)
    rep outsb
    pop rdi
    retm<>
    endm
__outdwordstring macro Port, Buffer, Count
    push rdi
    _mm_loadreg(rdi, Buffer)
    _mm_loadreg(edx, Port)
    _mm_loadreg(ecx, Count)
    rep outsd
    pop rdi
    retm<>
    endm
__outwordstring macro Port, Buffer, Count
    push rdi
    _mm_loadreg(rdi, Buffer)
    _mm_loadreg(edx, Port)
    _mm_loadreg(ecx, Count)
    rep outsw
    pop rdi
    retm<>
    endm
endif

ifdef __MACHINEX86_X64
__popcnt macro value
    popcnt eax,value
    retm<eax>
    endm

__popcnt16 macro value
    popcnt ax,value
    retm<ax>
    endm
endif

ifdef __MACHINEX64
__popcnt64 macro value
    popcnt rax,value
    retm<rax>
    endm
endif

ifdef __MACHINEX86_X64
__rdtsc macro
    rdtsc
ifdef _WIN64
    shl rdx,32
    or rax,rdx
endif
    retm<rax>
    endm

__rdtscp macro Aux
    push rdi
    _mm_loadreg(rdi, Aux)
    rdtscp
ifdef _WIN64
    shl rdx,32
    or rax,rdx
endif
    mov [rdi],ecx
    pop rdi
    retm<rax>
    endm
endif

if 0

__MACHINEX64(__readcr0 proto)
__MACHINEX86(__readcr0 proto)
__MACHINEX64(__readcr2 proto)
__MACHINEX86(__readcr2 proto)
__MACHINEX64(__readcr3 proto)
__MACHINEX86(__readcr3 proto)
__MACHINEX64(__readcr4 proto)
__MACHINEX86(__readcr4 proto)
__MACHINEX64(__readcr8 proto)
__MACHINEX86(__readcr8 proto)
__MACHINEX64(__readdr proto :dword)
__MACHINEX86(__readdr proto :dword)
__MACHINEX64(__readeflags proto)
__MACHINEX86(__readeflags proto)
__MACHINEX86(__readfsbyte proto :dword)
__MACHINEX86(__readfsdword proto :dword)
__MACHINEX86(__readfsqword proto :dword)
__MACHINEX86(__readfsword proto :dword)
__MACHINEX64(__readgsbyte proto :dword)
__MACHINEX64(__readgsdword proto :dword)
__MACHINEX64(__readgsqword proto :dword)
__MACHINEX64(__readgsword proto :dword)
__MACHINEX86_X64(__readmsr proto :dword)
__MACHINEX86_X64(__readpmc proto :dword)
__MACHINEX86_X64(__segmentlimit proto :dword)
__MACHINEX64(__shiftleft128 proto :qword, :qword, :byte)
__MACHINEX64(__shiftright128 proto :qword, :qword, :byte)
__MACHINEX86_X64(__sidt proto :ptr)
__MACHINEX86_X64(__stosb proto :LPSTR, :byte, :size_t)
__MACHINEX86_X64(__stosd proto :ptr, :dword, :size_t)
__MACHINEX64(__stosq proto :ptr, :qword, :size_t)
__MACHINEX86_X64(__stosw proto :ptr, :word, :size_t)
__MACHINEX86_X64(__svm_clgi proto)
__MACHINEX86_X64(__svm_invlpga proto :ptr, :sdword)
__MACHINEX86_X64(__svm_skinit proto :sdword)
__MACHINEX86_X64(__svm_stgi proto)
__MACHINEX86_X64(__svm_vmload proto :size_t)
__MACHINEX86_X64(__svm_vmrun proto :size_t)
__MACHINEX86_X64(__svm_vmsave proto :size_t)
__MACHINEX86_X64(__ud2 proto)
__MACHINEX86_X64(__vmx_off proto)
__MACHINEX64(__vmx_on proto :ptr)
__MACHINEX64(__vmx_vmclear proto :ptr)
__MACHINEX64(__vmx_vmlaunch proto)
__MACHINEX64(__vmx_vmptrld proto :ptr)
__MACHINEX86_X64(__vmx_vmptrst proto :ptr)
__MACHINEX64(__vmx_vmread proto :size_t, :ptr)
__MACHINEX64(__vmx_vmresume proto)
__MACHINEX64(__vmx_vmwrite proto :size_t, :size_t)
__MACHINEX86_X64(__wbinvd proto)
__MACHINEX64(__writecr0 proto :qword)
__MACHINEX86(__writecr0 proto :dword)
__MACHINEX64(__writecr2 proto :qword)
__MACHINEX86(__writecr2 proto :dword)
__MACHINEX64(__writecr3 proto :qword)
__MACHINEX86(__writecr3 proto :dword)
__MACHINEX64(__writecr4 proto :qword)
__MACHINEX86(__writecr4 proto :dword)
__MACHINEX64(__writecr8 proto :qword)
__MACHINEX86(__writecr8 proto :dword)
__MACHINEX64(__writedr proto :dword, :qword)
__MACHINEX86(__writedr proto :dword, :dword)
__MACHINEX64(__writeeflags proto :qword)
__MACHINEX86(__writeeflags proto :dword)
__MACHINEX86(__writefsbyte proto :dword, :byte)
__MACHINEX86(__writefsdword proto :dword, :dword)
__MACHINEX86(__writefsqword proto :dword, :qword)
__MACHINEX86(__writefsword proto :dword, :word)
__MACHINEX64(__writegsbyte proto :dword, :byte)
__MACHINEX64(__writegsdword proto :dword, :dword)
__MACHINEX64(__writegsqword proto :dword, :qword)
__MACHINEX64(__writegsword proto :dword, :word)
__MACHINEX86_X64(__writemsr proto :dword, :qword)

__MACHINEX86_X64(_rsm proto)
__MACHINEX86_X64(_lgdt proto :ptr)
__MACHINEX86_X64(_sgdt proto :ptr)
__MACHINEX86_X64(_clac proto)
__MACHINEX86_X64(_stac proto)
__MACHINEX86_X64(_addcarry_u8 proto __cdecl :byte, :byte, :byte, :ptr)
__MACHINEX86_X64(_subborrow_u8 proto __cdecl :byte, :byte, :byte, :ptr)
__MACHINEX86_X64(_addcarry_u16 proto __cdecl :byte, :word, :word, :ptr)
__MACHINEX86_X64(_subborrow_u16 proto __cdecl :byte, :word, :word, :ptr)
__MACHINEX86_X64(_addcarry_u32 proto __cdecl :byte, :dword, :dword, :ptr)
__MACHINEX86_X64(_subborrow_u32 proto __cdecl :byte, :dword, :dword, :ptr)
__MACHINEX64(_addcarry_u64 proto __cdecl :byte, :qword, :qword, :ptr)
__MACHINEX64(_subborrow_u64 proto __cdecl :byte, :qword, :qword, :ptr)

endif

.pragma list(pop)
endif

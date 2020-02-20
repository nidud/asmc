.pragma list(push, 0)
.pragma cref(push, 0)
ifndef __INTRIN_H_
__INTRIN_H_ equ <>
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

_BitScanForward proto :ptr, :long_t
_BitScanReverse proto :ptr, :long_t

_BitScanForward macro lpIndex, dwMask
    xor     eax,eax
    bsf     eax,edx
    mov     [rcx],eax
    setne   al
    retm    <al>
    endm

_BitScanReverse macro lpIndex, dwMask
    xor     eax,eax
    bsr     eax,edx
    mov     [rcx],eax
    setne   al
    retm    <al>
    endm

ifdef __MACHINEX64

_BitScanForward64 proto :ptr, :qword
_BitScanReverse64 proto :ptr, :qword

_BitScanForward64 macro lpIndex, dwMask
    xor     eax,eax
    bsf     rax,rdx
    mov     [rcx],eax
    setne   al
    retm    <al>
    endm

_BitScanReverse64 macro lpIndex, dwMask
    xor     eax,eax
    bsr     rax,rdx
    mov     [rcx],eax
    setne   al
    retm    <al>
    endm

endif

_InterlockedCompareExchange     proto :ptr, :long_t, :long_t
_InterlockedCompareExchange8    proto :ptr, :byte, :byte
_InterlockedCompareExchange16   proto :ptr, :word, :word
_InterlockedCompareExchange64   proto :ptr, :qword, :qword
_InterlockedDecrement16         proto :ptr
_InterlockedDecrement           proto :ptr

_InterlockedCompareExchange macro Destination, Exchange, Comparand
    mov     eax,Comparand
    push    [rcx]
    lock    cmpxchg dword ptr [rcx],edx
    pop     rax
    retm    <eax>
    endm

_InterlockedCompareExchange8 macro Destination, Exchange, Comparand
    mov     al,Comparand
    push    [rcx]
    lock    cmpxchg byte ptr [rcx],dl
    pop     rax
    retm    <al>
    endm

_InterlockedCompareExchange16 macro Destination, Exchange, Comparand
    mov     ax,Comparand
    push    [rcx]
    lock    cmpxchg word ptr [rcx],dl
    pop     rax
    retm    <ax>
    endm

_InterlockedCompareExchange64 macro Destination, Exchange, Comparand
    mov     rax,Comparand
    push    [rcx]
    lock    cmpxchg size_t ptr [rcx],rdx
    pop     rax
    retm    <rax>
    endm

_InterlockedCompareExchangePointer equ <_InterlockedCompareExchange64>

_InterlockedDecrement16 macro lpAddend
    lock    dec word ptr [rcx]
    mov     ax,[rcx]
    retm    <ax>
    endm

_InterlockedDecrement macro lpAddend
    lock    dec dword ptr [rcx]
    mov     eax,[rcx]
    retm    <eax>
    endm

ifdef __MACHINEX64

_InterlockedDecrement64 proto :ptr

_InterlockedDecrement64 macro lpAddend
    lock dec qword ptr [rcx]
    mov rax,[rcx]
    retm<rax>
    endm

endif

_InterlockedIncrement16 proto :ptr
_InterlockedIncrement   proto :ptr

_InterlockedIncrement16 macro lpAddend
    lock    inc word ptr [rcx]
    mov     ax,[rcx]
    retm    <ax>
    endm

_InterlockedIncrement macro lpAddend
    lock    inc dword ptr [rcx]
    mov     eax,[rcx]
    retm    <eax>
    endm

ifdef __MACHINEX64

_InterlockedIncrement64 proto :ptr

_InterlockedIncrement64 macro lpAddend
    lock    inc qword ptr [rcx]
    mov     rax,[rcx]
    retm    <rax>
    endm

endif

_InterlockedExchangePointer proto :ptr, :ptr
__fastfail proto :int_t

_InterlockedExchangePointer macro Target, Value
    xchg    [rcx],rdx
    mov     rax,rdx
    retm    <rax>
    endm

__fastfail macro code
    int     0x29
    exitm   <>
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

_InterlockedAnd     proto :ptr, :long_t
_InterlockedAnd8    proto :ptr, :byte
_InterlockedAnd16   proto :ptr, :word
_InterlockedAnd64   proto :ptr, :qword
_InterlockedOr      proto :ptr, :long_t
_InterlockedOr8     proto :ptr, :byte
_InterlockedOr16    proto :ptr, :word
_InterlockedOr64    proto :ptr, :qword
_InterlockedXor     proto :ptr, :long_t
_InterlockedXor8    proto :ptr, :byte
_InterlockedXor16   proto :ptr, :word
_InterlockedXor64   proto :ptr, :qword

_InterlockedAnd macro lpValue, dwMask
    mov     eax,[rcx]
    lock    and [rcx],edx
    retm    <eax>
    endm

_InterlockedAnd8 macro lpValue, dwMask
    movzx   eax,byte ptr [rcx]
    lock    and [rcx],dl
    retm    <eax>
    endm

_InterlockedAnd16 macro lpValue, dwMask
    movzx   eax,word ptr [rcx]
    lock    and [rcx],dx
    retm    <eax>
    endm

_InterlockedAnd64 macro lpValue, dwMask
    mov     rax,[rcx]
    lock    and [rcx],rdx
    retm    <rax>
    endm

_InterlockedOr macro lpValue, dwMask
    mov     eax,[rcx]
    lock    or [rcx],edx
    retm    <eax>
    endm

_InterlockedOr8 macro lpValue, dwMask
    movzx   eax,byte ptr [rcx]
    lock    or [rcx],dl
    retm    <eax>
    endm

_InterlockedOr16 macro lpValue, dwMask
    movzx   eax,word ptr [rcx]
    lock    or [rcx],dx
    retm    <eax>
    endm

_InterlockedOr64 macro lpValue, dwMask
    mov     rax,[rcx]
    lock    or [rcx],rdx
    retm    <rax>
    endm

_InterlockedXor macro lpValue, dwMask
    mov     eax,[rcx]
    lock    or [rcx],edx
    retm    <eax>
    endm

_InterlockedXor8 macro lpValue, dwMask
    movzx   eax,byte ptr [rcx]
    lock    xor [rcx],dl
    retm    <eax>
    endm

_InterlockedXor16 macro lpValue, dwMask
    movzx   eax,word ptr [rcx]
    lock    xor [rcx],dx
    retm    <eax>
    endm

_InterlockedXor64 macro lpValue, dwMask
    mov     rax,[rcx]
    lock    xor [rcx],rdx
    retm    <rax>
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
__readfsbyte macro offs
    assume fs:nothing
    mov al,fs:[offs]
    assume fs:error
    retm<al>
    endm
__readfsdword macro offs
    assume fs:nothing
    mov eax,fs:[offs]
    assume fs:error
    retm<eax>
    endm
__readfsqword macro offs
    assume fs:nothing
    mov eax,fs:[offs]
    mov edx,fs:[offs+4]
    assume fs:error
    retm<eax>
    endm
__readfsword macro offs
    assume fs:nothing
    mov ax,fs:[offs]
    assume fs:error
    retm<ax>
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
__readgsbyte macro offs
    mov al,gs:[offs]
    retm<al>
    endm
__readgsdword macro offs
    mov eax,gs:[offs]
    retm<eax>
    endm
__readgsqword macro offs
    mov rax,gs:[offs]
    retm<rax>
    endm
__readgsword macro offs
    mov ax,gs:[offs]
    retm<ax>
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

__cpuid     proto :ptr_t, :int_t
__cpuidex   proto :ptr_t, :int_t, :int_t
__emul      proto :int_t, :int_t
__emulu     proto :int_t, :int_t

__clts macro
    exitm<clts>
    endm

__cpuid macro cpuInfo, function_id
    push    rsi
    push    rbx
    mov     rsi,cpuInfo
    mov     eax,function_id
    xor     ecx,ecx
    cpuid
    mov     [rsi],eax
    mov     [rsi+4],ebx
    mov     [rsi+8],ecx
    mov     [rsi+12],edx
    pop     rbx
    pop     rsi
    retm    <eax>
    endm

__cpuidex macro cpuInfo, function_id, subfunction_id
    push    rsi
    push    rbx
    mov     rsi,cpuInfo
    mov     eax,function_id
    mov     ecx,subfunction_id
    cpuid
    mov     [rsi],eax
    mov     [rsi+4],ebx
    mov     [rsi+8],ecx
    mov     [rsi+12],edx
    pop     rbx
    pop     rsi
    retm    <eax>
    endm

__emul macro a, b
    movsxd  r8,ecx
    movsxd  rax,edx
    imul    r8
    retm    <rax>
    endm

__emulu macro a, b
    mov     eax,b
    mul     rcx
    retm    <rax>
    endm

endif

_mul128 proto :qword, :qword, :ptr qword

ifdef __MACHINEX64

_mul256 proto :ptr, :ptr, :ptr
umul256 proto syscall :oword, :oword, :ptr

_mul128 macro Multiplier, Multiplicand, HighProduct
    mov rax,rdx
    mul rcx
    .if r8
        mov [r8],rdx
    .endif
    retm <rax>
    endm

_mul256 macro Multiplier, Multiplicand, HighProduct
    mov rax,[rcx]
    mov r10,[rcx+8]
    mov r9, [rdx+8]
    .if !r10 && !r9
        .if r8
            mov [r8],r9
            mov [r8+8],r9
        .endif
        mul qword ptr [rdx]
    .else
        mov     r11,[rdx]
        mul     r11         ; a * b
        push    rax
        xchg    rdx,r11
        mov     rax,r10
        mul     rdx         ; a[8] * b
        add     r11,rax
        xchg    rcx,rdx
        mov     rax,[rdx]
        mul     r9          ; a * b[8]
        add     r11,rax
        adc     rcx,rdx
        mov     edx,0
        adc     edx,0
        .if r8
            xchg    rdx,r9
            mov     rax,r10
            mul     rdx     ; a[8] * b[8]
            add     rax,rcx
            adc     rdx,r9
            mov     [r8],rax
            mov     [r8+8],rdx
        .endif
        pop rax
        mov rdx,r11
    .endif
    exitm<>
    endm

endif

_umul128 equ <_mul128>

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

__inbytestring  proto :int_t, :ptr_t, :int_t
__indwordstring proto :int_t, :ptr_t, :int_t
__invlpg        proto :ptr_t
__lidt          proto :ptr_t
__lzcnt         proto :int_t
__lzcnt16       proto :int_t

__inbytestring macro Port, Buffer, Count
    push    rdi
    mov     rdi,Buffer
    mov     edx,Port
    mov     ecx,Count
    rep     insb
    pop     rdi
    exitm   <>
    endm

__indwordstring macro Port, Buffer, Count
    push    rdi
    mov     rdi,Buffer
    mov     edx,Port
    mov     ecx,Count
    rep     insw
    pop     rdi
    exitm   <>
    endm

__int2c macro
    int     0x2c
    exitm   <>
    endm

__invlpg macro Address
    invlpg  byte ptr [rcx]
    exitm   <>
    endm

__lidt macro Address
    lidt    byte ptr [rcx]
    exitm   <>
    endm

__lzcnt macro value
    lzcnt   eax,value
    retm    <eax>
    endm

__lzcnt16 macro value
    lzcnt   eax,value
    retm    <eax>
    endm

endif

ifdef __MACHINEX64

__lzcnt64       proto :int_t

__lzcnt64 macro value
    lzcnt   eax,value
    retm    <eax>
    endm

endif

ifdef __MACHINEX86_X64

__movsb proto :ptr, :ptr, :int_t
__movsd proto :ptr, :ptr, :int_t
__movsw proto :ptr, :ptr, :int_t
__stosb proto :ptr, :byte, :int_t
__stosw proto :ptr, :word, :int_t
__stosd proto :ptr, :dword, :int_t

__movsb macro Destination, Source, Count
    push    rsi
    push    rdi
    mov     rdi,Destination
    mov     rsi,Source
    mov     ecx,Count
    rep     movsb
    pop     rdi
    pop     rsi
    exitm   <>
    endm

__movsw macro Destination, Source, Count
    push    rsi
    push    rdi
    mov     rdi,Destination
    mov     rsi,Source
    mov     ecx,Count
    rep     movsw
    pop     rdi
    pop     rsi
    exitm   <>
    endm

__movsd macro Destination, Source, Count
    push    rsi
    push    rdi
    mov     rdi,Destination
    mov     rsi,Source
    mov     ecx,Count
    rep     movsd
    pop     rdi
    pop     rsi
    exitm   <>
    endm

__stosb macro Destination, Val, Count
    push    rdi
    mov     rdi,Destination
    mov     al,Val
    mov     ecx,Count
    rep     stosb
    pop     rdi
    exitm   <>
    endm

__stosw macro Destination, Val, Count
    push    rdi
    mov     rdi,Destination
    mov     ax,Val
    mov     ecx,Count
    rep     stosw
    pop     rdi
    exitm   <>
    endm

__stosd macro Destination, Val, Count
    push    rdi
    mov     rdi,Destination
    mov     eax,Val
    mov     ecx,Count
    rep     stosd
    pop     rdi
    exitm   <>
    endm

endif

ifdef __MACHINEX64

__stosq proto :ptr, :qword, :int_t
__movsq proto :ptr, :ptr, :int_t

__movsq macro Destination, Source, Count
    push    rsi
    push    rdi
    mov     rdi,Destination
    mov     rsi,Source
    mov     ecx,Count
    rep     movsq
    pop     rdi
    pop     rsi
    exitm   <>
    endm

__stosq macro Destination, Val, Count
    push    rdi
    mov     rdi,Destination
    mov     rax,Val
    mov     ecx,Count
    rep     stosd
    pop     rdi
    exitm   <>
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

__outbytestring     proto :int_t, :ptr, :int_t
__outdwordstring    proto :int_t, :ptr, :int_t
__outwordstring     proto :int_t, :ptr, :int_t

__outbytestring macro Port, Buffer, Count
    push    rdi
    mov     rdi,Buffer
    mov     edx,Port
    mov     ecx,Count
    rep     outsb
    pop     rdi
    exitm   <>
    endm

__outwordstring macro Port, Buffer, Count
    push    rdi
    mov     rdi,Buffer
    mov     edx,Port
    mov     ecx,Count
    rep     outsw
    pop     rdi
    exitm   <>
    endm

__outdwordstring macro Port, Buffer, Count
    push    rdi
    mov     rdi,Buffer
    mov     edx,Port
    mov     ecx,Count
    rep     outsd
    pop     rdi
    exitm   <>
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

__readcr0 macro
    mov rax,cr0
    retm<rax>
    endm
__readcr2 macro
    mov rax,cr2
    retm<rax>
    endm
__readcr3 macro
    mov rax,cr3
    retm<rax>
    endm
__readcr4 macro
    mov rax,cr4
    retm<rax>
    endm
__readcr8 macro
    mov rax,cr8
    retm<rax>
    endm

__writecr0 macro val
    mov cr0,val
    retm<>
    endm
__writecr2 macro val
    mov cr2,val
    retm<>
    endm
__writecr3 macro val
    mov cr3,val
    retm<>
    endm
__writecr4 macro val
    mov cr4,val
    retm<>
    endm
__writecr8 macro val
    mov cr8,val
    retm<>
    endm

__readdr macro imm
    mov rax,dr&imm&
    retm<rax>
    endm

__writedr macro imm, val
    mov dr&imm&,val
    retm<>
    endm

__readeflags macro
ifdef _WIN64
    pushfq
else
    pushfd
endif
    pop rax
    retm<rax>
    endm

__writeeflags macro val
    push val
ifdef _WIN64
    popfq
else
    popfd
endif
    retm<>
    endm

endif

ifdef __MACHINEX64

__shiftleft128 macro LowPart, HighPart, Count
    _mm_loadreg(rax, LowPart)
    _mm_loadreg(rdx, HighPart)
    shld rdx,rax,Count
    sal rax,Count
    .if cl & 0xC0
        .if cl & 0x80
            xor eax,eax
            xor edx,edx
        .else
            mov rdx,rax
            xor rax,rax
        .endif
    .endif
    retm<rax>
    endm

__shiftright128 macro LowPart, HighPart, Count
    _mm_loadreg(rax, LowPart)
    _mm_loadreg(rdx, HighPart)
    shrd rax,rdx,Count
    sar rdx,Count
    .if cl & 0xC0
        .if cl & 0x80
            xor eax,eax
            xor edx,edx
        .else
            mov rax,rdx
            xor rdx,rdx
        .endif
    .endif
    retm<rax>
    endm

endif

ifdef __MACHINEX86_X64

__readmsr macro register
    _mm_loadreg(ecx, register)
    rdmsr
ifdef _WIN64
    shl rdx,32
    or rax,rdx
endif
    retm<rax>
    endm

__readpmc macro counter
    _mm_loadreg(ecx, counter)
    rdpmc
ifdef _WIN64
    shl rdx,32
    or rax,rdx
endif
    retm<rax>
    endm

__segmentlimit macro a
    _mm_loadreg(eax, a)
    lsl eax,eax
    retm<eax>
    endm

__sidt macro Destination
    _mm_loadreg(rcx, Destination)
    sidt qword ptr [rcx]
    retm<>
    endm

__svm_clgi macro
    clgi
    endm

__svm_invlpga macro Va, ASID
    _mm_loadreg(rax, Va)
    _mm_loadreg(ecx, ASID)
    invlpga rax,ecx
    retm<>
    endm

__svm_skinit macro SLB
    _mm_loadreg(eax, SLB)
    skinit eax
    retm<>
    endm

__svm_stgi macro
    stgi
    retm<>
    endm

__svm_vmload macro VmcbPhysicalAddress
    _mm_loadreg(eax, VmcbPhysicalAddress)
    vmload rax
    retm<>
    endm

__svm_vmrun macro VmcbPhysicalAddress
    _mm_loadreg(eax, VmcbPhysicalAddress)
    vmrun rax
    retm<>
    endm

__svm_vmsave macro VmcbPhysicalAddress
    _mm_loadreg(eax, VmcbPhysicalAddress)
    vmsave rax
    retm<>
    endm

__ud2 macro
    ud2
    retm<>
    endm

__vmx_off macro
    vmxoff
    retm<>
    endm

endif

ifdef __MACHINEX64

__vmx_on        proto :ptr
__vmx_vmclear   proto :ptr
__vmx_vmptrld   proto :ptr
__vmx_vmread    proto :ptr, :ptr
__vmx_vmwrite   proto :ptr, :ptr

__vmx_on macro VmsSupportPhysicalAddress
    vmxon   qword ptr [rcx]
    exitm   <>
    endm

__vmx_vmclear macro VmcsPhysicalAddress
    vmclear qword ptr [rcx]
    exitm   <>
    endm

__vmx_vmlaunch macro
    vmlaunch
    exitm   <>
    endm

__vmx_vmptrld macro VmcsPhysicalAddress
    vmptrld qword ptr [rcx]
    exitm   <>
    endm

__vmx_vmread macro Field, FieldValue
    mov     rax,Field
    mov     rcx,FieldValue
    vmread  rax,rcx
    exitm   <>
    endm

__vmx_vmresume macro
    vmresume
    exitm   <>
    endm

__vmx_vmwrite macro Field, FieldValue
    mov     rax,Field
    mov     rcx,FieldValue
    vmwrite rax,rcx
    exitm   <>
    endm

endif

ifdef __MACHINEX86_X64

__vmx_vmptrst proto :ptr

__vmx_vmptrst macro VmcsPhysicalAddress
    vmptrst qword ptr [rcx]
    exitm   <>
    endm

endif

ifdef __MACHINEX86_X64

__wbinvd macro
    wbinvd
    endm

endif

ifdef __MACHINEX86

__writefsbyte macro offs, val
    assume fs:nothing
    mov byte ptr fs:[offs],val
    assume fs:error
    retm<>
    endm
__writefsdword macro offs, val
    assume fs:nothing
    mov dword ptr fs:[offs],val
    assume fs:error
    retm<>
    endm
__writefsqword macro offs, val
    assume fs:nothing
    mov eax,dword ptr val
    mov edx,dword ptr val[4]
    mov fs:[offs],eax
    mov fs:[offs+4],edx
    assume fs:error
    retm<>
    endm
__writefsword macro offs, val
    assume fs:nothing
    mov word ptr fs:[offs],val
    assume fs:error
    retm<>
    endm

endif

ifdef __MACHINEX64

__writegsbyte macro offs, val
    mov byte ptr gs:[offs],val
    retm<>
    endm
__writegsdword macro offs, val
    mov dword ptr gs:[offs],val
    retm<>
    endm
__writegsqword macro offs, val
    mov qword ptr gs:[offs],val
    retm<>
    endm
__writegsword macro offs, val
    mov word ptr gs:[offs],val
    retm<>
    endm

endif

ifdef __MACHINEX86_X64

__writemsr  proto :ptr, :ptr
_lgdt       proto :ptr
_sgdt       proto :ptr

__writemsr macro Register, Value
    mov     rax,rdx
    shr     rdx,32
    wrmsr
    exitm   <>
    endm

_rsm macro
    rsm
    retm<>
    endm

_lgdt macro p
    lgdt    qword ptr [rcx]
    exitm   <>
    endm

_sgdt macro p
    sgdt    qword ptr [rcx]
    exitm   <>
    endm

_clac macro
    clac
    exitm   <>
    endm

_stac macro
    stac
    exitm   <>
    endm

_addcarry_u8    proto :byte, :byte, :byte, :ptr
_subborrow_u8   proto :byte, :byte, :byte, :ptr
_addcarry_u16   proto :byte, :word, :word, :ptr
_subborrow_u16  proto :byte, :word, :word, :ptr
_addcarry_u32   proto :byte, :dword, :dword, :ptr
_subborrow_u32  proto :byte, :dword, :dword, :ptr

_addcarry_u8 macro carry, a, b, p
    add     cl,-1
    adc     dl,r8b
    mov     [r9],dl
    setb    al
    retm    <al>
    endm

_subborrow_u8 macro carry, a, b, p
    add     cl,-1
    sbb     dl,r8b
    mov     [r9],dl
    setb    al
    retm    <al>
    endm

_addcarry_u16 macro carry, a, b, p
    add     cl,-1
    adc     dx,r8w
    mov     [r9],dx
    setb    al
    movzx   eax,al
    retm    <eax>
    endm

_subborrow_u16 macro carry, a, b, p
    add     cl,-1
    sbb     dx,r8w
    mov     [r9],dx
    setb    al
    movzx   eax,al
    retm    <eax>
    endm

_addcarry_u32 macro carry, a, b, p
    add     cl,-1
    adc     edx,r8d
    mov     [r9],edx
    setb    al
    movzx   eax,al
    retm    <eax>
    endm

_subborrow_u32 macro carry, a, b, p
    add     cl,-1
    sbb     edx,r8d
    mov     [r9],edx
    setb    al
    movzx   eax,al
    retm    <eax>
    endm

endif

ifdef __MACHINEX64

_addcarry_u64   proto :byte, :qword, :qword, :ptr
_subborrow_u64  proto :byte, :qword, :qword, :ptr

_addcarry_u64 macro carry, a, b, p
    add     cl,-1
    adc     rdx,r8
    mov     [r9],rdx
    setb    al
    movzx   eax,al
    retm    <eax>
    endm

_subborrow_u64 macro carry, a, b, p
    add     cl,-1
    sbb     rdx,r8
    mov     [r9],rdx
    setb    al
    movzx   eax,al
    retm    <eax>
    endm

endif

endif
.pragma cref(pop)
.pragma list(pop)

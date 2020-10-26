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

_BitScanForward proto :ptr, :long_t {
    xor     eax,eax
    bsf     eax,edx
    mov     [rcx],eax
    setne   al
    }

_BitScanReverse proto :ptr, :long_t {
    xor     eax,eax
    bsr     eax,edx
    mov     [rcx],eax
    setne   al
    }

ifdef __MACHINEX64

_BitScanForward64 proto :ptr, :qword {
    xor     eax,eax
    bsf     rax,rdx
    mov     [rcx],eax
    setne   al
    }

_BitScanReverse64 proto :ptr, :qword {
    xor     eax,eax
    bsr     rax,rdx
    mov     [rcx],eax
    setne   al
    }

endif

_InterlockedCompareExchange proto :ptr, :long_t, :long_t {
    mov     eax,r8d
    push    [rcx]
    lock    cmpxchg dword ptr [rcx],edx
    pop     rax
    }

_InterlockedCompareExchange8 proto :ptr, :byte, :byte {
    mov     al,r8b
    push    [rcx]
    lock    cmpxchg byte ptr [rcx],dl
    pop     rax
    }

_InterlockedCompareExchange16 proto :ptr, :word, :word {
    mov     ax,r8w
    push    [rcx]
    lock    cmpxchg word ptr [rcx],dl
    pop     rax
    }

_InterlockedCompareExchange64 proto :ptr, :qword, :qword {
    mov     rax,r8
    push    [rcx]
    lock    cmpxchg size_t ptr [rcx],rdx
    pop     rax
    }

_InterlockedCompareExchangePointer equ <_InterlockedCompareExchange64>

_InterlockedDecrement16 proto :ptr {
    lock    dec word ptr [rcx]
    mov     ax,[rcx]
    }

_InterlockedDecrement proto :ptr {
    lock    dec dword ptr [rcx]
    mov     eax,[rcx]
    }

ifdef __MACHINEX64

_InterlockedDecrement64 proto :ptr {
    lock dec qword ptr [rcx]
    mov rax,[rcx]
    }

endif

_InterlockedIncrement16 proto :ptr {
    lock    inc word ptr [rcx]
    mov     ax,[rcx]
    }

_InterlockedIncrement proto :ptr {
    lock    inc dword ptr [rcx]
    mov     eax,[rcx]
    }

ifdef __MACHINEX64

_InterlockedIncrement64 proto :ptr {
    lock    inc qword ptr [rcx]
    mov     rax,[rcx]
    }

endif

_InterlockedExchangePointer proto :ptr, :ptr {
    xchg    [rcx],rdx
    mov     rax,rdx
    }

__fastfail proto :int_t {
    int     0x29
    }

_bittest proto :ptr, :abs {
    xor     eax,eax
    bt      dword ptr [rcx],_1
    setb    al
    }

_bittestandcomplement proto :ptr, :abs {
    xor     eax,eax
    btc     dword ptr [rcx],_1
    setb    al
    }

_bittestandreset proto :ptr, :abs {
    xor     eax,eax
    btr     dword ptr [rcx],_1
    setb    al
    }

_bittestandset proto :ptr, :abs {
    xor     eax,eax
    bts     dword ptr [rcx],_1
    setb    al
    }

_interlockedbittestandreset proto :ptr, :abs {
    xor     eax,eax
    lock    btr dword ptr [rcx],_1
    setb    al
    }

_byteswap_ulong proto :dword {
    mov     eax,ecx
    bswap   eax
    }

_byteswap_uint64 proto :qword {
    mov     rax,rcx
    bswap   rax
    }

_byteswap_ushort proto :word {
    mov     ax,cx
    ror     ax,8
    }

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

_InterlockedAnd proto fastcall :ptr, :long_t {
    mov     eax,[rcx]
    lock    and [rcx],edx
    }

_InterlockedAnd8 proto fastcall :ptr, :byte {
    movzx   eax,byte ptr [rcx]
    lock    and [rcx],dl
    }

_InterlockedAnd16 proto fastcall :ptr, :word {
    movzx   eax,word ptr [rcx]
    lock    and [rcx],dx
    }

_InterlockedAnd64 proto fastcall :ptr, :qword {
    mov     rax,[rcx]
    lock    and [rcx],rdx
    }

_InterlockedOr proto fastcall :ptr, :long_t {
    mov     eax,[rcx]
    lock    or [rcx],edx
    }

_InterlockedOr8 proto fastcall :ptr, :byte {
    movzx   eax,byte ptr [rcx]
    lock    or [rcx],dl
    }

_InterlockedOr16 proto fastcall :ptr, :word {
    movzx   eax,word ptr [rcx]
    lock    or [rcx],dx
    }

_InterlockedOr64 proto fastcall :ptr, :qword {
    mov     rax,[rcx]
    lock    or [rcx],rdx
    }

_InterlockedXor proto fastcall :ptr, :long_t {
    mov     eax,[rcx]
    lock    or [rcx],edx
    }

_InterlockedXor8 proto fastcall :ptr, :byte {
    movzx   eax,byte ptr [rcx]
    lock    xor [rcx],dl
    }

_InterlockedXor16 proto fastcall :ptr, :word {
    movzx   eax,word ptr [rcx]
    lock    xor [rcx],dx
    }

_InterlockedXor64 proto fastcall :ptr, :qword {
    mov     rax,[rcx]
    lock    xor [rcx],rdx
    }

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

__addfsbyte proto fastcall :ptr, :byte {
    assume  fs:nothing
    add     fs:[rcx],dl
    assume  fs:error
    }

__addfsword proto fastcall :ptr, :word {
    assume  fs:nothing
    add     fs:[rcx],dx
    assume  fs:error
    }

__addfsdword proto fastcall :ptr, :dword {
    assume  fs:nothing
    add     fs:[rcx],edx
    assume  fs:error
    }

__readfsbyte proto fastcall :ptr {
    assume  fs:nothing
    mov al, fs:[rcx]
    assume  fs:error
    }

__readfsdword proto fastcall :ptr {
    assume  fs:nothing
    mov     eax,fs:[rcx]
    assume  fs:error
    }

__readfsqword proto fastcall :ptr {
    assume  fs:nothing
ifdef _WIN64
    mov     rax,fs:[rcx]
else
    mov     eax,fs:[rcx]
    mov     edx,fs:[rcx+4]
endif
    assume  fs:error
    }

__readfsword proto fastcall :ptr {
    assume  fs:nothing
    mov     ax,fs:[rcx]
    assume  fs:error
    }

endif

ifdef __MACHINEX64

__addgsbyte proto fastcall :ptr, :byte {
    add     gs:[rcx],dl
    }
__addgsword proto fastcall :ptr, :word {
    add     gs:[rcx],dx
    }
__addgsdword proto fastcall :ptr, :dword {
    add     gs:[rcx],edx
    }
__addgsqword proto fastcall :ptr, :qword {
    add     gs:[rcx],rdx
    }
__incgsbyte proto fastcall :ptr {
    inc     byte ptr gs:[rcx]
    }
__incgsdword proto fastcall :ptr {
    inc     dword ptr gs:[rcx]
    }
__incgsqword proto fastcall :ptr {
    inc     qword ptr gs:[rcx]
    }
__incgsword proto fastcall :ptr {
    inc     word ptr gs:[rcx]
    }
__readgsbyte proto fastcall :ptr {
    movzx   eax,byte ptr gs:[rcx]
    }
__readgsdword proto fastcall :ptr {
    mov     eax,gs:[rcx]
    }
__readgsqword proto fastcall :ptr {
    mov     rax,gs:[rcx]
    }
__readgsword proto fastcall :ptr {
    movzx   eax,word ptr gs:[rcx]
    }
endif

ifdef __MACHINEX86

__incfsbyte proto fastcall :ptr {
    assume  fs:nothing
    inc     byte ptr fs:[rcx]
    assume  fs:error
    }
__incfsdword proto fastcall :ptr {
    assume  fs:nothing
    inc     dword ptr fs:[rcx]
    assume  fs:error
    }
__incfsword proto fastcall :ptr {
    assume  fs:nothing
    inc     word ptr fs:[rcx]
    assume  fs:error
    }
endif

ifdef __MACHINEX86_X64

__clts macro
    exitm<clts>
    endm

__cpuid proto fastcall :ptr, :int_t {
    push    rsi
    push    rbx
    mov     rsi,rcx
    mov     eax,edx
    xor     ecx,ecx
    cpuid
    mov     [rsi],eax
    mov     [rsi+4],ebx
    mov     [rsi+8],ecx
    mov     [rsi+12],edx
    pop     rbx
    pop     rsi
    }

__cpuidex proto fastcall :ptr_t, :int_t, :int_t {
    push    rsi
    push    rbx
    mov     rsi,this
    mov     eax,_1
    mov     ecx,_2
    cpuid
    mov     [rsi],eax
    mov     [rsi+4],ebx
    mov     [rsi+8],ecx
    mov     [rsi+12],edx
    pop     rbx
    pop     rsi
    }

__emul proto fastcall :int_t, :int_t {
    movsxd  rcx,ecx
    movsxd  rax,edx
    imul    rcx
    }

__emulu proto fastcall :int_t, :int_t {
    mov     eax,b
    mul     rcx
    }

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

__ll_lshift proto fastcall :qword, :dword {
    mov     rax,rcx
    mov     ecx,edx
    shl     rax,cl
    }

__ll_rshift proto fastcall :qword, :dword {
    mov     rax,rcx
    mov     ecx,edx
    sar     rax,cl
    }

__ull_rshift proto fastcall :qword, :dword {
    mov     rax,rcx
    mov     ecx,edx
    shr     rax,cl
    }
endif

ifdef __MACHINEX64

__faststorefence proto :abs {
    lock or dword ptr [rsp],0
    }

endif

ifdef __MACHINEX86_X64

__getcallerseflags macro
    pushfq
    pop     rax
    retm    <eax>
    endm

__halt proto :abs {
    hlt
    }

__inbyte proto :int_t {
    mov     edx,ecx
    in      al,dx
    }

__inword proto :int_t {
    mov     edx,ecx
    in      ax,dx
    }

__indword proto :int_t {
    mov     edx,ecx
    in      eax,dx
    }

__inbytestring proto :int_t, :ptr_t, :int_t {
    push    rdi
    mov     rdi,rdx
    mov     edx,ecx
    mov     ecx,r8d
    rep     insb
    pop     rdi
    }

__indwordstring proto :int_t, :ptr_t, :int_t {
    push    rdi
    mov     rdi,rdx
    mov     edx,ecx
    mov     ecx,r8d
    rep     insw
    pop     rdi
    }

__int2c proto :abs {
    int     0x2c
    }

__invlpg proto :ptr {
    invlpg  byte ptr [rcx]
    }

__lidt proto :ptr {
    lidt    byte ptr [rcx]
    }

__lzcnt proto :int_t {
    lzcnt   eax,ecx
    }

__lzcnt16 proto :int_t {
    lzcnt   eax,ecx
    }

endif

ifdef __MACHINEX64

__lzcnt64 proto :int_t {
    lzcnt   eax,ecx
    }

endif

ifdef __MACHINEX86_X64

__movsb proto :ptr, :ptr, :int_t {
    push    rsi
    push    rdi
    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,r8d
    rep     movsb
    pop     rdi
    pop     rsi
    }

__movsw proto :ptr, :ptr, :int_t {
    push    rsi
    push    rdi
    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,r8d
    rep     movsw
    pop     rdi
    pop     rsi
    }

__movsd proto :ptr, :ptr, :int_t {
    push    rsi
    push    rdi
    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,r8d
    rep     movsd
    pop     rdi
    pop     rsi
    }

__stosb proto :ptr, :byte, :int_t {
    push    rdi
    mov     rdi,rcx
    mov     al,dl
    mov     ecx,r8d
    rep     stosb
    pop     rdi
    }

__stosw proto :ptr, :word, :int_t {
    push    rdi
    mov     rdi,rcx
    mov     ax,dx
    mov     ecx,r8d
    rep     stosw
    pop     rdi
    }

__stosd proto :ptr, :dword, :int_t {
    push    rdi
    mov     rdi,rcx
    mov     eax,edx
    mov     ecx,r8d
    rep     stosd
    pop     rdi
    }

endif

ifdef __MACHINEX64

__movsq proto :ptr, :qword, :int_t {
    push    rsi
    push    rdi
    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,r8d
    rep     movsq
    pop     rdi
    pop     rsi
    }

__stosq proto :ptr, :ptr, :int_t {
    push    rdi
    mov     rdi,rcx
    mov     rax,rdx
    mov     ecx,r8d
    rep     stosd
    pop     rdi
    }

endif

ifdef __MACHINEX86_X64
__nvreg_restore_fence macro
    endm
__nvreg_save_fence macro
    endm
endif

ifdef __MACHINEX86_X64

__outbyte proto :dword, :byte {
    mov     al,dl
    mov     edx,ecx
    out     dx,al
    }

__outword proto :dword, :word {
    mov     eax,edx
    mov     edx,ecx
    out     dx,ax
    }

__outdword proto :dword, :dword {
    mov     eax,edx
    mov     edx,ecx
    out     dx,eax
    }

__outbytestring proto :int_t, :ptr, :int_t {
    push    rdi
    mov     rdi,rdx
    mov     edx,ecx
    mov     ecx,r8d
    rep     outsb
    pop     rdi
    }

__outwordstring proto :int_t, :ptr, :int_t {
    push    rdi
    mov     rdi,rdx
    mov     edx,ecx
    mov     ecx,r8d
    rep     outsw
    pop     rdi
    }

__outdwordstring proto :int_t, :ptr, :int_t {
    push    rdi
    mov     rdi,rdx
    mov     edx,ecx
    mov     ecx,r8d
    rep     outsd
    pop     rdi
    }

endif

ifdef __MACHINEX86_X64

__popcnt proto :dword {
    popcnt  eax,ecx
    }

__popcnt16 proto :word {
    popcnt  ax,cx
    }

endif

ifdef __MACHINEX64

__popcnt64 proto :qword {
    popcnt  rax,rcx
    }

endif

ifdef __MACHINEX86_X64

__rdtsc macro
    rdtsc
    shl     rdx,32
    or      rax,rdx
    retm   <rax>
    endm

__rdtscp proto :ptr {
    push    rdi
    mov     rdi,rcx
    rdtscp
    shl     rdx,32
    or      rax,rdx
    mov     [rdi],ecx
    pop     rdi
    }

__readcr0 proto :abs {
    mov     rax,cr0
    }
__readcr2 proto :abs {
    mov     rax,cr2
    }
__readcr3 proto :abs {
    mov     rax,cr3
    }
__readcr4 proto :abs {
    mov     rax,cr4
    }
__readcr8 proto :abs {
    mov     rax,cr8
    }

__writecr0 proto :ptr {
    mov     cr0,rcx
    }
__writecr2 proto :ptr {
    mov     cr2,rcx
    }
__writecr3 proto :ptr {
    mov     cr3,rcx
    }
__writecr4 proto :ptr {
    mov     cr4,rcx
    }
__writecr8 proto :ptr {
    mov     cr8,rcx
    }

__readdr proto :abs {
    mov     rax,dr&this&
    }

__writedr proto :abs, :ptr {
    mov     dr&this&,rdx
    }

__readeflags macro
ifdef _WIN64
    pushfq
else
    pushfd
endif
    pop     rax
    retm   <rax>
    endm

__writeeflags proto :ptr {
    push    rcx
    popfq
    }

endif

ifdef __MACHINEX64

__shiftleft128 proto :qword, :qword, :dword {
    mov     rax,rcx
    mov     ecx,r8d
    shld    rdx,rax,cl
    sal     rax,cl
    .if cl & 0xC0
        .if cl & 0x80
            xor eax,eax
            xor edx,edx
        .else
            mov rdx,rax
            xor eax,eax
        .endif
    .endif
    }

__shiftright128 proto :qword, :qword, :dword {
    mov     rax,rcx
    mov     ecx,r8d
    shrd    rdx,rax,cl
    sar     rax,cl
    .if cl & 0xC0
        .if cl & 0x80
            xor eax,eax
            xor edx,edx
        .else
            mov rax,rdx
            xor rdx,rdx
        .endif
    .endif
    }

endif

ifdef __MACHINEX86_X64

__readmsr proto :dword {
    rdmsr
    shl     rdx,32
    or      rax,rdx
    }

__readpmc proto :dword {
    rdpmc
    shl     rdx,32
    or      rax,rdx
    }

__segmentlimit proto :dword {
    mov     eax,ecx
    lsl     eax,eax
    }

__sidt proto :ptr {
    sidt    qword ptr [rcx]
    }

__svm_clgi proto :abs {
    clgi
    }

__svm_invlpga proto :qword, :dword {
    mov     rax,rcx
    mov     ecx,edx
    invlpga rax,ecx
    }

__svm_skinit proto :dword {
    mov     eax,ecx
    skinit  eax
    }

__svm_stgi proto :abs {
    stgi
    }

__svm_vmload proto :dword {
    mov     eax,ecx
    vmload  rax
    }

__svm_vmrun proto :dword {
    mov     eax,ecx
    vmrun   rax
    }

__svm_vmsave proto :dword {
    mov     eax,ecx
    vmsave  rax
    }

__ud2 proto :abs {
    ud2
    }

__vmx_off proto :abs {
    vmxoff
    }

endif

ifdef __MACHINEX64

__vmx_on proto :ptr {
    vmxon   qword ptr [rcx]
    }

__vmx_vmclear proto :ptr {
    vmclear qword ptr [rcx]
    }

__vmx_vmlaunch proto :abs {
    vmlaunch
    }

__vmx_vmptrld proto :ptr {
    vmptrld qword ptr [rcx]
    }

__vmx_vmread proto :ptr, :ptr {
    mov     rax,rcx
    mov     rcx,rdx
    vmread  rax,rcx
    }

__vmx_vmresume proto :abs {
    vmresume
    }

__vmx_vmwrite proto :ptr, :ptr {
    mov     rax,rcx
    mov     rcx,rdx
    vmwrite rax,rcx
    }

endif

ifdef __MACHINEX86_X64

__vmx_vmptrst proto :ptr {
    vmptrst qword ptr [rcx]
    }

endif

ifdef __MACHINEX86_X64

__wbinvd proto :abs {
    wbinvd
    }

endif

ifdef __MACHINEX86

__writefsbyte proto fastcall :ptr, :byte {
    assume  fs:nothing
    mov     fs:[rcx],dl
    assume  fs:error
    }

__writefsdword proto fastcall :ptr, :dword {
    assume  fs:nothing
    mov     fs:[rcx],edx
    assume  fs:error
    }

__writefsqword proto fastcall :ptr, :qword {
    assume  fs:nothing
    mov     fs:[rcx],rdx
    assume  fs:error
    }

__writefsword proto fastcall :ptr, :word {
    assume  fs:nothing
    mov     fs:[rcx],dx
    assume  fs:error
    }

endif

ifdef __MACHINEX64

__writegsbyte proto :ptr, :byte {
    mov     gs:[rcx],dl
    }
__writegsdword proto :ptr, :dword {
    mov     gs:[rcx],edx
    }
__writegsqword proto :ptr, :qword {
    mov     gs:[rcx],rdx
    }
__writegsword proto :ptr, :word {
    mov     gs:[rcx],dx
    }

endif

ifdef __MACHINEX86_X64

__writemsr proto :ptr, :ptr {
    mov     rax,rdx
    shr     rdx,32
    wrmsr
    }

_rsm proto :abs {
    rsm
    }

_lgdt proto :ptr {
    lgdt    qword ptr [rcx]
    }

_sgdt proto :ptr {
    sgdt    qword ptr [rcx]
    }

_clac proto :abs {
    clac
    }

_stac proto :abs {
    stac
    }

_addcarry_u8 proto :byte, :byte, :byte, :ptr {
    add     cl,-1
    adc     dl,r8b
    mov     [r9],dl
    setb    al
    }

_subborrow_u8 proto :byte, :byte, :byte, :ptr {
    add     cl,-1
    sbb     dl,r8b
    mov     [r9],dl
    setb    al
    }

_addcarry_u16 proto :byte, :word, :word, :ptr {
    add     cl,-1
    adc     dx,r8w
    mov     [r9],dx
    setb    al
    movzx   eax,al
    }

_subborrow_u16 proto :byte, :word, :word, :ptr {
    add     cl,-1
    sbb     dx,r8w
    mov     [r9],dx
    setb    al
    movzx   eax,al
    }

_addcarry_u32 proto :byte, :dword, :dword, :ptr {
    add     cl,-1
    adc     edx,r8d
    mov     [r9],edx
    setb    al
    movzx   eax,al
    }

_subborrow_u32 proto :byte, :dword, :dword, :ptr {
    add     cl,-1
    sbb     edx,r8d
    mov     [r9],edx
    setb    al
    movzx   eax,al
    }

endif

ifdef __MACHINEX64

_addcarry_u64 proto :byte, :qword, :qword, :ptr {
    add     cl,-1
    adc     rdx,r8
    mov     [r9],rdx
    setb    al
    movzx   eax,al
    }

_subborrow_u64 proto :byte, :qword, :qword, :ptr {
    add     cl,-1
    sbb     rdx,r8
    mov     [r9],rdx
    setb    al
    movzx   eax,al
    }

endif

endif
.pragma cref(pop)
.pragma list(pop)

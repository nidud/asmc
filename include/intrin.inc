.pragma list(push, 0)
.pragma cref(push, 0)
ifndef __INTRIN_H_
define __INTRIN_H_
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

_BitScanForward proto fastcall :ptr, :int_t {
    xor     eax,eax
    bsf     eax,edx
    mov     [rcx],eax
    setne   al
    }

_BitScanReverse proto fastcall :ptr, :int_t {
    xor     eax,eax
    bsr     eax,edx
    mov     [rcx],eax
    setne   al
    }

ifdef __MACHINEX64

_BitScanForward64 proto fastcall :ptr, :qword {
    xor     eax,eax
    bsf     rax,rdx
    mov     [rcx],eax
    setne   al
    }

_BitScanReverse64 proto fastcall :ptr, :qword {
    xor     eax,eax
    bsr     rax,rdx
    mov     [rcx],eax
    setne   al
    }

endif

_InterlockedCompareExchange proto :ptr, :int_t, :int_t {
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

_InterlockedDecrement16 proto watcall :ptr {
    lock    dec word ptr [rax]
    mov     ax,[rax]
    }

_InterlockedDecrement proto watcall :ptr {
    lock    dec dword ptr [rax]
    mov     eax,[rax]
    }

ifdef __MACHINEX64

_InterlockedDecrement64 proto watcall :ptr {
    lock dec qword ptr [rax]
    mov rax,[rax]
    }

endif

_InterlockedIncrement16 proto watcall :ptr {
    lock    inc word ptr [rax]
    mov     ax,[rax]
    }

_InterlockedIncrement proto watcall :ptr {
    lock    inc dword ptr [rax]
    mov     eax,[rax]
    }

ifdef __MACHINEX64

_InterlockedIncrement64 proto watcall :ptr {
    lock    inc qword ptr [rax]
    mov     rax,[rax]
    }

endif

_InterlockedExchangePointer proto watcall :ptr, :ptr {
    xchg    [rax],rdx
    mov     rax,rdx
    }

__fastfail proto fastcall :int_t {
    int     0x29
    }

_bittest proto fastcall :ptr, :abs {
    xor     eax,eax
    bt      dword ptr [rcx],_2
    setb    al
    }

_bittestandcomplement proto fastcall :ptr, :abs {
    xor     eax,eax
    btc     dword ptr [rcx],_2
    setb    al
    }

_bittestandreset proto fastcall :ptr, :abs {
    xor     eax,eax
    btr     dword ptr [rcx],_2
    setb    al
    }

_bittestandset proto fastcall :ptr, :abs {
    xor     eax,eax
    bts     dword ptr [rcx],_2
    setb    al
    }

_interlockedbittestandreset proto fastcall :ptr, :abs {
    xor     eax,eax
    lock    btr dword ptr [rcx],_2
    setb    al
    }

_byteswap_ulong proto watcall :dword {
    bswap   eax
    }

_byteswap_uint64 proto watcall :qword {
    bswap   rax
    }

_byteswap_ushort proto watcall :word {
    ror     ax,8
    }

_disable proto fastcall {
    cli
    }
_enable proto fastcall {
    sti
    }

_rotl proto watcall :uint_t, :abs {
    rol     eax,_2
    }
_rotr proto watcall :uint_t, :abs {
    ror     eax,_2
    }
_lrotl proto watcall :int_t, :abs {
    rol     eax,_2
    }
_lrotr proto watcall :int_t, :abs {
    ror     eax,_2
    }

_rotl8 proto watcall :uchar_t, :abs {
    rol     al,_2
    }
_rotl16 proto watcall :ushort_t, :abs {
    rol     ax,_2
    }
_rotl64 proto watcall :uint64_t, :abs {
    rol     rax,_2
    }
_rotr8 proto watcall :uchar_t, :abs {
    ror     al,_2
    }
_rotr16 proto watcall :ushort_t, :abs {
    ror     ax,_2
    }
_rotr64 proto watcall :uint64_t, :abs {
    ror     rax,_2
    }

ifdef __MACHINEX86

_InterlockedAddLargeStatistic proto watcall :ptr, :uint_t {
    lock add [rax],edx
    .ifc
        lock add [rax+4],0
    .endif
    mov eax,edx
    }

endif

ifdef __MACHINEX64

_InterlockedAnd proto fastcall :ptr, :int_t {
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

_InterlockedOr proto fastcall :ptr, :int_t {
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

_InterlockedXor proto fastcall :ptr, :int_t {
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

__addfsbyte proto watcall :ptr, :byte {
    assume  fs:nothing
    add     fs:[rax],dl
    assume  fs:error
    }

__addfsword proto watcall :ptr, :word {
    assume  fs:nothing
    add     fs:[rax],dx
    assume  fs:error
    }

__addfsdword proto watcall :ptr, :dword {
    assume  fs:nothing
    add     fs:[rax],edx
    assume  fs:error
    }

__readfsbyte proto watcall :ptr {
    assume  fs:nothing
    mov al, fs:[rax]
    assume  fs:error
    }

__readfsdword proto watcall :ptr {
    assume  fs:nothing
    mov     eax,fs:[rax]
    assume  fs:error
    }

__readfsqword proto watcall :ptr {
    assume  fs:nothing
ifdef _WIN64
    mov     rax,fs:[rax]
else
    mov     edx,fs:[rax+4]
    mov     eax,fs:[rax]
endif
    assume  fs:error
    }

__readfsword proto watcall :ptr {
    assume  fs:nothing
    mov     ax,fs:[rax]
    assume  fs:error
    }

endif

ifdef __MACHINEX64

__addgsbyte proto watcall :ptr, :byte {
    add     gs:[rax],dl
    }
__addgsword proto watcall :ptr, :word {
    add     gs:[rax],dx
    }
__addgsdword proto watcall :ptr, :dword {
    add     gs:[rax],edx
    }
__addgsqword proto watcall :ptr, :qword {
    add     gs:[rax],rdx
    }

__incgsbyte proto watcall :ptr {
    inc     byte ptr gs:[rax]
    }
__incgsdword proto watcall :ptr {
    inc     dword ptr gs:[rax]
    }
__incgsqword proto watcall :ptr {
    inc     qword ptr gs:[rax]
    }
__incgsword proto watcall :ptr {
    inc     word ptr gs:[rax]
    }

__readgsbyte proto watcall :ptr {
    movzx   eax,byte ptr gs:[rax]
    }
__readgsword proto watcall :ptr {
    movzx   eax,word ptr gs:[rax]
    }
__readgsdword proto watcall :ptr {
    mov     eax,gs:[rax]
    }
__readgsqword proto watcall :ptr {
    mov     rax,gs:[rax]
    }
endif

ifdef __MACHINEX86

__incfsbyte proto watcall :ptr {
    assume  fs:nothing
    inc     byte ptr fs:[rax]
    assume  fs:error
    }
__incfsdword proto watcall :ptr {
    assume  fs:nothing
    inc     dword ptr fs:[rax]
    assume  fs:error
    }
__incfsword proto watcall :ptr {
    assume  fs:nothing
    inc     word ptr fs:[rax]
    assume  fs:error
    }
endif

ifdef __MACHINEX86_X64

__clts macro
    exitm<clts>
    endm

__cpuidex proto asmcall :ptr, :int_t, :int_t {
ifdef _WIN64
    mov     r8,rax
    mov     r9,rbx
    mov     eax,edx
    cpuid
    mov     [r8+0x0],eax
    mov     [r8+0x4],ebx
    mov     [r8+0x8],ecx
    mov     [r8+0xC],edx
    mov     rbx,r9
else
    push    esi
    push    ebx
    mov     esi,eax
    mov     eax,edx
    cpuid
    mov     [esi+0x0],eax
    mov     [esi+0x4],ebx
    mov     [esi+0x8],ecx
    mov     [esi+0xC],edx
    pop     ebx
    pop     esi
endif
    }

__cpuid macro p, i
    exitm<__cpuidex(p, i, 0)>
    endm

__emul proto watcall :int_t, :int_t {
ifdef _WIN64
    movsxd  rdx,edx
    movsxd  rax,eax
endif
    imul    rdx
    }

__emulu proto watcall :int_t, :int_t {
    mul     rdx
    }

endif

ifndef __MUL128_DEFINED
define __MUL128_DEFINED
ifdef _WIN64
_mul128 proto asmcall :qword, :qword, :ptr qword {
    mul rdx
    .if rcx
        mov [rcx],rdx
    .endif
    }
else
_mul128 proto :qword, :qword, :ptr qword
endif
endif

_umul128 equ <_mul128>

ifdef _WIN64

umul256 proto syscall :oword, :oword, :ptr

_mul256 proto fastcall :ptr, :ptr, :ptr {
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
    }
endif

ifdef __MACHINEX86_X64

__ll_lshift proto watcall :qword, :dword {
    mov     ecx,edx
    shl     rax,cl
    }

__ll_rshift proto watcall :qword, :dword {
    mov     ecx,edx
    sar     rax,cl
    }

__ull_rshift proto watcall :qword, :dword {
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

__getcallerseflags proto fastcall {
    pushfq
    pop     rax
    }

__halt proto :abs {
    hlt
    }

__inbyte proto fastcall :int_t {
    mov     edx,ecx
    in      al,dx
    }

__inword proto fastcall :int_t {
    mov     edx,ecx
    in      ax,dx
    }

__indword proto fastcall :int_t {
    mov     edx,ecx
    in      eax,dx
    }

__inbytestring proto asmcall :int_t, :ptr_t, :int_t {
    xchg    rax,rdx
    xchg    rax,rdi
    rep     insb
    mov     rdi,rax
    }

__indwordstring proto asmcall :int_t, :ptr_t, :int_t {
    xchg    rax,rdx
    xchg    rax,rdi
    rep     insw
    mov     rdi,rax
    }

__int2c proto fastcall {
    int     0x2c
    }

__invlpg proto fastcall :ptr {
    invlpg  byte ptr [rcx]
    }

__lidt proto fastcall :ptr {
    lidt    byte ptr [rcx]
    }

__lzcnt proto fastcall :int_t {
    lzcnt   eax,ecx
    }

__lzcnt16 proto fastcall :int_t {
    lzcnt   eax,ecx
    }

endif

ifdef __MACHINEX64

__lzcnt64 proto fastcall :int_t {
    lzcnt   eax,ecx
    }

endif

ifndef __MOVSB_DEFINED
define __MOVSB_DEFINED
__movsb proto asmcall :ptr, :ptr, :sdword {
    xchg    rax,rdi
    xchg    rdx,rsi
    rep     movsb
    mov     rdi,rax
    mov     rsi,rdx
    }
__movsw proto asmcall :ptr, :ptr, :sdword {
    xchg    rax,rdi
    xchg    rdx,rsi
    rep     movsw
    mov     rdi,rax
    mov     rsi,rdx
    }
__movsd proto asmcall :ptr, :ptr, :sdword {
    xchg    rax,rdi
    xchg    rdx,rsi
    rep     movsd
    mov     rdi,rax
    mov     rsi,rdx
    }
__stosb proto asmcall :ptr, :byte, :sdword {
    xchg    rdx,rax
    xchg    rdx,rdi
    rep     stosb
    mov     rdi,rdx
    }
__stosw proto asmcall :ptr, :word, :sdword {
    xchg    rdx,rax
    xchg    rdx,rdi
    rep     stosw
    mov     rdi,rdx
    }
__stosd proto asmcall :ptr, :dword, :sdword {
    xchg    rdx,rax
    xchg    rdx,rdi
    rep     stosd
    mov     rdi,rdx
    }
ifdef _WIN64
__movsq proto asmcall :ptr, :ptr, :sdword {
    xchg    rax,rdi
    xchg    rdx,rsi
    rep     movsq
    mov     rdi,rax
    mov     rsi,rdx
    }
__stosq proto asmcall :ptr, :qword, :sdword {
    xchg    rdx,rax
    xchg    rdx,rdi
    rep     stosq
    mov     rdi,rdx
    }
endif
endif

ifdef __MACHINEX86_X64
__nvreg_restore_fence macro
    endm
__nvreg_save_fence macro
    endm
endif

ifdef __MACHINEX86_X64

__outbyte proto watcall :dword, :byte {
    xchg    eax,edx
    out     dx,al
    }
__outword proto watcall :dword, :word {
    xchg    eax,edx
    out     dx,ax
    }
__outdword proto watcall :dword, :dword {
    xchg    eax,edx
    out     dx,eax
    }

__outbytestring proto asmcall :int_t, :ptr, :int_t {
    xchg    rax,rdx
    xchg    rax,rdi
    rep     outsb
    mov     rdi,rax
    }
__outwordstring proto asmcall :int_t, :ptr, :int_t {
    xchg    rax,rdx
    xchg    rax,rdi
    rep     outsw
    mov     rdi,rax
    }
__outdwordstring proto asmcall :int_t, :ptr, :int_t {
    xchg    rax,rdx
    xchg    rax,rdi
    rep     outsd
    mov     rdi,rax
    }

endif

ifdef __MACHINEX86_X64

__popcnt proto watcall :dword {
    popcnt  eax,eax
    }

__popcnt16 proto watcall :word {
    popcnt  ax,ax
    }

endif

ifdef __MACHINEX64

__popcnt64 proto watcall :qword {
    popcnt  rax,rax
    }

endif

ifdef __MACHINEX86_X64

__rdtsc proto fastcall {
    rdtsc
    shl     rdx,32
    or      rax,rdx
    }

__rdtscp proto fastcall :ptr {
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

__writecr0 proto watcall :ptr {
    mov     cr0,rax
    }
__writecr2 proto watcall :ptr {
    mov     cr2,rax
    }
__writecr3 proto watcall :ptr {
    mov     cr3,rax
    }
__writecr4 proto watcall :ptr {
    mov     cr4,rax
    }
__writecr8 proto watcall :ptr {
    mov     cr8,rax
    }

__readdr proto :abs {
    mov     rax,dr&_1&
    }

__writedr proto :abs, :ptr {
    mov     dr&_1&,rdx
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

__writeeflags proto watcall :ptr {
    push    rax
    popfq
    }

endif

ifdef __MACHINEX64

ifndef __SHIFT128_DEFINED
define __SHIFT128_DEFINED
__shiftleft128 proto asmcall :qword, :qword, :dword {
    shld rdx,rax,cl
    sal rax,cl
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

__shiftright128 proto asmcall :qword, :qword, :dword {
    shrd rdx,rax,cl
    sar rax,cl
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
endif

ifdef __MACHINEX86_X64

__readmsr proto fastcall :dword {
    rdmsr
    shl     rdx,32
    or      rax,rdx
    }

__readpmc proto fastcall :dword {
    rdpmc
    shl     rdx,32
    or      rax,rdx
    }

__segmentlimit proto watcall :dword {
    lsl     eax,eax
    }

__sidt proto watcall :ptr {
    sidt    qword ptr [rax]
    }

__svm_clgi proto :abs {
    clgi
    }

__svm_invlpga proto watcall :qword, :dword {
    mov     ecx,edx
    invlpga rax,ecx
    }

__svm_skinit proto watcall :dword {
    skinit  eax
    }

__svm_stgi proto :abs {
    stgi
    }

__svm_vmload proto watcall :dword {
    vmload  rax
    }

__svm_vmrun proto watcall :dword {
    vmrun   rax
    }

__svm_vmsave proto watcall :dword {
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

__vmx_on proto watcall :ptr {
    vmxon   qword ptr [rax]
    }

__vmx_vmclear proto watcall :ptr {
    vmclear qword ptr [rax]
    }

__vmx_vmlaunch proto :abs {
    vmlaunch
    }

__vmx_vmptrld proto watcall :ptr {
    vmptrld qword ptr [rax]
    }

__vmx_vmread proto watcall :ptr, :ptr {
    mov     rcx,rdx
    vmread  rax,rcx
    }

__vmx_vmresume proto :abs {
    vmresume
    }

__vmx_vmwrite proto watcall :ptr, :ptr {
    mov     rcx,rdx
    vmwrite rax,rcx
    }

endif

ifdef __MACHINEX86_X64

__vmx_vmptrst proto watcall :ptr {
    vmptrst qword ptr [rax]
    }

endif

ifdef __MACHINEX86_X64

__wbinvd proto :abs {
    wbinvd
    }

endif

ifdef __MACHINEX86

__writefsbyte proto watcall :ptr, :byte {
    assume  fs:nothing
    mov     fs:[rax],dl
    assume  fs:error
    }

__writefsdword proto watcall :ptr, :dword {
    assume  fs:nothing
    mov     fs:[rax],edx
    assume  fs:error
    }

__writefsqword proto watcall :ptr, :qword {
    assume  fs:nothing
    mov     fs:[rax],rdx
    assume  fs:error
    }

__writefsword proto watcall :ptr, :word {
    assume  fs:nothing
    mov     fs:[rax],dx
    assume  fs:error
    }

endif

ifdef __MACHINEX64

__writegsbyte proto watcall :ptr, :byte {
    mov     gs:[rax],dl
    }
__writegsdword proto watcall :ptr, :dword {
    mov     gs:[rax],edx
    }
__writegsqword proto watcall :ptr, :qword {
    mov     gs:[rax],rdx
    }
__writegsword proto watcall :ptr, :word {
    mov     gs:[rax],dx
    }

endif

ifdef __MACHINEX86_X64

__writemsr proto watcall :ptr, :ptr {
    shr     rdx,32
    wrmsr
    }

_rsm proto :abs {
    rsm
    }

_lgdt proto watcall :ptr {
    lgdt    qword ptr [rax]
    }

_sgdt proto watcall :ptr {
    sgdt    qword ptr [rax]
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

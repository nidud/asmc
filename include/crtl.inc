.pragma list(push, 0)

ifndef __CRTL_INC
define __CRTL_INC

ifndef __LIBC_INC
 include libc.inc
endif

.pragma comment(lib, libc)

define _EXEC_BAT 1
define _EXEC_COM 2
define _EXEC_EXE 3
define _EXEC_CMD 4

externdef       OldErrorMode:dword

__isexec        proto __cdecl :string_t
__setenvp       proto __cdecl :string_t
__wsetenvp      proto __cdecl :wstring_t
__coreleft      proto __cdecl
__xtoi          proto __cdecl :string_t
__xtoi64        proto __cdecl :string_t

strfn           proto __cdecl :string_t
strext          proto __cdecl :string_t
strfcat         proto __cdecl :string_t, :string_t, :string_t
memxchg         proto __cdecl :string_t, :string_t, :size_t

__copy_path_to_wide_string proto __cdecl :ptr char_t, :ptr ptr wchar_t

; GCC

ifdef _AMD64_

__divti3        proto __cdecl :int128_t, :int128_t
__udivti3       proto __cdecl :uint128_t, :uint128_t
__modti3        proto __cdecl :int128_t, :int128_t
__umodti3       proto __cdecl :uint128_t, :uint128_t

endif

; Microsoft
;
; EDX:EAX, CL, C decoration
;
_allshr         proto __cdecl ; edx:eax >> cl
_aullshr        proto __cdecl ; edx:eax >> cl
__ullshr        proto __cdecl ; edx:eax >> cl
_allshl         proto __cdecl ; edx:eax << cl
__llshl         proto __cdecl ; edx:eax << cl
;
; STDCALL calling convention, C decoration
;
__lldiv         proto __cdecl ; :int64_t,  :int64_t
_alldiv         proto __cdecl ; :int64_t,  :int64_t
__llmul         proto __cdecl ; :int64_t,  :int64_t
_allmul         proto __cdecl ; :int64_t,  :int64_t
_allrem         proto __cdecl ; :int64_t,  :int64_t
_aulldiv        proto __cdecl ; :uint64_t, :uint64_t
__ullmod        proto __cdecl ; :uint64_t, :uint64_t
_aullrem        proto __cdecl ; :uint64_t, :uint64_t

; Watcom
;
; WATCALL calling convention, C decoration
;
_I8D            proto __cdecl ; :int64_t,  :int64_t
_U8D            proto __cdecl ; :uint64_t, :uint64_t ; edx:eax / ecx:ebx --> edx:eax.ecx
_U8M            proto __cdecl ; :uint64_t, :uint64_t ; edx:eax * ecx:ebx --> ecx:ebx:edx:eax
_I8M            proto __cdecl ; :int64_t,  :int64_t  ; edx:eax * ecx:ebx --> ecx:ebx:edx:eax
_I8LS           proto __cdecl ; :int64_t,  :int_t    ; edx:eax << bl
_U8LS           proto __cdecl ; :uint64_t, :int_t    ; edx:eax << bl
_I8RS           proto __cdecl ; :int64_t,  :int_t    ; edx:eax >> bl
_U8RS           proto __cdecl ; :uint64_t, :int_t    ; edx:eax >> bl

ifdef _WIN64

alldiv proto watcall :int64_t, :int64_t {
    mov     rcx,rdx
    cdq
    idiv    rcx
    }
aulldiv proto watcall :uint64_t, :uint64_t {
    mov     rcx,rdx
    xor     edx,edx
    div     rcx
    }
allmul proto watcall :int64_t, :int64_t {
    imul    rdx
    }
allshr proto watcall :int64_t, :int_t {
    mov     ecx,edx
    sar     rax,cl
    }
aullshr proto watcall :uint64_t, :int_t {
    mov     ecx,edx
    shr     rax,cl
    }
allshl proto watcall :int64_t, :int_t {
    mov     ecx,edx
    shl     rax,cl
    }
allrem proto watcall :int64_t, :int64_t {
    alldiv(_1, _2)
    mov     rax,rdx
    }
aullrem proto watcall :uint64_t, :uint64_t {
    aulldiv(_1, _2)
    mov     rax,rdx
    }

else

alldiv proto watcall :int64_t, :int64_t {
    call    _I8D
    }
aulldiv proto watcall :uint64_t, :uint64_t {
    call    _U8D
    }
allmul proto watcall :int64_t, :int64_t {
    call    _I8M
    }
allshr proto watcall :int64_t, :int_t {
    call    _I8RS
    }
aullshr proto watcall :uint64_t, :int_t {
    call    _U8RS
    }
allshl proto watcall :int64_t, :int_t {
    call    _U8LS
    }
allrem proto watcall :int64_t, :int64_t {
    call    _I8D
    mov     eax,ebx
    mov     edx,ecx
    }
aullrem proto watcall :uint64_t, :uint64_t {
    call    _U8D
    mov     eax,ebx
    mov     edx,ecx
    }

endif

endif

.pragma list(pop)

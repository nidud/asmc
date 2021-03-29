include Windows.inc
include crtdbg.inc
include intrin.inc
include malloc.inc
include stdlib.inc
include vcruntime.inc

extern __ImageBase:IMAGE_DOS_HEADER

ifdef _M_CEE
    _CRT_INTEROPSERVICES_DLLIMPORT macro _DllName , _EntryPoint , _CallingConvention
        exitm<>
        endm
    _CRT_SUPPRESS_UNMANAGED_CODE_SECURITY macro
        exitm<>
        endm
    _CRT_CALLING_CONVENTION_CDECL macro
        exitm<>
        endm
    _CRT_CALLING_CONVENTION_WINAPI macro
        exitm<>
        endm
    _CRT_RELIABILITY_CONTRACT macro
        exitm<>
        endm
    _CRT_ASSERT_UNMANAGED_CODE_ATTRIBUTE macro
        exitm<>
        endm
    _CRT_SECURITYCRITICAL_ATTRIBUTE macro
        exitm<>
        endm
    _CRT_SECURITYSAFECRITICAL_ATTRIBUTE macro
        exitm<>
        endm
else
    _CRT_INTEROPSERVICES_DLLIMPORT macro _DllName , _EntryPoint , _CallingConvention
        exitm<>
        endm
    _CRT_SUPPRESS_UNMANAGED_CODE_SECURITY macro
        exitm<>
        endm
    _CRT_CALLING_CONVENTION_CDECL macro
        exitm<>
        endm
    _CRT_CALLING_CONVENTION_WINAPI macro
        exitm<>
        endm
    _CRT_RELIABILITY_CONTRACT macro
        exitm<>
        endm
    _CRT_ASSERT_UNMANAGED_CODE_ATTRIBUTE macro
        exitm<>
        endm
    _CRT_SECURITYCRITICAL_ATTRIBUTE macro
        exitm<>
        endm
    _CRT_SECURITYSAFECRITICAL_ATTRIBUTE macro
        exitm<>
        endm
endif

ifdef _M_IX86

    undef _InterlockedExchangePointer
    undef _InterlockedCompareExchangePointer

    _InterlockedExchangePointer macro target, value
        exitm<_InterlockedExchange(target, value)>
        endm

    _InterlockedCompareExchangePointer macro target, exchange, comparand
        exitm<_InterlockedCompareExchange(target, exchange, comparand)>
        endm

endif

_BEGIN_SECURE_CRT_DEPRECATION_DISABLE macro
    .pragma warning(push)
    .pragma warning(disable:4996)
    .pragma warning(disable:25025)
    .pragma warning(disable:28719)
    exitm<>
    endm

_END_SECURE_CRT_DEPRECATION_DISABLE macro
    .pragma warning(pop)
    exitm<>
    endm

CRT_WARNING_DISABLE_PUSH macro x, y
    .pragma warning(push)
    .pragma warning(disable: x)
    exitm<>
    endm

CRT_WARNING_POP macro
    .pragma warning(pop)
    exitm<>
    endm

if 0

.pragma section(".CRT$XCA",    long, read) ;; First C++ Initializer
.pragma section(".CRT$XCAA",   long, read) ;; Startup C++ Initializer
.pragma section(".CRT$XCZ",    long, read) ;; Last C++ Initializer

.pragma section(".CRT$XDA",    long, read) ;; First Dynamic TLS Initializer
.pragma section(".CRT$XDZ",    long, read) ;; Last Dynamic TLS Initializer

.pragma section(".CRT$XIA",    long, read) ;; First C Initializer
.pragma section(".CRT$XIAA",   long, read) ;; Startup C Initializer
.pragma section(".CRT$XIAB",   long, read) ;; PGO C Initializer
.pragma section(".CRT$XIAC",   long, read) ;; Post-PGO C Initializer
.pragma section(".CRT$XIC",    long, read) ;; CRT C Initializers
.pragma section(".CRT$XIYA",   long, read) ;; VCCorLib Threading Model Initializer
.pragma section(".CRT$XIYAA",  long, read) ;; XAML Designer Threading Model Override Initializer
.pragma section(".CRT$XIYB",   long, read) ;; VCCorLib Main Initializer
.pragma section(".CRT$XIZ",    long, read) ;; Last C Initializer

.pragma section(".CRT$XLA",    long, read) ;; First Loader TLS Callback
.pragma section(".CRT$XLC",    long, read) ;; CRT TLS Constructor
.pragma section(".CRT$XLD",    long, read) ;; CRT TLS Terminator
.pragma section(".CRT$XLZ",    long, read) ;; Last Loader TLS Callback

.pragma section(".CRT$XPA",    long, read) ;; First Pre-Terminator
.pragma section(".CRT$XPB",    long, read) ;; CRT ConcRT Pre-Terminator
.pragma section(".CRT$XPX",    long, read) ;; CRT Pre-Terminators
.pragma section(".CRT$XPXA",   long, read) ;; CRT stdio Pre-Terminator
.pragma section(".CRT$XPZ",    long, read) ;; Last Pre-Terminator

.pragma section(".CRT$XTA",    long, read) ;; First Terminator
.pragma section(".CRT$XTZ",    long, read) ;; Last Terminator

.pragma section(".CRTMA$XCA",  long, read) ;; First Managed C++ Initializer
.pragma section(".CRTMA$XCZ",  long, read) ;; Last Managed C++ Initializer

.pragma section(".CRTVT$XCA",  long, read) ;; First Managed VTable Initializer
.pragma section(".CRTVT$XCZ",  long, read) ;; Last Managed VTable Initializer

.pragma section(".rdata$T",    long, read)

.pragma section(".rtc$IAA",    long, read) ;; First RTC Initializer
.pragma section(".rtc$IZZ",    long, read) ;; Last RTC Initializer

.pragma section(".rtc$TAA",    long, read) ;; First RTC Terminator
.pragma section(".rtc$TZZ",    long, read) ;; Last RTC Terminator

endif

_CRTALLOC macro x
    exitm<>;__declspec(allocate(x))>
    endm

ifndef _M_CEE
    CALLBACKC(_PVFV)
    CALLBACKC(_PIFV)

    externdef _CRTALLOC(".CRT$XIA") __xi_a:_PIFV ;; First C Initializer
    externdef _CRTALLOC(".CRT$XIZ") __xi_z:_PIFV ;; Last C Initializer
    externdef _CRTALLOC(".CRT$XCA") __xc_a:_PVFV ;; First C++ Initializer
    externdef _CRTALLOC(".CRT$XCZ") __xc_z:_PVFV ;; Last C++ Initializer
    externdef _CRTALLOC(".CRT$XPA") __xp_a:_PVFV ;; First Pre-Terminator
    externdef _CRTALLOC(".CRT$XPZ") __xp_z:_PVFV ;; Last Pre-Terminator
    externdef _CRTALLOC(".CRT$XTA") __xt_a:_PVFV ;; First Terminator
    externdef _CRTALLOC(".CRT$XTZ") __xt_z:_PVFV ;; Last Terminator
endif



ifdef __cplusplus
endif

ifdef _DEBUG

    _NORMAL_BLOCK    equ 1
    _CRT_BLOCK       equ 2

    _calloc_crt macro c, s
        exitm<_calloc_dbg(c, s, _CRT_BLOCK, __FILE__, __LINE__)>
        endm
    _free_crt macro p
        exitm<_free_dbg(p, _CRT_BLOCK)>
        endm
    _malloc_crt macro s
        exitm<_malloc_dbg(s, _CRT_BLOCK, __FILE__, __LINE__)>
        endm
    _msize_crt macro p
        exitm<_msize_dbg(p, _CRT_BLOCK)>
        endm
    _recalloc_crt macro p, c, s
        exitm<_recalloc_dbg(p, c, s, _CRT_BLOCK, __FILE__, __LINE__)>
        endm
    _realloc_crt macro p, s
        exitm<_realloc_dbg(p, s, _CRT_BLOCK, __FILE__, __LINE__)>
        endm
    _malloca_crt macro size
        exitm<>
        endm

else

    _calloc_crt   equ <_calloc_base>
    _free_crt     equ <_free_base>
    _malloc_crt   equ <_malloc_base>
    _realloc_crt  equ <_realloc_base>

    ifdef _CRT_WINDOWS
        _msize_crt    equ <_msize_base>
        _recalloc_crt equ <_recalloc_base>
    else
        _msize_crt    equ <_msize>
        _recalloc_crt equ <_recalloc>
    endif

    _malloca_crt macro size
        .pragma warning(suppress: 6255)
        .if _MallocaComputeSize(size)
            .if _MallocaComputeSize(size) <= _ALLOCA_S_THRESHOLD
                _MarkAllocaS(_alloca(_MallocaComputeSize(size)), _ALLOCA_S_STACK_MARKER)
            .else
                _MarkAllocaS(_malloc_crt(_MallocaComputeSize(size)), _ALLOCA_S_HEAP_MARKER))
            .endif
        .endif
        exitm<>
        endm

endif

.pragma warning(push)
.pragma warning(disable: 6014)

_freea_crt proto :ptr {

    .if _1

        sub _1,_ALLOCA_S_MARKER_SIZE
        mov eax,[_1]
        .if eax == _ALLOCA_S_HEAP_MARKER

            _free_crt(_1)

        .elseif eax != _ALLOCA_S_STACK_MARKER

            .assert( "Corrupted pointer passed to _freea" ==  0 )
        .endif
    .endif
    }

.pragma warning(pop)

ifdef __cplusplus

    .template __crt_internal_free_policy

        .inline throw :ptr {
            _free_crt(_1)
            }
        .ends

    .template __crt_public_free_policy

        .inline throw :ptr {
            free(_1)
            }
        .ends

    .template __crt_unique_heap_ptr : public __crt_internal_free_policy

        _p ptr_t ?

        .inline __crt_unique_heap_ptr :abs=<NULL>, :vararg {
            this.typeid(__crt_unique_heap_ptr, _1)(_1)
            }
        .inline __crt_unique_heap_ptrIMM32 :abs, :vararg {
            mov this._p,_1
            }
        .inline __crt_unique_heap_ptrP__crt_unique_heap_ptr :ptr __crt_unique_heap_ptr, :vararg {
            mov this._p,[_1].__crt_unique_heap_ptr._p
            mov [_1].__crt_unique_heap_ptr._p,NULL
            }

        .inline Free :ptr, :vararg {
            this.throw(_1)
            }

        .inline detach :vararg {
            mov rax,this._p
            mov this._p,NULL
            }

        .inline attach :ptr, :vararg {
            mov rax,this._p
            mov this._p,rdx
            this.Free(rax)
            }

        .inline release :vararg {
            mov rax,this._p
            mov this._p,NULL
            this.Free(rax)
            }

        .inline is_valid :vararg {
            xor eax,eax
            mov edx,1
            cmp rax,this._p
            cmovne eax,edx
            }

        .inline bool :vararg {
            this.is_valid()
            }

        .inline get :vararg {
            mov rax,this._p
            }

        .inline get_address_of :vararg {
            lea rax,this._p
            }

        .inline release_and_get_address_of :vararg {

            this.release()
            lea rax,this._p
            }

        .ends

    ;; An internal-use scoped smart pointer for memory allocated by _malloca_crt.
    .template __crt_scoped_stack_ptr_tag

        _p ptr_t ?

        .inline __crt_scoped_stack_ptr_tag :ptr {
            mov this._p,_1
            }
        .ends


    .template __crt_scoped_stack_ptr

        _p ptr_t ?

        .inline __crt_scoped_stack_ptr :ptr, :vararg {
            mov this._p,_1
            }

        .inline Release :vararg {
            _freea_crt([this].__crt_scoped_stack_ptr._p)
            }

        .inline get {
            mov rax,[this].__crt_scoped_stack_ptr._p
            }

        .inline bool {
            xor eax,eax
            mov edx,1
            cmp rax,this._p
            cmovne eax,edx
            }
        .ends

    _calloc_crt_t macro t, n
        exitm<_calloc_crt((n), sizeof(t))
        endm
    _malloc_crt_t macro t, n
        exitm<_malloc_crt((n) * sizeof(t))>
    _recalloc_crt_t macro t, p, n
        exitm<_recalloc_crt((p), (n),  sizeof(t))>
        endm
    _malloca_crt_t macro t, n
        exitm<_malloca_crt((n) * sizeof(t))>
        endm

    .enum : int_t {
        __crt_maximum_pointer_shift = sizeof(uintptr_t) * 8
        }

    __crt_rotate_pointer_value proto :uint_t, :int_t {
        RotateRight32(_1, _2)
        }

    __crt_rotate_pointer_value proto :uint_t, :int_t {
        RotateRight64(_1, _2)
        }

    __crt_fast_decode_pointer proto :ptr {
        mov rax,__security_cookie
        xor rcx,rax
        xor edx,edx
        div __crt_maximum_pointer_shift
        __crt_rotate_pointer_value(rcx, rdx)
        }

    __crt_fast_encode_pointer proto :ptr {

        mov rax,__security_cookie
        xor edx,edx
        div __crt_maximum_pointer_shift
        mov rax,__crt_maximum_pointer_shift
        sub rax,rdx
        __crt_rotate_pointer_value(rcx, rax)
        xor rax,__security_cookie
        }

    .template __crt_fast_encoded_nullptr_t
        .inline throw {
            __crt_fast_encode_pointer(0)
            }
        .ends

    __crt_fast_encode_pointer proto {
        __crt_fast_encoded_nullptr_t()
        }


    __crt_get_proc_address proto :HMODULE, :ptr {
        GetProcAddress(_1, _2)
        }

    __crt_interlocked_exchange_pointer proto :ptr, :abs {
        _InterlockedExchangePointer(_1, _2)
        }

    __crt_interlocked_compare_exchange proto :ptr, :abs, :abs {
        static_assert(sizeof(_1) == sizeof(LONG), "Type being compared must be same size as a LONG.")
        _InterlockedCompareExchange(_1, _2, _3)
        }

    __crt_interlocked_compare_exchange_pointer proto :ptr, :abs, :abs {
        _InterlockedCompareExchangePointer(_1, _2, _3)
        }

    ifndef _M_CEE_PURE

            __crt_interlocked_memory_barrier macro
        ifdef _M_ARM
                exitm<__dmb(_ARM_BARRIER_ISH)>
        elseifdef _M_ARM64
                exitm<__dmb(_ARM64_BARRIER_ISH)>
        endif
                endm

        __crt_interlocked_read_32 macro target

            .new result:ptr
            if defined(_M_IX86) or defined(_M_X64)
            mov result,[target]
            _ReadWriteBarrier()
            mov rax,result
            elseif defined(_M_ARM) or defined(_M_ARM64)
            mov result,__iso_volatile_load32(target)
            __crt_interlocked_memory_barrier()
            mov rax,result
            else
            .err <Unsupported architecture>
            endif
            exitm<>
            endm

        ifdef _WIN64
            __crt_interlocked_read_64 macro target
            .new result:ptr
            ifdef _M_X64
                mov result,[target]
                _ReadWriteBarrier()
                mov rax,result
            elseifdef _M_ARM64
                mov result,__iso_volatile_load64(target)
                __crt_interlocked_memory_barrier()
                mov rax,result
            else
                .err <Unsupported architecture>
            endif
            exitm<>
            endm
        endif

        __crt_interlocked_read macro target
            static_assert(sizeof(target) == sizeof(int_t), "Type being read must be 32 bits in size.")
            __crt_interlocked_read_32(target)
            exitm<>
            endm


        __crt_interlocked_read_pointer macro target
        ifdef _WIN64
            __crt_interlocked_read_64(target)
        else
            __crt_interlocked_read_32(target)
        endif
            exitm<>
            endm

    endif ;; _M_CEE_PURE
endif ;; __cplusplus



_CRT_DEBUGGER_IGNORE             equ -1
_CRT_DEBUGGER_GSFAILURE          equ 1
_CRT_DEBUGGER_INVALIDPARAMETER   equ 2
_CRT_DEBUGGER_ABORT              equ 3

__crt_debugger_hook proto __cdecl :int_t
_CRT_DEBUGGER_HOOK equ <__crt_debugger_hook>

_INVALID_PARAMETER macro expr
ifdef _DEBUG
    exitm<_invalid_parameter_noinfo(expr, __FUNCTIONW__, __FILEW__, __LINE__, 0)>
else
    exitm<_invalid_parameter_noinfo()>
endif
    endm

_VALIDATE_CLEAR_OSSERR_RETURN macro expr, errorcode, retexpr

    _ASSERT_EXPR((expr), _CRT_WIDE(expr))

    .if !(expr)
        mov _doserrno,0
        mov errno,errorcode
        _INVALID_PARAMETER(_CRT_WIDE(expr))
        .return retexpr
    .endif
    exitm<>
    endm

_VALIDATE_CLEAR_OSSERR_RETURN_ERRCODE macro expr, errorcode

    _ASSERT_EXPR((expr), _CRT_WIDE(expr))

    .if !(expr)

        mov _doserrno,0
        mov errno,errorcode
        _INVALID_PARAMETER(_CRT_WIDE(expr))
        .return errorcode;
    .endif
    exitm<>
    endm

_VALIDATE_RETURN macro expr, errorcode, retexpr

    _ASSERT_EXPR((expr), _CRT_WIDE(expr))

    .if !(expr)

        mov _doserrno,0
        mov errno,errorcode
        _INVALID_PARAMETER(_CRT_WIDE(expr))
        .return retexpr
    .endif
    exitm<>
    endm

_VALIDATE_RETURN_ERRCODE macro expr, errorcode

    _ASSERT_EXPR((expr), _CRT_WIDE(expr))

    .if !(expr)

        mov errno,errorcode
        _INVALID_PARAMETER(_CRT_WIDE(expr))
        .return errorcode
    .endif
    exitm<>
    endm

_VALIDATE_RETURN_ERRCODE_NOEXC macro expr, errorcode

    .if !(expr)

        mov errno,errorcode
        .return errorcode
    .endif
    exitm<>
    endm

_VALIDATE_RETURN_NOERRNO macro expr, retexpr

    _ASSERT_EXPR((expr), _CRT_WIDE(expr))

    .if !(expr)

        _INVALID_PARAMETER(_CRT_WIDE(expr))
        .return retexpr
    .endif
    exitm<>
    endm

_VALIDATE_RETURN_NOEXC macro expr, errorcode, retexpr

    .if !(expr)

        mov errno,errorcode
        .return retexpr
    .endif
    exitm<>
    endm

_VALIDATE_RETURN_VOID macro expr, errorcode

    _ASSERT_EXPR((expr), _CRT_WIDE(expr))

    .if !(expr)

        mov errno,errorcode
        _INVALID_PARAMETER(_CRT_WIDE(expr))
    .endif
    exitm<>
    endm

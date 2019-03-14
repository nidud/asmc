ifndef _INC_RTCAPI
_INC_RTCAPI equ <>

if defined(_RTC) or defined(_CRTBLD) eq 0

include crtdefs.inc

.pragma pack(push,_CRT_PACKING)


;; Previous versions of this header included declarations of functions used by RTC but
;; not intended for use by end-users. These functions are now declared deprecated by default
;; and may be removed in a future version.

ifndef _CRT_ENABLE_RTC_INTERNALS
_RTCINTERNAL_DEPRECATED equ _CRT_DEPRECATE_TEXT("These internal RTC functions are obsolete and should not be used")
else
_RTCINTERNAL_DEPRECATED equ <>
endif

;; General User API

_RTC_ErrorNumber            typedef SDWORD
_RTC_CHKSTK                 equ 0
_RTC_CVRT_LOSS_INFO         equ 1
_RTC_CORRUPT_STACK          equ 2
_RTC_UNINIT_LOCAL_USE       equ 3
_RTC_CORRUPTED_ALLOCA       equ 4
_RTC_ILLEGAL                equ 5


_RTC_ERRTYPE_IGNORE         equ -1
_RTC_ERRTYPE_ASK            equ -2

ifndef _WCHAR_T_DEFINED
_WCHAR_T_DEFINED equ <>
wchar_t typedef word
endif

    CALLBACKC(_RTC_error_fn, :int_t, :string_t, :int_t, :string_t, :string_t, :vararg
    CALLBACKC(_RTC_error_fnW, :int_t, :wstring_t, :int_t, :wstring_t, :wstring_t, :vararg

    ;; User API
    _RTC_NumErrors      proto __cdecl
    _RTC_GetErrDesc     proto __cdecl :_RTC_ErrorNumber
    _RTC_SetErrorType   proto __cdecl :_RTC_ErrorNumber, :int_t
    _RTC_SetErrorFunc   proto __cdecl :_RTC_error_fn
    _RTC_SetErrorFuncW  proto __cdecl :_RTC_error_fnW

    ;; Power User/library API


    ;; Init functions

    ;; These functions all call _CRT_RTC_INIT
    _RTC_Initialize proto __cdecl
    _RTC_Terminate  proto __cdecl

    ;;
    ;; If you're not using the CRT, you have to implement _CRT_RTC_INIT
    ;; Just return either null, or your error reporting function
    ;; *** Don't mess with res0/res1/res2/res3/res4 - YOU'VE BEEN WARNED! ***
    ;;
    _CRT_RTC_INIT  proc __cdecl :ptr, :ptr ptr, :int_t, :int_t, :int_t
    _CRT_RTC_INITW proc __cdecl :ptr, :ptr ptr, :int_t, :int_t, :int_t

    ;; Compiler generated calls (unlikely to be used, even by power users)
    ;; Types
    _RTC_vardesc struct
        _addr int_t ?
        _size int_t ?
        _name string_t ?
    _RTC_vardesc ends
    LP_RTC_vardesc typedef ptr _RTC_vardesc

    _RTC_framedesc struct
        varCount int_t ?
        variables LP_RTC_vardesc ?
    _RTC_framedesc ends

    ;; NOTE:
    ;;  Changing this structure requires a matching compiler backend
    ;;  update, because the offsets are hardcoded inside there.
    ;;
.pragma pack(push, 1)
    ;;  Structure padded under 32-bit x86, to get consistent
    ;;  execution between 32/64 targets.

    _RTC_ALLOCA_NODE struct
        guard1      int_t ?
        next        ptr_t ?
if defined(_M_IX86) or defined(_M_ARM)
        dummypad    int_t ?
endif
        size_t allocaSize;
if defined(_M_IX86) or defined(_M_ARM)
        dummypad2   int_t ?
endif
        guard2      int_t 3 dup(?)
    _RTC_ALLOCA_NODE ends
.pragma pack(pop)

if (defined(_M_CEE) eq 0) and (defined(_M_CEE_PURE) eq 0)
    ;; These unsupported functions are deprecated in native mode and not supported at all in /clr mode

    ;; Shortening convert checks - name indicates src bytes to target bytes
    ;; Signedness is NOT checked
    _RTC_Check_2_to_1 proto fastcall :short_t
    _RTC_Check_4_to_1 proto fastcall :int_t
    _RTC_Check_8_to_1 proto fastcall :int64_t
    _RTC_Check_4_to_2 proto fastcall :int_t
    _RTC_Check_8_to_2 proto fastcall :int64_t
    _RTC_Check_8_to_4 proto fastcall :int64_t
endif


    ;; Stack Checking Calls
ifdef _M_IX86
    _RTC_CheckEsp proto __cdecl
endif

if (defined(_M_CEE) eq 0) and (defined(_M_CEE_PURE) eq 0)
    ;; These unsupported functions are deprecated in native mode and not supported at all in /clr mode

    _RTC_CheckStackVars  proto fastcall :ptr, :ptr _RTC_framedesc
    _RTC_CheckStackVars2 proto fastcall :ptr, :ptr _RTC_framedesc, :ptr _RTC_ALLOCA_NODE
    _RTC_AllocaHelper    proto fastcall :ptr _RTC_ALLOCA_NODE, :size_t, :ptr ptr _RTC_ALLOCA_NODE
endif
    ;; Unintialized Local call
    _RTC_UninitUse proto __cdecl :string_t

if !defined (_M_CEE) && !defined (_M_CEE_PURE)

    ;; These unsupported functions are deprecated in native mode and not supported at all in /clr mode

endif

    ;; Subsystem initialization stuff
    _RTC_Shutdown proto __cdecl
    _RTC_InitBase proto __cdecl

.pragma pack(pop)

endif ;; defined(_RTC) || !defined(_CRTBLD)

endif ;; _INC_RTCAPI

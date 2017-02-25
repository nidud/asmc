ifndef __LIBC_INC
 include libc.inc
endif

.xlist

ifndef _INC_EXCPT
_INC_EXCPT equ 1

ifdef _MSC_VER
;
; Currently, all MS C compilers for Win32 platforms default to 8 byte
; alignment.
;
option fieldalign:8
endif

; Define _CRTAPI1 (for compatibility with the NT SDK)

if not defined(_CRTAPI1) and defined(_MSC_VER)
 if (_MSC_VER GE 800) and (_M_IX86 GE 300)
  _CRTAPI1 equ <C>
 else
  _CRTAPI1 equ <>
 endif
endif

;
; Prototype for SEH support function.
;
ifdef _M_IX86

_except_handler proto _CType \
	ExceptionRecord:	PVOID,
	EstablisherFrame:	PVOID,
	ContextRecord:		PVOID,
	DispatcherContext:	PVOID

endif

;
; Keywords and intrinsics for SEH
;

ifdef _MSC_VER

_exception_code		proto
_exception_info		proto
_abnormal_termination	proto

endif

;
; Legal values for expression in except().
;

EXCEPTION_EXECUTE_HANDLER	equ 1
EXCEPTION_CONTINUE_SEARCH	equ 0
EXCEPTION_CONTINUE_EXECUTION	equ -1


ifndef _INTERNAL_IFSTRIP_
;
; for convenience, define a type name for a pointer to signal-handler
;
PHNDLR_T TYPEDEF PROTO :SINT
_PHNDLR TYPEDEF PTR PHNDLR_T

;
; Exception-action table used by the C runtime to identify and dispose of
; exceptions corresponding to C runtime errors or C signals.
;
_XCPT_ACTION STRUC

    ;
    ; exception code or number. defined by the host OS.
    ;
    XcptNum dd ?

    ;
    ; signal code or number. defined by the C runtime.
    ;
    SigNum dd ?

    ;
    ; exception action code. either a special code or the address of
    ; a handler function. always determines how the exception filter
    ; should dispose of the exception.
    ;
    XcptAction _PHNDLR ?
_XCPT_ACTION ENDS

externdef _XcptActTab:_XCPT_ACTION

;
; number of entries in the exception-action table
;
externdef _XcptActTabCount:SINT

;
; size of exception-action table (in bytes)
;
externdef _XcptActTabSize:SINT

;
; index of the first floating point exception entry
;
externdef _First_FPE_Indx:SINT

;
; number of FPE entries
;
externdef _Num_FPE:SINT

;
; return values and prototype for the exception filter function used in the
; C startup
;
_XcptFilter proto :ULONG, :PVOID

endif	; _INTERNAL_IFSTRIP_
endif	; _INC_EXCPT

.list

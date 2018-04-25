ifndef __EXCPT_INC
__EXCPT_INC equ <>
ifndef _WINDEF_
 include windef.inc
endif

if not defined(_CRTAPI1) and defined(_MSC_VER) and defined(_M_IX86)
 if (_MSC_VER GE 800) and (_M_IX86 GE 300)
  _CRTAPI1 equ <C>
 else
  _CRTAPI1 equ <>
 endif
endif

ifdef _M_IX86

_except_handler proto WINAPI \
	ExceptionRecord:	PVOID,
	EstablisherFrame:	PVOID,
	ContextRecord:		PVOID,
	DispatcherContext:	PVOID

endif

ifdef _MSC_VER

_exception_code		proto
_exception_info		proto
_abnormal_termination	proto

endif

EXCEPTION_EXECUTE_HANDLER	equ 1
EXCEPTION_CONTINUE_SEARCH	equ 0
EXCEPTION_CONTINUE_EXECUTION	equ -1

ifndef _INTERNAL_IFSTRIP_

CALLBACK(_PHNDLR, :SINT)

_XCPT_ACTION STRUC
    XcptNum dd ?
    SigNum dd ?
    XcptAction _PHNDLR ?
_XCPT_ACTION ENDS

externdef _XcptActTab:_XCPT_ACTION
externdef _XcptActTabCount:SINT
externdef _XcptActTabSize:SINT
externdef _First_FPE_Indx:SINT
externdef _Num_FPE:SINT

_XcptFilter proto WINAPI :ULONG, :PVOID

endif

endif

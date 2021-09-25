ifndef __EXCPT_INC
define __EXCPT_INC
ifndef _WINDEF_
 include windef.inc
endif

;; Exception disposition return values.

.enum EXCEPTION_DISPOSITION {
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind
    }

ifdef _M_IX86

_except_handler proto __cdecl \
       ExceptionRecord: ptr EXCEPTION_RECORD,
      EstablisherFrame: ptr,
	 ContextRecord: ptr CONTEXT,
     DispatcherContext: ptr

elseif defined (_M_X64) or defined (_M_ARM)

ifndef _M_CEE_PURE

__C_specific_handler proto __cdecl \
       ExceptionRecord: ptr EXCEPTION_RECORD,
      EstablisherFrame: ptr,
	 ContextRecord: ptr CONTEXT,
     DispatcherContext: ptr DISPATCHER_CONTEXT

endif

endif

;; Keywords and intrinsics for SEH

GetExceptionCode	    equ <_exception_code>
exception_code		    equ <_exception_code>
GetExceptionInformation	    equ <_exception_info>
exception_info		    equ <_exception_info>
AbnormalTermination	    equ <_abnormal_termination>
abnormal_termination	    equ <_abnormal_termination>

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

_XCPT_ACTION	STRUC
XcptNum		dd ?
SigNum		dd ?
XcptAction	_PHNDLR ?
_XCPT_ACTION	ENDS

externdef _XcptActTab:_XCPT_ACTION
externdef _XcptActTabCount:SINT
externdef _XcptActTabSize:SINT
externdef _First_FPE_Indx:SINT
externdef _Num_FPE:SINT

_XcptFilter proto WINAPI :ULONG, :ptr ; PEXCEPTION_POINTERS

endif

endif

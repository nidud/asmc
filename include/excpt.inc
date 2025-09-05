ifndef _EXCPT_
define _EXCPT_
ifndef _WINDEF_
include windef.inc
endif

.enum EXCEPTION_DISPOSITION {
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind
    }

ifdef _M_IX86
_except_handler proto __cdecl :ptr, :ptr, :ptr, :ptr
elseif defined (_M_X64) or defined (_M_ARM)
ifndef _M_CEE_PURE
__C_specific_handler proto __cdecl :ptr, :ptr, :ptr, :ptr
endif
endif

define GetExceptionCode		<_exception_code>
define exception_code		<_exception_code>
define GetExceptionInformation	<_exception_info>
define exception_info		<_exception_info>
define AbnormalTermination	<_abnormal_termination>
define abnormal_termination	<_abnormal_termination>

ifdef _MSC_VER
_exception_code		proto
_exception_info		proto
_abnormal_termination	proto
endif

define EXCEPTION_EXECUTE_HANDLER	1
define EXCEPTION_CONTINUE_SEARCH	0
define EXCEPTION_CONTINUE_EXECUTION	(-1)

ifndef _INTERNAL_IFSTRIP_

CALLBACK(_PHNDLR, :int_t)

_XCPT_ACTION	STRUC
XcptNum		int_t ?
SigNum		int_t ?
XcptAction	_PHNDLR ?
_XCPT_ACTION	ENDS

externdef _XcptActTab:_XCPT_ACTION
externdef _XcptActTabCount:int_t
externdef _XcptActTabSize:int_t
externdef _First_FPE_Indx:int_t
externdef _Num_FPE:SINT

_XcptFilter proto WINAPI :DWORD, :ptr

endif

endif

include specstrings.inc
.pragma list(push, 0)
.pragma comment(lib, wer)
.pragma pack(push, 8)

HREPORT typedef HANDLE

WER_FAULT_REPORTING_FLAG_NOHEAP equ 1
WER_FAULT_REPORTING_FLAG_QUEUE equ 2
WER_FAULT_REPORTING_FLAG_DISABLE_THREAD_SUSPENSION equ 4
WER_FAULT_REPORTING_FLAG_QUEUE_UPLOAD equ 8
WER_FAULT_REPORTING_ALWAYS_SHOW_UI equ 16
WER_MAX_EVENT_NAME_LENGTH equ 64
WER_MAX_SIGNATURE_NAME_LENGTH equ 128
WER_MAX_TOTAL_PARAM_LENGTH equ 1720
WER_MAX_PARAM_LENGTH	equ (MAX_PATH)
WER_MAX_PREFERRED_MODULES equ 128
WER_MAX_PREFERRED_MODULES_BUFFER equ 256
WER_MAX_PARAM_COUNT	equ 10
WER_MAX_MEM_BLOCK_SIZE	equ (64 * 1024)
APPCRASH_EVENT		equ <L"APPCRASH">

WER_P0			equ 0
WER_P1			equ 1
WER_P2			equ 2
WER_P3			equ 3
WER_P4			equ 4
WER_P5			equ 5
WER_P6			equ 6
WER_P7			equ 7
WER_P8			equ 8
WER_P9			equ 9

WER_ERROR_START		equ (0xff00)

WER_E_INSUFFICIENT_BUFFER equ (HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
WER_E_NOT_FOUND		equ (HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
WER_E_LENGTH_EXCEEDED	equ (HRESULT_FROM_WIN32(ERROR_PARAMETER_QUOTA_EXCEEDED))
WER_E_INVALID_STATE	equ (HRESULT_FROM_WIN32(ERROR_INVALID_STATE))
WER_E_STORE_DISABLED	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WINDOWS, WER_ERROR_START + 3)
WER_E_MISSING_PARAM	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WINDOWS, WER_ERROR_START + 5)

WER_REPORT_UI		typedef SDWORD
WerUIAdditionalDataDlgHeader equ 1
WerUIIconFilePath	equ 2
WerUIConsentDlgHeader	equ 3
WerUIConsentDlgBody	equ 4
WerUIOnlineSolutionCheckText equ 5
WerUIOfflineSolutionCheckText equ 6
WerUICloseText		equ 7
WerUICloseDlgHeader	equ 8
WerUICloseDlgBody	equ 9
WerUICloseDlgButtonText equ 10
WerUICustomActionButtonText equ 11
WerUIMax		equ 11

WER_REGISTER_FILE_TYPE	typedef SDWORD
WerRegFileTypeUserDocument equ 1
WerRegFileTypeOther	equ 2
WerRegFileTypeMax	equ 2

WER_FILE_TYPE		typedef SDWORD
WerFileTypeMicrodump	equ 1
WerFileTypeMinidump	equ 2
WerFileTypeHeapdump	equ 3
WerFileTypeUserDocument equ 4
WerFileTypeOther	equ 5
WerFileTypeMax		equ 5

WER_SUBMIT_RESULT	typedef SDWORD
WerReportQueued		equ 1
WerReportUploaded	equ 2
WerReportDebug		equ 3
WerReportFailed		equ 4
WerDisabled		equ 5
WerReportCancelled	equ 6
WerDisabledQueue	equ 7
WerReportAsync		equ 8
WerCustomAction		equ 9
PWER_SUBMIT_RESULT	typedef ptr WER_SUBMIT_RESULT

WER_REPORT_TYPE		typedef SDWORD
WerReportNonCritical	equ 0
WerReportCritical	equ 1
WerReportApplicationCrash equ 2
WerReportApplicationHang equ 3
WerReportKernel		equ 4
WerReportInvalid	equ 5

WER_FILE_DELETE_WHEN_DONE equ 1
WER_FILE_ANONYMOUS_DATA equ 2

WER_SUBMIT_HONOR_RECOVERY equ 1
WER_SUBMIT_HONOR_RESTART equ 2
WER_SUBMIT_QUEUE	equ 4
WER_SUBMIT_SHOW_DEBUG	equ 8
WER_SUBMIT_ADD_REGISTERED_DATA equ 16
WER_SUBMIT_OUTOFPROCESS equ 32
WER_SUBMIT_NO_CLOSE_UI	equ 64
WER_SUBMIT_NO_QUEUE	equ 128
WER_SUBMIT_NO_ARCHIVE	equ 256
WER_SUBMIT_START_MINIMIZED equ 512
WER_SUBMIT_OUTOFPROCESS_ASYNC equ 1024
WER_SUBMIT_BYPASS_DATA_THROTTLING equ 2048
WER_SUBMIT_ARCHIVE_PARAMETERS_ONLY equ 4096
WER_SUBMIT_REPORT_MACHINE_ID equ 8192

WER_REPORT_INFORMATION	STRUC
dwSize			dd ?
hProcess		HANDLE ?
wzConsentKey		WCHAR 64 dup(?)
wzFriendlyEventName	WCHAR 128 dup(?)
wzApplicationName	WCHAR 128 dup(?)
wzApplicationPath	WCHAR MAX_PATH dup(?)
wzDescription		WCHAR 512 dup(?)
hwndParent		HWND ?
WER_REPORT_INFORMATION	ENDS
PWER_REPORT_INFORMATION typedef ptr WER_REPORT_INFORMATION

WER_DUMP_CUSTOM_OPTIONS STRUC
dwSize			dd ?
dwMask			dd ?
dwDumpFlags		dd ?
bOnlyThisThread		BOOL ?
dwExceptionThreadFlags	dd ?
dwOtherThreadFlags	dd ?
dwExceptionThreadExFlags dd ?
dwOtherThreadExFlags	dd ?
dwPreferredModuleFlags	dd ?
dwOtherModuleFlags	dd ?
wzPreferredModuleList	WCHAR WER_MAX_PREFERRED_MODULES_BUFFER dup(?)
WER_DUMP_CUSTOM_OPTIONS ENDS
PWER_DUMP_CUSTOM_OPTIONS typedef ptr WER_DUMP_CUSTOM_OPTIONS

WER_EXCEPTION_INFORMATION STRUC
pExceptionPointers	PEXCEPTION_POINTERS ?
bClientPointers		BOOL ?
WER_EXCEPTION_INFORMATION ENDS
PWER_EXCEPTION_INFORMATION typedef ptr WER_EXCEPTION_INFORMATION

WER_CONSENT		typedef SDWORD
WerConsentNotAsked	equ 1
WerConsentApproved	equ 2
WerConsentDenied	equ 3
WerConsentAlwaysPrompt	equ 4
WerConsentMax		equ 4

WerReportCreate proto WINAPI \
	  pwzEventType: PCWSTR,
	       repType: WER_REPORT_TYPE,
    pReportInformation: PWER_REPORT_INFORMATION,
	phReportHandle: ptr HREPORT

WerReportSetParameter proto WINAPI \
	 hReportHandle: HREPORT,
	     dwparamID: DWORD,
	       pwzName: PCWSTR,
	      pwzValue: PCWSTR

WerReportAddFile proto WINAPI \
	 hReportHandle: HREPORT,
	       pwzPath: PCWSTR,
	   repFileType: WER_FILE_TYPE,
	   dwFileFlags: DWORD

WerReportSetUIOption proto WINAPI \
	 hReportHandle: HREPORT,
	   repUITypeID: WER_REPORT_UI,
	      pwzValue: PCWSTR

WerReportSubmit proto WINAPI \
	 hReportHandle: HREPORT,
	       consent: WER_CONSENT,
	       dwFlags: DWORD,
	 pSubmitResult: PWER_SUBMIT_RESULT


WER_DUMP_MASK_START	equ 1
WER_DUMP_MASK_DUMPTYPE	equ (WER_DUMP_MASK_START SHL 0)
WER_DUMP_MASK_ONLY_THISTHREAD equ (WER_DUMP_MASK_START SHL 1)
WER_DUMP_MASK_THREADFLAGS equ (WER_DUMP_MASK_START SHL 2)
WER_DUMP_MASK_THREADFLAGS_EX equ (WER_DUMP_MASK_START SHL 3)
WER_DUMP_MASK_OTHERTHREADFLAGS equ (WER_DUMP_MASK_START SHL 4)
WER_DUMP_MASK_OTHERTHREADFLAGS_EX equ (WER_DUMP_MASK_START SHL 5)
WER_DUMP_MASK_PREFERRED_MODULESFLAGS equ (WER_DUMP_MASK_START SHL 6)
WER_DUMP_MASK_OTHER_MODULESFLAGS equ (WER_DUMP_MASK_START SHL 7)
WER_DUMP_MASK_PREFERRED_MODULE_LIST equ (WER_DUMP_MASK_START SHL 8)

WER_DUMP_NOHEAP_ONQUEUE equ 1

WER_DUMP_TYPE		typedef SDWORD
WerDumpTypeMicroDump	equ 1
WerDumpTypeMiniDump	equ 2
WerDumpTypeHeapDump	equ 3
WerDumpTypeMax		equ 4

WerReportAddDump proto WINAPI \
	 hReportHandle: HREPORT,
	      hProcess: HANDLE,
	       hThread: HANDLE,
	      dumpType: WER_DUMP_TYPE,
       pExceptionParam: PWER_EXCEPTION_INFORMATION,
    pDumpCustomOptions: PWER_DUMP_CUSTOM_OPTIONS,
	       dwFlags: DWORD


WerReportCloseHandle proto WINAPI \
	 hReportHandle: HREPORT

WER_MAX_REGISTERED_ENTRIES equ 512

WerRegisterFile proto WINAPI \
	       pwzFile: PCWSTR,
	   regFileType: WER_REGISTER_FILE_TYPE,
	       dwFlags: DWORD

WerUnregisterFile proto WINAPI \
	   pwzFilePath: PCWSTR

WerRegisterMemoryBlock proto WINAPI \
	     pvAddress: PVOID,
		dwSize: DWORD

WerUnregisterMemoryBlock proto WINAPI \
	     pvAddress: PVOID

WerSetFlags proto WINAPI \
	       dwFlags: DWORD

WerGetFlags proto WINAPI \
	      hProcess: HANDLE,
	      pdwFlags: PDWORD

WerAddExcludedApplication proto WINAPI \
	    pwzExeName: PCWSTR,
	     bAllUsers: BOOL

WerRemoveExcludedApplication proto WINAPI \
	    pwzExeName: PCWSTR,
	     bAllUsers: BOOL

WER_MAX_REGISTERED_RUNTIME_EXCEPTION_MODULES equ 16

WerRegisterRuntimeExceptionModule proto WINAPI \
pwszOutOfProcessCallbackDll: PCWSTR,
	      pContext: PVOID


WerUnregisterRuntimeExceptionModule proto WINAPI \
pwszOutOfProcessCallbackDll: PCWSTR,
	      pContext: PVOID


WER_RUNTIME_EXCEPTION_EVENT_FUNCTION equ <"OutOfProcessExceptionEventCallback">
WER_RUNTIME_EXCEPTION_EVENT_SIGNATURE_FUNCTION equ <"OutOfProcessExceptionEventSignatureCallback">
WER_RUNTIME_EXCEPTION_DEBUGGER_LAUNCH equ <"OutOfProcessExceptionEventDebuggerLaunchCallback">

WER_RUNTIME_EXCEPTION_INFORMATION STRUC
dwSize			dd ?
hProcess		HANDLE ?
hThread			HANDLE ?
exceptionRecord		EXCEPTION_RECORD <>
context			CONTEXT <>
pwszReportId		PCWSTR ?
WER_RUNTIME_EXCEPTION_INFORMATION ENDS
PWER_RUNTIME_EXCEPTION_INFORMATION typedef ptr WER_RUNTIME_EXCEPTION_INFORMATION


CALLBACK(PFN_WER_RUNTIME_EXCEPTION_EVENT, \
	:PVOID, :PWER_RUNTIME_EXCEPTION_INFORMATION, :ptr BOOL, :PWSTR, :PDWORD, :PDWORD)

CALLBACK(PFN_WER_RUNTIME_EXCEPTION_EVENT_SIGNATURE, \
	:PVOID, :PWER_RUNTIME_EXCEPTION_INFORMATION, :DWORD, :PWSTR, :PDWORD, :PWSTR, :PDWORD)

CALLBACK(PFN_WER_RUNTIME_EXCEPTION_DEBUGGER_LAUNCH, \
	:PVOID, :PWER_RUNTIME_EXCEPTION_INFORMATION, :PBOOL, :PWSTR, :PDWORD, :PBOOL)

.pragma pack(pop)
.pragma list(pop)

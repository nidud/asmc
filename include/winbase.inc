;
; This module defines the 32-Bit Windows Base APIs
;
ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINERROR_
 include winerror.inc
endif
ifndef _WINDEF_
 include windef.inc
endif

.xlist

ifndef _WINBASE_
_WINBASE_ equ 1

ifndef _WIN32_WINDOWS
_WIN32_WINDOWS equ 0x400
endif
ifndef _WIN32_WINNT
_WIN32_WINNT equ _WIN32_WINDOWS
endif

;
; Define API decoration for direct importing of DLL references.
;

ifdef __PE__
WINADVAPI equ <option dllimport:<advapi32>>
else
WINADVAPI equ <>
endif

ifdef __PE__
WINBASEAPI equ <option dllimport:<kernel32>>
else
WINBASEAPI equ <>
endif
;
; Compatibility macros
;

DefineHandleTable macro w
	exitm<((w),TRUE)>
	endm
LimitEmsPages macro w
	endm
SetSwapAreaSize macro w
	exitm<(w)>
	endm
LockSegment macro w
	exitm<GlobalFix(w)>
	endm
UnlockSegment macro w
	exitm<GlobalUnfix(w)>
	endm
GetCurrentTime	equ <GetTickCount>

Yield	macro
	endm

INVALID_HANDLE_VALUE	equ -1
INVALID_FILE_SIZE	equ 0xFFFFFFFF

FILE_BEGIN		equ 0
FILE_CURRENT		equ 1
FILE_END		equ 2

TIME_ZONE_ID_INVALID	equ 0xFFFFFFFF

WAIT_FAILED		equ 0xFFFFFFFF
WAIT_OBJECT_0		equ <((STATUS_WAIT_0 ) + 0 )>

WAIT_ABANDONED		equ <((STATUS_ABANDONED_WAIT_0 ) + 0 )>
WAIT_ABANDONED_0	equ <((STATUS_ABANDONED_WAIT_0 ) + 0 )>

WAIT_TIMEOUT			    equ STATUS_TIMEOUT
WAIT_IO_COMPLETION		    equ STATUS_USER_APC
STILL_ACTIVE			    equ STATUS_PENDING
EXCEPTION_ACCESS_VIOLATION	    equ STATUS_ACCESS_VIOLATION
EXCEPTION_DATATYPE_MISALIGNMENT	    equ STATUS_DATATYPE_MISALIGNMENT
EXCEPTION_BREAKPOINT		    equ STATUS_BREAKPOINT
EXCEPTION_SINGLE_STEP		    equ STATUS_SINGLE_STEP
EXCEPTION_ARRAY_BOUNDS_EXCEEDED	    equ STATUS_ARRAY_BOUNDS_EXCEEDED
EXCEPTION_FLT_DENORMAL_OPERAND	    equ STATUS_FLOAT_DENORMAL_OPERAND
EXCEPTION_FLT_DIVIDE_BY_ZERO	    equ STATUS_FLOAT_DIVIDE_BY_ZERO
EXCEPTION_FLT_INEXACT_RESULT	    equ STATUS_FLOAT_INEXACT_RESULT
EXCEPTION_FLT_INVALID_OPERATION	    equ STATUS_FLOAT_INVALID_OPERATION
EXCEPTION_FLT_OVERFLOW		    equ STATUS_FLOAT_OVERFLOW
EXCEPTION_FLT_STACK_CHECK	    equ STATUS_FLOAT_STACK_CHECK
EXCEPTION_FLT_UNDERFLOW		    equ STATUS_FLOAT_UNDERFLOW
EXCEPTION_INT_DIVIDE_BY_ZERO	    equ STATUS_INTEGER_DIVIDE_BY_ZERO
EXCEPTION_INT_OVERFLOW		    equ STATUS_INTEGER_OVERFLOW
EXCEPTION_PRIV_INSTRUCTION	    equ STATUS_PRIVILEGED_INSTRUCTION
EXCEPTION_IN_PAGE_ERROR		    equ STATUS_IN_PAGE_ERROR
EXCEPTION_ILLEGAL_INSTRUCTION	    equ STATUS_ILLEGAL_INSTRUCTION
EXCEPTION_NONCONTINUABLE_EXCEPTION  equ STATUS_NONCONTINUABLE_EXCEPTION
EXCEPTION_STACK_OVERFLOW	    equ STATUS_STACK_OVERFLOW
EXCEPTION_INVALID_DISPOSITION	    equ STATUS_INVALID_DISPOSITION
EXCEPTION_GUARD_PAGE		    equ STATUS_GUARD_PAGE_VIOLATION
EXCEPTION_INVALID_HANDLE	    equ STATUS_INVALID_HANDLE
CONTROL_C_EXIT			    equ STATUS_CONTROL_C_EXIT

MoveMemory equ RtlMoveMemory
CopyMemory equ RtlCopyMemory
FillMemory equ RtlFillMemory
ZeroMemory equ RtlZeroMemory

if (_WIN32_WINNT GE 0x0500)
ifdef _M_ALPHA
MoveMemoryVlm equ RtlMoveMemory
CopyMemoryVlm equ RtlCopyMemory
FillMemoryVlm equ RtlFillMemory
ZeroMemoryVlm equ RtlZeroMemory
endif
endif

;
; File creation flags must start at the high end since they
; are combined with the attributes
;

FILE_FLAG_WRITE_THROUGH		equ 0x80000000
FILE_FLAG_OVERLAPPED		equ 0x40000000
FILE_FLAG_NO_BUFFERING		equ 0x20000000
FILE_FLAG_RANDOM_ACCESS		equ 0x10000000
FILE_FLAG_SEQUENTIAL_SCAN	equ 0x08000000
FILE_FLAG_DELETE_ON_CLOSE	equ 0x04000000
FILE_FLAG_BACKUP_SEMANTICS	equ 0x02000000
FILE_FLAG_POSIX_SEMANTICS	equ 0x01000000
FILE_FLAG_OPEN_REPARSE_POINT	equ 0x00200000
FILE_FLAG_OPEN_NO_RECALL	equ 0x00100000

CREATE_NEW	    equ 1
CREATE_ALWAYS	    equ 2
OPEN_EXISTING	    equ 3
OPEN_ALWAYS	    equ 4
TRUNCATE_EXISTING   equ 5

if (_WIN32_WINNT GE 0x0400)
;
; Define possible return codes from the CopyFileEx callback routine
;

PROGRESS_CONTINUE   equ 0
PROGRESS_CANCEL	    equ 1
PROGRESS_STOP	    equ 2
PROGRESS_QUIET	    equ 3

;
; Define CopyFileEx callback routine state change values
;

CALLBACK_CHUNK_FINISHED		equ 0x00000000
CALLBACK_STREAM_SWITCH		equ 0x00000001

;
; Define CopyFileEx option flags
;

COPY_FILE_FAIL_IF_EXISTS	equ 0x00000001
COPY_FILE_RESTARTABLE		equ 0x00000002
COPY_FILE_OPEN_SOURCE_FOR_WRITE equ 0x00000004
endif

;
; Define the NamedPipe definitions
;


;
; Define the dwOpenMode values for CreateNamedPipe
;

PIPE_ACCESS_INBOUND	    equ 0x00000001
PIPE_ACCESS_OUTBOUND	    equ 0x00000002
PIPE_ACCESS_DUPLEX	    equ 0x00000003

;
; Define the Named Pipe End flags for GetNamedPipeInfo
;

PIPE_CLIENT_END		    equ 0x00000000
PIPE_SERVER_END		    equ 0x00000001

;
; Define the dwPipeMode values for CreateNamedPipe
;

PIPE_WAIT		    equ 0x00000000
PIPE_NOWAIT		    equ 0x00000001
PIPE_READMODE_BYTE	    equ 0x00000000
PIPE_READMODE_MESSAGE	    equ 0x00000002
PIPE_TYPE_BYTE		    equ 0x00000000
PIPE_TYPE_MESSAGE	    equ 0x00000004

;
; Define the well known values for CreateNamedPipe nMaxInstances
;

PIPE_UNLIMITED_INSTANCES    equ 255

;
; Define the Security Quality of Service bits to be passed
; into CreateFile
;

SECURITY_ANONYMOUS	    equ ( SecurityAnonymous	 shl 16 )
SECURITY_IDENTIFICATION	    equ ( SecurityIdentification shl 16 )
SECURITY_IMPERSONATION	    equ ( SecurityImpersonation	 shl 16 )
SECURITY_DELEGATION	    equ ( SecurityDelegation	 shl 16 )

SECURITY_CONTEXT_TRACKING  equ 0x00040000
SECURITY_EFFECTIVE_ONLY	   equ 0x00080000

SECURITY_SQOS_PRESENT	   equ 0x00100000
SECURITY_VALID_SQOS_FLAGS  equ 0x001F0000

;
;  File structures
;

OVERLAPPED		STRUC
Internal		dd ?
InternalHigh		dd ?
_Offset			dd ?
OffsetHigh		dd ?
hEvent			HANDLE ?
OVERLAPPED		ENDS

LPOVERLAPPED		TYPEDEF PTR OVERLAPPED

SECURITY_ATTRIBUTES	STRUC SIZE_T
nLength			dd ?
lpSecurityDescriptor	PVOID ?
bInheritHandle		BOOL ?
SECURITY_ATTRIBUTES	ENDS

PSECURITY_ATTRIBUTES	TYPEDEF PTR SECURITY_ATTRIBUTES
LPSECURITY_ATTRIBUTES	TYPEDEF PTR SECURITY_ATTRIBUTES

PROCESS_INFORMATION	STRUC SIZE_T
hProcess		HANDLE ?
hThread			HANDLE ?
dwProcessId		dd ?
dwThreadId		dd ?
PROCESS_INFORMATION	ENDS

PPROCESS_INFORMATION	TYPEDEF PTR PROCESS_INFORMATION
LPPROCESS_INFORMATION	TYPEDEF PTR PROCESS_INFORMATION

;
;  File System time stamps are represented with the following structure:
;

FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS

PFILETIME	TYPEDEF PTR FILETIME
LPFILETIME	TYPEDEF PTR FILETIME

;
; System time is represented with the following structure:
;

SYSTEMTIME	STRUC
wYear		dw ?
wMonth		dw ?
wDayOfWeek	dw ?
wDay		dw ?
wHour		dw ?
wMinute		dw ?
wSecond		dw ?
wMilliseconds	dw ?
SYSTEMTIME	ENDS

PSYSTEMTIME	TYPEDEF PTR SYSTEMTIME
LPSYSTEMTIME	TYPEDEF PTR SYSTEMTIME

THREAD_ROUTINE_T	TYPEDEF PROTO :PVOID
PTHREAD_START_ROUTINE	TYPEDEF PTR THREAD_ROUTINE_T
LPTHREAD_START_ROUTINE	TYPEDEF PTHREAD_START_ROUTINE

if (_WIN32_WINNT GE 0x0400)
PFIBER_START_ROUTINE	TYPEDEF PTR THREAD_ROUTINE_T
LPFIBER_START_ROUTINE	TYPEDEF PFIBER_START_ROUTINE
endif

CRITICAL_SECTION	typedef RTL_CRITICAL_SECTION
PCRITICAL_SECTION	typedef PRTL_CRITICAL_SECTION
LPCRITICAL_SECTION	typedef PRTL_CRITICAL_SECTION

CRITICAL_SECTION_DEBUG	typedef RTL_CRITICAL_SECTION_DEBUG
PCRITICAL_SECTION_DEBUG typedef PRTL_CRITICAL_SECTION_DEBUG
LPCRITICAL_SECTION_DEBUG typedef PRTL_CRITICAL_SECTION_DEBUG

ifdef _X86_
LPLDT_ENTRY	typedef PLDT_ENTRY
else
LPLDT_ENTRY	typedef PVOID
endif

MUTEX_MODIFY_STATE	equ MUTANT_QUERY_STATE
MUTEX_ALL_ACCESS	equ MUTANT_ALL_ACCESS

;
; Serial provider type.
;

SP_SERIALCOMM		equ 0x00000001

;
; Provider SubTypes
;

PST_UNSPECIFIED	     equ 0x00000000
PST_RS232	     equ 0x00000001
PST_PARALLELPORT     equ 0x00000002
PST_RS422	     equ 0x00000003
PST_RS423	     equ 0x00000004
PST_RS449	     equ 0x00000005
PST_MODEM	     equ 0x00000006
PST_FAX		     equ 0x00000021
PST_SCANNER	     equ 0x00000022
PST_NETWORK_BRIDGE   equ 0x00000100
PST_LAT		     equ 0x00000101
PST_TCPIP_TELNET     equ 0x00000102
PST_X25		     equ 0x00000103


;
; Provider capabilities flags.
;

PCF_DTRDSR	  equ 0x0001
PCF_RTSCTS	  equ 0x0002
PCF_RLSD	  equ 0x0004
PCF_PARITY_CHECK  equ 0x0008
PCF_XONXOFF	  equ 0x0010
PCF_SETXCHAR	  equ 0x0020
PCF_TOTALTIMEOUTS equ 0x0040
PCF_INTTIMEOUTS	  equ 0x0080
PCF_SPECIALCHARS  equ 0x0100
PCF_16BITMODE	  equ 0x0200

;
; Comm provider settable parameters.
;

SP_PARITY	  equ 0x0001
SP_BAUD		  equ 0x0002
SP_DATABITS	  equ 0x0004
SP_STOPBITS	  equ 0x0008
SP_HANDSHAKING	  equ 0x0010
SP_PARITY_CHECK	  equ 0x0020
SP_RLSD		  equ 0x0040

;
; Settable baud rates in the provider.
;

BAUD_075	  equ 0x00000001
BAUD_110	  equ 0x00000002
BAUD_134_5	  equ 0x00000004
BAUD_150	  equ 0x00000008
BAUD_300	  equ 0x00000010
BAUD_600	  equ 0x00000020
BAUD_1200	  equ 0x00000040
BAUD_1800	  equ 0x00000080
BAUD_2400	  equ 0x00000100
BAUD_4800	  equ 0x00000200
BAUD_7200	  equ 0x00000400
BAUD_9600	  equ 0x00000800
BAUD_14400	  equ 0x00001000
BAUD_19200	  equ 0x00002000
BAUD_38400	  equ 0x00004000
BAUD_56K	  equ 0x00008000
BAUD_128K	  equ 0x00010000
BAUD_115200	  equ 0x00020000
BAUD_57600	  equ 0x00040000
BAUD_USER	  equ 0x10000000

;
; Settable Data Bits
;

DATABITS_5	equ 0x0001
DATABITS_6	equ 0x0002
DATABITS_7	equ 0x0004
DATABITS_8	equ 0x0008
DATABITS_16	equ 0x0010
DATABITS_16X	equ 0x0020

;
; Settable Stop and Parity bits.
;

STOPBITS_10	equ 0x0001
STOPBITS_15	equ 0x0002
STOPBITS_20	equ 0x0004
PARITY_NONE	equ 0x0100
PARITY_ODD	equ 0x0200
PARITY_EVEN	equ 0x0400
PARITY_MARK	equ 0x0800
PARITY_SPACE	equ 0x1000

COMMPROP		STRUC
wPacketLength		WORD ?
wPacketVersion		WORD ?
dwServiceMask		DWORD ?
dwReserved1		DWORD ?
dwMaxTxQueue		DWORD ?
dwMaxRxQueue		DWORD ?
dwMaxBaud		DWORD ?
dwProvSubType		DWORD ?
dwProvCapabilities	DWORD ?
dwSettableParams	DWORD ?
dwSettableBaud		DWORD ?
wSettableData		WORD ?
wSettableStopParity	WORD ?
dwCurrentTxQueue	DWORD ?
dwCurrentRxQueue	DWORD ?
dwProvSpec1		DWORD ?
dwProvSpec2		DWORD ?
wcProvChar		WORD ?
COMMPROP		ENDS

LPCOMMPROP	typedef ptr COMMPROP

;
; Set dwProvSpec1 to COMMPROP_INITIALIZED to indicate that wPacketLength
; is valid before a call to GetCommProperties().
;
COMMPROP_INITIALIZED equ 0xE73CF52E

COMSTAT_R0 RECORD \
	coms_fReserved: 25,
	coms_fTxim:	1,
	coms_fEof:	1,
	coms_fXoffSent: 1,
	coms_fXoffHold: 1,
	coms_fRlsdHold: 1,
	coms_fDsrHold:	1,
	coms_fCtsHold:	1

COMSTAT		STRUC
r0		COMSTAT_R0 <>
cbInQue		DWORD ?
cbOutQue	DWORD ?
COMSTAT		ENDS

LPCOMSTAT	typedef COMSTAT

;
; DTR Control Flow Values.
;
DTR_CONTROL_DISABLE    equ 0x00
DTR_CONTROL_ENABLE     equ 0x01
DTR_CONTROL_HANDSHAKE  equ 0x02

;
; RTS Control Flow Values
;
RTS_CONTROL_DISABLE    equ 0x00
RTS_CONTROL_ENABLE     equ 0x01
RTS_CONTROL_HANDSHAKE  equ 0x02
RTS_CONTROL_TOGGLE     equ 0x03

DCB_R0 RECORD \
    DCB_fDummy:		17, ; Reserved
    DCB_fAbortOnError:	1,  ; Abort all reads and writes on Error
    DCB_fRtsControl:	2,  ; Rts Flow control
    DCB_fNull:		1,  ; Enable Null stripping
    DCB_fErrorChar:	1,  ; Enable Err Replacement
    DCB_fInX:		1,  ; Enable input X-ON/X-OFF
    DCB_fOutX:		1,  ; Enable output X-ON/X-OFF
    DCB_fTXContinueOnXoff:1,  ; Continue TX when Xoff sent
    DCB_fDsrSensitivity:1,  ; DSR Sensitivity
    DCB_fDtrControl:	2,  ; DTR Flow control
    DCB_fOutxDsrFlow:	1,  ; DSR handshaking on output
    DCB_fOutxCtsFlow:	1,  ; CTS handshaking on output
    DCB_fParity:	1,  ; Enable parity checking
    DCB_fBinary:	1   ; Binary Mode (skip EOF check)

DCB STRUC
    DCBlength dd ?	; sizeof(DCB)
    BaudRate  dd ?	; Baudrate at which running
    R0	      DCB_R0 <>
    wReserved dw ?	; Not currently used
    XonLim    dw ?	; Transmit X-ON threshold
    XoffLim   dw ?	; Transmit X-OFF threshold
    ByteSize  db ?	; Number of bits/byte, 4-8
    Parity    db ?	; 0-4=None,Odd,Even,Mark,Space
    StopBits  db ?	; 0,1,2 = 1, 1.5, 2
    XonChar   db ?	; Tx and Rx X-ON character
    XoffChar  db ?	; Tx and Rx X-OFF character
    ErrorChar db ?	; Error replacement char
    EofChar   db ?	; End of Input character
    EvtChar   db ?	; Received Event character
    wReserved1 dw ?	; Fill for now.
DCB ENDS

LPDCB typedef ptr DCB

COMMTIMEOUTS			STRUC
ReadIntervalTimeout		dd ? ; Maximum time between read chars.
ReadTotalTimeoutMultiplier	dd ? ; Multiplier of characters.
ReadTotalTimeoutConstant	dd ? ; Constant in milliseconds.
WriteTotalTimeoutMultiplier	dd ? ; Multiplier of characters.
WriteTotalTimeoutConstant	dd ? ; Constant in milliseconds.
COMMTIMEOUTS			ENDS

LPCOMMTIMEOUTS typedef ptr COMMTIMEOUTS

COMMCONFIG		STRUC
dwSize			dd ?	; Size of the entire struct
wVersion		dw ?	; version of the structure
wReserved		dw ?	; alignment
dcb			DCB <>	; device control block
dwProviderSubType	dd ?	; ordinal value for identifying
				; provider-defined data structure format
dwProviderOffset	dd ?	; Specifies the offset of provider specific
				; data field in bytes from the start
dwProviderSize		dd ?	; size of the provider-specific data field
wcProviderData		dw ?	; provider-specific data
COMMCONFIG		ENDS

LPCOMMCONFIG typedef ptr COMMCONFIG

SYSTEM_INFO			STRUC
union
    dwOemId			dd ?	; Obsolete field...do not use
    struc
	wProcessorArchitecture	dw ?
	wReserved		dw ?
    ends
ends
dwPageSize			dd ?
lpMinimumApplicationAddress	PVOID ?
lpMaximumApplicationAddress	PVOID ?
dwActiveProcessorMask		dd ?
dwNumberOfProcessors		dd ?
dwProcessorType			dd ?
dwAllocationGranularity		dd ?
wProcessorLevel			dw ?
wProcessorRevision		dw ?
SYSTEM_INFO			ENDS

LPSYSTEM_INFO typedef ptr SYSTEM_INFO

FreeModule macro hLibModule
	FreeLibrary(hLibModule)
	endm
MakeProcInstance macro lpProc, hInstance
	exitm<(lpProc)>
	endm
FreeProcInstance macro lpProc
	exitm<(lpProc)>
	endm

; Global Memory Flags
GMEM_FIXED		equ 0x0000
GMEM_MOVEABLE		equ 0x0002
GMEM_NOCOMPACT		equ 0x0010
GMEM_NODISCARD		equ 0x0020
GMEM_ZEROINIT		equ 0x0040
GMEM_MODIFY		equ 0x0080
GMEM_DISCARDABLE	equ 0x0100
GMEM_NOT_BANKED		equ 0x1000
GMEM_SHARE		equ 0x2000
GMEM_DDESHARE		equ 0x2000
GMEM_NOTIFY		equ 0x4000
GMEM_LOWER		equ GMEM_NOT_BANKED
GMEM_VALID_FLAGS	equ 0x7F72
GMEM_INVALID_HANDLE	equ 0x8000

GHND	equ GMEM_MOVEABLE or GMEM_ZEROINIT
GPTR	equ GMEM_FIXED or GMEM_ZEROINIT

GlobalLRUNewest macro h
	exitm<h>
	endm
GlobalLRUOldest macro h
	exitm<h>
	endm
GlobalDiscard macro h
	exitm<GlobalReAlloc(h, 0, GMEM_MOVEABLE)>
	endm


; Flags returned by GlobalFlags (in addition to GMEM_DISCARDABLE)
GMEM_DISCARDED		equ 0x4000
GMEM_LOCKCOUNT		equ 0x00FF

MEMORYSTATUS		STRUC
dwLength		dd ?
dwMemoryLoad		dd ?
dwTotalPhys		dd ?
dwAvailPhys		dd ?
dwTotalPageFile		dd ?
dwAvailPageFile		dd ?
dwTotalVirtual		dd ?
dwAvailVirtual		dd ?
MEMORYSTATUS		ENDS
LPMEMORYSTATUS		TYPEDEF PTR MEMORYSTATUS

MEMORYSTATUSEX		STRUC
dwLength		dd ?	; Size of structure: must be set before call
dwMemoryLoad		dd ?	; A number between 0 and 100 that specifies the
				; approximate percentage of physical memory that
				; is in use (0 indicates no memory use and 100
				; indicates full memory use).
ullTotalPhys		dq ?	; The amount of actual physical memory in bytes
ullAvailPhys		dq ?	; The amount of physical memory currently
				; available, in bytes. This is the amount of
				; physical memory that can be immediately reused
				; without having to write its contents to disk
				; first. It is the sum of the size of the
				; standby, free, and zero lists.
ullTotalPageFile	dq ?	; The current committed memory limit for the
				; system or the current process, whichever is
				; smaller, in bytes. To get the system-wide
				; committed memory limit, call
				; GetPerformanceInfo.
ullAvailPageFile	dq ?	; The maximum amount of memory the current
				; process can commit, in bytes. This value is
				; equal to or smaller than the system-wide
				; available commit value. To calculate the
				; system-wide available commit value, call
				; GetPerformanceInfo and subtract the value of
				; CommitTotal from the value of CommitLimit.
ullTotalVirtual		dq ?	; The size of the user-mode portion of the
				; virtual address space of the calling process,
				; in bytes. This value depends on the type of
				; process, the type of processor, and the
				; configuration of the operating system. For
				; example, this value is approximately 2 GB for
				; most 32-bit processes on an x86 processor and
				; approximately 3 GB for 32-bit processes that
				; are large address aware running on a system
				; with 4-gigabyte tuning enabled.
ullAvailVirtual		dq ?	; The amount of unreserved and uncommitted
				; memory currently in the user-mode portion of
				; the virtual address space of the calling
				; process, in bytes.
ullAvailExtendedVirtual dq ?	; Reserved. This value is always 0.
MEMORYSTATUSEX		ENDS
LPMEMORYSTATUSEX	TYPEDEF PTR MEMORYSTATUSEX

; Local Memory Flags
LMEM_FIXED		equ 0x0000
LMEM_MOVEABLE		equ 0x0002
LMEM_NOCOMPACT		equ 0x0010
LMEM_NODISCARD		equ 0x0020
LMEM_ZEROINIT		equ 0x0040
LMEM_MODIFY		equ 0x0080
LMEM_DISCARDABLE	equ 0x0F00
LMEM_VALID_FLAGS	equ 0x0F72
LMEM_INVALID_HANDLE	equ 0x8000

LHND			equ (LMEM_MOVEABLE or LMEM_ZEROINIT)
LPTR			equ (LMEM_FIXED or LMEM_ZEROINIT)

NONZEROLHND		equ (LMEM_MOVEABLE)
NONZEROLPTR		equ (LMEM_FIXED)

LocalDiscard macro h
	exitm<LocalReAlloc(h, 0, LMEM_MOVEABLE)>
	endm

; Flags returned by LocalFlags (in addition to LMEM_DISCARDABLE)
LMEM_DISCARDED		equ 0x4000
LMEM_LOCKCOUNT		equ 0x00FF

;
; dwCreationFlag values
;

DEBUG_PROCESS		    equ 0x00000001
DEBUG_ONLY_THIS_PROCESS	    equ 0x00000002

CREATE_SUSPENDED	    equ 0x00000004

DETACHED_PROCESS	    equ 0x00000008

CREATE_NEW_CONSOLE	    equ 0x00000010

NORMAL_PRIORITY_CLASS	    equ 0x00000020
IDLE_PRIORITY_CLASS	    equ 0x00000040
HIGH_PRIORITY_CLASS	    equ 0x00000080
REALTIME_PRIORITY_CLASS	    equ 0x00000100

CREATE_NEW_PROCESS_GROUP    equ 0x00000200
CREATE_UNICODE_ENVIRONMENT  equ 0x00000400

CREATE_SEPARATE_WOW_VDM	    equ 0x00000800
CREATE_SHARED_WOW_VDM	    equ 0x00001000
CREATE_FORCEDOS		    equ 0x00002000

CREATE_DEFAULT_ERROR_MODE   equ 0x04000000
CREATE_NO_WINDOW	    equ 0x08000000

PROFILE_USER		    equ 0x10000000
PROFILE_KERNEL		    equ 0x20000000
PROFILE_SERVER		    equ 0x40000000

THREAD_PRIORITY_LOWEST		equ THREAD_BASE_PRIORITY_MIN
THREAD_PRIORITY_BELOW_NORMAL	equ (THREAD_PRIORITY_LOWEST+1)
THREAD_PRIORITY_NORMAL		equ 0
THREAD_PRIORITY_HIGHEST		equ THREAD_BASE_PRIORITY_MAX
THREAD_PRIORITY_ABOVE_NORMAL	equ (THREAD_PRIORITY_HIGHEST-1)
THREAD_PRIORITY_ERROR_RETURN	equ (MAXLONG)

THREAD_PRIORITY_TIME_CRITICAL	equ THREAD_BASE_PRIORITY_LOWRT
THREAD_PRIORITY_IDLE		equ THREAD_BASE_PRIORITY_IDLE

;
; Debug APIs
;
EXCEPTION_DEBUG_EVENT	    equ 1
CREATE_THREAD_DEBUG_EVENT   equ 2
CREATE_PROCESS_DEBUG_EVENT  equ 3
EXIT_THREAD_DEBUG_EVENT	    equ 4
EXIT_PROCESS_DEBUG_EVENT    equ 5
LOAD_DLL_DEBUG_EVENT	    equ 6
UNLOAD_DLL_DEBUG_EVENT	    equ 7
OUTPUT_DEBUG_STRING_EVENT   equ 8
RIP_EVENT		    equ 9

EXCEPTION_DEBUG_INFO	STRUC
ExceptionRecord		EXCEPTION_RECORD <>
dwFirstChance		DWORD ?
EXCEPTION_DEBUG_INFO	ENDS
LPEXCEPTION_DEBUG_INFO	TYPEDEF PTR EXCEPTION_DEBUG_INFO

CREATE_THREAD_DEBUG_INFO STRUC
hThread			HANDLE ?
lpThreadLocalBase	PVOID ?
lpStartAddress		LPTHREAD_START_ROUTINE ?
CREATE_THREAD_DEBUG_INFO ENDS
LPCREATE_THREAD_DEBUG_INFO TYPEDEF PTR CREATE_THREAD_DEBUG_INFO

CREATE_PROCESS_DEBUG_INFO STRUC
hFile			HANDLE ?
hProcess		HANDLE ?
hThread			HANDLE ?
lpBaseOfImage		PVOID ?
dwDebugInfoFileOffset	DWORD ?
DebugInfoSize		DWORD ?
lpThreadLocalBase	PVOID ?
lpStartAddress		LPTHREAD_START_ROUTINE ?
lpImageName		PVOID ?
fUnicode		WORD ?
CREATE_PROCESS_DEBUG_INFO ENDS
LPCREATE_PROCESS_DEBUG_INFO TYPEDEF PTR CREATE_PROCESS_DEBUG_INFO

EXIT_THREAD_DEBUG_INFO	STRUC
dwExitCode		DWORD ?
EXIT_THREAD_DEBUG_INFO	ENDS
LPEXIT_THREAD_DEBUG_INFO TYPEDEF PTR EXIT_THREAD_DEBUG_INFO

EXIT_PROCESS_DEBUG_INFO STRUC
dwExitCode		DWORD ?
EXIT_PROCESS_DEBUG_INFO ENDS
LPEXIT_PROCESS_DEBUG_INFO TYPEDEF PTR EXIT_PROCESS_DEBUG_INFO

LOAD_DLL_DEBUG_INFO	STRUC
hFile			HANDLE ?
lpBaseOfDll		PVOID ?
dwDebugInfoFileOffset	DWORD ?
nDebugInfoSize		DWORD ?
lpImageName		PVOID ?
fUnicode		WORD ?
LOAD_DLL_DEBUG_INFO	ENDS
LPLOAD_DLL_DEBUG_INFO	TYPEDEF PTR LOAD_DLL_DEBUG_INFO

UNLOAD_DLL_DEBUG_INFO	STRUC
lpBaseOfDll		PVOID ?
UNLOAD_DLL_DEBUG_INFO	ENDS
LPUNLOAD_DLL_DEBUG_INFO TYPEDEF PTR UNLOAD_DLL_DEBUG_INFO

OUTPUT_DEBUG_STRING_INFO STRUC
lpDebugStringData	LPSTR ?
fUnicode		dw ?
nDebugStringLength	dw ?
OUTPUT_DEBUG_STRING_INFO ENDS
LPOUTPUT_DEBUG_STRING_INFO TYPEDEF PTR OUTPUT_DEBUG_STRING_INFO

RIP_INFO		STRUC
dwError			dd ?
dwType			dd ?
RIP_INFO		ENDS
LPRIP_INFO		TYPEDEF PTR RIP_INFO


DEBUG_EVENT		STRUC
dwDebugEventCode	DWORD ?
dwProcessId		DWORD ?
dwThreadId		DWORD ?
UNION
  Exception		EXCEPTION_DEBUG_INFO <>
  CreateThread		CREATE_THREAD_DEBUG_INFO <>
  CreateProcessInfo	CREATE_PROCESS_DEBUG_INFO <>
  ExitThread		EXIT_THREAD_DEBUG_INFO <>
  ExitProcess		EXIT_PROCESS_DEBUG_INFO <>
  LoadDll		LOAD_DLL_DEBUG_INFO <>
  UnloadDll		UNLOAD_DLL_DEBUG_INFO <>
  DebugString		OUTPUT_DEBUG_STRING_INFO <>
  RipInfo		RIP_INFO <>
ENDS
DEBUG_EVENT		ENDS

LPDEBUG_EVENT		TYPEDEF PTR DEBUG_EVENT

ifndef MIDL_PASS
LPCONTEXT		TYPEDEF PCONTEXT
LPEXCEPTION_RECORD	TYPEDEF PEXCEPTION_RECORD
LPEXCEPTION_POINTERS	TYPEDEF PEXCEPTION_POINTERS
endif

DRIVE_UNKNOWN		equ 0
DRIVE_NO_ROOT_DIR	equ 1
DRIVE_REMOVABLE		equ 2
DRIVE_FIXED		equ 3
DRIVE_REMOTE		equ 4
DRIVE_CDROM		equ 5
DRIVE_RAMDISK		equ 6

GetFreeSpace macro w
	exitm<0x100000>
	endm

FILE_TYPE_UNKNOWN   equ 0x0000
FILE_TYPE_DISK	    equ 0x0001
FILE_TYPE_CHAR	    equ 0x0002
FILE_TYPE_PIPE	    equ 0x0003
FILE_TYPE_REMOTE    equ 0x8000


STD_INPUT_HANDLE    equ -10
STD_OUTPUT_HANDLE   equ -11
STD_ERROR_HANDLE    equ -12

NOPARITY	    equ 0
ODDPARITY	    equ 1
EVENPARITY	    equ 2
MARKPARITY	    equ 3
SPACEPARITY	    equ 4

ONESTOPBIT	    equ 0
ONE5STOPBITS	    equ 1
TWOSTOPBITS	    equ 2

IGNORE		    equ 0	    ; Ignore signal
INFINITE	    equ 0xFFFFFFFF ; Infinite timeout

;
; Baud rates at which the communication device operates
;

CBR_110		    equ 110
CBR_300		    equ 300
CBR_600		    equ 600
CBR_1200	    equ 1200
CBR_2400	    equ 2400
CBR_4800	    equ 4800
CBR_9600	    equ 9600
CBR_14400	    equ 14400
CBR_19200	    equ 19200
CBR_38400	    equ 38400
CBR_56000	    equ 56000
CBR_57600	    equ 57600
CBR_115200	    equ 115200
CBR_128000	    equ 128000
CBR_256000	    equ 256000

;
; Error Flags
;

CE_RXOVER	    equ 0x0001	; Receive Queue overflow
CE_OVERRUN	    equ 0x0002	; Receive Overrun Error
CE_RXPARITY	    equ 0x0004	; Receive Parity Error
CE_FRAME	    equ 0x0008	; Receive Framing error
CE_BREAK	    equ 0x0010	; Break Detected
CE_TXFULL	    equ 0x0100	; TX Queue is full
CE_PTO		    equ 0x0200	; LPTx Timeout
CE_IOE		    equ 0x0400	; LPTx I/O Error
CE_DNS		    equ 0x0800	; LPTx Device not selected
CE_OOP		    equ 0x1000	; LPTx Out-Of-Paper
CE_MODE		    equ 0x8000	; Requested mode unsupported

IE_BADID	    equ (-1)	; Invalid or unsupported id
IE_OPEN		    equ (-2)	; Device Already Open
IE_NOPEN	    equ (-3)	; Device Not Open
IE_MEMORY	    equ (-4)	; Unable to allocate queues
IE_DEFAULT	    equ (-5)	; Error in default parameters
IE_HARDWARE	    equ (-10)	; Hardware Not Present
IE_BYTESIZE	    equ (-11)	; Illegal Byte Size
IE_BAUDRATE	    equ (-12)	; Unsupported BaudRate

;
; Events
;

EV_RXCHAR	    equ 0x0001	; Any Character received
EV_RXFLAG	    equ 0x0002	; Received certain character
EV_TXEMPTY	    equ 0x0004	; Transmitt Queue Empty
EV_CTS		    equ 0x0008	; CTS changed state
EV_DSR		    equ 0x0010	; DSR changed state
EV_RLSD		    equ 0x0020	; RLSD changed state
EV_BREAK	    equ 0x0040	; BREAK received
EV_ERR		    equ 0x0080	; Line status error occurred
EV_RING		    equ 0x0100	; Ring signal detected
EV_PERR		    equ 0x0200	; Printer error occured
EV_RX80FULL	    equ 0x0400	; Receive buffer is 80 percent full
EV_EVENT1	    equ 0x0800	; Provider specific event 1
EV_EVENT2	    equ 0x1000	; Provider specific event 2

;
; Escape Functions
;

SETXOFF		    equ 1	; Simulate XOFF received
SETXON		    equ 2	; Simulate XON received
SETRTS		    equ 3	; Set RTS high
CLRRTS		    equ 4	; Set RTS low
SETDTR		    equ 5	; Set DTR high
CLRDTR		    equ 6	; Set DTR low
RESETDEV	    equ 7	; Reset device if possible
SETBREAK	    equ 8	; Set the device break line.
CLRBREAK	    equ 9	; Clear the device break line.

;
; PURGE function flags.
;
PURGE_TXABORT	    equ 0x0001	; Kill the pending/current writes to the comm port.
PURGE_RXABORT	    equ 0x0002	; Kill the pending/current reads to the comm port.
PURGE_TXCLEAR	    equ 0x0004	; Kill the transmit queue if there.
PURGE_RXCLEAR	    equ 0x0008	; Kill the typeahead buffer if there.

LPTx		    equ 0x80	; Set if ID is for LPT device

;
; Modem Status Flags
;
MS_CTS_ON	    equ 0x0010
MS_DSR_ON	    equ 0x0020
MS_RING_ON	    equ 0x0040
MS_RLSD_ON	    equ 0x0080

;
; WaitSoundState() Constants
;

S_QUEUEEMPTY	    equ 0
S_THRESHOLD	    equ 1
S_ALLTHRESHOLD	    equ 2

;
; Accent Modes
;

S_NORMAL      equ 0
S_LEGATO      equ 1
S_STACCATO    equ 2

;
; SetSoundNoise() Sources
;

S_PERIOD512   equ 0	    ; Freq = N/512 high pitch, less coarse hiss
S_PERIOD1024  equ 1	    ; Freq = N/1024
S_PERIOD2048  equ 2	    ; Freq = N/2048 low pitch, more coarse hiss
S_PERIODVOICE equ 3	    ; Source is frequency from voice channel (3)
S_WHITE512    equ 4	    ; Freq = N/512 high pitch, less coarse hiss
S_WHITE1024   equ 5	    ; Freq = N/1024
S_WHITE2048   equ 6	    ; Freq = N/2048 low pitch, more coarse hiss
S_WHITEVOICE  equ 7	    ; Source is frequency from voice channel (3)

S_SERDVNA     equ (-1)	; Device not available
S_SEROFM      equ (-2)	; Out of memory
S_SERMACT     equ (-3)	; Music active
S_SERQFUL     equ (-4)	; Queue full
S_SERBDNT     equ (-5)	; Invalid note
S_SERDLN      equ (-6)	; Invalid note length
S_SERDCC      equ (-7)	; Invalid note count
S_SERDTP      equ (-8)	; Invalid tempo
S_SERDVL      equ (-9)	; Invalid volume
S_SERDMD      equ (-10) ; Invalid mode
S_SERDSH      equ (-11) ; Invalid shape
S_SERDPT      equ (-12) ; Invalid pitch
S_SERDFQ      equ (-13) ; Invalid frequency
S_SERDDR      equ (-14) ; Invalid duration
S_SERDSR      equ (-15) ; Invalid source
S_SERDST      equ (-16) ; Invalid state

NMPWAIT_WAIT_FOREVER		equ 0xffffffff
NMPWAIT_NOWAIT			equ 0x00000001
NMPWAIT_USE_DEFAULT_WAIT	equ 0x00000000

FS_CASE_IS_PRESERVED		equ FILE_CASE_PRESERVED_NAMES
FS_CASE_SENSITIVE		equ FILE_CASE_SENSITIVE_SEARCH
FS_UNICODE_STORED_ON_DISK	equ FILE_UNICODE_ON_DISK
FS_PERSISTENT_ACLS		equ FILE_PERSISTENT_ACLS
FS_VOL_IS_COMPRESSED		equ FILE_VOLUME_IS_COMPRESSED
FS_FILE_COMPRESSION		equ FILE_FILE_COMPRESSION


FILE_MAP_COPY	    equ SECTION_QUERY
FILE_MAP_WRITE	    equ SECTION_MAP_WRITE
FILE_MAP_READ	    equ SECTION_MAP_READ
FILE_MAP_ALL_ACCESS equ SECTION_ALL_ACCESS

OF_READ		    equ 0x00000000
OF_WRITE	    equ 0x00000001
OF_READWRITE	    equ 0x00000002
OF_SHARE_COMPAT	    equ 0x00000000
OF_SHARE_EXCLUSIVE  equ 0x00000010
OF_SHARE_DENY_WRITE equ 0x00000020
OF_SHARE_DENY_READ  equ 0x00000030
OF_SHARE_DENY_NONE  equ 0x00000040
OF_PARSE	    equ 0x00000100
OF_DELETE	    equ 0x00000200
OF_VERIFY	    equ 0x00000400
OF_CANCEL	    equ 0x00000800
OF_CREATE	    equ 0x00001000
OF_PROMPT	    equ 0x00002000
OF_EXIST	    equ 0x00004000
OF_REOPEN	    equ 0x00008000

OFS_MAXPATHNAME equ 128

OFSTRUCT	STRUC
cBytes		BYTE ?
fFixedDisk	BYTE ?
nErrCode	WORD ?
Reserved1	WORD ?
Reserved2	WORD ?
szPathName	SBYTE OFS_MAXPATHNAME dup(?)
OFSTRUCT	ENDS

LPOFSTRUCT	TYPEDEF PTR OFSTRUCT
POFSTRUCT	TYPEDEF PTR OFSTRUCT

;
; The MS-MIPS and Alpha compilers support intrinsic functions for interlocked
; increment, decrement, and exchange.
;

WINBASEAPI

if(_WIN32_WINNT GE 0x0500)
GetConsoleWindow	proto _CType
else
GetConsoleWindow_P	typedef proto _CType
GetConsoleWindow_T	typedef ptr GetConsoleWindow_P
externdef		GetConsoleWindow:GetConsoleWindow_T
endif

ifndef _NTOS_

InterlockedIncrement proto _CType \
	      lpAddend: LPLONG
;LONG
InterlockedDecrement proto _CType \
	      lpAddend: LPLONG
;LONG
InterlockedExchange proto _CType \
		Target: LPLONG,
		 Value: LONG
;LONG
InterlockedExchangeAdd proto _CType \
		Addend: LPLONG,
		 Value: LONG
;PVOID
InterlockedCompareExchange proto _CType \
	   Destination: PTR PVOID,
	      Exchange: PVOID,
	     Comperand: PVOID
endif

;BOOL
FreeResource proto _CType \
	      hResData: HGLOBAL
;LPVOID
LockResource proto _CType \
	      hResData: HGLOBAL

;UnlockResource(hResData) ((hResData), 0)
MAXINTATOM	equ 0xC000
;MAKEINTATOM(i)	 (LPTSTR)((DWORD)((WORD)(i)))
INVALID_ATOM	equ 0

WinMain proto _CType \
	     hInstance: HINSTANCE,
	 hPrevInstance: HINSTANCE,
	     lpCmdLine: LPSTR,
	      nShowCmd: SINT

;BOOL
FreeLibrary proto _CType \
	    hLibModule: HMODULE
;VOID
FreeLibraryAndExitThread proto _CType \
	    hLibModule: HMODULE,
	    dwExitCode: DWORD
;BOOL
DisableThreadLibraryCalls proto _CType \
	    hLibModule: HMODULE
;FARPROC
GetProcAddress proto _CType \
	       hModule: HMODULE,
	    lpProcName: LPCSTR
;DWORD
GetVersion proto _CType

;HGLOBAL
GlobalAlloc proto _CType \
		uFlags: UINT,
	       dwBytes: SIZE_T

GlobalFree proto _CType \
		  hMem: HANDLE

GlobalReAlloc proto _CType \
		  hMem: HANDLE,
	       dwBytes: SIZE_T,
		uFlags: UINT

GlobalSize proto _CType \
		  hMem: HANDLE

GlobalFlags proto _CType \
		  hMem: HANDLE

GlobalHandle proto _CType \
		  pMem: PVOID

GlobalLock proto _CType \
		  hMem: HANDLE

GlobalUnlock proto _CType \
		  hMem: HANDLE

GlobalCompact proto _CType \
	     dwMinFree: SIZE_T

GlobalFix proto _CType \
		  hMem: HANDLE

GlobalUnfix proto _CType \
		  hMem: HANDLE

GlobalWire proto _CType \
		  hMem: HANDLE

GlobalUnWire proto _CType \
		  hMem: HANDLE

GlobalMemoryStatus proto _CType \
	      lpBuffer: LPMEMORYSTATUS

GlobalMemoryStatusEx proto _CType \
	      lpBuffer: LPMEMORYSTATUSEX

;HLOCAL
LocalAlloc proto _CType \
		uFlags: UINT,
		uBytes: SIZE_T

LocalReAlloc proto _CType \
		  hMem: HANDLE,
		uBytes: SIZE_T,
		uFlags: UINT

LocalLock proto _CType \
		  hMem: HANDLE

LocalHandle proto _CType \
		  pMem: PVOID

LocalUnlock proto _CType \
		  hMem: HANDLE

LocalSize proto _CType \
		  hMem: HANDLE

LocalFlags proto _CType \
		  hMem: HANDLE

LocalFree proto _CType \
		  hMem: HANDLE

LocalShrink proto _CType \
		  hMem: HANDLE,
	     cbNewSize: SIZE_T

LocalCompact proto _CType \
	      uMinFree: SIZE_T

;BOOL
FlushInstructionCache proto _CType \
	      hProcess: HANDLE,
	 lpBaseAddress: LPCVOID,
		dwSize: DWORD
;LPVOID
VirtualAlloc proto _CType \
	     lpAddress: PVOID,
		dwSize: SIZE_T,
      flAllocationType: DWORD,
	     flProtect: DWORD

VirtualFree proto _CType \
	     lpAddress: PVOID,
		dwSize: SIZE_T,
	    dwFreeType: DWORD

VirtualProtect proto _CType \
	     lpAddress: PVOID,
		dwSize: SIZE_T,
	  flNewProtect: DWORD,
	lpflOldProtect: PTR DWORD

VirtualQuery proto _CType \
	     lpAddress: PVOID,
	      lpBuffer: PTR MEMORY_BASIC_INFORMATION,
	      dwLength: SIZE_T

VirtualAllocEx proto _CType \
	      hProcess: HANDLE,
	     lpAddress: PVOID,
		dwSize: SIZE_T,
      flAllocationType: DWORD,
	     flProtect: DWORD

VirtualFreeEx proto _CType \
	      hProcess: HANDLE,
	     lpAddress: PVOID,
		dwSize: SIZE_T,
	    dwFreeType: DWORD

VirtualProtectEx proto _CType \
	      hProcess: HANDLE,
	     lpAddress: PVOID,
		dwSize: SIZE_T,
	  flNewProtect: DWORD,
	lpflOldProtect: PTR DWORD

VirtualQueryEx proto _CType \
	      hProcess: HANDLE,
	     lpAddress: PVOID,
	      lpBuffer: PTR MEMORY_BASIC_INFORMATION,
	      dwLength: SIZE_T

HeapCreate proto _CType \
	     flOptions: DWORD,
	 dwInitialSize: SIZE_T,
	 dwMaximumSize: SIZE_T

HeapDestroy proto _CType \
		 hHeap: HANDLE

HeapAlloc proto _CType \
		 hHeap: HANDLE,
	       dwFlags: DWORD,
	       dwBytes: SIZE_T

HeapReAlloc proto _CType \
		 hHeap: HANDLE,
	       dwFlags: DWORD,
		 lpMem: PVOID,
	       dwBytes: SIZE_T

HeapFree proto _CType \
		 hHeap: HANDLE,
	       dwFlags: DWORD,
		 lpMem: PVOID

HeapSize proto _CType \
		 hHeap: HANDLE,
	       dwFlags: DWORD,
		 lpMem: PVOID

HeapValidate proto _CType \
		 hHeap: HANDLE,
	       dwFlags: DWORD,
		 lpMem: PVOID

HeapCompact proto _CType \
		 hHeap: HANDLE,
	       dwFlags: DWORD

GetProcessHeap proto _CType

GetProcessHeaps proto _CType \
	 NumberOfHeaps: DWORD,
	  ProcessHeaps: PVOID

PROCESS_HEAP_ENTRY	STRUC SIZE_T
lpData			PVOID ?
cbData			DWORD ?
cbOverhead		BYTE ?
iRegionIndex		BYTE ?
wFlags			WORD ?
UNION
    STRUC ;Block
	hMem		HANDLE ?
	dwReserved	DD 3 dup(?)
    ENDS
    STRUC ;Region
	dwCommittedSize DWORD ?
	dwUnCommittedSize DWORD ?
	lpFirstBlock	PVOID ?
	lpLastBlock	PVOID ?
    ENDS
ENDS
PROCESS_HEAP_ENTRY	ENDS

LPPROCESS_HEAP_ENTRY	TYPEDEF PTR PROCESS_HEAP_ENTRY
PPROCESS_HEAP_ENTRY	TYPEDEF PTR PROCESS_HEAP_ENTRY

PROCESS_HEAP_REGION		equ 0x0001
PROCESS_HEAP_UNCOMMITTED_RANGE	equ 0x0002
PROCESS_HEAP_ENTRY_BUSY		equ 0x0004
PROCESS_HEAP_ENTRY_MOVEABLE	equ 0x0010
PROCESS_HEAP_ENTRY_DDESHARE	equ 0x0020

HeapLock proto _CType hHeap:HANDLE
HeapUnlock proto _CType hHeap:HANDLE
HeapWalk proto _CType \
		 hHeap: HANDLE,
	       lpEntry: PTR LPPROCESS_HEAP_ENTRY

; GetBinaryType return values.

SCS_32BIT_BINARY    equ 0
SCS_DOS_BINARY	    equ 1
SCS_WOW_BINARY	    equ 2
SCS_PIF_BINARY	    equ 3
SCS_POSIX_BINARY    equ 4
SCS_OS216_BINARY    equ 5

;BOOL
GetBinaryTypeA proto _CType \
     lpApplicationName: LPSTR,
	  lpBinaryType: LPDWORD
GetBinaryTypeW proto _CType :LPCWSTR, :LPDWORD
ifdef _UNICODE
GetBinaryType equ <GetBinaryTypeW>
else
GetBinaryType equ <GetBinaryTypeA>
endif

;DWORD
GetShortPathNameA proto _CType \
	  lpszLongPath: LPCSTR,
	 lpszShortPath: LPSTR,
	     cchBuffer: DWORD
GetShortPathNameW proto _CType :LPCWSTR, :LPWSTR, :DWORD
ifdef _UNICODE
GetShortPathName equ <GetShortPathNameW>
else
GetShortPathName equ <GetShortPathNameA>
endif

;DWORD
GetLongPathNameA proto _CType \
	 lpszShortPath: LPSTR,
	  lpszLongPath: LPSTR,
	     cchBuffer: DWORD
GetLongPathNameW proto _CType \
	 lpszShortPath: LPWSTR,
	  lpszLongPath: LPWSTR,
	     cchBuffer: DWORD
ifdef _UNICODE
GetLongPathName equ <GetLongPathNameW>
else
GetLongPathName equ <GetLongPathNameA>
endif

;BOOL
GetProcessAffinityMask proto _CType \
	      hProcess: HANDLE,
 lpProcessAffinityMask: LPDWORD,
  lpSystemAffinityMask: LPDWORD

SetProcessAffinityMask proto _CType \
	      hProcess: HANDLE,
 lpProcessAffinityMask: LPDWORD

GetProcessTimes proto _CType \
	      hProcess: HANDLE,
	lpCreationTime: LPFILETIME,
	    lpExitTime: LPFILETIME,
	  lpKernelTime: LPFILETIME,
	    lpUserTime: LPFILETIME

GetProcessWorkingSetSize proto _CType \
	      hProcess: HANDLE,
lpMinimumWorkingSetSize: LPDWORD,
lpMaximumWorkingSetSize: LPDWORD

SetProcessWorkingSetSize proto _CType \
	      hProcess: HANDLE,
dwMinimumWorkingSetSize: DWORD,
dwMaximumWorkingSetSize: DWORD
;HANDLE
OpenProcess proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
	   dwProcessId: DWORD

GetCurrentProcess proto _CType
GetCurrentProcessId proto _CType

ExitProcess proto _CType uExitCode:UINT

;BOOL
TerminateProcess proto _CType \
	      hProcess: HANDLE,
	     uExitCode: UINT

GetExitCodeProcess proto _CType \
	      hProcess: HANDLE,
	    lpExitCode: LPDWORD

FatalExit proto _CType ExitCode:UINT

GetEnvironmentStringsA proto _CType
GetEnvironmentStringsW proto _CType
ifdef _UNICODE
GetEnvironmentStrings equ <GetEnvironmentStringsW>
else
GetEnvironmentStrings equ <GetEnvironmentStringsA>
endif

FreeEnvironmentStringsA proto _CType :LPSTR
FreeEnvironmentStringsW proto _CType :LPWSTR
ifdef _UNICODE
FreeEnvironmentStrings equ <FreeEnvironmentStringsW>
else
FreeEnvironmentStrings equ <FreeEnvironmentStringsA>
endif

RaiseException proto _CType \
       dwExceptionCode: DWORD,
      dwExceptionFlags: DWORD,
    nNumberOfArguments: DWORD,
	   lpArguments: LPDWORD
;LONG
UnhandledExceptionFilter proto _CType \
	 ExceptionInfo: PTR _EXCEPTION_POINTERS

TOP_LEVEL_EXCEPTION_FILTER   TYPEDEF PROTO :_EXCEPTION_POINTERS
PTOP_LEVEL_EXCEPTION_FILTER  TYPEDEF PTR TOP_LEVEL_EXCEPTION_FILTER
LPTOP_LEVEL_EXCEPTION_FILTER TYPEDEF PTOP_LEVEL_EXCEPTION_FILTER

;LPTOP_LEVEL_EXCEPTION_FILTER
SetUnhandledExceptionFilter proto _CType \
lpTopLevelExceptionFilter: LPTOP_LEVEL_EXCEPTION_FILTER

if(_WIN32_WINNT GE 0x0400)
;LPVOID
CreateFiber proto _CType \
	   dwStackSize: DWORD,
	lpStartAddress: LPFIBER_START_ROUTINE,
	   lpParameter: LPVOID
;VOID
DeleteFiber proto _CType \
	       lpFiber: LPVOID
;LPVOID
ConvertThreadToFiber proto _CType \
	   lpParameter: LPVOID
;VOID
SwitchToFiber proto _CType \
	       lpFiber: LPVOID
;BOOL
SwitchToThread proto _CType
endif

;HANDLE
CreateThread proto _CType \
    lpThreadAttributes: LPSECURITY_ATTRIBUTES,
	   dwStackSize: DWORD,
	lpStartAddress: LPTHREAD_START_ROUTINE,
	   lpParameter: LPVOID,
       dwCreationFlags: DWORD,
	    lpThreadId: LPDWORD

CreateRemoteThread proto _CType \
	      hProcess: HANDLE,
    lpThreadAttributes: LPSECURITY_ATTRIBUTES,
	   dwStackSize: DWORD,
	lpStartAddress: LPTHREAD_START_ROUTINE,
	   lpParameter: LPVOID,
       dwCreationFlags: DWORD,
	    lpThreadId: LPDWORD

GetCurrentThread proto _CType

GetCurrentThreadId proto _CType

SetThreadAffinityMask proto _CType \
	       hThread: HANDLE,
  dwThreadAffinityMask: DWORD

if(_WIN32_WINNT GE 0x0400)
;DWORD
SetThreadIdealProcessor proto _CType \
	       hThread: HANDLE,
      dwIdealProcessor: DWORD
endif

;BOOL
SetProcessPriorityBoost proto _CType \
	      hProcess: HANDLE,
 bDisablePriorityBoost: BOOL

GetProcessPriorityBoost proto _CType \
	      hProcess: HANDLE,
 bDisablePriorityBoost: BOOL

RequestWakeupLatency proto _CType \
	       latency: LATENCY_TIME

SetThreadPriority proto _CType \
	       hThread: HANDLE,
	     nPriority: SINT

SetThreadPriorityBoost proto _CType \
	       hThread: HANDLE,
 bDisablePriorityBoost: BOOL

GetThreadPriorityBoost proto _CType \
	       hThread: HANDLE,
 pDisablePriorityBoost: PBOOL
;int
GetThreadPriority proto _CType \
	       hThread: HANDLE
;BOOL
GetThreadTimes proto _CType \
	       hThread: HANDLE,
	lpCreationTime: LPFILETIME,
	    lpExitTime: LPFILETIME,
	  lpKernelTime: LPFILETIME,
	    lpUserTime: LPFILETIME
;VOID
ExitThread proto _CType \
	    dwExitCode: DWORD
;BOOL
TerminateThread proto _CType \
	       hThread: HANDLE,
	    dwExitCode: DWORD
;BOOL
GetExitCodeThread proto _CType \
	       hThread: HANDLE,
	    lpExitCode: LPDWORD
;BOOL
GetThreadSelectorEntry proto _CType \
	       hThread: HANDLE,
	    dwSelector: DWORD,
       lpSelectorEntry: LPLDT_ENTRY
;EXECUTION_STATE
SetThreadExecutionState proto _CType \
	       esFlags: EXECUTION_STATE
;DWORD
GetLastError proto _CType

SetLastError proto _CType \
	     dwErrCode: DWORD

;HasOverlappedIoCompleted(lpOverlapped) ((lpOverlapped)->Internal != STATUS_PENDING)

;BOOL
GetOverlappedResult proto _CType \
		 hFile: HANDLE,
	  lpOverlapped: LPOVERLAPPED,
lpNumberOfBytesTransferred: LPDWORD,
		 bWait: BOOL
;HANDLE
CreateIoCompletionPort proto _CType \
	    FileHandle: HANDLE,
ExistingCompletionPort: HANDLE,
	 CompletionKey: DWORD,
NumberOfConcurrentThreads: DWORD
;BOOL
GetQueuedCompletionStatus proto _CType \
	CompletionPort: HANDLE,
lpNumberOfBytesTransferred: LPDWORD,
       lpCompletionKey: LPDWORD,
	  lpOverlapped: LPOVERLAPPED,
	dwMilliseconds: DWORD

PostQueuedCompletionStatus proto _CType \
	CompletionPort: HANDLE,
lpNumberOfBytesTransferred: DWORD,
       lpCompletionKey: DWORD,
	  lpOverlapped: LPOVERLAPPED

SEM_FAILCRITICALERRORS	    equ 0x0001
SEM_NOGPFAULTERRORBOX	    equ 0x0002
SEM_NOALIGNMENTFAULTEXCEPT  equ 0x0004
SEM_NOOPENFILEERRORBOX	    equ 0x8000

;UINT
SetErrorMode proto _CType \
		 uMode: UINT
;BOOL
ReadProcessMemory proto _CType \
	      hProcess: HANDLE,
	 lpBaseAddress: LPCVOID,
	      lpBuffer: LPVOID,
		 nSize: DWORD,
   lpNumberOfBytesRead: LPDWORD

WriteProcessMemory proto _CType \
	      hProcess: HANDLE,
	 lpBaseAddress: LPVOID,
	      lpBuffer: LPVOID,
		 nSize: DWORD,
lpNumberOfBytesWritten: LPDWORD
ifndef MIDL_PASS

GetThreadContext proto _CType \
	       hThread: HANDLE,
	     lpContext: LPCONTEXT

SetThreadContext proto _CType \
	       hThread: HANDLE,
	     lpContext: PTR CONTEXT
endif

;DWORD
SuspendThread proto _CType \
	       hThread: HANDLE

ResumeThread proto _CType \
	       hThread: HANDLE

if(_WIN32_WINNT GE 0x0400)

APCFUNC_T TYPEDEF PROTO dwParam:DWORD
PAPCFUNC  TYPEDEF PTR APCFUNC_T

QueueUserAPC proto _CType \
		pfnAPC: PAPCFUNC,
	       hThread: HANDLE,
		dwData: DWORD
endif

if (_WIN32_WINNT GE 0x0400) or (_WIN32_WINDOWS GT 0x0400)
;BOOL
IsDebuggerPresent proto _CType
endif

;VOID
DebugBreak proto _CType
;BOOL
WaitForDebugEvent proto _CType \
	  lpDebugEvent: LPDEBUG_EVENT,
	dwMilliseconds: DWORD

ContinueDebugEvent proto _CType \
	   dwProcessId: DWORD,
	    dwThreadId: DWORD,
      dwContinueStatus: DWORD

DebugActiveProcess proto _CType \
	   dwProcessId: DWORD
;VOID
InitializeCriticalSection proto _CType \
     lpCriticalSection: LPCRITICAL_SECTION

EnterCriticalSection proto _CType \
     lpCriticalSection: LPCRITICAL_SECTION

LeaveCriticalSection proto _CType \
     lpCriticalSection: LPCRITICAL_SECTION

if (_WIN32_WINNT GE 0x0500)
;BOOL
InitializeCriticalSectionAndSpinCount proto _CType \
     lpCriticalSection: LPCRITICAL_SECTION,
	   dwSpinCount: DWORD
;DWORD
SetCriticalSectionSpinCount proto _CType \
     lpCriticalSection: LPCRITICAL_SECTION,
	   dwSpinCount: DWORD
endif

if(_WIN32_WINNT GE 0x0400)
;BOOL
TryEnterCriticalSection proto _CType \
     lpCriticalSection: LPCRITICAL_SECTION
endif

;VOID
DeleteCriticalSection proto _CType \
     lpCriticalSection: LPCRITICAL_SECTION
;BOOL
SetEvent proto _CType \
		hEvent: HANDLE

ResetEvent proto _CType \
		hEvent: HANDLE

PulseEvent proto _CType \
		hEvent: HANDLE

ReleaseSemaphore proto _CType \
	    hSemaphore: HANDLE,
	 lReleaseCount: LONG,
       lpPreviousCount: LPLONG

ReleaseMutex proto _CType \
		hMutex: HANDLE
;DWORD
WaitForSingleObject proto _CType \
	       hHandle: HANDLE,
	dwMilliseconds: DWORD

WaitForMultipleObjects proto _CType \
		nCount: DWORD,
	     lpHandles: PTR HANDLE,
	      bWaitAll: BOOL,
	dwMilliseconds: DWORD
;VOID
Sleep proto _CType \
	dwMilliseconds: DWORD
;HGLOBAL
LoadResource proto _CType \
	       hModule: HMODULE,
	      hResInfo: HRSRC
;DWORD
SizeofResource proto _CType \
	       hModule: HMODULE,
	      hResInfo: HRSRC
;ATOM
GlobalDeleteAtom proto _CType \
		 nAtom: ATOM
;BOOL
InitAtomTable proto _CType \
		 nSize: DWORD
;ATOM
DeleteAtom proto _CType \
		 nAtom: ATOM
;UINT
SetHandleCount proto _CType \
	       uNumber: UINT
;DWORD
GetLogicalDrives proto _CType
;BOOL
LockFile proto _CType \
		 hFile: HANDLE,
       dwFileOffsetLow: DWORD,
      dwFileOffsetHigh: DWORD,
nNumberOfBytesToLockLow: DWORD,
nNumberOfBytesToLockHigh: DWORD

UnlockFile proto _CType \
		 hFile: HANDLE,
       dwFileOffsetLow: DWORD,
      dwFileOffsetHigh: DWORD,
nNumberOfBytesToLockLow: DWORD,
nNumberOfBytesToLockHigh: DWORD

LockFileEx proto _CType \
		 hFile: HANDLE,
	       dwFlags: DWORD,
	    dwReserved: DWORD,
nNumberOfBytesToLockLow: DWORD,
nNumberOfBytesToLockHigh: DWORD,
	  lpOverlapped: LPOVERLAPPED

LOCKFILE_FAIL_IMMEDIATELY   equ 0x00000001
LOCKFILE_EXCLUSIVE_LOCK	    equ 0x00000002

UnlockFileEx proto _CType \
		 hFile: HANDLE,
	    dwReserved: DWORD,
nNumberOfBytesToUnlockLow: DWORD,
nNumberOfBytesToUnlockHigh: DWORD,
	  lpOverlapped: LPOVERLAPPED

BY_HANDLE_FILE_INFORMATION STRUC
dwFileAttributes	DWORD ?
ftCreationTime		FILETIME <>
ftLastAccessTime	FILETIME <>
ftLastWriteTime		FILETIME <>
dwVolumeSerialNumber	DWORD ?
nFileSizeHigh		DWORD ?
nFileSizeLow		DWORD ?
nNumberOfLinks		DWORD ?
nFileIndexHigh		DWORD ?
nFileIndexLow		DWORD ?
BY_HANDLE_FILE_INFORMATION ENDS

PBY_HANDLE_FILE_INFORMATION	TYPEDEF PTR BY_HANDLE_FILE_INFORMATION
LPBY_HANDLE_FILE_INFORMATION	TYPEDEF PTR BY_HANDLE_FILE_INFORMATION

;BOOL
GetFileInformationByHandle proto _CType \
		 hFile: HANDLE,
     lpFileInformation: LPBY_HANDLE_FILE_INFORMATION
;DWORD
GetFileType proto _CType \
		 hFile: HANDLE

GetFileSize proto _CType \
		 hFile: HANDLE,
	lpFileSizeHigh: LPDWORD

if (WINVER GE 0x0502)
;BOOL
GetFileSizeEx proto _CType \
		 hFile: HANDLE,
	    lpFileSize: PLARGE_INTEGER
else
GetFileSizeEx_P typedef proto _CType \
		 hFile: HANDLE,
	    lpFileSize: PLARGE_INTEGER
GetFileSizeEx_T typedef ptr GetFileSizeEx_P
externdef GetFileSizeEx:GetFileSizeEx_T
endif

;HANDLE
GetStdHandle proto _CType \
	    nStdHandle: DWORD
;BOOL
SetStdHandle proto _CType \
	    nStdHandle: DWORD,
	       hHandle: HANDLE

WriteFile proto _CType \
		 hFile: HANDLE,
	      lpBuffer: PVOID,
 nNumberOfBytesToWrite: DWORD,
lpNumberOfBytesWritten: LPDWORD,
	  lpOverlapped: LPOVERLAPPED

ReadFile proto _CType \
		 hFile: HANDLE,
	      lpBuffer: PVOID,
  nNumberOfBytesToRead: DWORD,
   lpNumberOfBytesRead: LPDWORD,
	  lpOverlapped: LPOVERLAPPED

FlushFileBuffers proto _CType \
		 hFile: HANDLE

DeviceIoControl proto _CType \
	       hDevice: HANDLE,
       dwIoControlCode: DWORD,
	    lpInBuffer: PVOID,
	 nInBufferSize: DWORD,
	   lpOutBuffer: PVOID,
	nOutBufferSize: DWORD,
       lpBytesReturned: LPDWORD,
	  lpOverlapped: LPOVERLAPPED

GetDevicePowerState proto _CType \
		 hFile: HANDLE

SetEndOfFile proto _CType \
		 hFile: HANDLE
;DWORD
SetFilePointer proto _CType \
		 hFile: HANDLE,
       lDistanceToMove: LONG,
  lpDistanceToMoveHigh: PLONG,
	  dwMoveMethod: DWORD

if (WINVER GE 0x0502)
;BOOL
SetFilePointerEx proto _CType \
		 hFile: HANDLE,
      liDistanceToMove: LARGE_INTEGER,
      lpNewFilePointer: PLARGE_INTEGER,
	  dwMoveMethod: DWORD
else
SetFilePointerEx_P typedef proto _CType \
		 hFile: HANDLE,
      liDistanceToMove: LARGE_INTEGER,
      lpNewFilePointer: PLARGE_INTEGER,
	  dwMoveMethod: DWORD
SetFilePointerEx_T typedef ptr SetFilePointerEx_P
externdef SetFilePointerEx:SetFilePointerEx_T
endif

;BOOL
FindClose proto _CType \
	     hFindFile: HANDLE

GetFileTime proto _CType \
		 hFile: HANDLE,
	lpCreationTime: LPFILETIME,
      lpLastAccessTime: LPFILETIME,
       lpLastWriteTime: LPFILETIME

SetFileTime proto _CType \
		 hFile: HANDLE,
	lpCreationTime: LPFILETIME,
      lpLastAccessTime: LPFILETIME,
       lpLastWriteTime: LPFILETIME

CloseHandle proto _CType \
	       hObject: HANDLE

DuplicateHandle proto _CType \
  hSourceProcessHandle: HANDLE,
	 hSourceHandle: HANDLE,
  hTargetProcessHandle: HANDLE,
	lpTargetHandle: LPHANDLE,
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
	     dwOptions: DWORD

GetHandleInformation proto _CType \
	       hObject: HANDLE,
	     lpdwFlags: LPDWORD

SetHandleInformation proto _CType \
	       hObject: HANDLE,
		dwMask: DWORD,
	       dwFlags: DWORD

HANDLE_FLAG_INHERIT		equ 0x00000001
HANDLE_FLAG_PROTECT_FROM_CLOSE	equ 0x00000002

HINSTANCE_ERROR equ 32

;DWORD
LoadModule proto _CType \
	  lpModuleName: LPCSTR,
      lpParameterBlock: LPVOID
;UINT
WinExec proto _CType \
	     lpCmdLine: LPCSTR,
	      uCmdShow: UINT
;BOOL
ClearCommBreak proto _CType \
		 hFile: HANDLE

ClearCommError proto _CType \
		 hFile: HANDLE,
	      lpErrors: LPDWORD,
		lpStat: LPCOMSTAT

SetupComm proto _CType \
		 hFile: HANDLE,
	     dwInQueue: DWORD,
	    dwOutQueue: DWORD

EscapeCommFunction proto _CType \
		 hFile: HANDLE,
		dwFunc: DWORD

GetCommConfig proto _CType \
	      hCommDev: HANDLE,
		  lpCC: LPCOMMCONFIG,
	      lpdwSize: LPDWORD

GetCommMask proto _CType \
		 hFile: HANDLE,
	     lpEvtMask: LPDWORD

GetCommProperties proto _CType \
		 hFile: HANDLE,
	    lpCommProp: LPCOMMPROP

GetCommModemStatus proto _CType \
		 hFile: HANDLE,
	   lpModemStat: LPDWORD

GetCommState proto _CType \
		 hFile: HANDLE,
		 lpDCB: LPDCB

GetCommTimeouts proto _CType \
		 hFile: HANDLE,
	lpCommTimeouts: LPCOMMTIMEOUTS

PurgeComm proto _CType \
		 hFile: HANDLE,
	       dwFlags: DWORD

SetCommBreak proto _CType \
		 hFile: HANDLE

SetCommConfig proto _CType \
	      hCommDev: HANDLE,
		  lpCC: LPCOMMCONFIG,
		dwSize: DWORD

SetCommMask proto _CType \
		 hFile: HANDLE,
	     dwEvtMask: DWORD

SetCommState proto _CType \
		 hFile: HANDLE,
		 lpDCB: LPDCB

SetCommTimeouts proto _CType \
		 hFile: HANDLE,
	lpCommTimeouts: LPCOMMTIMEOUTS

TransmitCommChar proto _CType \
		 hFile: HANDLE,
		 cChar: UINT ; char

WaitCommEvent proto _CType \
		 hFile: HANDLE,
	     lpEvtMask: LPDWORD,
	  lpOverlapped: LPOVERLAPPED
;DWORD
SetTapePosition proto _CType \
	       hDevice: HANDLE,
      dwPositionMethod: DWORD,
	   dwPartition: DWORD,
	   dwOffsetLow: DWORD,
	  dwOffsetHigh: DWORD,
	    bImmediate: BOOL

GetTapePosition proto _CType \
	       hDevice: HANDLE,
	dwPositionType: DWORD,
	 lpdwPartition: LPDWORD,
	 lpdwOffsetLow: LPDWORD,
	lpdwOffsetHigh: LPDWORD

PrepareTape proto _CType \
	       hDevice: HANDLE,
	   dwOperation: DWORD,
	    bImmediate: BOOL

EraseTape proto _CType \
	       hDevice: HANDLE,
	   dwEraseType: DWORD,
	    bImmediate: BOOL

CreateTapePartition proto _CType \
	       hDevice: HANDLE,
     dwPartitionMethod: DWORD,
	       dwCount: DWORD,
		dwSize: DWORD

WriteTapemark proto _CType \
	       hDevice: HANDLE,
	dwTapemarkType: DWORD,
       dwTapemarkCount: DWORD,
	    bImmediate: BOOL

GetTapeStatus proto _CType \
	       hDevice: HANDLE

GetTapeParameters proto _CType \
	       hDevice: HANDLE,
	   dwOperation: DWORD,
	      lpdwSize: LPDWORD,
     lpTapeInformation: LPVOID

GET_TAPE_MEDIA_INFORMATION equ 0
GET_TAPE_DRIVE_INFORMATION equ 1

SetTapeParameters proto _CType \
	       hDevice: HANDLE,
	   dwOperation: DWORD,
     lpTapeInformation: PVOID

SET_TAPE_MEDIA_INFORMATION equ 0
SET_TAPE_DRIVE_INFORMATION equ 1

;BOOL
Beep proto _CType \
		dwFreq: DWORD,
	    dwDuration: DWORD
;int
MulDiv proto _CType \
	       nNumber: SINT,
	    nNumerator: SINT,
	  nDenominator: SINT
;VOID
GetSystemTime proto _CType \
	  lpSystemTime: LPSYSTEMTIME

GetSystemTimeAsFileTime proto _CType \
lpSystemTimeAsFileTime: LPFILETIME
;BOOL
SetSystemTime proto _CType \
	  lpSystemTime: LPSYSTEMTIME
;VOID
GetLocalTime proto _CType \
	  lpSystemTime: LPSYSTEMTIME
;BOOL
SetLocalTime proto _CType \
	  lpSystemTime: LPSYSTEMTIME
;VOID
GetSystemInfo proto _CType \
	  lpSystemInfo: LPSYSTEM_INFO
;BOOL
IsProcessorFeaturePresent proto _CType \
      ProcessorFeature: DWORD

TIME_ZONE_INFORMATION	STRUC
Bias			dd ?		;LONG
StandardName		dw 32 dup(?)	;WCHAR[ 32 ];
StandardDate		SYSTEMTIME <>
StandardBias		dd ?		;LONG
DaylightName		dw 32 dup(?)	;WCHAR[ 32 ];
DaylightDate		SYSTEMTIME <>
DaylightBias		dd ?		;LONG
TIME_ZONE_INFORMATION	ENDS

PTIME_ZONE_INFORMATION	TYPEDEF PTR TIME_ZONE_INFORMATION
LPTIME_ZONE_INFORMATION TYPEDEF PTR TIME_ZONE_INFORMATION

;BOOL
SystemTimeToTzSpecificLocalTime proto _CType \
 lpTimeZoneInformation: LPTIME_ZONE_INFORMATION,
       lpUniversalTime: LPSYSTEMTIME,
	   lpLocalTime: LPSYSTEMTIME
;DWORD
GetTimeZoneInformation proto _CType \
 lpTimeZoneInformation: LPTIME_ZONE_INFORMATION
;BOOL
SetTimeZoneInformation proto _CType \
 lpTimeZoneInformation: LPTIME_ZONE_INFORMATION

;
; Routines to convert back and forth between system time and file time
;

SystemTimeToFileTime proto _CType \
	  lpSystemTime: LPSYSTEMTIME,
	    lpFileTime: LPFILETIME

FileTimeToLocalFileTime proto _CType \
	    lpFileTime: LPFILETIME,
       lpLocalFileTime: LPFILETIME

LocalFileTimeToFileTime proto _CType \
       lpLocalFileTime: LPFILETIME,
	    lpFileTime: LPFILETIME

FileTimeToSystemTime proto _CType \
	    lpFileTime: LPFILETIME,
	  lpSystemTime: LPSYSTEMTIME
;LONG
CompareFileTime proto _CType \
	   lpFileTime1: LPFILETIME,
	   lpFileTime2: LPFILETIME
;BOOL
FileTimeToDosDateTime proto _CType \
	    lpFileTime: LPFILETIME,	;; pointer to 64-bit file time
	     lpFatDate: LPWORD,		;; pointer to variable for MS-DOS date
	     lpFatTime: LPWORD		;; pointer to variable for MS-DOS time

; BOOL - 16-bit date and time
DosDateTimeToFileTime proto _CType \
	      wFatDate: WORD,		;; 16-bit MS-DOS date
	      wFatTime: WORD,		;; 16-bit MS-DOS time
	    lpFileTime: LPFILETIME	;; pointer to buffer for 64-bit file time
;DWORD
GetTickCount proto _CType
;BOOL
SetSystemTimeAdjustment proto _CType \
      dwTimeAdjustment: DWORD,
bTimeAdjustmentDisabled: BOOL

GetSystemTimeAdjustment proto _CType \
      lpTimeAdjustment: PDWORD,
       lpTimeIncrement: PDWORD,
lpTimeAdjustmentDisabled: PBOOL

ifndef MIDL_PASS
;DWORD
FormatMessageA proto _CType \
	       dwFlags: DWORD,
	      lpSource: PVOID,
	   dwMessageId: DWORD,
	  dwLanguageId: DWORD,
	      lpBuffer: LPSTR,
		 nSize: DWORD,
	     Arguments: PVOID	; va_list *
FormatMessageW proto _CType \
	       dwFlags: DWORD,
	      lpSource: PVOID,
	   dwMessageId: DWORD,
	  dwLanguageId: DWORD,
	      lpBuffer: LPWSTR,
		 nSize: DWORD,
	     Arguments: PVOID	; va_list *
ifdef _UNICODE
FormatMessage equ <FormatMessageW>
else
FormatMessage equ <FormatMessageA>
endif
endif

FORMAT_MESSAGE_ALLOCATE_BUFFER equ 0x00000100
FORMAT_MESSAGE_IGNORE_INSERTS  equ 0x00000200
FORMAT_MESSAGE_FROM_STRING     equ 0x00000400
FORMAT_MESSAGE_FROM_HMODULE    equ 0x00000800
FORMAT_MESSAGE_FROM_SYSTEM     equ 0x00001000
FORMAT_MESSAGE_ARGUMENT_ARRAY  equ 0x00002000
FORMAT_MESSAGE_MAX_WIDTH_MASK  equ 0x000000FF


;BOOL
CreatePipe proto _CType \
	     hReadPipe: PHANDLE,
	    hWritePipe: PHANDLE,
      lpPipeAttributes: LPSECURITY_ATTRIBUTES,
		 nSize: DWORD

ConnectNamedPipe proto _CType \
	    hNamedPipe: HANDLE,
	  lpOverlapped: LPOVERLAPPED

DisconnectNamedPipe proto _CType \
	    hNamedPipe: HANDLE

SetNamedPipeHandleState proto _CType \
	    hNamedPipe: HANDLE,
		lpMode: LPDWORD,
  lpMaxCollectionCount: LPDWORD,
  lpCollectDataTimeout: LPDWORD

GetNamedPipeInfo proto _CType \
	    hNamedPipe: HANDLE,
	       lpFlags: LPDWORD,
       lpOutBufferSize: LPDWORD,
	lpInBufferSize: LPDWORD,
	lpMaxInstances: LPDWORD

PeekNamedPipe proto _CType \
	    hNamedPipe: HANDLE,
	      lpBuffer: PVOID,
	   nBufferSize: DWORD,
	   lpBytesRead: LPDWORD,
     lpTotalBytesAvail: LPDWORD,
lpBytesLeftThisMessage: LPDWORD

TransactNamedPipe proto _CType \
	    hNamedPipe: HANDLE,
	    lpInBuffer: PVOID,
	 nInBufferSize: DWORD,
	   lpOutBuffer: PVOID,
	nOutBufferSize: DWORD,
	   lpBytesRead: LPDWORD,
	  lpOverlapped: LPOVERLAPPED
;HANDLE
CreateMailslotA proto _CType \
		lpName: LPSTR,
       nMaxMessageSize: DWORD,
	  lReadTimeout: DWORD,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
CreateMailslotW proto _CType \
		lpName: LPWSTR,
       nMaxMessageSize: DWORD,
	  lReadTimeout: DWORD,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
ifdef _UNICODE
CreateMailslot equ <CreateMailslotW>
else
CreateMailslot equ <CreateMailslotA>
endif

;BOOL
GetMailslotInfo proto _CType \
	     hMailslot: HANDLE,
      lpMaxMessageSize: LPDWORD,
	    lpNextSize: LPDWORD,
	lpMessageCount: LPDWORD,
	 lpReadTimeout: LPDWORD

SetMailslotInfo proto _CType \
	     hMailslot: HANDLE,
	  lReadTimeout: DWORD
;PVOID
MapViewOfFile proto _CType \
    hFileMappingObject: HANDLE,
       dwDesiredAccess: DWORD,
      dwFileOffsetHigh: DWORD,
       dwFileOffsetLow: DWORD,
  dwNumberOfBytesToMap: DWORD
;PVOID64
MapViewOfFileVlm proto _CType \
    hFileMappingObject: HANDLE,
       dwDesiredAccess: DWORD,
	      ulOffset: DWORDLONG,
  ulNumberOfBytesToMap: DWORDLONG,
	 lpBaseAddress: PVOID64
;BOOL
FlushViewOfFile proto _CType \
	 lpBaseAddress: LPCVOID,
dwNumberOfBytesToFlush: DWORD

UnmapViewOfFile proto _CType \
	 lpBaseAddress: LPCVOID

UnmapViewOfFileVlm proto _CType \
	 lpBaseAddress: PVOID64

;
; File Encryption API
;
WINADVAPI
EncryptFileA proto _CType \
	    lpFileName: LPCSTR
EncryptFileW proto _CType \
	    lpFileName: LPCWSTR
ifdef _UNICODE
EncryptFile equ <EncryptFileW>
else
EncryptFile equ <EncryptFileA>
endif

DecryptFileA proto _CType \
	    lpFileName: LPCSTR,
	    dwReserved: DWORD
DecryptFileW proto _CType \
	    lpFileName: LPCWSTR,
	    dwReserved: DWORD
ifdef _UNICODE
DecryptFile equ <DecryptFileW>
else
DecryptFile equ <DecryptFileA>
endif

;
; Currently defined recovery flags
;

EFS_USE_RECOVERY_KEYS	equ 1

PFE_EXPORT_T	TYPEDEF PROTO :PTR BYTE, :PVOID, :ULONG
PFE_EXPORT_FUNC TYPEDEF PTR PFE_EXPORT_T
PFE_IMPORT_FUNC TYPEDEF PTR PFE_EXPORT_T

;
;  OpenRaw flag values
;

CREATE_FOR_IMPORT  equ 1
CREATE_FOR_DIR	   equ 2

;DWORD
OpenRawA proto _CType \
	    lpFileName: LPCSTR,
	       ulFlags: ULONG,
	     pvContext: PTR PVOID
OpenRawW proto _CType \
	    lpFileName: LPCWSTR,
	       ulFlags: ULONG,
	     pvContext: PTR PVOID
ifdef _UNICODE
OpenRaw equ <OpenRawW>
else
OpenRaw equ <OpenRawA>
endif

ReadRaw proto _CType \
      pfExportCallback: PFE_EXPORT_FUNC,
     pvCallbackContext: PVOID,
	     pvContext: PVOID

WriteRaw proto _CType \
      pfImportCallback: PFE_IMPORT_FUNC,
     pvCallbackContext: PVOID,
	     pvContext: PVOID
;VOID
CloseRaw proto _CType \
	     pvContext: PVOID

RECOVERY_AGENT_INFORMATIONA	STRUC
NextEntryOffset			dd ?
AgentNameLength			dd ?
AgentInformation		db ?
RECOVERY_AGENT_INFORMATIONA	ENDS

RECOVERY_AGENT_INFORMATIONW	STRUC
NextEntryOffset			dd ?
AgentNameLength			dd ?
AgentInformation		dw ?
RECOVERY_AGENT_INFORMATIONW	ENDS

LPRECOVERY_AGENT_INFORMATIONA	TYPEDEF PTR RECOVERY_AGENT_INFORMATIONA
LPRECOVERY_AGENT_INFORMATIONW	TYPEDEF PTR RECOVERY_AGENT_INFORMATIONW

ifdef _UNICODE
RECOVERY_AGENT_INFORMATION	typedef RECOVERY_AGENT_INFORMATIONW
LPRECOVERY_AGENT_INFORMATION	typedef LPRECOVERY_AGENT_INFORMATIONW
else
RECOVERY_AGENT_INFORMATION	typedef RECOVERY_AGENT_INFORMATIONA
LPRECOVERY_AGENT_INFORMATION	typedef LPRECOVERY_AGENT_INFORMATIONA
endif

;DWORD
QueryRecoveryAgentsA proto _CType \
	    lpFileName: LPCSTR,
	    AgentCount: PDWORD,
RecoveryAgentInformation: PTR LPRECOVERY_AGENT_INFORMATIONA

QueryRecoveryAgentsW proto _CType \
	    lpFileName: LPCWSTR,
	    AgentCount: PDWORD,
RecoveryAgentInformation: PTR LPRECOVERY_AGENT_INFORMATIONW
ifdef _UNICODE
QueryRecoveryAgents equ <QueryRecoveryAgentsW>
else
QueryRecoveryAgents equ <QueryRecoveryAgentsA>
endif

;
; _l Compat Functions
;
WINBASEAPI
lstrcatA	PROTO _CType :LPSTR, :LPSTR
lstrcatW	PROTO _CType :LPWSTR, :LPWSTR
lstrcmpA	PROTO _CType :LPSTR, :LPSTR
lstrcmpW	PROTO _CType :LPWSTR, :LPWSTR
lstrcmpiA	PROTO _CType :LPSTR, :LPSTR
lstrcmpiW	PROTO _CType :LPWSTR, :LPWSTR
lstrcpyA	PROTO _CType :LPSTR, :LPSTR
lstrcpyW	PROTO _CType :LPWSTR, :LPWSTR
lstrcpynA	PROTO _CType :LPSTR, :LPSTR, :SIZE_T
lstrcpynW	PROTO _CType :LPWSTR, :LPWSTR, :SIZE_T
lstrlenA	PROTO _CType :LPSTR
lstrlenW	PROTO _CType :LPWSTR

IFDEF _UNICODE
lstrcat		equ <lstrcatW>
lstrcmp		equ <lstrcmpW>
lstrcmpi	equ <lstrcmpiW>
lstrcpy		equ <lstrcpyW>
lstrcpyn	equ <lstrcpynW>
lstrlen		equ <lstrlenW>
ELSE
lstrcat		equ <lstrcatA>
lstrcmp		equ <lstrcmpA>
lstrcmpi	equ <lstrcmpiA>
lstrcpy		equ <lstrcpyA>
lstrcpyn	equ <lstrcpynA>
lstrlen		equ <lstrlenA>
ENDIF


;HFILE
OpenFile proto _CType \
	    lpFileName: LPCSTR,
	  lpReOpenBuff: LPOFSTRUCT,
		uStyle: UINT

_lopen proto _CType \
	    lpPathName: LPCSTR,
	    iReadWrite: SINT

_lcreat proto _CType \
	    lpPathName: LPCSTR,
	    iAttribute: UINT
;UINT
_lread proto _CType \
		 hFile: HFILE,
	      lpBuffer: PVOID,
		uBytes: UINT

_lwrite proto _CType \
		 hFile: HFILE,
	      lpBuffer: PVOID,
		uBytes: UINT
;long
_hread proto _CType \
		 hFile: HFILE,
	      lpBuffer: PVOID,
		lBytes: LONG

_hwrite proto _CType \
		 hFile: HFILE,
	      lpBuffer: PVOID,
		lBytes: LONG
;HFILE
_lclose proto _CType \
		 hFile: HFILE
;LONG
_llseek proto _CType \
		 hFile: HFILE,
	       lOffset: LONG,
	       iOrigin: SINT
;BOOL
IsTextUnicode proto _CType \
	      lpBuffer: PVOID,
		    cb: SINT,
		   lpi: LPINT
;DWORD
TlsAlloc proto _CType

TLS_OUT_OF_INDEXES equ 0xFFFFFFFF

;LPVOID
TlsGetValue proto _CType \
	    dwTlsIndex: DWORD
;BOOL
TlsSetValue proto _CType \
	    dwTlsIndex: DWORD,
	    lpTlsValue: PVOID

TlsFree proto _CType \
	    dwTlsIndex: DWORD

OVERLAPPED_T TYPEDEF PROTO :DWORD, :DWORD, :LPOVERLAPPED
LPOVERLAPPED_COMPLETION_ROUTINE TYPEDEF PTR OVERLAPPED_T

;DWORD
SleepEx proto _CType \
	dwMilliseconds: DWORD,
	    bAlertable: BOOL

WaitForSingleObjectEx proto _CType \
	       hHandle: HANDLE,
	dwMilliseconds: DWORD,
	    bAlertable: BOOL

WaitForMultipleObjectsEx proto _CType \
		nCount: DWORD,
	     lpHandles: LPHANDLE,
	      bWaitAll: BOOL,
	dwMilliseconds: DWORD,
	    bAlertable: BOOL

if(_WIN32_WINNT GE 0x0400)

SignalObjectAndWait proto _CType \
       hObjectToSignal: HANDLE,
       hObjectToWaitOn: HANDLE,
	dwMilliseconds: DWORD,
	    bAlertable: BOOL
endif

;BOOL
ReadFileEx proto _CType \
		 hFile: HANDLE,
	      lpBuffer: PVOID,
  nNumberOfBytesToRead: DWORD,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPOVERLAPPED_COMPLETION_ROUTINE

WriteFileEx proto _CType \
		 hFile: HANDLE,
	      lpBuffer: PVOID,
 nNumberOfBytesToWrite: DWORD,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPOVERLAPPED_COMPLETION_ROUTINE

BackupRead proto _CType \
		 hFile: HANDLE,
	      lpBuffer: LPBYTE,
  nNumberOfBytesToRead: DWORD,
   lpNumberOfBytesRead: LPDWORD,
		bAbort: BOOL,
      bProcessSecurity: BOOL,
	     lpContext: PTR PVOID

BackupSeek proto _CType \
		 hFile: HANDLE,
      dwLowBytesToSeek: DWORD,
     dwHighBytesToSeek: DWORD,
     lpdwLowByteSeeked: LPDWORD,
    lpdwHighByteSeeked: LPDWORD,
	     lpContext: PTR PVOID

BackupWrite proto _CType \
		 hFile: HANDLE,
	      lpBuffer: LPBYTE,
 nNumberOfBytesToWrite: DWORD,
lpNumberOfBytesWritten: LPDWORD,
		bAbort: BOOL,
      bProcessSecurity: BOOL,
	     lpContext: PTR PVOID

;
;  Stream id structure
;
WIN32_STREAM_ID		STRUC
dwStreamId		dd ?
dwStreamAttributes	dd ?
_Size			LARGE_INTEGER <>
dwStreamNameSize	dd ?
cStreamName		dw ANYSIZE_ARRAY dup(?)
WIN32_STREAM_ID		ENDS

LPWIN32_STREAM_ID typedef ptr WIN32_STREAM_ID

;
;  Stream Ids
;

BACKUP_INVALID		equ 0x00000000
BACKUP_DATA		equ 0x00000001
BACKUP_EA_DATA		equ 0x00000002
BACKUP_SECURITY_DATA	equ 0x00000003
BACKUP_ALTERNATE_DATA	equ 0x00000004
BACKUP_LINK		equ 0x00000005
BACKUP_PROPERTY_DATA	equ 0x00000006
BACKUP_OBJECT_ID	equ 0x00000007
BACKUP_REPARSE_DATA	equ 0x00000008
BACKUP_SPARSE_BLOCK	equ 0x00000009


;
;  Stream Attributes
;

STREAM_NORMAL_ATTRIBUTE		equ 0x00000000
STREAM_MODIFIED_WHEN_READ	equ 0x00000001
STREAM_CONTAINS_SECURITY	equ 0x00000002
STREAM_CONTAINS_PROPERTIES	equ 0x00000004
STREAM_SPARSE_ATTRIBUTE		equ 0x00000008

;BOOL
ReadFileScatter proto _CType \
		 hFile: HANDLE,
	 aSegmentArray: FILE_SEGMENT_ELEMENT,
  nNumberOfBytesToRead: DWORD,
	    lpReserved: LPDWORD,
	  lpOverlapped: LPOVERLAPPED

WriteFileGather proto _CType \
		 hFile: HANDLE,
	 aSegmentArray: FILE_SEGMENT_ELEMENT,
 nNumberOfBytesToWrite: DWORD,
	    lpReserved: LPDWORD,
	  lpOverlapped: LPOVERLAPPED

;
; Dual Mode API below this line. Dual Mode Structures also included.
;

STARTF_USESHOWWINDOW	equ 0x00000001
STARTF_USESIZE		equ 0x00000002
STARTF_USEPOSITION	equ 0x00000004
STARTF_USECOUNTCHARS	equ 0x00000008
STARTF_USEFILLATTRIBUTE equ 0x00000010
STARTF_RUNFULLSCREEN	equ 0x00000020	; ignored for non-x86 platforms
STARTF_FORCEONFEEDBACK	equ 0x00000040
STARTF_FORCEOFFFEEDBACK equ 0x00000080
STARTF_USESTDHANDLES	equ 0x00000100
if(WINVER GE 0x0400)
STARTF_USEHOTKEY	equ 0x00000200
endif

STARTUPINFOA	STRUC
cb		dd ?
lpReserved	LPSTR ?
lpDesktop	LPSTR ?
lpTitle		LPSTR ?
dwX		dd ?
dwY		dd ?
dwXSize		dd ?
dwYSize		dd ?
dwXCountChars	dd ?
dwYCountChars	dd ?
dwFillAttribute dd ?
dwFlags		dd ?
wShowWindow	dw ?
cbReserved2	dw ?
lpReserved2	LPBYTE ?
hStdInput	HANDLE ?
hStdOutput	HANDLE ?
hStdError	HANDLE ?
STARTUPINFOA	ENDS

LPSTARTUPINFOA	TYPEDEF PTR STARTUPINFOA

STARTUPINFOW	STRUC
cb		dd ?
lpReserved	LPWSTR ?
lpDesktop	LPWSTR ?
lpTitle		LPWSTR ?
dwX		dd ?
dwY		dd ?
dwXSize		dd ?
dwYSize		dd ?
dwXCountChars	dd ?
dwYCountChars	dd ?
dwFillAttribute dd ?
dwFlags		dd ?
wShowWindow	dw ?
cbReserved2	dw ?
lpReserved2	LPBYTE ?
hStdInput	HANDLE ?
hStdOutput	HANDLE ?
hStdError	HANDLE ?
STARTUPINFOW	ENDS

LPSTARTUPINFOW	TYPEDEF PTR STARTUPINFOW

ifdef _UNICODE
STARTUPINFO	typedef STARTUPINFOW
LPSTARTUPINFO	typedef LPSTARTUPINFOW
else
STARTUPINFO	typedef STARTUPINFOA
LPSTARTUPINFO	typedef LPSTARTUPINFOA
endif

SHUTDOWN_NORETRY	equ 0x00000001

WIN32_FIND_DATAA	STRUC
dwFileAttributes	dd ?
ftCreationTime		dq ?
ftLastAccessTime	dq ?
ftLastWriteTime		dq ?
nFileSizeHigh		dd ?
nFileSizeLow		dd ?
dwReserved0		dd ?
dwReserved1		dd ?
cFileName		SBYTE 260 dup(?)
cAlternateFileName	SBYTE 14 dup(?)
WIN32_FIND_DATAA	ENDS

WIN32_FIND_DATAW	STRUC
dwFileAttributes	dd ?
ftCreationTime		dq ?
ftLastAccessTime	dq ?
ftLastWriteTime		dq ?
nFileSizeHigh		dd ?
nFileSizeLow		dd ?
dwReserved0		dd ?
dwReserved1		dd ?
cFileName		WORD 260 dup(?)
cAlternateFileName	WORD 14 dup(?)
WIN32_FIND_DATAW	ENDS

PWIN32_FIND_DATAA	TYPEDEF PTR WIN32_FIND_DATAA
PWIN32_FIND_DATAW	TYPEDEF PTR WIN32_FIND_DATAW
LPWIN32_FIND_DATAA	TYPEDEF PTR WIN32_FIND_DATAA
LPWIN32_FIND_DATAW	TYPEDEF PTR WIN32_FIND_DATAW

ifdef _UNICODE
WIN32_FIND_DATA		typedef WIN32_FIND_DATAW
PWIN32_FIND_DATA	typedef PWIN32_FIND_DATAW
LPWIN32_FIND_DATA	typedef LPWIN32_FIND_DATAW
else
WIN32_FIND_DATA		typedef WIN32_FIND_DATAA
PWIN32_FIND_DATA	typedef PWIN32_FIND_DATAA
LPWIN32_FIND_DATA	typedef LPWIN32_FIND_DATAA
endif

WIN32_FILE_ATTRIBUTE_DATA STRUC
dwFileAttributes	dd ?
ftCreationTime		FILETIME <>
ftLastAccessTime	FILETIME <>
ftLastWriteTime		FILETIME <>
nFileSizeHigh		dd ?
nFileSizeLow		dd ?
WIN32_FILE_ATTRIBUTE_DATA ENDS

LPWIN32_FILE_ATTRIBUTE_DATA	TYPEDEF PTR WIN32_FILE_ATTRIBUTE_DATA

;HANDLE
CreateMutexA proto _CType \
     lpMutexAttributes: LPSECURITY_ATTRIBUTES,
	 bInitialOwner: BOOL,
		lpName: LPCSTR
CreateMutexW proto _CType \
     lpMutexAttributes: LPSECURITY_ATTRIBUTES,
	 bInitialOwner: BOOL,
		lpName: LPCWSTR
ifdef _UNICODE
CreateMutex equ <CreateMutexW>
else
CreateMutex equ <CreateMutexA>
endif

OpenMutexA proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPCSTR
OpenMutexW proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPCWSTR
ifdef _UNICODE
OpenMutex equ <OpenMutexW>
else
OpenMutex equ <OpenMutexA>
endif

CreateEventA proto _CType \
     lpEventAttributes: LPSECURITY_ATTRIBUTES,
	  bManualReset: BOOL,
	 bInitialState: BOOL,
		lpName: LPCSTR
CreateEventW proto _CType \
     lpEventAttributes: LPSECURITY_ATTRIBUTES,
	  bManualReset: BOOL,
	 bInitialState: BOOL,
		lpName: LPCWSTR
ifdef _UNICODE
CreateEvent equ <CreateEventW>
else
CreateEvent equ <CreateEventA>
endif

OpenEventA proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPCSTR
OpenEventW proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPCWSTR
ifdef _UNICODE
OpenEvent equ <OpenEventW>
else
OpenEvent equ <OpenEventA>
endif

CreateSemaphoreA proto _CType \
 lpSemaphoreAttributes: LPSECURITY_ATTRIBUTES,
	 lInitialCount: LONG,
	 lMaximumCount: LONG,
		lpName: LPCSTR
CreateSemaphoreW proto _CType \
 lpSemaphoreAttributes: LPSECURITY_ATTRIBUTES,
	 lInitialCount: LONG,
	 lMaximumCount: LONG,
		lpName: LPCWSTR
ifdef _UNICODE
CreateSemaphore equ <CreateSemaphoreW>
else
CreateSemaphore equ <CreateSemaphoreA>
endif

OpenSemaphoreA proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPCSTR
OpenSemaphoreW proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPCWSTR
ifdef _UNICODE
OpenSemaphore equ <OpenSemaphoreW>
else
OpenSemaphore equ <OpenSemaphoreA>
endif

if (_WIN32_WINNT GE 0x0400) or (_WIN32_WINDOWS GT 0x0400)

TIMERAPCROUTINE_T TYPEDEF PROTO :PVOID, :DWORD, :DWORD
PTIMERAPCROUTINE  TYPEDEF PTR TIMERAPCROUTINE_T


CreateWaitableTimerA proto _CType \
     lpTimerAttributes: LPSECURITY_ATTRIBUTES,
	  bManualReset: BOOL,
	   lpTimerName: LPCSTR
CreateWaitableTimerW proto _CType \
     lpTimerAttributes: LPSECURITY_ATTRIBUTES,
	  bManualReset: BOOL,
	   lpTimerName: LPCWSTR
ifdef _UNICODE
CreateWaitableTimer equ <CreateWaitableTimerW>
else
CreateWaitableTimer equ <CreateWaitableTimerA>
endif

OpenWaitableTimerA proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
	   lpTimerName: LPCSTR
OpenWaitableTimerW proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
	   lpTimerName: LPCWSTR
ifdef _UNICODE
OpenWaitableTimer equ <OpenWaitableTimerW>
else
OpenWaitableTimer equ <OpenWaitableTimerA>
endif

;BOOL
SetWaitableTimer proto _CType \
		hTimer: HANDLE,
	     lpDueTime: PTR LARGE_INTEGER,
	       lPeriod: LONG,
  pfnCompletionRoutine: PTIMERAPCROUTINE,
lpArgToCompletionRoutine: PVOID,
	       fResume: BOOL

CancelWaitableTimer proto _CType \
		hTimer: HANDLE
endif

;HANDLE
CreateFileMappingA proto _CType \
		 hFile: HANDLE,
lpFileMappingAttributes: LPSECURITY_ATTRIBUTES,
	     flProtect: DWORD,
     dwMaximumSizeHigh: DWORD,
      dwMaximumSizeLow: DWORD,
		lpName: LPCSTR
CreateFileMappingW proto _CType \
		 hFile: HANDLE,
lpFileMappingAttributes: LPSECURITY_ATTRIBUTES,
	     flProtect: DWORD,
     dwMaximumSizeHigh: DWORD,
      dwMaximumSizeLow: DWORD,
		lpName: LPCWSTR
ifdef _UNICODE
CreateFileMapping equ <CreateFileMappingW>
else
CreateFileMapping equ <CreateFileMappingA>
endif

OpenFileMappingA proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPCSTR
OpenFileMappingW proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPCWSTR
ifdef _UNICODE
OpenFileMapping equ <OpenFileMappingW>
else
OpenFileMapping equ <OpenFileMappingA>
endif

;DWORD
GetLogicalDriveStringsA proto _CType \
	 nBufferLength: DWORD,
	      lpBuffer: LPSTR
GetLogicalDriveStringsW proto _CType \
	 nBufferLength: DWORD,
	      lpBuffer: LPWSTR
ifdef _UNICODE
GetLogicalDriveStrings equ <GetLogicalDriveStringsW>
else
GetLogicalDriveStrings equ <GetLogicalDriveStringsA>
endif

;HMODULE
LoadLibraryA proto _CType \
	 lpLibFileName: LPCSTR	; address of filename of executable module
LoadLibraryW proto _CType \
	 lpLibFileName: LPCWSTR
ifdef _UNICODE
LoadLibrary equ <LoadLibraryW>
else
LoadLibrary equ <LoadLibraryA>
endif

LoadLibraryExA proto _CType \
	 lpLibFileName: LPCSTR,
		 hFile: HANDLE,
	       dwFlags: DWORD
LoadLibraryExW proto _CType \
	 lpLibFileName: LPCWSTR,
		 hFile: HANDLE,
	       dwFlags: DWORD
ifdef _UNICODE
LoadLibraryEx equ <LoadLibraryExW>
else
LoadLibraryEx equ <LoadLibraryExA>
endif


DONT_RESOLVE_DLL_REFERENCES	equ 0x00000001
LOAD_LIBRARY_AS_DATAFILE	equ 0x00000002
LOAD_WITH_ALTERED_SEARCH_PATH	equ 0x00000008


;DWORD
GetModuleFileNameA proto _CType \
	       hModule: HMODULE,
	    lpFilename: LPSTR,
		 nSize: DWORD
GetModuleFileNameW proto _CType \
	       hModule: HMODULE,
	    lpFilename: LPWSTR,
		 nSize: DWORD
ifdef _UNICODE
GetModuleFileName equ <GetModuleFileNameW>
else
GetModuleFileName equ <GetModuleFileNameA>
endif

;HMODULE
GetModuleHandleA proto _CType \
	  lpModuleName: LPCSTR
GetModuleHandleW proto _CType \
	  lpModuleName: LPCWSTR
ifdef _UNICODE
GetModuleHandle equ <GetModuleHandleW>
else
GetModuleHandle equ <GetModuleHandleA>
endif

;BOOL
CreateProcessA proto _CType \
     lpApplicationName: LPCSTR,
	 lpCommandLine: LPSTR,
   lpProcessAttributes: LPSECURITY_ATTRIBUTES,
    lpThreadAttributes: LPSECURITY_ATTRIBUTES,
       bInheritHandles: BOOL,
       dwCreationFlags: DWORD,
	 lpEnvironment: PVOID,
    lpCurrentDirectory: LPCSTR,
	 lpStartupInfo: LPSTARTUPINFOA,
  lpProcessInformation: LPPROCESS_INFORMATION
CreateProcessW proto _CType \
     lpApplicationName: LPCWSTR,
	 lpCommandLine: LPWSTR,
   lpProcessAttributes: LPSECURITY_ATTRIBUTES,
    lpThreadAttributes: LPSECURITY_ATTRIBUTES,
       bInheritHandles: BOOL,
       dwCreationFlags: DWORD,
	 lpEnvironment: PVOID,
    lpCurrentDirectory: LPCSTR,
	 lpStartupInfo: LPSTARTUPINFOA,
  lpProcessInformation: LPPROCESS_INFORMATION
ifdef _UNICODE
CreateProcess equ <CreateProcessW>
else
CreateProcess equ <CreateProcessA>
endif

SetProcessShutdownParameters proto _CType \
	       dwLevel: DWORD,
	       dwFlags: DWORD

GetProcessShutdownParameters proto _CType \
	     lpdwLevel: LPDWORD,
	     lpdwFlags: LPDWORD
;DWORD
GetProcessVersion proto _CType \
	     ProcessId: DWORD
;VOID
FatalAppExitA proto _CType \
	       uAction: UINT,
	 lpMessageText: LPCSTR
FatalAppExitW proto _CType \
	       uAction: UINT,
	 lpMessageText: LPCWSTR
ifdef _UNICODE
FatalAppExit equ <FatalAppExitW>
else
FatalAppExit equ <FatalAppExitA>
endif

;VOID
GetStartupInfoA proto _CType \
	 lpStartupInfo: LPSTARTUPINFOA
GetStartupInfoW proto _CType \
	 lpStartupInfo: LPSTARTUPINFOW
ifdef _UNICODE
GetStartupInfo equ <GetStartupInfoW>
else
GetStartupInfo equ <GetStartupInfoA>
endif

;LPSTR
GetCommandLineA proto _CType
;LPWSTR
GetCommandLineW proto _CType
ifdef _UNICODE
GetCommandLine equ <GetCommandLineW>
else
GetCommandLine equ <GetCommandLineA>
endif

;DWORD
GetEnvironmentVariableA proto _CType \
		lpName: LPCSTR,
	      lpBuffer: LPSTR,
		 nSize: DWORD
GetEnvironmentVariableW proto _CType \
		lpName: LPCWSTR,
	      lpBuffer: LPWSTR,
		 nSize: DWORD
ifdef _UNICODE
GetEnvironmentVariable equ <GetEnvironmentVariableW>
else
GetEnvironmentVariable equ <GetEnvironmentVariableA>
endif

;BOOL
SetEnvironmentVariableA proto _CType \
		lpName: LPCSTR,
	       lpValue: LPCSTR
SetEnvironmentVariableW proto _CType \
		lpName: LPCWSTR,
	       lpValue: LPCWSTR
ifdef _UNICODE
SetEnvironmentVariable equ <SetEnvironmentVariableW>
else
SetEnvironmentVariable equ <SetEnvironmentVariableA>
endif

;DWORD
ExpandEnvironmentStringsA proto _CType \
		 lpSrc: LPCSTR,
		 lpDst: LPSTR,
		 nSize: DWORD
ExpandEnvironmentStringsW proto _CType \
		 lpSrc: LPCWSTR,
		 lpDst: LPWSTR,
		 nSize: DWORD
ifdef _UNICODE
ExpandEnvironmentStrings equ <ExpandEnvironmentStringsW>
else
ExpandEnvironmentStrings equ <ExpandEnvironmentStringsA>
endif

;VOID
OutputDebugStringA proto _CType \
	lpOutputString: LPCSTR
OutputDebugStringW proto _CType \
	lpOutputString: LPCWSTR
ifdef _UNICODE
OutputDebugString equ <OutputDebugStringW>
else
OutputDebugString equ <OutputDebugStringA>
endif

;HRSRC
FindResourceA proto _CType \
	       hModule: HMODULE,
		lpName: LPCSTR,
		lpType: LPCSTR
FindResourceW proto _CType \
	       hModule: HMODULE,
		lpName: LPCWSTR,
		lpType: LPCWSTR
ifdef _UNICODE
FindResource equ <FindResourceW>
else
FindResource equ <FindResourceA>
endif

FindResourceExA proto _CType \
	       hModule: HMODULE,
		lpType: LPCSTR,
		lpName: LPCSTR,
	     wLanguage: DWORD	;WORD
FindResourceExW proto _CType \
	       hModule: HMODULE,
		lpType: LPCWSTR,
		lpName: LPCWSTR,
	     wLanguage: DWORD	;WORD
ifdef _UNICODE
FindResourceEx equ <FindResourceExW>
else
FindResourceEx equ <FindResourceExA>
endif

ifdef STRICT
ENUMRESTYPEPROC_T TYPEDEF PROTO :HMODULE, :LPTSTR, :LONG
ENUMRESTYPEPROC TYPEDEF PTR ENUMRESTYPEPROC_T
ENUMRESNAMEPROC_T TYPEDEF PROTO :HMODULE, :LPTSTR, :LPTSTR, :LONG
ENUMRESNAMEPROC TYPEDEF PTR ENUMRESNAMEPROC_T
ENUMRESLANGPROC_T TYPEDEF PROTO :HMODULE, :LPTSTR, :LPTSTR, :DWORD, :LONG
ENUMRESLANGPROC TYPEDEF PTR ENUMRESTYPEPROC_T
else
ENUMRESTYPEPROC typedef FARPROC
ENUMRESNAMEPROC typedef FARPROC
ENUMRESLANGPROC typedef FARPROC
endif

;BOOL
EnumResourceTypesA proto _CType \
	       hModule: HMODULE,
	    lpEnumFunc: ENUMRESTYPEPROC,
		lParam: LONG
EnumResourceTypesW proto _CType \
	       hModule: HMODULE,
	    lpEnumFunc: ENUMRESTYPEPROC,
		lParam: LONG
ifdef _UNICODE
EnumResourceTypes equ <EnumResourceTypesW>
else
EnumResourceTypes equ <EnumResourceTypesA>
endif

EnumResourceNamesA proto _CType \
	       hModule: HMODULE,
		lpType: LPCSTR,
	    lpEnumFunc: ENUMRESNAMEPROC,
		lParam: LONG
EnumResourceNamesW proto _CType \
	       hModule: HMODULE,
		lpType: LPCWSTR,
	    lpEnumFunc: ENUMRESNAMEPROC,
		lParam: LONG
ifdef _UNICODE
EnumResourceNames equ <EnumResourceNamesW>
else
EnumResourceNames equ <EnumResourceNamesA>
endif

EnumResourceLanguagesA proto _CType \
	       hModule: HMODULE,
		lpType: LPCSTR,
		lpName: LPCSTR,
	    lpEnumFunc: ENUMRESLANGPROC,
		lParam: LONG
EnumResourceLanguagesW proto _CType \
	       hModule: HMODULE,
		lpType: LPCSTR,
		lpName: LPCSTR,
	    lpEnumFunc: ENUMRESLANGPROC,
		lParam: LONG
ifdef _UNICODE
EnumResourceLanguages equ <EnumResourceLanguagesW>
else
EnumResourceLanguages equ <EnumResourceLanguagesA>
endif

;HANDLE
BeginUpdateResourceA proto _CType \
	     pFileName: LPCSTR,
bDeleteExistingResources: BOOL
BeginUpdateResourceW proto _CType \
	     pFileName: LPCWSTR,
bDeleteExistingResources: BOOL
ifdef _UNICODE
BeginUpdateResource equ <BeginUpdateResourceW>
else
BeginUpdateResource equ <BeginUpdateResourceA>
endif

;BOOL
UpdateResourceA proto _CType \
	       hUpdate: HANDLE,
		lpType: LPCSTR,
		lpName: LPCSTR,
	     wLanguage: WORD,
		lpData: PVOID,
		cbData: DWORD
UpdateResourceW proto _CType \
	       hUpdate: HANDLE,
		lpType: LPCWSTR,
		lpName: LPCWSTR,
	     wLanguage: DWORD,
		lpData: PVOID,
		cbData: DWORD
ifdef _UNICODE
UpdateResource equ <UpdateResourceW>
else
UpdateResource equ <UpdateResourceA>
endif

;BOOL
EndUpdateResourceA proto _CType \
	       hUpdate: HANDLE,
	      fDiscard: BOOL
EndUpdateResourceW proto _CType \
	       hUpdate: HANDLE,
	      fDiscard: BOOL
ifdef _UNICODE
EndUpdateResource equ <EndUpdateResourceW>
else
EndUpdateResource equ <EndUpdateResourceA>
endif

;ATOM
GlobalAddAtomA proto _CType \
	      lpString: LPCSTR
GlobalAddAtomW proto _CType \
	      lpString: LPCWSTR
ifdef _UNICODE
GlobalAddAtom equ <GlobalAddAtomW>
else
GlobalAddAtom equ <GlobalAddAtomA>
endif

;ATOM
GlobalFindAtomA proto _CType \
	      lpString: LPCSTR
GlobalFindAtomW proto _CType \
	      lpString: LPCWSTR
ifdef _UNICODE
GlobalFindAtom equ <GlobalFindAtomW>
else
GlobalFindAtom equ <GlobalFindAtomA>
endif

;UINT
GlobalGetAtomNameA proto _CType \
		 nAtom: ATOM,
	      lpBuffer: LPSTR,
		 nSize: SINT
GlobalGetAtomNameW proto _CType \
		 nAtom: ATOM,
	      lpBuffer: LPWSTR,
		 nSize: SINT
ifdef _UNICODE
GlobalGetAtomName equ <GlobalGetAtomNameW>
else
GlobalGetAtomName equ <GlobalGetAtomNameA>
endif

;ATOM
AddAtomA proto _CType lpString:LPCSTR
AddAtomW proto _CType lpString:LPCWSTR
ifdef _UNICODE
AddAtom equ <AddAtomW>
else
AddAtom equ <AddAtomA>
endif

FindAtomA proto _CType lpString:LPCSTR
FindAtomW proto _CType lpString:LPCWSTR
ifdef _UNICODE
FindAtom equ <FindAtomW>
else
FindAtom equ <FindAtomA>
endif

;UINT
GetAtomNameA proto _CType \
		 nAtom: ATOM,
	      lpBuffer: LPSTR,
		 nSize: SINT
GetAtomNameW proto _CType \
		 nAtom: ATOM,
	      lpBuffer: LPWSTR,
		 nSize: SINT
ifdef _UNICODE
GetAtomName equ <GetAtomNameW>
else
GetAtomName equ <GetAtomNameA>
endif

GetProfileIntA proto _CType \
	     lpAppName: LPCSTR,
	     lpKeyName: LPCSTR,
	      nDefault: SINT
GetProfileIntW proto _CType \
	     lpAppName: LPCWSTR,
	     lpKeyName: LPCWSTR,
	      nDefault: SINT
ifdef _UNICODE
GetProfileInt equ <GetProfileIntW>
else
GetProfileInt equ <GetProfileIntA>
endif

;DWORD
GetProfileStringA proto _CType \
	     lpAppName: LPCSTR,
	     lpKeyName: LPCSTR,
	     lpDefault: LPCSTR,
      lpReturnedString: LPSTR,
		 nSize: DWORD
GetProfileStringW proto _CType \
	     lpAppName: LPCWSTR,
	     lpKeyName: LPCWSTR,
	     lpDefault: LPCWSTR,
      lpReturnedString: LPWSTR,
		 nSize: DWORD
ifdef _UNICODE
GetProfileString equ <GetProfileStringW>
else
GetProfileString equ <GetProfileStringA>
endif

;BOOL
WriteProfileStringA proto _CType \
	     lpAppName: LPCSTR,
	     lpKeyName: LPCSTR,
	      lpString: LPCSTR
WriteProfileStringW proto _CType \
	     lpAppName: LPCWSTR,
	     lpKeyName: LPCWSTR,
	      lpString: LPCWSTR
ifdef _UNICODE
WriteProfileString equ <WriteProfileStringW>
else
WriteProfileString equ <WriteProfileStringA>
endif

;DWORD
GetProfileSectionA proto _CType \
	     lpAppName: LPCSTR,
      lpReturnedString: LPSTR,
		 nSize: DWORD
GetProfileSectionW proto _CType \
	     lpAppName: LPCWSTR,
      lpReturnedString: LPSTR,
		 nSize: DWORD
ifdef _UNICODE
GetProfileSection equ <GetProfileSectionW>
else
GetProfileSection equ <GetProfileSectionA>
endif

;BOOL
WriteProfileSectionA proto _CType \
	     lpAppName: LPCSTR,
	      lpString: LPCSTR
WriteProfileSectionW proto _CType \
	     lpAppName: LPCWSTR,
	      lpString: LPCWSTR
ifdef _UNICODE
WriteProfileSection equ <WriteProfileSectionW>
else
WriteProfileSection equ <WriteProfileSectionA>
endif

;UINT
GetPrivateProfileIntA proto _CType \
	     lpAppName: LPCSTR,
	     lpKeyName: LPCSTR,
	      nDefault: SINT,
	    lpFileName: LPCSTR
GetPrivateProfileIntW proto _CType \
	     lpAppName: LPCWSTR,
	     lpKeyName: LPCWSTR,
	      nDefault: SINT,
	    lpFileName: LPCWSTR
ifdef _UNICODE
GetPrivateProfileInt equ <GetPrivateProfileIntW>
else
GetPrivateProfileInt equ <GetPrivateProfileIntA>
endif

;DWORD
GetPrivateProfileStringA proto _CType \
	     lpAppName: LPCSTR,
	     lpKeyName: LPCSTR,
	     lpDefault: LPCSTR,
      lpReturnedString: LPSTR,
		 nSize: DWORD,
	    lpFileName: LPCSTR
GetPrivateProfileStringW proto _CType \
	     lpAppName: LPCWSTR,
	     lpKeyName: LPCWSTR,
	     lpDefault: LPCWSTR,
      lpReturnedString: LPWSTR,
		 nSize: DWORD,
	    lpFileName: LPCWSTR
ifdef _UNICODE
GetPrivateProfileString equ <GetPrivateProfileStringW>
else
GetPrivateProfileString equ <GetPrivateProfileStringA>
endif

;BOOL
WritePrivateProfileStringA proto _CType \
	     lpAppName: LPCSTR,
	     lpKeyName: LPCSTR,
	      lpString: LPCSTR,
	    lpFileName: LPCSTR
WritePrivateProfileStringW proto _CType \
	     lpAppName: LPCWSTR,
	     lpKeyName: LPCWSTR,
	      lpString: LPCWSTR,
	    lpFileName: LPCWSTR
ifdef _UNICODE
WritePrivateProfileString equ <WritePrivateProfileStringW>
else
WritePrivateProfileString equ <WritePrivateProfileStringA>
endif

GetPrivateProfileSectionA proto _CType \
	     lpAppName: LPCSTR,
      lpReturnedString: LPSTR,
		 nSize: DWORD,
	    lpFileName: LPCSTR
GetPrivateProfileSectionW proto _CType \
	     lpAppName: LPCWSTR,
      lpReturnedString: LPWSTR,
		 nSize: DWORD,
	    lpFileName: LPCWSTR
ifdef _UNICODE
GetPrivateProfileSection equ <GetPrivateProfileSectionW>
else
GetPrivateProfileSection equ <GetPrivateProfileSectionA>
endif

WritePrivateProfileSectionA proto _CType \
	     lpAppName: LPCSTR,
	      lpString: LPCSTR,
	    lpFileName: LPCSTR
WritePrivateProfileSectionW proto _CType \
	     lpAppName: LPCWSTR,
	      lpString: LPCWSTR,
	    lpFileName: LPCWSTR
ifdef _UNICODE
WritePrivateProfileSection equ <WritePrivateProfileSectionW>
else
WritePrivateProfileSection equ <WritePrivateProfileSectionA>
endif

;DWORD
GetPrivateProfileSectionNamesA proto _CType \
      lpszReturnBuffer: LPSTR,
		 nSize: DWORD,
	    lpFileName: LPCSTR
GetPrivateProfileSectionNamesW proto _CType \
      lpszReturnBuffer: LPWSTR,
		 nSize: DWORD,
	    lpFileName: LPCWSTR
ifdef _UNICODE
GetPrivateProfileSectionNames equ <GetPrivateProfileSectionNamesW>
else
GetPrivateProfileSectionNames equ <GetPrivateProfileSectionNamesA>
endif

;BOOL
GetPrivateProfileStructA proto _CType \
	   lpszSection: LPCSTR,
	       lpszKey: LPCSTR,
	      lpStruct: LPVOID,
	   uSizeStruct: UINT,
		szFile: LPCSTR
GetPrivateProfileStructW proto _CType \
	   lpszSection: LPCWSTR,
	       lpszKey: LPCWSTR,
	      lpStruct: LPVOID,
	   uSizeStruct: UINT,
		szFile: LPCWSTR
ifdef _UNICODE
GetPrivateProfileStruct equ <GetPrivateProfileStructW>
else
GetPrivateProfileStruct equ <GetPrivateProfileStructA>
endif

WritePrivateProfileStructA proto _CType \
	   lpszSection: LPCSTR,
	       lpszKey: LPCSTR,
	      lpStruct: LPVOID,
	   uSizeStruct: UINT,
		szFile: LPCSTR
WritePrivateProfileStructW proto _CType \
	   lpszSection: LPCWSTR,
	       lpszKey: LPCWSTR,
	      lpStruct: LPVOID,
	   uSizeStruct: UINT,
		szFile: LPCWSTR
ifdef _UNICODE
WritePrivateProfileStruct equ <WritePrivateProfileStructW>
else
WritePrivateProfileStruct equ <WritePrivateProfileStructA>
endif


;UINT
GetDriveTypeA proto _CType \
	lpRootPathName: LPCSTR
GetDriveTypeW proto _CType \
	lpRootPathName: LPCWSTR
ifdef _UNICODE
GetDriveType equ <GetDriveTypeW>
else
GetDriveType equ <GetDriveTypeA>
endif

GetSystemDirectoryA proto _CType \
	      lpBuffer: LPSTR,
		 uSize: UINT
GetSystemDirectoryW proto _CType \
	      lpBuffer: LPWSTR,
		 uSize: UINT
ifdef _UNICODE
GetSystemDirectory equ <GetSystemDirectoryW>
else
GetSystemDirectory equ <GetSystemDirectoryA>
endif

;DWORD
GetTempPathA proto _CType \
	 nBufferLength: DWORD,
	      lpBuffer: LPSTR
GetTempPathW proto _CType \
	 nBufferLength: DWORD,
	      lpBuffer: LPWSTR
ifdef _UNICODE
GetTempPath equ <GetTempPathW>
else
GetTempPath equ <GetTempPathA>
endif

;UINT
GetTempFileNameA proto _CType \
	    lpPathName: LPCSTR,
	lpPrefixString: LPCSTR,
	       uUnique: UINT,
	lpTempFileName: LPSTR
GetTempFileNameW proto _CType \
	    lpPathName: LPCWSTR,
	lpPrefixString: LPCWSTR,
	       uUnique: UINT,
	lpTempFileName: LPWSTR
ifdef _UNICODE
GetTempFileName equ <GetTempFileNameW>
else
GetTempFileName equ <GetTempFileNameA>
endif

GetWindowsDirectoryA proto _CType \
	      lpBuffer: LPSTR,
		 uSize: UINT
GetWindowsDirectoryW proto _CType \
	      lpBuffer: LPWSTR,
		 uSize: UINT
ifdef _UNICODE
GetWindowsDirectory equ <GetWindowsDirectoryW>
else
GetWindowsDirectory equ <GetWindowsDirectoryA>
endif

;BOOL
SetCurrentDirectoryA proto _CType \
	    lpPathName: LPCSTR
SetCurrentDirectoryW proto _CType \
	    lpPathName: LPCWSTR
ifdef _UNICODE
SetCurrentDirectory equ <SetCurrentDirectoryW>
else
SetCurrentDirectory equ <SetCurrentDirectoryA>
endif

;DWORD
GetCurrentDirectoryA proto _CType \
	 nBufferLength: DWORD,
	      lpBuffer: LPSTR
GetCurrentDirectoryW proto _CType \
	 nBufferLength: DWORD,
	      lpBuffer: LPWSTR
ifdef _UNICODE
GetCurrentDirectory equ <GetCurrentDirectoryW>
else
GetCurrentDirectory equ <GetCurrentDirectoryA>
endif

;BOOL
GetDiskFreeSpaceA proto _CType \
	lpRootPathName: LPCSTR,
   lpSectorsPerCluster: LPDWORD,
      lpBytesPerSector: LPDWORD,
lpNumberOfFreeClusters: LPDWORD,
lpTotalNumberOfClusters: LPDWORD
GetDiskFreeSpaceW proto _CType \
	lpRootPathName: LPCWSTR,
   lpSectorsPerCluster: LPDWORD,
      lpBytesPerSector: LPDWORD,
lpNumberOfFreeClusters: LPDWORD,
lpTotalNumberOfClusters: LPDWORD
ifdef _UNICODE
GetDiskFreeSpace equ <GetDiskFreeSpaceW>
else
GetDiskFreeSpace equ <GetDiskFreeSpaceA>
endif

GetDiskFreeSpaceExA proto _CType \
       lpDirectoryName: LPCSTR,
lpFreeBytesAvailableToCaller: PULARGE_INTEGER,
  lpTotalNumberOfBytes: PULARGE_INTEGER,
lpTotalNumberOfFreeBytes: PULARGE_INTEGER
GetDiskFreeSpaceExW proto _CType \
       lpDirectoryName: LPCWSTR,
lpFreeBytesAvailableToCaller: PULARGE_INTEGER,
  lpTotalNumberOfBytes: PULARGE_INTEGER,
lpTotalNumberOfFreeBytes: PULARGE_INTEGER
ifdef _UNICODE
GetDiskFreeSpaceEx equ <GetDiskFreeSpaceExW>
else
GetDiskFreeSpaceEx equ <GetDiskFreeSpaceExA>
endif

CreateDirectoryA proto _CType \
	    lpPathName: LPCSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
CreateDirectoryW proto _CType \
	    lpPathName: LPCWSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
ifdef _UNICODE
CreateDirectory equ <CreateDirectoryW>
else
CreateDirectory equ <CreateDirectoryA>
endif

CreateDirectoryExA proto _CType \
   lpTemplateDirectory: LPCSTR,
	lpNewDirectory: LPCSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
CreateDirectoryExW proto _CType \
   lpTemplateDirectory: LPCWSTR,
	lpNewDirectory: LPCWSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
ifdef _UNICODE
CreateDirectoryEx equ <CreateDirectoryExW>
else
CreateDirectoryEx equ <CreateDirectoryExA>
endif

;BOOL
RemoveDirectoryA proto _CType \
	    lpPathName: LPCSTR
RemoveDirectoryW proto _CType \
	    lpPathName: LPCWSTR
ifdef _UNICODE
RemoveDirectory equ <RemoveDirectoryW>
else
RemoveDirectory equ <RemoveDirectoryA>
endif

;DWORD
GetFullPathNameA proto _CType \
	    lpFileName: LPCSTR,
	 nBufferLength: DWORD,
	      lpBuffer: LPSTR,
	    lpFilePart: PTR LPSTR
GetFullPathNameW proto _CType \
	    lpFileName: LPCWSTR,
	 nBufferLength: DWORD,
	      lpBuffer: LPWSTR,
	    lpFilePart: PTR LPWSTR
ifdef _UNICODE
GetFullPathName equ <GetFullPathNameW>
else
GetFullPathName equ <GetFullPathNameA>
endif

DDD_RAW_TARGET_PATH	    equ 0x00000001
DDD_REMOVE_DEFINITION	    equ 0x00000002
DDD_EXACT_MATCH_ON_REMOVE   equ 0x00000004
DDD_NO_BROADCAST_SYSTEM	    equ 0x00000008

;BOOL
DefineDosDeviceA proto _CType \
	       dwFlags: DWORD,
	  lpDeviceName: LPCSTR,
	  lpTargetPath: LPCSTR
DefineDosDeviceW proto _CType \
	       dwFlags: DWORD,
	  lpDeviceName: LPCWSTR,
	  lpTargetPath: LPCWSTR
ifdef _UNICODE
DefineDosDevice equ <DefineDosDeviceW>
else
DefineDosDevice equ <DefineDosDeviceA>
endif

;DWORD
QueryDosDeviceA proto _CType \
	  lpDeviceName: LPCSTR,
	  lpTargetPath: LPSTR,
	       ucchMax: DWORD
QueryDosDeviceW proto _CType \
	  lpDeviceName: LPCWSTR,
	  lpTargetPath: LPWSTR,
	       ucchMax: DWORD
ifdef _UNICODE
QueryDosDevice equ <QueryDosDeviceW>
else
QueryDosDevice equ <QueryDosDeviceA>
endif

EXPAND_LOCAL_DRIVES equ 1

;HANDLE
CreateFileA proto _CType \
	    lpFileName: LPSTR,
       dwDesiredAccess: DWORD,
	   dwShareMode: DWORD,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES,
 dwCreationDisposition: DWORD,
  dwFlagsAndAttributes: DWORD,
	 hTemplateFile: HANDLE
CreateFileW proto _CType \
	    lpFileName: LPWSTR,
       dwDesiredAccess: DWORD,
	   dwShareMode: DWORD,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES,
 dwCreationDisposition: DWORD,
  dwFlagsAndAttributes: DWORD,
	 hTemplateFile: HANDLE
ifdef _UNICODE
CreateFile equ <CreateFileW>
else
CreateFile equ <CreateFileA>
endif

;BOOL
SetFileAttributesA proto _CType \
	    lpFileName: LPSTR,	; pointer to filename
      dwFileAttributes: DWORD	; attributes to set
SetFileAttributesW proto _CType \
	    lpFileName: LPWSTR,
      dwFileAttributes: DWORD
ifdef _UNICODE
SetFileAttributes equ <SetFileAttributesW>
else
SetFileAttributes equ <SetFileAttributesA>
endif

;DWORD
GetFileAttributesA proto _CType \
	    lpFileName: LPSTR	; pointer to the name of a file or directory
GetFileAttributesW proto _CType \
	    lpFileName: LPWSTR
ifdef _UNICODE
GetFileAttributes equ <GetFileAttributesW>
else
GetFileAttributes equ <GetFileAttributesA>
endif

GetFileExInfoStandard	equ 0
GetFileExMaxInfoLevel	equ 1
GET_FILEEX_INFO_LEVELS	typedef dword

;BOOL
GetFileAttributesExA proto _CType \
	    lpFileName: LPCSTR,
	  fInfoLevelId: GET_FILEEX_INFO_LEVELS,
     lpFileInformation: LPVOID
GetFileAttributesExW proto _CType \
	    lpFileName: LPCWSTR,
	  fInfoLevelId: GET_FILEEX_INFO_LEVELS,
     lpFileInformation: LPVOID
ifdef _UNICODE
GetFileAttributesEx equ <GetFileAttributesExW>
else
GetFileAttributesEx equ <GetFileAttributesExA>
endif

;DWORD
GetCompressedFileSizeA proto _CType \
	    lpFileName: LPCSTR,
	lpFileSizeHigh: LPDWORD
GetCompressedFileSizeW proto _CType \
	    lpFileName: LPCWSTR,
	lpFileSizeHigh: LPDWORD
ifdef _UNICODE
GetCompressedFileSize equ <GetCompressedFileSizeW>
else
GetCompressedFileSize equ <GetCompressedFileSizeA>
endif

;BOOL
DeleteFileA proto _CType \
	    lpFileName: LPCSTR
DeleteFileW proto _CType \
	    lpFileName: LPCWSTR
ifdef _UNICODE
DeleteFile equ <DeleteFileW>
else
DeleteFile equ <DeleteFileA>
endif

if(_WIN32_WINNT GE 0x0400)

FindExInfoStandard		equ 0
FindExInfoMaxInfoLevel		equ 1
FINDEX_INFO_LEVELS		typedef dword

FindExSearchNameMatch		equ 0
FindExSearchLimitToDirectories	equ 1
FindExSearchLimitToDevices	equ 2
FindExSearchMaxSearchOp		equ 3
FINDEX_SEARCH_OPS		typedef dword

FIND_FIRST_EX_CASE_SENSITIVE   equ 0x00000001

;HANDLE
FindFirstFileExA proto _CType \
	    lpFileName: LPCSTR,
	  fInfoLevelId: FINDEX_INFO_LEVELS,
	lpFindFileData: LPVOID,
	     fSearchOp: FINDEX_SEARCH_OPS,
	lpSearchFilter: LPVOID,
     dwAdditionalFlags: DWORD
FindFirstFileExW proto _CType \
	    lpFileName: LPCWSTR,
	  fInfoLevelId: FINDEX_INFO_LEVELS,
	lpFindFileData: LPVOID,
	     fSearchOp: FINDEX_SEARCH_OPS,
	lpSearchFilter: LPVOID,
     dwAdditionalFlags: DWORD
ifdef _UNICODE
FindFirstFileEx equ <FindFirstFileExW>
else
FindFirstFileEx equ <FindFirstFileExA>
endif
endif

FindFirstFileA proto _CType \
	    lpFileName: LPCSTR,
	lpFindFileData: LPWIN32_FIND_DATAA
FindFirstFileW proto _CType \
	    lpFileName: LPCWSTR,
	lpFindFileData: LPWIN32_FIND_DATAW
ifdef _UNICODE
FindFirstFile equ <FindFirstFileW>
else
FindFirstFile equ <FindFirstFileA>
endif

;BOOL
FindNextFileA proto _CType \
	     hFindFile: HANDLE,
	lpFindFileData: LPWIN32_FIND_DATAA
FindNextFileW proto _CType \
	     hFindFile: HANDLE,
	lpFindFileData: LPWIN32_FIND_DATAW
ifdef _UNICODE
FindNextFile equ <FindNextFileW>
else
FindNextFile equ <FindNextFileA>
endif

;DWORD
SearchPathA proto \
	lpPath:		LPSTR,	; pointer to search path
	lpFileName:	LPSTR,	; pointer to filename
	lpExtension:	LPSTR,	; pointer to extension
	nBufferLength:	DWORD,	; size, in characters, of buffer
	lpBuffer:	LPSTR,	; pointer to buffer for found filename
	lpFilePart:	LPSTR	; pointer to pointer to file component
SearchPathW proto	:LPWSTR, :LPWSTR, :LPWSTR, :DWORD, :LPWSTR, :LPWSTR
ifdef _UNICODE
SearchPath equ <SearchPathW>
else
SearchPath equ <SearchPathA>
endif

;BOOL
CopyFileA proto _CType \
    lpExistingFileName: LPCSTR,
	 lpNewFileName: LPCSTR,
	 bFailIfExists: BOOL
CopyFileW proto _CType \
    lpExistingFileName: LPCWSTR,
	 lpNewFileName: LPCWSTR,
	 bFailIfExists: BOOL
ifdef _UNICODE
CopyFile equ <CopyFileW>
else
CopyFile equ <CopyFileA>
endif

if(_WIN32_WINNT GE 0x0400)

PROGRESS_ROUTINE_T TYPEDEF PROTO :LARGE_INTEGER,
	:LARGE_INTEGER, :LARGE_INTEGER, :LARGE_INTEGER,
	:DWORD, :DWORD, :HANDLE, :HANDLE, :LPVOID
LPPROGRESS_ROUTINE TYPEDEF PTR PROGRESS_ROUTINE_T
;BOOL
CopyFileExA proto _CType \
    lpExistingFileName: LPCSTR,
	 lpNewFileName: LPCSTR,
     lpProgressRoutine: LPPROGRESS_ROUTINE,; OPTIONAL,
		lpData: LPVOID,; OPTIONAL,
	      pbCancel: LPBOOL,; OPTIONAL,
	   dwCopyFlags: DWORD
CopyFileExW proto _CType \
    lpExistingFileName: LPCWSTR,
	 lpNewFileName: LPCWSTR,
     lpProgressRoutine: LPPROGRESS_ROUTINE,
		lpData: LPVOID,
	      pbCancel: LPBOOL,
	   dwCopyFlags: DWORD
ifdef _UNICODE
CopyFileEx equ <CopyFileExW>
else
CopyFileEx equ <CopyFileExA>
endif
endif

MoveFileA proto _CType \
    lpExistingFileName: LPCSTR,
	 lpNewFileName: LPCSTR
MoveFileW proto _CType \
    lpExistingFileName: LPCWSTR,
	 lpNewFileName: LPCWSTR
ifdef _UNICODE
MoveFile equ <MoveFileW>
else
MoveFile equ <MoveFileA>
endif

MoveFileExA proto _CType \
    lpExistingFileName: LPCSTR,
	 lpNewFileName: LPCSTR,
	       dwFlags: DWORD
MoveFileExW proto _CType \
    lpExistingFileName: LPCWSTR,
	 lpNewFileName: LPCWSTR,
	       dwFlags: DWORD
ifdef _UNICODE
MoveFileEx equ <MoveFileExW>
else
MoveFileEx equ <MoveFileExA>
endif

if (_WIN32_WINNT GE 0x0500)

MoveFileWithProgressA proto _CType \
    lpExistingFileName: LPCSTR,
	 lpNewFileName: LPCSTR,
     lpProgressRoutine: LPPROGRESS_ROUTINE,
		lpData: LPVOID,
	       dwFlags: DWORD
MoveFileWithProgressW proto _CType \
    lpExistingFileName: LPCWSTR,
	 lpNewFileName: LPCWSTR,
     lpProgressRoutine: LPPROGRESS_ROUTINE,
		lpData: LPVOID,
	       dwFlags: DWORD
ifdef _UNICODE
MoveFileWithProgress equ <MoveFileWithProgressW>
else
MoveFileWithProgress equ <MoveFileWithProgressA>
endif ; !UNICODE
endif ; (_WIN32_WINNT >= equ 0x0500)

MOVEFILE_REPLACE_EXISTING	equ 0x00000001
MOVEFILE_COPY_ALLOWED		equ 0x00000002
MOVEFILE_DELAY_UNTIL_REBOOT	equ 0x00000004
MOVEFILE_WRITE_THROUGH		equ 0x00000008
if (_WIN32_WINNT GE 0x0500)
MOVEFILE_CREATE_HARDLINK	equ 0x00000010
MOVEFILE_FAIL_IF_NOT_TRACKABLE	equ 0x00000020
endif


if (_WIN32_WINNT GE 0x0500)
;
; API call to create hard links.
;

;BOOL
CreateHardLinkA proto _CType \
	    lpFileName: LPCSTR,
    lpExistingFileName: LPCSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
CreateHardLinkW proto _CType \
	    lpFileName: LPCWSTR,
    lpExistingFileName: LPCWSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
ifdef _UNICODE
CreateHardLink equ <CreateHardLinkW>
else
CreateHardLink equ <CreateHardLinkA>
endif

endif ; (_WIN32_WINNT >= equ 0x0500)

;HANDLE
CreateNamedPipeA proto _CType \
		lpName: LPCSTR,
	    dwOpenMode: DWORD,
	    dwPipeMode: DWORD,
	 nMaxInstances: DWORD,
	nOutBufferSize: DWORD,
	 nInBufferSize: DWORD,
       nDefaultTimeOut: DWORD,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
CreateNamedPipeW proto _CType \
		lpName: LPCWSTR,
	    dwOpenMode: DWORD,
	    dwPipeMode: DWORD,
	 nMaxInstances: DWORD,
	nOutBufferSize: DWORD,
	 nInBufferSize: DWORD,
       nDefaultTimeOut: DWORD,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
ifdef _UNICODE
CreateNamedPipe equ <CreateNamedPipeW>
else
CreateNamedPipe equ <CreateNamedPipeA>
endif

;BOOL
GetNamedPipeHandleStateA proto _CType \
	    hNamedPipe: HANDLE,
	       lpState: LPDWORD,
	lpCurInstances: LPDWORD,
  lpMaxCollectionCount: LPDWORD,
  lpCollectDataTimeout: LPDWORD,
	    lpUserName: LPSTR,
      nMaxUserNameSize: DWORD
GetNamedPipeHandleStateW proto _CType \
	    hNamedPipe: HANDLE,
	       lpState: LPDWORD,
	lpCurInstances: LPDWORD,
  lpMaxCollectionCount: LPDWORD,
  lpCollectDataTimeout: LPDWORD,
	    lpUserName: LPWSTR,
      nMaxUserNameSize: DWORD
ifdef _UNICODE
GetNamedPipeHandleState equ <GetNamedPipeHandleStateW>
else
GetNamedPipeHandleState equ <GetNamedPipeHandleStateA>
endif

CallNamedPipeA proto _CType \
       lpNamedPipeName: LPCSTR,
	    lpInBuffer: LPVOID,
	 nInBufferSize: DWORD,
	   lpOutBuffer: LPVOID,
	nOutBufferSize: DWORD,
	   lpBytesRead: LPDWORD,
	      nTimeOut: DWORD
CallNamedPipeW proto _CType \
       lpNamedPipeName: LPCWSTR,
	    lpInBuffer: LPVOID,
	 nInBufferSize: DWORD,
	   lpOutBuffer: LPVOID,
	nOutBufferSize: DWORD,
	   lpBytesRead: LPDWORD,
	      nTimeOut: DWORD
ifdef _UNICODE
CallNamedPipe equ <CallNamedPipeW>
else
CallNamedPipe equ <CallNamedPipeA>
endif

WaitNamedPipeA proto _CType \
       lpNamedPipeName: LPCSTR,
	      nTimeOut: DWORD
WaitNamedPipeW proto _CType \
       lpNamedPipeName: LPCWSTR,
	      nTimeOut: DWORD
ifdef _UNICODE
WaitNamedPipe equ <WaitNamedPipeW>
else
WaitNamedPipe equ <WaitNamedPipeA>
endif

SetVolumeLabelA proto _CType \
	lpRootPathName: LPCSTR,
	  lpVolumeName: LPCSTR
SetVolumeLabelW proto _CType \
	lpRootPathName: LPCWSTR,
	  lpVolumeName: LPCWSTR
ifdef _UNICODE
SetVolumeLabel equ <SetVolumeLabelW>
else
SetVolumeLabel equ <SetVolumeLabelA>
endif

SetFileApisToOEM  proto _CType
SetFileApisToANSI proto _CType
AreFileApisANSI	  proto _CType

GetVolumeInformationA proto _CType \
	lpRootPathName: LPSTR,	; address of root directory of the file system
    lpVolumeNameBuffer: LPSTR,	; address of name of the volume
       nVolumeNameSize: DWORD,	; length of lpVolumeNameBuffer
  lpVolumeSerialNumber: LPDWORD,; address of volume serial number,
lpMaximumComponentLength: LPDWORD,; address of system's maximum filename length
     lpFileSystemFlags: LPDWORD,; address of file system flags
lpFileSystemNameBuffer: LPSTR,	; address of name of file system
   nFileSystemNameSize: DWORD	; length of lpFileSystemNameBuffer
GetVolumeInformationW proto _CType \
	lpRootPathName: LPWSTR,
    lpVolumeNameBuffer: LPWSTR,
       nVolumeNameSize: DWORD,
  lpVolumeSerialNumber: LPDWORD,
lpMaximumComponentLength: LPDWORD,
     lpFileSystemFlags: LPDWORD,
lpFileSystemNameBuffer: LPWSTR,
   nFileSystemNameSize: DWORD
ifdef _UNICODE
GetVolumeInformation equ <GetVolumeInformationW>
else
GetVolumeInformation equ <GetVolumeInformationA>
endif

;BOOL
CancelIo proto _CType \
		 hFile: HANDLE

;
; Event logging APIs
;

ClearEventLogA proto _CType \
	     hEventLog: HANDLE,
      lpBackupFileName: LPCSTR

ClearEventLogW proto _CType \
	     hEventLog: HANDLE,
      lpBackupFileName: LPCWSTR
ifdef _UNICODE
ClearEventLog equ <ClearEventLogW>
else
ClearEventLog equ <ClearEventLogA>
endif

BackupEventLogA proto _CType \
	     hEventLog: HANDLE,
      lpBackupFileName: LPCSTR
BackupEventLogW proto _CType \
	     hEventLog: HANDLE,
      lpBackupFileName: LPCWSTR
ifdef _UNICODE
BackupEventLog equ <BackupEventLogW>
else
BackupEventLog equ <BackupEventLogA>
endif

CloseEventLog proto _CType \
	     hEventLog: HANDLE

DeregisterEventSource proto _CType \
	     hEventLog: HANDLE

NotifyChangeEventLog proto _CType \
	     hEventLog: HANDLE,
		hEvent: HANDLE

GetNumberOfEventLogRecords proto _CType \
	     hEventLog: HANDLE,
       NumberOfRecords: PDWORD

GetOldestEventLogRecord proto _CType \
	     hEventLog: HANDLE,
	  OldestRecord: PDWORD
;HANDLE
OpenEventLogA proto _CType \
       lpUNCServerName: LPCSTR,
	  lpSourceName: LPCSTR
OpenEventLogW proto _CType \
       lpUNCServerName: LPCWSTR,
	  lpSourceName: LPCWSTR
ifdef _UNICODE
OpenEventLog equ <OpenEventLogW>
else
OpenEventLog equ <OpenEventLogA>
endif

RegisterEventSourceA proto _CType \
       lpUNCServerName: LPCSTR,
	  lpSourceName: LPCSTR
RegisterEventSourceW proto _CType \
       lpUNCServerName: LPCWSTR,
	  lpSourceName: LPCWSTR
ifdef _UNICODE
RegisterEventSource equ <RegisterEventSourceW>
else
RegisterEventSource equ <RegisterEventSourceA>
endif

OpenBackupEventLogA proto _CType \
       lpUNCServerName: LPCSTR,
	    lpFileName: LPCSTR
OpenBackupEventLogW proto _CType \
       lpUNCServerName: LPCWSTR,
	    lpFileName: LPCWSTR
ifdef _UNICODE
OpenBackupEventLog equ <OpenBackupEventLogW>
else
OpenBackupEventLog equ <OpenBackupEventLogA>
endif

;BOOL
ReadEventLogA proto _CType \
	     hEventLog: HANDLE,
	   dwReadFlags: DWORD,
	dwRecordOffset: DWORD,
	      lpBuffer: PVOID,
  nNumberOfBytesToRead: DWORD,
	   pnBytesRead: PTR DWORD,
pnMinNumberOfBytesNeeded: PTR DWORD
ReadEventLogW proto _CType \
	     hEventLog: HANDLE,
	   dwReadFlags: DWORD,
	dwRecordOffset: DWORD,
	      lpBuffer: PVOID,
  nNumberOfBytesToRead: DWORD,
	   pnBytesRead: PTR DWORD,
pnMinNumberOfBytesNeeded: PTR DWORD
ifdef _UNICODE
ReadEventLog equ <ReadEventLogW>
else
ReadEventLog equ <ReadEventLogA>
endif

ReportEventA proto _CType \
	     hEventLog: HANDLE,
		 wType: WORD,
	     wCategory: WORD,
	     dwEventID: DWORD,
	     lpUserSid: PSID,
	   wNumStrings: WORD,
	    dwDataSize: DWORD,
	     lpStrings: PTR LPCSTR,
	     lpRawData: LPVOID
ReportEventW proto _CType \
	     hEventLog: HANDLE,
		 wType: WORD,
	     wCategory: WORD,
	     dwEventID: DWORD,
	     lpUserSid: PSID,
	   wNumStrings: WORD,
	    dwDataSize: DWORD,
	     lpStrings: PTR LPCWSTR,
	     lpRawData: LPVOID
ifdef _UNICODE
ReportEvent equ <ReportEventW>
else
ReportEvent equ <ReportEventA>
endif

;
;
; Security APIs
;

;BOOL
DuplicateToken proto _CType \
   ExistingTokenHandle: HANDLE,
    ImpersonationLevel: SECURITY_IMPERSONATION_LEVEL,
  DuplicateTokenHandle: PHANDLE

GetKernelObjectSecurity proto _CType \
		Handle: HANDLE,
  RequestedInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	       nLength: DWORD,
       lpnLengthNeeded: LPDWORD

ImpersonateNamedPipeClient proto _CType \
	    hNamedPipe: HANDLE

ImpersonateSelf proto _CType \
    ImpersonationLevel: SECURITY_IMPERSONATION_LEVEL

RevertToSelf proto _CType

SetThreadToken proto _CType \
		Thread: PHANDLE,
		 Token: HANDLE

AccessCheck proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	   ClientToken: HANDLE,
	 DesiredAccess: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	  PrivilegeSet: PPRIVILEGE_SET,
    PrivilegeSetLength: LPDWORD,
	 GrantedAccess: LPDWORD,
	  AccessStatus: LPBOOL
if(_WIN32_WINNT GE 0x0500)

AccessCheckByType proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
      PrincipalSelfSid: PSID,
	   ClientToken: HANDLE,
	 DesiredAccess: DWORD,
	ObjectTypeList: POBJECT_TYPE_LIST,
  ObjectTypeListLength: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	  PrivilegeSet: PPRIVILEGE_SET,
    PrivilegeSetLength: LPDWORD,
	 GrantedAccess: LPDWORD,
	  AccessStatus: LPBOOL

AccessCheckByTypeResultList proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
      PrincipalSelfSid: PSID,
	   ClientToken: HANDLE,
	 DesiredAccess: DWORD,
	ObjectTypeList: POBJECT_TYPE_LIST,
  ObjectTypeListLength: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	  PrivilegeSet: PPRIVILEGE_SET,
    PrivilegeSetLength: LPDWORD,
     GrantedAccessList: LPDWORD,
      AccessStatusList: LPDWORD
endif


OpenProcessToken proto _CType \
	 ProcessHandle: HANDLE,
	 DesiredAccess: DWORD,
	   TokenHandle: PHANDLE

OpenThreadToken proto _CType \
	  ThreadHandle: HANDLE,
	 DesiredAccess: DWORD,
	    OpenAsSelf: BOOL,
	   TokenHandle: PHANDLE

GetTokenInformation proto _CType \
	   TokenHandle: HANDLE,
 TokenInformationClass: TOKEN_INFORMATION_CLASS,
      TokenInformation: LPVOID,
TokenInformationLength: DWORD,
	  ReturnLength: PDWORD

SetTokenInformation proto _CType \
	   TokenHandle: HANDLE,
 TokenInformationClass: TOKEN_INFORMATION_CLASS,
      TokenInformation: LPVOID,
TokenInformationLength: DWORD

AdjustTokenPrivileges proto _CType \
	   TokenHandle: HANDLE,
  DisableAllPrivileges: BOOL,
	      NewState: PTOKEN_PRIVILEGES,
	  BufferLength: DWORD,
	 PreviousState: PTOKEN_PRIVILEGES,
	  ReturnLength: PDWORD

AdjustTokenGroups proto _CType \
	   TokenHandle: HANDLE,
	ResetToDefault: BOOL,
	      NewState: PTOKEN_GROUPS,
	  BufferLength: DWORD,
	 PreviousState: PTOKEN_GROUPS,
	  ReturnLength: PDWORD

PrivilegeCheck proto _CType \
	   ClientToken: HANDLE,
    RequiredPrivileges: PPRIVILEGE_SET,
	      pfResult: LPBOOL

AccessCheckAndAuditAlarmA proto _CType \
	 SubsystemName: LPCSTR,
	      HandleId: LPVOID,
	ObjectTypeName: LPSTR,
	    ObjectName: LPSTR,
    SecurityDescriptor: PSECURITY_DESCRIPTOR,
	 DesiredAccess: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	ObjectCreation: BOOL,
	 GrantedAccess: LPDWORD,
	  AccessStatus: LPBOOL,
     pfGenerateOnClose: LPBOOL

AccessCheckAndAuditAlarmW proto _CType \
	 SubsystemName: LPCWSTR,
	      HandleId: LPVOID,
	ObjectTypeName: LPWSTR,
	    ObjectName: LPWSTR,
    SecurityDescriptor: PSECURITY_DESCRIPTOR,
	 DesiredAccess: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	ObjectCreation: BOOL,
	 GrantedAccess: LPDWORD,
	  AccessStatus: LPBOOL,
     pfGenerateOnClose: LPBOOL
ifdef _UNICODE
AccessCheckAndAuditAlarm equ <AccessCheckAndAuditAlarmW>
else
AccessCheckAndAuditAlarm equ <AccessCheckAndAuditAlarmA>
endif

if(_WIN32_WINNT GE 0x0500)

AccessCheckByTypeAndAuditAlarmA proto _CType \
	 SubsystemName: LPCSTR,
	      HandleId: LPVOID,
	ObjectTypeName: LPCSTR,
	    ObjectName: LPCSTR,
    SecurityDescriptor: PSECURITY_DESCRIPTOR,
      PrincipalSelfSid: PSID,
	 DesiredAccess: DWORD,
	     AuditType: AUDIT_EVENT_TYPE,
		 Flags: DWORD,
	ObjectTypeList: POBJECT_TYPE_LIST,
  ObjectTypeListLength: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	ObjectCreation: BOOL,
	 GrantedAccess: LPDWORD,
	  AccessStatus: LPBOOL,
     pfGenerateOnClose: LPBOOL
AccessCheckByTypeAndAuditAlarmW proto _CType \
	 SubsystemName: LPCWSTR,
	      HandleId: LPVOID,
	ObjectTypeName: LPCWSTR,
	    ObjectName: LPCWSTR,
    SecurityDescriptor: PSECURITY_DESCRIPTOR,
      PrincipalSelfSid: PSID,
	 DesiredAccess: DWORD,
	     AuditType: AUDIT_EVENT_TYPE,
		 Flags: DWORD,
	ObjectTypeList: POBJECT_TYPE_LIST,
  ObjectTypeListLength: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	ObjectCreation: BOOL,
	 GrantedAccess: LPDWORD,
	  AccessStatus: LPBOOL,
     pfGenerateOnClose: LPBOOL
ifdef _UNICODE
AccessCheckByTypeAndAuditAlarm equ <AccessCheckByTypeAndAuditAlarmW>
else
AccessCheckByTypeAndAuditAlarm equ <AccessCheckByTypeAndAuditAlarmA>
endif

AccessCheckByTypeResultListAndAuditAlarmA proto _CType \
	 SubsystemName: LPCSTR,
	      HandleId: LPVOID,
	ObjectTypeName: LPCSTR,
	    ObjectName: LPCSTR,
    SecurityDescriptor: PSECURITY_DESCRIPTOR,
      PrincipalSelfSid: PSID,
	 DesiredAccess: DWORD,
	     AuditType: AUDIT_EVENT_TYPE,
		 Flags: DWORD,
	ObjectTypeList: POBJECT_TYPE_LIST,
  ObjectTypeListLength: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	ObjectCreation: BOOL,
	 GrantedAccess: LPDWORD,
      AccessStatusList: LPDWORD,
     pfGenerateOnClose: LPBOOL
AccessCheckByTypeResultListAndAuditAlarmW proto _CType \
	 SubsystemName: LPCWSTR,
	      HandleId: LPVOID,
	ObjectTypeName: LPCWSTR,
	    ObjectName: LPCWSTR,
    SecurityDescriptor: PSECURITY_DESCRIPTOR,
      PrincipalSelfSid: PSID,
	 DesiredAccess: DWORD,
	     AuditType: AUDIT_EVENT_TYPE,
		 Flags: DWORD,
	ObjectTypeList: POBJECT_TYPE_LIST,
  ObjectTypeListLength: DWORD,
	GenericMapping: PGENERIC_MAPPING,
	ObjectCreation: BOOL,
	 GrantedAccess: LPDWORD,
      AccessStatusList: LPDWORD,
     pfGenerateOnClose: LPBOOL
ifdef _UNICODE
AccessCheckByTypeResultListAndAuditAlarm equ <AccessCheckByTypeResultListAndAuditAlarmW>
else
AccessCheckByTypeResultListAndAuditAlarm equ <AccessCheckByTypeResultListAndAuditAlarmA>
endif

endif ;(_WIN32_WINNT >= 0x0500)

ObjectOpenAuditAlarmA proto _CType \
	 SubsystemName: LPCSTR,
	      HandleId: LPVOID,
	ObjectTypeName: LPSTR,
	    ObjectName: LPSTR,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	   ClientToken: HANDLE,
	 DesiredAccess: DWORD,
	 GrantedAccess: DWORD,
	    Privileges: PPRIVILEGE_SET,
	ObjectCreation: BOOL,
	 AccessGranted: BOOL,
       GenerateOnClose: LPBOOL
ObjectOpenAuditAlarmW proto _CType \
	 SubsystemName: LPCWSTR,
	      HandleId: LPVOID,
	ObjectTypeName: LPWSTR,
	    ObjectName: LPWSTR,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	   ClientToken: HANDLE,
	 DesiredAccess: DWORD,
	 GrantedAccess: DWORD,
	    Privileges: PPRIVILEGE_SET,
	ObjectCreation: BOOL,
	 AccessGranted: BOOL,
       GenerateOnClose: LPBOOL
ifdef _UNICODE
ObjectOpenAuditAlarm equ <ObjectOpenAuditAlarmW>
else
ObjectOpenAuditAlarm equ <ObjectOpenAuditAlarmA>
endif

ObjectPrivilegeAuditAlarmA proto _CType \
	 SubsystemName: LPCSTR,
	      HandleId: LPVOID,
	   ClientToken: HANDLE,
	 DesiredAccess: DWORD,
	    Privileges: PPRIVILEGE_SET,
	 AccessGranted: BOOL
ObjectPrivilegeAuditAlarmW proto _CType \
	 SubsystemName: LPCWSTR,
	      HandleId: LPVOID,
	   ClientToken: HANDLE,
	 DesiredAccess: DWORD,
	    Privileges: PPRIVILEGE_SET,
	 AccessGranted: BOOL
ifdef _UNICODE
ObjectPrivilegeAuditAlarm equ <ObjectPrivilegeAuditAlarmW>
else
ObjectPrivilegeAuditAlarm equ <ObjectPrivilegeAuditAlarmA>
endif

ObjectCloseAuditAlarmA proto _CType \
	 SubsystemName: LPCSTR,
	      HandleId: LPVOID,
       GenerateOnClose: BOOL
ObjectCloseAuditAlarmW proto _CType \
	 SubsystemName: LPCWSTR,
	      HandleId: LPVOID,
       GenerateOnClose: BOOL
ifdef _UNICODE
ObjectCloseAuditAlarm equ <ObjectCloseAuditAlarmW>
else
ObjectCloseAuditAlarm equ <ObjectCloseAuditAlarmA>
endif

ObjectDeleteAuditAlarmA proto _CType \
	 SubsystemName: LPCSTR,
	      HandleId: LPVOID,
       GenerateOnClose: BOOL
ObjectDeleteAuditAlarmW proto _CType \
	 SubsystemName: LPCWSTR,
	      HandleId: LPVOID,
       GenerateOnClose: BOOL
ifdef _UNICODE
ObjectDeleteAuditAlarm equ <ObjectDeleteAuditAlarmW>
else
ObjectDeleteAuditAlarm equ <ObjectDeleteAuditAlarmA>
endif

PrivilegedServiceAuditAlarmA proto _CType \
	 SubsystemName: LPCSTR,
	   ServiceName: LPCSTR,
	   ClientToken: HANDLE,
	    Privileges: PPRIVILEGE_SET,
	 AccessGranted: BOOL
PrivilegedServiceAuditAlarmW proto _CType \
	 SubsystemName: LPCWSTR,
	   ServiceName: LPCWSTR,
	   ClientToken: HANDLE,
	    Privileges: PPRIVILEGE_SET,
	 AccessGranted: BOOL
ifdef _UNICODE
PrivilegedServiceAuditAlarm equ <PrivilegedServiceAuditAlarmW>
else
PrivilegedServiceAuditAlarm equ <PrivilegedServiceAuditAlarmA>
endif

IsValidSid proto _CType \
		  pSid: PSID

EqualSid proto _CType \
		 pSid1: PSID,
		 pSid2: PSID

EqualPrefixSid proto _CType \
		 pSid1: PSID,
		 pSid2: PSID
;DWORD
GetSidLengthRequired proto _CType \
    nSubAuthorityCount: DWORD;UCHAR
;BOOL
AllocateAndInitializeSid proto _CType \
  pIdentifierAuthority: PSID_IDENTIFIER_AUTHORITY,
    nSubAuthorityCount: BYTE,
	nSubAuthority0: DWORD,
	nSubAuthority1: DWORD,
	nSubAuthority2: DWORD,
	nSubAuthority3: DWORD,
	nSubAuthority4: DWORD,
	nSubAuthority5: DWORD,
	nSubAuthority6: DWORD,
	nSubAuthority7: DWORD,
		  pSid: PTR PSID
;PVOID
FreeSid proto _CType \
		  pSid: PSID
;BOOL
InitializeSid proto _CType \
		   Sid: PSID,
  pIdentifierAuthority: PSID_IDENTIFIER_AUTHORITY,
    nSubAuthorityCount: DWORD;BYTE
;PSID_IDENTIFIER_AUTHORITY
GetSidIdentifierAuthority proto _CType \
		  pSid: PSID
;PDWORD
GetSidSubAuthority proto _CType \
		  pSid: PSID,
	 nSubAuthority: DWORD
;PUCHAR
GetSidSubAuthorityCount proto _CType \
		  pSid: PSID
;DWORD
GetLengthSid proto _CType \
		  pSid: PSID
;BOOL
CopySid proto _CType \
 nDestinationSidLength: DWORD,
       pDestinationSid: PSID,
	    pSourceSid: PSID

AreAllAccessesGranted proto _CType \
	 GrantedAccess: DWORD,
	 DesiredAccess: DWORD

AreAnyAccessesGranted proto _CType \
	 GrantedAccess: DWORD,
	 DesiredAccess: DWORD
;VOID
MapGenericMask proto _CType \
	    AccessMask: PDWORD,
	GenericMapping: PGENERIC_MAPPING
;BOOL
IsValidAcl proto _CType \
		  pAcl: PACL

InitializeAcl proto _CType \
		  pAcl: PACL,
	    nAclLength: DWORD,
	 dwAclRevision: DWORD

GetAclInformation proto _CType \
		  pAcl: PACL,
       pAclInformation: LPVOID,
 nAclInformationLength: DWORD,
 dwAclInformationClass: ACL_INFORMATION_CLASS

SetAclInformation proto _CType \
		  pAcl: PACL,
       pAclInformation: LPVOID,
 nAclInformationLength: DWORD,
 dwAclInformationClass: ACL_INFORMATION_CLASS

AddAce proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
    dwStartingAceIndex: DWORD,
	      pAceList: LPVOID,
	nAceListLength: DWORD

DeleteAce proto _CType \
		  pAcl: PACL,
	    dwAceIndex: DWORD

GetAce proto _CType \
		  pAcl: PACL,
	    dwAceIndex: DWORD,
		  pAce: PTR LPVOID

AddAccessAllowedAce proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	    AccessMask: DWORD,
		  pSid: PSID

if(_WIN32_WINNT GE 0x0500)
AddAccessAllowedAceEx proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	      AceFlags: DWORD,
	    AccessMask: DWORD,
		  pSid: PSID
endif

AddAccessDeniedAce proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	    AccessMask: DWORD,
		  pSid: PSID

if (_WIN32_WINNT GE 0x0500)

AddAccessDeniedAceEx proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	      AceFlags: DWORD,
	    AccessMask: DWORD,
		  pSid: PSID
endif

AddAuditAccessAce proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	  dwAccessMask: DWORD,
		  pSid: PSID,
	 bAuditSuccess: BOOL,
	 bAuditFailure: BOOL

if (_WIN32_WINNT GE 0x0500)

AddAuditAccessAceEx proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	      AceFlags: DWORD,
	  dwAccessMask: DWORD,
		  pSid: PSID,
	 bAuditSuccess: BOOL,
	 bAuditFailure: BOOL

AddAccessAllowedObjectAce proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	      AceFlags: DWORD,
	    AccessMask: DWORD,
	ObjectTypeGuid: PTR GUID,
InheritedObjectTypeGuid: PTR GUID,
		  pSid: PSID

AddAccessDeniedObjectAce proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	      AceFlags: DWORD,
	    AccessMask: DWORD,
	ObjectTypeGuid: PTR GUID,
InheritedObjectTypeGuid: PTR GUID,
		  pSid: PSID

AddAuditAccessObjectAce proto _CType \
		  pAcl: PACL,
	 dwAceRevision: DWORD,
	      AceFlags: DWORD,
	    AccessMask: DWORD,
	ObjectTypeGuid: PTR GUID,
InheritedObjectTypeGuid: PTR GUID,
		  pSid: PSID,
	 bAuditSuccess: BOOL,
	 bAuditFailure: BOOL
endif


FindFirstFreeAce proto _CType \
		  pAcl: PACL,
		  pAce: PTR LPVOID

InitializeSecurityDescriptor proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	    dwRevision: DWORD

IsValidSecurityDescriptor proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR
;DWORD
GetSecurityDescriptorLength proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR
;BOOL
GetSecurityDescriptorControl proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	      pControl: PSECURITY_DESCRIPTOR_CONTROL,
	  lpdwRevision: LPDWORD

if (_WIN32_WINNT GE 0x0500)

SetSecurityDescriptorControl proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
 ControlBitsOfInterest: SECURITY_DESCRIPTOR_CONTROL,
      ControlBitsToSet: SECURITY_DESCRIPTOR_CONTROL
endif

SetSecurityDescriptorDacl proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	  bDaclPresent: BOOL,
		 pDacl: PACL,
	bDaclDefaulted: BOOL

GetSecurityDescriptorDacl proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	lpbDaclPresent: LPBOOL,
		 pDacl: PTR PACL,
      lpbDaclDefaulted: LPBOOL

SetSecurityDescriptorSacl proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	  bSaclPresent: BOOL,
		 pSacl: PACL,
	bSaclDefaulted: BOOL

GetSecurityDescriptorSacl proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	lpbSaclPresent: LPBOOL,
		 pSacl: PTR PACL,
      lpbSaclDefaulted: LPBOOL

SetSecurityDescriptorOwner proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
		pOwner: PSID,
       bOwnerDefaulted: BOOL

GetSecurityDescriptorOwner proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
		pOwner: PTR PSID,
     lpbOwnerDefaulted: LPBOOL

SetSecurityDescriptorGroup proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
		pGroup: PSID,
       bGroupDefaulted: BOOL

GetSecurityDescriptorGroup proto _CType \
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
		pGroup: PTR PSID,
     lpbGroupDefaulted: LPBOOL

CreatePrivateObjectSecurity proto _CType \
      ParentDescriptor: PSECURITY_DESCRIPTOR,
     CreatorDescriptor: PSECURITY_DESCRIPTOR,
	 NewDescriptor: PTR PSECURITY_DESCRIPTOR,
     IsDirectoryObject: BOOL,
		 Token: HANDLE,
	GenericMapping: PGENERIC_MAPPING

if (_WIN32_WINNT GE 0x0500)

ConvertToAutoInheritPrivateObjectSecurity proto _CType \
      ParentDescriptor: PSECURITY_DESCRIPTOR,
CurrentSecurityDescriptor: PSECURITY_DESCRIPTOR,
 NewSecurityDescriptor: PTR PSECURITY_DESCRIPTOR,
	    ObjectType: PTR GUID,
     IsDirectoryObject: BOOLEAN,
	GenericMapping: PGENERIC_MAPPING

CreatePrivateObjectSecurityEx proto _CType \
      ParentDescriptor: PSECURITY_DESCRIPTOR,
     CreatorDescriptor: PSECURITY_DESCRIPTOR,
	 NewDescriptor: PTR PSECURITY_DESCRIPTOR,
	    ObjectType: PTR GUID,
     IsContainerObject: BOOL,
      AutoInheritFlags: ULONG,
		 Token: HANDLE,
	GenericMapping: PGENERIC_MAPPING

endif ; _WIN32_WINNT >=	 0x0500

SetPrivateObjectSecurity proto _CType \
   SecurityInformation: SECURITY_INFORMATION,
ModificationDescriptor: PSECURITY_DESCRIPTOR,
ObjectsSecurityDescriptor: PTR PSECURITY_DESCRIPTOR,
	GenericMapping: PGENERIC_MAPPING,
		 Token: HANDLE

if (_WIN32_WINNT GE 0x0500)

SetPrivateObjectSecurityEx proto _CType \
   SecurityInformation: SECURITY_INFORMATION,
ModificationDescriptor: PSECURITY_DESCRIPTOR,
ObjectsSecurityDescriptor: PTR PSECURITY_DESCRIPTOR,
      AutoInheritFlags: ULONG,
	GenericMapping: PGENERIC_MAPPING,
		 Token: HANDLE ;OPTIONAL
endif ; _WIN32_WINNT >=	 equ 0x0500


GetPrivateObjectSecurity proto _CType \
      ObjectDescriptor: PSECURITY_DESCRIPTOR,
   SecurityInformation: SECURITY_INFORMATION,
   ResultantDescriptor: PSECURITY_DESCRIPTOR,
      DescriptorLength: DWORD,
	  ReturnLength: PDWORD

DestroyPrivateObjectSecurity proto _CType \
      ObjectDescriptor: PTR PSECURITY_DESCRIPTOR

MakeSelfRelativeSD proto _CType \
pAbsoluteSecurityDescriptor: PSECURITY_DESCRIPTOR,
pSelfRelativeSecurityDescriptor: PSECURITY_DESCRIPTOR,
      lpdwBufferLength: LPDWORD

MakeAbsoluteSD proto _CType \
pSelfRelativeSecurityDescriptor: PSECURITY_DESCRIPTOR,
pAbsoluteSecurityDescriptor: PSECURITY_DESCRIPTOR,
lpdwAbsoluteSecurityDescriptorSize: LPDWORD,
		 pDacl: PACL,
	  lpdwDaclSize: LPDWORD,
		 pSacl: PACL,
	  lpdwSaclSize: LPDWORD,
		pOwner: PSID,
	 lpdwOwnerSize: LPDWORD,
	 pPrimaryGroup: PSID,
  lpdwPrimaryGroupSize: LPDWORD

SetFileSecurityA proto _CType \
	    lpFileName: LPCSTR,
   SecurityInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR
SetFileSecurityW proto _CType \
	    lpFileName: LPCWSTR,
   SecurityInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR
ifdef _UNICODE
SetFileSecurity equ <SetFileSecurityW>
else
SetFileSecurity equ <SetFileSecurityA>
endif


GetFileSecurityA proto _CType \
	    lpFileName: LPCSTR,
  RequestedInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	       nLength: DWORD,
       lpnLengthNeeded: LPDWORD
GetFileSecurityW proto _CType \
	    lpFileName: LPCWSTR,
  RequestedInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
	       nLength: DWORD,
       lpnLengthNeeded: LPDWORD
ifdef _UNICODE
GetFileSecurity equ <GetFileSecurityW>
else
GetFileSecurity equ <GetFileSecurityA>
endif


SetKernelObjectSecurity proto _CType \
		Handle: HANDLE,
   SecurityInformation: SECURITY_INFORMATION,
    SecurityDescriptor: PSECURITY_DESCRIPTOR
;HANDLE
FindFirstChangeNotificationA proto _CType \
	    lpPathName: LPCSTR,
	 bWatchSubtree: BOOL,
	dwNotifyFilter: DWORD
FindFirstChangeNotificationW proto _CType \
	    lpPathName: LPCWSTR,
	 bWatchSubtree: BOOL,
	dwNotifyFilter: DWORD
ifdef _UNICODE
FindFirstChangeNotification equ <FindFirstChangeNotificationW>
else
FindFirstChangeNotification equ <FindFirstChangeNotificationA>
endif

;BOOL
FindNextChangeNotification proto _CType \
	 hChangeHandle: HANDLE

FindCloseChangeNotification proto _CType \
	 hChangeHandle: HANDLE

if (_WIN32_WINNT GE 0x0400)

ReadDirectoryChangesW proto _CType \
	    hDirectory: HANDLE,
	      lpBuffer: LPVOID,
	 nBufferLength: DWORD,
	 bWatchSubtree: BOOL,
	dwNotifyFilter: DWORD,
       lpBytesReturned: LPDWORD,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPOVERLAPPED_COMPLETION_ROUTINE

endif	; _WIN32_WINNT >= equ 0x0400

VirtualLock proto _CType \
	     lpAddress: LPVOID,
		dwSize: DWORD

VirtualUnlock proto _CType \
	     lpAddress: LPVOID,
		dwSize: DWORD
;LPVOID
MapViewOfFileEx proto _CType \
    hFileMappingObject: HANDLE,
       dwDesiredAccess: DWORD,
      dwFileOffsetHigh: DWORD,
       dwFileOffsetLow: DWORD,
  dwNumberOfBytesToMap: DWORD,
	 lpBaseAddress: LPVOID
;BOOL
SetPriorityClass proto _CType \
	      hProcess: HANDLE,
       dwPriorityClass: DWORD
;DWORD
GetPriorityClass proto _CType \
	      hProcess: HANDLE
;BOOL
IsBadReadPtr proto _CType \
		    lp: LPVOID,
		   ucb: UINT

IsBadWritePtr proto _CType \
		    lp: LPVOID,
		   ucb: UINT

IsBadHugeReadPtr proto _CType \
		    lp: LPVOID,
		   ucb: UINT

IsBadHugeWritePtr proto _CType \
		    lp: LPVOID,
		   ucb: UINT

IsBadCodePtr proto _CType \
		  lpfn: FARPROC

IsBadStringPtrA proto _CType \
		  lpsz: LPCSTR,
	       ucchMax: UINT
IsBadStringPtrW proto _CType \
		  lpsz: LPCWSTR,
	       ucchMax: UINT
ifdef UNICODE
IsBadStringPtr equ <IsBadStringPtrW>
else
IsBadStringPtr equ <IsBadStringPtrA>
endif

LookupAccountSidA proto _CType \
	  lpSystemName: LPCSTR,
		   Sid: PSID,
		 _Name: LPSTR,
		cbName: LPDWORD,
  ReferencedDomainName: LPSTR,
cbReferencedDomainName: LPDWORD,
		 peUse: PSID_NAME_USE

LookupAccountSidW proto _CType \
	  lpSystemName: LPCWSTR,
		   Sid: PSID,
		 _Name: LPWSTR,
		cbName: LPDWORD,
  ReferencedDomainName: LPWSTR,
cbReferencedDomainName: LPDWORD,
		 peUse: PSID_NAME_USE
ifdef _UNICODE
LookupAccountSid equ <LookupAccountSidW>
else
LookupAccountSid equ <LookupAccountSidA>
endif

LookupAccountNameA proto _CType \
	  lpSystemName: LPCSTR,
	 lpAccountName: LPCSTR,
		   Sid: PSID,
		 cbSid: LPDWORD,
  ReferencedDomainName: LPSTR,
cbReferencedDomainName: LPDWORD,
		 peUse: PSID_NAME_USE

LookupAccountNameW proto _CType \
	  lpSystemName: LPCWSTR,
	 lpAccountName: LPCWSTR,
		   Sid: PSID,
		 cbSid: LPDWORD,
  ReferencedDomainName: LPWSTR,
cbReferencedDomainName: LPDWORD,
		 peUse: PSID_NAME_USE
ifdef _UNICODE
LookupAccountName equ <LookupAccountNameW>
else
LookupAccountName equ <LookupAccountNameA>
endif

LookupPrivilegeValueA proto _CType \
	  lpSystemName: LPCSTR,
		lpName: LPCSTR,
		lpLuid: PLUID
LookupPrivilegeValueW proto _CType \
	  lpSystemName: LPCWSTR,
		lpName: LPCWSTR,
		lpLuid: PLUID
ifdef _UNICODE
LookupPrivilegeValue equ <LookupPrivilegeValueW>
else
LookupPrivilegeValue equ <LookupPrivilegeValueA>
endif

LookupPrivilegeNameA proto _CType \
	  lpSystemName: LPCSTR,
		lpLuid: PLUID,
		lpName: LPSTR,
		cbName: LPDWORD
LookupPrivilegeNameW proto _CType \
	  lpSystemName: LPCWSTR,
		lpLuid: PLUID,
		lpName: LPWSTR,
		cbName: LPDWORD
ifdef _UNICODE
LookupPrivilegeName equ <LookupPrivilegeNameW>
else
LookupPrivilegeName equ <LookupPrivilegeNameA>
endif

LookupPrivilegeDisplayNameA proto _CType \
	  lpSystemName: LPCSTR,
		lpName: LPCSTR,
	 lpDisplayName: LPSTR,
	 cbDisplayName: LPDWORD,
	  lpLanguageId: LPDWORD
LookupPrivilegeDisplayNameW proto _CType \
	  lpSystemName: LPCWSTR,
		lpName: LPCWSTR,
	 lpDisplayName: LPWSTR,
	 cbDisplayName: LPDWORD,
	  lpLanguageId: LPDWORD
ifdef _UNICODE
LookupPrivilegeDisplayName equ <LookupPrivilegeDisplayNameW>
else
LookupPrivilegeDisplayName equ <LookupPrivilegeDisplayNameA>
endif

AllocateLocallyUniqueId proto _CType \
		  Luid: PLUID

BuildCommDCBA proto _CType \
		 lpDef: LPCSTR,
		 lpDCB: LPDCB
BuildCommDCBW proto _CType lpDef:LPCWSTR, lpDCB:LPDCB
ifdef _UNICODE
BuildCommDCB equ <BuildCommDCBW>
else
BuildCommDCB equ <BuildCommDCBA>
endif

BuildCommDCBAndTimeoutsA proto _CType \
		 lpDef: LPCSTR,
		 lpDCB: LPDCB,
	lpCommTimeouts: LPCOMMTIMEOUTS
BuildCommDCBAndTimeoutsW proto _CType \
		 lpDef: LPCWSTR,
		 lpDCB: LPDCB,
	lpCommTimeouts: LPCOMMTIMEOUTS
ifdef _UNICODE
BuildCommDCBAndTimeouts equ <BuildCommDCBAndTimeoutsW>
else
BuildCommDCBAndTimeouts equ <BuildCommDCBAndTimeoutsA>
endif

CommConfigDialogA proto _CType \
	      lpszName: LPCSTR,
		  hWnd: HWND,
		  lpCC: LPCOMMCONFIG
CommConfigDialogW proto _CType \
	      lpszName: LPCWSTR,
		  hWnd: HWND,
		  lpCC: LPCOMMCONFIG
ifdef _UNICODE
CommConfigDialog equ <CommConfigDialogW>
else
CommConfigDialog equ <CommConfigDialogA>
endif

GetDefaultCommConfigA proto _CType \
	      lpszName: LPCSTR,
		  lpCC: LPCOMMCONFIG,
	      lpdwSize: LPDWORD
GetDefaultCommConfigW proto _CType \
	      lpszName: LPCWSTR,
		  lpCC: LPCOMMCONFIG,
	      lpdwSize: LPDWORD
ifdef _UNICODE
GetDefaultCommConfig equ <GetDefaultCommConfigW>
else
GetDefaultCommConfig equ <GetDefaultCommConfigA>
endif

SetDefaultCommConfigA proto _CType \
	      lpszName: LPCSTR,
		  lpCC: LPCOMMCONFIG,
		dwSize: DWORD
SetDefaultCommConfigW proto _CType \
	      lpszName: LPCWSTR,
		  lpCC: LPCOMMCONFIG,
		dwSize: DWORD
ifdef _UNICODE
SetDefaultCommConfig equ <SetDefaultCommConfigW>
else
SetDefaultCommConfig equ <SetDefaultCommConfigA>
endif

MAX_COMPUTERNAME_LENGTH equ 15

GetComputerNameA proto _CType \
	      lpBuffer: LPSTR,
		 nSize: LPDWORD
GetComputerNameW proto _CType \
	      lpBuffer: LPWSTR,
		 nSize: LPDWORD
ifdef _UNICODE
GetComputerName equ <GetComputerNameW>
else
GetComputerName equ <GetComputerNameA>
endif

SetComputerNameA proto _CType \
	lpComputerName: LPCSTR
SetComputerNameW proto _CType \
	lpComputerName: LPCWSTR
ifdef _UNICODE
SetComputerName equ <SetComputerNameW>
else
SetComputerName equ <SetComputerNameA>
endif

GetUserNameA proto _CType \
	      lpBuffer: LPSTR,
		 nSize: LPDWORD
GetUserNameW proto _CType \
	      lpBuffer: LPWSTR,
		 nSize: LPDWORD
ifdef _UNICODE
GetUserName equ <GetUserNameW>
else
GetUserName equ <GetUserNameA>
endif

;
; Logon Support APIs
;

LOGON32_LOGON_INTERACTIVE   equ 2
LOGON32_LOGON_NETWORK	    equ 3
LOGON32_LOGON_BATCH	    equ 4
LOGON32_LOGON_SERVICE	    equ 5

LOGON32_PROVIDER_DEFAULT    equ 0
LOGON32_PROVIDER_WINNT35    equ 1
if(_WIN32_WINNT GE 0x0400)
LOGON32_PROVIDER_WINNT40    equ 2
endif
if(_WIN32_WINNT GE 0x0500)
LOGON32_PROVIDER_WINNT50    equ 3
endif

LogonUserA proto _CType \
	  lpszUsername: LPSTR,
	    lpszDomain: LPSTR,
	  lpszPassword: LPSTR,
	   dwLogonType: DWORD,
       dwLogonProvider: DWORD,
	       phToken: PHANDLE
LogonUserW proto _CType \
	  lpszUsername: LPWSTR,
	    lpszDomain: LPWSTR,
	  lpszPassword: LPWSTR,
	   dwLogonType: DWORD,
       dwLogonProvider: DWORD,
	       phToken: PHANDLE
ifdef _UNICODE
LogonUser equ <LogonUserW>
else
LogonUser equ <LogonUserA>
endif

ImpersonateLoggedOnUser proto _CType \
		hToken: HANDLE

CreateProcessAsUserA proto _CType \
		hToken: HANDLE,
     lpApplicationName: LPCSTR,
	 lpCommandLine: LPSTR,
   lpProcessAttributes: LPSECURITY_ATTRIBUTES,
    lpThreadAttributes: LPSECURITY_ATTRIBUTES,
       bInheritHandles: BOOL,
       dwCreationFlags: DWORD,
	 lpEnvironment: LPVOID,
    lpCurrentDirectory: LPCSTR,
	 lpStartupInfo: LPSTARTUPINFOA,
  lpProcessInformation: LPPROCESS_INFORMATION
CreateProcessAsUserW proto _CType \
		hToken: HANDLE,
     lpApplicationName: LPCWSTR,
	 lpCommandLine: LPWSTR,
   lpProcessAttributes: LPSECURITY_ATTRIBUTES,
    lpThreadAttributes: LPSECURITY_ATTRIBUTES,
       bInheritHandles: BOOL,
       dwCreationFlags: DWORD,
	 lpEnvironment: LPVOID,
    lpCurrentDirectory: LPCWSTR,
	 lpStartupInfo: LPSTARTUPINFOA,
  lpProcessInformation: LPPROCESS_INFORMATION
ifdef _UNICODE
CreateProcessAsUser equ <CreateProcessAsUserW>
else
PreateProcessAsUser equ <CreateProcessAsUserA>
endif

;BOOL
uplicateTokenEx proto _CType \
	hExistingToken: HANDLE,
       dwDesiredAccess: DWORD,
     lpTokenAttributes: LPSECURITY_ATTRIBUTES,
    ImpersonationLevel: SECURITY_IMPERSONATION_LEVEL,
	     TokenType: TOKEN_TYPE,
	    phNewToken: PHANDLE

CreateRestrictedToken proto _CType \
   ExistingTokenHandle: HANDLE,
		 Flags: DWORD,
       DisableSidCount: DWORD,
	 SidsToDisable: PSID_AND_ATTRIBUTES,
  DeletePrivilegeCount: DWORD,
    PrivilegesToDelete: PLUID_AND_ATTRIBUTES,
    RestrictedSidCount: DWORD,
	SidsToRestrict: PSID_AND_ATTRIBUTES,
	NewTokenHandle: PHANDLE

IsTokenRestricted proto _CType \
	   TokenHandle: HANDLE


if(_WIN32_WINNT GE 0x0400)
;
; Plug-and-Play API's
;

HW_PROFILE_GUIDLEN	   equ 39	   ; 36-characters plus NULL terminator
MAX_PROFILE_LEN		   equ 80

DOCKINFO_UNDOCKED	   equ 0x1
DOCKINFO_DOCKED		   equ 0x2
DOCKINFO_USER_SUPPLIED	   equ 0x4
DOCKINFO_USER_UNDOCKED	   equ (DOCKINFO_USER_SUPPLIED or DOCKINFO_UNDOCKED)
DOCKINFO_USER_DOCKED	   equ (DOCKINFO_USER_SUPPLIED or DOCKINFO_DOCKED)

HW_PROFILE_INFOA	STRUC
dwDockInfo		dd ?
szHwProfileGuid		db HW_PROFILE_GUIDLEN dup(?)
szHwProfileName		db MAX_PROFILE_LEN dup(?)
HW_PROFILE_INFOA	ENDS

HW_PROFILE_INFOW	STRUC
dwDockInfo		dd ?
szHwProfileGuid		dw HW_PROFILE_GUIDLEN dup(?)
szHwProfileName		dw MAX_PROFILE_LEN dup(?)
HW_PROFILE_INFOW	ENDS

LPHW_PROFILE_INFOA	typedef ptr HW_PROFILE_INFOA
LPHW_PROFILE_INFOW	typedef ptr HW_PROFILE_INFOW

ifdef _UNICODE
HW_PROFILE_INFO		typedef HW_PROFILE_INFOW
LPHW_PROFILE_INFO	typedef LPHW_PROFILE_INFOW
else
HW_PROFILE_INFO		typedef HW_PROFILE_INFOA
LPHW_PROFILE_INFO	typedef LPHW_PROFILE_INFOA
endif

;BOOL
GetCurrentHwProfileA proto _CType \
       lpHwProfileInfo: LPHW_PROFILE_INFOA
GetCurrentHwProfileW proto _CType \
       lpHwProfileInfo: LPHW_PROFILE_INFOW
ifdef _UNICODE
GetCurrentHwProfile equ <GetCurrentHwProfileW>
else
GetCurrentHwProfile equ <GetCurrentHwProfileA>
endif
endif

;
; Performance counter API's
;

;BOOL
QueryPerformanceCounter proto _CType \
    lpPerformanceCount: PTR LARGE_INTEGER

QueryPerformanceFrequency proto _CType \
	   lpFrequency: PTR LARGE_INTEGER

OSVERSIONINFOA		STRUC
dwOSVersionInfoSize	dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformId		dd ?
szCSDVersion		db 128 dup(?) ; Maintenance string for PSS usage
OSVERSIONINFOA		ENDS

POSVERSIONINFOA		TYPEDEF PTR OSVERSIONINFOA
LPOSVERSIONINFOA	TYPEDEF PTR OSVERSIONINFOA

OSVERSIONINFOW		STRUC
dwOSVersionInfoSize	dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformId		dd ?
szCSDVersion		dw 128 dup(?) ; Maintenance string for PSS usage
OSVERSIONINFOW		ENDS

POSVERSIONINFOW		TYPEDEF PTR OSVERSIONINFOW
LPOSVERSIONINFOW	TYPEDEF PTR OSVERSIONINFOW

ifdef _UNICODE
OSVERSIONINFO	typedef OSVERSIONINFOW
POSVERSIONINFO	typedef POSVERSIONINFOW
LPOSVERSIONINFO typedef LPOSVERSIONINFOW
else
OSVERSIONINFO	typedef OSVERSIONINFOA
POSVERSIONINFO	typedef POSVERSIONINFOA
LPOSVERSIONINFO typedef LPOSVERSIONINFOA
endif

OSVERSIONINFOEXA	STRUC
dwOSVersionInfoSize	dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformId		dd ?
szCSDVersion		db 128 dup(?)	; Maintenance string for PSS usage
wServicePackMajor	dw ?
wServicePackMinor	dw ?
wReserved		dw 2 dup(?)
OSVERSIONINFOEXA	ENDS

POSVERSIONINFOEXA	typedef PTR OSVERSIONINFOEXA
LPOSVERSIONINFOEXA	typedef PTR OSVERSIONINFOEXA

OSVERSIONINFOEXW	STRUC
dwOSVersionInfoSize	dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformId		dd ?
szCSDVersion		dw 128 dup(?)	; Maintenance string for PSS usage
wServicePackMajor	dw ?
wServicePackMinor	dw ?
wReserved		dw 2 dup(?)
OSVERSIONINFOEXW	ENDS

POSVERSIONINFOEXW	typedef PTR OSVERSIONINFOEXW
LPOSVERSIONINFOEXW	typedef PTR OSVERSIONINFOEXW

ifdef _UNICODE
OSVERSIONINFOEX		typedef OSVERSIONINFOEXW
POSVERSIONINFOEX	typedef POSVERSIONINFOEXW
LPOSVERSIONINFOEX	typedef LPOSVERSIONINFOEXW
else
OSVERSIONINFOEX		typedef OSVERSIONINFOEXA
POSVERSIONINFOEX	typedef POSVERSIONINFOEXA
LPOSVERSIONINFOEX	typedef LPOSVERSIONINFOEXA
endif

;
; dwPlatformId defines:
;

VER_PLATFORM_WIN32s		equ 0
VER_PLATFORM_WIN32_WINDOWS	equ 1
VER_PLATFORM_WIN32_NT		equ 2


;BOOL
GetVersionExA proto _CType \
  lpVersionInformation: LPOSVERSIONINFOA
GetVersionExW proto _CType \
  lpVersionInformation: LPOSVERSIONINFOW
ifdef _UNICODE
GetVersionEx equ <GetVersionExW>
else
GetVersionEx equ <GetVersionExA>
endif

; Abnormal termination codes

TC_NORMAL	equ 0
TC_HARDERR	equ 1
TC_GP_TRAP	equ 2
TC_SIGNAL	equ 3

if (WINVER GE 0x0400)
;
; Power Management APIs
;

AC_LINE_OFFLINE			equ 0x00
AC_LINE_ONLINE			equ 0x01
AC_LINE_BACKUP_POWER		equ 0x02
AC_LINE_UNKNOWN			equ 0xFF

BATTERY_FLAG_HIGH		equ 0x01
BATTERY_FLAG_LOW		equ 0x02
BATTERY_FLAG_CRITICAL		equ 0x04
BATTERY_FLAG_CHARGING		equ 0x08
BATTERY_FLAG_NO_BATTERY		equ 0x80
BATTERY_FLAG_UNKNOWN		equ 0xFF

BATTERY_PERCENTAGE_UNKNOWN	equ 0xFF

BATTERY_LIFE_UNKNOWN	equ 0xFFFFFFFF

SYSTEM_POWER_STATUS	STRUC
ACLineStatus		BYTE ?
BatteryFlag		BYTE ?
BatteryLifePercent	BYTE ?
Reserved1		BYTE ?
BatteryLifeTime		DWORD ?
BatteryFullLifeTime	DWORD ?
SYSTEM_POWER_STATUS	ENDS

LPSYSTEM_POWER_STATUS	TYPEDEF PTR SYSTEM_POWER_STATUS

;BOOL
GetSystemPowerStatus proto _CType \
   lpSystemPowerStatus: LPSYSTEM_POWER_STATUS
;BOOL
SetSystemPowerState proto _CType \
	      fSuspend: BOOL,
		fForce: BOOL

endif

;
; Win Certificate API and Structures
;

;
; Structures
;

WIN_CERTIFICATE		STRUC
dwLength		dd ?
wRevision		dw ?
wCertificateType	dw ? ; WIN_CERT_TYPE_xxx
bCertificate		SBYTE ANYSIZE_ARRAY dup(?)
WIN_CERTIFICATE		ENDS
LPWIN_CERTIFICATE	typedef ptr WIN_CERTIFICATE

;
; Currently, the only defined certificate revision is WIN_CERT_REVISION_1_0
;

WIN_CERT_REVISION_1_0	equ 0x0100
WIN_CERT_REVISION_2_0	equ 0x0200

;
; Possible certificate types are specified by the following values
;

 WIN_CERT_TYPE_X509		  equ 0x0001	; bCertificate contains an X.509 Certificate
 WIN_CERT_TYPE_PKCS_SIGNED_DATA	  equ 0x0002	; bCertificate contains a PKCS SignedData structure
 WIN_CERT_TYPE_RESERVED_1	  equ 0x0003	; Reserved

;
; API
;

;BOOL
WinSubmitCertificate proto _CType \
	 lpCertificate: LPWIN_CERTIFICATE

;
; Trust API and Structures
;

;LONG
WinVerifyTrust proto _CType \
		  hwnd: HWND,
	      ActionID: PVOID, ; GUID *
	    ActionData: PVOID

WinLoadTrustProvider proto _CType \
	      ActionID: PVOID ; GUID *

;
; Common Trust API Data Structures
;

;
; Data type commonly used in ActionData structures
;

WIN_TRUST_SUBJECT typedef PVOID

;
; Two commonly used ActionData structures
;

WIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT STRUC

hClientToken	HANDLE ?
SubjectType	PVOID ? ; GUID *
Subject		WIN_TRUST_SUBJECT ?

WIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT ENDS
LPWIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT typedef ptr WIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT


WIN_TRUST_ACTDATA_SUBJECT_ONLY STRUC

SubjectType	PVOID ? ; GUID *
Subject		WIN_TRUST_SUBJECT ?

WIN_TRUST_ACTDATA_SUBJECT_ONLY ENDS
LPWIN_TRUST_ACTDATA_SUBJECT_ONLY TYPEDEF PTR WIN_TRUST_ACTDATA_SUBJECT_ONLY


;
; SUBJECT FORM DEFINITIONS
;

;
; Currently defined Subject Type Identifiers.  All of the below
; use the WIN_TRUST_SUBJECT_FILE subject form, defined below.
;

;
; Associated Subject Data Structure:
;

WIN_TRUST_SUBJECT_FILE STRUC

hFile	HANDLE ?
lpPath	LPWSTR ?

WIN_TRUST_SUBJECT_FILE ENDS
LPWIN_TRUST_SUBJECT_FILE TYPEDEF PTR WIN_TRUST_SUBJECT_FILE


;
; The following subject types use the
; WIN_TRUST_SUBJECT_FILE_AND_DISPLAY subject type, defined
; below.
;

;
; Associated Subject Data Structure:
;

WIN_TRUST_SUBJECT_FILE_AND_DISPLAY STRUC

hFile		HANDLE ?	; handle to the open file if you got it
lpPath		LPWSTR ?	; the path to open if you don't
lpDisplayName	LPWSTR ?	;	; (optional) display name to show to user
				;      in place of path

WIN_TRUST_SUBJECT_FILE_AND_DISPLAY ENDS
LPWIN_TRUST_SUBJECT_FILE_AND_DISPLAY TYPEDEF PTR WIN_TRUST_SUBJECT_FILE_AND_DISPLAY


;
; Other subject types:
;


;
; Data Structures:
;
; WIN_SPUB_ACTION_TRUSTED_PUBLISHER:
;
;      Uses WIN_SPUB_TRUSTED_PUBLISHER_DATA
;
; WIN_SPUB_ACTION_NT_ACTIVATE_IMAGE:
;
;      Uses WIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT
;
; WIN_SPUB_ACTION_PUBLISHED_SOFTWARE:
;
;      Uses WIN_TRUST_ACTDATA_CONTEXT_WITH_SUBJECT
;

WIN_SPUB_TRUSTED_PUBLISHER_DATA STRUC
hClientToken	HANDLE ?
lpCertificate	LPWIN_CERTIFICATE ?
WIN_SPUB_TRUSTED_PUBLISHER_DATA ENDS
LPWIN_SPUB_TRUSTED_PUBLISHER_DATA TYPEDEF PTR WIN_SPUB_TRUSTED_PUBLISHER_DATA

if (_WIN32_WINNT GE 0x0500)
;
; Very Large Memory API Subset
;

;PVOID64
VirtualAllocVlm proto _CType \
	      hProcess: HANDLE,
	     lpAddress: PVOID64,
	       ullSize: DWORDLONG,
      flAllocationType: DWORD,
	     flProtect: DWORD
;BOOL
VirtualFreeVlm proto _CType \
	      hProcess: HANDLE,
	     lpAddress: PVOID64,
	       ullSize: DWORDLONG,
	    dwFreeType: DWORD

VirtualProtectVlm proto _CType \
	      hProcess: HANDLE,
	     lpAddress: PVOID64,
	       ullSize: DWORDLONG,
	  flNewProtect: DWORD,
	lpflOldProtect: PDWORD
;DWORD
VirtualQueryVlm proto _CType \
	      hProcess: HANDLE,
	     lpAddress: PVOID64,
	      lpBuffer: PMEMORY_BASIC_INFORMATION_VLM,
	      dwLength: DWORD

MEMORYSTATUSVLM		STRUC
dwLength		DWORD ?
dwMemoryLoad		DWORD ?
ullTotalPhys		DWORDLONG ?
ullAvailPhys		DWORDLONG ?
ullTotalPageFile	DWORDLONG ?
ullAvailPageFile	DWORDLONG ?
ullTotalVirtual		DWORDLONG ?
ullAvailVirtual		DWORDLONG ?
ullAvailExtendedVirtual DWORDLONG ?
MEMORYSTATUSVLM		ENDS

LPMEMORYSTATUSVLM TYPEDEF PTR LPMEMORYSTATUSVLM

;VOID
GlobalMemoryStatusVlm proto _CType \
	      lpBuffer: LPMEMORYSTATUSVLM
;BOOL
ReadProcessMemoryVlm proto _CType \
	      hProcess: HANDLE,
	 lpBaseAddress: PVOID64,
	      lpBuffer: PVOID64,
		 nSize: DWORD,
   lpNumberOfBytesRead: LPDWORD

WriteProcessMemoryVlm proto _CType \
	      hProcess: HANDLE,
	 lpBaseAddress: PVOID64,
	      lpBuffer: PVOID64,
		 nSize: DWORD,
lpNumberOfBytesWritten: LPDWORD

ReadFileVlm proto _CType \
		 hFile: HANDLE,
	      lpBuffer: PVOID64,
  nNumberOfBytesToRead: DWORD,
	    lpReserved: LPDWORD,
	  lpOverlapped: LPOVERLAPPED

WriteFileVlm proto _CType \
		 hFile: HANDLE,
	      lpBuffer: PVOID64,
 nNumberOfBytesToWrite: DWORD,
	    lpReserved: LPDWORD,
	  lpOverlapped: LPOVERLAPPED
;HANDLE
CreateJobObjectA proto _CType \
       lpJobAttributes: LPSECURITY_ATTRIBUTES,
		lpName: LPSTR
CreateJobObjectW proto _CType \
       lpJobAttributes: LPSECURITY_ATTRIBUTES,
		lpName: LPWSTR
ifdef _UNICODE
CreateJobObject equ <CreateJobObjectW>
else
CreateJobObject equ <CreateJobObjectA>
endif

;HANDLE
OpenJobObjectA proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPSTR
OpenJobObjectW proto _CType \
       dwDesiredAccess: DWORD,
	bInheritHandle: BOOL,
		lpName: LPWSTR
ifdef _UNICODE
OpenJobObject equ <OpenJobObjectW>
else
OpenJobObject equ <OpenJobObjectA>
endif

;BOOL
AssignProcessToJobObject proto _CType \
		  hJob: HANDLE,
	      hProcess: HANDLE

TerminateJobObject proto _CType \
		  hJob: HANDLE,
	     uExitCode: UINT

QueryInformationJobObject proto _CType \
		  hJob: HANDLE,
JobObjectInformationClass: JOBOBJECTINFOCLASS,
lpJobObjectInformation: LPVOID,
cbJobObjectInformationLength: DWORD,
	lpReturnLength: LPDWORD

SetInformationJobObject proto _CType \
		  hJob: HANDLE,
JobObjectInformationClass: JOBOBJECTINFOCLASS,
lpJobObjectInformation: PVOID,
cbJobObjectInformationLength: DWORD

endif ; (_WIN32_WINNT >= 0x0500)
endif ; _WINBASE_

.list

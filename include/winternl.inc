ifndef _WINTERNL_
_WINTERNL_ equ <>
.pragma list(push, 0)

if (_WIN32_WINNT ge 0x0500)
include windef.inc

.pragma pack(push, 8)

;typedef __success(return >= 0) LONG NTSTATUS;

NTSTATUS	typedef sdword
PCSZ		typedef ptr sbyte

STRING		STRUC
Length		USHORT ?
MaximumLength	USHORT ?
Buffer		PCHAR ?
STRING		ENDS
PSTRING		typedef ptr STRING

ANSI_STRING	typedef STRING
PANSI_STRING	typedef PSTRING
PCANSI_STRING	typedef PSTRING

OEM_STRING	typedef STRING
POEM_STRING	typedef PSTRING
PCOEM_STRING	typedef ptr STRING

UNICODE_STRING	STRUC
Length		USHORT ?
MaximumLength	USHORT ?
Buffer		PWSTR ?
UNICODE_STRING	ENDS
PUNICODE_STRING typedef ptr UNICODE_STRING
PCUNICODE_STRING typedef ptr UNICODE_STRING


PEB_LDR_DATA		STRUC
Reserved1		BYTE 8 dup(?)
Reserved2		PVOID 3 dup(?)
InMemoryOrderModuleList LIST_ENTRY <>
PEB_LDR_DATA		ENDS
PPEB_LDR_DATA		typedef ptr PEB_LDR_DATA

LDR_DATA_TABLE_ENTRY	STRUC
Reserved1		PVOID 2 dup(?)
InMemoryOrderLinks	LIST_ENTRY <>
Reserved2		PVOID 2 dup(?)
DllBase			PVOID ?
Reserved3		PVOID 2 dup(?)
FullDllName		UNICODE_STRING <>
Reserved4		BYTE 8 dup(?)
Reserved5		PVOID 3 dup(?)
UNION ;DUMMYUNIONNAME
 CheckSum		ULONG ?
 Reserved6		PVOID ?
ENDS
TimeDateStamp		ULONG ?
LDR_DATA_TABLE_ENTRY	ENDS
PLDR_DATA_TABLE_ENTRY	typedef ptr LDR_DATA_TABLE_ENTRY

RTL_USER_PROCESS_PARAMETERS STRUC
Reserved1		BYTE 16 dup(?)
Reserved2		PVOID 10 dup(?)
ImagePathName		UNICODE_STRING <>
CommandLine		UNICODE_STRING <>
RTL_USER_PROCESS_PARAMETERS ENDS
PRTL_USER_PROCESS_PARAMETERS typedef ptr RTL_USER_PROCESS_PARAMETERS

CALLBACK(PPS_POST_PROCESS_INIT_ROUTINE)

PEB			STRUC
Reserved1		BYTE 2 dup(?)
BeingDebugged		BYTE ?
Reserved2		BYTE 1 dup(?)
Reserved3		PVOID 2 dup(?)
Ldr			PPEB_LDR_DATA ?
ProcessParameters	PRTL_USER_PROCESS_PARAMETERS ?
Reserved4		BYTE 104 dup(?)
Reserved5		PVOID 52 dup(?)
PostProcessInitRoutine	PPS_POST_PROCESS_INIT_ROUTINE ?
Reserved6		BYTE 128 dup(?)
Reserved7		PVOID 1 dup(?)
SessionId		ULONG ?
PEB			ENDS
PPEB			typedef ptr PEB

TEB			STRUC
Reserved1		BYTE 1952 dup(?)
Reserved2		PVOID 412 dup(?)
TlsSlots		PVOID 64 dup(?)
Reserved3		BYTE 8 dup(?)
Reserved4		PVOID 26 dup(?)
ReservedForOle		PVOID ?
Reserved5		PVOID 4 dup(?)
TlsExpansionSlots	PVOID ?
TEB			ENDS
PTEB			typedef ptr TEB

OBJECT_ATTRIBUTES	STRUC
Length			ULONG ?
RootDirectory		HANDLE ?
ObjectName		PUNICODE_STRING ?
Attributes		ULONG ?
SecurityDescriptor	PVOID ?
SecurityQualityOfService PVOID ?
OBJECT_ATTRIBUTES	ENDS
POBJECT_ATTRIBUTES	typedef ptr OBJECT_ATTRIBUTES

IO_STATUS_BLOCK		STRUC
UNION
 Status			NTSTATUS ?
 Pointer		PVOID ?
ENDS
Information		ULONG_PTR ?
IO_STATUS_BLOCK		ENDS
PIO_STATUS_BLOCK	typedef ptr IO_STATUS_BLOCK

CALLBACK(PIO_APC_ROUTINE, :PVOID, :PIO_STATUS_BLOCK, :ULONG)

PROCESS_BASIC_INFORMATION STRUC
Reserved1		PVOID ?
PebBaseAddress		PPEB ?
Reserved2		PVOID 2 dup(?)
UniqueProcessId		ULONG_PTR ?
Reserved3		PVOID ?
PROCESS_BASIC_INFORMATION ENDS
PPROCESS_BASIC_INFORMATION typedef ptr PROCESS_BASIC_INFORMATION

SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION STRUC
IdleTime		LARGE_INTEGER <>
KernelTime		LARGE_INTEGER <>
UserTime		LARGE_INTEGER <>
Reserved1		LARGE_INTEGER 2 dup(<>)
Reserved2		ULONG ?
SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION ENDS
PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION typedef ptr SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION

SYSTEM_PROCESS_INFORMATION STRUC
NextEntryOffset		ULONG ?
Reserved1		BYTE 52 dup(?)
Reserved2		PVOID 3 dup(?)
UniqueProcessId		HANDLE ?
Reserved3		PVOID ?
HandleCount		ULONG ?
Reserved4		BYTE 4 dup(?)
Reserved5		PVOID 11 dup(?)
PeakPagefileUsage	SIZE_T ?
PrivatePageCount	SIZE_T ?
Reserved6		LARGE_INTEGER 6 dup(<>)
SYSTEM_PROCESS_INFORMATION ENDS
PSYSTEM_PROCESS_INFORMATION typedef ptr SYSTEM_PROCESS_INFORMATION

SYSTEM_REGISTRY_QUOTA_INFORMATION STRUC
RegistryQuotaAllowed	ULONG ?
RegistryQuotaUsed	ULONG ?
Reserved1		PVOID ?
SYSTEM_REGISTRY_QUOTA_INFORMATION ENDS
PSYSTEM_REGISTRY_QUOTA_INFORMATION typedef ptr SYSTEM_REGISTRY_QUOTA_INFORMATION

SYSTEM_BASIC_INFORMATION STRUC
Reserved1		BYTE 24 dup(?)
Reserved2		PVOID 4 dup(?)
NumberOfProcessors	sbyte ?
SYSTEM_BASIC_INFORMATION ENDS
PSYSTEM_BASIC_INFORMATION typedef ptr SYSTEM_BASIC_INFORMATION

SYSTEM_TIMEOFDAY_INFORMATION STRUC
Reserved1		BYTE 48 dup(?)
SYSTEM_TIMEOFDAY_INFORMATION ENDS
PSYSTEM_TIMEOFDAY_INFORMATION typedef ptr SYSTEM_TIMEOFDAY_INFORMATION

SYSTEM_PERFORMANCE_INFORMATION STRUC
Reserved1		BYTE 312 dup(?)
SYSTEM_PERFORMANCE_INFORMATION ENDS
PSYSTEM_PERFORMANCE_INFORMATION typedef ptr SYSTEM_PERFORMANCE_INFORMATION

SYSTEM_EXCEPTION_INFORMATION STRUC
Reserved1		BYTE 16 dup(?)
SYSTEM_EXCEPTION_INFORMATION ENDS
PSYSTEM_EXCEPTION_INFORMATION typedef ptr SYSTEM_EXCEPTION_INFORMATION

SYSTEM_LOOKASIDE_INFORMATION STRUC
Reserved1		BYTE 32 dup(?)
SYSTEM_LOOKASIDE_INFORMATION ENDS
PSYSTEM_LOOKASIDE_INFORMATION typedef ptr SYSTEM_LOOKASIDE_INFORMATION

SYSTEM_INTERRUPT_INFORMATION STRUC
Reserved1		BYTE 24 dup(?)
SYSTEM_INTERRUPT_INFORMATION ENDS
PSYSTEM_INTERRUPT_INFORMATION typedef ptr SYSTEM_INTERRUPT_INFORMATION

FILE_INFORMATION_CLASS		typedef sdword
FileDirectoryInformation	equ 1

PROCESSINFOCLASS		typedef sdword
ProcessBasicInformation		equ 0
ProcessWow64Information		equ 26

THREADINFOCLASS			typedef sdword
ThreadIsIoPending		equ 16

SYSTEM_INFORMATION_CLASS	typedef sdword
SystemBasicInformation		equ 0
SystemPerformanceInformation	equ 2
SystemTimeOfDayInformation	equ 3
SystemProcessInformation	equ 5
SystemProcessorPerformanceInformation equ 8
SystemInterruptInformation	equ 23
SystemExceptionInformation	equ 33
SystemRegistryQuotaInformation	equ 37
SystemLookasideInformation	equ 45


OBJECT_INFORMATION_CLASS	typedef sdword
ObjectBasicInformation		equ 0
ObjectTypeInformation		equ 2


PUBLIC_OBJECT_BASIC_INFORMATION STRUC
Attributes		ULONG ?
GrantedAccess		ACCESS_MASK ?
HandleCount		ULONG ?
PointerCount		ULONG ?
Reserved		ULONG 10 dup(?)
PUBLIC_OBJECT_BASIC_INFORMATION ENDS
PPUBLIC_OBJECT_BASIC_INFORMATION typedef ptr PUBLIC_OBJECT_BASIC_INFORMATION

PUBLIC_OBJECT_TYPE_INFORMATION	STRUC
TypeName		UNICODE_STRING <>
Reserved		ULONG 22 dup(?)
PUBLIC_OBJECT_TYPE_INFORMATION	ENDS
PPUBLIC_OBJECT_TYPE_INFORMATION typedef ptr PUBLIC_OBJECT_TYPE_INFORMATION

if (_WIN32_WINNT ge 0x0501)
;INTERNAL_TS_ACTIVE_CONSOLE_ID equ <dword ptr [0x7ffe02d8]>
endif


RtlMoveMemory equ <memmove>
RtlFillMemory macro Destination, Length, Fill
	exitm<memset(Destination, Fill, Length)>
	endm
RtlZeroMemory macro Destination, Length
	exitm<memset(Destination, 0, Length)>
	endm

;NTSTATUS NTAPI
NtClose proto WINAPI Handle:HANDLE

;NTSTATUS NTAPI
NtCreateFile proto WINAPI \
	    FileHandle: PHANDLE,
	 DesiredAccess: ACCESS_MASK,
      ObjectAttributes: POBJECT_ATTRIBUTES,
	 IoStatusBlock: PIO_STATUS_BLOCK,
	AllocationSize: PLARGE_INTEGER,
	FileAttributes: ULONG,
	   ShareAccess: ULONG,
     CreateDisposition: ULONG,
	 CreateOptions: ULONG,
	      EaBuffer: PVOID,
	      EaLength: ULONG

;NTSTATUS NTAPI
NtOpenFile proto WINAPI \
	    FileHandle: PHANDLE,
	 DesiredAccess: ACCESS_MASK,
      ObjectAttributes: POBJECT_ATTRIBUTES,
	 IoStatusBlock: PIO_STATUS_BLOCK,
	   ShareAccess: ULONG,
	   OpenOptions: ULONG

;NTSTATUS NTAPI
NtDeviceIoControlFile proto WINAPI \
	    FileHandle: HANDLE,
		 Event: HANDLE,
	    ApcRoutine: PIO_APC_ROUTINE,
	    ApcContext: PVOID,
	 IoStatusBlock: PIO_STATUS_BLOCK,
	 IoControlCode: ULONG,
	   InputBuffer: PVOID,
     InputBufferLength: ULONG,
	  OutputBuffer: PVOID,
    OutputBufferLength: ULONG

;NTSTATUS NTAPI
NtWaitForSingleObject proto WINAPI \
		Handle: HANDLE,
	     Alertable: BOOLEAN,
	       Timeout: PLARGE_INTEGER

;BOOLEAN NTAPI
RtlIsNameLegalDOS8Dot3 proto WINAPI \
		 _Name: PUNICODE_STRING,
	       OemName: POEM_STRING,
    NameContainsSpaces: PBOOLEAN

;ULONG NTAPI
RtlNtStatusToDosError proto WINAPI Status:NTSTATUS

;__kernel_entry NTSTATUS NTAPI
NtQueryInformationProcess proto WINAPI \
	 ProcessHandle: HANDLE,
ProcessInformationClass: PROCESSINFOCLASS,
    ProcessInformation: PVOID,
ProcessInformationLength: ULONG,
	  ReturnLength: PULONG

;__kernel_entry NTSTATUS NTAPI
NtQueryInformationThread proto WINAPI \
	  ThreadHandle: HANDLE,
ThreadInformationClass: THREADINFOCLASS,
     ThreadInformation: PVOID,
ThreadInformationLength: ULONG,
	  ReturnLength: PULONG


;__kernel_entry NTSYSCALLAPI NTSTATUS NTAPI
NtQueryObject proto WINAPI \
		Handle: HANDLE,
ObjectInformationClass: OBJECT_INFORMATION_CLASS,
     ObjectInformation: PVOID,
ObjectInformationLength: ULONG,
	  ReturnLength: PULONG


;__kernel_entry NTSTATUS NTAPI
NtQuerySystemInformation proto WINAPI \
SystemInformationClass: SYSTEM_INFORMATION_CLASS,
     SystemInformation: PVOID,
SystemInformationLength: ULONG,
	  ReturnLength: PULONG

;__kernel_entry NTSTATUS NTAPI
NtQuerySystemTime proto WINAPI SystemTime:PLARGE_INTEGER

;NTSTATUS NTAPI
RtlLocalTimeToSystemTime proto WINAPI \
	     LocalTime: PLARGE_INTEGER,
	    SystemTime: PLARGE_INTEGER

;BOOLEAN NTAPI
RtlTimeToSecondsSince1970 proto WINAPI \
		  Time: PLARGE_INTEGER,
	ElapsedSeconds: PULONG

;VOID NTAPI
RtlFreeAnsiString proto WINAPI AnsiString:PANSI_STRING

;VOID NTAPI
RtlFreeUnicodeString proto WINAPI UnicodeString:PUNICODE_STRING

;VOID NTAPI
RtlFreeOemString proto WINAPI OemString:POEM_STRING

;VOID NTAPI
RtlInitString proto WINAPI DestinationString:PSTRING, SourceString:PCSZ

;VOID NTAPI
RtlInitAnsiString proto WINAPI DestinationString:PANSI_STRING, SourceString:PCSZ

;VOID NTAPI
RtlInitUnicodeString proto WINAPI DestinationString:PUNICODE_STRING, SourceString:PCWSTR

;NTSTATUS NTAPI
RtlAnsiStringToUnicodeString proto WINAPI \
     DestinationString: PUNICODE_STRING,
	  SourceString: PCANSI_STRING,
AllocateDestinationString: BOOLEAN

;NTSTATUS NTAPI
RtlUnicodeStringToAnsiString proto WINAPI \
     DestinationString: PANSI_STRING,
	  SourceString: PCUNICODE_STRING,
AllocateDestinationString: BOOLEAN

;NTSTATUS NTAPI
RtlUnicodeStringToOemString proto WINAPI \
     DestinationString: POEM_STRING,
	  SourceString: PCUNICODE_STRING,
AllocateDestinationString: BOOLEAN

;NTSTATUS NTAPI
RtlUnicodeToMultiByteSize proto WINAPI \
BytesInMultiByteString: PULONG,
	 UnicodeString: PWCH,
  BytesInUnicodeString: ULONG

;NTSTATUS NTAPI
RtlCharToInteger proto WINAPI String:PCSZ, Base:ULONG, Value:PULONG

;NTSTATUS
;NTAPI
RtlConvertSidToUnicodeString proto WINAPI \
	 UnicodeString: PUNICODE_STRING,
		   Sid: PSID,
AllocateDestinationString: BOOLEAN

;ULONG
;NTAPI
RtlUniform proto WINAPI Seed:PULONG

LOGONID_CURRENT		equ -1
SERVERNAME_CURRENT	equ 0

WINSTATIONINFOCLASS	typedef SDWORD
WinStationInformation	equ 8


WINSTATIONINFORMATIONW	STRUC
Reserved2		BYTE 70 dup(?)
LogonId			ULONG ?
Reserved3		BYTE 1140 dup(?)
WINSTATIONINFORMATIONW	ENDS
PWINSTATIONINFORMATIONW typedef ptr WINSTATIONINFORMATIONW

CALLBACK(PWINSTATIONQUERYINFORMATIONW, :HANDLE, :ULONG, :WINSTATIONINFOCLASS, :PVOID, :ULONG, :PULONG)


ifndef NT_SUCCESS
NT_SUCCESS macro Status
	shr eax,30
	exitm<eax == 0>
	endm
endif


ifndef NT_INFORMATION
NT_INFORMATION macro Status
	shr eax,30
	exitm<eax == 1>
	endm
endif


ifndef NT_WARNING
NT_WARNING macro Status
	shr eax,30
	exitm<eax == 2>
	endm
endif


ifndef NT_ERROR
NT_ERROR macro Status
	shr eax,30
	exitm<eax == 3>
	endm
endif


ifndef InitializeObjectAttributes
InitializeObjectAttributes macro p, n, a, r, s
    mov p.OBJECT_ATTRIBUTES.Length,sizeof(OBJECT_ATTRIBUTES)
    mov p.OBJECT_ATTRIBUTES.RootDirectory,r
    mov p.OBJECT_ATTRIBUTES.Attributes,a
    mov p.OBJECT_ATTRIBUTES.ObjectName,n
    mov p.OBJECT_ATTRIBUTES.SecurityDescriptor,s
    mov p.OBJECT_ATTRIBUTES.SecurityQualityOfService,NULL
    endm
endif


OBJ_INHERIT		equ 0x00000002
OBJ_PERMANENT		equ 0x00000010
OBJ_EXCLUSIVE		equ 0x00000020
OBJ_CASE_INSENSITIVE	equ 0x00000040
OBJ_OPENIF		equ 0x00000080
OBJ_OPENLINK		equ 0x00000100
OBJ_KERNEL_HANDLE	equ 0x00000200
OBJ_FORCE_ACCESS_CHECK	equ 0x00000400
OBJ_VALID_ATTRIBUTES	equ 0x000007F2


FILE_SUPERSEDE			equ 0x00000000
FILE_OPEN			equ 0x00000001
FILE_CREATE			equ 0x00000002
FILE_OPEN_IF			equ 0x00000003
FILE_OVERWRITE			equ 0x00000004
FILE_OVERWRITE_IF		equ 0x00000005
FILE_MAXIMUM_DISPOSITION	equ 0x00000005


FILE_DIRECTORY_FILE		equ 0x00000001
FILE_WRITE_THROUGH		equ 0x00000002
FILE_SEQUENTIAL_ONLY		equ 0x00000004
FILE_NO_INTERMEDIATE_BUFFERING	equ 0x00000008

FILE_SYNCHRONOUS_IO_ALERT	equ 0x00000010
FILE_SYNCHRONOUS_IO_NONALERT	equ 0x00000020
FILE_NON_DIRECTORY_FILE		equ 0x00000040
FILE_CREATE_TREE_CONNECTION	equ 0x00000080

FILE_COMPLETE_IF_OPLOCKED	equ 0x00000100
FILE_NO_EA_KNOWLEDGE		equ 0x00000200
FILE_OPEN_REMOTE_INSTANCE	equ 0x00000400
FILE_RANDOM_ACCESS		equ 0x00000800

FILE_DELETE_ON_CLOSE		equ 0x00001000
FILE_OPEN_BY_FILE_ID		equ 0x00002000
FILE_OPEN_FOR_BACKUP_INTENT	equ 0x00004000
FILE_NO_COMPRESSION		equ 0x00008000

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)
FILE_OPEN_REQUIRING_OPLOCK		equ 0x00010000
endif

FILE_RESERVE_OPFILTER			equ 0x00100000
FILE_OPEN_REPARSE_POINT			equ 0x00200000
FILE_OPEN_NO_RECALL			equ 0x00400000
FILE_OPEN_FOR_FREE_SPACE_QUERY		equ 0x00800000

FILE_VALID_OPTION_FLAGS			equ 0x00ffffff
FILE_VALID_PIPE_OPTION_FLAGS		equ 0x00000032
FILE_VALID_MAILSLOT_OPTION_FLAGS	equ 0x00000032
FILE_VALID_SET_FLAGS			equ 0x00000036


FILE_SUPERSEDED		equ 0x00000000
FILE_OPENED		equ 0x00000001
FILE_CREATED		equ 0x00000002
FILE_OVERWRITTEN	equ 0x00000003
FILE_EXISTS		equ 0x00000004
FILE_DOES_NOT_EXIST	equ 0x00000005

.pragma pack(pop)

endif ; (_WIN32_WINNT >= 0x0500)

.pragma list(pop)
endif

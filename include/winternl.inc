ifndef _WINTERNL_
define _WINTERNL_
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

if (_WIN32_WINNT ge 0x0500)

include windef.inc

NTSTATUS                typedef LONG
PCSZ                    typedef ptr sbyte

STRING                  struct
Length                  USHORT ?
MaximumLength           USHORT ?
Buffer                  PCHAR ?
STRING                  ends
PSTRING                 typedef ptr STRING

ANSI_STRING             typedef STRING
PANSI_STRING            typedef PSTRING
PCANSI_STRING           typedef PSTRING

OEM_STRING              typedef STRING
POEM_STRING             typedef PSTRING
PCOEM_STRING            typedef ptr STRING

UNICODE_STRING          struct
Length                  USHORT ?
MaximumLength           USHORT ?
Buffer                  PWSTR ?
UNICODE_STRING          ends
PUNICODE_STRING         typedef ptr UNICODE_STRING
PCUNICODE_STRING        typedef ptr UNICODE_STRING

KPRIORITY               typedef LONG

CLIENT_ID               struct
UniqueProcess           HANDLE ?
UniqueThread            HANDLE ?
CLIENT_ID               ends

PEB_LDR_DATA            struct
Reserved1               BYTE 8 dup(?)
Reserved2               PVOID 3 dup(?)
InMemoryOrderModuleList LIST_ENTRY <>
PEB_LDR_DATA            ends
PPEB_LDR_DATA           typedef ptr PEB_LDR_DATA

LDR_DATA_TABLE_ENTRY    struct
Reserved1               PVOID 2 dup(?)
InMemoryOrderLinks      LIST_ENTRY <>
Reserved2               PVOID 2 dup(?)
DllBase                 PVOID ?
Reserved3               PVOID 2 dup(?)
FullDllName             UNICODE_STRING <>
Reserved4               BYTE 8 dup(?)
Reserved5               PVOID 3 dup(?)
union
 CheckSum               ULONG ?
 Reserved6              PVOID ?
ends
TimeDateStamp           ULONG ?
LDR_DATA_TABLE_ENTRY    ends
PLDR_DATA_TABLE_ENTRY   typedef ptr LDR_DATA_TABLE_ENTRY

RTL_USER_PROCESS_PARAMETERS struct
Reserved1               BYTE 16 dup(?)
Reserved2               PVOID 10 dup(?)
ImagePathName           UNICODE_STRING <>
CommandLine             UNICODE_STRING <>
RTL_USER_PROCESS_PARAMETERS ends
PRTL_USER_PROCESS_PARAMETERS typedef ptr RTL_USER_PROCESS_PARAMETERS

CALLBACK(PPS_POST_PROCESS_INIT_ROUTINE,)

PEB                     struct
Reserved1               BYTE 2 dup(?)
BeingDebugged           BYTE ?
Reserved2               BYTE 1 dup(?)
Reserved3               PVOID 2 dup(?)
_Ldr                    PPEB_LDR_DATA ?
ProcessParameters       PRTL_USER_PROCESS_PARAMETERS ?
Reserved4               PVOID 3 dup(?)
AtlThunkSListPtr        PVOID ?
Reserved5               PVOID ?
Reserved6               ULONG ?
Reserved7               PVOID ?
Reserved8               ULONG ?
AtlThunkSListPtr32      ULONG ?
Reserved9               PVOID 45 dup(?)
Reserved10              BYTE 96 dup(?)
PostProcessInitRoutine  PPS_POST_PROCESS_INIT_ROUTINE ?
Reserved11              BYTE 128 dup(?)
Reserved12              PVOID 1 dup(?)
SessionId               ULONG ?
PEB                     ends
PPEB                    typedef ptr PEB

TEB                     struct
Reserved1               PVOID 12 dup(?)
ProcessEnvironmentBlock PPEB ?
Reserved2               PVOID 399 dup(?)
Reserved3               BYTE 1952 dup(?)
TlsSlots                PVOID 64 dup(?)
Reserved4               BYTE 8 dup(?)
Reserved5               PVOID 26 dup(?)
ReservedForOle          PVOID ?
Reserved6               PVOID 4 dup(?)
TlsExpansionSlots       PVOID ?
TEB                     ends
PTEB                    typedef ptr TEB

OBJECT_ATTRIBUTES       struct
Length                  ULONG ?
RootDirectory           HANDLE ?
ObjectName              PUNICODE_STRING ?
Attributes              ULONG ?
SecurityDescriptor      PVOID ?
SecurityQualityOfService PVOID ?
OBJECT_ATTRIBUTES       ends
POBJECT_ATTRIBUTES      typedef ptr OBJECT_ATTRIBUTES

IO_STATUS_BLOCK         struct
union
 Status                 NTSTATUS ?
 Pointer                PVOID ?
ends
Information             ULONG_PTR ?
IO_STATUS_BLOCK         ends
PIO_STATUS_BLOCK        typedef ptr _IO_STATUS_BLOCK

CALLBACK(PIO_APC_ROUTINE, :PVOID, :PIO_STATUS_BLOCK, :ULONG)

PROCESS_BASIC_INFORMATION struct
Reserved1               PVOID ?
PebBaseAddress          PPEB ?
Reserved2               PVOID 2 dup(?)
UniqueProcessId         ULONG_PTR ?
Reserved3               PVOID ?
PROCESS_BASIC_INFORMATION ends
PPROCESS_BASIC_INFORMATION typedef ptr PROCESS_BASIC_INFORMATION

SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION struct
IdleTime                LARGE_INTEGER <>
KernelTime              LARGE_INTEGER <>
UserTime                LARGE_INTEGER <>
Reserved1               LARGE_INTEGER 2 dup(<>)
Reserved2               ULONG ?
SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION ends
PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION typedef ptr SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION

SYSTEM_PROCESS_INFORMATION struct
NextEntryOffset         ULONG ?
NumberOfThreads         ULONG ?
Reserved1               BYTE 48 dup(?)
ImageName               UNICODE_STRING <>
BasePriority            KPRIORITY ?
UniqueProcessId         HANDLE ?
Reserved2               PVOID ?
HandleCount             ULONG ?
SessionId               ULONG ?
Reserved3               PVOID ?
PeakVirtualSize         SIZE_T ?
VirtualSize             SIZE_T ?
Reserved4               ULONG ?
PeakWorkingSetSize      SIZE_T ?
WorkingSetSize          SIZE_T ?
Reserved5               PVOID ?
QuotaPagedPoolUsage     SIZE_T ?
Reserved6               PVOID ?
QuotaNonPagedPoolUsage  SIZE_T ?
PagefileUsage           SIZE_T ?
PeakPagefileUsage       SIZE_T ?
PrivatePageCount        SIZE_T ?
Reserved7               LARGE_INTEGER 6 dup(<>)
SYSTEM_PROCESS_INFORMATION ends
PSYSTEM_PROCESS_INFORMATION typedef ptr SYSTEM_PROCESS_INFORMATION

SYSTEM_THREAD_INFORMATION struct
Reserved1               LARGE_INTEGER 3 dup(<>)
Reserved2               ULONG ?
StartAddress            PVOID ?
ClientId                CLIENT_ID <>
Priority                KPRIORITY ?
BasePriority            LONG ?
Reserved3               ULONG ?
ThreadState             ULONG ?
WaitReason              ULONG ?
SYSTEM_THREAD_INFORMATION ends
PSYSTEM_THREAD_INFORMATION typedef ptr SYSTEM_THREAD_INFORMATION

SYSTEM_REGISTRY_QUOTA_INFORMATION struct
RegistryQuotaAllowed    ULONG ?
RegistryQuotaUsed       ULONG ?
Reserved1               PVOID ?
SYSTEM_REGISTRY_QUOTA_INFORMATION ends
PSYSTEM_REGISTRY_QUOTA_INFORMATION typedef ptr SYSTEM_REGISTRY_QUOTA_INFORMATION

SYSTEM_BASIC_INFORMATION struct
Reserved1               BYTE 24 dup(?)
Reserved2               PVOID 4 dup(?)
NumberOfProcessors      CCHAR ?
SYSTEM_BASIC_INFORMATION ends
PSYSTEM_BASIC_INFORMATION typedef ptr SYSTEM_BASIC_INFORMATION

SYSTEM_TIMEOFDAY_INFORMATION struct
Reserved1               BYTE 48 dup(?)
SYSTEM_TIMEOFDAY_INFORMATION ends
PSYSTEM_TIMEOFDAY_INFORMATION typedef ptr SYSTEM_TIMEOFDAY_INFORMATION

SYSTEM_PERFORMANCE_INFORMATION struct
Reserved1               BYTE 312 dup(?)
SYSTEM_PERFORMANCE_INFORMATION ends
PSYSTEM_PERFORMANCE_INFORMATION typedef ptr SYSTEM_PERFORMANCE_INFORMATION

SYSTEM_EXCEPTION_INFORMATION struct
Reserved1               BYTE 16 dup(?)
SYSTEM_EXCEPTION_INFORMATION ends
PSYSTEM_EXCEPTION_INFORMATION typedef ptr SYSTEM_EXCEPTION_INFORMATION

SYSTEM_LOOKASIDE_INFORMATION struct
Reserved1               BYTE 32 dup(?)
SYSTEM_LOOKASIDE_INFORMATION ends
PSYSTEM_LOOKASIDE_INFORMATION typedef ptr SYSTEM_LOOKASIDE_INFORMATION

SYSTEM_INTERRUPT_INFORMATION struct
Reserved1               BYTE 24 dup(?)
SYSTEM_INTERRUPT_INFORMATION ends
PSYSTEM_INTERRUPT_INFORMATION typedef ptr SYSTEM_INTERRUPT_INFORMATION

SYSTEM_POLICY_INFORMATION struct
Reserved1               PVOID 2 dup(?)
Reserved2               ULONG 3 dup(?)
SYSTEM_POLICY_INFORMATION ends
PSYSTEM_POLICY_INFORMATION typedef ptr SYSTEM_POLICY_INFORMATION

.enum FILE_INFORMATION_CLASS {
    FileDirectoryInformation = 1
    }

.enum PROCESSINFOCLASS {
    ProcessBasicInformation = 0,
    ProcessDebugPort = 7,
    ProcessWow64Information = 26,
    ProcessImageFileName = 27,
    ProcessBreakOnTermination = 29
    }

.enum THREADINFOCLASS {
    ThreadIsIoPending = 16
    }

define CODEINTEGRITY_OPTION_ENABLED                        0x01
define CODEINTEGRITY_OPTION_TESTSIGN                       0x02
define CODEINTEGRITY_OPTION_UMCI_ENABLED                   0x04
define CODEINTEGRITY_OPTION_UMCI_AUDITMODE_ENABLED         0x08
define CODEINTEGRITY_OPTION_UMCI_EXCLUSIONPATHS_ENABLED    0x10
define CODEINTEGRITY_OPTION_TEST_BUILD                     0x20
define CODEINTEGRITY_OPTION_PREPRODUCTION_BUILD            0x40
define CODEINTEGRITY_OPTION_DEBUGMODE_ENABLED              0x80
define CODEINTEGRITY_OPTION_FLIGHT_BUILD                   0x100
define CODEINTEGRITY_OPTION_FLIGHTING_ENABLED              0x200
define CODEINTEGRITY_OPTION_HVCI_KMCI_ENABLED              0x400
define CODEINTEGRITY_OPTION_HVCI_KMCI_AUDITMODE_ENABLED    0x800
define CODEINTEGRITY_OPTION_HVCI_KMCI_STRICTMODE_ENABLED   0x1000
define CODEINTEGRITY_OPTION_HVCI_IUM_ENABLED               0x2000

SYSTEM_CODEINTEGRITY_INFORMATION struct
Length                  ULONG ?
CodeIntegrityOptions    ULONG ?
SYSTEM_CODEINTEGRITY_INFORMATION ends
PSYSTEM_CODEINTEGRITY_INFORMATION typedef ptr SYSTEM_CODEINTEGRITY_INFORMATION

.enum SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation = 0,
    SystemPerformanceInformation = 2,
    SystemTimeOfDayInformation = 3,
    SystemProcessInformation = 5,
    SystemProcessorPerformanceInformation = 8,
    SystemInterruptInformation = 23,
    SystemExceptionInformation = 33,
    SystemRegistryQuotaInformation = 37,
    SystemLookasideInformation = 45,
    SystemCodeIntegrityInformation = 103,
    SystemPolicyInformation = 134,
    }

.enum OBJECT_INFORMATION_CLASS {
    ObjectBasicInformation = 0,
    ObjectTypeInformation = 2
    }

PUBLIC_OBJECT_BASIC_INFORMATION struct
Attributes              ULONG ?
GrantedAccess           ACCESS_MASK ?
HandleCount             ULONG ?
PointerCount            ULONG ?
Reserved                ULONG 10 dup(?)
PUBLIC_OBJECT_BASIC_INFORMATION ends
PPUBLIC_OBJECT_BASIC_INFORMATION typedef ptr PUBLIC_OBJECT_BASIC_INFORMATION

PUBLIC_OBJECT_TYPE_INFORMATION struct
TypeName                UNICODE_STRING <>
Reserved                ULONG 22 dup(?)
PUBLIC_OBJECT_TYPE_INFORMATION ends
PPUBLIC_OBJECT_TYPE_INFORMATION typedef ptr PUBLIC_OBJECT_TYPE_INFORMATION

if (_WIN32_WINNT ge 0x0501)
;INTERNAL_TS_ACTIVE_CONSOLE_ID equ <dword ptr [0x7ffe02d8]>
endif

RtlMoveMemory equ <memmove>
RtlFillMemory macro Destination,Length,Fill
  exitm<memset((Destination),(Fill),(Length))>
  endm
RtlZeroMemory macro Destination,Length
  exitm<memset((Destination),0,(Length))>
  endm

NtClose proto WINAPI :HANDLE
NtCreateFile proto WINAPI :PHANDLE, :ACCESS_MASK, :POBJECT_ATTRIBUTES, :PIO_STATUS_BLOCK, :PLARGE_INTEGER, :ULONG, :ULONG, :ULONG, :ULONG, :ptr, :ULONG
NtOpenFile proto WINAPI :PHANDLE, :ACCESS_MASK, :POBJECT_ATTRIBUTES, :PIO_STATUS_BLOCK, :ULONG, :ULONG
NtRenameKey proto WINAPI :HANDLE, :PUNICODE_STRING
NtNotifyChangeMultipleKeys proto WINAPI :HANDLE, :ULONG, :OBJECT_ATTRIBUTES, :HANDLE, :PIO_APC_ROUTINE, :PVOID, :PIO_STATUS_BLOCK, :ULONG, :BOOLEAN, :PVOID, :ULONG, :BOOLEAN

KEY_VALUE_ENTRY         struct
ValueName               PUNICODE_STRING ?
DataLength              ULONG ?
DataOffset              ULONG ?
Type                    ULONG ?
KEY_VALUE_ENTRY         ends
PKEY_VALUE_ENTRY        typedef ptr KEY_VALUE_ENTRY

NtQueryMultipleValueKey proto WINAPI :HANDLE, :PKEY_VALUE_ENTRY, :ULONG, :PVOID, :PULONG, :PULONG

.enum KEY_SET_INFORMATION_CLASS {
    KeyWriteTimeInformation,
    KeyWow64FlagsInformation,
    KeyControlFlagsInformation,
    KeySetVirtualizationInformation,
    KeySetDebugInformation,
    KeySetHandleTagsInformation,
    MaxKeySetInfoClass
    }

NtSetInformationKey proto WINAPI :HANDLE, :KEY_SET_INFORMATION_CLASS, :PVOID, :ULONG
NtDeviceIoControlFile proto WINAPI :HANDLE, :HANDLE, :PIO_APC_ROUTINE, :ptr, :PIO_STATUS_BLOCK, :ULONG, :ptr, :ULONG, :ptr, :ULONG
NtWaitForSingleObject proto WINAPI :HANDLE, :BOOLEAN, :PLARGE_INTEGER
RtlIsNameLegalDOS8Dot3 proto WINAPI :PUNICODE_STRING, :POEM_STRING, :PBOOLEAN
RtlNtStatusToDosError proto WINAPI :NTSTATUS
NtQueryInformationProcess proto WINAPI :HANDLE, :PROCESSINFOCLASS, :PVOID, :ULONG, :PULONG
NtQueryInformationThread proto WINAPI :HANDLE, :THREADINFOCLASS, :PVOID, :ULONG, :PULONG
NtQueryObject proto WINAPI :HANDLE, :OBJECT_INFORMATION_CLASS, :PVOID, :ULONG, :PULONG
NtQuerySystemInformation proto WINAPI :SYSTEM_INFORMATION_CLASS, :PVOID, :ULONG, :PULONG
NtQuerySystemTime proto WINAPI :PLARGE_INTEGER
RtlLocalTimeToSystemTime proto WINAPI :PLARGE_INTEGER, :PLARGE_INTEGER
RtlTimeToSecondsSince1970 proto WINAPI :PLARGE_INTEGER, :PULONG
RtlFreeAnsiString proto WINAPI :PANSI_STRING
RtlFreeUnicodeString proto WINAPI :PUNICODE_STRING
RtlFreeOemString proto WINAPI :POEM_STRING
RtlInitString proto WINAPI :PSTRING, :PCSZ
RtlInitStringEx proto WINAPI :PSTRING, :PCSZ
RtlInitAnsiString proto WINAPI :PANSI_STRING, :PCSZ
RtlInitAnsiStringEx proto WINAPI :PANSI_STRING, :PCSZ
RtlInitUnicodeString proto WINAPI :PUNICODE_STRING, :PCWSTR
RtlAnsiStringToUnicodeString proto WINAPI :PUNICODE_STRING, :PCANSI_STRING, :BOOLEAN
RtlUnicodeStringToAnsiString proto WINAPI :PANSI_STRING, :PCUNICODE_STRING, :BOOLEAN
RtlUnicodeStringToOemString proto WINAPI :POEM_STRING, :PCUNICODE_STRING, :BOOLEAN
RtlUnicodeToMultiByteSize proto WINAPI :PULONG, :PWCH, :ULONG
RtlCharToInteger proto WINAPI :PCSZ, :ULONG, :PULONG
RtlConvertSidToUnicodeString proto WINAPI :PUNICODE_STRING, :PSID, :BOOLEAN
RtlUniform proto WINAPI :PULONG

define LOGONID_CURRENT     (-1)
define SERVERNAME_CURRENT  (NULL)

.enum WINSTATIONINFOCLASS {
    WinStationInformation = 8
    }

WINSTATIONINFORMATIONW  struct
Reserved2               BYTE 70 dup(?)
LogonId                 ULONG ?
Reserved3               BYTE 1140 dup(?)
WINSTATIONINFORMATIONW  ends
PWINSTATIONINFORMATIONW typedef ptr _WINSTATIONINFORMATIONW

CALLBACK(PWINSTATIONQUERYINFORMATIONW, :HANDLE, :ULONG, :WINSTATIONINFOCLASS, :PVOID, :ULONG, :PULONG)

ifndef NT_SUCCESS
NT_SUCCESS macro Status
  exitm<((Status) !>= 0)>
  endm
endif

ifndef NT_INFORMATION
NT_INFORMATION proto watcall Status:NTSTATUS {
    shr     eax,30
    retm    <(eax == 1)>
    }
endif

ifndef NT_WARNING
NT_WARNING proto watcall Status:NTSTATUS {
    shr     eax,30
    retm    <(eax == 2)>
    }
endif

ifndef NT_ERROR
NT_ERROR proto watcall Status:NTSTATUS {
    shr     eax,30
    retm    <(eax == 3)>
    }
endif

ifndef InitializeObjectAttributes
InitializeObjectAttributes macro  p, n, a, r, s
    mov p.OBJECT_ATTRIBUTES.Length,OBJECT_ATTRIBUTES
    mov p.OBJECT_ATTRIBUTES.RootDirectory,r
    mov p.OBJECT_ATTRIBUTES.Attributes,a
    mov p.OBJECT_ATTRIBUTES.ObjectName,n
    mov p.OBJECT_ATTRIBUTES.SecurityDescriptor,s
    mov p.OBJECT_ATTRIBUTES.SecurityQualityOfService,NULL
    exitm<>
    endm
endif

define OBJ_INHERIT                         0x00000002
define OBJ_PERMANENT                       0x00000010
define OBJ_EXCLUSIVE                       0x00000020
define OBJ_CASE_INSENSITIVE                0x00000040
define OBJ_OPENIF                          0x00000080
define OBJ_OPENLINK                        0x00000100
define OBJ_KERNEL_HANDLE                   0x00000200
define OBJ_FORCE_ACCESS_CHECK              0x00000400
define OBJ_IGNORE_IMPERSONATED_DEVICEMAP   0x00000800
define OBJ_DONT_REPARSE                    0x00001000
define OBJ_VALID_ATTRIBUTES                0x00001FF2

define FILE_SUPERSEDE                  0x00000000
define FILE_OPEN                       0x00000001
define FILE_CREATE                     0x00000002
define FILE_OPEN_IF                    0x00000003
define FILE_OVERWRITE                  0x00000004
define FILE_OVERWRITE_IF               0x00000005
define FILE_MAXIMUM_DISPOSITION        0x00000005

define FILE_DIRECTORY_FILE                     0x00000001
define FILE_WRITE_THROUGH                      0x00000002
define FILE_SEQUENTIAL_ONLY                    0x00000004
define FILE_NO_INTERMEDIATE_BUFFERING          0x00000008

define FILE_SYNCHRONOUS_IO_ALERT               0x00000010
define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
define FILE_NON_DIRECTORY_FILE                 0x00000040
define FILE_CREATE_TREE_CONNECTION             0x00000080

define FILE_COMPLETE_IF_OPLOCKED               0x00000100
define FILE_NO_EA_KNOWLEDGE                    0x00000200
define FILE_OPEN_REMOTE_INSTANCE               0x00000400
define FILE_RANDOM_ACCESS                      0x00000800

define FILE_DELETE_ON_CLOSE                    0x00001000
define FILE_OPEN_BY_FILE_ID                    0x00002000
define FILE_OPEN_FOR_BACKUP_INTENT             0x00004000
define FILE_NO_COMPRESSION                     0x00008000

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)
define FILE_OPEN_REQUIRING_OPLOCK              0x00010000
endif

define FILE_RESERVE_OPFILTER                   0x00100000
define FILE_OPEN_REPARSE_POINT                 0x00200000
define FILE_OPEN_NO_RECALL                     0x00400000
define FILE_OPEN_FOR_FREE_SPACE_QUERY          0x00800000

define FILE_VALID_OPTION_FLAGS                 0x00ffffff
define FILE_VALID_PIPE_OPTION_FLAGS            0x00000032
define FILE_VALID_MAILSLOT_OPTION_FLAGS        0x00000032
define FILE_VALID_SET_FLAGS                    0x00000036

define FILE_SUPERSEDED                 0x00000000
define FILE_OPENED                     0x00000001
define FILE_CREATED                    0x00000002
define FILE_OVERWRITTEN                0x00000003
define FILE_EXISTS                     0x00000004
define FILE_DOES_NOT_EXIST             0x00000005

endif

endif

endif

.pragma list(push, 0)
ifndef _WINBASE_
define _WINBASE_
ifndef __LIBC_INC
include libc.inc
endif

ifdef _WIN64
.pragma pack(push, 8)
endif

include winapifamily.inc

.pragma comment(lib, kernel32)

include apisetcconv.inc
include minwinbase.inc

include apiquery2.inc
include processenv.inc
include fileapifromapp.inc
include debugapi.inc
include utilapiset.inc
include handleapi.inc
include errhandlingapi.inc
include fibersapi.inc
include namedpipeapi.inc
include profileapi.inc
include heapapi.inc
include ioapiset.inc
include synchapi.inc
include interlockedapi.inc
include processthreadsapi.inc
include sysinfoapi.inc
include memoryapi.inc
include enclaveapi.inc
include threadpoollegacyapiset.inc
include threadpoolapiset.inc
include jobapi.inc
include jobapi2.inc
include wow64apiset.inc
include libloaderapi.inc
include securitybaseapi.inc
include namespaceapi.inc
include systemtopologyapi.inc
include processtopologyapi.inc
include securityappcontainer.inc
include realtimeapiset.inc

GetImageBase macro
ifdef _WIN64
    mov     rax,gs:[0x60]
    mov     rax,[rax+0x10]
    retm    <rax>
else
    assume  fs:nothing
    mov     eax,fs:[0x30]
    assume  fs:error
    mov     eax,[eax+0x08]
    retm    <eax>
endif
    endm

DefineHandleTable macro w
  exitm<((w),TRUE)>
  endm
LimitEmsPages macro w
  exitm<>
  endm
SetSwapAreaSize macro w
  exitm<(w)>
  endm
LockSegment macro w
  exitm<GlobalFix((w))>
  endm
UnlockSegment macro w
  exitm<GlobalUnfix((w))>
  endm

GetCurrentTime macro
  exitm<GetTickCount()>
  endm

Yield macro
  exitm<>
  endm

define FILE_BEGIN           0
define FILE_CURRENT         1
define FILE_END             2

define WAIT_FAILED          (0xFFFFFFFF)
define WAIT_OBJECT_0        ((STATUS_WAIT_0 ) + 0 )

define WAIT_ABANDONED       ((STATUS_ABANDONED_WAIT_0 ) + 0 )
define WAIT_ABANDONED_0     ((STATUS_ABANDONED_WAIT_0 ) + 0 )

define WAIT_IO_COMPLETION   STATUS_USER_APC

define SecureZeroMemory <RtlSecureZeroMemory>
define CaptureStackBackTrace <RtlCaptureStackBackTrace>

define FILE_FLAG_WRITE_THROUGH         0x80000000
define FILE_FLAG_OVERLAPPED            0x40000000
define FILE_FLAG_NO_BUFFERING          0x20000000
define FILE_FLAG_RANDOM_ACCESS         0x10000000
define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
define FILE_FLAG_POSIX_SEMANTICS       0x01000000
define FILE_FLAG_SESSION_AWARE         0x00800000
define FILE_FLAG_OPEN_REPARSE_POINT    0x00200000
define FILE_FLAG_OPEN_NO_RECALL        0x00100000
define FILE_FLAG_FIRST_PIPE_INSTANCE   0x00080000

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
define FILE_FLAG_OPEN_REQUIRING_OPLOCK 0x00040000
endif

if(_WIN32_WINNT ge 0x0400)

define PROGRESS_CONTINUE   0
define PROGRESS_CANCEL     1
define PROGRESS_STOP       2
define PROGRESS_QUIET      3

define CALLBACK_CHUNK_FINISHED         0x00000000
define CALLBACK_STREAM_SWITCH          0x00000001

define COPY_FILE_FAIL_IF_EXISTS                 0x00000001
define COPY_FILE_RESTARTABLE                    0x00000002
define COPY_FILE_OPEN_SOURCE_FOR_WRITE          0x00000004
define COPY_FILE_ALLOW_DECRYPTED_DESTINATION    0x00000008

if (_WIN32_WINNT ge 0x0600)
define COPY_FILE_COPY_SYMLINK                   0x00000800
define COPY_FILE_NO_BUFFERING                   0x00001000
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
define COPY_FILE_REQUEST_SECURITY_PRIVILEGES    0x00002000
define COPY_FILE_RESUME_FROM_PAUSE              0x00004000
define COPY_FILE_NO_OFFLOAD                     0x00040000
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN10)
define COPY_FILE_IGNORE_EDP_BLOCK               0x00400000
define COPY_FILE_IGNORE_SOURCE_ENCRYPTION       0x00800000
define COPY_FILE_DONT_REQUEST_DEST_WRITE_DAC    0x02000000
define COPY_FILE_REQUEST_COMPRESSED_TRAFFIC     0x10000000
endif

if (NTDDI_VERSION ge NTDDI_WIN10_VB)
define COPY_FILE_OPEN_AND_COPY_REPARSE_POINT    0x00200000
define COPY_FILE_DIRECTORY                      0x00000080
define COPY_FILE_SKIP_ALTERNATE_STREAMS         0x00008000
define COPY_FILE_DISABLE_PRE_ALLOCATION         0x04000000
define COPY_FILE_ENABLE_LOW_FREE_SPACE_MODE     0x08000000
endif

endif

if (_WIN32_WINNT ge 0x0500)
define REPLACEFILE_WRITE_THROUGH       0x00000001
define REPLACEFILE_IGNORE_MERGE_ERRORS 0x00000002
if (_WIN32_WINNT ge 0x0600)
define REPLACEFILE_IGNORE_ACL_ERRORS   0x00000004
endif
endif

define PIPE_ACCESS_INBOUND         0x00000001
define PIPE_ACCESS_OUTBOUND        0x00000002
define PIPE_ACCESS_DUPLEX          0x00000003

define PIPE_CLIENT_END             0x00000000
define PIPE_SERVER_END             0x00000001

define PIPE_WAIT                   0x00000000
define PIPE_NOWAIT                 0x00000001
define PIPE_READMODE_BYTE          0x00000000
define PIPE_READMODE_MESSAGE       0x00000002
define PIPE_TYPE_BYTE              0x00000000
define PIPE_TYPE_MESSAGE           0x00000004
define PIPE_ACCEPT_REMOTE_CLIENTS  0x00000000
define PIPE_REJECT_REMOTE_CLIENTS  0x00000008

define PIPE_UNLIMITED_INSTANCES    255

define SECURITY_ANONYMOUS          ( SecurityAnonymous shl 16 )
define SECURITY_IDENTIFICATION     ( SecurityIdentification shl 16 )
define SECURITY_IMPERSONATION      ( SecurityImpersonation shl 16 )
define SECURITY_DELEGATION         ( SecurityDelegation shl 16 )

define SECURITY_CONTEXT_TRACKING  0x00040000
define SECURITY_EFFECTIVE_ONLY    0x00080000

define SECURITY_SQOS_PRESENT      0x00100000
define SECURITY_VALID_SQOS_FLAGS  0x001F0000

if(_WIN32_WINNT ge 0x0400)
CALLBACK(PFIBER_START_ROUTINE, :LPVOID)
LPFIBER_START_ROUTINE   typedef PFIBER_START_ROUTINE

CALLBACK(PFIBER_CALLOUT_ROUTINE, :LPVOID)
endif

define FAIL_FAST_GENERATE_EXCEPTION_ADDRESS    0x1
define FAIL_FAST_NO_HARD_ERROR_DLG             0x2

ifdef _X86_
LPLDT_ENTRY typedef PLDT_ENTRY
else
LPLDT_ENTRY typedef ptr
endif


define SP_SERIALCOMM    (0x00000001)

define PST_UNSPECIFIED      (0x00000000)
define PST_RS232            (0x00000001)
define PST_PARALLELPORT     (0x00000002)
define PST_RS422            (0x00000003)
define PST_RS423            (0x00000004)
define PST_RS449            (0x00000005)
define PST_MODEM            (0x00000006)
define PST_FAX              (0x00000021)
define PST_SCANNER          (0x00000022)
define PST_NETWORK_BRIDGE   (0x00000100)
define PST_LAT              (0x00000101)
define PST_TCPIP_TELNET     (0x00000102)
define PST_X25              (0x00000103)

define PCF_DTRDSR        (0x0001)
define PCF_RTSCTS        (0x0002)
define PCF_RLSD          (0x0004)
define PCF_PARITY_CHECK  (0x0008)
define PCF_XONXOFF       (0x0010)
define PCF_SETXCHAR      (0x0020)
define PCF_TOTALTIMEOUTS (0x0040)
define PCF_INTTIMEOUTS   (0x0080)
define PCF_SPECIALCHARS  (0x0100)
define PCF_16BITMODE     (0x0200)

define SP_PARITY         (0x0001)
define SP_BAUD           (0x0002)
define SP_DATABITS       (0x0004)
define SP_STOPBITS       (0x0008)
define SP_HANDSHAKING    (0x0010)
define SP_PARITY_CHECK   (0x0020)
define SP_RLSD           (0x0040)

define BAUD_075          (0x00000001)
define BAUD_110          (0x00000002)
define BAUD_134_5        (0x00000004)
define BAUD_150          (0x00000008)
define BAUD_300          (0x00000010)
define BAUD_600          (0x00000020)
define BAUD_1200         (0x00000040)
define BAUD_1800         (0x00000080)
define BAUD_2400         (0x00000100)
define BAUD_4800         (0x00000200)
define BAUD_7200         (0x00000400)
define BAUD_9600         (0x00000800)
define BAUD_14400        (0x00001000)
define BAUD_19200        (0x00002000)
define BAUD_38400        (0x00004000)
define BAUD_56K          (0x00008000)
define BAUD_128K         (0x00010000)
define BAUD_115200       (0x00020000)
define BAUD_57600        (0x00040000)
define BAUD_USER         (0x10000000)

define DATABITS_5        (0x0001)
define DATABITS_6        (0x0002)
define DATABITS_7        (0x0004)
define DATABITS_8        (0x0008)
define DATABITS_16       (0x0010)
define DATABITS_16X      (0x0020)

define STOPBITS_10       (0x0001)
define STOPBITS_15       (0x0002)
define STOPBITS_20       (0x0004)
define PARITY_NONE       (0x0100)
define PARITY_ODD        (0x0200)
define PARITY_EVEN       (0x0400)
define PARITY_MARK       (0x0800)
define PARITY_SPACE      (0x1000)

COMMPROP                struct
wPacketLength           WORD ?
wPacketVersion          WORD ?
dwServiceMask           DWORD ?
dwReserved1             DWORD ?
dwMaxTxQueue            DWORD ?
dwMaxRxQueue            DWORD ?
dwMaxBaud               DWORD ?
dwProvSubType           DWORD ?
dwProvCapabilities      DWORD ?
dwSettableParams        DWORD ?
dwSettableBaud          DWORD ?
wSettableData           WORD ?
wSettableStopParity     WORD ?
dwCurrentTxQueue        DWORD ?
dwCurrentRxQueue        DWORD ?
dwProvSpec1             DWORD ?
dwProvSpec2             DWORD ?
wcProvChar              WCHAR 1 dup(?)
COMMPROP                ends
LPCOMMPROP              typedef ptr COMMPROP

define COMMPROP_INITIALIZED (0xE73CF52E)

COMSTAT                 struct
record
 fCtsHold               DWORD :  1 ?
 fDsrHold               DWORD :  1 ?
 fRlsdHold              DWORD :  1 ?
 fXoffHold              DWORD :  1 ?
 fXoffSent              DWORD :  1 ?
 fEof                   DWORD :  1 ?
 fTxim                  DWORD :  1 ?
 fReserved              DWORD : 25 ?
ends
cbInQue                 DWORD ?
cbOutQue                DWORD ?
COMSTAT                 ends
LPCOMSTAT               typedef ptr COMSTAT

define DTR_CONTROL_DISABLE    0x00
define DTR_CONTROL_ENABLE     0x01
define DTR_CONTROL_HANDSHAKE  0x02

define RTS_CONTROL_DISABLE    0x00
define RTS_CONTROL_ENABLE     0x01
define RTS_CONTROL_HANDSHAKE  0x02
define RTS_CONTROL_TOGGLE     0x03

DCB                     struct
DCBlength               DWORD ?
BaudRate                DWORD ?
record
 fBinary                DWORD :  1 ?
 fParity                DWORD :  1 ?
 fOutxCtsFlow           DWORD :  1 ?
 fOutxDsrFlow           DWORD :  1 ?
 fDtrControl            DWORD :  2 ?
 fDsrSensitivity        DWORD :  1 ?
 fTXContinueOnXoff      DWORD :  1 ?
 fOutX                  DWORD :  1 ?
 fInX                   DWORD :  1 ?
 fErrorChar             DWORD :  1 ?
 fNull                  DWORD :  1 ?
 fRtsControl            DWORD :  2 ?
 fAbortOnError          DWORD :  1 ?
 fDummy2                DWORD : 17 ?
ends
wReserved               WORD ?
XonLim                  WORD ?
XoffLim                 WORD ?
ByteSize                BYTE ?
Parity                  BYTE ?
StopBits                BYTE ?
XonChar                 sbyte ?
XoffChar                sbyte ?
ErrorChar               sbyte ?
EofChar                 sbyte ?
EvtChar                 sbyte ?
wReserved1              WORD ?
DCB                     ends
LPDCB                   typedef ptr DCB

COMMTIMEOUTS            struct
ReadIntervalTimeout     DWORD ?
ReadTotalTimeoutMultiplier DWORD ?
ReadTotalTimeoutConstant DWORD ?
WriteTotalTimeoutMultiplier DWORD ?
WriteTotalTimeoutConstant DWORD ?
COMMTIMEOUTS            ends
LPCOMMTIMEOUTS          typedef ptr COMMTIMEOUTS

COMMCONFIG              struct
dwSize                  DWORD ?
wVersion                WORD ?
wReserved               WORD ?
dcb                     DCB <>
dwProviderSize          DWORD ?
wcProviderData          WCHAR 1 dup(?)
COMMCONFIG              ends
LPCOMMCONFIG            typedef ptr COMMCONFIG

FreeModule macro hLibModule
  exitm<FreeLibrary((hLibModule))>
  endm
MakeProcInstance macro lpProc,hInstance
  exitm<(lpProc)>
  endm
FreeProcInstance macro lpProc
  exitm<(lpProc)>
  endm

define GMEM_FIXED          0x0000
define GMEM_MOVEABLE       0x0002
define GMEM_NOCOMPACT      0x0010
define GMEM_NODISCARD      0x0020
define GMEM_ZEROINIT       0x0040
define GMEM_MODIFY         0x0080
define GMEM_DISCARDABLE    0x0100
define GMEM_NOT_BANKED     0x1000
define GMEM_SHARE          0x2000
define GMEM_DDESHARE       0x2000
define GMEM_NOTIFY         0x4000
define GMEM_LOWER          GMEM_NOT_BANKED
define GMEM_VALID_FLAGS    0x7F72
define GMEM_INVALID_HANDLE 0x8000

define GHND                (GMEM_MOVEABLE or GMEM_ZEROINIT)
define GPTR                (GMEM_FIXED or GMEM_ZEROINIT)

GlobalLRUNewest macro  h
  exitm<(h)>
  endm
GlobalLRUOldest macro  h
  exitm<(h)>
  endm
GlobalDiscard macro  h
  exitm<GlobalReAlloc( (h), 0, GMEM_MOVEABLE )>
  endm

define GMEM_DISCARDED      0x4000
define GMEM_LOCKCOUNT      0x00FF

MEMORYSTATUS            struct
dwLength                DWORD ?
dwMemoryLoad            DWORD ?
dwTotalPhys             SIZE_T ?
dwAvailPhys             SIZE_T ?
dwTotalPageFile         SIZE_T ?
dwAvailPageFile         SIZE_T ?
dwTotalVirtual          SIZE_T ?
dwAvailVirtual          SIZE_T ?
MEMORYSTATUS            ends
LPMEMORYSTATUS          typedef ptr MEMORYSTATUS

define DEBUG_PROCESS                     0x00000001
define DEBUG_ONLY_THIS_PROCESS           0x00000002
define CREATE_SUSPENDED                  0x00000004
define DETACHED_PROCESS                  0x00000008

define CREATE_NEW_CONSOLE                0x00000010
define NORMAL_PRIORITY_CLASS             0x00000020
define IDLE_PRIORITY_CLASS               0x00000040
define HIGH_PRIORITY_CLASS               0x00000080

define REALTIME_PRIORITY_CLASS           0x00000100
define CREATE_NEW_PROCESS_GROUP          0x00000200
define CREATE_UNICODE_ENVIRONMENT        0x00000400
define CREATE_SEPARATE_WOW_VDM           0x00000800

define CREATE_SHARED_WOW_VDM             0x00001000
define CREATE_FORCEDOS                   0x00002000
define BELOW_NORMAL_PRIORITY_CLASS       0x00004000
define ABOVE_NORMAL_PRIORITY_CLASS       0x00008000

define INHERIT_PARENT_AFFINITY           0x00010000
define INHERIT_CALLER_PRIORITY           0x00020000
define CREATE_PROTECTED_PROCESS          0x00040000
define EXTENDED_STARTUPINFO_PRESENT      0x00080000

define PROCESS_MODE_BACKGROUND_BEGIN     0x00100000
define PROCESS_MODE_BACKGROUND_END       0x00200000
define CREATE_SECURE_PROCESS             0x00400000

define CREATE_BREAKAWAY_FROM_JOB         0x01000000
define CREATE_PRESERVE_CODE_AUTHZ_LEVEL  0x02000000
define CREATE_DEFAULT_ERROR_MODE         0x04000000
define CREATE_NO_WINDOW                  0x08000000

define PROFILE_USER                      0x10000000
define PROFILE_KERNEL                    0x20000000
define PROFILE_SERVER                    0x40000000
define CREATE_IGNORE_SYSTEM_DEFAULT      0x80000000

define STACK_SIZE_PARAM_IS_A_RESERVATION   0x00010000

define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
define THREAD_PRIORITY_BELOW_NORMAL    (THREAD_PRIORITY_LOWEST+1)
define THREAD_PRIORITY_NORMAL          0
define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
define THREAD_PRIORITY_ABOVE_NORMAL    (THREAD_PRIORITY_HIGHEST-1)
define THREAD_PRIORITY_ERROR_RETURN    (MAXLONG)

define THREAD_PRIORITY_TIME_CRITICAL   THREAD_BASE_PRIORITY_LOWRT
define THREAD_PRIORITY_IDLE            THREAD_BASE_PRIORITY_IDLE

define THREAD_MODE_BACKGROUND_BEGIN    0x00010000
define THREAD_MODE_BACKGROUND_END      0x00020000

define VOLUME_NAME_DOS  0x0
define VOLUME_NAME_GUID 0x1
define VOLUME_NAME_NT   0x2
define VOLUME_NAME_NONE 0x4

define FILE_NAME_NORMALIZED 0x0
define FILE_NAME_OPENED     0x8

JIT_DEBUG_INFO          struct
dwSize                  DWORD ?
dwProcessorArchitecture DWORD ?
dwThreadID              DWORD ?
dwReserved0             DWORD ?
lpExceptionAddress      ULONG64 ?
lpExceptionRecord       ULONG64 ?
lpContextRecord         ULONG64 ?
JIT_DEBUG_INFO          ends
LPJIT_DEBUG_INFO        typedef ptr JIT_DEBUG_INFO

LPJIT_DEBUG_INFO32      typedef ptr JIT_DEBUG_INFO32
LPJIT_DEBUG_INFO64      typedef ptr JIT_DEBUG_INFO64

ifndef MIDL_PASS
LPEXCEPTION_RECORD      typedef PEXCEPTION_RECORD
LPEXCEPTION_POINTERS    typedef PEXCEPTION_POINTERS
endif

define DRIVE_UNKNOWN     0
define DRIVE_NO_ROOT_DIR 1
define DRIVE_REMOVABLE   2
define DRIVE_FIXED       3
define DRIVE_REMOTE      4
define DRIVE_CDROM       5
define DRIVE_RAMDISK     6

ifndef _MAC
GetFreeSpace macro w
  exitm<(0x100000)>
  endm
else
GetFreeSpace proto WINAPI :UINT
endif

define FILE_TYPE_UNKNOWN   0x0000
define FILE_TYPE_DISK      0x0001
define FILE_TYPE_CHAR      0x0002
define FILE_TYPE_PIPE      0x0003
define FILE_TYPE_REMOTE    0x8000

define STD_INPUT_HANDLE    (-10)
define STD_OUTPUT_HANDLE   (-11)
define STD_ERROR_HANDLE    (-12)

define NOPARITY            0
define ODDPARITY           1
define EVENPARITY          2
define MARKPARITY          3
define SPACEPARITY         4

define ONESTOPBIT          0
define ONE5STOPBITS        1
define TWOSTOPBITS         2

define IGNORE              0

define INFINITE            0xFFFFFFFF

define CBR_110             110
define CBR_300             300
define CBR_600             600
define CBR_1200            1200
define CBR_2400            2400
define CBR_4800            4800
define CBR_9600            9600
define CBR_14400           14400
define CBR_19200           19200
define CBR_38400           38400
define CBR_56000           56000
define CBR_57600           57600
define CBR_115200          115200
define CBR_128000          128000
define CBR_256000          256000

define CE_RXOVER           0x0001
define CE_OVERRUN          0x0002
define CE_RXPARITY         0x0004
define CE_FRAME            0x0008
define CE_BREAK            0x0010
define CE_TXFULL           0x0100
define CE_PTO              0x0200
define CE_IOE              0x0400
define CE_DNS              0x0800
define CE_OOP              0x1000
define CE_MODE             0x8000

define IE_BADID            (-1)
define IE_OPEN             (-2)
define IE_NOPEN            (-3)
define IE_MEMORY           (-4)
define IE_DEFAULT          (-5)
define IE_HARDWARE         (-10)
define IE_BYTESIZE         (-11)
define IE_BAUDRATE         (-12)

define EV_RXCHAR           0x0001
define EV_RXFLAG           0x0002
define EV_TXEMPTY          0x0004
define EV_CTS              0x0008
define EV_DSR              0x0010
define EV_RLSD             0x0020
define EV_BREAK            0x0040
define EV_ERR              0x0080
define EV_RING             0x0100
define EV_PERR             0x0200
define EV_RX80FULL         0x0400
define EV_EVENT1           0x0800
define EV_EVENT2           0x1000

define SETXOFF             1
define SETXON              2
define SETRTS              3
define CLRRTS              4
define SETDTR              5
define CLRDTR              6
define RESETDEV            7
define SETBREAK            8
define CLRBREAK            9

define PURGE_TXABORT       0x0001
define PURGE_RXABORT       0x0002
define PURGE_TXCLEAR       0x0004
define PURGE_RXCLEAR       0x0008

define LPTx                0x80

define MS_CTS_ON           (0x0010)
define MS_DSR_ON           (0x0020)
define MS_RING_ON          (0x0040)
define MS_RLSD_ON          (0x0080)

define S_QUEUEEMPTY        0
define S_THRESHOLD         1
define S_ALLTHRESHOLD      2

define S_NORMAL      0
define S_LEGATO      1
define S_STACCATO    2

define S_PERIOD512   0
define S_PERIOD1024  1
define S_PERIOD2048  2
define S_PERIODVOICE 3
define S_WHITE512    4
define S_WHITE1024   5
define S_WHITE2048   6
define S_WHITEVOICE  7

define S_SERDVNA     (-1)
define S_SEROFM      (-2)
define S_SERMACT     (-3)
define S_SERQFUL     (-4)
define S_SERBDNT     (-5)
define S_SERDLN      (-6)
define S_SERDCC      (-7)
define S_SERDTP      (-8)
define S_SERDVL      (-9)
define S_SERDMD      (-10)
define S_SERDSH      (-11)
define S_SERDPT      (-12)
define S_SERDFQ      (-13)
define S_SERDDR      (-14)
define S_SERDSR      (-15)
define S_SERDST      (-16)

define NMPWAIT_WAIT_FOREVER            0xffffffff
define NMPWAIT_NOWAIT                  0x00000001
define NMPWAIT_USE_DEFAULT_WAIT        0x00000000

define FS_CASE_IS_PRESERVED            FILE_CASE_PRESERVED_NAMES
define FS_CASE_SENSITIVE               FILE_CASE_SENSITIVE_SEARCH
define FS_UNICODE_STORED_ON_DISK       FILE_UNICODE_ON_DISK
define FS_PERSISTENT_ACLS              FILE_PERSISTENT_ACLS
define FS_VOL_IS_COMPRESSED            FILE_VOLUME_IS_COMPRESSED
define FS_FILE_COMPRESSION             FILE_FILE_COMPRESSION
define FS_FILE_ENCRYPTION              FILE_SUPPORTS_ENCRYPTION

define OF_READ             0x00000000
define OF_WRITE            0x00000001
define OF_READWRITE        0x00000002
define OF_SHARE_COMPAT     0x00000000
define OF_SHARE_EXCLUSIVE  0x00000010
define OF_SHARE_DENY_WRITE 0x00000020
define OF_SHARE_DENY_READ  0x00000030
define OF_SHARE_DENY_NONE  0x00000040
define OF_PARSE            0x00000100
define OF_DELETE           0x00000200
define OF_VERIFY           0x00000400
define OF_CANCEL           0x00000800
define OF_CREATE           0x00001000
define OF_PROMPT           0x00002000
define OF_EXIST            0x00004000
define OF_REOPEN           0x00008000

define OFS_MAXPATHNAME 128
OFSTRUCT                struct
cBytes                  BYTE ?
fFixedDisk              BYTE ?
nErrCode                WORD ?
Reserved1               WORD ?
Reserved2               WORD ?
szPathName              CHAR OFS_MAXPATHNAME dup(?)
OFSTRUCT                ends
LPOFSTRUCT              typedef ptr OFSTRUCT
POFSTRUCT               typedef ptr OFSTRUCT

UnlockResource macro hResData
  exitm<((hResData), 0)>
  endm
define MAXINTATOM 0xC000
MAKEINTATOM macro i
  exitm<(i)>
  endm
define INVALID_ATOM (0)

if(_WIN32_WINNT GE 0x0500)
GetConsoleWindow proto WINAPI
endif

ifdef __PE__
option dllimport:none
endif
WinMain proto WINAPI :HINSTANCE, :HINSTANCE, :LPSTR, :int_t
wWinMain proto WINAPI :HINSTANCE, :HINSTANCE, :LPWSTR, :int_t
ifdef __PE__
.pragma comment(lib, kernel32)
endif

GlobalAlloc proto WINAPI :UINT, :SIZE_T
GlobalReAlloc proto WINAPI :HGLOBAL, :SIZE_T, :UINT

GlobalSize proto WINAPI :HGLOBAL
GlobalUnlock proto WINAPI :HGLOBAL
GlobalLock proto WINAPI :HGLOBAL

GlobalFlags proto WINAPI :HGLOBAL
GlobalHandle proto WINAPI :LPCVOID

GlobalFree proto WINAPI :HGLOBAL

GlobalCompact proto WINAPI :DWORD
GlobalFix proto WINAPI :HGLOBAL
GlobalUnfix proto WINAPI :HGLOBAL
GlobalWire proto WINAPI :HGLOBAL
GlobalUnWire proto WINAPI :HGLOBAL
GlobalMemoryStatus proto WINAPI :LPMEMORYSTATUS

LocalAlloc proto WINAPI :UINT, :SIZE_T
LocalReAlloc proto WINAPI :HLOCAL, :SIZE_T, :UINT
LocalLock proto WINAPI :HLOCAL
LocalHandle proto WINAPI :LPCVOID
LocalUnlock proto WINAPI :HLOCAL
LocalSize proto WINAPI :HLOCAL
LocalFlags proto WINAPI :HLOCAL
LocalFree proto WINAPI :HLOCAL
LocalShrink proto WINAPI :HLOCAL, :UINT
LocalCompact proto WINAPI :UINT

define SCS_32BIT_BINARY    0
define SCS_DOS_BINARY      1
define SCS_WOW_BINARY      2
define SCS_PIF_BINARY      3
define SCS_POSIX_BINARY    4
define SCS_OS216_BINARY    5
define SCS_64BIT_BINARY    6

ifdef _WIN64
define SCS_THIS_PLATFORM_BINARY SCS_64BIT_BINARY
else
define SCS_THIS_PLATFORM_BINARY SCS_32BIT_BINARY
endif

GetBinaryTypeA proto WINAPI :LPCSTR, :LPDWORD
GetBinaryTypeW proto WINAPI :LPCWSTR, :LPDWORD
ifdef _UNICODE
define GetBinaryType  <GetBinaryTypeW>
else
define GetBinaryType  <GetBinaryTypeA>
endif

GetShortPathNameA proto WINAPI :LPCSTR, :LPSTR, :DWORD
ifndef _UNICODE
define GetShortPathName  <GetShortPathNameA>
endif

if _WIN32_WINNT ge 0x0600

GetLongPathNameTransactedA proto WINAPI :LPCSTR, :LPSTR, :DWORD, :HANDLE
GetLongPathNameTransactedW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD, :HANDLE
ifdef _UNICODE
define GetLongPathNameTransacted  <GetLongPathNameTransactedW>
else
define GetLongPathNameTransacted  <GetLongPathNameTransactedA>
endif

endif

GetProcessAffinityMask proto WINAPI :HANDLE, :PDWORD_PTR, :PDWORD_PTR
SetProcessAffinityMask proto WINAPI :HANDLE, :DWORD_PTR
GetProcessIoCounters proto WINAPI :HANDLE, :PIO_COUNTERS
GetProcessWorkingSetSize proto WINAPI :HANDLE, :PSIZE_T, :PSIZE_T
SetProcessWorkingSetSize proto WINAPI :HANDLE, :SIZE_T, :SIZE_T
FatalExit proto WINAPI :sdword

SetEnvironmentStringsA proto WINAPI :LPCH
ifndef _UNICODE
define SetEnvironmentStrings  <SetEnvironmentStringsA>
endif

if(_WIN32_WINNT ge 0x0400)

define FIBER_FLAG_FLOAT_SWITCH 0x1

SwitchToFiber proto WINAPI :LPVOID
DeleteFiber proto WINAPI :LPVOID

if (_WIN32_WINNT ge 0x0501)
ConvertFiberToThread proto WINAPI
endif

CreateFiberEx proto WINAPI :SIZE_T, :SIZE_T, :DWORD, :LPFIBER_START_ROUTINE, :LPVOID
ConvertThreadToFiberEx proto WINAPI :LPVOID, :DWORD

CreateFiber proto WINAPI :SIZE_T, :LPFIBER_START_ROUTINE, :LPVOID
ConvertThreadToFiber proto WINAPI :LPVOID

if (_WIN32_WINNT ge 0x0601) and not defined(MIDL_PASS)

define UMS_VERSION RTL_UMS_VERSION

PUMS_CONTEXT            typedef ptr
PUMS_COMPLETION_LIST    typedef ptr

.enum _RTL_UMS_THREAD_INFO_CLASS {
    }
UMS_THREAD_INFO_CLASS   typedef _RTL_UMS_THREAD_INFO_CLASS
PUMS_THREAD_INFO_CLASS  typedef ptr _RTL_UMS_THREAD_INFO_CLASS

.enum _RTL_UMS_SCHEDULER_REASON {
    }
UMS_SCHEDULER_REASON    typedef _RTL_UMS_SCHEDULER_REASON

PUMS_SCHEDULER_ENTRY_POINT typedef PRTL_UMS_SCHEDULER_ENTRY_POINT

UMS_SCHEDULER_STARTUP_INFO struct
UmsVersion              ULONG ?
CompletionList          PUMS_COMPLETION_LIST ?
SchedulerProc           PUMS_SCHEDULER_ENTRY_POINT ?
SchedulerParam          PVOID ?
UMS_SCHEDULER_STARTUP_INFO ends
PUMS_SCHEDULER_STARTUP_INFO typedef ptr UMS_SCHEDULER_STARTUP_INFO

UMS_SYSTEM_THREAD_INFORMATION struct
UmsVersion              ULONG ?
union
 struct
  record
   IsUmsSchedulerThread ULONG :  1 ?
   IsUmsWorkerThread    ULONG :  1 ?
  ends
 ends
 ThreadUmsFlags         ULONG ?
ends
UMS_SYSTEM_THREAD_INFORMATION ends
PUMS_SYSTEM_THREAD_INFORMATION typedef ptr UMS_SYSTEM_THREAD_INFORMATION

CreateUmsCompletionList proto WINAPI :ptr PUMS_COMPLETION_LIST
DequeueUmsCompletionListItems proto WINAPI :PUMS_COMPLETION_LIST, :DWORD, :ptr PUMS_CONTEXT
GetUmsCompletionListEvent proto WINAPI :PUMS_COMPLETION_LIST, :PHANDLE
ExecuteUmsThread proto WINAPI :PUMS_CONTEXT
UmsThreadYield proto WINAPI :ptr
DeleteUmsCompletionList proto WINAPI :PUMS_COMPLETION_LIST
GetCurrentUmsThread proto WINAPI
GetNextUmsListItem proto WINAPI :PUMS_CONTEXT
QueryUmsThreadInformation proto WINAPI :PUMS_CONTEXT, :UMS_THREAD_INFO_CLASS, :ptr, :ULONG, :PULONG
SetUmsThreadInformation proto WINAPI :PUMS_CONTEXT, :UMS_THREAD_INFO_CLASS, :ptr, :ULONG
DeleteUmsThreadContext proto WINAPI :PUMS_CONTEXT
CreateUmsThreadContext proto WINAPI :ptr PUMS_CONTEXT
EnterUmsSchedulingMode proto WINAPI :PUMS_SCHEDULER_STARTUP_INFO
GetUmsSystemThreadInformation proto WINAPI :HANDLE, :PUMS_SYSTEM_THREAD_INFORMATION

endif

endif

SetThreadAffinityMask proto WINAPI :HANDLE, :DWORD_PTR

if (_WIN32_WINNT ge 0x0600)

define PROCESS_DEP_ENABLE                          0x00000001
define PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION     0x00000002

SetProcessDEPPolicy proto WINAPI :DWORD
GetProcessDEPPolicy proto WINAPI :HANDLE, :LPDWORD, :PBOOL

endif

RequestWakeupLatency proto WINAPI :LATENCY_TIME
IsSystemResumeAutomatic proto WINAPI
GetThreadSelectorEntry proto WINAPI :HANDLE, :DWORD, :LPLDT_ENTRY
SetThreadExecutionState proto WINAPI :EXECUTION_STATE

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)

LPPOWER_REQUEST_CONTEXT typedef ptr POWER_REQUEST_CONTEXT

PowerCreateRequest proto WINAPI :PREASON_CONTEXT
PowerSetRequest proto WINAPI :HANDLE, :POWER_REQUEST_TYPE
PowerClearRequest proto WINAPI :HANDLE, :POWER_REQUEST_TYPE

endif

ifdef _M_CEE_PURE
define GetLastError <System::Runtime::InteropServices::Marshal::GetLastWin32Error>
endif

ifndef RC_INVOKED
ifdef WINBASE_DECLARE_RESTORE_LAST_ERROR

RestoreLastError proto WINAPI :DWORD

CALLBACK(PRESTORE_LAST_ERROR, :DWORD)
define RESTORE_LAST_ERROR_NAME_A    <"RestoreLastError">
define RESTORE_LAST_ERROR_NAME_W    <L"RestoreLastError">
define RESTORE_LAST_ERROR_NAME      <"RestoreLastError">

endif
endif

HasOverlappedIoCompleted macro lpOverlapped
  exitm<(((lpOverlapped).Internal) ne STATUS_PENDING)>
  endm

if (_WIN32_WINNT ge 0x0600)

define FILE_SKIP_COMPLETION_PORT_ON_SUCCESS    0x1
define FILE_SKIP_SET_EVENT_ON_HANDLE           0x2

SetFileCompletionNotificationModes proto WINAPI :HANDLE, :UCHAR

endif

define SEM_FAILCRITICALERRORS      0x0001
define SEM_NOGPFAULTERRORBOX       0x0002
define SEM_NOALIGNMENTFAULTEXCEPT  0x0004
define SEM_NOOPENFILEERRORBOX      0x8000

if not defined(MIDL_PASS)
if (_WIN32_WINNT ge 0x0601)
Wow64GetThreadSelectorEntry proto WINAPI :HANDLE, :DWORD, :PWOW64_LDT_ENTRY
endif
endif

DebugSetProcessKillOnExit proto WINAPI :BOOL
DebugBreakProcess proto WINAPI :HANDLE

if (_WIN32_WINNT ge 0x0403)
define CRITICAL_SECTION_NO_DEBUG_INFO  RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO
endif

PulseEvent proto WINAPI :HANDLE
GlobalDeleteAtom proto WINAPI :ATOM
InitAtomTable proto WINAPI :DWORD
DeleteAtom proto WINAPI :ATOM
SetHandleCount proto WINAPI :UINT
RequestDeviceWakeup proto WINAPI :HANDLE
CancelDeviceWakeupRequest proto WINAPI :HANDLE
GetDevicePowerState proto WINAPI :HANDLE, :ptr BOOL
SetMessageWaitingIndicator proto WINAPI :HANDLE, :ULONG
SetFileShortNameA proto WINAPI :HANDLE, :LPCSTR
SetFileShortNameW proto WINAPI :HANDLE, :LPCWSTR
ifdef _UNICODE
define SetFileShortName  <SetFileShortNameW>
else
define SetFileShortName  <SetFileShortNameA>
endif

define HANDLE_FLAG_INHERIT             0x00000001
define HANDLE_FLAG_PROTECT_FROM_CLOSE  0x00000002

define HINSTANCE_ERROR 32

LoadModule proto WINAPI :LPCSTR, :LPVOID
WinExec proto WINAPI :LPCSTR, :UINT

ClearCommBreak proto WINAPI :HANDLE
ClearCommError proto WINAPI :HANDLE, :LPDWORD, :LPCOMSTAT
SetupComm proto WINAPI :HANDLE, :DWORD, :DWORD
EscapeCommFunction proto WINAPI :HANDLE, :DWORD
GetCommConfig proto WINAPI :HANDLE, :LPCOMMCONFIG, :LPDWORD
GetCommMask proto WINAPI :HANDLE, :LPDWORD
GetCommProperties proto WINAPI :HANDLE, :LPCOMMPROP
GetCommModemStatus proto WINAPI :HANDLE, :LPDWORD
GetCommState proto WINAPI :HANDLE, :LPDCB
GetCommTimeouts proto WINAPI :HANDLE, :LPCOMMTIMEOUTS
PurgeComm proto WINAPI :HANDLE, :DWORD
SetCommBreak proto WINAPI :HANDLE
SetCommConfig proto WINAPI :HANDLE, :LPCOMMCONFIG, :DWORD
SetCommMask proto WINAPI :HANDLE, :DWORD
SetCommState proto WINAPI :HANDLE, :LPDCB
SetCommTimeouts proto WINAPI :HANDLE, :LPCOMMTIMEOUTS
TransmitCommChar proto WINAPI :HANDLE, :SBYTE
WaitCommEvent proto WINAPI :HANDLE, :LPDWORD, :LPOVERLAPPED

if (NTDDI_VERSION ge NTDDI_WIN10_RS3)
OpenCommPort proto WINAPI :ULONG, :DWORD, :DWORD
endif
if (NTDDI_VERSION ge NTDDI_WIN10_RS3)
GetCommPorts proto WINAPI :PULONG, :ULONG, :PULONG
endif

SetTapePosition proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :DWORD, :BOOL
GetTapePosition proto WINAPI :HANDLE, :DWORD, :LPDWORD, :LPDWORD, :LPDWORD
PrepareTape proto WINAPI :HANDLE, :DWORD, :BOOL
EraseTape proto WINAPI :HANDLE, :DWORD, :BOOL
CreateTapePartition proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD
WriteTapemark proto WINAPI :HANDLE, :DWORD, :DWORD, :BOOL
GetTapeStatus proto WINAPI :HANDLE
GetTapeParameters proto WINAPI :HANDLE, :DWORD, :LPDWORD, :LPVOID

define GET_TAPE_MEDIA_INFORMATION 0
define GET_TAPE_DRIVE_INFORMATION 1

SetTapeParameters proto WINAPI :HANDLE, :DWORD, :LPVOID

define SET_TAPE_MEDIA_INFORMATION 0
define SET_TAPE_DRIVE_INFORMATION 1

MulDiv proto WINAPI :int_t, :int_t, :int_t

.enum DEP_SYSTEM_POLICY_TYPE {
    DEPPolicyAlwaysOff = 0,
    DEPPolicyAlwaysOn,
    DEPPolicyOptIn,
    DEPPolicyOptOut,
    DEPTotalPolicyCount
    }

if (NTDDI_VERSION ge NTDDI_WINXPSP3)
GetSystemDEPPolicy proto WINAPI
endif

if _WIN32_WINNT ge 0x0501
GetSystemRegistryQuota proto WINAPI :PDWORD, :PDWORD
endif

FileTimeToDosDateTime proto WINAPI :ptr, :LPWORD, :LPWORD
DosDateTimeToFileTime proto WINAPI :WORD, :WORD, :LPFILETIME

define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100

ifndef MIDL_PASS
FormatMessageA proto WINAPI :DWORD, :LPCVOID, :DWORD, :DWORD, :LPSTR, :DWORD, :ptr
FormatMessageW proto WINAPI :DWORD, :LPCVOID, :DWORD, :DWORD, :LPWSTR, :DWORD, :ptr
ifdef _UNICODE
define FormatMessage  <FormatMessageW>
else
define FormatMessage  <FormatMessageA>
endif
endif

define FORMAT_MESSAGE_IGNORE_INSERTS  0x00000200
define FORMAT_MESSAGE_FROM_STRING     0x00000400
define FORMAT_MESSAGE_FROM_HMODULE    0x00000800
define FORMAT_MESSAGE_FROM_SYSTEM     0x00001000
define FORMAT_MESSAGE_ARGUMENT_ARRAY  0x00002000
define FORMAT_MESSAGE_MAX_WIDTH_MASK  0x000000FF

CreateMailslotA proto WINAPI :LPCSTR, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES
CreateMailslotW proto WINAPI :LPCWSTR, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES
ifdef _UNICODE
define CreateMailslot  <CreateMailslotW>
else
define CreateMailslot  <CreateMailslotA>
endif

GetMailslotInfo proto WINAPI :HANDLE, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD
SetMailslotInfo proto WINAPI :HANDLE, :DWORD

.pragma(comment(lib, advapi32))

EncryptFileA proto WINAPI :LPCSTR
EncryptFileW proto WINAPI :LPCWSTR
ifdef _UNICODE
define EncryptFile  <EncryptFileW>
else
define EncryptFile  <EncryptFileA>
endif

DecryptFileA proto WINAPI :LPCSTR, :DWORD
DecryptFileW proto WINAPI :LPCWSTR, :DWORD
ifdef _UNICODE
define DecryptFile  <DecryptFileW>
else
define DecryptFile  <DecryptFileA>
endif

define FILE_ENCRYPTABLE                0
define FILE_IS_ENCRYPTED               1
define FILE_SYSTEM_ATTR                2
define FILE_ROOT_DIR                   3
define FILE_SYSTEM_DIR                 4
define FILE_UNKNOWN                    5
define FILE_SYSTEM_NOT_SUPPORT         6
define FILE_USER_DISALLOWED            7
define FILE_READ_ONLY                  8
define FILE_DIR_DISALLOWED             9

FileEncryptionStatusA proto WINAPI :LPCSTR, :LPDWORD
FileEncryptionStatusW proto WINAPI :LPCWSTR, :LPDWORD
ifdef _UNICODE
define FileEncryptionStatus  <FileEncryptionStatusW>
else
define FileEncryptionStatus  <FileEncryptionStatusA>
endif

define EFS_USE_RECOVERY_KEYS  (0x1)

CALLBACK(PFE_EXPORT_FUNC, :PBYTE, :ptr, :ULONG)
CALLBACK(PFE_IMPORT_FUNC, :ptr, :ptr, :ptr, :PULONG)

define CREATE_FOR_IMPORT               (1)
define CREATE_FOR_DIR                  (2)
define OVERWRITE_HIDDEN                (4)
define EFSRPC_SECURE_ONLY              (8)
define EFS_DROP_ALTERNATE_STREAMS      (0x10)

OpenEncryptedFileRawA proto WINAPI :LPCSTR, :ULONG, :ptr
OpenEncryptedFileRawW proto WINAPI :LPCWSTR, :ULONG, :ptr
ifdef _UNICODE
define OpenEncryptedFileRaw  <OpenEncryptedFileRawW>
else
define OpenEncryptedFileRaw  <OpenEncryptedFileRawA>
endif

ReadEncryptedFileRaw proto WINAPI :PFE_EXPORT_FUNC, :ptr, :ptr
WriteEncryptedFileRaw proto WINAPI :PFE_IMPORT_FUNC, :ptr, :ptr
CloseEncryptedFileRaw proto WINAPI :ptr

ifdef __PE__
.pragma comment(lib, kernel32)
endif

lstrcmpA proto WINAPI :LPCSTR, :LPCSTR
lstrcmpW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define lstrcmp  <lstrcmpW>
else
define lstrcmp  <lstrcmpA>
endif

lstrcmpiA proto WINAPI :LPCSTR, :LPCSTR
lstrcmpiW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define lstrcmpi  <lstrcmpiW>
else
define lstrcmpi  <lstrcmpiA>
endif

lstrcpynA proto WINAPI :LPSTR, :LPCSTR, :sdword
lstrcpynW proto WINAPI :LPWSTR, :LPCWSTR, :sdword
ifdef _UNICODE
define lstrcpyn  <lstrcpynW>
else
define lstrcpyn  <lstrcpynA>
endif

lstrcpyA proto WINAPI :LPSTR, :LPCSTR
lstrcpyW proto WINAPI :LPWSTR, :LPCWSTR
ifdef _UNICODE
define lstrcpy  <lstrcpyW>
else
define lstrcpy  <lstrcpyA>
endif

lstrcatA proto WINAPI :LPSTR, :LPCSTR
lstrcatW proto WINAPI :LPWSTR, :LPCWSTR
ifdef _UNICODE
define lstrcat  <lstrcatW>
else
define lstrcat  <lstrcatA>
endif

lstrlenA proto WINAPI :LPCSTR
lstrlenW proto WINAPI :LPCWSTR
ifdef _UNICODE
define lstrlen  <lstrlenW>
else
define lstrlen  <lstrlenA>
endif

OpenFile proto WINAPI :LPCSTR, :LPOFSTRUCT, :UINT

_lopen proto WINAPI :LPCSTR, :sdword
_lcreat proto WINAPI :LPCSTR, :sdword
_lread proto WINAPI :HFILE, :LPVOID, :UINT
_lwrite proto WINAPI :HFILE, :LPCCH, :UINT
_hread proto WINAPI :HFILE, :LPVOID, :sdword
_hwrite proto WINAPI :HFILE, :LPCCH, :sdword
_lclose proto WINAPI :HFILE
_llseek proto WINAPI :HFILE, :LONG, :sdword

IsTextUnicode proto WINAPI :ptr, :sdword, :LPINT

if(_WIN32_WINNT ge 0x0400)
SignalObjectAndWait proto WINAPI :HANDLE, :HANDLE, :DWORD, :BOOL
endif

BackupRead proto WINAPI :HANDLE, :LPBYTE, :DWORD, :LPDWORD, :BOOL, :BOOL, :ptr
BackupSeek proto WINAPI :HANDLE, :DWORD, :DWORD, :LPDWORD, :LPDWORD, :ptr
BackupWrite proto WINAPI :HANDLE, :LPBYTE, :DWORD, :LPDWORD, :BOOL, :BOOL, :ptr

WIN32_STREAM_ID         struct
dwStreamId              DWORD ?
dwStreamAttributes      DWORD ?
Size                    LARGE_INTEGER <>
dwStreamNameSize        DWORD ?
cStreamName             WCHAR ANYSIZE_ARRAY dup(?)
WIN32_STREAM_ID         ends
LPWIN32_STREAM_ID       typedef ptr WIN32_STREAM_ID

define BACKUP_INVALID          0x00000000
define BACKUP_DATA             0x00000001
define BACKUP_EA_DATA          0x00000002
define BACKUP_SECURITY_DATA    0x00000003
define BACKUP_ALTERNATE_DATA   0x00000004
define BACKUP_LINK             0x00000005
define BACKUP_PROPERTY_DATA    0x00000006
define BACKUP_OBJECT_ID        0x00000007
define BACKUP_REPARSE_DATA     0x00000008
define BACKUP_SPARSE_BLOCK     0x00000009
define BACKUP_TXFS_DATA        0x0000000a
define BACKUP_GHOSTED_FILE_EXTENTS 0x0000000b

define STREAM_NORMAL_ATTRIBUTE         0x00000000
define STREAM_MODIFIED_WHEN_READ       0x00000001
define STREAM_CONTAINS_SECURITY        0x00000002
define STREAM_CONTAINS_PROPERTIES      0x00000004
define STREAM_SPARSE_ATTRIBUTE         0x00000008
define STREAM_CONTAINS_GHOSTED_FILE_EXTENTS 0x00000010

define STARTF_USESHOWWINDOW       0x00000001
define STARTF_USESIZE             0x00000002
define STARTF_USEPOSITION         0x00000004
define STARTF_USECOUNTCHARS       0x00000008
define STARTF_USEFILLATTRIBUTE    0x00000010
define STARTF_RUNFULLSCREEN       0x00000020
define STARTF_FORCEONFEEDBACK     0x00000040
define STARTF_FORCEOFFFEEDBACK    0x00000080
define STARTF_USESTDHANDLES       0x00000100

if (WINVER ge 0x0400)
define STARTF_USEHOTKEY           0x00000200
define STARTF_TITLEISLINKNAME     0x00000800
define STARTF_TITLEISAPPID        0x00001000
define STARTF_PREVENTPINNING      0x00002000
endif

if (WINVER ge 0x0600)
define STARTF_UNTRUSTEDSOURCE     0x00008000
endif

if (_WIN32_WINNT ge 0x0600)

STARTUPINFOEXA          struct
StartupInfo             STARTUPINFOA <>
lpAttributeList         LPPROC_THREAD_ATTRIBUTE_LIST ?
STARTUPINFOEXA          ends
LPSTARTUPINFOEXA        typedef ptr STARTUPINFOEXA
STARTUPINFOEXW          struct
StartupInfo             STARTUPINFOW <>
lpAttributeList         LPPROC_THREAD_ATTRIBUTE_LIST ?
STARTUPINFOEXW          ends
LPSTARTUPINFOEXW        typedef ptr STARTUPINFOEXW
ifdef _UNICODE
STARTUPINFOEX           typedef STARTUPINFOEXW
LPSTARTUPINFOEX         typedef LPSTARTUPINFOEXW
else
STARTUPINFOEX           typedef STARTUPINFOEXA
LPSTARTUPINFOEX         typedef LPSTARTUPINFOEXA
endif

endif

define SHUTDOWN_NORETRY                0x00000001

OpenMutexA proto WINAPI :DWORD, :BOOL, :LPCSTR
ifndef _UNICODE
define OpenMutex  <OpenMutexA>
endif

CreateSemaphoreA proto WINAPI :LPSECURITY_ATTRIBUTES, :LONG, :LONG, :LPCSTR
ifndef _UNICODE
define CreateSemaphore  <CreateSemaphoreA>
endif

OpenSemaphoreA proto WINAPI :DWORD, :BOOL, :LPCSTR
ifndef _UNICODE
define OpenSemaphore  <OpenSemaphoreA>
endif

if (_WIN32_WINNT ge 0x0400) or (_WIN32_WINDOWS gt 0x0400)

CreateWaitableTimerA proto WINAPI :LPSECURITY_ATTRIBUTES, :BOOL, :LPCSTR
ifndef _UNICODE
define CreateWaitableTimer  <CreateWaitableTimerA>
endif

OpenWaitableTimerA proto WINAPI :DWORD, :BOOL, :LPCSTR
ifndef _UNICODE
define OpenWaitableTimer  <OpenWaitableTimerA>
endif

if (_WIN32_WINNT ge 0x0600)

CreateSemaphoreExA proto WINAPI :LPSECURITY_ATTRIBUTES, :LONG, :LONG, :LPCSTR, :DWORD, :DWORD
ifndef _UNICODE
define CreateSemaphoreEx  <CreateSemaphoreExA>
endif

CreateWaitableTimerExA proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCSTR, :DWORD, :DWORD
ifndef _UNICODE
define CreateWaitableTimerEx  <CreateWaitableTimerExA>
endif

endif
endif

CreateFileMappingA proto WINAPI :HANDLE, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :DWORD, :LPCSTR
ifndef _UNICODE
define CreateFileMapping  <CreateFileMappingA>
endif

if _WIN32_WINNT ge 0x0600

CreateFileMappingNumaA proto WINAPI :HANDLE, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :DWORD, :LPCSTR, :DWORD
ifndef _UNICODE
define CreateFileMappingNuma  <CreateFileMappingNumaA>
endif

endif

OpenFileMappingA proto WINAPI :DWORD, :BOOL, :LPCSTR
ifndef _UNICODE
define OpenFileMapping  <OpenFileMappingA>
endif

GetLogicalDriveStringsA proto WINAPI :DWORD, :LPSTR
ifndef _UNICODE
define GetLogicalDriveStrings  <GetLogicalDriveStringsA>
endif

if (_WIN32_WINNT ge 0x0602)
LoadPackagedLibrary proto WINAPI :LPCWSTR, :DWORD
endif

if (_WIN32_WINNT ge 0x0600)

define PROTECTION_LEVEL_WINTCB_LIGHT       0x00000000
define PROTECTION_LEVEL_WINDOWS            0x00000001
define PROTECTION_LEVEL_WINDOWS_LIGHT      0x00000002
define PROTECTION_LEVEL_ANTIMALWARE_LIGHT  0x00000003
define PROTECTION_LEVEL_LSA_LIGHT          0x00000004
define PROTECTION_LEVEL_WINTCB             0x00000005
define PROTECTION_LEVEL_CODEGEN_LIGHT      0x00000006
define PROTECTION_LEVEL_AUTHENTICODE       0x00000007
define PROTECTION_LEVEL_PPL_APP            0x00000008
define PROTECTION_LEVEL_SAME               0xFFFFFFFF
define PROTECTION_LEVEL_NONE               0xFFFFFFFE

endif

if (_WIN32_WINNT ge 0x0600)

define PROCESS_NAME_NATIVE     0x00000001

QueryFullProcessImageNameA proto WINAPI :HANDLE, :DWORD, :LPSTR, :PDWORD
QueryFullProcessImageNameW proto WINAPI :HANDLE, :DWORD, :LPWSTR, :PDWORD
ifdef _UNICODE
define QueryFullProcessImageName  <QueryFullProcessImageNameW>
else
define QueryFullProcessImageName  <QueryFullProcessImageNameA>
endif

endif

if (_WIN32_WINNT ge 0x0600)

define PROC_THREAD_ATTRIBUTE_NUMBER    0x0000FFFF
define PROC_THREAD_ATTRIBUTE_THREAD    0x00010000
define PROC_THREAD_ATTRIBUTE_INPUT     0x00020000
define PROC_THREAD_ATTRIBUTE_ADDITIVE  0x00040000

ifndef _USE_FULL_PROC_THREAD_ATTRIBUTE
.enum PROC_THREAD_ATTRIBUTE_NUM {
    ProcThreadAttributeParentProcess                = 0,
    ProcThreadAttributeHandleList                   = 2,
if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)
    ProcThreadAttributeGroupAffinity                = 3,
    ProcThreadAttributePreferredNode                = 4,
    ProcThreadAttributeIdealProcessor               = 5,
    ProcThreadAttributeUmsThread                    = 6,
    ProcThreadAttributeMitigationPolicy             = 7,
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
    ProcThreadAttributeSecurityCapabilities         = 9,
endif
    ProcThreadAttributeProtectionLevel              = 11,
if (_WIN32_WINNT ge _WIN32_WINNT_WINBLUE)
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WINTHRESHOLD)
    ProcThreadAttributeJobList                      = 13,
    ProcThreadAttributeChildProcessPolicy           = 14,
    ProcThreadAttributeAllApplicationPackagesPolicy = 15,
    ProcThreadAttributeWin32kFilter                 = 16,
endif
if (NTDDI_VERSION ge NTDDI_WIN10_RS1)
    ProcThreadAttributeSafeOpenPromptOriginClaim    = 17,
endif
if (NTDDI_VERSION ge NTDDI_WIN10_RS2)
    ProcThreadAttributeDesktopAppPolicy             = 18,
endif
if (NTDDI_VERSION ge NTDDI_WIN10_RS5)
    ProcThreadAttributePseudoConsole                = 22,
endif
if (NTDDI_VERSION ge NTDDI_WIN10_19H1)
endif
if (NTDDI_VERSION ge NTDDI_WIN10_MN)
    ProcThreadAttributeMitigationAuditPolicy        = 24,
endif
}
endif

if 0
ProcThreadAttributeValue macro Number, Thread, Input, Additive
    if Thread
     if Input
      if Additive
       exitm<(Number or PROC_THREAD_ATTRIBUTE_THREAD or PROC_THREAD_ATTRIBUTE_INPUT or PROC_THREAD_ATTRIBUTE_ADDITIVE)>
      else
       exitm<(Number or PROC_THREAD_ATTRIBUTE_THREAD or PROC_THREAD_ATTRIBUTE_INPUT)>
      endif
     elseif Additive
      exitm<(Number or PROC_THREAD_ATTRIBUTE_THREAD or PROC_THREAD_ATTRIBUTE_ADDITIVE)>
     else
      exitm<(Number or PROC_THREAD_ATTRIBUTE_THREAD)>
     endif
    elseif Input
     if Additive
      exitm<(Number or PROC_THREAD_ATTRIBUTE_INPUT or PROC_THREAD_ATTRIBUTE_ADDITIVE)>
     else
      exitm<(Number or PROC_THREAD_ATTRIBUTE_INPUT)>
     endif
    elseif Additive
     exitm<(Number or PROC_THREAD_ATTRIBUTE_ADDITIVE)>
    endif
    exitm<(Number)>
    endm
endif

define PROC_THREAD_ATTRIBUTE_PARENT_PROCESS (ProcThreadAttributeParentProcess or PROC_THREAD_ATTRIBUTE_INPUT)
define PROC_THREAD_ATTRIBUTE_HANDLE_LIST (ProcThreadAttributeHandleList or PROC_THREAD_ATTRIBUTE_INPUT)

endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)
define PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY (ProcThreadAttributeGroupAffinity or PROC_THREAD_ATTRIBUTE_THREAD or PROC_THREAD_ATTRIBUTE_INPUT)
define PROC_THREAD_ATTRIBUTE_PREFERRED_NODE (ProcThreadAttributePreferredNode or PROC_THREAD_ATTRIBUTE_INPUT)
define PROC_THREAD_ATTRIBUTE_IDEAL_PROCESSOR (ProcThreadAttributeIdealProcessor or PROC_THREAD_ATTRIBUTE_THREAD or PROC_THREAD_ATTRIBUTE_INPUT)
define PROC_THREAD_ATTRIBUTE_UMS_THREAD (ProcThreadAttributeUmsThread or PROC_THREAD_ATTRIBUTE_THREAD or PROC_THREAD_ATTRIBUTE_INPUT)
define PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY (ProcThreadAttributeMitigationPolicy or PROC_THREAD_ATTRIBUTE_INPUT)
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
define PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES (ProcThreadAttributeSecurityCapabilities or PROC_THREAD_ATTRIBUTE_INPUT)
endif

define PROC_THREAD_ATTRIBUTE_PROTECTION_LEVEL (ProcThreadAttributeProtectionLevel or PROC_THREAD_ATTRIBUTE_INPUT)

if (NTDDI_VERSION ge NTDDI_WIN10_RS5)
define PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE (ProcThreadAttributePseudoConsole or PROC_THREAD_ATTRIBUTE_INPUT)
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)
define PROCESS_CREATION_MITIGATION_POLICY_DEP_ENABLE            0x01
define PROCESS_CREATION_MITIGATION_POLICY_DEP_ATL_THUNK_ENABLE  0x02
define PROCESS_CREATION_MITIGATION_POLICY_SEHOP_ENABLE          0x04
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)

define PROCESS_CREATION_MITIGATION_POLICY_FORCE_RELOCATE_IMAGES_MASK                     (0x00000003 shl 8)
define PROCESS_CREATION_MITIGATION_POLICY_FORCE_RELOCATE_IMAGES_DEFER                    (0x00000000 shl 8)
define PROCESS_CREATION_MITIGATION_POLICY_FORCE_RELOCATE_IMAGES_ALWAYS_ON                (0x00000001 shl 8)
define PROCESS_CREATION_MITIGATION_POLICY_FORCE_RELOCATE_IMAGES_ALWAYS_OFF               (0x00000002 shl 8)
define PROCESS_CREATION_MITIGATION_POLICY_FORCE_RELOCATE_IMAGES_ALWAYS_ON_REQ_RELOCS     (0x00000003 shl 8)

define PROCESS_CREATION_MITIGATION_POLICY_HEAP_TERMINATE_MASK                            (0x00000003 shl 12)
define PROCESS_CREATION_MITIGATION_POLICY_HEAP_TERMINATE_DEFER                           (0x00000000 shl 12)
define PROCESS_CREATION_MITIGATION_POLICY_HEAP_TERMINATE_ALWAYS_ON                       (0x00000001 shl 12)
define PROCESS_CREATION_MITIGATION_POLICY_HEAP_TERMINATE_ALWAYS_OFF                      (0x00000002 shl 12)
define PROCESS_CREATION_MITIGATION_POLICY_HEAP_TERMINATE_RESERVED                        (0x00000003 shl 12)

define PROCESS_CREATION_MITIGATION_POLICY_BOTTOM_UP_ASLR_MASK                            (0x00000003 shl 16)
define PROCESS_CREATION_MITIGATION_POLICY_BOTTOM_UP_ASLR_DEFER                           (0x00000000 shl 16)
define PROCESS_CREATION_MITIGATION_POLICY_BOTTOM_UP_ASLR_ALWAYS_ON                       (0x00000001 shl 16)
define PROCESS_CREATION_MITIGATION_POLICY_BOTTOM_UP_ASLR_ALWAYS_OFF                      (0x00000002 shl 16)
define PROCESS_CREATION_MITIGATION_POLICY_BOTTOM_UP_ASLR_RESERVED                        (0x00000003 shl 16)

define PROCESS_CREATION_MITIGATION_POLICY_HIGH_ENTROPY_ASLR_MASK                         (0x00000003 shl 20)
define PROCESS_CREATION_MITIGATION_POLICY_HIGH_ENTROPY_ASLR_DEFER                        (0x00000000 shl 20)
define PROCESS_CREATION_MITIGATION_POLICY_HIGH_ENTROPY_ASLR_ALWAYS_ON                    (0x00000001 shl 20)
define PROCESS_CREATION_MITIGATION_POLICY_HIGH_ENTROPY_ASLR_ALWAYS_OFF                   (0x00000002 shl 20)
define PROCESS_CREATION_MITIGATION_POLICY_HIGH_ENTROPY_ASLR_RESERVED                     (0x00000003 shl 20)

define PROCESS_CREATION_MITIGATION_POLICY_STRICT_HANDLE_CHECKS_MASK                      (0x00000003 shl 24)
define PROCESS_CREATION_MITIGATION_POLICY_STRICT_HANDLE_CHECKS_DEFER                     (0x00000000 shl 24)
define PROCESS_CREATION_MITIGATION_POLICY_STRICT_HANDLE_CHECKS_ALWAYS_ON                 (0x00000001 shl 24)
define PROCESS_CREATION_MITIGATION_POLICY_STRICT_HANDLE_CHECKS_ALWAYS_OFF                (0x00000002 shl 24)
define PROCESS_CREATION_MITIGATION_POLICY_STRICT_HANDLE_CHECKS_RESERVED                  (0x00000003 shl 24)

define PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_MASK                (0x00000003 shl 28)
define PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_DEFER               (0x00000000 shl 28)
define PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_ALWAYS_ON           (0x00000001 shl 28)
define PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_ALWAYS_OFF          (0x00000002 shl 28)
define PROCESS_CREATION_MITIGATION_POLICY_WIN32K_SYSTEM_CALL_DISABLE_RESERVED            (0x00000003 shl 28)

define PROCESS_CREATION_MITIGATION_POLICY_EXTENSION_POINT_DISABLE_MASK                   (0x00000003 shl 32)
define PROCESS_CREATION_MITIGATION_POLICY_EXTENSION_POINT_DISABLE_DEFER                  (0x00000000 shl 32)
define PROCESS_CREATION_MITIGATION_POLICY_EXTENSION_POINT_DISABLE_ALWAYS_ON              (0x00000001 shl 32)
define PROCESS_CREATION_MITIGATION_POLICY_EXTENSION_POINT_DISABLE_ALWAYS_OFF             (0x00000002 shl 32)
define PROCESS_CREATION_MITIGATION_POLICY_EXTENSION_POINT_DISABLE_RESERVED               (0x00000003 shl 32)

if (_WIN32_WINNT ge _WIN32_WINNT_WINBLUE)

define PROCESS_CREATION_MITIGATION_POLICY_PROHIBIT_DYNAMIC_CODE_MASK                     (0x00000003 shl 36)
define PROCESS_CREATION_MITIGATION_POLICY_PROHIBIT_DYNAMIC_CODE_DEFER                    (0x00000000 shl 36)
define PROCESS_CREATION_MITIGATION_POLICY_PROHIBIT_DYNAMIC_CODE_ALWAYS_ON                (0x00000001 shl 36)
define PROCESS_CREATION_MITIGATION_POLICY_PROHIBIT_DYNAMIC_CODE_ALWAYS_OFF               (0x00000002 shl 36)
define PROCESS_CREATION_MITIGATION_POLICY_PROHIBIT_DYNAMIC_CODE_ALWAYS_ON_ALLOW_OPT_OUT  (0x00000003 shl 36)

define PROCESS_CREATION_MITIGATION_POLICY_CONTROL_FLOW_GUARD_MASK                        (0x00000003 shl 40)
define PROCESS_CREATION_MITIGATION_POLICY_CONTROL_FLOW_GUARD_DEFER                       (0x00000000 shl 40)
define PROCESS_CREATION_MITIGATION_POLICY_CONTROL_FLOW_GUARD_ALWAYS_ON                   (0x00000001 shl 40)
define PROCESS_CREATION_MITIGATION_POLICY_CONTROL_FLOW_GUARD_ALWAYS_OFF                  (0x00000002 shl 40)
define PROCESS_CREATION_MITIGATION_POLICY_CONTROL_FLOW_GUARD_EXPORT_SUPPRESSION          (0x00000003 shl 40)

define PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_MASK              (0x00000003 shl 44)
define PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_DEFER             (0x00000000 shl 44)
define PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_ALWAYS_ON         (0x00000001 shl 44)
define PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_ALWAYS_OFF        (0x00000002 shl 44)
define PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_ALLOW_STORE       (0x00000003 shl 44)

if (_WIN32_WINNT ge _WIN32_WINNT_WINTHRESHOLD)

define PROCESS_CREATION_MITIGATION_POLICY_FONT_DISABLE_MASK                              (0x00000003 shl 48)
define PROCESS_CREATION_MITIGATION_POLICY_FONT_DISABLE_DEFER                             (0x00000000 shl 48)
define PROCESS_CREATION_MITIGATION_POLICY_FONT_DISABLE_ALWAYS_ON                         (0x00000001 shl 48)
define PROCESS_CREATION_MITIGATION_POLICY_FONT_DISABLE_ALWAYS_OFF                        (0x00000002 shl 48)
define PROCESS_CREATION_MITIGATION_POLICY_AUDIT_NONSYSTEM_FONTS                          (0x00000003 shl 48)

define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_REMOTE_MASK                      (0x00000003 shl 52)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_REMOTE_DEFER                     (0x00000000 shl 52)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_REMOTE_ALWAYS_ON                 (0x00000001 shl 52)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_REMOTE_ALWAYS_OFF                (0x00000002 shl 52)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_REMOTE_RESERVED                  (0x00000003 shl 52)

define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_LOW_LABEL_MASK                   (0x00000003 shl 56)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_LOW_LABEL_DEFER                  (0x00000000 shl 56)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_LOW_LABEL_ALWAYS_ON              (0x00000001 shl 56)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_LOW_LABEL_ALWAYS_OFF             (0x00000002 shl 56)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_LOW_LABEL_RESERVED               (0x00000003 shl 56)

define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_PREFER_SYSTEM32_MASK                (0x00000003 shl 60)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_PREFER_SYSTEM32_DEFER               (0x00000000 shl 60)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_PREFER_SYSTEM32_ALWAYS_ON           (0x00000001 shl 60)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_PREFER_SYSTEM32_ALWAYS_OFF          (0x00000002 shl 60)
define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_PREFER_SYSTEM32_RESERVED            (0x00000003 shl 60)

define PROCESS_CREATION_MITIGATION_POLICY2_LOADER_INTEGRITY_CONTINUITY_MASK              (0x00000003 shl 4)
define PROCESS_CREATION_MITIGATION_POLICY2_LOADER_INTEGRITY_CONTINUITY_DEFER             (0x00000000 shl 4)
define PROCESS_CREATION_MITIGATION_POLICY2_LOADER_INTEGRITY_CONTINUITY_ALWAYS_ON         (0x00000001 shl 4)
define PROCESS_CREATION_MITIGATION_POLICY2_LOADER_INTEGRITY_CONTINUITY_ALWAYS_OFF        (0x00000002 shl 4)
define PROCESS_CREATION_MITIGATION_POLICY2_LOADER_INTEGRITY_CONTINUITY_AUDIT             (0x00000003 shl 4)

define PROCESS_CREATION_MITIGATION_POLICY2_STRICT_CONTROL_FLOW_GUARD_MASK                (0x00000003 shl 8)
define PROCESS_CREATION_MITIGATION_POLICY2_STRICT_CONTROL_FLOW_GUARD_DEFER               (0x00000000 shl 8)
define PROCESS_CREATION_MITIGATION_POLICY2_STRICT_CONTROL_FLOW_GUARD_ALWAYS_ON           (0x00000001 shl 8)
define PROCESS_CREATION_MITIGATION_POLICY2_STRICT_CONTROL_FLOW_GUARD_ALWAYS_OFF          (0x00000002 shl 8)
define PROCESS_CREATION_MITIGATION_POLICY2_STRICT_CONTROL_FLOW_GUARD_RESERVED            (0x00000003 shl 8)

define PROCESS_CREATION_MITIGATION_POLICY2_MODULE_TAMPERING_PROTECTION_MASK              (0x00000003 shl 12)
define PROCESS_CREATION_MITIGATION_POLICY2_MODULE_TAMPERING_PROTECTION_DEFER             (0x00000000 shl 12)
define PROCESS_CREATION_MITIGATION_POLICY2_MODULE_TAMPERING_PROTECTION_ALWAYS_ON         (0x00000001 shl 12)
define PROCESS_CREATION_MITIGATION_POLICY2_MODULE_TAMPERING_PROTECTION_ALWAYS_OFF        (0x00000002 shl 12)
define PROCESS_CREATION_MITIGATION_POLICY2_MODULE_TAMPERING_PROTECTION_NOINHERIT         (0x00000003 shl 12)

define PROCESS_CREATION_MITIGATION_POLICY2_RESTRICT_INDIRECT_BRANCH_PREDICTION_MASK        (0x00000003 shl 16)
define PROCESS_CREATION_MITIGATION_POLICY2_RESTRICT_INDIRECT_BRANCH_PREDICTION_DEFER       (0x00000000 shl 16)
define PROCESS_CREATION_MITIGATION_POLICY2_RESTRICT_INDIRECT_BRANCH_PREDICTION_ALWAYS_ON   (0x00000001 shl 16)
define PROCESS_CREATION_MITIGATION_POLICY2_RESTRICT_INDIRECT_BRANCH_PREDICTION_ALWAYS_OFF  (0x00000002 shl 16)
define PROCESS_CREATION_MITIGATION_POLICY2_RESTRICT_INDIRECT_BRANCH_PREDICTION_RESERVED    (0x00000003 shl 16)

define PROCESS_CREATION_MITIGATION_POLICY2_ALLOW_DOWNGRADE_DYNAMIC_CODE_POLICY_MASK       (0x00000003 shl 20)
define PROCESS_CREATION_MITIGATION_POLICY2_ALLOW_DOWNGRADE_DYNAMIC_CODE_POLICY_DEFER      (0x00000000 shl 20)
define PROCESS_CREATION_MITIGATION_POLICY2_ALLOW_DOWNGRADE_DYNAMIC_CODE_POLICY_ALWAYS_ON  (0x00000001 shl 20)
define PROCESS_CREATION_MITIGATION_POLICY2_ALLOW_DOWNGRADE_DYNAMIC_CODE_POLICY_ALWAYS_OFF (0x00000002 shl 20)
define PROCESS_CREATION_MITIGATION_POLICY2_ALLOW_DOWNGRADE_DYNAMIC_CODE_POLICY_RESERVED   (0x00000003 shl 20)

define PROCESS_CREATION_MITIGATION_POLICY2_SPECULATIVE_STORE_BYPASS_DISABLE_MASK          (0x00000003 shl 24)
define PROCESS_CREATION_MITIGATION_POLICY2_SPECULATIVE_STORE_BYPASS_DISABLE_DEFER         (0x00000000 shl 24)
define PROCESS_CREATION_MITIGATION_POLICY2_SPECULATIVE_STORE_BYPASS_DISABLE_ALWAYS_ON     (0x00000001 shl 24)
define PROCESS_CREATION_MITIGATION_POLICY2_SPECULATIVE_STORE_BYPASS_DISABLE_ALWAYS_OFF    (0x00000002 shl 24)
define PROCESS_CREATION_MITIGATION_POLICY2_SPECULATIVE_STORE_BYPASS_DISABLE_RESERVED      (0x00000003 shl 24)

define PROCESS_CREATION_MITIGATION_POLICY2_CET_USER_SHADOW_STACKS_MASK                    (0x00000003 shl 28)
define PROCESS_CREATION_MITIGATION_POLICY2_CET_USER_SHADOW_STACKS_DEFER                   (0x00000000 shl 28)
define PROCESS_CREATION_MITIGATION_POLICY2_CET_USER_SHADOW_STACKS_ALWAYS_ON               (0x00000001 shl 28)
define PROCESS_CREATION_MITIGATION_POLICY2_CET_USER_SHADOW_STACKS_ALWAYS_OFF              (0x00000002 shl 28)
define PROCESS_CREATION_MITIGATION_POLICY2_CET_USER_SHADOW_STACKS_STRICT_MODE             (0x00000003 shl 28)

define PROCESS_CREATION_MITIGATION_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_MASK         (0x00000003 shl 32)
define PROCESS_CREATION_MITIGATION_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_DEFER        (0x00000000 shl 32)
define PROCESS_CREATION_MITIGATION_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_ALWAYS_ON    (0x00000001 shl 32)
define PROCESS_CREATION_MITIGATION_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_ALWAYS_OFF   (0x00000002 shl 32)
define PROCESS_CREATION_MITIGATION_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_RELAXED_MODE (0x00000003 shl 32)

define PROCESS_CREATION_MITIGATION_POLICY2_BLOCK_NON_CET_BINARIES_MASK                    (0x00000003 shl 36)
define PROCESS_CREATION_MITIGATION_POLICY2_BLOCK_NON_CET_BINARIES_DEFER                   (0x00000000 shl 36)
define PROCESS_CREATION_MITIGATION_POLICY2_BLOCK_NON_CET_BINARIES_ALWAYS_ON               (0x00000001 shl 36)
define PROCESS_CREATION_MITIGATION_POLICY2_BLOCK_NON_CET_BINARIES_ALWAYS_OFF              (0x00000002 shl 36)
define PROCESS_CREATION_MITIGATION_POLICY2_BLOCK_NON_CET_BINARIES_NON_EHCONT              (0x00000003 shl 36)

define PROCESS_CREATION_MITIGATION_POLICY2_CET_DYNAMIC_APIS_OUT_OF_PROC_ONLY_MASK         (0x00000003 shl 48)
define PROCESS_CREATION_MITIGATION_POLICY2_CET_DYNAMIC_APIS_OUT_OF_PROC_ONLY_DEFER        (0x00000000 shl 48)
define PROCESS_CREATION_MITIGATION_POLICY2_CET_DYNAMIC_APIS_OUT_OF_PROC_ONLY_ALWAYS_ON    (0x00000001 shl 48)
define PROCESS_CREATION_MITIGATION_POLICY2_CET_DYNAMIC_APIS_OUT_OF_PROC_ONLY_ALWAYS_OFF   (0x00000002 shl 48)
define PROCESS_CREATION_MITIGATION_POLICY2_CET_DYNAMIC_APIS_OUT_OF_PROC_ONLY_RESERVED     (0x00000003 shl 48)

endif
endif
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINTHRESHOLD)
define PROC_THREAD_ATTRIBUTE_JOB_LIST (ProcThreadAttributeJobList or PROC_THREAD_ATTRIBUTE_INPUT)
define PROCESS_CREATION_CHILD_PROCESS_RESTRICTED                                         0x01
define PROCESS_CREATION_CHILD_PROCESS_OVERRIDE                                           0x02
define PROCESS_CREATION_CHILD_PROCESS_RESTRICTED_UNLESS_SECURE                           0x04
define PROC_THREAD_ATTRIBUTE_CHILD_PROCESS_POLICY (ProcThreadAttributeChildProcessPolicy or PROC_THREAD_ATTRIBUTE_INPUT)
define PROCESS_CREATION_ALL_APPLICATION_PACKAGES_OPT_OUT                                 0x01
define PROC_THREAD_ATTRIBUTE_ALL_APPLICATION_PACKAGES_POLICY (ProcThreadAttributeAllApplicationPackagesPolicy or PROC_THREAD_ATTRIBUTE_INPUT)
define PROC_THREAD_ATTRIBUTE_WIN32K_FILTER (ProcThreadAttributeWin32kFilter or PROC_THREAD_ATTRIBUTE_INPUT)
endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS2)
define PROCESS_CREATION_DESKTOP_APP_BREAKAWAY_ENABLE_PROCESS_TREE                        0x01
define PROCESS_CREATION_DESKTOP_APP_BREAKAWAY_DISABLE_PROCESS_TREE                       0x02
define PROCESS_CREATION_DESKTOP_APP_BREAKAWAY_OVERRIDE                                   0x04
define PROC_THREAD_ATTRIBUTE_DESKTOP_APP_POLICY (ProcThreadAttributeDesktopAppPolicy or PROC_THREAD_ATTRIBUTE_INPUT)
endif

if (NTDDI_VERSION ge NTDDI_WIN10_MN)

define PROC_THREAD_ATTRIBUTE_MITIGATION_AUDIT_POLICY (ProcThreadAttributeMitigationAuditPolicy or PROC_THREAD_ATTRIBUTE_INPUT)

define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_CET_USER_SHADOW_STACKS_MASK                    (0x00000003 shl 28)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_CET_USER_SHADOW_STACKS_DEFER                   (0x00000000 shl 28)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_CET_USER_SHADOW_STACKS_ALWAYS_ON               (0x00000001 shl 28)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_CET_USER_SHADOW_STACKS_ALWAYS_OFF              (0x00000002 shl 28)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_CET_USER_SHADOW_STACKS_RESERVED                (0x00000003 shl 28)

define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_MASK        (0x00000003 shl 32)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_DEFER       (0x00000000 shl 32)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_ALWAYS_ON   (0x00000001 shl 32)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_ALWAYS_OFF  (0x00000002 shl 32)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_USER_CET_SET_CONTEXT_IP_VALIDATION_RESERVED    (0x00000003 shl 32)

define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_BLOCK_NON_CET_BINARIES_MASK                    (0x00000003 shl 36)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_BLOCK_NON_CET_BINARIES_DEFER                   (0x00000000 shl 36)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_BLOCK_NON_CET_BINARIES_ALWAYS_ON               (0x00000001 shl 36)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_BLOCK_NON_CET_BINARIES_ALWAYS_OFF              (0x00000002 shl 36)
define PROCESS_CREATION_MITIGATION_AUDIT_POLICY2_BLOCK_NON_CET_BINARIES_RESERVED                (0x00000003 shl 36)

endif

GetStartupInfoA proto WINAPI :LPSTARTUPINFOA
ifndef _UNICODE
define GetStartupInfo  <GetStartupInfoA>
endif

GetFirmwareEnvironmentVariableA proto WINAPI :LPCSTR, :LPCSTR, :PVOID, :DWORD
GetFirmwareEnvironmentVariableW proto WINAPI :LPCWSTR, :LPCWSTR, :PVOID, :DWORD
ifdef _UNICODE
define GetFirmwareEnvironmentVariable  <GetFirmwareEnvironmentVariableW>
else
define GetFirmwareEnvironmentVariable  <GetFirmwareEnvironmentVariableA>
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)

GetFirmwareEnvironmentVariableExA proto WINAPI :LPCSTR, :LPCSTR, :PVOID, :DWORD, :PDWORD
GetFirmwareEnvironmentVariableExW proto WINAPI :LPCWSTR, :LPCWSTR, :PVOID, :DWORD, :PDWORD
ifdef _UNICODE
define GetFirmwareEnvironmentVariableEx  <GetFirmwareEnvironmentVariableExW>
else
define GetFirmwareEnvironmentVariableEx  <GetFirmwareEnvironmentVariableExA>
endif

endif

SetFirmwareEnvironmentVariableA proto WINAPI :LPCSTR, :LPCSTR, :PVOID, :DWORD
SetFirmwareEnvironmentVariableW proto WINAPI :LPCWSTR, :LPCWSTR, :PVOID, :DWORD
ifdef _UNICODE
define SetFirmwareEnvironmentVariable  <SetFirmwareEnvironmentVariableW>
else
define SetFirmwareEnvironmentVariable  <SetFirmwareEnvironmentVariableA>
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)

SetFirmwareEnvironmentVariableExA proto WINAPI :LPCSTR, :LPCSTR, :PVOID, :DWORD, :DWORD
SetFirmwareEnvironmentVariableExW proto WINAPI :LPCWSTR, :LPCWSTR, :PVOID, :DWORD, :DWORD
ifdef _UNICODE
define SetFirmwareEnvironmentVariableEx  <SetFirmwareEnvironmentVariableExW>
else
define SetFirmwareEnvironmentVariableEx  <SetFirmwareEnvironmentVariableExA>
endif

endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
GetFirmwareType proto WINAPI :PFIRMWARE_TYPE
IsNativeVhdBoot proto WINAPI :PBOOL
endif

FindResourceA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR
ifndef _UNICODE
define FindResource  <FindResourceA>
endif

FindResourceExA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR, :WORD
ifndef _UNICODE
define FindResourceEx  <FindResourceExA>
endif

EnumResourceTypesA proto WINAPI :HMODULE, :ENUMRESTYPEPROCA, :LONG_PTR
EnumResourceTypesW proto WINAPI :HMODULE, :ENUMRESTYPEPROCW, :LONG_PTR
ifdef _UNICODE
define EnumResourceTypes  <EnumResourceTypesW>
else
define EnumResourceTypes  <EnumResourceTypesA>
endif

EnumResourceNamesA proto WINAPI :HMODULE, :LPCSTR, :ENUMRESNAMEPROCA, :LONG_PTR
ifndef _UNICODE
define EnumResourceNames  <EnumResourceNamesA>
endif

EnumResourceLanguagesA proto WINAPI :HMODULE, :LPCSTR, :LPCSTR, :ENUMRESLANGPROCA, :LONG_PTR
EnumResourceLanguagesW proto WINAPI :HMODULE, :LPCWSTR, :LPCWSTR, :ENUMRESLANGPROCW, :LONG_PTR
ifdef _UNICODE
define EnumResourceLanguages  <EnumResourceLanguagesW>
else
define EnumResourceLanguages  <EnumResourceLanguagesA>
endif

BeginUpdateResourceA proto WINAPI :LPCSTR, :BOOL
BeginUpdateResourceW proto WINAPI :LPCWSTR, :BOOL
ifdef _UNICODE
define BeginUpdateResource  <BeginUpdateResourceW>
else
define BeginUpdateResource  <BeginUpdateResourceA>
endif

UpdateResourceA proto WINAPI :HANDLE, :LPCSTR, :LPCSTR, :WORD, :LPVOID, :DWORD
UpdateResourceW proto WINAPI :HANDLE, :LPCWSTR, :LPCWSTR, :WORD, :LPVOID, :DWORD
ifdef _UNICODE
define UpdateResource  <UpdateResourceW>
else
define UpdateResource  <UpdateResourceA>
endif

EndUpdateResourceA proto WINAPI :HANDLE, :BOOL
EndUpdateResourceW proto WINAPI :HANDLE, :BOOL
ifdef _UNICODE
define EndUpdateResource  <EndUpdateResourceW>
else
define EndUpdateResource  <EndUpdateResourceA>
endif

define ATOM_FLAG_GLOBAL 0x2

GlobalAddAtomA proto WINAPI :LPCSTR
GlobalAddAtomW proto WINAPI :LPCWSTR
ifdef _UNICODE
define GlobalAddAtom  <GlobalAddAtomW>
else
define GlobalAddAtom  <GlobalAddAtomA>
endif

GlobalAddAtomExA proto WINAPI :LPCSTR, :DWORD
GlobalAddAtomExW proto WINAPI :LPCWSTR, :DWORD
ifdef _UNICODE
define GlobalAddAtomEx  <GlobalAddAtomExW>
else
define GlobalAddAtomEx  <GlobalAddAtomExA>
endif

GlobalFindAtomA proto WINAPI :LPCSTR
GlobalFindAtomW proto WINAPI :LPCWSTR
ifdef _UNICODE
define GlobalFindAtom  <GlobalFindAtomW>
else
define GlobalFindAtom  <GlobalFindAtomA>
endif

GlobalGetAtomNameA proto WINAPI :ATOM, :LPSTR, :sdword
GlobalGetAtomNameW proto WINAPI :ATOM, :LPWSTR, :sdword
ifdef _UNICODE
define GlobalGetAtomName  <GlobalGetAtomNameW>
else
define GlobalGetAtomName  <GlobalGetAtomNameA>
endif

AddAtomA proto WINAPI :LPCSTR
AddAtomW proto WINAPI :LPCWSTR
ifdef _UNICODE
define AddAtom  <AddAtomW>
else
define AddAtom  <AddAtomA>
endif

FindAtomA proto WINAPI :LPCSTR
FindAtomW proto WINAPI :LPCWSTR
ifdef _UNICODE
define FindAtom  <FindAtomW>
else
define FindAtom  <FindAtomA>
endif

GetAtomNameA proto WINAPI :ATOM, :LPSTR, :sdword
GetAtomNameW proto WINAPI :ATOM, :LPWSTR, :sdword
ifdef _UNICODE
define GetAtomName  <GetAtomNameW>
else
define GetAtomName  <GetAtomNameA>
endif

GetProfileIntA proto WINAPI :LPCSTR, :LPCSTR, :sdword
GetProfileIntW proto WINAPI :LPCWSTR, :LPCWSTR, :sdword
ifdef _UNICODE
define GetProfileInt  <GetProfileIntW>
else
define GetProfileInt  <GetProfileIntA>
endif

GetProfileStringA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :LPSTR, :DWORD
GetProfileStringW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPWSTR, :DWORD
ifdef _UNICODE
define GetProfileString  <GetProfileStringW>
else
define GetProfileString  <GetProfileStringA>
endif

WriteProfileStringA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR
WriteProfileStringW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define WriteProfileString  <WriteProfileStringW>
else
define WriteProfileString  <WriteProfileStringA>
endif

GetProfileSectionA proto WINAPI :LPCSTR, :LPSTR, :DWORD
GetProfileSectionW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD
ifdef _UNICODE
define GetProfileSection  <GetProfileSectionW>
else
define GetProfileSection  <GetProfileSectionA>
endif

WriteProfileSectionA proto WINAPI :LPCSTR, :LPCSTR
WriteProfileSectionW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define WriteProfileSection  <WriteProfileSectionW>
else
define WriteProfileSection  <WriteProfileSectionA>
endif

GetPrivateProfileIntA proto WINAPI :LPCSTR, :LPCSTR, :sdword, :LPCSTR
GetPrivateProfileIntW proto WINAPI :LPCWSTR, :LPCWSTR, :sdword, :LPCWSTR
ifdef _UNICODE
define GetPrivateProfileInt  <GetPrivateProfileIntW>
else
define GetPrivateProfileInt  <GetPrivateProfileIntA>
endif

GetPrivateProfileStringA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :LPSTR, :DWORD, :LPCSTR
GetPrivateProfileStringW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPWSTR, :DWORD, :LPCWSTR
ifdef _UNICODE
define GetPrivateProfileString  <GetPrivateProfileStringW>
else
define GetPrivateProfileString  <GetPrivateProfileStringA>
endif

WritePrivateProfileStringA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :LPCSTR
WritePrivateProfileStringW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define WritePrivateProfileString  <WritePrivateProfileStringW>
else
define WritePrivateProfileString  <WritePrivateProfileStringA>
endif

GetPrivateProfileSectionA proto WINAPI :LPCSTR, :LPSTR, :DWORD, :LPCSTR
GetPrivateProfileSectionW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD, :LPCWSTR
ifdef _UNICODE
define GetPrivateProfileSection  <GetPrivateProfileSectionW>
else
define GetPrivateProfileSection  <GetPrivateProfileSectionA>
endif

WritePrivateProfileSectionA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR
WritePrivateProfileSectionW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define WritePrivateProfileSection  <WritePrivateProfileSectionW>
else
define WritePrivateProfileSection  <WritePrivateProfileSectionA>
endif

GetPrivateProfileSectionNamesA proto WINAPI :LPSTR, :DWORD, :LPCSTR
GetPrivateProfileSectionNamesW proto WINAPI :LPWSTR, :DWORD, :LPCWSTR
ifdef _UNICODE
define GetPrivateProfileSectionNames  <GetPrivateProfileSectionNamesW>
else
define GetPrivateProfileSectionNames  <GetPrivateProfileSectionNamesA>
endif

GetPrivateProfileStructA proto WINAPI :LPCSTR, :LPCSTR, :LPVOID, :UINT, :LPCSTR
GetPrivateProfileStructW proto WINAPI :LPCWSTR, :LPCWSTR, :LPVOID, :UINT, :LPCWSTR
ifdef _UNICODE
define GetPrivateProfileStruct  <GetPrivateProfileStructW>
else
define GetPrivateProfileStruct  <GetPrivateProfileStructA>
endif

WritePrivateProfileStructA proto WINAPI :LPCSTR, :LPCSTR, :LPVOID, :UINT, :LPCSTR
WritePrivateProfileStructW proto WINAPI :LPCWSTR, :LPCWSTR, :LPVOID, :UINT, :LPCWSTR
ifdef _UNICODE
define WritePrivateProfileStruct  <WritePrivateProfileStructW>
else
define WritePrivateProfileStruct  <WritePrivateProfileStructA>
endif

ifndef RC_INVOKED
if _WIN32_WINNT ge 0x0501 or defined(WINBASE_DECLARE_GET_SYSTEM_WOW64_DIRECTORY)

Wow64EnableWow64FsRedirection proto WINAPI :BOOLEAN

CALLBACK(PGET_SYSTEM_WOW64_DIRECTORY_A, :LPSTR, :UINT)
CALLBACK(PGET_SYSTEM_WOW64_DIRECTORY_W, :LPWSTR, :UINT)

define GET_SYSTEM_WOW64_DIRECTORY_NAME_A_A  <"GetSystemWow64DirectoryA">
define GET_SYSTEM_WOW64_DIRECTORY_NAME_A_W  <L"GetSystemWow64DirectoryA">
define GET_SYSTEM_WOW64_DIRECTORY_NAME_A_T  <"GetSystemWow64DirectoryA">
define GET_SYSTEM_WOW64_DIRECTORY_NAME_W_A  <"GetSystemWow64DirectoryW">
define GET_SYSTEM_WOW64_DIRECTORY_NAME_W_W  <L"GetSystemWow64DirectoryW">
define GET_SYSTEM_WOW64_DIRECTORY_NAME_W_T  <"GetSystemWow64DirectoryW">

ifdef _UNICODE
define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_A <GET_SYSTEM_WOW64_DIRECTORY_NAME_W_A>
define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_W <GET_SYSTEM_WOW64_DIRECTORY_NAME_W_W>
define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_T <GET_SYSTEM_WOW64_DIRECTORY_NAME_W_T>
else
define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_A <GET_SYSTEM_WOW64_DIRECTORY_NAME_A_A>
define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_W <GET_SYSTEM_WOW64_DIRECTORY_NAME_A_W>
define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_T <GET_SYSTEM_WOW64_DIRECTORY_NAME_A_T>
endif

endif
endif

if _WIN32_WINNT ge 0x0502

SetDllDirectoryA proto WINAPI :LPCSTR
SetDllDirectoryW proto WINAPI :LPCWSTR
ifdef _UNICODE
define SetDllDirectory  <SetDllDirectoryW>
else
define SetDllDirectory  <SetDllDirectoryA>
endif
endif

if _WIN32_WINNT ge 0x0502
GetDllDirectoryA proto WINAPI :DWORD, :LPSTR
GetDllDirectoryW proto WINAPI :DWORD, :LPWSTR
ifdef _UNICODE
define GetDllDirectory  <GetDllDirectoryW>
else
define GetDllDirectory  <GetDllDirectoryA>
endif

endif

define BASE_SEARCH_PATH_ENABLE_SAFE_SEARCHMODE 0x1
define BASE_SEARCH_PATH_DISABLE_SAFE_SEARCHMODE 0x10000
define BASE_SEARCH_PATH_PERMANENT 0x8000
define BASE_SEARCH_PATH_INVALID_FLAGS not 0x18001

SetSearchPathMode proto WINAPI :DWORD

CreateDirectoryExA proto WINAPI :LPCSTR, :LPCSTR, :LPSECURITY_ATTRIBUTES
CreateDirectoryExW proto WINAPI :LPCWSTR, :LPCWSTR, :LPSECURITY_ATTRIBUTES
ifdef _UNICODE
define CreateDirectoryEx  <CreateDirectoryExW>
else
define CreateDirectoryEx  <CreateDirectoryExA>
endif

if _WIN32_WINNT ge 0x0600

CreateDirectoryTransactedA proto WINAPI :LPCSTR, :LPCSTR, :LPSECURITY_ATTRIBUTES, :HANDLE
CreateDirectoryTransactedW proto WINAPI :LPCWSTR, :LPCWSTR, :LPSECURITY_ATTRIBUTES, :HANDLE
ifdef _UNICODE
define CreateDirectoryTransacted  <CreateDirectoryTransactedW>
else
define CreateDirectoryTransacted  <CreateDirectoryTransactedA>
endif

RemoveDirectoryTransactedA proto WINAPI :LPCSTR, :HANDLE
RemoveDirectoryTransactedW proto WINAPI :LPCWSTR, :HANDLE
ifdef _UNICODE
define RemoveDirectoryTransacted  <RemoveDirectoryTransactedW>
else
define RemoveDirectoryTransacted  <RemoveDirectoryTransactedA>
endif

GetFullPathNameTransactedA proto WINAPI :LPCSTR, :DWORD, :LPSTR, :ptr, :HANDLE
GetFullPathNameTransactedW proto WINAPI :LPCWSTR, :DWORD, :LPWSTR, :ptr, :HANDLE
ifdef _UNICODE
define GetFullPathNameTransacted  <GetFullPathNameTransactedW>
else
define GetFullPathNameTransacted  <GetFullPathNameTransactedA>
endif

endif

define DDD_RAW_TARGET_PATH         0x00000001
define DDD_REMOVE_DEFINITION       0x00000002
define DDD_EXACT_MATCH_ON_REMOVE   0x00000004
define DDD_NO_BROADCAST_SYSTEM     0x00000008
define DDD_LUID_BROADCAST_DRIVE    0x00000010

DefineDosDeviceA proto WINAPI :DWORD, :LPCSTR, :LPCSTR
ifndef _UNICODE
define DefineDosDevice  <DefineDosDeviceA>
endif

QueryDosDeviceA proto WINAPI :LPCSTR, :LPSTR, :DWORD
ifndef _UNICODE
define QueryDosDevice  <QueryDosDeviceA>
endif

define EXPAND_LOCAL_DRIVES

if _WIN32_WINNT ge 0x0600

CreateFileTransactedA proto WINAPI :LPCSTR, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :HANDLE, :HANDLE, :PUSHORT, :PVOID
CreateFileTransactedW proto WINAPI :LPCWSTR, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :HANDLE, :HANDLE, :PUSHORT, :PVOID
ifdef _UNICODE
define CreateFileTransacted  <CreateFileTransactedW>
else
define CreateFileTransacted  <CreateFileTransactedA>
endif

endif

if _WIN32_WINNT ge 0x0502
ReOpenFile proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD
endif

if _WIN32_WINNT ge 0x0600

SetFileAttributesTransactedA proto WINAPI :LPCSTR, :DWORD, :HANDLE
SetFileAttributesTransactedW proto WINAPI :LPCWSTR, :DWORD, :HANDLE
ifdef _UNICODE
define SetFileAttributesTransacted  <SetFileAttributesTransactedW>
else
define SetFileAttributesTransacted  <SetFileAttributesTransactedA>
endif

GetFileAttributesTransactedA proto WINAPI :LPCSTR, :GET_FILEEX_INFO_LEVELS, :LPVOID, :HANDLE
GetFileAttributesTransactedW proto WINAPI :LPCWSTR, :GET_FILEEX_INFO_LEVELS, :LPVOID, :HANDLE
ifdef _UNICODE
define GetFileAttributesTransacted  <GetFileAttributesTransactedW>
else
define GetFileAttributesTransacted  <GetFileAttributesTransactedA>
endif

GetCompressedFileSizeTransactedA proto WINAPI :LPCSTR, :LPDWORD, :HANDLE
GetCompressedFileSizeTransactedW proto WINAPI :LPCWSTR, :LPDWORD, :HANDLE
ifdef _UNICODE
define GetCompressedFileSizeTransacted  <GetCompressedFileSizeTransactedW>
else
define GetCompressedFileSizeTransacted  <GetCompressedFileSizeTransactedA>
endif

DeleteFileTransactedA proto WINAPI :LPCSTR, :HANDLE
DeleteFileTransactedW proto WINAPI :LPCWSTR, :HANDLE
ifdef _UNICODE
define DeleteFileTransacted  <DeleteFileTransactedW>
else
define DeleteFileTransacted  <DeleteFileTransactedA>
endif

endif

if _WIN32_WINNT ge 0x0501
CheckNameLegalDOS8Dot3A proto WINAPI :LPCSTR, :LPSTR, :DWORD, :PBOOL, :PBOOL
CheckNameLegalDOS8Dot3W proto WINAPI :LPCWSTR, :LPSTR, :DWORD, :PBOOL, :PBOOL
ifdef _UNICODE
define CheckNameLegalDOS8Dot3  <CheckNameLegalDOS8Dot3W>
else
define CheckNameLegalDOS8Dot3  <CheckNameLegalDOS8Dot3A>
endif
endif

if(_WIN32_WINNT ge 0x0400)
if _WIN32_WINNT ge 0x0600
FindFirstFileTransactedA proto WINAPI :LPCSTR, :FINDEX_INFO_LEVELS, :LPVOID, :FINDEX_SEARCH_OPS, :LPVOID, :DWORD, :HANDLE
FindFirstFileTransactedW proto WINAPI :LPCWSTR, :FINDEX_INFO_LEVELS, :LPVOID, :FINDEX_SEARCH_OPS, :LPVOID, :DWORD, :HANDLE
ifdef _UNICODE
define FindFirstFileTransacted  <FindFirstFileTransactedW>
else
define FindFirstFileTransacted  <FindFirstFileTransactedA>
endif
endif
endif

CopyFileA proto WINAPI :LPCSTR, :LPCSTR, :BOOL
CopyFileW proto WINAPI :LPCWSTR, :LPCWSTR, :BOOL
ifdef _UNICODE
define CopyFile  <CopyFileW>
else
define CopyFile  <CopyFileA>
endif

if(_WIN32_WINNT ge 0x0400)
CALLBACK(LPPROGRESS_ROUTINE, :LARGE_INTEGER, :LARGE_INTEGER, :LARGE_INTEGER, :LARGE_INTEGER, :DWORD, :DWORD, :HANDLE, :HANDLE, :LPVOID)
CopyFileExA proto WINAPI :LPCSTR, :LPCSTR, :LPPROGRESS_ROUTINE, :LPVOID, :LPBOOL, :DWORD
CopyFileExW proto WINAPI :LPCWSTR, :LPCWSTR, :LPPROGRESS_ROUTINE, :LPVOID, :LPBOOL, :DWORD
ifdef _UNICODE
define CopyFileEx  <CopyFileExW>
else
define CopyFileEx  <CopyFileExA>
endif

if _WIN32_WINNT ge 0x0600
CopyFileTransactedA proto WINAPI :LPCSTR, :LPCSTR, :LPPROGRESS_ROUTINE, :LPVOID, :LPBOOL, :DWORD, :HANDLE
CopyFileTransactedW proto WINAPI :LPCWSTR, :LPCWSTR, :LPPROGRESS_ROUTINE, :LPVOID, :LPBOOL, :DWORD, :HANDLE
ifdef _UNICODE
define CopyFileTransacted  <CopyFileTransactedW>
else
define CopyFileTransacted  <CopyFileTransactedA>
endif
endif

if _WIN32_WINNT ge 0x0601

.enum COPYFILE2_MESSAGE_TYPE {
     COPYFILE2_CALLBACK_NONE = 0,
     COPYFILE2_CALLBACK_CHUNK_STARTED,
     COPYFILE2_CALLBACK_CHUNK_FINISHED,
     COPYFILE2_CALLBACK_STREAM_STARTED,
     COPYFILE2_CALLBACK_STREAM_FINISHED,
     COPYFILE2_CALLBACK_POLL_CONTINUE,
     COPYFILE2_CALLBACK_ERROR,
     COPYFILE2_CALLBACK_MAX,
    }

.enum COPYFILE2_MESSAGE_ACTION {
    COPYFILE2_PROGRESS_CONTINUE = 0,
    COPYFILE2_PROGRESS_CANCEL,
    COPYFILE2_PROGRESS_STOP,
    COPYFILE2_PROGRESS_QUIET,
    COPYFILE2_PROGRESS_PAUSE,
    }

.enum COPYFILE2_COPY_PHASE {
    COPYFILE2_PHASE_NONE = 0,
    COPYFILE2_PHASE_PREPARE_SOURCE,
    COPYFILE2_PHASE_PREPARE_DEST,
    COPYFILE2_PHASE_READ_SOURCE,
    COPYFILE2_PHASE_WRITE_DESTINATION,
    COPYFILE2_PHASE_SERVER_COPY,
    COPYFILE2_PHASE_NAMEGRAFT_COPY,
    COPYFILE2_PHASE_MAX,
    }

define COPYFILE2_MESSAGE_COPY_OFFLOAD     (0x00000001)

COPYFILE2_MESSAGE       struct
Type                    COPYFILE2_MESSAGE_TYPE ?
dwPadding               DWORD ?
union Info
 struct ChunkStarted
  dwStreamNumber        DWORD ?
  dwReserved            DWORD ?
  hSourceFile           HANDLE ?
  hDestinationFile      HANDLE ?
  uliChunkNumber        ULARGE_INTEGER <>
  uliChunkSize          ULARGE_INTEGER <>
  uliStreamSize         ULARGE_INTEGER <>
  uliTotalFileSize      ULARGE_INTEGER <>
 ends
 struct ChunkFinished
  dwStreamNumber        DWORD ?
  dwFlags               DWORD ?
  hSourceFile           HANDLE ?
  hDestinationFile      HANDLE ?
  uliChunkNumber        ULARGE_INTEGER <>
  uliChunkSize          ULARGE_INTEGER <>
  uliStreamSize         ULARGE_INTEGER <>
  uliStreamBytesTransferred ULARGE_INTEGER <>
  uliTotalFileSize      ULARGE_INTEGER <>
  uliTotalBytesTransferred ULARGE_INTEGER <>
 ends
 struct StreamStarted
  dwStreamNumber        DWORD ?
  dwReserved            DWORD ?
  hSourceFile           HANDLE ?
  hDestinationFile      HANDLE ?
  uliStreamSize         ULARGE_INTEGER <>
  uliTotalFileSize      ULARGE_INTEGER <>
 ends
 struct StreamFinished
  dwStreamNumber        DWORD ?
  dwReserved            DWORD ?
  hSourceFile           HANDLE ?
  hDestinationFile      HANDLE ?
  uliStreamSize         ULARGE_INTEGER <>
  uliStreamBytesTransferred ULARGE_INTEGER <>
  uliTotalFileSize      ULARGE_INTEGER <>
  uliTotalBytesTransferred ULARGE_INTEGER <>
 ends
 struct PollContinue
  dwReserved            DWORD ?
 ends
 struct Error
  CopyPhase             COPYFILE2_COPY_PHASE ?
  dwStreamNumber        DWORD ?
  hrFailure             HRESULT ?
  dwReserved            DWORD ?
  uliChunkNumber        ULARGE_INTEGER <>
  uliStreamSize         ULARGE_INTEGER <>
  uliStreamBytesTransferred ULARGE_INTEGER <>
  uliTotalFileSize      ULARGE_INTEGER <>
  uliTotalBytesTransferred ULARGE_INTEGER <>
 ends
ends
COPYFILE2_MESSAGE       ends

CALLBACK(PCOPYFILE2_PROGRESS_ROUTINE, :ptr, :PVOID)

COPYFILE2_EXTENDED_PARAMETERS struct
dwSize                  DWORD ?
dwCopyFlags             DWORD ?
pfCancel                ptr BOOL ?
pProgressRoutine        PCOPYFILE2_PROGRESS_ROUTINE ?
pvCallbackContext       PVOID ?
COPYFILE2_EXTENDED_PARAMETERS ends

CopyFile2 proto WINAPI :PCWSTR, :PCWSTR, :ptr

endif

endif

MoveFileA proto WINAPI :LPCSTR, :LPCSTR
MoveFileW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define MoveFile  <MoveFileW>
else
define MoveFile  <MoveFileA>
endif

MoveFileExA proto WINAPI :LPCSTR, :LPCSTR, :DWORD
MoveFileExW proto WINAPI :LPCWSTR, :LPCWSTR, :DWORD
ifdef _UNICODE
define MoveFileEx  <MoveFileExW>
else
define MoveFileEx  <MoveFileExA>
endif


if (_WIN32_WINNT ge 0x0500)
MoveFileWithProgressA proto WINAPI :LPCSTR, :LPCSTR, :LPPROGRESS_ROUTINE, :LPVOID, :DWORD
MoveFileWithProgressW proto WINAPI :LPCWSTR, :LPCWSTR, :LPPROGRESS_ROUTINE, :LPVOID, :DWORD
ifdef _UNICODE
define MoveFileWithProgress  <MoveFileWithProgressW>
else
define MoveFileWithProgress  <MoveFileWithProgressA>
endif
endif

if (_WIN32_WINNT ge 0x0600)
MoveFileTransactedA proto WINAPI :LPCSTR, :LPCSTR, :LPPROGRESS_ROUTINE, :LPVOID, :DWORD, :HANDLE
MoveFileTransactedW proto WINAPI :LPCWSTR, :LPCWSTR, :LPPROGRESS_ROUTINE, :LPVOID, :DWORD, :HANDLE
ifdef _UNICODE
define MoveFileTransacted  <MoveFileTransactedW>
else
define MoveFileTransacted  <MoveFileTransactedA>
endif
endif

define MOVEFILE_REPLACE_EXISTING       0x00000001
define MOVEFILE_COPY_ALLOWED           0x00000002
define MOVEFILE_DELAY_UNTIL_REBOOT     0x00000004
define MOVEFILE_WRITE_THROUGH          0x00000008
if (_WIN32_WINNT ge 0x0500)
define MOVEFILE_CREATE_HARDLINK        0x00000010
define MOVEFILE_FAIL_IF_NOT_TRACKABLE  0x00000020
endif

if (_WIN32_WINNT ge 0x0500)

ReplaceFileA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :DWORD, :LPVOID, :LPVOID
ReplaceFileW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD, :LPVOID, :LPVOID
ifdef _UNICODE
define ReplaceFile  <ReplaceFileW>
else
define ReplaceFile  <ReplaceFileA>
endif
endif

if (_WIN32_WINNT ge 0x0500)

CreateHardLinkA proto WINAPI :LPCSTR, :LPCSTR, :LPSECURITY_ATTRIBUTES
CreateHardLinkW proto WINAPI :LPCWSTR, :LPCWSTR, :LPSECURITY_ATTRIBUTES
ifdef _UNICODE
define CreateHardLink  <CreateHardLinkW>
else
define CreateHardLink  <CreateHardLinkA>
endif

endif

if (_WIN32_WINNT ge 0x0600)

CreateHardLinkTransactedA proto WINAPI :LPCSTR, :LPCSTR, :LPSECURITY_ATTRIBUTES, :HANDLE
CreateHardLinkTransactedW proto WINAPI :LPCWSTR, :LPCWSTR, :LPSECURITY_ATTRIBUTES, :HANDLE
ifdef _UNICODE
define CreateHardLinkTransacted  <CreateHardLinkTransactedW>
else
define CreateHardLinkTransacted  <CreateHardLinkTransactedA>
endif

endif

if _WIN32_WINNT ge 0x0600
FindFirstStreamTransactedW proto WINAPI :LPCWSTR, :STREAM_INFO_LEVELS, :LPVOID, :DWORD, :HANDLE
FindFirstFileNameTransactedW proto WINAPI :LPCWSTR, :DWORD, :LPDWORD, :PWSTR, :HANDLE
endif

CreateNamedPipeA proto WINAPI :LPCSTR, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES
ifndef _UNICODE
define CreateNamedPipe  <CreateNamedPipeA>
endif

GetNamedPipeHandleStateA proto WINAPI :HANDLE, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPSTR, :DWORD
ifndef _UNICODE
define GetNamedPipeHandleState  <GetNamedPipeHandleStateA>
endif

CallNamedPipeA proto WINAPI :LPCSTR, :LPVOID, :DWORD, :LPVOID, :DWORD, :LPDWORD, :DWORD

ifndef _UNICODE
define CallNamedPipe  <CallNamedPipeA>
endif

WaitNamedPipeA proto WINAPI :LPCSTR, :DWORD
ifndef _UNICODE
define WaitNamedPipe  <WaitNamedPipeA>
endif

if (_WIN32_WINNT ge 0x0600)

GetNamedPipeClientComputerNameA proto WINAPI :HANDLE, :LPSTR, :ULONG

ifndef _UNICODE
define GetNamedPipeClientComputerName  <GetNamedPipeClientComputerNameA>
endif

GetNamedPipeClientProcessId proto WINAPI :HANDLE, :PULONG
GetNamedPipeClientSessionId proto WINAPI :HANDLE, :PULONG
GetNamedPipeServerProcessId proto WINAPI :HANDLE, :PULONG
GetNamedPipeServerSessionId proto WINAPI :HANDLE, :PULONG

endif

SetVolumeLabelA proto WINAPI :LPCSTR, :LPCSTR
SetVolumeLabelW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define SetVolumeLabel  <SetVolumeLabelW>
else
define SetVolumeLabel  <SetVolumeLabelA>
endif

.pragma comment(lib, advapi32)

if (_WIN32_WINNT ge 0x0600)
SetFileBandwidthReservation proto WINAPI :HANDLE, :DWORD, :DWORD, :BOOL, :LPDWORD, :LPDWORD
GetFileBandwidthReservation proto WINAPI :HANDLE, :LPDWORD, :LPDWORD, :LPBOOL, :LPDWORD, :LPDWORD
endif

ClearEventLogA proto WINAPI :HANDLE, :LPCSTR
ClearEventLogW proto WINAPI :HANDLE, :LPCWSTR
ifdef _UNICODE
define ClearEventLog  <ClearEventLogW>
else
define ClearEventLog  <ClearEventLogA>
endif

BackupEventLogA proto WINAPI :HANDLE, :LPCSTR
BackupEventLogW proto WINAPI :HANDLE, :LPCWSTR
ifdef _UNICODE
define BackupEventLog  <BackupEventLogW>
else
define BackupEventLog  <BackupEventLogA>
endif

CloseEventLog proto WINAPI :HANDLE

DeregisterEventSource proto WINAPI :HANDLE

NotifyChangeEventLog proto WINAPI :HANDLE, :HANDLE
GetNumberOfEventLogRecords proto WINAPI :HANDLE, :PDWORD
GetOldestEventLogRecord proto WINAPI :HANDLE, :PDWORD
OpenEventLogA proto WINAPI :LPCSTR, :LPCSTR
OpenEventLogW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define OpenEventLog  <OpenEventLogW>
else
define OpenEventLog  <OpenEventLogA>
endif

RegisterEventSourceA proto WINAPI :LPCSTR, :LPCSTR
RegisterEventSourceW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define RegisterEventSource  <RegisterEventSourceW>
else
define RegisterEventSource  <RegisterEventSourceA>
endif

OpenBackupEventLogA proto WINAPI :LPCSTR, :LPCSTR
OpenBackupEventLogW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define OpenBackupEventLog  <OpenBackupEventLogW>
else
define OpenBackupEventLog  <OpenBackupEventLogA>
endif

ReadEventLogA proto WINAPI :HANDLE, :DWORD, :DWORD, :LPVOID, :DWORD, :ptr, :ptr
ReadEventLogW proto WINAPI :HANDLE, :DWORD, :DWORD, :LPVOID, :DWORD, :ptr, :ptr
ifdef _UNICODE
define ReadEventLog  <ReadEventLogW>
else
define ReadEventLog  <ReadEventLogA>
endif

ReportEventA proto WINAPI :HANDLE, :WORD, :WORD, :DWORD, :PSID, :WORD, :DWORD, :ptr, :LPVOID
ReportEventW proto WINAPI :HANDLE, :WORD, :WORD, :DWORD, :PSID, :WORD, :DWORD, :ptr, :LPVOID
ifdef _UNICODE
define ReportEvent  <ReportEventW>
else
define ReportEvent  <ReportEventA>
endif

define EVENTLOG_FULL_INFO      0

EVENTLOG_FULL_INFORMATION struct
dwFull                  DWORD ?
EVENTLOG_FULL_INFORMATION ends
LPEVENTLOG_FULL_INFORMATION typedef ptr EVENTLOG_FULL_INFORMATION

GetEventLogInformation proto WINAPI :HANDLE, :DWORD, :LPVOID, :DWORD, :LPDWORD

if (_WIN32_WINNT ge 0x0602)

define OPERATION_API_VERSION                   1
OPERATION_ID            typedef ULONG

OPERATION_START_PARAMETERS struct
Version                 ULONG ?
OperationId             OPERATION_ID ?
Flags                   ULONG ?
OPERATION_START_PARAMETERS ends
POPERATION_START_PARAMETERS typedef ptr OPERATION_START_PARAMETERS

define OPERATION_START_TRACE_CURRENT_THREAD    0x1

OPERATION_END_PARAMETERS struct
Version                 ULONG ?
OperationId             OPERATION_ID ?
Flags                   ULONG ?
OPERATION_END_PARAMETERS ends
POPERATION_END_PARAMETERS typedef ptr OPERATION_END_PARAMETERS

define OPERATION_END_DISCARD                   0x1

OperationStart proto WINAPI :ptr
OperationEnd proto WINAPI :ptr

endif

AccessCheckAndAuditAlarmA proto WINAPI :LPCSTR, :LPVOID, :LPSTR, :LPSTR, :PSECURITY_DESCRIPTOR, :DWORD, :PGENERIC_MAPPING, :BOOL, :LPDWORD, :LPBOOL, :LPBOOL
ifndef _UNICODE
define AccessCheckAndAuditAlarm  <AccessCheckAndAuditAlarmA>
endif

if(_WIN32_WINNT ge 0x0500)

AccessCheckByTypeAndAuditAlarmA proto WINAPI :LPCSTR, :LPVOID, :LPCSTR, :LPCSTR, :PSECURITY_DESCRIPTOR, :PSID, :DWORD, :AUDIT_EVENT_TYPE, :DWORD, :POBJECT_TYPE_LIST, :DWORD, :PGENERIC_MAPPING, :BOOL, :LPDWORD, :LPBOOL, :LPBOOL
ifndef _UNICODE
define AccessCheckByTypeAndAuditAlarm  <AccessCheckByTypeAndAuditAlarmA>
endif

AccessCheckByTypeResultListAndAuditAlarmA proto WINAPI :LPCSTR, :LPVOID, :LPCSTR, :LPCSTR, :PSECURITY_DESCRIPTOR, :PSID, :DWORD, :AUDIT_EVENT_TYPE, :DWORD, :POBJECT_TYPE_LIST, :DWORD, :PGENERIC_MAPPING, :BOOL, :LPDWORD, :LPDWORD, :LPBOOL
ifndef _UNICODE
define AccessCheckByTypeResultListAndAuditAlarm  <AccessCheckByTypeResultListAndAuditAlarmA>
endif

AccessCheckByTypeResultListAndAuditAlarmByHandleA proto WINAPI :LPCSTR, :LPVOID, :HANDLE, :LPCSTR, :LPCSTR, :PSECURITY_DESCRIPTOR, :PSID, :DWORD, :AUDIT_EVENT_TYPE, :DWORD, :POBJECT_TYPE_LIST, :DWORD, :PGENERIC_MAPPING, :BOOL, :LPDWORD, :LPDWORD, :LPBOOL
ifndef _UNICODE
define AccessCheckByTypeResultListAndAuditAlarmByHandle  <AccessCheckByTypeResultListAndAuditAlarmByHandleA>
endif
endif

ObjectOpenAuditAlarmA proto WINAPI :LPCSTR, :LPVOID, :LPSTR, :LPSTR, :PSECURITY_DESCRIPTOR, :HANDLE, :DWORD, :DWORD, :PPRIVILEGE_SET, :BOOL, :BOOL, :LPBOOL
ifndef _UNICODE
define ObjectOpenAuditAlarm  <ObjectOpenAuditAlarmA>
endif

ObjectPrivilegeAuditAlarmA proto WINAPI :LPCSTR, :LPVOID, :HANDLE, :DWORD, :PPRIVILEGE_SET, :BOOL
ifndef _UNICODE
define ObjectPrivilegeAuditAlarm  <ObjectPrivilegeAuditAlarmA>
endif

ObjectCloseAuditAlarmA proto WINAPI :LPCSTR, :LPVOID, :BOOL
ifndef _UNICODE
define ObjectCloseAuditAlarm  <ObjectCloseAuditAlarmA>
endif

ObjectDeleteAuditAlarmA proto WINAPI :LPCSTR, :LPVOID, :BOOL
ifndef _UNICODE
define ObjectDeleteAuditAlarm  <ObjectDeleteAuditAlarmA>
endif

PrivilegedServiceAuditAlarmA proto WINAPI :LPCSTR, :LPCSTR, :HANDLE, :PPRIVILEGE_SET, :BOOL
ifndef _UNICODE
define PrivilegedServiceAuditAlarm  <PrivilegedServiceAuditAlarmA>
endif

if(_WIN32_WINNT ge 0x0601)
AddConditionalAce proto WINAPI :PACL, :DWORD, :DWORD, :UCHAR, :DWORD, :PSID, :PWCHAR, :ptr
endif

SetFileSecurityA proto WINAPI :LPCSTR, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR
ifndef _UNICODE
define SetFileSecurity  <SetFileSecurityA>
endif

GetFileSecurityA proto WINAPI :LPCSTR, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR, :DWORD, :LPDWORD
ifndef _UNICODE
define GetFileSecurity  <GetFileSecurityA>
endif

if(_WIN32_WINNT ge 0x0400)
ReadDirectoryChangesW proto WINAPI :HANDLE, :LPVOID, :DWORD, :BOOL, :DWORD, :LPDWORD, :LPOVERLAPPED, :LPOVERLAPPED_COMPLETION_ROUTINE

if (NTDDI_VERSION ge NTDDI_WIN10_RS3)
ReadDirectoryChangesExW proto WINAPI :HANDLE, :LPVOID, :DWORD, :BOOL, :DWORD, :LPDWORD, :LPOVERLAPPED, :LPOVERLAPPED_COMPLETION_ROUTINE, :READ_DIRECTORY_NOTIFY_INFORMATION_CLASS
endif
endif

if _WIN32_WINNT ge 0x0600
MapViewOfFileExNuma proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :SIZE_T, :LPVOID, :DWORD
endif

.pragma comment(lib, kernel32)

IsBadReadPtr proto WINAPI :ptr, :UINT_PTR
IsBadWritePtr proto WINAPI :LPVOID, :UINT_PTR
IsBadHugeReadPtr proto WINAPI :ptr, :UINT_PTR
IsBadHugeWritePtr proto WINAPI :LPVOID, :UINT_PTR
IsBadCodePtr proto WINAPI :FARPROC
IsBadStringPtrA proto WINAPI :LPCSTR, :UINT_PTR
IsBadStringPtrW proto WINAPI :LPCWSTR, :UINT_PTR
ifdef _UNICODE
define IsBadStringPtr  <IsBadStringPtrW>
else
define IsBadStringPtr  <IsBadStringPtrA>
endif


.pragma comment(lib, Advapi32)

LookupAccountSidA proto WINAPI :LPCSTR, :PSID, :LPSTR, :LPDWORD, :LPSTR, :LPDWORD, :PSID_NAME_USE
LookupAccountSidW proto WINAPI :LPCWSTR, :PSID, :LPWSTR, :LPDWORD, :LPWSTR, :LPDWORD, :PSID_NAME_USE
ifdef _UNICODE
define LookupAccountSid  <LookupAccountSidW>
else
define LookupAccountSid  <LookupAccountSidA>
endif

LookupAccountNameA proto WINAPI :LPCSTR, :LPCSTR, :PSID, :LPDWORD, :LPSTR, :LPDWORD, :PSID_NAME_USE
LookupAccountNameW proto WINAPI :LPCWSTR, :LPCWSTR, :PSID, :LPDWORD, :LPWSTR, :LPDWORD, :PSID_NAME_USE
ifdef _UNICODE
define LookupAccountName  <LookupAccountNameW>
else
define LookupAccountName  <LookupAccountNameA>
endif

if _WIN32_WINNT ge 0x0601

LookupAccountNameLocalA proto WINAPI :LPCSTR, :PSID, :LPDWORD, :LPSTR, :LPDWORD, :PSID_NAME_USE
LookupAccountNameLocalW proto WINAPI :LPCWSTR, :PSID, :LPDWORD, :LPWSTR, :LPDWORD, :PSID_NAME_USE
ifdef _UNICODE
define LookupAccountNameLocal  <LookupAccountNameLocalW>
else
define LookupAccountNameLocal  <LookupAccountNameLocalA>
endif

LookupAccountSidLocalA proto WINAPI :PSID, :LPSTR, :LPDWORD, :LPSTR, :LPDWORD, :PSID_NAME_USE
LookupAccountSidLocalW proto WINAPI :PSID, :LPWSTR, :LPDWORD, :LPWSTR, :LPDWORD, :PSID_NAME_USE
ifdef _UNICODE
define LookupAccountSidLocal  <LookupAccountSidLocalW>
else
define LookupAccountSidLocal  <LookupAccountSidLocalA>
endif

else

LookupAccountNameLocalA macro n, s, cs, d, cd, u
  exitm<LookupAccountNameA(NULL, n, s, cs, d, cd, u)>
  endm
LookupAccountNameLocalW macro n, s, cs, d, cd, u
  exitm<LookupAccountNameW(NULL, n, s, cs, d, cd, u)>
  endm
ifdef _UNICODE
define LookupAccountNameLocal  <LookupAccountNameLocalW>
else
define LookupAccountNameLocal  <LookupAccountNameLocalA>
endif

LookupAccountSidLocalA macro s, n, cn, d, cd, u
  exitm<LookupAccountSidA(NULL, s, n, cn, d, cd, u)>
  endm
LookupAccountSidLocalW macro s, n, cn, d, cd, u
  exitm<LookupAccountSidW(NULL, s, n, cn, d, cd, u)>
  endm
ifdef _UNICODE
define LookupAccountSidLocal  <LookupAccountSidLocalW>
else
define LookupAccountSidLocal  <LookupAccountSidLocalA>
endif

endif

LookupPrivilegeValueA proto WINAPI :LPCSTR, :LPCSTR, :PLUID
LookupPrivilegeValueW proto WINAPI :LPCWSTR, :LPCWSTR, :PLUID
ifdef _UNICODE
define LookupPrivilegeValue  <LookupPrivilegeValueW>
else
define LookupPrivilegeValue  <LookupPrivilegeValueA>
endif

LookupPrivilegeNameA proto WINAPI :LPCSTR, :PLUID, :LPSTR, :LPDWORD
LookupPrivilegeNameW proto WINAPI :LPCWSTR, :PLUID, :LPWSTR, :LPDWORD
ifdef _UNICODE
define LookupPrivilegeName  <LookupPrivilegeNameW>
else
define LookupPrivilegeName  <LookupPrivilegeNameA>
endif

LookupPrivilegeDisplayNameA proto WINAPI :LPCSTR, :LPCSTR, :LPSTR, :LPDWORD, :LPDWORD
LookupPrivilegeDisplayNameW proto WINAPI :LPCWSTR, :LPCWSTR, :LPWSTR, :LPDWORD, :LPDWORD
ifdef _UNICODE
define LookupPrivilegeDisplayName  <LookupPrivilegeDisplayNameW>
else
define LookupPrivilegeDisplayName  <LookupPrivilegeDisplayNameA>
endif

.pragma comment(lib, kernel32)

BuildCommDCBA proto WINAPI :LPCSTR, :LPDCB
BuildCommDCBW proto WINAPI :LPCWSTR, :LPDCB
ifdef _UNICODE
define BuildCommDCB  <BuildCommDCBW>
else
define BuildCommDCB  <BuildCommDCBA>
endif

BuildCommDCBAndTimeoutsA proto WINAPI :LPCSTR, :LPDCB, :LPCOMMTIMEOUTS
BuildCommDCBAndTimeoutsW proto WINAPI :LPCWSTR, :LPDCB, :LPCOMMTIMEOUTS
ifdef _UNICODE
define BuildCommDCBAndTimeouts  <BuildCommDCBAndTimeoutsW>
else
define BuildCommDCBAndTimeouts  <BuildCommDCBAndTimeoutsA>
endif

CommConfigDialogA proto WINAPI :LPCSTR, :HWND, :LPCOMMCONFIG
CommConfigDialogW proto WINAPI :LPCWSTR, :HWND, :LPCOMMCONFIG
ifdef _UNICODE
define CommConfigDialog  <CommConfigDialogW>
else
define CommConfigDialog  <CommConfigDialogA>
endif

GetDefaultCommConfigA proto WINAPI :LPCSTR, :LPCOMMCONFIG, :LPDWORD
GetDefaultCommConfigW proto WINAPI :LPCWSTR, :LPCOMMCONFIG, :LPDWORD
ifdef _UNICODE
define GetDefaultCommConfig  <GetDefaultCommConfigW>
else
define GetDefaultCommConfig  <GetDefaultCommConfigA>
endif

SetDefaultCommConfigA proto WINAPI :LPCSTR, :LPCOMMCONFIG, :DWORD
SetDefaultCommConfigW proto WINAPI :LPCWSTR, :LPCOMMCONFIG, :DWORD
ifdef _UNICODE
define SetDefaultCommConfig  <SetDefaultCommConfigW>
else
define SetDefaultCommConfig  <SetDefaultCommConfigA>
endif

ifndef _MAC
define MAX_COMPUTERNAME_LENGTH 15
else
define MAX_COMPUTERNAME_LENGTH 31
endif

GetComputerNameA proto WINAPI :LPSTR, :LPDWORD
GetComputerNameW proto WINAPI :LPWSTR, :LPDWORD
ifdef _UNICODE
define GetComputerName  <GetComputerNameW>
else
define GetComputerName  <GetComputerNameA>
endif

if (_WIN32_WINNT ge 0x0500)

DnsHostnameToComputerNameA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD
DnsHostnameToComputerNameW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD
ifdef _UNICODE
define DnsHostnameToComputerName  <DnsHostnameToComputerNameW>
else
define DnsHostnameToComputerName  <DnsHostnameToComputerNameA>
endif

endif

GetUserNameA proto WINAPI :LPSTR, :LPDWORD
GetUserNameW proto WINAPI :LPWSTR, :LPDWORD
ifdef _UNICODE
define GetUserName  <GetUserNameW>
else
define GetUserName  <GetUserNameA>
endif

define LOGON32_LOGON_INTERACTIVE       2
define LOGON32_LOGON_NETWORK           3
define LOGON32_LOGON_BATCH             4
define LOGON32_LOGON_SERVICE           5
define LOGON32_LOGON_UNLOCK            7
if(_WIN32_WINNT ge 0x0500)
define LOGON32_LOGON_NETWORK_CLEARTEXT 8
define LOGON32_LOGON_NEW_CREDENTIALS   9
endif

define LOGON32_PROVIDER_DEFAULT    0
define LOGON32_PROVIDER_WINNT35    1
if(_WIN32_WINNT ge 0x0400)
define LOGON32_PROVIDER_WINNT40    2
endif
if(_WIN32_WINNT ge 0x0500)
define LOGON32_PROVIDER_WINNT50    3
endif
if(_WIN32_WINNT ge 0x0600)
define LOGON32_PROVIDER_VIRTUAL    4
endif

LogonUserA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :DWORD, :DWORD, :PHANDLE
LogonUserW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD, :PHANDLE
ifdef _UNICODE
define LogonUser  <LogonUserW>
else
define LogonUser  <LogonUserA>
endif

LogonUserExA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :DWORD, :DWORD, :PHANDLE, :ptr, :ptr, :LPDWORD, :PQUOTA_LIMITS
LogonUserExW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD, :PHANDLE, :ptr, :ptr, :LPDWORD, :PQUOTA_LIMITS
ifdef _UNICODE
define LogonUserEx  <LogonUserExW>
else
define LogonUserEx  <LogonUserExA>
endif

if(_WIN32_WINNT ge 0x0500)

define LOGON_WITH_PROFILE              0x00000001
define LOGON_NETCREDENTIALS_ONLY       0x00000002
define LOGON_ZERO_PASSWORD_BUFFER      0x80000000

CreateProcessWithLogonW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD, :LPCWSTR, :LPWSTR, :DWORD, :LPVOID, :LPCWSTR, :LPSTARTUPINFOW, :LPPROCESS_INFORMATION
CreateProcessWithTokenW proto WINAPI :HANDLE, :DWORD, :LPCWSTR, :LPWSTR, :DWORD, :LPVOID, :LPCWSTR, :LPSTARTUPINFOW, :LPPROCESS_INFORMATION

endif

IsTokenUntrusted proto WINAPI :HANDLE

ifdef __PE__
.pragma comment(lib, kernel32)
endif

if (_WIN32_WINNT ge 0x0500)

RegisterWaitForSingleObject proto WINAPI :PHANDLE, :HANDLE, :WAITORTIMERCALLBACK, :PVOID, :ULONG, :ULONG
UnregisterWait proto WINAPI :HANDLE
BindIoCompletionCallback proto WINAPI :HANDLE, :LPOVERLAPPED_COMPLETION_ROUTINE, :ULONG
SetTimerQueueTimer proto WINAPI :HANDLE, :WAITORTIMERCALLBACK, :PVOID, :DWORD, :DWORD, :BOOL
CancelTimerQueueTimer proto WINAPI :HANDLE, :HANDLE
DeleteTimerQueue proto WINAPI :HANDLE

endif

if (_WIN32_WINNT ge 0x0500)
if (_WIN32_WINNT ge 0x0600)
ifndef MIDL_PASS

InitializeThreadpoolEnvironment macro pcbe
    TpInitializeCallbackEnviron(pcbe)
    endm
SetThreadpoolCallbackPool macro pcbe, ptpp
    TpSetCallbackThreadpool(pcbe, ptpp)
    endm
SetThreadpoolCallbackCleanupGroup macro pcbe, ptpcg, pfng
    TpSetCallbackCleanupGroup(pcbe, ptpcg, pfng)
    endm
SetThreadpoolCallbackRunsLong macro pcbe
    TpSetCallbackLongFunction(pcbe)
    endm
SetThreadpoolCallbackLibrary macro pcbe, _mod
    TpSetCallbackRaceWithDll(pcbe, _mod)
    endm

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)

SetThreadpoolCallbackPriority macro pcbe, Priority
    TpSetCallbackPriority(pcbe, Priority)
    endm

endif

SetThreadpoolCallbackPersistent macro pcbe
    TpSetCallbackPersistent(pcbe)
    endm

endif
endif
endif

if (_WIN32_WINNT ge 0x0600)
ifndef MIDL_PASS

SetThreadpoolCallbackPersistent macro pcbe
    TpSetCallbackPersistent(pcbe)
    endm

endif
endif

CreatePrivateNamespaceA proto WINAPI :LPSECURITY_ATTRIBUTES, :LPVOID, :LPCSTR
ifndef _UNICODE
define CreatePrivateNamespace <CreatePrivateNamespaceA>
else
define CreatePrivateNamespace <CreatePrivateNamespaceW>
endif

OpenPrivateNamespaceA proto WINAPI :LPVOID, :LPCSTR
ifndef _UNICODE
define OpenPrivateNamespace <OpenPrivateNamespaceA>
else
define OpenPrivateNamespace <OpenPrivateNamespaceW>
endif

CreateBoundaryDescriptorA proto WINAPI :LPCSTR, :ULONG
ifndef _UNICODE
define CreateBoundaryDescriptor <CreateBoundaryDescriptorA>
else
define CreateBoundaryDescriptor <CreateBoundaryDescriptorW>
endif

AddIntegrityLabelToBoundaryDescriptor proto WINAPI :ptr, :PSID

if(_WIN32_WINNT ge 0x0400)

define HW_PROFILE_GUIDLEN         39
define MAX_PROFILE_LEN            80

define DOCKINFO_UNDOCKED          (0x1)
define DOCKINFO_DOCKED            (0x2)
define DOCKINFO_USER_SUPPLIED     (0x4)
define DOCKINFO_USER_UNDOCKED     (DOCKINFO_USER_SUPPLIED or DOCKINFO_UNDOCKED)
define DOCKINFO_USER_DOCKED       (DOCKINFO_USER_SUPPLIED or DOCKINFO_DOCKED)

HW_PROFILE_INFOA        struct
dwDockInfo              DWORD ?
szHwProfileGuid         CHAR HW_PROFILE_GUIDLEN dup(?)
szHwProfileName         CHAR MAX_PROFILE_LEN dup(?)
HW_PROFILE_INFOA        ends
LPHW_PROFILE_INFOA      typedef ptr HW_PROFILE_INFOA
HW_PROFILE_INFOW        struct
dwDockInfo              DWORD ?
szHwProfileGuid         WCHAR HW_PROFILE_GUIDLEN dup(?)
szHwProfileName         WCHAR MAX_PROFILE_LEN dup(?)
HW_PROFILE_INFOW        ends
LPHW_PROFILE_INFOW      typedef ptr HW_PROFILE_INFOW
ifdef _UNICODE
HW_PROFILE_INFO         typedef HW_PROFILE_INFOW
LPHW_PROFILE_INFO       typedef LPHW_PROFILE_INFOW
else
HW_PROFILE_INFO         typedef HW_PROFILE_INFOA
LPHW_PROFILE_INFO       typedef LPHW_PROFILE_INFOA
endif

GetCurrentHwProfileA proto WINAPI :LPHW_PROFILE_INFOA
GetCurrentHwProfileW proto WINAPI :LPHW_PROFILE_INFOW
ifdef _UNICODE
define GetCurrentHwProfile  <GetCurrentHwProfileW>
else
define GetCurrentHwProfile  <GetCurrentHwProfileA>
endif
endif

VerifyVersionInfoA proto WINAPI :LPOSVERSIONINFOEXA, :DWORD, :DWORDLONG
VerifyVersionInfoW proto WINAPI :LPOSVERSIONINFOEXW, :DWORD, :DWORDLONG
ifdef _UNICODE
define VerifyVersionInfo  <VerifyVersionInfoW>
else
define VerifyVersionInfo  <VerifyVersionInfoA>
endif

include winerror.inc
include timezoneapi.inc

define TC_NORMAL       0
define TC_HARDERR      1
define TC_GP_TRAP      2
define TC_SIGNAL       3

if(WINVER ge 0x0400)
SetSystemPowerState proto WINAPI :BOOL, :BOOL
endif

if(WINVER ge 0x0400)

define AC_LINE_OFFLINE                 0x00
define AC_LINE_ONLINE                  0x01
define AC_LINE_BACKUP_POWER            0x02
define AC_LINE_UNKNOWN                 0xFF

define BATTERY_FLAG_HIGH               0x01
define BATTERY_FLAG_LOW                0x02
define BATTERY_FLAG_CRITICAL           0x04
define BATTERY_FLAG_CHARGING           0x08
define BATTERY_FLAG_NO_BATTERY         0x80
define BATTERY_FLAG_UNKNOWN            0xFF

define BATTERY_PERCENTAGE_UNKNOWN      0xFF

define SYSTEM_STATUS_FLAG_POWER_SAVING_ON      0x01

define BATTERY_LIFE_UNKNOWN        0xFFFFFFFF

SYSTEM_POWER_STATUS     struct
ACLineStatus            BYTE ?
BatteryFlag             BYTE ?
BatteryLifePercent      BYTE ?
SystemStatusFlag        BYTE ?
BatteryLifeTime         DWORD ?
BatteryFullLifeTime     DWORD ?
SYSTEM_POWER_STATUS     ends
LPSYSTEM_POWER_STATUS   typedef ptr SYSTEM_POWER_STATUS

GetSystemPowerStatus proto WINAPI :LPSYSTEM_POWER_STATUS

endif

if (_WIN32_WINNT ge 0x0500)

MapUserPhysicalPagesScatter proto WINAPI :ptr, :ULONG_PTR, :PULONG_PTR

CreateJobObjectA proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCSTR
ifdef _UNICODE
define CreateJobObject  <CreateJobObjectW>
else
define CreateJobObject  <CreateJobObjectA>
endif

OpenJobObjectA proto WINAPI :DWORD, :BOOL, :LPCSTR
ifdef _UNICODE
define OpenJobObject  <OpenJobObjectW>
else
define OpenJobObject  <OpenJobObjectA>
endif

CreateJobSet proto WINAPI :ULONG, :PJOB_SET_ARRAY, :ULONG

FindFirstVolumeA proto WINAPI :LPSTR, :DWORD
ifndef _UNICODE
define FindFirstVolume <FindFirstVolumeA>
endif

FindNextVolumeA proto WINAPI :HANDLE, :LPSTR, :DWORD
ifndef _UNICODE
define FindNextVolume <FindNextVolumeA>
endif

FindFirstVolumeMountPointA proto WINAPI :LPCSTR, :LPSTR, :DWORD
FindFirstVolumeMountPointW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD
ifdef _UNICODE
define FindFirstVolumeMountPoint <FindFirstVolumeMountPointW>
else
define FindFirstVolumeMountPoint <FindFirstVolumeMountPointA>
endif

FindNextVolumeMountPointA proto WINAPI :HANDLE, :LPSTR, :DWORD
FindNextVolumeMountPointW proto WINAPI :HANDLE, :LPWSTR, :DWORD
ifdef _UNICODE
define FindNextVolumeMountPoint <FindNextVolumeMountPointW>
else
define FindNextVolumeMountPoint <FindNextVolumeMountPointA>
endif

FindVolumeMountPointClose proto WINAPI :HANDLE

SetVolumeMountPointA proto WINAPI :LPCSTR, :LPCSTR
SetVolumeMountPointW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define SetVolumeMountPoint  <SetVolumeMountPointW>
else
define SetVolumeMountPoint  <SetVolumeMountPointA>
endif

DeleteVolumeMountPointA proto WINAPI :LPCSTR
ifndef _UNICODE
define DeleteVolumeMountPoint  <DeleteVolumeMountPointA>
endif

ifndef _UNICODE
define GetVolumeNameForVolumeMountPoint  <GetVolumeNameForVolumeMountPointA>
endif

GetVolumeNameForVolumeMountPointA proto WINAPI :LPCSTR, :LPSTR, :DWORD

GetVolumePathNameA proto WINAPI :LPCSTR, :LPSTR, :DWORD
ifndef _UNICODE
define GetVolumePathName  <GetVolumePathNameA>
endif

endif

if(_WIN32_WINNT ge 0x0501)
GetVolumePathNamesForVolumeNameA proto WINAPI :LPCSTR, :LPCH, :DWORD, :PDWORD
ifndef _UNICODE
define GetVolumePathNamesForVolumeName  <GetVolumePathNamesForVolumeNameA>
endif
endif

if (_WIN32_WINNT ge 0x0500) or (_WIN32_FUSION ge 0x0100) ;or ISOLATION_AWARE_ENABLED

define ACTCTX_FLAG_PROCESSOR_ARCHITECTURE_VALID    (0x00000001)
define ACTCTX_FLAG_LANGID_VALID                    (0x00000002)
define ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID        (0x00000004)
define ACTCTX_FLAG_RESOURCE_NAME_VALID             (0x00000008)
define ACTCTX_FLAG_SET_PROCESS_DEFAULT             (0x00000010)
define ACTCTX_FLAG_APPLICATION_NAME_VALID          (0x00000020)
define ACTCTX_FLAG_SOURCE_IS_ASSEMBLYREF           (0x00000040)
define ACTCTX_FLAG_HMODULE_VALID                   (0x00000080)

ACTCTXA                 struct
cbSize                  ULONG ?
dwFlags                 DWORD ?
lpSource                LPCSTR ?
wProcessorArchitecture  USHORT ?
wLangId                 LANGID ?
lpAssemblyDirectory     LPCSTR ?
lpResourceName          LPCSTR ?
lpApplicationName       LPCSTR ?
hModule                 HMODULE ?
ACTCTXA                 ends
PACTCTXA                typedef ptr ACTCTXA
ACTCTXW                 struct
cbSize                  ULONG ?
dwFlags                 DWORD ?
lpSource                LPCWSTR ?
wProcessorArchitecture  USHORT ?
wLangId                 LANGID ?
lpAssemblyDirectory     LPCWSTR ?
lpResourceName          LPCWSTR ?
lpApplicationName       LPCWSTR ?
hModule                 HMODULE ?
ACTCTXW                 ends
PACTCTXW                typedef ptr ACTCTXW
ifdef _UNICODE
ACTCTX                  typedef ACTCTXW
PACTCTX                 typedef PACTCTXW
else
ACTCTX                  typedef ACTCTXA
PACTCTX                 typedef PACTCTXA
endif

PCACTCTXA               typedef ptr ACTCTXA
PCACTCTXW               typedef ptr ACTCTXW
ifdef _UNICODE
PCACTCTX                typedef PCACTCTXW
else
PCACTCTX                typedef PCACTCTXA
endif

CreateActCtxA proto WINAPI :PCACTCTXA
CreateActCtxW proto WINAPI :PCACTCTXW
ifdef _UNICODE
define CreateActCtx  <CreateActCtxW>
else
define CreateActCtx  <CreateActCtxA>
endif

AddRefActCtx proto WINAPI :HANDLE
ReleaseActCtx proto WINAPI :HANDLE
ZombifyActCtx proto WINAPI :HANDLE
ActivateActCtx proto WINAPI :HANDLE, :ptr

define DEACTIVATE_ACTCTX_FLAG_FORCE_EARLY_DEACTIVATION (0x00000001)

DeactivateActCtx proto WINAPI :DWORD, :ULONG_PTR
GetCurrentActCtx proto WINAPI :ptr

ACTCTX_SECTION_KEYED_DATA_2600 struct
cbSize                  ULONG ?
ulDataFormatVersion     ULONG ?
lpData                  PVOID ?
ulLength                ULONG ?
lpSectionGlobalData     PVOID ?
ulSectionGlobalDataLength ULONG ?
lpSectionBase           PVOID ?
ulSectionTotalLength    ULONG ?
hActCtx                 HANDLE ?
ulAssemblyRosterIndex   ULONG ?
ACTCTX_SECTION_KEYED_DATA_2600 ends
PACTCTX_SECTION_KEYED_DATA_2600 typedef ptr ACTCTX_SECTION_KEYED_DATA_2600
PCACTCTX_SECTION_KEYED_DATA_2600 typedef ptr ACTCTX_SECTION_KEYED_DATA_2600

ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA struct
lpInformation           PVOID ?
lpSectionBase           PVOID ?
ulSectionLength         ULONG ?
lpSectionGlobalDataBase PVOID ?
ulSectionGlobalDataLength ULONG ?
ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA ends
PACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA typedef ptr ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA
PCACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA typedef ptr ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA

ACTCTX_SECTION_KEYED_DATA struct
cbSize                  ULONG ?
ulDataFormatVersion     ULONG ?
lpData                  PVOID ?
ulLength                ULONG ?
lpSectionGlobalData     PVOID ?
ulSectionGlobalDataLength ULONG ?
lpSectionBase           PVOID ?
ulSectionTotalLength    ULONG ?
hActCtx                 HANDLE ?
ulAssemblyRosterIndex   ULONG ?
ulFlags                 ULONG ?
AssemblyMetadata        ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA <>
ACTCTX_SECTION_KEYED_DATA ends
PACTCTX_SECTION_KEYED_DATA typedef ptr ACTCTX_SECTION_KEYED_DATA
PCACTCTX_SECTION_KEYED_DATA typedef ptr ACTCTX_SECTION_KEYED_DATA

define FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX (0x00000001)
define FIND_ACTCTX_SECTION_KEY_RETURN_FLAGS   (0x00000002)
define FIND_ACTCTX_SECTION_KEY_RETURN_ASSEMBLY_METADATA (0x00000004)

FindActCtxSectionStringA proto WINAPI :DWORD, :ptr, :ULONG, :LPCSTR, :PACTCTX_SECTION_KEYED_DATA
FindActCtxSectionStringW proto WINAPI :DWORD, :ptr, :ULONG, :LPCWSTR, :PACTCTX_SECTION_KEYED_DATA
ifdef _UNICODE
define FindActCtxSectionString  <FindActCtxSectionStringW>
else
define FindActCtxSectionString  <FindActCtxSectionStringA>
endif

FindActCtxSectionGuid proto WINAPI :DWORD, :ptr, :ULONG, :ptr, :PACTCTX_SECTION_KEYED_DATA

if not defined(RC_INVOKED)
if not defined(ACTIVATION_CONTEXT_BASIC_INFORMATION_DEFINED)

ACTIVATION_CONTEXT_BASIC_INFORMATION struct
hActCtx                 HANDLE ?
dwFlags                 DWORD ?
ACTIVATION_CONTEXT_BASIC_INFORMATION ends
PACTIVATION_CONTEXT_BASIC_INFORMATION typedef ptr ACTIVATION_CONTEXT_BASIC_INFORMATION
PCACTIVATION_CONTEXT_BASIC_INFORMATION typedef ptr ACTIVATION_CONTEXT_BASIC_INFORMATION

define ACTIVATION_CONTEXT_BASIC_INFORMATION_DEFINED 1

endif
endif

define QUERY_ACTCTX_FLAG_USE_ACTIVE_ACTCTX (0x00000004)
define QUERY_ACTCTX_FLAG_ACTCTX_IS_HMODULE (0x00000008)
define QUERY_ACTCTX_FLAG_ACTCTX_IS_ADDRESS (0x00000010)
define QUERY_ACTCTX_FLAG_NO_ADDREF         (0x80000000)

QueryActCtxW proto WINAPI :DWORD, :HANDLE, :PVOID, :ULONG, :PVOID, :SIZE_T, :ptr
CALLBACK(PQUERYACTCTXW_FUNC, :DWORD, :HANDLE, :PVOID, :ULONG, :PVOID, :SIZE_T, :ptr SIZE_T)

endif

if _WIN32_WINNT ge 0x0501
WTSGetActiveConsoleSessionId proto WINAPI
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINTHRESHOLD)
WTSGetServiceSessionId proto WINAPI
WTSIsServerContainer proto WINAPI
endif

if _WIN32_WINNT ge 0x0601
GetActiveProcessorGroupCount proto WINAPI
GetMaximumProcessorGroupCount proto WINAPI
GetActiveProcessorCount proto WINAPI :WORD
GetMaximumProcessorCount proto WINAPI :WORD
endif

GetNumaProcessorNode proto WINAPI :UCHAR, :PUCHAR

if _WIN32_WINNT ge 0x0601
GetNumaNodeNumberFromHandle proto WINAPI :HANDLE, :PUSHORT
endif

if _WIN32_WINNT ge 0x0601
GetNumaProcessorNodeEx proto WINAPI :PPROCESSOR_NUMBER, :PUSHORT
endif

GetNumaNodeProcessorMask proto WINAPI :UCHAR, :PULONGLONG
GetNumaAvailableMemoryNode proto WINAPI :UCHAR, :PULONGLONG

if _WIN32_WINNT ge 0x0601
GetNumaAvailableMemoryNodeEx proto WINAPI :USHORT, :PULONGLONG
endif

if (_WIN32_WINNT ge 0x0600)
GetNumaProximityNode proto WINAPI :ULONG, :PUCHAR
endif

CALLBACK(APPLICATION_RECOVERY_CALLBACK, :PVOID)

define RESTART_MAX_CMD_LINE    1024
define RESTART_NO_CRASH        1
define RESTART_NO_HANG         2
define RESTART_NO_PATCH        4
define RESTART_NO_REBOOT       8

define RECOVERY_DEFAULT_PING_INTERVAL  5000
define RECOVERY_MAX_PING_INTERVAL      (5 * 60 * 1000)

if (_WIN32_WINNT ge 0x0600)
RegisterApplicationRecoveryCallback proto WINAPI :APPLICATION_RECOVERY_CALLBACK, :PVOID, :DWORD, :DWORD
UnregisterApplicationRecoveryCallback proto WINAPI
RegisterApplicationRestart proto WINAPI :PCWSTR, :DWORD
UnregisterApplicationRestart proto WINAPI
endif

if (_WIN32_WINNT ge 0x0600)
GetApplicationRecoveryCallback proto WINAPI :HANDLE, :ptr, :ptr, :PDWORD, :PDWORD
GetApplicationRestartSettings proto WINAPI :HANDLE, :PWSTR, :PDWORD, :PDWORD
endif

if (_WIN32_WINNT ge 0x0600)
ApplicationRecoveryInProgress proto WINAPI :PBOOL
ApplicationRecoveryFinished proto WINAPI :BOOL
endif

if (_WIN32_WINNT ge 0x0600)

FILE_BASIC_INFO         struct
CreationTime            LARGE_INTEGER <>
LastAccessTime          LARGE_INTEGER <>
LastWriteTime           LARGE_INTEGER <>
ChangeTime              LARGE_INTEGER <>
FileAttributes          DWORD ?
FILE_BASIC_INFO         ends
PFILE_BASIC_INFO        typedef ptr FILE_BASIC_INFO

FILE_STANDARD_INFO      struct
AllocationSize          LARGE_INTEGER <>
EndOfFile               LARGE_INTEGER <>
NumberOfLinks           DWORD ?
DeletePending           BOOLEAN ?
Directory               BOOLEAN ?
FILE_STANDARD_INFO      ends
PFILE_STANDARD_INFO     typedef ptr FILE_STANDARD_INFO

FILE_NAME_INFO          struct
FileNameLength          DWORD ?
FileName                WCHAR 1 dup(?)
FILE_NAME_INFO          ends
PFILE_NAME_INFO         typedef ptr FILE_NAME_INFO

FILE_CASE_SENSITIVE_INFO struct
Flags                   ULONG ?
FILE_CASE_SENSITIVE_INFO ends
PFILE_CASE_SENSITIVE_INFO typedef ptr FILE_CASE_SENSITIVE_INFO

if (_WIN32_WINNT ge _WIN32_WINNT_WIN10_RS1)
define FILE_RENAME_FLAG_REPLACE_IF_EXISTS                  0x00000001
define FILE_RENAME_FLAG_POSIX_SEMANTICS                    0x00000002
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN10_RS3)
define FILE_RENAME_FLAG_SUPPRESS_PIN_STATE_INHERITANCE     0x00000004
endif

FILE_RENAME_INFO        struct
if (_WIN32_WINNT ge _WIN32_WINNT_WIN10_RS1)
union
 ReplaceIfExists        BOOLEAN ?
 Flags                  DWORD ?
ends
else
ReplaceIfExists         BOOLEAN ?
endif
RootDirectory           HANDLE ?
FileNameLength          DWORD ?
FileName                WCHAR 1 dup(?)
FILE_RENAME_INFO        ends
PFILE_RENAME_INFO       typedef ptr FILE_RENAME_INFO

FILE_ALLOCATION_INFO    struct
AllocationSize          LARGE_INTEGER <>
FILE_ALLOCATION_INFO    ends
PFILE_ALLOCATION_INFO   typedef ptr FILE_ALLOCATION_INFO

FILE_END_OF_FILE_INFO   struct
EndOfFile               LARGE_INTEGER <>
FILE_END_OF_FILE_INFO   ends
PFILE_END_OF_FILE_INFO  typedef ptr FILE_END_OF_FILE_INFO

FILE_STREAM_INFO        struct
NextEntryOffset         DWORD ?
StreamNameLength        DWORD ?
StreamSize              LARGE_INTEGER <>
StreamAllocationSize    LARGE_INTEGER <>
StreamName              WCHAR 1 dup(?)
FILE_STREAM_INFO        ends
PFILE_STREAM_INFO       typedef ptr FILE_STREAM_INFO

FILE_COMPRESSION_INFO   struct
CompressedFileSize      LARGE_INTEGER <>
CompressionFormat       WORD ?
CompressionUnitShift    UCHAR ?
ChunkShift              UCHAR ?
ClusterShift            UCHAR ?
Reserved                UCHAR 3 dup(?)
FILE_COMPRESSION_INFO   ends
PFILE_COMPRESSION_INFO  typedef ptr FILE_COMPRESSION_INFO

FILE_ATTRIBUTE_TAG_INFO struct
FileAttributes          DWORD ?
ReparseTag              DWORD ?
FILE_ATTRIBUTE_TAG_INFO ends
PFILE_ATTRIBUTE_TAG_INFO typedef ptr FILE_ATTRIBUTE_TAG_INFO

FILE_DISPOSITION_INFO   struct
DeleteFile              BOOLEAN ?
FILE_DISPOSITION_INFO   ends
PFILE_DISPOSITION_INFO  typedef ptr FILE_DISPOSITION_INFO

if (_WIN32_WINNT ge _WIN32_WINNT_WIN10_RS1)
define FILE_DISPOSITION_FLAG_DO_NOT_DELETE              0x00000000
define FILE_DISPOSITION_FLAG_DELETE                     0x00000001
define FILE_DISPOSITION_FLAG_POSIX_SEMANTICS            0x00000002
define FILE_DISPOSITION_FLAG_FORCE_IMAGE_SECTION_CHECK  0x00000004
define FILE_DISPOSITION_FLAG_ON_CLOSE                   0x00000008
if (_WIN32_WINNT ge _WIN32_WINNT_WIN10_RS5)
define FILE_DISPOSITION_FLAG_IGNORE_READONLY_ATTRIBUTE  0x00000010
endif

FILE_DISPOSITION_INFO_EX struct
Flags                   DWORD ?
FILE_DISPOSITION_INFO_EX ends
PFILE_DISPOSITION_INFO_EX typedef ptr FILE_DISPOSITION_INFO_EX
endif

FILE_ID_BOTH_DIR_INFO   struct
NextEntryOffset         DWORD ?
FileIndex               DWORD ?
CreationTime            LARGE_INTEGER <>
LastAccessTime          LARGE_INTEGER <>
LastWriteTime           LARGE_INTEGER <>
ChangeTime              LARGE_INTEGER <>
EndOfFile               LARGE_INTEGER <>
AllocationSize          LARGE_INTEGER <>
FileAttributes          DWORD ?
FileNameLength          DWORD ?
EaSize                  DWORD ?
ShortNameLength         CCHAR ?
ShortName               WCHAR 12 dup(?)
FileId                  LARGE_INTEGER <>
FileName                WCHAR 1 dup(?)
FILE_ID_BOTH_DIR_INFO   ends
PFILE_ID_BOTH_DIR_INFO  typedef ptr FILE_ID_BOTH_DIR_INFO

FILE_FULL_DIR_INFO      struct
NextEntryOffset         ULONG ?
FileIndex               ULONG ?
CreationTime            LARGE_INTEGER <>
LastAccessTime          LARGE_INTEGER <>
LastWriteTime           LARGE_INTEGER <>
ChangeTime              LARGE_INTEGER <>
EndOfFile               LARGE_INTEGER <>
AllocationSize          LARGE_INTEGER <>
FileAttributes          ULONG ?
FileNameLength          ULONG ?
EaSize                  ULONG ?
FileName                WCHAR 1 dup(?)
FILE_FULL_DIR_INFO      ends
PFILE_FULL_DIR_INFO     typedef ptr FILE_FULL_DIR_INFO

.enum PRIORITY_HINT {
    IoPriorityHintVeryLow = 0,
    IoPriorityHintLow,
    IoPriorityHintNormal,
    MaximumIoPriorityHintType
    }

FILE_IO_PRIORITY_HINT_INFO struct
PriorityHint            PRIORITY_HINT ?
FILE_IO_PRIORITY_HINT_INFO ends
PFILE_IO_PRIORITY_HINT_INFO typedef ptr FILE_IO_PRIORITY_HINT_INFO

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)

FILE_ALIGNMENT_INFO     struct
AlignmentRequirement    ULONG ?
FILE_ALIGNMENT_INFO     ends
PFILE_ALIGNMENT_INFO    typedef ptr FILE_ALIGNMENT_INFO

define STORAGE_INFO_FLAGS_ALIGNED_DEVICE                 0x00000001
define STORAGE_INFO_FLAGS_PARTITION_ALIGNED_ON_DEVICE    0x00000002
define STORAGE_INFO_OFFSET_UNKNOWN (0xffffffff)

FILE_STORAGE_INFO       struct
LogicalBytesPerSector   ULONG ?
PhysicalBytesPerSectorForAtomicity ULONG ?
PhysicalBytesPerSectorForPerformance ULONG ?
FileSystemEffectivePhysicalBytesPerSectorForAtomicity ULONG ?
Flags                   ULONG ?
ByteOffsetForSectorAlignment ULONG ?
ByteOffsetForPartitionAlignment ULONG ?
FILE_STORAGE_INFO       ends
PFILE_STORAGE_INFO      typedef ptr FILE_STORAGE_INFO

FILE_ID_INFO            struct
VolumeSerialNumber      ULONGLONG ?
FileId                  FILE_ID_128 <>
FILE_ID_INFO            ends
PFILE_ID_INFO           typedef ptr FILE_ID_INFO

FILE_ID_EXTD_DIR_INFO   struct
NextEntryOffset         ULONG ?
FileIndex               ULONG ?
CreationTime            LARGE_INTEGER <>
LastAccessTime          LARGE_INTEGER <>
LastWriteTime           LARGE_INTEGER <>
ChangeTime              LARGE_INTEGER <>
EndOfFile               LARGE_INTEGER <>
AllocationSize          LARGE_INTEGER <>
FileAttributes          ULONG ?
FileNameLength          ULONG ?
EaSize                  ULONG ?
ReparsePointTag         ULONG ?
FileId                  FILE_ID_128 <>
FileName                WCHAR 1 dup(?)
FILE_ID_EXTD_DIR_INFO   ends
PFILE_ID_EXTD_DIR_INFO  typedef ptr FILE_ID_EXTD_DIR_INFO

endif

define REMOTE_PROTOCOL_INFO_FLAG_LOOPBACK              0x00000001
define REMOTE_PROTOCOL_INFO_FLAG_OFFLINE               0x00000002

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
define REMOTE_PROTOCOL_INFO_FLAG_PERSISTENT_HANDLE     0x00000004
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
define RPI_FLAG_SMB2_SHARECAP_TIMEWARP                0x00000002
define RPI_FLAG_SMB2_SHARECAP_DFS                     0x00000008
define RPI_FLAG_SMB2_SHARECAP_CONTINUOUS_AVAILABILITY 0x00000010
define RPI_FLAG_SMB2_SHARECAP_SCALEOUT                0x00000020
define RPI_FLAG_SMB2_SHARECAP_CLUSTER                 0x00000040
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
define RPI_SMB2_FLAG_SERVERCAP_DFS                    0x00000001
define RPI_SMB2_FLAG_SERVERCAP_LEASING                0x00000002
define RPI_SMB2_FLAG_SERVERCAP_LARGEMTU               0x00000004
define RPI_SMB2_FLAG_SERVERCAP_MULTICHANNEL           0x00000008
define RPI_SMB2_FLAG_SERVERCAP_PERSISTENT_HANDLES     0x00000010
define RPI_SMB2_FLAG_SERVERCAP_DIRECTORY_LEASING      0x00000020
endif

FILE_REMOTE_PROTOCOL_INFO struct
StructureVersion        USHORT ?
StructureSize           USHORT ?
Protocol                ULONG ?
ProtocolMajorVersion    USHORT ?
ProtocolMinorVersion    USHORT ?
ProtocolRevision        USHORT ?
Reserved                USHORT ?
Flags                   ULONG ?
struct GenericReserved
 Reserved               ULONG 8 dup(?)
ends
if (_WIN32_WINNT lt _WIN32_WINNT_WIN8)
struct ProtocolSpecificReserved
 Reserved               ULONG 16 dup(?)
ends
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
union ProtocolSpecific
 struct Smb2
  struct Server
   Capabilities         ULONG ?
  ends
  struct Share
   Capabilities         ULONG ?
   CachingFlags         ULONG ?
  ends
 ends
 Reserved               ULONG 16 dup(?)
ends
endif
FILE_REMOTE_PROTOCOL_INFO ends
PFILE_REMOTE_PROTOCOL_INFO typedef ptr FILE_REMOTE_PROTOCOL_INFO

GetFileInformationByHandleEx proto WINAPI :HANDLE, :FILE_INFO_BY_HANDLE_CLASS, :LPVOID, :DWORD

.enum FILE_ID_TYPE {
    FileIdType,
    ObjectIdType,
    ExtendedFileIdType,
    MaximumFileIdType
    }

FILE_ID_DESCRIPTOR      struct
dwSize                  DWORD ?
Type                    FILE_ID_TYPE ?
union
 FileId                 LARGE_INTEGER <>
 ObjectId               GUID <>
if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
 ExtendedFileId         FILE_ID_128 <>
endif
ends
FILE_ID_DESCRIPTOR      ends
LPFILE_ID_DESCRIPTOR    typedef ptr FILE_ID_DESCRIPTOR

OpenFileById proto WINAPI :HANDLE, :LPFILE_ID_DESCRIPTOR, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES, :DWORD

endif ; (_WIN32_WINNT ge 0x0600)


if (_WIN32_WINNT ge 0x0600)

define SYMBOLIC_LINK_FLAG_DIRECTORY                    (0x1)
define SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE    (0x2)

CreateSymbolicLinkA proto WINAPI :LPCSTR, :LPCSTR, :DWORD
CreateSymbolicLinkW proto WINAPI :LPCWSTR, :LPCWSTR, :DWORD
ifdef _UNICODE
define CreateSymbolicLink  <CreateSymbolicLinkW>
else
define CreateSymbolicLink  <CreateSymbolicLinkA>
endif

endif

if (_WIN32_WINNT ge 0x0600)
QueryActCtxSettingsW proto WINAPI :DWORD, :HANDLE, :PCWSTR, :PCWSTR, :PWSTR, :SIZE_T, :ptr
endif

if (_WIN32_WINNT ge 0x0600)
CreateSymbolicLinkTransactedA proto WINAPI :LPCSTR, :LPCSTR, :DWORD, :HANDLE
CreateSymbolicLinkTransactedW proto WINAPI :LPCWSTR, :LPCWSTR, :DWORD, :HANDLE
ifdef _UNICODE
define CreateSymbolicLinkTransacted  <CreateSymbolicLinkTransactedW>
else
define CreateSymbolicLinkTransacted  <CreateSymbolicLinkTransactedA>
endif
endif

if (_WIN32_WINNT ge 0x0600)
ReplacePartitionUnit proto WINAPI :PWSTR, :PWSTR, :ULONG
endif

if (_WIN32_WINNT ge 0x0600)
AddSecureMemoryCacheCallback proto WINAPI :PSECURE_MEMORY_CACHE_CALLBACK
RemoveSecureMemoryCacheCallback proto WINAPI :PSECURE_MEMORY_CACHE_CALLBACK
endif

if (NTDDI_VERSION ge NTDDI_WIN7SP1)

CopyContext proto WINAPI :PCONTEXT, :DWORD, :PCONTEXT

InitializeContext proto WINAPI :PVOID, :DWORD, :ptr, :PDWORD

if (NTDDI_VERSION ge NTDDI_WIN10_RS5)
InitializeContext2 proto WINAPI :PVOID, :DWORD, :ptr, :PDWORD, :ULONG64
endif

if defined(_AMD64_) or defined(_X86_)
GetEnabledXStateFeatures proto WINAPI
GetXStateFeaturesMask proto WINAPI :PCONTEXT, :PDWORD64
LocateXStateFeature proto WINAPI :PCONTEXT, :DWORD, :PDWORD
SetXStateFeaturesMask proto WINAPI :PCONTEXT, :DWORD64
endif

endif ; (NTDDI_VERSION ge NTDDI_WIN7SP1)

if (_WIN32_WINNT ge 0x0601)
EnableThreadProfiling proto WINAPI :HANDLE, :DWORD, :DWORD64, :ptr
DisableThreadProfiling proto WINAPI :HANDLE
QueryThreadProfiling proto WINAPI :HANDLE, :PBOOLEAN
ReadThreadProfilingData proto WINAPI :HANDLE, :DWORD, :PPERFORMANCE_DATA
endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS4)
RaiseCustomSystemEventTrigger proto WINAPI :PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG
endif

ifndef RC_INVOKED
if defined(ISOLATION_AWARE_ENABLED) and (ISOLATION_AWARE_ENABLED ne 0)
include winbase.inl
endif
endif

ifdef _WIN64
.pragma pack(pop)
endif
endif ; _WINBASE_


ifndef RC_INVOKED
ifndef NOWINBASEINTERLOCK
ifndef _NTOS_

ifndef RC_INVOKED

ifndef MICROSOFT_WINDOWS_WINBASE_INTERLOCKED_CPLUSPLUS_H_INCLUDED
define MICROSOFT_WINDOWS_WINBASE_INTERLOCKED_CPLUSPLUS_H_INCLUDED

ifndef MIDL_PASS

ifndef MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS
define MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS (_WIN32_WINNT ge 0x0501 or not defined(_WINBASE_))
endif

if MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS

;ifdef __cplusplus

InterlockedIncrement proto watcall :ptr {
    lock    inc dword ptr [rax]
    mov     eax,[rax]
    }

if (defined(_WIN64) and not defined(_ARM64_)) or ((_WIN32_WINNT ge 0x0502) and defined(_WINBASE_) and not defined(_MANAGED))
InterlockedIncrement64 proto watcall :ptr {
    lock    inc qword ptr [rax]
    mov     rax,[rax]
    }
endif

InterlockedDecrement proto watcall :ptr {
    lock    dec dword ptr [rax]
    mov     eax,[rax]
    }

if (defined(_WIN64) and not defined(_ARM64_)) or ((_WIN32_WINNT ge 0x0502) and defined(_WINBASE_) and not defined(_MANAGED))
InterlockedDecrement64 proto watcall :ptr {
    lock dec qword ptr [rax]
    mov rax,[rax]
    }
endif

ifndef _M_CEE_PURE

InterlockedExchange proto watcall :ptr, :ptr {
    xchg    [rax],edx
    mov     eax,edx
    }

if defined(_WIN64) or ((_WIN32_WINNT ge 0x0502) and defined(_WINBASE_) and not defined(_MANAGED))
InterlockedExchange64 proto watcall :ptr, :ptr {
    xchg    [rax],rdx
    mov     rax,rdx
    }
endif

InterlockedExchangeAdd proto WINAPI :ptr LONG, :LONG

if defined(_WIN64) or ((_WIN32_WINNT ge 0x0502) and defined(_WINBASE_) and not defined(_MANAGED))
InterlockedExchangeAdd64 proto WINAPI :ptr LONGLONG, :LONGLONG
endif

InterlockedCompareExchange proto fastcall :ptr, :sdword, :sdword {
    mov     eax,r8d
    push    [rcx]
    lock    cmpxchg dword ptr [rcx],edx
    pop     rax
    }

if defined(_WIN64) or ((_WIN32_WINNT ge 0x0502) and defined(_WINBASE_) and not defined(_MANAGED))
InterlockedCompareExchange64 proto fastcall :ptr, :qword, :qword {
    mov     rax,r8
    push    [rcx]
    lock    cmpxchg qword ptr [rcx],rdx
    pop     rax
    }
InterlockedAnd64 proto fastcall :ptr, :qword {
    mov     rax,[rcx]
    lock    and [rcx],rdx
    }
InterlockedOr64 proto fastcall :ptr, :qword {
    mov     rax,[rcx]
    lock    or [rcx],rdx
    }
InterlockedXor64 proto fastcall :ptr, :qword {
    mov     rax,[rcx]
    lock    xor [rcx],rdx
    }
endif

endif ; !_M_CEE_PURE
;endif ; __cplusplus
endif ; MICROSOFT_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS

undef MICROSOFT_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS
define MICROSOFT_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS 0

endif ; MIDL_PASS
endif ; MICROSOFT_WINDOWS_WINBASE_INTERLOCKED_CPLUSPLUS_H_INCLUDED
endif ; RC_INVOKED
endif ; _NTOS_
endif ; NOWINBASEINTERLOCK
endif ; RC_INVOKED

.pragma list(pop)


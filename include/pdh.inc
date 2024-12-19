ifndef _PDH_H_
define _PDH_H_
include windows.inc
include winperf.inc
.pragma list(push, 0)
.pragma comment(lib, pdh)

PDH_STATUS		typedef LONG
PDH_FUNCTION		equ PDH_STATUS ;__stdcall

PDH_CVERSION_WIN40	equ 0x0400
PDH_CVERSION_WIN50	equ 0x0500
PDH_VERSION		equ PDH_CVERSION_WIN50 + 0x0003

IsSuccessSeverity macro ErrorCode
    if ((ErrorCode) AND 0xC0000000) EQ 0x00000000
	exitm<TRUE>
    else
	exitm<FALSE>
    endif
    endm
IsInformationalSeverity macro ErrorCode
    if ((ErrorCode) AND 0xC0000000) EQ 0x40000000
	exitm<TRUE>
    else
	exitm<FALSE>
    endif
    endm
IsWarningSeverity macro ErrorCode
    if ((ErrorCode) AND 0xC0000000) EQ 0x80000000
	exitm<TRUE>
    else
	exitm<FALSE>
    endif
    endm
IsErrorSeverity macro ErrorCode
    if ((ErrorCode) AND 0xC0000000) EQ 0xC0000000
	exitm<TRUE>
    else
	exitm<FALSE>
    endif
    endm

if (_WIN32_WINDOWS GE 0x0501 OR _WIN32_WINNT GE 0x0501 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WINXP))
MAX_COUNTER_PATH	equ 256
if (_WIN32_WINDOWS GE 0x0502 OR _WIN32_WINNT GE 0x0502 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WIN2003))
PDH_MAX_COUNTER_NAME	equ 1024
PDH_MAX_INSTANCE_NAME	equ 1024
PDH_MAX_COUNTER_PATH	equ 2048
PDH_MAX_DATASOURCE_PATH equ 1024
endif
PDH_OBJECT_HAS_INSTANCES equ 0x00000001
endif

PDH_HCOUNTER		typedef HANDLE
PDH_HQUERY		typedef HANDLE
PDH_HLOG		typedef HANDLE

HCOUNTER		typedef PDH_HCOUNTER
HQUERY			typedef PDH_HQUERY
ifndef _LMHLOGDEFINED_
HLOG			typedef PDH_HLOG
endif

ifdef INVALID_HANDLE_VALUE
undef INVALID_HANDLE_VALUE
INVALID_HANDLE_VALUE	equ (-1)
endif

H_REALTIME_DATASOURCE	equ NULL
H_WBEM_DATASOURCE	equ INVALID_HANDLE_VALUE

.pragma pack(push, size_t)

PDH_RAW_COUNTER		STRUC
CStatus			DWORD ?
TimeStamp		FILETIME <>
FirstValue		LONGLONG ?
SecondValue		LONGLONG ?
MultiCount		dd ?
PDH_RAW_COUNTER		ENDS
PPDH_RAW_COUNTER	typedef ptr PDH_RAW_COUNTER

PDH_RAW_COUNTER_ITEM_A	STRUC
szName			LPSTR ?
RawValue		PDH_RAW_COUNTER <>
PDH_RAW_COUNTER_ITEM_A	ENDS
PPDH_RAW_COUNTER_ITEM_A typedef ptr PDH_RAW_COUNTER_ITEM_A

PDH_RAW_COUNTER_ITEM_W	STRUC
szName			LPWSTR ?
RawValue		PDH_RAW_COUNTER <>
PDH_RAW_COUNTER_ITEM_W	ENDS
PPDH_RAW_COUNTER_ITEM_W typedef ptr PDH_RAW_COUNTER_ITEM_W

PDH_FMT_COUNTERVALUE	STRUC
CStatus			dd ?
UNION ; {
longValue		LONG ?
doubleValue		REAL8 ?
largeValue		LONGLONG ?
AnsiStringValue		LPCSTR ?
WideStringValue		LPCWSTR ?
ENDS ;
PDH_FMT_COUNTERVALUE	ENDS
PPDH_FMT_COUNTERVALUE	typedef ptr PDH_FMT_COUNTERVALUE

PDH_FMT_COUNTERVALUE_ITEM_A  STRUC
szName			LPSTR ?
FmtValue		PDH_FMT_COUNTERVALUE <>
PDH_FMT_COUNTERVALUE_ITEM_A ENDS
PPDH_FMT_COUNTERVALUE_ITEM_A typedef ptr PDH_FMT_COUNTERVALUE_ITEM_A

PDH_FMT_COUNTERVALUE_ITEM_W  STRUC
szName			LPWSTR ?
FmtValue		PDH_FMT_COUNTERVALUE <>
PDH_FMT_COUNTERVALUE_ITEM_W ENDS
PPDH_FMT_COUNTERVALUE_ITEM_W typedef ptr PDH_FMT_COUNTERVALUE_ITEM_W

PDH_STATISTICS		STRUC
dwFormat		dd ?
count			dd ?
min			PDH_FMT_COUNTERVALUE <>
max			PDH_FMT_COUNTERVALUE <>
mean			PDH_FMT_COUNTERVALUE <>
PDH_STATISTICS		ENDS
PPDH_STATISTICS typedef ptr PDH_STATISTICS

PDH_COUNTER_PATH_ELEMENTS_A  STRUC
szMachineName		LPSTR ?
szObjectName		LPSTR ?
szInstanceName		LPSTR ?
szParentInstance	LPSTR ?
dwInstanceIndex		dd ?
szCounterName		LPSTR ?
PDH_COUNTER_PATH_ELEMENTS_A ENDS
PPDH_COUNTER_PATH_ELEMENTS_A typedef ptr PDH_COUNTER_PATH_ELEMENTS_A

PDH_COUNTER_PATH_ELEMENTS_W  STRUC
szMachineName		LPWSTR ?
szObjectName		LPWSTR ?
szInstanceName		LPWSTR ?
szParentInstance	LPWSTR ?
dwInstanceIndex		dd ?
szCounterName		LPWSTR ?
PDH_COUNTER_PATH_ELEMENTS_W ENDS
PPDH_COUNTER_PATH_ELEMENTS_W typedef ptr PDH_COUNTER_PATH_ELEMENTS_W

PDH_DATA_ITEM_PATH_ELEMENTS_A  STRUC
szMachineName		LPSTR ?
ObjectGUID		GUID <>
dwItemId		dd ?
szInstanceName		LPSTR ?
PDH_DATA_ITEM_PATH_ELEMENTS_A ENDS
PPDH_DATA_ITEM_PATH_ELEMENTS_A typedef ptr PDH_DATA_ITEM_PATH_ELEMENTS_A

PDH_DATA_ITEM_PATH_ELEMENTS_W  STRUC
szMachineName		LPWSTR ?
ObjectGUID		GUID <>
dwItemId		dd ?
szInstanceName		LPWSTR ?
PDH_DATA_ITEM_PATH_ELEMENTS_W ENDS
PPDH_DATA_ITEM_PATH_ELEMENTS_W typedef ptr PDH_DATA_ITEM_PATH_ELEMENTS_W

PDH_COUNTER_INFO_A	STRUC
dwLength		dd ?
dwType			dd ?
CVersion		dd ?
CStatus			dd ?
lScale			LONG ?
lDefaultScale		LONG ?
dwUserData		dd ?
dwQueryUserData		dd ?
szFullPath		LPSTR ?
UNION ; {
 DataItemPath		PDH_DATA_ITEM_PATH_ELEMENTS_A <>
 CounterPath		PDH_COUNTER_PATH_ELEMENTS_A <>
 STRUC
  szMachineName		LPSTR ?
  szObjectName		LPSTR ?
  szInstanceName		LPSTR ?
  szParentInstance	LPSTR ?
  dwInstanceIndex		dd ?
  szCounterName		LPSTR ?
 ENDS
ENDS
szExplainText		LPSTR ?
DataBuffer		dd 1 dup(?)
PDH_COUNTER_INFO_A	ENDS
PPDH_COUNTER_INFO_A	typedef ptr PDH_COUNTER_INFO_A

PDH_COUNTER_INFO_W	STRUC
dwLength		dd ?
dwType			dd ?
CVersion		dd ?
CStatus			dd ?
lScale			LONG ?
lDefaultScale		LONG ?
dwUserData		dd ?
dwQueryUserData		dd ?
szFullPath		LPWSTR ?
UNION
 DataItemPath		PDH_DATA_ITEM_PATH_ELEMENTS_W <>
 CounterPath		PDH_COUNTER_PATH_ELEMENTS_W <>
 STRUC
  szMachineName		LPWSTR ?
  szObjectName		LPWSTR ?
  szInstanceName	LPWSTR ?
  szParentInstance	LPWSTR ?
  dwInstanceIndex	dd ?
  szCounterName		LPWSTR ?
 ENDS
ENDS
szExplainText		LPWSTR ?
DataBuffer		dd 1 dup(?)
PDH_COUNTER_INFO_W	ENDS
PPDH_COUNTER_INFO_W	typedef ptr PDH_COUNTER_INFO_W

PDH_TIME_INFO		STRUC
StartTime		LONGLONG ?
EndTime			LONGLONG ?
SampleCount		dd ?
PDH_TIME_INFO		ENDS
PPDH_TIME_INFO		typedef ptr PDH_TIME_INFO

PDH_RAW_LOG_RECORD	STRUC
dwStructureSize		dd ?
dwRecordType		dd ?
dwItems			dd ?
RawBytes		UCHAR 1 dup(?)
PDH_RAW_LOG_RECORD	ENDS
PPDH_RAW_LOG_RECORD	typedef ptr PDH_RAW_LOG_RECORD

PDH_LOG_SERVICE_QUERY_INFO_A  STRUC
dwSize			dd ?
dwFlags			dd ?
dwLogQuota		dd ?
szLogFileCaption	LPSTR ?
szDefaultDir		LPSTR ?
szBaseFileName		LPSTR ?
dwFileType		dd ?
dwReserved		dd ?
UNION
 STRUC
  PdlAutoNameInterval	dd ?
  PdlAutoNameUnits	dd ?
  PdlCommandFilename	LPSTR ?
  PdlCounterList	LPSTR ?
  PdlAutoNameFormat	dd ?
  PdlSampleInterval	dd ?
  PdlLogStartTime	FILETIME <>
  PdlLogEndTime		FILETIME <>
 ENDS
 STRUC
  TlNumberOfBuffers	dd ?
  TlMinimumBuffers	dd ?
  TlMaximumBuffers	dd ?
  TlFreeBuffers		dd ?
  TlBufferSize		dd ?
  TlEventsLost		dd ?
  TlLoggerThreadId	dd ?
  TlBuffersWritten	dd ?
  TlLogHandle		dd ?
  TlLogFileName		LPSTR ?
 ENDS
ENDS
PDH_LOG_SERVICE_QUERY_INFO_A ENDS
PPDH_LOG_SERVICE_QUERY_INFO_A typedef ptr PDH_LOG_SERVICE_QUERY_INFO_A

PDH_LOG_SERVICE_QUERY_INFO_W  STRUC
dwSize			dd ?
dwFlags			dd ?
dwLogQuota		dd ?
szLogFileCaption	LPWSTR ?
szDefaultDir		LPWSTR ?
szBaseFileName		LPWSTR ?
dwFileType		dd ?
dwReserved		dd ?
UNION
 STRUC
  PdlAutoNameInterval	dd ?
  PdlAutoNameUnits	dd ?
  PdlCommandFilename	LPWSTR ?
  PdlCounterList	LPWSTR ?
  PdlAutoNameFormat	dd ?
  PdlSampleInterval	dd ?
  PdlLogStartTime	FILETIME <>
  PdlLogEndTime		FILETIME <>
 ENDS
 STRUC
  TlNumberOfBuffers	dd ?
  TlMinimumBuffers	dd ?
  TlMaximumBuffers	dd ?
  TlFreeBuffers		dd ?
  TlBufferSize		dd ?
  TlEventsLost		dd ?
  TlLoggerThreadId	dd ?
  TlBuffersWritten	dd ?
  TlLogHandle		dd ?
  TlLogFileName		LPWSTR ?
 ENDS
ENDS
PDH_LOG_SERVICE_QUERY_INFO_W ENDS
PPDH_LOG_SERVICE_QUERY_INFO_W typedef ptr PDH_LOG_SERVICE_QUERY_INFO_W

MAX_TIME_VALUE		equ 0x7FFFFFFFFFFFFFFF
MIN_TIME_VALUE		equ 0

PdhGetDllVersion proto WINAPI :LPDWORD
PdhOpenQueryW proto WINAPI :LPCWSTR, :DWORD_PTR, :ptr
PdhOpenQueryA proto WINAPI :LPCSTR, :DWORD_PTR, :ptr
PdhAddCounterW proto WINAPI :PDH_HQUERY, :LPCWSTR, :DWORD_PTR, :ptr
PdhAddCounterA proto WINAPI :PDH_HQUERY, :LPCSTR, :DWORD_PTR, :ptr

if (_WIN32_WINDOWS GE 0x0600 OR _WIN32_WINNT GE 0x0600 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_VISTA))
PdhAddEnglishCounterW proto WINAPI :PDH_HQUERY, :LPCWSTR, :DWORD_PTR, :ptr
PdhAddEnglishCounterA proto WINAPI :PDH_HQUERY, :LPCSTR, :DWORD_PTR, :ptr
PdhCollectQueryDataWithTime proto WINAPI :PDH_HQUERY, :ptr
PdhValidatePathExW proto WINAPI :PDH_HLOG, :LPCWSTR
PdhValidatePathExA proto WINAPI :PDH_HLOG, :LPCSTR
endif
PdhRemoveCounter proto WINAPI :PDH_HCOUNTER
PdhCollectQueryData proto WINAPI :PDH_HQUERY
PdhCloseQuery proto WINAPI :PDH_HQUERY
PdhGetFormattedCounterValue proto WINAPI :PDH_HCOUNTER, :DWORD, :LPDWORD, :PPDH_FMT_COUNTERVALUE
PdhGetFormattedCounterArrayA proto WINAPI :PDH_HCOUNTER, :DWORD, :LPDWORD, :LPDWORD, :PPDH_FMT_COUNTERVALUE_ITEM_A
PdhGetFormattedCounterArrayW proto WINAPI :PDH_HCOUNTER, :DWORD, :LPDWORD, :LPDWORD, :PPDH_FMT_COUNTERVALUE_ITEM_W

PDH_FMT_RAW		equ 0x00000010
PDH_FMT_ANSI		equ 0x00000020
PDH_FMT_UNICODE		equ 0x00000040
PDH_FMT_LONG		equ 0x00000100
PDH_FMT_DOUBLE		equ 0x00000200
PDH_FMT_LARGE		equ 0x00000400
PDH_FMT_NOSCALE		equ 0x00001000
PDH_FMT_1000		equ 0x00002000
PDH_FMT_NODATA		equ 0x00004000
PDH_FMT_NOCAP100	equ 0x00008000
PERF_DETAIL_COSTLY	equ 0x00010000
PERF_DETAIL_STANDARD	equ 0x0000FFFF

PdhGetRawCounterValue proto WINAPI :PDH_HCOUNTER, :LPDWORD, :PPDH_RAW_COUNTER
PdhGetRawCounterArrayA proto WINAPI :PDH_HCOUNTER, :LPDWORD, :LPDWORD, :PPDH_RAW_COUNTER_ITEM_A
PdhGetRawCounterArrayW proto WINAPI :PDH_HCOUNTER, :LPDWORD, :LPDWORD, :PPDH_RAW_COUNTER_ITEM_W
PdhCalculateCounterFromRawValue proto WINAPI :PDH_HCOUNTER, :DWORD, :PPDH_RAW_COUNTER, :PPDH_RAW_COUNTER, :PPDH_FMT_COUNTERVALUE
PdhComputeCounterStatistics proto WINAPI :PDH_HCOUNTER, :DWORD, :DWORD, :DWORD, :PPDH_RAW_COUNTER, :PPDH_STATISTICS
PdhGetCounterInfoW proto WINAPI :PDH_HCOUNTER, :BOOLEAN, :LPDWORD, :PPDH_COUNTER_INFO_W
PdhGetCounterInfoA proto WINAPI :PDH_HCOUNTER, :BOOLEAN, :LPDWORD, :PPDH_COUNTER_INFO_A

PDH_MAX_SCALE		equ (7)
PDH_MIN_SCALE		equ (-7)

PdhSetCounterScaleFactor proto WINAPI :PDH_HCOUNTER, :LONG
PdhConnectMachineW proto WINAPI :LPCWSTR
PdhConnectMachineA proto WINAPI :LPCSTR
PdhEnumMachinesW proto WINAPI :LPCWSTR, :PZZWSTR, :LPDWORD
PdhEnumMachinesA proto WINAPI :LPCSTR, :PZZSTR, :LPDWORD
PdhEnumObjectsW proto WINAPI :LPCWSTR, :LPCWSTR, :PZZWSTR, :LPDWORD, :DWORD, :BOOL
PdhEnumObjectsA proto WINAPI :LPCSTR, :LPCSTR, :PZZSTR, :LPDWORD, :DWORD, :BOOL
PdhEnumObjectItemsW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :PZZWSTR, :LPDWORD, :PZZWSTR, :LPDWORD, :DWORD, :DWORD
PdhEnumObjectItemsA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :PZZSTR, :LPDWORD, :PZZSTR, :LPDWORD, :DWORD, :DWORD
PdhMakeCounterPathW proto WINAPI :PPDH_COUNTER_PATH_ELEMENTS_W, :LPWSTR, :LPDWORD, :DWORD
PdhMakeCounterPathA proto WINAPI :PPDH_COUNTER_PATH_ELEMENTS_A, :LPSTR, :LPDWORD, :DWORD
PdhParseCounterPathW proto WINAPI :LPCWSTR, :PPDH_COUNTER_PATH_ELEMENTS_W, :LPDWORD, :DWORD
PdhParseCounterPathA proto WINAPI :LPCSTR, :PPDH_COUNTER_PATH_ELEMENTS_A, :LPDWORD, :DWORD

PDH_PATH_WBEM_RESULT	equ 0x00000001
PDH_PATH_WBEM_INPUT	equ 0x00000002

PDH_PATH_LANG_FLAGS macro LangId, Flags
	exitm<((((LangId AND 0x0000FFFF) SHL 16) OR (Flags AND 0x0000FFFF)))>
	endm

PdhParseInstanceNameW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD, :LPWSTR, :LPDWORD, :LPDWORD
PdhParseInstanceNameA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD, :LPSTR, :LPDWORD, :LPDWORD
PdhValidatePathW proto WINAPI :LPCWSTR
PdhValidatePathA proto WINAPI :LPCSTR
PdhGetDefaultPerfObjectW proto WINAPI :LPCWSTR, :LPCWSTR, :LPWSTR, :LPDWORD
PdhGetDefaultPerfObjectA proto WINAPI :LPCSTR, :LPCSTR, :LPSTR, :LPDWORD
PdhGetDefaultPerfCounterW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPWSTR, :LPDWORD
PdhGetDefaultPerfCounterA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :LPSTR, :LPDWORD

CALLBACK(CounterPathCallBack, :DWORD_PTR)

if (_WIN32_WINDOWS GE 0x0501 OR _WIN32_WINNT GE 0x0501 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WINXP))
PDH_BROWSE_DLG_CONFIG_HW STRUC
flags			dd ?
hWndOwner		HWND ?
hDataSource		PDH_HLOG ?
szReturnPathBuffer	LPWSTR ?
cchReturnPathLength	dd ?
pCallBack		CounterPathCallBack ?
dwCallBackArg		dd ?
CallBackStatus		PDH_STATUS ?
dwDefaultDetailLevel	dd ?
szDialogBoxCaption	LPWSTR ?
PDH_BROWSE_DLG_CONFIG_HW ENDS
PPDH_BROWSE_DLG_CONFIG_HW typedef ptr PDH_BROWSE_DLG_CONFIG_HW

PDH_BROWSE_DLG_CONFIG_HA STRUC
flags			dd ?
hWndOwner		HWND ?
hDataSource		PDH_HLOG ?
szReturnPathBuffer	LPSTR ?
cchReturnPathLength	dd ?
pCallBack		CounterPathCallBack ?
dwCallBackArg		dd ?
CallBackStatus		PDH_STATUS ?
dwDefaultDetailLevel	dd ?
szDialogBoxCaption	LPSTR ?
PDH_BROWSE_DLG_CONFIG_HA ENDS
PPDH_BROWSE_DLG_CONFIG_HA typedef ptr PDH_BROWSE_DLG_CONFIG_HA

PDH_BROWSE_DLG_CONFIG_W STRUC
flags			dd ?
hWndOwner		HWND ?
szDataSource		LPWSTR ?
szReturnPathBuffer	LPWSTR ?
cchReturnPathLength	dd ?
pCallBack		CounterPathCallBack ?
dwCallBackArg		dd ?
CallBackStatus		PDH_STATUS ?
dwDefaultDetailLevel	dd ?
szDialogBoxCaption	LPWSTR ?
PDH_BROWSE_DLG_CONFIG_W ENDS
PPDH_BROWSE_DLG_CONFIG_W typedef ptr PDH_BROWSE_DLG_CONFIG_W

PDH_BROWSE_DLG_CONFIG_A STRUC
flags			dd ?
hWndOwner		HWND ?
szDataSource		LPSTR ?
szReturnPathBuffer	LPSTR ?
cchReturnPathLength	dd ?
pCallBack		CounterPathCallBack ?
dwCallBackArg		dd ?
CallBackStatus		PDH_STATUS ?
dwDefaultDetailLevel	dd ?
szDialogBoxCaption	LPSTR ?
PDH_BROWSE_DLG_CONFIG_A ENDS
PPDH_BROWSE_DLG_CONFIG_A typedef ptr PDH_BROWSE_DLG_CONFIG_A
else

PDH_BROWSE_DLG_CONFIG_W STRUC
flags			dd ?
hWndOwner		HWND ?
szDataSource		LPWSTR ?
szReturnPathBuffer	LPWSTR ?
cchReturnPathLength	dd ?
pCallBack		CounterPathCallBack ?
dwCallBackArg		dd ?
CallBackStatus		PDH_STATUS ?
dwDefaultDetailLevel	dd ?
szDialogBoxCaption	LPWSTR ?
PDH_BROWSE_DLG_CONFIG_W ENDS
PPDH_BROWSE_DLG_CONFIG_W typedef ptr PDH_BROWSE_DLG_CONFIG_W

PDH_BROWSE_DLG_CONFIG_A STRUC
flags			dd ?
hWndOwner		HWND ?
szDataSource		LPSTR ?
szReturnPathBuffer	LPSTR ?
cchReturnPathLength	dd ?
pCallBack		CounterPathCallBack ?
dwCallBackArg		dd ?
CallBackStatus		PDH_STATUS ?
dwDefaultDetailLevel	dd ?
szDialogBoxCaption	LPSTR ?
PDH_BROWSE_DLG_CONFIG_A ENDS
 PPDH_BROWSE_DLG_CONFIG_A typedef ptr PDH_BROWSE_DLG_CONFIG_A
endif

PdhBrowseCountersW proto WINAPI :PPDH_BROWSE_DLG_CONFIG_W
PdhBrowseCountersA proto WINAPI :PPDH_BROWSE_DLG_CONFIG_A
PdhExpandCounterPathW proto WINAPI :LPCWSTR, :PZZWSTR, :LPDWORD
PdhExpandCounterPathA proto WINAPI :LPCSTR, :PZZSTR, :LPDWORD
PdhLookupPerfNameByIndexW proto WINAPI :LPCWSTR, :DWORD, :LPWSTR, :LPDWORD
PdhLookupPerfNameByIndexA proto WINAPI :LPCSTR, :DWORD, :LPSTR, :LPDWORD
PdhLookupPerfIndexByNameW proto WINAPI :LPCWSTR, :LPCWSTR, :LPDWORD
PdhLookupPerfIndexByNameA proto WINAPI :LPCSTR, :LPCSTR, :LPDWORD

PDH_NOEXPANDCOUNTERS	equ 1
PDH_NOEXPANDINSTANCES	equ 2
if (_WIN32_WINDOWS GE 0x0502 OR _WIN32_WINNT GE 0x0502 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WIN2003))
PDH_REFRESHCOUNTERS	equ 4
endif

PdhExpandWildCardPathA proto WINAPI :LPCSTR, :LPCSTR, :PZZSTR, :LPDWORD, :DWORD
PdhExpandWildCardPathW proto WINAPI :LPCWSTR, :LPCWSTR, :PZZWSTR, :LPDWORD, :DWORD

PDH_LOG_READ_ACCESS	equ 0x00010000
PDH_LOG_WRITE_ACCESS	equ 0x00020000
PDH_LOG_UPDATE_ACCESS	equ 0x00040000
PDH_LOG_ACCESS_MASK	equ 0x000F0000

PDH_LOG_CREATE_NEW	equ 0x00000001
PDH_LOG_CREATE_ALWAYS	equ 0x00000002
PDH_LOG_OPEN_ALWAYS	equ 0x00000003
PDH_LOG_OPEN_EXISTING	equ 0x00000004
PDH_LOG_CREATE_MASK	equ 0x0000000F

PDH_LOG_OPT_USER_STRING equ 0x01000000
PDH_LOG_OPT_CIRCULAR	equ 0x02000000
PDH_LOG_OPT_MAX_IS_BYTES equ 0x04000000
if (_WIN32_WINDOWS GE 0x0501 OR _WIN32_WINNT GE 0x0501 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WINXP))
PDH_LOG_OPT_APPEND	equ 0x08000000
endif
PDH_LOG_OPT_MASK	equ 0x0F000000

PDH_LOG_TYPE_UNDEFINED	equ 0
PDH_LOG_TYPE_CSV	equ 1
PDH_LOG_TYPE_TSV	equ 2
PDH_LOG_TYPE_TRACE_KERNEL equ 4
PDH_LOG_TYPE_TRACE_GENERIC equ 5
PDH_LOG_TYPE_PERFMON	equ 6
if (_WIN32_WINDOWS GE 0x0501 OR _WIN32_WINNT GE 0x0501 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WINXP))
PDH_LOG_TYPE_SQL	equ 7
PDH_LOG_TYPE_BINARY	equ 8
else
PDH_LOG_TYPE_BINARY	equ 3
endif

PdhOpenLogW proto WINAPI :LPCWSTR, :DWORD, :LPDWORD, :PDH_HQUERY, :DWORD, :LPCWSTR, :ptr
PdhOpenLogA proto WINAPI :LPCSTR, :DWORD, :LPDWORD, :PDH_HQUERY, :DWORD, :LPCSTR, :ptr
PdhUpdateLogW proto WINAPI :PDH_HLOG, :LPCWSTR
PdhUpdateLogA proto WINAPI :PDH_HLOG, :LPCSTR
PdhUpdateLogFileCatalog proto WINAPI :PDH_HLOG
PdhGetLogFileSize proto WINAPI :PDH_HLOG, :ptr
PdhCloseLog proto WINAPI :PDH_HLOG, :DWORD

PDH_FLAGS_CLOSE_QUERY	equ 0x00000001
PDH_FLAGS_FILE_BROWSER_ONLY equ 0x00000001

PdhSelectDataSourceW proto WINAPI :HWND, :DWORD, :LPWSTR, :LPDWORD
PdhSelectDataSourceA proto WINAPI :HWND, :DWORD, :LPSTR, :LPDWORD
PdhIsRealTimeQuery proto WINAPI :PDH_HQUERY
PdhSetQueryTimeRange proto WINAPI :PDH_HQUERY, :PPDH_TIME_INFO
PdhGetDataSourceTimeRangeW proto WINAPI :LPCWSTR, :LPDWORD, :PPDH_TIME_INFO, :LPDWORD
PdhGetDataSourceTimeRangeA proto WINAPI :LPCSTR, :LPDWORD, :PPDH_TIME_INFO, :LPDWORD
PdhCollectQueryDataEx proto WINAPI :PDH_HQUERY, :DWORD, :HANDLE
PdhFormatFromRawValue proto WINAPI :DWORD, :DWORD, :ptr, :PPDH_RAW_COUNTER, :PPDH_RAW_COUNTER, :PPDH_FMT_COUNTERVALUE
PdhGetCounterTimeBase proto WINAPI :PDH_HCOUNTER, :ptr
PdhReadRawLogRecord proto WINAPI :PDH_HLOG, :FILETIME, :PPDH_RAW_LOG_RECORD, :LPDWORD

DATA_SOURCE_REGISTRY	equ 0x00000001
DATA_SOURCE_LOGFILE	equ 0x00000002
DATA_SOURCE_WBEM	equ 0x00000004

PdhSetDefaultRealTimeDataSource proto WINAPI :DWORD

if (_WIN32_WINDOWS GE 0x0501 OR _WIN32_WINNT GE 0x0501 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WINXP))
PdhBindInputDataSourceW proto WINAPI :ptr, :LPCWSTR
PdhBindInputDataSourceA proto WINAPI :ptr, :LPCSTR
PdhOpenQueryH proto WINAPI :PDH_HLOG, :DWORD_PTR, :ptr
PdhEnumMachinesHW proto WINAPI :PDH_HLOG, :PZZWSTR, :LPDWORD
PdhEnumMachinesHA proto WINAPI :PDH_HLOG, :PZZSTR, :LPDWORD
PdhEnumObjectsHW proto WINAPI :PDH_HLOG, :LPCWSTR, :PZZWSTR, :LPDWORD, :DWORD, :BOOL
PdhEnumObjectsHA proto WINAPI :PDH_HLOG, :LPCSTR, :PZZSTR, :LPDWORD, :DWORD, :BOOL
PdhEnumObjectItemsHW proto WINAPI :PDH_HLOG, :LPCWSTR, :LPCWSTR, :PZZWSTR, :LPDWORD, :PZZWSTR, :LPDWORD, :DWORD, :DWORD
PdhEnumObjectItemsHA proto WINAPI :PDH_HLOG, :LPCSTR, :LPCSTR, :PZZSTR, :LPDWORD, :PZZSTR, :LPDWORD, :DWORD, :DWORD
PdhExpandWildCardPathHW proto WINAPI :PDH_HLOG, :LPCWSTR, :PZZWSTR, :LPDWORD, :DWORD
PdhExpandWildCardPathHA proto WINAPI :PDH_HLOG, :LPCSTR, :PZZSTR, :LPDWORD, :DWORD
PdhGetDataSourceTimeRangeH proto WINAPI :PDH_HLOG, :LPDWORD, :PDH_TIME_INFO, :LPDWORD
PdhGetDefaultPerfObjectHW proto WINAPI :PDH_HLOG, :LPCWSTR, :LPWSTR, :LPDWORD
PdhGetDefaultPerfObjectHA proto WINAPI :PDH_HLOG, :LPCSTR, :LPSTR, :LPDWORD
PdhGetDefaultPerfCounterHW proto WINAPI :PDH_HLOG, :LPCWSTR, :LPCWSTR, :LPWSTR, :LPDWORD
PdhGetDefaultPerfCounterHA proto WINAPI :PDH_HLOG, :LPCSTR, :LPCSTR, :LPSTR, :LPDWORD
PdhBrowseCountersHW proto WINAPI :PPDH_BROWSE_DLG_CONFIG_HW
PdhBrowseCountersHA proto WINAPI :PPDH_BROWSE_DLG_CONFIG_HA
PdhVerifySQLDBW proto WINAPI :LPCWSTR
PdhVerifySQLDBA proto WINAPI :LPCSTR
PdhCreateSQLTablesW proto WINAPI :LPCWSTR
PdhCreateSQLTablesA proto WINAPI :LPCSTR
PdhEnumLogSetNamesW proto WINAPI :LPCWSTR, :PZZWSTR, :LPDWORD
PdhEnumLogSetNamesA proto WINAPI :LPCSTR, :PZZSTR, :LPDWORD
PdhGetLogSetGUID proto WINAPI :PDH_HLOG, :ptr, :ptr
PdhSetLogSetRunID proto WINAPI :PDH_HLOG, :SINT
endif

ifdef UNICODE
ifndef _UNICODE
define _UNICODE 1
endif
endif

ifdef _UNICODE
ifndef UNICODE
define UNICODE 1
endif
endif

ifdef _UNICODE
PdhOpenQuery		equ <PdhOpenQueryW>
PdhAddCounter		equ <PdhAddCounterW>
if (_WIN32_WINDOWS GE 0x0600 OR _WIN32_WINNT GE 0x0600 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_VISTA))
PdhAddEnglishCounter	equ <PdhAddEnglishCounterW>
PdhValidatePathEx	equ <PdhValidatePathExW>
endif
PdhGetCounterInfo	equ <PdhGetCounterInfoW>
PDH_COUNTER_INFO	equ <PDH_COUNTER_INFO_W>
PPDH_COUNTER_INFO	equ <PPDH_COUNTER_INFO_W>
PdhConnectMachine	equ <PdhConnectMachineW>
PdhEnumMachines		equ <PdhEnumMachinesW>
PdhEnumObjects		equ <PdhEnumObjectsW>
PdhEnumObjectItems	equ <PdhEnumObjectItemsW>
PdhMakeCounterPath	equ <PdhMakeCounterPathW>
PDH_COUNTER_PATH_ELEMENTS equ <PDH_COUNTER_PATH_ELEMENTS_W>
PPDH_COUNTER_PATH_ELEMENTS equ <PPDH_COUNTER_PATH_ELEMENTS_W>
PdhParseCounterPath	equ <PdhParseCounterPathW>
PdhParseInstanceName	equ <PdhParseInstanceNameW>
PdhValidatePath		equ <PdhValidatePathW>
PdhGetDefaultPerfObject equ <PdhGetDefaultPerfObjectW>
PdhGetDefaultPerfCounter equ <PdhGetDefaultPerfCounterW>
PdhBrowseCounters	equ <PdhBrowseCountersW>
PDH_BROWSE_DLG_CONFIG	equ <PDH_BROWSE_DLG_CONFIG_W>
PPDH_BROWSE_DLG_CONFIG	equ <PPDH_BROWSE_DLG_CONFIG_W>
PdhExpandCounterPath	equ <PdhExpandCounterPathW>
PDH_FMT_COUNTERVALUE_ITEM equ <PDH_FMT_COUNTERVALUE_ITEM_W>
PPDH_FMT_COUNTERVALUE_ITEM equ <PPDH_FMT_COUNTERVALUE_ITEM_W>
PDH_RAW_COUNTER_ITEM	equ <PDH_RAW_COUNTER_ITEM_W>
PPDH_RAW_COUNTER_ITEM	equ <PPDH_RAW_COUNTER_ITEM_W>
PdhGetFormattedCounterArray equ <PdhGetFormattedCounterArrayW>
PdhGetRawCounterArray	equ <PdhGetRawCounterArrayW>
PdhLookupPerfNameByIndex equ <PdhLookupPerfNameByIndexW>
PdhOpenLog		equ <PdhOpenLogW>
PdhUpdateLog		equ <PdhUpdateLogW>
PdhSelectDataSource	equ <PdhSelectDataSourceW>
PdhGetDataSourceTimeRange equ <PdhGetDataSourceTimeRangeW>
PDH_LOG_SERVICE_QUERY_INFO equ <PDH_LOG_SERVICE_QUERY_INFO_W>
PPDH_LOG_SERVICE_QUERY_INFO equ <PPDH_LOG_SERVICE_QUERY_INFO_W>
PdhLogServiceControl	equ <PdhLogServiceControlW>
PdhLogServiceQuery	equ <PdhLogServiceQueryW>
PdhExpandWildCardPath	equ <PdhExpandWildCardPathW>

if (_WIN32_WINDOWS GE 0x0501 OR _WIN32_WINNT GE 0x0501 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WINXP))
PdhBindInputDataSource	equ <PdhBindInputDataSourceW>
PdhBrowseCountersH	equ <PdhBrowseCountersHW>
PDH_BROWSE_DLG_CONFIG_H equ <PDH_BROWSE_DLG_CONFIG_HW>
PPDH_BROWSE_DLG_CONFIG_H equ <PPDH_BROWSE_DLG_CONFIG_HW>
PdhEnumMachinesH	equ <PdhEnumMachinesHW>
PdhEnumObjectsH		equ <PdhEnumObjectsHW>
PdhEnumObjectItemsH	equ <PdhEnumObjectItemsHW>
PdhExpandWildCardPathH	equ <PdhExpandWildCardPathHW>
PdhGetDefaultPerfObjectH equ <PdhGetDefaultPerfObjectHW>
PdhGetDefaultPerfCounterH equ <PdhGetDefaultPerfCounterHW>
PdhEnumLogSetNames	equ <PdhEnumLogSetNamesW>
PdhCreateSQLTables	equ <PdhCreateSQLTablesW>
PdhVerifySQLDB		equ <PdhVerifySQLDBW>
PdhLookupPerfIndexByName equ <PdhLookupPerfIndexByNameW>
endif

else
PdhOpenQuery		equ <PdhOpenQueryA>
PdhAddCounter		equ <PdhAddCounterA>
if (_WIN32_WINDOWS GE 0x0600 OR _WINNT_WINNT GE 0x0600 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_VISTA))
PdhAddEnglishCounter	equ <PdhAddEnglishCounterA>
PdhValidatePathEx	equ <PdhValidatePathExA>
endif
PdhGetCounterInfo	equ <PdhGetCounterInfoA>
PDH_COUNTER_INFO	equ <PDH_COUNTER_INFO_A>
PPDH_COUNTER_INFO	equ <PPDH_COUNTER_INFO_A>
PdhConnectMachine	equ <PdhConnectMachineA>
PdhEnumMachines		equ <PdhEnumMachinesA>
PdhEnumObjects		equ <PdhEnumObjectsA>
PdhEnumObjectItems	equ <PdhEnumObjectItemsA>
PdhMakeCounterPath	equ <PdhMakeCounterPathA>
PDH_COUNTER_PATH_ELEMENTS equ <PDH_COUNTER_PATH_ELEMENTS_A>
PPDH_COUNTER_PATH_ELEMENTS equ <PPDH_COUNTER_PATH_ELEMENTS_A>
PdhParseCounterPath	equ <PdhParseCounterPathA>
PdhParseInstanceName	equ <PdhParseInstanceNameA>
PdhValidatePath		equ <PdhValidatePathA>
PdhGetDefaultPerfObject equ <PdhGetDefaultPerfObjectA>
PdhGetDefaultPerfCounter equ <PdhGetDefaultPerfCounterA>
PdhBrowseCounters	equ <PdhBrowseCountersA>
PDH_BROWSE_DLG_CONFIG	equ <PDH_BROWSE_DLG_CONFIG_A>
PPDH_BROWSE_DLG_CONFIG	equ <PPDH_BROWSE_DLG_CONFIG_A>
PdhExpandCounterPath	equ <PdhExpandCounterPathA>
PDH_FMT_COUNTERVALUE_ITEM equ <PDH_FMT_COUNTERVALUE_ITEM_A>
PPDH_FMT_COUNTERVALUE_ITEM equ <PPDH_FMT_COUNTERVALUE_ITEM_A>
PDH_RAW_COUNTER_ITEM	equ <PDH_RAW_COUNTER_ITEM_A>
PPDH_RAW_COUNTER_ITEM	equ <PPDH_RAW_COUNTER_ITEM_A>
PdhGetFormattedCounterArray equ <PdhGetFormattedCounterArrayA>
PdhGetRawCounterArray	equ <PdhGetRawCounterArrayA>
PdhLookupPerfNameByIndex equ <PdhLookupPerfNameByIndexA>
PdhOpenLog		equ <PdhOpenLogA>
PdhUpdateLog		equ <PdhUpdateLogA>
PdhSelectDataSource	equ <PdhSelectDataSourceA>
PdhGetDataSourceTimeRange equ <PdhGetDataSourceTimeRangeA>
PDH_LOG_SERVICE_QUERY_INFO equ <PDH_LOG_SERVICE_QUERY_INFO_A>
PPDH_LOG_SERVICE_QUERY_INFO equ <PPDH_LOG_SERVICE_QUERY_INFO_A>
PdhLogServiceControl	equ <PdhLogServiceControlA>
PdhLogServiceQuery	equ <PdhLogServiceQueryA>
PdhExpandWildCardPath	equ <PdhExpandWildCardPathA>

if (_WIN32_WINDOWS GE 0x0501 OR _WIN32_WINNT GE 0x0501 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WINXP))
PdhBindInputDataSource	equ <PdhBindInputDataSourceA>
PDH_BROWSE_DLG_CONFIG_H equ <PDH_BROWSE_DLG_CONFIG_HA>
PPDH_BROWSE_DLG_CONFIG_H equ <PPDH_BROWSE_DLG_CONFIG_HA>
PdhBrowseCountersH	equ <PdhBrowseCountersHA>
PdhEnumMachinesH	equ <PdhEnumMachinesHA>
PdhEnumObjectsH		equ <PdhEnumObjectsHA>
PdhEnumObjectItemsH	equ <PdhEnumObjectItemsHA>
PdhExpandWildCardPathH	equ <PdhExpandWildCardPathHA>
PdhGetDefaultPerfObjectH equ <PdhGetDefaultPerfObjectHA>
PdhGetDefaultPerfCounterH equ <PdhGetDefaultPerfCounterHA>
PdhEnumLogSetNames	equ <PdhEnumLogSetNamesA>
PdhCreateSQLTables	equ <PdhCreateSQLTablesA>
PdhVerifySQLDB		equ <PdhVerifySQLDBA>
PdhLookupPerfIndexByName equ <PdhLookupPerfIndexByNameA>
endif

endif

.pragma pack(pop)
.pragma list(pop)
endif

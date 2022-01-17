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

;PDH_FUNCTION
PdhGetDllVersion proto WINAPI \
	   lpdwVersion: LPDWORD

;PDH_FUNCTION
PdhOpenQueryW proto WINAPI \
	  szDataSource: LPCWSTR,
	    dwUserData: DWORD_PTR,
	       phQuery: ptr PDH_HQUERY

;PDH_FUNCTION
PdhOpenQueryA proto WINAPI \
	  szDataSource: LPCSTR,
	    dwUserData: DWORD_PTR,
	       phQuery: ptr PDH_HQUERY

;PDH_FUNCTION
PdhAddCounterW proto WINAPI \
		hQuery: PDH_HQUERY,
     szFullCounterPath: LPCWSTR,
	    dwUserData: DWORD_PTR,
	     phCounter: ptr PDH_HCOUNTER

;PDH_FUNCTION
PdhAddCounterA proto WINAPI \
		hQuery: PDH_HQUERY,
     szFullCounterPath: LPCSTR,
	    dwUserData: DWORD_PTR,
	     phCounter: ptr PDH_HCOUNTER

if (_WIN32_WINDOWS GE 0x0600 OR _WIN32_WINNT GE 0x0600 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_VISTA))
;PDH_FUNCTION
PdhAddEnglishCounterW proto WINAPI \
		hQuery: PDH_HQUERY,
     szFullCounterPath: LPCWSTR,
	    dwUserData: DWORD_PTR,
	     phCounter: ptr PDH_HCOUNTER

;PDH_FUNCTION
PdhAddEnglishCounterA proto WINAPI \
		hQuery: PDH_HQUERY,
     szFullCounterPath: LPCSTR,
	    dwUserData: DWORD_PTR,
	     phCounter: ptr PDH_HCOUNTER

;PDH_FUNCTION
PdhCollectQueryDataWithTime proto WINAPI \
		hQuery: PDH_HQUERY,
	  pllTimeStamp: ptr LONGLONG

;PDH_FUNCTION
PdhValidatePathExW proto WINAPI \
	   hDataSource: PDH_HLOG,
      szFullPathBuffer: LPCWSTR

;PDH_FUNCTION
PdhValidatePathExA proto WINAPI \
	   hDataSource: PDH_HLOG,
      szFullPathBuffer: LPCSTR
endif

;PDH_FUNCTION
PdhRemoveCounter proto WINAPI \
	      hCounter: PDH_HCOUNTER

;PDH_FUNCTION
PdhCollectQueryData proto WINAPI \
		hQuery: PDH_HQUERY

;PDH_FUNCTION
PdhCloseQuery proto WINAPI \
		hQuery: PDH_HQUERY

;PDH_FUNCTION
PdhGetFormattedCounterValue proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	      dwFormat: DWORD,
	      lpdwType: LPDWORD,
		pValue: PPDH_FMT_COUNTERVALUE

;PDH_FUNCTION
PdhGetFormattedCounterArrayA proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	      dwFormat: DWORD,
	lpdwBufferSize: LPDWORD,
	 lpdwItemCount: LPDWORD,
	    ItemBuffer: PPDH_FMT_COUNTERVALUE_ITEM_A

;PDH_FUNCTION
PdhGetFormattedCounterArrayW proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	      dwFormat: DWORD,
	lpdwBufferSize: LPDWORD,
	 lpdwItemCount: LPDWORD,
	    ItemBuffer: PPDH_FMT_COUNTERVALUE_ITEM_W

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

;PDH_FUNCTION
PdhGetRawCounterValue proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	      lpdwType: LPDWORD,
		pValue: PPDH_RAW_COUNTER


;PDH_FUNCTION
PdhGetRawCounterArrayA proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	lpdwBufferSize: LPDWORD,
	 lpdwItemCount: LPDWORD,
	    ItemBuffer: PPDH_RAW_COUNTER_ITEM_A

;PDH_FUNCTION
PdhGetRawCounterArrayW proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	lpdwBufferSize: LPDWORD,
	 lpdwItemCount: LPDWORD,
	    ItemBuffer: PPDH_RAW_COUNTER_ITEM_W

;PDH_FUNCTION
PdhCalculateCounterFromRawValue proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	      dwFormat: DWORD,
	     rawValue1: PPDH_RAW_COUNTER,
	     rawValue2: PPDH_RAW_COUNTER,
	      fmtValue: PPDH_FMT_COUNTERVALUE

;PDH_FUNCTION
PdhComputeCounterStatistics proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	      dwFormat: DWORD,
	  dwFirstEntry: DWORD,
	  dwNumEntries: DWORD,
       lpRawValueArray: PPDH_RAW_COUNTER,
		 _data: PPDH_STATISTICS


;PDH_FUNCTION
PdhGetCounterInfoW proto WINAPI \
	      hCounter: PDH_HCOUNTER,
  bRetrieveExplainText: BOOLEAN,
	 pdwBufferSize: LPDWORD,
	      lpBuffer: PPDH_COUNTER_INFO_W

;PDH_FUNCTION
PdhGetCounterInfoA proto WINAPI \
	      hCounter: PDH_HCOUNTER,
  bRetrieveExplainText: BOOLEAN,
	 pdwBufferSize: LPDWORD,
	      lpBuffer: PPDH_COUNTER_INFO_A

PDH_MAX_SCALE		equ (7)
PDH_MIN_SCALE		equ (-7)

;PDH_FUNCTION
PdhSetCounterScaleFactor proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	       lFactor: LONG

;PDH_FUNCTION
PdhConnectMachineW proto WINAPI \
	 szMachineName: LPCWSTR


;PDH_FUNCTION
PdhConnectMachineA proto WINAPI \
	 szMachineName: LPCSTR


;PDH_FUNCTION
PdhEnumMachinesW proto WINAPI \
	  szDataSource: LPCWSTR,
	mszMachineList: PZZWSTR,
	pcchBufferSize: LPDWORD

;PDH_FUNCTION
PdhEnumMachinesA proto WINAPI \
	  szDataSource: LPCSTR,
	mszMachineList: PZZSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhEnumObjectsW proto WINAPI \
	  szDataSource: LPCWSTR,
	 szMachineName: LPCWSTR,
	 mszObjectList: PZZWSTR,
	pcchBufferSize: LPDWORD,
	 dwDetailLevel: DWORD,
	      bRefresh: BOOL

;PDH_FUNCTION
PdhEnumObjectsA proto WINAPI \
	  szDataSource: LPCSTR,
	 szMachineName: LPCSTR,
	 mszObjectList: PZZSTR,
	pcchBufferSize: LPDWORD,
	 dwDetailLevel: DWORD,
	      bRefresh: BOOL

;PDH_FUNCTION
PdhEnumObjectItemsW proto WINAPI \
	  szDataSource: LPCWSTR,
	 szMachineName: LPCWSTR,
	  szObjectName: LPCWSTR,
	mszCounterList: PZZWSTR,
 pcchCounterListLength: LPDWORD,
       mszInstanceList: PZZWSTR,
pcchInstanceListLength: LPDWORD,
	 dwDetailLevel: DWORD,
	       dwFlags: DWORD


;PDH_FUNCTION
PdhEnumObjectItemsA proto WINAPI \
	  szDataSource: LPCSTR,
	 szMachineName: LPCSTR,
	  szObjectName: LPCSTR,
	mszCounterList: PZZSTR,
 pcchCounterListLength: LPDWORD,
       mszInstanceList: PZZSTR,
pcchInstanceListLength: LPDWORD,
	 dwDetailLevel: DWORD,
	       dwFlags: DWORD

;PDH_FUNCTION
PdhMakeCounterPathW proto WINAPI \
  pCounterPathElements: PPDH_COUNTER_PATH_ELEMENTS_W,
      szFullPathBuffer: LPWSTR,
	pcchBufferSize: LPDWORD,
	       dwFlags: DWORD

;PDH_FUNCTION
PdhMakeCounterPathA proto WINAPI \
  pCounterPathElements: PPDH_COUNTER_PATH_ELEMENTS_A,
      szFullPathBuffer: LPSTR,
	pcchBufferSize: LPDWORD,
	       dwFlags: DWORD

;PDH_FUNCTION
PdhParseCounterPathW proto WINAPI \
      szFullPathBuffer: LPCWSTR,
  pCounterPathElements: PPDH_COUNTER_PATH_ELEMENTS_W,
	 pdwBufferSize: LPDWORD,
	       dwFlags: DWORD

;PDH_FUNCTION
PdhParseCounterPathA proto WINAPI \
      szFullPathBuffer: LPCSTR,
  pCounterPathElements: PPDH_COUNTER_PATH_ELEMENTS_A,
	 pdwBufferSize: LPDWORD,
	       dwFlags: DWORD

PDH_PATH_WBEM_RESULT	equ 0x00000001
PDH_PATH_WBEM_INPUT	equ 0x00000002

PDH_PATH_LANG_FLAGS macro LangId, Flags
	exitm<((((LangId AND 0x0000FFFF) SHL 16) OR (Flags AND 0x0000FFFF)))>
	endm

;PDH_FUNCTION
PdhParseInstanceNameW proto WINAPI \
      szInstanceString: LPCWSTR,
	szInstanceName: LPWSTR,
pcchInstanceNameLength: LPDWORD,
	  szParentName: LPWSTR,
  pcchParentNameLength: LPDWORD,
	       lpIndex: LPDWORD


;PDH_FUNCTION
PdhParseInstanceNameA proto WINAPI \
      szInstanceString: LPCSTR,
	szInstanceName: LPSTR,
pcchInstanceNameLength: LPDWORD,
	  szParentName: LPSTR,
  pcchParentNameLength: LPDWORD,
	       lpIndex: LPDWORD


;PDH_FUNCTION
PdhValidatePathW proto WINAPI \
      szFullPathBuffer: LPCWSTR


;PDH_FUNCTION
PdhValidatePathA proto WINAPI \
      szFullPathBuffer: LPCSTR


;PDH_FUNCTION
PdhGetDefaultPerfObjectW proto WINAPI \
	  szDataSource: LPCWSTR,
	 szMachineName: LPCWSTR,
	szDefaultObjectName: LPWSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhGetDefaultPerfObjectA proto WINAPI \
	  szDataSource: LPCSTR,
	 szMachineName: LPCSTR,
	szDefaultObjectName: LPSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhGetDefaultPerfCounterW proto WINAPI \
	  szDataSource: LPCWSTR,
	 szMachineName: LPCWSTR,
	  szObjectName: LPCWSTR,
	szDefaultCounterName: LPWSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhGetDefaultPerfCounterA proto WINAPI \
	  szDataSource: LPCSTR,
	 szMachineName: LPCSTR,
	  szObjectName: LPCSTR,
	szDefaultCounterName: LPSTR,
	pcchBufferSize: LPDWORD


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

;PDH_FUNCTION
PdhBrowseCountersW proto WINAPI \
	pBrowseDlgData: PPDH_BROWSE_DLG_CONFIG_W


;PDH_FUNCTION
PdhBrowseCountersA proto WINAPI \
	pBrowseDlgData: PPDH_BROWSE_DLG_CONFIG_A


;PDH_FUNCTION
PdhExpandCounterPathW proto WINAPI \
	szWildCardPath: LPCWSTR,
	 mszExpandedPathList: PZZWSTR,
    pcchPathListLength: LPDWORD


;PDH_FUNCTION
PdhExpandCounterPathA proto WINAPI \
	szWildCardPath: LPCSTR,
	 mszExpandedPathList: PZZSTR,
    pcchPathListLength: LPDWORD


;PDH_FUNCTION
PdhLookupPerfNameByIndexW proto WINAPI \
	 szMachineName: LPCWSTR,
	   dwNameIndex: DWORD,
	  szNameBuffer: LPWSTR,
    pcchNameBufferSize: LPDWORD

;PDH_FUNCTION
PdhLookupPerfNameByIndexA proto WINAPI \
	 szMachineName: LPCSTR,
	   dwNameIndex: DWORD,
	  szNameBuffer: LPSTR,
    pcchNameBufferSize: LPDWORD

;PDH_FUNCTION
PdhLookupPerfIndexByNameW proto WINAPI \
	 szMachineName: LPCWSTR,
	  szNameBuffer: LPCWSTR,
	      pdwIndex: LPDWORD

;PDH_FUNCTION
PdhLookupPerfIndexByNameA proto WINAPI \
	 szMachineName: LPCSTR,
	  szNameBuffer: LPCSTR,
	      pdwIndex: LPDWORD


PDH_NOEXPANDCOUNTERS	equ 1
PDH_NOEXPANDINSTANCES	equ 2
if (_WIN32_WINDOWS GE 0x0502 OR _WIN32_WINNT GE 0x0502 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WIN2003))
PDH_REFRESHCOUNTERS	equ 4
endif

;PDH_FUNCTION
PdhExpandWildCardPathA proto WINAPI \
	  szDataSource: LPCSTR,
	szWildCardPath: LPCSTR,
   mszExpandedPathList: PZZSTR,
    pcchPathListLength: LPDWORD,
	       dwFlags: DWORD


;PDH_FUNCTION
PdhExpandWildCardPathW proto WINAPI \
	  szDataSource: LPCWSTR,
	szWildCardPath: LPCWSTR,
   mszExpandedPathList: PZZWSTR,
    pcchPathListLength: LPDWORD,
	       dwFlags: DWORD

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

;PDH_FUNCTION
PdhOpenLogW proto WINAPI \
	 szLogFileName: LPCWSTR,
	 dwAccessFlags: DWORD,
	   lpdwLogType: LPDWORD,
		hQuery: PDH_HQUERY,
	     dwMaxSize: DWORD,
	 szUserCaption: LPCWSTR,
		 phLog: ptr PDH_HLOG

;PDH_FUNCTION
PdhOpenLogA proto WINAPI \
	 szLogFileName: LPCSTR,
	 dwAccessFlags: DWORD,
	   lpdwLogType: LPDWORD,
		hQuery: PDH_HQUERY,
	     dwMaxSize: DWORD,
	 szUserCaption: LPCSTR,
		 phLog: ptr PDH_HLOG

;PDH_FUNCTION
PdhUpdateLogW proto WINAPI \
		  hLog: PDH_HLOG,
	  szUserString: LPCWSTR


;PDH_FUNCTION
PdhUpdateLogA proto WINAPI \
		  hLog: PDH_HLOG,
	  szUserString: LPCSTR

;PDH_FUNCTION
PdhUpdateLogFileCatalog proto WINAPI \
		  hLog: PDH_HLOG

;PDH_FUNCTION
PdhGetLogFileSize proto WINAPI \
		  hLog: PDH_HLOG,
		llSize: ptr LONGLONG

;PDH_FUNCTION
PdhCloseLog proto WINAPI \
		  hLog: PDH_HLOG,
	       dwFlags: DWORD

PDH_FLAGS_CLOSE_QUERY	equ 0x00000001
PDH_FLAGS_FILE_BROWSER_ONLY equ 0x00000001

;PDH_FUNCTION
PdhSelectDataSourceW proto WINAPI \
	     hWndOwner: HWND,
	       dwFlags: DWORD,
	  szDataSource: LPWSTR,
      pcchBufferLength: LPDWORD

;PDH_FUNCTION
PdhSelectDataSourceA proto WINAPI \
	     hWndOwner: HWND,
	       dwFlags: DWORD,
	  szDataSource: LPSTR,
      pcchBufferLength: LPDWORD

;BOOL
PdhIsRealTimeQuery proto WINAPI \
		hQuery: PDH_HQUERY

;PDH_FUNCTION
PdhSetQueryTimeRange proto WINAPI \
		hQuery: PDH_HQUERY,
		 pInfo: PPDH_TIME_INFO

;PDH_FUNCTION
PdhGetDataSourceTimeRangeW proto WINAPI \
	  szDataSource: LPCWSTR,
	 pdwNumEntries: LPDWORD,
		 pInfo: PPDH_TIME_INFO,
	 pdwBufferSize: LPDWORD

;PDH_FUNCTION
PdhGetDataSourceTimeRangeA proto WINAPI \
	  szDataSource: LPCSTR,
	 pdwNumEntries: LPDWORD,
		 pInfo: PPDH_TIME_INFO,
	 pdwBufferSize: LPDWORD

;PDH_FUNCTION
PdhCollectQueryDataEx proto WINAPI \
		hQuery: PDH_HQUERY,
	dwIntervalTime: DWORD,
	 hNewDataEvent: HANDLE

;PDH_FUNCTION
PdhFormatFromRawValue proto WINAPI \
	 dwCounterType: DWORD,
	      dwFormat: DWORD,
	     pTimeBase: ptr LONGLONG,
	    pRawValue1: PPDH_RAW_COUNTER,
	    pRawValue2: PPDH_RAW_COUNTER,
	     pFmtValue: PPDH_FMT_COUNTERVALUE

;PDH_FUNCTION
PdhGetCounterTimeBase proto WINAPI \
	      hCounter: PDH_HCOUNTER,
	     pTimeBase: ptr LONGLONG

;PDH_FUNCTION
PdhReadRawLogRecord proto WINAPI \
		  hLog: PDH_HLOG,
	      ftRecord: FILETIME,
	 pRawLogRecord: PPDH_RAW_LOG_RECORD,
       pdwBufferLength: LPDWORD


DATA_SOURCE_REGISTRY	equ 0x00000001
DATA_SOURCE_LOGFILE	equ 0x00000002
DATA_SOURCE_WBEM	equ 0x00000004

;PDH_FUNCTION
PdhSetDefaultRealTimeDataSource proto WINAPI \
	dwDataSourceId: DWORD


if (_WIN32_WINDOWS GE 0x0501 OR _WIN32_WINNT GE 0x0501 OR (defined(NTDDI_VERSION) AND NTDDI_VERSION GE NTDDI_WINXP))
;PDH_FUNCTION
PdhBindInputDataSourceW proto WINAPI \
	  phDataSource: ptr PDH_HLOG,
       LogFileNameList: LPCWSTR


;PDH_FUNCTION
PdhBindInputDataSourceA proto WINAPI \
	  phDataSource: ptr PDH_HLOG,
       LogFileNameList: LPCSTR


;PDH_FUNCTION
PdhOpenQueryH proto WINAPI \
	   hDataSource: PDH_HLOG,
	    dwUserData: DWORD_PTR,
	       phQuery: ptr PDH_HQUERY


;PDH_FUNCTION
PdhEnumMachinesHW proto WINAPI \
	   hDataSource: PDH_HLOG,
	  mszMachineList: PZZWSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhEnumMachinesHA proto WINAPI \
	   hDataSource: PDH_HLOG,
	  mszMachineList: PZZSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhEnumObjectsHW proto WINAPI \
	   hDataSource: PDH_HLOG,
	 szMachineName: LPCWSTR,
	  mszObjectList: PZZWSTR,
	pcchBufferSize: LPDWORD,
	 dwDetailLevel: DWORD,
	      bRefresh: BOOL

;PDH_FUNCTION
PdhEnumObjectsHA proto WINAPI \
	   hDataSource: PDH_HLOG,
	 szMachineName: LPCSTR,
	  mszObjectList: PZZSTR,
	pcchBufferSize: LPDWORD,
	 dwDetailLevel: DWORD,
	      bRefresh: BOOL


;PDH_FUNCTION
PdhEnumObjectItemsHW proto WINAPI \
	   hDataSource: PDH_HLOG,
	 szMachineName: LPCWSTR,
	  szObjectName: LPCWSTR,
	mszCounterList: PZZWSTR,
 pcchCounterListLength: LPDWORD,
       mszInstanceList: PZZWSTR,
pcchInstanceListLength: LPDWORD,
	 dwDetailLevel: DWORD,
	       dwFlags: DWORD


;PDH_FUNCTION
PdhEnumObjectItemsHA proto WINAPI \
	   hDataSource: PDH_HLOG,
	 szMachineName: LPCSTR,
	  szObjectName: LPCSTR,
	mszCounterList: PZZSTR,
 pcchCounterListLength: LPDWORD,
       mszInstanceList: PZZSTR,
pcchInstanceListLength: LPDWORD,
	 dwDetailLevel: DWORD,
	       dwFlags: DWORD


;PDH_FUNCTION
PdhExpandWildCardPathHW proto WINAPI \
	   hDataSource: PDH_HLOG,
	szWildCardPath: LPCWSTR,
   mszExpandedPathList: PZZWSTR,
    pcchPathListLength: LPDWORD,
	       dwFlags: DWORD


;PDH_FUNCTION
PdhExpandWildCardPathHA proto WINAPI \
	   hDataSource: PDH_HLOG,
	szWildCardPath: LPCSTR,
   mszExpandedPathList: PZZSTR,
    pcchPathListLength: LPDWORD,
	       dwFlags: DWORD

;PDH_FUNCTION
PdhGetDataSourceTimeRangeH proto WINAPI \
	   hDataSource: PDH_HLOG,
	 pdwNumEntries: LPDWORD,
		 pInfo: PPDH_TIME_INFO,
	 pdwBufferSize: LPDWORD

;PDH_FUNCTION
PdhGetDefaultPerfObjectHW proto WINAPI \
	   hDataSource: PDH_HLOG,
	 szMachineName: LPCWSTR,
   szDefaultObjectName: LPWSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhGetDefaultPerfObjectHA proto WINAPI \
	   hDataSource: PDH_HLOG,
	 szMachineName: LPCSTR,
   szDefaultObjectName: LPSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhGetDefaultPerfCounterHW proto WINAPI \
	   hDataSource: PDH_HLOG,
	 szMachineName: LPCWSTR,
	  szObjectName: LPCWSTR,
  szDefaultCounterName: LPWSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhGetDefaultPerfCounterHA proto WINAPI \
	   hDataSource: PDH_HLOG,
	 szMachineName: LPCSTR,
	  szObjectName: LPCSTR,
  szDefaultCounterName: LPSTR,
	pcchBufferSize: LPDWORD


;PDH_FUNCTION
PdhBrowseCountersHW proto WINAPI \
	pBrowseDlgData: PPDH_BROWSE_DLG_CONFIG_HW

;PDH_FUNCTION
PdhBrowseCountersHA proto WINAPI \
	pBrowseDlgData: PPDH_BROWSE_DLG_CONFIG_HA

;PDH_FUNCTION
PdhVerifySQLDBW proto WINAPI \
	  szDataSource: LPCWSTR

;PDH_FUNCTION
PdhVerifySQLDBA proto WINAPI \
	  szDataSource: LPCSTR

;PDH_FUNCTION
PdhCreateSQLTablesW proto WINAPI \
	  szDataSource: LPCWSTR

;PDH_FUNCTION
PdhCreateSQLTablesA proto WINAPI \
	  szDataSource: LPCSTR

;PDH_FUNCTION
PdhEnumLogSetNamesW proto WINAPI \
	  szDataSource: LPCWSTR,
    mszDataSetNameList: PZZWSTR,
      pcchBufferLength: LPDWORD


;PDH_FUNCTION
PdhEnumLogSetNamesA proto WINAPI \
	  szDataSource: LPCSTR,
    mszDataSetNameList: PZZSTR,
      pcchBufferLength: LPDWORD


;PDH_FUNCTION
PdhGetLogSetGUID proto WINAPI \
		  hLog: PDH_HLOG,
		 pGuid: ptr GUID,
		pRunId: ptr SINT

;PDH_FUNCTION
PdhSetLogSetRunID proto WINAPI \
		  hLog: PDH_HLOG,
		 RunId: SINT
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

ifdef UNICODE
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

.pragma list(pop)
endif

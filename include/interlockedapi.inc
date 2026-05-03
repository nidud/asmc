ifndef _INTERLOCKAPI_H_
define _INTERLOCKAPI_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif

ifndef NOWINBASEINTERLOCK
ifndef _NTOS_
if defined(_SLIST_HEADER_) and not defined(_NTOSP_)
InitializeSListHead proto WINAPI :PSLIST_HEADER
InterlockedPopEntrySList proto WINAPI :PSLIST_HEADER
InterlockedPushEntrySList proto WINAPI :PSLIST_HEADER, :PSLIST_ENTRY
if (NTDDI_VERSION ge NTDDI_WIN8)
define InterlockedPushListSList <InterlockedPushListSListEx>
InterlockedPushListSListEx proto WINAPI :PSLIST_HEADER, :PSLIST_ENTRY, :PSLIST_ENTRY, :ULONG
endif
InterlockedFlushSList proto WINAPI :PSLIST_HEADER
QueryDepthSList proto WINAPI :PSLIST_HEADER
endif
endif
endif

endif

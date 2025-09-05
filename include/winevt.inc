ifndef __WINEVT_H__
define __WINEVT_H__
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_PKG_EVENTLOGSERVICE)

if (WINVER ge _WIN32_WINNT_LONGHORN)

EVT_HANDLE		typedef HANDLE
PEVT_HANDLE		typedef ptr HANDLE

.enum EVT_VARIANT_TYPE {
    EvtVarTypeNull	  = 0,
    EvtVarTypeString	  = 1,
    EvtVarTypeAnsiString  = 2,
    EvtVarTypeSByte	  = 3,
    EvtVarTypeByte	  = 4,
    EvtVarTypeInt16	  = 5,
    EvtVarTypeUInt16	  = 6,
    EvtVarTypeInt32	  = 7,
    EvtVarTypeUInt32	  = 8,
    EvtVarTypeInt64	  = 9,
    EvtVarTypeUInt64	  = 10,
    EvtVarTypeSingle	  = 11,
    EvtVarTypeDouble	  = 12,
    EvtVarTypeBoolean	  = 13,
    EvtVarTypeBinary	  = 14,
    EvtVarTypeGuid	  = 15,
    EvtVarTypeSizeT	  = 16,
    EvtVarTypeFileTime	  = 17,
    EvtVarTypeSysTime	  = 18,
    EvtVarTypeSid	  = 19,
    EvtVarTypeHexInt32	  = 20,
    EvtVarTypeHexInt64	  = 21,
    EvtVarTypeEvtHandle	  = 32,
    EvtVarTypeEvtXml	  = 35
    }

define EVT_VARIANT_TYPE_MASK 0x7f
define EVT_VARIANT_TYPE_ARRAY 128

EVT_VARIANT		struct
union
 BooleanVal		BOOL ?
 SByteVal		INT8 ?
 Int16Val		INT16 ?
 Int32Val		INT32 ?
 Int64Val		INT64 ?
 ByteVal		UINT8 ?
 UInt16Val		UINT16 ?
 UInt32Val		UINT32 ?
 UInt64Val		UINT64 ?
 SingleVal		real4 ?
 DoubleVal		real8 ?
 FileTimeVal		ULONGLONG ?
 SysTimeVal		ptr SYSTEMTIME ?
 GuidVal		ptr GUID ?
 StringVal		LPCWSTR ?
 AnsiStringVal		LPCSTR ?
 BinaryVal		PBYTE ?
 SidVal			PSID ?
 SizeTVal		size_t ?
 BooleanArr		ptr BOOL ?
 SByteArr		ptr INT8 ?
 Int16Arr		ptr INT16 ?
 Int32Arr		ptr INT32 ?
 Int64Arr		ptr INT64 ?
 ByteArr		ptr UINT8 ?
 UInt16Arr		ptr UINT16 ?
 UInt32Arr		ptr UINT32 ?
 UInt64Arr		ptr UINT64 ?
 SingleArr		ptr real4 ?
 DoubleArr		ptr real8 ?
 FileTimeArr		ptr FILETIME ?
 SysTimeArr		ptr SYSTEMTIME ?
 GuidArr		ptr GUID ?
 StringArr		ptr LPWSTR ?
 AnsiStringArr		ptr LPSTR ?
 SidArr			ptr PSID ?
 SizeTArr		ptr size_t ?
 EvtHandleVal		EVT_HANDLE ?
 XmlVal			LPCWSTR ?
 XmlValArr		ptr LPCWSTR ?
ends
Count			DWORD ?
Type			DWORD ?
EVT_VARIANT		ends
PEVT_VARIANT		typedef ptr EVT_VARIANT

.enum EVT_LOGIN_CLASS {
    EvtRpcLogin = 1
    }

.enum EVT_RPC_LOGIN_FLAGS {
    EvtRpcLoginAuthDefault = 0,
    EvtRpcLoginAuthNegotiate,
    EvtRpcLoginAuthKerberos,
    EvtRpcLoginAuthNTLM
    }

EVT_RPC_LOGIN		struct
Server			LPWSTR ?
User			LPWSTR ?
Domain			LPWSTR ?
Password		LPWSTR ?
Flags			DWORD ?
EVT_RPC_LOGIN		ends

EvtOpenSession proto WINAPI :EVT_LOGIN_CLASS, :PVOID, :DWORD, :DWORD
EvtClose proto WINAPI :EVT_HANDLE
EvtCancel proto WINAPI :EVT_HANDLE
EvtGetExtendedStatus proto WINAPI :DWORD, :LPWSTR, :PDWORD

.enum EVT_QUERY_FLAGS {
    EvtQueryChannelPath			= 0x1,
    EvtQueryFilePath			= 0x2,
    EvtQueryForwardDirection		= 0x100,
    EvtQueryReverseDirection		= 0x200,
    EvtQueryTolerateQueryErrors		= 0x1000
    }

.enum EVT_SEEK_FLAGS {
    EvtSeekRelativeToFirst    = 1,
    EvtSeekRelativeToLast     = 2,
    EvtSeekRelativeToCurrent  = 3,
    EvtSeekRelativeToBookmark = 4,
    EvtSeekOriginMask	      = 7,
    EvtSeekStrict	      = 0x10000,
    }

EvtQuery proto WINAPI :EVT_HANDLE, :LPCWSTR, :LPCWSTR, :DWORD
EvtNext proto WINAPI :EVT_HANDLE, :DWORD, :PEVT_HANDLE, :DWORD, :DWORD, :PDWORD
EvtSeek proto WINAPI :EVT_HANDLE, :LONGLONG, :EVT_HANDLE, :DWORD, :DWORD

.enum EVT_SUBSCRIBE_FLAGS {
    EvtSubscribeToFutureEvents	    = 1,
    EvtSubscribeStartAtOldestRecord = 2,
    EvtSubscribeStartAfterBookmark  = 3,
    EvtSubscribeOriginMask	    = 3,
    EvtSubscribeTolerateQueryErrors = 0x1000,
    EvtSubscribeStrict		    = 0x10000,
    }

.enum EVT_SUBSCRIBE_NOTIFY_ACTION {
    EvtSubscribeActionError = 0,
    EvtSubscribeActionDeliver
    }

CALLBACK(EVT_SUBSCRIBE_CALLBACK, :EVT_SUBSCRIBE_NOTIFY_ACTION, :PVOID, :EVT_HANDLE)

EvtSubscribe proto WINAPI :EVT_HANDLE, :HANDLE, :LPCWSTR, :LPCWSTR, :EVT_HANDLE, :PVOID, :EVT_SUBSCRIBE_CALLBACK, :DWORD

.enum EVT_SYSTEM_PROPERTY_ID {
    EvtSystemProviderName = 0,
    EvtSystemProviderGuid,
    EvtSystemEventID,
    EvtSystemQualifiers,
    EvtSystemLevel,
    EvtSystemTask,
    EvtSystemOpcode,
    EvtSystemKeywords,
    EvtSystemTimeCreated,
    EvtSystemEventRecordId,
    EvtSystemActivityID,
    EvtSystemRelatedActivityID,
    EvtSystemProcessID,
    EvtSystemThreadID,
    EvtSystemChannel,
    EvtSystemComputer,
    EvtSystemUserID,
    EvtSystemVersion,
    EvtSystemPropertyIdEND
    }

.enum EVT_RENDER_CONTEXT_FLAGS {
    EvtRenderContextValues = 0,
    EvtRenderContextSystem,
    EvtRenderContextUser
    }

.enum EVT_RENDER_FLAGS {
    EvtRenderEventValues = 0,
    EvtRenderEventXml,
    EvtRenderBookmark
    }

EvtCreateRenderContext proto WINAPI :DWORD, :ptr, :DWORD
EvtRender proto WINAPI :EVT_HANDLE, :EVT_HANDLE, :DWORD, :DWORD, :PVOID, :PDWORD, :PDWORD

.enum EVT_FORMAT_MESSAGE_FLAGS {
    EvtFormatMessageEvent = 1,
    EvtFormatMessageLevel,
    EvtFormatMessageTask,
    EvtFormatMessageOpcode,
    EvtFormatMessageKeyword,
    EvtFormatMessageChannel,
    EvtFormatMessageProvider,
    EvtFormatMessageId,
    EvtFormatMessageXml,
    }

EvtFormatMessage proto WINAPI :EVT_HANDLE, :EVT_HANDLE, :DWORD, :DWORD, :PEVT_VARIANT, :DWORD, :DWORD, :LPWSTR, :PDWORD

.enum EVT_OPEN_LOG_FLAGS {
    EvtOpenChannelPath		= 0x1,
    EvtOpenFilePath		= 0x2
    }

.enum EVT_LOG_PROPERTY_ID {
    EvtLogCreationTime = 0,
    EvtLogLastAccessTime,
    EvtLogLastWriteTime,
    EvtLogFileSize,
    EvtLogAttributes,
    EvtLogNumberOfLogRecords,
    EvtLogOldestRecordNumber,
    EvtLogFull,
    }

EvtOpenLog proto WINAPI :EVT_HANDLE, :LPCWSTR, :DWORD
EvtGetLogInfo proto WINAPI :EVT_HANDLE, :EVT_LOG_PROPERTY_ID, :DWORD, :PEVT_VARIANT, :PDWORD
EvtClearLog proto WINAPI :EVT_HANDLE, :LPCWSTR, :LPCWSTR, :DWORD

.enum EVT_EXPORTLOG_FLAGS {
    EvtExportLogChannelPath	= 0x1,
    EvtExportLogFilePath	= 0x2,
    EvtExportLogTolerateQueryErrors = 0x1000,
    EvtExportLogOverwrite = 0x2000
    }

EvtExportLog proto WINAPI :EVT_HANDLE, :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD
EvtArchiveExportedLog proto WINAPI :EVT_HANDLE, :LPCWSTR, :LCID, :DWORD

.enum EVT_CHANNEL_CONFIG_PROPERTY_ID {
    EvtChannelConfigEnabled = 0,
    EvtChannelConfigIsolation,
    EvtChannelConfigType,
    EvtChannelConfigOwningPublisher,
    EvtChannelConfigClassicEventlog,
    EvtChannelConfigAccess,
    EvtChannelLoggingConfigRetention,
    EvtChannelLoggingConfigAutoBackup,
    EvtChannelLoggingConfigMaxSize,
    EvtChannelLoggingConfigLogFilePath,
    EvtChannelPublishingConfigLevel,
    EvtChannelPublishingConfigKeywords,
    EvtChannelPublishingConfigControlGuid,
    EvtChannelPublishingConfigBufferSize,
    EvtChannelPublishingConfigMinBuffers,
    EvtChannelPublishingConfigMaxBuffers,
    EvtChannelPublishingConfigLatency,
    EvtChannelPublishingConfigClockType,
    EvtChannelPublishingConfigSidType,
    EvtChannelPublisherList,
    EvtChannelPublishingConfigFileMax,
    EvtChannelConfigPropertyIdEND
    }

.enum EVT_CHANNEL_TYPE {
    EvtChannelTypeAdmin = 0,
    EvtChannelTypeOperational,
    EvtChannelTypeAnalytic,
    EvtChannelTypeDebug
    }

.enum EVT_CHANNEL_ISOLATION_TYPE {
    EvtChannelIsolationTypeApplication = 0,
    EvtChannelIsolationTypeSystem,
    EvtChannelIsolationTypeCustom
    }

.enum EVT_CHANNEL_CLOCK_TYPE {
    EvtChannelClockTypeSystemTime = 0,
    EvtChannelClockTypeQPC
    }

.enum EVT_CHANNEL_SID_TYPE {
    EvtChannelSidTypeNone = 0,
    EvtChannelSidTypePublishing
    }

EvtOpenChannelEnum proto WINAPI :EVT_HANDLE, :DWORD
EvtNextChannelPath proto WINAPI :EVT_HANDLE, :DWORD, :LPWSTR, :PDWORD
EvtOpenChannelConfig proto WINAPI :EVT_HANDLE, :LPCWSTR, :DWORD
EvtSaveChannelConfig proto WINAPI :EVT_HANDLE, :DWORD
EvtSetChannelConfigProperty proto WINAPI :EVT_HANDLE, :EVT_CHANNEL_CONFIG_PROPERTY_ID, :DWORD, :PEVT_VARIANT
EvtGetChannelConfigProperty proto WINAPI :EVT_HANDLE, :EVT_CHANNEL_CONFIG_PROPERTY_ID, :DWORD, :DWORD, :PEVT_VARIANT, :PDWORD

.enum EVT_CHANNEL_REFERENCE_FLAGS {
    EvtChannelReferenceImported = 0x1,
    }

.enum EVT_PUBLISHER_METADATA_PROPERTY_ID {
    EvtPublisherMetadataPublisherGuid = 0,
    EvtPublisherMetadataResourceFilePath,
    EvtPublisherMetadataParameterFilePath,
    EvtPublisherMetadataMessageFilePath,
    EvtPublisherMetadataHelpLink,
    EvtPublisherMetadataPublisherMessageID,
    EvtPublisherMetadataChannelReferences,
    EvtPublisherMetadataChannelReferencePath,
    EvtPublisherMetadataChannelReferenceIndex,
    EvtPublisherMetadataChannelReferenceID,
    EvtPublisherMetadataChannelReferenceFlags,
    EvtPublisherMetadataChannelReferenceMessageID,
    EvtPublisherMetadataLevels,
    EvtPublisherMetadataLevelName,
    EvtPublisherMetadataLevelValue,
    EvtPublisherMetadataLevelMessageID,
    EvtPublisherMetadataTasks,
    EvtPublisherMetadataTaskName,
    EvtPublisherMetadataTaskEventGuid,
    EvtPublisherMetadataTaskValue,
    EvtPublisherMetadataTaskMessageID,
    EvtPublisherMetadataOpcodes,
    EvtPublisherMetadataOpcodeName,
    EvtPublisherMetadataOpcodeValue,
    EvtPublisherMetadataOpcodeMessageID,
    EvtPublisherMetadataKeywords,
    EvtPublisherMetadataKeywordName,
    EvtPublisherMetadataKeywordValue,
    EvtPublisherMetadataKeywordMessageID,
    EvtPublisherMetadataPropertyIdEND
    }

EvtOpenPublisherEnum proto WINAPI :EVT_HANDLE, :DWORD
EvtNextPublisherId proto WINAPI :EVT_HANDLE, :DWORD, :LPWSTR, :PDWORD
EvtOpenPublisherMetadata proto WINAPI :EVT_HANDLE, :LPCWSTR, :LPCWSTR, :LCID, :DWORD
EvtGetPublisherMetadataProperty proto WINAPI :EVT_HANDLE, :EVT_PUBLISHER_METADATA_PROPERTY_ID, :DWORD, :DWORD, :PEVT_VARIANT, :PDWORD

.enum EVT_EVENT_METADATA_PROPERTY_ID {
    EventMetadataEventID,
    EventMetadataEventVersion,
    EventMetadataEventChannel,
    EventMetadataEventLevel,
    EventMetadataEventOpcode,
    EventMetadataEventTask,
    EventMetadataEventKeyword,
    EventMetadataEventMessageID,
    EventMetadataEventTemplate,
    EvtEventMetadataPropertyIdEND
    }

EvtOpenEventMetadataEnum proto WINAPI :EVT_HANDLE, :DWORD
EvtNextEventMetadata proto WINAPI :EVT_HANDLE, :DWORD
EvtGetEventMetadataProperty proto WINAPI :EVT_HANDLE, :EVT_EVENT_METADATA_PROPERTY_ID, :DWORD, :DWORD, :PEVT_VARIANT, :PDWORD

EVT_OBJECT_ARRAY_PROPERTY_HANDLE typedef HANDLE

EvtGetObjectArraySize proto WINAPI :EVT_OBJECT_ARRAY_PROPERTY_HANDLE, :PDWORD
EvtGetObjectArrayProperty proto WINAPI :EVT_OBJECT_ARRAY_PROPERTY_HANDLE, :DWORD, :DWORD, :DWORD, :DWORD, :PEVT_VARIANT, :PDWORD

.enum EVT_QUERY_PROPERTY_ID {
    EvtQueryNames,
    EvtQueryStatuses,
    EvtQueryPropertyIdEND
    }

.enum EVT_EVENT_PROPERTY_ID {
    EvtEventQueryIDs = 0,
    EvtEventPath,
    EvtEventPropertyIdEND
    }

EvtGetQueryInfo proto WINAPI :EVT_HANDLE, :EVT_QUERY_PROPERTY_ID, :DWORD, :PEVT_VARIANT, :PDWORD
EvtCreateBookmark proto WINAPI :LPCWSTR
EvtUpdateBookmark proto WINAPI :EVT_HANDLE, :EVT_HANDLE
EvtGetEventInfo proto WINAPI :EVT_HANDLE, :EVT_EVENT_PROPERTY_ID, :DWORD, :PEVT_VARIANT, :PDWORD

define EVT_READ_ACCESS	  0x1
define EVT_WRITE_ACCESS	  0x2
define EVT_CLEAR_ACCESS	  0x4
define EVT_ALL_ACCESS	  0x7

endif

endif

endif

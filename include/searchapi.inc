.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __searchapi_h__
define __searchapi_h__

include unknwn.inc
include objidl.inc
include ocidl.inc
include propidl.inc
include filter.inc
include filtereg.inc
include propsys.inc
include oledb.inc
include structuredquery.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ITEMID	typedef LONG

ifndef __IUrlAccessor_INTERFACE_DEFINED__
define __IUrlAccessor_INTERFACE_DEFINED__

DEFINE_IIDX(IUrlAccessor, "0b63e318-9ccc-11d0-bcdb-00805fccce04")

.comdef IUrlAccessor : public IUnknown

    AddRequestParameter proc :ptr, :ptr
    GetDocFormat	proc :ptr, :DWORD, :ptr
    GetCLSID		proc :ptr
    GetHost		proc :ptr, :DWORD, :ptr
    IsDirectory		proc
    GetSize		proc :ptr
    GetLastModified	proc :ptr
    GetFileName		proc :ptr, :DWORD, :ptr
    GetSecurityDescriptor proc
    GetRedirectedURL	proc :ptr, :DWORD, :ptr
    GetSecurityProvider proc :ptr
    BindToStream	proc :ptr
    BindToFilter	proc :ptr
   .ends

endif


ifndef __IUrlAccessor2_INTERFACE_DEFINED__
define __IUrlAccessor2_INTERFACE_DEFINED__

DEFINE_IIDX(IUrlAccessor2, "c7310734-ac80-11d1-8df3-00c04fb6ef4f")

.comdef IUrlAccessor2 : public IUrlAccessor

    GetDisplayUrl	proc :ptr, :DWORD, :ptr
    IsDocument		proc
    GetCodePage		proc :ptr, :DWORD, :ptr
   .ends

endif


ifndef __IUrlAccessor3_INTERFACE_DEFINED__
define __IUrlAccessor3_INTERFACE_DEFINED__

DEFINE_IIDX(IUrlAccessor3, "6FBC7005-0455-4874-B8FF-7439450241A3")

.comdef IUrlAccessor3 : public IUrlAccessor2

    GetImpersonationSidBlobs proc :LPCWSTR, :ptr, :ptr
   .ends

endif


ifndef __IUrlAccessor4_INTERFACE_DEFINED__
define __IUrlAccessor4_INTERFACE_DEFINED__

DEFINE_IIDX(IUrlAccessor4, "5CC51041-C8D2-41d7-BCA3-9E9E286297DC")

.comdef IUrlAccessor4 : public IUrlAccessor3

    ShouldIndexItemContent proc :ptr
    ShouldIndexProperty proc :REFPROPERTYKEY, :ptr
   .ends

endif

ifndef __IOpLockStatus_INTERFACE_DEFINED__
define __IOpLockStatus_INTERFACE_DEFINED__

DEFINE_IIDX(IOpLockStatus, "c731065d-ac80-11d1-8df3-00c04fb6ef4f")

.comdef IOpLockStatus : public IUnknown

    IsOplockValid	proc :ptr
    IsOplockBroken	proc :ptr
    GetOplockEventHandle proc :ptr
   .ends

endif


ifndef __ISearchProtocolThreadContext_INTERFACE_DEFINED__
define __ISearchProtocolThreadContext_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchProtocolThreadContext, "c73106e1-ac80-11d1-8df3-00c04fb6ef4f")

.comdef ISearchProtocolThreadContext : public IUnknown

    ThreadInit		proc
    ThreadShutdown	proc
    ThreadIdle		proc :DWORD
   .ends

endif

.pragma pack(push, 8)

TIMEOUT_INFO		STRUC
dwSize			dd ?
dwConnectTimeout	dd ?
dwDataTimeout		dd ?
TIMEOUT_INFO		ENDS

.enum PROXY_ACCESS {
    PROXY_ACCESS_PRECONFIG = 0,
    PROXY_ACCESS_DIRECT = ( PROXY_ACCESS_PRECONFIG + 1 ),
    PROXY_ACCESS_PROXY	= ( PROXY_ACCESS_DIRECT + 1 )
    }

PROXY_INFO		STRUC
dwSize			dd ?
pcwszUserAgent		LPCWSTR ?
paUseProxy		PROXY_ACCESS ?
fLocalBypass		BOOL ?
dwPortNumber		dd ?
pcwszProxyName		LPCWSTR ?
pcwszBypassList		LPCWSTR ?
PROXY_INFO		ENDS

.enum AUTH_TYPE {
    eAUTH_TYPE_ANONYMOUS = 0,
    eAUTH_TYPE_NTLM	= ( eAUTH_TYPE_ANONYMOUS + 1 ),
    eAUTH_TYPE_BASIC	= ( eAUTH_TYPE_NTLM + 1 )
    }

AUTHENTICATION_INFO	STRUC
dwSize			dd ?
atAuthenticationType	AUTH_TYPE ?
pcwszUser		LPCWSTR ?
pcwszPassword		LPCWSTR ?
AUTHENTICATION_INFO	ENDS

INCREMENTAL_ACCESS_INFO STRUC
dwSize			dd ?
ftLastModifiedTime	FILETIME <>
INCREMENTAL_ACCESS_INFO ENDS

ITEM_INFO		STRUC
dwSize			dd ?
pcwszFromEMail		LPCWSTR ?
pcwszApplicationName	LPCWSTR ?
pcwszCatalogName	LPCWSTR ?
pcwszContentClass	LPCWSTR ?
ITEM_INFO		ENDS

ifndef __ISearchProtocol_INTERFACE_DEFINED__
define __ISearchProtocol_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchProtocol, "c73106ba-ac80-11d1-8df3-00c04fb6ef4f")

.comdef ISearchProtocol : public IUnknown

    Init		proc :ptr, :ptr, :ptr
    CreateAccessor	proc :LPCWSTR, :ptr, :ptr, :ptr, :ptr
    CloseAccessor	proc :ptr
    ShutDown		proc
   .ends

endif


ifndef __ISearchProtocol2_INTERFACE_DEFINED__
define __ISearchProtocol2_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchProtocol2, "7789F0B2-B5B2-4722-8B65-5DBD150697A9")

.comdef ISearchProtocol2 : public ISearchProtocol

    CreateAccessorEx	proc :LPCWSTR, :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif


ifndef __IProtocolHandlerSite_INTERFACE_DEFINED__
define __IProtocolHandlerSite_INTERFACE_DEFINED__

DEFINE_IIDX(IProtocolHandlerSite, "0b63e385-9ccc-11d0-bcdb-00805fccce04")

.comdef IProtocolHandlerSite : public IUnknown

    GetFilter		proc :ptr, :LPCWSTR, :LPCWSTR, :ptr
   .ends

endif

.pragma pack(pop)

ifndef __ISearchRoot_INTERFACE_DEFINED__
define __ISearchRoot_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchRoot, "04C18CCF-1F57-4CBD-88CC-3900F5195CE3")

.comdef ISearchRoot : public IUnknown

    put_Schedule	proc :LPCWSTR
    get_Schedule	proc :ptr
    put_RootURL		proc :LPCWSTR
    get_RootURL		proc :ptr
    put_IsHierarchical	proc :BOOL
    get_IsHierarchical	proc :ptr
    put_ProvidesNotifications proc :BOOL
    get_ProvidesNotifications proc :ptr
    put_UseNotificationsOnly proc :BOOL
    get_UseNotificationsOnly proc :ptr
    put_EnumerationDepth proc :DWORD
    get_EnumerationDepth proc :ptr
    put_HostDepth	proc :DWORD
    get_HostDepth	proc :ptr
    put_FollowDirectories proc :BOOL
    get_FollowDirectories proc :ptr
    put_AuthenticationType proc :AUTH_TYPE
    get_AuthenticationType proc :ptr
    put_User		proc :LPCWSTR
    get_User		proc :ptr
    put_Password	proc :LPCWSTR
    get_Password	proc :ptr
   .ends

endif


ifndef __IEnumSearchRoots_INTERFACE_DEFINED__
define __IEnumSearchRoots_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumSearchRoots, "AB310581-AC80-11D1-8DF3-00C04FB6EF52")

.comdef IEnumSearchRoots : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

.enum FOLLOW_FLAGS {
    FF_INDEXCOMPLEXURLS = 0x1,
    FF_SUPPRESSINDEXING = 0x2
    }


ifndef __ISearchScopeRule_INTERFACE_DEFINED__
define __ISearchScopeRule_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchScopeRule, "AB310581-AC80-11D1-8DF3-00C04FB6EF53")

.comdef ISearchScopeRule : public IUnknown

    get_PatternOrURL	proc :ptr
    get_IsIncluded	proc :ptr
    get_IsDefault	proc :ptr
    get_FollowFlags	proc :ptr
   .ends

endif


ifndef __IEnumSearchScopeRules_INTERFACE_DEFINED__
define __IEnumSearchScopeRules_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumSearchScopeRules, "AB310581-AC80-11D1-8DF3-00C04FB6EF54")

.comdef IEnumSearchScopeRules : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

.enum CLUSION_REASON {
    CLUSIONREASON_UNKNOWNSCOPE	= 0,
    CLUSIONREASON_DEFAULT	= 1,
    CLUSIONREASON_USER	= 2,
    CLUSIONREASON_GROUPPOLICY	= 3
    }

ifndef __ISearchCrawlScopeManager_INTERFACE_DEFINED__
define __ISearchCrawlScopeManager_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchCrawlScopeManager, "AB310581-AC80-11D1-8DF3-00C04FB6EF55")

.comdef ISearchCrawlScopeManager : public IUnknown

    AddDefaultScopeRule proc :LPCWSTR, :BOOL, :DWORD
    AddRoot		proc :ptr
    RemoveRoot		proc :LPCWSTR
    EnumerateRoots	proc :ptr
    AddHierarchicalScope proc :LPCWSTR, :BOOL, :BOOL, :BOOL
    AddUserScopeRule	proc :LPCWSTR, :BOOL, :BOOL, :DWORD
    RemoveScopeRule	proc :LPCWSTR
    EnumerateScopeRules proc :ptr
    HasParentScopeRule	proc :LPCWSTR, :ptr
    HasChildScopeRule	proc :LPCWSTR, :ptr
    IncludedInCrawlScope proc :LPCWSTR, :ptr
    IncludedInCrawlScopeEx proc :LPCWSTR, :ptr, :ptr
    RevertToDefaultScopes proc
    SaveAll		proc
    GetParentScopeVersionId proc :LPCWSTR, :ptr
    RemoveDefaultScopeRule proc :LPCWSTR
   .ends

endif


ifndef __ISearchCrawlScopeManager2_INTERFACE_DEFINED__
define __ISearchCrawlScopeManager2_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchCrawlScopeManager2, "6292F7AD-4E19-4717-A534-8FC22BCD5CCD")

.comdef ISearchCrawlScopeManager2 : public ISearchCrawlScopeManager

    GetVersion		proc :ptr, :ptr
   .ends

endif

.enum SEARCH_KIND_OF_CHANGE {
    SEARCH_CHANGE_ADD	= 0,
    SEARCH_CHANGE_DELETE	= 1,
    SEARCH_CHANGE_MODIFY	= 2,
    SEARCH_CHANGE_MOVE_RENAME	= 3,
    SEARCH_CHANGE_SEMANTICS_DIRECTORY	= 0x40000,
    SEARCH_CHANGE_SEMANTICS_SHALLOW	= 0x80000,
    SEARCH_CHANGE_SEMANTICS_UPDATE_SECURITY	= 0x400000
    }

.enum SEARCH_NOTIFICATION_PRIORITY {
    SEARCH_NORMAL_PRIORITY	= 0,
    SEARCH_HIGH_PRIORITY	= 1
    }


ifndef __ISearchItemsChangedSink_INTERFACE_DEFINED__
define __ISearchItemsChangedSink_INTERFACE_DEFINED__

SEARCH_ITEM_CHANGE	STRUC
Change			SEARCH_KIND_OF_CHANGE ?
Priority		SEARCH_NOTIFICATION_PRIORITY ?
pUserData		LPBLOB ?
lpwszURL		LPWSTR ?
SEARCH_ITEM_CHANGE	ENDS

DEFINE_IIDX(ISearchItemsChangedSink, "AB310581-AC80-11D1-8DF3-00C04FB6EF58")

.comdef ISearchItemsChangedSink : public IUnknown

    StartedMonitoringScope proc :LPCWSTR
    StoppedMonitoringScope proc :LPCWSTR
    OnItemsChanged	proc :DWORD, :ptr, :ptr, :ptr
   .ends

endif


ifndef __ISearchPersistentItemsChangedSink_INTERFACE_DEFINED__
define __ISearchPersistentItemsChangedSink_INTERFACE_DEFINED__


SEARCH_ITEM_PERSISTENT_CHANGE STRUC
Change			SEARCH_KIND_OF_CHANGE ?
URL			LPWSTR ?
Priority		SEARCH_NOTIFICATION_PRIORITY ?
SEARCH_ITEM_PERSISTENT_CHANGE ENDS

DEFINE_IIDX(ISearchPersistentItemsChangedSink, "A2FFDF9B-4758-4F84-B729-DF81A1A0612F")

.comdef ISearchPersistentItemsChangedSink : public IUnknown

    StartedMonitoringScope proc :LPCWSTR
    StoppedMonitoringScope proc :LPCWSTR
    OnItemsChanged	proc :DWORD, :ptr, :ptr
   .ends

endif


ifndef __ISearchViewChangedSink_INTERFACE_DEFINED__
define __ISearchViewChangedSink_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchViewChangedSink, "AB310581-AC80-11D1-8DF3-00C04FB6EF65")

.comdef ISearchViewChangedSink : public IUnknown

    OnChange		proc :ptr, :ptr, :ptr
   .ends

endif

ifndef __ISearchNotifyInlineSite_INTERFACE_DEFINED__
define __ISearchNotifyInlineSite_INTERFACE_DEFINED__

.enum SEARCH_INDEXING_PHASE {
    SEARCH_INDEXING_PHASE_GATHERER	= 0,
    SEARCH_INDEXING_PHASE_QUERYABLE	= 1,
    SEARCH_INDEXING_PHASE_PERSISTED	= 2
    }

SEARCH_ITEM_INDEXING_STATUS STRUC
dwDocID			dd ?
hrIndexingStatus	HRESULT ?
SEARCH_ITEM_INDEXING_STATUS ENDS

DEFINE_IIDX(ISearchNotifyInlineSite, "B5702E61-E75C-4B64-82A1-6CB4F832FCCF")

.comdef ISearchNotifyInlineSite : public IUnknown

    OnItemIndexedStatusChange proc :SEARCH_INDEXING_PHASE, :DWORD, :SEARCH_ITEM_INDEXING_STATUS
    OnCatalogStatusChange proc :REFGUID, :REFGUID, :DWORD
   .ends

endif

.enum CatalogStatus {
    CATALOG_STATUS_IDLE = 0,
    CATALOG_STATUS_PAUSED	= 1,
    CATALOG_STATUS_RECOVERING	= 2,
    CATALOG_STATUS_FULL_CRAWL	= 3,
    CATALOG_STATUS_INCREMENTAL_CRAWL	= 4,
    CATALOG_STATUS_PROCESSING_NOTIFICATIONS	= 5,
    CATALOG_STATUS_SHUTTING_DOWN	= 6
    }

.enum CatalogPausedReason {
    CATALOG_PAUSED_REASON_NONE	= 0,
    CATALOG_PAUSED_REASON_HIGH_IO	= 1,
    CATALOG_PAUSED_REASON_HIGH_CPU	= 2,
    CATALOG_PAUSED_REASON_HIGH_NTF_RATE = 3,
    CATALOG_PAUSED_REASON_LOW_BATTERY	= 4,
    CATALOG_PAUSED_REASON_LOW_MEMORY	= 5,
    CATALOG_PAUSED_REASON_LOW_DISK	= 6,
    CATALOG_PAUSED_REASON_DELAYED_RECOVERY	= 7,
    CATALOG_PAUSED_REASON_USER_ACTIVE	= 8,
    CATALOG_PAUSED_REASON_EXTERNAL	= 9,
    CATALOG_PAUSED_REASON_UPGRADING	= 10
    }


ifndef __ISearchCatalogManager_INTERFACE_DEFINED__
define __ISearchCatalogManager_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchCatalogManager, "AB310581-AC80-11D1-8DF3-00C04FB6EF50")

.comdef ISearchCatalogManager : public IUnknown

    get_Name		proc :ptr
    GetParameter	proc :LPCWSTR, :ptr
    SetParameter	proc :LPCWSTR, :ptr
    GetCatalogStatus	proc :ptr, :ptr
    Reset		proc
    Reindex		proc
    ReindexMatchingURLs proc :LPCWSTR
    ReindexSearchRoot	proc :LPCWSTR
    put_ConnectTimeout	proc :DWORD
    get_ConnectTimeout	proc :ptr
    put_DataTimeout	proc :DWORD
    get_DataTimeout	proc :ptr
    NumberOfItems	proc :ptr
    NumberOfItemsToIndex proc :ptr, :ptr, :ptr
    URLBeingIndexed	proc :ptr
    GetURLIndexingState proc :LPCWSTR, :ptr
    GetPersistentItemsChangedSink proc :ptr
    RegisterViewForNotification proc :LPCWSTR, :ptr, :ptr
    GetItemsChangedSink proc :ptr, :REFIID, :ptr, :ptr, :ptr, :ptr
    UnregisterViewForNotification proc :DWORD
    SetExtensionClusion proc :LPCWSTR, :BOOL
    EnumerateExcludedExtensions proc :ptr
    GetQueryHelper	proc :ptr
    put_DiacriticSensitivity proc :BOOL
    get_DiacriticSensitivity proc :ptr
    GetCrawlScopeManager proc :ptr
    .ends

endif

.enum tagPRIORITIZE_FLAGS {
    PRIORITIZE_FLAG_RETRYFAILEDITEMS	= 0x1,
    PRIORITIZE_FLAG_IGNOREFAILURECOUNT	= 0x2
    }

PRIORITIZE_FLAGS	typedef int_t


ifndef __ISearchCatalogManager2_INTERFACE_DEFINED__
define __ISearchCatalogManager2_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchCatalogManager2, "7AC3286D-4D1D-4817-84FC-C1C85E3AF0D9")

.comdef ISearchCatalogManager2 : public ISearchCatalogManager

    PrioritizeMatchingURLs proc :LPCWSTR, :PRIORITIZE_FLAGS
   .ends

endif

ifndef __ISearchQueryHelper_INTERFACE_DEFINED__
define __ISearchQueryHelper_INTERFACE_DEFINED__


.enum SEARCH_TERM_EXPANSION {
    SEARCH_TERM_NO_EXPANSION	= 0,
    SEARCH_TERM_PREFIX_ALL	= ( SEARCH_TERM_NO_EXPANSION + 1 ) ,
    SEARCH_TERM_STEM_ALL	= ( SEARCH_TERM_PREFIX_ALL + 1 )
    }

.enum SEARCH_QUERY_SYNTAX {
    SEARCH_NO_QUERY_SYNTAX	= 0,
    SEARCH_ADVANCED_QUERY_SYNTAX	= ( SEARCH_NO_QUERY_SYNTAX + 1 ) ,
    SEARCH_NATURAL_QUERY_SYNTAX = ( SEARCH_ADVANCED_QUERY_SYNTAX + 1 )
    }

SEARCH_COLUMN_PROPERTIES STRUC
Value			PROPVARIANT <>
lcid			LCID ?
SEARCH_COLUMN_PROPERTIES ENDS

DEFINE_IIDX(ISearchQueryHelper, "AB310581-AC80-11D1-8DF3-00C04FB6EF63")

.comdef ISearchQueryHelper : public IUnknown

    get_ConnectionString proc :ptr
    put_QueryContentLocale proc :LCID
    get_QueryContentLocale proc :ptr
    put_QueryKeywordLocale proc :LCID
    get_QueryKeywordLocale proc :ptr
    put_QueryTermExpansion proc :SEARCH_TERM_EXPANSION
    get_QueryTermExpansion proc :ptr
    put_QuerySyntax	proc :SEARCH_QUERY_SYNTAX
    get_QuerySyntax	proc :ptr
    put_QueryContentProperties proc :LPCWSTR
    get_QueryContentProperties proc :ptr
    put_QuerySelectColumns proc :LPCWSTR
    get_QuerySelectColumns proc :ptr
    put_QueryWhereRestrictions proc :LPCWSTR
    get_QueryWhereRestrictions proc :ptr
    put_QuerySorting	proc :LPCWSTR
    get_QuerySorting	proc :ptr
    GenerateSQLFromUserQuery proc :LPCWSTR, :ptr
    WriteProperties	proc :ITEMID, :DWORD, :ptr, :ptr, :ptr
    put_QueryMaxResults proc :LONG
    get_QueryMaxResults proc :ptr
    .ends

endif

.enum PRIORITY_LEVEL {
    PRIORITY_LEVEL_FOREGROUND	= 0,
    PRIORITY_LEVEL_HIGH = 1,
    PRIORITY_LEVEL_LOW	= 2,
    PRIORITY_LEVEL_DEFAULT	= 3
    }

ifndef __IRowsetPrioritization_INTERFACE_DEFINED__
define __IRowsetPrioritization_INTERFACE_DEFINED__

DEFINE_IIDX(IRowsetPrioritization, "42811652-079D-481B-87A2-09A69ECC5F44")

.comdef IRowsetPrioritization : public IUnknown

    SetScopePriority	proc :PRIORITY_LEVEL, :DWORD
    GetScopePriority	proc :ptr, :ptr
    GetScopeStatistics	proc :ptr, :ptr, :ptr
   .ends

endif

.enum ROWSETEVENT_ITEMSTATE {
    ROWSETEVENT_ITEMSTATE_NOTINROWSET	= 0,
    ROWSETEVENT_ITEMSTATE_INROWSET	= 1,
    ROWSETEVENT_ITEMSTATE_UNKNOWN	= 2
    }

.enum ROWSETEVENT_TYPE {
    ROWSETEVENT_TYPE_DATAEXPIRED	= 0,
    ROWSETEVENT_TYPE_FOREGROUNDLOST	= 1,
    ROWSETEVENT_TYPE_SCOPESTATISTICS	= 2
    }

ifndef __IRowsetEvents_INTERFACE_DEFINED__
define __IRowsetEvents_INTERFACE_DEFINED__

DEFINE_IIDX(IRowsetEvents, "1551AEA5-5D66-4B11-86F5-D5634CB211B9")

.comdef IRowsetEvents : public IUnknown

    OnNewItem		proc :REFPROPVARIANT, :ROWSETEVENT_ITEMSTATE
    OnChangedItem	proc :REFPROPVARIANT, :ROWSETEVENT_ITEMSTATE, :ROWSETEVENT_ITEMSTATE
    OnDeletedItem	proc :REFPROPVARIANT, :ROWSETEVENT_ITEMSTATE
    OnRowsetEvent	proc :ROWSETEVENT_TYPE, :REFPROPVARIANT
   .ends

endif

ifndef __ISearchManager_INTERFACE_DEFINED__
define __ISearchManager_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchManager, "AB310581-AC80-11D1-8DF3-00C04FB6EF69")

.comdef ISearchManager : public IUnknown

    GetIndexerVersionStr proc :ptr
    GetIndexerVersion	proc :ptr, :ptr
    GetParameter	proc :LPCWSTR, :ptr
    SetParameter	proc :LPCWSTR, :ptr
    get_ProxyName	proc :ptr
    get_BypassList	proc :ptr
    SetProxy		proc :PROXY_ACCESS, :BOOL, :DWORD, :LPCWSTR, :LPCWSTR
    GetCatalog		proc :LPCWSTR, :ptr
    get_UserAgent	proc :ptr
    put_UserAgent	proc :LPCWSTR
    get_UseProxy	proc :ptr
    get_LocalBypass	proc :ptr
    get_PortNumber	proc :ptr
   .ends

endif


ifndef __ISearchManager2_INTERFACE_DEFINED__
define __ISearchManager2_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchManager2, "DBAB3F73-DB19-4A79-BFC0-A61A93886DDF")

.comdef ISearchManager2 : public ISearchManager

    CreateCatalog	proc :LPCWSTR, :ptr
    DeleteCatalog	proc :LPCWSTR
   .ends

endif

DEFINE_GUIDS(CLSID_CSearchLanguageSupport, "6A68CC80-4337-4dbc-BD27-FBFB1053820B")

ifndef __ISearchLanguageSupport_INTERFACE_DEFINED__
define __ISearchLanguageSupport_INTERFACE_DEFINED__

DEFINE_IIDX(ISearchLanguageSupport, "24C3CBAA-EBC1-491a-9EF1-9F6D8DEB1B8F")

.comdef ISearchLanguageSupport : public IUnknown

    SetDiacriticSensitivity proc :BOOL
    GetDiacriticSensitivity proc :ptr
    LoadWordBreaker	proc :LCID, :REFIID, :ptr, :ptr
    LoadStemmer		proc :LCID, :REFIID, :ptr, :ptr
    IsPrefixNormalized	proc :LPCWSTR, :ULONG, :ptr
   .ends

endif

ifndef __SearchAPILib_LIBRARY_DEFINED__
define __SearchAPILib_LIBRARY_DEFINED__

externdef LIBID_SearchAPILib:IID
DEFINE_GUIDS(CLSID_CSearchManager,	"7D096C5F-AC08-4f1f-BEB7-5C22C517CE39")
DEFINE_GUIDS(CLSID_CSearchRoot,		"30766BD2-EA1C-4F28-BF27-0B44E2F68DB7")
DEFINE_GUIDS(CLSID_CSearchScopeRule,	"E63DE750-3BD7-4BE5-9C84-6B4281988C44")
DEFINE_GUIDS(CLSID_FilterRegistration,	"9E175B8D-F52A-11D8-B9A5-505054503030")

endif

endif

BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

LPSAFEARRAY_UserSize proto WINAPI :ptr, :dword, :ptr
LPSAFEARRAY_UserMarshal proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserFree proto WINAPI :ptr, :ptr

BSTR_UserSize64 proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree64 proto WINAPI :ptr, :ptr

LPSAFEARRAY_UserSize64 proto WINAPI :ptr, :dword, :ptr
LPSAFEARRAY_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserFree64 proto WINAPI :ptr, :ptr

endif
.pragma list(pop)

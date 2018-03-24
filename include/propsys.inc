ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
 .err <this stub requires an updated version of rpcndr>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __propsys_h__
__propsys_h__ equ <>

include objidl.inc
include oleidl.inc
include ocidl.inc
include shtypes.inc
include StructuredQueryCondition.inc
include propkeydef.inc
.xlist

externdef		__MIDL_itf_propsys_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propsys_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInitializeWithFile_INTERFACE_DEFINED__
__IInitializeWithFile_INTERFACE_DEFINED__ equ 1

externdef		IID_IInitializeWithFile:IID
IInitializeWithFileVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :LPCWSTR, :DWORD
IInitializeWithFileVtbl ends
IInitializeWithFile struct
	lpVtbl		PVOID ?
IInitializeWithFile ends

endif

ifndef __IInitializeWithStream_INTERFACE_DEFINED__
__IInitializeWithStream_INTERFACE_DEFINED__ equ 1

externdef		IID_IInitializeWithStream:IID
IInitializeWithStreamVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :ptr, :DWORD
IInitializeWithStreamVtbl ends
IInitializeWithStream struct
	lpVtbl		PVOID ?
IInitializeWithStream ends

;HRESULT
IInitializeWithStream_RemoteInitialize_Proxy proto WINAPI \
		 _This: ptr IInitializeWithStream,
	       pstream: ptr IStream,
	       grfMode: DWORD

;void
IInitializeWithStream_RemoteInitialize_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IPropertyStore_INTERFACE_DEFINED__
__IPropertyStore_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyStore:IID
IPropertyStoreVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCount, :ptr
	STDMETHOD	GetAt, :DWORD, :ptr
	STDMETHOD	GetValue, :REFPROPERTYKEY, :ptr
	STDMETHOD	SetValue, :REFPROPERTYKEY, :REFPROPVARIANT
	STDMETHOD	Commit
IPropertyStoreVtbl ends
IPropertyStore struct
	lpVtbl		PVOID ?
IPropertyStore ends
LPPROPERTYSTORE		typedef ptr IPropertyStore

endif

externdef		__MIDL_itf_propsys_0000_0003_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propsys_0000_0003_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INamedPropertyStore_INTERFACE_DEFINED__
__INamedPropertyStore_INTERFACE_DEFINED__ equ 1

externdef		IID_INamedPropertyStore:IID
INamedPropertyStoreVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetNamedValue, :LPCWSTR, :ptr
	STDMETHOD	SetNamedValue, :LPCWSTR, :REFPROPVARIANT
	STDMETHOD	GetNameCount, :ptr
	STDMETHOD	GetNameAt, :DWORD, :ptr
INamedPropertyStoreVtbl ends
INamedPropertyStore struct
	lpVtbl		PVOID ?
INamedPropertyStore ends

endif

GETPROPERTYSTOREFLAGS	typedef SDWORD
GPS_DEFAULT		equ 0
GPS_HANDLERPROPERTIESONLY equ 0x1
GPS_READWRITE		equ 0x2
GPS_TEMPORARY		equ 0x4
GPS_FASTPROPERTIESONLY	equ 0x8
GPS_OPENSLOWITEM	equ 0x10
GPS_DELAYCREATION	equ 0x20
GPS_BESTEFFORT		equ 0x40
GPS_NO_OPLOCK		equ 0x80
GPS_MASK_VALID		equ 0xff

DEFINE_ENUM_FLAG_OPERATORS(GETPROPERTYSTOREFLAGS)

externdef		__MIDL_itf_propsys_0000_0004_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propsys_0000_0004_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IObjectWithPropertyKey_INTERFACE_DEFINED__
__IObjectWithPropertyKey_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectWithPropertyKey:IID
IObjectWithPropertyKeyVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetPropertyKey, :REFPROPERTYKEY
	STDMETHOD	GetPropertyKey, :ptr
IObjectWithPropertyKeyVtbl ends
IObjectWithPropertyKey struct
	lpVtbl		PVOID ?
IObjectWithPropertyKey ends

endif

PKA_FLAGS		typedef SDWORD
PKA_SET			equ 0
PKA_APPEND		equ ( PKA_SET + 1 )
PKA_DELETE		equ ( PKA_APPEND + 1 )

externdef		__MIDL_itf_propsys_0000_0005_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propsys_0000_0005_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPropertyChange_INTERFACE_DEFINED__
__IPropertyChange_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyChange:IID
IPropertyChangeVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetPropertyKey, :REFPROPERTYKEY
	STDMETHOD	GetPropertyKey, :ptr
	STDMETHOD	ApplyToPropVariant, :REFPROPVARIANT, :ptr
IPropertyChangeVtbl ends
IPropertyChange struct
	lpVtbl		PVOID ?
IPropertyChange ends

endif

ifndef __IPropertyChangeArray_INTERFACE_DEFINED__
__IPropertyChangeArray_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyChangeArray:IID
IPropertyChangeArrayVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCount, :ptr
	STDMETHOD	GetAt, :UINT, :REFIID, :ptr
	STDMETHOD	InsertAt, :UINT, :ptr
	STDMETHOD	Append, :ptr
	STDMETHOD	AppendOrReplace, :ptr
	STDMETHOD	RemoveAt, :UINT
	STDMETHOD	IsKeyInArray, :REFPROPERTYKEY
IPropertyChangeArrayVtbl ends
IPropertyChangeArray struct
	lpVtbl		PVOID ?
IPropertyChangeArray ends

endif

ifndef __IPropertyStoreCapabilities_INTERFACE_DEFINED__
__IPropertyStoreCapabilities_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyStoreCapabilities:IID
IPropertyStoreCapabilitiesVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	IsPropertyWritable, :REFPROPERTYKEY
IPropertyStoreCapabilitiesVtbl ends
IPropertyStoreCapabilities struct
	lpVtbl		PVOID ?
IPropertyStoreCapabilities ends

endif

ifndef __IPropertyStoreCache_INTERFACE_DEFINED__
__IPropertyStoreCache_INTERFACE_DEFINED__ equ 1

PSC_STATE		typedef ptr SDWORD
PSC_NORMAL		equ 0
PSC_NOTINSOURCE		equ 1
PSC_DIRTY		equ 2
PSC_READONLY		equ 3

externdef		IID_IPropertyStoreCache:IID
IPropertyStoreCacheVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCount, :ptr
	STDMETHOD	GetAt, :DWORD, :ptr
	STDMETHOD	GetValue, :REFPROPERTYKEY, :ptr
	STDMETHOD	SetValue, :REFPROPERTYKEY, :REFPROPVARIANT
	STDMETHOD	Commit
	STDMETHOD	GetState, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetValueAndState, :REFPROPERTYKEY, :ptr, :ptr
	STDMETHOD	SetState, :REFPROPERTYKEY, :PSC_STATE
	STDMETHOD	SetValueAndState, :REFPROPERTYKEY, :ptr, :PSC_STATE
IPropertyStoreCacheVtbl ends
IPropertyStoreCache struct
	lpVtbl		PVOID ?
IPropertyStoreCache ends

endif

ifndef __IPropertyEnumType_INTERFACE_DEFINED__
__IPropertyEnumType_INTERFACE_DEFINED__ equ 1

PROPENUMTYPE		typedef SDWORD
PET_DISCRETEVALUE	equ 0
PET_RANGEDVALUE		equ 1
PET_DEFAULTVALUE	equ 2
PET_ENDRANGE		equ 3

externdef		IID_IPropertyEnumType:IID
IPropertyEnumTypeVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetEnumType, :ptr
	STDMETHOD	GetValue, :ptr
	STDMETHOD	GetRangeMinValue, :ptr
	STDMETHOD	GetRangeSetValue, :ptr
	STDMETHOD	GetDisplayText, :ptr
IPropertyEnumTypeVtbl ends
IPropertyEnumType struct
	lpVtbl		PVOID ?
IPropertyEnumType ends

endif

ifndef __IPropertyEnumType2_INTERFACE_DEFINED__
__IPropertyEnumType2_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyEnumType2:IID
IPropertyEnumType2Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetEnumType, :ptr
	STDMETHOD	GetValue, :ptr
	STDMETHOD	GetRangeMinValue, :ptr
	STDMETHOD	GetRangeSetValue, :ptr
	STDMETHOD	GetDisplayText, :ptr
	STDMETHOD	GetImageReference, :ptr
IPropertyEnumType2Vtbl ends
IPropertyEnumType2 struct
	lpVtbl		PVOID ?
IPropertyEnumType2 ends

endif

ifndef __IPropertyEnumTypeList_INTERFACE_DEFINED__
__IPropertyEnumTypeList_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyEnumTypeList:IID

IPropertyEnumTypeListVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCount, :ptr
	STDMETHOD	GetAt, :UINT, :REFIID, :ptr
	STDMETHOD	GetConditionAt, :UINT, :REFIID, :ptr
	STDMETHOD	FindMatchingIndex, :REFPROPVARIANT, :ptr
IPropertyEnumTypeListVtbl ends
IPropertyEnumTypeList struct
	lpVtbl		PVOID ?
IPropertyEnumTypeList ends

endif

ifndef __IPropertyDescription_INTERFACE_DEFINED__
__IPropertyDescription_INTERFACE_DEFINED__ equ 1


PROPDESC_TYPE_FLAGS	typedef SDWORD
PDTF_DEFAULT		equ 0
PDTF_MULTIPLEVALUES	equ 0x1
PDTF_ISINNATE		equ 0x2
PDTF_ISGROUP		equ 0x4
PDTF_CANGROUPBY		equ 0x8
PDTF_CANSTACKBY		equ 0x10
PDTF_ISTREEPROPERTY	equ 0x20
PDTF_INCLUDEINFULLTEXTQUERY equ 0x40
PDTF_ISVIEWABLE		equ 0x80
PDTF_ISQUERYABLE	equ 0x100
PDTF_CANBEPURGED	equ 0x200
PDTF_SEARCHRAWVALUE	equ 0x400
PDTF_ISSYSTEMPROPERTY	equ 0x80000000
PDTF_MASK_ALL		equ 0x800007ff

DEFINE_ENUM_FLAG_OPERATORS(PROPDESC_TYPE_FLAGS)
PROPDESC_VIEW_FLAGS	typedef SDWORD
PDVF_DEFAULT		equ 0
PDVF_CENTERALIGN	equ 0x1
PDVF_RIGHTALIGN		equ 0x2
PDVF_BEGINNEWGROUP	equ 0x4
PDVF_FILLAREA		equ 0x8
PDVF_SORTDESCENDING	equ 0x10
PDVF_SHOWONLYIFPRESENT	equ 0x20
PDVF_SHOWBYDEFAULT	equ 0x40
PDVF_SHOWINPRIMARYLIST	equ 0x80
PDVF_SHOWINSECONDARYLIST equ 0x100
PDVF_HIDELABEL		equ 0x200
PDVF_HIDDEN		equ 0x800
PDVF_CANWRAP		equ 0x1000
PDVF_MASK_ALL		equ 0x1bff

DEFINE_ENUM_FLAG_OPERATORS(PROPDESC_VIEW_FLAGS)
PROPDESC_DISPLAYTYPE	typedef SDWORD
PDDT_STRING		equ 0
PDDT_NUMBER		equ 1
PDDT_BOOLEAN		equ 2
PDDT_DATETIME		equ 3
PDDT_ENUMERATED		equ 4

PROPDESC_GROUPING_RANGE typedef SDWORD
PDGR_DISCRETE		equ 0
PDGR_ALPHANUMERIC	equ 1
PDGR_SIZE		equ 2
PDGR_DYNAMIC		equ 3
PDGR_DATE		equ 4
PDGR_PERCENT		equ 5
PDGR_ENUMERATED		equ 6

PROPDESC_FORMAT_FLAGS	typedef SDWORD
PDFF_DEFAULT		equ 0
PDFF_PREFIXNAME		equ 0x1
PDFF_FILENAME		equ 0x2
PDFF_ALWAYSKB		equ 0x4
PDFF_RESERVED_RIGHTTOLEFT equ 0x8
PDFF_SHORTTIME		equ 0x10
PDFF_LONGTIME		equ 0x20
PDFF_HIDETIME		equ 0x40
PDFF_SHORTDATE		equ 0x80
PDFF_LONGDATE		equ 0x100
PDFF_HIDEDATE		equ 0x200
PDFF_RELATIVEDATE	equ 0x400
PDFF_USEEDITINVITATION	equ 0x800
PDFF_READONLY		equ 0x1000
PDFF_NOAUTOREADINGORDER equ 0x2000

DEFINE_ENUM_FLAG_OPERATORS(PROPDESC_FORMAT_FLAGS)

PROPDESC_SORTDESCRIPTION typedef SDWORD
PDSD_GENERAL		equ 0
PDSD_A_Z		equ 1
PDSD_LOWEST_HIGHEST	equ 2
PDSD_SMALLEST_BIGGEST	equ 3
PDSD_OLDEST_NEWEST	equ 4

PROPDESC_RELATIVEDESCRIPTION_TYPE typedef SDWORD
PDRDT_GENERAL		equ 0
PDRDT_DATE		equ 1
PDRDT_SIZE		equ 2
PDRDT_COUNT		equ 3
PDRDT_REVISION		equ 4
PDRDT_LENGTH		equ 5
PDRDT_DURATION		equ 6
PDRDT_SPEED		equ 7
PDRDT_RATE		equ 8
PDRDT_RATING		equ 9
PDRDT_PRIORITY		equ 10

PROPDESC_AGGREGATION_TYPE typedef SDWORD
PDAT_DEFAULT		equ 0
PDAT_FIRST		equ 1
PDAT_SUM		equ 2
PDAT_AVERAGE		equ 3
PDAT_DATERANGE		equ 4
PDAT_UNION		equ 5
PDAT_MAX		equ 6
PDAT_MIN		equ 7

PROPDESC_CONDITION_TYPE typedef SDWORD
PDCOT_NONE		equ 0
PDCOT_STRING		equ 1
PDCOT_SIZE		equ 2
PDCOT_DATETIME		equ 3
PDCOT_BOOLEAN		equ 4
PDCOT_NUMBER		equ 5


externdef		IID_IPropertyDescription:IID
IPropertyDescriptionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPropertyKey, :ptr
	STDMETHOD	GetCanonicalName, :ptr
	STDMETHOD	GetPropertyType, :ptr
	STDMETHOD	GetDisplayName, :ptr
	STDMETHOD	GetEditInvitation, :ptr
	STDMETHOD	GetTypeFlags, :PROPDESC_TYPE_FLAGS, :ptr
	STDMETHOD	GetViewFlags, :ptr
	STDMETHOD	GetDefaultColumnWidth, :ptr
	STDMETHOD	GetDisplayType, :ptr
	STDMETHOD	GetColumnState, :ptr
	STDMETHOD	GetGroupingRange, :ptr
	STDMETHOD	GetRelativeDescriptionType, :ptr
	STDMETHOD	GetRelativeDescription, :REFPROPVARIANT, :REFPROPVARIANT, :ptr, :ptr
	STDMETHOD	GetSortDescription, :ptr
	STDMETHOD	GetSortDescriptionLabel, :BOOL, :ptr
	STDMETHOD	GetAggregationType, :ptr
	STDMETHOD	GetConditionType, :ptr, :ptr
	STDMETHOD	GetEnumTypeList, :REFIID, :ptr
	STDMETHOD	CoerceToCanonicalValue, :ptr
	STDMETHOD	FormatForDisplay, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
	STDMETHOD	IsValueCanonical, :REFPROPVARIANT
IPropertyDescriptionVtbl ends
IPropertyDescription struct
	lpVtbl		PVOID ?
IPropertyDescription ends

;HRESULT
IPropertyDescription_RemoteCoerceToCanonicalValue_Proxy proto WINAPI \
		 _This: ptr IPropertyDescription,
	       propvar: REFPROPVARIANT,
	      ppropvar: ptr PROPVARIANT

;void
IPropertyDescription_RemoteCoerceToCanonicalValue_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IPropertyDescription2_INTERFACE_DEFINED__
__IPropertyDescription2_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyDescription2:IID
IPropertyDescription2Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPropertyKey, :ptr
	STDMETHOD	GetCanonicalName, :ptr
	STDMETHOD	GetPropertyType, :ptr
	STDMETHOD	GetDisplayName, :ptr
	STDMETHOD	GetEditInvitation, :ptr
	STDMETHOD	GetTypeFlags, :PROPDESC_TYPE_FLAGS, :ptr
	STDMETHOD	GetViewFlags, :ptr
	STDMETHOD	GetDefaultColumnWidth, :ptr
	STDMETHOD	GetDisplayType, :ptr
	STDMETHOD	GetColumnState, :ptr
	STDMETHOD	GetGroupingRange, :ptr
	STDMETHOD	GetRelativeDescriptionType, :ptr
	STDMETHOD	GetRelativeDescription, :REFPROPVARIANT, :REFPROPVARIANT, :ptr, :ptr
	STDMETHOD	GetSortDescription, :ptr
	STDMETHOD	GetSortDescriptionLabel, :BOOL, :ptr
	STDMETHOD	GetAggregationType, :ptr
	STDMETHOD	GetConditionType, :ptr, :ptr
	STDMETHOD	GetEnumTypeList, :REFIID, :ptr
	STDMETHOD	CoerceToCanonicalValue, :ptr
	STDMETHOD	FormatForDisplay, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
	STDMETHOD	IsValueCanonical, :REFPROPVARIANT
	STDMETHOD	GetImageReferenceForValue, :REFPROPVARIANT, :ptr
IPropertyDescription2Vtbl ends
IPropertyDescription2 struct
	lpVtbl		PVOID ?
IPropertyDescription2 ends

endif

ifndef __IPropertyDescriptionAliasInfo_INTERFACE_DEFINED__
__IPropertyDescriptionAliasInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyDescriptionAliasInfo:IID
IPropertyDescriptionAliasInfoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPropertyKey, :ptr
	STDMETHOD	GetCanonicalName, :ptr
	STDMETHOD	GetPropertyType, :ptr
	STDMETHOD	GetDisplayName, :ptr
	STDMETHOD	GetEditInvitation, :ptr
	STDMETHOD	GetTypeFlags, :PROPDESC_TYPE_FLAGS, :ptr
	STDMETHOD	GetViewFlags, :ptr
	STDMETHOD	GetDefaultColumnWidth, :ptr
	STDMETHOD	GetDisplayType, :ptr
	STDMETHOD	GetColumnState, :ptr
	STDMETHOD	GetGroupingRange, :ptr
	STDMETHOD	GetRelativeDescriptionType, :ptr
	STDMETHOD	GetRelativeDescription, :REFPROPVARIANT, :REFPROPVARIANT, :ptr, :ptr
	STDMETHOD	GetSortDescription, :ptr
	STDMETHOD	GetSortDescriptionLabel, :BOOL, :ptr
	STDMETHOD	GetAggregationType, :ptr
	STDMETHOD	GetConditionType, :ptr, :ptr
	STDMETHOD	GetEnumTypeList, :REFIID, :ptr
	STDMETHOD	CoerceToCanonicalValue, :ptr
	STDMETHOD	FormatForDisplay, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
	STDMETHOD	IsValueCanonical, :REFPROPVARIANT
	STDMETHOD	GetSortByAlias, :REFIID, :ptr
	STDMETHOD	GetAdditionalSortByAliases, :REFIID, :ptr
IPropertyDescriptionAliasInfoVtbl ends
IPropertyDescriptionAliasInfo struct
	lpVtbl		PVOID ?
IPropertyDescriptionAliasInfo ends

endif

ifndef __IPropertyDescriptionSearchInfo_INTERFACE_DEFINED__
__IPropertyDescriptionSearchInfo_INTERFACE_DEFINED__ equ 1

PROPDESC_SEARCHINFO_FLAGS typedef SDWORD
PDSIF_DEFAULT		equ 0
PDSIF_ININVERTEDINDEX	equ 0x1
PDSIF_ISCOLUMN		equ 0x2
PDSIF_ISCOLUMNSPARSE	equ 0x4
PDSIF_ALWAYSINCLUDE	equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(PROPDESC_SEARCHINFO_FLAGS)
PROPDESC_COLUMNINDEX_TYPE typedef SDWORD
PDCIT_NONE		equ 0
PDCIT_ONDISK		equ 1
PDCIT_INMEMORY		equ 2
PDCIT_ONDEMAND		equ 3
PDCIT_ONDISKALL		equ 4
PDCIT_ONDISKVECTOR	equ 5

externdef		IID_IPropertyDescriptionSearchInfo:IID
IPropertyDescriptionSearchInfoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPropertyKey, :ptr
	STDMETHOD	GetCanonicalName, :ptr
	STDMETHOD	GetPropertyType, :ptr
	STDMETHOD	GetDisplayName, :ptr
	STDMETHOD	GetEditInvitation, :ptr
	STDMETHOD	GetTypeFlags, :PROPDESC_TYPE_FLAGS, :ptr
	STDMETHOD	GetViewFlags, :ptr
	STDMETHOD	GetDefaultColumnWidth, :ptr
	STDMETHOD	GetDisplayType, :ptr
	STDMETHOD	GetColumnState, :ptr
	STDMETHOD	GetGroupingRange, :ptr
	STDMETHOD	GetRelativeDescriptionType, :ptr
	STDMETHOD	GetRelativeDescription, :REFPROPVARIANT, :REFPROPVARIANT, :ptr, :ptr
	STDMETHOD	GetSortDescription, :ptr
	STDMETHOD	GetSortDescriptionLabel, :BOOL, :ptr
	STDMETHOD	GetAggregationType, :ptr
	STDMETHOD	GetConditionType, :ptr, :ptr
	STDMETHOD	GetEnumTypeList, :REFIID, :ptr
	STDMETHOD	CoerceToCanonicalValue, :ptr
	STDMETHOD	FormatForDisplay, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
	STDMETHOD	IsValueCanonical, :REFPROPVARIANT
	STDMETHOD	GetSearchInfoFlags, :ptr
	STDMETHOD	GetColumnIndexType, :ptr
	STDMETHOD	GetProjectionString, :ptr
	STDMETHOD	GetMaxSize, :ptr
IPropertyDescriptionSearchInfoVtbl ends
IPropertyDescriptionSearchInfo struct
	lpVtbl		PVOID ?
IPropertyDescriptionSearchInfo ends

endif

ifndef __IPropertyDescriptionRelatedPropertyInfo_INTERFACE_DEFINED__
__IPropertyDescriptionRelatedPropertyInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyDescriptionRelatedPropertyInfo:IID
IPropertyDescriptionRelatedPropertyInfoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPropertyKey, :ptr
	STDMETHOD	GetCanonicalName, :ptr
	STDMETHOD	GetPropertyType, :ptr
	STDMETHOD	GetDisplayName, :ptr
	STDMETHOD	GetEditInvitation, :ptr
	STDMETHOD	GetTypeFlags, :PROPDESC_TYPE_FLAGS, :ptr
	STDMETHOD	GetViewFlags, :ptr
	STDMETHOD	GetDefaultColumnWidth, :ptr
	STDMETHOD	GetDisplayType, :ptr
	STDMETHOD	GetColumnState, :ptr
	STDMETHOD	GetGroupingRange, :ptr
	STDMETHOD	GetRelativeDescriptionType, :ptr
	STDMETHOD	GetRelativeDescription, :REFPROPVARIANT, :REFPROPVARIANT, :ptr, :ptr
	STDMETHOD	GetSortDescription, :ptr
	STDMETHOD	GetSortDescriptionLabel, :BOOL, :ptr
	STDMETHOD	GetAggregationType, :ptr
	STDMETHOD	GetConditionType, :ptr, :ptr
	STDMETHOD	GetEnumTypeList, :REFIID, :ptr
	STDMETHOD	CoerceToCanonicalValue, :ptr
	STDMETHOD	FormatForDisplay, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
	STDMETHOD	IsValueCanonical, :REFPROPVARIANT
	STDMETHOD	GetRelatedProperty, :LPCWSTR, :REFIID, :ptr
IPropertyDescriptionRelatedPropertyInfoVtbl ends
IPropertyDescriptionRelatedPropertyInfo struct
	lpVtbl		PVOID ?
IPropertyDescriptionRelatedPropertyInfo ends

endif


PROPDESC_ENUMFILTER	typedef SDWORD
PDEF_ALL		equ 0
PDEF_SYSTEM		equ 1
PDEF_NONSYSTEM		equ 2
PDEF_VIEWABLE		equ 3
PDEF_QUERYABLE		equ 4
PDEF_INFULLTEXTQUERY	equ 5
PDEF_COLUMN		equ 6

externdef		__MIDL_itf_propsys_0000_0017_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propsys_0000_0017_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPropertySystem_INTERFACE_DEFINED__
__IPropertySystem_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertySystem:IID
IPropertySystemVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPropertyDescription, :REFPROPERTYKEY, :REFIID, :ptr
	STDMETHOD	GetPropertyDescriptionByName, :LPCWSTR, :REFIID, :ptr
	STDMETHOD	GetPropertyDescriptionListFromString, :LPCWSTR, :REFIID, :ptr
	STDMETHOD	EnumeratePropertyDescriptions, :PROPDESC_ENUMFILTER, :REFIID, :ptr
	STDMETHOD	FormatForDisplay, :REFPROPERTYKEY, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :LPWSTR, :DWORD
	STDMETHOD	FormatForDisplayAlloc, :REFPROPERTYKEY, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
	STDMETHOD	RegisterPropertySchema, :LPCWSTR
	STDMETHOD	UnregisterPropertySchema, :LPCWSTR
	STDMETHOD	RefreshPropertySchema
IPropertySystemVtbl ends
IPropertySystem struct
	lpVtbl		PVOID ?
IPropertySystem ends

endif

ifndef __IPropertyDescriptionList_INTERFACE_DEFINED__
__IPropertyDescriptionList_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyDescriptionList:IID
IPropertyDescriptionListVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCount, :ptr
	STDMETHOD	GetAt, :UINT, :REFIID, :ptr
IPropertyDescriptionListVtbl ends
IPropertyDescriptionList struct
	lpVtbl		PVOID ?
IPropertyDescriptionList ends

endif

ifndef __IPropertyStoreFactory_INTERFACE_DEFINED__
__IPropertyStoreFactory_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyStoreFactory:IID
IPropertyStoreFactoryVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPropertyStore, :GETPROPERTYSTOREFLAGS, :ptr, :REFIID, :ptr
	STDMETHOD	GetPropertyStoreForKeys, :UINT, :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
IPropertyStoreFactoryVtbl ends
IPropertyStoreFactory struct
	lpVtbl		PVOID ?
IPropertyStoreFactory ends

endif

ifndef __IDelayedPropertyStoreFactory_INTERFACE_DEFINED__
__IDelayedPropertyStoreFactory_INTERFACE_DEFINED__ equ 1

externdef		IID_IDelayedPropertyStoreFactory:IID
IDelayedPropertyStoreFactoryVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPropertyStore, :GETPROPERTYSTOREFLAGS, :ptr, :REFIID, :ptr
	STDMETHOD	GetPropertyStoreForKeys, :UINT, :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
	STDMETHOD	GetDelayedPropertyStore, :GETPROPERTYSTOREFLAGS, :DWORD, :REFIID, :ptr
IDelayedPropertyStoreFactoryVtbl ends
IDelayedPropertyStoreFactory struct
	lpVtbl		PVOID ?
IDelayedPropertyStoreFactory ends

endif

PERSIST_SPROPSTORE_FLAGS typedef SDWORD
FPSPS_DEFAULT		equ 0
FPSPS_READONLY		equ 0x1
PERSIST_SPROPSTORE_FLAGS typedef SINT

SERIALIZEDPROPSTORAGE	typedef SERIALIZEDPROPSTORAGE
PUSERIALIZEDPROPSTORAGE typedef ptr SERIALIZEDPROPSTORAGE
PCUSERIALIZEDPROPSTORAGE typedef ptr SERIALIZEDPROPSTORAGE

externdef		__MIDL_itf_propsys_0000_0021_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propsys_0000_0021_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPersistSerializedPropStorage_INTERFACE_DEFINED__
__IPersistSerializedPropStorage_INTERFACE_DEFINED__ equ 1

externdef		IID_IPersistSerializedPropStorage:IID
IPersistSerializedPropStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetFlags, :PERSIST_SPROPSTORE_FLAGS
	STDMETHOD	SetPropertyStorage, :PCUSERIALIZEDPROPSTORAGE, :DWORD
	STDMETHOD	GetPropertyStorage, :ptr, :ptr
IPersistSerializedPropStorageVtbl ends
IPersistSerializedPropStorage struct
	lpVtbl		PVOID ?
IPersistSerializedPropStorage ends

endif

ifndef __IPersistSerializedPropStorage2_INTERFACE_DEFINED__
__IPersistSerializedPropStorage2_INTERFACE_DEFINED__ equ 1

externdef		IID_IPersistSerializedPropStorage2:IID
IPersistSerializedPropStorage2Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetFlags, :PERSIST_SPROPSTORE_FLAGS
	STDMETHOD	SetPropertyStorage, :PCUSERIALIZEDPROPSTORAGE, :DWORD
	STDMETHOD	GetPropertyStorage, :ptr, :ptr
	STDMETHOD	GetPropertyStorageSize, :ptr
	STDMETHOD	GetPropertyStorageBuffer, :ptr, :DWORD, :ptr
IPersistSerializedPropStorage2Vtbl ends
IPersistSerializedPropStorage2 struct
	lpVtbl		PVOID ?
IPersistSerializedPropStorage2 ends

endif

ifndef __IPropertySystemChangeNotify_INTERFACE_DEFINED__
__IPropertySystemChangeNotify_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertySystemChangeNotify:IID
IPropertySystemChangeNotifyVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SchemaRefreshed
IPropertySystemChangeNotifyVtbl ends
IPropertySystemChangeNotify struct
	lpVtbl		PVOID ?
IPropertySystemChangeNotify ends

endif

ifndef __ICreateObject_INTERFACE_DEFINED__
__ICreateObject_INTERFACE_DEFINED__ equ 1

externdef		IID_ICreateObject:IID
ICreateObjectVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CreateObject, :REFCLSID, :ptr, :REFIID, :ptr
ICreateObjectVtbl ends
ICreateObject struct
	lpVtbl		PVOID ?
ICreateObject ends

endif

;PSSTDAPI
PSFormatForDisplay proto WINAPI \
	       propkey: REFPROPVARIANT,
	       propvar: REFPROPVARIANT,
	      pdfFlags: PROPDESC_FORMAT_FLAGS,
	      pwszText: LPWSTR,
	       cchText: DWORD

;PSSTDAPI
PSFormatForDisplayAlloc proto WINAPI \
		   key: REFPROPERTYKEY,
	       propvar: REFPROPVARIANT,
		  pdff: PROPDESC_FORMAT_FLAGS,
	   ppszDisplay: ptr PWSTR


;PSSTDAPI
PSFormatPropertyValue proto WINAPI \
		   pps: ptr IPropertyStore,
		   ppd: ptr IPropertyDescription,
		  pdff: PROPDESC_FORMAT_FLAGS,
	   ppszDisplay: ptr LPWSTR


;PSSTDAPI
PSGetImageReferenceForValue proto WINAPI \
	       propkey: REFPROPERTYKEY,
	       propvar: REFPROPVARIANT,
	  ppszImageRes: ptr PWSTR



PKEY_PIDSTR_MAX		equ 10
GUIDSTRING_MAX		equ (1 + 8 + 1 + 4 + 1 + 4 + 1 + 4 + 1 + 12 + 1 + 1)
PKEYSTR_MAX		equ (GUIDSTRING_MAX + 1 + PKEY_PIDSTR_MAX)

;PSSTDAPI
PSStringFromPropertyKey proto WINAPI \
		  pkey: REFPROPERTYKEY,
		   psz: LPWSTR,
		   cch: UINT

;PSSTDAPI
PSPropertyKeyFromString proto WINAPI \
	     pszString: LPCWSTR,
		  pkey: ptr PROPERTYKEY

;PSSTDAPI
PSCreateMemoryPropertyStore proto WINAPI \
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSCreateDelayedMultiplexPropertyStore proto WINAPI \
		 flags: GETPROPERTYSTOREFLAGS,
		 pdpsf: ptr IDelayedPropertyStoreFactory,
	    rgStoreIds: ptr DWORD,
	       cStores: DWORD,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSCreateMultiplexPropertyStore proto WINAPI \
	 prgpunkStores: ptr IUnknown,
	       cStores: DWORD,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSCreatePropertyChangeArray proto WINAPI \
	     rgpropkey: ptr PROPERTYKEY,
	       rgflags: ptr PKA_FLAGS,
	     rgpropvar: ptr PROPVARIANT,
	      cChanges: UINT,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSCreateSimplePropertyChange proto WINAPI \
		 flags: PKA_FLAGS,
		   key: REFPROPERTYKEY,
	       propvar: REFPROPVARIANT,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSGetPropertyDescription proto WINAPI \
	       propkey: REFPROPERTYKEY,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSGetPropertyDescriptionByName proto WINAPI \
      pszCanonicalName: LPCWSTR,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSLookupPropertyHandlerCLSID proto WINAPI \
	   pszFilePath: PCWSTR,
		pclsid: ptr CLSID

;PSSTDAPI
PSGetItemPropertyHandler proto WINAPI \
	      punkItem: ptr IUnknown,
	    fReadWrite: BOOL,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSGetItemPropertyHandlerWithCreateObject proto WINAPI \
	      punkItem: ptr IUnknown,
	    fReadWrite: BOOL,
      punkCreateObject: ptr IUnknown,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSGetPropertyValue proto WINAPI \
		   pps: ptr IPropertyStore,
		   ppd: ptr IPropertyDescription,
	      ppropvar: ptr PROPVARIANT

;PSSTDAPI
PSSetPropertyValue proto WINAPI \
		   pps: ptr IPropertyStore,
		   ppd: ptr IPropertyDescription,
	       propvar: REFPROPVARIANT

;PSSTDAPI
PSRegisterPropertySchema proto WINAPI \
	       pszPath: PCWSTR

;PSSTDAPI
PSUnregisterPropertySchema proto WINAPI \
	       pszPath: PCWSTR

;PSSTDAPI
PSRefreshPropertySchema proto WINAPI

;PSSTDAPI
PSEnumeratePropertyDescriptions proto WINAPI \
	      filterOn: PROPDESC_ENUMFILTER,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSGetPropertyKeyFromName proto WINAPI \
	       pszName: PCWSTR,
	      ppropkey: ptr PROPERTYKEY

;PSSTDAPI
PSGetNameFromPropertyKey proto WINAPI \
	       propkey: REFPROPERTYKEY,
     ppszCanonicalName: ptr PWSTR

;PSSTDAPI
PSCoerceToCanonicalValue proto WINAPI \
		   key: REFPROPERTYKEY,
	      ppropvar: ptr PROPVARIANT

;PSSTDAPI
PSGetPropertyDescriptionListFromString proto WINAPI \
	   pszPropList: LPCWSTR,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSCreatePropertyStoreFromPropertySetStorage proto WINAPI \
		  ppss: ptr IPropertySetStorage,
	       grfMode: DWORD,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSCreatePropertyStoreFromObject proto WINAPI \
		  punk: ptr IUnknown,
	       grfMode: DWORD,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSCreateAdapterFromPropertyStore proto WINAPI \
		   pps: ptr IPropertyStore,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSGetPropertySystem proto WINAPI \
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSGetPropertyFromPropertyStorage proto WINAPI \
		  psps: PCUSERIALIZEDPROPSTORAGE,
		    cb: DWORD,
		 rpkey: REFPROPERTYKEY,
	      ppropvar: LPPROPVARIANT

;PSSTDAPI
PSGetNamedPropertyFromPropertyStorage proto WINAPI \
		  psps: PCUSERIALIZEDPROPSTORAGE,
		    cb: DWORD,
	       pszName: LPCWSTR,
	      ppropvar: LPPROPVARIANT

;PSSTDAPI
PSPropertyBag_ReadType proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		   var: ptr VARIANT,
		 _type: VARTYPE

;PSSTDAPI
PSPropertyBag_ReadStr proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: LPWSTR

;PSSTDAPI
PSPropertyBag_ReadStrAlloc proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr PWSTR

;PSSTDAPI
PSPropertyBag_ReadBSTR proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr BSTR

;PSSTDAPI
PSPropertyBag_WriteStr proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: LPCWSTR

;PSSTDAPI
PSPropertyBag_WriteBSTR proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: BSTR

;PSSTDAPI
PSPropertyBag_ReadInt proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr SINT

;PSSTDAPI
PSPropertyBag_WriteInt proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: SINT

;PSSTDAPI
PSPropertyBag_ReadSHORT proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr SWORD

;PSSTDAPI
PSPropertyBag_WriteSHORT proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: SWORD

;PSSTDAPI
PSPropertyBag_ReadLONG proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr LONG

;PSSTDAPI
PSPropertyBag_WriteLONG proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: LONG

;PSSTDAPI
PSPropertyBag_ReadDWORD proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr DWORD

;PSSTDAPI
PSPropertyBag_WriteDWORD proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: DWORD

;PSSTDAPI
PSPropertyBag_ReadBOOL proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr BOOL

;PSSTDAPI
PSPropertyBag_WriteBOOL proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: BOOL

;PSSTDAPI
PSPropertyBag_ReadPOINTL proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr POINTL

;PSSTDAPI
PSPropertyBag_WritePOINTL proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr POINTL

;PSSTDAPI
PSPropertyBag_ReadPOINTS proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr POINTS

;PSSTDAPI
PSPropertyBag_WritePOINTS proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr POINTL

;PSSTDAPI
PSPropertyBag_ReadRECTL proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr RECTL

;PSSTDAPI
PSPropertyBag_WriteRECTL proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr POINTL

;PSSTDAPI
PSPropertyBag_ReadStream proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr IStream

;PSSTDAPI
PSPropertyBag_WriteStream proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr IStream

;PSSTDAPI
PSPropertyBag_Delete proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR

;PSSTDAPI
PSPropertyBag_ReadULONGLONG proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr ULONGLONG

;PSSTDAPI
PSPropertyBag_WriteULONGLONG proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ULONGLONG

;PSSTDAPI
PSPropertyBag_ReadUnknown proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		  riid: REFIID,
		   ppv: ptr

;PSSTDAPI
PSPropertyBag_WriteUnknown proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		  punk: ptr IUnknown

;PSSTDAPI
PSPropertyBag_ReadGUID proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr GUID

;PSSTDAPI
PSPropertyBag_WriteGUID proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr GUID

;PSSTDAPI
PSPropertyBag_ReadPropertyKey proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: ptr PROPERTYKEY

;PSSTDAPI
PSPropertyBag_WritePropertyKey proto WINAPI \
	       propBag: ptr IPropertyBag,
	      propName: LPCWSTR,
		 value: REFPROPERTYKEY


externdef		__MIDL_itf_propsys_0000_0025_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propsys_0000_0025_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __PropSysObjects_LIBRARY_DEFINED__
__PropSysObjects_LIBRARY_DEFINED__ equ 1
externdef		LIBID_PropSysObjects:IID
externdef		CLSID_InMemoryPropertyStore:CLSID
externdef		CLSID_PropertySystem:CLSID
endif

;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
LPSAFEARRAY_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;void
LPSAFEARRAY_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY

;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
LPSAFEARRAY_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;void
LPSAFEARRAY_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY

;HRESULT
IInitializeWithStream_Initialize_Proxy proto WINAPI \
		 _This: ptr IInitializeWithStream,
	       pstream: ptr IStream,
	       grfMode: DWORD

;HRESULT
IInitializeWithStream_Initialize_Stub proto WINAPI \
		 _This: ptr IInitializeWithStream,
	       pstream: ptr IStream,
	       grfMode: DWORD

;HRESULT
IPropertyDescription_CoerceToCanonicalValue_Proxy proto WINAPI \
		 _This: ptr IPropertyDescription,
	      ppropvar: ptr PROPVARIANT

;HRESULT
IPropertyDescription_CoerceToCanonicalValue_Stub proto WINAPI \
		 _This: ptr IPropertyDescription,
	       propvar: REFPROPVARIANT,
	      ppropvar: ptr PROPVARIANT

.list
endif ; __propsys_h__

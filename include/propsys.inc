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

ifndef __propsys_h__
define __propsys_h__

include objidl.inc
include oleidl.inc
include ocidl.inc
include shtypes.inc
include StructuredQueryCondition.inc

include winapifamily.inc

ifndef REFPROPERTYKEY
REFPROPERTYKEY typedef ptr PROPERTYKEY
endif

include propkeydef.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IInitializeWithFile_INTERFACE_DEFINED__
define __IInitializeWithFile_INTERFACE_DEFINED__

DEFINE_IIDX(IInitializeWithFile, "b7d14566-0509-4cce-a71f-0a554233bd9b")

.comdef IInitializeWithFile : public IUnknown
    Initialize		proc :LPCWSTR, :DWORD
   .ends

endif

ifndef __IInitializeWithStream_INTERFACE_DEFINED__
define __IInitializeWithStream_INTERFACE_DEFINED__

DEFINE_IIDX(IInitializeWithStream, "b824b49d-22ac-4161-ac8a-9916e8fa3f7f")

.comdef IInitializeWithStream : public IUnknown
    Initialize		proc :ptr, :DWORD
   .ends

IInitializeWithStream_RemoteInitialize_Proxy proto WINAPI :ptr, :ptr, :DWORD
IInitializeWithStream_RemoteInitialize_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_GAMES)

ifndef __IPropertyStore_INTERFACE_DEFINED__
define __IPropertyStore_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyStore, "886d8eeb-8cf2-4446-8d02-cdba1dbdcf99")

.comdef IPropertyStore : public IUnknown
    GetCount		proc :ptr
    GetAt		proc :DWORD, :ptr
    GetValue		proc :REFPROPERTYKEY, :ptr
    SetValue		proc :REFPROPERTYKEY, :REFPROPVARIANT
    Commit		proc
   .ends

endif

LPPROPERTYSTORE		typedef ptr IPropertyStore

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
PropVariantToWinRTPropertyValue proto WINAPI :REFPROPVARIANT, :REFIID, :ptr ptr
WinRTPropertyValueToPropVariant proto WINAPI :ptr, :ptr
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __INamedPropertyStore_INTERFACE_DEFINED__
define __INamedPropertyStore_INTERFACE_DEFINED__

DEFINE_IIDX(INamedPropertyStore, "71604b0f-97b0-4764-8577-2f13e98a1422")

.comdef INamedPropertyStore : public IUnknown
    GetNamedValue	proc :LPCWSTR, :ptr
    SetNamedValue	proc :LPCWSTR, :REFPROPVARIANT
    GetNameCount	proc :ptr
    GetNameAt		proc :DWORD, :ptr
   .ends

endif

.enum GETPROPERTYSTOREFLAGS {
	GPS_DEFAULT	= 0,
	GPS_HANDLERPROPERTIESONLY	= 0x1,
	GPS_READWRITE	= 0x2,
	GPS_TEMPORARY	= 0x4,
	GPS_FASTPROPERTIESONLY	= 0x8,
	GPS_OPENSLOWITEM	= 0x10,
	GPS_DELAYCREATION	= 0x20,
	GPS_BESTEFFORT	= 0x40,
	GPS_NO_OPLOCK	= 0x80,
	GPS_PREFERQUERYPROPERTIES	= 0x100,
	GPS_EXTRINSICPROPERTIES = 0x200,
	GPS_EXTRINSICPROPERTIESONLY	= 0x400,
	GPS_VOLATILEPROPERTIES	= 0x800,
	GPS_VOLATILEPROPERTIESONLY	= 0x1000,
	GPS_MASK_VALID	= 0x1fff
    }

ifndef __IObjectWithPropertyKey_INTERFACE_DEFINED__
define __IObjectWithPropertyKey_INTERFACE_DEFINED__

DEFINE_IIDX(IObjectWithPropertyKey, "fc0ca0a7-c316-4fd2-9031-3e628e6d4f23")

.comdef IObjectWithPropertyKey : public IUnknown
    SetPropertyKey	proc :REFPROPERTYKEY
    GetPropertyKey	proc :ptr
   .ends

endif

.enum PKA_FLAGS {
	PKA_SET = 0,
	PKA_APPEND	= ( PKA_SET + 1 ) ,
	PKA_DELETE	= ( PKA_APPEND + 1 )
    }

ifndef __IPropertyChange_INTERFACE_DEFINED__
define __IPropertyChange_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyChange, "f917bc8a-1bba-4478-a245-1bde03eb9431")

.comdef IPropertyChange : public IObjectWithPropertyKey
    ApplyToPropVariant	proc :REFPROPVARIANT, :ptr
   .ends

endif

ifndef __IPropertyChangeArray_INTERFACE_DEFINED__
define __IPropertyChangeArray_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyChangeArray, "380f5cad-1b5e-42f2-805d-637fd392d31e")

.comdef IPropertyChangeArray : public IUnknown
    GetCount		proc :ptr
    GetAt		proc :UINT, :REFIID, :ptr
    InsertAt		proc :UINT, :ptr
    Append		proc :ptr
    AppendOrReplace	proc :ptr
    RemoveAt		proc :UINT
    IsKeyInArray	proc :REFPROPERTYKEY
   .ends

endif

ifndef __IPropertyStoreCapabilities_INTERFACE_DEFINED__
define __IPropertyStoreCapabilities_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyStoreCapabilities, "c8e2d566-186e-4d49-bf41-6909ead56acc")

.comdef IPropertyStoreCapabilities : public IUnknown
    IsPropertyWritable	proc :REFPROPERTYKEY
   .ends

endif

ifndef __IPropertyStoreCache_INTERFACE_DEFINED__
define __IPropertyStoreCache_INTERFACE_DEFINED__

.enum PSC_STATE {
	PSC_NORMAL	= 0,
	PSC_NOTINSOURCE = 1,
	PSC_DIRTY	= 2,
	PSC_READONLY	= 3
    }

DEFINE_IIDX(IPropertyStoreCache, "3017056d-9a91-4e90-937d-746c72abbf4f")

.comdef IPropertyStoreCache : public IPropertyStore
    GetState		proc :REFPROPERTYKEY, :ptr
    GetValueAndState	proc :REFPROPERTYKEY, :ptr, :ptr
    SetState		proc :REFPROPERTYKEY, :PSC_STATE
    SetValueAndState	proc :REFPROPERTYKEY, :ptr, :PSC_STATE
   .ends

endif

ifndef __IPropertyEnumType_INTERFACE_DEFINED__
define __IPropertyEnumType_INTERFACE_DEFINED__

.enum PROPENUMTYPE {
	PET_DISCRETEVALUE	= 0,
	PET_RANGEDVALUE = 1,
	PET_DEFAULTVALUE	= 2,
	PET_ENDRANGE	= 3
    }

DEFINE_IIDX(IPropertyEnumType, "11e1fbf9-2d56-4a6b-8db3-7cd193a471f2")

.comdef IPropertyEnumType : public IUnknown
    GetEnumType		proc :ptr
    GetValue		proc :ptr
    GetRangeMinValue	proc :ptr
    GetRangeSetValue	proc :ptr
    GetDisplayText	proc :ptr
   .ends

endif

ifndef __IPropertyEnumType2_INTERFACE_DEFINED__
define __IPropertyEnumType2_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyEnumType2, "9b6e051c-5ddd-4321-9070-fe2acb55e794")

.comdef IPropertyEnumType2 : public IPropertyEnumType
    GetImageReference	proc :ptr
   .ends

endif

ifndef __IPropertyEnumTypeList_INTERFACE_DEFINED__
define __IPropertyEnumTypeList_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyEnumTypeList, "a99400f4-3d84-4557-94ba-1242fb2cc9a6")

.comdef IPropertyEnumTypeList : public IUnknown
    GetCount		proc :ptr
    GetAt		proc :UINT, :REFIID, :ptr
    GetConditionAt	proc :UINT, :REFIID, :ptr
    FindMatchingIndex	proc :REFPROPVARIANT, :ptr
   .ends

endif

ifndef __IPropertyDescription_INTERFACE_DEFINED__
define __IPropertyDescription_INTERFACE_DEFINED__

.enum PROPDESC_TYPE_FLAGS {
	PDTF_DEFAULT	= 0,
	PDTF_MULTIPLEVALUES	= 0x1,
	PDTF_ISINNATE	= 0x2,
	PDTF_ISGROUP	= 0x4,
	PDTF_CANGROUPBY = 0x8,
	PDTF_CANSTACKBY = 0x10,
	PDTF_ISTREEPROPERTY	= 0x20,
	PDTF_INCLUDEINFULLTEXTQUERY	= 0x40,
	PDTF_ISVIEWABLE = 0x80,
	PDTF_ISQUERYABLE	= 0x100,
	PDTF_CANBEPURGED	= 0x200,
	PDTF_SEARCHRAWVALUE	= 0x400,
	PDTF_DONTCOERCEEMPTYSTRINGS	= 0x800,
	PDTF_ALWAYSINSUPPLEMENTALSTORE	= 0x1000,
	PDTF_ISSYSTEMPROPERTY	= 0x80000000,
	PDTF_MASK_ALL	= 0x80001fff
    }

.enum PROPDESC_VIEW_FLAGS {
	PDVF_DEFAULT	= 0,
	PDVF_CENTERALIGN	= 0x1,
	PDVF_RIGHTALIGN = 0x2,
	PDVF_BEGINNEWGROUP	= 0x4,
	PDVF_FILLAREA	= 0x8,
	PDVF_SORTDESCENDING	= 0x10,
	PDVF_SHOWONLYIFPRESENT	= 0x20,
	PDVF_SHOWBYDEFAULT	= 0x40,
	PDVF_SHOWINPRIMARYLIST	= 0x80,
	PDVF_SHOWINSECONDARYLIST	= 0x100,
	PDVF_HIDELABEL	= 0x200,
	PDVF_HIDDEN	= 0x800,
	PDVF_CANWRAP	= 0x1000,
	PDVF_MASK_ALL	= 0x1bff
    }

.enum PROPDESC_DISPLAYTYPE {
	PDDT_STRING	= 0,
	PDDT_NUMBER	= 1,
	PDDT_BOOLEAN	= 2,
	PDDT_DATETIME	= 3,
	PDDT_ENUMERATED = 4
    }

.enum PROPDESC_GROUPING_RANGE {
	PDGR_DISCRETE	= 0,
	PDGR_ALPHANUMERIC	= 1,
	PDGR_SIZE	= 2,
	PDGR_DYNAMIC	= 3,
	PDGR_DATE	= 4,
	PDGR_PERCENT	= 5,
	PDGR_ENUMERATED = 6
    }

.enum PROPDESC_FORMAT_FLAGS {
	PDFF_DEFAULT	= 0,
	PDFF_PREFIXNAME = 0x1,
	PDFF_FILENAME	= 0x2,
	PDFF_ALWAYSKB	= 0x4,
	PDFF_RESERVED_RIGHTTOLEFT	= 0x8,
	PDFF_SHORTTIME	= 0x10,
	PDFF_LONGTIME	= 0x20,
	PDFF_HIDETIME	= 0x40,
	PDFF_SHORTDATE	= 0x80,
	PDFF_LONGDATE	= 0x100,
	PDFF_HIDEDATE	= 0x200,
	PDFF_RELATIVEDATE	= 0x400,
	PDFF_USEEDITINVITATION	= 0x800,
	PDFF_READONLY	= 0x1000,
	PDFF_NOAUTOREADINGORDER = 0x2000
    }

define PDFF_PREFERFRIENDLY    static_cast lt PROPDESC_FORMAT_FLAGS gt (0x10000000)
.enum PROPDESC_SORTDESCRIPTION {
	PDSD_GENERAL	= 0,
	PDSD_A_Z	= 1,
	PDSD_LOWEST_HIGHEST	= 2,
	PDSD_SMALLEST_BIGGEST	= 3,
	PDSD_OLDEST_NEWEST	= 4
    }

.enum PROPDESC_RELATIVEDESCRIPTION_TYPE {
	PDRDT_GENERAL	= 0,
	PDRDT_DATE	= 1,
	PDRDT_SIZE	= 2,
	PDRDT_COUNT	= 3,
	PDRDT_REVISION	= 4,
	PDRDT_LENGTH	= 5,
	PDRDT_DURATION	= 6,
	PDRDT_SPEED	= 7,
	PDRDT_RATE	= 8,
	PDRDT_RATING	= 9,
	PDRDT_PRIORITY	= 10
    }

.enum PROPDESC_AGGREGATION_TYPE {
	PDAT_DEFAULT	= 0,
	PDAT_FIRST	= 1,
	PDAT_SUM	= 2,
	PDAT_AVERAGE	= 3,
	PDAT_DATERANGE	= 4,
	PDAT_UNION	= 5,
	PDAT_MAX	= 6,
	PDAT_MIN	= 7
    }

.enum PROPDESC_CONDITION_TYPE {
	PDCOT_NONE	= 0,
	PDCOT_STRING	= 1,
	PDCOT_SIZE	= 2,
	PDCOT_DATETIME	= 3,
	PDCOT_BOOLEAN	= 4,
	PDCOT_NUMBER	= 5
    }

DEFINE_IIDX(IPropertyDescription, "6f79d558-3e96-4549-a1d1-7d75d2288814")

.comdef IPropertyDescription : public IUnknown
    GetPropertyKey	proc :ptr
    GetCanonicalName	proc :ptr
    GetPropertyType	proc :ptr
    GetDisplayName	proc :ptr
    GetEditInvitation	proc :ptr
    GetTypeFlags	proc :PROPDESC_TYPE_FLAGS, :ptr
    GetViewFlags	proc :ptr
    GetDefaultColumnWidth proc :ptr
    GetDisplayType	proc :ptr
    GetColumnState	proc :ptr
    GetGroupingRange	proc :ptr
    GetRelativeDescriptionType proc :ptr
    GetRelativeDescription proc :REFPROPVARIANT, :REFPROPVARIANT, :ptr, :ptr
    GetSortDescription	proc :ptr
    GetSortDescriptionLabel proc :BOOL, :ptr
    GetAggregationType	proc :ptr
    GetConditionType	proc :ptr, :ptr
    GetEnumTypeList	proc :REFIID, :ptr
    CoerceToCanonicalValue proc :ptr
    FormatForDisplay	proc :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
    IsValueCanonical	proc :REFPROPVARIANT
   .ends

IPropertyDescription_RemoteCoerceToCanonicalValue_Proxy proto WINAPI :ptr, :REFPROPVARIANT, :ptr

IPropertyDescription_RemoteCoerceToCanonicalValue_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IPropertyDescription2_INTERFACE_DEFINED__
define __IPropertyDescription2_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyDescription2, "57d2eded-5062-400e-b107-5dae79fe57a6")

.comdef IPropertyDescription2 : public IPropertyDescription
    GetImageReferenceForValue proc :REFPROPVARIANT, :ptr
   .ends

endif

ifndef __IPropertyDescriptionAliasInfo_INTERFACE_DEFINED__
define __IPropertyDescriptionAliasInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyDescriptionAliasInfo, "f67104fc-2af9-46fd-b32d-243c1404f3d1")

.comdef IPropertyDescriptionAliasInfo : public IPropertyDescription
    GetSortByAlias	proc :REFIID, :ptr
    GetAdditionalSortByAliases proc :REFIID, :ptr
   .ends

endif

ifndef __IPropertyDescriptionSearchInfo_INTERFACE_DEFINED__
define __IPropertyDescriptionSearchInfo_INTERFACE_DEFINED__

.enum PROPDESC_SEARCHINFO_FLAGS {
	PDSIF_DEFAULT	= 0,
	PDSIF_ININVERTEDINDEX	= 0x1,
	PDSIF_ISCOLUMN	= 0x2,
	PDSIF_ISCOLUMNSPARSE	= 0x4,
	PDSIF_ALWAYSINCLUDE	= 0x8,
	PDSIF_USEFORTYPEAHEAD	= 0x10
    }

.enum PROPDESC_COLUMNINDEX_TYPE {
	PDCIT_NONE	= 0,
	PDCIT_ONDISK	= 1,
	PDCIT_INMEMORY	= 2,
	PDCIT_ONDEMAND	= 3,
	PDCIT_ONDISKALL = 4,
	PDCIT_ONDISKVECTOR	= 5
    }

DEFINE_IIDX(IPropertyDescriptionSearchInfo, "078f91bd-29a2-440f-924e-46a291524520")

.comdef IPropertyDescriptionSearchInfo : public IPropertyDescription
    GetSearchInfoFlags	proc :ptr
    GetColumnIndexType	proc :ptr
    GetProjectionString proc :ptr
    GetMaxSize		proc :ptr
   .ends

endif

ifndef __IPropertyDescriptionRelatedPropertyInfo_INTERFACE_DEFINED__
define __IPropertyDescriptionRelatedPropertyInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyDescriptionRelatedPropertyInfo, "507393f4-2a3d-4a60-b59e-d9c75716c2dd")

.comdef IPropertyDescriptionRelatedPropertyInfo : public IPropertyDescription
    GetRelatedProperty	proc :LPCWSTR, :REFIID, :ptr
   .ends

endif

.enum PROPDESC_ENUMFILTER {
	PDEF_ALL	= 0,
	PDEF_SYSTEM	= 1,
	PDEF_NONSYSTEM	= 2,
	PDEF_VIEWABLE	= 3,
	PDEF_QUERYABLE	= 4,
	PDEF_INFULLTEXTQUERY	= 5,
	PDEF_COLUMN	= 6
    }

ifndef __IPropertySystem_INTERFACE_DEFINED__
define __IPropertySystem_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertySystem, "ca724e8a-c3e6-442b-88a4-6fb0db8035a3")

.comdef IPropertySystem : public IUnknown
    GetPropertyDescription proc :REFPROPERTYKEY, :REFIID, :ptr
    GetPropertyDescriptionByName proc :LPCWSTR, :REFIID, :ptr
    GetPropertyDescriptionListFromString proc :LPCWSTR, :REFIID, :ptr
    EnumeratePropertyDescriptions proc :PROPDESC_ENUMFILTER, :REFIID, :ptr
    FormatForDisplay	proc :REFPROPERTYKEY, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :LPWSTR, :DWORD
    FormatForDisplayAlloc proc :REFPROPERTYKEY, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
    RegisterPropertySchema proc :LPCWSTR
    UnregisterPropertySchema proc :LPCWSTR
    RefreshPropertySchema proc
   .ends

endif

ifndef __IPropertyDescriptionList_INTERFACE_DEFINED__
define __IPropertyDescriptionList_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyDescriptionList, "1f9fc1d0-c39b-4b26-817f-011967d3440e")

.comdef IPropertyDescriptionList : public IUnknown
    GetCount		proc :ptr
    GetAt		proc :UINT, :REFIID, :ptr
   .ends

endif

ifndef __IPropertyStoreFactory_INTERFACE_DEFINED__
define __IPropertyStoreFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyStoreFactory, "bc110b6d-57e8-4148-a9c6-91015ab2f3a5")

.comdef IPropertyStoreFactory : public IUnknown
    GetPropertyStore	proc :GETPROPERTYSTOREFLAGS, :ptr, :REFIID, :ptr
    GetPropertyStoreForKeys proc :ptr, :UINT, :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
   .ends

endif

ifndef __IDelayedPropertyStoreFactory_INTERFACE_DEFINED__
define __IDelayedPropertyStoreFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IDelayedPropertyStoreFactory, "40d4577f-e237-4bdb-bd69-58f089431b6a")

.comdef IDelayedPropertyStoreFactory : public IPropertyStoreFactory
    GetDelayedPropertyStore proc :GETPROPERTYSTOREFLAGS, :DWORD, :REFIID, :ptr
   .ends

endif

.enum PERSIST_SPROPSTORE_FLAGS {
	FPSPS_DEFAULT	= 0,
	FPSPS_READONLY	= 0x1,
	FPSPS_TREAT_NEW_VALUES_AS_DIRTY = 0x2
    }
PERSIST_SPROPSTORE_FLAGS typedef sdword

;SERIALIZEDPROPSTORAGE	 typedef SERIALIZEDPROPSTORAGE
PUSERIALIZEDPROPSTORAGE typedef ptr SERIALIZEDPROPSTORAGE
PCUSERIALIZEDPROPSTORAGE typedef ptr SERIALIZEDPROPSTORAGE

ifndef __IPersistSerializedPropStorage_INTERFACE_DEFINED__
define __IPersistSerializedPropStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistSerializedPropStorage, "e318ad57-0aa0-450f-aca5-6fab7103d917")

.comdef IPersistSerializedPropStorage : public IUnknown
    SetFlags		proc :PERSIST_SPROPSTORE_FLAGS
    SetPropertyStorage	proc :PCUSERIALIZEDPROPSTORAGE, :DWORD
    GetPropertyStorage	proc :ptr, :ptr
   .ends

endif

ifndef __IPersistSerializedPropStorage2_INTERFACE_DEFINED__
define __IPersistSerializedPropStorage2_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistSerializedPropStorage2, "77effa68-4f98-4366-ba72-573b3d880571")

.comdef IPersistSerializedPropStorage2 : public IPersistSerializedPropStorage
    GetPropertyStorageSize proc :ptr
    GetPropertyStorageBuffer proc :ptr, :DWORD, :ptr
   .ends

endif

ifndef __IPropertySystemChangeNotify_INTERFACE_DEFINED__
define __IPropertySystemChangeNotify_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertySystemChangeNotify, "fa955fd9-38be-4879-a6ce-824cf52d609f")

.comdef IPropertySystemChangeNotify : public IUnknown
    SchemaRefreshed	proc
   .ends

endif

ifndef __ICreateObject_INTERFACE_DEFINED__
define __ICreateObject_INTERFACE_DEFINED__

DEFINE_IIDX(ICreateObject, "75121952-e0d0-43e5-9380-1d80483acf72")

.comdef ICreateObject : public IUnknown
    CreateObject	proc :REFCLSID, :ptr, :REFIID, :ptr
   .ends

endif

PSFormatForDisplay proto WINAPI :REFPROPERTYKEY, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :LPWSTR, :DWORD
PSFormatForDisplayAlloc proto WINAPI :REFPROPERTYKEY, :REFPROPVARIANT, :PROPDESC_FORMAT_FLAGS, :ptr
PSFormatPropertyValue proto WINAPI :ptr, :ptr, :PROPDESC_FORMAT_FLAGS, :ptr
PSGetImageReferenceForValue proto WINAPI :REFPROPERTYKEY, :REFPROPVARIANT, :ptr

define PKEY_PIDSTR_MAX	   10
define GUIDSTRING_MAX	   (1 + 8 + 1 + 4 + 1 + 4 + 1 + 4 + 1 + 12 + 1 + 1)
define PKEYSTR_MAX	   (GUIDSTRING_MAX + 1 + PKEY_PIDSTR_MAX)

PSStringFromPropertyKey proto WINAPI :REFPROPERTYKEY, :LPWSTR, :UINT
PSPropertyKeyFromString proto WINAPI :LPCWSTR, :ptr
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
PSCreateMemoryPropertyStore proto WINAPI :REFIID, :ptr ptr
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

PSCreateDelayedMultiplexPropertyStore proto WINAPI :GETPROPERTYSTOREFLAGS, :ptr, :ptr, :DWORD, :REFIID, :ptr ptr
PSCreateMultiplexPropertyStore proto WINAPI :ptr ptr, :DWORD, :REFIID, :ptr ptr
PSCreatePropertyChangeArray proto WINAPI :ptr, :ptr, :ptr, :UINT, :REFIID, :ptr ptr
PSCreateSimplePropertyChange proto WINAPI :PKA_FLAGS, :REFPROPERTYKEY, :REFPROPVARIANT, :REFIID, :ptr ptr
PSGetPropertyDescription proto WINAPI :REFPROPERTYKEY, :REFIID, :ptr ptr
PSGetPropertyDescriptionByName proto WINAPI :LPCWSTR, :REFIID, :ptr ptr
PSLookupPropertyHandlerCLSID proto WINAPI :PCWSTR, :ptr
PSGetItemPropertyHandler proto WINAPI :ptr, :BOOL, :REFIID, :ptr ptr
PSGetItemPropertyHandlerWithCreateObject proto WINAPI :ptr, :BOOL, :ptr, :REFIID, :ptr ptr
PSGetPropertyValue proto WINAPI :ptr, :ptr, :ptr
PSSetPropertyValue proto WINAPI :ptr, :ptr, :REFPROPVARIANT
PSRegisterPropertySchema proto WINAPI :PCWSTR
PSUnregisterPropertySchema proto WINAPI :PCWSTR
PSRefreshPropertySchema proto WINAPI
PSEnumeratePropertyDescriptions proto WINAPI :PROPDESC_ENUMFILTER, :REFIID, :ptr ptr
PSGetPropertyKeyFromName proto WINAPI :PCWSTR, :ptr
PSGetNameFromPropertyKey proto WINAPI :REFPROPERTYKEY, :ptr
PSCoerceToCanonicalValue proto WINAPI :REFPROPERTYKEY, :ptr
PSGetPropertyDescriptionListFromString proto WINAPI :LPCWSTR, :REFIID, :ptr ptr
PSCreatePropertyStoreFromPropertySetStorage proto WINAPI :ptr, :DWORD, :REFIID, :ptr ptr
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
PSCreatePropertyStoreFromObject proto WINAPI :ptr, :DWORD, :REFIID, :ptr ptr
PSCreateAdapterFromPropertyStore proto WINAPI :ptr, :REFIID, :ptr ptr
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

PSGetPropertySystem proto WINAPI :REFIID, :ptr ptr
PSGetPropertyFromPropertyStorage proto WINAPI :PCUSERIALIZEDPROPSTORAGE, :DWORD, :REFPROPERTYKEY, :ptr
PSGetNamedPropertyFromPropertyStorage proto WINAPI :PCUSERIALIZEDPROPSTORAGE, :DWORD, :LPCWSTR, :ptr

PSPropertyBag_ReadType proto WINAPI :ptr, :LPCWSTR, :ptr, :VARTYPE
PSPropertyBag_ReadStr proto WINAPI :ptr, :LPCWSTR, :LPWSTR, :sdword
PSPropertyBag_ReadStrAlloc proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_ReadBSTR proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteStr proto WINAPI :ptr, :LPCWSTR, :LPCWSTR
PSPropertyBag_WriteBSTR proto WINAPI :ptr, :LPCWSTR, :BSTR
PSPropertyBag_ReadInt proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteInt proto WINAPI :ptr, :LPCWSTR, :sdword
PSPropertyBag_ReadSHORT proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteSHORT proto WINAPI :ptr, :LPCWSTR, :sword
PSPropertyBag_ReadLONG proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteLONG proto WINAPI :ptr, :LPCWSTR, :LONG
PSPropertyBag_ReadDWORD proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteDWORD proto WINAPI :ptr, :LPCWSTR, :DWORD
PSPropertyBag_ReadBOOL proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteBOOL proto WINAPI :ptr, :LPCWSTR, :BOOL
PSPropertyBag_ReadPOINTL proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WritePOINTL proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_ReadPOINTS proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WritePOINTS proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_ReadRECTL proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteRECTL proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_ReadStream proto WINAPI :ptr, :LPCWSTR, :ptr ptr
PSPropertyBag_WriteStream proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_Delete proto WINAPI :ptr, :LPCWSTR
PSPropertyBag_ReadULONGLONG proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteULONGLONG proto WINAPI :ptr, :LPCWSTR, :ULONGLONG
PSPropertyBag_ReadUnknown proto WINAPI :ptr, :LPCWSTR, :REFIID, :ptr ptr
PSPropertyBag_WriteUnknown proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_ReadGUID proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WriteGUID proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_ReadPropertyKey proto WINAPI :ptr, :LPCWSTR, :ptr
PSPropertyBag_WritePropertyKey proto WINAPI :ptr, :LPCWSTR, :REFPROPERTYKEY

ifndef __PropSysObjects_LIBRARY_DEFINED__
define __PropSysObjects_LIBRARY_DEFINED__

externdef LIBID_PropSysObjects:IID
DEFINE_GUIDS(CLSID_InMemoryPropertyStore, "9a02e012-6303-4e1e-b9a1-630f802592c5")
DEFINE_GUIDS(CLSID_InMemoryPropertyStoreMarshalByValue, "D4CA0E2D-6DA7-4b75-A97C-5F306F0EAEDC")
DEFINE_GUIDS(CLSID_PropertySystem, "b8967f85-58ae-4f46-9fb2-5d7904798f4b")

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

IInitializeWithStream_Initialize_Proxy proto WINAPI :ptr, :ptr, :DWORD
IInitializeWithStream_Initialize_Stub proto WINAPI :ptr, :ptr, :DWORD
IPropertyDescription_CoerceToCanonicalValue_Proxy proto WINAPI :ptr, :ptr
IPropertyDescription_CoerceToCanonicalValue_Stub proto WINAPI :ptr, :REFPROPVARIANT, :ptr

endif


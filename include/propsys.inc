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

ifndef __PROPSYS_INC
define __PROPSYS_INC
.pragma list(push, 0)

include objidl.inc
include oleidl.inc
include ocidl.inc
include shtypes.inc
include StructuredQueryCondition.inc
include propkeydef.inc

ifndef __IInitializeWithFile_INTERFACE_DEFINED__
__IInitializeWithFile_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInitializeWithFile, "b7d14566-0509-4cce-a71f-0a554233bd9b")

.comdef IInitializeWithFile : public IUnknown

    Initialize		proc :LPCWSTR, :DWORD

    .ends

endif

ifndef __IInitializeWithStream_INTERFACE_DEFINED__
__IInitializeWithStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInitializeWithStream, "b824b49d-22ac-4161-ac8a-9916e8fa3f7f")

.comdef IInitializeWithStream : public IUnknown

    Initialize		proc :ptr, :DWORD

    .ends

endif

ifndef __IPropertyStore_INTERFACE_DEFINED__
__IPropertyStore_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyStore, "886d8eeb-8cf2-4446-8d02-cdba1dbdcf99")

.comdef IPropertyStore : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :DWORD, :ptr
    GetValue		proc :REFPROPERTYKEY, :ptr
    SetValue		proc :REFPROPERTYKEY, :REFPROPVARIANT
    Commit		proc

    .ends
    LPPROPERTYSTORE	typedef ptr IPropertyStore
endif

ifndef __INamedPropertyStore_INTERFACE_DEFINED__
__INamedPropertyStore_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INamedPropertyStore, "71604b0f-97b0-4764-8577-2f13e98a1422")

.comdef INamedPropertyStore : public IUnknown

    GetNamedValue	proc :LPCWSTR, :ptr
    SetNamedValue	proc :LPCWSTR, :REFPROPVARIANT
    GetNameCount	proc :ptr
    GetNameAt		proc :DWORD, :ptr

    .ends
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

ifndef __IObjectWithPropertyKey_INTERFACE_DEFINED__
__IObjectWithPropertyKey_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectWithPropertyKey, "fc0ca0a7-c316-4fd2-9031-3e628e6d4f23")

.comdef IObjectWithPropertyKey : public IUnknown

    SetPropertyKey	proc :REFPROPERTYKEY
    GetPropertyKey	proc :ptr

    .ends
endif

.enum PKA_FLAGS {
	PKA_SET		= 0,
	PKA_APPEND	= PKA_SET + 1,
	PKA_DELETE	= PKA_APPEND + 1
    }

ifndef __IPropertyChange_INTERFACE_DEFINED__
__IPropertyChange_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyChange, "f917bc8a-1bba-4478-a245-1bde03eb9431")

.comdef IPropertyChange : public IObjectWithPropertyKey

    ApplyToPropVariant	proc :REFPROPVARIANT, :ptr

    .ends
endif

ifndef __IPropertyChangeArray_INTERFACE_DEFINED__
__IPropertyChangeArray_INTERFACE_DEFINED__ equ 1

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
__IPropertyStoreCapabilities_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyStoreCapabilities, "c8e2d566-186e-4d49-bf41-6909ead56acc")

.comdef IPropertyStoreCapabilities : public IUnknown

    IsPropertyWritable	proc :REFPROPERTYKEY

    .ends
endif

ifndef __IPropertyStoreCache_INTERFACE_DEFINED__
__IPropertyStoreCache_INTERFACE_DEFINED__ equ 1

.enum PSC_STATE {
    PSC_NORMAL		= 0,
    PSC_NOTINSOURCE	= 1,
    PSC_DIRTY		= 2,
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
__IPropertyEnumType_INTERFACE_DEFINED__ equ 1

.enum PROPENUMTYPE {
    PET_DISCRETEVALUE	= 0,
    PET_RANGEDVALUE	= 1,
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
__IPropertyEnumType2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyEnumType2, "9b6e051c-5ddd-4321-9070-fe2acb55e794")

.comdef IPropertyEnumType2 : public IPropertyEnumType

    GetImageReference	proc :ptr

    .ends
endif

ifndef __IPropertyEnumTypeList_INTERFACE_DEFINED__
__IPropertyEnumTypeList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyEnumTypeList, "a99400f4-3d84-4557-94ba-1242fb2cc9a6")

.comdef IPropertyEnumTypeList : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT, :REFIID, :ptr
    GetConditionAt	proc :UINT, :REFIID, :ptr
    FindMatchingIndex	proc :REFPROPVARIANT, :ptr

    .ends
endif

ifndef __IPropertyDescription_INTERFACE_DEFINED__
__IPropertyDescription_INTERFACE_DEFINED__ equ 1

.enum PROPDESC_TYPE_FLAGS {
    PDTF_DEFAULT	= 0,
    PDTF_MULTIPLEVALUES = 0x1,
    PDTF_ISINNATE	= 0x2,
    PDTF_ISGROUP	= 0x4,
    PDTF_CANGROUPBY	= 0x8,
    PDTF_CANSTACKBY	= 0x10,
    PDTF_ISTREEPROPERTY = 0x20,
    PDTF_INCLUDEINFULLTEXTQUERY = 0x40,
    PDTF_ISVIEWABLE	= 0x80,
    PDTF_ISQUERYABLE	= 0x100,
    PDTF_CANBEPURGED	= 0x200,
    PDTF_SEARCHRAWVALUE = 0x400,
    PDTF_ISSYSTEMPROPERTY = 0x80000000,
    PDTF_MASK_ALL	= 0x800007ff
}

.enum PROPDESC_VIEW_FLAGS {
    PDVF_DEFAULT	= 0,
    PDVF_CENTERALIGN	= 0x1,
    PDVF_RIGHTALIGN	= 0x2,
    PDVF_BEGINNEWGROUP	= 0x4,
    PDVF_FILLAREA	= 0x8,
    PDVF_SORTDESCENDING = 0x10,
    PDVF_SHOWONLYIFPRESENT = 0x20,
    PDVF_SHOWBYDEFAULT	= 0x40,
    PDVF_SHOWINPRIMARYLIST = 0x80,
    PDVF_SHOWINSECONDARYLIST = 0x100,
    PDVF_HIDELABEL	= 0x200,
    PDVF_HIDDEN		= 0x800,
    PDVF_CANWRAP	= 0x1000,
    PDVF_MASK_ALL	= 0x1bff
}

.enum PROPDESC_DISPLAYTYPE {
    PDDT_STRING		= 0,
    PDDT_NUMBER		= 1,
    PDDT_BOOLEAN	= 2,
    PDDT_DATETIME	= 3,
    PDDT_ENUMERATED	= 4
}

.enum PROPDESC_GROUPING_RANGE {
    PDGR_DISCRETE	= 0,
    PDGR_ALPHANUMERIC	= 1,
    PDGR_SIZE		= 2,
    PDGR_DYNAMIC	= 3,
    PDGR_DATE		= 4,
    PDGR_PERCENT	= 5,
    PDGR_ENUMERATED	= 6
}

.enum PROPDESC_FORMAT_FLAGS {
    PDFF_DEFAULT	= 0,
    PDFF_PREFIXNAME	= 0x1,
    PDFF_FILENAME	= 0x2,
    PDFF_ALWAYSKB	= 0x4,
    PDFF_RESERVED_RIGHTTOLEFT = 0x8,
    PDFF_SHORTTIME	= 0x10,
    PDFF_LONGTIME	= 0x20,
    PDFF_HIDETIME	= 0x40,
    PDFF_SHORTDATE	= 0x80,
    PDFF_LONGDATE	= 0x100,
    PDFF_HIDEDATE	= 0x200,
    PDFF_RELATIVEDATE	= 0x400,
    PDFF_USEEDITINVITATION = 0x800,
    PDFF_READONLY	= 0x1000,
    PDFF_NOAUTOREADINGORDER = 0x2000
}

.enum PROPDESC_SORTDESCRIPTION {
    PDSD_GENERAL	= 0,
    PDSD_A_Z		= 1,
    PDSD_LOWEST_HIGHEST = 2,
    PDSD_SMALLEST_BIGGEST = 3,
    PDSD_OLDEST_NEWEST	= 4
}

.enum PROPDESC_RELATIVEDESCRIPTION_TYPE {
    PDRDT_GENERAL	= 0,
    PDRDT_DATE		= 1,
    PDRDT_SIZE		= 2,
    PDRDT_COUNT		= 3,
    PDRDT_REVISION	= 4,
    PDRDT_LENGTH	= 5,
    PDRDT_DURATION	= 6,
    PDRDT_SPEED		= 7,
    PDRDT_RATE		= 8,
    PDRDT_RATING	= 9,
    PDRDT_PRIORITY	= 10
}

.enum PROPDESC_AGGREGATION_TYPE {
    PDAT_DEFAULT	= 0,
    PDAT_FIRST		= 1,
    PDAT_SUM		= 2,
    PDAT_AVERAGE	= 3,
    PDAT_DATERANGE	= 4,
    PDAT_UNION		= 5,
    PDAT_MAX		= 6,
    PDAT_MIN		= 7
}

.enum PROPDESC_CONDITION_TYPE {
    PDCOT_NONE		= 0,
    PDCOT_STRING	= 1,
    PDCOT_SIZE		= 2,
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
endif

ifndef __IPropertyDescription2_INTERFACE_DEFINED__
__IPropertyDescription2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyDescription2, "57d2eded-5062-400e-b107-5dae79fe57a6")

.comdef IPropertyDescription2 : public IPropertyDescription

    GetImageReferenceForValue proc :REFPROPVARIANT, :ptr

    .ends
endif

ifndef __IPropertyDescriptionAliasInfo_INTERFACE_DEFINED__
__IPropertyDescriptionAliasInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyDescriptionAliasInfo, "f67104fc-2af9-46fd-b32d-243c1404f3d1")

.comdef IPropertyDescriptionAliasInfo : public IPropertyDescription

    GetSortByAlias	proc :REFIID, :ptr
    GetAdditionalSortByAliases proc :REFIID, :ptr

    .ends
endif

ifndef __IPropertyDescriptionSearchInfo_INTERFACE_DEFINED__
__IPropertyDescriptionSearchInfo_INTERFACE_DEFINED__ equ 1

.enum PROPDESC_SEARCHINFO_FLAGS {
    PDSIF_DEFAULT		= 0,
    PDSIF_ININVERTEDINDEX	= 0x1,
    PDSIF_ISCOLUMN		= 0x2,
    PDSIF_ISCOLUMNSPARSE	= 0x4,
    PDSIF_ALWAYSINCLUDE		= 0x8
}

.enum PROPDESC_COLUMNINDEX_TYPE {
    PDCIT_NONE		= 0,
    PDCIT_ONDISK	= 1,
    PDCIT_INMEMORY	= 2,
    PDCIT_ONDEMAND	= 3,
    PDCIT_ONDISKALL	= 4,
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
__IPropertyDescriptionRelatedPropertyInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyDescriptionRelatedPropertyInfo, "507393f4-2a3d-4a60-b59e-d9c75716c2dd")

.comdef IPropertyDescriptionRelatedPropertyInfo : public IPropertyDescription

    GetRelatedProperty	proc :LPCWSTR, :REFIID, :ptr

    .ends
endif


.enum PROPDESC_ENUMFILTER {
    PDEF_ALL		= 0,
    PDEF_SYSTEM		= 1,
    PDEF_NONSYSTEM	= 2,
    PDEF_VIEWABLE	= 3,
    PDEF_QUERYABLE	= 4,
    PDEF_INFULLTEXTQUERY = 5,
    PDEF_COLUMN		= 6
}

ifndef __IPropertySystem_INTERFACE_DEFINED__
__IPropertySystem_INTERFACE_DEFINED__ equ 1

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
__IPropertyDescriptionList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyDescriptionList, "1f9fc1d0-c39b-4b26-817f-011967d3440e")

.comdef IPropertyDescriptionList : public IUnknown

    GetCount		proc :ptr
    GetAt		proc :UINT, :REFIID, :ptr

    .ends
endif

ifndef __IPropertyStoreFactory_INTERFACE_DEFINED__
__IPropertyStoreFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyStoreFactory, "bc110b6d-57e8-4148-a9c6-91015ab2f3a5")

.comdef IPropertyStoreFactory : public IUnknown

    GetPropertyStore	proc :GETPROPERTYSTOREFLAGS, :ptr, :REFIID, :ptr
    GetPropertyStoreForKeys proc :UINT, :GETPROPERTYSTOREFLAGS, :REFIID, :ptr

    .ends
endif

ifndef __IDelayedPropertyStoreFactory_INTERFACE_DEFINED__
__IDelayedPropertyStoreFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDelayedPropertyStoreFactory, "40d4577f-e237-4bdb-bd69-58f089431b6a")

.comdef IDelayedPropertyStoreFactory : public IPropertyStoreFactory

    GetDelayedPropertyStore proc :GETPROPERTYSTOREFLAGS, :DWORD, :REFIID, :ptr

    .ends
endif

PERSIST_SPROPSTORE_FLAGS typedef SDWORD
FPSPS_DEFAULT		equ 0
FPSPS_READONLY		equ 0x1
PERSIST_SPROPSTORE_FLAGS typedef SINT

SERIALIZEDPROPSTORAGE	typedef SERIALIZEDPROPSTORAGE
PUSERIALIZEDPROPSTORAGE typedef ptr SERIALIZEDPROPSTORAGE
PCUSERIALIZEDPROPSTORAGE typedef ptr SERIALIZEDPROPSTORAGE

ifndef __IPersistSerializedPropStorage_INTERFACE_DEFINED__
__IPersistSerializedPropStorage_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistSerializedPropStorage, "e318ad57-0aa0-450f-aca5-6fab7103d917")

.comdef IPersistSerializedPropStorage : public IUnknown

    SetFlags		proc :PERSIST_SPROPSTORE_FLAGS
    SetPropertyStorage	proc :PCUSERIALIZEDPROPSTORAGE, :DWORD
    GetPropertyStorage	proc :ptr, :ptr

    .ends
endif

ifndef __IPersistSerializedPropStorage2_INTERFACE_DEFINED__
__IPersistSerializedPropStorage2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistSerializedPropStorage2, "77effa68-4f98-4366-ba72-573b3d880571")

.comdef IPersistSerializedPropStorage2 : public IPersistSerializedPropStorage

    GetPropertyStorageSize proc :ptr
    GetPropertyStorageBuffer proc :ptr, :DWORD, :ptr

    .ends
endif

ifndef __IPropertySystemChangeNotify_INTERFACE_DEFINED__
__IPropertySystemChangeNotify_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertySystemChangeNotify, "fa955fd9-38be-4879-a6ce-824cf52d609f")

.comdef IPropertySystemChangeNotify : public IUnknown

    SchemaRefreshed	proc

    .ends
endif

ifndef __ICreateObject_INTERFACE_DEFINED__
__ICreateObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICreateObject, "75121952-e0d0-43e5-9380-1d80483acf72")

.comdef ICreateObject : public IUnknown

    CreateObject	proc :REFCLSID, :ptr, :REFIID, :ptr

    .ends
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
		  type: VARTYPE

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


ifndef __PropSysObjects_LIBRARY_DEFINED__
__PropSysObjects_LIBRARY_DEFINED__ equ 1

externdef LIBID_PropSysObjects:IID
DEFINE_GUIDS(CLSID_InMemoryPropertyStore, "9a02e012-6303-4e1e-b9a1-630f802592c5")
DEFINE_GUIDS(CLSID_PropertySystem,	  "b8967f85-58ae-4f46-9fb2-5d7904798f4b")

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

.pragma list(pop)
endif

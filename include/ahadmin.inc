ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __ahadmin_h__
define __ahadmin_h__
ifndef __unknwn_h__
include unknwn.inc
endif
ifndef __oaidl_h__
include oaidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IAppHostMethodExtension_INTERFACE_DEFINED__
define __IAppHostMethodExtension_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostMethodExtension, "70184ac9-7673-4770-96b1-445ce035cf70")

.comdef IAppHostMethodExtension : public IUnknown
    ProvideMethod       proc :ptr, :ptr, :ptr
   .ends

endif

ifndef __IAppHostPropertyExtension_INTERFACE_DEFINED__
define __IAppHostPropertyExtension_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostPropertyExtension, "88e220f3-33e8-4534-afac-b4a98eccf9ae")

.comdef IAppHostPropertyExtension : public IUnknown
    ProvideGetProperty  proc :ptr, :ptr
   .ends

endif

ifndef __IAppHostElementExtension_INTERFACE_DEFINED__
define __IAppHostElementExtension_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostElementExtension, "518eb37d-1ff4-42dd-86c3-3140bc35b823")

.comdef IAppHostElementExtension : public IUnknown
    ProvideElement      proc :ptr
   .ends

endif

ifndef __IAppHostMappingExtension_INTERFACE_DEFINED__
define __IAppHostMappingExtension_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostMappingExtension, "31a83ea0-c0e4-4a2c-8a01-353cc2a4c60a")

.comdef IAppHostMappingExtension : public IUnknown
    GetSiteNameFromSiteId proc :DWORD, :ptr
    GetSiteIdFromSiteName proc :BSTR, :ptr
    GetSiteElementFromSiteId proc :DWORD, :ptr ptr
    MapPath             proc :BSTR, :BSTR, :ptr, :ptr ptr, :ptr ptr
   .ends

endif

ifndef __IAppHostChildElementCollection_INTERFACE_DEFINED__
define __IAppHostChildElementCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostChildElementCollection, "08a90f5f-0702-48d6-b45f-02a9885a9768")

.comdef IAppHostChildElementCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
   .ends

endif

ifndef __IAppHostPropertyCollection_INTERFACE_DEFINED__
define __IAppHostPropertyCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostPropertyCollection, "0191775e-bcff-445a-b4f4-3bdda54e2816")

.comdef IAppHostPropertyCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
   .ends

endif

ifndef __IAppHostConfigLocationCollection_INTERFACE_DEFINED__
define __IAppHostConfigLocationCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostConfigLocationCollection, "832a32f7-b3ea-4b8c-b260-9a2923001184")

.comdef IAppHostConfigLocationCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
    AddLocation         proc :BSTR, :ptr ptr
    DeleteLocation      proc :VARIANT
    RenameLocation      proc :VARIANT, :BSTR
   .ends

endif

ifndef __IAppHostMethodCollection_INTERFACE_DEFINED__
define __IAppHostMethodCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostMethodCollection, "d6c7cd8f-bb8d-4f96-b591-d3a5f1320269")

.comdef IAppHostMethodCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
   .ends

endif

ifndef __IAppHostElementSchemaCollection_INTERFACE_DEFINED__
define __IAppHostElementSchemaCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostElementSchemaCollection, "0344cdda-151e-4cbf-82da-66ae61e97754")

.comdef IAppHostElementSchemaCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
   .ends

endif

ifndef __IAppHostPropertySchemaCollection_INTERFACE_DEFINED__
define __IAppHostPropertySchemaCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostPropertySchemaCollection, "8bed2c68-a5fb-4b28-8581-a0dc5267419f")

.comdef IAppHostPropertySchemaCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
   .ends

endif

ifndef __IAppHostConstantValueCollection_INTERFACE_DEFINED__
define __IAppHostConstantValueCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostConstantValueCollection, "5b5a68e6-8b9f-45e1-8199-a95ffccdffff")

.comdef IAppHostConstantValueCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
   .ends

endif

ifndef __IAppHostConstantValue_INTERFACE_DEFINED__
define __IAppHostConstantValue_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostConstantValue, "0716caf8-7d05-4a46-8099-77594be91394")

.comdef IAppHostConstantValue : public IUnknown
    get_Name            proc :ptr
    get_Value           proc :ptr
   .ends

endif

ifndef __IAppHostPropertySchema_INTERFACE_DEFINED__
define __IAppHostPropertySchema_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostPropertySchema, "450386db-7409-4667-935e-384dbbee2a9e")

.comdef IAppHostPropertySchema : public IUnknown
    get_Name            proc :ptr
    get_Type            proc :ptr
    get_DefaultValue    proc :ptr
    get_IsRequired      proc :ptr
    get_IsUniqueKey     proc :ptr
    get_IsCombinedKey   proc :ptr
    get_IsExpanded      proc :ptr
    get_ValidationType  proc :ptr
    get_ValidationParameter proc :ptr
    GetMetadata         proc :BSTR, :ptr
    get_IsCaseSensitive proc :ptr
    get_PossibleValues  proc :ptr ptr
    get_DoesAllowInfinite proc :ptr
    get_IsEncrypted     proc :ptr
    get_TimeSpanFormat  proc :ptr
   .ends

endif

ifndef __IAppHostCollectionSchema_INTERFACE_DEFINED__
define __IAppHostCollectionSchema_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostCollectionSchema, "de095db1-5368-4d11-81f6-efef619b7bcf")

.comdef IAppHostCollectionSchema : public IUnknown
    get_AddElementNames proc :ptr
    GetAddElementSchema proc :BSTR, :ptr ptr
    get_RemoveElementSchema proc :ptr ptr
    get_ClearElementSchema proc :ptr ptr
    get_IsMergeAppend   proc :ptr
    GetMetadata         proc :BSTR, :ptr
    get_DoesAllowDuplicates proc :ptr
   .ends

endif

ifndef __IAppHostElementSchema_INTERFACE_DEFINED__
define __IAppHostElementSchema_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostElementSchema, "ef13d885-642c-4709-99ec-b89561c6bc69")

.comdef IAppHostElementSchema : public IUnknown
    get_Name            proc :ptr
    get_DoesAllowUnschematizedProperties proc :ptr
    GetMetadata         proc :BSTR, :ptr
    get_CollectionSchema proc :ptr ptr
    get_ChildElementSchemas proc :ptr ptr
    get_PropertySchemas proc :ptr ptr
    get_IsCollectionDefault proc :ptr
   .ends

endif

ifndef __IAppHostMethodSchema_INTERFACE_DEFINED__
define __IAppHostMethodSchema_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostMethodSchema, "2d9915fb-9d42-4328-b782-1b46819fab9e")

.comdef IAppHostMethodSchema : public IUnknown
    get_Name            proc :ptr
    get_InputSchema     proc :ptr ptr
    get_OutputSchema    proc :ptr ptr
    GetMetadata         proc :BSTR, :ptr
   .ends

endif

ifndef __IAppHostMethodInstance_INTERFACE_DEFINED__
define __IAppHostMethodInstance_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostMethodInstance, "b80f3c42-60e0-4ae0-9007-f52852d3dbed")

.comdef IAppHostMethodInstance : public IUnknown
    get_Input           proc :ptr ptr
    get_Output          proc :ptr ptr
    Execute             proc
    GetMetadata         proc :BSTR, :ptr
    SetMetadata         proc :BSTR, :VARIANT
   .ends

endif

ifndef __IAppHostMethod_INTERFACE_DEFINED__
define __IAppHostMethod_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostMethod, "7883ca1c-1112-4447-84c3-52fbeb38069d")

.comdef IAppHostMethod : public IUnknown
    get_Name            proc :ptr
    get_Schema          proc :ptr ptr
    CreateInstance      proc :ptr ptr
   .ends

endif

ifndef __IAppHostConfigException_INTERFACE_DEFINED__
define __IAppHostConfigException_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostConfigException, "4dfa1df3-8900-4bc7-bbb5-d1a458c52410")

.comdef IAppHostConfigException : public IUnknown
    get_LineNumber      proc :ptr
    get_FileName        proc :ptr
    get_ConfigPath      proc :ptr
    get_ErrorLine       proc :ptr
    get_PreErrorLine    proc :ptr
    get_PostErrorLine   proc :ptr
    get_ErrorString     proc :ptr
   .ends

endif

ifndef __IAppHostPropertyException_INTERFACE_DEFINED__
define __IAppHostPropertyException_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostPropertyException, "eafe4895-a929-41ea-b14d-613e23f62b71")

.comdef IAppHostPropertyException : public IAppHostConfigException
    get_InvalidValue    proc :ptr
    get_ValidationFailureReason proc :ptr
    get_ValidationFailureParameters proc :ptr
   .ends

endif

ifndef __IAppHostElementCollection_INTERFACE_DEFINED__
define __IAppHostElementCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostElementCollection, "c8550bff-5281-4b1e-ac34-99b6fa38464d")

.comdef IAppHostElementCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
    AddElement          proc :ptr, :int_t
    DeleteElement       proc :VARIANT
    Clear               proc
    CreateNewElement    proc :BSTR, :ptr ptr
    get_Schema          proc :ptr ptr
   .ends

endif

ifndef __IAppHostElement_INTERFACE_DEFINED__
define __IAppHostElement_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostElement, "64ff8ccc-b287-4dae-b08a-a72cbf45f453")

.comdef IAppHostElement : public IUnknown
    get_Name            proc :ptr
    get_Collection      proc :ptr ptr
    get_Properties      proc :ptr ptr
    get_ChildElements   proc :ptr ptr
    GetMetadata         proc :BSTR, :ptr
    SetMetadata         proc :BSTR, :VARIANT
    get_Schema          proc :ptr ptr
    GetElementByName    proc :BSTR, :ptr ptr
    GetPropertyByName   proc :BSTR, :ptr ptr
    Clear               proc
    get_Methods         proc :ptr ptr
   .ends

endif

ifndef __IAppHostProperty_INTERFACE_DEFINED__
define __IAppHostProperty_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostProperty, "ed35f7a1-5024-4e7b-a44d-07ddaf4b524d")

.comdef IAppHostProperty : public IUnknown
    get_Name            proc :ptr
    get_Value           proc :ptr
    put_Value           proc :VARIANT
    Clear               proc
    get_StringValue     proc :ptr
    get_Exception       proc :ptr ptr
    GetMetadata         proc :BSTR, :ptr
    SetMetadata         proc :BSTR, :VARIANT
    get_Schema          proc :ptr ptr
   .ends

endif

ifndef __IAppHostConfigLocation_INTERFACE_DEFINED__
define __IAppHostConfigLocation_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostConfigLocation, "370af178-7758-4dad-8146-7391f6e18585")

.comdef IAppHostConfigLocation : public IUnknown
    get_Path            proc :ptr
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
    AddConfigSection    proc :BSTR, :ptr ptr
    DeleteConfigSection proc :VARIANT
   .ends

endif

ifndef __IAppHostSectionDefinition_INTERFACE_DEFINED__
define __IAppHostSectionDefinition_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostSectionDefinition, "c5c04795-321c-4014-8fd6-d44658799393")

.comdef IAppHostSectionDefinition : public IUnknown
    get_Name            proc :ptr
    get_Type            proc :ptr
    put_Type            proc :BSTR
    get_OverrideModeDefault proc :ptr
    put_OverrideModeDefault proc :BSTR
    get_AllowDefinition proc :ptr
    put_AllowDefinition proc :BSTR
    get_AllowLocation   proc :ptr
    put_AllowLocation   proc :BSTR
    get_RequirePermission proc :ptr
    put_RequirePermission proc :VARIANT_BOOL
   .ends

endif

ifndef __IAppHostSectionDefinitionCollection_INTERFACE_DEFINED__
define __IAppHostSectionDefinitionCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostSectionDefinitionCollection, "b7d381ee-8860-47a1-8af4-1f33b2b1f325")

.comdef IAppHostSectionDefinitionCollection : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
    AddSection          proc :BSTR, :ptr ptr
    DeleteSection       proc :VARIANT
   .ends

endif

ifndef __IAppHostSectionGroup_INTERFACE_DEFINED__
define __IAppHostSectionGroup_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostSectionGroup, "0dd8a158-ebe6-4008-a1d9-b7ecc8f1104b")

.comdef IAppHostSectionGroup : public IUnknown
    get_Count           proc :ptr
    get_Item            proc :VARIANT, :ptr ptr
    get_Sections        proc :ptr ptr
    AddSectionGroup     proc :BSTR, :ptr ptr
    DeleteSectionGroup  proc :VARIANT
    get_Name            proc :ptr
    get_Type            proc :ptr
    put_Type            proc :BSTR
   .ends

endif

ifndef __IAppHostConfigFile_INTERFACE_DEFINED__
define __IAppHostConfigFile_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostConfigFile, "ada4e6fb-e025-401e-a5d0-c3134a281f07")

.comdef IAppHostConfigFile : public IUnknown
    get_ConfigPath      proc :ptr
    get_FilePath        proc :ptr
    get_Locations       proc :ptr ptr
    GetAdminSection     proc :BSTR, :BSTR, :ptr ptr
    GetMetadata         proc :BSTR, :ptr
    SetMetadata         proc :BSTR, :VARIANT
    ClearInvalidSections proc
    get_RootSectionGroup proc :ptr ptr
   .ends

endif

ifndef __IAppHostPathMapper_INTERFACE_DEFINED__
define __IAppHostPathMapper_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostPathMapper, "e7927575-5cc3-403b-822e-328a6b904bee")

.comdef IAppHostPathMapper : public IUnknown
    MapPath             proc :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __IAppHostPathMapper2_INTERFACE_DEFINED__
define __IAppHostPathMapper2_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostPathMapper2, "0f80e901-8f4c-449a-bf90-13d5d082f187")

.comdef IAppHostPathMapper2 : public IUnknown
    MapPath             proc :BSTR, :BSTR, :ptr, :ptr
   .ends

endif

ifndef __IAppHostChangeHandler_INTERFACE_DEFINED__
define __IAppHostChangeHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostChangeHandler, "09829352-87c2-418d-8d79-4133969a489d")

.comdef IAppHostChangeHandler : public IUnknown
    OnSectionChanges    proc :BSTR, :BSTR
   .ends

endif

ifndef __IAppHostAdminManager_INTERFACE_DEFINED__
define __IAppHostAdminManager_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostAdminManager, "9be77978-73ed-4a9a-87fd-13f09fec1b13")

.comdef IAppHostAdminManager : public IUnknown
    GetAdminSection     proc :BSTR, :BSTR, :ptr ptr
    GetMetadata         proc :BSTR, :ptr
    SetMetadata         proc :BSTR, :VARIANT
    get_ConfigManager   proc :ptr ptr
   .ends

endif

ifndef __IAppHostWritableAdminManager_INTERFACE_DEFINED__
define __IAppHostWritableAdminManager_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostWritableAdminManager, "fa7660f6-7b3f-4237-a8bf-ed0ad0dcbbd9")

.comdef IAppHostWritableAdminManager : public IAppHostAdminManager
    CommitChanges       proc
    get_CommitPath      proc :ptr
    put_CommitPath      proc :BSTR
   .ends

endif

ifndef __IAppHostConfigManager_INTERFACE_DEFINED__
define __IAppHostConfigManager_INTERFACE_DEFINED__

DEFINE_IIDX(IAppHostConfigManager, "8f6d760f-f0cb-4d69-b5f6-848b33e9bdc6")

.comdef IAppHostConfigManager : public IUnknown
    GetConfigFile       proc :BSTR, :ptr ptr
    GetUniqueConfigPath proc :BSTR, :ptr
   .ends

endif

ifndef __AppHostAdminLibrary_LIBRARY_DEFINED__
define __AppHostAdminLibrary_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_AppHostAdminLibrary, 0x598f9c7d,0xd2d7,0x4980,0xb2,0x34,0xf1,0xe7,0x53,0xcd,0x9f,0xd9)
DEFINE_GUIDS(CLSID_AppHostAdminManager, "228fb8f7-fb53-4fd5-8c7b-ff59de606c5b")
DEFINE_GUIDS(CLSID_AppHostWritableAdminManager, "2b72133b-3f5b-4602-8952-803546ce3344")

endif

endif

endif

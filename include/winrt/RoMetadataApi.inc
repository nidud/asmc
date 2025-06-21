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

ifndef __rometadataapi_h__
define __rometadataapi_h__

include unknwn.inc
include oaidl.inc

ifdef _WIN64
HCORENUM                typedef  sqword
else
HCORENUM                typedef  sdword
endif

COR_SIGNATURE           typedef byte
PCOR_SIGNATURE          typedef ptr COR_SIGNATURE
PCCOR_SIGNATURE         typedef ptr COR_SIGNATURE

MDUTF8CSTR              typedef ptr sbyte
UVCP_CONSTANT           typedef ptr sbyte

mdToken                 typedef ULONG32
mdModule                typedef mdToken
mdTypeRef               typedef mdToken
mdTypeDef               typedef mdToken
mdFieldDef              typedef mdToken
mdMethodDef             typedef mdToken
mdParamDef              typedef mdToken
mdInterfaceImpl         typedef mdToken
mdMemberRef             typedef mdToken
mdCustomAttribute       typedef mdToken
mdPermission            typedef mdToken
mdSignature             typedef mdToken
mdEvent                 typedef mdToken
mdProperty              typedef mdToken
mdModuleRef             typedef mdToken
mdAssembly              typedef mdToken
mdAssemblyRef           typedef mdToken
mdFile                  typedef mdToken
mdExportedType          typedef mdToken
mdManifestResource      typedef mdToken
mdTypeSpec              typedef mdToken
mdGenericParam          typedef mdToken
mdMethodSpec            typedef mdToken
mdGenericParamConstraint typedef mdToken
mdString                typedef mdToken

COR_FIELD_OFFSET        STRUC
ridOfField              mdFieldDef ?
ulOffset                ULONG32 ?
COR_FIELD_OFFSET        ENDS

OSINFO                  STRUC
dwOSPlatformId          dd ?
dwOSMajorVersion        dd ?
dwOSMinorVersion        dd ?
OSINFO                  ENDS

ASSEMBLYMETADATA        STRUC
usMajorVersion          USHORT ?
usMinorVersion          USHORT ?
usBuildNumber           USHORT ?
usRevisionNumber        USHORT ?
szLocale                LPWSTR ?
cbLocale                ULONG ?
rProcessor              LPDWORD ?
ulProcessor             ULONG ?
rOS                     ptr OSINFO ?
ulOS                    ULONG ?
ASSEMBLYMETADATA        ENDS

ifndef __IMetaDataDispenser_INTERFACE_DEFINED__
define __IMetaDataDispenser_INTERFACE_DEFINED__
DEFINE_IIDX(IMetaDataDispenser, "809C652E-7396-11D2-9771-00A0C9B4D50C")

.comdef IMetaDataDispenser : public IUnknown

    DefineScope         proc :REFCLSID, :DWORD, :REFIID, :ptr
    OpenScope           proc :LPCWSTR, :DWORD, :REFIID, :ptr
    OpenScopeOnMemory   proc :ptr, :ULONG, :DWORD, :REFIID, :ptr
   .ends

endif

ifndef __IMetaDataDispenserEx_INTERFACE_DEFINED__
define __IMetaDataDispenserEx_INTERFACE_DEFINED__
DEFINE_IIDX(IMetaDataDispenserEx, "31BCFCE2-DAFB-11D2-9F81-00C04F79A0A3")

.comdef IMetaDataDispenserEx : public IMetaDataDispenser

    SetOption           proc :REFGUID, :ptr
    GetOption           proc :REFGUID, :ptr
    OpenScopeOnITypeInfo proc :ptr, :DWORD, :REFIID, :ptr
    GetCORSystemDirectory proc :LPWSTR, :DWORD, :ptr
    FindAssembly        proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPWSTR, :ULONG, :ptr
    FindAssemblyModule  proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPWSTR, :ULONG, :ptr
   .ends

endif

ifndef __IMetaDataAssemblyImport_INTERFACE_DEFINED__
define __IMetaDataAssemblyImport_INTERFACE_DEFINED__
DEFINE_IIDX(IMetaDataAssemblyImport, "EE62470B-E94B-424E-9B7C-2F00C9249F93")

.comdef IMetaDataAssemblyImport : public IUnknown

    GetAssemblyProps    proc :mdAssembly, :ptr, :ptr, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr
    GetAssemblyRefProps proc :mdAssemblyRef, :ptr, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr, :ptr
    GetFileProps        proc :mdFile, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr
    GetExportedTypeProps proc :mdExportedType, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr
    GetManifestResourceProps proc :mdManifestResource, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr
    EnumAssemblyRefs    proc :ptr, :ptr, :ULONG, :ptr
    EnumFiles           proc :ptr, :ptr, :ULONG, :ptr
    EnumExportedTypes   proc :ptr, :ptr, :ULONG, :ptr
    EnumManifestResources proc :ptr, :ptr, :ULONG, :ptr
    GetAssemblyFromScope proc :ptr
    FindExportedTypeByName proc :LPCWSTR, :mdToken, :ptr
    FindManifestResourceByName proc :LPCWSTR, :ptr
    CloseEnum           proc :HCORENUM
    FindAssembliesByName proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr, :ULONG, :ptr
   .ends

endif

ifndef __IMetaDataImport_INTERFACE_DEFINED__
define __IMetaDataImport_INTERFACE_DEFINED__
DEFINE_IIDX(IMetaDataImport, "7DAC8207-D3AE-4C75-9B67-92801A497D44")

.comdef IMetaDataImport : public IUnknown

    CloseEnum           proc :HCORENUM
    CountEnum           proc :HCORENUM, :ptr
    ResetEnum           proc :HCORENUM, :ULONG
    EnumTypeDefs        proc :ptr, :ptr, :ULONG, :ptr
    EnumInterfaceImpls  proc :ptr, :ptr, :ptr, :ULONG, :ptr
    EnumTypeRefs        proc :ptr, :ptr, :ULONG, :ptr
    FindTypeDefByName   proc :LPCWSTR, :ptr, :ptr
    GetScopeProps       proc :LPWSTR, :ULONG, :ptr, :ptr
    GetModuleFromScope  proc :ptr
    GetTypeDefProps     proc :mdTypeDef, :LPWSTR, :ULONG, :ptr, :ptr, :ptr
    GetInterfaceImplProps proc :ptr, :ptr, :ptr
    GetTypeRefProps     proc :ptr, :ptr, :LPWSTR, :ULONG, :ptr
    ResolveTypeRef      proc :ptr, :REFIID, :ptr, :ptr
    EnumMembers         proc :ptr, :mdTypeDef, :ptr, :ULONG, :ptr
    EnumMembersWithName proc :ptr, :mdTypeDef, :LPCWSTR, :ptr, :ULONG, :ptr
    EnumMethods         proc :ptr, :mdTypeDef, :ptr, :ULONG, :ptr
    EnumMethodsWithName proc :ptr, :mdTypeDef, :LPCWSTR, :ptr, :ULONG, :ptr
    EnumFields          proc :ptr, :mdTypeDef, :ptr, :ULONG, :ptr
    EnumFieldsWithName  proc :ptr, :mdTypeDef, :LPCWSTR, :ptr, :ULONG, :ptr
    EnumParams          proc :ptr, :mdMethodDef, :ptr, :ULONG, :ptr
    EnumMemberRefs      proc :ptr, :mdToken, :ptr, :ULONG, :ptr
    EnumMethodImpls     proc :ptr, :mdTypeDef, :ptr, :ptr, :ULONG, :ptr
    EnumPermissionSets  proc :ptr, :mdToken, :DWORD, :ptr, :ULONG, :ptr
    FindMember          proc :mdTypeDef, :LPCWSTR, :PCCOR_SIGNATURE, :ULONG, :ptr
    FindMethod          proc :mdTypeDef, :LPCWSTR, :PCCOR_SIGNATURE, :ULONG, :ptr
    FindField           proc :mdTypeDef, :LPCWSTR, :PCCOR_SIGNATURE, :ULONG, :ptr
    FindMemberRef       proc :mdTypeRef, :LPCWSTR, :PCCOR_SIGNATURE, :ULONG, :ptr
    GetMethodProps      proc :mdMethodDef, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    GetMemberRefProps   proc :mdMemberRef, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr
    EnumProperties      proc :ptr, :mdTypeDef, :ptr, :ULONG, :ptr
    EnumEvents          proc :ptr, :mdTypeDef, :ptr, :ULONG, :ptr
    GetEventProps       proc :mdEvent, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ULONG, :ptr
    EnumMethodSemantics proc :ptr, :mdMethodDef, :ptr, :ULONG, :ptr
    GetMethodSemantics  proc :mdMethodDef, :mdToken, :ptr
    GetClassLayout      proc :mdTypeDef, :ptr, :ptr, :ULONG, :ptr, :ptr
    GetFieldMarshal     proc :mdToken, :ptr, :ptr
    GetRVA              proc :mdToken, :ptr, :ptr
    GetPermissionSetProps proc :mdPermission, :ptr, :ptr, :ptr
    GetSigFromToken     proc :mdSignature, :ptr, :ptr
    GetModuleRefProps   proc :mdModuleRef, :LPWSTR, :ULONG, :ptr
    EnumModuleRefs      proc :ptr, :ptr, :ULONG, :ptr
    GetTypeSpecFromToken proc :mdTypeSpec, :ptr, :ptr
    GetNameFromToken    proc :mdToken, :ptr
    EnumUnresolvedMethods proc :ptr, :ptr, :ULONG, :ptr
    GetUserString       proc :mdString, :LPWSTR, :ULONG, :ptr
    GetPinvokeMap       proc :mdToken, :ptr, :LPWSTR, :ULONG, :ptr, :ptr
    EnumSignatures      proc :ptr, :ptr, :ULONG, :ptr
    EnumTypeSpecs       proc :ptr, :ptr, :ULONG, :ptr
    EnumUserStrings     proc :ptr, :ptr, :ULONG, :ptr
    GetParamForMethodIndex proc :mdMethodDef, :ULONG, :ptr
    EnumCustomAttributes proc :ptr, :mdToken, :mdToken, :ptr, :ULONG, :ptr
    GetCustomAttributeProps proc :mdCustomAttribute, :ptr, :ptr, :ptr, :ptr
    FindTypeRef         proc :mdToken, :LPCWSTR, :ptr
    GetMemberProps      proc :mdToken, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    GetFieldProps       proc :mdFieldDef, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    GetPropertyProps    proc :mdProperty, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ULONG, :ptr
    GetParamProps       proc :mdParamDef, :ptr, :ptr, :LPWSTR, :ULONG, :ptr, :ptr, :ptr, :ptr, :ptr
    GetCustomAttributeByName proc :mdToken, :LPCWSTR, :ptr, :ptr
    IsValidToken        proc :mdToken
    GetNestedClassProps proc :mdTypeDef, :ptr
    GetNativeCallConvFromSig proc :ptr, :ULONG, :ptr
    IsGlobal            proc :mdToken, :ptr
   .ends

endif

ifndef __IMetaDataImport2_INTERFACE_DEFINED__
define __IMetaDataImport2_INTERFACE_DEFINED__
DEFINE_IIDX(IMetaDataImport2, "FCE5EFA0-8BBA-4f8E-A036-8F2022B08466")

.comdef IMetaDataImport2 : public IMetaDataImport

    EnumGenericParams   proc :ptr, :mdToken, :ptr, :ULONG, :ptr
    GetGenericParamProps proc :mdGenericParam, :ptr, :ptr, :ptr, :ptr, :LPWSTR, :ULONG, :ptr
    GetMethodSpecProps  proc :mdMethodSpec, :ptr, :ptr, :ptr
    EnumGenericParamConstraints proc :ptr, :mdGenericParam, :ptr, :ULONG, :ptr
    GetGenericParamConstraintProps proc :mdGenericParamConstraint, :ptr, :ptr
    GetPEKind           proc :ptr, :ptr
    GetVersionString    proc :LPWSTR, :DWORD, :ptr
    EnumMethodSpecs     proc :ptr, :mdToken, :ptr, :ULONG, :ptr
   .ends

endif

ifndef __IMetaDataTables_INTERFACE_DEFINED__
define __IMetaDataTables_INTERFACE_DEFINED__
DEFINE_IIDX(IMetaDataTables, "D8F579AB-402D-4B8E-82D9-5D63B1065C68")

.comdef IMetaDataTables : public IUnknown

    GetStringHeapSize   proc :ptr
    GetBlobHeapSize     proc :ptr
    GetGuidHeapSize     proc :ptr
    GetUserStringHeapSize proc :ptr
    GetNumTables        proc :ptr
    GetTableIndex       proc :ULONG, :ptr
    GetTableInfo        proc :ULONG, :ptr, :ptr, :ptr, :ptr, :ptr
    GetColumnInfo       proc :ULONG, :ULONG, :ptr, :ptr, :ptr, :ptr
    GetCodedTokenInfo   proc :ULONG, :ptr, :ptr, :ptr
    GetRow              proc :ULONG, :ULONG, :ptr
    GetColumn           proc :ULONG, :ULONG, :ULONG, :ptr
    GetString           proc :ULONG, :ptr
    GetBlob             proc :ULONG, :ptr, :ptr
    GetGuid             proc :ULONG, :ptr
    GetUserString       proc :ULONG, :ptr, :ptr
    GetNextString       proc :ULONG, :ptr
    GetNextBlob         proc :ULONG, :ptr
    GetNextGuid         proc :ULONG, :ptr
    GetNextUserString   proc :ULONG, :ptr
   .ends

endif

ifndef __IMetaDataTables2_INTERFACE_DEFINED__
define __IMetaDataTables2_INTERFACE_DEFINED__
DEFINE_IIDX(IMetaDataTables2, "BADB5F70-58DA-43a9-A1C6-D74819F19B15")

.comdef IMetaDataTables2 : public IMetaDataTables

    GetMetaDataStorage  proc :ptr, :ptr
    GetMetaDataStreamInfo proc :ULONG, :ptr, :ptr, :ptr
   .ends

endif

;else
;include cor.inc
;include corhdr.inc
;endif

endif

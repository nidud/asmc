.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err<this stub requires an updated version of rpcndr.inc>
endif

ifndef __appxpackaging_h__
__appxpackaging_h__ equ <>

ifndef __IAppxPackageWriter_FWD_DEFINED__
__IAppxPackageWriter_FWD_DEFINED__ equ 1
endif
ifndef __IAppxPackageReader_FWD_DEFINED__
__IAppxPackageReader_FWD_DEFINED__ equ 1
endif
ifndef __IAppxFile_FWD_DEFINED__
__IAppxFile_FWD_DEFINED__ equ 1
endif
ifndef __IAppxFilesEnumerator_FWD_DEFINED__
__IAppxFilesEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBlockMapReader_FWD_DEFINED__
__IAppxBlockMapReader_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBlockMapFile_FWD_DEFINED__
__IAppxBlockMapFile_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBlockMapFilesEnumerator_FWD_DEFINED__
__IAppxBlockMapFilesEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBlockMapBlock_FWD_DEFINED__
__IAppxBlockMapBlock_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBlockMapBlocksEnumerator_FWD_DEFINED__
__IAppxBlockMapBlocksEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestReader_FWD_DEFINED__
__IAppxManifestReader_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestPackageId_FWD_DEFINED__
__IAppxManifestPackageId_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestProperties_FWD_DEFINED__
__IAppxManifestProperties_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestPackageDependency_FWD_DEFINED__
__IAppxManifestPackageDependency_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestPackageDependenciesEnumerator_FWD_DEFINED__
__IAppxManifestPackageDependenciesEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestResourcesEnumerator_FWD_DEFINED__
__IAppxManifestResourcesEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestDeviceCapabilitiesEnumerator_FWD_DEFINED__
__IAppxManifestDeviceCapabilitiesEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestApplicationsEnumerator_FWD_DEFINED__
__IAppxManifestApplicationsEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestApplication_FWD_DEFINED__
__IAppxManifestApplication_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestQualifiedResourcesEnumerator_FWD_DEFINED__
__IAppxManifestQualifiedResourcesEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestQualifiedResource_FWD_DEFINED__
__IAppxManifestQualifiedResource_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBundleFactory_FWD_DEFINED__
__IAppxBundleFactory_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBundleWriter_FWD_DEFINED__
__IAppxBundleWriter_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBundleReader_FWD_DEFINED__
__IAppxBundleReader_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBundleManifestReader_FWD_DEFINED__
__IAppxBundleManifestReader_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBundleManifestPackageInfoEnumerator_FWD_DEFINED__
__IAppxBundleManifestPackageInfoEnumerator_FWD_DEFINED__ equ 1
endif
ifndef __IAppxBundleManifestPackageInfo_FWD_DEFINED__
__IAppxBundleManifestPackageInfo_FWD_DEFINED__ equ 1
endif
ifndef __IAppxFactory_FWD_DEFINED__
__IAppxFactory_FWD_DEFINED__ equ 1
endif
ifndef __AppxFactory_FWD_DEFINED__
__AppxFactory_FWD_DEFINED__ equ 1
endif
ifndef __IAppxManifestReader2_FWD_DEFINED__
__IAppxManifestReader2_FWD_DEFINED__ equ 1
endif
ifndef __AppxBundleFactory_FWD_DEFINED__
__AppxBundleFactory_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (NTDDI_VERSION GE NTDDI_WIN7)

ifndef __APPXPACKAGING_LIBRARY_DEFINED__
__APPXPACKAGING_LIBRARY_DEFINED__ equ 1

APPX_PACKAGE_SETTINGS	STRUC
forceZip32		BOOL ?
hashMethod		PVOID ? ; *IUri
APPX_PACKAGE_SETTINGS	ENDS

APPX_COMPRESSION_OPTION typedef SDWORD
APPX_COMPRESSION_OPTION_NONE equ 0
APPX_COMPRESSION_OPTION_NORMAL equ 1
APPX_COMPRESSION_OPTION_MAXIMUM equ 2
APPX_COMPRESSION_OPTION_FAST equ 3
APPX_COMPRESSION_OPTION_SUPERFAST equ 4

APPX_FOOTPRINT_FILE_TYPE typedef SDWORD
APPX_FOOTPRINT_FILE_TYPE_MANIFEST equ 0
APPX_FOOTPRINT_FILE_TYPE_BLOCKMAP equ 1
APPX_FOOTPRINT_FILE_TYPE_SIGNATURE equ 2
APPX_FOOTPRINT_FILE_TYPE_CODEINTEGRITY equ 3

APPX_BUNDLE_FOOTPRINT_FILE_TYPE typedef SDWORD
APPX_BUNDLE_FOOTPRINT_FILE_TYPE_FIRST equ 0
APPX_BUNDLE_FOOTPRINT_FILE_TYPE_MANIFEST equ 0
APPX_BUNDLE_FOOTPRINT_FILE_TYPE_BLOCKMAP equ 1
APPX_BUNDLE_FOOTPRINT_FILE_TYPE_SIGNATURE equ 2
APPX_BUNDLE_FOOTPRINT_FILE_TYPE_LAST equ 2

APPX_PACKAGE_ARCHITECTURE typedef SDWORD
APPX_PACKAGE_ARCHITECTURE_X86 equ 0
APPX_PACKAGE_ARCHITECTURE_ARM equ 5
APPX_PACKAGE_ARCHITECTURE_X64 equ 9
APPX_PACKAGE_ARCHITECTURE_NEUTRAL equ 11

APPX_BUNDLE_PAYLOAD_PACKAGE_TYPE typedef SDWORD
APPX_BUNDLE_PAYLOAD_PACKAGE_TYPE_APPLICATION equ 0
APPX_BUNDLE_PAYLOAD_PACKAGE_TYPE_RESOURCE equ 1

APPX_CAPABILITIES	typedef SDWORD
APPX_CAPABILITY_INTERNET_CLIENT equ 0x1
APPX_CAPABILITY_INTERNET_CLIENT_SERVER equ 0x2
APPX_CAPABILITY_PRIVATE_NETWORK_CLIENT_SERVER equ 0x4
APPX_CAPABILITY_DOCUMENTS_LIBRARY equ 0x8
APPX_CAPABILITY_PICTURES_LIBRARY equ 0x10
APPX_CAPABILITY_VIDEOS_LIBRARY equ 0x20
APPX_CAPABILITY_MUSIC_LIBRARY equ 0x40
APPX_CAPABILITY_ENTERPRISE_AUTHENTICATION equ 0x80
APPX_CAPABILITY_SHARED_USER_CERTIFICATES equ 0x100
APPX_CAPABILITY_REMOVABLE_STORAGE equ 0x200
APPX_CAPABILITY_APPOINTMENTS equ 0x400
APPX_CAPABILITY_CONTACTS equ 0x800

DEFINE_ENUM_FLAG_OPERATORS(APPX_CAPABILITIES);
DX_FEATURE_LEVEL	typedef SDWORD
DX_FEATURE_LEVEL_UNSPECIFIED equ 0
DX_FEATURE_LEVEL_9	equ 1
DX_FEATURE_LEVEL_10	equ 2
DX_FEATURE_LEVEL_11	equ 3

externdef		LIBID_APPXPACKAGING:IID

ifndef __IAppxPackageWriter_INTERFACE_DEFINED__
__IAppxPackageWriter_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxPackageWriter:IID

.comdef IAppxPackageWriter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddPayloadFile	proc :LPCWSTR, :LPCWSTR, :APPX_COMPRESSION_OPTION, :ptr
    Close		proc :ptr
    .ends

endif

ifndef __IAppxPackageReader_INTERFACE_DEFINED__
__IAppxPackageReader_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxPackageReader:IID

.comdef IAppxPackageReader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetBlockMap		proc :ptr
    GetFootprintFile	proc :APPX_FOOTPRINT_FILE_TYPE, :ptr
    GetPayloadFile	proc :LPCWSTR, :ptr
    GetPayloadFiles	proc :ptr
    GetManifest		proc :ptr
    .ends

endif

ifndef __IAppxFile_INTERFACE_DEFINED__
__IAppxFile_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxFile:IID

.comdef IAppxFile

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCompressionOption proc :ptr
    GetContentType	proc :ptr
    GetName		proc :ptr
    GetSize		proc :ptr
    GetStream		proc :ptr
    .ends

endif

ifndef __IAppxFilesEnumerator_INTERFACE_DEFINED__
__IAppxFilesEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxFilesEnumerator:IID

.comdef IAppxFilesEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxBlockMapReader_INTERFACE_DEFINED__
__IAppxBlockMapReader_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBlockMapReader:IID

.comdef IAppxBlockMapReader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFile		proc :LPCWSTR, :ptr
    GetFiles		proc :ptr
    GetHashMethod	proc :ptr
    GetStream		proc :ptr
    .ends

endif

ifndef __IAppxBlockMapFile_INTERFACE_DEFINED__
__IAppxBlockMapFile_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBlockMapFile:IID

.comdef IAppxBlockMapFile

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetBlocks		proc :ptr
    GetLocalFileHeaderSize proc :ptr
    GetName		proc :ptr
    GetUncompressedSize proc :ptr
    ValidateFileHash	proc :ptr, :ptr
    .ends

endif

ifndef __IAppxBlockMapFilesEnumerator_INTERFACE_DEFINED__
__IAppxBlockMapFilesEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBlockMapFilesEnumerator:IID

.comdef IAppxBlockMapFilesEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxBlockMapBlock_INTERFACE_DEFINED__
__IAppxBlockMapBlock_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBlockMapBlock:IID

.comdef IAppxBlockMapBlock

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetHash		proc :ptr, :ptr
    GetCompressedSize	proc :ptr
    .ends

endif

ifndef __IAppxBlockMapBlocksEnumerator_INTERFACE_DEFINED__
__IAppxBlockMapBlocksEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBlockMapBlocksEnumerator:IID

.comdef IAppxBlockMapBlocksEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxManifestReader_INTERFACE_DEFINED__
__IAppxManifestReader_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestReader:IID

.comdef IAppxManifestReader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPackageId	proc :ptr
    GetProperties	proc :ptr
    GetPackageDependencies proc :ptr
    GetCapabilities	proc :ptr
    GetResources	proc :ptr
    GetDeviceCapabilities proc :ptr
    GetPrerequisite	proc :LPCWSTR, :ptr
    GetApplications	proc :ptr
    GetStream		proc :ptr
    .ends

endif

ifndef __IAppxManifestPackageId_INTERFACE_DEFINED__
__IAppxManifestPackageId_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestPackageId:IID

.comdef IAppxManifestPackageId

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetName		proc :ptr
    GetArchitecture	proc :ptr
    GetPublisher	proc :ptr
    GetVersion		proc :ptr
    GetResourceId	proc :ptr
    ComparePublisher	proc :LPCWSTR, :ptr
    GetPackageFullName	proc :ptr
    GetPackageFamilyName proc :ptr
    .ends

endif

ifndef __IAppxManifestProperties_INTERFACE_DEFINED__
__IAppxManifestProperties_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestProperties:IID

.comdef IAppxManifestProperties

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetBoolValue	proc :LPCWSTR, :ptr
    GetStringValue	proc :LPCWSTR, :ptr
    .ends

endif

ifndef __IAppxManifestPackageDependency_INTERFACE_DEFINED__
__IAppxManifestPackageDependency_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestPackageDependency:IID

.comdef IAppxManifestPackageDependency

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetName		proc :ptr
    GetPublisher	proc :ptr
    GetMinVersion	proc :ptr
    .ends

endif

ifndef __IAppxManifestPackageDependenciesEnumerator_INTERFACE_DEFINED__
__IAppxManifestPackageDependenciesEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestPackageDependenciesEnumerator:IID

.comdef IAppxManifestPackageDependenciesEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxManifestResourcesEnumerator_INTERFACE_DEFINED__
__IAppxManifestResourcesEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestResourcesEnumerator:IID

.comdef IAppxManifestResourcesEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxManifestDeviceCapabilitiesEnumerator_INTERFACE_DEFINED__
__IAppxManifestDeviceCapabilitiesEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestDeviceCapabilitiesEnumerator:IID

.comdef IAppxManifestDeviceCapabilitiesEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxManifestApplicationsEnumerator_INTERFACE_DEFINED__
__IAppxManifestApplicationsEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestApplicationsEnumerator:IID

.comdef IAppxManifestApplicationsEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxManifestApplication_INTERFACE_DEFINED__
__IAppxManifestApplication_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestApplication:IID

.comdef IAppxManifestApplication

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetStringValue	proc :LPCWSTR, :ptr
    GetAppUserModelId	proc :ptr
    .ends

endif

ifndef __IAppxManifestQualifiedResourcesEnumerator_INTERFACE_DEFINED__
__IAppxManifestQualifiedResourcesEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestQualifiedResourcesEnumerator:IID

.comdef IAppxManifestQualifiedResourcesEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxManifestQualifiedResource_INTERFACE_DEFINED__
__IAppxManifestQualifiedResource_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestQualifiedResource:IID

.comdef IAppxManifestQualifiedResource

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetLanguage		proc :ptr
    GetScale		proc :ptr
    GetDXFeatureLevel	proc :ptr
    .ends

endif

ifndef __IAppxBundleFactory_INTERFACE_DEFINED__
__IAppxBundleFactory_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBundleFactory:IID

.comdef IAppxBundleFactory

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateBundleWriter	proc :ptr, :UINT64, :ptr
    CreateBundleReader	proc :ptr, :ptr
    CreateBundleManifestReader proc :ptr, :ptr
    .ends

endif

ifndef __IAppxBundleWriter_INTERFACE_DEFINED__
__IAppxBundleWriter_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBundleWriter:IID

.comdef IAppxBundleWriter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddPayloadPackage	proc :LPCWSTR, :ptr
    Close		proc
    .ends

endif

ifndef __IAppxBundleReader_INTERFACE_DEFINED__
__IAppxBundleReader_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBundleReader:IID

.comdef IAppxBundleReader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFootprintFile	proc :APPX_BUNDLE_FOOTPRINT_FILE_TYPE, :ptr
    GetBlockMap		proc :ptr
    GetManifest		proc :ptr
    GetPayloadPackages	proc :ptr
    GetPayloadPackage	proc :LPCWSTR, :ptr
    .ends

endif

ifndef __IAppxBundleManifestReader_INTERFACE_DEFINED__
__IAppxBundleManifestReader_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBundleManifestReader:IID

.comdef IAppxBundleManifestReader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPackageId	proc :ptr
    GetPackageInfoItems proc :ptr
    GetStream		proc :ptr
    .ends

endif

ifndef __IAppxBundleManifestPackageInfoEnumerator_INTERFACE_DEFINED__
__IAppxBundleManifestPackageInfoEnumerator_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBundleManifestPackageInfoEnumerator:IID

.comdef IAppxBundleManifestPackageInfoEnumerator

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
    .ends

endif

ifndef __IAppxBundleManifestPackageInfo_INTERFACE_DEFINED__
__IAppxBundleManifestPackageInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxBundleManifestPackageInfo:IID

.comdef IAppxBundleManifestPackageInfo

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPackageType	proc :ptr
    GetPackageId	proc :ptr
    GetFileName		proc :ptr
    GetOffset		proc :ptr
    GetSize		proc :ptr
    GetResources	proc :ptr
    .ends

endif

ifndef __IAppxFactory_INTERFACE_DEFINED__
__IAppxFactory_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxFactory:IID

.comdef IAppxFactory

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreatePackageWriter proc :ptr, :ptr, :ptr
    CreatePackageReader proc :ptr, :ptr
    CreateManifestReader proc :ptr, :ptr
    CreateBlockMapReader proc :ptr, :ptr
    CreateValidatedBlockMapReader proc :ptr, :LPCWSTR, :ptr
    .ends

endif

externdef		CLSID_AppxFactory:CLSID
DEFINE_GUID(CLSID_AppxFactory, 0x5842a140, 0xff9f, 0x4166, 0x8f, 0x5c, 0x62, 0xf5, 0xb7, 0xb0, 0xc7, 0x81)
ifdef __cplusplus
DECLSPEC_UUID("5842a140-ff9f-4166-8f5c-62f5b7b0c781")
endif

ifndef __IAppxManifestReader2_INTERFACE_DEFINED__
__IAppxManifestReader2_INTERFACE_DEFINED__ equ 1

externdef		IID_IAppxManifestReader2:IID

.comdef IAppxManifestReader2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPackageId	proc :ptr
    GetProperties	proc :ptr
    GetPackageDependencies proc :ptr
    GetCapabilities	proc :ptr
    GetResources	proc :ptr
    GetDeviceCapabilities proc :ptr
    GetPrerequisite	proc :LPCWSTR, :ptr
    GetApplications	proc :ptr
    GetStream		proc :ptr
    GetQualifiedResources proc :ptr
    .ends

endif

externdef		CLSID_AppxBundleFactory:CLSID

DEFINE_GUID(CLSID_AppxBundleFactory, 0x378E0446, 0x5384, 0x43B7, 0x88, 0x77, 0xE7, 0xDB, 0xDD, 0x88, 0x34, 0x46)
ifdef __cplusplus
DECLSPEC_UUID("378E0446-5384-43B7-8877-E7DBDD883446")
endif
endif ;; __APPXPACKAGING_LIBRARY_DEFINED__

endif ;; (NTDDI GE NTDDI_WIN7)
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
.pragma list(pop)

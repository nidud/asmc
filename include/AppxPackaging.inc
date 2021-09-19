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
.err<this stub requires an updated version of rpcndr.inc>
endif

ifndef __appxpackaging_h__
define __appxpackaging_h__

include oaidl.inc
include ocidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (NTDDI_VERSION GE NTDDI_WIN7)

ifndef __APPXPACKAGING_LIBRARY_DEFINED__
define __APPXPACKAGING_LIBRARY_DEFINED__

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

DX_FEATURE_LEVEL	typedef SDWORD
DX_FEATURE_LEVEL_UNSPECIFIED equ 0
DX_FEATURE_LEVEL_9	equ 1
DX_FEATURE_LEVEL_10	equ 2
DX_FEATURE_LEVEL_11	equ 3

externdef LIBID_APPXPACKAGING:IID

ifndef __IAppxPackageWriter_INTERFACE_DEFINED__
define __IAppxPackageWriter_INTERFACE_DEFINED__

externdef IID_IAppxPackageWriter:IID

.comdef IAppxPackageWriter : public IUnknown

    AddPayloadFile	proc :LPCWSTR, :LPCWSTR, :APPX_COMPRESSION_OPTION, :ptr
    Close		proc :ptr
   .ends

endif

ifndef __IAppxPackageReader_INTERFACE_DEFINED__
define __IAppxPackageReader_INTERFACE_DEFINED__

externdef IID_IAppxPackageReader:IID

.comdef IAppxPackageReader : public IUnknown

    GetBlockMap		proc :ptr
    GetFootprintFile	proc :APPX_FOOTPRINT_FILE_TYPE, :ptr
    GetPayloadFile	proc :LPCWSTR, :ptr
    GetPayloadFiles	proc :ptr
    GetManifest		proc :ptr
   .ends

endif

ifndef __IAppxFile_INTERFACE_DEFINED__
define __IAppxFile_INTERFACE_DEFINED__

externdef IID_IAppxFile:IID

.comdef IAppxFile : public IUnknown

    GetCompressionOption proc :ptr
    GetContentType	proc :ptr
    GetName		proc :ptr
    GetSize		proc :ptr
    GetStream		proc :ptr
   .ends

endif

ifndef __IAppxFilesEnumerator_INTERFACE_DEFINED__
define __IAppxFilesEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxFilesEnumerator:IID

.comdef IAppxFilesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxBlockMapReader_INTERFACE_DEFINED__
define __IAppxBlockMapReader_INTERFACE_DEFINED__

externdef IID_IAppxBlockMapReader:IID

.comdef IAppxBlockMapReader : public IUnknown

    GetFile		proc :LPCWSTR, :ptr
    GetFiles		proc :ptr
    GetHashMethod	proc :ptr
    GetStream		proc :ptr
   .ends

endif

ifndef __IAppxBlockMapFile_INTERFACE_DEFINED__
define __IAppxBlockMapFile_INTERFACE_DEFINED__

externdef IID_IAppxBlockMapFile:IID

.comdef IAppxBlockMapFile : public IUnknown

    GetBlocks		proc :ptr
    GetLocalFileHeaderSize proc :ptr
    GetName		proc :ptr
    GetUncompressedSize proc :ptr
    ValidateFileHash	proc :ptr, :ptr
   .ends

endif

ifndef __IAppxBlockMapFilesEnumerator_INTERFACE_DEFINED__
define __IAppxBlockMapFilesEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxBlockMapFilesEnumerator:IID

.comdef IAppxBlockMapFilesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxBlockMapBlock_INTERFACE_DEFINED__
define __IAppxBlockMapBlock_INTERFACE_DEFINED__

externdef IID_IAppxBlockMapBlock:IID

.comdef IAppxBlockMapBlock : public IUnknown

    GetHash		proc :ptr, :ptr
    GetCompressedSize	proc :ptr
   .ends

endif

ifndef __IAppxBlockMapBlocksEnumerator_INTERFACE_DEFINED__
define __IAppxBlockMapBlocksEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxBlockMapBlocksEnumerator:IID

.comdef IAppxBlockMapBlocksEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestReader_INTERFACE_DEFINED__
define __IAppxManifestReader_INTERFACE_DEFINED__

externdef IID_IAppxManifestReader:IID

.comdef IAppxManifestReader : public IUnknown

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
define __IAppxManifestPackageId_INTERFACE_DEFINED__

externdef IID_IAppxManifestPackageId:IID

.comdef IAppxManifestPackageId : public IUnknown

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
define __IAppxManifestProperties_INTERFACE_DEFINED__

externdef IID_IAppxManifestProperties:IID

.comdef IAppxManifestProperties : public IUnknown

    GetBoolValue	proc :LPCWSTR, :ptr
    GetStringValue	proc :LPCWSTR, :ptr
   .ends

endif

ifndef __IAppxManifestPackageDependency_INTERFACE_DEFINED__
define __IAppxManifestPackageDependency_INTERFACE_DEFINED__

externdef IID_IAppxManifestPackageDependency:IID

.comdef IAppxManifestPackageDependency : public IUnknown

    GetName		proc :ptr
    GetPublisher	proc :ptr
    GetMinVersion	proc :ptr
   .ends

endif

ifndef __IAppxManifestPackageDependenciesEnumerator_INTERFACE_DEFINED__
define __IAppxManifestPackageDependenciesEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxManifestPackageDependenciesEnumerator:IID

.comdef IAppxManifestPackageDependenciesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestResourcesEnumerator_INTERFACE_DEFINED__
define __IAppxManifestResourcesEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxManifestResourcesEnumerator:IID

.comdef IAppxManifestResourcesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestDeviceCapabilitiesEnumerator_INTERFACE_DEFINED__
define __IAppxManifestDeviceCapabilitiesEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxManifestDeviceCapabilitiesEnumerator:IID

.comdef IAppxManifestDeviceCapabilitiesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestApplicationsEnumerator_INTERFACE_DEFINED__
define __IAppxManifestApplicationsEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxManifestApplicationsEnumerator:IID

.comdef IAppxManifestApplicationsEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestApplication_INTERFACE_DEFINED__
define __IAppxManifestApplication_INTERFACE_DEFINED__

externdef IID_IAppxManifestApplication:IID

.comdef IAppxManifestApplication : public IUnknown

    GetStringValue	proc :LPCWSTR, :ptr
    GetAppUserModelId	proc :ptr
   .ends

endif

ifndef __IAppxManifestQualifiedResourcesEnumerator_INTERFACE_DEFINED__
define __IAppxManifestQualifiedResourcesEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxManifestQualifiedResourcesEnumerator:IID

.comdef IAppxManifestQualifiedResourcesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestQualifiedResource_INTERFACE_DEFINED__
define __IAppxManifestQualifiedResource_INTERFACE_DEFINED__

externdef IID_IAppxManifestQualifiedResource:IID

.comdef IAppxManifestQualifiedResource : public IUnknown

    GetLanguage		proc :ptr
    GetScale		proc :ptr
    GetDXFeatureLevel	proc :ptr
   .ends

endif

ifndef __IAppxBundleFactory_INTERFACE_DEFINED__
define __IAppxBundleFactory_INTERFACE_DEFINED__

externdef IID_IAppxBundleFactory:IID

.comdef IAppxBundleFactory : public IUnknown

    CreateBundleWriter	proc :ptr, :UINT64, :ptr
    CreateBundleReader	proc :ptr, :ptr
    CreateBundleManifestReader proc :ptr, :ptr
   .ends

endif

ifndef __IAppxBundleWriter_INTERFACE_DEFINED__
define __IAppxBundleWriter_INTERFACE_DEFINED__

externdef IID_IAppxBundleWriter:IID

.comdef IAppxBundleWriter : public IUnknown

    AddPayloadPackage	proc :LPCWSTR, :ptr
    Close		proc
   .ends

endif

ifndef __IAppxBundleReader_INTERFACE_DEFINED__
define __IAppxBundleReader_INTERFACE_DEFINED__

externdef IID_IAppxBundleReader:IID

.comdef IAppxBundleReader : public IUnknown

    GetFootprintFile	proc :APPX_BUNDLE_FOOTPRINT_FILE_TYPE, :ptr
    GetBlockMap		proc :ptr
    GetManifest		proc :ptr
    GetPayloadPackages	proc :ptr
    GetPayloadPackage	proc :LPCWSTR, :ptr
   .ends

endif

ifndef __IAppxBundleManifestReader_INTERFACE_DEFINED__
define __IAppxBundleManifestReader_INTERFACE_DEFINED__

externdef IID_IAppxBundleManifestReader:IID

.comdef IAppxBundleManifestReader : public IUnknown

    GetPackageId	proc :ptr
    GetPackageInfoItems proc :ptr
    GetStream		proc :ptr
   .ends

endif

ifndef __IAppxBundleManifestPackageInfoEnumerator_INTERFACE_DEFINED__
define __IAppxBundleManifestPackageInfoEnumerator_INTERFACE_DEFINED__

externdef IID_IAppxBundleManifestPackageInfoEnumerator:IID

.comdef IAppxBundleManifestPackageInfoEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxBundleManifestPackageInfo_INTERFACE_DEFINED__
define __IAppxBundleManifestPackageInfo_INTERFACE_DEFINED__

externdef IID_IAppxBundleManifestPackageInfo:IID

.comdef IAppxBundleManifestPackageInfo : public IUnknown

    GetPackageType	proc :ptr
    GetPackageId	proc :ptr
    GetFileName		proc :ptr
    GetOffset		proc :ptr
    GetSize		proc :ptr
    GetResources	proc :ptr
   .ends

endif

ifndef __IAppxFactory_INTERFACE_DEFINED__
define __IAppxFactory_INTERFACE_DEFINED__

externdef IID_IAppxFactory:IID

.comdef IAppxFactory : public IUnknown

    CreatePackageWriter proc :ptr, :ptr, :ptr
    CreatePackageReader proc :ptr, :ptr
    CreateManifestReader proc :ptr, :ptr
    CreateBlockMapReader proc :ptr, :ptr
    CreateValidatedBlockMapReader proc :ptr, :LPCWSTR, :ptr
   .ends

endif

externdef CLSID_AppxFactory:CLSID
DEFINE_GUID(CLSID_AppxFactory, 0x5842a140, 0xff9f, 0x4166, 0x8f, 0x5c, 0x62, 0xf5, 0xb7, 0xb0, 0xc7, 0x81)

ifndef __IAppxManifestReader2_INTERFACE_DEFINED__
define __IAppxManifestReader2_INTERFACE_DEFINED__

externdef IID_IAppxManifestReader2:IID

.comdef IAppxManifestReader2 : public IUnknown

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

externdef CLSID_AppxBundleFactory:CLSID

DEFINE_GUID(CLSID_AppxBundleFactory, 0x378E0446, 0x5384, 0x43B7, 0x88, 0x77, 0xE7, 0xDB, 0xDD, 0x88, 0x34, 0x46)
endif ;; __APPXPACKAGING_LIBRARY_DEFINED__

endif ;; (NTDDI GE NTDDI_WIN7)
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
.pragma list(pop)

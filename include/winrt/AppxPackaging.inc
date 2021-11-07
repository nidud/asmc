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
hashMethod		ptr IUri ?
APPX_PACKAGE_SETTINGS	ENDS

.enum APPX_COMPRESSION_OPTION {
    APPX_COMPRESSION_OPTION_NONE	= 0,
    APPX_COMPRESSION_OPTION_NORMAL	= 1,
    APPX_COMPRESSION_OPTION_MAXIMUM	= 2,
    APPX_COMPRESSION_OPTION_FAST	= 3,
    APPX_COMPRESSION_OPTION_SUPERFAST	= 4
    }

.enum APPX_FOOTPRINT_FILE_TYPE {
    APPX_FOOTPRINT_FILE_TYPE_MANIFEST	= 0,
    APPX_FOOTPRINT_FILE_TYPE_BLOCKMAP	= 1,
    APPX_FOOTPRINT_FILE_TYPE_SIGNATURE	= 2,
    APPX_FOOTPRINT_FILE_TYPE_CODEINTEGRITY = 3
    }

.enum APPX_BUNDLE_FOOTPRINT_FILE_TYPE {
    APPX_BUNDLE_FOOTPRINT_FILE_TYPE_FIRST = 0,
    APPX_BUNDLE_FOOTPRINT_FILE_TYPE_MANIFEST	= 0,
    APPX_BUNDLE_FOOTPRINT_FILE_TYPE_BLOCKMAP	= 1,
    APPX_BUNDLE_FOOTPRINT_FILE_TYPE_SIGNATURE	= 2,
    APPX_BUNDLE_FOOTPRINT_FILE_TYPE_LAST	= 2
    }

.enum APPX_PACKAGE_ARCHITECTURE {
    APPX_PACKAGE_ARCHITECTURE_X86	= 0,
    APPX_PACKAGE_ARCHITECTURE_ARM	= 5,
    APPX_PACKAGE_ARCHITECTURE_X64	= 9,
    APPX_PACKAGE_ARCHITECTURE_NEUTRAL	= 11
    }

.enum APPX_BUNDLE_PAYLOAD_PACKAGE_TYPE {
    APPX_BUNDLE_PAYLOAD_PACKAGE_TYPE_APPLICATION = 0,
    APPX_BUNDLE_PAYLOAD_PACKAGE_TYPE_RESOURCE	 = 1
    }

.enum APPX_CAPABILITIES {
    APPX_CAPABILITY_INTERNET_CLIENT		= 0x1,
    APPX_CAPABILITY_INTERNET_CLIENT_SERVER	= 0x2,
    APPX_CAPABILITY_PRIVATE_NETWORK_CLIENT_SERVER = 0x4,
    APPX_CAPABILITY_DOCUMENTS_LIBRARY		= 0x8,
    APPX_CAPABILITY_PICTURES_LIBRARY		= 0x10,
    APPX_CAPABILITY_VIDEOS_LIBRARY		= 0x20,
    APPX_CAPABILITY_MUSIC_LIBRARY		= 0x40,
    APPX_CAPABILITY_ENTERPRISE_AUTHENTICATION	= 0x80,
    APPX_CAPABILITY_SHARED_USER_CERTIFICATES	= 0x100,
    APPX_CAPABILITY_REMOVABLE_STORAGE		= 0x200,
    APPX_CAPABILITY_APPOINTMENTS		= 0x400,
    APPX_CAPABILITY_CONTACTS			= 0x800
    }

.enum DX_FEATURE_LEVEL {
    DX_FEATURE_LEVEL_UNSPECIFIED = 0,
    DX_FEATURE_LEVEL_9	= 1,
    DX_FEATURE_LEVEL_10 = 2,
    DX_FEATURE_LEVEL_11 = 3
    }

externdef LIBID_APPXPACKAGING:IID

ifndef __IAppxPackageWriter_INTERFACE_DEFINED__
define __IAppxPackageWriter_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxPackageWriter, "9099e33b-246f-41e4-881a-008eb613f858")

.comdef IAppxPackageWriter : public IUnknown

    AddPayloadFile	proc :LPCWSTR, :LPCWSTR, :APPX_COMPRESSION_OPTION, :ptr
    Close		proc :ptr
   .ends

endif

ifndef __IAppxPackageReader_INTERFACE_DEFINED__
define __IAppxPackageReader_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxPackageReader, "b5c49650-99bc-481c-9a34-3d53a4106708")

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

DEFINE_IIDX(IAppxFile, "91df827b-94fd-468f-827b-57f41b2f6f2e")

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

DEFINE_IIDX(IAppxFilesEnumerator, "f007eeaf-9831-411c-9847-917cdc62d1fe")

.comdef IAppxFilesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxBlockMapReader_INTERFACE_DEFINED__
define __IAppxBlockMapReader_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBlockMapReader, "5efec991-bca3-42d1-9ec2-e92d609ec22a")

.comdef IAppxBlockMapReader : public IUnknown

    GetFile		proc :LPCWSTR, :ptr
    GetFiles		proc :ptr
    GetHashMethod	proc :ptr
    GetStream		proc :ptr
   .ends

endif

ifndef __IAppxBlockMapFile_INTERFACE_DEFINED__
define __IAppxBlockMapFile_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBlockMapFile, "277672ac-4f63-42c1-8abc-beae3600eb59")

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

DEFINE_IIDX(IAppxBlockMapFilesEnumerator, "02b856a2-4262-4070-bacb-1a8cbbc42305")

.comdef IAppxBlockMapFilesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxBlockMapBlock_INTERFACE_DEFINED__
define __IAppxBlockMapBlock_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBlockMapBlock, "75cf3930-3244-4fe0-a8c8-e0bcb270b889")

.comdef IAppxBlockMapBlock : public IUnknown

    GetHash		proc :ptr, :ptr
    GetCompressedSize	proc :ptr
   .ends

endif

ifndef __IAppxBlockMapBlocksEnumerator_INTERFACE_DEFINED__
define __IAppxBlockMapBlocksEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBlockMapBlocksEnumerator, "6b429b5b-36ef-479e-b9eb-0c1482b49e16")

.comdef IAppxBlockMapBlocksEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestReader_INTERFACE_DEFINED__
define __IAppxManifestReader_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestReader, "4e1bd148-55a0-4480-a3d1-15544710637c")

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

DEFINE_IIDX(IAppxManifestPackageId, "283ce2d7-7153-4a91-9649-7a0f7240945f")

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

DEFINE_IIDX(IAppxManifestProperties, "03faf64d-f26f-4b2c-aaf7-8fe7789b8bca")

.comdef IAppxManifestProperties : public IUnknown

    GetBoolValue	proc :LPCWSTR, :ptr
    GetStringValue	proc :LPCWSTR, :ptr
   .ends

endif

ifndef __IAppxManifestPackageDependency_INTERFACE_DEFINED__
define __IAppxManifestPackageDependency_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestPackageDependency, "e4946b59-733e-43f0-a724-3bde4c1285a0")

.comdef IAppxManifestPackageDependency : public IUnknown

    GetName		proc :ptr
    GetPublisher	proc :ptr
    GetMinVersion	proc :ptr
   .ends

endif

ifndef __IAppxManifestPackageDependenciesEnumerator_INTERFACE_DEFINED__
define __IAppxManifestPackageDependenciesEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestPackageDependenciesEnumerator, "b43bbcf9-65a6-42dd-bac0-8c6741e7f5a4")

.comdef IAppxManifestPackageDependenciesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestResourcesEnumerator_INTERFACE_DEFINED__
define __IAppxManifestResourcesEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestResourcesEnumerator, "de4dfbbd-881a-48bb-858c-d6f2baeae6ed")

.comdef IAppxManifestResourcesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestDeviceCapabilitiesEnumerator_INTERFACE_DEFINED__
define __IAppxManifestDeviceCapabilitiesEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestDeviceCapabilitiesEnumerator, "30204541-427b-4a1c-bacf-655bf463a540")

.comdef IAppxManifestDeviceCapabilitiesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestApplicationsEnumerator_INTERFACE_DEFINED__
define __IAppxManifestApplicationsEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestApplicationsEnumerator, "9eb8a55a-f04b-4d0d-808d-686185d4847a")

.comdef IAppxManifestApplicationsEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestApplication_INTERFACE_DEFINED__
define __IAppxManifestApplication_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestApplication, "5da89bf4-3773-46be-b650-7e744863b7e8")

.comdef IAppxManifestApplication : public IUnknown

    GetStringValue	proc :LPCWSTR, :ptr
    GetAppUserModelId	proc :ptr
   .ends

endif

ifndef __IAppxManifestQualifiedResourcesEnumerator_INTERFACE_DEFINED__
define __IAppxManifestQualifiedResourcesEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestQualifiedResourcesEnumerator, "8ef6adfe-3762-4a8f-9373-2fc5d444c8d2")

.comdef IAppxManifestQualifiedResourcesEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxManifestQualifiedResource_INTERFACE_DEFINED__
define __IAppxManifestQualifiedResource_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestQualifiedResource, "3b53a497-3c5c-48d1-9ea3-bb7eac8cd7d4")

.comdef IAppxManifestQualifiedResource : public IUnknown

    GetLanguage		proc :ptr
    GetScale		proc :ptr
    GetDXFeatureLevel	proc :ptr
   .ends

endif

ifndef __IAppxBundleFactory_INTERFACE_DEFINED__
define __IAppxBundleFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBundleFactory, "BBA65864-965F-4A5F-855F-F074BDBF3A7B")

.comdef IAppxBundleFactory : public IUnknown

    CreateBundleWriter	proc :ptr, :UINT64, :ptr
    CreateBundleReader	proc :ptr, :ptr
    CreateBundleManifestReader proc :ptr, :ptr
   .ends

endif

ifndef __IAppxBundleWriter_INTERFACE_DEFINED__
define __IAppxBundleWriter_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBundleWriter, "EC446FE8-BFEC-4C64-AB4F-49F038F0C6D2")

.comdef IAppxBundleWriter : public IUnknown

    AddPayloadPackage	proc :LPCWSTR, :ptr
    Close		proc
   .ends

endif

ifndef __IAppxBundleReader_INTERFACE_DEFINED__
define __IAppxBundleReader_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBundleReader, "DD75B8C0-BA76-43B0-AE0F-68656A1DC5C8")

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

DEFINE_IIDX(IAppxBundleManifestReader, "CF0EBBC1-CC99-4106-91EB-E67462E04FB0")

.comdef IAppxBundleManifestReader : public IUnknown

    GetPackageId	proc :ptr
    GetPackageInfoItems proc :ptr
    GetStream		proc :ptr
   .ends

endif

ifndef __IAppxBundleManifestPackageInfoEnumerator_INTERFACE_DEFINED__
define __IAppxBundleManifestPackageInfoEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBundleManifestPackageInfoEnumerator, "F9B856EE-49A6-4E19-B2B0-6A2406D63A32")

.comdef IAppxBundleManifestPackageInfoEnumerator : public IUnknown

    GetCurrent		proc :ptr
    GetHasCurrent	proc :ptr
    MoveNext		proc :ptr
   .ends

endif

ifndef __IAppxBundleManifestPackageInfo_INTERFACE_DEFINED__
define __IAppxBundleManifestPackageInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxBundleManifestPackageInfo, "54CD06C1-268F-40BB-8ED2-757A9EBAEC8D")

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

DEFINE_IIDX(IAppxFactory, "beb94909-e451-438b-b5a7-d79e767b75d8")

.comdef IAppxFactory : public IUnknown

    CreatePackageWriter proc :ptr, :ptr, :ptr
    CreatePackageReader proc :ptr, :ptr
    CreateManifestReader proc :ptr, :ptr
    CreateBlockMapReader proc :ptr, :ptr
    CreateValidatedBlockMapReader proc :ptr, :LPCWSTR, :ptr
   .ends

endif

DEFINE_GUID(CLSID_AppxFactory, 0x5842a140, 0xff9f, 0x4166, 0x8f, 0x5c, 0x62, 0xf5, 0xb7, 0xb0, 0xc7, 0x81)

ifndef __IAppxManifestReader2_INTERFACE_DEFINED__
define __IAppxManifestReader2_INTERFACE_DEFINED__

DEFINE_IIDX(IAppxManifestReader2, "d06f67bc-b31d-4eba-a8af-638e73e77b4d")

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

DEFINE_GUID(CLSID_AppxBundleFactory, 0x378E0446, 0x5384, 0x43B7, 0x88, 0x77, 0xE7, 0xDB, 0xDD, 0x88, 0x34, 0x46)

endif ;; __APPXPACKAGING_LIBRARY_DEFINED__
endif ;; (NTDDI GE NTDDI_WIN7)
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
.pragma list(pop)

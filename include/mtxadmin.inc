include rpc.inc
include rpcndr.inc
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __mtxadmin_h__
define __mtxadmin_h__
ifndef __unknwn_h__
include unknwn.inc
endif
ifndef __oaidl_h__
include oaidl.inc
endif
include objbase.inc

ifndef __ICatalog_INTERFACE_DEFINED__
define __ICatalog_INTERFACE_DEFINED__

DEFINE_IIDX(ICatalog, "6eb22870-8a19-11d0-81b6-00a0c9231c29")

.comdef ICatalog : public IDispatch
    GetCollection	proc :BSTR, :ptr
    Connect		proc :BSTR, :ptr
    get_MajorVersion	proc :ptr
    get_MinorVersion	proc :ptr
   .ends

endif

ifndef __ICatalogObject_INTERFACE_DEFINED__
define __ICatalogObject_INTERFACE_DEFINED__

DEFINE_IIDX(ICatalogObject, "6eb22871-8a19-11d0-81b6-00a0c9231c29")

.comdef ICatalogObject : public IDispatch
    get_Value		proc :BSTR, :ptr
    put_Value		proc :BSTR, :VARIANT
    get_Key		proc :ptr
    get_Name		proc :ptr
    IsPropertyReadOnly	proc :BSTR, :ptr
    get_Valid		proc :ptr
    IsPropertyWriteOnly proc :BSTR, :ptr
   .ends

endif

ifndef __ICatalogCollection_INTERFACE_DEFINED__
define __ICatalogCollection_INTERFACE_DEFINED__

DEFINE_IIDX(ICatalogCollection, "6eb22872-8a19-11d0-81b6-00a0c9231c29")

.comdef ICatalogCollection : public IDispatch
    get__NewEnum	proc :ptr
    get_Item		proc :LONG, :ptr
    get_Count		proc :ptr
    Remove		proc :LONG
    _Add		proc :ptr
    Populate		proc
    SaveChanges		proc :ptr
    GetCollection	proc :BSTR, :VARIANT, :ptr
    get_Name		proc :ptr
    get_AddEnabled	proc :ptr
    get_RemoveEnabled	proc :ptr
    GetUtilInterface	proc :ptr
    get_DataStoreMajorVersion proc :ptr
    get_DataStoreMinorVersion proc :ptr
    PopulateByKey	proc :ptr
    PopulateByQuery	proc :BSTR, :LONG
   .ends

endif

ifndef __IComponentUtil_INTERFACE_DEFINED__
define __IComponentUtil_INTERFACE_DEFINED__

DEFINE_IIDX(IComponentUtil, "6eb22873-8a19-11d0-81b6-00a0c9231c29")

.comdef IComponentUtil : public IDispatch
    InstallComponent	proc :BSTR, :BSTR, :BSTR
    ImportComponent	proc :BSTR
    ImportComponentByName proc :BSTR
    GetCLSIDs		proc :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __IPackageUtil_INTERFACE_DEFINED__
define __IPackageUtil_INTERFACE_DEFINED__

DEFINE_IIDX(IPackageUtil, "6eb22874-8a19-11d0-81b6-00a0c9231c29")

.comdef IPackageUtil : public IDispatch
    InstallPackage	proc :BSTR, :BSTR, :LONG
    ExportPackage	proc :BSTR, :BSTR, :LONG
    ShutdownPackage	proc :BSTR
   .ends

endif

ifndef __IRemoteComponentUtil_INTERFACE_DEFINED__
define __IRemoteComponentUtil_INTERFACE_DEFINED__

DEFINE_IIDX(IRemoteComponentUtil, "6eb22875-8a19-11d0-81b6-00a0c9231c29")

.comdef IRemoteComponentUtil : public IDispatch
    InstallRemoteComponent proc :BSTR, :BSTR, :BSTR
    InstallRemoteComponentByName proc :BSTR, :BSTR, :BSTR
   .ends

endif

ifndef __IRoleAssociationUtil_INTERFACE_DEFINED__
define __IRoleAssociationUtil_INTERFACE_DEFINED__

DEFINE_IIDX(IRoleAssociationUtil, "6eb22876-8a19-11d0-81b6-00a0c9231c29")

.comdef IRoleAssociationUtil : public IDispatch
    AssociateRole	proc :BSTR
    AssociateRoleByName proc :BSTR
   .ends

endif

ifndef __MTSAdmin_LIBRARY_DEFINED__
define __MTSAdmin_LIBRARY_DEFINED__

.enum MTSPackageInstallOptions {
	mtsInstallUsers = 1
	}

.enum MTSPackageExportOptions {
	mtsExportUsers	= 1
	}

.enum MTSAdminErrorCodes {
	mtsErrObjectInvalid		= 0x80110402,
	mtsErrKeyMissing		= 0x80110403,
	mtsErrAlreadyInstalled		= 0x80110404,
	mtsErrDownloadFailed		= 0x80110405,
	mtsErrPDFWriteFail		= 0x80110407,
	mtsErrPDFReadFail		= 0x80110408,
	mtsErrPDFVersion		= 0x80110409,
	mtsErrCoReqCompInstalled	= 0x80110410,
	mtsErrBadPath			= 0x8011040a,
	mtsErrPackageExists		= 0x8011040b,
	mtsErrRoleExists		= 0x8011040c,
	mtsErrCantCopyFile		= 0x8011040d,
	mtsErrNoTypeLib			= 0x8011040e,
	mtsErrNoUser			= 0x8011040f,
	mtsErrInvalidUserids		= 0x80110410,
	mtsErrNoRegistryCLSID		= 0x80110411,
	mtsErrBadRegistryProgID		= 0x80110412,
	mtsErrAuthenticationLevel	= 0x80110413,
	mtsErrUserPasswdNotValid	= 0x80110414,
	mtsErrNoRegistryRead		= 0x80110415,
	mtsErrNoRegistryWrite		= 0x80110416,
	mtsErrNoRegistryRepair		= 0x80110417,
	mtsErrCLSIDOrIIDMismatch	= 0x80110418,
	mtsErrRemoteInterface		= 0x80110419,
	mtsErrDllRegisterServer		= 0x8011041a,
	mtsErrNoServerShare		= 0x8011041b,
	mtsErrNoAccessToUNC		= 0x8011041c,
	mtsErrDllLoadFailed		= 0x8011041d,
	mtsErrBadRegistryLibID		= 0x8011041e,
	mtsErrPackDirNotFound		= 0x8011041f,
	mtsErrTreatAs			= 0x80110420,
	mtsErrBadForward		= 0x80110421,
	mtsErrBadIID			= 0x80110422,
	mtsErrRegistrarFailed		= 0x80110423,
	mtsErrCompFileDoesNotExist	= 0x80110424,
	mtsErrCompFileLoadDLLFail	= 0x80110425,
	mtsErrCompFileGetClassObj	= 0x80110426,
	mtsErrCompFileClassNotAvail	= 0x80110427,
	mtsErrCompFileBadTLB		= 0x80110428,
	mtsErrCompFileNotInstallable	= 0x80110429,
	mtsErrNotChangeable		= 0x8011042a,
	mtsErrNotDeletable		= 0x8011042b,
	mtsErrSession			= 0x8011042c,
	mtsErrCompFileNoRegistrar	= 0x80110434
    }

define E_MTS_OBJECTERRORS		mtsErrObjectErrors
define E_MTS_OBJECTINVALID		mtsErrObjectInvalid
define E_MTS_KEYMISSING			mtsErrKeyMissing
define E_MTS_ALREADYINSTALLED		mtsErrAlreadyInstalled
define E_MTS_DOWNLOADFAILED		mtsErrDownloadFailed
define E_MTS_PDFWRITEFAIL		mtsErrPDFWriteFail
define E_MTS_PDFREADFAIL		mtsErrPDFReadFail
define E_MTS_PDFVERSION			mtsErrPDFVersion
define E_MTS_COREQCOMPINSTALLED		mtsErrCoReqCompInstalled
define E_MTS_BADPATH			mtsErrBadPath
define E_MTS_PACKAGEEXISTS		mtsErrPackageExists
define E_MTS_ROLEEXISTS			mtsErrRoleExists
define E_MTS_CANTCOPYFILE		mtsErrCantCopyFile
define E_MTS_NOTYPELIB			mtsErrNoTypeLib
define E_MTS_NOUSER			mtsErrNoUser
define E_MTS_INVALIDUSERIDS		mtsErrInvalidUserids
define E_MTS_NOREGISTRYCLSID		mtsErrNoRegistryCLSID
define E_MTS_BADREGISTRYPROGID		mtsErrBadRegistryProgID
define E_MTS_AUTHENTICATIONLEVEL	mtsErrAuthenticationLevel
define E_MTS_USERPASSWDNOTVALID		mtsErrUserPasswdNotValid
define E_MTS_NOREGISTRYREAD		mtsErrNoRegistryRead
define E_MTS_NOREGISTRYWRITE		mtsErrNoRegistryWrite
define E_MTS_NOREGISTRYREPAIR		mtsErrNoRegistryRepair
define E_MTS_CLSIDORIIDMISMATCH		mtsErrCLSIDOrIIDMismatch
define E_MTS_REMOTEINTERFACE		mtsErrRemoteInterface
define E_MTS_DLLREGISTERSERVER		mtsErrDllRegisterServer
define E_MTS_NOSERVERSHARE		mtsErrNoServerShare
define E_MTS_NOACCESSTOUNC		mtsErrNoAccessToUNC
define E_MTS_DLLLOADFAILED		mtsErrDllLoadFailed
define E_MTS_BADREGISTRYLIBID		mtsErrBadRegistryLibID
define E_MTS_PACKDIRNOTFOUND		mtsErrPackDirNotFound
define E_MTS_TREATAS			mtsErrTreatAs
define E_MTS_BADFORWARD			mtsErrBadForward
define E_MTS_BADIID			mtsErrBadIID
define E_MTS_REGISTRARFAILED		mtsErrRegistrarFailed
define E_MTS_COMPFILE_DOESNOTEXIST	mtsErrCompFileDoesNotExist
define E_MTS_COMPFILE_LOADDLLFAIL	mtsErrCompFileLoadDLLFail
define E_MTS_COMPFILE_GETCLASSOBJ	mtsErrCompFileGetClassObj
define E_MTS_COMPFILE_CLASSNOTAVAIL	mtsErrCompFileClassNotAvail
define E_MTS_COMPFILE_BADTLB		mtsErrCompFileBadTLB
define E_MTS_COMPFILE_NOTINSTALLABLE	mtsErrCompFileNotInstallable
define E_MTS_NOTCHANGEABLE		mtsErrNotChangeable
define E_MTS_NOTDELETEABLE		mtsErrNotDeleteable
define E_MTS_SESSION			mtsErrSession
define E_MTS_COMPFILE_NOREGISTRAR	mtsErrCompFileNoRegistrar

DEFINE_GUID(LIBID_MTSAdmin, 0x6eb22880,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)
DEFINE_GUID(CLSID_Catalog, 0x6eb22881,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)
DEFINE_GUID(CLSID_CatalogObject, 0x6eb22882,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)
DEFINE_GUID(CLSID_CatalogCollection, 0x6eb22883,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)
DEFINE_GUID(CLSID_ComponentUtil, 0x6eb22884,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)
DEFINE_GUID(CLSID_PackageUtil, 0x6eb22885,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)
DEFINE_GUID(CLSID_RemoteComponentUtil, 0x6eb22886,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)
DEFINE_GUID(CLSID_RoleAssociationUtil, 0x6eb22887,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)

endif

endif

ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __mtsadmin_h__
define __mtsadmin_h__
ifndef __unknwn_h__
include unknwn.inc
endif
include comadmin.inc
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

.enum __MIDL___MIDL_itf_mtsadmin_0123_0003 {
	mtsErrObjectInvalid		= 0x80110402,
	mtsErrKeyMissing		= 0x80110403,
	mtsErrAlreadyInstalled		= 0x80110404,
	mtsErrDownloadFailed		= 0x80110405,
	mtsErrPDFWriteFail		= 0x80110407,
	mtsErrPDFReadFail		= 0x80110408,
	mtsErrPDFVersion		= 0x80110409,
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
	mtsErrCompMoveLocked		= 0x8011042d,
	mtsErrCompMoveBadDest		= 0x8011042e,
	mtsErrRegisterTLB		= 0x80110430,
	mtsErrSystemPack		= 0x80110433,
	mtsErrCompFileNoRegistrar	= 0x80110434,
	mtsErrCoReqCompInstalled	= 0x80110435,
	mtsErrPropSaveFailed		= 0x80110437,
	mtsErrObjectExists		= 0x80110438,
	mtsErrRegFileCorrupt		= 0x8011043b,
	mtsErrPropertyOverflow		= 0x8011043c,
	mtsErrNotInRegistry		= 0x8011043e,
	mtsErrApplidMatchesClsid	= 0x80110446,
	mtsErrRoleDoesNotExist		= 0x80110447,
	mtsErrObjectParentMissing	= 0x80110808,
	mtsErrObjectDoesNotExist	= 0x80110809,
	mtsErrCanNotExportAppProxy	= 0x8011044a,
	mtsErrCanNotExportSystemPack	= 0x8011044c
	}

define E_MTS_OBJECTERRORS		mtsErrObjectErrors
define E_MTS_OBJECTINVALID		mtsErrObjectInvalid
define E_MTS_KEYMISSING			mtsErrKeyMissing
define E_MTS_ALREADYINSTALLED		mtsErrAlreadyInstalled
define E_MTS_DOWNLOADFAILED		mtsErrDownloadFailed
define E_MTS_PDFWRITEFAIL		mtsErrPDFWriteFail
define E_MTS_PDFREADFAIL		mtsErrPDFReadFail
define E_MTS_PDFVERSION			mtsErrPDFVersion
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
define E_MTS_NOTDELETEABLE		mtsErrNotDeletable
define E_MTS_SESSION			mtsErrSession
define E_MTS_COMP_MOVE_LOCKED		mtsErrCompMoveLocked
define E_MTS_COMP_MOVE_BAD_DEST		mtsErrCompMoveBadDest
define E_MTS_REGISTERTLB		mtsErrRegisterTLB
define E_MTS_SYSTEMPACK			mtsErrSystemPack
define E_MTS_COMPFILE_NOREGISTRAR	mtsErrCompFileNoRegistrar
define E_MTS_COREQCOMPINSTALLED		mtsErrCoReqCompInstalled
define E_MTS_PROPERTYSAVEFAILED		mtsErrPropSaveFailed
define E_MTS_OBJECTEXISTS		mtsErrObjectExists
define E_MTS_REGFILE_CORRUPT		mtsErrRegFileCorrupt
define E_MTS_PROPERTY_OVERFLOW		mtsErrPropertyOverflow
define E_MTS_NOTINREGISTRY		mtsErrNotInRegistry
define E_MTS_APPLID_MATCHES_CLSID	mtsErrApplidMatchesClsid
define E_MTS_ROLE_DOES_NOT_EXIST	mtsErrRoleDoesNotExist
define E_MTS_OBJECT_PARENT_MISSING	mtsErrObjectParentMissing
define E_MTS_OBJECT_DOES_NOT_EXIST	mtsErrObjectDoesNotExist
define E_MTS_CAN_NOT_EXPORT_APP_PROXY	mtsErrCanNotExportAppProxy
define E_MTS_CAN_NOT_EXPORT_SYSTEM_PACK mtsErrCanNotExportSystemPack

DEFINE_GUID(LIBID_MTSAdmin, 0x6eb22880,0x8a19,0x11d0,0x81,0xb6,0x00,0xa0,0xc9,0x23,0x1c,0x29)

DEFINE_GUIDS(CLSID_Catalog, "6eb22881-8a19-11d0-81b6-00a0c9231c29")
DEFINE_GUIDS(CLSID_CatalogObject, "6eb22882-8a19-11d0-81b6-00a0c9231c29")
DEFINE_GUIDS(CLSID_CatalogCollection, "6eb22883-8a19-11d0-81b6-00a0c9231c29")
DEFINE_GUIDS(CLSID_ComponentUtil, "6eb22884-8a19-11d0-81b6-00a0c9231c29")
DEFINE_GUIDS(CLSID_PackageUtil, "6eb22885-8a19-11d0-81b6-00a0c9231c29")
DEFINE_GUIDS(CLSID_RemoteComponentUtil, "6eb22886-8a19-11d0-81b6-00a0c9231c29")
DEFINE_GUIDS(CLSID_RoleAssociationUtil, "6eb22887-8a19-11d0-81b6-00a0c9231c29")

endif

endif

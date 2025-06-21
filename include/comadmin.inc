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

ifndef __comadmin_h__
define __comadmin_h__

include unknwn.inc
include oaidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include objbase.inc

ifndef __ICOMAdminCatalog_INTERFACE_DEFINED__
define __ICOMAdminCatalog_INTERFACE_DEFINED__

DEFINE_IIDX(ICOMAdminCatalog, "DD662187-DFC2-11d1-A2CF-00805FC79235")

.comdef ICOMAdminCatalog : public IDispatch

    GetCollection	proc :BSTR, :ptr
    Connect		proc :BSTR, :ptr
    get_MajorVersion	proc :ptr
    get_MinorVersion	proc :ptr
    GetCollectionByQuery proc :BSTR, :ptr, :ptr
    ImportComponent	proc :BSTR, :BSTR
    InstallComponent	proc :BSTR, :BSTR, :BSTR, :BSTR
    ShutdownApplication proc :BSTR
    ExportApplication	proc :BSTR, :BSTR, :LONG
    InstallApplication	proc :BSTR, :BSTR, :LONG, :BSTR, :BSTR, :BSTR
    StopRouter		proc
    RefreshRouter	proc
    StartRouter		proc
    Reserved1		proc
    Reserved2		proc
    InstallMultipleComponents proc :BSTR, :ptr, :ptr
    GetMultipleComponentsInfo proc :BSTR, :ptr, :ptr, :ptr, :ptr, :ptr
    RefreshComponents	proc
    BackupREGDB		proc :BSTR
    RestoreREGDB	proc :BSTR
    QueryApplicationFile proc :BSTR, :ptr, :ptr, :ptr, :ptr, :ptr
    StartApplication	proc :BSTR
    ServiceCheck	proc :LONG, :ptr
    InstallMultipleEventClasses proc :BSTR, :ptr, :ptr
    InstallEventClass	proc :BSTR, :BSTR, :BSTR, :BSTR
    GetEventClassesForIID proc :BSTR, :ptr, :ptr, :ptr
   .ends

endif

.enum COMAdminInUse {
    COMAdminNotInUse	= 0,
    COMAdminInUseByCatalog	= 0x1,
    COMAdminInUseByRegistryUnknown	= 0x2,
    COMAdminInUseByRegistryProxyStub	= 0x3,
    COMAdminInUseByRegistryTypeLib	= 0x4,
    COMAdminInUseByRegistryClsid	= 0x5
    }

ifndef __ICOMAdminCatalog2_INTERFACE_DEFINED__
define __ICOMAdminCatalog2_INTERFACE_DEFINED__

DEFINE_IIDX(ICOMAdminCatalog2, "790C6E0B-9194-4cc9-9426-A48A63185696")

.comdef ICOMAdminCatalog2 : public ICOMAdminCatalog

    GetCollectionByQuery2 proc :BSTR, :ptr, :ptr
    GetApplicationInstanceIDFromProcessID proc :LONG, :ptr
    ShutdownApplicationInstances proc :ptr
    PauseApplicationInstances proc :ptr
    ResumeApplicationInstances proc :ptr
    RecycleApplicationInstances proc :ptr, :LONG
    AreApplicationInstancesPaused proc :ptr, :ptr
    DumpApplicationInstance proc :BSTR, :BSTR, :LONG, :ptr
    get_IsApplicationInstanceDumpSupported proc :ptr
    CreateServiceForApplication proc :BSTR, :BSTR, :BSTR, :BSTR, :BSTR, :BSTR, :BSTR, :VARIANT_BOOL
    DeleteServiceForApplication proc :BSTR
    GetPartitionID	proc :BSTR, :ptr
    GetPartitionName	proc :BSTR, :ptr
    put_CurrentPartition proc :BSTR
    get_CurrentPartitionID proc :ptr
    get_CurrentPartitionName proc :ptr
    get_GlobalPartitionID proc :ptr
    FlushPartitionCache proc
    CopyApplications	proc :BSTR, :ptr, :BSTR
    CopyComponents	proc :BSTR, :ptr, :BSTR
    MoveComponents	proc :BSTR, :ptr, :BSTR
    AliasComponent	proc :BSTR, :BSTR, :BSTR, :BSTR, :BSTR
    IsSafeToDelete	proc :BSTR, :ptr
    ImportUnconfiguredComponents proc :BSTR, :ptr, :ptr
    PromoteUnconfiguredComponents proc :BSTR, :ptr, :ptr
    ImportComponents	proc :BSTR, :ptr, :ptr
    get_Is64BitCatalogServer proc :ptr
    ExportPartition	proc :BSTR, :BSTR, :LONG
    InstallPartition	proc :BSTR, :BSTR, :LONG, :BSTR, :BSTR, :BSTR
    QueryApplicationFile2 proc :BSTR, :ptr
    GetComponentVersionCount proc :BSTR, :ptr
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

ifndef __COMAdmin_LIBRARY_DEFINED__
define __COMAdmin_LIBRARY_DEFINED__

.enum COMAdminComponentType {
    COMAdmin32BitComponent	= 0x1,
    COMAdmin64BitComponent	= 0x2
    }

.enum COMAdminApplicationInstallOptions {
    COMAdminInstallNoUsers	= 0,
    COMAdminInstallUsers	= 1,
    COMAdminInstallForceOverwriteOfFiles	= 2
    }

.enum COMAdminApplicationExportOptions {
    COMAdminExportNoUsers	= 0,
    COMAdminExportUsers = 1,
    COMAdminExportApplicationProxy	= 2,
    COMAdminExportForceOverwriteOfFiles = 4,
    COMAdminExportIn10Format	= 16
    }

.enum COMAdminThreadingModels {
    COMAdminThreadingModelApartment	= 0,
    COMAdminThreadingModelFree	= 1,
    COMAdminThreadingModelMain	= 2,
    COMAdminThreadingModelBoth	= 3,
    COMAdminThreadingModelNeutral	= 4,
    COMAdminThreadingModelNotSpecified	= 5
    }

.enum COMAdminTransactionOptions {
    COMAdminTransactionIgnored	= 0,
    COMAdminTransactionNone	= 1,
    COMAdminTransactionSupported	= 2,
    COMAdminTransactionRequired = 3,
    COMAdminTransactionRequiresNew	= 4
    }

.enum COMAdminTxIsolationLevelOptions {
    COMAdminTxIsolationLevelAny = 0,
    COMAdminTxIsolationLevelReadUnCommitted	= ( COMAdminTxIsolationLevelAny + 1 ) ,
    COMAdminTxIsolationLevelReadCommitted	= ( COMAdminTxIsolationLevelReadUnCommitted + 1 ) ,
    COMAdminTxIsolationLevelRepeatableRead	= ( COMAdminTxIsolationLevelReadCommitted + 1 ) ,
    COMAdminTxIsolationLevelSerializable	= ( COMAdminTxIsolationLevelRepeatableRead + 1 )
    }

.enum COMAdminSynchronizationOptions {
    COMAdminSynchronizationIgnored	= 0,
    COMAdminSynchronizationNone = 1,
    COMAdminSynchronizationSupported	= 2,
    COMAdminSynchronizationRequired	= 3,
    COMAdminSynchronizationRequiresNew	= 4
    }

.enum COMAdminActivationOptions {
    COMAdminActivationInproc	= 0,
    COMAdminActivationLocal	= 1
    }

.enum COMAdminAccessChecksLevelOptions {
    COMAdminAccessChecksApplicationLevel	= 0,
    COMAdminAccessChecksApplicationComponentLevel	= 1
    }

.enum COMAdminAuthenticationLevelOptions {
    COMAdminAuthenticationDefault	= 0,
    COMAdminAuthenticationNone	= 1,
    COMAdminAuthenticationConnect	= 2,
    COMAdminAuthenticationCall	= 3,
    COMAdminAuthenticationPacket	= 4,
    COMAdminAuthenticationIntegrity	= 5,
    COMAdminAuthenticationPrivacy	= 6
    }

.enum COMAdminImpersonationLevelOptions {
    COMAdminImpersonationAnonymous	= 1,
    COMAdminImpersonationIdentify	= 2,
    COMAdminImpersonationImpersonate	= 3,
    COMAdminImpersonationDelegate	= 4
    }

.enum COMAdminAuthenticationCapabilitiesOptions {
    COMAdminAuthenticationCapabilitiesNone	= 0,
    COMAdminAuthenticationCapabilitiesSecureReference	= 0x2,
    COMAdminAuthenticationCapabilitiesStaticCloaking	= 0x20,
    COMAdminAuthenticationCapabilitiesDynamicCloaking	= 0x40
    }

.enum COMAdminOS {
    COMAdminOSNotInitialized	= 0,
    COMAdminOSWindows3_1	= 1,
    COMAdminOSWindows9x = 2,
    COMAdminOSWindows2000	= 3,
    COMAdminOSWindows2000AdvancedServer = 4,
    COMAdminOSWindows2000Unknown	= 5,
    COMAdminOSUnknown	= 6,
    COMAdminOSWindowsXPPersonal = 11,
    COMAdminOSWindowsXPProfessional	= 12,
    COMAdminOSWindowsNETStandardServer	= 13,
    COMAdminOSWindowsNETEnterpriseServer	= 14,
    COMAdminOSWindowsNETDatacenterServer	= 15,
    COMAdminOSWindowsNETWebServer	= 16,
    COMAdminOSWindowsLonghornPersonal	= 17,
    COMAdminOSWindowsLonghornProfessional	= 18,
    COMAdminOSWindowsLonghornStandardServer	= 19,
    COMAdminOSWindowsLonghornEnterpriseServer	= 20,
    COMAdminOSWindowsLonghornDatacenterServer	= 21,
    COMAdminOSWindowsLonghornWebServer	= 22,
    COMAdminOSWindows7Personal	= 23,
    COMAdminOSWindows7Professional	= 24,
    COMAdminOSWindows7StandardServer	= 25,
    COMAdminOSWindows7EnterpriseServer	= 26,
    COMAdminOSWindows7DatacenterServer	= 27,
    COMAdminOSWindows7WebServer = 28,
    COMAdminOSWindows8Personal	= 29,
    COMAdminOSWindows8Professional	= 30,
    COMAdminOSWindows8StandardServer	= 31,
    COMAdminOSWindows8EnterpriseServer	= 32,
    COMAdminOSWindows8DatacenterServer	= 33,
    COMAdminOSWindows8WebServer = 34,
    COMAdminOSWindowsBluePersonal	= 35,
    COMAdminOSWindowsBlueProfessional	= 36,
    COMAdminOSWindowsBlueStandardServer = 37,
    COMAdminOSWindowsBlueEnterpriseServer	= 38,
    COMAdminOSWindowsBlueDatacenterServer	= 39,
    COMAdminOSWindowsBlueWebServer	= 40
    }

.enum COMAdminServiceOptions {
    COMAdminServiceLoadBalanceRouter	= 1
    }

.enum COMAdminServiceStatusOptions {
    COMAdminServiceStopped	= 0,
    COMAdminServiceStartPending = ( COMAdminServiceStopped + 1 ),
    COMAdminServiceStopPending	= ( COMAdminServiceStartPending + 1 ),
    COMAdminServiceRunning	= ( COMAdminServiceStopPending + 1 ),
    COMAdminServiceContinuePending	= ( COMAdminServiceRunning + 1 ),
    COMAdminServicePausePending = ( COMAdminServiceContinuePending + 1 ),
    COMAdminServicePaused	= ( COMAdminServicePausePending + 1 ),
    COMAdminServiceUnknownState = ( COMAdminServicePaused + 1 )
    }

.enum COMAdminQCMessageAuthenticateOptions {
    COMAdminQCMessageAuthenticateSecureApps	= 0,
    COMAdminQCMessageAuthenticateOff	= 1,
    COMAdminQCMessageAuthenticateOn	= 2
    }

.enum COMAdminFileFlags {
    COMAdminFileFlagLoadable	= 0x1,
    COMAdminFileFlagCOM = 0x2,
    COMAdminFileFlagContainsPS	= 0x4,
    COMAdminFileFlagContainsComp	= 0x8,
    COMAdminFileFlagContainsTLB = 0x10,
    COMAdminFileFlagSelfReg	= 0x20,
    COMAdminFileFlagSelfUnReg	= 0x40,
    COMAdminFileFlagUnloadableDLL	= 0x80,
    COMAdminFileFlagDoesNotExist	= 0x100,
    COMAdminFileFlagAlreadyInstalled	= 0x200,
    COMAdminFileFlagBadTLB	= 0x400,
    COMAdminFileFlagGetClassObjFailed	= 0x800,
    COMAdminFileFlagClassNotAvailable	= 0x1000,
    COMAdminFileFlagRegistrar	= 0x2000,
    COMAdminFileFlagNoRegistrar = 0x4000,
    COMAdminFileFlagDLLRegsvrFailed	= 0x8000,
    COMAdminFileFlagRegTLBFailed	= 0x10000,
    COMAdminFileFlagRegistrarFailed	= 0x20000,
    COMAdminFileFlagError	= 0x40000
    }

.enum COMAdminComponentFlags {
    COMAdminCompFlagTypeInfoFound	= 0x1,
    COMAdminCompFlagCOMPlusPropertiesFound	= 0x2,
    COMAdminCompFlagProxyFound		= 0x4,
    COMAdminCompFlagInterfacesFound	= 0x8,
    COMAdminCompFlagAlreadyInstalled	= 0x10,
    COMAdminCompFlagNotInApplication	= 0x20
    }

COMAdminCollectionRoot	equ <"Root">
COMAdminCollectionApplications equ <"Applications">
COMAdminCollectionComponents equ <"Components">
COMAdminCollectionComputerList equ <"ComputerList">
COMAdminCollectionApplicationCluster equ <"ApplicationCluster">
COMAdminCollectionLocalComputer equ <"LocalComputer">
COMAdminCollectionInprocServers equ <"InprocServers">
COMAdminCollectionRelatedCollectionInfo equ <"RelatedCollectionInfo">
COMAdminCollectionPropertyInfo equ <"PropertyInfo">
COMAdminCollectionRoles equ <"Roles">
COMAdminCollectionErrorInfo equ <"ErrorInfo">
COMAdminCollectionInterfacesForComponent equ <"InterfacesForComponent">
COMAdminCollectionRolesForComponent equ <"RolesForComponent">
COMAdminCollectionMethodsForInterface equ <"MethodsForInterface">
COMAdminCollectionRolesForInterface equ <"RolesForInterface">
COMAdminCollectionRolesForMethod equ <"RolesForMethod">
COMAdminCollectionUsersInRole equ <"UsersInRole">
COMAdminCollectionDCOMProtocols equ <"DCOMProtocols">
COMAdminCollectionPartitions equ <"Partitions">

.enum COMAdminErrorCodes {
    COMAdminErrObjectErrors	= 0x80110401,
    COMAdminErrObjectInvalid	= 0x80110402,
    COMAdminErrKeyMissing	= 0x80110403,
    COMAdminErrAlreadyInstalled = 0x80110404,
    COMAdminErrAppFileWriteFail = 0x80110407,
    COMAdminErrAppFileReadFail	= 0x80110408,
    COMAdminErrAppFileVersion	= 0x80110409,
    COMAdminErrBadPath		= 0x8011040a,
    COMAdminErrApplicationExists	= 0x8011040b,
    COMAdminErrRoleExists	= 0x8011040c,
    COMAdminErrCantCopyFile	= 0x8011040d,
    COMAdminErrNoUser		= 0x8011040f,
    COMAdminErrInvalidUserids	= 0x80110410,
    COMAdminErrNoRegistryCLSID	= 0x80110411,
    COMAdminErrBadRegistryProgID	= 0x80110412,
    COMAdminErrAuthenticationLevel	= 0x80110413,
    COMAdminErrUserPasswdNotValid	= 0x80110414,
    COMAdminErrCLSIDOrIIDMismatch	= 0x80110418,
    COMAdminErrRemoteInterface	= 0x80110419,
    COMAdminErrDllRegisterServer	= 0x8011041a,
    COMAdminErrNoServerShare	= 0x8011041b,
    COMAdminErrDllLoadFailed	= 0x8011041d,
    COMAdminErrBadRegistryLibID = 0x8011041e,
    COMAdminErrAppDirNotFound	= 0x8011041f,
    COMAdminErrRegistrarFailed	= 0x80110423,
    COMAdminErrCompFileDoesNotExist	= 0x80110424,
    COMAdminErrCompFileLoadDLLFail	= 0x80110425,
    COMAdminErrCompFileGetClassObj	= 0x80110426,
    COMAdminErrCompFileClassNotAvail	= 0x80110427,
    COMAdminErrCompFileBadTLB	= 0x80110428,
    COMAdminErrCompFileNotInstallable	= 0x80110429,
    COMAdminErrNotChangeable	= 0x8011042a,
    COMAdminErrNotDeletable	= 0x8011042b,
    COMAdminErrSession		= 0x8011042c,
    COMAdminErrCompMoveLocked	= 0x8011042d,
    COMAdminErrCompMoveBadDest	= 0x8011042e,
    COMAdminErrRegisterTLB	= 0x80110430,
    COMAdminErrSystemApp	= 0x80110433,
    COMAdminErrCompFileNoRegistrar	= 0x80110434,
    COMAdminErrCoReqCompInstalled	= 0x80110435,
    COMAdminErrServiceNotInstalled	= 0x80110436,
    COMAdminErrPropertySaveFailed	= 0x80110437,
    COMAdminErrObjectExists	= 0x80110438,
    COMAdminErrComponentExists	= 0x80110439,
    COMAdminErrRegFileCorrupt	= 0x8011043b,
    COMAdminErrPropertyOverflow = 0x8011043c,
    COMAdminErrNotInRegistry	= 0x8011043e,
    COMAdminErrObjectNotPoolable	= 0x8011043f,
    COMAdminErrApplidMatchesClsid	= 0x80110446,
    COMAdminErrRoleDoesNotExist = 0x80110447,
    COMAdminErrStartAppNeedsComponents	= 0x80110448,
    COMAdminErrRequiresDifferentPlatform	= 0x80110449,
    COMAdminErrQueuingServiceNotAvailable	= 0x80110602,
    COMAdminErrObjectParentMissing	= 0x80110808,
    COMAdminErrObjectDoesNotExist	= 0x80110809,
    COMAdminErrCanNotExportAppProxy	= 0x8011044a,
    COMAdminErrCanNotStartApp	= 0x8011044b,
    COMAdminErrCanNotExportSystemApp	= 0x8011044c,
    COMAdminErrCanNotSubscribeToComponent	= 0x8011044d,
    COMAdminErrAppNotRunning	= 0x8011080a,
    COMAdminErrEventClassCannotBeSubscriber	= 0x8011044e,
    COMAdminErrLibAppProxyIncompatible	= 0x8011044f,
    COMAdminErrBasePartitionOnly	= 0x80110450,
    COMAdminErrDuplicatePartitionName	= 0x80110457,
    COMAdminErrPartitionInUse	= 0x80110459,
    COMAdminErrImportedComponentsNotAllowed	= 0x8011045b,
    COMAdminErrRegdbNotInitialized	= 0x80110472,
    COMAdminErrRegdbNotOpen	= 0x80110473,
    COMAdminErrRegdbSystemErr	= 0x80110474,
    COMAdminErrRegdbAlreadyRunning	= 0x80110475,
    COMAdminErrMigVersionNotSupported	= 0x80110480,
    COMAdminErrMigSchemaNotFound	= 0x80110481,
    COMAdminErrCatBitnessMismatch	= 0x80110482,
    COMAdminErrCatUnacceptableBitness	= 0x80110483,
    COMAdminErrCatWrongAppBitnessBitness	= 0x80110484,
    COMAdminErrCatPauseResumeNotSupported	= 0x80110485,
    COMAdminErrCatServerFault	= 0x80110486,
    COMAdminErrCantRecycleLibraryApps	= 0x8011080f,
    COMAdminErrCantRecycleServiceApps	= 0x80110811,
    COMAdminErrProcessAlreadyRecycled	= 0x80110812,
    COMAdminErrPausedProcessMayNotBeRecycled	= 0x80110813,
    COMAdminErrInvalidPartition = 0x8011080b,
    COMAdminErrPartitionMsiOnly = 0x80110819,
    COMAdminErrStartAppDisabled = 0x80110451,
    COMAdminErrCompMoveSource	= 0x8011081c,
    COMAdminErrCompMoveDest	= 0x8011081d,
    COMAdminErrCompMovePrivate	= 0x8011081e,
    COMAdminErrCannotCopyEventClass	= 0x80110820
    }


externdef LIBID_COMAdmin:IID

DEFINE_GUIDS(CLSID_COMAdminCatalog, "F618C514-DFB8-11d1-A2CF-00805FC79235")
DEFINE_GUIDS(CLSID_COMAdminCatalogObject, "F618C515-DFB8-11d1-A2CF-00805FC79235")
DEFINE_GUIDS(CLSID_COMAdminCatalogCollection, "F618C516-DFB8-11d1-A2CF-00805FC79235")

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

VARIANT_UserSize proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree proto WINAPI :ptr, :ptr

BSTR_UserSize64 proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree64 proto WINAPI :ptr, :ptr

LPSAFEARRAY_UserSize64 proto WINAPI :ptr, :dword, :ptr
LPSAFEARRAY_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserFree64 proto WINAPI :ptr, :ptr

VARIANT_UserSize64 proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree64 proto WINAPI :ptr, :ptr

endif

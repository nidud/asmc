ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __wbemdisp_h__
__wbemdisp_h__ equ <>

ifndef __ISWbemServices_FWD_DEFINED__
__ISWbemServices_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemLocator_FWD_DEFINED__
__ISWbemLocator_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemObject_FWD_DEFINED__
__ISWbemObject_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemObjectSet_FWD_DEFINED__
__ISWbemObjectSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemNamedValue_FWD_DEFINED__
__ISWbemNamedValue_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemNamedValueSet_FWD_DEFINED__
__ISWbemNamedValueSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemQualifier_FWD_DEFINED__
__ISWbemQualifier_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemQualifierSet_FWD_DEFINED__
__ISWbemQualifierSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemProperty_FWD_DEFINED__
__ISWbemProperty_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemPropertySet_FWD_DEFINED__
__ISWbemPropertySet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemMethod_FWD_DEFINED__
__ISWbemMethod_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemMethodSet_FWD_DEFINED__
__ISWbemMethodSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemEventSource_FWD_DEFINED__
__ISWbemEventSource_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemObjectPath_FWD_DEFINED__
__ISWbemObjectPath_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemLastError_FWD_DEFINED__
__ISWbemLastError_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemSinkEvents_FWD_DEFINED__
__ISWbemSinkEvents_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemSink_FWD_DEFINED__
__ISWbemSink_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemSecurity_FWD_DEFINED__
__ISWbemSecurity_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemPrivilege_FWD_DEFINED__
__ISWbemPrivilege_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemPrivilegeSet_FWD_DEFINED__
__ISWbemPrivilegeSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemServicesEx_FWD_DEFINED__
__ISWbemServicesEx_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemObjectEx_FWD_DEFINED__
__ISWbemObjectEx_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemDateTime_FWD_DEFINED__
__ISWbemDateTime_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemRefresher_FWD_DEFINED__
__ISWbemRefresher_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemRefreshableItem_FWD_DEFINED__
__ISWbemRefreshableItem_FWD_DEFINED__ equ 1
endif
ifndef __SWbemLocator_FWD_DEFINED__
__SWbemLocator_FWD_DEFINED__ equ 1
endif
ifndef __SWbemNamedValueSet_FWD_DEFINED__
__SWbemNamedValueSet_FWD_DEFINED__ equ 1
endif
ifndef __SWbemObjectPath_FWD_DEFINED__
__SWbemObjectPath_FWD_DEFINED__ equ 1
endif
ifndef __SWbemLastError_FWD_DEFINED__
__SWbemLastError_FWD_DEFINED__ equ 1
endif
ifndef __SWbemSink_FWD_DEFINED__
__SWbemSink_FWD_DEFINED__ equ 1
endif
ifndef __SWbemDateTime_FWD_DEFINED__
__SWbemDateTime_FWD_DEFINED__ equ 1
endif
ifndef __SWbemRefresher_FWD_DEFINED__
__SWbemRefresher_FWD_DEFINED__ equ 1
endif
ifndef __SWbemServices_FWD_DEFINED__
__SWbemServices_FWD_DEFINED__ equ 1
endif
ifndef __SWbemServicesEx_FWD_DEFINED__
__SWbemServicesEx_FWD_DEFINED__ equ 1
endif
ifndef __SWbemObject_FWD_DEFINED__
__SWbemObject_FWD_DEFINED__ equ 1
endif
ifndef __SWbemObjectEx_FWD_DEFINED__
__SWbemObjectEx_FWD_DEFINED__ equ 1
endif
ifndef __SWbemObjectSet_FWD_DEFINED__
__SWbemObjectSet_FWD_DEFINED__ equ 1
endif
ifndef __SWbemNamedValue_FWD_DEFINED__
__SWbemNamedValue_FWD_DEFINED__ equ 1
endif
ifndef __SWbemQualifier_FWD_DEFINED__
__SWbemQualifier_FWD_DEFINED__ equ 1
endif
ifndef __SWbemQualifierSet_FWD_DEFINED__
__SWbemQualifierSet_FWD_DEFINED__ equ 1
endif
ifndef __SWbemProperty_FWD_DEFINED__
__SWbemProperty_FWD_DEFINED__ equ 1
endif
ifndef __SWbemPropertySet_FWD_DEFINED__
__SWbemPropertySet_FWD_DEFINED__ equ 1
endif
ifndef __SWbemMethod_FWD_DEFINED__
__SWbemMethod_FWD_DEFINED__ equ 1
endif
ifndef __SWbemMethodSet_FWD_DEFINED__
__SWbemMethodSet_FWD_DEFINED__ equ 1
endif
ifndef __SWbemEventSource_FWD_DEFINED__
__SWbemEventSource_FWD_DEFINED__ equ 1
endif
ifndef __SWbemSecurity_FWD_DEFINED__
__SWbemSecurity_FWD_DEFINED__ equ 1
endif
ifndef __SWbemPrivilege_FWD_DEFINED__
__SWbemPrivilege_FWD_DEFINED__ equ 1
endif
ifndef __SWbemPrivilegeSet_FWD_DEFINED__
__SWbemPrivilegeSet_FWD_DEFINED__ equ 1
endif
ifndef __SWbemRefreshableItem_FWD_DEFINED__
__SWbemRefreshableItem_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemLocator_FWD_DEFINED__
__ISWbemLocator_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemServices_FWD_DEFINED__
__ISWbemServices_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemServicesEx_FWD_DEFINED__
__ISWbemServicesEx_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemObject_FWD_DEFINED__
__ISWbemObject_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemObjectEx_FWD_DEFINED__
__ISWbemObjectEx_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemLastError_FWD_DEFINED__
__ISWbemLastError_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemObjectSet_FWD_DEFINED__
__ISWbemObjectSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemNamedValueSet_FWD_DEFINED__
__ISWbemNamedValueSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemNamedValue_FWD_DEFINED__
__ISWbemNamedValue_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemObjectPath_FWD_DEFINED__
__ISWbemObjectPath_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemProperty_FWD_DEFINED__
__ISWbemProperty_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemPropertySet_FWD_DEFINED__
__ISWbemPropertySet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemQualifier_FWD_DEFINED__
__ISWbemQualifier_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemQualifierSet_FWD_DEFINED__
__ISWbemQualifierSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemMethod_FWD_DEFINED__
__ISWbemMethod_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemMethodSet_FWD_DEFINED__
__ISWbemMethodSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemSink_FWD_DEFINED__
__ISWbemSink_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemSinkEvents_FWD_DEFINED__
__ISWbemSinkEvents_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemEventSource_FWD_DEFINED__
__ISWbemEventSource_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemSecurity_FWD_DEFINED__
__ISWbemSecurity_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemPrivilege_FWD_DEFINED__
__ISWbemPrivilege_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemPrivilegeSet_FWD_DEFINED__
__ISWbemPrivilegeSet_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemDateTime_FWD_DEFINED__
__ISWbemDateTime_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemRefreshableItem_FWD_DEFINED__
__ISWbemRefreshableItem_FWD_DEFINED__ equ 1
endif
ifndef __ISWbemRefresher_FWD_DEFINED__
__ISWbemRefresher_FWD_DEFINED__ equ 1
endif

include dispex.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __WbemScripting_LIBRARY_DEFINED__
__WbemScripting_LIBRARY_DEFINED__ equ 1

DEFINE_IIDX(WbemChangeFlagEnum, "4A249B72-FC9A-11d1-8B1E-00600806D9B6")
.enum WbemChangeFlagEnum {
    wbemChangeFlagCreateOrUpdate	= 0,
    wbemChangeFlagUpdateOnly	= 0x1,
    wbemChangeFlagCreateOnly	= 0x2,
    wbemChangeFlagUpdateCompatible	= 0,
    wbemChangeFlagUpdateSafeMode	= 0x20,
    wbemChangeFlagUpdateForceMode	= 0x40,
    wbemChangeFlagStrongValidation	= 0x80,
    wbemChangeFlagAdvisory	= 0x10000
    }

DEFINE_IIDX(WbemFlagEnum, "4A249B73-FC9A-11d1-8B1E-00600806D9B6")
.enum WbemFlagEnum {
    wbemFlagReturnImmediately	= 0x10,
    wbemFlagReturnWhenComplete	= 0,
    wbemFlagBidirectional	= 0,
    wbemFlagForwardOnly = 0x20,
    wbemFlagNoErrorObject	= 0x40,
    wbemFlagReturnErrorObject	= 0,
    wbemFlagSendStatus	= 0x80,
    wbemFlagDontSendStatus	= 0,
    wbemFlagEnsureLocatable = 0x100,
    wbemFlagDirectRead	= 0x200,
    wbemFlagSendOnlySelected	= 0,
    wbemFlagUseAmendedQualifiers	= 0x20000,
    wbemFlagGetDefault	= 0,
    wbemFlagSpawnInstance	= 0x1,
    wbemFlagUseCurrentTime	= 0x1
    }

DEFINE_IIDX(WbemQueryFlagEnum, "4A249B76-FC9A-11d1-8B1E-00600806D9B6")
.enum WbemQueryFlagEnum {
    wbemQueryFlagDeep	= 0,
    wbemQueryFlagShallow	= 1,
    wbemQueryFlagPrototype	= 2
    }

DEFINE_IIDX(WbemTextFlagEnum, "4A249B78-FC9A-11d1-8B1E-00600806D9B6")
.enum WbemTextFlagEnum {
    wbemTextFlagNoFlavors	= 0x1
    }

DEFINE_IIDX(WbemTimeout, "BF078C2A-07D9-11d2-8B21-00600806D9B6")
.enum WbemTimeout {
    wbemTimeoutInfinite = 0xffffffff
    }

DEFINE_IIDX(WbemComparisonFlagEnum, "4A249B79-FC9A-11d1-8B1E-00600806D9B6")
.enum WbemComparisonFlagEnum {
    wbemComparisonFlagIncludeAll	= 0,
    wbemComparisonFlagIgnoreQualifiers	= 0x1,
    wbemComparisonFlagIgnoreObjectSource	= 0x2,
    wbemComparisonFlagIgnoreDefaultValues	= 0x4,
    wbemComparisonFlagIgnoreClass	= 0x8,
    wbemComparisonFlagIgnoreCase	= 0x10,
    wbemComparisonFlagIgnoreFlavor	= 0x20
    }

DEFINE_IIDX(WbemCimtypeEnum, "4A249B7B-FC9A-11d1-8B1E-00600806D9B6")
.enum WbemCimtypeEnum {
    wbemCimtypeSint8	= 16,
    wbemCimtypeUint8	= 17,
    wbemCimtypeSint16	= 2,
    wbemCimtypeUint16	= 18,
    wbemCimtypeSint32	= 3,
    wbemCimtypeUint32	= 19,
    wbemCimtypeSint64	= 20,
    wbemCimtypeUint64	= 21,
    wbemCimtypeReal32	= 4,
    wbemCimtypeReal64	= 5,
    wbemCimtypeBoolean	= 11,
    wbemCimtypeString	= 8,
    wbemCimtypeDatetime = 101,
    wbemCimtypeReference	= 102,
    wbemCimtypeChar16	= 103,
    wbemCimtypeObject	= 13
    }

DEFINE_IIDX(WbemErrorEnum, "4A249B7C-FC9A-11d1-8B1E-00600806D9B6")
.enum WbemErrorEnum {
    wbemNoErr	= 0,
    wbemErrFailed	= 0x80041001,
    wbemErrNotFound = 0x80041002,
    wbemErrAccessDenied = 0x80041003,
    wbemErrProviderFailure	= 0x80041004,
    wbemErrTypeMismatch = 0x80041005,
    wbemErrOutOfMemory	= 0x80041006,
    wbemErrInvalidContext	= 0x80041007,
    wbemErrInvalidParameter = 0x80041008,
    wbemErrNotAvailable = 0x80041009,
    wbemErrCriticalError	= 0x8004100a,
    wbemErrInvalidStream	= 0x8004100b,
    wbemErrNotSupported = 0x8004100c,
    wbemErrInvalidSuperclass	= 0x8004100d,
    wbemErrInvalidNamespace = 0x8004100e,
    wbemErrInvalidObject	= 0x8004100f,
    wbemErrInvalidClass = 0x80041010,
    wbemErrProviderNotFound = 0x80041011,
    wbemErrInvalidProviderRegistration	= 0x80041012,
    wbemErrProviderLoadFailure	= 0x80041013,
    wbemErrInitializationFailure	= 0x80041014,
    wbemErrTransportFailure = 0x80041015,
    wbemErrInvalidOperation = 0x80041016,
    wbemErrInvalidQuery = 0x80041017,
    wbemErrInvalidQueryType = 0x80041018,
    wbemErrAlreadyExists	= 0x80041019,
    wbemErrOverrideNotAllowed	= 0x8004101a,
    wbemErrPropagatedQualifier	= 0x8004101b,
    wbemErrPropagatedProperty	= 0x8004101c,
    wbemErrUnexpected	= 0x8004101d,
    wbemErrIllegalOperation = 0x8004101e,
    wbemErrCannotBeKey	= 0x8004101f,
    wbemErrIncompleteClass	= 0x80041020,
    wbemErrInvalidSyntax	= 0x80041021,
    wbemErrNondecoratedObject	= 0x80041022,
    wbemErrReadOnly = 0x80041023,
    wbemErrProviderNotCapable	= 0x80041024,
    wbemErrClassHasChildren = 0x80041025,
    wbemErrClassHasInstances	= 0x80041026,
    wbemErrQueryNotImplemented	= 0x80041027,
    wbemErrIllegalNull	= 0x80041028,
    wbemErrInvalidQualifierType = 0x80041029,
    wbemErrInvalidPropertyType	= 0x8004102a,
    wbemErrValueOutOfRange	= 0x8004102b,
    wbemErrCannotBeSingleton	= 0x8004102c,
    wbemErrInvalidCimType	= 0x8004102d,
    wbemErrInvalidMethod	= 0x8004102e,
    wbemErrInvalidMethodParameters	= 0x8004102f,
    wbemErrSystemProperty	= 0x80041030,
    wbemErrInvalidProperty	= 0x80041031,
    wbemErrCallCancelled	= 0x80041032,
    wbemErrShuttingDown = 0x80041033,
    wbemErrPropagatedMethod = 0x80041034,
    wbemErrUnsupportedParameter = 0x80041035,
    wbemErrMissingParameter = 0x80041036,
    wbemErrInvalidParameterId	= 0x80041037,
    wbemErrNonConsecutiveParameterIds	= 0x80041038,
    wbemErrParameterIdOnRetval	= 0x80041039,
    wbemErrInvalidObjectPath	= 0x8004103a,
    wbemErrOutOfDiskSpace	= 0x8004103b,
    wbemErrBufferTooSmall	= 0x8004103c,
    wbemErrUnsupportedPutExtension	= 0x8004103d,
    wbemErrUnknownObjectType	= 0x8004103e,
    wbemErrUnknownPacketType	= 0x8004103f,
    wbemErrMarshalVersionMismatch	= 0x80041040,
    wbemErrMarshalInvalidSignature	= 0x80041041,
    wbemErrInvalidQualifier = 0x80041042,
    wbemErrInvalidDuplicateParameter	= 0x80041043,
    wbemErrTooMuchData	= 0x80041044,
    wbemErrServerTooBusy	= 0x80041045,
    wbemErrInvalidFlavor	= 0x80041046,
    wbemErrCircularReference	= 0x80041047,
    wbemErrUnsupportedClassUpdate	= 0x80041048,
    wbemErrCannotChangeKeyInheritance	= 0x80041049,
    wbemErrCannotChangeIndexInheritance = 0x80041050,
    wbemErrTooManyProperties	= 0x80041051,
    wbemErrUpdateTypeMismatch	= 0x80041052,
    wbemErrUpdateOverrideNotAllowed = 0x80041053,
    wbemErrUpdatePropagatedMethod	= 0x80041054,
    wbemErrMethodNotImplemented = 0x80041055,
    wbemErrMethodDisabled	= 0x80041056,
    wbemErrRefresherBusy	= 0x80041057,
    wbemErrUnparsableQuery	= 0x80041058,
    wbemErrNotEventClass	= 0x80041059,
    wbemErrMissingGroupWithin	= 0x8004105a,
    wbemErrMissingAggregationList	= 0x8004105b,
    wbemErrPropertyNotAnObject	= 0x8004105c,
    wbemErrAggregatingByObject	= 0x8004105d,
    wbemErrUninterpretableProviderQuery = 0x8004105f,
    wbemErrBackupRestoreWinmgmtRunning	= 0x80041060,
    wbemErrQueueOverflow	= 0x80041061,
    wbemErrPrivilegeNotHeld = 0x80041062,
    wbemErrInvalidOperator	= 0x80041063,
    wbemErrLocalCredentials = 0x80041064,
    wbemErrCannotBeAbstract = 0x80041065,
    wbemErrAmendedObject	= 0x80041066,
    wbemErrClientTooSlow	= 0x80041067,
    wbemErrNullSecurityDescriptor	= 0x80041068,
    wbemErrTimeout	= 0x80041069,
    wbemErrInvalidAssociation	= 0x8004106a,
    wbemErrAmbiguousOperation	= 0x8004106b,
    wbemErrQuotaViolation	= 0x8004106c,
    wbemErrTransactionConflict	= 0x8004106d,
    wbemErrForcedRollback	= 0x8004106e,
    wbemErrUnsupportedLocale	= 0x8004106f,
    wbemErrHandleOutOfDate	= 0x80041070,
    wbemErrConnectionFailed = 0x80041071,
    wbemErrInvalidHandleRequest = 0x80041072,
    wbemErrPropertyNameTooWide	= 0x80041073,
    wbemErrClassNameTooWide = 0x80041074,
    wbemErrMethodNameTooWide	= 0x80041075,
    wbemErrQualifierNameTooWide = 0x80041076,
    wbemErrRerunCommand = 0x80041077,
    wbemErrDatabaseVerMismatch	= 0x80041078,
    wbemErrVetoPut	= 0x80041079,
    wbemErrVetoDelete	= 0x8004107a,
    wbemErrInvalidLocale	= 0x80041080,
    wbemErrProviderSuspended	= 0x80041081,
    wbemErrSynchronizationRequired	= 0x80041082,
    wbemErrNoSchema = 0x80041083,
    wbemErrProviderAlreadyRegistered	= 0x80041084,
    wbemErrProviderNotRegistered	= 0x80041085,
    wbemErrFatalTransportError	= 0x80041086,
    wbemErrEncryptedConnectionRequired	= 0x80041087,
    wbemErrRegistrationTooBroad = 0x80042001,
    wbemErrRegistrationTooPrecise	= 0x80042002,
    wbemErrTimedout = 0x80043001,
    wbemErrResetToDefault	= 0x80043002
    }

DEFINE_IIDX(WbemAuthenticationLevelEnum, "B54D66E7-2287-11d2-8B33-00600806D9B6")
.enum WbemAuthenticationLevelEnum {
    wbemAuthenticationLevelDefault	= 0,
    wbemAuthenticationLevelNone = 1,
    wbemAuthenticationLevelConnect	= 2,
    wbemAuthenticationLevelCall = 3,
    wbemAuthenticationLevelPkt	= 4,
    wbemAuthenticationLevelPktIntegrity = 5,
    wbemAuthenticationLevelPktPrivacy	= 6
    }

DEFINE_IIDX(WbemImpersonationLevelEnum, "B54D66E8-2287-11d2-8B33-00600806D9B6")
.enum WbemImpersonationLevelEnum {
    wbemImpersonationLevelAnonymous = 1,
    wbemImpersonationLevelIdentify	= 2,
    wbemImpersonationLevelImpersonate	= 3,
    wbemImpersonationLevelDelegate	= 4
    }

DEFINE_IIDX(WbemPrivilegeEnum, "176D2F70-5AF3-11d2-8B4A-00600806D9B6")
.enum WbemPrivilegeEnum {
    wbemPrivilegeCreateToken	= 1,
    wbemPrivilegePrimaryToken	= 2,
    wbemPrivilegeLockMemory = 3,
    wbemPrivilegeIncreaseQuota	= 4,
    wbemPrivilegeMachineAccount = 5,
    wbemPrivilegeTcb	= 6,
    wbemPrivilegeSecurity	= 7,
    wbemPrivilegeTakeOwnership	= 8,
    wbemPrivilegeLoadDriver = 9,
    wbemPrivilegeSystemProfile	= 10,
    wbemPrivilegeSystemtime = 11,
    wbemPrivilegeProfileSingleProcess	= 12,
    wbemPrivilegeIncreaseBasePriority	= 13,
    wbemPrivilegeCreatePagefile = 14,
    wbemPrivilegeCreatePermanent	= 15,
    wbemPrivilegeBackup = 16,
    wbemPrivilegeRestore	= 17,
    wbemPrivilegeShutdown	= 18,
    wbemPrivilegeDebug	= 19,
    wbemPrivilegeAudit	= 20,
    wbemPrivilegeSystemEnvironment	= 21,
    wbemPrivilegeChangeNotify	= 22,
    wbemPrivilegeRemoteShutdown = 23,
    wbemPrivilegeUndock = 24,
    wbemPrivilegeSyncAgent	= 25,
    wbemPrivilegeEnableDelegation	= 26,
    wbemPrivilegeManageVolume	= 27
    }

DEFINE_IIDX(WbemObjectTextFormatEnum, "09FF1992-EA0E-11d3-B391-00105A1F473A")
.enum WbemObjectTextFormatEnum {
    wbemObjectTextFormatCIMDTD20	= 1,
    wbemObjectTextFormatWMIDTD20	= 2
    }

.enum WbemConnectOptionsEnum {
    wbemConnectFlagUseMaxWait	= 0x80
    }


externdef LIBID_WbemScripting:IID

ifndef __ISWbemServices_INTERFACE_DEFINED__
__ISWbemServices_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemServices, "76A6415C-CB41-11d1-8B02-00600806D9B6")

.comdef ISWbemServices : public IDispatch

    Get			proc :BSTR, :LONG, :ptr, :ptr
    GetAsync		proc :ptr, :BSTR, :LONG, :ptr, :ptr
    Delete		proc :BSTR, :LONG, :ptr
    DeleteAsync		proc :ptr, :BSTR, :LONG, :ptr, :ptr
    InstancesOf		proc :BSTR, :LONG, :ptr, :ptr
    InstancesOfAsync	proc :ptr, :BSTR, :LONG, :ptr, :ptr
    SubclassesOf	proc :BSTR, :LONG, :ptr, :ptr
    SubclassesOfAsync	proc :ptr, :BSTR, :LONG, :ptr, :ptr
    ExecQuery		proc :BSTR, :BSTR, :LONG, :ptr, :ptr
    ExecQueryAsync	proc :ptr, :BSTR, :BSTR, :LONG, :ptr, :ptr
    AssociatorsOf	proc :BSTR, :BSTR, :BSTR, :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :BSTR, :LONG, :ptr, :ptr
    AssociatorsOfAsync	proc :ptr, :BSTR, :BSTR, :BSTR, :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :BSTR, :LONG, :ptr, :ptr
    ReferencesTo	proc :BSTR, :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :LONG, :ptr, :ptr
    ReferencesToAsync	proc :ptr, :BSTR, :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :LONG, :ptr, :ptr
    ExecNotificationQuery proc :BSTR, :BSTR, :LONG, :ptr, :ptr
    ExecNotificationQueryAsync proc :ptr, :BSTR, :BSTR, :LONG, :ptr, :ptr
    ExecMethod		proc :BSTR, :BSTR, :ptr, :LONG, :ptr, :ptr
    ExecMethodAsync	proc :ptr, :BSTR, :BSTR, :ptr, :LONG, :ptr, :ptr
    get_Security_	proc :ptr
    .ends

endif

ifndef __ISWbemLocator_INTERFACE_DEFINED__
__ISWbemLocator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemLocator, "76A6415B-CB41-11d1-8B02-00600806D9B6")

.comdef ISWbemLocator : public IDispatch

    ConnectServer	proc :BSTR, :BSTR, :BSTR, :BSTR, :BSTR, :BSTR, :LONG, :ptr, :ptr
    get_Security_	proc :ptr
    .ends

endif

ifndef __ISWbemObject_INTERFACE_DEFINED__
__ISWbemObject_INTERFACE_DEFINED__ equ 1

WBEMS_DISPID_DERIVATION equ ( 23 )

DEFINE_IIDX(ISWbemObject, "76A6415A-CB41-11d1-8B02-00600806D9B6")

.comdef ISWbemObject : public IDispatch

    Put_		proc :LONG, :ptr, :ptr
    PutAsync_		proc :ptr, :LONG, :ptr, :ptr
    Delete_		proc :LONG, :ptr
    DeleteAsync_	proc :ptr, :LONG, :ptr, :ptr
    Instances_		proc :LONG, :ptr, :ptr
    InstancesAsync_	proc :ptr, :LONG, :ptr, :ptr
    Subclasses_		proc :LONG, :ptr, :ptr
    SubclassesAsync_	proc :ptr, :LONG, :ptr, :ptr
    Associators_	proc :BSTR, :BSTR, :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :BSTR, :LONG, :ptr, :ptr
    AssociatorsAsync_	proc :ptr, :BSTR, :BSTR, :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :BSTR, :LONG, :ptr, :ptr
    References_		proc :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :LONG, :ptr, :ptr
    ReferencesAsync_	proc :ptr, :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :LONG, :ptr, :ptr
    ExecMethod_		proc :BSTR, :ptr, :LONG, :ptr, :ptr
    ExecMethodAsync_	proc :ptr, :BSTR, :ptr, :LONG, :ptr, :ptr
    Clone_		proc :ptr
    GetObjectText_	proc :LONG, :ptr
    SpawnDerivedClass_	proc :LONG, :ptr
    SpawnInstance_	proc :LONG, :ptr
    CompareTo_		proc :ptr, :LONG, :ptr
    get_Qualifiers_	proc :ptr
    get_Properties_	proc :ptr
    get_Methods_	proc :ptr
    get_Derivation_	proc :ptr
    get_Path_		proc :ptr
    get_Security_	proc :ptr
    .ends

endif

ifndef __ISWbemObjectSet_INTERFACE_DEFINED__
__ISWbemObjectSet_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemObjectSet, "76A6415F-CB41-11d1-8B02-00600806D9B6")

.comdef ISWbemObjectSet : public IDispatch

    get__NewEnum	proc :ptr
    Item		proc :BSTR, :LONG, :ptr
    get_Count		proc :ptr
    get_Security_	proc :ptr
    ItemIndex		proc :LONG, :ptr
    .ends

endif

ifndef __ISWbemNamedValue_INTERFACE_DEFINED__
__ISWbemNamedValue_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemNamedValue, "76A64164-CB41-11d1-8B02-00600806D9B6")

.comdef ISWbemNamedValue : public IDispatch

    get_Value		proc :ptr
    put_Value		proc :ptr
    get_Name		proc :ptr
    .ends

endif

ifndef __ISWbemNamedValueSet_INTERFACE_DEFINED__
__ISWbemNamedValueSet_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemNamedValueSet, "CF2376EA-CE8C-11d1-8B05-00600806D9B6")

.comdef ISWbemNamedValueSet : public IDispatch

    get__NewEnum	proc :ptr
    Item		proc :BSTR, :LONG, :ptr
    get_Count		proc :ptr
    _Add		proc :BSTR, :ptr, :LONG, :ptr
    Remove		proc :BSTR, :LONG
    Clone		proc :ptr
    DeleteAll		proc
    .ends

endif

ifndef __ISWbemQualifier_INTERFACE_DEFINED__
__ISWbemQualifier_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemQualifier, "79B05932-D3B7-11d1-8B06-00600806D9B6")

.comdef ISWbemQualifier : public IDispatch

    get_Value		proc :ptr
    put_Value		proc :ptr
    get_Name		proc :ptr
    get_IsLocal		proc :ptr
    get_PropagatesToSubclass proc :ptr
    put_PropagatesToSubclass proc :VARIANT_BOOL
    get_PropagatesToInstance proc :ptr
    put_PropagatesToInstance proc :VARIANT_BOOL
    get_IsOverridable	proc :ptr
    put_IsOverridable	proc :VARIANT_BOOL
    get_IsAmended	proc :ptr
    .ends

endif

ifndef __ISWbemQualifierSet_INTERFACE_DEFINED__
__ISWbemQualifierSet_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemQualifierSet, "9B16ED16-D3DF-11d1-8B08-00600806D9B6")

.comdef ISWbemQualifierSet : public IDispatch

    get__NewEnum	proc :ptr
    Item		proc :BSTR, :LONG, :ptr
    get_Count		proc :ptr
    _Add		proc :BSTR, :ptr, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL, :LONG, :ptr
    Remove		proc :BSTR, :LONG
    .ends

endif

ifndef __ISWbemProperty_INTERFACE_DEFINED__
__ISWbemProperty_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemProperty, "1A388F98-D4BA-11d1-8B09-00600806D9B6")

.comdef ISWbemProperty : public IDispatch

    get_Value		proc :ptr
    put_Value		proc :ptr
    get_Name		proc :ptr
    get_IsLocal		proc :ptr
    get_Origin		proc :ptr
    get_CIMType		proc :ptr
    get_Qualifiers_	proc :ptr
    get_IsArray		proc :ptr
    .ends

endif

ifndef __ISWbemPropertySet_INTERFACE_DEFINED__
__ISWbemPropertySet_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemPropertySet, "DEA0A7B2-D4BA-11d1-8B09-00600806D9B6")

.comdef ISWbemPropertySet : public IDispatch

    get__NewEnum	proc :ptr
    Item		proc :BSTR, :LONG, :ptr
    get_Count		proc :ptr
    _Add		proc :BSTR, :WbemCimtypeEnum, :VARIANT_BOOL, :LONG, :ptr
    Remove		proc :BSTR, :LONG
    .ends

endif

ifndef __ISWbemMethod_INTERFACE_DEFINED__
__ISWbemMethod_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemMethod, "422E8E90-D955-11d1-8B09-00600806D9B6")

.comdef ISWbemMethod : public IDispatch

    get_Name		proc :ptr
    get_Origin		proc :ptr
    get_InParameters	proc :ptr
    get_OutParameters	proc :ptr
    get_Qualifiers_	proc :ptr
    .ends

endif

ifndef __ISWbemMethodSet_INTERFACE_DEFINED__
__ISWbemMethodSet_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemMethodSet, "C93BA292-D955-11d1-8B09-00600806D9B6")

.comdef ISWbemMethodSet : public IDispatch

    get__NewEnum	proc :ptr
    Item		proc :BSTR, :LONG, :ptr
    get_Count		proc :ptr
    .ends

endif

ifndef __ISWbemEventSource_INTERFACE_DEFINED__
__ISWbemEventSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemEventSource, "27D54D92-0EBE-11d2-8B22-00600806D9B6")

.comdef ISWbemEventSource : public IDispatch

    NextEvent		proc :LONG, :ptr
    get_Security_	proc :ptr
    .ends

endif

ifndef __ISWbemObjectPath_INTERFACE_DEFINED__
__ISWbemObjectPath_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemObjectPath, "5791BC27-CE9C-11d1-97BF-0000F81E849C")

.comdef ISWbemObjectPath : public IDispatch

    get_Path		proc :ptr
    put_Path		proc :BSTR
    get_RelPath		proc :ptr
    put_RelPath		proc :BSTR
    get_Server		proc :ptr
    put_Server		proc :BSTR
    get_Namespace	proc :ptr
    put_Namespace	proc :BSTR
    get_ParentNamespace proc :ptr
    get_DisplayName	proc :ptr
    put_DisplayName	proc :BSTR
    get_Class		proc :ptr
    put_Class		proc :BSTR
    get_IsClass		proc :ptr
    SetAsClass		proc
    get_IsSingleton	proc :ptr
    SetAsSingleton	proc
    get_Keys		proc :ptr
    get_Security_	proc :ptr
    get_Locale		proc :ptr
    put_Locale		proc :BSTR
    get_Authority	proc :ptr
    put_Authority	proc :BSTR
    .ends

endif

ifndef __ISWbemLastError_INTERFACE_DEFINED__
__ISWbemLastError_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemLastError, "D962DB84-D4BB-11d1-8B09-00600806D9B6")

.comdef ISWbemLastError : public ISWbemObject

    .ends

endif

ifndef __ISWbemSinkEvents_DISPINTERFACE_DEFINED__
__ISWbemSinkEvents_DISPINTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemSinkEvents, "75718CA0-F029-11d1-A1AC-00C04FB6C223")

.comdef ISWbemSinkEvents : public IDispatch

    .ends

endif


ifndef __ISWbemSink_INTERFACE_DEFINED__
__ISWbemSink_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemSink, "75718C9F-F029-11d1-A1AC-00C04FB6C223")

.comdef ISWbemSink : public IDispatch

    Cancel		proc
    .ends

endif

ifndef __ISWbemSecurity_INTERFACE_DEFINED__
__ISWbemSecurity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemSecurity, "B54D66E6-2287-11d2-8B33-00600806D9B6")

.comdef ISWbemSecurity : public IDispatch

    get_ImpersonationLevel proc :ptr
    put_ImpersonationLevel proc :WbemImpersonationLevelEnum
    get_AuthenticationLevel proc :ptr
    put_AuthenticationLevel proc :WbemAuthenticationLevelEnum
    get_Privileges	proc :ptr
    .ends

endif

ifndef __ISWbemPrivilege_INTERFACE_DEFINED__
__ISWbemPrivilege_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemPrivilege, "26EE67BD-5804-11d2-8B4A-00600806D9B6")

.comdef ISWbemPrivilege : public IDispatch

    get_IsEnabled	proc :ptr
    put_IsEnabled	proc :VARIANT_BOOL
    get_Name		proc :ptr
    get_DisplayName	proc :ptr
    get_Identifier	proc :ptr
    .ends

endif

ifndef __ISWbemPrivilegeSet_INTERFACE_DEFINED__
__ISWbemPrivilegeSet_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemPrivilegeSet, "26EE67BF-5804-11d2-8B4A-00600806D9B6")

.comdef ISWbemPrivilegeSet : public IDispatch

    get__NewEnum	proc :ptr
    Item		proc :WbemPrivilegeEnum, :ptr
    get_Count		proc :ptr
    _Add		proc :WbemPrivilegeEnum, :VARIANT_BOOL, :ptr
    Remove		proc :WbemPrivilegeEnum
    DeleteAll		proc
    AddAsString		proc :BSTR, :VARIANT_BOOL, :ptr
    .ends

endif

ifndef __ISWbemServicesEx_INTERFACE_DEFINED__
__ISWbemServicesEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemServicesEx, "D2F68443-85DC-427e-91D8-366554CC754C")

.comdef ISWbemServicesEx : public ISWbemServices

    Put			proc :ptr, :LONG, :ptr, :ptr
    PutAsync		proc :ptr, :ptr, :LONG, :ptr, :ptr
    .ends

endif

ifndef __ISWbemObjectEx_INTERFACE_DEFINED__
__ISWbemObjectEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemObjectEx, "269AD56A-8A67-4129-BC8C-0506DCFE9880")

.comdef ISWbemObjectEx : public ISWbemObject

    Refresh_		proc :LONG, :ptr
    get_SystemProperties_ proc :ptr
    GetText_		proc :WbemObjectTextFormatEnum, :LONG, :ptr, :ptr
    SetFromText_	proc :BSTR, :WbemObjectTextFormatEnum, :LONG, :ptr
    .ends

endif

ifndef __ISWbemDateTime_INTERFACE_DEFINED__
__ISWbemDateTime_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemDateTime, "5E97458A-CF77-11d3-B38F-00105A1F473A")

.comdef ISWbemDateTime : public IDispatch

    get_Value		proc :ptr
    put_Value		proc :BSTR
    get_Year		proc :ptr
    put_Year		proc :LONG
    get_YearSpecified	proc :ptr
    put_YearSpecified	proc :VARIANT_BOOL
    get_Month		proc :ptr
    put_Month		proc :LONG
    get_MonthSpecified	proc :ptr
    put_MonthSpecified	proc :VARIANT_BOOL
    get_Day		proc :ptr
    put_Day		proc :LONG
    get_DaySpecified	proc :ptr
    put_DaySpecified	proc :VARIANT_BOOL
    get_Hours		proc :ptr
    put_Hours		proc :LONG
    get_HoursSpecified	proc :ptr
    put_HoursSpecified	proc :VARIANT_BOOL
    get_Minutes		proc :ptr
    put_Minutes		proc :LONG
    get_MinutesSpecified proc :ptr
    put_MinutesSpecified proc :VARIANT_BOOL
    get_Seconds		proc :ptr
    put_Seconds		proc :LONG
    get_SecondsSpecified proc :ptr
    put_SecondsSpecified proc :VARIANT_BOOL
    get_Microseconds	proc :ptr
    put_Microseconds	proc :LONG
    get_MicrosecondsSpecified proc :ptr
    put_MicrosecondsSpecified proc :VARIANT_BOOL
    get_UTC		proc :ptr
    put_UTC		proc :LONG
    get_UTCSpecified	proc :ptr
    put_UTCSpecified	proc :VARIANT_BOOL
    get_IsInterval	proc :ptr
    put_IsInterval	proc :VARIANT_BOOL
    GetVarDate		proc :VARIANT_BOOL, :ptr
    SetVarDate		proc :DATE, :VARIANT_BOOL
    GetFileTime		proc :VARIANT_BOOL, :ptr
    SetFileTime		proc :BSTR, :VARIANT_BOOL
    .ends

endif

ifndef __ISWbemRefresher_INTERFACE_DEFINED__
__ISWbemRefresher_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemRefresher, "14D8250E-D9C2-11d3-B38F-00105A1F473A")

.comdef ISWbemRefresher : public IDispatch

    get__NewEnum	proc :ptr
    Item		proc :LONG, :ptr
    get_Count		proc :ptr
    _Add		proc :ptr, :BSTR, :LONG, :ptr, :ptr
    AddEnum		proc :ptr, :BSTR, :LONG, :ptr, :ptr
    Remove		proc :LONG, :LONG
    Refresh		proc :LONG
    get_AutoReconnect	proc :ptr
    put_AutoReconnect	proc :VARIANT_BOOL
    DeleteAll		proc
    .ends

endif

ifndef __ISWbemRefreshableItem_INTERFACE_DEFINED__
__ISWbemRefreshableItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISWbemRefreshableItem, "5AD4BF92-DAAB-11d3-B38F-00105A1F473A")

.comdef ISWbemRefreshableItem : public IDispatch

    get_Index		proc :ptr
    get_Refresher	proc :ptr
    get_IsSet		proc :ptr
    get_Object		proc :ptr
    get_ObjectSet	proc :ptr
    Remove		proc :LONG
    .ends

endif

DEFINE_GUIDS(CLSID_SWbemLocator, "76A64158-CB41-11d1-8B02-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemNamedValueSet, "9AED384E-CE8B-11d1-8B05-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemObjectPath, "5791BC26-CE9C-11d1-97BF-0000F81E849C")
DEFINE_GUIDS(CLSID_SWbemLastError, "C2FEEEAC-CFCD-11d1-8B05-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemSink, "75718C9A-F029-11d1-A1AC-00C04FB6C223")
DEFINE_GUIDS(CLSID_SWbemDateTime, "47DFBE54-CF76-11d3-B38F-00105A1F473A")
DEFINE_GUIDS(CLSID_SWbemRefresher, "D269BF5C-D9C1-11d3-B38F-00105A1F473A")
DEFINE_GUIDS(CLSID_SWbemServices, "04B83D63-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemServicesEx, "62E522DC-8CF3-40a8-8B2E-37D595651E40")
DEFINE_GUIDS(CLSID_SWbemObject, "04B83D62-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemObjectEx, "D6BDAFB2-9435-491f-BB87-6AA0F0BC31A2")
DEFINE_GUIDS(CLSID_SWbemObjectSet, "04B83D61-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemNamedValue, "04B83D60-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemQualifier, "04B83D5F-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemQualifierSet, "04B83D5E-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemProperty, "04B83D5D-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemPropertySet, "04B83D5C-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemMethod, "04B83D5B-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemMethodSet, "04B83D5A-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemEventSource, "04B83D58-21AE-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemSecurity, "B54D66E9-2287-11d2-8B33-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemPrivilege, "26EE67BC-5804-11d2-8B4A-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemPrivilegeSet, "26EE67BE-5804-11d2-8B4A-00600806D9B6")
DEFINE_GUIDS(CLSID_SWbemRefreshableItem, "8C6854BC-DE4B-11d3-B390-00105A1F473A")

endif

WBEMS_DISPID_OBJECT_READY equ ( 1 )
WBEMS_DISPID_COMPLETED	equ ( 2 )
WBEMS_DISPID_PROGRESS	equ ( 3 )
WBEMS_DISPID_OBJECT_PUT equ ( 4 )
WBEMS_DISPID_CONNECTION_READY equ ( 5 )

endif
endif

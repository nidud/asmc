ifndef _ADOINT_H_
_ADOINT_H_ equ <>
.pragma list(push, 0)

ifndef _INC_TCHAR
include tchar.inc
endif

if (_MSC_VER GE 1100) AND defined (__cplusplus)
DECLSPEC_UUID macro x
	exitm<__declspec(uuid(x))>
	endm
else
DECLSPEC_UUID macro x
	exitm<>
	endm
endif

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
ifndef __ado10_h__
__ado10_h__ equ <>

ifndef ___ADOCollection_FWD_DEFINED__
___ADOCollection_FWD_DEFINED__ equ 1
; _ADOCollection typedef _ADOCollection
endif
ifndef ___ADODynaCollection_FWD_DEFINED__
___ADODynaCollection_FWD_DEFINED__ equ 1
endif
ifndef ___ADO_FWD_DEFINED__
___ADO_FWD_DEFINED__ equ 1
endif
ifndef __Error_FWD_DEFINED__
__Error_FWD_DEFINED__ equ 1
endif
ifndef __Errors_FWD_DEFINED__
__Errors_FWD_DEFINED__ equ 1
endif
ifndef __Command15_FWD_DEFINED__
__Command15_FWD_DEFINED__ equ 1
endif
ifndef __Command25_FWD_DEFINED__
__Command25_FWD_DEFINED__ equ 1
endif
ifndef ___Command_FWD_DEFINED__
___Command_FWD_DEFINED__ equ 1
;_Command typedef _ADOCommand
endif
ifndef __ConnectionEventsVt_FWD_DEFINED__
__ConnectionEventsVt_FWD_DEFINED__ equ 1
endif
ifndef __RecordsetEventsVt_FWD_DEFINED__
__RecordsetEventsVt_FWD_DEFINED__ equ 1
endif
ifndef __ConnectionEvents_FWD_DEFINED__
__ConnectionEvents_FWD_DEFINED__ equ 1
endif
ifndef __RecordsetEvents_FWD_DEFINED__
__RecordsetEvents_FWD_DEFINED__ equ 1
endif
ifndef __Connection15_FWD_DEFINED__
__Connection15_FWD_DEFINED__ equ 1
endif
ifndef ___Connection_FWD_DEFINED__
___Connection_FWD_DEFINED__ equ 1
endif
ifndef __ADOConnectionConstruction15_FWD_DEFINED__
__ADOConnectionConstruction15_FWD_DEFINED__ equ 1
endif
ifndef __ADOConnectionConstruction_FWD_DEFINED__
__ADOConnectionConstruction_FWD_DEFINED__ equ 1
endif
ifndef __Connection_FWD_DEFINED__
__Connection_FWD_DEFINED__ equ 1
;_Connection typedef _ADOConnection
endif
ifndef ___Record_FWD_DEFINED__
___Record_FWD_DEFINED__ equ 1
endif
ifndef __Record_FWD_DEFINED__
__Record_FWD_DEFINED__ equ 1
;Record typedef ADORecord
endif
ifndef ___Stream_FWD_DEFINED__
___Stream_FWD_DEFINED__ equ 1
endif
ifndef __Stream_FWD_DEFINED__
__Stream_FWD_DEFINED__ equ 1
;Stream typedef ADOStream
endif
ifndef __ADORecordConstruction_FWD_DEFINED__
__ADORecordConstruction_FWD_DEFINED__ equ 1
endif
ifndef __ADOStreamConstruction_FWD_DEFINED__
__ADOStreamConstruction_FWD_DEFINED__ equ 1
endif
ifndef __ADOCommandConstruction_FWD_DEFINED__
__ADOCommandConstruction_FWD_DEFINED__ equ 1
endif
ifndef __Command_FWD_DEFINED__
__Command_FWD_DEFINED__ equ 1
;_Command typedef _ADOCommand
endif
ifndef __Recordset_FWD_DEFINED__
__Recordset_FWD_DEFINED__ equ 1
;Recordset typedef ADORecordset
endif
ifndef __Recordset15_FWD_DEFINED__
__Recordset15_FWD_DEFINED__ equ 1
endif
ifndef __Recordset20_FWD_DEFINED__
__Recordset20_FWD_DEFINED__ equ 1
endif
ifndef __Recordset21_FWD_DEFINED__
__Recordset21_FWD_DEFINED__ equ 1
endif
ifndef ___Recordset_FWD_DEFINED__
___Recordset_FWD_DEFINED__ equ 1
endif
ifndef __ADORecordsetConstruction_FWD_DEFINED__
__ADORecordsetConstruction_FWD_DEFINED__ equ 1
endif
ifndef __Field15_FWD_DEFINED__
__Field15_FWD_DEFINED__ equ 1
endif
ifndef __Field20_FWD_DEFINED__
__Field20_FWD_DEFINED__ equ 1
endif
ifndef __Field_FWD_DEFINED__
__Field_FWD_DEFINED__ equ 1
endif
ifndef __Fields15_FWD_DEFINED__
__Fields15_FWD_DEFINED__ equ 1
endif
ifndef __Fields20_FWD_DEFINED__
__Fields20_FWD_DEFINED__ equ 1
endif
ifndef __Fields_FWD_DEFINED__
__Fields_FWD_DEFINED__ equ 1
endif
ifndef ___Parameter_FWD_DEFINED__
___Parameter_FWD_DEFINED__ equ 1
endif
ifndef __Parameter_FWD_DEFINED__
__Parameter_FWD_DEFINED__ equ 1
;Parameter typedef ADOParameter
endif
ifndef __Parameters_FWD_DEFINED__
__Parameters_FWD_DEFINED__ equ 1
endif
ifndef __Property_FWD_DEFINED__
__Property_FWD_DEFINED__ equ 1
endif
ifndef __Properties_FWD_DEFINED__
__Properties_FWD_DEFINED__ equ 1
endif

ifdef _WIN64
ADO_LONGPTR		typedef LONGLONG
else
ADO_LONGPTR		typedef LONG
endif
ifndef __ADODB_LIBRARY_DEFINED__
__ADODB_LIBRARY_DEFINED__ equ 1
DECLSPEC_UUID("0000051B-0000-0010-8000-00AA006D2EA4")
.enum CursorTypeEnum {
	adOpenUnspecified = -1,
	adOpenForwardOnly = 0,
	adOpenKeyset	= 1,
	adOpenDynamic	= 2,
	adOpenStatic	= 3
    }
DECLSPEC_UUID("0000051C-0000-0010-8000-00AA006D2EA4")
.enum CursorOptionEnum {
	adHoldRecords	= 0x100,
	adMovePrevious	= 0x200,
	adAddNew	= 0x1000400,
	adDelete	= 0x1000800,
	adUpdate	= 0x1008000,
	adBookmark	= 0x2000,
	adApproxPosition = 0x4000,
	adUpdateBatch	= 0x10000,
	adResync	= 0x20000,
	adNotify	= 0x40000,
	adFind		= 0x80000,
	adSeek		= 0x400000,
	adIndex		= 0x800000
    }
DECLSPEC_UUID("0000051D-0000-0010-8000-00AA006D2EA4")
.enum LockTypeEnum {
	adLockUnspecified = -1,
	adLockReadOnly	= 1,
	adLockPessimistic = 2,
	adLockOptimistic = 3,
	adLockBatchOptimistic = 4
    }
DECLSPEC_UUID("0000051E-0000-0010-8000-00AA006D2EA4")
.enum ExecuteOptionEnum {
	adOptionUnspecified = -1,
	adAsyncExecute	= 0x10,
	adAsyncFetch	= 0x20,
	adAsyncFetchNonBlocking = 0x40,
	adExecuteNoRecords = 0x80,
	adExecuteStream = 0x400,
	adExecuteRecord = 0x800
    }
DECLSPEC_UUID("00000541-0000-0010-8000-00AA006D2EA4")
.enum ConnectOptionEnum {
	adConnectUnspecified = -1,
	adAsyncConnect	= 0x10
    }
DECLSPEC_UUID("00000532-0000-0010-8000-00AA006D2EA4")
.enum ObjectStateEnum {
	adStateClosed	= 0,
	adStateOpen	= 0x1,
	adStateConnecting = 0x2,
	adStateExecuting = 0x4,
	adStateFetching = 0x8
    }
DECLSPEC_UUID("0000052F-0000-0010-8000-00AA006D2EA4")
.enum CursorLocationEnum {
	adUseNone	= 1,
	adUseServer	= 2,
	adUseClient	= 3,
	adUseClientBatch = 3
    }
DECLSPEC_UUID("0000051F-0000-0010-8000-00AA006D2EA4")
.enum DataTypeEnum {
	adEmpty		= 0,
	adTinyInt	= 16,
	adSmallInt	= 2,
	adInteger	= 3,
	adBigInt	= 20,
	adUnsignedTinyInt = 17,
	adUnsignedSmallInt = 18,
	adUnsignedInt	= 19,
	adUnsignedBigInt = 21,
	adSingle	= 4,
	adDouble	= 5,
	adCurrency	= 6,
	adDecimal	= 14,
	adNumeric	= 131,
	adBoolean	= 11,
	adError		= 10,
	adUserDefined	= 132,
	adVariant	= 12,
	adIDispatch	= 9,
	adIUnknown	= 13,
	adGUID		= 72,
	adDate		= 7,
	adDBDate	= 133,
	adDBTime	= 134,
	adDBTimeStamp	= 135,
	adBSTR		= 8,
	adChar		= 129,
	adVarChar	= 200,
	adLongVarChar	= 201,
	adWChar		= 130,
	adVarWChar	= 202,
	adLongVarWChar	= 203,
	adBinary	= 128,
	adVarBinary	= 204,
	adLongVarBinary = 205,
	adChapter	= 136,
	adFileTime	= 64,
	adPropVariant	= 138,
	adVarNumeric	= 139,
	adArray		= 0x2000
    }
DECLSPEC_UUID("00000525-0000-0010-8000-00AA006D2EA4")
.enum FieldAttributeEnum {
	adFldUnspecified = -1,
	adFldMayDefer	= 0x2,
	adFldUpdatable	= 0x4,
	adFldUnknownUpdatable = 0x8,
	adFldFixed	= 0x10,
	adFldIsNullable = 0x20,
	adFldMayBeNull	= 0x40,
	adFldLong	= 0x80,
	adFldRowID	= 0x100,
	adFldRowVersion = 0x200,
	adFldCacheDeferred = 0x1000,
	adFldIsChapter	= 0x2000,
	adFldNegativeScale = 0x4000,
	adFldKeyColumn	= 0x8000,
	adFldIsRowURL	= 0x10000,
	adFldIsDefaultStream = 0x20000,
	adFldIsCollection = 0x40000
    }
DECLSPEC_UUID("00000526-0000-0010-8000-00AA006D2EA4")
.enum EditModeEnum {
	adEditNone	= 0,
	adEditInProgress = 0x1,
	adEditAdd	= 0x2,
	adEditDelete	= 0x4
    }
DECLSPEC_UUID("00000527-0000-0010-8000-00AA006D2EA4")
.enum RecordStatusEnum {
	adRecOK		= 0,
	adRecNew	= 0x1,
	adRecModified	= 0x2,
	adRecDeleted	= 0x4,
	adRecUnmodified = 0x8,
	adRecInvalid	= 0x10,
	adRecMultipleChanges = 0x40,
	adRecPendingChanges = 0x80,
	adRecCanceled	= 0x100,
	adRecCantRelease = 0x400,
	adRecConcurrencyViolation = 0x800,
	adRecIntegrityViolation = 0x1000,
	adRecMaxChangesExceeded = 0x2000,
	adRecObjectOpen = 0x4000,
	adRecOutOfMemory = 0x8000,
	adRecPermissionDenied = 0x10000,
	adRecSchemaViolation = 0x20000,
	adRecDBDeleted	= 0x40000
    }
DECLSPEC_UUID("00000542-0000-0010-8000-00AA006D2EA4")
.enum GetRowsOptionEnum {
	adGetRowsRest	= -1
    }
DECLSPEC_UUID("00000528-0000-0010-8000-00AA006D2EA4")
.enum PositionEnum {
	adPosUnknown	= -1,
	adPosBOF	= -2,
	adPosEOF	= -3
    }

ifdef _WIN64
PositionEnum_Param	typedef LONGLONG
else
PositionEnum_Param	typedef PositionEnum
endif
.enum BookmarkEnum {
	adBookmarkCurrent = 0,
	adBookmarkFirst = 1,
	adBookmarkLast	= 2
    }
DECLSPEC_UUID("00000540-0000-0010-8000-00AA006D2EA4")
.enum MarshalOptionsEnum {
	adMarshalAll	= 0,
	adMarshalModifiedOnly	= 1
    }
DECLSPEC_UUID("00000543-0000-0010-8000-00AA006D2EA4")
.enum AffectEnum {
	adAffectCurrent = 1,
	adAffectGroup	= 2,
	adAffectAll	= 3,
	adAffectAllChapters	= 4
    }
DECLSPEC_UUID("00000544-0000-0010-8000-00AA006D2EA4")
.enum ResyncEnum {
	adResyncUnderlyingValues	= 1,
	adResyncAllValues	= 2
    }
DECLSPEC_UUID("00000545-0000-0010-8000-00AA006D2EA4")
.enum CompareEnum {
	adCompareLessThan	= 0,
	adCompareEqual	= 1,
	adCompareGreaterThan	= 2,
	adCompareNotEqual	= 3,
	adCompareNotComparable	= 4
    }
DECLSPEC_UUID("00000546-0000-0010-8000-00AA006D2EA4")
.enum FilterGroupEnum {
	adFilterNone	= 0,
	adFilterPendingRecords	= 1,
	adFilterAffectedRecords = 2,
	adFilterFetchedRecords	= 3,
	adFilterPredicate	= 4,
	adFilterConflictingRecords	= 5
    }
DECLSPEC_UUID("00000547-0000-0010-8000-00AA006D2EA4")
.enum SearchDirectionEnum {
	adSearchForward = 1,
	adSearchBackward	= -1
    }
SearchDirection typedef	 SearchDirectionEnum
DECLSPEC_UUID("00000548-0000-0010-8000-00AA006D2EA4")
.enum PersistFormatEnum {
	adPersistADTG	= 0,
	adPersistXML	= 1
    }
DECLSPEC_UUID("00000549-0000-0010-8000-00AA006D2EA4")
.enum StringFormatEnum {
	adClipString	= 2
    }
DECLSPEC_UUID("00000520-0000-0010-8000-00AA006D2EA4")
.enum ConnectPromptEnum {
	adPromptAlways	= 1,
	adPromptComplete	= 2,
	adPromptCompleteRequired	= 3,
	adPromptNever	= 4
    }
DECLSPEC_UUID("00000521-0000-0010-8000-00AA006D2EA4")
.enum ConnectModeEnum {
	adModeUnknown	= 0,
	adModeRead	= 1,
	adModeWrite	= 2,
	adModeReadWrite = 3,
	adModeShareDenyRead	= 4,
	adModeShareDenyWrite	= 8,
	adModeShareExclusive	= 0xc,
	adModeShareDenyNone	= 0x10,
	adModeRecursive = 0x400000
    }
DECLSPEC_UUID("00000570-0000-0010-8000-00AA006D2EA4")
.enum RecordCreateOptionsEnum {
	adCreateCollection	= 0x2000,
	adCreateStructDoc	= 0x80000000,
	adCreateNonCollection	= 0,
	adOpenIfExists	= 0x2000000,
	adCreateOverwrite	= 0x4000000,
	adFailIfNotExists	= -1
    }
DECLSPEC_UUID("00000571-0000-0010-8000-00AA006D2EA4")
.enum RecordOpenOptionsEnum {
	adOpenRecordUnspecified = -1,
	adOpenSource	= 0x800000,
	adOpenOutput	= 0x800000,
	adOpenAsync	= 0x1000,
	adDelayFetchStream	= 0x4000,
	adDelayFetchFields	= 0x8000,
	adOpenExecuteCommand	= 0x10000
    }
DECLSPEC_UUID("00000523-0000-0010-8000-00AA006D2EA4")
.enum IsolationLevelEnum {
	adXactUnspecified	= 0xffffffff,
	adXactChaos	= 0x10,
	adXactReadUncommitted	= 0x100,
	adXactBrowse	= 0x100,
	adXactCursorStability	= 0x1000,
	adXactReadCommitted	= 0x1000,
	adXactRepeatableRead	= 0x10000,
	adXactSerializable	= 0x100000,
	adXactIsolated	= 0x100000
    }
DECLSPEC_UUID("00000524-0000-0010-8000-00AA006D2EA4")
.enum XactAttributeEnum {
	adXactCommitRetaining	= 0x20000,
	adXactAbortRetaining	= 0x40000,
	adXactAsyncPhaseOne	= 0x80000,
	adXactSyncPhaseOne	= 0x100000
    }
DECLSPEC_UUID("00000529-0000-0010-8000-00AA006D2EA4")
.enum PropertyAttributesEnum {
	adPropNotSupported	= 0,
	adPropRequired	= 0x1,
	adPropOptional	= 0x2,
	adPropRead	= 0x200,
	adPropWrite	= 0x400
    }
DECLSPEC_UUID("0000052A-0000-0010-8000-00AA006D2EA4")
.enum ErrorValueEnum {
	adErrProviderFailed	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbb8),
	adErrInvalidArgument	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbb9),
	adErrOpeningFile	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbba),
	adErrReadFile		= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbbb),
	adErrWriteFile		= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbbc),
	adErrNoCurrentRecord	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbcd),
	adErrIllegalOperation	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xc93),
	adErrCantChangeProvider = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xc94),
	adErrInTransaction	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xcae),
	adErrFeatureNotAvailable= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xcb3),
	adErrItemNotFound	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xcc1),
	adErrObjectInCollection = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xd27),
	adErrObjectNotSet	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xd5c),
	adErrDataConversion	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xd5d),
	adErrObjectClosed	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe78),
	adErrObjectOpen		= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe79),
	adErrProviderNotFound	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7a),
	adErrBoundToCommand	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7b),
	adErrInvalidParamInfo	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7c),
	adErrInvalidConnection	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7d),
	adErrNotReentrant	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7e),
	adErrStillExecuting	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7f),
	adErrOperationCancelled = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe80),
	adErrStillConnecting	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe81),
	adErrInvalidTransaction = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe82),
	adErrNotExecuting	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe83),
	adErrUnsafeOperation	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe84),
	adwrnSecurityDialog	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe85),
	adwrnSecurityDialogHeader = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe86),
	adErrIntegrityViolation = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe87),
	adErrPermissionDenied	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe88),
	adErrDataOverflow	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe89),
	adErrSchemaViolation	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8a),
	adErrSignMismatch	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8b),
	adErrCantConvertvalue	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8c),
	adErrCantCreate		= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8d),
	adErrColumnNotOnThisRow = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8e),
	adErrURLDoesNotExist	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8f),
	adErrTreePermissionDenied = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe90),
	adErrInvalidURL		= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe91),
	adErrResourceLocked	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe92),
	adErrResourceExists	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe93),
	adErrCannotComplete	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe94),
	adErrVolumeNotFound	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe95),
	adErrOutOfSpace		= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe96),
	adErrResourceOutOfScope = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe97),
	adErrUnavailable	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe98),
	adErrURLNamedRowDoesNotExist = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe99),
	adErrDelResOutOfScope	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9a),
	adErrPropInvalidColumn	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9b),
	adErrPropInvalidOption	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9c),
	adErrPropInvalidValue	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9d),
	adErrPropConflicting	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9e),
	adErrPropNotAllSettable = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9f),
	adErrPropNotSet		= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea0),
	adErrPropNotSettable	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea1),
	adErrPropNotSupported	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea2),
	adErrCatalogNotSet	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea3),
	adErrCantChangeConnection = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea4),
	adErrFieldsUpdateFailed = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea5),
	adErrDenyNotSupported	= MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea6),
	adErrDenyTypeNotSupported = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea7),
	adErrProviderNotSpecified = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea9),
	adErrConnectionStringTooLong = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xeaa)
    }
DECLSPEC_UUID("0000052B-0000-0010-8000-00AA006D2EA4")
.enum ParameterAttributesEnum {
	adParamSigned	= 0x10,
	adParamNullable = 0x40,
	adParamLong	= 0x80
    }
DECLSPEC_UUID("0000052C-0000-0010-8000-00AA006D2EA4")
.enum ParameterDirectionEnum {
	adParamUnknown	= 0,
	adParamInput	= 0x1,
	adParamOutput	= 0x2,
	adParamInputOutput	= 0x3,
	adParamReturnValue	= 0x4
    }
DECLSPEC_UUID("0000052E-0000-0010-8000-00AA006D2EA4")
.enum CommandTypeEnum {
	adCmdUnspecified	= -1,
	adCmdUnknown	= 0x8,
	adCmdText	= 0x1,
	adCmdTable	= 0x2,
	adCmdStoredProc = 0x4,
	adCmdFile	= 0x100,
	adCmdTableDirect	= 0x200
    }
DECLSPEC_UUID("00000530-0000-0010-8000-00AA006D2EA4")
.enum EventStatusEnum {
	adStatusOK	= 0x1,
	adStatusErrorsOccurred	= 0x2,
	adStatusCantDeny	= 0x3,
	adStatusCancel	= 0x4,
	adStatusUnwantedEvent	= 0x5
    }
DECLSPEC_UUID("00000531-0000-0010-8000-00AA006D2EA4")
.enum EventReasonEnum {
	adRsnAddNew	= 1,
	adRsnDelete	= 2,
	adRsnUpdate	= 3,
	adRsnUndoUpdate = 4,
	adRsnUndoAddNew = 5,
	adRsnUndoDelete = 6,
	adRsnRequery	= 7,
	adRsnResynch	= 8,
	adRsnClose	= 9,
	adRsnMove	= 10,
	adRsnFirstChange = 11,
	adRsnMoveFirst	= 12,
	adRsnMoveNext	= 13,
	adRsnMovePrevious = 14,
	adRsnMoveLast	= 15
    }
DECLSPEC_UUID("00000533-0000-0010-8000-00AA006D2EA4")
.enum SchemaEnum {
	adSchemaProviderSpecific = -1,
	adSchemaAsserts = 0,
	adSchemaCatalogs	= 1,
	adSchemaCharacterSets	= 2,
	adSchemaCollations	= 3,
	adSchemaColumns = 4,
	adSchemaCheckConstraints	= 5,
	adSchemaConstraintColumnUsage	= 6,
	adSchemaConstraintTableUsage	= 7,
	adSchemaKeyColumnUsage	= 8,
	adSchemaReferentialContraints	= 9,
	adSchemaReferentialConstraints	= 9,
	adSchemaTableConstraints	= 10,
	adSchemaColumnsDomainUsage	= 11,
	adSchemaIndexes = 12,
	adSchemaColumnPrivileges	= 13,
	adSchemaTablePrivileges = 14,
	adSchemaUsagePrivileges = 15,
	adSchemaProcedures	= 16,
	adSchemaSchemata	= 17,
	adSchemaSQLLanguages	= 18,
	adSchemaStatistics	= 19,
	adSchemaTables	= 20,
	adSchemaTranslations	= 21,
	adSchemaProviderTypes	= 22,
	adSchemaViews	= 23,
	adSchemaViewColumnUsage = 24,
	adSchemaViewTableUsage	= 25,
	adSchemaProcedureParameters	= 26,
	adSchemaForeignKeys	= 27,
	adSchemaPrimaryKeys	= 28,
	adSchemaProcedureColumns	= 29,
	adSchemaDBInfoKeywords	= 30,
	adSchemaDBInfoLiterals	= 31,
	adSchemaCubes	= 32,
	adSchemaDimensions	= 33,
	adSchemaHierarchies	= 34,
	adSchemaLevels	= 35,
	adSchemaMeasures	= 36,
	adSchemaProperties	= 37,
	adSchemaMembers = 38,
	adSchemaTrustees	= 39,
	adSchemaFunctions	= 40,
	adSchemaActions = 41,
	adSchemaCommands	= 42,
	adSchemaSets	= 43
    }
DECLSPEC_UUID("0000057E-0000-0010-8000-00AA006D2EA4")
.enum FieldStatusEnum {
	adFieldOK	= 0,
	adFieldCantConvertValue = 2,
	adFieldIsNull	= 3,
	adFieldTruncated	= 4,
	adFieldSignMismatch	= 5,
	adFieldDataOverflow	= 6,
	adFieldCantCreate	= 7,
	adFieldUnavailable	= 8,
	adFieldPermissionDenied = 9,
	adFieldIntegrityViolation	= 10,
	adFieldSchemaViolation	= 11,
	adFieldBadStatus	= 12,
	adFieldDefault	= 13,
	adFieldIgnore	= 15,
	adFieldDoesNotExist	= 16,
	adFieldInvalidURL	= 17,
	adFieldResourceLocked	= 18,
	adFieldResourceExists	= 19,
	adFieldCannotComplete	= 20,
	adFieldVolumeNotFound	= 21,
	adFieldOutOfSpace	= 22,
	adFieldCannotDeleteSource	= 23,
	adFieldReadOnly = 24,
	adFieldResourceOutOfScope	= 25,
	adFieldAlreadyExists	= 26,
	adFieldPendingInsert	= 0x10000,
	adFieldPendingDelete	= 0x20000,
	adFieldPendingChange	= 0x40000,
	adFieldPendingUnknown	= 0x80000,
	adFieldPendingUnknownDelete	= 0x100000
    }
DECLSPEC_UUID("00000552-0000-0010-8000-00AA006D2EA4")
.enum SeekEnum {
	adSeekFirstEQ	= 0x1,
	adSeekLastEQ	= 0x2,
	adSeekAfterEQ	= 0x4,
	adSeekAfter	= 0x8,
	adSeekBeforeEQ	= 0x10,
	adSeekBefore	= 0x20
    }

ifndef _COMMON_ADC_AND_ADO_PROPS_
_COMMON_ADC_AND_ADO_PROPS_ equ <>
DECLSPEC_UUID("0000054A-0000-0010-8000-00AA006D2EA4")
.enum ADCPROP_UPDATECRITERIA_ENUM {
	adCriteriaKey	= 0,
	adCriteriaAllCols	= 1,
	adCriteriaUpdCols	= 2,
	adCriteriaTimeStamp	= 3
    }
DECLSPEC_UUID("0000054B-0000-0010-8000-00AA006D2EA4")
.enum ADCPROP_ASYNCTHREADPRIORITY_ENUM {
	adPriorityLowest	= 1,
	adPriorityBelowNormal	= 2,
	adPriorityNormal	= 3,
	adPriorityAboveNormal	= 4,
	adPriorityHighest	= 5
    }
DECLSPEC_UUID("00000554-0000-0010-8000-00AA006D2EA4")
.enum ADCPROP_AUTORECALC_ENUM {
	adRecalcUpFront = 0,
	adRecalcAlways	= 1
    }
DECLSPEC_UUID("00000553-0000-0010-8000-00AA006D2EA4")
.enum ADCPROP_UPDATERESYNC_ENUM {
	adResyncNone	= 0,
	adResyncAutoIncrement	= 1,
	adResyncConflicts	= 2,
	adResyncUpdates = 4,
	adResyncInserts = 8,
	adResyncAll	= 15
    }
endif

CEResyncEnum typedef ADCPROP_UPDATERESYNC_ENUM

DECLSPEC_UUID("00000573-0000-0010-8000-00AA006D2EA4")
.enum MoveRecordOptionsEnum {
	adMoveUnspecified	= -1,
	adMoveOverWrite = 1,
	adMoveDontUpdateLinks	= 2,
	adMoveAllowEmulation	= 4
    }
DECLSPEC_UUID("00000574-0000-0010-8000-00AA006D2EA4")
.enum CopyRecordOptionsEnum {
	adCopyUnspecified	= -1,
	adCopyOverWrite = 1,
	adCopyAllowEmulation	= 4,
	adCopyNonRecursive	= 2
    }
DECLSPEC_UUID("00000576-0000-0010-8000-00AA006D2EA4")
.enum StreamTypeEnum {
	adTypeBinary	= 1,
	adTypeText	= 2
    }
DECLSPEC_UUID("00000577-0000-0010-8000-00AA006D2EA4")
.enum LineSeparatorEnum {
	adLF	= 10,
	adCR	= 13,
	adCRLF	= -1
    }
DECLSPEC_UUID("0000057A-0000-0010-8000-00AA006D2EA4")
.enum StreamOpenOptionsEnum {
	adOpenStreamUnspecified = -1,
	adOpenStreamAsync	= 1,
	adOpenStreamFromRecord	= 4
    }
DECLSPEC_UUID("0000057B-0000-0010-8000-00AA006D2EA4")
.enum StreamWriteEnum {
	adWriteChar	= 0,
	adWriteLine	= 1,
	stWriteChar	= 0,
	stWriteLine	= 1
    }
DECLSPEC_UUID("0000057C-0000-0010-8000-00AA006D2EA4")
.enum SaveOptionsEnum {
	adSaveCreateNotExist	= 1,
	adSaveCreateOverWrite	= 2
    }
.enum FieldEnum {
	adDefaultStream = -1,
	adRecordURL	= -2
    }
.enum StreamReadEnum {
	adReadAll	= -1,
	adReadLine	= -2
    }
DECLSPEC_UUID("0000057D-0000-0010-8000-00AA006D2EA4")
.enum RecordTypeEnum {
	adSimpleRecord	= 0,
	adCollectionRecord = 1,
	adStructDoc	= 2
    }

ifndef ___ADOCollection_INTERFACE_DEFINED__
___ADOCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_ADOCollection, "00000512-0000-0010-8000-00AA006D2EA4")

.comdef _ADOCollection : public IUnknown

    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc

    .ends

endif

ifndef ___ADODynaCollection_INTERFACE_DEFINED__
___ADODynaCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_ADODynaCollection, "00000513-0000-0010-8000-00AA006D2EA4")

.comdef _ADODynaCollection : public _ADOCollection

    Append		proc :ptr
    Delete		proc :VARIANT

    .ends

endif

ifndef ___ADO_INTERFACE_DEFINED__
___ADO_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_ADO, "00000534-0000-0010-8000-00AA006D2EA4")

.comdef _ADO : public IUnknown

    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr

    .ends

endif

ifndef __Error_INTERFACE_DEFINED__
__Error_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Error, "00000500-0000-0010-8000-00AA006D2EA4")

.comdef Error : public IUnknown

    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Number		proc :ptr
    get_Source		proc :ptr
    get_Description	proc :ptr
    get_HelpFile	proc :ptr
    get_HelpContext	proc :ptr
    get_SQLState	proc :ptr
    get_NativeError	proc :ptr

    .ends

endif

ifndef __Errors_INTERFACE_DEFINED__
__Errors_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Errors, "00000501-0000-0010-8000-00AA006D2EA4")

.comdef Errors : public IUnknown

    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc

    get_Item		proc :VARIANT, :ptr
    Clear		proc

    .ends

endif

ifndef __Command15_INTERFACE_DEFINED__
__Command15_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Command15, "00000508-0000-0010-8000-00AA006D2EA4")

.comdef Command15 : public _ADO

    get_ActiveConnection proc :ptr
    putref_ActiveADOConnection proc :ptr
    put_ActiveConnection proc :VARIANT
    get_CommandText	proc :ptr
    put_CommandText	proc :BSTR
    get_CommandTimeout	proc :ptr
    put_CommandTimeout	proc :LONG
    get_Prepared	proc :ptr
    put_Prepared	proc :VARIANT_BOOL
    Execute		proc :ptr, :ptr, :LONG, :ptr
    CreateParameter	proc :BSTR, :DataTypeEnum, :ParameterDirectionEnum, :ADO_LONGPTR, :VARIANT, :ptr
    get_Parameters	proc :ptr
    put_CommandType	proc :CommandTypeEnum
    get_CommandType	proc :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR

    .ends

endif

ifndef __Command25_INTERFACE_DEFINED__
__Command25_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Command25, "0000054E-0000-0010-8000-00AA006D2EA4")

.comdef Command25 : public Command15

    get_State		proc :ptr
    Cancel		proc

    .ends

endif

ifndef ___Command_INTERFACE_DEFINED__
___Command_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_Command, "B08400BD-F9D1-4D02-B856-71D5DBA123E9")

.comdef _Command : public _ADO

    get_ActiveConnection proc :ptr
    putref_ActiveADOConnection proc :ptr
    put_ActiveConnection proc :VARIANT
    get_CommandText	proc :ptr
    put_CommandText	proc :BSTR
    get_CommandTimeout	proc :ptr
    put_CommandTimeout	proc :LONG
    get_Prepared	proc :ptr
    put_Prepared	proc :VARIANT_BOOL
    Execute		proc :ptr, :ptr, :LONG, :ptr
    CreateParameter	proc :BSTR, :DataTypeEnum, :ParameterDirectionEnum, :ADO_LONGPTR, :VARIANT, :ptr
    get_Parameters	proc :ptr
    put_CommandType	proc :CommandTypeEnum
    get_CommandType	proc :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_State		proc :ptr
    Cancel		proc
    putref_CommandADOStream proc :ptr
    get_CommandStream	proc :ptr
    put_Dialect		proc :BSTR
    get_Dialect		proc :ptr
    put_NamedParameters proc :VARIANT_BOOL
    get_NamedParameters proc :ptr

    .ends

endif

ifndef __ConnectionEventsVt_INTERFACE_DEFINED__
__ConnectionEventsVt_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ConnectionEventsVt, "00000402-0000-0010-8000-00AA006D2EA4")

.comdef ConnectionEventsVt : public IUnknown

    InfoMessage		proc :ptr, :ptr, :ptr
    BeginTransComplete	proc :LONG, :ptr, :ptr, :ptr
    CommitTransComplete proc :ptr, :ptr, :ptr
    RollbackTransComplete proc :ptr, :ptr, :ptr
    WillExecute		proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    ExecuteComplete	proc :LONG, :ptr, :ptr, :ptr, :ptr, :ptr
    WillConnect		proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    ConnectComplete	proc :ptr, :ptr, :ptr
    Disconnect		proc :ptr, :ptr

    .ends

endif

ifndef __RecordsetEventsVt_INTERFACE_DEFINED__
__RecordsetEventsVt_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(RecordsetEventsVt, "00000403-0000-0010-8000-00AA006D2EA4")

.comdef RecordsetEventsVt : public IUnknown

    WillChangeADOField	proc :LONG, :VARIANT, :ptr, :ptr
    FieldChangeComplete proc :LONG, :VARIANT, :ptr, :ptr, :ptr
    WillChangeADORecord proc :EventReasonEnum, :LONG, :ptr, :ptr
    RecordChangeComplete proc :EventReasonEnum, :LONG, :ptr, :ptr, :ptr
    WillChangeADORecordset proc :EventReasonEnum, :ptr, :ptr
    RecordsetChangeComplete proc :EventReasonEnum, :ptr, :ptr, :ptr
    WillMove		proc :EventReasonEnum, :ptr, :ptr
    MoveComplete	proc :EventReasonEnum, :ptr, :ptr, :ptr
    EndOfADORecordset	proc :ptr, :ptr, :ptr
    FetchProgress	proc :LONG, :LONG, :ptr, :ptr
    FetchComplete	proc :ptr, :ptr, :ptr

    .ends

endif

ifndef __ConnectionEvents_DISPINTERFACE_DEFINED__
__ConnectionEvents_DISPINTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ConnectionEvents, "00000400-0000-0010-8000-00AA006D2EA4")

.comdef ConnectionEvents : public IUnknown

    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr

    .ends

endif

ifndef __RecordsetEvents_DISPINTERFACE_DEFINED__
__RecordsetEvents_DISPINTERFACE_DEFINED__ equ 1

DEFINE_IIDX(RecordsetEvents, "00000266-0000-0010-8000-00AA006D2EA4")

.comdef RecordsetEvents : public IUnknown

    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr

    .ends

endif

ifndef __Connection15_INTERFACE_DEFINED__
__Connection15_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Connection15, "00000515-0000-0010-8000-00AA006D2EA4")

.comdef Connection15 : public RecordsetEvents

    get_Properties	proc :ptr
    get_ConnectionString proc :ptr
    put_ConnectionString proc :BSTR
    get_CommandTimeout	proc :ptr
    put_CommandTimeout	proc :LONG
    get_ConnectionTimeout proc :ptr
    put_ConnectionTimeout proc :LONG
    get_Version		proc :ptr
    Close		proc
    Execute		proc :BSTR, :ptr, :LONG, :ptr
    BeginTrans		proc :ptr
    CommitTrans		proc
    RollbackTrans	proc
    Open		proc :BSTR, :BSTR, :BSTR, :LONG
    get_Errors		proc :ptr
    get_DefaultDatabase proc :ptr
    put_DefaultDatabase proc :BSTR
    get_IsolationLevel	proc :ptr
    put_IsolationLevel	proc :IsolationLevelEnum
    get_Attributes	proc :ptr
    put_Attributes	proc :LONG
    get_CursorLocation	proc :ptr
    put_CursorLocation	proc :CursorLocationEnum
    get_Mode		proc :ptr
    put_Mode		proc :ConnectModeEnum
    get_Provider	proc :ptr
    put_Provider	proc :BSTR
    get_State		proc :ptr
    OpenSchema		proc :SchemaEnum, :VARIANT, :VARIANT, :ptr

    .ends

endif

ifndef ___Connection_INTERFACE_DEFINED__
___Connection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_Connection, "00000550-0000-0010-8000-00AA006D2EA4")

.comdef _Connection : public Connection15

    Cancel		proc

    .ends

endif

ifndef __ADOConnectionConstruction15_INTERFACE_DEFINED__
__ADOConnectionConstruction15_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ADOConnectionConstruction15, "00000516-0000-0010-8000-00AA006D2EA4")

.comdef ADOConnectionConstruction15 : public IUnknown

    get_DSO		proc :ptr
    get_Session		proc :ptr
    WrapDSOandSession	proc :ptr, :ptr

    .ends

endif

ifndef __ADOConnectionConstruction_INTERFACE_DEFINED__
__ADOConnectionConstruction_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ADOConnectionConstruction, "00000551-0000-0010-8000-00AA006D2EA4")

.comdef ADOConnectionConstruction : public ADOConnectionConstruction15

    .ends

endif
externdef		CLSID_Connection:CLSID

ifndef ___Record_INTERFACE_DEFINED__
___Record_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_Record, "00000562-0000-0010-8000-00AA006D2EA4")

.comdef _Record : public _ADO

    get_ActiveConnection proc :ptr
    put_ActiveConnection proc :BSTR
    putref_ActiveADOConnection proc :ptr
    get_State		proc :ptr
    get_Source		proc :ptr
    put_Source		proc :BSTR
    putref_Source	proc :ptr
    get_Mode		proc :ptr
    put_Mode		proc :ConnectModeEnum
    get_ParentURL	proc :ptr
    MoveADORecord	proc :BSTR, :BSTR, :BSTR, :BSTR, :MoveRecordOptionsEnum, :VARIANT_BOOL, :ptr
    CopyADORecord	proc :BSTR, :BSTR, :BSTR, :BSTR, :CopyRecordOptionsEnum, :VARIANT_BOOL, :ptr
    DeleteADORecord	proc :BSTR, :VARIANT_BOOL
    Open		proc :VARIANT, :VARIANT, :ConnectModeEnum, :RecordCreateOptionsEnum, :RecordOpenOptionsEnum, :BSTR, :BSTR
    Close		proc
    get_Fields		proc :ptr
    get_RecordType	proc :ptr
    GetChildren		proc :ptr
    Cancel		proc

    .ends

endif
externdef		CLSID_Record:CLSID

ifndef ___Stream_INTERFACE_DEFINED__
___Stream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_Stream, "00000565-0000-0010-8000-00AA006D2EA4")

.comdef _Stream : public RecordsetEvents

    get_Size		proc :ptr
    get_EOS		proc :ptr
    get_Position	proc :ptr
    put_Position	proc :ADO_LONGPTR
    get_Type		proc :ptr
    put_Type		proc :StreamTypeEnum
    get_LineSeparator	proc :ptr
    put_LineSeparator	proc :LineSeparatorEnum
    get_State		proc :ptr
    get_Mode		proc :ptr
    put_Mode		proc :ConnectModeEnum
    get_Charset		proc :ptr
    put_Charset		proc :BSTR
    Read		proc :LONG, :ptr
    Open		proc :VARIANT, :ConnectModeEnum, :StreamOpenOptionsEnum, :BSTR, :BSTR
    Close		proc
    SkipLine		proc
    Write		proc :VARIANT
    SetEOS		proc
    CopyTo		proc :ptr, :ADO_LONGPTR
    Flush		proc
    SaveToFile		proc :BSTR, :SaveOptionsEnum
    LoadFromFile	proc :BSTR
    ReadText		proc :LONG, :ptr
    WriteText		proc :BSTR, :StreamWriteEnum
    Cancel		proc

    .ends

endif
externdef		CLSID_Stream:CLSID

ifndef __ADORecordConstruction_INTERFACE_DEFINED__
__ADORecordConstruction_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ADORecordConstruction, "00000567-0000-0010-8000-00AA006D2EA4")

.comdef ADORecordConstruction : public RecordsetEvents

    get_Row		proc :ptr
    put_Row		proc :ptr
    put_ParentRow	proc :ptr

    .ends

endif

ifndef __ADOStreamConstruction_INTERFACE_DEFINED__
__ADOStreamConstruction_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ADOStreamConstruction, "00000568-0000-0010-8000-00AA006D2EA4")

.comdef ADOStreamConstruction : public RecordsetEvents

    get_Stream		proc :ptr
    put_Stream		proc :ptr

    .ends

endif

ifndef __ADOCommandConstruction_INTERFACE_DEFINED__
__ADOCommandConstruction_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ADOCommandConstruction, "00000517-0000-0010-8000-00AA006D2EA4")

.comdef ADOCommandConstruction : public IUnknown

    get_OLEDBCommand	proc :ptr
    put_OLEDBCommand	proc :ptr

    .ends

endif
externdef		CLSID_Command:CLSID
externdef		CLSID_Recordset:CLSID

ifndef __Recordset15_INTERFACE_DEFINED__
__Recordset15_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Recordset15, "0000050E-0000-0010-8000-00AA006D2EA4")

.comdef Recordset15 : public _ADO

    get_AbsolutePosition proc :ptr
    put_AbsolutePosition proc :PositionEnum_Param
    putref_ActiveADOConnection proc :ptr
    put_ActiveConnection proc :VARIANT
    get_ActiveConnection proc :ptr
    get_BOF		proc :ptr
    get_Bookmark	proc :ptr
    put_Bookmark	proc :VARIANT
    get_CacheSize	proc :ptr
    put_CacheSize	proc :LONG
    get_CursorType	proc :ptr
    put_CursorType	proc :CursorTypeEnum
    get_EOF		proc :ptr
    get_Fields		proc :ptr
    get_LockType	proc :ptr
    put_LockType	proc :LockTypeEnum
    get_MaxRecords	proc :ptr
    put_MaxRecords	proc :ADO_LONGPTR
    get_RecordCount	proc :ptr
    putref_Source	proc :ptr
    put_Source		proc :BSTR
    get_Source		proc :ptr
    AddNew		proc :VARIANT, :VARIANT
    CancelUpdate	proc
    Close		proc
    Delete		proc :AffectEnum
    GetRows		proc :LONG, :VARIANT, :VARIANT, :ptr
    Move		proc :ADO_LONGPTR, :VARIANT
    MoveNext		proc
    MovePrevious	proc
    MoveFirst		proc
    MoveLast		proc
    Open		proc :VARIANT, :VARIANT, :CursorTypeEnum, :LockTypeEnum, :LONG
    Requery		proc :LONG
    _xResync		proc :AffectEnum
    Update		proc :VARIANT, :VARIANT
    get_AbsolutePage	proc :ptr
    put_AbsolutePage	proc :PositionEnum_Param
    get_EditMode	proc :ptr
    get_Filter		proc :ptr
    put_Filter		proc :VARIANT
    get_PageCount	proc :ptr
    get_PageSize	proc :ptr
    put_PageSize	proc :LONG
    get_Sort		proc :ptr
    put_Sort		proc :BSTR
    get_Status		proc :ptr
    get_State		proc :ptr
    _xClone		proc :ptr
    UpdateBatch		proc :AffectEnum
    CancelBatch		proc :AffectEnum
    get_CursorLocation	proc :ptr
    put_CursorLocation	proc :CursorLocationEnum
    NextADORecordset	proc :ptr, :ptr
    Supports		proc :CursorOptionEnum, :ptr
    get_Collect		proc :VARIANT, :ptr
    put_Collect		proc :VARIANT, :VARIANT
    get_MarshalOptions	proc :ptr
    put_MarshalOptions	proc :MarshalOptionsEnum
    Find		proc :BSTR, :ADO_LONGPTR, :SearchDirectionEnum, :VARIANT

    .ends

endif

ifndef __Recordset20_INTERFACE_DEFINED__
__Recordset20_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Recordset20, "0000054F-0000-0010-8000-00AA006D2EA4")

.comdef Recordset20 : public Recordset15

    Cancel		proc
    get_DataSource	proc :ptr
    putref_DataSource	proc :ptr
    _xSave		proc :BSTR, :PersistFormatEnum
    get_ActiveCommand	proc :ptr
    put_StayInSync	proc :VARIANT_BOOL
    get_StayInSync	proc :ptr
    GetString		proc :StringFormatEnum, :LONG, :BSTR, :BSTR, :BSTR, :ptr
    get_DataMember	proc :ptr
    put_DataMember	proc :BSTR
    CompareBookmarks	proc :VARIANT, :VARIANT, :ptr
    Clone		proc :LockTypeEnum, :ptr
    Resync		proc :AffectEnum, :ResyncEnum

    .ends

endif

ifndef __Recordset21_INTERFACE_DEFINED__
__Recordset21_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Recordset21, "00000555-0000-0010-8000-00AA006D2EA4")

.comdef Recordset21 : public Recordset20

    Seek		proc :VARIANT, :SeekEnum
    put_Index		proc :BSTR
    get_Index		proc :ptr

    .ends

endif

ifndef ___Recordset_INTERFACE_DEFINED__
___Recordset_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_Recordset, "00000556-0000-0010-8000-00AA006D2EA4")

.comdef _Recordset : public Recordset21

    Save		proc :VARIANT, :PersistFormatEnum

    .ends

endif

ifndef __ADORecordsetConstruction_INTERFACE_DEFINED__
__ADORecordsetConstruction_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(ADORecordsetConstruction, "00000283-0000-0010-8000-00AA006D2EA4")

.comdef ADORecordsetConstruction : public RecordsetEvents

    get_Rowset		proc :ptr
    put_Rowset		proc :ptr
    get_Chapter		proc :ptr
    put_Chapter		proc :ADO_LONGPTR
    get_RowPosition	proc :ptr
    put_RowPosition	proc :ptr

    .ends

endif

ifndef __Field15_INTERFACE_DEFINED__
__Field15_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(Field15, "00000505-0000-0010-8000-00AA006D2EA4")

.comdef Field15 : public RecordsetEvents

    get_Properties	proc :ptr
    get_ActualSize	proc :ptr
    get_Attributes	proc :ptr
    get_DefinedSize	proc :ptr
    get_Name		proc :ptr
    get_Type		proc :ptr
    get_Value		proc :ptr
    put_Value		proc :VARIANT
    get_Precision	proc :ptr
    get_NumericScale	proc :ptr
    AppendChunk		proc :VARIANT
    GetChunk		proc :LONG, :ptr
    get_OriginalValue	proc :ptr
    get_UnderlyingValue proc :ptr

    .ends

endif

ifndef __Field20_INTERFACE_DEFINED__
__Field20_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Field20, "0000054C-0000-0010-8000-00AA006D2EA4")

.comdef Field20 : public Field15

    get_DataFormat	proc :ptr
    putref_DataFormat	proc :ptr
    put_Precision	proc :BYTE
    put_NumericScale	proc :BYTE
    put_Type		proc :DataTypeEnum
    put_DefinedSize	proc :ADO_LONGPTR
    put_Attributes	proc :LONG

    .ends

endif

ifndef __Field_INTERFACE_DEFINED__
__Field_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(Field, "00000569-0000-0010-8000-00AA006D2EA4")

.comdef Field : public Field20

    get_Status		proc :ptr

    .ends

endif

ifndef __Fields15_INTERFACE_DEFINED__
__Fields15_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Fields15, "00000506-0000-0010-8000-00AA006D2EA4")

.comdef Fields15 : public RecordsetEvents

    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr

    .ends

endif

ifndef __Fields20_INTERFACE_DEFINED__
__Fields20_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Fields20, "0000054D-0000-0010-8000-00AA006D2EA4")

.comdef Fields20 : public Fields15

    _Append		proc :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum
    Delete		proc :VARIANT

    .ends

endif

ifndef __Fields_INTERFACE_DEFINED__
__Fields_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Fields, "00000564-0000-0010-8000-00AA006D2EA4")

.comdef Fields : public Fields20

    Append		proc :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum, :VARIANT
    Update		proc
    Resync		proc :ResyncEnum
    CancelUpdate	proc

    .ends

endif

ifndef ___Parameter_INTERFACE_DEFINED__
___Parameter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(_Parameter, "0000050C-0000-0010-8000-00AA006D2EA4")

.comdef _Parameter : public RecordsetEvents

    get_Properties	proc :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_Value		proc :ptr
    put_Value		proc :VARIANT
    get_Type		proc :ptr
    put_Type		proc :DataTypeEnum
    put_Direction	proc :ParameterDirectionEnum
    get_Direction	proc :ptr
    put_Precision	proc :BYTE
    get_Precision	proc :ptr
    put_NumericScale	proc :BYTE
    get_NumericScale	proc :ptr
    put_Size		proc :ADO_LONGPTR
    get_Size		proc :ptr
    AppendChunk		proc :VARIANT
    get_Attributes	proc :ptr
    put_Attributes	proc :LONG

    .ends

endif
externdef		CLSID_Parameter:CLSID

ifdef __cplusplus
Parameter;
endif

ifndef __Parameters_INTERFACE_DEFINED__
__Parameters_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Parameters, "0000050D-0000-0010-8000-00AA006D2EA4")

.comdef Parameters : public RecordsetEvents

    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    Append		proc :ptr
    Delete		proc :VARIANT
    get_Item		proc :VARIANT, :ptr

    .ends

endif

ifndef __Property_INTERFACE_DEFINED__
__Property_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Property, "00000503-0000-0010-8000-00AA006D2EA4")

.comdef Property : public RecordsetEvents

    get_Value		proc :ptr
    put_Value		proc :VARIANT
    get_Name		proc :ptr
    get_Type		proc :ptr
    get_Attributes	proc :ptr
    put_Attributes	proc :LONG

    .ends

endif

ifndef __Properties_INTERFACE_DEFINED__
__Properties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Properties, "00000504-0000-0010-8000-00AA006D2EA4")

.comdef Properties : public RecordsetEvents

    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr

    .ends

endif

endif
endif

.pragma list(pop)
endif

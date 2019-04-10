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
CursorTypeEnum		typedef SDWORD
adOpenUnspecified	equ -1
adOpenForwardOnly	equ 0
adOpenKeyset		equ 1
adOpenDynamic		equ 2
adOpenStatic		equ 3
DECLSPEC_UUID("0000051C-0000-0010-8000-00AA006D2EA4")
CursorOptionEnum	typedef SDWORD
adHoldRecords		equ 0x100
adMovePrevious		equ 0x200
adAddNew		equ 0x1000400
adDelete		equ 0x1000800
adUpdate		equ 0x1008000
adBookmark		equ 0x2000
adApproxPosition	equ 0x4000
adUpdateBatch		equ 0x10000
adResync		equ 0x20000
adNotify		equ 0x40000
adFind			equ 0x80000
adSeek			equ 0x400000
adIndex			equ 0x800000
DECLSPEC_UUID("0000051D-0000-0010-8000-00AA006D2EA4")
LockTypeEnum		typedef SDWORD
adLockUnspecified	equ -1
adLockReadOnly		equ 1
adLockPessimistic	equ 2
adLockOptimistic	equ 3
adLockBatchOptimistic	equ 4
DECLSPEC_UUID("0000051E-0000-0010-8000-00AA006D2EA4")
ExecuteOptionEnum	typedef SDWORD
adOptionUnspecified	equ -1
adAsyncExecute		equ 0x10
adAsyncFetch		equ 0x20
adAsyncFetchNonBlocking equ 0x40
adExecuteNoRecords	equ 0x80
adExecuteStream		equ 0x400
adExecuteRecord		equ 0x800
DECLSPEC_UUID("00000541-0000-0010-8000-00AA006D2EA4")
ConnectOptionEnum	typedef SDWORD
adConnectUnspecified	equ -1
adAsyncConnect		equ 0x10
DECLSPEC_UUID("00000532-0000-0010-8000-00AA006D2EA4")
ObjectStateEnum		typedef SDWORD
adStateClosed		equ 0
adStateOpen		equ 0x1
adStateConnecting	equ 0x2
adStateExecuting	equ 0x4
adStateFetching		equ 0x8
DECLSPEC_UUID("0000052F-0000-0010-8000-00AA006D2EA4")
CursorLocationEnum	typedef SDWORD
adUseNone		equ 1
adUseServer		equ 2
adUseClient		equ 3
adUseClientBatch	equ 3
DECLSPEC_UUID("0000051F-0000-0010-8000-00AA006D2EA4")
DataTypeEnum		typedef SDWORD
adEmpty			equ 0
adTinyInt		equ 16
adSmallInt		equ 2
adInteger		equ 3
adBigInt		equ 20
adUnsignedTinyInt	equ 17
adUnsignedSmallInt	equ 18
adUnsignedInt		equ 19
adUnsignedBigInt	equ 21
adSingle		equ 4
adDouble		equ 5
adCurrency		equ 6
adDecimal		equ 14
adNumeric		equ 131
adBoolean		equ 11
adError			equ 10
adUserDefined		equ 132
adVariant		equ 12
adIDispatch		equ 9
adIUnknown		equ 13
adGUID			equ 72
adDate			equ 7
adDBDate		equ 133
adDBTime		equ 134
adDBTimeStamp		equ 135
adBSTR			equ 8
adChar			equ 129
adVarChar		equ 200
adLongVarChar		equ 201
adWChar			equ 130
adVarWChar		equ 202
adLongVarWChar		equ 203
adBinary		equ 128
adVarBinary		equ 204
adLongVarBinary		equ 205
adChapter		equ 136
adFileTime		equ 64
adPropVariant		equ 138
adVarNumeric		equ 139
adArray			equ 0x2000
DECLSPEC_UUID("00000525-0000-0010-8000-00AA006D2EA4")
FieldAttributeEnum	typedef SDWORD
adFldUnspecified	equ -1
adFldMayDefer		equ 0x2
adFldUpdatable		equ 0x4
adFldUnknownUpdatable	equ 0x8
adFldFixed		equ 0x10
adFldIsNullable		equ 0x20
adFldMayBeNull		equ 0x40
adFldLong		equ 0x80
adFldRowID		equ 0x100
adFldRowVersion		equ 0x200
adFldCacheDeferred	equ 0x1000
adFldIsChapter		equ 0x2000
adFldNegativeScale	equ 0x4000
adFldKeyColumn		equ 0x8000
adFldIsRowURL		equ 0x10000
adFldIsDefaultStream	equ 0x20000
adFldIsCollection	equ 0x40000
DECLSPEC_UUID("00000526-0000-0010-8000-00AA006D2EA4")
EditModeEnum		typedef SDWORD
adEditNone		equ 0
adEditInProgress	equ 0x1
adEditAdd		equ 0x2
adEditDelete		equ 0x4
DECLSPEC_UUID("00000527-0000-0010-8000-00AA006D2EA4")
RecordStatusEnum	typedef SDWORD
adRecOK			equ 0
adRecNew		equ 0x1
adRecModified		equ 0x2
adRecDeleted		equ 0x4
adRecUnmodified		equ 0x8
adRecInvalid		equ 0x10
adRecMultipleChanges	equ 0x40
adRecPendingChanges	equ 0x80
adRecCanceled		equ 0x100
adRecCantRelease	equ 0x400
adRecConcurrencyViolation equ 0x800
adRecIntegrityViolation equ 0x1000
adRecMaxChangesExceeded equ 0x2000
adRecObjectOpen		equ 0x4000
adRecOutOfMemory	equ 0x8000
adRecPermissionDenied	equ 0x10000
adRecSchemaViolation	equ 0x20000
adRecDBDeleted		equ 0x40000
DECLSPEC_UUID("00000542-0000-0010-8000-00AA006D2EA4")
GetRowsOptionEnum	typedef SDWORD
adGetRowsRest		equ -1
DECLSPEC_UUID("00000528-0000-0010-8000-00AA006D2EA4")
PositionEnum		typedef SDWORD
adPosUnknown		equ -1
adPosBOF		equ -2
adPosEOF		equ -3
ifdef _WIN64
PositionEnum_Param	typedef LONGLONG
else
PositionEnum_Param	typedef PositionEnum
endif
BookmarkEnum		typedef SDWORD
adBookmarkCurrent	equ 0
adBookmarkFirst		equ 1
adBookmarkLast		equ 2
DECLSPEC_UUID("00000540-0000-0010-8000-00AA006D2EA4")
MarshalOptionsEnum	typedef SDWORD
adMarshalAll		equ 0
adMarshalModifiedOnly	equ 1
DECLSPEC_UUID("00000543-0000-0010-8000-00AA006D2EA4")
AffectEnum		typedef SDWORD
adAffectCurrent		equ 1
adAffectGroup		equ 2
adAffectAll		equ 3
adAffectAllChapters	equ 4
DECLSPEC_UUID("00000544-0000-0010-8000-00AA006D2EA4")
ResyncEnum		typedef SDWORD
adResyncUnderlyingValues equ 1
adResyncAllValues	equ 2
DECLSPEC_UUID("00000545-0000-0010-8000-00AA006D2EA4")
CompareEnum		typedef SDWORD
adCompareLessThan	equ 0
adCompareEqual		equ 1
adCompareGreaterThan	equ 2
adCompareNotEqual	equ 3
adCompareNotComparable	equ 4
DECLSPEC_UUID("00000546-0000-0010-8000-00AA006D2EA4")
FilterGroupEnum		typedef SDWORD
adFilterNone		equ 0
adFilterPendingRecords	equ 1
adFilterAffectedRecords equ 2
adFilterFetchedRecords	equ 3
adFilterPredicate	equ 4
adFilterConflictingRecords equ 5
DECLSPEC_UUID("00000547-0000-0010-8000-00AA006D2EA4")
SearchDirectionEnum	typedef SDWORD
adSearchForward		equ 1
adSearchBackward	equ -1
SearchDirection		typedef	 SearchDirectionEnum
DECLSPEC_UUID("00000548-0000-0010-8000-00AA006D2EA4")
PersistFormatEnum	typedef SDWORD
adPersistADTG		equ 0
adPersistXML		equ 1
DECLSPEC_UUID("00000549-0000-0010-8000-00AA006D2EA4")
StringFormatEnum	typedef SDWORD
adClipString		equ 2
DECLSPEC_UUID("00000520-0000-0010-8000-00AA006D2EA4")
ConnectPromptEnum	typedef SDWORD
adPromptAlways		equ 1
adPromptComplete	equ 2
adPromptCompleteRequired equ 3
adPromptNever		equ 4
DECLSPEC_UUID("00000521-0000-0010-8000-00AA006D2EA4")
ConnectModeEnum		typedef SDWORD
adModeUnknown		equ 0
adModeRead		equ 1
adModeWrite		equ 2
adModeReadWrite		equ 3
adModeShareDenyRead	equ 4
adModeShareDenyWrite	equ 8
adModeShareExclusive	equ 0xc
adModeShareDenyNone	equ 0x10
adModeRecursive		equ 0x400000
DECLSPEC_UUID("00000570-0000-0010-8000-00AA006D2EA4")
RecordCreateOptionsEnum typedef SDWORD
adCreateCollection	equ 0x2000
adCreateStructDoc	equ 0x80000000
adCreateNonCollection	equ 0
adOpenIfExists		equ 0x2000000
adCreateOverwrite	equ 0x4000000
adFailIfNotExists	equ -1
DECLSPEC_UUID("00000571-0000-0010-8000-00AA006D2EA4")
RecordOpenOptionsEnum	typedef SDWORD
adOpenRecordUnspecified equ -1
adOpenSource		equ 0x800000
adOpenOutput		equ 0x800000
adOpenAsync		equ 0x1000
adDelayFetchStream	equ 0x4000
adDelayFetchFields	equ 0x8000
adOpenExecuteCommand	equ 0x10000
DECLSPEC_UUID("00000523-0000-0010-8000-00AA006D2EA4")
IsolationLevelEnum	typedef SDWORD
adXactUnspecified	equ 0xffffffff
adXactChaos		equ 0x10
adXactReadUncommitted	equ 0x100
adXactBrowse		equ 0x100
adXactCursorStability	equ 0x1000
adXactReadCommitted	equ 0x1000
adXactRepeatableRead	equ 0x10000
adXactSerializable	equ 0x100000
adXactIsolated		equ 0x100000
DECLSPEC_UUID("00000524-0000-0010-8000-00AA006D2EA4")
XactAttributeEnum	typedef SDWORD
adXactCommitRetaining	equ 0x20000
adXactAbortRetaining	equ 0x40000
adXactAsyncPhaseOne	equ 0x80000
adXactSyncPhaseOne	equ 0x100000
DECLSPEC_UUID("00000529-0000-0010-8000-00AA006D2EA4")
PropertyAttributesEnum	typedef SDWORD
adPropNotSupported	equ 0
adPropRequired		equ 0x1
adPropOptional		equ 0x2
adPropRead		equ 0x200
adPropWrite		equ 0x400
DECLSPEC_UUID("0000052A-0000-0010-8000-00AA006D2EA4")
ErrorValueEnum		typedef SDWORD
adErrProviderFailed	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbb8)
adErrInvalidArgument	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbb9)
adErrOpeningFile	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbba)
adErrReadFile		equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbbb)
adErrWriteFile		equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbbc)
adErrNoCurrentRecord	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xbcd)
adErrIllegalOperation	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xc93)
adErrCantChangeProvider equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xc94)
adErrInTransaction	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xcae)
adErrFeatureNotAvailable equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xcb3)
adErrItemNotFound	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xcc1)
adErrObjectInCollection equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xd27)
adErrObjectNotSet	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xd5c)
adErrDataConversion	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xd5d)
adErrObjectClosed	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe78)
adErrObjectOpen		equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe79)
adErrProviderNotFound	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7a)
adErrBoundToCommand	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7b)
adErrInvalidParamInfo	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7c)
adErrInvalidConnection	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7d)
adErrNotReentrant	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7e)
adErrStillExecuting	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe7f)
adErrOperationCancelled equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe80)
adErrStillConnecting	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe81)
adErrInvalidTransaction equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe82)
adErrNotExecuting	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe83)
adErrUnsafeOperation	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe84)
adwrnSecurityDialog	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe85)
adwrnSecurityDialogHeader equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe86)
adErrIntegrityViolation equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe87)
adErrPermissionDenied	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe88)
adErrDataOverflow	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe89)
adErrSchemaViolation	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8a)
adErrSignMismatch	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8b)
adErrCantConvertvalue	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8c)
adErrCantCreate		equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8d)
adErrColumnNotOnThisRow equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8e)
adErrURLDoesNotExist	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe8f)
adErrTreePermissionDenied equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe90)
adErrInvalidURL		equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe91)
adErrResourceLocked	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe92)
adErrResourceExists	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe93)
adErrCannotComplete	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe94)
adErrVolumeNotFound	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe95)
adErrOutOfSpace		equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe96)
adErrResourceOutOfScope equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe97)
adErrUnavailable	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe98)
adErrURLNamedRowDoesNotExist equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,	 0xe99)
adErrDelResOutOfScope	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9a)
adErrPropInvalidColumn	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9b)
adErrPropInvalidOption	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9c)
adErrPropInvalidValue	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9d)
adErrPropConflicting	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9e)
adErrPropNotAllSettable equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xe9f)
adErrPropNotSet		equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea0)
adErrPropNotSettable	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea1)
adErrPropNotSupported	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea2)
adErrCatalogNotSet	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea3)
adErrCantChangeConnection equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea4)
adErrFieldsUpdateFailed equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea5)
adErrDenyNotSupported	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea6)
adErrDenyTypeNotSupported equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea7)
adErrProviderNotSpecified equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xea9)
adErrConnectionStringTooLong equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL
DECLSPEC_UUID("0000052B-0000-0010-8000-00AA006D2EA4")
ParameterAttributesEnum typedef SDWORD
adParamSigned		equ 0x10
adParamNullable		equ 0x40
adParamLong		equ 0x80
DECLSPEC_UUID("0000052C-0000-0010-8000-00AA006D2EA4")
ParameterDirectionEnum	typedef SDWORD
adParamUnknown		equ 0
adParamInput		equ 0x1
adParamOutput		equ 0x2
adParamInputOutput	equ 0x3
adParamReturnValue	equ 0x4
DECLSPEC_UUID("0000052E-0000-0010-8000-00AA006D2EA4")
CommandTypeEnum		typedef SDWORD
adCmdUnspecified	equ -1
adCmdUnknown		equ 0x8
adCmdText		equ 0x1
adCmdTable		equ 0x2
adCmdStoredProc		equ 0x4
adCmdFile		equ 0x100
adCmdTableDirect	equ 0x200
DECLSPEC_UUID("00000530-0000-0010-8000-00AA006D2EA4")
EventStatusEnum		typedef SDWORD
adStatusOK		equ 0x1
adStatusErrorsOccurred	equ 0x2
adStatusCantDeny	equ 0x3
adStatusCancel		equ 0x4
adStatusUnwantedEvent	equ 0x5
DECLSPEC_UUID("00000531-0000-0010-8000-00AA006D2EA4")
EventReasonEnum		typedef SDWORD
adRsnAddNew		equ 1
adRsnDelete		equ 2
adRsnUpdate		equ 3
adRsnUndoUpdate		equ 4
adRsnUndoAddNew		equ 5
adRsnUndoDelete		equ 6
adRsnRequery		equ 7
adRsnResynch		equ 8
adRsnClose		equ 9
adRsnMove		equ 10
adRsnFirstChange	equ 11
adRsnMoveFirst		equ 12
adRsnMoveNext		equ 13
adRsnMovePrevious	equ 14
adRsnMoveLast		equ 15
DECLSPEC_UUID("00000533-0000-0010-8000-00AA006D2EA4")
SchemaEnum		typedef SDWORD
adSchemaProviderSpecific equ -1
adSchemaAsserts		equ 0
adSchemaCatalogs	equ 1
adSchemaCharacterSets	equ 2
adSchemaCollations	equ 3
adSchemaColumns		equ 4
adSchemaCheckConstraints equ 5
adSchemaConstraintColumnUsage equ 6
adSchemaConstraintTableUsage equ 7
adSchemaKeyColumnUsage	equ 8
adSchemaReferentialContraints equ 9
adSchemaReferentialConstraints equ 9
adSchemaTableConstraints equ 10
adSchemaColumnsDomainUsage equ 11
adSchemaIndexes		equ 12
adSchemaColumnPrivileges equ 13
adSchemaTablePrivileges equ 14
adSchemaUsagePrivileges equ 15
adSchemaProcedures	equ 16
adSchemaSchemata	equ 17
adSchemaSQLLanguages	equ 18
adSchemaStatistics	equ 19
adSchemaTables		equ 20
adSchemaTranslations	equ 21
adSchemaProviderTypes	equ 22
adSchemaViews		equ 23
adSchemaViewColumnUsage equ 24
adSchemaViewTableUsage	equ 25
adSchemaProcedureParameters equ 26
adSchemaForeignKeys	equ 27
adSchemaPrimaryKeys	equ 28
adSchemaProcedureColumns equ 29
adSchemaDBInfoKeywords	equ 30
adSchemaDBInfoLiterals	equ 31
adSchemaCubes		equ 32
adSchemaDimensions	equ 33
adSchemaHierarchies	equ 34
adSchemaLevels		equ 35
adSchemaMeasures	equ 36
adSchemaProperties	equ 37
adSchemaMembers		equ 38
adSchemaTrustees	equ 39
adSchemaFunctions	equ 40
adSchemaActions		equ 41
adSchemaCommands	equ 42
adSchemaSets		equ 43
DECLSPEC_UUID("0000057E-0000-0010-8000-00AA006D2EA4")
FieldStatusEnum		typedef SDWORD
adFieldOK		equ 0
adFieldCantConvertValue equ 2
adFieldIsNull		equ 3
adFieldTruncated	equ 4
adFieldSignMismatch	equ 5
adFieldDataOverflow	equ 6
adFieldCantCreate	equ 7
adFieldUnavailable	equ 8
adFieldPermissionDenied equ 9
adFieldIntegrityViolation equ 10
adFieldSchemaViolation	equ 11
adFieldBadStatus	equ 12
adFieldDefault		equ 13
adFieldIgnore		equ 15
adFieldDoesNotExist	equ 16
adFieldInvalidURL	equ 17
adFieldResourceLocked	equ 18
adFieldResourceExists	equ 19
adFieldCannotComplete	equ 20
adFieldVolumeNotFound	equ 21
adFieldOutOfSpace	equ 22
adFieldCannotDeleteSource equ 23
adFieldReadOnly		equ 24
adFieldResourceOutOfScope equ 25
adFieldAlreadyExists	equ 26
adFieldPendingInsert	equ 0x10000
adFieldPendingDelete	equ 0x20000
adFieldPendingChange	equ 0x40000
adFieldPendingUnknown	equ 0x80000
adFieldPendingUnknownDelete equ 0x100000
DECLSPEC_UUID("00000552-0000-0010-8000-00AA006D2EA4")
SeekEnum		typedef SDWORD
adSeekFirstEQ		equ 0x1
adSeekLastEQ		equ 0x2
adSeekAfterEQ		equ 0x4
adSeekAfter		equ 0x8
adSeekBeforeEQ		equ 0x10
adSeekBefore		equ 0x20
ifndef _COMMON_ADC_AND_ADO_PROPS_
_COMMON_ADC_AND_ADO_PROPS_ equ 1
DECLSPEC_UUID("0000054A-0000-0010-8000-00AA006D2EA4")
ADCPROP_UPDATECRITERIA_ENUM typedef SDWORD
adCriteriaKey		equ 0
adCriteriaAllCols	equ 1
adCriteriaUpdCols	equ 2
adCriteriaTimeStamp	equ 3
DECLSPEC_UUID("0000054B-0000-0010-8000-00AA006D2EA4")
ADCPROP_ASYNCTHREADPRIORITY_ENUM typedef SDWORD
adPriorityLowest	equ 1
adPriorityBelowNormal	equ 2
adPriorityNormal	equ 3
adPriorityAboveNormal	equ 4
adPriorityHighest	equ 5
DECLSPEC_UUID("00000554-0000-0010-8000-00AA006D2EA4")
ADCPROP_AUTORECALC_ENUM typedef SDWORD
adRecalcUpFront		equ 0
adRecalcAlways		equ 1
DECLSPEC_UUID("00000553-0000-0010-8000-00AA006D2EA4")
ADCPROP_UPDATERESYNC_ENUM typedef SDWORD
adResyncNone		equ 0
adResyncAutoIncrement	equ 1
adResyncConflicts	equ 2
adResyncUpdates		equ 4
adResyncInserts		equ 8
adResyncAll		equ 15
endif
CEResyncEnum		typedef ADCPROP_UPDATERESYNC_ENUM
DECLSPEC_UUID("00000573-0000-0010-8000-00AA006D2EA4")
MoveRecordOptionsEnum	typedef SDWORD
adMoveUnspecified	equ -1
adMoveOverWrite		equ 1
adMoveDontUpdateLinks	equ 2
adMoveAllowEmulation	equ 4
DECLSPEC_UUID("00000574-0000-0010-8000-00AA006D2EA4")
CopyRecordOptionsEnum	typedef SDWORD
adCopyUnspecified	equ -1
adCopyOverWrite		equ 1
adCopyAllowEmulation	equ 4
adCopyNonRecursive	equ 2
DECLSPEC_UUID("00000576-0000-0010-8000-00AA006D2EA4")
StreamTypeEnum		typedef SDWORD
adTypeBinary		equ 1
adTypeText		equ 2
DECLSPEC_UUID("00000577-0000-0010-8000-00AA006D2EA4")
LineSeparatorEnum	typedef SDWORD
adLF			equ 10
adCR			equ 13
adCRLF			equ -1
DECLSPEC_UUID("0000057A-0000-0010-8000-00AA006D2EA4")
StreamOpenOptionsEnum	typedef SDWORD
adOpenStreamUnspecified equ -1
adOpenStreamAsync	equ 1
adOpenStreamFromRecord	equ 4
DECLSPEC_UUID("0000057B-0000-0010-8000-00AA006D2EA4")
StreamWriteEnum		typedef SDWORD
adWriteChar		equ 0
adWriteLine		equ 1
stWriteChar		equ 0
stWriteLine		equ 1
DECLSPEC_UUID("0000057C-0000-0010-8000-00AA006D2EA4")
SaveOptionsEnum		typedef SDWORD
adSaveCreateNotExist	equ 1
adSaveCreateOverWrite	equ 2
FieldEnum		typedef SDWORD
adDefaultStream		equ -1
adRecordURL		equ -2
StreamReadEnum		typedef SDWORD
adReadAll		equ -1
adReadLine		equ -2
DECLSPEC_UUID("0000057D-0000-0010-8000-00AA006D2EA4")
RecordTypeEnum		typedef SDWORD
adSimpleRecord		equ 0
adCollectionRecord	equ 1
adStructDoc		equ 2
externdef		LIBID_ADODB:IID
ifndef ___ADOCollection_INTERFACE_DEFINED__
___ADOCollection_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(_ADOCollection, "00000512-0000-0010-8000-00AA006D2EA4")
.comdef _ADOCollection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
.comdef _ADODynaCollection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    Append		proc :ptr
    Delete		proc :VARIANT
    .ends

endif
ifndef ___ADO_INTERFACE_DEFINED__
___ADO_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(_ADO, "00000534-0000-0010-8000-00AA006D2EA4")
.comdef _ADO
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
.comdef Error
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
.comdef Errors
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
.comdef Command15
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr
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
.comdef Command25
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr
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
    .ends

endif
ifndef ___Command_INTERFACE_DEFINED__
___Command_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(_Command, "B08400BD-F9D1-4D02-B856-71D5DBA123E9")
.comdef _Command
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr
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
.comdef ConnectionEventsVt
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
.comdef RecordsetEventsVt
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
.comdef ConnectionEvents
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    .ends

endif
ifndef __RecordsetEvents_DISPINTERFACE_DEFINED__
__RecordsetEvents_DISPINTERFACE_DEFINED__ equ 1
DEFINE_IIDX(RecordsetEvents, "00000266-0000-0010-8000-00AA006D2EA4")
.comdef RecordsetEvents
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    .ends

endif
ifndef __Connection15_INTERFACE_DEFINED__
__Connection15_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(Connection15, "00000515-0000-0010-8000-00AA006D2EA4")
.comdef Connection15
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
.comdef _Connection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
    Cancel		proc
    .ends

endif
ifndef __ADOConnectionConstruction15_INTERFACE_DEFINED__
__ADOConnectionConstruction15_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(ADOConnectionConstruction15, "00000516-0000-0010-8000-00AA006D2EA4")
.comdef ADOConnectionConstruction15
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_DSO		proc :ptr
    get_Session		proc :ptr
    WrapDSOandSession	proc :ptr, :ptr
    .ends

endif
ifndef __ADOConnectionConstruction_INTERFACE_DEFINED__
__ADOConnectionConstruction_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(ADOConnectionConstruction, "00000551-0000-0010-8000-00AA006D2EA4")
.comdef ADOConnectionConstruction
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_DSO		proc :ptr
    get_Session		proc :ptr
    WrapDSOandSession	proc :ptr, :ptr
    .ends

endif
externdef		CLSID_Connection:CLSID
ifndef ___Record_INTERFACE_DEFINED__
___Record_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(_Record, "00000562-0000-0010-8000-00AA006D2EA4")
.comdef _Record
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr
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
.comdef _Stream
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
.comdef ADORecordConstruction
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Row		proc :ptr
    put_Row		proc :ptr
    put_ParentRow	proc :ptr
    .ends

endif
ifndef __ADOStreamConstruction_INTERFACE_DEFINED__
__ADOStreamConstruction_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(ADOStreamConstruction, "00000568-0000-0010-8000-00AA006D2EA4")
.comdef ADOStreamConstruction
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Stream		proc :ptr
    put_Stream		proc :ptr
    .ends

endif
ifndef __ADOCommandConstruction_INTERFACE_DEFINED__
__ADOCommandConstruction_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(ADOCommandConstruction, "00000517-0000-0010-8000-00AA006D2EA4")
.comdef ADOCommandConstruction
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    get_OLEDBCommand	proc :ptr
    put_OLEDBCommand	proc :ptr
    .ends

endif
externdef		CLSID_Command:CLSID
externdef		CLSID_Recordset:CLSID

ifndef __Recordset15_INTERFACE_DEFINED__
__Recordset15_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(Recordset15, "0000050E-0000-0010-8000-00AA006D2EA4")
.comdef Recordset15
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr
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
.comdef Recordset20
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr
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
.comdef Recordset21
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr
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
    Seek		proc :VARIANT, :SeekEnum
    put_Index		proc :BSTR
    get_Index		proc :ptr
    .ends

endif
ifndef ___Recordset_INTERFACE_DEFINED__
___Recordset_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(_Recordset, "00000556-0000-0010-8000-00AA006D2EA4")
.comdef _Recordset
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Properties	proc :ptr
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
    Seek		proc :VARIANT, :SeekEnum
    put_Index		proc :BSTR
    get_Index		proc :ptr
    Save		proc :VARIANT, :PersistFormatEnum
    .ends

endif
ifndef __ADORecordsetConstruction_INTERFACE_DEFINED__
__ADORecordsetConstruction_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(ADORecordsetConstruction, "00000283-0000-0010-8000-00AA006D2EA4")
.comdef ADORecordsetConstruction
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
.comdef Field15
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
.comdef Field20
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
.comdef Field
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
    get_DataFormat	proc :ptr
    putref_DataFormat	proc :ptr
    put_Precision	proc :BYTE
    put_NumericScale	proc :BYTE
    put_Type		proc :DataTypeEnum
    put_DefinedSize	proc :ADO_LONGPTR
    put_Attributes	proc :LONG
    get_Status		proc :ptr
    .ends

endif
ifndef __Fields15_INTERFACE_DEFINED__
__Fields15_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(Fields15, "00000506-0000-0010-8000-00AA006D2EA4")
.comdef Fields15
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    .ends

endif
ifndef __Fields20_INTERFACE_DEFINED__
__Fields20_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(Fields20, "0000054D-0000-0010-8000-00AA006D2EA4")
.comdef Fields20
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    _Append		proc :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum
    Delete		proc :VARIANT
    .ends

endif
ifndef __Fields_INTERFACE_DEFINED__
__Fields_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(Fields, "00000564-0000-0010-8000-00AA006D2EA4")
.comdef Fields
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    _Append		proc :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum
    Delete		proc :VARIANT
    Append		proc :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum, :VARIANT
    Update		proc
    Resync		proc :ResyncEnum
    CancelUpdate	proc
    .ends

endif
ifndef ___Parameter_INTERFACE_DEFINED__
___Parameter_INTERFACE_DEFINED__ equ 1
DEFINE_IIDX(_Parameter, "0000050C-0000-0010-8000-00AA006D2EA4")
.comdef _Parameter
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
.comdef Parameters
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
.comdef Property
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
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
.comdef Properties
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    _NewEnum		proc :ptr
    Refresh		proc
    get_Item		proc :VARIANT, :ptr
    .ends

endif
endif

endif
if 0
ADOCommand		equ <_ADOCommand>
ADORecordset		equ <_ADORecordset>
ADOTransaction		equ <_ADOTransaction>
ADOParameter		equ <_ADOParameter>
ADOConnection		equ <_ADOConnection>
ADOCollection		equ <_ADOCollection>
ADODynaCollection	equ <_ADODynaCollection>
ADORecord		equ <_ADORecord>
ADORecField		equ <_ADORecField>
ADOStream		equ <_ADOStream>
endif

.pragma list(pop)
endif

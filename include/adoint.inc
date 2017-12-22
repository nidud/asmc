ifndef _ADOINT_H_
_ADOINT_H_ equ 1

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
__ado10_h__ equ 1

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
externdef		__MIDL_itf_ado10_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_ado10_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE
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
externdef		IID__ADOCollection:IID
_ADOCollection		STRUC

	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Refresh

_ADOCollection		ENDS
endif

ifndef ___ADODynaCollection_INTERFACE_DEFINED__
___ADODynaCollection_INTERFACE_DEFINED__ equ 1
externdef		IID__ADODynaCollection:IID
_ADODynaCollection	STRUC

	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Refresh
	STDMETHOD	Append, :ptr
	STDMETHOD	Delete, :VARIANT

_ADODynaCollection	ENDS

endif
ifndef ___ADO_INTERFACE_DEFINED__
___ADO_INTERFACE_DEFINED__ equ 1
externdef		IID__ADO:IID
_ADO			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr


_ADO			ENDS

endif
ifndef __Error_INTERFACE_DEFINED__
__Error_INTERFACE_DEFINED__ equ 1
externdef		IID_Error:IID
Error			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Number, :ptr
	STDMETHOD	get_Source, :ptr
	STDMETHOD	get_Description, :ptr
	STDMETHOD	get_HelpFile, :ptr
	STDMETHOD	get_HelpContext, :ptr
	STDMETHOD	get_SQLState, :ptr
	STDMETHOD	get_NativeError, :ptr


Error			ENDS

endif
ifndef __Errors_INTERFACE_DEFINED__
__Errors_INTERFACE_DEFINED__ equ 1
externdef		IID_Errors:IID
Errors			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Refresh
	STDMETHOD	get_Item, :VARIANT, :ptr
	STDMETHOD	Clear


Errors			ENDS

endif
ifndef __Command15_INTERFACE_DEFINED__
__Command15_INTERFACE_DEFINED__ equ 1
externdef		IID_Command15:IID
Command15		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ActiveConnection, :ptr
	STDMETHOD	putref_ActiveADOConnection, :ptr
	STDMETHOD	put_ActiveConnection, :VARIANT
	STDMETHOD	get_CommandText, :ptr
	STDMETHOD	put_CommandText, :BSTR
	STDMETHOD	get_CommandTimeout, :ptr
	STDMETHOD	put_CommandTimeout, :LONG
	STDMETHOD	get_Prepared, :ptr
	STDMETHOD	put_Prepared, :VARIANT_BOOL
	STDMETHOD	Execute, :ptr, :ptr, :LONG, :ptr
	STDMETHOD	CreateParameter, :BSTR, :DataTypeEnum, :ParameterDirectionEnum, :ADO_LONGPTR, :VARIANT, :ptr
	STDMETHOD	get_Parameters, :ptr
	STDMETHOD	put_CommandType, :CommandTypeEnum
	STDMETHOD	get_CommandType, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	put_Name, :BSTR


Command15		ENDS

endif
ifndef __Command25_INTERFACE_DEFINED__
__Command25_INTERFACE_DEFINED__ equ 1
externdef		IID_Command25:IID
Command25		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ActiveConnection, :ptr
	STDMETHOD	putref_ActiveADOConnection, :ptr
	STDMETHOD	put_ActiveConnection, :VARIANT
	STDMETHOD	get_CommandText, :ptr
	STDMETHOD	put_CommandText, :BSTR
	STDMETHOD	get_CommandTimeout, :ptr
	STDMETHOD	put_CommandTimeout, :LONG
	STDMETHOD	get_Prepared, :ptr
	STDMETHOD	put_Prepared, :VARIANT_BOOL
	STDMETHOD	Execute, :ptr, :ptr, :LONG, :ptr
	STDMETHOD	CreateParameter, :BSTR, :DataTypeEnum, :ParameterDirectionEnum, :ADO_LONGPTR, :VARIANT, :ptr
	STDMETHOD	get_Parameters, :ptr
	STDMETHOD	put_CommandType, :CommandTypeEnum
	STDMETHOD	get_CommandType, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	put_Name, :BSTR
	STDMETHOD	get_State, :ptr
	STDMETHOD	Cancel


Command25		ENDS

endif
ifndef ___Command_INTERFACE_DEFINED__
___Command_INTERFACE_DEFINED__ equ 1
externdef		IID__Command:IID
_Command		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ActiveConnection, :ptr
	STDMETHOD	putref_ActiveADOConnection, :ptr
	STDMETHOD	put_ActiveConnection, :VARIANT
	STDMETHOD	get_CommandText, :ptr
	STDMETHOD	put_CommandText, :BSTR
	STDMETHOD	get_CommandTimeout, :ptr
	STDMETHOD	put_CommandTimeout, :LONG
	STDMETHOD	get_Prepared, :ptr
	STDMETHOD	put_Prepared, :VARIANT_BOOL
	STDMETHOD	Execute, :ptr, :ptr, :LONG, :ptr
	STDMETHOD	CreateParameter, :BSTR, :DataTypeEnum, :ParameterDirectionEnum, :ADO_LONGPTR, :VARIANT, :ptr
	STDMETHOD	get_Parameters, :ptr
	STDMETHOD	put_CommandType, :CommandTypeEnum
	STDMETHOD	get_CommandType, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	put_Name, :BSTR
	STDMETHOD	get_State, :ptr
	STDMETHOD	Cancel
	STDMETHOD	putref_CommandADOStream, :ptr
	STDMETHOD	get_CommandStream, :ptr
	STDMETHOD	put_Dialect, :BSTR
	STDMETHOD	get_Dialect, :ptr
	STDMETHOD	put_NamedParameters, :VARIANT_BOOL
	STDMETHOD	get_NamedParameters, :ptr

_Command		ENDS

endif
ifndef __ConnectionEventsVt_INTERFACE_DEFINED__
__ConnectionEventsVt_INTERFACE_DEFINED__ equ 1
externdef		IID_ConnectionEventsVt:IID
ConnectionEventsVt	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	InfoMessage, :ptr, :ptr, :ptr
	STDMETHOD	BeginTransComplete, :LONG, :ptr, :ptr, :ptr
	STDMETHOD	CommitTransComplete, :ptr, :ptr, :ptr
	STDMETHOD	RollbackTransComplete, :ptr, :ptr, :ptr
	STDMETHOD	WillExecute, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	ExecuteComplete, :LONG, :ptr, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	WillConnect, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	ConnectComplete, :ptr, :ptr, :ptr
	STDMETHOD	Disconnect, :ptr, :ptr


ConnectionEventsVt	ENDS

endif
ifndef __RecordsetEventsVt_INTERFACE_DEFINED__
__RecordsetEventsVt_INTERFACE_DEFINED__ equ 1
externdef		IID_RecordsetEventsVt:IID
RecordsetEventsVt	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	WillChangeADOField, :LONG, :VARIANT, :ptr, :ptr
	STDMETHOD	FieldChangeComplete, :LONG, :VARIANT, :ptr, :ptr, :ptr
	STDMETHOD	WillChangeADORecord, :EventReasonEnum, :LONG, :ptr, :ptr
	STDMETHOD	RecordChangeComplete, :EventReasonEnum, :LONG, :ptr, :ptr, :ptr
	STDMETHOD	WillChangeADORecordset, :EventReasonEnum, :ptr, :ptr
	STDMETHOD	RecordsetChangeComplete, :EventReasonEnum, :ptr, :ptr, :ptr
	STDMETHOD	WillMove, :EventReasonEnum, :ptr, :ptr
	STDMETHOD	MoveComplete, :EventReasonEnum, :ptr, :ptr, :ptr
	STDMETHOD	EndOfADORecordset, :ptr, :ptr, :ptr
	STDMETHOD	FetchProgress, :LONG, :LONG, :ptr, :ptr
	STDMETHOD	FetchComplete, :ptr, :ptr, :ptr


RecordsetEventsVt	ENDS

endif
ifndef __ConnectionEvents_DISPINTERFACE_DEFINED__
__ConnectionEvents_DISPINTERFACE_DEFINED__ equ 1
externdef		DIID_ConnectionEvents:IID
ConnectionEvents	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr


ConnectionEvents	ENDS

endif
ifndef __RecordsetEvents_DISPINTERFACE_DEFINED__
__RecordsetEvents_DISPINTERFACE_DEFINED__ equ 1
externdef		DIID_RecordsetEvents:IID
RecordsetEvents		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr


RecordsetEvents		ENDS

endif
ifndef __Connection15_INTERFACE_DEFINED__
__Connection15_INTERFACE_DEFINED__ equ 1
externdef		IID_Connection15:IID
Connection15		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ConnectionString, :ptr
	STDMETHOD	put_ConnectionString, :BSTR
	STDMETHOD	get_CommandTimeout, :ptr
	STDMETHOD	put_CommandTimeout, :LONG
	STDMETHOD	get_ConnectionTimeout, :ptr
	STDMETHOD	put_ConnectionTimeout, :LONG
	STDMETHOD	get_Version, :ptr
	STDMETHOD	Close
	STDMETHOD	Execute, :BSTR, :ptr, :LONG, :ptr
	STDMETHOD	BeginTrans, :ptr
	STDMETHOD	CommitTrans
	STDMETHOD	RollbackTrans
	STDMETHOD	Open, :BSTR, :BSTR, :BSTR, :LONG
	STDMETHOD	get_Errors, :ptr
	STDMETHOD	get_DefaultDatabase, :ptr
	STDMETHOD	put_DefaultDatabase, :BSTR
	STDMETHOD	get_IsolationLevel, :ptr
	STDMETHOD	put_IsolationLevel, :IsolationLevelEnum
	STDMETHOD	get_Attributes, :ptr
	STDMETHOD	put_Attributes, :LONG
	STDMETHOD	get_CursorLocation, :ptr
	STDMETHOD	put_CursorLocation, :CursorLocationEnum
	STDMETHOD	get_Mode, :ptr
	STDMETHOD	put_Mode, :ConnectModeEnum
	STDMETHOD	get_Provider, :ptr
	STDMETHOD	put_Provider, :BSTR
	STDMETHOD	get_State, :ptr
	STDMETHOD	OpenSchema, :SchemaEnum, :VARIANT, :VARIANT, :ptr


Connection15		ENDS

endif
ifndef ___Connection_INTERFACE_DEFINED__
___Connection_INTERFACE_DEFINED__ equ 1
externdef		IID__Connection:IID
_Connection		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ConnectionString, :ptr
	STDMETHOD	put_ConnectionString, :BSTR
	STDMETHOD	get_CommandTimeout, :ptr
	STDMETHOD	put_CommandTimeout, :LONG
	STDMETHOD	get_ConnectionTimeout, :ptr
	STDMETHOD	put_ConnectionTimeout, :LONG
	STDMETHOD	get_Version, :ptr
	STDMETHOD	Close
	STDMETHOD	Execute, :BSTR, :ptr, :LONG, :ptr
	STDMETHOD	BeginTrans, :ptr
	STDMETHOD	CommitTrans
	STDMETHOD	RollbackTrans
	STDMETHOD	Open, :BSTR, :BSTR, :BSTR, :LONG
	STDMETHOD	get_Errors, :ptr
	STDMETHOD	get_DefaultDatabase, :ptr
	STDMETHOD	put_DefaultDatabase, :BSTR
	STDMETHOD	get_IsolationLevel, :ptr
	STDMETHOD	put_IsolationLevel, :IsolationLevelEnum
	STDMETHOD	get_Attributes, :ptr
	STDMETHOD	put_Attributes, :LONG
	STDMETHOD	get_CursorLocation, :ptr
	STDMETHOD	put_CursorLocation, :CursorLocationEnum
	STDMETHOD	get_Mode, :ptr
	STDMETHOD	put_Mode, :ConnectModeEnum
	STDMETHOD	get_Provider, :ptr
	STDMETHOD	put_Provider, :BSTR
	STDMETHOD	get_State, :ptr
	STDMETHOD	OpenSchema, :SchemaEnum, :VARIANT, :VARIANT, :ptr
	STDMETHOD	Cancel

_Connection		ENDS

endif
ifndef __ADOConnectionConstruction15_INTERFACE_DEFINED__
__ADOConnectionConstruction15_INTERFACE_DEFINED__ equ 1
externdef		IID_ADOConnectionConstruction15:IID
ADOConnectionConstruction15 STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	get_DSO, :ptr
	STDMETHOD	get_Session, :ptr
	STDMETHOD	WrapDSOandSession, :ptr, :ptr


ADOConnectionConstruction15 ENDS

endif
ifndef __ADOConnectionConstruction_INTERFACE_DEFINED__
__ADOConnectionConstruction_INTERFACE_DEFINED__ equ 1
externdef		IID_ADOConnectionConstruction:IID
ADOConnectionConstruction STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	get_DSO, :ptr
	STDMETHOD	get_Session, :ptr
	STDMETHOD	WrapDSOandSession, :ptr, :ptr


ADOConnectionConstruction ENDS

endif
externdef		CLSID_Connection:CLSID
ifndef ___Record_INTERFACE_DEFINED__
___Record_INTERFACE_DEFINED__ equ 1
externdef		IID__Record:IID
_Record			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ActiveConnection, :ptr
	STDMETHOD	put_ActiveConnection, :BSTR
	STDMETHOD	putref_ActiveADOConnection, :ptr
	STDMETHOD	get_State, :ptr
	STDMETHOD	get_Source, :ptr
	STDMETHOD	put_Source, :BSTR
	STDMETHOD	putref_Source, :ptr
	STDMETHOD	get_Mode, :ptr
	STDMETHOD	put_Mode, :ConnectModeEnum
	STDMETHOD	get_ParentURL, :ptr
	STDMETHOD	MoveADORecord, :BSTR, :BSTR, :BSTR, :BSTR, :MoveRecordOptionsEnum, :VARIANT_BOOL, :ptr
	STDMETHOD	CopyADORecord, :BSTR, :BSTR, :BSTR, :BSTR, :CopyRecordOptionsEnum, :VARIANT_BOOL, :ptr
	STDMETHOD	DeleteADORecord, :BSTR, :VARIANT_BOOL
	STDMETHOD	Open, :VARIANT, :VARIANT, :ConnectModeEnum, :RecordCreateOptionsEnum, :RecordOpenOptionsEnum, :BSTR, :BSTR
	STDMETHOD	Close
	STDMETHOD	get_Fields, :ptr
	STDMETHOD	get_RecordType, :ptr
	STDMETHOD	GetChildren, :ptr
	STDMETHOD	Cancel

_Record			ENDS

endif
externdef		CLSID_Record:CLSID
ifndef ___Stream_INTERFACE_DEFINED__
___Stream_INTERFACE_DEFINED__ equ 1
externdef		IID__Stream:IID
_Stream			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Size, :ptr
	STDMETHOD	get_EOS, :ptr
	STDMETHOD	get_Position, :ptr
	STDMETHOD	put_Position, :ADO_LONGPTR
	STDMETHOD	get_Type, :ptr
	STDMETHOD	put_Type, :StreamTypeEnum
	STDMETHOD	get_LineSeparator, :ptr
	STDMETHOD	put_LineSeparator, :LineSeparatorEnum
	STDMETHOD	get_State, :ptr
	STDMETHOD	get_Mode, :ptr
	STDMETHOD	put_Mode, :ConnectModeEnum
	STDMETHOD	get_Charset, :ptr
	STDMETHOD	put_Charset, :BSTR
	STDMETHOD	Read, :LONG, :ptr
	STDMETHOD	Open, :VARIANT, :ConnectModeEnum, :StreamOpenOptionsEnum, :BSTR, :BSTR
	STDMETHOD	Close
	STDMETHOD	SkipLine
	STDMETHOD	Write, :VARIANT
	STDMETHOD	SetEOS
	STDMETHOD	CopyTo, :ptr, :ADO_LONGPTR
	STDMETHOD	Flush
	STDMETHOD	SaveToFile, :BSTR, :SaveOptionsEnum
	STDMETHOD	LoadFromFile, :BSTR
	STDMETHOD	ReadText, :LONG, :ptr
	STDMETHOD	WriteText, :BSTR, :StreamWriteEnum
	STDMETHOD	Cancel

_Stream			ENDS

endif
externdef		CLSID_Stream:CLSID
ifndef __ADORecordConstruction_INTERFACE_DEFINED__
__ADORecordConstruction_INTERFACE_DEFINED__ equ 1
externdef		IID_ADORecordConstruction:IID
ADORecordConstruction	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Row, :ptr
	STDMETHOD	put_Row, :ptr
	STDMETHOD	put_ParentRow, :ptr


ADORecordConstruction	ENDS

endif
ifndef __ADOStreamConstruction_INTERFACE_DEFINED__
__ADOStreamConstruction_INTERFACE_DEFINED__ equ 1
externdef		IID_ADOStreamConstruction:IID
ADOStreamConstruction	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Stream, :ptr
	STDMETHOD	put_Stream, :ptr


ADOStreamConstruction	ENDS

endif
ifndef __ADOCommandConstruction_INTERFACE_DEFINED__
__ADOCommandConstruction_INTERFACE_DEFINED__ equ 1
externdef		IID_ADOCommandConstruction:IID
ADOCommandConstruction	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	get_OLEDBCommand, :ptr
	STDMETHOD	put_OLEDBCommand, :ptr


ADOCommandConstruction	ENDS

endif
externdef		CLSID_Command:CLSID
externdef		CLSID_Recordset:CLSID

ifndef __Recordset15_INTERFACE_DEFINED__
__Recordset15_INTERFACE_DEFINED__ equ 1
externdef		IID_Recordset15:IID
Recordset15		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_AbsolutePosition, :ptr
	STDMETHOD	put_AbsolutePosition, :PositionEnum_Param
	STDMETHOD	putref_ActiveADOConnection, :ptr
	STDMETHOD	put_ActiveConnection, :VARIANT
	STDMETHOD	get_ActiveConnection, :ptr
	STDMETHOD	get_BOF, :ptr
	STDMETHOD	get_Bookmark, :ptr
	STDMETHOD	put_Bookmark, :VARIANT
	STDMETHOD	get_CacheSize, :ptr
	STDMETHOD	put_CacheSize, :LONG
	STDMETHOD	get_CursorType, :ptr
	STDMETHOD	put_CursorType, :CursorTypeEnum
	STDMETHOD	get_EOF, :ptr
	STDMETHOD	get_Fields, :ptr
	STDMETHOD	get_LockType, :ptr
	STDMETHOD	put_LockType, :LockTypeEnum
	STDMETHOD	get_MaxRecords, :ptr
	STDMETHOD	put_MaxRecords, :ADO_LONGPTR
	STDMETHOD	get_RecordCount, :ptr
	STDMETHOD	putref_Source, :ptr
	STDMETHOD	put_Source, :BSTR
	STDMETHOD	get_Source, :ptr
	STDMETHOD	AddNew, :VARIANT, :VARIANT
	STDMETHOD	CancelUpdate
	STDMETHOD	Close
	STDMETHOD	Delete, :AffectEnum
	STDMETHOD	GetRows, :LONG, :VARIANT, :VARIANT, :ptr
	STDMETHOD	Move, :ADO_LONGPTR, :VARIANT
	STDMETHOD	MoveNext
	STDMETHOD	MovePrevious
	STDMETHOD	MoveFirst
	STDMETHOD	MoveLast
	STDMETHOD	Open, :VARIANT, :VARIANT, :CursorTypeEnum, :LockTypeEnum, :LONG
	STDMETHOD	Requery, :LONG
	STDMETHOD	_xResync, :AffectEnum
	STDMETHOD	Update, :VARIANT, :VARIANT
	STDMETHOD	get_AbsolutePage, :ptr
	STDMETHOD	put_AbsolutePage, :PositionEnum_Param
	STDMETHOD	get_EditMode, :ptr
	STDMETHOD	get_Filter, :ptr
	STDMETHOD	put_Filter, :VARIANT
	STDMETHOD	get_PageCount, :ptr
	STDMETHOD	get_PageSize, :ptr
	STDMETHOD	put_PageSize, :LONG
	STDMETHOD	get_Sort, :ptr
	STDMETHOD	put_Sort, :BSTR
	STDMETHOD	get_Status, :ptr
	STDMETHOD	get_State, :ptr
	STDMETHOD	_xClone, :ptr
	STDMETHOD	UpdateBatch, :AffectEnum
	STDMETHOD	CancelBatch, :AffectEnum
	STDMETHOD	get_CursorLocation, :ptr
	STDMETHOD	put_CursorLocation, :CursorLocationEnum
	STDMETHOD	NextADORecordset, :ptr, :ptr
	STDMETHOD	Supports, :CursorOptionEnum, :ptr
	STDMETHOD	get_Collect, :VARIANT, :ptr
	STDMETHOD	put_Collect, :VARIANT, :VARIANT
	STDMETHOD	get_MarshalOptions, :ptr
	STDMETHOD	put_MarshalOptions, :MarshalOptionsEnum
	STDMETHOD	Find, :BSTR, :ADO_LONGPTR, :SearchDirectionEnum, :VARIANT


Recordset15		ENDS

endif
ifndef __Recordset20_INTERFACE_DEFINED__
__Recordset20_INTERFACE_DEFINED__ equ 1
externdef		IID_Recordset20:IID
Recordset20		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_AbsolutePosition, :ptr
	STDMETHOD	put_AbsolutePosition, :PositionEnum_Param
	STDMETHOD	putref_ActiveADOConnection, :ptr
	STDMETHOD	put_ActiveConnection, :VARIANT
	STDMETHOD	get_ActiveConnection, :ptr
	STDMETHOD	get_BOF, :ptr
	STDMETHOD	get_Bookmark, :ptr
	STDMETHOD	put_Bookmark, :VARIANT
	STDMETHOD	get_CacheSize, :ptr
	STDMETHOD	put_CacheSize, :LONG
	STDMETHOD	get_CursorType, :ptr
	STDMETHOD	put_CursorType, :CursorTypeEnum
	STDMETHOD	get_EOF, :ptr
	STDMETHOD	get_Fields, :ptr
	STDMETHOD	get_LockType, :ptr
	STDMETHOD	put_LockType, :LockTypeEnum
	STDMETHOD	get_MaxRecords, :ptr
	STDMETHOD	put_MaxRecords, :ADO_LONGPTR
	STDMETHOD	get_RecordCount, :ptr
	STDMETHOD	putref_Source, :ptr
	STDMETHOD	put_Source, :BSTR
	STDMETHOD	get_Source, :ptr
	STDMETHOD	AddNew, :VARIANT, :VARIANT
	STDMETHOD	CancelUpdate
	STDMETHOD	Close
	STDMETHOD	Delete, :AffectEnum
	STDMETHOD	GetRows, :LONG, :VARIANT, :VARIANT, :ptr
	STDMETHOD	Move, :ADO_LONGPTR, :VARIANT
	STDMETHOD	MoveNext
	STDMETHOD	MovePrevious
	STDMETHOD	MoveFirst
	STDMETHOD	MoveLast
	STDMETHOD	Open, :VARIANT, :VARIANT, :CursorTypeEnum, :LockTypeEnum, :LONG
	STDMETHOD	Requery, :LONG
	STDMETHOD	_xResync, :AffectEnum
	STDMETHOD	Update, :VARIANT, :VARIANT
	STDMETHOD	get_AbsolutePage, :ptr
	STDMETHOD	put_AbsolutePage, :PositionEnum_Param
	STDMETHOD	get_EditMode, :ptr
	STDMETHOD	get_Filter, :ptr
	STDMETHOD	put_Filter, :VARIANT
	STDMETHOD	get_PageCount, :ptr
	STDMETHOD	get_PageSize, :ptr
	STDMETHOD	put_PageSize, :LONG
	STDMETHOD	get_Sort, :ptr
	STDMETHOD	put_Sort, :BSTR
	STDMETHOD	get_Status, :ptr
	STDMETHOD	get_State, :ptr
	STDMETHOD	_xClone, :ptr
	STDMETHOD	UpdateBatch, :AffectEnum
	STDMETHOD	CancelBatch, :AffectEnum
	STDMETHOD	get_CursorLocation, :ptr
	STDMETHOD	put_CursorLocation, :CursorLocationEnum
	STDMETHOD	NextADORecordset, :ptr, :ptr
	STDMETHOD	Supports, :CursorOptionEnum, :ptr
	STDMETHOD	get_Collect, :VARIANT, :ptr
	STDMETHOD	put_Collect, :VARIANT, :VARIANT
	STDMETHOD	get_MarshalOptions, :ptr
	STDMETHOD	put_MarshalOptions, :MarshalOptionsEnum
	STDMETHOD	Find, :BSTR, :ADO_LONGPTR, :SearchDirectionEnum, :VARIANT
	STDMETHOD	Cancel
	STDMETHOD	get_DataSource, :ptr
	STDMETHOD	putref_DataSource, :ptr
	STDMETHOD	_xSave, :BSTR, :PersistFormatEnum
	STDMETHOD	get_ActiveCommand, :ptr
	STDMETHOD	put_StayInSync, :VARIANT_BOOL
	STDMETHOD	get_StayInSync, :ptr
	STDMETHOD	GetString, :StringFormatEnum, :LONG, :BSTR, :BSTR, :BSTR, :ptr
	STDMETHOD	get_DataMember, :ptr
	STDMETHOD	put_DataMember, :BSTR
	STDMETHOD	CompareBookmarks, :VARIANT, :VARIANT, :ptr
	STDMETHOD	Clone, :LockTypeEnum, :ptr
	STDMETHOD	Resync, :AffectEnum, :ResyncEnum


Recordset20		ENDS

endif
ifndef __Recordset21_INTERFACE_DEFINED__
__Recordset21_INTERFACE_DEFINED__ equ 1
externdef		IID_Recordset21:IID
Recordset21		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_AbsolutePosition, :ptr
	STDMETHOD	put_AbsolutePosition, :PositionEnum_Param
	STDMETHOD	putref_ActiveADOConnection, :ptr
	STDMETHOD	put_ActiveConnection, :VARIANT
	STDMETHOD	get_ActiveConnection, :ptr
	STDMETHOD	get_BOF, :ptr
	STDMETHOD	get_Bookmark, :ptr
	STDMETHOD	put_Bookmark, :VARIANT
	STDMETHOD	get_CacheSize, :ptr
	STDMETHOD	put_CacheSize, :LONG
	STDMETHOD	get_CursorType, :ptr
	STDMETHOD	put_CursorType, :CursorTypeEnum
	STDMETHOD	get_EOF, :ptr
	STDMETHOD	get_Fields, :ptr
	STDMETHOD	get_LockType, :ptr
	STDMETHOD	put_LockType, :LockTypeEnum
	STDMETHOD	get_MaxRecords, :ptr
	STDMETHOD	put_MaxRecords, :ADO_LONGPTR
	STDMETHOD	get_RecordCount, :ptr
	STDMETHOD	putref_Source, :ptr
	STDMETHOD	put_Source, :BSTR
	STDMETHOD	get_Source, :ptr
	STDMETHOD	AddNew, :VARIANT, :VARIANT
	STDMETHOD	CancelUpdate
	STDMETHOD	Close
	STDMETHOD	Delete, :AffectEnum
	STDMETHOD	GetRows, :LONG, :VARIANT, :VARIANT, :ptr
	STDMETHOD	Move, :ADO_LONGPTR, :VARIANT
	STDMETHOD	MoveNext
	STDMETHOD	MovePrevious
	STDMETHOD	MoveFirst
	STDMETHOD	MoveLast
	STDMETHOD	Open, :VARIANT, :VARIANT, :CursorTypeEnum, :LockTypeEnum, :LONG
	STDMETHOD	Requery, :LONG
	STDMETHOD	_xResync, :AffectEnum
	STDMETHOD	Update, :VARIANT, :VARIANT
	STDMETHOD	get_AbsolutePage, :ptr
	STDMETHOD	put_AbsolutePage, :PositionEnum_Param
	STDMETHOD	get_EditMode, :ptr
	STDMETHOD	get_Filter, :ptr
	STDMETHOD	put_Filter, :VARIANT
	STDMETHOD	get_PageCount, :ptr
	STDMETHOD	get_PageSize, :ptr
	STDMETHOD	put_PageSize, :LONG
	STDMETHOD	get_Sort, :ptr
	STDMETHOD	put_Sort, :BSTR
	STDMETHOD	get_Status, :ptr
	STDMETHOD	get_State, :ptr
	STDMETHOD	_xClone, :ptr
	STDMETHOD	UpdateBatch, :AffectEnum
	STDMETHOD	CancelBatch, :AffectEnum
	STDMETHOD	get_CursorLocation, :ptr
	STDMETHOD	put_CursorLocation, :CursorLocationEnum
	STDMETHOD	NextADORecordset, :ptr, :ptr
	STDMETHOD	Supports, :CursorOptionEnum, :ptr
	STDMETHOD	get_Collect, :VARIANT, :ptr
	STDMETHOD	put_Collect, :VARIANT, :VARIANT
	STDMETHOD	get_MarshalOptions, :ptr
	STDMETHOD	put_MarshalOptions, :MarshalOptionsEnum
	STDMETHOD	Find, :BSTR, :ADO_LONGPTR, :SearchDirectionEnum, :VARIANT
	STDMETHOD	Cancel
	STDMETHOD	get_DataSource, :ptr
	STDMETHOD	putref_DataSource, :ptr
	STDMETHOD	_xSave, :BSTR, :PersistFormatEnum
	STDMETHOD	get_ActiveCommand, :ptr
	STDMETHOD	put_StayInSync, :VARIANT_BOOL
	STDMETHOD	get_StayInSync, :ptr
	STDMETHOD	GetString, :StringFormatEnum, :LONG, :BSTR, :BSTR, :BSTR, :ptr
	STDMETHOD	get_DataMember, :ptr
	STDMETHOD	put_DataMember, :BSTR
	STDMETHOD	CompareBookmarks, :VARIANT, :VARIANT, :ptr
	STDMETHOD	Clone, :LockTypeEnum, :ptr
	STDMETHOD	Resync, :AffectEnum, :ResyncEnum
	STDMETHOD	Seek, :VARIANT, :SeekEnum
	STDMETHOD	put_Index, :BSTR
	STDMETHOD	get_Index, :ptr


Recordset21		ENDS

endif
ifndef ___Recordset_INTERFACE_DEFINED__
___Recordset_INTERFACE_DEFINED__ equ 1
externdef		IID__Recordset:IID
_Recordset		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_AbsolutePosition, :ptr
	STDMETHOD	put_AbsolutePosition, :PositionEnum_Param
	STDMETHOD	putref_ActiveADOConnection, :ptr
	STDMETHOD	put_ActiveConnection, :VARIANT
	STDMETHOD	get_ActiveConnection, :ptr
	STDMETHOD	get_BOF, :ptr
	STDMETHOD	get_Bookmark, :ptr
	STDMETHOD	put_Bookmark, :VARIANT
	STDMETHOD	get_CacheSize, :ptr
	STDMETHOD	put_CacheSize, :LONG
	STDMETHOD	get_CursorType, :ptr
	STDMETHOD	put_CursorType, :CursorTypeEnum
	STDMETHOD	get_EOF, :ptr
	STDMETHOD	get_Fields, :ptr
	STDMETHOD	get_LockType, :ptr
	STDMETHOD	put_LockType, :LockTypeEnum
	STDMETHOD	get_MaxRecords, :ptr
	STDMETHOD	put_MaxRecords, :ADO_LONGPTR
	STDMETHOD	get_RecordCount, :ptr
	STDMETHOD	putref_Source, :ptr
	STDMETHOD	put_Source, :BSTR
	STDMETHOD	get_Source, :ptr
	STDMETHOD	AddNew, :VARIANT, :VARIANT
	STDMETHOD	CancelUpdate
	STDMETHOD	Close
	STDMETHOD	Delete, :AffectEnum
	STDMETHOD	GetRows, :LONG, :VARIANT, :VARIANT, :ptr
	STDMETHOD	Move, :ADO_LONGPTR, :VARIANT
	STDMETHOD	MoveNext
	STDMETHOD	MovePrevious
	STDMETHOD	MoveFirst
	STDMETHOD	MoveLast
	STDMETHOD	Open, :VARIANT, :VARIANT, :CursorTypeEnum, :LockTypeEnum, :LONG
	STDMETHOD	Requery, :LONG
	STDMETHOD	_xResync, :AffectEnum
	STDMETHOD	Update, :VARIANT, :VARIANT
	STDMETHOD	get_AbsolutePage, :ptr
	STDMETHOD	put_AbsolutePage, :PositionEnum_Param
	STDMETHOD	get_EditMode, :ptr
	STDMETHOD	get_Filter, :ptr
	STDMETHOD	put_Filter, :VARIANT
	STDMETHOD	get_PageCount, :ptr
	STDMETHOD	get_PageSize, :ptr
	STDMETHOD	put_PageSize, :LONG
	STDMETHOD	get_Sort, :ptr
	STDMETHOD	put_Sort, :BSTR
	STDMETHOD	get_Status, :ptr
	STDMETHOD	get_State, :ptr
	STDMETHOD	_xClone, :ptr
	STDMETHOD	UpdateBatch, :AffectEnum
	STDMETHOD	CancelBatch, :AffectEnum
	STDMETHOD	get_CursorLocation, :ptr
	STDMETHOD	put_CursorLocation, :CursorLocationEnum
	STDMETHOD	NextADORecordset, :ptr, :ptr
	STDMETHOD	Supports, :CursorOptionEnum, :ptr
	STDMETHOD	get_Collect, :VARIANT, :ptr
	STDMETHOD	put_Collect, :VARIANT, :VARIANT
	STDMETHOD	get_MarshalOptions, :ptr
	STDMETHOD	put_MarshalOptions, :MarshalOptionsEnum
	STDMETHOD	Find, :BSTR, :ADO_LONGPTR, :SearchDirectionEnum, :VARIANT
	STDMETHOD	Cancel
	STDMETHOD	get_DataSource, :ptr
	STDMETHOD	putref_DataSource, :ptr
	STDMETHOD	_xSave, :BSTR, :PersistFormatEnum
	STDMETHOD	get_ActiveCommand, :ptr
	STDMETHOD	put_StayInSync, :VARIANT_BOOL
	STDMETHOD	get_StayInSync, :ptr
	STDMETHOD	GetString, :StringFormatEnum, :LONG, :BSTR, :BSTR, :BSTR, :ptr
	STDMETHOD	get_DataMember, :ptr
	STDMETHOD	put_DataMember, :BSTR
	STDMETHOD	CompareBookmarks, :VARIANT, :VARIANT, :ptr
	STDMETHOD	Clone, :LockTypeEnum, :ptr
	STDMETHOD	Resync, :AffectEnum, :ResyncEnum
	STDMETHOD	Seek, :VARIANT, :SeekEnum
	STDMETHOD	put_Index, :BSTR
	STDMETHOD	get_Index, :ptr
	STDMETHOD	Save, :VARIANT, :PersistFormatEnum


_Recordset		ENDS

endif
ifndef __ADORecordsetConstruction_INTERFACE_DEFINED__
__ADORecordsetConstruction_INTERFACE_DEFINED__ equ 1
externdef		IID_ADORecordsetConstruction:IID
ADORecordsetConstruction STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Rowset, :ptr
	STDMETHOD	put_Rowset, :ptr
	STDMETHOD	get_Chapter, :ptr
	STDMETHOD	put_Chapter, :ADO_LONGPTR
	STDMETHOD	get_RowPosition, :ptr
	STDMETHOD	put_RowPosition, :ptr


ADORecordsetConstruction ENDS

endif
ifndef __Field15_INTERFACE_DEFINED__
__Field15_INTERFACE_DEFINED__ equ 1
externdef		IID_Field15:IID
Field15			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ActualSize, :ptr
	STDMETHOD	get_Attributes, :ptr
	STDMETHOD	get_DefinedSize, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	get_Value, :ptr
	STDMETHOD	put_Value, :VARIANT
	STDMETHOD	get_Precision, :ptr
	STDMETHOD	get_NumericScale, :ptr
	STDMETHOD	AppendChunk, :VARIANT
	STDMETHOD	GetChunk, :LONG, :ptr
	STDMETHOD	get_OriginalValue, :ptr
	STDMETHOD	get_UnderlyingValue, :ptr


Field15			ENDS

endif
ifndef __Field20_INTERFACE_DEFINED__
__Field20_INTERFACE_DEFINED__ equ 1
externdef		IID_Field20:IID
Field20			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ActualSize, :ptr
	STDMETHOD	get_Attributes, :ptr
	STDMETHOD	get_DefinedSize, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	get_Value, :ptr
	STDMETHOD	put_Value, :VARIANT
	STDMETHOD	get_Precision, :ptr
	STDMETHOD	get_NumericScale, :ptr
	STDMETHOD	AppendChunk, :VARIANT
	STDMETHOD	GetChunk, :LONG, :ptr
	STDMETHOD	get_OriginalValue, :ptr
	STDMETHOD	get_UnderlyingValue, :ptr
	STDMETHOD	get_DataFormat, :ptr
	STDMETHOD	putref_DataFormat, :ptr
	STDMETHOD	put_Precision, :BYTE
	STDMETHOD	put_NumericScale, :BYTE
	STDMETHOD	put_Type, :DataTypeEnum
	STDMETHOD	put_DefinedSize, :ADO_LONGPTR
	STDMETHOD	put_Attributes, :LONG


Field20			ENDS

endif
ifndef __Field_INTERFACE_DEFINED__
__Field_INTERFACE_DEFINED__ equ 1
externdef		IID_Field:IID
Field			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_ActualSize, :ptr
	STDMETHOD	get_Attributes, :ptr
	STDMETHOD	get_DefinedSize, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	get_Value, :ptr
	STDMETHOD	put_Value, :VARIANT
	STDMETHOD	get_Precision, :ptr
	STDMETHOD	get_NumericScale, :ptr
	STDMETHOD	AppendChunk, :VARIANT
	STDMETHOD	GetChunk, :LONG, :ptr
	STDMETHOD	get_OriginalValue, :ptr
	STDMETHOD	get_UnderlyingValue, :ptr
	STDMETHOD	get_DataFormat, :ptr
	STDMETHOD	putref_DataFormat, :ptr
	STDMETHOD	put_Precision, :BYTE
	STDMETHOD	put_NumericScale, :BYTE
	STDMETHOD	put_Type, :DataTypeEnum
	STDMETHOD	put_DefinedSize, :ADO_LONGPTR
	STDMETHOD	put_Attributes, :LONG
	STDMETHOD	get_Status, :ptr


Field			ENDS

endif
ifndef __Fields15_INTERFACE_DEFINED__
__Fields15_INTERFACE_DEFINED__ equ 1
externdef		IID_Fields15:IID
Fields15		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Refresh
	STDMETHOD	get_Item, :VARIANT, :ptr


Fields15		ENDS

endif
ifndef __Fields20_INTERFACE_DEFINED__
__Fields20_INTERFACE_DEFINED__ equ 1
externdef		IID_Fields20:IID
Fields20		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Refresh
	STDMETHOD	get_Item, :VARIANT, :ptr
	STDMETHOD	_Append, :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum
	STDMETHOD	Delete, :VARIANT


Fields20		ENDS

endif
ifndef __Fields_INTERFACE_DEFINED__
__Fields_INTERFACE_DEFINED__ equ 1
externdef		IID_Fields:IID
Fields			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Refresh
	STDMETHOD	get_Item, :VARIANT, :ptr
	STDMETHOD	_Append, :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum
	STDMETHOD	Delete, :VARIANT
	STDMETHOD	Append, :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum, :VARIANT
	STDMETHOD	Update
	STDMETHOD	Resync, :ResyncEnum
	STDMETHOD	CancelUpdate


Fields			ENDS

endif
ifndef ___Parameter_INTERFACE_DEFINED__
___Parameter_INTERFACE_DEFINED__ equ 1
externdef		IID__Parameter:IID
_Parameter		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	put_Name, :BSTR
	STDMETHOD	get_Value, :ptr
	STDMETHOD	put_Value, :VARIANT
	STDMETHOD	get_Type, :ptr
	STDMETHOD	put_Type, :DataTypeEnum
	STDMETHOD	put_Direction, :ParameterDirectionEnum
	STDMETHOD	get_Direction, :ptr
	STDMETHOD	put_Precision, :BYTE
	STDMETHOD	get_Precision, :ptr
	STDMETHOD	put_NumericScale, :BYTE
	STDMETHOD	get_NumericScale, :ptr
	STDMETHOD	put_Size, :ADO_LONGPTR
	STDMETHOD	get_Size, :ptr
	STDMETHOD	AppendChunk, :VARIANT
	STDMETHOD	get_Attributes, :ptr
	STDMETHOD	put_Attributes, :LONG


_Parameter		ENDS

endif
externdef		CLSID_Parameter:CLSID
ifdef __cplusplus
Parameter;
endif
ifndef __Parameters_INTERFACE_DEFINED__
__Parameters_INTERFACE_DEFINED__ equ 1
externdef		IID_Parameters:IID
Parameters		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Refresh
	STDMETHOD	Append, :ptr
	STDMETHOD	Delete, :VARIANT
	STDMETHOD	get_Item, :VARIANT, :ptr


Parameters		ENDS

endif
ifndef __Property_INTERFACE_DEFINED__
__Property_INTERFACE_DEFINED__ equ 1
externdef		IID_Property:IID
Property		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Value, :ptr
	STDMETHOD	put_Value, :VARIANT
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	get_Attributes, :ptr
	STDMETHOD	put_Attributes, :LONG


Property		ENDS

endif
ifndef __Properties_INTERFACE_DEFINED__
__Properties_INTERFACE_DEFINED__ equ 1
externdef		IID_Properties:IID
Properties		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Refresh
	STDMETHOD	get_Item, :VARIANT, :ptr


Properties		ENDS

endif
endif
externdef		__MIDL_itf_ado10_0001_0035_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_ado10_0001_0035_v0_0_s_ifspec:RPC_IF_HANDLE

endif

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

ifndef _ADOINT_H_
define _ADOINT_H_
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef _TCHAR_
include tchar.inc
endif
ifndef _RPC500_
include rpc500.inc
endif
ifndef __ado10_h__
define __ado10_h__

ifdef _WIN64
ADO_LONGPTR	typedef LONGLONG
else
ADO_LONGPTR	typedef LONG
endif

ifndef __ADODB_LIBRARY_DEFINED__
define __ADODB_LIBRARY_DEFINED__

.enum CursorTypeEnum {
	adOpenUnspecified	= -1,
	adOpenForwardOnly	= 0,
	adOpenKeyset		= 1,
	adOpenDynamic		= 2,
	adOpenStatic		= 3
	}

.enum CursorOptionEnum {
	adHoldRecords		= 0x100,
	adMovePrevious		= 0x200,
	adAddNew		= 0x1000400,
	adDelete		= 0x1000800,
	adUpdate		= 0x1008000,
	adBookmark		= 0x2000,
	adApproxPosition	= 0x4000,
	adUpdateBatch		= 0x10000,
	adResync		= 0x20000,
	adNotify		= 0x40000,
	adFind			= 0x80000,
	adSeek			= 0x400000,
	adIndex			= 0x800000
	}

.enum LockTypeEnum {
	adLockUnspecified	= -1,
	adLockReadOnly		= 1,
	adLockPessimistic	= 2,
	adLockOptimistic	= 3,
	adLockBatchOptimistic	= 4
	}

.enum ExecuteOptionEnum {
	adOptionUnspecified	= -1,
	adAsyncExecute		= 0x10,
	adAsyncFetch		= 0x20,
	adAsyncFetchNonBlocking = 0x40,
	adExecuteNoRecords	= 0x80,
	adExecuteStream		= 0x400,
	adExecuteRecord		= 0x800
	}

.enum ConnectOptionEnum {
	adConnectUnspecified	= -1,
	adAsyncConnect		= 0x10
	}

.enum ObjectStateEnum {
	adStateClosed		= 0,
	adStateOpen		= 0x1,
	adStateConnecting	= 0x2,
	adStateExecuting	= 0x4,
	adStateFetching		= 0x8
	}

.enum CursorLocationEnum {
	adUseNone		= 1,
	adUseServer		= 2,
	adUseClient		= 3,
	adUseClientBatch	= 3
	}

.enum DataTypeEnum {
	adEmpty			= 0,
	adTinyInt		= 16,
	adSmallInt		= 2,
	adInteger		= 3,
	adBigInt		= 20,
	adUnsignedTinyInt	= 17,
	adUnsignedSmallInt	= 18,
	adUnsignedInt		= 19,
	adUnsignedBigInt	= 21,
	adSingle		= 4,
	adDouble		= 5,
	adCurrency		= 6,
	adDecimal		= 14,
	adNumeric		= 131,
	adBoolean		= 11,
	adError			= 10,
	adUserDefined		= 132,
	adVariant		= 12,
	adIDispatch		= 9,
	adIUnknown		= 13,
	adGUID			= 72,
	adDate			= 7,
	adDBDate		= 133,
	adDBTime		= 134,
	adDBTimeStamp		= 135,
	adBSTR			= 8,
	adChar			= 129,
	adVarChar		= 200,
	adLongVarChar		= 201,
	adWChar			= 130,
	adVarWChar		= 202,
	adLongVarWChar		= 203,
	adBinary		= 128,
	adVarBinary		= 204,
	adLongVarBinary		= 205,
	adChapter		= 136,
	adFileTime		= 64,
	adPropVariant		= 138,
	adVarNumeric		= 139,
	adArray			= 0x2000
	}

.enum FieldAttributeEnum {
	adFldUnspecified	= -1,
	adFldMayDefer		= 0x2,
	adFldUpdatable		= 0x4,
	adFldUnknownUpdatable	= 0x8,
	adFldFixed		= 0x10,
	adFldIsNullable		= 0x20,
	adFldMayBeNull		= 0x40,
	adFldLong		= 0x80,
	adFldRowID		= 0x100,
	adFldRowVersion		= 0x200,
	adFldCacheDeferred	= 0x1000,
	adFldIsChapter		= 0x2000,
	adFldNegativeScale	= 0x4000,
	adFldKeyColumn		= 0x8000,
	adFldIsRowURL		= 0x10000,
	adFldIsDefaultStream	= 0x20000,
	adFldIsCollection	= 0x40000
	}

.enum EditModeEnum {
	adEditNone		= 0,
	adEditInProgress	= 0x1,
	adEditAdd		= 0x2,
	adEditDelete		= 0x4
	}

.enum RecordStatusEnum {
	adRecOK			= 0,
	adRecNew		= 0x1,
	adRecModified		= 0x2,
	adRecDeleted		= 0x4,
	adRecUnmodified		= 0x8,
	adRecInvalid		= 0x10,
	adRecMultipleChanges	= 0x40,
	adRecPendingChanges	= 0x80,
	adRecCanceled		= 0x100,
	adRecCantRelease	= 0x400,
	adRecConcurrencyViolation = 0x800,
	adRecIntegrityViolation = 0x1000,
	adRecMaxChangesExceeded = 0x2000,
	adRecObjectOpen		= 0x4000,
	adRecOutOfMemory	= 0x8000,
	adRecPermissionDenied	= 0x10000,
	adRecSchemaViolation	= 0x20000,
	adRecDBDeleted		= 0x40000
	}

.enum GetRowsOptionEnum {
	adGetRowsRest		= -1
	}

.enum PositionEnum {
	adPosUnknown		= -1,
	adPosBOF		= -2,
	adPosEOF		= -3
	}

ifdef _WIN64
PositionEnum_Param	typedef LONGLONG
else
PositionEnum_Param	typedef PositionEnum
endif

.enum BookmarkEnum {
	adBookmarkCurrent	= 0,
	adBookmarkFirst		= 1,
	adBookmarkLast		= 2
	}

.enum MarshalOptionsEnum {
	adMarshalAll		= 0,
	adMarshalModifiedOnly	= 1
	}

.enum AffectEnum {
	adAffectCurrent		= 1,
	adAffectGroup		= 2,
	adAffectAll		= 3,
	adAffectAllChapters	= 4
	}

.enum ResyncEnum {
	adResyncUnderlyingValues = 1,
	adResyncAllValues	= 2
	}

.enum CompareEnum {
	adCompareLessThan	= 0,
	adCompareEqual		= 1,
	adCompareGreaterThan	= 2,
	adCompareNotEqual	= 3,
	adCompareNotComparable	= 4
	}

.enum FilterGroupEnum {
	adFilterNone		= 0,
	adFilterPendingRecords	= 1,
	adFilterAffectedRecords = 2,
	adFilterFetchedRecords	= 3,
	adFilterPredicate	= 4,
	adFilterConflictingRecords = 5
	}

.enum SearchDirectionEnum {
	adSearchForward		= 1,
	adSearchBackward	= -1
	}
	SearchDirection typedef SearchDirectionEnum

.enum PersistFormatEnum {
	adPersistADTG		= 0,
	adPersistXML		= 1
	}

.enum StringFormatEnum {
	adClipString		= 2
	}

.enum ConnectPromptEnum {
	adPromptAlways		= 1,
	adPromptComplete	= 2,
	adPromptCompleteRequired = 3,
	adPromptNever		= 4
	}

.enum ConnectModeEnum {
	adModeUnknown		= 0,
	adModeRead		= 1,
	adModeWrite		= 2,
	adModeReadWrite		= 3,
	adModeShareDenyRead	= 4,
	adModeShareDenyWrite	= 8,
	adModeShareExclusive	= 0xc,
	adModeShareDenyNone	= 0x10,
	adModeRecursive		= 0x400000
	}

.enum RecordCreateOptionsEnum {
	adCreateCollection	= 0x2000,
	adCreateStructDoc	= 0x80000000,
	adCreateNonCollection	= 0,
	adOpenIfExists		= 0x2000000,
	adCreateOverwrite	= 0x4000000,
	adFailIfNotExists	= -1
	}

.enum RecordOpenOptionsEnum {
	adOpenRecordUnspecified = -1,
	adOpenSource		= 0x800000,
	adOpenOutput		= 0x800000,
	adOpenAsync		= 0x1000,
	adDelayFetchStream	= 0x4000,
	adDelayFetchFields	= 0x8000,
	adOpenExecuteCommand	= 0x10000
	}

.enum IsolationLevelEnum {
	adXactUnspecified	= 0xffffffff,
	adXactChaos		= 0x10,
	adXactReadUncommitted	= 0x100,
	adXactBrowse		= 0x100,
	adXactCursorStability	= 0x1000,
	adXactReadCommitted	= 0x1000,
	adXactRepeatableRead	= 0x10000,
	adXactSerializable	= 0x100000,
	adXactIsolated		= 0x100000
	}

.enum XactAttributeEnum {
	adXactCommitRetaining	= 0x20000,
	adXactAbortRetaining	= 0x40000,
	adXactAsyncPhaseOne	= 0x80000,
	adXactSyncPhaseOne	= 0x100000
	}

.enum PropertyAttributesEnum {
	adPropNotSupported	= 0,
	adPropRequired		= 0x1,
	adPropOptional		= 0x2,
	adPropRead		= 0x200,
	adPropWrite		= 0x400
	}

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
	adErrFeatureNotAvailable = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_CONTROL,  0xcb3),
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

.enum ParameterAttributesEnum {
	adParamSigned		= 0x10,
	adParamNullable		= 0x40,
	adParamLong		= 0x80
	}

.enum ParameterDirectionEnum {
	adParamUnknown		= 0,
	adParamInput		= 0x1,
	adParamOutput		= 0x2,
	adParamInputOutput	= 0x3,
	adParamReturnValue	= 0x4
	}

.enum CommandTypeEnum {
	adCmdUnspecified	= -1,
	adCmdUnknown		= 0x8,
	adCmdText		= 0x1,
	adCmdTable		= 0x2,
	adCmdStoredProc		= 0x4,
	adCmdFile		= 0x100,
	adCmdTableDirect	= 0x200
	}

.enum EventStatusEnum {
	adStatusOK		= 0x1,
	adStatusErrorsOccurred	= 0x2,
	adStatusCantDeny	= 0x3,
	adStatusCancel		= 0x4,
	adStatusUnwantedEvent	= 0x5
	}

.enum EventReasonEnum {
	adRsnAddNew		= 1,
	adRsnDelete		= 2,
	adRsnUpdate		= 3,
	adRsnUndoUpdate		= 4,
	adRsnUndoAddNew		= 5,
	adRsnUndoDelete		= 6,
	adRsnRequery		= 7,
	adRsnResynch		= 8,
	adRsnClose		= 9,
	adRsnMove		= 10,
	adRsnFirstChange	= 11,
	adRsnMoveFirst		= 12,
	adRsnMoveNext		= 13,
	adRsnMovePrevious	= 14,
	adRsnMoveLast		= 15
	}

.enum SchemaEnum {
	adSchemaProviderSpecific = -1,
	adSchemaAsserts		= 0,
	adSchemaCatalogs	= 1,
	adSchemaCharacterSets	= 2,
	adSchemaCollations	= 3,
	adSchemaColumns		= 4,
	adSchemaCheckConstraints = 5,
	adSchemaConstraintColumnUsage = 6,
	adSchemaConstraintTableUsage = 7,
	adSchemaKeyColumnUsage	= 8,
	adSchemaReferentialContraints = 9,
	adSchemaReferentialConstraints = 9,
	adSchemaTableConstraints = 10,
	adSchemaColumnsDomainUsage = 11,
	adSchemaIndexes		= 12,
	adSchemaColumnPrivileges = 13,
	adSchemaTablePrivileges = 14,
	adSchemaUsagePrivileges = 15,
	adSchemaProcedures	= 16,
	adSchemaSchemata	= 17,
	adSchemaSQLLanguages	= 18,
	adSchemaStatistics	= 19,
	adSchemaTables		= 20,
	adSchemaTranslations	= 21,
	adSchemaProviderTypes	= 22,
	adSchemaViews		= 23,
	adSchemaViewColumnUsage = 24,
	adSchemaViewTableUsage	= 25,
	adSchemaProcedureParameters = 26,
	adSchemaForeignKeys	= 27,
	adSchemaPrimaryKeys	= 28,
	adSchemaProcedureColumns = 29,
	adSchemaDBInfoKeywords	= 30,
	adSchemaDBInfoLiterals	= 31,
	adSchemaCubes		= 32,
	adSchemaDimensions	= 33,
	adSchemaHierarchies	= 34,
	adSchemaLevels		= 35,
	adSchemaMeasures	= 36,
	adSchemaProperties	= 37,
	adSchemaMembers		= 38,
	adSchemaTrustees	= 39,
	adSchemaFunctions	= 40,
	adSchemaActions		= 41,
	adSchemaCommands	= 42,
	adSchemaSets		= 43
	}

.enum FieldStatusEnum {
	adFieldOK		= 0,
	adFieldCantConvertValue = 2,
	adFieldIsNull		= 3,
	adFieldTruncated	= 4,
	adFieldSignMismatch	= 5,
	adFieldDataOverflow	= 6,
	adFieldCantCreate	= 7,
	adFieldUnavailable	= 8,
	adFieldPermissionDenied = 9,
	adFieldIntegrityViolation = 10,
	adFieldSchemaViolation	= 11,
	adFieldBadStatus	= 12,
	adFieldDefault		= 13,
	adFieldIgnore		= 15,
	adFieldDoesNotExist	= 16,
	adFieldInvalidURL	= 17,
	adFieldResourceLocked	= 18,
	adFieldResourceExists	= 19,
	adFieldCannotComplete	= 20,
	adFieldVolumeNotFound	= 21,
	adFieldOutOfSpace	= 22,
	adFieldCannotDeleteSource = 23,
	adFieldReadOnly		= 24,
	adFieldResourceOutOfScope = 25,
	adFieldAlreadyExists	= 26,
	adFieldPendingInsert	= 0x10000,
	adFieldPendingDelete	= 0x20000,
	adFieldPendingChange	= 0x40000,
	adFieldPendingUnknown	= 0x80000,
	adFieldPendingUnknownDelete = 0x100000
	}

.enum SeekEnum {
	adSeekFirstEQ		= 0x1,
	adSeekLastEQ		= 0x2,
	adSeekAfterEQ		= 0x4,
	adSeekAfter		= 0x8,
	adSeekBeforeEQ		= 0x10,
	adSeekBefore		= 0x20
	}
ifndef _COMMON_ADC_AND_ADO_PROPS_
define _COMMON_ADC_AND_ADO_PROPS_

.enum ADCPROP_UPDATECRITERIA_ENUM {
	adCriteriaKey		= 0,
	adCriteriaAllCols	= 1,
	adCriteriaUpdCols	= 2,
	adCriteriaTimeStamp	= 3
	}

.enum ADCPROP_ASYNCTHREADPRIORITY_ENUM {
	adPriorityLowest	= 1,
	adPriorityBelowNormal	= 2,
	adPriorityNormal	= 3,
	adPriorityAboveNormal	= 4,
	adPriorityHighest	= 5
	}

.enum ADCPROP_AUTORECALC_ENUM {
	adRecalcUpFront		= 0,
	adRecalcAlways		= 1
	}

.enum ADCPROP_UPDATERESYNC_ENUM {
	adResyncNone		= 0,
	adResyncAutoIncrement	= 1,
	adResyncConflicts	= 2,
	adResyncUpdates		= 4,
	adResyncInserts		= 8,
	adResyncAll		= 15
	}
endif
CEResyncEnum typedef ADCPROP_UPDATERESYNC_ENUM

.enum MoveRecordOptionsEnum {
	adMoveUnspecified	= -1,
	adMoveOverWrite		= 1,
	adMoveDontUpdateLinks	= 2,
	adMoveAllowEmulation	= 4
	}

.enum CopyRecordOptionsEnum {
	adCopyUnspecified	= -1,
	adCopyOverWrite		= 1,
	adCopyAllowEmulation	= 4,
	adCopyNonRecursive	= 2
	}

.enum StreamTypeEnum {
	adTypeBinary		= 1,
	adTypeText		= 2
	}

.enum LineSeparatorEnum {
	adLF			= 10,
	adCR			= 13,
	adCRLF			= -1
	}

.enum StreamOpenOptionsEnum {
	adOpenStreamUnspecified = -1,
	adOpenStreamAsync	= 1,
	adOpenStreamFromRecord	= 4
	}

.enum StreamWriteEnum {
	adWriteChar		= 0,
	adWriteLine		= 1,
	stWriteChar		= 0,
	stWriteLine		= 1
	}

.enum SaveOptionsEnum {
	adSaveCreateNotExist	= 1,
	adSaveCreateOverWrite	= 2
	}

.enum FieldEnum {
	adDefaultStream		= -1,
	adRecordURL		= -2
	}

.enum StreamReadEnum {
	adReadAll		= -1,
	adReadLine		= -2
	}

.enum RecordTypeEnum {
	adSimpleRecord		= 0,
	adCollectionRecord	= 1,
	adStructDoc		= 2
	}

externdef LIBID_ADODB:IID

ifndef ___ADOCollection_INTERFACE_DEFINED__
define ___ADOCollection_INTERFACE_DEFINED__
DEFINE_IIDX(_ADOCollection, "00000512-0000-0010-8000-00AA006D2EA4")

.comdef _ADOCollection : public IDispatch
    get_Count		proc :ptr
    _NewEnum		proc :ptr ptr
    Refresh		proc
   .ends
endif

ifndef ___ADODynaCollection_INTERFACE_DEFINED__
define ___ADODynaCollection_INTERFACE_DEFINED__
DEFINE_IIDX(_ADODynaCollection, "00000513-0000-0010-8000-00AA006D2EA4")

.comdef _ADODynaCollection : public _ADOCollection
    Append		proc :ptr
    Delete		proc :VARIANT
   .ends
endif

ifndef ___ADO_INTERFACE_DEFINED__
define ___ADO_INTERFACE_DEFINED__
DEFINE_IIDX(_ADO, "00000534-0000-0010-8000-00AA006D2EA4")

.comdef _ADO : public IDispatch
    get_Properties	proc :ptr ptr
   .ends
endif

ifndef __Error_INTERFACE_DEFINED__
define __Error_INTERFACE_DEFINED__
DEFINE_IIDX(ADOError, "00000500-0000-0010-8000-00AA006D2EA4")

.comdef ADOError : public IDispatch
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
define __Errors_INTERFACE_DEFINED__
DEFINE_IIDX(ADOErrors, "00000501-0000-0010-8000-00AA006D2EA4")

.comdef ADOErrors : public _ADOCollection
    get_Item		proc :VARIANT, :ptr ptr
    Clear		proc
   .ends
endif

ifndef __Command15_INTERFACE_DEFINED__
define __Command15_INTERFACE_DEFINED__
DEFINE_IIDX(Command15, "00000508-0000-0010-8000-00AA006D2EA4")

.comdef Command15 : public _ADO
    get_ActiveConnection proc :ptr ptr
    putref_ActiveConnection proc :ptr
    put_ActiveConnection proc :VARIANT
    get_CommandText	proc :ptr
    put_CommandText	proc :BSTR
    get_CommandTimeout	proc :ptr
    put_CommandTimeout	proc :LONG
    get_Prepared	proc :ptr
    put_Prepared	proc :VARIANT_BOOL
    Execute		proc :ptr, :ptr, :LONG, :ptr ptr
    CreateParameter	proc :BSTR, :DataTypeEnum, :ParameterDirectionEnum, :ADO_LONGPTR, :VARIANT, :ptr ptr
    get_Parameters	proc :ptr ptr
    put_CommandType	proc :CommandTypeEnum
    get_CommandType	proc :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
   .ends
endif

ifndef __Command25_INTERFACE_DEFINED__
define __Command25_INTERFACE_DEFINED__
DEFINE_IIDX(Command25, "0000054E-0000-0010-8000-00AA006D2EA4")

.comdef Command25 : public Command15
    get_State		proc :ptr
    Cancel		proc
   .ends
endif

ifndef ___Command_INTERFACE_DEFINED__
define ___Command_INTERFACE_DEFINED__
DEFINE_IIDX(_ADOCommand, "B08400BD-F9D1-4D02-B856-71D5DBA123E9")

.comdef _ADOCommand : public Command25
    putref_CommandStream proc :ptr
    get_CommandStream	proc :ptr
    put_Dialect		proc :BSTR
    get_Dialect		proc :ptr
    put_NamedParameters proc :VARIANT_BOOL
    get_NamedParameters proc :ptr
   .ends
endif

ifndef __ConnectionEventsVt_INTERFACE_DEFINED__
define __ConnectionEventsVt_INTERFACE_DEFINED__
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
define __RecordsetEventsVt_INTERFACE_DEFINED__
DEFINE_IIDX(RecordsetEventsVt, "00000403-0000-0010-8000-00AA006D2EA4")

.comdef RecordsetEventsVt : public IUnknown
    WillChangeField	proc :LONG, :VARIANT, :ptr, :ptr
    FieldChangeComplete proc :LONG, :VARIANT, :ptr, :ptr, :ptr
    WillChangeRecord	proc :EventReasonEnum, :LONG, :ptr, :ptr
    RecordChangeComplete proc :EventReasonEnum, :LONG, :ptr, :ptr, :ptr
    WillChangeRecordset proc :EventReasonEnum, :ptr, :ptr
    RecordsetChangeComplete proc :EventReasonEnum, :ptr, :ptr, :ptr
    WillMove		proc :EventReasonEnum, :ptr, :ptr
    MoveComplete	proc :EventReasonEnum, :ptr, :ptr, :ptr
    EndOfRecordset	proc :ptr, :ptr, :ptr
    FetchProgress	proc :LONG, :LONG, :ptr, :ptr
    FetchComplete	proc :ptr, :ptr, :ptr
   .ends
endif

ifndef __ConnectionEvents_DISPINTERFACE_DEFINED__
define __ConnectionEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(ConnectionEvents, "00000400-0000-0010-8000-00AA006D2EA4")

.comdef ConnectionEvents : public IDispatch
   .ends
endif

ifndef __RecordsetEvents_DISPINTERFACE_DEFINED__
define __RecordsetEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(RecordsetEvents, "00000266-0000-0010-8000-00AA006D2EA4")

.comdef RecordsetEvents : public IDispatch
   .ends
endif

ifndef __Connection15_INTERFACE_DEFINED__
define __Connection15_INTERFACE_DEFINED__
DEFINE_IIDX(Connection15, "00000515-0000-0010-8000-00AA006D2EA4")

.comdef Connection15 : public _ADO
    get_ConnectionString proc :ptr
    put_ConnectionString proc :BSTR
    get_CommandTimeout	proc :ptr
    put_CommandTimeout	proc :LONG
    get_ConnectionTimeout proc :ptr
    put_ConnectionTimeout proc :LONG
    get_Version		proc :ptr
    Close		proc
    Execute		proc :BSTR, :ptr, :LONG, :ptr ptr
    BeginTrans		proc :ptr
    CommitTrans		proc
    RollbackTrans	proc
    Open		proc :BSTR, :BSTR, :BSTR, :LONG
    get_Errors		proc :ptr ptr
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
    OpenSchema		proc :SchemaEnum, :VARIANT, :VARIANT, :ptr ptr
   .ends
endif

ifndef ___Connection_INTERFACE_DEFINED__
define ___Connection_INTERFACE_DEFINED__
DEFINE_IIDX(_ADOConnection, "00000550-0000-0010-8000-00AA006D2EA4")

.comdef _ADOConnection : public Connection15
    Cancel		proc
   .ends
endif

ifndef __ADOConnectionConstruction15_INTERFACE_DEFINED__
define __ADOConnectionConstruction15_INTERFACE_DEFINED__
DEFINE_IIDX(ADOConnectionConstruction15, "00000516-0000-0010-8000-00AA006D2EA4")

.comdef ADOConnectionConstruction15 : public IUnknown
    get_DSO		proc :ptr ptr
    get_Session		proc :ptr ptr
    WrapDSOandSession	proc :ptr, :ptr
   .ends
endif

ifndef __ADOConnectionConstruction_INTERFACE_DEFINED__
define __ADOConnectionConstruction_INTERFACE_DEFINED__
DEFINE_IIDX(ADOConnectionConstruction, "00000551-0000-0010-8000-00AA006D2EA4")

.comdef ADOConnectionConstruction : public ADOConnectionConstruction15
   .ends
endif

ifndef ___Record_INTERFACE_DEFINED__
define ___Record_INTERFACE_DEFINED__
DEFINE_IIDX(_ADORecord, "00000562-0000-0010-8000-00AA006D2EA4")

.comdef _ADORecord : public _ADO
    get_ActiveConnection proc :ptr
    put_ActiveConnection proc :BSTR
    putref_ActiveConnection proc :ptr
    get_State		proc :ptr
    get_Source		proc :ptr
    put_Source		proc :BSTR
    putref_Source	proc :ptr
    get_Mode		proc :ptr
    put_Mode		proc :ConnectModeEnum
    get_ParentURL	proc :ptr
    MoveRecord		proc :BSTR, :BSTR, :BSTR, :BSTR, :MoveRecordOptionsEnum, :VARIANT_BOOL, :ptr
    CopyRecord		proc :BSTR, :BSTR, :BSTR, :BSTR, :CopyRecordOptionsEnum, :VARIANT_BOOL, :ptr
    DeleteRecord	proc :BSTR, :VARIANT_BOOL
    Open		proc :VARIANT, :VARIANT, :ConnectModeEnum, :RecordCreateOptionsEnum, :RecordOpenOptionsEnum, :BSTR, :BSTR
    Close		proc
    get_Fields		proc :ptr ptr
    get_RecordType	proc :ptr
    GetChildren		proc :ptr ptr
    Cancel		proc
   .ends
endif

ifndef ___Stream_INTERFACE_DEFINED__
define ___Stream_INTERFACE_DEFINED__
DEFINE_IIDX(_ADOStream, "00000565-0000-0010-8000-00AA006D2EA4")

.comdef _ADOStream : public IDispatch
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

ifndef __ADORecordConstruction_INTERFACE_DEFINED__
define __ADORecordConstruction_INTERFACE_DEFINED__
DEFINE_IIDX(ADORecordConstruction, "00000567-0000-0010-8000-00AA006D2EA4")

.comdef ADORecordConstruction : public IDispatch
    get_Row		proc :ptr ptr
    put_Row		proc :ptr
    put_ParentRow	proc :ptr
   .ends
endif

ifndef __ADOStreamConstruction_INTERFACE_DEFINED__
define __ADOStreamConstruction_INTERFACE_DEFINED__
DEFINE_IIDX(ADOStreamConstruction, "00000568-0000-0010-8000-00AA006D2EA4")

.comdef ADOStreamConstruction : public IDispatch
    get_Stream		proc :ptr ptr
    put_Stream		proc :ptr
   .ends
endif

ifndef __ADOCommandConstruction_INTERFACE_DEFINED__
define __ADOCommandConstruction_INTERFACE_DEFINED__
DEFINE_IIDX(ADOCommandConstruction, "00000517-0000-0010-8000-00AA006D2EA4")

.comdef ADOCommandConstruction : public IUnknown
    get_OLEDBCommand	proc :ptr ptr
    put_OLEDBCommand	proc :ptr
   .ends
endif

ifndef __Recordset15_INTERFACE_DEFINED__
define __Recordset15_INTERFACE_DEFINED__
DEFINE_IIDX(Recordset15, "0000050E-0000-0010-8000-00AA006D2EA4")

.comdef Recordset15 : public _ADO
    get_AbsolutePosition proc :ptr
    put_AbsolutePosition proc :PositionEnum_Param
    putref_ActiveConnection proc :ptr
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
    get_Fields		proc :ptr ptr
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
    _xClone		proc :ptr ptr
    UpdateBatch		proc :AffectEnum
    CancelBatch		proc :AffectEnum
    get_CursorLocation	proc :ptr
    put_CursorLocation	proc :CursorLocationEnum
    NextRecordset	proc :ptr, :ptr ptr
    Supports		proc :CursorOptionEnum, :ptr
    get_Collect		proc :VARIANT, :ptr
    put_Collect		proc :VARIANT, :VARIANT
    get_MarshalOptions	proc :ptr
    put_MarshalOptions	proc :MarshalOptionsEnum
    Find		proc :BSTR, :ADO_LONGPTR, :SearchDirectionEnum, :VARIANT
   .ends
endif

ifndef __Recordset20_INTERFACE_DEFINED__
define __Recordset20_INTERFACE_DEFINED__
DEFINE_IIDX(Recordset20, "0000054F-0000-0010-8000-00AA006D2EA4")

.comdef Recordset20 : public Recordset15
    Cancel		proc
    get_DataSource	proc :ptr ptr
    putref_DataSource	proc :ptr
    _xSave		proc :BSTR, :PersistFormatEnum
    get_ActiveCommand	proc :ptr ptr
    put_StayInSync	proc :VARIANT_BOOL
    get_StayInSync	proc :ptr
    GetString		proc :StringFormatEnum, :LONG, :BSTR, :BSTR, :BSTR, :ptr
    get_DataMember	proc :ptr
    put_DataMember	proc :BSTR
    CompareBookmarks	proc :VARIANT, :VARIANT, :ptr
    Clone		proc :LockTypeEnum, :ptr ptr
    Resync		proc :AffectEnum, :ResyncEnum
   .ends
endif

ifndef __Recordset21_INTERFACE_DEFINED__
define __Recordset21_INTERFACE_DEFINED__
DEFINE_IIDX(Recordset21, "00000555-0000-0010-8000-00AA006D2EA4")

.comdef Recordset21 : public Recordset20
    Seek		proc :VARIANT, :SeekEnum
    put_Index		proc :BSTR
    get_Index		proc :ptr
   .ends
endif

ifndef ___Recordset_INTERFACE_DEFINED__
define ___Recordset_INTERFACE_DEFINED__
DEFINE_IIDX(_ADORecordset, "00000556-0000-0010-8000-00AA006D2EA4")

.comdef _ADORecordset : public Recordset21
    Save		proc :VARIANT, :PersistFormatEnum
   .ends
endif

ifndef __ADORecordsetConstruction_INTERFACE_DEFINED__
define __ADORecordsetConstruction_INTERFACE_DEFINED__
DEFINE_IIDX(ADORecordsetConstruction, "00000283-0000-0010-8000-00AA006D2EA4")

.comdef ADORecordsetConstruction : public IDispatch
    get_Rowset		proc :ptr ptr
    put_Rowset		proc :ptr
    get_Chapter		proc :ptr
    put_Chapter		proc :ADO_LONGPTR
    get_RowPosition	proc :ptr ptr
    put_RowPosition	proc :ptr
   .ends
endif

ifndef __Field15_INTERFACE_DEFINED__
define __Field15_INTERFACE_DEFINED__
DEFINE_IIDX(Field15, "00000505-0000-0010-8000-00AA006D2EA4")

.comdef Field15 : public _ADO
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
define __Field20_INTERFACE_DEFINED__
DEFINE_IIDX(Field20, "0000054C-0000-0010-8000-00AA006D2EA4")

.comdef Field20 : public _ADO
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
    get_DataFormat	proc :ptr ptr
    putref_DataFormat	proc :ptr
    put_Precision	proc :BYTE
    put_NumericScale	proc :BYTE
    put_Type		proc :DataTypeEnum
    put_DefinedSize	proc :ADO_LONGPTR
    put_Attributes	proc :LONG
   .ends
endif

ifndef __Field_INTERFACE_DEFINED__
define __Field_INTERFACE_DEFINED__
DEFINE_IIDX(ADOField, "00000569-0000-0010-8000-00AA006D2EA4")

.comdef ADOField : public Field20
    get_Status		proc :ptr
   .ends
endif

ifndef __Fields15_INTERFACE_DEFINED__
define __Fields15_INTERFACE_DEFINED__
DEFINE_IIDX(Fields15, "00000506-0000-0010-8000-00AA006D2EA4")

.comdef Fields15 : public _ADOCollection
    get_Item		proc :VARIANT, :ptr ptr
   .ends
endif

ifndef __Fields20_INTERFACE_DEFINED__
define __Fields20_INTERFACE_DEFINED__
DEFINE_IIDX(Fields20, "0000054D-0000-0010-8000-00AA006D2EA4")

.comdef Fields20 : public Fields15
    _Append		proc :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum
    Delete		proc :VARIANT
   .ends
endif

ifndef __Fields_INTERFACE_DEFINED__
define __Fields_INTERFACE_DEFINED__
DEFINE_IIDX(ADOFields, "00000564-0000-0010-8000-00AA006D2EA4")

.comdef ADOFields : public Fields20
    Append		proc :BSTR, :DataTypeEnum, :ADO_LONGPTR, :FieldAttributeEnum, :VARIANT
    Update		proc
    Resync		proc :ResyncEnum
    CancelUpdate	proc
   .ends
endif

ifndef ___Parameter_INTERFACE_DEFINED__
define ___Parameter_INTERFACE_DEFINED__
DEFINE_IIDX(_ADOParameter, "0000050C-0000-0010-8000-00AA006D2EA4")

.comdef _ADOParameter : public _ADO
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

ifndef __Parameters_INTERFACE_DEFINED__
define __Parameters_INTERFACE_DEFINED__
DEFINE_IIDX(ADOParameters, "0000050D-0000-0010-8000-00AA006D2EA4")

.comdef ADOParameters : public _ADODynaCollection
    get_Item		proc :VARIANT, :ptr ptr
   .ends
endif

ifndef __Property_INTERFACE_DEFINED__
define __Property_INTERFACE_DEFINED__
DEFINE_IIDX(ADOProperty, "00000503-0000-0010-8000-00AA006D2EA4")

.comdef ADOProperty : public IDispatch
    get_Value		proc :ptr
    put_Value		proc :VARIANT
    get_Name		proc :ptr
    get_Type		proc :ptr
    get_Attributes	proc :ptr
    put_Attributes	proc :LONG
   .ends
endif

ifndef __Properties_INTERFACE_DEFINED__
define __Properties_INTERFACE_DEFINED__
DEFINE_IIDX(ADOProperties, "00000504-0000-0010-8000-00AA006D2EA4")

.comdef ADOProperties : public _ADOCollection
    get_Item		proc :VARIANT, :ptr ptr
   .ends
endif

endif

endif

ADOCommand		typedef _ADOCommand
ADORecordset		typedef _ADORecordset
ADOParameter		typedef _ADOParameter
ADOConnection		typedef _ADOConnection
ADOCollection		typedef _ADOCollection
ADODynaCollection	typedef _ADODynaCollection
ADORecord		typedef _ADORecord
ADOStream		typedef _ADOStream

endif

endif

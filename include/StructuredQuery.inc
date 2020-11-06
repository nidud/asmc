.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
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

ifndef __structuredquery_h__
__structuredquery_h__ equ <>

ifndef __IQueryParser_FWD_DEFINED__
__IQueryParser_FWD_DEFINED__ equ 1
endif
ifndef __IConditionFactory_FWD_DEFINED__
__IConditionFactory_FWD_DEFINED__ equ 1
endif
ifndef __IQuerySolution_FWD_DEFINED__
__IQuerySolution_FWD_DEFINED__ equ 1
endif
ifndef __IConditionFactory2_FWD_DEFINED__
__IConditionFactory2_FWD_DEFINED__ equ 1
endif
ifndef __IConditionGenerator_FWD_DEFINED__
__IConditionGenerator_FWD_DEFINED__ equ 1
endif
ifndef __IInterval_FWD_DEFINED__
__IInterval_FWD_DEFINED__ equ 1
endif
ifndef __IMetaData_FWD_DEFINED__
__IMetaData_FWD_DEFINED__ equ 1
endif
ifndef __IEntity_FWD_DEFINED__
__IEntity_FWD_DEFINED__ equ 1
endif
ifndef __IRelationship_FWD_DEFINED__
__IRelationship_FWD_DEFINED__ equ 1
endif
ifndef __INamedEntity_FWD_DEFINED__
__INamedEntity_FWD_DEFINED__ equ 1
endif
ifndef __ISchemaProvider_FWD_DEFINED__
__ISchemaProvider_FWD_DEFINED__ equ 1
endif
ifndef __ITokenCollection_FWD_DEFINED__
__ITokenCollection_FWD_DEFINED__ equ 1
endif
ifndef __INamedEntityCollector_FWD_DEFINED__
__INamedEntityCollector_FWD_DEFINED__ equ 1
endif
ifndef __ISchemaLocalizerSupport_FWD_DEFINED__
__ISchemaLocalizerSupport_FWD_DEFINED__ equ 1
endif
ifndef __IQueryParserManager_FWD_DEFINED__
__IQueryParserManager_FWD_DEFINED__ equ 1
endif
ifndef __QueryParser_FWD_DEFINED__
__QueryParser_FWD_DEFINED__ equ 1
endif
ifndef __NegationCondition_FWD_DEFINED__
__NegationCondition_FWD_DEFINED__ equ 1
endif
ifndef __CompoundCondition_FWD_DEFINED__
__CompoundCondition_FWD_DEFINED__ equ 1
endif
ifndef __LeafCondition_FWD_DEFINED__
__LeafCondition_FWD_DEFINED__ equ 1
endif
ifndef __ConditionFactory_FWD_DEFINED__
__ConditionFactory_FWD_DEFINED__ equ 1
endif
ifndef __Interval_FWD_DEFINED__
__Interval_FWD_DEFINED__ equ 1
endif
ifndef __QueryParserManager_FWD_DEFINED__
__QueryParserManager_FWD_DEFINED__ equ 1
endif

include StructuredQueryCondition.inc
include ObjectArray.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include propkeydef.inc

.enum STRUCTURED_QUERY_SYNTAX {
    SQS_NO_SYNTAX	= 0,
    SQS_ADVANCED_QUERY_SYNTAX	= ( SQS_NO_SYNTAX + 1 ) ,
    SQS_NATURAL_QUERY_SYNTAX	= ( SQS_ADVANCED_QUERY_SYNTAX + 1 )
    }

.enum STRUCTURED_QUERY_SINGLE_OPTION {
    SQSO_SCHEMA = 0,
    SQSO_LOCALE_WORD_BREAKING	= ( SQSO_SCHEMA + 1 ) ,
    SQSO_WORD_BREAKER	= ( SQSO_LOCALE_WORD_BREAKING + 1 ) ,
    SQSO_NATURAL_SYNTAX = ( SQSO_WORD_BREAKER + 1 ) ,
    SQSO_AUTOMATIC_WILDCARD	= ( SQSO_NATURAL_SYNTAX + 1 ) ,
    SQSO_TRACE_LEVEL	= ( SQSO_AUTOMATIC_WILDCARD + 1 ) ,
    SQSO_LANGUAGE_KEYWORDS	= ( SQSO_TRACE_LEVEL + 1 ) ,
    SQSO_SYNTAX = ( SQSO_LANGUAGE_KEYWORDS + 1 ) ,
    SQSO_TIME_ZONE	= ( SQSO_SYNTAX + 1 ) ,
    SQSO_IMPLICIT_CONNECTOR	= ( SQSO_TIME_ZONE + 1 ) ,
    SQSO_CONNECTOR_CASE = ( SQSO_IMPLICIT_CONNECTOR + 1 )
    }

.enum STRUCTURED_QUERY_MULTIOPTION {
    SQMO_VIRTUAL_PROPERTY	= 0,
    SQMO_DEFAULT_PROPERTY	= ( SQMO_VIRTUAL_PROPERTY + 1 ) ,
    SQMO_GENERATOR_FOR_TYPE	= ( SQMO_DEFAULT_PROPERTY + 1 ) ,
    SQMO_MAP_PROPERTY	= ( SQMO_GENERATOR_FOR_TYPE + 1 )
    }

.enum STRUCTURED_QUERY_PARSE_ERROR {
    SQPE_NONE	= 0,
    SQPE_EXTRA_OPENING_PARENTHESIS	= ( SQPE_NONE + 1 ) ,
    SQPE_EXTRA_CLOSING_PARENTHESIS	= ( SQPE_EXTRA_OPENING_PARENTHESIS + 1 ) ,
    SQPE_IGNORED_MODIFIER	= ( SQPE_EXTRA_CLOSING_PARENTHESIS + 1 ) ,
    SQPE_IGNORED_CONNECTOR	= ( SQPE_IGNORED_MODIFIER + 1 ) ,
    SQPE_IGNORED_KEYWORD	= ( SQPE_IGNORED_CONNECTOR + 1 ) ,
    SQPE_UNHANDLED	= ( SQPE_IGNORED_KEYWORD + 1 )
    }

.enum STRUCTURED_QUERY_RESOLVE_OPTION {
    SQRO_DEFAULT	= 0,
    SQRO_DONT_RESOLVE_DATETIME	= 0x1,
    SQRO_ALWAYS_ONE_INTERVAL	= 0x2,
    SQRO_DONT_SIMPLIFY_CONDITION_TREES	= 0x4,
    SQRO_DONT_MAP_RELATIONS	= 0x8,
    SQRO_DONT_RESOLVE_RANGES	= 0x10,
    SQRO_DONT_REMOVE_UNRESTRICTED_KEYWORDS	= 0x20,
    SQRO_DONT_SPLIT_WORDS	= 0x40,
    SQRO_IGNORE_PHRASE_ORDER	= 0x80,
    SQRO_ADD_VALUE_TYPE_FOR_PLAIN_VALUES	= 0x100,
    SQRO_ADD_ROBUST_ITEM_NAME	= 0x200
    }

.enum CASE_REQUIREMENT {
    CASE_REQUIREMENT_ANY	= 0,
    CASE_REQUIREMENT_UPPER_IF_AQS	= ( CASE_REQUIREMENT_ANY + 1 )
    }

.enum INTERVAL_LIMIT_KIND {
    ILK_EXPLICIT_INCLUDED	= 0,
    ILK_EXPLICIT_EXCLUDED	= ( ILK_EXPLICIT_INCLUDED + 1 ) ,
    ILK_NEGATIVE_INFINITY	= ( ILK_EXPLICIT_EXCLUDED + 1 ) ,
    ILK_POSITIVE_INFINITY	= ( ILK_NEGATIVE_INFINITY + 1 )
    }

.enum QUERY_PARSER_MANAGER_OPTION {
    QPMO_SCHEMA_BINARY_NAME	= 0,
    QPMO_PRELOCALIZED_SCHEMA_BINARY_PATH	= ( QPMO_SCHEMA_BINARY_NAME + 1 ) ,
    QPMO_UNLOCALIZED_SCHEMA_BINARY_PATH = ( QPMO_PRELOCALIZED_SCHEMA_BINARY_PATH + 1 ) ,
    QPMO_LOCALIZED_SCHEMA_BINARY_PATH	= ( QPMO_UNLOCALIZED_SCHEMA_BINARY_PATH + 1 ) ,
    QPMO_APPEND_LCID_TO_LOCALIZED_PATH	= ( QPMO_LOCALIZED_SCHEMA_BINARY_PATH + 1 ) ,
    QPMO_LOCALIZER_SUPPORT	= ( QPMO_APPEND_LCID_TO_LOCALIZED_PATH + 1 )
    }

ifndef __IQueryParser_INTERFACE_DEFINED__
__IQueryParser_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IQueryParser, "2EBDEE67-3505-43f8-9946-EA44ABC8E5B0")

.comdef IQueryParser : public IUnknown

    Parse		proc :LPCWSTR, :ptr, :ptr
    SetOption		proc :STRUCTURED_QUERY_SINGLE_OPTION, :ptr
    GetOption		proc :STRUCTURED_QUERY_SINGLE_OPTION, :ptr
    SetMultiOption	proc :STRUCTURED_QUERY_MULTIOPTION, :LPCWSTR, :ptr
    GetSchemaProvider	proc :ptr
    RestateToString	proc :ptr, :BOOL, :ptr
    ParsePropertyValue	proc :LPCWSTR, :LPCWSTR, :ptr
    RestatePropertyValueToString proc :ptr, :BOOL, :ptr, :ptr
    .ends

endif

ifndef __IConditionFactory_INTERFACE_DEFINED__
__IConditionFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IConditionFactory, "A5EFE073-B16F-474f-9F3E-9F8B497A3E08")

.comdef IConditionFactory : public IUnknown

    MakeNot		proc :ptr, :BOOL, :ptr
    MakeAndOr		proc :CONDITION_TYPE, :ptr, :BOOL, :ptr
    MakeLeaf		proc :LPCWSTR, :CONDITION_OPERATION, :LPCWSTR, :ptr, :ptr, :ptr, :ptr, :BOOL, :ptr
    Resolve		proc :ptr, :STRUCTURED_QUERY_RESOLVE_OPTION, :ptr, :ptr
    .ends

endif

ifndef __IQuerySolution_INTERFACE_DEFINED__
__IQuerySolution_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IQuerySolution, "D6EBC66B-8921-4193-AFDD-A1789FB7FF57")

.comdef IQuerySolution : public IConditionFactory

    GetQuery		proc :ptr, :ptr
    GetErrors		proc :REFIID, :ptr
    GetLexicalData	proc :ptr, :ptr, :ptr, :ptr
    .ends

endif

.enum CONDITION_CREATION_OPTIONS {
    CONDITION_CREATION_DEFAULT	= 0,
    CONDITION_CREATION_NONE	= 0,
    CONDITION_CREATION_SIMPLIFY = 0x1,
    CONDITION_CREATION_VECTOR_AND	= 0x2,
    CONDITION_CREATION_VECTOR_OR	= 0x4,
    CONDITION_CREATION_VECTOR_LEAF	= 0x8,
    CONDITION_CREATION_USE_CONTENT_LOCALE	= 0x10
    }


ifndef __IConditionFactory2_INTERFACE_DEFINED__
__IConditionFactory2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IConditionFactory2, "71D222E1-432F-429e-8C13-B6DAFDE5077A")

.comdef IConditionFactory2 : public IConditionFactory

    CreateTrueFalse	proc :BOOL, :CONDITION_CREATION_OPTIONS, :REFIID, :ptr
    CreateNegation	proc :ptr, :CONDITION_CREATION_OPTIONS, :REFIID, :ptr
    CreateCompoundFromObjectArray proc :CONDITION_TYPE, :ptr, :CONDITION_CREATION_OPTIONS, :REFIID, :ptr
    CreateCompoundFromArray proc :CONDITION_TYPE, :ptr, :ULONG, :CONDITION_CREATION_OPTIONS, :REFIID, :ptr
    CreateStringLeaf	proc :REFPROPERTYKEY, :CONDITION_OPERATION, :LPCWSTR, :LPCWSTR, :CONDITION_CREATION_OPTIONS, :REFIID, :ptr
    CreateIntegerLeaf	proc :REFPROPERTYKEY, :CONDITION_OPERATION, :INT32, :CONDITION_CREATION_OPTIONS, :REFIID, :ptr
    CreateBooleanLeaf	proc :REFPROPERTYKEY, :CONDITION_OPERATION, :BOOL, :CONDITION_CREATION_OPTIONS, :REFIID, :ptr
    CreateLeaf		proc :REFPROPERTYKEY, :CONDITION_OPERATION, :REFPROPVARIANT, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :ptr, :CONDITION_CREATION_OPTIONS, :REFIID, :ptr
    ResolveCondition	proc :ptr, :STRUCTURED_QUERY_RESOLVE_OPTION, :ptr, :REFIID, :ptr
    .ends

endif

ifndef __IConditionGenerator_INTERFACE_DEFINED__
__IConditionGenerator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IConditionGenerator, "92D2CC58-4386-45a3-B98C-7E0CE64A4117")

.comdef IConditionGenerator : public IUnknown

    Initialize		proc :ptr
    RecognizeNamedEntities proc :LPCWSTR, :LCID, :ptr, :ptr
    GenerateForLeaf	proc :ptr, :LPCWSTR, :CONDITION_OPERATION, :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :ptr, :BOOL, :ptr, :ptr
    DefaultPhrase	proc :LPCWSTR, :ptr, :BOOL, :ptr
    .ends

endif

ifndef __IInterval_INTERFACE_DEFINED__
__IInterval_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInterval, "6BF0A714-3C18-430b-8B5D-83B1C234D3DB")

.comdef IInterval : public IUnknown

    GetLimits		proc :ptr, :ptr, :ptr, :ptr
    .ends

endif

ifndef __IMetaData_INTERFACE_DEFINED__
__IMetaData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMetaData, "780102B0-C43B-4876-BC7B-5E9BA5C88794")

.comdef IMetaData : public IUnknown

    GetData		proc :ptr, :ptr
    .ends

endif

ifndef __IEntity_INTERFACE_DEFINED__
__IEntity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEntity, "24264891-E80B-4fd3-B7CE-4FF2FAE8931F")

.comdef IEntity : public IUnknown

    Name		proc :ptr
    Base		proc :ptr
    Relationships	proc :REFIID, :ptr
    GetRelationship	proc :LPCWSTR, :ptr
    MetaData		proc :REFIID, :ptr
    NamedEntities	proc :REFIID, :ptr
    GetNamedEntity	proc :LPCWSTR, :ptr
    DefaultPhrase	proc :ptr
    .ends

endif

ifndef __IRelationship_INTERFACE_DEFINED__
__IRelationship_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRelationship, "2769280B-5108-498c-9C7F-A51239B63147")

.comdef IRelationship : public IUnknown

    Name		proc :ptr
    IsReal		proc :ptr
    Destination		proc :ptr
    MetaData		proc :REFIID, :ptr
    DefaultPhrase	proc :ptr
    .ends

endif

ifndef __INamedEntity_INTERFACE_DEFINED__
__INamedEntity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INamedEntity, "ABDBD0B1-7D54-49fb-AB5C-BFF4130004CD")

.comdef INamedEntity : public IUnknown

    GetValue		proc :ptr
    DefaultPhrase	proc :ptr
    .ends

endif

ifndef __ISchemaProvider_INTERFACE_DEFINED__
__ISchemaProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaProvider, "8CF89BCB-394C-49b2-AE28-A59DD4ED7F68")

.comdef ISchemaProvider : public IUnknown

    Entities		proc :REFIID, :ptr
    RootEntity		proc :ptr
    GetEntity		proc :LPCWSTR, :ptr
    MetaData		proc :REFIID, :ptr
    Localize		proc :LCID, :ptr
    SaveBinary		proc :LPCWSTR
    LookupAuthoredNamedEntity proc :ptr, :LPCWSTR, :ptr, :ULONG, :ptr, :ptr
    .ends

endif

ifndef __ITokenCollection_INTERFACE_DEFINED__
__ITokenCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITokenCollection, "22D8B4F2-F577-4adb-A335-C2AE88416FAB")

.comdef ITokenCollection : public IUnknown

    NumberOfTokens	proc :ptr
    GetToken		proc :ULONG, :ptr, :ptr, :ptr
    .ends

endif

.enum NAMED_ENTITY_CERTAINTY {
    NEC_LOW	= 0,
    NEC_MEDIUM	= ( NEC_LOW + 1 ) ,
    NEC_HIGH	= ( NEC_MEDIUM + 1 )
    }

ifndef __INamedEntityCollector_INTERFACE_DEFINED__
__INamedEntityCollector_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INamedEntityCollector, "AF2440F6-8AFC-47d0-9A7F-396A0ACFB43D")

.comdef INamedEntityCollector : public IUnknown

    _Add		proc :ULONG, :ULONG, :ULONG, :ULONG, :ptr, :LPCWSTR, :NAMED_ENTITY_CERTAINTY
    .ends

endif

ifndef __ISchemaLocalizerSupport_INTERFACE_DEFINED__
__ISchemaLocalizerSupport_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaLocalizerSupport, "CA3FDCA2-BFBE-4eed-90D7-0CAEF0A1BDA1")

.comdef ISchemaLocalizerSupport : public IUnknown

    Localize		proc :LPCWSTR, :ptr
    .ends

endif

ifndef __IQueryParserManager_INTERFACE_DEFINED__
__IQueryParserManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IQueryParserManager, "A879E3C4-AF77-44fb-8F37-EBD1487CF920")

.comdef IQueryParserManager : public IUnknown

    CreateLoadedParser	proc :LPCWSTR, :LANGID, :REFIID, :ptr
    InitializeOptions	proc :BOOL, :BOOL, :ptr
    SetOption		proc :QUERY_PARSER_MANAGER_OPTION, :ptr
    .ends

endif

HITRANGE		STRUC
iPosition		ULONG ?
cLength			ULONG ?
HITRANGE		ENDS

ifndef __StructuredQuery1_LIBRARY_DEFINED__
__StructuredQuery1_LIBRARY_DEFINED__ equ 1

externdef LIBID_StructuredQuery1:IID
DEFINE_GUIDS(CLSID_QueryParser, "B72F8FD8-0FAB-4dd9-BDBF-245A6CE1485B")
DEFINE_GUIDS(CLSID_NegationCondition, "8DE9C74C-605A-4acd-BEE3-2B222AA2D23D")
DEFINE_GUIDS(CLSID_CompoundCondition, "116F8D13-101E-4fa5-84D4-FF8279381935")
DEFINE_GUIDS(CLSID_LeafCondition, "52F15C89-5A17-48e1-BBCD-46A3F89C7CC2")
DEFINE_GUIDS(CLSID_ConditionFactory, "E03E85B0-7BE3-4000-BA98-6C13DE9FA486")
DEFINE_GUIDS(CLSID_Interval, "D957171F-4BF9-4de2-BCD5-C70A7CA55836")
DEFINE_GUIDS(CLSID_QueryParserManager, "5088B39A-29B4-4d9d-8245-4EE289222F66")

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

BSTR_UserSize		proto WINAPI :ptr DWORD, :DWORD, :ptr BSTR
BSTR_UserMarshal	proto WINAPI :ptr DWORD, :ptr SBYTE, :ptr BSTR
BSTR_UserUnmarshal	proto WINAPI :ptr DWORD, :ptr SBYTE, :ptr BSTR
BSTR_UserFree		proto WINAPI :ptr DWORD, :ptr BSTR
LPSAFEARRAY_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr LPSAFEARRAY
LPSAFEARRAY_UserMarshal proto WINAPI :ptr DWORD, :ptr SBYTE, :ptr LPSAFEARRAY
LPSAFEARRAY_UserUnmarshal proto WINAPI :ptr DWORD, :ptr SBYTE, :ptr LPSAFEARRAY
LPSAFEARRAY_UserFree	proto WINAPI :ptr DWORD, :ptr LPSAFEARRAY

endif
.pragma list(pop)
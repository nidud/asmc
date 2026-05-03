ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __structuredquerycondition_h__
define __structuredquerycondition_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include propidl.inc

.enum CONDITION_TYPE {
    CT_AND_CONDITION,
    CT_OR_CONDITION,
    CT_NOT_CONDITION,
    CT_LEAF_CONDITION
}

.enum CONDITION_OPERATION {
    COP_IMPLICIT,
    COP_EQUAL,
    COP_NOTEQUAL,
    COP_LESSTHAN,
    COP_GREATERTHAN,
    COP_LESSTHANOREQUAL,
    COP_GREATERTHANOREQUAL,
    COP_VALUE_STARTSWITH,
    COP_VALUE_ENDSWITH,
    COP_VALUE_CONTAINS,
    COP_VALUE_NOTCONTAINS,
    COP_DOSWILDCARDS,
    COP_WORD_EQUAL,
    COP_WORD_STARTSWITH,
    COP_APPLICATION_SPECIFIC
}

ifndef __IRichChunk_INTERFACE_DEFINED__
define __IRichChunk_INTERFACE_DEFINED__

externdef IID_IRichChunk:IID

.comdef IRichChunk : public IUnknown

    GetData		proc :ptr, :ptr, :ptr, :ptr
   .ends
endif

ifndef __ICondition_INTERFACE_DEFINED__
define __ICondition_INTERFACE_DEFINED__

externdef IID_ICondition:IID

.comdef ICondition : public IPersistStream

    GetConditionType	proc :ptr
    GetSubConditions	proc :REFIID, :ptr
    GetComparisonInfo	proc :ptr, :ptr, :ptr
    GetValueType	proc :ptr
    GetValueNormalization proc :ptr
    GetInputTerms	proc :ptr, :ptr, :ptr
    Clone		proc :ptr
   .ends
endif

ifndef __ICondition2_INTERFACE_DEFINED__
define __ICondition2_INTERFACE_DEFINED__

externdef IID_ICondition2:IID

.comdef ICondition2 : public ICondition

    GetLocale		proc :ptr
    GetLeafConditionInfo proc :ptr, :ptr, :ptr
   .ends
endif

endif

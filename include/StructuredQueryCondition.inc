ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
 .err <this stub requires an updated version of rpcndr>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __structuredquerycondition_h__
__structuredquerycondition_h__ equ <>

ifndef __IRichChunk_FWD_DEFINED__
__IRichChunk_FWD_DEFINED__ equ 1
endif
ifndef __ICondition_FWD_DEFINED__
__ICondition_FWD_DEFINED__ equ 1
endif
ifndef __ICondition2_FWD_DEFINED__
__ICondition2_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc
include propidl.inc

CONDITION_TYPE		typedef SDWORD
CT_AND_CONDITION	equ 0
CT_OR_CONDITION		equ ( CT_AND_CONDITION + 1 )
CT_NOT_CONDITION	equ ( CT_OR_CONDITION + 1 )
CT_LEAF_CONDITION	equ ( CT_NOT_CONDITION + 1 )

CONDITION_OPERATION	typedef SDWORD
COP_IMPLICIT		equ 0
COP_EQUAL		equ ( COP_IMPLICIT + 1 )
COP_NOTEQUAL		equ ( COP_EQUAL + 1 )
COP_LESSTHAN		equ ( COP_NOTEQUAL + 1 )
COP_GREATERTHAN		equ ( COP_LESSTHAN + 1 )
COP_LESSTHANOREQUAL	equ ( COP_GREATERTHAN + 1 )
COP_GREATERTHANOREQUAL	equ ( COP_LESSTHANOREQUAL + 1 )
COP_VALUE_STARTSWITH	equ ( COP_GREATERTHANOREQUAL + 1 )
COP_VALUE_ENDSWITH	equ ( COP_VALUE_STARTSWITH + 1 )
COP_VALUE_CONTAINS	equ ( COP_VALUE_ENDSWITH + 1 )
COP_VALUE_NOTCONTAINS	equ ( COP_VALUE_CONTAINS + 1 )
COP_DOSWILDCARDS	equ ( COP_VALUE_NOTCONTAINS + 1 )
COP_WORD_EQUAL		equ ( COP_DOSWILDCARDS + 1 )
COP_WORD_STARTSWITH	equ ( COP_WORD_EQUAL + 1 )
COP_APPLICATION_SPECIFIC equ ( COP_WORD_STARTSWITH + 1 )

ifndef __IRichChunk_INTERFACE_DEFINED__
__IRichChunk_INTERFACE_DEFINED__ equ 1

externdef		IID_IRichChunk:IID
.comdef IRichChunk
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetData		proc :ptr, :ptr, :ptr, :ptr
    .ends

endif

ifndef __ICondition_INTERFACE_DEFINED__
__ICondition_INTERFACE_DEFINED__ equ 1

externdef		IID_ICondition:IID
.comdef ICondition
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetClassID		proc :ptr
    IsDirty		proc
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    GetSizeMax		proc :ptr
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
__ICondition2_INTERFACE_DEFINED__ equ 1

externdef		IID_ICondition2:IID
.comdef ICondition2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetClassID		proc :ptr
    IsDirty		proc
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    GetSizeMax		proc :ptr
    GetConditionType	proc :ptr
    GetSubConditions	proc :REFIID, :ptr
    GetComparisonInfo	proc :ptr, :ptr, :ptr
    GetValueType	proc :ptr
    GetValueNormalization proc :ptr
    GetInputTerms	proc :ptr, :ptr, :ptr
    Clone		proc :ptr
    GetLocale		proc :ptr
    GetLeafConditionInfo proc :ptr, :ptr, :ptr
    .ends

endif

;; Additional Prototypes for ALL interfaces

;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR
;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR
;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR
;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR
;DWORD
LPSAFEARRAY_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY
;LPSTR
LPSAFEARRAY_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY
;LPSTR
LPSAFEARRAY_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY
;void
LPSAFEARRAY_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY
endif

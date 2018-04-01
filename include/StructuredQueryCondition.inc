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
.xlist

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
.xlist

tagCONDITION_TYPE	typedef SDWORD
CT_AND_CONDITION	equ 0
CT_OR_CONDITION		equ ( CT_AND_CONDITION + 1 )
CT_NOT_CONDITION	equ ( CT_OR_CONDITION + 1 )
CT_LEAF_CONDITION	equ ( CT_NOT_CONDITION + 1 )

tagCONDITION_OPERATION	typedef SDWORD
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

externdef		__MIDL_itf_structuredquerycondition_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_structuredquerycondition_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IRichChunk_INTERFACE_DEFINED__
__IRichChunk_INTERFACE_DEFINED__ equ 1

externdef		IID_IRichChunk:IID
.comdef IRichChunk
    QueryInterface      proc :REFIID, :ptr
    AddRef              proc
    Release             proc
    GetData             proc :ptr, :ptr, :ptr, :ptr
    .ends

;HRESULT
IRichChunk_RemoteGetData_Proxy proto WINAPI \
		 _This: ptr IRichChunk,
	     pFirstPos: ptr ULONG,
	       pLength: ptr ULONG,
		  ppsz: ptr LPWSTR,
		pValue: ptr PROPVARIANT
;void
IRichChunk_RemoteGetData_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


endif	;; __IRichChunk_INTERFACE_DEFINED__

ifndef __ICondition_INTERFACE_DEFINED__
__ICondition_INTERFACE_DEFINED__ equ 1

externdef		IID_ICondition:IID
.comdef ICondition
    QueryInterface      proc :REFIID, :ptr
    AddRef              proc
    Release             proc
    GetClassID          proc :ptr
    IsDirty             proc
    Load                proc :ptr
    Save                proc :ptr, :BOOL
    GetSizeMax          proc :ptr
    GetConditionType    proc :ptr
    GetSubConditions    proc :REFIID, :ptr
    GetComparisonInfo   proc :ptr, :ptr, :ptr
    GetValueType        proc :ptr
    GetValueNormalization proc :ptr
    GetInputTerms       proc :ptr, :ptr, :ptr
    Clone               proc :ptr
    .ends

;HRESULT
ICondition_RemoteGetComparisonInfo_Proxy proto WINAPI \
		 _This: ptr ICondition,
      ppszPropertyName: ptr LPWSTR,
		  pcop: ptr CONDITION_OPERATION,
	      ppropvar: ptr PROPVARIANT

;void
ICondition_RemoteGetComparisonInfo_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
ICondition_RemoteGetInputTerms_Proxy proto WINAPI \
		 _This: ptr ICondition,
	ppPropertyTerm: ptr IRichChunk,
       ppOperationTerm: ptr IRichChunk,
	   ppValueTerm: ptr IRichChunk

;void
ICondition_RemoteGetInputTerms_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif	;; __ICondition_INTERFACE_DEFINED__

ifndef __ICondition2_INTERFACE_DEFINED__
__ICondition2_INTERFACE_DEFINED__ equ 1

externdef		IID_ICondition2:IID
.comdef ICondition2
    QueryInterface      proc :REFIID, :ptr
    AddRef              proc
    Release             proc
    GetClassID          proc :ptr
    IsDirty             proc
    Load                proc :ptr
    Save                proc :ptr, :BOOL
    GetSizeMax          proc :ptr
    GetConditionType    proc :ptr
    GetSubConditions    proc :REFIID, :ptr
    GetComparisonInfo   proc :ptr, :ptr, :ptr
    GetValueType        proc :ptr
    GetValueNormalization proc :ptr
    GetInputTerms       proc :ptr, :ptr, :ptr
    Clone               proc :ptr
    GetLocale           proc :ptr
    GetLeafConditionInfo proc :ptr, :ptr, :ptr
    .ends

;HRESULT
ICondition2_RemoteGetLeafConditionInfo_Proxy proto WINAPI \
		 _This: ptr ICondition2,
	      ppropkey: ptr PROPERTYKEY,
		  pcop: ptr CONDITION_OPERATION,
	      ppropvar: ptr PROPVARIANT

;void
ICondition2_RemoteGetLeafConditionInfo_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif	;; __ICondition2_INTERFACE_DEFINED__

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
;HRESULT
IRichChunk_GetData_Proxy proto WINAPI \
		 _This: ptr IRichChunk,
	     pFirstPos: ptr ULONG,
	       pLength: ptr ULONG,
		  ppsz: ptr LPWSTR,
		pValue: ptr PROPVARIANT
;HRESULT
IRichChunk_GetData_Stub proto WINAPI \
		 _This: ptr IRichChunk,
	     pFirstPos: ptr ULONG,
	       pLength: ptr ULONG,
		  ppsz: ptr LPWSTR,
		pValue: ptr PROPVARIANT
;HRESULT
ICondition_GetComparisonInfo_Proxy proto WINAPI \
		 _This: ptr ICondition,
      ppszPropertyName: ptr LPWSTR,
		  pcop: ptr CONDITION_OPERATION,
	      ppropvar: ptr PROPVARIANT
;HRESULT
ICondition_GetComparisonInfo_Stub proto WINAPI \
		 _This: ptr ICondition,
      ppszPropertyName: ptr LPWSTR,
		  pcop: ptr CONDITION_OPERATION,
	      ppropvar: ptr PROPVARIANT
;HRESULT
ICondition_GetInputTerms_Proxy proto WINAPI \
		 _This: ptr ICondition,
	ppPropertyTerm: ptr IRichChunk,
       ppOperationTerm: ptr IRichChunk,
	   ppValueTerm: ptr IRichChunk
;HRESULT
ICondition_GetInputTerms_Stub proto WINAPI \
		 _This: ptr ICondition,
	ppPropertyTerm: ptr IRichChunk,
       ppOperationTerm: ptr IRichChunk,
	   ppValueTerm: ptr IRichChunk
;HRESULT
ICondition2_GetLeafConditionInfo_Proxy proto WINAPI \
		 _This: ptr ICondition2,
	      ppropkey: ptr PROPERTYKEY,
		  pcop: ptr CONDITION_OPERATION,
	      ppropvar: ptr PROPVARIANT
;HRESULT
ICondition2_GetLeafConditionInfo_Stub proto WINAPI \
		 _This: ptr ICondition2,
	      ppropkey: ptr PROPERTYKEY,
		  pcop: ptr CONDITION_OPERATION,
	      ppropvar: ptr PROPVARIANT

.list
endif ; __structuredquerycondition_h__

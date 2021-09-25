ifndef __LIBC_INC
 include libc.inc
endif
ifndef __RPCNDR_H_VERSION__
define __RPCNDR_H_VERSION__ 500
endif
ifndef __RPCNDR_H__
define __RPCNDR_H__

ifdef __REQUIRED_RPCNDR_H_VERSION__
 if ( __RPCNDR_H_VERSION__ LT __REQUIRED_RPCNDR_H_VERSION__ )
  .err <incorrect rpcndr.inc version. Use the header that matches with the MIDL compiler.>
 endif
endif

include rpcnsip.inc

NDR_CHAR_REP_MASK	equ 0X0000000F
NDR_INT_REP_MASK	equ 0X000000F0
NDR_FLOAT_REP_MASK	equ 0X0000FF00
NDR_LITTLE_ENDIAN	equ 0X00000010
NDR_BIG_ENDIAN		equ 0X00000000
NDR_IEEE_FLOAT		equ 0X00000000
NDR_VAX_FLOAT		equ 0X00000100
NDR_ASCII_CHAR		equ 0X00000000
NDR_EBCDIC_CHAR		equ 0X00000001
NDR_LOCAL_DATA_REPRESENTATION equ 0X00000010
NDR_LOCAL_ENDIAN	equ NDR_LITTLE_ENDIAN

if (0x500 LE _WIN32_WINNT)
TARGET_IS_NT50_OR_LATER equ 1
else
TARGET_IS_NT50_OR_LATER equ 0
endif

if (defined(_WIN32_DCOM) OR 0x400 LE _WIN32_WINNT)
TARGET_IS_NT40_OR_LATER equ 1
else
TARGET_IS_NT40_OR_LATER equ 0
endif

if (0x400 LE WINVER)
TARGET_IS_NT351_OR_WIN95_OR_LATER equ 1
else
TARGET_IS_NT351_OR_WIN95_OR_LATER equ 0
endif

boolean			typedef BYTE

ifndef _HYPER_DEFINED
_HYPER_DEFINED		equ 1

if (_INTEGRAL_MAX_BITS GE 64) AND NOT defined(_M_IX86)
hyper			equ <QWORD>
MIDL_uhyper		equ <QWORD>
else
hyper			typedef REAL8
MIDL_uhyper		typedef REAL8
endif

endif

ifndef _WCHAR_T_DEFINED
wchar_t			typedef WORD
_WCHAR_T_DEFINED	equ 1
endif

ifndef _SIZE_T_DEFINED
ifdef _WIN64
size_t			typedef QWORD
else
size_t			typedef DWORD
endif
_SIZE_T_DEFINED		equ 1
endif

ifdef __RPC_WIN32__
if   (_MSC_VER GE 800) OR defined(_STDCALL_SUPPORTED)
__RPC_CALLEE		equ <stdcall>
else
__RPC_CALLEE		equ <>
endif
endif

ifndef __MIDL_USER_DEFINED
midl_user_allocate	equ <MID_user_allocate>
midl_user_free		equ <MID_user_free>
__MIDL_USER_DEFINED	equ 1
endif

;PVOID
MIDL_user_allocate proto WINAPI \
		      : size_t

;void
MIDL_user_free proto WINAPI \
		      : PVOID

ifdef __RPC_WIN16__
RPC_VAR_ENTRY		equ <export c>
else
RPC_VAR_ENTRY		equ <c>
endif


NDR_CCONTEXT		typedef PVOID

_NDR_SCONTEXT		STRUC
pad			PVOID 2 dup(?)
userContext		PVOID ?
_NDR_SCONTEXT		ENDS
NDR_SCONTEXT		typedef ptr _NDR_SCONTEXT

NDRSContextValue macro hContext
	.err <Macro not implemented>
	endm

cbNDRContext		equ 20

CALLBACK(NDR_RUNDOWN, context:PVOID)

SCONTEXT_QUEUE		STRUC
NumberOfObjects		dd ?
ArrayOfObjects		NDR_SCONTEXT ?
SCONTEXT_QUEUE		ENDS
PSCONTEXT_QUEUE		typedef ptr SCONTEXT_QUEUE

;RPC_BINDING_HANDLE
NDRCContextBinding proto WINAPI \
	      CContext: NDR_CCONTEXT

;void
NDRCContextMarshall proto WINAPI \
	      CContext: NDR_CCONTEXT,
		 pBuff: PVOID

;void
NDRCContextUnmarshall proto WINAPI \
	     pCContext: ptr NDR_CCONTEXT,
	      hBinding: RPC_BINDING_HANDLE,
		 pBuff: PVOID,
    DataRepresentation: DWORD

;void
NDRSContextMarshall proto WINAPI \
	      CContext: NDR_SCONTEXT,
		 pBuff: PVOID,
	 userRunDownIn: NDR_RUNDOWN

;NDR_SCONTEXT
NDRSContextUnmarshall proto WINAPI \
		 pBuff: PVOID,
    DataRepresentation: DWORD

;void
NDRSContextMarshallEx proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE,
	      CContext: NDR_SCONTEXT,
		 pBuff: PVOID,
	 userRunDownIn: NDR_RUNDOWN

;NDR_SCONTEXT
NDRSContextUnmarshallEx proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE,
		 pBuff: PVOID,
    DataRepresentation: DWORD

;void
RpcSsDestroyClientContext proto WINAPI \
	 ContextHandle: PVOID

;void
NDRcopy proto WINAPI \
	       pTarget: PVOID,
	       pSource: PVOID,
		  size: UINT

;size_t
MIDL_wchar_strlen proto WINAPI \
		     s: ptr wchar_t

;void
MIDL_wchar_strcpy proto WINAPI \
		     t: PVOID,
		     s: ptr wchar_t

;void
char_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
		Target: LPBYTE

;void
char_array_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: LPBYTE

;void
short_from_ndr proto WINAPI \
		source: PRPC_MESSAGE,
		target: LPWORD

;void
short_array_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: LPWORD

;void
short_from_ndr_temp proto WINAPI \
		source: LPBYTE,
		target: LPWORD,
		format: DWORD

;void
long_from_ndr proto WINAPI \
		source: PRPC_MESSAGE,
		target: LPDWORD

;void
long_array_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: LPDWORD

;void
long_from_ndr_temp proto WINAPI \
		source: LPBYTE,
		target: LPDWORD,
		format: DWORD

;void
enum_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
		Target: LPWORD

;void
float_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
		Target: PVOID

;void
float_array_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: PVOID

;void
double_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
		Target: PVOID

;void
double_array_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: PVOID

;void
hyper_from_ndr proto WINAPI \
		source: PRPC_MESSAGE,
		target: ptr hyper

;void
hyper_array_from_ndr proto WINAPI \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: ptr hyper

;void
hyper_from_ndr_temp proto WINAPI \
		source: LPBYTE,
		target: ptr hyper,
		format: DWORD

;void
data_from_ndr proto WINAPI \
		source: PRPC_MESSAGE,
		target: PVOID,
		format: LPSTR,
		MscPak: BYTE

;void
data_into_ndr proto WINAPI \
		source: PVOID,
		target: PRPC_MESSAGE,
		format: LPSTR,
		MscPak: BYTE

;void
tree_into_ndr proto WINAPI \
		source: PVOID,
		target: PRPC_MESSAGE,
		format: LPSTR,
		MscPak: BYTE

;void
data_size_ndr proto WINAPI \
		source: PVOID,
		target: PRPC_MESSAGE,
		format: LPSTR,
		MscPak: BYTE

;void
tree_size_ndr proto WINAPI \
		source: PVOID,
		target: PRPC_MESSAGE,
		format: LPSTR,
		MscPak: BYTE

;void
tree_peek_ndr proto WINAPI \
		source: PRPC_MESSAGE,
		buffer: LPBYTE,
		format: LPSTR,
		MscPak: BYTE

;PVOID
midl_allocate proto WINAPI \
		  size: size_t


error_status_t		typedef DWORD


NdrFieldOffset macro s,f
	exitm<s.f>
	endm
NdrFieldPad macro s,f,p,t
	exitm<(NdrFieldOffset(s,f) - NdrFieldOffset(s,p) - sizeof(t))>
	endm

NdrFcShort macro s
	exitm<(s AND 0xff), (s SHR 8)>
	endm
NdrFcLong macro s
	exitm<(s AND 0xff), ((s AND 0x0000ff00) SHR 8), ((s AND 0x00ff0000) SHR 16), (s SHR 24)>
	endm


RPC_BAD_STUB_DATA_EXCEPTION_FILTER equ <( (RpcExceptionCode() EQ STATUS_ACCESS_VIOLATION) OR (RpcExceptionCode() EQ STATUS_DATATYPE_MISAIGNMENT) OR (RpcExceptionCode() EQ RPC_X_BAD_STUB_DATA) )>


RPC_BUFPTR		typedef LPBYTE
RPC_LENGTH		typedef DWORD

;void
CALLBACK(EXPR_EVAL, :PVOID)
PFORMAT_STRING		typedef LPBYTE

ARRAY_INFO		STRUC
Dimension		LONG ?

BufferConformanceMark	LPDWORD ?
BufferVarianceMark	LPDWORD ?

MaxCountArray		LPDWORD ?
OffsetArray		LPDWORD ?
ActualCountArray	LPDWORD ?
ARRAY_INFO		ENDS
PARRAY_INFO		typedef ptr ARRAY_INFO


PNDR_PIPE_DESC		typedef ptr NDR_PIPE_DESC
PNDR_PIPE_MESSAGE	typedef ptr NDR_PIPE_MESSAGE
PNDR_ASYNC_MESSAGE	typedef ptr NDR_ASYNC_MESSAGE


MIDL_STUB_MESSAGE	STRUC
RpcMsg			PRPC_MESSAGE ?
Buffer			LPBYTE ?
BufferStart		LPBYTE ?
BufferEnd		LPBYTE ?
BufferMark		LPBYTE ?
BufferLength		dd ?
MemorySize		dd ?
Memory			LPBYTE ?
IsClient		SINT ?
ReuseBuffer		SINT ?
AllocAllNodesMemory	LPBYTE ?
AllocAllNodesMemoryEnd	LPBYTE ?
IgnoreEmbeddedPointers	SINT ?
PointerBufferMark	LPBYTE ?
fBufferValid		db ?
Unused			db ?
MaxCount		dd ?
_Offset			dd ?
ActualCount		dd ?
pfnAllocate		PVOID ? ; (*pfnAllocate)(size_t)
pfnFree			PVOID ? ; (*pfnFree)(PVOID)
StackTop		LPBYTE ?
pPresentedType		LPBYTE ?
pTransmitType		LPBYTE ?
SavedHandle		handle_t ?
StubDesc		PVOID ? ; _MIDL_STUB_DES*
FullPtrXlatTables	PVOID ? ; _FULL_PTR_XLAT_TABLES*
FullPtrRefId		dd ?
fCheckBounds		SINT ?
if 0
fInDontFree	  :1	SINT ?
fDontCallFreeInst :1	SINT ?
fInOnlyParam	  :1	SINT ?
fHasReturn	  :1	SINT ?
else
R0			SINT ?
endif
dwDestContext		dd ?
pvDestContext		PVOID ?

SavedContextHandles	NDR_SCONTEXT ?
ParamNumber		LONG ?
pRpcChannelBuffer	PVOID ?; IRpcChannelBuffer* ?
pArrayInfo		PARRAY_INFO ?
SizePtrCountArray	LPDWORD ?
SizePtrOffsetArray	LPDWORD ?
SizePtrLengthArray	LPDWORD ?
pArgQueue		PVOID ?
dwStubPhase		dd ?
pPipeDesc		PNDR_PIPE_DESC ?
pAsyncMsg		PNDR_ASYNC_MESSAGE ?
Reserved		dd 3 dup(?)
MIDL_STUB_MESSAGE	ENDS
PMIDL_STUB_MESSAGE	typedef ptr MIDL_STUB_MESSAGE

;include <poppack.h>

;PVOID
CALLBACK(GENERIC_BINDING_ROUTINE, :PVOID)
;void
CALLBACK(GENERIC_UNBIND_ROUTINE, :PVOID, :LPBYTE)

GENERIC_BINDING_ROUTINE_PAIR STRUC
pfnBind			GENERIC_BINDING_ROUTINE ?
pfnUnbind		GENERIC_UNBIND_ROUTINE ?
GENERIC_BINDING_ROUTINE_PAIR ENDS
PGENERIC_BINDING_ROUTINE_PAIR typedef ptr GENERIC_BINDING_ROUTINE_PAIR

GENERIC_BINDING_INFO	STRUC
pObj			PVOID ?
Size			UINT ?
pfnBind			GENERIC_BINDING_ROUTINE ?
pfnUnbind		GENERIC_UNBIND_ROUTINE ?
GENERIC_BINDING_INFO	ENDS
PGENERIC_BINDING_INFO	typedef ptr GENERIC_BINDING_INFO


if (defined(_MSC_VER)) AND NOT defined(MIDL_PASS)
NDR_SHAREABLE		equ <inline>
else
NDR_SHAREABLE		equ <static>
endif

;void
CALLBACK(XMIT_HELPER_ROUTINE, :PMIDL_STUB_MESSAGE)

XMIT_ROUTINE_QUINTUPLE	STRUC
pfnTranslateToXmit	XMIT_HELPER_ROUTINE ?
pfnTranslateFromXmit	XMIT_HELPER_ROUTINE ?
pfnFreeXmit		XMIT_HELPER_ROUTINE ?
pfnFreeInst		XMIT_HELPER_ROUTINE ?
XMIT_ROUTINE_QUINTUPLE	ENDS
PXMIT_ROUTINE_QUINTUPLE typedef ptr XMIT_ROUTINE_QUINTUPLE


;DWORD
CALLBACK(USER_MARSHAL_SIZING_ROUTINE, :LPDWORD, :DWORD, :PVOID)
;LPBYTE
CALLBACK(USER_MARSHAL_MARSHALLING_ROUTINE, :LPDWORD, :LPBYTE, :PVOID)
;LPBYTE
CALLBACK(USER_MARSHAL_UNMARSHALLING_ROUTINE, :LPDWORD, :LPBYTE, :PVOID)
;void
;LPDWORD
CALLBACK(USER_MARSHAL_FREEING_ROUTINE, :LPDWORD, :PVOID)

USER_MARSHAL_ROUTINE_QUADRUPLE STRUC
pfnBufferSize		USER_MARSHAL_SIZING_ROUTINE ?
pfnMarshall		USER_MARSHAL_MARSHALLING_ROUTINE ?
pfnUnmarshall		USER_MARSHAL_UNMARSHALLING_ROUTINE ?
pfnFree			USER_MARSHAL_FREEING_ROUTINE ?
USER_MARSHAL_ROUTINE_QUADRUPLE ENDS

USER_MARSHAL_CB		STRUC
Flags			dd ?
pStubMsg		PMIDL_STUB_MESSAGE ?
pReserve		PFORMAT_STRING ?
USER_MARSHAL_CB		ENDS


USER_CALL_CTXT_MASK macro f
	exitm<((f) AND 0x00ff)>
	endm
USER_CALL_AUX_MASK macro f
	exitm<((f) AND 0xff00)>
	endm
GET_USER_DATA_REP macro f
	exitm<((f) SHR 16)>
	endm

USER_CALL_IS_ASYNC	equ 0x0100


MALLOC_FREE_STRUCT	STRUC
pfnAllocate		PVOID ? ; (*pfnAllocate)(size_t)
pfnFree			PVOID ? ; (*pfnFree)(PVOID)
MALLOC_FREE_STRUCT	ENDS

COMM_FAULT_OFFSETS	STRUC
CommOffset		dw ?
FaultOffset		dw ?
COMM_FAULT_OFFSETS	ENDS


MIDL_STUB_DESC		STRUC
RpcInterfaceInformation PVOID ?
pfnAllocate		PVOID ? ; (*pfnAllocate)(size_t)
pfnFree			PVOID ? ; (*pfnFree)(PVOID)
UNION IMPLICIT_HANDLE_INFO
 pAutoHandle		PVOID ? ; handle_t* ?
 pPrimitiveHandle	PVOID ? ; handle_t* ?
 pGenericBindingInfo	PGENERIC_BINDING_INFO ?
ENDS
apfnNdrRundownRoutines	NDR_RUNDOWN ?
aGenericBindingRoutinePairs PGENERIC_BINDING_ROUTINE_PAIR ?
apfnExprEval		PVOID ? ; EXPR_EVAL* ?
aXmitQuintuple		PXMIT_ROUTINE_QUINTUPLE ?
pFormatTypes		LPBYTE ?
fCheckBounds		SINT ?
Version			dd ?
pMallocFreeStruct	PVOID ? ; MALLOC_FREE_STRUCT* ?
MIDLVersion		LONG ?
CommFaultOffsets	PVOID ? ; COMM_FAULT_OFFSETS* ?
aUserMarshalQuadruple	PVOID ? ; USER_MARSHAL_ROUTINE_QUADRUPLE* ?
Reserved1		LONG ?
Reserved2		LONG ?
Reserved3		LONG ?
Reserved4		LONG ?
Reserved5		LONG ?
MIDL_STUB_DESC		ENDS
PMIDL_STUB_DESC		typedef ptr MIDL_STUB_DESC
PMIDL_XMIT_TYPE		typedef PVOID

MIDL_FORMAT_STRING	STRUC
Pad			dw ?
Format			db ?
MIDL_FORMAT_STRING	ENDS

;void
CALLBACK(STUB_THUNK, :PMIDL_STUB_MESSAGE)
SERVER_ROUTINE		typedef LONG
PSERVER_ROUTINE		typedef ptr SERVER_ROUTINE

MIDL_SERVER_INFO	STRUC
pStubDesc		PMIDL_STUB_DESC ?
DispatchTable		PSERVER_ROUTINE ?
ProcString		PFORMAT_STRING ?
FmtStringOffset		LPWORD ?
ThunkTable		STUB_THUNK ?
LocalFormatTypes	PFORMAT_STRING ?
LocalProcString		PFORMAT_STRING ?
LocalFmtStringOffset	LPWORD ?
MIDL_SERVER_INFO	ENDS
PMIDL_SERVER_INFO	typedef ptr MIDL_SERVER_INFO

MIDL_STUBLESS_PROXY_INFO STRUC
pStubDesc		PMIDL_STUB_DESC ?
ProcFormatString	PFORMAT_STRING ?
FormatStringOffset	LPWORD ?
LocalFormatTypes	PFORMAT_STRING ?
LocalProcString		PFORMAT_STRING ?
LocalFmtStringOffset	LPWORD ?
MIDL_STUBLESS_PROXY_INFO ENDS

PMIDL_STUBLESS_PROXY_INFO typedef ptr MIDL_STUBLESS_PROXY_INFO

CLIENT_CALL_RETURN	UNION
Pointer			PVOID ?
Simple			LONG ?
CLIENT_CALL_RETURN	ENDS


XLAT_SIDE		typedef sdword
XLAT_SERVER		equ 1
XLAT_CLIENT		equ 2

FULL_PTR_TO_REFID_ELEMENT STRUC
Next			PVOID ?; FULL_PTR_TO_REFID_ELEMENT *
Pointer			PVOID ?
RefId			dd ?
State			db ?
FULL_PTR_TO_REFID_ELEMENT ENDS
PFULL_PTR_TO_REFID_ELEMENT typedef ptr FULL_PTR_TO_REFID_ELEMENT

FULL_PTR_XLAT_TABLES	STRUC
STRUC RefIdToPointer
 XlatTable		PVOID ?
 StateTable		LPBYTE ?
 NumberOfEntries	dd ?
ENDS

STRUC PointerToRefId
 XlatTable		PFULL_PTR_TO_REFID_ELEMENT ?
 NumberOfBuckets	dd ?
 HashMask		dd ?
ENDS

NextRefId		dd ?

XlatSide		XLAT_SIDE ?
FULL_PTR_XLAT_TABLES	ENDS
PFULL_PTR_XLAT_TABLES	typedef ptr FULL_PTR_XLAT_TABLES



;void
NdrSimpleTypeMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	    FormatChar: BYTE

;LPBYTE
NdrPointerMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;LPBYTE
NdrSimpleStructMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantStructMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantVaryingStructMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrHardStructMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrComplexStructMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;LPBYTE
NdrFixedArrayMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantArrayMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantVaryingArrayMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrVaryingArrayMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrComplexArrayMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;LPBYTE
NdrNonConformantStringMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantStringMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;LPBYTE
NdrEncapsulatedUnionMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrNonEncapsulatedUnionMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;LPBYTE
NdrByteCountPointerMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;LPBYTE
NdrXmitOrRepAsMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;LPBYTE
NdrUserMarshalMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;LPBYTE
NdrInterfacePointerMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrClientContextMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	 ContextHandle: NDR_CCONTEXT,
		fCheck: SINT

;void
NdrServerContextMarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	 ContextHandle: NDR_SCONTEXT,
	RundownRoutine: NDR_RUNDOWN


;void
NdrSimpleTypeUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	    FormatChar: BYTE

;LPBYTE
NdrPointerUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;LPBYTE
NdrSimpleStructUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantStructUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantVaryingStructUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrHardStructUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrComplexStructUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;LPBYTE
NdrFixedArrayUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantArrayUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantVaryingArrayUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrVaryingArrayUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrComplexArrayUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;LPBYTE
NdrNonConformantStringUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantStringUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;LPBYTE
NdrEncapsulatedUnionUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrNonEncapsulatedUnionUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;LPBYTE
NdrByteCountPointerUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;LPBYTE
NdrXmitOrRepAsUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;LPBYTE
NdrUserMarshalUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;LPBYTE
NdrInterfacePointerUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE


;void
NdrClientContextUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	pContextHandle: ptr NDR_CCONTEXT,
	    BindHandle: RPC_BINDING_HANDLE

;NDR_SCONTEXT
NdrServerContextUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE


;void
NdrPointerBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrSimpleStructBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantStructBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantVaryingStructBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrHardStructBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrComplexStructBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrFixedArrayBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantArrayBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantVaryingArrayBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrVaryingArrayBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrComplexArrayBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrConformantStringBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrNonConformantStringBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrEncapsulatedUnionBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrNonEncapsulatedUnionBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrByteCountPointerBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrXmitOrRepAsBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrUserMarshalBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrInterfacePointerBufferSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrContextHandleSize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;DWORD
NdrPointerMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;DWORD
NdrSimpleStructMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrConformantStructMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrConformantVaryingStructMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrHardStructMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrComplexStructMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;DWORD
NdrFixedArrayMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrConformantArrayMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrConformantVaryingArrayMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrVaryingArrayMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrComplexArrayMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;DWORD
NdrConformantStringMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrNonConformantStringMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;DWORD
NdrEncapsulatedUnionMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrNonEncapsulatedUnionMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;DWORD
NdrXmitOrRepAsMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;DWORD
NdrUserMarshalMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;DWORD
NdrInterfacePointerMemorySize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;void
NdrPointerFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrSimpleStructFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantStructFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantVaryingStructFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrHardStructFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrComplexStructFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrFixedArrayFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantArrayFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantVaryingArrayFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrVaryingArrayFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrComplexArrayFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrEncapsulatedUnionFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrNonEncapsulatedUnionFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrByteCountPointerFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrXmitOrRepAsFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrUserMarshalFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrInterfacePointerFree proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING


;void
NdrConvert2 proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING,
	  NumberParams: LONG

;void
NdrConvert proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

USER_MARSHAL_FC_BYTE	equ 1
USER_MARSHAL_FC_CHAR	equ 2
USER_MARSHAL_FC_SMALL	equ 3
USER_MARSHAL_FC_USMALL	equ 4
USER_MARSHAL_FC_WCHAR	equ 5
USER_MARSHAL_FC_SHORT	equ 6
USER_MARSHAL_FC_USHORT	equ 7
USER_MARSHAL_FC_LONG	equ 8
USER_MARSHAL_FC_ULONG	equ 9
USER_MARSHAL_FC_FLOAT	equ 10
USER_MARSHAL_FC_HYPER	equ 11
USER_MARSHAL_FC_DOUBLE	equ 12

;LPBYTE
NdrUserMarshalSimpleTypeConvert proto WINAPI \
		pFlags: LPDWORD,
	       pBuffer: LPBYTE,
	    FormatChar: BYTE


;void
NdrClientInitializeNew proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
	       ProcNum: UINT

;LPBYTE
NdrServerInitializeNew proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC

;void
NdrServerInitializePartial proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
   RequestedBufferSize: DWORD

;void
NdrClientInitialize proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
	       ProcNum: UINT

;LPBYTE
NdrServerInitialize proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC

;LPBYTE
NdrServerInitializeUnmarshall proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
	       pRpcMsg: PRPC_MESSAGE

;void
NdrServerInitializeMarshall proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE

;LPBYTE
NdrGetBuffer proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	  BufferLength: DWORD,
		Handle: RPC_BINDING_HANDLE

;LPBYTE
NdrNsGetBuffer proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	  BufferLength: DWORD,
		Handle: RPC_BINDING_HANDLE

;LPBYTE
NdrGetPipeBuffer proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	  BufferLength: DWORD,
		Handle: RPC_BINDING_HANDLE

;void
NdrGetPartialBuffer proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE

;LPBYTE
NdrSendReceive proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	    pBufferEnd: LPBYTE

;LPBYTE
NdrNsSendReceive proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	    pBufferEnd: LPBYTE,
	   pAutoHandle: ptr RPC_BINDING_HANDLE

;void
NdrPipeSendReceive proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPipeDesc: PNDR_PIPE_DESC

;void
NdrFreeBuffer proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE

;RPC_STATUS
NdrGetDcomProtocolVersion proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      pVersion: ptr RPC_VERSION

;void
NdrPipesInitialize proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	    pParamDesc: PFORMAT_STRING,
	     pPipeDesc: PNDR_PIPE_DESC,
	      pPipeMsg: PNDR_PIPE_MESSAGE,
	     pStackTop: LPSTR,
	  NumberParams: DWORD

;void
NdrPipePull proto WINAPI \
		pState: LPSTR,
		   buf: PVOID,
		 esize: DWORD,
		ecount: LPDWORD

;void
NdrPipePush proto WINAPI \
		pState: LPSTR,
		   buf: PVOID,
		ecount: DWORD

;void
NdrIsAppDoneWithPipes proto WINAPI \
	     pPipeDesc: PNDR_PIPE_DESC

;void
NdrPipesDone proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE

;CLIENT_CALL_RETURN RPC_VAR_ENTRY
NdrClientCall2 proto WINAPI \
       pStubDescriptor: PMIDL_STUB_DESC,
	       pFormat: PFORMAT_STRING

;CLIENT_CALL_RETURN RPC_VAR_ENTRY
NdrClientCall proto WINAPI \
       pStubDescriptor: PMIDL_STUB_DESC,
	       pFormat: PFORMAT_STRING

;CLIENT_CALL_RETURN RPC_VAR_ENTRY
NdrAsyncClientCall proto WINAPI \
       pStubDescriptor: PMIDL_STUB_DESC,
	       pFormat: PFORMAT_STRING


STUB_UNMARSHAL		equ 0
STUB_CALL_SERVER	equ 1
STUB_MARSHAL		equ 2
STUB_CALL_SERVER_NO_HRESULT equ 3
STUB_PHASE		typedef sdword

PROXY_PHASE		typedef sdword
PROXY_CALCSIZE		equ 0
PROXY_GETBUFFER		equ 1
PROXY_MARSHAL		equ 2
PROXY_SENDRECEIVE	equ 3
PROXY_UNMARSHAL		equ 4

;IRpcStubBuffer;

;long
NdrAsyncStubCall proto WINAPI \
		 pThis: PVOID,;struct IRpcStubBuffer *
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	       pRpcMsg: PRPC_MESSAGE,
	  pdwStubPhase: LPDWORD

;void
NdrAsyncServerCall proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE

;long
NdrStubCall2 proto WINAPI \
		 pThis: PVOID,;struct IRpcStubBuffer *
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	       pRpcMsg: PRPC_MESSAGE,
	  pdwStubPhase: LPDWORD

;void
NdrServerCall2 proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE

;long
NdrStubCall proto WINAPI \
		 pThis: PVOID,;struct IRpcStubBuffer *
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	       pRpcMsg: PRPC_MESSAGE,
	  pdwStubPhase: LPDWORD

;void
NdrServerCall proto WINAPI \
	       pRpcMsg: PRPC_MESSAGE

;int
NdrServerUnmarshall proto WINAPI \
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
	       pFormat: PFORMAT_STRING,
	    pParamList: PVOID

;void
NdrServerMarshall proto WINAPI \
		 pThis: PVOID,;struct IRpcStubBuffer *
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING


;RPC_STATUS
NdrMapCommAndFaultStatus proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	   pCommStatus: LPDWORD,
	  pFaultStatus: LPDWORD,
		Status: RPC_STATUS


;int
NdrSH_UPDecision proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
	       pBuffer: RPC_BUFPTR

;int
NdrSH_TLUPDecision proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE

;int
NdrSH_TLUPDecisionBuffer proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE

;int
NdrSH_IfAlloc proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;int
NdrSH_IfAllocRef proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;int
NdrSH_IfAllocSet proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;RPC_BUFPTR
NdrSH_IfCopy proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;RPC_BUFPTR
NdrSH_IfAllocCopy proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;DWORD
NdrSH_Copy proto WINAPI \
	      pStubMsg: LPBYTE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;void
NdrSH_IfFree proto WINAPI \
	      pMessage: PMIDL_STUB_MESSAGE,
		  pPtr: LPBYTE


;RPC_BUFPTR
NdrSH_StringMarshall proto WINAPI \
	      pMessage: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
		 Count: DWORD,
		  Size: SINT

;RPC_BUFPTR
NdrSH_StringUnMarshall proto WINAPI \
	      pMessage: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
		  Size: SINT


RPC_SS_THREAD_HANDLE	typedef PVOID

;PVOID
CALLBACK(RPC_CLIENT_ALLOC,_Size: size_t)
;void
CALLBACK(RPC_CLIENT_FREE, :PVOID)


;PVOID
RpcSsAllocate proto WINAPI \
		  Size: size_t

;void
RpcSsDisableAllocate proto WINAPI

;void
RpcSsEnableAllocate proto WINAPI

;void
RpcSsFree proto WINAPI \
	    NodeToFree: PVOID

;RPC_SS_THREAD_HANDLE
RpcSsGetThreadHandle proto WINAPI

;void
RpcSsSetClientAllocFree proto WINAPI \
	   ClientAlloc: ptr RPC_CLIENT_ALLOC,
	    ClientFree: ptr RPC_CLIENT_FREE

;void
RpcSsSetThreadHandle proto WINAPI \
		    Id: RPC_SS_THREAD_HANDLE

;void
RpcSsSwapClientAllocFree proto WINAPI \
	   ClientAlloc: ptr RPC_CLIENT_ALLOC,
	    ClientFree: ptr RPC_CLIENT_FREE,
	OldClientAlloc: RPC_CLIENT_ALLOC,
	 OldClientFree: RPC_CLIENT_FREE


;PVOID
RpcSmAllocate proto WINAPI \
		  Size: size_t,
	       pStatus: ptr RPC_STATUS

;RPC_STATUS
RpcSmClientFree proto WINAPI \
	   pNodeToFree: PVOID

;RPC_STATUS
RpcSmDestroyClientContext proto WINAPI \
	 ContextHandle: PVOID

;RPC_STATUS
RpcSmDisableAllocate proto WINAPI

;RPC_STATUS
RpcSmEnableAllocate proto WINAPI

;RPC_STATUS
RpcSmFree proto WINAPI \
	    NodeToFree: PVOID

;RPC_SS_THREAD_HANDLE
RpcSmGetThreadHandle proto WINAPI \
	       pStatus: ptr RPC_STATUS

;RPC_STATUS
RpcSmSetClientAllocFree proto WINAPI \
	   ClientAlloc: ptr RPC_CLIENT_ALLOC,
	    ClientFree: ptr RPC_CLIENT_FREE

;RPC_STATUS
RpcSmSetThreadHandle proto WINAPI \
		    Id: RPC_SS_THREAD_HANDLE

;RPC_STATUS
RpcSmSwapClientAllocFree proto WINAPI \
	   ClientAlloc: ptr RPC_CLIENT_ALLOC,
	    ClientFree: ptr RPC_CLIENT_FREE,
	OldClientAlloc: ptr RPC_CLIENT_ALLOC,
	 OldClientFree: ptr RPC_CLIENT_FREE


;void
NdrRpcSsEnableAllocate proto WINAPI \
	      pMessage: PMIDL_STUB_MESSAGE

;void
NdrRpcSsDisableAllocate proto WINAPI \
	      pMessage: PMIDL_STUB_MESSAGE

;void
NdrRpcSmSetClientToOsf proto WINAPI \
	      pMessage: PMIDL_STUB_MESSAGE

;PVOID
NdrRpcSmClientAllocate proto WINAPI \
		  Size: size_t

;void
NdrRpcSmClientFree proto WINAPI \
	    NodeToFree: PVOID

;PVOID
NdrRpcSsDefaultAllocate proto WINAPI \
		  Size: size_t

;void
NdrRpcSsDefaultFree proto WINAPI \
	    NodeToFree: PVOID



;PFULL_PTR_XLAT_TABLES
NdrFullPointerXlatInit proto WINAPI \
      NumberOfPointers: DWORD,
	      XlatSide: XLAT_SIDE

;void
NdrFullPointerXlatFree proto WINAPI \
	   pXlatTables: PFULL_PTR_XLAT_TABLES

;int
NdrFullPointerQueryPointer proto WINAPI \
	   pXlatTables: PFULL_PTR_XLAT_TABLES,
	      pPointer: PVOID,
	     QueryType: BYTE,
		pRefId: LPDWORD

;int
NdrFullPointerQueryRefId proto WINAPI \
	   pXlatTables: PFULL_PTR_XLAT_TABLES,
		 RefId: DWORD,
	     QueryType: BYTE,
	     ppPointer: PVOID

;void
NdrFullPointerInsertRefId proto WINAPI \
	   pXlatTables: PFULL_PTR_XLAT_TABLES,
		 RefId: DWORD,
	      pPointer: PVOID

;int
NdrFullPointerFree proto WINAPI \
	   pXlatTables: PFULL_PTR_XLAT_TABLES,
	       Pointer: PVOID

;PVOID
NdrAllocate proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
		   Len: size_t

;void
NdrClearOutParameters proto WINAPI \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING,
	       ArgAddr: PVOID



;PVOID
NdrOleAllocate proto WINAPI \
		  Size: size_t

;void
NdrOleFree proto WINAPI \
	    NodeToFree: PVOID

if 0
ifdef CONST_VTABLE
CONST_VTBL equ <const>
else
CONST_VTBL equ <>
endif


if _MSC_VER GE 1100
DECLSPEC_UUID macro x
	exitm<__declspec(uuid(x))>
	endm
MIDL_INTERFACE macro x
	exitm<struct __declspec(uuid(x)) __declspec(novtable)>
	endm
else
DECLSPEC_UUID macro x
	exitm <>
	endm
MIDL_INTERFACE macro x
	exitm<struct>
	endm
endif

if _MSC_VER GE 1100
EXTERN_GUID macro itf,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8
	exitm<itf IID <l1,s1,s2,<c1,c2,c3,c4,c5,c6,c7,c8>>>
	endm
else
EXTERN_GUID macro itf,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8
	exitm<externdef itf:IID>
	endm
endif

endif
endif

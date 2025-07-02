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

MIDL_user_allocate proto WINAPI :size_t
MIDL_user_free proto WINAPI :ptr

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

CALLBACK(NDR_RUNDOWN, :ptr)

SCONTEXT_QUEUE		STRUC
NumberOfObjects		dd ?
ArrayOfObjects		NDR_SCONTEXT ?
SCONTEXT_QUEUE		ENDS
PSCONTEXT_QUEUE		typedef ptr SCONTEXT_QUEUE

NDRCContextBinding proto WINAPI :NDR_CCONTEXT
NDRCContextMarshall proto WINAPI :NDR_CCONTEXT, :ptr
NDRCContextUnmarshall proto WINAPI :ptr, :RPC_BINDING_HANDLE, :ptr, :DWORD
NDRSContextMarshall proto WINAPI :NDR_SCONTEXT, :ptr, :NDR_RUNDOWN
NDRSContextUnmarshall proto WINAPI :ptr, :DWORD
NDRSContextMarshallEx proto WINAPI :RPC_BINDING_HANDLE, :NDR_SCONTEXT, :ptr, :NDR_RUNDOWN
NDRSContextUnmarshallEx proto WINAPI :RPC_BINDING_HANDLE, :ptr, :DWORD
RpcSsDestroyClientContext proto WINAPI :ptr
NDRcopy proto WINAPI :ptr, :ptr, :UINT
MIDL_wchar_strlen proto WINAPI :ptr
MIDL_wchar_strcpy proto WINAPI :ptr, :ptr
char_from_ndr proto WINAPI :PRPC_MESSAGE, :LPBYTE
char_array_from_ndr proto WINAPI :PRPC_MESSAGE, :DWORD, :DWORD, :LPBYTE
short_from_ndr proto WINAPI :PRPC_MESSAGE, :LPWORD
short_array_from_ndr proto WINAPI :PRPC_MESSAGE, :DWORD, :DWORD, :LPWORD
short_from_ndr_temp proto WINAPI :LPBYTE, :LPWORD, :DWORD
long_from_ndr proto WINAPI :PRPC_MESSAGE, :LPDWORD
long_array_from_ndr proto WINAPI :PRPC_MESSAGE, :DWORD, :DWORD, :LPDWORD
long_from_ndr_temp proto WINAPI :LPBYTE, :LPDWORD, :DWORD
enum_from_ndr proto WINAPI :PRPC_MESSAGE, :LPWORD
float_from_ndr proto WINAPI :PRPC_MESSAGE, :ptr
float_array_from_ndr proto WINAPI :PRPC_MESSAGE, :DWORD, :DWORD, :ptr
double_from_ndr proto WINAPI :PRPC_MESSAGE, :ptr
double_array_from_ndr proto WINAPI :PRPC_MESSAGE, :DWORD, :DWORD, :ptr
hyper_from_ndr proto WINAPI :PRPC_MESSAGE, :ptr
hyper_array_from_ndr proto WINAPI :PRPC_MESSAGE, :DWORD, :DWORD, :ptr
hyper_from_ndr_temp proto WINAPI :LPBYTE, :ptr, :DWORD
data_from_ndr proto WINAPI :PRPC_MESSAGE, :ptr, :LPSTR, :BYTE
data_into_ndr proto WINAPI :ptr, :PRPC_MESSAGE, :LPSTR, :BYTE
tree_into_ndr proto WINAPI :ptr, :PRPC_MESSAGE, :LPSTR, :BYTE
data_size_ndr proto WINAPI :ptr, :PRPC_MESSAGE, :LPSTR, :BYTE
tree_size_ndr proto WINAPI :ptr, :PRPC_MESSAGE, :LPSTR, :BYTE
tree_peek_ndr proto WINAPI :PRPC_MESSAGE, :LPBYTE, :LPSTR, :BYTE
midl_allocate proto WINAPI :size_t

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


CALLBACK(USER_MARSHAL_SIZING_ROUTINE, :LPDWORD, :DWORD, :PVOID)
CALLBACK(USER_MARSHAL_MARSHALLING_ROUTINE, :LPDWORD, :LPBYTE, :PVOID)
CALLBACK(USER_MARSHAL_UNMARSHALLING_ROUTINE, :LPDWORD, :LPBYTE, :PVOID)
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



NdrSimpleTypeMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :BYTE
NdrPointerMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrSimpleStructMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantStructMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantVaryingStructMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrHardStructMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrComplexStructMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrFixedArrayMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantArrayMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantVaryingArrayMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrVaryingArrayMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrComplexArrayMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrNonConformantStringMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantStringMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrEncapsulatedUnionMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrNonEncapsulatedUnionMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrByteCountPointerMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrXmitOrRepAsMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrUserMarshalMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING

NdrInterfacePointerMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrClientContextMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :NDR_CCONTEXT, :SINT
NdrServerContextMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :NDR_SCONTEXT, :NDR_RUNDOWN
NdrSimpleTypeUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :BYTE
NdrPointerUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrSimpleStructUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrConformantStructUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrConformantVaryingStructUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrHardStructUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrComplexStructUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrFixedArrayUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrConformantArrayUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrConformantVaryingArrayUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrVaryingArrayUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrComplexArrayUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrNonConformantStringUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrConformantStringUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrEncapsulatedUnionUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrNonEncapsulatedUnionUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrByteCountPointerUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrXmitOrRepAsUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrUserMarshalUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE

NdrInterfacePointerUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING, :BYTE
NdrClientContextUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :ptr, :RPC_BINDING_HANDLE
NdrServerContextUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE
NdrPointerBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrSimpleStructBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantStructBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantVaryingStructBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrHardStructBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrComplexStructBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrFixedArrayBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantArrayBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantVaryingArrayBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrVaryingArrayBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrComplexArrayBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantStringBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrNonConformantStringBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrEncapsulatedUnionBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrNonEncapsulatedUnionBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrByteCountPointerBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrXmitOrRepAsBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrUserMarshalBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrInterfacePointerBufferSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrContextHandleSize proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrPointerMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrSimpleStructMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrConformantStructMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrConformantVaryingStructMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrHardStructMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrComplexStructMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrFixedArrayMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrConformantArrayMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrConformantVaryingArrayMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrVaryingArrayMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrComplexArrayMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrConformantStringMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrNonConformantStringMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrEncapsulatedUnionMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrNonEncapsulatedUnionMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrXmitOrRepAsMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrUserMarshalMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrInterfacePointerMemorySize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrPointerFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrSimpleStructFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantStructFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantVaryingStructFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrHardStructFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrComplexStructFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrFixedArrayFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantArrayFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConformantVaryingArrayFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrVaryingArrayFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrComplexArrayFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrEncapsulatedUnionFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrNonEncapsulatedUnionFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrByteCountPointerFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrXmitOrRepAsFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrUserMarshalFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrInterfacePointerFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :PFORMAT_STRING
NdrConvert2 proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING, :LONG
NdrConvert proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING

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

NdrUserMarshalSimpleTypeConvert proto WINAPI :LPDWORD, :LPBYTE, :BYTE
NdrClientInitializeNew proto WINAPI :PRPC_MESSAGE, :PMIDL_STUB_MESSAGE, :PMIDL_STUB_DESC, :UINT
NdrServerInitializeNew proto WINAPI :PRPC_MESSAGE, :PMIDL_STUB_MESSAGE, :PMIDL_STUB_DESC
NdrServerInitializePartial proto WINAPI :PRPC_MESSAGE, :PMIDL_STUB_MESSAGE, :PMIDL_STUB_DESC, :DWORD
NdrClientInitialize proto WINAPI :PRPC_MESSAGE, :PMIDL_STUB_MESSAGE, :PMIDL_STUB_DESC, :UINT
NdrServerInitialize proto WINAPI :PRPC_MESSAGE, :PMIDL_STUB_MESSAGE, :PMIDL_STUB_DESC
NdrServerInitializeUnmarshall proto WINAPI :PMIDL_STUB_MESSAGE, :PMIDL_STUB_DESC, :PRPC_MESSAGE
NdrServerInitializeMarshall proto WINAPI :PRPC_MESSAGE, :PMIDL_STUB_MESSAGE
NdrGetBuffer proto WINAPI :PMIDL_STUB_MESSAGE, :DWORD, :RPC_BINDING_HANDLE
NdrNsGetBuffer proto WINAPI :PMIDL_STUB_MESSAGE, :DWORD, :RPC_BINDING_HANDLE
NdrGetPipeBuffer proto WINAPI :PMIDL_STUB_MESSAGE, :DWORD, :RPC_BINDING_HANDLE
NdrGetPartialBuffer proto WINAPI :PMIDL_STUB_MESSAGE
NdrSendReceive proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE
NdrNsSendReceive proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :ptr
NdrPipeSendReceive proto WINAPI :PMIDL_STUB_MESSAGE, :PNDR_PIPE_DESC
NdrFreeBuffer proto WINAPI :PMIDL_STUB_MESSAGE
NdrGetDcomProtocolVersion proto WINAPI :PMIDL_STUB_MESSAGE, :ptr
NdrPipesInitialize proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING, :PNDR_PIPE_DESC, :PNDR_PIPE_MESSAGE, :LPSTR, :DWORD
NdrPipePull proto WINAPI :LPSTR, :ptr, :DWORD, :LPDWORD
NdrPipePush proto WINAPI :LPSTR, :ptr, :DWORD
NdrIsAppDoneWithPipes proto WINAPI :PNDR_PIPE_DESC
NdrPipesDone proto WINAPI :PMIDL_STUB_MESSAGE
NdrClientCall2 proto WINAPI :PMIDL_STUB_DESC, :PFORMAT_STRING
NdrClientCall proto WINAPI :PMIDL_STUB_DESC, :PFORMAT_STRING
NdrAsyncClientCall proto WINAPI :PMIDL_STUB_DESC, :PFORMAT_STRING

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

NdrAsyncStubCall proto WINAPI :ptr, :ptr, :ptr, :ptr
NdrAsyncServerCall proto WINAPI :PRPC_MESSAGE
NdrStubCall2 proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :LPDWORD
NdrServerCall2 proto WINAPI :PRPC_MESSAGE
NdrStubCall proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :LPDWORD
NdrServerCall proto WINAPI :PRPC_MESSAGE
NdrServerUnmarshall proto WINAPI :ptr, :PRPC_MESSAGE, :PMIDL_STUB_MESSAGE, :PMIDL_STUB_DESC, :PFORMAT_STRING, :ptr
NdrServerMarshall proto WINAPI :ptr, :ptr, :PMIDL_STUB_MESSAGE, :PFORMAT_STRING
NdrMapCommAndFaultStatus proto WINAPI :PMIDL_STUB_MESSAGE, :LPDWORD, :LPDWORD, :RPC_STATUS
NdrSH_UPDecision proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :RPC_BUFPTR
NdrSH_TLUPDecision proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE
NdrSH_TLUPDecisionBuffer proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE
NdrSH_IfAlloc proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :DWORD
NdrSH_IfAllocRef proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :DWORD
NdrSH_IfAllocSet proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :DWORD
NdrSH_IfCopy proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :DWORD
NdrSH_IfAllocCopy proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :DWORD
NdrSH_Copy proto WINAPI :LPBYTE, :LPBYTE, :DWORD
NdrSH_IfFree proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE
NdrSH_StringMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :DWORD, :SINT
NdrSH_StringUnMarshall proto WINAPI :PMIDL_STUB_MESSAGE, :LPBYTE, :SINT

RPC_SS_THREAD_HANDLE typedef ptr

CALLBACK(RPC_CLIENT_ALLOC, :size_t)
CALLBACK(RPC_CLIENT_FREE, :ptr)

RpcSsAllocate proto WINAPI :size_t
RpcSsDisableAllocate proto WINAPI
RpcSsEnableAllocate proto WINAPI
RpcSsFree proto WINAPI :ptr
RpcSsGetThreadHandle proto WINAPI
RpcSsSetClientAllocFree proto WINAPI :ptr, :ptr
RpcSsSetThreadHandle proto WINAPI :RPC_SS_THREAD_HANDLE
RpcSsSwapClientAllocFree proto WINAPI :ptr, :ptr, :RPC_CLIENT_ALLOC, :RPC_CLIENT_FREE
RpcSmAllocate proto WINAPI :size_t, :ptr
RpcSmClientFree proto WINAPI :ptr
RpcSmDestroyClientContext proto WINAPI :ptr
RpcSmDisableAllocate proto WINAPI
RpcSmEnableAllocate proto WINAPI
RpcSmFree proto WINAPI :ptr
RpcSmGetThreadHandle proto WINAPI :ptr
RpcSmSetClientAllocFree proto WINAPI :ptr, :ptr
RpcSmSetThreadHandle proto WINAPI :RPC_SS_THREAD_HANDLE
RpcSmSwapClientAllocFree proto WINAPI :ptr, :ptr, :ptr, :ptr
NdrRpcSsEnableAllocate proto WINAPI :PMIDL_STUB_MESSAGE
NdrRpcSsDisableAllocate proto WINAPI :PMIDL_STUB_MESSAGE
NdrRpcSmSetClientToOsf proto WINAPI :PMIDL_STUB_MESSAGE
NdrRpcSmClientAllocate proto WINAPI :size_t
NdrRpcSmClientFree proto WINAPI :ptr
NdrRpcSsDefaultAllocate proto WINAPI :size_t
NdrRpcSsDefaultFree proto WINAPI :ptr

NdrFullPointerXlatInit proto WINAPI :DWORD, :XLAT_SIDE
NdrFullPointerXlatFree proto WINAPI :PFULL_PTR_XLAT_TABLES
NdrFullPointerQueryPointer proto WINAPI :PFULL_PTR_XLAT_TABLES, :ptr, :BYTE, :LPDWORD
NdrFullPointerQueryRefId proto WINAPI :PFULL_PTR_XLAT_TABLES, :DWORD, :BYTE, :ptr
NdrFullPointerInsertRefId proto WINAPI :PFULL_PTR_XLAT_TABLES, :DWORD, :ptr
NdrFullPointerFree proto WINAPI :PFULL_PTR_XLAT_TABLES, :ptr
NdrAllocate proto WINAPI :PMIDL_STUB_MESSAGE, :size_t
NdrClearOutParameters proto WINAPI :PMIDL_STUB_MESSAGE, :PFORMAT_STRING, :ptr
NdrOleAllocate proto WINAPI :size_t
NdrOleFree proto WINAPI :ptr

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

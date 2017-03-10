ifndef __LIBC_INC
 include libc.inc
endif
.xlist
ifndef __RPCNDR_H_VERSION__
__RPCNDR_H_VERSION__ equ 450
;;
;; Definitions for stub data structures and prototypes of helper functions.
;;
;; This version of the rpcproxy.h file corresponds to MIDL version 3.3.106
;; used with NT5 beta env from build #1574 on.
;;
endif ;; __RPCNDR_H_VERSION__

ifndef __RPCNDR_H__
__RPCNDR_H__ equ 1

ifdef __REQUIRED_RPCNDR_H_VERSION__
if ( __RPCNDR_H_VERSION__ LT __REQUIRED_RPCNDR_H_VERSION__ )
.err <incorrect LT rpcndr.h GT version. Use the header that matches with the MIDL compiler.>
endif
endif

;;
;; Set the packing level for RPC structures for Dos, Windows and Mac.
;;

include rpcnsip.inc
.xlist

;;;;***************************************************************************
;;
;;     Network Computing Architecture (NCA) definition:
;;
;;     Network Data Representation: (NDR) Label format:
;;     An unsigned long (32 bits) with the following layout:
;;
;;     3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
;;     1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;;    +---------------+---------------+---------------+-------+-------+
;;    |	  Reserved    |	  Reserved    |Floating point | Int   | Char  |
;;    |		      |		      |Representation | Rep.  | Rep.  |
;;    +---------------+---------------+---------------+-------+-------+
;;
;;     Where
;;
;;	   Reserved:
;;
;;	       Must be zero (0) for NCA 1.5 and NCA 2.0.
;;
;;	   Floating point Representation is:
;;
;;	       0 - IEEE
;;	       1 - VAX
;;	       2 - Cray
;;	       3 - IBM
;;
;;	   Int Rep. is Integer Representation:
;;
;;	       0 - Big Endian
;;	       1 - Little Endian
;;
;;	   Char Rep. is Character Representation:
;;
;;	       0 - ASCII
;;	       1 - EBCDIC
;;
;;     The Microsoft Local Data Representation (for all platforms which are
;;     of interest currently is edefined below:
;;
;; ***************************************************************************

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


;;***************************************************************************
;;  Macros for targeted platforms
;;**************************************************************************

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

;;***************************************************************************
;;  Other MIDL base types / predefined types:
;;**************************************************************************

;#define small char
;typedef BYTE byte;
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

endif ;; _HYPER_DEFINED

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
MIDL_user_allocate proto _CType \
		      : size_t

;void
MIDL_user_free proto _CType \
		      : PVOID

ifdef __RPC_WIN16__
RPC_VAR_ENTRY		equ <export c>
else
RPC_VAR_ENTRY		equ <c>
endif


;; winnt only
if defined(_M_MRX000) OR defined(_M_IX86) OR defined(_M_ALPHA)
__MIDL_DECLSPEC_DLLIMPORT equ <__declspec(dllimport)>
__MIDL_DECLSPEC_DLLEXPORT equ <__declspec(dllexport)>
else
__MIDL_DECLSPEC_DLLIMPORT equ <>
__MIDL_DECLSPEC_DLLEXPORT equ <>
endif




;;***************************************************************************
;; Context handle management related definitions:
;;
;; Client and Server Contexts.
;;
;;**************************************************************************

NDR_CCONTEXT		typedef PVOID

_NDR_SCONTEXT		STRUC
pad			PVOID 2 dup(?)
userContext		PVOID ?
_NDR_SCONTEXT		ENDS
NDR_SCONTEXT		typedef ptr _NDR_SCONTEXT

NDRSContextValue macro hContext
	.err <Macro not implemented>
	endm

cbNDRContext		equ 20		;; size of context on WIRE

;void
NDR_RUNDOWN_T typedef proto _CType \
	       context: PVOID
NDR_RUNDOWN typedef ptr NDR_RUNDOWN_T

SCONTEXT_QUEUE		STRUC
NumberOfObjects		dd ?
ArrayOfObjects		NDR_SCONTEXT ?
SCONTEXT_QUEUE		ENDS
PSCONTEXT_QUEUE		typedef ptr SCONTEXT_QUEUE

;RPC_BINDING_HANDLE
NDRCContextBinding proto _CType \
	      CContext: NDR_CCONTEXT

;void
NDRCContextMarshall proto _CType \
	      CContext: NDR_CCONTEXT,
		 pBuff: PVOID

;void
NDRCContextUnmarshall proto _CType \
	     pCContext: ptr NDR_CCONTEXT,
	      hBinding: RPC_BINDING_HANDLE,
		 pBuff: PVOID,
    DataRepresentation: DWORD

;void
NDRSContextMarshall proto _CType \
	      CContext: NDR_SCONTEXT,
		 pBuff: PVOID,
	 userRunDownIn: NDR_RUNDOWN

;NDR_SCONTEXT
NDRSContextUnmarshall proto _CType \
		 pBuff: PVOID,
    DataRepresentation: DWORD

;void
NDRSContextMarshallEx proto _CType \
	 BindingHandle: RPC_BINDING_HANDLE,
	      CContext: NDR_SCONTEXT,
		 pBuff: PVOID,
	 userRunDownIn: NDR_RUNDOWN

;NDR_SCONTEXT
NDRSContextUnmarshallEx proto _CType \
	 BindingHandle: RPC_BINDING_HANDLE,
		 pBuff: PVOID,
    DataRepresentation: DWORD

;void
RpcSsDestroyClientContext proto _CType \
	 ContextHandle: PVOID


;;***************************************************************************
;; NDR conversion related definitions.
;;**************************************************************************

byte_from_ndr macro source, target
	.err <Macro not implemented>
	endm
byte_array_from_ndr macro Source, LowerIndex, UpperIndex, Target
	.err <Macro not implemented>
	endm
boolean_from_ndr macro source, target
	.err <Macro not implemented>
	endm
boolean_array_from_ndr macro Source, LowerIndex, UpperIndex, Target
	.err <Macro not implemented>
	endm
small_from_ndr macro source, target
	.err <Macro not implemented>
	endm
small_from_ndr_temp macro source, target, format
	.err <Macro not implemented>
	endm
small_array_from_ndr macro Source, LowerIndex, UpperIndex, Target
	.err <Macro not implemented>
	endm

;;***************************************************************************
;; Platform specific mapping of c-runtime functions.
;;**************************************************************************

ifdef __RPC_WIN32__
MIDL_ascii_strlen macro string
	exitm<strlen(string)>
	endm
MIDL_ascii_strcpy macro target,source
	exitm<strcpy(target,source)>
	endm
MIDL_memset macro s,c,n
	exitm<memset(s,c,n)>
	endm
endif

;;***************************************************************************
;; Ndr Library helper function prototypes for MIDL 1.0 ndr functions.
;;**************************************************************************

;void
NDRcopy proto _CType \
	       pTarget: PVOID,
	       pSource: PVOID,
		 _size: UINT

;size_t
MIDL_wchar_strlen proto _CType \
		     s: ptr wchar_t

;void
MIDL_wchar_strcpy proto _CType \
		     t: PVOID,
		     s: ptr wchar_t

;void
char_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
		Target: LPBYTE

;void
char_array_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: LPBYTE

;void
short_from_ndr proto _CType \
		source: PRPC_MESSAGE,
		target: LPWORD

;void
short_array_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: LPWORD

;void
short_from_ndr_temp proto _CType \
		source: LPBYTE,
		target: LPWORD,
		format: DWORD

;void
long_from_ndr proto _CType \
		source: PRPC_MESSAGE,
		target: LPDWORD

;void
long_array_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: LPDWORD

;void
long_from_ndr_temp proto _CType \
		source: LPBYTE,
		target: LPDWORD,
		format: DWORD

;void
enum_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
		Target: LPWORD

;void
float_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
		Target: PVOID

;void
float_array_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: PVOID

;void
double_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
		Target: PVOID

;void
double_array_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: PVOID

;void
hyper_from_ndr proto _CType \
		source: PRPC_MESSAGE,
		target: ptr hyper

;void
hyper_array_from_ndr proto _CType \
	 SourceMessage: PRPC_MESSAGE,
	    LowerIndex: DWORD,
	    UpperIndex: DWORD,
		Target: ptr hyper

;void
hyper_from_ndr_temp proto _CType \
		source: LPBYTE,
		target: ptr hyper,
		format: DWORD

;void
data_from_ndr proto _CType \
		source: PRPC_MESSAGE,
		target: PVOID,
		format: LPSTR,
		MscPak: BYTE

;void
data_into_ndr proto _CType \
		source: PVOID,
		target: PRPC_MESSAGE,
		format: LPSTR,
		MscPak: BYTE

;void
tree_into_ndr proto _CType \
		source: PVOID,
		target: PRPC_MESSAGE,
		format: LPSTR,
		MscPak: BYTE

;void
data_size_ndr proto _CType \
		source: PVOID,
		target: PRPC_MESSAGE,
		format: LPSTR,
		MscPak: BYTE

;void
tree_size_ndr proto _CType \
		source: PVOID,
		target: PRPC_MESSAGE,
		format: LPSTR,
		MscPak: BYTE

;void
tree_peek_ndr proto _CType \
		source: PRPC_MESSAGE,
		buffer: LPBYTE,
		format: LPSTR,
		MscPak: BYTE

;PVOID
midl_allocate proto _CType \
		 _size: size_t

;;***************************************************************************
;; MIDL 2.0 ndr definitions.
;;**************************************************************************

error_status_t		typedef DWORD

_midl_ma1 macro p, cast
	exitm<*(*( cast **) AND p)++>
	endm
_midl_ma2 macro p, cast
	exitm<*(*( cast **) AND p)++>
	endm
_midl_ma4 macro p, cast
	exitm<*(*( cast **) AND p)++>
	endm
_midl_ma8 macro p, cast
	exitm<*(*( cast **) AND p)++>
	endm

_midl_unma1 macro p, cast
	exitm<*(( cast *)p)++>
	endm
_midl_unma2 macro p, cast
	exitm<*(( cast *)p)++>
	endm
_midl_unma3 macro p, cast
	exitm<*(( cast *)p)++>
	endm
_midl_unma4 macro p, cast
	exitm<*(( cast *)p)++>
	endm

;; Some alignment specific macros.


_midl_fa2 macro p
	inc p
	and p,-2
	exitm<p>
	endm
_midl_fa4 macro p
	add p,3
	and p,-4
	exitm<p>
	endm
_midl_fa8 macro p
	add p,7
	and p,-8
	exitm<p>
	endm

_midl_addp macro p, n
	exitm<(p += n)>
	endm

;; Marshalling macros

_midl_marsh_lhs macro p, cast
	exitm<*(*( cast **) AND p)++>
	endm
_midl_marsh_up macro mp, p
	exitm<*(*(DWORD **) AND mp)++ = p>
	endm
_midl_advmp macro mp
	exitm<*(*(DWORD **) AND mp)++>
	endm
_midl_unmarsh_up macro p
	exitm<(*(*(DWORD **) AND p)++)>
	endm


;;//////////////////////////////////////////////////////////////////////////
;; Ndr macros.
;;//////////////////////////////////////////////////////////////////////////

NdrMarshConfStringHdr macro p, s, l
	exitm<(_midl_ma4( p, DWORD) = s, _midl_ma4( p, DWORD) = 0, _midl_ma4( p, DWORD) = l)>
	endm

NdrUnMarshConfStringHdr macro p, s, l
	exitm<((s=_midl_unma4(p,DWORD), (_midl_addp(p,4)),  (l=_midl_unma4(p,DWORD))>
	endm

NdrMarshCCtxtHdl macro pc,p
	exitm<(NDRCContextMarshall( (NDR_CCONTEXT)pc, p ),p+20)>
	endm

NdrUnMarshCCtxtHdl macro pc,p,h,drep
	exitm<(NDRCContextUnmarshall((NDR_CONTEXT)pc,h,p,drep), p+20)>
	endm

NdrUnMarshSCtxtHdl macro pc, p,drep
	exitm<(pc = NdrSContextUnMarshall(p,drep ))>
	endm


NdrMarshSCtxtHdl macro pc,p,rd
	exitm<(NdrSContextMarshall((NDR_SCONTEXT)pc,p, (NDR_RUNDOWN)rd)>
	endm

NdrFieldOffset macro s,f
	exitm<(long)( AND (((s *)0)- GT f))>
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

;;
;; On the server side, the following exceptions are mapped to
;; the bad stub data exception if -error stub_data is used.
;;

RPC_BAD_STUB_DATA_EXCEPTION_FILTER equ ( (RpcExceptionCode() EQ STATUS_ACCESS_VIOLATION) OR (RpcExceptionCode() EQ STATUS_DATATYPE_MISAIGNMENT) OR (RpcExceptionCode() EQ RPC_X_BAD_STUB_DATA) )

;;///////////////////////////////////////////////////////////////////////////
;; Some stub helper functions.
;;///////////////////////////////////////////////////////////////////////////

;;//////////////////////////////////////////////////////////////////////////
;; Stub helper structures.
;;//////////////////////////////////////////////////////////////////////////

;MIDL_STUB_MESSAGE	typedef STRUC
;MIDL_STUB_DESC		typedef STRUC
;FULL_PTR_XLAT_TABLES	typedef STRUC

RPC_BUFPTR		typedef LPBYTE
RPC_LENGTH		typedef DWORD

;; Expression evaluation callback routine prototype.
;void
EXPR_EVAL_T		typedef proto _CType :PVOID
EXPR_EVAL		typedef ptr EXPR_EVAL_T
PFORMAT_STRING		typedef LPBYTE

;;
;; Multidimensional conformant/varying array struct.
;;
ARRAY_INFO		STRUC
Dimension		LONG ?

;; These fields MUST be (DWORD *)
BufferConformanceMark	LPDWORD ?
BufferVarianceMark	LPDWORD ?

;; Count arrays, used for top level arrays in -Os stubs
MaxCountArray		LPDWORD ?
OffsetArray		LPDWORD ?
ActualCountArray	LPDWORD ?
ARRAY_INFO		ENDS
PARRAY_INFO		typedef ptr ARRAY_INFO

;;
;;  Pipe related definitions.
;;

PNDR_PIPE_DESC		typedef ptr NDR_PIPE_DESC
PNDR_PIPE_MESSAGE	typedef ptr NDR_PIPE_MESSAGE
PNDR_ASYNC_MESSAGE	typedef ptr NDR_ASYNC_MESSAGE

;;
;; MIDL Stub Message
;;
;;if NOT defined(__RPC_DOS__) AND NOT defined(__RPC_WIN16__) AND NOT defined(__RPC_MAC__)
;;include <pshpack4.h>
;;endif

MIDL_STUB_MESSAGE	STRUC
;; RPC message structure.
RpcMsg			PRPC_MESSAGE ?

;; Pointer into RPC message buffer.
Buffer			LPBYTE ?

;;
;; These are used internally by the Ndr routines to mark the beginning
;; and end of an incoming RPC buffer.
;;
BufferStart		LPBYTE ?
BufferEnd		LPBYTE ?

;;
;; Used internally by the Ndr routines as a place holder in the buffer.
;; On the marshalling side it's used to mark the location where conformance
;; size should be marshalled.
;; On the unmarshalling side it's used to mark the location in the buffer
;; used during pointer unmarshalling to base pointer offsets off of.
;;
BufferMark		LPBYTE ?

;; Set by the buffer sizing routines.
BufferLength		dd ?

;; Set by the memory sizing routines.
MemorySize		dd ?

;; Pointer to user memory.
Memory			LPBYTE ?

;; Is the Ndr routine begin called from a client side stub.
IsClient		SINT ?

;; Can the buffer be re-used for memory on unmarshalling.
ReuseBuffer		SINT ?

;; Holds the current pointer to an allocate all nodes memory block.
AllocAllNodesMemory	LPBYTE ?

;; Used for debugging asserts only, remove later.
AllocAllNodesMemoryEnd	LPBYTE ?

;;
;; Stuff needed while handling complex structures
;;

;; Ignore imbeded pointers while computing buffer or memory sizes.
IgnoreEmbeddedPointers	SINT ?

;;
;; This marks the location in the buffer where pointees of a complex
;; struct reside.
;;
PointerBufferMark	LPBYTE ?

;;
;; Used to catch errors in SendReceive.
;;
fBufferValid		db ?

;;
;; Obsolete unused field (formerly MaxContextHandleNumber).
;;
Unused			db ?

;;
;; Used internally by the Ndr routines.	 Holds the max counts for
;; a conformant array.
;;
MaxCount		dd ?

;;
;; Used internally by the Ndr routines.	 Holds the offsets for a varying
;; array.
;;
_Offset			dd ?

;;
;; Used internally by the Ndr routines.	 Holds the actual counts for
;; a varying array.
;;
ActualCount		dd ?

;; Allocation and Free routine to be used by the Ndr routines.
pfnAllocate		PVOID ? ; (*pfnAllocate)(size_t)
pfnFree			PVOID ? ; (*pfnFree)(PVOID)

;;
;; Top of parameter stack.	Used for "single call" stubs during marshalling
;; to hold the beginning of the parameter list on the stack.  Needed to
;; extract parameters which hold attribute values for top level arrays and
;; pointers.
;;
StackTop		LPBYTE ?

;;
;;	Fields used for the transmit_as and represent_as objects.
;;	For represent_as the mapping is: presented=local, transmit=named.
;;
pPresentedType		LPBYTE ?
pTransmitType		LPBYTE ?

;;
;; When we first construct a binding on the client side, stick it
;; in the rpcmessage and later call RpcGetBuffer, the handle field
;; in the rpcmessage is changed. That's fine except that we need to
;; have that original handle for use in unmarshalling context handles
;; (the second argument in NDRCContextUnmarshall to be exact). So
;; stash the contructed handle here and extract it when needed.
;;
SavedHandle		handle_t ?

;;
;; Pointer back to the stub descriptor.	 Use this to get all handle info.
;;
StubDesc		PVOID ? ; _MIDL_STUB_DES*

;;
;; Full pointer stuff.
;;
FullPtrXlatTables	PVOID ? ; _FULL_PTR_XLAT_TABLES*

FullPtrRefId		dd ?

;;
;; flags
;;

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

;;
;; This is where the Beta2 stub message ends.
;;

SizePtrCountArray	LPDWORD ?
SizePtrOffsetArray	LPDWORD ?
SizePtrLengthArray	LPDWORD ?

;;
;; Interpreter argument queue.	Used on server side only.
;;
pArgQueue		PVOID ?

dwStubPhase		dd ?

;;
;; Pipe descriptor, defined for the 4.0 release.
;;
pPipeDesc		PNDR_PIPE_DESC ?

;;
;;	Async message pointer, an NT 5.0 feature.
;;
pAsyncMsg		PNDR_ASYNC_MESSAGE ?

Reserved		dd 3 dup(?)

;;
;;	Fields up to this point present since the 3.50 release.
;;

MIDL_STUB_MESSAGE	ENDS
PMIDL_STUB_MESSAGE	typedef ptr MIDL_STUB_MESSAGE

;include <poppack.h>

;;
;; Generic handle bind/unbind routine pair.
;;
;PVOID
GENERIC_BINDING_ROUTINE_T typedef proto _CType \
		      : PVOID
GENERIC_BINDING_ROUTINE typedef ptr GENERIC_BINDING_ROUTINE_T
;void
GENERIC_UNBIND_ROUTINE_T typedef proto _CType \
		      : PVOID,
		      : LPBYTE
GENERIC_UNBIND_ROUTINE typedef ptr GENERIC_UNBIND_ROUTINE_T

GENERIC_BINDING_ROUTINE_PAIR STRUC
pfnBind			GENERIC_BINDING_ROUTINE ?
pfnUnbind		GENERIC_UNBIND_ROUTINE ?
GENERIC_BINDING_ROUTINE_PAIR ENDS
PGENERIC_BINDING_ROUTINE_PAIR typedef ptr GENERIC_BINDING_ROUTINE_PAIR

GENERIC_BINDING_INFO	STRUC
pObj			PVOID ?
_Size			UINT ?
pfnBind			GENERIC_BINDING_ROUTINE ?
pfnUnbind		GENERIC_UNBIND_ROUTINE ?
GENERIC_BINDING_INFO	ENDS
PGENERIC_BINDING_INFO	typedef ptr GENERIC_BINDING_INFO

;; typedef EXPR_EVAL - see above
;; typedefs for xmit_as

if (defined(_MSC_VER)) AND NOT defined(MIDL_PASS)
;; a Microsoft C++ compiler
NDR_SHAREABLE		equ <inline>
else
NDR_SHAREABLE		equ <static>
endif


;void
XMIT_HELPER_ROUTINE_T typedef proto _CType \
		      : PMIDL_STUB_MESSAGE
XMIT_HELPER_ROUTINE typedef ptr XMIT_HELPER_ROUTINE_T

XMIT_ROUTINE_QUINTUPLE	STRUC
pfnTranslateToXmit	XMIT_HELPER_ROUTINE ?
pfnTranslateFromXmit	XMIT_HELPER_ROUTINE ?
pfnFreeXmit		XMIT_HELPER_ROUTINE ?
pfnFreeInst		XMIT_HELPER_ROUTINE ?
XMIT_ROUTINE_QUINTUPLE	ENDS
PXMIT_ROUTINE_QUINTUPLE typedef ptr XMIT_ROUTINE_QUINTUPLE


;DWORD
USER_MARSHAL_SIZING_ROUTINE_T typedef proto _CType \
		      : LPDWORD,
		      : DWORD,
		      : PVOID
USER_MARSHAL_SIZING_ROUTINE typedef ptr USER_MARSHAL_SIZING_ROUTINE_T
;LPBYTE
USER_MARSHAL_MARSHALLING_ROUTINE_T typedef proto _CType \
		      : LPDWORD,
		      : LPBYTE,
		      : PVOID
USER_MARSHAL_MARSHALLING_ROUTINE typedef ptr USER_MARSHAL_MARSHALLING_ROUTINE_T

;LPBYTE
USER_MARSHAL_UNMARSHALLING_ROUTINE_T typedef proto _CType \
		      : LPDWORD,
		      : LPBYTE,
		      : PVOID
USER_MARSHAL_UNMARSHALLING_ROUTINE typedef ptr USER_MARSHAL_UNMARSHALLING_ROUTINE_T
;void
;LPDWORD
USER_MARSHAL_FREEING_ROUTINE_T typedef proto _CType \
		      : LPDWORD,
		      : PVOID
USER_MARSHAL_FREEING_ROUTINE typedef ptr USER_MARSHAL_FREEING_ROUTINE_T

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

USER_CALL_IS_ASYNC	equ 0x0100	    ;; aux flag: in an [async] call


MALLOC_FREE_STRUCT	STRUC
pfnAllocate		PVOID ? ; (*pfnAllocate)(size_t)
pfnFree			PVOID ? ; (*pfnFree)(PVOID)
MALLOC_FREE_STRUCT	ENDS

COMM_FAULT_OFFSETS	STRUC
CommOffset		dw ?
FaultOffset		dw ?
COMM_FAULT_OFFSETS	ENDS

;;
;; MIDL Stub Descriptor
;;

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

;; Ndr library version.
Version			dd ?

;;
;; Reserved for future use. (no reserves )
;;

pMallocFreeStruct	PVOID ? ; MALLOC_FREE_STRUCT* ?
MIDLVersion		LONG ?
CommFaultOffsets	PVOID ? ; COMM_FAULT_OFFSETS* ?

;;New fields for version 3.0+

aUserMarshalQuadruple	PVOID ? ; USER_MARSHAL_ROUTINE_QUADRUPLE* ?

Reserved1		LONG ?
Reserved2		LONG ?
Reserved3		LONG ?
Reserved4		LONG ?
Reserved5		LONG ?

MIDL_STUB_DESC		ENDS
PMIDL_STUB_DESC		typedef ptr MIDL_STUB_DESC
PMIDL_XMIT_TYPE		typedef PVOID

;;
;; MIDL Stub Format String.  This is a const in the stub.
;;
if NOT defined( RC_INVOKED )
;;pragma warning( disable:4200 )
endif
MIDL_FORMAT_STRING	STRUC
Pad			dw ?
Format			db ?
MIDL_FORMAT_STRING	ENDS
if NOT defined( RC_INVOKED )
;pragma warning( default:4200 )
endif

;;
;; Stub thunk used for some interpreted server stubs.
;;
;void
STUB_THUNK_T typedef proto _CType \
		      : PMIDL_STUB_MESSAGE

STUB_THUNK		typedef ptr STUB_THUNK_T
SERVER_ROUTINE		typedef LONG
PSERVER_ROUTINE		typedef ptr SERVER_ROUTINE

;;
;; Server Interpreter's information strucuture.
;;
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

;;
;; Stubless object proxy information structure.
;;
MIDL_STUBLESS_PROXY_INFO STRUC
pStubDesc		PMIDL_STUB_DESC ?
ProcFormatString	PFORMAT_STRING ?
FormatStringOffset	LPWORD ?
LocalFormatTypes	PFORMAT_STRING ?
LocalProcString		PFORMAT_STRING ?
LocalFmtStringOffset	LPWORD ?
MIDL_STUBLESS_PROXY_INFO ENDS

PMIDL_STUBLESS_PROXY_INFO typedef ptr MIDL_STUBLESS_PROXY_INFO

;;
;; This is the return value from NdrClientCall.
;;
CLIENT_CALL_RETURN	UNION
Pointer			PVOID ?
Simple			LONG ?
CLIENT_CALL_RETURN	ENDS

;;
;; Full pointer data structures.
;;

XLAT_SIDE		typedef sdword
XLAT_SERVER		equ 1
XLAT_CLIENT		equ 2

;;
;; Stores the translation for the conversion from a full pointer into it's
;; corresponding ref id.
;;
FULL_PTR_TO_REFID_ELEMENT STRUC
Next			PVOID ?; FULL_PTR_TO_REFID_ELEMENT *
Pointer			PVOID ?
RefId			dd ?
State			db ?
FULL_PTR_TO_REFID_ELEMENT ENDS
PFULL_PTR_TO_REFID_ELEMENT typedef ptr FULL_PTR_TO_REFID_ELEMENT

;;
;; Full pointer translation tables.
;;
FULL_PTR_XLAT_TABLES	STRUC
;;
;; Ref id to pointer translation information.
;;
STRUC RefIdToPointer
 XlatTable		PVOID ?
 StateTable		LPBYTE ?
 NumberOfEntries	dd ?
ENDS

;;
;; Pointer to ref id translation information.
;;
STRUC PointerToRefId
 XlatTable		PFULL_PTR_TO_REFID_ELEMENT ?
 NumberOfBuckets	dd ?
 HashMask		dd ?
ENDS

;;
;; Next ref id to use.
;;
NextRefId		dd ?

;;
;; Keep track of the translation size we're handling : server or client.
;; This tells us when we have to do reverse translations when we insert
;; new translations.  On the server we must insert a pointer-to-refid
;; translation whenever we insert a refid-to-pointer translation, and
;; vica versa for the client.
;;
XlatSide		XLAT_SIDE ?
FULL_PTR_XLAT_TABLES	ENDS
PFULL_PTR_XLAT_TABLES	typedef ptr FULL_PTR_XLAT_TABLES

;;**************************************************************************
;;* New MIDL 2.0 Ndr routine templates
;;*************************************************************************

;;
;; Marshall routines
;;

;void
NdrSimpleTypeMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	    FormatChar: BYTE

;LPBYTE
NdrPointerMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Structures

;LPBYTE
NdrSimpleStructMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantStructMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantVaryingStructMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrHardStructMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrComplexStructMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Arrays

;LPBYTE
NdrFixedArrayMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantArrayMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantVaryingArrayMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrVaryingArrayMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrComplexArrayMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Strings

;LPBYTE
NdrNonConformantStringMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrConformantStringMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Unions

;LPBYTE
NdrEncapsulatedUnionMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;LPBYTE
NdrNonEncapsulatedUnionMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Byte count pointer

;LPBYTE
NdrByteCountPointerMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Transmit as and represent as

;LPBYTE
NdrXmitOrRepAsMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; User_marshal

;LPBYTE
NdrUserMarshalMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Cairo interface pointer

;LPBYTE
NdrInterfacePointerMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Context handles

;void
NdrClientContextMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	 ContextHandle: NDR_CCONTEXT,
		fCheck: SINT

;void
NdrServerContextMarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	 ContextHandle: NDR_SCONTEXT,
	RundownRoutine: NDR_RUNDOWN

;;
;; Unmarshall routines
;;

;void
NdrSimpleTypeUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	    FormatChar: BYTE

;LPBYTE
NdrPointerUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; Structures

;LPBYTE
NdrSimpleStructUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantStructUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantVaryingStructUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrHardStructUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrComplexStructUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; Arrays

;LPBYTE
NdrFixedArrayUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantArrayUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantVaryingArrayUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrVaryingArrayUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrComplexArrayUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; Strings

;LPBYTE
NdrNonConformantStringUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrConformantStringUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; Unions

;LPBYTE
NdrEncapsulatedUnionUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;LPBYTE
NdrNonEncapsulatedUnionUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; Byte count pointer

;LPBYTE
NdrByteCountPointerUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; Transmit as and represent as

;LPBYTE
NdrXmitOrRepAsUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; User_marshal

;LPBYTE
NdrUserMarshalUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; Cairo interface pointer

;LPBYTE
NdrInterfacePointerUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      ppMemory: LPBYTE,
	       pFormat: PFORMAT_STRING,
	    fMustAlloc: BYTE

;; Context handles

;void
NdrClientContextUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	pContextHandle: ptr NDR_CCONTEXT,
	    BindHandle: RPC_BINDING_HANDLE

;NDR_SCONTEXT
NdrServerContextUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE

;;
;; Buffer sizing routines
;;

;void
NdrPointerBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Structures

;void
NdrSimpleStructBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantStructBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantVaryingStructBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrHardStructBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrComplexStructBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Arrays

;void
NdrFixedArrayBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantArrayBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantVaryingArrayBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrVaryingArrayBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrComplexArrayBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Strings

;void
NdrConformantStringBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrNonConformantStringBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Unions

;void
NdrEncapsulatedUnionBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrNonEncapsulatedUnionBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Byte count pointer

;void
NdrByteCountPointerBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Transmit as and represent as

;void
NdrXmitOrRepAsBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; User_marshal

;void
NdrUserMarshalBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Cairo Interface pointer

;void
NdrInterfacePointerBufferSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Context Handle size
;;
;void
NdrContextHandleSize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;;
;; Memory sizing routines
;;

;DWORD
NdrPointerMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;; Structures

;DWORD
NdrSimpleStructMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrConformantStructMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrConformantVaryingStructMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrHardStructMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrComplexStructMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;; Arrays

;DWORD
NdrFixedArrayMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrConformantArrayMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrConformantVaryingArrayMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrVaryingArrayMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrComplexArrayMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;; Strings

;DWORD
NdrConformantStringMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrNonConformantStringMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;; Unions

;DWORD
NdrEncapsulatedUnionMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;DWORD
NdrNonEncapsulatedUnionMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;; Transmit as and represent as

;DWORD
NdrXmitOrRepAsMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;; User_marshal

;DWORD
NdrUserMarshalMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;; Cairo Interface pointer

;DWORD
NdrInterfacePointerMemorySize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;;
;; Freeing routines
;;

;void
NdrPointerFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Structures

;void
NdrSimpleStructFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantStructFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantVaryingStructFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrHardStructFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrComplexStructFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Arrays

;void
NdrFixedArrayFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantArrayFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrConformantVaryingArrayFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrVaryingArrayFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrComplexArrayFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Unions

;void
NdrEncapsulatedUnionFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;void
NdrNonEncapsulatedUnionFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Byte count

;void
NdrByteCountPointerFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Transmit as and represent as

;void
NdrXmitOrRepAsFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; User_marshal

;void
NdrUserMarshalFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;; Cairo Interface pointer

;void
NdrInterfacePointerFree proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
	       pFormat: PFORMAT_STRING

;;
;; Endian conversion routine.
;;

;void
NdrConvert2 proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING,
	  NumberParams: LONG

;void
NdrConvert proto _CType \
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
NdrUserMarshalSimpleTypeConvert proto _CType \
		pFlags: LPDWORD,
	       pBuffer: LPBYTE,
	    FormatChar: BYTE

;;
;; Auxilary routines
;;

;void
NdrClientInitializeNew proto _CType \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
	       ProcNum: UINT

;LPBYTE
NdrServerInitializeNew proto _CType \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC

;void
NdrServerInitializePartial proto _CType \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
   RequestedBufferSize: DWORD

;void
NdrClientInitialize proto _CType \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
	       ProcNum: UINT

;LPBYTE
NdrServerInitialize proto _CType \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC

;LPBYTE
NdrServerInitializeUnmarshall proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
	       pRpcMsg: PRPC_MESSAGE

;void
NdrServerInitializeMarshall proto _CType \
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE

;LPBYTE
NdrGetBuffer proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	  BufferLength: DWORD,
		Handle: RPC_BINDING_HANDLE

;LPBYTE
NdrNsGetBuffer proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	  BufferLength: DWORD,
		Handle: RPC_BINDING_HANDLE

;LPBYTE
NdrGetPipeBuffer proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	  BufferLength: DWORD,
		Handle: RPC_BINDING_HANDLE

;void
NdrGetPartialBuffer proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE

;LPBYTE
NdrSendReceive proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	    pBufferEnd: LPBYTE

;LPBYTE
NdrNsSendReceive proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	    pBufferEnd: LPBYTE,
	   pAutoHandle: ptr RPC_BINDING_HANDLE

;void
NdrPipeSendReceive proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPipeDesc: PNDR_PIPE_DESC

;void
NdrFreeBuffer proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE

;RPC_STATUS
NdrGetDcomProtocolVersion proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	      pVersion: ptr RPC_VERSION


;;
;; Pipe specific calls
;;

;void
NdrPipesInitialize proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	    pParamDesc: PFORMAT_STRING,
	     pPipeDesc: PNDR_PIPE_DESC,
	      pPipeMsg: PNDR_PIPE_MESSAGE,
	     pStackTop: LPSTR,
	  NumberParams: DWORD

;void
NdrPipePull proto _CType \
		pState: LPSTR,
		   buf: PVOID,
		 esize: DWORD,
		ecount: LPDWORD

;void
NdrPipePush proto _CType \
		pState: LPSTR,
		   buf: PVOID,
		ecount: DWORD

;void
NdrIsAppDoneWithPipes proto _CType \
	     pPipeDesc: PNDR_PIPE_DESC

;void
NdrPipesDone proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE


;;
;; Interpeter calls.
;;

;; client

;CLIENT_CALL_RETURN RPC_VAR_ENTRY
NdrClientCall2 proto _CType \
       pStubDescriptor: PMIDL_STUB_DESC,
	       pFormat: PFORMAT_STRING

;CLIENT_CALL_RETURN RPC_VAR_ENTRY
NdrClientCall proto _CType \
       pStubDescriptor: PMIDL_STUB_DESC,
	       pFormat: PFORMAT_STRING

;CLIENT_CALL_RETURN RPC_VAR_ENTRY
NdrAsyncClientCall proto _CType \
       pStubDescriptor: PMIDL_STUB_DESC,
	       pFormat: PFORMAT_STRING

;; server

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

;IRpcStubBuffer;	    ;; Forward declaration STRUC

;long
NdrAsyncStubCall proto _CType \
		 pThis: PVOID,;struct IRpcStubBuffer *
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	       pRpcMsg: PRPC_MESSAGE,
	  pdwStubPhase: LPDWORD

;void
NdrAsyncServerCall proto _CType \
	       pRpcMsg: PRPC_MESSAGE

;long
NdrStubCall2 proto _CType \
		 pThis: PVOID,;struct IRpcStubBuffer *
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	       pRpcMsg: PRPC_MESSAGE,
	  pdwStubPhase: LPDWORD

;void
NdrServerCall2 proto _CType \
	       pRpcMsg: PRPC_MESSAGE

;long
NdrStubCall proto _CType \
		 pThis: PVOID,;struct IRpcStubBuffer *
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	       pRpcMsg: PRPC_MESSAGE,
	  pdwStubPhase: LPDWORD

;void
NdrServerCall proto _CType \
	       pRpcMsg: PRPC_MESSAGE

;int
NdrServerUnmarshall proto _CType \
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	       pRpcMsg: PRPC_MESSAGE,
	      pStubMsg: PMIDL_STUB_MESSAGE,
       pStubDescriptor: PMIDL_STUB_DESC,
	       pFormat: PFORMAT_STRING,
	    pParamList: PVOID

;void
NdrServerMarshall proto _CType \
		 pThis: PVOID,;struct IRpcStubBuffer *
	      pChannel: PVOID,;struct IRpcChannelBuffer *
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING

;; Comm and Fault status

;RPC_STATUS
NdrMapCommAndFaultStatus proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	   pCommStatus: LPDWORD,
	  pFaultStatus: LPDWORD,
		Status: RPC_STATUS

;; Helper routines

;int
NdrSH_UPDecision proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
	       pBuffer: RPC_BUFPTR

;int
NdrSH_TLUPDecision proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE

;int
NdrSH_TLUPDecisionBuffer proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE

;int
NdrSH_IfAlloc proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;int
NdrSH_IfAllocRef proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;int
NdrSH_IfAllocSet proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;RPC_BUFPTR
NdrSH_IfCopy proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;RPC_BUFPTR
NdrSH_IfAllocCopy proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;DWORD
NdrSH_Copy proto _CType \
	      pStubMsg: LPBYTE,
	     pPtrInMem: LPBYTE,
		 Count: DWORD

;void
NdrSH_IfFree proto _CType \
	      pMessage: PMIDL_STUB_MESSAGE,
		  pPtr: LPBYTE


;RPC_BUFPTR
NdrSH_StringMarshall proto _CType \
	      pMessage: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
		 Count: DWORD,
		__Size: SINT

;RPC_BUFPTR
NdrSH_StringUnMarshall proto _CType \
	      pMessage: PMIDL_STUB_MESSAGE,
	       pMemory: LPBYTE,
		 _Size: SINT

;;***************************************************************************
;; 2.0 memory package: rpc_ss_* rpc_sm_* MIDL ?
;;**************************************************************************

RPC_SS_THREAD_HANDLE	typedef PVOID

;PVOID
RPC_CLIENT_ALLOC_T typedef proto _CType \
		 _Size: size_t
RPC_CLIENT_ALLOC typedef ptr RPC_CLIENT_ALLOC_T

;void
RPC_CLIENT_FREE_T typedef proto _CType \
		      : PVOID

;;++
;; RpcSs* package
;;--

;PVOID
RpcSsAllocate proto _CType \
		 _Size: size_t

;void
RpcSsDisableAllocate proto _CType

;void
RpcSsEnableAllocate proto _CType

;void
RpcSsFree proto _CType \
	    NodeToFree: PVOID

;RPC_SS_THREAD_HANDLE
RpcSsGetThreadHandle proto _CType

;void
RpcSsSetClientAllocFree proto _CType \
	   ClientAlloc: ptr RPC_CLIENT_ALLOC,
	    ClientFree: ptr RPC_CLIENT_FREE

;void
RpcSsSetThreadHandle proto _CType \
		    Id: RPC_SS_THREAD_HANDLE

;void
RpcSsSwapClientAllocFree proto _CType \
	   ClientAlloc: ptr RPC_CLIENT_ALLOC,
	    ClientFree: ptr RPC_CLIENT_FREE,
	OldClientAlloc: RPC_CLIENT_ALLOC,
	 OldClientFree: RPC_CLIENT_FREE

;;++
;;  RpcSm* package
;;--

;PVOID
RpcSmAllocate proto _CType \
		 _Size: size_t,
	       pStatus: ptr RPC_STATUS

;RPC_STATUS
RpcSmClientFree proto _CType \
	   pNodeToFree: PVOID

;RPC_STATUS
RpcSmDestroyClientContext proto _CType \
	 ContextHandle: PVOID

;RPC_STATUS
RpcSmDisableAllocate proto _CType

;RPC_STATUS
RpcSmEnableAllocate proto _CType

;RPC_STATUS
RpcSmFree proto _CType \
	    NodeToFree: PVOID

;RPC_SS_THREAD_HANDLE
RpcSmGetThreadHandle proto _CType \
	       pStatus: ptr RPC_STATUS

;RPC_STATUS
RpcSmSetClientAllocFree proto _CType \
	   ClientAlloc: ptr RPC_CLIENT_ALLOC,
	    ClientFree: ptr RPC_CLIENT_FREE

;RPC_STATUS
RpcSmSetThreadHandle proto _CType \
		    Id: RPC_SS_THREAD_HANDLE

;RPC_STATUS
RpcSmSwapClientAllocFree proto _CType \
	   ClientAlloc: ptr RPC_CLIENT_ALLOC,
	    ClientFree: ptr RPC_CLIENT_FREE,
	OldClientAlloc: ptr RPC_CLIENT_ALLOC,
	 OldClientFree: ptr RPC_CLIENT_FREE

;;++
;; Ndr stub entry points
;;--

;void
NdrRpcSsEnableAllocate proto _CType \
	      pMessage: PMIDL_STUB_MESSAGE

;void
NdrRpcSsDisableAllocate proto _CType \
	      pMessage: PMIDL_STUB_MESSAGE

;void
NdrRpcSmSetClientToOsf proto _CType \
	      pMessage: PMIDL_STUB_MESSAGE

;PVOID
NdrRpcSmClientAllocate proto _CType \
		 _Size: size_t

;void
NdrRpcSmClientFree proto _CType \
	    NodeToFree: PVOID

;PVOID
NdrRpcSsDefaultAllocate proto _CType \
		 _Size: size_t

;void
NdrRpcSsDefaultFree proto _CType \
	    NodeToFree: PVOID

;;***************************************************************************
;; end of memory package: rpc_ss_* rpc_sm_*
;;**************************************************************************

;;***************************************************************************
;; Full Pointer APIs
;;**************************************************************************

;PFULL_PTR_XLAT_TABLES
NdrFullPointerXlatInit proto _CType \
      NumberOfPointers: DWORD,
	      XlatSide: XLAT_SIDE

;void
NdrFullPointerXlatFree proto _CType \
	   pXlatTables: PFULL_PTR_XLAT_TABLES

;int
NdrFullPointerQueryPointer proto _CType \
	   pXlatTables: PFULL_PTR_XLAT_TABLES,
	      pPointer: PVOID,
	     QueryType: BYTE,
		pRefId: LPDWORD

;int
NdrFullPointerQueryRefId proto _CType \
	   pXlatTables: PFULL_PTR_XLAT_TABLES,
		 RefId: DWORD,
	     QueryType: BYTE,
	     ppPointer: PVOID

;void
NdrFullPointerInsertRefId proto _CType \
	   pXlatTables: PFULL_PTR_XLAT_TABLES,
		 RefId: DWORD,
	      pPointer: PVOID

;int
NdrFullPointerFree proto _CType \
	   pXlatTables: PFULL_PTR_XLAT_TABLES,
	       Pointer: PVOID

;PVOID
NdrAllocate proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
		   Len: size_t

;void
NdrClearOutParameters proto _CType \
	      pStubMsg: PMIDL_STUB_MESSAGE,
	       pFormat: PFORMAT_STRING,
	       ArgAddr: PVOID


;;***************************************************************************
;; Proxy APIs
;;**************************************************************************

;PVOID
NdrOleAllocate proto _CType \
		 _Size: size_t

;void
NdrOleFree proto _CType \
	    NodeToFree: PVOID

if 0
ifdef CONST_VTABLE
CONST_VTBL equ <const>
else
CONST_VTBL equ <>
endif

;;***************************************************************************
;; Special things for VC5 Com support
;;**************************************************************************

if _MSC_VER GE 1100
DECLSPEC_UUID macro x
	exitm<__declspec(uuid(x))>
	endm
MIDL_INTERFACE macro x
	exitm<struct __declspec(uuid(x)) __declspec(novtable)>
	endm
else
DECLSPEC_UUID(x) equ 1
MIDL_INTERFACE macro x
	exitm<struct>
	endm
endif

if _MSC_VER GE 1100
EXTERN_GUID macro itf,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8
	exitm<\>
	endm
const IID __declspec(selectany) itf = {l1,s1,s2,{c1,c2,c3,c4,c5,c6,c7,c8}} EXTERN_C ?
else
EXTERN_GUID macro itf,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8
	exitm<EXTERN_C const IID itf>
	endm
endif

;; Reset the packing level for DOS, Windows and Mac.

if defined(__RPC_DOS__) OR defined(__RPC_WIN16__) OR defined(__RPC_MAC__)
;;pragma pack()
endif
endif ;; 0

.list
endif ;; __RPCNDR_H__



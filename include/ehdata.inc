ifndef _INC_EHDATA
_INC_EHDATA equ <>

ifdef ONLY_VALUES
_EHDATA_NOHEADERS equ 1
endif

ifndef _CRTBLD
ifndef _VC_VER_INC
;include vcver.inc
endif
endif

if defined(_M_IX86) AND _M_IX86 GE 300
ifndef CC_EXPLICITFRAME
CC_EXPLICITFRAME equ 0
endif
endif

if (defined(_M_IA64) OR defined(_M_AMD64) OR defined(_M_ARM_NT) OR defined(_M_ARM64))
_EH_RELATIVE_OFFSETS	equ 1
else
_EH_RELATIVE_OFFSETS	equ 0
endif

ifdef _WIN64
_EH_PTR64 equ <__ptr64>
else
_EH_PTR64 equ <>
endif

ifndef _EHDATA_NOHEADERS
include stddef.inc
include excpt.inc
ifdef _WIN32
include windows.inc
else
include nowin.inc
endif
endif

.pragma pack(push, 4)

EH_EXCEPTION_NUMBER	equ ('msc' OR 0xE0000000)	;; The NT Exception # that we use

EH_MAGIC_NUMBER1	equ 0x19930520
EH_MAGIC_NUMBER2	equ 0x19930521
EH_MAGIC_NUMBER3	equ 0x19930522

EH_PURE_MAGIC_NUMBER1	equ 0x01994000

FI_EHS_FLAG		equ 0x00000001
FI_DYNSTKALIGN_FLAG	equ 0x00000002

if (EH_MAGIC_NUMBER2 LE EH_MAGIC_NUMBER1) OR (EH_MAGIC_NUMBER3 LE EH_MAGIC_NUMBER2)
.err <new magic number must be greater than the old one>
endif

if (EH_MAGIC_NUMBER1 AND 0xE0000000) OR (EH_MAGIC_NUMBER2 AND 0xE0000000) OR (EH_MAGIC_NUMBER3 AND 0xE0000000)
.err <magic number too big -- must fit into 29 bits>
endif

if (EH_PURE_MAGIC_NUMBER1 GE EH_MAGIC_NUMBER1)
.err <pure EH magic number must be less than native one>
endif

EH_MAGIC_HAS_ES		equ EH_MAGIC_NUMBER2

if _EH_RELATIVE_OFFSETS
EH_EXCEPTION_PARAMETERS equ 4
else
EH_EXCEPTION_PARAMETERS equ 3
endif

ifdef ALLOW_UNWIND_ABORT
EH_ABORT_FRAME_UNWIND_PART equ EH_EXCEPTION_NUMBER+1
endif

EH_EMPTY_STATE		equ -1

ifndef ONLY_VALUES

PMD			STRUC
ifdef _WIN64
mdisp			SINT ?
pdisp			SINT ?
vdisp			SINT ?
else
mdisp			ptrdiff_t ?
pdisp			ptrdiff_t ?
vdisp			ptrdiff_t ?
endif
PMD			ENDS

ifndef WANT_NO_TYPES
if _EH_RELATIVE_OFFSETS AND NOT defined(VERSP_IA64) AND NOT defined(_M_CEE_PURE)
PMFN typedef sdword
else
CALLBACK(PMFN, :LPVOID)
endif
endif

TPGETWINRT_OOM_EXCEPTION typedef proto stdcall
PGETWINRT_OOM_EXCEPTION	 typedef ptr TPGETWINRT_OOM_EXCEPTION

if defined(_M_ALPHA64) OR defined(_M_IA64) OR defined(VERSP_IA64) OR defined(_M_AMD64) OR defined(_M_ARM64)
.pragma pack(push, 8)
endif

ifndef WANT_NO_TYPES
TypeDescriptor		STRUC
if defined(_WIN64) OR defined(_RTTI)
pVFTable		LPVOID ?
else
hash			dd ?
endif
spare			LPVOID ?
name			db 1 dup(?)
TypeDescriptor		ENDS
endif
LPTypeDescriptor	typedef ptr TypeDescriptor

if defined(_M_ALPHA64) OR defined(_M_IA64) OR defined(VERSP_IA64) OR defined(_M_AMD64)
.pragma pack(pop)
endif

TD_HASH macro td
	exitm<((td).hash)>
	endm
TD_NAME macro td
	exitm<((td).name)>
	endm

TD_IS_TYPE_ELLIPSIS macro td
	exitm<.err>
	endm


ifndef _EHDATA_NOTHROW

ifndef WANT_NO_TYPES
CatchableType		STRUC
properties		UINT ?
if _EH_RELATIVE_OFFSETS AND NOT defined(VERSP_IA64) AND NOT defined(_M_CEE_PURE)
pType			SINT ?
else
pType			LPTypeDescriptor ?
endif
thisDisplacement	PMD <>
sizeOrOffset		SINT ?
copyFunction		PMFN ?
CatchableType		ENDS
endif
LPCatchableType		typedef ptr CatchableType

CT_IsSimpleType		equ 0x00000001
CT_ByReferenceOnly	equ 0x00000002
CT_HasVirtualBase	equ 0x00000004
CT_IsWinRTHandle	equ 0x00000008
CT_IsStdBadAlloc	equ 0x00000010

CT_PROPERTIES macro ct
	exitm<((ct).properties)>
	endm
if _EH_RELATIVE_OFFSETS AND NOT defined(_M_CEE_PURE)
CT_PTD_IB macro ct,ib
	exitm<(((ib) + (ct).pType))>
	endm
CT_COPYFUNC_IB macro ct,ib
	exitm<.err>
	endm
else
CT_PTD macro ct
	exitm<((ct).pType)>
	endm
CT_COPYFUNC macro ct
	exitm<((ct).copyFunction)>
	endm
endif
CT_THISDISP macro ct
	exitm<((ct).thisDisplacement)>
	endm
CT_SIZE macro ct
	exitm<((ct).sizeOrOffset)>
	endm
CT_OFFSET macro ct
	exitm<((ct).sizeOrOffset)>
	endm
CT_HASH macro ct
	exitm<(TD_HASH(*CT_PTD(ct)))>
	endm
CT_NAME macro ct
	exitm<(TD_NAME(*CT_PTD(ct)))>
	endm

SET_CT_ISSIMPLETYPE macro ct
	exitm<(CT_PROPERTIES(ct) |= CT_IsSimpleType)>
	endm
SET_CT_BYREFONLY macro ct
	exitm<(CT_PROPERTIES(ct) |= CT_ByReferenceOnly)>
	endm
SET_CT_HASVB macro ct
	exitm<(CT_PROPERTIES(ct) |= CT_HasVirtualBase)>
	endm
SET_CT_ISWINRTHANDLE macro ct
	exitm<(CT_PROPERTIES(ct) |= CT_IsWinRTHandle)>
	endm
SET_CT_ISSTDBADALLOC macro ct
	exitm<(CT_PROPERTIES(ct) |= CT_IsStdBadAlloc)>
	endm

CT_ISSIMPLETYPE macro ct
	exitm<(CT_PROPERTIES(ct) !& CT_IsSimpleType)>
	endm
CT_BYREFONLY macro ct
	exitm<(CT_PROPERTIES(ct) !& CT_ByReferenceOnly)>
	endm
CT_HASVB macro ct
	exitm<(CT_PROPERTIES(ct) !& CT_HasVirtualBase)>
	endm
CT_ISWINRTHANDLE macro ct
	exitm<(CT_PROPERTIES(ct) !& CT_IsWinRTHandle)>
	endm
CT_ISSTDBADALLOC macro ct
	exitm<(CT_PROPERTIES(ct) !& CT_IsStdBadAlloc)>
	endm

ifndef WANT_NO_TYPES
CatchableTypeArray	STRUC
nCatchableTypes		SINT ?
if _EH_RELATIVE_OFFSETS AND NOT defined(VERSP_IA64) AND NOT defined(_M_CEE_PURE)
arrayOfCatchableTypes	SINT 1 dup(?)
else
arrayOfCatchableTypes	LPCatchableType 1 dup(?)
endif
CatchableTypeArray	ENDS
endif
LPCatchableTypeArray	typedef ptr CatchableTypeArray

ifndef WANT_NO_TYPES
ThrowInfo		STRUC
attributes		UINT ?
pmfnUnwind		PMFN ?
if _EH_RELATIVE_OFFSETS AND NOT defined(VERSP_IA64) AND NOT defined(_M_CEE_PURE)
pForwardCompat		SINT ?
pCatchableTypeArray	SINT ?
else
pForwardCompat		PVOID ?
endif
pCatchableTypeArray	LPCatchableTypeArray ?
ThrowInfo		ENDS
endif

TI_IsConst		equ 0x00000001
TI_IsVolatile		equ 0x00000002
TI_IsUnaligned		equ 0x00000004
TI_IsPure		equ 0x00000008
TI_IsWinRT		equ 0x00000010

_CxxThrowException proto WINAPI :ptr, :ptr

ifndef WANT_NO_TYPES
__CxxExceptionFilter proto __cdecl :ptr, :int_t, :ptr
ifdef _MANAGED
___CxxExceptionFilter proto :ptr, :int_t, :ptr
endif
__CxxRegisterExceptionObject proto __cdecl :ptr, :ptr
__CxxDetectRethrow proto __cdecl :ptr
__CxxQueryExceptionSize proto __cdecl
__CxxUnregisterExceptionObject proto __cdecl :ptr, :int_t
endif ;; WANT_NO_TYPES

endif ;; _EHDATA_NOTHROW


ifndef _EHDATA_NOFUNCINFO
ifndef WANT_NO_TYPES
endif
HT_IsConst		equ 0x00000001
HT_IsVolatile		equ 0x00000002
HT_IsUnaligned		equ 0x00000004
HT_IsReference		equ 0x00000008
HT_IsResumable		equ 0x00000010
HT_IsStdDotDot		equ 0x00000040
HT_IsBadAllocCompat	equ 0x00000080
HT_IsComplusEh		equ 0x80000000
ifndef WANT_NO_TYPES
endif
ifndef WANT_NO_TYPES
endif
BBT_UNIQUE_FUNCINFO	equ 1
ifndef WANT_NO_TYPES
endif
endif ;; _EHDATA_NOFUNCINFO

ifndef _EHDATA_NONT
if defined(_M_IA64) OR defined(_M_ALPHA64) OR defined(_M_AMD64) OR defined(_M_ARM64)
.pragma pack(push, 8)
endif
ifndef WANT_NO_TYPES
EHExceptionRecord	STRUC
ExceptionCode		dd ?
ExceptionFlags		dd ?
ExceptionRecord		LPVOID ?
ExceptionAddress	LPVOID ?
NumberParameters	dd ?
STRUC params
 magicNumber		dd ?
 pExceptionObject	LPVOID ?
 pThrowInfo		LPVOID ?
if _EH_RELATIVE_OFFSETS
 pThrowImageBase	LPVOID ?
endif
ENDS
EHExceptionRecord	ENDS
endif
if defined(_M_IA64) OR defined(_M_ALPHA64) OR defined(_M_AMD64) OR defined(_M_ARM64)
.pragma pack(pop)
endif
endif ;; _EHDATA_NONT

endif ;; ONLY_VALUES
.pragma pack(pop)
endif ;; _INC_EHDATA

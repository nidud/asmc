;;**
;;ehdata.h -
;;
;;	Copyright (c) 1993-1995, Microsoft Corporation. All rights reserved.
;;
;;Purpose:
;;	Declare misc. types, macros, etc. for implementation
;;	of C++ Exception Handling for the run-time and the compiler.
;;	Hardware independent, assumes Windows NT.
;;
;; Portions of this header file can be disabled by defining the following
;; macros:
;;	_EHDATA_NOHEADERS - suppresses inclusion of standard header files
;;		If this is specified, then appropriate typedefs or macros must
;;		be provided by some other means.
;;	_EHDATA_NOTHROW - suppresses definitions used only to describe a throw
;;	_EHDATA_NOFUNCINFO - suppresses definitions for the frame descriptor
;;	_EHDATA_NONT - suppresses definitions of our version of NT's stuff
;;
;; Other conditional compilation macros:
;;    CC_EXPLICITFRAME - if true, representation of registration node includes
;;	the value of the frame-pointer for that frame, making the location
;;	of the registration node on the frame flexible.  This is intended
;;	primarily for early testing.
;;
;;       [Internal]
;;
;;Revision History:
;;       05-20-93  BS	Module Created.
;;       03-01-94  CFW	Remove CONTEXT def for x86 for TiborL.
;;       03-03-94  TL	Mips (_M_MRX000 >= 4000) changes
;;       09-02-94  SKS	This header file added.
;;       09-12-94  GJF	Merged in changes from/for DEC (Al Doser, dated 6/20,
;;                       and Bill Baxter, dated 6/28).
;;       11-06-94  GJF	Changed pack pragma to 8 byte alignment.
;;       02-14-95  CFW   Clean up Mac merge.
;;       03-22-95  PML   Add for read-only structs
;;       03-29-95  CFW   Add error message to internal headers.
;;       04-14-95  JWM	Added EH_ABORT_FRAME_UNWIND_PART for EH/SEH exception handling.
;;       04-20-95  TGL	Added iFrameNestLevel field to MIPS FuncInfo
;;       04-27-95  JWM	EH_ABORT_FRAME_UNWIND_PART now #ifdef ALLOW_UNWIND_ABORT.
;;       06-08-95  JWM	Merged CRT version of ehdata.h into langapi source.
;;       01-25-00  GB	Declared _CxxThrowException __declspec(noreturn)
;;       02-08-00  GB	Added HT_ISCOMPLUSEH
;;       03-27-00  PML	Remove CC_P7_SOFT25, which is now on permanently.
;;       09-20-00  GB	Add __cdecl to URT C++ EH support routines (vs7#89576)
;;       09-18-01  GB	Added Support for ExceptionSpecification. Changes mainly made by Arturl.
;;       09-20-01  PML   Buildfix - can't rename EH_MAGIC_NUMBER1, call the new
;;                       code EH_MAGIC_NUMBER2 instead.
;;       11-14-02  GB    Added RtlUnwindEx of IA64
;;       01-31-03  GB    Added support for Pure C++ catch(...) which does not catch seh.
;;       02-28-03  SSM   Remove _RUNTIME_FUNCTION for AMD64 & IA64. Now exposed in Winnt.h
;;       06-09-04  GB    Fixed the pure C++ excpetion handling for 64 bit platforms.
;;       06-29-04  SJ    HandlerType changed to be a ptr on x86 & a 32 bit int on 64 bit
;;                       platforms. Corresponding macros also fixed.
;;       01-26-05  SJ    Fix longjmp behavior VSW#411664
;;       03-19-05  PML   Throw from pure region can't be caught by native/mixed
;;                       and vice-versa (VSW#422533)
;;
;;**

ifndef _INC_EHDATA
_INC_EHDATA equ 1

ifdef ONLY_VALUES
_EHDATA_NOHEADERS equ 1
endif

ifndef _CRTBLD
ifndef _VC_VER_INC
include vcver.inc
endif
endif ;; _CRTBLD 


if defined(_M_IX86) AND _M_IX86 GE 300 ;;IFSTRIP=IGN
 ifndef CC_EXPLICITFRAME
  define CC_EXPLICITFRAME	0	;; If non-zero, we're using a hack version of the
								;; registration node.
 endif
endif

if (defined(_M_IA64) OR defined(_M_AMD64) OR defined(_M_ARM_NT) OR defined(_M_ARM64))
_EH_RELATIVE_OFFSETS    equ 1
else
_EH_RELATIVE_OFFSETS    equ 0
endif

if defined(_WIN64)
_EH_PTR64               equ __ptr64
else
_EH_PTR64 equ 1
endif

ifndef _EHDATA_NOHEADERS
include stddef.inc
include excpt.inc
if defined(_WIN32)
include windows.inc
else
include nowin.inc
endif
endif ;; _EHDATA_NOHEADERS 

pragma pack(push, ehdata, 4)

EH_EXCEPTION_NUMBER     equ ('msc' OR 0xE0000000)	;; The NT Exception # that we use

;; As magic numbers increase, we have to keep track of the versions that we are
;; backwards compatible with.  The top 3 bits of the magic number DWORD are
;; used for other purposes, so while the magic number started as a YYYYMMDD
;; date, it can't represent the year 2000 or later.  Old CRTs also recognize
;; unknown magic numbers with a >= test.  Therefore, we just increment the
;; the magic number by one every time we need another.
;;
;; EH_MAGIC_NUMBER1     The original, still used in exception records for
;;                      native or mixed C++ thrown objects.
;; EH_MAGIC_NUMBER2     Used in the FuncInfo if exception specifications are
;;                      supported and FuncInfo::pESTypeList is valid.
;; EH_MAGIC_NUMBER3     Used in the FuncInfo if FuncInfo::EHFlags is valid, so
;;                      we can check if the function was compiled -EHs or -EHa.

EH_MAGIC_NUMBER1        equ 0x19930520
EH_MAGIC_NUMBER2        equ 0x19930521
EH_MAGIC_NUMBER3        equ 0x19930522

;; We use a different magic number in the thrown object's exception record to
;; indicate it arose from a pure region.  Pure throws can't be caught by native
;; or mixed code, and vice-versa.  Note that the pure magic number is only 7
;; digits, not 8, so it will be less than any of the native EH magic numbers
;; and won't be detected as an unknown newer magic number by the native EH
;; handlers.

EH_PURE_MAGIC_NUMBER1   equ 0x01994000

FI_EHS_FLAG             equ 0x00000001
FI_DYNSTKALIGN_FLAG     equ 0x00000002

if (EH_MAGIC_NUMBER2 LE EH_MAGIC_NUMBER1) OR (EH_MAGIC_NUMBER3 LE EH_MAGIC_NUMBER2)
error new magic number must be greater than the old one
endif

if (EH_MAGIC_NUMBER1 AND 0xE0000000) OR (EH_MAGIC_NUMBER2 AND 0xE0000000) OR (EH_MAGIC_NUMBER3 AND 0xE0000000)
error magic number too big -- must fit into 29 bits
endif

if (EH_PURE_MAGIC_NUMBER1 GE EH_MAGIC_NUMBER1)
error pure EH magic number must be less than native one
endif

EH_MAGIC_HAS_ES         equ EH_MAGIC_NUMBER2	;; Magic number is greater or equal than that
											;; indicates presence of exception specification

if _EH_RELATIVE_OFFSETS
EH_EXCEPTION_PARAMETERS equ 4			;; Number of parameters in exception record
else
EH_EXCEPTION_PARAMETERS equ 3			;; Number of parameters in exception record
endif

ifdef ALLOW_UNWIND_ABORT
EH_ABORT_FRAME_UNWIND_PART equ EH_EXCEPTION_NUMBER+1
endif

EH_EMPTY_STATE          equ -1

ifndef ONLY_VALUES

;;
;; PMD - Pointer to Member Data: generalized pointer-to-member descriptor
;;

PMD                     STRUC
if defined(_WIN64)	 ;;IFSTRIP=IGN
mdisp                   __int32 ?	;; Offset of intended data within base
pdisp                   __int32 ?	;; Displacement to virtual base pointer
vdisp                   __int32 ?	;; Index within vbTable to offset of base
else
mdisp                   ptrdiff_t ?	;; Offset of intended data within base
pdisp                   ptrdiff_t ?	;; Displacement to virtual base pointer
vdisp                   ptrdiff_t ?	;; Index within vbTable to offset of base
endif
PMD                     ENDS

;;
;; PMFN - Pointer to Member Function
;;			M00REVIEW: we may need something more than this, but this will do for now.
;;

ifndef WANT_NO_TYPES
if _EH_RELATIVE_OFFSETS AND NOT defined(VERSP_IA64) AND NOT defined(_M_CEE_PURE);;IFSTRIP=IGN
;                       typedef	__int32	PMFN;  Image relative offset of Member Function
else
_EH_PTR64)              typedef ptr void (
endif
endif ;; WANT_NO_TYPES

    PGETWINRT_OOM_EXCEPTION proc :
;;
;; TypeDescriptor - per-type record which uniquely identifies the type.
;;
;; Each type has a decorated name which uniquely identifies it, and a hash
;; value which is computed by the compiler.  The hash function used is not
;; important; the only thing which is essential is that it be the same for
;; all time.
;;
;; The special type '...' (ellipsis) is represented by a null name.
;;
pragma warning(disable:4200)		;; get rid of obnoxious nonstandard extension warning

if defined(_M_ALPHA64) OR defined(_M_IA64) OR defined(VERSP_IA64) OR defined(_M_AMD64) OR defined(_M_ARM64)
pragma pack(push, TypeDescriptor, 8)
endif

ifndef WANT_NO_TYPES
TypeDescriptor          STRUC
if defined(_WIN64) OR defined(_RTTI) ;;IFSTRIP=IGN
 _EH_PTR64	pVFTable     LPvoid ?	;; Field overloaded by RTTI
else
hash                    dd ?	;; Hash value computed from type's decorated name
endif
 _EH_PTR64			spare      LPvoid ?	;; reserved, possible for RTTI
name                    char  dup(?)	;; The decorated name of the type; 0 terminated.
TypeDescriptor          ENDS
endif ;; WANT_NO_TYPES

if defined(_M_ALPHA64) OR defined(_M_IA64) OR defined(VERSP_IA64) OR defined(_M_AMD64)
pragma pack(pop, TypeDescriptor)
endif
pragma warning(default:4200)

TD_HASH macro td
	exitm<((td).hash)>
	endm
TD_NAME macro td
	exitm<((td).name)>
	endm

TD_IS_TYPE_ELLIPSIS macro td
	exitm<((td EQ NULL) OR (TD_NAME(*td)[0] EQ '\0'))>
	endm


ifndef _EHDATA_NOTHROW

;;///////////////////////////////////////////////////////////////////////////
;;
;; Description of the thrown object.  (M00REVIEW: not final)
;;
;; This information is broken down into three levels, to allow for maximum
;; comdat folding (at the cost of some extra pointers).
;;
;; ThrowInfo is the head of the description, and contains information about
;; 				the particular variant thrown.
;; CatchableTypeArray is an array of pointers to type descriptors.  It will
;;				be shared between objects thrown by reference but with varying
;;				qualifiers.
;; CatchableType is the description of an individual type, and how to effect
;;				the conversion from a given type.
;;
;;---------------------------------------------------------------------------


;;
;; CatchableType - description of a type that can be caught.
;;
;; Note:  although isSimpleType can be part of ThrowInfo, it is more
;;		  convenient for the run-time to have it here.
;;

ifndef WANT_NO_TYPES
s_CatchableType         STRUC
int	properties          unsigned ?	;; Catchable Type properties (Bit field)
if _EH_RELATIVE_OFFSETS AND NOT defined(VERSP_IA64) AND NOT defined(_M_CEE_PURE)	;;IFSTRIP=IGN
pType                   __int32 ?	;; Image relative offset of TypeDescriptor
else
 _EH_PTR64 pType        LPTypeDescriptor ?	;; Pointer to the type descriptor for this type
endif
thisDisplacement        PMD ?	;; Pointer to instance of catch type within
											;; thrown object.
sizeOrOffset            SINT ?	;; Size of simple-type object or offset into
											;; buffer of 'this' pointer for catch object
copyFunction            PMFN ?	;; Copy constructor or CC-closure
CatchableType           ENDS
endif ;; WANT_NO_TYPES

CT_IsSimpleType         equ 0x00000001		;; type is a simple type
CT_ByReferenceOnly      equ 0x00000002		;; type must be caught by reference
CT_HasVirtualBase       equ 0x00000004		;; type is a class with virtual bases
CT_IsWinRTHandle        equ 0x00000008		;; type is a winrt handle
CT_IsStdBadAlloc        equ 0x00000010		;; type is a a std::bad_alloc

CT_PROPERTIES macro ct
	exitm<((ct).properties)>
	endm
if _EH_RELATIVE_OFFSETS AND NOT defined(_M_CEE_PURE)
CT_PTD_IB macro ct,ib
	exitm<((TypeDescriptor *)((ib) + (ct).pType))>
	endm
CT_COPYFUNC_IB macro ct,ib
	exitm<((void (* _EH_PTR64)(void* _EH_PTR64))((ib) + (ct).copyFunction))>
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
	exitm<(CT_PROPERTIES(ct) OR = CT_IsSimpleType)>
	endm
SET_CT_BYREFONLY macro ct
	exitm<(CT_PROPERTIES(ct) OR = CT_ByReferenceOnly)>
	endm
SET_CT_HASVB macro ct
	exitm<(CT_PROPERTIES(ct) OR = CT_HasVirtualBase)>
	endm
SET_CT_ISWINRTHANDLE macro ct
	exitm<(CT_PROPERTIES(ct) OR = CT_IsWinRTHandle)>
	endm
SET_CT_ISSTDBADALLOC macro ct
	exitm<(CT_PROPERTIES(ct) OR = CT_IsStdBadAlloc)>
	endm

CT_ISSIMPLETYPE macro ct
	exitm<(CT_PROPERTIES(ct) AND CT_IsSimpleType)		;; Is it a simple type?>
	endm
CT_BYREFONLY macro ct
	exitm<(CT_PROPERTIES(ct) AND CT_ByReferenceOnly)	;; Must it be caught by reference?>
	endm
CT_HASVB macro ct
	exitm<(CT_PROPERTIES(ct) AND CT_HasVirtualBase)		;; Is this type a class with virtual bases?>
	endm
CT_ISWINRTHANDLE macro ct
	exitm<(CT_PROPERTIES(ct) AND CT_IsWinRTHandle)		;; Is it a winrt handle?>
	endm
CT_ISSTDBADALLOC macro ct
	exitm<(CT_PROPERTIES(ct) AND CT_IsStdBadAlloc)		;; Is it a std::bad_alloc?>
	endm

;;
;; CatchableTypeArray - array of pointers to catchable types, with length
;;
pragma warning(disable:4200)		;; get rid of obnoxious nonstandard extension warning
ifndef WANT_NO_TYPES
s_CatchableTypeArray    STRUC
nCatchableTypes         SINT ?	
if _EH_RELATIVE_OFFSETS AND NOT defined(VERSP_IA64) AND NOT defined(_M_CEE_PURE)	;;IFSTRIP=IGN
arrayOfCatchableTypes   __int32  dup(?)	;; Image relative offset of Catchable Types
else
 _EH_PTR64 arrayOfCatchableTypes LPCatchableType  dup(?)	
endif
CatchableTypeArray      ENDS
endif ;; WANT_NO_TYPES
pragma warning(default:4200)

;;
;; ThrowInfo - information describing the thrown object, staticly built
;; at the throw site.
;;
;; pExceptionObject (the dynamic part of the throw; see below) is always a
;; reference, whether or not it is logically one.  If 'isSimpleType' is true,
;; it is a reference to the simple type, which is 'size' bytes long.  If
;; 'isReference' and 'isSimpleType' are both false, then it's a UDT or
;; a pointer to any type (ie pExceptionObject points to a pointer).  If it's
;; a pointer, copyFunction is NULL, otherwise it is a pointer to a copy
;; constructor or copy constructor closure.
;;
;; The pForwardCompat function pointer is intended to be filled in by future
;; versions, so that if say a DLL built with a newer version (say C10) throws,
;; and a C9 frame attempts a catch, the frame handler attempting the catch (C9)
;; can let the version that knows all the latest stuff do the work.
;;

ifndef WANT_NO_TYPES
s_ThrowInfo             STRUC
int	attributes          unsigned ?	;; Throw Info attributes (Bit field)
pmfnUnwind              PMFN ?	;; Destructor to call when exception
										;; has been handled or aborted.
if _EH_RELATIVE_OFFSETS AND NOT defined(VERSP_IA64) AND NOT defined(_M_CEE_PURE)	;;IFSTRIP=IGN
pForwardCompat          __int32 ?	;; Image relative offset of Forward compatibility frame handler
pCatchableTypeArray     __int32 ?	;; Image relative offset of CatchableTypeArray
else
(__cdecl* _EH_PTR64 pForwardCompat)() SINT ?	;; Forward compatibility frame handler
endif
 _EH_PTR64 pCatchableTypeArray LPCatchableTypeArray ?	;; Pointer to list of pointers to types.
endif
ThrowInfo               ENDS
endif ;; WANT_NO_TYPES

TI_IsConst              equ 0x00000001		;; thrown object has qualifier
TI_IsVolatile           equ 0x00000002		;; thrown object has volatile qualifier
TI_IsUnaligned          equ 0x00000004		;; thrown object has unaligned qualifier
TI_IsPure               equ 0x00000008		;; object thrown from a pure module
TI_IsWinRT              equ 0x00000010      ;; object thrown is a WinRT Exception

THROW_ATTRS macro t
	exitm<((t).attributes)>
	endm
if _EH_RELATIVE_OFFSETS AND NOT defined(_M_CEE_PURE)
THROW_UNWINDFUNC_IB macro t,ib
	exitm<((void (* _EH_PTR64)(void* _EH_PTR64))((ib) + (t).pmfnUnwind))>
	endm
THROW_FORWARDCOMPAT_IB macro t,ib
	exitm<((int(__cdecl * _EH_PTR64)(...))((ib) + (t).pForwardCompat))>
	endm
THROW_CTARRAY_IB macro t,ib
	exitm<((CatchableTypeArray*)((ib) + (t).pCatchableTypeArray))>
	endm
THROW_COUNT_IB macro t,ib
	exitm<(THROW_CTARRAY_IB(t,ib)- GT nCatchableTypes)>
	endm
THROW_CTLIST_IB macro t,ib
	exitm<(THROW_CTARRAY_IB(t,ib)- GT arrayOfCatchableTypes)>
	endm
else
THROW_FORWARDCOMPAT macro t
	exitm<((t).pForwardCompat)>
	endm
THROW_COUNT macro t
	exitm<((t).pCatchableTypeArray- GT nCatchableTypes)>
	endm
THROW_CTLIST macro t
	exitm<((t).pCatchableTypeArray- GT arrayOfCatchableTypes)>
	endm
endif
THROW_UNWINDFUNC macro t
	exitm<((t).pmfnUnwind)>
	endm
THROW_PCTLIST macro t
	exitm<( AND THROW_CTLIST(t))>
	endm
THROW_CT macro t, n
	exitm<(*THROW_CTLIST(t)[n])>
	endm
THROW_PCT macro t, n
	exitm<(THROW_CTLIST(t)[n])>
	endm

SET_TI_ISCONST macro t
	exitm<(THROW_ATTRS(t) OR = TI_IsConst)		;; Is the object thrown 'const' qualified>
	endm
SET_TI_ISVOLATILE macro t
	exitm<(THROW_ATTRS(t) OR = TI_IsVolatile)	;; Is the object thrown 'volatile' qualified>
	endm
SET_TI_ISUNALIGNED macro t
	exitm<(THROW_ATTRS(t) OR = TI_IsUnaligned)	;; Is the object thrown 'unaligned' qualified>
	endm
SET_TI_ISPURE macro t
	exitm<(THROW_ATTRS(t) OR = TI_IsPure)		;; Is the object thrown from a pure module>
	endm
SET_TI_WINRT macro t
	exitm<(THROW_ATTRS(t) OR = TI_IsWinRT)		;; Is the object thrown a WinRT Exception>
	endm

THROW_ISCONST macro t
	exitm<(THROW_ATTRS(t) AND TI_IsConst)>
	endm
THROW_ISVOLATILE macro t
	exitm<(THROW_ATTRS(t) AND TI_IsVolatile)>
	endm
THROW_ISUNALIGNED macro t
	exitm<(THROW_ATTRS(t) AND TI_IsUnaligned)>
	endm
THROW_ISPURE macro t
	exitm<(THROW_ATTRS(t) AND TI_IsPure)>
	endm
THROW_ISWINRT macro t
	exitm<(THROW_ATTRS(t) AND TI_IsWinRT)>
	endm
;;
;; Here's how to throw:
;; M00HACK: _ThrowInfo is the name of the type that is 'pre-injected' into the
;; compiler; since this prototype is known to the FE along with the pre-injected
;; types, it has to match exactly.
;;
__declspec (noreturn) extern "C" void __stdcall _CxxThrowException(void* pExceptionObject, _ThrowInfo* pThrowInfo);

ifndef WANT_NO_TYPES
externdef               int __cdecl __CxxExceptionFilter(void*, void*, int, void *):"C"

ifdef prepifdef
_MANAGED                prepifdef ?
__clrcall ___CxxExceptionFilter(void*, void*, int, void *) SINT ?	
                        prependif ?	; _MANAGED
else
ifdef _MANAGED
__clrcall ___CxxExceptionFilter(void*, void*, int, void *) SINT ?	
endif		;; _MANAGED
endif

;; Returns true if the object is really a C++ exception
;; If it is, stores the previous exception in *storage, and saves the current one
;; This is needed to keep track of the current exception object (used for rethrow & destruction)
externdef               int __cdecl __CxxRegisterExceptionObject(void *exception, void *storage):"C"

ifdef prepifdef
_MANAGED                prepifdef ?
__clrcall ___CxxRegisterExceptionObject(void *exception, void *storage) SINT ?	
                        prependif ?	; _MANAGED
else
ifdef _MANAGED
__clrcall ___CxxRegisterExceptionObject(void *exception, void *storage) SINT ?	
endif		;; _MANAGED
endif

;; Returns true if exception is a C++ rethrown exception
;; This is needed, so Unregister can know whether or not to destroy the object
externdef               int __cdecl __CxxDetectRethrow(void *exception):"C"

ifdef prepifdef
_MANAGED                prepifdef ?
__clrcall ___CxxDetectRethrow(void *exception) SINT ?	
                        prependif ?	; _MANAGED
else
ifdef _MANAGED
__clrcall ___CxxDetectRethrow(void *exception) SINT ?	
endif		;; _MANAGED
endif

;; Returns the byte count of stack space required to store the exception info
externdef               int __cdecl __CxxQueryExceptionSize(void):"C"

ifdef prepifdef
_MANAGED                prepifdef ?
__clrcall ___CxxQueryExceptionSize(void) SINT ?	
                        prependif ?	; _MANAGED
else
ifdef _MANAGED
__clrcall ___CxxQueryExceptionSize(void) SINT ?	
endif		;; _MANAGED
endif

;; Pops the current exception, restoring the previous one from *storage
;; This detects whether or not the exception object needs to be destroyed
externdef               void __cdecl __CxxUnregisterExceptionObject(void *storage, int rethrow):"C"

ifdef prepifdef
_MANAGED                prepifdef ?
__clrcall ___CxxUnregisterExceptionObject(void *storage, int rethrow) void ?	
                        prependif ?	; _MANAGED
else
ifdef _MANAGED
__clrcall ___CxxUnregisterExceptionObject(void *storage, int rethrow) void ?	
endif		;; _MANAGED
endif

endif ;; WANT_NO_TYPES

endif ;; _EHDATA_NOTHROW 


ifndef _EHDATA_NOFUNCINFO

;;///////////////////////////////////////////////////////////////////////////
;;
;; Describing 'try/catch' blocks:
;;
;;---------------------------------------------------------------------------

;;
;; Current state of a function.
;; -1 is the 'blank' state, ie there is nothing to unwind, no try blocks active.
;;

;                       typedef int __ehstate_t;  The type of a state index


;;
;; HandlerType - description of a single 'catch'
;;

ifndef WANT_NO_TYPES
s_HandlerType           STRUC
int	adjectives          unsigned ?	;; Handler Type adjectives (bitfield)
if _EH_RELATIVE_OFFSETS AND NOT defined(_M_CEE_PURE)
dispType                __int32 ?	;; Image relative offset of the corresponding type descriptor
dispCatchObj            __int32 ?	;; Displacement of catch object from base
dispOfHandler           __int32 ?	;; Image relative offset of 'catch' code
if defined(_M_AMD64) OR defined(_M_ARM64)
dispFrame               __int32 ?	;; displacement of address of function frame wrt establisher frame
endif
else
pType                   LPTypeDescriptor ?	;; Pointer to the corresponding type descriptor
if defined(_M_ALPHA64)
dispCatchObj            __int32 ?	;; Displacement of catch object from base
else
dispCatchObj            ptrdiff_t ?	;; Displacement of catch object from base
endif
if (_M_MRX000 GE 4000) OR defined(_M_ARM)	 ;;IFSTRIP=IGN
frameNestLevel          ULONG ?	;; The static nesting level of parent function
endif
			addressOfHandler     LPvoid ?	;; Address of 'catch' code
endif
HandlerType             ENDS
endif

HT_IsConst              equ 0x00000001		;; type referenced is 'const' qualified
HT_IsVolatile           equ 0x00000002		;; type referenced is 'volatile' qualified
HT_IsUnaligned          equ 0x00000004		;; type referenced is 'unaligned' qualified
HT_IsReference          equ 0x00000008		;; catch type is by reference
HT_IsResumable          equ 0x00000010		;; the catch may choose to resume (Reserved)
HT_IsStdDotDot          equ 0x00000040      ;; the catch is std C++ catch(...) which is suppose to catch only C++ exception.
HT_IsBadAllocCompat     equ 0x00000080      ;; the WinRT type can catch a std::bad_alloc
HT_IsComplusEh          equ 0x80000000      ;; Is handling within complus eh.

HT_ADJECTIVES macro ht
	exitm<((ht).adjectives)>
	endm
if _EH_RELATIVE_OFFSETS AND NOT defined(_M_CEE_PURE)
HT_PTD_IB macro ht,ib
	exitm<((TypeDescriptor*)((ib) + (ht).dispType))>
	endm
HT_HANDLER_IB macro ht,ib
	exitm<((void* _EH_PTR64)((ib) + (ht).dispOfHandler))>
	endm
else
HT_PTD macro ht
	exitm<((ht).pType)>
	endm
HT_HANDLER macro ht
	exitm<((ht).addressOfHandler)>
	endm
endif
HT_DISPCATCH macro ht
	exitm<((ht).dispCatchObj)>
	endm
if ((_M_MRX000 GE 4000) OR defined(_M_ARM)) AND NOT defined(_M_ARM_NT)	 ;;IFSTRIP=IGN
HT_FRAMENEST macro ht
	exitm<((ht).frameNestLevel)>
	endm
endif
HT_NAME macro ht
	exitm<(TD_NAME(*HT_PTD(ht)))>
	endm
HT_HASH macro ht
	exitm<(TD_HASH(*HT_PTD(ht)))>
	endm
HT_IS_TYPE_ELLIPSIS macro ht
	exitm<TD_IS_TYPE_ELLIPSIS(HT_PTD(ht))>
	endm

SET_HT_ISCONST macro ht
	exitm<(HT_ADJECTIVES(ht) OR = HT_IsConst)>
	endm
SET_HT_ISVOLATILE macro ht
	exitm<(HT_ADJECTIVES(ht) OR = HT_IsVolatile)>
	endm
SET_HT_ISUNALIGNED macro ht
	exitm<(HT_ADJECTIVES(ht) OR = HT_IsUnaligned)>
	endm
SET_HT_ISREFERENCE macro ht
	exitm<(HT_ADJECTIVES(ht) OR = HT_IsReference)>
	endm
SET_HT_ISRESUMABLE macro ht
	exitm<(HT_ADJECTIVES(ht) OR = HT_IsResumable)>
	endm
SET_HT_ISCOMPLUSEH macro ht
	exitm<(HT_ADJECTIVES(ht) OR = HT_IsComplusEh)>
	endm

HT_ISCONST macro ht
	exitm<(HT_ADJECTIVES(ht) AND HT_IsConst)		;; Is the type referenced 'const' qualified>
	endm
HT_ISVOLATILE macro ht
	exitm<(HT_ADJECTIVES(ht) AND HT_IsVolatile)		;; Is the type referenced 'volatile' qualified>
	endm
HT_ISUNALIGNED macro ht
	exitm<(HT_ADJECTIVES(ht) AND HT_IsUnaligned)	;; Is the type referenced 'unaligned' qualified>
	endm
HT_ISREFERENCE macro ht
	exitm<(HT_ADJECTIVES(ht) AND HT_IsReference)	;; Is the catch type by reference>
	endm
HT_ISRESUMABLE macro ht
	exitm<(HT_ADJECTIVES(ht) AND HT_IsResumable)	;; Might the catch choose to resume (Reserved)>
	endm
HT_ISCOMPLUSEH macro ht
	exitm<(HT_ADJECTIVES(ht) AND HT_IsComplusEh)>
	endm

HT_ISBADALLOCCOMPAT macro ht
	exitm<(HT_ADJECTIVES(ht) AND HT_IsBadAllocCompat)>
	endm

HT_IS_STD_DOTDOT macro ht
	exitm<(HT_ADJECTIVES(ht) AND HT_IsStdDotDot)>
	endm

;;
;; HandlerMapEntry - associates a handler list (sequence of catches) with a
;;	range of eh-states.
;;

ifndef WANT_NO_TYPES
s_TryBlockMapEntry      STRUC
tryLow                  __ehstate_t ?	;; Lowest state index of try
tryHigh                 __ehstate_t ?	;; Highest state index of try
if NOT defined(_M_ALPHA)
catchHigh               __ehstate_t ?	;; Highest state index of any associated catch
endif
nCatches                SINT ?	;; Number of entries in array
if _EH_RELATIVE_OFFSETS	;;IFSTRIP=IGN
dispHandlerArray        __int32 ?	;; Image relative offset of list of handlers for this try
else
pHandlerArray           LPHandlerType ?	;; List of handlers for this try
endif
TryBlockMapEntry        ENDS
endif ;; WANT_NO_TYPES

TBME_LOW macro hm
	exitm<((hm).tryLow)>
	endm
TBME_HIGH macro hm
	exitm<((hm).tryHigh)>
	endm
TBME_CATCHHIGH macro hm
	exitm<((hm).catchHigh)>
	endm
TBME_NCATCHES macro hm
	exitm<((hm).nCatches)>
	endm
if _EH_RELATIVE_OFFSETS	;;IFSTRIP=IGN
TBME_PLIST macro hm,ib
	exitm<((HandlerType*)((ib) + (hm).dispHandlerArray))>
	endm
TBME_CATCH macro hm,n,ib
	exitm<(TBME_PLIST(hm,ib)[n])>
	endm
TBME_PCATCH macro hm,n,ib
	exitm<( AND (TBME_PLIST(hm,ib)[n]))>
	endm
else
TBME_PLIST macro hm
	exitm<((hm).pHandlerArray)>
	endm
TBME_CATCH macro hm, n
	exitm<(TBME_PLIST(hm)[n])>
	endm
TBME_PCATCH macro hm, n
	exitm<( AND (TBME_PLIST(hm)[n]))>
	endm
endif


;;///////////////////////////////////////////////////////////////////////////
;;
;; Description of the function:
;;
;;---------------------------------------------------------------------------

;;
;; UnwindMapEntry - Description of each state transition for unwinding
;;	the stack (ie destructing objects).
;;
;; The unwind map is an array, indexed by current state.  Each entry specifies
;; the state to go to during unwind, and the action required to get there.
;; Note that states are represented by a signed integer, and that the 'blank'
;; state is -1 so that the array remains 0-based (because by definition there
;; is never any unwind action to be performed from state -1).  It is also
;; assumed that state indices will be dense, ie that there will be no gaps of
;; unused state indices in a function.
;;

s_UnwindMapEntry        STRUC
toState                 __ehstate_t ?	;; State this action takes us to
if _EH_RELATIVE_OFFSETS	;;IFSTRIP=IGN
action                  __int32 ?	;; Image relative offset of funclet
else
(*action)(void)         void ?	;; Funclet to call to effect state change
endif
UnwindMapEntry          ENDS

UWE_TOSTATE macro uwe
	exitm<((uwe).toState)>
	endm
if _EH_RELATIVE_OFFSETS
UWE_ACTION_IB macro uwe,ib
	exitm<((void (*_EH_PTR64)(void))((ib) + (uwe).action))>
	endm
else
UWE_ACTION macro uwe
	exitm<((uwe).action)>
	endm
endif

if _M_MRX000 GE 4000 OR defined(_M_MPPC) OR defined(_M_PPC) OR defined(_M_IA64) OR defined(_M_AMD64) OR defined(_M_ARM) OR defined(_M_ARM64)	 ;;IFSTRIP=IGN
IptoStateMapEntry       STRUC
if _EH_RELATIVE_OFFSETS	;;IFSTRIP=IGN
Ip                      __int32 ?	;; Image relative offset of IP
else
Ip                      ULONG ?	
endif
State                   __ehstate_t ?	
IptoStateMapEntry       ENDS
endif

ifndef WANT_NO_TYPES
s_ESTypeList            STRUC
nCount                  SINT ?	;; how many types are there
if _EH_RELATIVE_OFFSETS
dispTypeArray           __int32 ?	;; offset of list of types in exception specification
else
pTypeArray              LPHandlerType ?	;; List of types in exception specification
endif
ESTypeList              ENDS

EST_COUNT macro x
	exitm<((x)- GT nCount)>
	endm
if _EH_RELATIVE_OFFSETS
EST_ARRAY_IB macro estl, ib, n
	exitm<( AND (((HandlerType*)((ib) + (estl)- GT dispTypeArray))[n]))>
	endm
else
EST_ARRAY macro x,n
	exitm<( AND ((x)- GT pTypeArray[n]))>
	endm
endif
endif ;; WANT_NO_TYPES

;;
;; FuncInfo - all the information that describes a function with exception
;;	handling information.
;;

;; bbtFlags values
BBT_UNIQUE_FUNCINFO     equ 1

ifndef WANT_NO_TYPES
;;
;; The magicNumber here is incremented with every compiler change that does not
;; break backwards compatiblity. If for some reason backward compatibilty
;; should be broken, then we will add new handler. What this means is that
;; current handler functions can assume that the structure layout that they
;; know about will remain the same and so even if magicNumber > my_magicNumber,
;; the handler can assume that what all it needs is there. The magicNumber will
;; be revised every time new data is added at the end of this structure.
;;
s_FuncInfo              STRUC
int		magicNumber:29     unsigned ?	;; Identifies version of compiler
int        bbtFlags:3   unsigned ?	;; flags that may be set by BBT processing
maxState                __ehstate_t ?	;; Highest state number plus one (thus
											;; number of entries in unwind map)
if _EH_RELATIVE_OFFSETS	;;IFSTRIP=IGN
dispUnwindMap           __int32 ?	;; Image relative offset of the unwind map
int		nTryBlocks         unsigned ?	;; Number of 'try' blocks in this function
dispTryBlockMap         __int32 ?	;; Image relative offset of the handler map
int		nIPMapEntries      unsigned ?	;; # entries in the IP-to-state map. NYI (reserved)
dispIPtoStateMap        __int32 ?	;; Image relative offset of the IP to state map
dispUwindHelp           __int32 ?	;; Displacement of unwind helpers from base
dispESTypeList          __int32 ?	;; Image relative list of types for exception specifications
else
pUnwindMap              LPUnwindMapEntry ?	;; Where the unwind map is
int		nTryBlocks         unsigned ?	;; Number of 'try' blocks in this function
pTryBlockMap            LPTryBlockMapEntry ?	;; Where the handler map is
if defined(_M_ALPHA)
int          EHContextDelta signed ?	;; Frame offset of EHContext record
endif
int		nIPMapEntries      unsigned ?	;; # entries in the IP-to-state map. NYI (reserved)
if _M_MRX000 GE 4000	 ;;IFSTRIP=IGN
pIPtoStateMap           LPIptoStateMapEntry ?	;; An IP to state map..
dispUnwindHelp          ptrdiff_t ?	;; Displacement of unwind helpers from base
iTryBlockIndex          SINT ?	;; Used by catch functions only
iFrameNestLevel         SINT ?	;; The static nesting level of parent function
elif defined(_M_MPPC) OR defined(_M_PPC) OR defined (_M_ARM)
pIPtoStateMap           LPIptoStateMapEntry ?	;; An IP to state map..
else
pIPtoStateMap           LPvoid ?	;; An IP to state map.  NYI (reserved).
endif
pESTypeList             LPESTypeList ?	;; List of types for exception specifications
endif
EHFlags                 __int32 ?	;; Flags for some features.
if defined(_M_ARM) AND NOT defined(_M_ARM_NT)
alignStack              __int32 ?	;; Dynamic stack alignment
gs_cookie_offset_noalign __int32 ?	;; /GS cookie offset if no alignment present
funcInfoAlign           ENDS
offsetAlignStack        __int32 ?	;; Offset from frame pointer before alignment
endif
if defined(_M_ARM) OR defined(_M_MIPS) OR defined(_M_SH)
gs_cookie_offset        __int32 ?	;; (optional) Offset from the (aligned) FP of the /GS cookie
endif
FuncInfo                ENDS
endif ;; WANT_NO_TYPES

FUNC_MAGICNUM macro fi
	exitm<((fi).magicNumber)>
	endm
FUNC_MAXSTATE macro fi
	exitm<((fi).maxState)>
	endm
FUNC_NTRYBLOCKS macro fi
	exitm<((fi).nTryBlocks)>
	endm
FUNC_NIPMAPENT macro fi
	exitm<((fi).nIPMapEntries)>
	endm
FUNC_FLAGS macro fi
	exitm<((fi).EHFlags)>
	endm
if _EH_RELATIVE_OFFSETS
FUNC_PUNWINDMAP macro fi,ib
	exitm<((UnwindMapEntry*)((ib) + (fi).dispUnwindMap))>
	endm
FUNC_PHANDLERMAP macro fi,ib
	exitm<((TryBlockMapEntry*)((ib) + (fi).dispTryBlockMap))>
	endm
FUNC_IPMAP macro fi,ib
	exitm<((IptoStateMapEntry*)((ib) + (fi).dispIPtoStateMap))>
	endm
FUNC_UNWIND macro fi,st,ib
	exitm<(FUNC_PUNWINDMAP(fi,ib)[st])>
	endm
FUNC_PUNWIND macro fi,st,ib
	exitm<( AND FUNC_UNWIND(fi,st,ib))>
	endm
FUNC_TRYBLOCK macro fi,n,ib
	exitm<(FUNC_PHANDLERMAP(fi,ib)[n])>
	endm
FUNC_PTRYBLOCK macro fi,n,ib
	exitm<( AND FUNC_TRYBLOCK(fi,n,ib))>
	endm
FUNC_ESTYPES_IB macro fi, ib
	exitm<((ESTypeList*)((ib) + (fi).dispESTypeList))>
	endm
FUNC_PESTYPES_IB macro fi, ib
	exitm<FUNC_ESTYPES_IB((*fi), ib)>
	endm
else
FUNC_PUNWINDMAP macro fi
	exitm<((fi).pUnwindMap)>
	endm
FUNC_PHANDLERMAP macro fi
	exitm<((fi).pTryBlockMap)>
	endm
FUNC_IPMAP macro fi
	exitm<((fi).pIPtoStateMap)>
	endm
FUNC_UNWIND macro fi, st
	exitm<((fi).pUnwindMap[st])>
	endm
FUNC_PUNWIND macro fi, st
	exitm<( AND FUNC_UNWIND(fi, st))>
	endm
FUNC_TRYBLOCK macro fi,n
	exitm<((fi).pTryBlockMap[n])>
	endm
FUNC_PTRYBLOCK macro fi,n
	exitm<( AND FUNC_TRYBLOCK(fi, n))>
	endm
FUNC_ESTYPES macro fi
	exitm<((fi).pESTypeList)>
	endm
FUNC_PESTYPES macro fi
	exitm<(FUNC_ESTYPES(*fi))>
	endm
endif
if defined(_M_ALPHA)
FUNC_EHCONTEXTDELTA macro fi
	exitm<((fi).EHContextDelta)>
	endm
endif
if _M_MRX000 GE 4000		 ;;IFSTRIP=IGN
FUNC_IPTOSTATE macro fi,n
	exitm<((fi).pIPtoStateMap[n])>
	endm
FUNC_PIPTOSTATE macro fi,n
	exitm<( AND FUNC_IPTOSTATE(fi,n))>
	endm
FUNC_DISPUNWINDHELP macro fi
	exitm<((fi).dispUnwindHelp)>
	endm
FUNC_TRYBLOCKINDEX macro fi
	exitm<((fi).iTryBlockIndex)>
	endm
FUNC_FRAMENEST macro fi
	exitm<((fi).iFrameNestLevel)>
	endm
elif defined(_M_MPPC) OR defined(_M_PPC) OR (defined(_M_ARM) AND NOT defined(_M_ARM_NT))
FUNC_IPTOSTATE macro fi,n
	exitm<((fi).pIPtoStateMap[n])>
	endm
FUNC_PIPTOSTATE macro fi,n
	exitm<( AND FUNC_IPTOSTATE(fi,n))>
	endm
elif _EH_RELATIVE_OFFSETS
FUNC_IPTOSTATE macro fi,n,ib
	exitm<(FUNC_IPMAP(fi,ib)[n])>
	endm
FUNC_PIPTOSTATE macro fi,n,ib
	exitm<( AND FUNC_IPTOSTATE(fi,n,ib))>
	endm
FUNC_DISPUNWINDHELP macro fi
	exitm<((fi).dispUwindHelp)>
	endm
else
FUNC_IPTOSTATE macro fi,n
	exitm<__ERROR_NYI__>
	endm
endif
if defined(_M_ARM)
FUNC_STKALIGN macro fi
	exitm<((fi).alignStack)>
	endm
FUNC_OFFSTKALIGN macro fi
	exitm<((fi).offsetAlignStack)>
	endm
endif

endif ;; _EHDATA_NOFUNCINFO 

ifndef _EHDATA_NONT

;;///////////////////////////////////////////////////////////////////////////
;;
;; Data types that are variants of data used by NT (and Chicago) to manage
;; exception handling.
;;
;;---------------------------------------------------------------------------

;;///////////////////////////////////////////////////////////////////////////
;;
;; A stack registration node (i386 only)
;;

if defined(_M_IX86) AND _M_IX86 GE 300 ;;IFSTRIP=IGN

                        typedef EHRegistrationNode
EHRegistrationNode      typedef EHRegistrationNode

EHRegistrationNode      STRUC
;; void *			stackPtr 
pNext                   LPEHRegistrationNode ?	;; Next node in the chain
				frameHandler        LPvoid ?	;; The handler function for this frame
state                   __ehstate_t ?	;; The current state of this function
if CC_EXPLICITFRAME
				frame               LPvoid ?	;; Value of ebp for this frame
endif
                        ENDS

if NOT CC_EXPLICITFRAME
				;; Cannonical offset
 define FRAME_OFFSET	sizeof(EHRegistrationNode)
endif

PRN_NEXT macro prn
	exitm<((prn)- GT pNext)>
	endm
PRN_HANDLER macro prn
	exitm<((prn)- GT frameHandler)>
	endm
PRN_STATE macro prn
	exitm<((prn)- GT state)>
	endm
PRN_STACK macro prn
	exitm<(((void**)(prn))[-1])>
	endm
if CC_EXPLICITFRAME
 define PRN_FRAME(prn)		((prn)- GT frame)
else
 define PRN_FRAME(prn)		((void*)(((char*)prn) + FRAME_OFFSET))
endif

;                       typedef void DispatcherContext;  Meaningless on Intel

elif _M_MRX000 GE 4000 ;;IFSTRIP=IGN
;;
;; On MIPS we don't have a registration node, just a pointer to the stack frame base
;;
EHRegistrationNode      typedef ULONG 

PRN_NEXT macro prn
	exitm<__ERROR__>
	endm
PRN_HANDLER macro prn
	exitm<__ERROR__>
	endm
PRN_STATE macro prn
	exitm<__ERROR__>
	endm
PRN_STACK macro prn
	exitm<__ERROR__>
	endm
PRN_FRAME macro prn
	exitm<__ERROR__>
	endm

FRAME_OFFSET            equ 0
if NOT defined(_NTSUBSET_)
RUNTIME_FUNCTION        STRUC
BeginAddress            ULONG ?	
EndAddress              ULONG ?	
(*ExceptionHandler)()   EXCEPTION_DISPOSITION ?	
HandlerData             PVOID ?	
PrologEndAddress        ULONG ?	
RUNTIME_FUNCTION        ENDS
PRUNTIME_FUNCTION       typedef ptr RUNTIME_FUNCTION
endif

xDISPATCHER_CONTEXT     STRUC
ControlPc               ULONG ?	
FunctionEntry           PRUNTIME_FUNCTION ?	
EstablisherFrame        ULONG ?	
ContextRecord           PCONTEXT ?	
DispatcherContext;					; ENDS

elif defined(_M_ARM) ;;IFSTRIP=IGN

PRN_NEXT macro prn
	exitm<__ERROR__>
	endm
PRN_HANDLER macro prn
	exitm<__ERROR__>
	endm
PRN_STATE macro prn
	exitm<__ERROR__>
	endm
PRN_STACK macro prn
	exitm<__ERROR__>
	endm
PRN_FRAME macro prn
	exitm<__ERROR__>
	endm

FRAME_OFFSET            equ 0

if NOT defined(_NTSUBSET_) AND NOT defined(_NTARMH_)
UNWIND_INFO             STRUC
__int16 Version         unsigned ?	;; Version Number
__int16 Flags           unsigned ?	;; Flags
__int32 DataLength      unsigned ?	;; Length of Descriptor Data
UNWIND_INFO             ENDS
PUNWIND_INFO            typedef ptr UNWIND_INFO

endif

xDISPATCHER_CONTEXT     STRUC
ControlPc               ULONG ?	
ImageBase               ULONG ?	
FunctionEntry           PRUNTIME_FUNCTION ?	
EstablisherFrame        ULONG ?	
TargetPc                ULONG ?	
ContextRecord           PCONTEXT ?	
LanguageHandler         PVOID ?	
HandlerData             PVOID ?	
HistoryTable            PVOID ?	
ScopeIndex              ULONG ?	
ControlPcIsUnwound      BOOLEAN ?	
NonVolatileRegisters    PUCHAR ?	
DispatcherContext;					; ENDS


;;
;; On ARM we don't have a registration node, just a pointer to the stack frame base
;;

EHRegistrationNode      typedef ULONG 

elif defined(_M_IA64) ;;IFSTRIP=IGN

PRN_NEXT macro prn
	exitm<__ERROR__>
	endm
PRN_HANDLER macro prn
	exitm<__ERROR__>
	endm
PRN_STATE macro prn
	exitm<__ERROR__>
	endm
PRN_STACK macro prn
	exitm<__ERROR__>
	endm
PRN_FRAME macro prn
	exitm<__ERROR__>
	endm

FRAME_OFFSET            equ 0

PUNWIND_HISTORY_TABLE   typedef UNWIND_HISTORY_TABLE*

xDISPATCHER_CONTEXT     STRUC
EstablisherFrame        FRAME_POINTERS ?	
ControlPc               __int64 ?	
ImageBase               __int64 ?	
FunctionEntry           PRUNTIME_FUNCTION ?	
ContextRecord           PCONTEXT ?	
HistoryTable            PUNWIND_HISTORY_TABLE ?	
__int64 TargetGp        unsigned ?	
Index                   dd ?	
DispatcherContext       ENDS

;;
;; On P7 we don't have a registration node, just a pointer to the stack frame base
;;
EHRegistrationNode      typedef FRAME_POINTERS 

elif defined(_M_AMD64);;IFSTRIP=IGN

PRN_NEXT macro prn
	exitm<__ERROR__>
	endm
PRN_HANDLER macro prn
	exitm<__ERROR__>
	endm
PRN_STATE macro prn
	exitm<__ERROR__>
	endm
PRN_STACK macro prn
	exitm<__ERROR__>
	endm
PRN_FRAME macro prn
	exitm<__ERROR__>
	endm

FRAME_OFFSET            equ 0

pragma warning (push)
pragma warning (disable: 4201)

if NOT defined(_NTSUBSET_) AND NOT defined(_NTAMD64_)
CodeOffset              typedef union _UNWIND_CODE { struct { unsigned char 
char UnwindOp : 4       unsigned ?	
char OpInfo : 4         unsigned ?	
                        ENDS
short FrameOffset       unsigned ?	
UNWIND_CODE             ENDS
PUNWIND_CODE            typedef ptr UNWIND_CODE
UNWIND_INFO             STRUC
char Version : 3        unsigned ?	;; Version Number
char Flags   : 5        unsigned ?	;; Flags
char SizeOfProlog       unsigned ?	
char CountOfCodes       unsigned ?	
FrameRegister : 4       unsigned ?	
FrameOffset   : 4       unsigned ?	
UnwindCode              UNWIND_CODE 1 dup(?)	
;;  UNWIND_CODE MoreUnwindCode[((CountOfCodes+1)&~1)-1];
;;  union {
;;      ULONG ExceptionHandler;
;;      ULONG FunctionEntry;
;;  };
;;  ULONG ExceptionData[];
;;
UNWIND_INFO             ENDS
PUNWIND_INFO            typedef ptr UNWIND_INFO
endif

pragma warning (pop)

PUNWIND_HISTORY_TABLE   typedef UNWIND_HISTORY_TABLE*

xDISPATCHER_CONTEXT     STRUC
ControlPc               __int64 ?	
ImageBase               __int64 ?	
FunctionEntry           PRUNTIME_FUNCTION ?	
EstablisherFrame        ULONG_PTR ?	
TargetIp                ULONG64 ?	
ContextRecord           PCONTEXT ?	
LanguageHandler         PVOID ?	
HandlerData             PVOID ?	
HistoryTable            PUNWIND_HISTORY_TABLE ?	
DispatcherContext;					; ENDS

;;
;; On P7 we don't have a registration node, just a pointer to the stack frame base
;;
EHRegistrationNode      typedef ULONG_PTR 

elif defined(_M_ARM64);;IFSTRIP=IGN

PRN_NEXT macro prn
	exitm<__ERROR__>
	endm
PRN_HANDLER macro prn
	exitm<__ERROR__>
	endm
PRN_STATE macro prn
	exitm<__ERROR__>
	endm
PRN_STACK macro prn
	exitm<__ERROR__>
	endm
PRN_FRAME macro prn
	exitm<__ERROR__>
	endm

FRAME_OFFSET            equ 0


pragma warning (push)
pragma warning (disable: 4201)

CodeOffset              typedef union _UNWIND_CODE { struct { unsigned char 
char UnwindOp : 4       unsigned ?	
char OpInfo : 4         unsigned ?	
                        ENDS
short FrameOffset       unsigned ?	
UNWIND_CODE             ENDS
PUNWIND_CODE            typedef ptr UNWIND_CODE

pragma warning (pop)
UNWIND_INFO             STRUC
char Version : 3        unsigned ?	;; Version Number
char Flags   : 5        unsigned ?	;; Flags
char SizeOfProlog       unsigned ?	
char CountOfCodes       unsigned ?	
FrameRegister : 4       unsigned ?	
FrameOffset   : 4       unsigned ?	
UnwindCode              UNWIND_CODE 1 dup(?)	
;;  UNWIND_CODE MoreUnwindCode[((CountOfCodes+1)&~1)-1];
;;  union {
;;      ULONG ExceptionHandler;
;;      ULONG FunctionEntry;
;;  };
;;  ULONG ExceptionData[];
;;
UNWIND_INFO             ENDS
PUNWIND_INFO            typedef ptr UNWIND_INFO

PUNWIND_HISTORY_TABLE   typedef UNWIND_HISTORY_TABLE*

xDISPATCHER_CONTEXT     STRUC
ControlPc               ULONG_PTR ?	
ImageBase               ULONG_PTR ?	
FunctionEntry           PRUNTIME_FUNCTION ?	
EstablisherFrame        ULONG_PTR ?	
TargetPc                ULONG_PTR ?	
ContextRecord           PCONTEXT ?	
LanguageHandler         PVOID ?	
HandlerData             PVOID ?	
HistoryTable            PUNWIND_HISTORY_TABLE ?	
ScopeIndex              dd ?	
ControlPcIsUnwound      BOOLEAN ?	
NonVolatileRegisters    PKNONVOLATILE_CONTEXT_POINTERS ?	
DispatcherContext;					; ENDS

;;
;; On P7 we don't have a registration node, just a pointer to the stack frame base
;;
EHRegistrationNode      typedef ULONG_PTR 

elif defined(_M_ALPHA)
;;
;; On Alpha we don't have a registration node,
;;     just a pointer to the stack frame base
;;
EHRegistrationNode      typedef ULONG_PTR 

PRN_NEXT macro prn
	exitm<__ERROR__>
	endm
PRN_HANDLER macro prn
	exitm<__ERROR__>
	endm
PRN_STATE macro prn
	exitm<__ERROR__>
	endm
PRN_STACK macro prn
	exitm<__ERROR__>
	endm
PRN_FRAME macro prn
	exitm<__ERROR__>
	endm

if defined(_M_ALPHA64)	 ;;IFSTRIP=IGN
pragma pack(push, EHContext, 8)
endif

FRAME_OFFSET            equ 0
if NOT defined(_NTSUBSET_)
RUNTIME_FUNCTION        STRUC
BeginAddress            ULONG_PTR ?	
EndAddress              ULONG_PTR ?	
(*ExceptionHandler)()   EXCEPTION_DISPOSITION ?	
HandlerData             PVOID ?	;; ptr to FuncInfo record
PrologEndAddress        ULONG_PTR ?	
RUNTIME_FUNCTION        ENDS
PRUNTIME_FUNCTION       typedef ptr RUNTIME_FUNCTION
endif

xDISPATCHER_CONTEXT     STRUC
ControlPc               ULONG_PTR ?	
FunctionEntry           PRUNTIME_FUNCTION ?	
EstablisherFrame        ULONG_PTR ?	;; Virtual Frame Pointer
ContextRecord           PCONTEXT ?	
DispatcherContext;            ; ENDS

;;
;; _EHCONTEXT is a struct built in the frame by the compiler.
;; On entry to a function, compiler generated code stores the
;; address of the base of the fixed frame area (the so-called
;; Real Frame Pointer) into the Rfp. On every state transition,
;; compiler generated code stores the current state index into
;; the State field.
;;
;; The FuncInfo record for the function contains the offset of
;; the _EHCONTEXT record from the Virtual Frame Pointer - a
;; pointer to the highest address of the frame so this offset
;; is negative (frames grow down in the address space).
;;
EHCONTEXT               STRUC
State                   ULONG ?	
Rfp                     PVOID ?	
EHContext               ENDS
if defined(_M_ALPHA64)	 ;;IFSTRIP=IGN
pragma pack(pop, EHContext)
endif

VIRTUAL_FP macro pDC
	exitm<(pDC- GT EstablisherFrame)>
	endm

REAL_FP macro VirtualFP, pFuncInfo
	exitm<\>
	endm
)((char *)VirtualFP           \ LP(((EHContext ?
pFuncInfo->EHContextDelta)) -> Rfp) + ?

EH_STATE macro VirtualFP, pFuncInfo
	exitm<\>
	endm
)((char *)VirtualFP           \ LP(((EHContext ?
pFuncInfo->EHContextDelta)) -> State) + ?

elif defined(_M_M68K)
EHRegistrationNode      STRUC
;;	void * 				_sp;			;; The stack pointer for the entry of try/catch	
				frameHandler        LPvoid ?	;; The handler function for this frame
state                   __ehstate_t ?	;; The current state of this function
                        ENDS

PRN_HANDLER macro prn
	exitm<((prn)- GT frameHandler)>
	endm
PRN_STATE macro prn
	exitm<((prn)- GT state)>
	endm

;                       typedef void DispatcherContext;  Meaningless on Mac


elif defined(_M_PPC) OR defined(_M_MPPC)
;;
;; On PowerPC we don't have a registration node, just a pointer to the stack
;; frame base
;;
EHRegistrationNode      typedef ULONG 

PRN_NEXT macro prn
	exitm<__ERROR__>
	endm
PRN_HANDLER macro prn
	exitm<__ERROR__>
	endm
PRN_STATE macro prn
	exitm<__ERROR__>
	endm
PRN_STACK macro prn
	exitm<__ERROR__>
	endm
PRN_FRAME macro prn
	exitm<__ERROR__>
	endm

FRAME_OFFSET            equ 0

if NOT defined(_NTSUBSET_)
RUNTIME_FUNCTION        STRUC
BeginAddress            ULONG ?	
EndAddress              ULONG ?	
(*ExceptionHandler)(...) EXCEPTION_DISPOSITION ?	
HandlerData             PVOID ?	
PrologEndAddress        ULONG ?	
RUNTIME_FUNCTION        ENDS
PRUNTIME_FUNCTION       typedef ptr RUNTIME_FUNCTION
endif

xDISPATCHER_CONTEXT     STRUC
ControlPc               ULONG ?	
FunctionEntry           PRUNTIME_FUNCTION ?	
EstablisherFrame        ULONG ?	
ContextRecord           PCONTEXT ?	
DispatcherContext       ENDS
    ;; changed the case of the name to conform to EH conventions

if defined(_M_MPPC)
ftinfo                  STRUC
dwMagicNumber           ULONG ?	;; magic number
pFrameInfo              LPvoid ?	;; pointer to runtime frame info
rgFuncTable             PRUNTIME_FUNCTION ?	;; function table
cFuncTable              ULONG ?	;; number of function entry
dwEntryCF               ULONG ?	;; address of starting of the code fragment
dwSizeCF                ULONG ?	;; size of the code fragment
FTINFO                  ENDS
PFTINFO                 typedef ptr FTINFO

offsFTINFO              equ 64
endif

else
error "Machine not supported"
endif

;;///////////////////////////////////////////////////////////////////////////
;;
;; The NT Exception record that we use to pass information from the throw to
;; the possible catches.
;;
;; The constants in the comments are the values we expect.
;; This is based on the definition of EXCEPTION_RECORD in winnt.h.
;;
if defined(_M_IA64) OR defined(_M_ALPHA64) OR defined(_M_AMD64) OR defined(_M_ARM64) ;;IFSTRIP=IGN
pragma pack(push, EHExceptionRecord, 8)
endif
ifndef WANT_NO_TYPES
EHExceptionRecord       STRUC
ExceptionCode           dd ?	;; The code of this exception. (= EH_EXCEPTION_NUMBER)
ExceptionFlags          dd ?	;; Flags determined by NT
ExceptionRecord         typedef ptr EXCEPTION_RECORD
 		ExceptionAddress     LPvoid ?	;; Address at which exception occurred
NumberParameters        dd ?	;; Number of extended parameters. (= EH_EXCEPTION_PARAMETERS)
EHParameters            STRUC
magicNumber             dd ?	;; = EH_MAGIC_NUMBER1
		pExceptionObject      LPvoid ?	;; Pointer to the actual object thrown
pThrowInfo              LPThrowInfo ?	;; Description of thrown object
if _EH_RELATIVE_OFFSETS
pThrowImageBase         LPvoid ?	;; Image base of thrown object
endif
params                  ENDS
EHExceptionRecord       ENDS
endif ;; WANT_NO_TYPES
if defined(_M_IA64) OR defined(_M_ALPHA64) OR defined(_M_AMD64) OR defined(_M_ARM64) ;;IFSTRIP=IGN
pragma pack(pop, EHExceptionRecord)
endif

PER_CODE macro per
	exitm<((per)- GT ExceptionCode)>
	endm
PER_FLAGS macro per
	exitm<((per)- GT ExceptionFlags)>
	endm
PER_NEXT macro per
	exitm<((per)- GT ExceptionRecord)>
	endm
PER_ADDRESS macro per
	exitm<((per)- GT ExceptionAddress)>
	endm
PER_NPARAMS macro per
	exitm<((per)- GT NumberParameters)>
	endm
PER_MAGICNUM macro per
	exitm<((per)- GT params.magicNumber)>
	endm
PER_PEXCEPTOBJ macro per
	exitm<((per)- GT params.pExceptionObject)>
	endm
PER_PTHROW macro per
	exitm<((per)- GT params.pThrowInfo)>
	endm
PER_EXCEPTINFO macro per
	exitm<((PULONG_PTR) AND (PER_MAGICNUM(per)))>
	endm
if _EH_RELATIVE_OFFSETS
PER_PTHROWIB macro per
	exitm<((per)- GT params.pThrowImageBase)>
	endm
endif
PER_THROW macro per
	exitm<(*PER_PTHROW(per))>
	endm

PER_ISSIMPLETYPE macro t
	exitm<(PER_THROW(t).isSimpleType)>
	endm
PER_ISREFERENCE macro t
	exitm<(PER_THROW(t).isReference)>
	endm
PER_ISCONST macro t
	exitm<(PER_THROW(t).isConst)>
	endm
PER_ISVOLATILE macro t
	exitm<(PER_THROW(t).isVolatile)>
	endm
PER_ISUNALIGNED macro t
	exitm<(PER_THROW(t).isUnaligned)>
	endm
PER_UNWINDFUNC macro t
	exitm<(PER_THROW(t).pmfnUnwind)>
	endm
PER_PCTLIST macro t
	exitm<(PER_THROW(t).pCatchable)>
	endm
PER_CTLIST macro t
	exitm<(*PER_PCTLIST(t))>
	endm

if defined(_M_CEE_PURE)
PER_IS_MSVC_EH macro per
	exitm<((PER_CODE(per) EQ EH_EXCEPTION_NUMBER) AND \>
	endm
== EH_EXCEPTION_PARAMETERS) &&	\ (PER_NPARAMS(per) ?
== EH_PURE_MAGIC_NUMBER1) ||	\ ((PER_MAGICNUM(per) ?
== NULL))               PER_PTHROW(per) ?
else
PER_IS_MSVC_EH macro per
	exitm<((PER_CODE(per) EQ EH_EXCEPTION_NUMBER) AND \>
	endm
== EH_EXCEPTION_PARAMETERS) &&	\ (PER_NPARAMS(per) ?
== EH_MAGIC_NUMBER1) ||   \ ((PER_MAGICNUM(per) ?
== EH_MAGIC_NUMBER2) ||   \ (PER_MAGICNUM(per) ?
== EH_MAGIC_NUMBER3)))  (PER_MAGICNUM(per) ?
endif

PER_IS_MSVC_PURE_OR_NATIVE_EH macro per
	exitm<\>
	endm
== EH_EXCEPTION_NUMBER) && 			\ ((PER_CODE(per) ?
== EH_EXCEPTION_PARAMETERS) &&	\ (PER_NPARAMS(per) ?
== EH_MAGIC_NUMBER1) ||   \ ((PER_MAGICNUM(per) ?
== EH_MAGIC_NUMBER2) ||   \ (PER_MAGICNUM(per) ?
== EH_MAGIC_NUMBER3) ||   \ (PER_MAGICNUM(per) ?
== EH_PURE_MAGIC_NUMBER1))) (PER_MAGICNUM(per) ?

;;///////////////////////////////////////////////////////////////////////////
;;
;; NT kernel routines and definitions required to implement exception handling:
;;
;; (from ntxcapi.h, which is not a public header file)
;;
;;---------------------------------------------------------------------------


endif ;; _EHDATA_NONT 

endif ;; ONLY_VALUES 

pragma pack(pop, ehdata)

endif ;; _INC_EHDATA 

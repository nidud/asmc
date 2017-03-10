ifndef _OLEAUTO_H_
.xlist
_OLEAUTO_H_ equ 1

;; Set packing to 8 for ISV, and Win95 support
;;#include <pshpack8.h>
;;  Definition of the OLE Automation APIs, and macros.

ifdef __PE__
option	dllimport:<oleaut32>
endif

externdef		IID_StdOle:IID

STDOLE_MAJORVERNUM	equ 0x1
STDOLE_MINORVERNUM	equ 0x0
STDOLE_LCID		equ 0x0000

;; Version # of stdole2.tlb
STDOLE2_MAJORVERNUM	equ 0x2
STDOLE2_MINORVERNUM	equ 0x0
STDOLE2_LCID		equ 0x0000

;; if not already picked up from olenls.h
ifndef _LCID_DEFINED
LCID			typedef DWORD
_LCID_DEFINED		equ 1
endif

ifndef BEGIN_INTERFACE
BEGIN_INTERFACE		equ <>
END_INTERFACE		equ <>
endif

;; pull in the MIDL generated header
include oaidl.inc
.xlist

;;---------------------------------------------------------------------
;;			      BSTR API
;;---------------------------------------------------------------------

;WINOLEAUTAPI_(BSTR)
SysAllocString proto _CType \
		      : ptr OLECHAR

;WINOLEAUTAPI_(INT)
SysReAllocString proto _CType \
		      : ptr BSTR,
		      : ptr OLECHAR

;WINOLEAUTAPI_(BSTR)
SysAllocStringLen proto _CType \
		      : ptr OLECHAR,
		      : UINT

;WINOLEAUTAPI_(INT)
SysReAllocStringLen proto _CType \
		      : ptr BSTR,
		      : ptr OLECHAR,
		      : UINT

;WINOLEAUTAPI_(void)
SysFreeString proto _CType \
		      : ptr BSTR

;WINOLEAUTAPI_(UINT)
SysStringLen proto _CType \
		      : ptr BSTR
ifdef _WIN32
;WINOLEAUTAPI_(UINT)
SysStringByteLen proto _CType \
		  bstr: BSTR

;WINOLEAUTAPI_(BSTR)
SysAllocStringByteLen proto _CType \
		   psz: LPCSTR,
		   len: UINT

endif

;;---------------------------------------------------------------------
;;			      Time API
;;---------------------------------------------------------------------

;WINOLEAUTAPI_(INT)
DosDateTimeToVariantTime proto _CType \
	      wDosDate: USHORT,
	      wDosTime: USHORT,
		pvtime: ptr DOUBLE


;WINOLEAUTAPI_(INT)
VariantTimeToDosDateTime proto _CType \
		 vtime: DOUBLE,
	     pwDosDate: ptr USHORT,
	     pwDosTime: ptr USHORT


ifdef _WIN32
;WINOLEAUTAPI_(INT)
SystemTimeToVariantTime proto _CType \
	  lpSystemTime: LPSYSTEMTIME,
		pvtime: ptr DOUBLE

;WINOLEAUTAPI_(INT)
VariantTimeToSystemTime proto _CType \
		 vtime: DOUBLE,
	  lpSystemTime: LPSYSTEMTIME

endif


;;---------------------------------------------------------------------
;;			    SafeArray API
;;---------------------------------------------------------------------

;WINOLEAUTAPI
SafeArrayAllocDescriptor proto _CType \
		 cDims: UINT,
	       ppsaOut: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayAllocDescriptorEx proto _CType \
		    vt: VARTYPE,
		 cDims: UINT,
	       ppsaOut: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayAllocData proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI_(SAFEARRAY
SafeArrayCreate proto _CType \
		    vt: VARTYPE,
		 cDims: UINT,
	     rgsabound: ptr SAFEARRAYBOUND

;WINOLEAUTAPI_(SAFEARRAY
SafeArrayCreateEx proto _CType \
		    vt: VARTYPE,
		 cDims: UINT,
	     rgsabound: ptr SAFEARRAYBOUND,
	       pvExtra: PVOID

;WINOLEAUTAPI
SafeArrayCopyData proto _CType \
	     psaSource: ptr SAFEARRAY,
	     psaTarget: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayDestroyDescriptor proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayDestroyData proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayDestroy proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayRedim proto _CType \
		   psa: ptr SAFEARRAY,
	   psaboundNew: ptr SAFEARRAYBOUND

;WINOLEAUTAPI_(UINT)
SafeArrayGetDim proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI_(UINT)
SafeArrayGetElemsize proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayGetUBound proto _CType \
		   psa: ptr SAFEARRAY,
		  nDim: UINT,
	      plUbound: ptr LONG

;WINOLEAUTAPI
SafeArrayGetLBound proto _CType \
		   psa: ptr SAFEARRAY,
		  nDim: UINT,
	      plLbound: ptr LONG

;WINOLEAUTAPI
SafeArrayLock proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayUnlock proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayAccessData proto _CType \
		   psa: ptr SAFEARRAY,
	       ppvData: PVOID

;WINOLEAUTAPI
SafeArrayUnaccessData proto _CType \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayGetElement proto _CType \
		   psa: ptr SAFEARRAY,
	     rgIndices: ptr LONG,
		    pv: PVOID

;WINOLEAUTAPI
SafeArrayPutElement proto _CType \
		   psa: ptr SAFEARRAY,
	     rgIndices: ptr LONG,
		    pv: PVOID

;WINOLEAUTAPI
SafeArrayCopy proto _CType \
		   psa: ptr SAFEARRAY,
	       ppsaOut: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayPtrOfIndex proto _CType \
		   psa: ptr SAFEARRAY,
	     rgIndices: ptr LONG,
	       ppvData: PVOID

;WINOLEAUTAPI
SafeArraySetRecordInfo proto _CType \
		   psa: ptr SAFEARRAY,
		prinfo: ptr IRecordInfo

;WINOLEAUTAPI
SafeArrayGetRecordInfo proto _CType \
		   psa: ptr SAFEARRAY,
		prinfo: ptr IRecordInfo

;WINOLEAUTAPI
SafeArraySetIID proto _CType \
		   psa: ptr SAFEARRAY,
		  guid: REFGUID

;WINOLEAUTAPI
SafeArrayGetIID proto _CType \
		   psa: ptr SAFEARRAY,
		 pguid: ptr GUID

;WINOLEAUTAPI
SafeArrayGetVartype proto _CType \
		   psa: ptr SAFEARRAY,
		   pvt: ptr VARTYPE

;WINOLEAUTAPI_(SAFEARRAY
SafeArrayCreateVector proto _CType \
		    vt: VARTYPE,
	       lLbound: LONG,
	     cElements: ULONG

;WINOLEAUTAPI_(SAFEARRAY
SafeArrayCreateVectorEx proto _CType \
		    vt: VARTYPE,
	       lLbound: LONG,
	     cElements: ULONG,
	       pvExtra: PVOID


;;---------------------------------------------------------------------
;;			     VARIANT API
;;---------------------------------------------------------------------

;WINOLEAUTAPI_(void)
VariantInit proto _CType \
		 pvarg: ptr VARIANTARG

;WINOLEAUTAPI
VariantClear proto _CType \
		 pvarg: ptr VARIANTARG

;WINOLEAUTAPI
VariantCopy proto _CType \
	     pvargDest: ptr VARIANTARG,
	      pvargSrc: ptr VARIANTARG

;WINOLEAUTAPI
VariantCopyInd proto _CType \
	      pvarDest: ptr VARIANT,
	      pvargSrc: ptr VARIANTARG

;WINOLEAUTAPI
VariantChangeType proto _CType \
	     pvargDest: ptr VARIANTARG,
	       pvarSrc: ptr VARIANTARG,
		wFlags: USHORT,
		    vt: VARTYPE

;WINOLEAUTAPI
VariantChangeTypeEx proto _CType \
	     pvargDest: ptr VARIANTARG,
	       pvarSrc: ptr VARIANTARG,
		  lcid: LCID,
		wFlags: USHORT,
		    vt: VARTYPE


;; Flags for VariantChangeType/VariantChangeTypeEx
VARIANT_NOVALUEPROP	equ 0x1
VARIANT_ALPHABOOL	equ 0x2 ;; For VT_BOOL to VT_BSTR conversions,
				;; convert to "True"/"False" instead of
				;; "-1"/"0"
VARIANT_NOUSEROVERRIDE	equ 0x4 ;; For conversions to/from VT_BSTR,
					;; passes LOCALE_NOUSEROVERRIDE
					;; to core coercion routines
VARIANT_LOCALBOOL	equ 0x8 ;; For VT_BOOL to VT_BSTR and back,
				;; convert to local language rather than
				;; English

;;---------------------------------------------------------------------
;;		  Vector <-> Bstr conversion APIs
;;---------------------------------------------------------------------

;WINOLEAUTAPI
VectorFromBstr proto _CType \
		  bstr: BSTR,
		  ppsa: ptr SAFEARRAY

;WINOLEAUTAPI
BstrFromVector proto _CType \
		   psa: ptr SAFEARRAY,
		 pbstr: ptr BSTR



;;---------------------------------------------------------------------
;;		       VARTYPE Coercion API
;;---------------------------------------------------------------------

;; Note: The routines that convert *from* a string are defined
;; to take a OLECHAR* rather than a BSTR because no allocation is
;; required, and this makes the routines a bit more generic.
;; They may of course still be passed a BSTR as the strIn param.
;;

;; Any of the coersion functions that converts either from or to a string
;; takes an additional lcid and dwFlags arguments. The lcid argument allows
;; locale specific parsing to occur.  The dwFlags allow additional function
;; specific condition to occur.	 All function that accept the dwFlags argument
;; can include either 0 or LOCALE_NOUSEROVERRIDE flag. In addition, the
;; VarDateFromStr and VarBstrFromDate functions also accept the
;; VAR_TIMEVALUEONLY and VAR_DATEVALUEONLY flags
;;

VAR_TIMEVALUEONLY	equ 0x00000001	   ;; return time value
VAR_DATEVALUEONLY	equ 0x00000002	   ;; return date value

;; Booleans can optionally be accepted in localized form. Pass VAR_LOCALBOOL
;; into VarBoolFromStr and VarBstrFromBool to use localized boolean names
;;
VAR_LOCALBOOL		equ 0x00000010

;WINOLEAUTAPI
VarUI1FromI2 proto _CType \
		   sIn: SWORD,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromI4 proto _CType \
		   lIn: LONG,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromR4 proto _CType \
		 fltIn: FLOAT,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromR8 proto _CType \
		 dblIn: DOUBLE,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromCy proto _CType \
		  cyIn: CY,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromDate proto _CType \
		dateIn: DATE,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromBool proto _CType \
		boolIn: VARIANT_BOOL,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromI1 proto _CType \
		   cIn: CHAR,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromUI2 proto _CType \
		  uiIn: USHORT,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromUI4 proto _CType \
		  ulIn: ULONG,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromDec proto _CType \
		pdecIn: ptr DECIMAL,
		 pbOut: ptr BYTE


;WINOLEAUTAPI
VarI2FromUI1 proto _CType \
		   bIn: BYTE,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromI4 proto _CType \
		   lIn: LONG,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromR4 proto _CType \
		 fltIn: FLOAT,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromR8 proto _CType \
		 dblIn: DOUBLE,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromCy proto _CType \
		  cyIn: CY,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromDate proto _CType \
		dateIn: DATE,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromBool proto _CType \
		boolIn: VARIANT_BOOL,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromI1 proto _CType \
		   cIn: CHAR,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromUI2 proto _CType \
		  uiIn: USHORT,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromUI4 proto _CType \
		  ulIn: ULONG,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromDec proto _CType \
		pdecIn: ptr DECIMAL,
		 psOut: ptr SWORD


;WINOLEAUTAPI
VarI4FromUI1 proto _CType \
		   bIn: BYTE,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromI2 proto _CType \
		   sIn: SWORD,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromR4 proto _CType \
		 fltIn: FLOAT,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromR8 proto _CType \
		 dblIn: DOUBLE,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromCy proto _CType \
		  cyIn: CY,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromDate proto _CType \
		dateIn: DATE,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromBool proto _CType \
		boolIn: VARIANT_BOOL,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromI1 proto _CType \
		   cIn: CHAR,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromUI2 proto _CType \
		  uiIn: USHORT,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromUI4 proto _CType \
		  ulIn: ULONG,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromDec proto _CType \
		pdecIn: ptr DECIMAL,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromInt proto _CType \
		 intIn: SINT,
		 plOut: ptr LONG


;WINOLEAUTAPI
VarR4FromUI1 proto _CType \
		   bIn: BYTE,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromI2 proto _CType \
		   sIn: SWORD,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromI4 proto _CType \
		   lIn: LONG,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromR8 proto _CType \
		 dblIn: DOUBLE,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromCy proto _CType \
		  cyIn: CY,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromDate proto _CType \
		dateIn: DATE,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromBool proto _CType \
		boolIn: VARIANT_BOOL,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromI1 proto _CType \
		   cIn: CHAR,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromUI2 proto _CType \
		  uiIn: USHORT,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromUI4 proto _CType \
		  ulIn: ULONG,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromDec proto _CType \
		pdecIn: ptr DECIMAL,
	       pfltOut: ptr FLOAT


;WINOLEAUTAPI
VarR8FromUI1 proto _CType \
		   bIn: BYTE,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromI2 proto _CType \
		   sIn: SWORD,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromI4 proto _CType \
		   lIn: LONG,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromR4 proto _CType \
		 fltIn: FLOAT,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromCy proto _CType \
		  cyIn: CY,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromDate proto _CType \
		dateIn: DATE,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromBool proto _CType \
		boolIn: VARIANT_BOOL,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromI1 proto _CType \
		   cIn: CHAR,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromUI2 proto _CType \
		  uiIn: USHORT,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromUI4 proto _CType \
		  ulIn: ULONG,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromDec proto _CType \
		pdecIn: ptr DECIMAL,
	       pdblOut: ptr DOUBLE


;WINOLEAUTAPI
VarDateFromUI1 proto _CType \
		   bIn: BYTE,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromI2 proto _CType \
		   sIn: SWORD,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromI4 proto _CType \
		   lIn: LONG,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromR4 proto _CType \
		 fltIn: FLOAT,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromR8 proto _CType \
		 dblIn: DOUBLE,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromCy proto _CType \
		  cyIn: CY,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromBool proto _CType \
		boolIn: VARIANT_BOOL,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromI1 proto _CType \
		   cIn: CHAR,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromUI2 proto _CType \
		  uiIn: USHORT,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromUI4 proto _CType \
		  ulIn: ULONG,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromDec proto _CType \
		pdecIn: ptr DECIMAL,
	      pdateOut: ptr DATE


;WINOLEAUTAPI
VarCyFromUI1 proto _CType \
		   bIn: BYTE,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromI2 proto _CType \
		   sIn: SWORD,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromI4 proto _CType \
		   lIn: LONG,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromR4 proto _CType \
		 fltIn: FLOAT,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromR8 proto _CType \
		 dblIn: DOUBLE,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromDate proto _CType \
		dateIn: DATE,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromBool proto _CType \
		boolIn: VARIANT_BOOL,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromI1 proto _CType \
		   cIn: CHAR,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromUI2 proto _CType \
		  uiIn: USHORT,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromUI4 proto _CType \
		  ulIn: ULONG,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromDec proto _CType \
		pdecIn: ptr DECIMAL,
		pcyOut: ptr CY


;WINOLEAUTAPI
VarBstrFromUI1 proto _CType \
		  bVal: BYTE,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromI2 proto _CType \
		  iVal: SWORD,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromI4 proto _CType \
		   lIn: LONG,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromR4 proto _CType \
		 fltIn: FLOAT,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromR8 proto _CType \
		 dblIn: DOUBLE,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromCy proto _CType \
		  cyIn: CY,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromDate proto _CType \
		dateIn: DATE,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromBool proto _CType \
		boolIn: VARIANT_BOOL,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromI1 proto _CType \
		   cIn: CHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromUI2 proto _CType \
		  uiIn: USHORT,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromUI4 proto _CType \
		  ulIn: ULONG,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromDec proto _CType \
		pdecIn: ptr DECIMAL,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR


;WINOLEAUTAPI
VarBoolFromUI1 proto _CType \
		   bIn: BYTE,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromI2 proto _CType \
		   sIn: SWORD,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromI4 proto _CType \
		   lIn: LONG,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromR4 proto _CType \
		 fltIn: FLOAT,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromR8 proto _CType \
		 dblIn: DOUBLE,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromDate proto _CType \
		dateIn: DATE,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromCy proto _CType \
		  cyIn: CY,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromI1 proto _CType \
		   cIn: CHAR,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromUI2 proto _CType \
		  uiIn: USHORT,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromUI4 proto _CType \
		  ulIn: ULONG,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromDec proto _CType \
		pdecIn: ptr DECIMAL,
	      pboolOut: ptr VARIANT_BOOL


;WINOLEAUTAPI
VarI1FromUI1 proto _CType \
		   bIn: BYTE,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromI2 proto _CType \
		  uiIn: SWORD,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromI4 proto _CType \
		   lIn: LONG,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromR4 proto _CType \
		 fltIn: FLOAT,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromR8 proto _CType \
		 dblIn: DOUBLE,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromDate proto _CType \
		dateIn: DATE,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromCy proto _CType \
		  cyIn: CY,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromBool proto _CType \
		boolIn: VARIANT_BOOL,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromUI2 proto _CType \
		  uiIn: USHORT,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromUI4 proto _CType \
		  ulIn: ULONG,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromDec proto _CType \
		pdecIn: ptr DECIMAL,
		 pcOut: ptr CHAR


;WINOLEAUTAPI
VarUI2FromUI1 proto _CType \
		   bIn: BYTE,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromI2 proto _CType \
		  uiIn: SWORD,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromI4 proto _CType \
		   lIn: LONG,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromR4 proto _CType \
		 fltIn: FLOAT,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromR8 proto _CType \
		 dblIn: DOUBLE,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromDate proto _CType \
		dateIn: DATE,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromCy proto _CType \
		  cyIn: CY,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromBool proto _CType \
		boolIn: VARIANT_BOOL,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromI1 proto _CType \
		   cIn: CHAR,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromUI4 proto _CType \
		  ulIn: ULONG,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromDec proto _CType \
		pdecIn: ptr DECIMAL,
		puiOut: ptr USHORT


;WINOLEAUTAPI
VarUI4FromUI1 proto _CType \
		   bIn: BYTE,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromI2 proto _CType \
		  uiIn: SWORD,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromI4 proto _CType \
		   lIn: LONG,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromR4 proto _CType \
		 fltIn: FLOAT,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromR8 proto _CType \
		 dblIn: DOUBLE,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromDate proto _CType \
		dateIn: DATE,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromCy proto _CType \
		  cyIn: CY,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromBool proto _CType \
		boolIn: VARIANT_BOOL,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromI1 proto _CType \
		   cIn: CHAR,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromUI2 proto _CType \
		  uiIn: USHORT,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromDec proto _CType \
		pdecIn: ptr DECIMAL,
		pulOut: ptr ULONG


;WINOLEAUTAPI
VarDecFromUI1 proto _CType \
		   bIn: BYTE,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromI2 proto _CType \
		  uiIn: SWORD,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromI4 proto _CType \
		   lIn: LONG,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromR4 proto _CType \
		 fltIn: FLOAT,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromR8 proto _CType \
		 dblIn: DOUBLE,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromDate proto _CType \
		dateIn: DATE,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromCy proto _CType \
		  cyIn: CY,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromDisp proto _CType \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromBool proto _CType \
		boolIn: VARIANT_BOOL,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromI1 proto _CType \
		   cIn: CHAR,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromUI2 proto _CType \
		  uiIn: USHORT,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromUI4 proto _CType \
		  ulIn: ULONG,
	       pdecOut: ptr DECIMAL


VarUI4FromUI4 macro _in, pOut
	exitm<(*(pOut) = (_in))>
	endm
VarI4FromI4 macro _in, pOut
	exitm<(*(pOut) = (_in))>
	endm

VarUI1FromInt		equ <VarUI1FromI4>
VarUI1FromUint		equ <VarUI1FromUI4>
VarI2FromInt		equ <VarI2FromI4>
VarI2FromUint		equ <VarI2FromUI4>
;VarI4FromInt		equ <VarI4FromI4>
VarI4FromUint		equ <VarI4FromUI4>
VarR4FromInt		equ <VarR4FromI4>
VarR4FromUint		equ <VarR4FromUI4>
VarR8FromInt		equ <VarR8FromI4>
VarR8FromUint		equ <VarR8FromUI4>
VarDateFromInt		equ <VarDateFromI4>
VarDateFromUint		equ <VarDateFromUI4>
VarCyFromInt		equ <VarCyFromI4>
VarCyFromUint		equ <VarCyFromUI4>
VarBstrFromInt		equ <VarBstrFromI4>
VarBstrFromUint		equ <VarBstrFromUI4>
VarBoolFromInt		equ <VarBoolFromI4>
VarBoolFromUint		equ <VarBoolFromUI4>
VarI1FromInt		equ <VarI1FromI4>
VarI1FromUint		equ <VarI1FromUI4>
VarUI2FromInt		equ <VarUI2FromI4>
VarUI2FromUint		equ <VarUI2FromUI4>
VarUI4FromInt		equ <VarUI4FromI4>
VarUI4FromUint		equ <VarUI4FromUI4>
VarDecFromInt		equ <VarDecFromI4>
VarDecFromUint		equ <VarDecFromUI4>
VarIntFromUI1		equ <VarI4FromUI1>
VarIntFromI2		equ <VarI4FromI2>
VarIntFromI4		equ <VarI4FromI4>
VarIntFromR4		equ <VarI4FromR4>
VarIntFromR8		equ <VarI4FromR8>
VarIntFromDate		equ <VarI4FromDate>
VarIntFromCy		equ <VarI4FromCy>
VarIntFromStr		equ <VarI4FromStr>
VarIntFromDisp		equ <VarI4FromDisp>
VarIntFromBool		equ <VarI4FromBool>
VarIntFromI1		equ <VarI4FromI1>
VarIntFromUI2		equ <VarI4FromUI2>
VarIntFromUI4		equ <VarI4FromUI4>
VarIntFromDec		equ <VarI4FromDec>
VarIntFromUint		equ <VarI4FromUI4>
VarUintFromUI1		equ <VarUI4FromUI1>
VarUintFromI2		equ <VarUI4FromI2>
VarUintFromI4		equ <VarUI4FromI4>
VarUintFromR4		equ <VarUI4FromR4>
VarUintFromR8		equ <VarUI4FromR8>
VarUintFromDate		equ <VarUI4FromDate>
VarUintFromCy		equ <VarUI4FromCy>
VarUintFromStr		equ <VarUI4FromStr>
VarUintFromDisp		equ <VarUI4FromDisp>
VarUintFromBool		equ <VarUI4FromBool>
VarUintFromI1		equ <VarUI4FromI1>
VarUintFromUI2		equ <VarUI4FromUI2>
VarUintFromUI4		equ <VarUI4FromUI4>
VarUintFromDec		equ <VarUI4FromDec>
VarUintFromInt		equ <VarUI4FromI4>

;; Mac Note: On the Mac, the coersion functions support the
;; Symantec C++ calling convention for float/double. To support
;; float/double arguments compiled with the MPW C compiler,
;; use the following APIs to move MPW float/double values into
;; a VARIANT.
;;

;;---------------------------------------------------------------------
;;	      New VARIANT <-> string parsing functions
;;---------------------------------------------------------------------

NUMPARSE		STRUC
cDig			SINT ?
dwInFlags		ULONG ?
dwOutFlags		ULONG ?
cchUsed			SINT ?
nBaseShift		SINT ?
nPwr10			SINT ?
NUMPARSE		ENDS

;; flags used by both dwInFlags and dwOutFlags:
;;
NUMPRS_LEADING_WHITE	equ 0x0001
NUMPRS_TRAILING_WHITE	equ 0x0002
NUMPRS_LEADING_PLUS	equ 0x0004
NUMPRS_TRAILING_PLUS	equ 0x0008
NUMPRS_LEADING_MINUS	equ 0x0010
NUMPRS_TRAILING_MINUS	equ 0x0020
NUMPRS_HEX_OCT		equ 0x0040
NUMPRS_PARENS		equ 0x0080
NUMPRS_DECIMAL		equ 0x0100
NUMPRS_THOUSANDS	equ 0x0200
NUMPRS_CURRENCY		equ 0x0400
NUMPRS_EXPONENT		equ 0x0800
NUMPRS_USE_ALL		equ 0x1000
NUMPRS_STD		equ 0x1FFF

;; flags used by dwOutFlags only:
;;
NUMPRS_NEG		equ 0x10000
NUMPRS_INEXACT		equ 0x20000

;; flags used by VarNumFromParseNum to indicate acceptable result types:
;;
VTBIT_I1		equ (1 SHL VT_I1)
VTBIT_UI1		equ (1 SHL VT_UI1)
VTBIT_I2		equ (1 SHL VT_I2)
VTBIT_UI2		equ (1 SHL VT_UI2)
VTBIT_I4		equ (1 SHL VT_I4)
VTBIT_UI4		equ (1 SHL VT_UI4)
VTBIT_R4		equ (1 SHL VT_R4)
VTBIT_R8		equ (1 SHL VT_R8)
VTBIT_CY		equ (1 SHL VT_CY)
VTBIT_DECIMAL		equ (1 SHL VT_DECIMA)


;WINOLEAUTAPI
VarParseNumFromStr proto _CType \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	       pnumprs: ptr NUMPARSE,
		rgbDig: ptr BYTE


;WINOLEAUTAPI
VarNumFromParseNum proto _CType \
	       pnumprs: ptr NUMPARSE,
		rgbDig: ptr BYTE,
	      dwVtBits: ULONG,
		  pvar: ptr VARIANT


;;---------------------------------------------------------------------
;;		       VARTYPE Math API
;;---------------------------------------------------------------------

;STDAPI
VarAdd proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarAnd proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarCat proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarDiv proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarEqv proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarIdiv proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarImp proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarMod proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarMul proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarOr proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarPow proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarSub proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarXor proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT


;STDAPI
VarAbs proto _CType \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarFix proto _CType \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarInt proto _CType \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarNeg proto _CType \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarNot proto _CType \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT


;STDAPI
VarRound proto _CType \
		pvarIn: LPVARIANT,
	     cDecimals: SINT,
	    pvarResult: LPVARIANT


;STDAPI
VarCmp proto _CType \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
		  lcid: LCID



;; Decimal math
;;
;STDAPI
VarDecAdd proto _CType \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecDiv proto _CType \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecMul proto _CType \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecSub proto _CType \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL,
	    pdecResult: LPDECIMAL


;STDAPI
VarDecAbs proto _CType \
		pdecIn: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecFix proto _CType \
		pdecIn: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecInt proto _CType \
		pdecIn: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecNeg proto _CType \
		pdecIn: LPDECIMAL,
	    pdecResult: LPDECIMAL


;STDAPI
VarDecRound proto _CType \
		pdecIn: LPDECIMAL,
	     cDecimals: SINT,
	    pdecResult: LPDECIMAL


;STDAPI
VarDecCmp proto _CType \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL

;STDAPI
VarDecCmpR8 proto _CType \
	      pdecLeft: LPDECIMAL,
	      dblRight: DOUBLE



;; Currency math
;;
;STDAPI
VarCyAdd proto _CType \
		cyLeft: CY,
	       cyRight: CY,
	     pcyResult: LPCY

;STDAPI
VarCyMul proto _CType \
		cyLeft: CY,
	       cyRight: CY,
	     pcyResult: LPCY

;STDAPI
VarCyMulI4 proto _CType \
		cyLeft: CY,
		lRight: LONG,
	     pcyResult: LPCY

;STDAPI
VarCySub proto _CType \
		cyLeft: CY,
	       cyRight: CY,
	     pcyResult: LPCY


;STDAPI
VarCyAbs proto _CType \
		  cyIn: CY,
	     pcyResult: LPCY

;STDAPI
VarCyFix proto _CType \
		  cyIn: CY,
	     pcyResult: LPCY

;STDAPI
VarCyInt proto _CType \
		  cyIn: CY,
	     pcyResult: LPCY

;STDAPI
VarCyNeg proto _CType \
		  cyIn: CY,
	     pcyResult: LPCY


;STDAPI
VarCyRound proto _CType \
		  cyIn: CY,
	     cDecimals: SINT,
	     pcyResult: LPCY


;STDAPI
VarCyCmp proto _CType \
		cyLeft: CY,
	       cyRight: CY

;STDAPI
VarCyCmpR8 proto _CType \
		cyLeft: CY,
	      dblRight: DOUBLE



;; Misc support functions
;;
;STDAPI
VarBstrCat proto _CType \
	      bstrLeft: BSTR,
	     bstrRight: BSTR,
	   pbstrResult: LPBSTR

;STDAPI
VarBstrCmp proto _CType \
	      bstrLeft: BSTR,
	     bstrRight: BSTR,
		  lcid: LCID

;STDAPI
VarR8Pow proto _CType \
	       dblLeft: DOUBLE,
	      dblRight: DOUBLE,
	    pdblResult: ptr DOUBLE

;STDAPI
VarR4CmpR8 proto _CType \
	       fltLeft: FLOAT,
	      dblRight: DOUBLE

;STDAPI
VarR8Round proto _CType \
		 dblIn: DOUBLE,
	     cDecimals: SINT,
	    pdblResult: ptr DOUBLE



;; Compare results.  These are returned as a SUCCESS HResult.  Subtracting
;; one gives the usual values of -1 for Less Than, 0 for Equal To, +1 for
;; Greater Than.
;;
VARCMP_LT		equ 0
VARCMP_EQ		equ 1
VARCMP_GT		equ 2
VARCMP_NULL		equ 3

;; VT_HARDTYPE tells the compare routine that the argument is a literal or
;; otherwise declared of that specific type.  It causes comparison rules to
;; change. For example, if a hard-type string is compared to a variant (not hard
;; -type) number, the number is converted to string.  If a hard-type number is
;; compared to a variant string, the string is converted to number.  If they're
;; both variant, then number < string.
VT_HARDTYPE		equ VT_RESERVED

;;---------------------------------------------------------------------
;;		     New date functions
;;---------------------------------------------------------------------

VAR_VALIDDATE		equ 0x0004    ;; VarDateFromUdate() only
VAR_CALENDAR_HIJRI	equ 0x0008    ;; use Hijri calender
VARIANT_CALENDAR_HIJRI	equ VAR_CAENDAR_HIJRI

;; The UDATE structure is used with VarDateFromUdate() and VarUdateFromDate().
;; It represents an "unpacked date".
;;
UDATE			STRUC
_st			SYSTEMTIME <>
wDayOfYear		dw ?
UDATE			ENDS

;; APIs to "pack" and "unpack" dates.
;;
;WINOLEAUTAPI
VarDateFromUdate proto _CType \
	      pudateIn: ptr UDATE,
	       dwFlags: ULONG,
	      pdateOut: ptr DATE


;WINOLEAUTAPI
VarUdateFromDate proto _CType \
		dateIn: DATE,
	       dwFlags: ULONG,
	     pudateOut: ptr UDATE


;; API to retrieve the secondary(altername) month names
;; Useful for Hijri, Polish and Russian alternate month names
;;
;WINOLEAUTAPI
GetAltMonthNames proto _CType \
		  lcid: LCID,
		  prgp: ptr LPOLESTR


;;---------------------------------------------------------------------
;;		   Format
;;---------------------------------------------------------------------

;; NOTE: dwFlags currently only accepts VAR_CALENDAR_HIJRI and
;; VAR_FORMAT_NOSUBSTITUTE

;; When passed into VarFormat and VarFormatFromTokens, prevents substitution
;; of formats in the case where a string is passed in that can not be
;; coverted into the desired type. (for ex, 'Format("Hello", "General Number")')
VAR_FORMAT_NOSUBSTITUTE equ 0x00000010

;WINOLEAUTAPI
VarFormat proto _CType \
		pvarIn: LPVARIANT,
	    pstrFormat: LPOLESTR,
	     iFirstDay: SINT,
	    iFirstWeek: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatDateTime proto _CType \
		pvarIn: LPVARIANT,
	  iNamedFormat: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatNumber proto _CType \
		pvarIn: LPVARIANT,
	       iNumDig: SINT,
	      iIncLead: SINT,
	    iUseParens: SINT,
		iGroup: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatPercent proto _CType \
		pvarIn: LPVARIANT,
	       iNumDig: SINT,
	      iIncLead: SINT,
	    iUseParens: SINT,
		iGroup: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatCurrency proto _CType \
		pvarIn: LPVARIANT,
	       iNumDig: SINT,
	      iIncLead: SINT,
	    iUseParens: SINT,
		iGroup: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR


;WINOLEAUTAPI
VarWeekdayName proto _CType \
	      iWeekday: SINT,
	       fAbbrev: SINT,
	     iFirstDay: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarMonthName proto _CType \
		iMonth: SINT,
	       fAbbrev: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR


;WINOLEAUTAPI
VarFormatFromTokens proto _CType \
		pvarIn: LPVARIANT,
	    pstrFormat: LPOLESTR,
	      pbTokCur: LPBYTE,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR,
		  lcid: LCID

;WINOLEAUTAPI_(LPBYTE)
VarTokenizeFormatString proto _CType \
	    pstrFormat: LPOLESTR,
		rgbTok: LPBYTE,
		 cbTok: SINT,
	     iFirstDay: SINT,
	    iFirstWeek: SINT,
		  lcid: LCID



;;---------------------------------------------------------------------
;;		   ITypeLib
;;---------------------------------------------------------------------

LPTYPELIB		typedef ptr ITypeLib


;;---------------------------------------------------------------------
;;		  ITypeInfo
;;---------------------------------------------------------------------


DISPID			typedef LONG
MEMBERID		typedef DISPID

MEMBERID_NIL		equ DISPID_UNKNOWN
ID_DEFAULTINST		equ -2


;; Flags for IDispatch::Invoke
DISPATCH_METHOD		equ 0x1
DISPATCH_PROPERTYGET	equ 0x2
DISPATCH_PROPERTYPUT	equ 0x4
DISPATCH_PROPERTYPUTREF equ 0x8

LPTYPEINFO		typedef ptr ITypeInfo


;;---------------------------------------------------------------------
;;		  ITypeComp
;;---------------------------------------------------------------------

LPTYPECOMP		typedef ptr ITypeComp


;;---------------------------------------------------------------------
;;	       ICreateTypeLib
;;---------------------------------------------------------------------

LPCREATETYPELIB		typedef ptr ICreateTypeLib

LPCREATETYPEINFO	typedef ptr ICreateTypeInfo

;;---------------------------------------------------------------------
;;	       TypeInfo API
;;---------------------------------------------------------------------

;; compute a 16bit hash value for the given name
;;
ifdef _WIN32
;WINOLEAUTAPI_(ULONG)
LHashValOfNameSysA proto _CType \
	       syskind: SYSKIND,
		  lcid: LCID,
		szName: LPCSTR
endif

LHashValOfNameSys proto _CType \
	       syskind: SYSKIND,
		  lcid: LCID,
		szName: ptr OLECHAR

LHashValOfName macro lcid, szName
	exitm<LHashValOfNameSys(SYS_WIN32, lcid, szName)>
	endm

WHashValOfLHashVal macro lhashval
	exitm<0x0000ffff AND lhashval>
	endm

IsHashValCompatible macro lhashval1, lhashval2
	exitm<(((0x00ff0000 AND (lhashval1)) EQ (0x00ff0000 AND (lhashval2))))>
	endm

;; load the typelib from the file with the given filename
;;
;WINOLEAUTAPI
LoadTypeLib proto _CType \
		szFile: ptr OLECHAR,
		pptlib: ptr ITypeLib


;; Control how a type library is registered
;;

REGKIND			typedef SDWORD
REGKIND_DEFAULT		equ 0
REGKIND_REGISTER	equ 1
REGKIND_NONE		equ 2

;WINOLEAUTAPI
LoadTypeLibEx proto _CType \
		szFile: LPCOLESTR,
	       regkind: REGKIND,
		pptlib: ptr ITypeLib


;; load registered typelib
;;
;WINOLEAUTAPI
LoadRegTypeLib proto _CType \
		 rguid: REFGUID,
	     wVerMajor: WORD,
	     wVerMinor: WORD,
		  lcid: LCID,
		pptlib: ptr ITypeLib


;; get path to registered typelib
;;
;WINOLEAUTAPI
QueryPathOfRegTypeLib proto _CType \
		  guid: REFGUID,
		  wMaj: USHORT,
		  wMin: USHORT,
		  lcid: LCID,
	lpbstrPathName: LPBSTR


;; add typelib to registry
;;
;WINOLEAUTAPI
RegisterTypeLib proto _CType \
		 ptlib: ptr ITypeLib,
	    szFullPath: ptr OLECHAR,
	     szHelpDir: ptr OLECHAR


;; remove typelib from registry
;;

;WINOLEAUTAPI
UnRegisterTypeLib proto _CType \
		 libID: REFGUID,
	     wVerMajor: WORD,
	     wVerMinor: WORD,
		  lcid: LCID,
	       syskind: SYSKIND


;WINOLEAUTAPI
CreateTypeLib proto _CType \
	       syskind: SYSKIND,
		szFile: ptr OLECHAR,
	       ppctlib: ptr ICreateTypeLib


;WINOLEAUTAPI
CreateTypeLib2 proto _CType \
	       syskind: SYSKIND,
		szFile: LPCOLESTR,
	       ppctlib: ptr ICreateTypeLib2



;;---------------------------------------------------------------------
;;	     IDispatch implementation support
;;---------------------------------------------------------------------

LPDISPATCH		typedef ptr IDispatch

PARAMDATA		STRUC
szName			LPOLECHAR ?	;; parameter name
vt			VARTYPE ?	;; parameter type
PARAMDATA		ENDS
LPPARAMDATA		typedef ptr PARAMDATA

METHODDATA		STRUC
szName			LPOLECHAR ?	;; method name
ppdata			LPPARAMDATA ?	;; pointer to an array of PARAMDATAs
dispid			DISPID ?	;; method ID
iMeth			UINT ?	;; method index
cc			CALLCONV ?	;; calling convention
cArgs			UINT ?	;; count of arguments
wFlags			dw ?	;; same wFlags as on IDispatch::Invoke()
vtReturn		VARTYPE ?
METHODDATA		ENDS
LPMETHODDATA		typedef ptr METHODDATA

INTERFACEDATA		STRUC
pmethdata		LPMETHODDATA ?	;; pointer to an array of METHODDATAs
cMembers		UINT ?	;; count of members
INTERFACEDATA		ENDS
LPINTERFACEDATA		typedef ptr INTERFACEDATA



;; Locate the parameter indicated by the given position, and
;; return it coerced to the given target VARTYPE (vtTarg).
;;
;WINOLEAUTAPI
DispGetParam proto _CType \
	   pdispparams: ptr DISPPARAMS,
	      position: UINT,
		vtTarg: VARTYPE,
	    pvarResult: ptr VARIANT,
	      puArgErr: ptr UINT


;; Automatic TypeInfo driven implementation of IDispatch::GetIDsOfNames()
;;
;WINOLEAUTAPI
DispGetIDsOfNames proto _CType \
		ptinfo: ptr ITypeInfo,
	     rgszNames: ptr OLECHAR,
		cNames: UINT,
	      rgdispid: ptr DISPID


;; Automatic TypeInfo driven implementation of IDispatch::Invoke()
;;
;WINOLEAUTAPI
DispInvoke proto _CType \
		 _this: ptr void,
		ptinfo: ptr ITypeInfo,
	  dispidMember: DISPID,
		wFlags: WORD,
	       pparams: ptr DISPPARAMS,
	    pvarResult: ptr VARIANT,
	    pexcepinfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT


;; Construct a TypeInfo from an interface data description
;;
;WINOLEAUTAPI
CreateDispTypeInfo proto _CType \
		pidata: ptr INTERFACEDATA,
		  lcid: LCID,
	       pptinfo: ptr ITypeInfo


;; Create an instance of the standard TypeInfo driven IDispatch
;; implementation.
;;
;WINOLEAUTAPI
CreateStdDispatch proto _CType \
	     punkOuter: ptr IUnknown,
		pvThis: ptr void,
		ptinfo: ptr ITypeInfo,
	  ppunkStdDisp: ptr IUnknown


;; Low-level helper for IDispatch::Invoke() provides machine independence
;; for customized Invoke().
;;
;WINOLEAUTAPI
DispCallFunc proto _CType \
	    pvInstance: ptr void,
		  oVft: ULONG,
		    cc: CALLCONV,
	      vtReturn: VARTYPE,
	      cActuals: UINT,
		 prgvt: ptr VARTYPE,
	      prgpvarg: ptr VARIANTARG,
	   pvargResult: ptr VARIANT



;;---------------------------------------------------------------------
;;	      Active Object Registration API
;;---------------------------------------------------------------------

;; flags for RegisterActiveObject
ACTIVEOBJECT_STRONG	equ 0x0
ACTIVEOBJECT_WEAK	equ 0x1

;WINOLEAUTAPI
RegisterActiveObject proto _CType \
		  punk: ptr IUnknown,
		rclsid: REFCLSID,
	       dwFlags: DWORD,
	   pdwRegister: ptr DWORD


;WINOLEAUTAPI
RevokeActiveObject proto _CType \
	    dwRegister: DWORD,


;WINOLEAUTAPI
GetActiveObject proto _CType \
		rclsid: REFCLSID,
	    pvReserved: ptr void,
		 ppunk: ptr IUnknown


;;---------------------------------------------------------------------
;;			     ErrorInfo API
;;---------------------------------------------------------------------

;WINOLEAUTAPI
SetErrorInfo proto _CType \
	    dwReserved: ULONG,
	      perrinfo: ptr IErrorInfo

;WINOLEAUTAPI
GetErrorInfo proto _CType \
	    dwReserved: ULONG,
	     pperrinfo: ptr IErrorInfo

;WINOLEAUTAPI
CreateErrorInfo proto _CType \
	     pperrinfo: ptr ICreateErrorInfo


;;---------------------------------------------------------------------
;;	     User Defined Data types support
;;---------------------------------------------------------------------

;WINOLEAUTAPI
GetRecordInfoFromTypeInfo proto _CType \
	     pTypeInfo: ptr ITypeInfo,
	     ppRecInfo: ptr IRecordInfo


;WINOLEAUTAPI
GetRecordInfoFromGuids proto _CType \
	  rGuidTypeLib: REFGUID,
	     uVerMajor: ULONG,
	     uVerMinor: ULONG,
		  lcid: LCID,
	 rGuidTypeInfo: REFGUID,
	     ppRecInfo: ptr IRecordInfo


;;---------------------------------------------------------------------
;;			     MISC API
;;---------------------------------------------------------------------

;WINOLEAUTAPI_(ULONG)
OaBuildVersion proto _CType

;WINOLEAUTAPI_(void)
ClearCustData proto _CType \
	     pCustData: LPCUSTDATA


;; Declare variant access functions.

if __STDC__ OR defined(NONAMELESSUNION)
V_UNION macro X, Y
	exitm<((X).n1.n2.n3.Y)>
	endm
V_VT macro X
	exitm<((X).n1.n2.vt)>
	endm
V_RECORDINFO macro X
	exitm<((X).n1.n2.n3.brecVal.pRecInfo)>
	endm
V_RECORD macro X
	exitm<((X).n1.n2.n3.brecVal.pvRecord)>
	endm
else
V_UNION macro X, Y
	exitm<((X).Y)>
	endm
V_VT macro X
	exitm<((X).vt)>
	endm
V_RECORDINFO macro X
	exitm<((X).pRecInfo)>
	endm
V_RECORD macro X
	exitm<((X).pvRecord)>
	endm
endif

;; Variant access macros
;;
V_ISBYREF macro X
	exitm<(V_VT(X) AND VT_BYREF)>
	endm
V_ISARRAY macro X
	exitm<(V_VT(X) AND VT_ARRAY)>
	endm
V_ISVECTOR macro X
	exitm<(V_VT(X) AND VT_VECTOR)>
	endm
V_NONE macro X
	exitm<V_I2(X)>
	endm

V_UI1 macro X
	exitm<V_UNION(X, bVal)>
	endm
V_UI1REF macro X
	exitm<V_UNION(X, pbVal)>
	endm
V_I2 macro X
	exitm<V_UNION(X, iVal)>
	endm
V_I2REF macro X
	exitm<V_UNION(X, piVal)>
	endm
V_I4 macro X
	exitm<V_UNION(X, lVal)>
	endm
V_I4REF macro X
	exitm<V_UNION(X, plVal)>
	endm
V_R4 macro X
	exitm<V_UNION(X, fltVal)>
	endm
V_R4REF macro X
	exitm<V_UNION(X, pfltVal)>
	endm
V_R8 macro X
	exitm<V_UNION(X, dblVal)>
	endm
V_R8REF macro X
	exitm<V_UNION(X, pdblVal)>
	endm
V_I1 macro X
	exitm<V_UNION(X, cVal)>
	endm
V_I1REF macro X
	exitm<V_UNION(X, pcVal)>
	endm
V_UI2 macro X
	exitm<V_UNION(X, uiVal)>
	endm
V_UI2REF macro X
	exitm<V_UNION(X, puiVal)>
	endm
V_UI4 macro X
	exitm<V_UNION(X, ulVal)>
	endm
V_UI4REF macro X
	exitm<V_UNION(X, pulVal)>
	endm
V_INT macro X
	exitm<V_UNION(X, intVal)>
	endm
V_INTREF macro X
	exitm<V_UNION(X, pintVal)>
	endm
V_UINT macro X
	exitm<V_UNION(X, uintVal)>
	endm
V_UINTREF macro X
	exitm<V_UNION(X, puintVal)>
	endm
V_CY macro X
	exitm<V_UNION(X, cyVal)>
	endm
V_CYREF macro X
	exitm<V_UNION(X, pcyVal)>
	endm
V_DATE macro X
	exitm<V_UNION(X, date)>
	endm
V_DATEREF macro X
	exitm<V_UNION(X, pdate)>
	endm
V_BSTR macro X
	exitm<V_UNION(X, bstrVal)>
	endm
V_BSTRREF macro X
	exitm<V_UNION(X, pbstrVal)>
	endm
V_DISPATCH macro X
	exitm<V_UNION(X, pdispVal)>
	endm
V_DISPATCHREF macro X
	exitm<V_UNION(X, ppdispVal)>
	endm
V_ERROR macro X
	exitm<V_UNION(X, scode)>
	endm
V_ERRORREF macro X
	exitm<V_UNION(X, pscode)>
	endm
V_BOOL macro X
	exitm<V_UNION(X, boolVal)>
	endm
V_BOOLREF macro X
	exitm<V_UNION(X, pboolVal)>
	endm
V_UNKNOWN macro X
	exitm<V_UNION(X, punkVal)>
	endm
V_UNKNOWNREF macro X
	exitm<V_UNION(X, ppunkVal)>
	endm
V_VARIANTREF macro X
	exitm<V_UNION(X, pvarVal)>
	endm
V_ARRAY macro X
	exitm<V_UNION(X, parray)>
	endm
V_ARRAYREF macro X
	exitm<V_UNION(X, pparray)>
	endm
V_BYREF macro X
	exitm<V_UNION(X, byref)>
	endm

V_DECIMAL macro X
	exitm<V_UNION(X, decVal)>
	endm
V_DECIMALREF macro X
	exitm<V_UNION(X, pdecVal)>
	endm

;;#include <poppack.h>
.list
endif	   ;; __OLEAUTO_H__

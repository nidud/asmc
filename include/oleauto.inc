ifndef _OLEAUTO_H_
.xlist
_OLEAUTO_H_ equ 1

ifdef __PE__
option	dllimport:<oleaut32>
else
includelib oleaut32.lib
endif

externdef		IID_StdOle:IID

STDOLE_MAJORVERNUM	equ 0x1
STDOLE_MINORVERNUM	equ 0x0
STDOLE_LCID		equ 0x0000
STDOLE2_MAJORVERNUM	equ 0x2
STDOLE2_MINORVERNUM	equ 0x0
STDOLE2_LCID		equ 0x0000

ifndef _LCID_DEFINED
LCID			typedef DWORD
_LCID_DEFINED		equ 1
endif

include oaidl.inc
.xlist

;WINOLEAUTAPI_(BSTR)
SysAllocString proto WINAPI \
		      : ptr OLECHAR

;WINOLEAUTAPI_(INT)
SysReAllocString proto WINAPI \
		      : ptr BSTR,
		      : ptr OLECHAR

;WINOLEAUTAPI_(BSTR)
SysAllocStringLen proto WINAPI \
		      : ptr OLECHAR,
		      : UINT

;WINOLEAUTAPI_(INT)
SysReAllocStringLen proto WINAPI \
		      : ptr BSTR,
		      : ptr OLECHAR,
		      : UINT

;WINOLEAUTAPI_(void)
SysFreeString proto WINAPI \
		      : ptr BSTR

;WINOLEAUTAPI_(UINT)
SysStringLen proto WINAPI \
		      : ptr BSTR
ifdef _WIN32
;WINOLEAUTAPI_(UINT)
SysStringByteLen proto WINAPI \
		  bstr: BSTR

;WINOLEAUTAPI_(BSTR)
SysAllocStringByteLen proto WINAPI \
		   psz: LPCSTR,
		   len: UINT

endif

;WINOLEAUTAPI_(INT)
DosDateTimeToVariantTime proto WINAPI \
	      wDosDate: USHORT,
	      wDosTime: USHORT,
		pvtime: ptr DOUBLE


;WINOLEAUTAPI_(INT)
VariantTimeToDosDateTime proto WINAPI \
		 vtime: DOUBLE,
	     pwDosDate: ptr USHORT,
	     pwDosTime: ptr USHORT

ifdef _WIN32
;WINOLEAUTAPI_(INT)
SystemTimeToVariantTime proto WINAPI \
	  lpSystemTime: LPSYSTEMTIME,
		pvtime: ptr DOUBLE

;WINOLEAUTAPI_(INT)
VariantTimeToSystemTime proto WINAPI \
		 vtime: DOUBLE,
	  lpSystemTime: LPSYSTEMTIME

endif

;WINOLEAUTAPI
SafeArrayAllocDescriptor proto WINAPI \
		 cDims: UINT,
	       ppsaOut: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayAllocDescriptorEx proto WINAPI \
		    vt: VARTYPE,
		 cDims: UINT,
	       ppsaOut: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayAllocData proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI_(SAFEARRAY
SafeArrayCreate proto WINAPI \
		    vt: VARTYPE,
		 cDims: UINT,
	     rgsabound: ptr SAFEARRAYBOUND

;WINOLEAUTAPI_(SAFEARRAY
SafeArrayCreateEx proto WINAPI \
		    vt: VARTYPE,
		 cDims: UINT,
	     rgsabound: ptr SAFEARRAYBOUND,
	       pvExtra: PVOID

;WINOLEAUTAPI
SafeArrayCopyData proto WINAPI \
	     psaSource: ptr SAFEARRAY,
	     psaTarget: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayDestroyDescriptor proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayDestroyData proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayDestroy proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayRedim proto WINAPI \
		   psa: ptr SAFEARRAY,
	   psaboundNew: ptr SAFEARRAYBOUND

;WINOLEAUTAPI_(UINT)
SafeArrayGetDim proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI_(UINT)
SafeArrayGetElemsize proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayGetUBound proto WINAPI \
		   psa: ptr SAFEARRAY,
		  nDim: UINT,
	      plUbound: ptr LONG

;WINOLEAUTAPI
SafeArrayGetLBound proto WINAPI \
		   psa: ptr SAFEARRAY,
		  nDim: UINT,
	      plLbound: ptr LONG

;WINOLEAUTAPI
SafeArrayLock proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayUnlock proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayAccessData proto WINAPI \
		   psa: ptr SAFEARRAY,
	       ppvData: PVOID

;WINOLEAUTAPI
SafeArrayUnaccessData proto WINAPI \
		   psa: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayGetElement proto WINAPI \
		   psa: ptr SAFEARRAY,
	     rgIndices: ptr LONG,
		    pv: PVOID

;WINOLEAUTAPI
SafeArrayPutElement proto WINAPI \
		   psa: ptr SAFEARRAY,
	     rgIndices: ptr LONG,
		    pv: PVOID

;WINOLEAUTAPI
SafeArrayCopy proto WINAPI \
		   psa: ptr SAFEARRAY,
	       ppsaOut: ptr SAFEARRAY

;WINOLEAUTAPI
SafeArrayPtrOfIndex proto WINAPI \
		   psa: ptr SAFEARRAY,
	     rgIndices: ptr LONG,
	       ppvData: PVOID

;WINOLEAUTAPI
SafeArraySetRecordInfo proto WINAPI \
		   psa: ptr SAFEARRAY,
		prinfo: ptr IRecordInfo

;WINOLEAUTAPI
SafeArrayGetRecordInfo proto WINAPI \
		   psa: ptr SAFEARRAY,
		prinfo: ptr IRecordInfo

;WINOLEAUTAPI
SafeArraySetIID proto WINAPI \
		   psa: ptr SAFEARRAY,
		  guid: REFGUID

;WINOLEAUTAPI
SafeArrayGetIID proto WINAPI \
		   psa: ptr SAFEARRAY,
		 pguid: ptr GUID

;WINOLEAUTAPI
SafeArrayGetVartype proto WINAPI \
		   psa: ptr SAFEARRAY,
		   pvt: ptr VARTYPE

;WINOLEAUTAPI_(SAFEARRAY
SafeArrayCreateVector proto WINAPI \
		    vt: VARTYPE,
	       lLbound: LONG,
	     cElements: ULONG

;WINOLEAUTAPI_(SAFEARRAY
SafeArrayCreateVectorEx proto WINAPI \
		    vt: VARTYPE,
	       lLbound: LONG,
	     cElements: ULONG,
	       pvExtra: PVOID



;WINOLEAUTAPI_(void)
VariantInit proto WINAPI \
		 pvarg: ptr VARIANTARG

;WINOLEAUTAPI
VariantClear proto WINAPI \
		 pvarg: ptr VARIANTARG

;WINOLEAUTAPI
VariantCopy proto WINAPI \
	     pvargDest: ptr VARIANTARG,
	      pvargSrc: ptr VARIANTARG

;WINOLEAUTAPI
VariantCopyInd proto WINAPI \
	      pvarDest: ptr VARIANT,
	      pvargSrc: ptr VARIANTARG

;WINOLEAUTAPI
VariantChangeType proto WINAPI \
	     pvargDest: ptr VARIANTARG,
	       pvarSrc: ptr VARIANTARG,
		wFlags: USHORT,
		    vt: VARTYPE

;WINOLEAUTAPI
VariantChangeTypeEx proto WINAPI \
	     pvargDest: ptr VARIANTARG,
	       pvarSrc: ptr VARIANTARG,
		  lcid: LCID,
		wFlags: USHORT,
		    vt: VARTYPE


VARIANT_NOVALUEPROP	equ 0x1
VARIANT_ALPHABOOL	equ 0x2
VARIANT_NOUSEROVERRIDE	equ 0x4
VARIANT_LOCALBOOL	equ 0x8


;WINOLEAUTAPI
VectorFromBstr proto WINAPI \
		  bstr: BSTR,
		  ppsa: ptr SAFEARRAY

;WINOLEAUTAPI
BstrFromVector proto WINAPI \
		   psa: ptr SAFEARRAY,
		 pbstr: ptr BSTR






VAR_TIMEVALUEONLY	equ 0x00000001
VAR_DATEVALUEONLY	equ 0x00000002

VAR_LOCALBOOL		equ 0x00000010

;WINOLEAUTAPI
VarUI1FromI2 proto WINAPI \
		   sIn: SWORD,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromI4 proto WINAPI \
		   lIn: LONG,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromR4 proto WINAPI \
		 fltIn: FLOAT,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromR8 proto WINAPI \
		 dblIn: DOUBLE,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromCy proto WINAPI \
		  cyIn: CY,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromDate proto WINAPI \
		dateIn: DATE,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromI1 proto WINAPI \
		   cIn: CHAR,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromUI2 proto WINAPI \
		  uiIn: USHORT,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromUI4 proto WINAPI \
		  ulIn: ULONG,
		 pbOut: ptr BYTE

;WINOLEAUTAPI
VarUI1FromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
		 pbOut: ptr BYTE


;WINOLEAUTAPI
VarI2FromUI1 proto WINAPI \
		   bIn: BYTE,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromI4 proto WINAPI \
		   lIn: LONG,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromR4 proto WINAPI \
		 fltIn: FLOAT,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromR8 proto WINAPI \
		 dblIn: DOUBLE,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromCy proto WINAPI \
		  cyIn: CY,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromDate proto WINAPI \
		dateIn: DATE,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromI1 proto WINAPI \
		   cIn: CHAR,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromUI2 proto WINAPI \
		  uiIn: USHORT,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromUI4 proto WINAPI \
		  ulIn: ULONG,
		 psOut: ptr SWORD

;WINOLEAUTAPI
VarI2FromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
		 psOut: ptr SWORD


;WINOLEAUTAPI
VarI4FromUI1 proto WINAPI \
		   bIn: BYTE,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromI2 proto WINAPI \
		   sIn: SWORD,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromR4 proto WINAPI \
		 fltIn: FLOAT,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromR8 proto WINAPI \
		 dblIn: DOUBLE,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromCy proto WINAPI \
		  cyIn: CY,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromDate proto WINAPI \
		dateIn: DATE,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromI1 proto WINAPI \
		   cIn: CHAR,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromUI2 proto WINAPI \
		  uiIn: USHORT,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromUI4 proto WINAPI \
		  ulIn: ULONG,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
		 plOut: ptr LONG

;WINOLEAUTAPI
VarI4FromInt proto WINAPI \
		 intIn: SINT,
		 plOut: ptr LONG


;WINOLEAUTAPI
VarR4FromUI1 proto WINAPI \
		   bIn: BYTE,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromI2 proto WINAPI \
		   sIn: SWORD,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromI4 proto WINAPI \
		   lIn: LONG,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromR8 proto WINAPI \
		 dblIn: DOUBLE,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromCy proto WINAPI \
		  cyIn: CY,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromDate proto WINAPI \
		dateIn: DATE,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromI1 proto WINAPI \
		   cIn: CHAR,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromUI2 proto WINAPI \
		  uiIn: USHORT,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromUI4 proto WINAPI \
		  ulIn: ULONG,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR4FromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
	       pfltOut: ptr FLOAT

;WINOLEAUTAPI
VarR8FromUI1 proto WINAPI \
		   bIn: BYTE,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromI2 proto WINAPI \
		   sIn: SWORD,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromI4 proto WINAPI \
		   lIn: LONG,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromR4 proto WINAPI \
		 fltIn: FLOAT,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromCy proto WINAPI \
		  cyIn: CY,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromDate proto WINAPI \
		dateIn: DATE,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromI1 proto WINAPI \
		   cIn: CHAR,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromUI2 proto WINAPI \
		  uiIn: USHORT,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromUI4 proto WINAPI \
		  ulIn: ULONG,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarR8FromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
	       pdblOut: ptr DOUBLE

;WINOLEAUTAPI
VarDateFromUI1 proto WINAPI \
		   bIn: BYTE,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromI2 proto WINAPI \
		   sIn: SWORD,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromI4 proto WINAPI \
		   lIn: LONG,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromR4 proto WINAPI \
		 fltIn: FLOAT,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromR8 proto WINAPI \
		 dblIn: DOUBLE,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromCy proto WINAPI \
		  cyIn: CY,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromI1 proto WINAPI \
		   cIn: CHAR,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromUI2 proto WINAPI \
		  uiIn: USHORT,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromUI4 proto WINAPI \
		  ulIn: ULONG,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarDateFromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
	      pdateOut: ptr DATE


;WINOLEAUTAPI
VarCyFromUI1 proto WINAPI \
		   bIn: BYTE,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromI2 proto WINAPI \
		   sIn: SWORD,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromI4 proto WINAPI \
		   lIn: LONG,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromR4 proto WINAPI \
		 fltIn: FLOAT,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromR8 proto WINAPI \
		 dblIn: DOUBLE,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromDate proto WINAPI \
		dateIn: DATE,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromI1 proto WINAPI \
		   cIn: CHAR,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromUI2 proto WINAPI \
		  uiIn: USHORT,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromUI4 proto WINAPI \
		  ulIn: ULONG,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarCyFromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
		pcyOut: ptr CY

;WINOLEAUTAPI
VarBstrFromUI1 proto WINAPI \
		  bVal: BYTE,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromI2 proto WINAPI \
		  iVal: SWORD,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromI4 proto WINAPI \
		   lIn: LONG,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromR4 proto WINAPI \
		 fltIn: FLOAT,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromR8 proto WINAPI \
		 dblIn: DOUBLE,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromCy proto WINAPI \
		  cyIn: CY,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromDate proto WINAPI \
		dateIn: DATE,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromI1 proto WINAPI \
		   cIn: CHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromUI2 proto WINAPI \
		  uiIn: USHORT,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromUI4 proto WINAPI \
		  ulIn: ULONG,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarBstrFromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR


;WINOLEAUTAPI
VarBoolFromUI1 proto WINAPI \
		   bIn: BYTE,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromI2 proto WINAPI \
		   sIn: SWORD,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromI4 proto WINAPI \
		   lIn: LONG,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromR4 proto WINAPI \
		 fltIn: FLOAT,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromR8 proto WINAPI \
		 dblIn: DOUBLE,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromDate proto WINAPI \
		dateIn: DATE,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromCy proto WINAPI \
		  cyIn: CY,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromI1 proto WINAPI \
		   cIn: CHAR,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromUI2 proto WINAPI \
		  uiIn: USHORT,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromUI4 proto WINAPI \
		  ulIn: ULONG,
	      pboolOut: ptr VARIANT_BOOL

;WINOLEAUTAPI
VarBoolFromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
	      pboolOut: ptr VARIANT_BOOL


;WINOLEAUTAPI
VarI1FromUI1 proto WINAPI \
		   bIn: BYTE,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromI2 proto WINAPI \
		  uiIn: SWORD,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromI4 proto WINAPI \
		   lIn: LONG,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromR4 proto WINAPI \
		 fltIn: FLOAT,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromR8 proto WINAPI \
		 dblIn: DOUBLE,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromDate proto WINAPI \
		dateIn: DATE,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromCy proto WINAPI \
		  cyIn: CY,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromUI2 proto WINAPI \
		  uiIn: USHORT,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromUI4 proto WINAPI \
		  ulIn: ULONG,
		 pcOut: ptr CHAR

;WINOLEAUTAPI
VarI1FromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
		 pcOut: ptr CHAR


;WINOLEAUTAPI
VarUI2FromUI1 proto WINAPI \
		   bIn: BYTE,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromI2 proto WINAPI \
		  uiIn: SWORD,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromI4 proto WINAPI \
		   lIn: LONG,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromR4 proto WINAPI \
		 fltIn: FLOAT,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromR8 proto WINAPI \
		 dblIn: DOUBLE,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromDate proto WINAPI \
		dateIn: DATE,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromCy proto WINAPI \
		  cyIn: CY,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromI1 proto WINAPI \
		   cIn: CHAR,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromUI4 proto WINAPI \
		  ulIn: ULONG,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI2FromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
		puiOut: ptr USHORT

;WINOLEAUTAPI
VarUI4FromUI1 proto WINAPI \
		   bIn: BYTE,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromI2 proto WINAPI \
		  uiIn: SWORD,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromI4 proto WINAPI \
		   lIn: LONG,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromR4 proto WINAPI \
		 fltIn: FLOAT,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromR8 proto WINAPI \
		 dblIn: DOUBLE,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromDate proto WINAPI \
		dateIn: DATE,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromCy proto WINAPI \
		  cyIn: CY,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromI1 proto WINAPI \
		   cIn: CHAR,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromUI2 proto WINAPI \
		  uiIn: USHORT,
		pulOut: ptr ULONG

;WINOLEAUTAPI
VarUI4FromDec proto WINAPI \
		pdecIn: ptr DECIMAL,
		pulOut: ptr ULONG


;WINOLEAUTAPI
VarDecFromUI1 proto WINAPI \
		   bIn: BYTE,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromI2 proto WINAPI \
		  uiIn: SWORD,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromI4 proto WINAPI \
		   lIn: LONG,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromR4 proto WINAPI \
		 fltIn: FLOAT,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromR8 proto WINAPI \
		 dblIn: DOUBLE,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromDate proto WINAPI \
		dateIn: DATE,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromCy proto WINAPI \
		  cyIn: CY,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromDisp proto WINAPI \
	       pdispIn: ptr IDispatch,
		  lcid: LCID,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromBool proto WINAPI \
		boolIn: VARIANT_BOOL,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromI1 proto WINAPI \
		   cIn: CHAR,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromUI2 proto WINAPI \
		  uiIn: USHORT,
	       pdecOut: ptr DECIMAL

;WINOLEAUTAPI
VarDecFromUI4 proto WINAPI \
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

NUMPARSE		STRUC
cDig			SINT ?
dwInFlags		ULONG ?
dwOutFlags		ULONG ?
cchUsed			SINT ?
nBaseShift		SINT ?
nPwr10			SINT ?
NUMPARSE		ENDS

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

NUMPRS_NEG		equ 0x10000
NUMPRS_INEXACT		equ 0x20000

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
VarParseNumFromStr proto WINAPI \
		 strIn: ptr OLECHAR,
		  lcid: LCID,
	       dwFlags: ULONG,
	       pnumprs: ptr NUMPARSE,
		rgbDig: ptr BYTE

;WINOLEAUTAPI
VarNumFromParseNum proto WINAPI \
	       pnumprs: ptr NUMPARSE,
		rgbDig: ptr BYTE,
	      dwVtBits: ULONG,
		  pvar: ptr VARIANT

;STDAPI
VarAdd proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarAnd proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarCat proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarDiv proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarEqv proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarIdiv proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarImp proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarMod proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarMul proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarOr proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarPow proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarSub proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarXor proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
	    pvarResult: LPVARIANT


;STDAPI
VarAbs proto WINAPI \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarFix proto WINAPI \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarInt proto WINAPI \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarNeg proto WINAPI \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT

;STDAPI
VarNot proto WINAPI \
		pvarIn: LPVARIANT,
	    pvarResult: LPVARIANT


;STDAPI
VarRound proto WINAPI \
		pvarIn: LPVARIANT,
	     cDecimals: SINT,
	    pvarResult: LPVARIANT

;STDAPI
VarCmp proto WINAPI \
	      pvarLeft: LPVARIANT,
	     pvarRight: LPVARIANT,
		  lcid: LCID

;STDAPI
VarDecAdd proto WINAPI \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecDiv proto WINAPI \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecMul proto WINAPI \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecSub proto WINAPI \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecAbs proto WINAPI \
		pdecIn: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecFix proto WINAPI \
		pdecIn: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecInt proto WINAPI \
		pdecIn: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecNeg proto WINAPI \
		pdecIn: LPDECIMAL,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecRound proto WINAPI \
		pdecIn: LPDECIMAL,
	     cDecimals: SINT,
	    pdecResult: LPDECIMAL

;STDAPI
VarDecCmp proto WINAPI \
	      pdecLeft: LPDECIMAL,
	     pdecRight: LPDECIMAL

;STDAPI
VarDecCmpR8 proto WINAPI \
	      pdecLeft: LPDECIMAL,
	      dblRight: DOUBLE

;STDAPI
VarCyAdd proto WINAPI \
		cyLeft: CY,
	       cyRight: CY,
	     pcyResult: LPCY

;STDAPI
VarCyMul proto WINAPI \
		cyLeft: CY,
	       cyRight: CY,
	     pcyResult: LPCY

;STDAPI
VarCyMulI4 proto WINAPI \
		cyLeft: CY,
		lRight: LONG,
	     pcyResult: LPCY

;STDAPI
VarCySub proto WINAPI \
		cyLeft: CY,
	       cyRight: CY,
	     pcyResult: LPCY

;STDAPI
VarCyAbs proto WINAPI \
		  cyIn: CY,
	     pcyResult: LPCY

;STDAPI
VarCyFix proto WINAPI \
		  cyIn: CY,
	     pcyResult: LPCY

;STDAPI
VarCyInt proto WINAPI \
		  cyIn: CY,
	     pcyResult: LPCY

;STDAPI
VarCyNeg proto WINAPI \
		  cyIn: CY,
	     pcyResult: LPCY

;STDAPI
VarCyRound proto WINAPI \
		  cyIn: CY,
	     cDecimals: SINT,
	     pcyResult: LPCY

;STDAPI
VarCyCmp proto WINAPI \
		cyLeft: CY,
	       cyRight: CY

;STDAPI
VarCyCmpR8 proto WINAPI \
		cyLeft: CY,
	      dblRight: DOUBLE

;STDAPI
VarBstrCat proto WINAPI \
	      bstrLeft: BSTR,
	     bstrRight: BSTR,
	   pbstrResult: LPBSTR

;STDAPI
VarBstrCmp proto WINAPI \
	      bstrLeft: BSTR,
	     bstrRight: BSTR,
		  lcid: LCID

;STDAPI
VarR8Pow proto WINAPI \
	       dblLeft: DOUBLE,
	      dblRight: DOUBLE,
	    pdblResult: ptr DOUBLE

;STDAPI
VarR4CmpR8 proto WINAPI \
	       fltLeft: FLOAT,
	      dblRight: DOUBLE

;STDAPI
VarR8Round proto WINAPI \
		 dblIn: DOUBLE,
	     cDecimals: SINT,
	    pdblResult: ptr DOUBLE


VARCMP_LT		equ 0
VARCMP_EQ		equ 1
VARCMP_GT		equ 2
VARCMP_NULL		equ 3

VT_HARDTYPE		equ VT_RESERVED

VAR_VALIDDATE		equ 0x0004
VAR_CALENDAR_HIJRI	equ 0x0008
VARIANT_CALENDAR_HIJRI	equ VAR_CAENDAR_HIJRI

UDATE			STRUC
_st			SYSTEMTIME <>
wDayOfYear		dw ?
UDATE			ENDS

;WINOLEAUTAPI
VarDateFromUdate proto WINAPI \
	      pudateIn: ptr UDATE,
	       dwFlags: ULONG,
	      pdateOut: ptr DATE

;WINOLEAUTAPI
VarUdateFromDate proto WINAPI \
		dateIn: DATE,
	       dwFlags: ULONG,
	     pudateOut: ptr UDATE


;WINOLEAUTAPI
GetAltMonthNames proto WINAPI \
		  lcid: LCID,
		  prgp: ptr LPOLESTR


VAR_FORMAT_NOSUBSTITUTE equ 0x00000010

;WINOLEAUTAPI
VarFormat proto WINAPI \
		pvarIn: LPVARIANT,
	    pstrFormat: LPOLESTR,
	     iFirstDay: SINT,
	    iFirstWeek: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatDateTime proto WINAPI \
		pvarIn: LPVARIANT,
	  iNamedFormat: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatNumber proto WINAPI \
		pvarIn: LPVARIANT,
	       iNumDig: SINT,
	      iIncLead: SINT,
	    iUseParens: SINT,
		iGroup: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatPercent proto WINAPI \
		pvarIn: LPVARIANT,
	       iNumDig: SINT,
	      iIncLead: SINT,
	    iUseParens: SINT,
		iGroup: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatCurrency proto WINAPI \
		pvarIn: LPVARIANT,
	       iNumDig: SINT,
	      iIncLead: SINT,
	    iUseParens: SINT,
		iGroup: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarWeekdayName proto WINAPI \
	      iWeekday: SINT,
	       fAbbrev: SINT,
	     iFirstDay: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarMonthName proto WINAPI \
		iMonth: SINT,
	       fAbbrev: SINT,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR

;WINOLEAUTAPI
VarFormatFromTokens proto WINAPI \
		pvarIn: LPVARIANT,
	    pstrFormat: LPOLESTR,
	      pbTokCur: LPBYTE,
	       dwFlags: ULONG,
	      pbstrOut: ptr BSTR,
		  lcid: LCID

;WINOLEAUTAPI_(LPBYTE)
VarTokenizeFormatString proto WINAPI \
	    pstrFormat: LPOLESTR,
		rgbTok: LPBYTE,
		 cbTok: SINT,
	     iFirstDay: SINT,
	    iFirstWeek: SINT,
		  lcid: LCID

LPTYPELIB		typedef ptr ITypeLib

DISPID			typedef LONG
MEMBERID		typedef DISPID

MEMBERID_NIL		equ DISPID_UNKNOWN
ID_DEFAULTINST		equ -2

DISPATCH_METHOD		equ 0x1
DISPATCH_PROPERTYGET	equ 0x2
DISPATCH_PROPERTYPUT	equ 0x4
DISPATCH_PROPERTYPUTREF equ 0x8

LPTYPEINFO		typedef ptr ITypeInfo
LPTYPECOMP		typedef ptr ITypeComp
LPCREATETYPELIB		typedef ptr ICreateTypeLib
LPCREATETYPEINFO	typedef ptr ICreateTypeInfo

ifdef _WIN32
;WINOLEAUTAPI_(ULONG)
LHashValOfNameSysA proto WINAPI \
	       syskind: SYSKIND,
		  lcid: LCID,
		szName: LPCSTR
endif

LHashValOfNameSys proto WINAPI \
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

;WINOLEAUTAPI
LoadTypeLib proto WINAPI \
		szFile: ptr OLECHAR,
		pptlib: ptr ITypeLib


REGKIND			typedef SDWORD
REGKIND_DEFAULT		equ 0
REGKIND_REGISTER	equ 1
REGKIND_NONE		equ 2

;WINOLEAUTAPI
LoadTypeLibEx proto WINAPI \
		szFile: LPCOLESTR,
	       regkind: REGKIND,
		pptlib: ptr ITypeLib

;WINOLEAUTAPI
LoadRegTypeLib proto WINAPI \
		 rguid: REFGUID,
	     wVerMajor: WORD,
	     wVerMinor: WORD,
		  lcid: LCID,
		pptlib: ptr ITypeLib

;WINOLEAUTAPI
QueryPathOfRegTypeLib proto WINAPI \
		  guid: REFGUID,
		  wMaj: USHORT,
		  wMin: USHORT,
		  lcid: LCID,
	lpbstrPathName: LPBSTR

;WINOLEAUTAPI
RegisterTypeLib proto WINAPI \
		 ptlib: ptr ITypeLib,
	    szFullPath: ptr OLECHAR,
	     szHelpDir: ptr OLECHAR

;WINOLEAUTAPI
UnRegisterTypeLib proto WINAPI \
		 libID: REFGUID,
	     wVerMajor: WORD,
	     wVerMinor: WORD,
		  lcid: LCID,
	       syskind: SYSKIND

;WINOLEAUTAPI
CreateTypeLib proto WINAPI \
	       syskind: SYSKIND,
		szFile: ptr OLECHAR,
	       ppctlib: ptr ICreateTypeLib

;WINOLEAUTAPI
CreateTypeLib2 proto WINAPI \
	       syskind: SYSKIND,
		szFile: LPCOLESTR,
	       ppctlib: ptr ICreateTypeLib2


LPDISPATCH		typedef ptr IDispatch

PARAMDATA		STRUC
szName			LPOLECHAR ?
vt			VARTYPE ?
PARAMDATA		ENDS
LPPARAMDATA		typedef ptr PARAMDATA

METHODDATA		STRUC
szName			LPOLECHAR ?
ppdata			LPPARAMDATA ?
dispid			DISPID ?
iMeth			UINT ?
cc			CALLCONV ?
cArgs			UINT ?
wFlags			dw ?
vtReturn		VARTYPE ?
METHODDATA		ENDS
LPMETHODDATA		typedef ptr METHODDATA

INTERFACEDATA		STRUC
pmethdata		LPMETHODDATA ?
cMembers		UINT ?
INTERFACEDATA		ENDS
LPINTERFACEDATA		typedef ptr INTERFACEDATA

;WINOLEAUTAPI
DispGetParam proto WINAPI \
	   pdispparams: ptr DISPPARAMS,
	      position: UINT,
		vtTarg: VARTYPE,
	    pvarResult: ptr VARIANT,
	      puArgErr: ptr UINT

;WINOLEAUTAPI
DispGetIDsOfNames proto WINAPI \
		ptinfo: ptr ITypeInfo,
	     rgszNames: ptr OLECHAR,
		cNames: UINT,
	      rgdispid: ptr DISPID

;WINOLEAUTAPI
DispInvoke proto WINAPI \
		 _this: ptr void,
		ptinfo: ptr ITypeInfo,
	  dispidMember: DISPID,
		wFlags: WORD,
	       pparams: ptr DISPPARAMS,
	    pvarResult: ptr VARIANT,
	    pexcepinfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

;WINOLEAUTAPI
CreateDispTypeInfo proto WINAPI \
		pidata: ptr INTERFACEDATA,
		  lcid: LCID,
	       pptinfo: ptr ITypeInfo

;WINOLEAUTAPI
CreateStdDispatch proto WINAPI \
	     punkOuter: ptr IUnknown,
		pvThis: ptr void,
		ptinfo: ptr ITypeInfo,
	  ppunkStdDisp: ptr IUnknown

;WINOLEAUTAPI
DispCallFunc proto WINAPI \
	    pvInstance: ptr void,
		  oVft: ULONG,
		    cc: CALLCONV,
	      vtReturn: VARTYPE,
	      cActuals: UINT,
		 prgvt: ptr VARTYPE,
	      prgpvarg: ptr VARIANTARG,
	   pvargResult: ptr VARIANT

ACTIVEOBJECT_STRONG	equ 0x0
ACTIVEOBJECT_WEAK	equ 0x1

;WINOLEAUTAPI
RegisterActiveObject proto WINAPI \
		  punk: ptr IUnknown,
		rclsid: REFCLSID,
	       dwFlags: DWORD,
	   pdwRegister: ptr DWORD

;WINOLEAUTAPI
RevokeActiveObject proto WINAPI \
	    dwRegister: DWORD,
		      : PVOID

;WINOLEAUTAPI
GetActiveObject proto WINAPI \
		rclsid: REFCLSID,
	    pvReserved: PVOID,
		 ppunk: ptr IUnknown

;WINOLEAUTAPI
SetErrorInfo proto WINAPI \
	    dwReserved: ULONG,
	      perrinfo: ptr IErrorInfo

;WINOLEAUTAPI
GetErrorInfo proto WINAPI \
	    dwReserved: ULONG,
	     pperrinfo: ptr IErrorInfo

;WINOLEAUTAPI
CreateErrorInfo proto WINAPI \
	     pperrinfo: ptr ICreateErrorInfo

;WINOLEAUTAPI
GetRecordInfoFromTypeInfo proto WINAPI \
	     pTypeInfo: ptr ITypeInfo,
	     ppRecInfo: ptr IRecordInfo

;WINOLEAUTAPI
GetRecordInfoFromGuids proto WINAPI \
	  rGuidTypeLib: REFGUID,
	     uVerMajor: ULONG,
	     uVerMinor: ULONG,
		  lcid: LCID,
	 rGuidTypeInfo: REFGUID,
	     ppRecInfo: ptr IRecordInfo

;WINOLEAUTAPI_(ULONG)
OaBuildVersion proto WINAPI

;WINOLEAUTAPI_(void)
ClearCustData proto WINAPI \
	     pCustData: LPCUSTDATA

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

.list
endif

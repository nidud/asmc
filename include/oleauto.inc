ifndef _OLEAUTO_H_
define _OLEAUTO_H_

.pragma comment(lib, oleaut32)

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

SysAllocString proto WINAPI :ptr
SysReAllocString proto WINAPI :ptr, :ptr
SysAllocStringLen proto WINAPI :ptr, :UINT
SysReAllocStringLen proto WINAPI :ptr, :ptr, :UINT
SysFreeString proto WINAPI :ptr
SysStringLen proto WINAPI :ptr
ifdef _WIN32
SysStringByteLen proto WINAPI :BSTR
SysAllocStringByteLen proto WINAPI :LPCSTR, :UINT
endif
DosDateTimeToVariantTime proto WINAPI :USHORT, :USHORT, :ptr
VariantTimeToDosDateTime proto WINAPI :DOUBLE, :ptr, :ptr
ifdef _WIN32
SystemTimeToVariantTime proto WINAPI :LPSYSTEMTIME, :ptr
VariantTimeToSystemTime proto WINAPI :DOUBLE, :LPSYSTEMTIME
endif
SafeArrayAllocDescriptor proto WINAPI :UINT, :ptr
SafeArrayAllocDescriptorEx proto WINAPI :VARTYPE, :UINT, :ptr
SafeArrayAllocData proto WINAPI :ptr
SafeArrayCreate proto WINAPI :VARTYPE, :UINT, :ptr
SafeArrayCreateEx proto WINAPI :VARTYPE, :UINT, :ptr, :ptr
SafeArrayCopyData proto WINAPI :ptr, :ptr
SafeArrayDestroyDescriptor proto WINAPI :ptr
SafeArrayDestroyData proto WINAPI :ptr
SafeArrayDestroy proto WINAPI :ptr
SafeArrayRedim proto WINAPI :ptr, :ptr
SafeArrayGetDim proto WINAPI :ptr
SafeArrayGetElemsize proto WINAPI :ptr
SafeArrayGetUBound proto WINAPI :ptr, :UINT, :ptr
SafeArrayGetLBound proto WINAPI :ptr, :UINT, :ptr
SafeArrayLock proto WINAPI :ptr
SafeArrayUnlock proto WINAPI :ptr
SafeArrayAccessData proto WINAPI :ptr, :ptr
SafeArrayUnaccessData proto WINAPI :ptr
SafeArrayGetElement proto WINAPI :ptr, :ptr, :ptr
SafeArrayPutElement proto WINAPI :ptr, :ptr, :ptr
SafeArrayCopy proto WINAPI :ptr, :ptr
SafeArrayPtrOfIndex proto WINAPI :ptr, :ptr, :ptr
SafeArraySetRecordInfo proto WINAPI :ptr, :ptr
SafeArrayGetRecordInfo proto WINAPI :ptr, :ptr
SafeArraySetIID proto WINAPI :ptr, :REFGUID
SafeArrayGetIID proto WINAPI :ptr, :ptr
SafeArrayGetVartype proto WINAPI :ptr, :ptr
SafeArrayCreateVector proto WINAPI :VARTYPE, :LONG, :ULONG
SafeArrayCreateVectorEx proto WINAPI :VARTYPE, :LONG, :ULONG, :ptr
VariantInit proto WINAPI :ptr
VariantClear proto WINAPI :ptr
VariantCopy proto WINAPI :ptr, :ptr
VariantCopyInd proto WINAPI :ptr, :ptr
VariantChangeType proto WINAPI :ptr, :ptr, :USHORT, :VARTYPE
VariantChangeTypeEx proto WINAPI :ptr, :ptr, :LCID, :USHORT, :VARTYPE

VARIANT_NOVALUEPROP	equ 0x1
VARIANT_ALPHABOOL	equ 0x2
VARIANT_NOUSEROVERRIDE	equ 0x4
VARIANT_LOCALBOOL	equ 0x8

VectorFromBstr proto WINAPI :BSTR, :ptr
BstrFromVector proto WINAPI :ptr, :ptr

VAR_TIMEVALUEONLY	equ 0x00000001
VAR_DATEVALUEONLY	equ 0x00000002
VAR_LOCALBOOL		equ 0x00000010

VarUI1FromI2 proto WINAPI :SWORD, :ptr
VarUI1FromI4 proto WINAPI :LONG, :ptr
VarUI1FromR4 proto WINAPI :FLOAT, :ptr
VarUI1FromR8 proto WINAPI :DOUBLE, :ptr
VarUI1FromCy proto WINAPI :CY, :ptr
VarUI1FromDate proto WINAPI :DATE, :ptr
VarUI1FromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarUI1FromDisp proto WINAPI :ptr, :LCID, :ptr
VarUI1FromBool proto WINAPI :VARIANT_BOOL, :ptr
VarUI1FromI1 proto WINAPI :CHAR, :ptr
VarUI1FromUI2 proto WINAPI :USHORT, :ptr
VarUI1FromUI4 proto WINAPI :ULONG, :ptr
VarUI1FromDec proto WINAPI :ptr, :ptr
VarI2FromUI1 proto WINAPI :BYTE, :ptr
VarI2FromI4 proto WINAPI :LONG, :ptr
VarI2FromR4 proto WINAPI :FLOAT, :ptr
VarI2FromR8 proto WINAPI :DOUBLE, :ptr
VarI2FromCy proto WINAPI :CY, :ptr
VarI2FromDate proto WINAPI :DATE, :ptr
VarI2FromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarI2FromDisp proto WINAPI :ptr, :LCID, :ptr
VarI2FromBool proto WINAPI :VARIANT_BOOL, :ptr
VarI2FromI1 proto WINAPI :CHAR, :ptr
VarI2FromUI2 proto WINAPI :USHORT, :ptr
VarI2FromUI4 proto WINAPI :ULONG, :ptr
VarI2FromDec proto WINAPI :ptr, :ptr
VarI4FromUI1 proto WINAPI :BYTE, :ptr
VarI4FromI2 proto WINAPI :SWORD, :ptr
VarI4FromR4 proto WINAPI :FLOAT, :ptr
VarI4FromR8 proto WINAPI :DOUBLE, :ptr
VarI4FromCy proto WINAPI :CY, :ptr
VarI4FromDate proto WINAPI :DATE, :ptr
VarI4FromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarI4FromDisp proto WINAPI :ptr, :LCID, :ptr
VarI4FromBool proto WINAPI :VARIANT_BOOL, :ptr
VarI4FromI1 proto WINAPI :CHAR, :ptr
VarI4FromUI2 proto WINAPI :USHORT, :ptr
VarI4FromUI4 proto WINAPI :ULONG, :ptr
VarI4FromDec proto WINAPI :ptr, :ptr
VarI4FromInt proto WINAPI :SINT, :ptr
VarR4FromUI1 proto WINAPI :BYTE, :ptr
VarR4FromI2 proto WINAPI :SWORD, :ptr
VarR4FromI4 proto WINAPI :LONG, :ptr
VarR4FromR8 proto WINAPI :DOUBLE, :ptr
VarR4FromCy proto WINAPI :CY, :ptr
VarR4FromDate proto WINAPI :DATE, :ptr
VarR4FromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarR4FromDisp proto WINAPI :ptr, :LCID, :ptr
VarR4FromBool proto WINAPI :VARIANT_BOOL, :ptr
VarR4FromI1 proto WINAPI :CHAR, :ptr
VarR4FromUI2 proto WINAPI :USHORT, :ptr
VarR4FromUI4 proto WINAPI :ULONG, :ptr
VarR4FromDec proto WINAPI :ptr, :ptr
VarR8FromUI1 proto WINAPI :BYTE, :ptr
VarR8FromI2 proto WINAPI :SWORD, :ptr
VarR8FromI4 proto WINAPI :LONG, :ptr
VarR8FromR4 proto WINAPI :FLOAT, :ptr
VarR8FromCy proto WINAPI :CY, :ptr
VarR8FromDate proto WINAPI :DATE, :ptr
VarR8FromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarR8FromDisp proto WINAPI :ptr, :LCID, :ptr
VarR8FromBool proto WINAPI :VARIANT_BOOL, :ptr
VarR8FromI1 proto WINAPI :CHAR, :ptr
VarR8FromUI2 proto WINAPI :USHORT, :ptr
VarR8FromUI4 proto WINAPI :ULONG, :ptr
VarR8FromDec proto WINAPI :ptr, :ptr
VarDateFromUI1 proto WINAPI :BYTE, :ptr
VarDateFromI2 proto WINAPI :SWORD, :ptr
VarDateFromI4 proto WINAPI :LONG, :ptr
VarDateFromR4 proto WINAPI :FLOAT, :ptr
VarDateFromR8 proto WINAPI :DOUBLE, :ptr
VarDateFromCy proto WINAPI :CY, :ptr
VarDateFromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarDateFromDisp proto WINAPI :ptr, :LCID, :ptr
VarDateFromBool proto WINAPI :VARIANT_BOOL, :ptr
VarDateFromI1 proto WINAPI :CHAR, :ptr
VarDateFromUI2 proto WINAPI :USHORT, :ptr
VarDateFromUI4 proto WINAPI :ULONG, :ptr
VarDateFromDec proto WINAPI :ptr, :ptr
VarCyFromUI1 proto WINAPI :BYTE, :ptr
VarCyFromI2 proto WINAPI :SWORD, :ptr
VarCyFromI4 proto WINAPI :LONG, :ptr
VarCyFromR4 proto WINAPI :FLOAT, :ptr
VarCyFromR8 proto WINAPI :DOUBLE, :ptr
VarCyFromDate proto WINAPI :DATE, :ptr
VarCyFromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarCyFromDisp proto WINAPI :ptr, :LCID, :ptr
VarCyFromBool proto WINAPI :VARIANT_BOOL, :ptr
VarCyFromI1 proto WINAPI :CHAR, :ptr
VarCyFromUI2 proto WINAPI :USHORT, :ptr
VarCyFromUI4 proto WINAPI :ULONG, :ptr
VarCyFromDec proto WINAPI :ptr, :ptr
VarBstrFromUI1 proto WINAPI :BYTE, :LCID, :ULONG, :ptr
VarBstrFromI2 proto WINAPI :SWORD, :LCID, :ULONG, :ptr
VarBstrFromI4 proto WINAPI :LONG, :LCID, :ULONG, :ptr
VarBstrFromR4 proto WINAPI :FLOAT, :LCID, :ULONG, :ptr
VarBstrFromR8 proto WINAPI :DOUBLE, :LCID, :ULONG, :ptr
VarBstrFromCy proto WINAPI :CY, :LCID, :ULONG, :ptr
VarBstrFromDate proto WINAPI :DATE, :LCID, :ULONG, :ptr
VarBstrFromDisp proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarBstrFromBool proto WINAPI :VARIANT_BOOL, :LCID, :ULONG, :ptr
VarBstrFromI1 proto WINAPI :CHAR, :LCID, :ULONG, :ptr
VarBstrFromUI2 proto WINAPI :USHORT, :LCID, :ULONG, :ptr
VarBstrFromUI4 proto WINAPI :ULONG, :LCID, :ULONG, :ptr
VarBstrFromDec proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarBoolFromUI1 proto WINAPI :BYTE, :ptr
VarBoolFromI2 proto WINAPI :SWORD, :ptr
VarBoolFromI4 proto WINAPI :LONG, :ptr
VarBoolFromR4 proto WINAPI :FLOAT, :ptr
VarBoolFromR8 proto WINAPI :DOUBLE, :ptr
VarBoolFromDate proto WINAPI :DATE, :ptr
VarBoolFromCy proto WINAPI :CY, :ptr
VarBoolFromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarBoolFromDisp proto WINAPI :ptr, :LCID, :ptr
VarBoolFromI1 proto WINAPI :CHAR, :ptr
VarBoolFromUI2 proto WINAPI :USHORT, :ptr
VarBoolFromUI4 proto WINAPI :ULONG, :ptr
VarBoolFromDec proto WINAPI :ptr, :ptr

VarI1FromUI1 proto WINAPI :BYTE, :ptr
VarI1FromI2 proto WINAPI :SWORD, :ptr
VarI1FromI4 proto WINAPI :LONG, :ptr
VarI1FromR4 proto WINAPI :FLOAT, :ptr
VarI1FromR8 proto WINAPI :DOUBLE, :ptr
VarI1FromDate proto WINAPI :DATE, :ptr
VarI1FromCy proto WINAPI :CY, :ptr
VarI1FromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarI1FromDisp proto WINAPI :ptr, :LCID, :ptr
VarI1FromBool proto WINAPI :VARIANT_BOOL, :ptr
VarI1FromUI2 proto WINAPI :USHORT, :ptr
VarI1FromUI4 proto WINAPI :ULONG, :ptr
VarI1FromDec proto WINAPI :ptr, : ptr
VarUI2FromUI1 proto WINAPI :BYTE, :ptr
VarUI2FromI2 proto WINAPI :SWORD, :ptr
VarUI2FromI4 proto WINAPI :LONG, :ptr
VarUI2FromR4 proto WINAPI :FLOAT, :ptr
VarUI2FromR8 proto WINAPI :DOUBLE, :ptr
VarUI2FromDate proto WINAPI :DATE, :ptr
VarUI2FromCy proto WINAPI :CY, :ptr
VarUI2FromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarUI2FromDisp proto WINAPI :ptr, :LCID, :ptr
VarUI2FromBool proto WINAPI :VARIANT_BOOL, :ptr
VarUI2FromI1 proto WINAPI :CHAR, :ptr
VarUI2FromUI4 proto WINAPI :ULONG, :ptr
VarUI2FromDec proto WINAPI :ptr, :ptr
VarUI4FromUI1 proto WINAPI :BYTE, :ptr
VarUI4FromI2 proto WINAPI :SWORD, :ptr
VarUI4FromI4 proto WINAPI :LONG, :ptr
VarUI4FromR4 proto WINAPI :FLOAT, :ptr
VarUI4FromR8 proto WINAPI :DOUBLE, :ptr
VarUI4FromDate proto WINAPI :DATE, :ptr
VarUI4FromCy proto WINAPI :CY, :ptr
VarUI4FromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarUI4FromDisp proto WINAPI :ptr, :LCID, :ptr
VarUI4FromBool proto WINAPI :VARIANT_BOOL, :ptr
VarUI4FromI1 proto WINAPI :CHAR, :ptr
VarUI4FromUI2 proto WINAPI :USHORT, :ptr
VarUI4FromDec proto WINAPI :ptr, :ptr
VarDecFromUI1 proto WINAPI :BYTE, :ptr
VarDecFromI2 proto WINAPI :SWORD, :ptr
VarDecFromI4 proto WINAPI :LONG, :ptr
VarDecFromR4 proto WINAPI :FLOAT, :ptr
VarDecFromR8 proto WINAPI :DOUBLE, :ptr
VarDecFromDate proto WINAPI :DATE, :ptr
VarDecFromCy proto WINAPI :CY, :ptr
VarDecFromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr
VarDecFromDisp proto WINAPI :ptr, :LCID, :ptr
VarDecFromBool proto WINAPI :VARIANT_BOOL, :ptr
VarDecFromI1 proto WINAPI :CHAR, :ptr
VarDecFromUI2 proto WINAPI :USHORT, :ptr
VarDecFromUI4 proto WINAPI :ULONG, :ptr

VarUI4FromUI4 proto watcall :dword, :ptr {
	mov [_2],_1
	}
VarI4FromI4 proto watcall :sdword, :ptr {
	mov [_2],_1
	}

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

VarParseNumFromStr proto WINAPI :ptr, :LCID, :ULONG, :ptr, :ptr
VarNumFromParseNum proto WINAPI :ptr, :ptr, :ULONG, :ptr
VarAdd proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarAnd proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarCat proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarDiv proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarEqv proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarIdiv proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarImp proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarMod proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarMul proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarOr proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarPow proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarSub proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT
VarXor proto WINAPI :LPVARIANT, :LPVARIANT, :LPVARIANT

VarAbs proto WINAPI :LPVARIANT, :LPVARIANT
VarFix proto WINAPI :LPVARIANT, :LPVARIANT
VarInt proto WINAPI :LPVARIANT, :LPVARIANT
VarNeg proto WINAPI :LPVARIANT, :LPVARIANT
VarNot proto WINAPI :LPVARIANT, :LPVARIANT
VarRound proto WINAPI :LPVARIANT, :SINT, :LPVARIANT
VarCmp proto WINAPI :LPVARIANT, :LPVARIANT, :LCID
VarDecAdd proto WINAPI :LPDECIMAL, :LPDECIMAL, :LPDECIMAL
VarDecDiv proto WINAPI :LPDECIMAL, :LPDECIMAL, :LPDECIMAL
VarDecMul proto WINAPI :LPDECIMAL, :LPDECIMAL, :LPDECIMAL
VarDecSub proto WINAPI :LPDECIMAL, :LPDECIMAL, :LPDECIMAL
VarDecAbs proto WINAPI :LPDECIMAL, :LPDECIMAL
VarDecFix proto WINAPI :LPDECIMAL, :LPDECIMAL
VarDecInt proto WINAPI :LPDECIMAL, :LPDECIMAL
VarDecNeg proto WINAPI :LPDECIMAL, :LPDECIMAL
VarDecRound proto WINAPI :LPDECIMAL, :SINT,:LPDECIMAL
VarDecCmp proto WINAPI :LPDECIMAL, :LPDECIMAL
VarDecCmpR8 proto WINAPI :LPDECIMAL, :DOUBLE
VarCyAdd proto WINAPI :CY, :CY, :LPCY
VarCyMul proto WINAPI :CY, :CY, :LPCY
VarCyMulI4 proto WINAPI :CY, :LONG, :LPCY
VarCySub proto WINAPI :CY, :CY, :LPCY
VarCyAbs proto WINAPI :CY, :LPCY
VarCyFix proto WINAPI :CY, :LPCY
VarCyInt proto WINAPI :CY, :LPCY
VarCyNeg proto WINAPI :CY, :LPCY
VarCyRound proto WINAPI :CY, :SINT, :LPCY
VarCyCmp proto WINAPI :CY, :CY
VarCyCmpR8 proto WINAPI :CY, :DOUBLE
VarBstrCat proto WINAPI :BSTR, :BSTR, :LPBSTR
VarBstrCmp proto WINAPI :BSTR, :BSTR, :LCID
VarR8Pow proto WINAPI :DOUBLE, :DOUBLE, :ptr
VarR4CmpR8 proto WINAPI :FLOAT, :DOUBLE
VarR8Round proto WINAPI :DOUBLE, :SINT, :ptr

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

VarDateFromUdate proto WINAPI :ptr, :ULONG, :ptr
VarUdateFromDate proto WINAPI :DATE, :ULONG, :ptr
GetAltMonthNames proto WINAPI :LCID, :ptr

VAR_FORMAT_NOSUBSTITUTE equ 0x00000010

VarFormat proto WINAPI :LPVARIANT, :LPOLESTR, :SINT, :SINT, :ULONG, :ptr
VarFormatDateTime proto WINAPI :LPVARIANT, :SINT, :ULONG, :ptr
VarFormatNumber proto WINAPI :LPVARIANT, :SINT, :SINT, :SINT, :SINT, :ULONG, :ptr
VarFormatPercent proto WINAPI :LPVARIANT, :SINT, :SINT, :SINT, :SINT, :ULONG, :ptr
VarFormatCurrency proto WINAPI :LPVARIANT, :SINT, :SINT, :SINT, :SINT, :ULONG, :ptr
VarWeekdayName proto WINAPI :SINT, :SINT, :SINT, :ULONG, :ptr
VarMonthName proto WINAPI :SINT, :SINT, :ULONG, :ptr
VarFormatFromTokens proto WINAPI :LPVARIANT, :LPOLESTR, :LPBYTE, :ULONG, :ptr, :LCID
VarTokenizeFormatString proto WINAPI :LPOLESTR, :LPBYTE, :SINT, :SINT, :SINT, :LCID

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
LHashValOfNameSysA proto WINAPI :SYSKIND, :LCID, :LPCSTR
endif
LHashValOfNameSys proto WINAPI :SYSKIND, :LCID, :ptr

LHashValOfName macro lcid, szName
	exitm<LHashValOfNameSys(SYS_WIN32, lcid, szName)>
	endm

WHashValOfLHashVal macro lhashval
	exitm<0x0000ffff AND lhashval>
	endm

IsHashValCompatible macro lhashval1, lhashval2
	exitm<(((0x00ff0000 AND (lhashval1)) EQ (0x00ff0000 AND (lhashval2))))>
	endm

LoadTypeLib proto WINAPI :ptr, :ptr

REGKIND			typedef SDWORD
REGKIND_DEFAULT		equ 0
REGKIND_REGISTER	equ 1
REGKIND_NONE		equ 2

LoadTypeLibEx proto WINAPI :LPCOLESTR, :REGKIND, :ptr
LoadRegTypeLib proto WINAPI :REFGUID, :WORD, :WORD, :LCID, :ptr
QueryPathOfRegTypeLib proto WINAPI :REFGUID, :USHORT, :USHORT, :LCID, :LPBSTR
RegisterTypeLib proto WINAPI :ptr, :ptr, :ptr
UnRegisterTypeLib proto WINAPI :REFGUID, :WORD, :WORD, :LCID, :SYSKIND
CreateTypeLib proto WINAPI :SYSKIND, :ptr, :ptr
CreateTypeLib2 proto WINAPI :SYSKIND, :LPCOLESTR, :ptr

LPDISPATCH		typedef ptr IDispatch

PARAMDATA		STRUC
szName			LPOLESTR ?
vt			VARTYPE ?
PARAMDATA		ENDS
LPPARAMDATA		typedef ptr PARAMDATA

METHODDATA		STRUC
szName			LPOLESTR ?
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

DispGetParam proto WINAPI :ptr, :UINT, :VARTYPE, :ptr, :ptr
DispGetIDsOfNames proto WINAPI :ptr, :ptr, :UINT, :ptr
DispInvoke proto WINAPI :ptr, :ptr, :DISPID, :WORD, :ptr, :ptr, :ptr, :ptr
CreateDispTypeInfo proto WINAPI :ptr, :LCID, :ptr
CreateStdDispatch proto WINAPI :ptr, :ptr, :ptr, :ptr
DispCallFunc proto WINAPI :ptr, :ULONG, :CALLCONV, :VARTYPE, :UINT, :ptr, :ptr, :ptr

ACTIVEOBJECT_STRONG	equ 0x0
ACTIVEOBJECT_WEAK	equ 0x1

RegisterActiveObject proto WINAPI :ptr, :REFCLSID, :DWORD, :ptr
RevokeActiveObject proto WINAPI :DWORD, :ptr
GetActiveObject proto WINAPI :REFCLSID, :ptr, :ptr
SetErrorInfo proto WINAPI :ULONG, :ptr
GetErrorInfo proto WINAPI :ULONG, :ptr
CreateErrorInfo proto WINAPI :ptr
GetRecordInfoFromTypeInfo proto WINAPI :ptr, :ptr
GetRecordInfoFromGuids proto WINAPI :REFGUID, :ULONG, :ULONG, :LCID, :REFGUID, :ptr
OaBuildVersion proto WINAPI
ClearCustData proto WINAPI :LPCUSTDATA

if __STDC__ OR defined(NONAMELESSUNION)
V_UNION macro X, Y
	exitm<(X.n1.n2.n3.Y)>
	endm
V_VT macro X
	exitm<(X.n1.n2.vt)>
	endm
V_RECORDINFO macro X
	exitm<(X.n1.n2.n3.brecVal.pRecInfo)>
	endm
V_RECORD macro X
	exitm<(X.n1.n2.n3.brecVal.pvRecord)>
	endm
else
V_UNION proto fastcall X:ptr VARIANT, Y:abs {
	retm<[rcx].VARIANT.Y>
	}
V_VT proto fastcall X:ptr VARIANT {
	retm<[rcx].VARIANT.vt>
	}
V_RECORDINFO proto fastcall X:ptr VARIANT {
	retm<[rcx].VARIANT.pRecInfo>
	}
V_RECORD proto fastcall X:ptr VARIANT {
	retm<[rcx].VARIANT.pvRecord>
	}
endif

V_ISBYREF macro X
	exitm<(V_VT(X) & VT_BYREF)>
	endm
V_ISARRAY macro X
	exitm<(V_VT(X) & VT_ARRAY)>
	endm
V_ISVECTOR macro X
	exitm<(V_VT(X) & VT_VECTOR)>
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
V_DISPATCH proto fastcall X:ptr VARIANT {
	retm<[rcx].VARIANT.pdispVal>
	}
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

endif

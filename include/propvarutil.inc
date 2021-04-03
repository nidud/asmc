include winapifamily.inc

NTSTATUS typedef LONG

include propapi.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include shtypes.inc
include shlwapi.inc

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum PSTIME_FLAGS {
    PSTF_UTC   = 0x00000000,
    PSTF_LOCAL = 0x00000001,
    }

InitPropVariantFromResource proto WINAPI \
		 hinst: HINSTANCE,
		    id: UINT,
	      ppropvar: ptr PROPVARIANT

InitPropVariantFromBuffer proto WINAPI \
		    pv: ptr void,
		    cb: UINT,
	      ppropvar: ptr PROPVARIANT

InitPropVariantFromCLSID proto WINAPI \
		 clsid: REFCLSID,
	      ppropvar: ptr PROPVARIANT

InitPropVariantFromGUIDAsString proto WINAPI \
		  guid: REFGUID,
	      ppropvar: ptr PROPVARIANT

InitPropVariantFromFileTime proto WINAPI \
		 pftIn: ptr FILETIME,
	      ppropvar: ptr PROPVARIANT

InitPropVariantFromPropVariantVectorElem proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		 iElem: ULONG,
	      ppropvar: ptr PROPVARIANT

InitPropVariantVectorFromPropVariant proto WINAPI \
	 propvarSingle: REFPROPVARIANT,
	ppropvarVector: ptr PROPVARIANT


InitPropVariantFromStrRet proto WINAPI \
	       pstrret: ptr STRRET,
		  pidl: PCUITEMID_CHILD,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromBooleanVector proto WINAPI \
		  prgf: ptr BOOL,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromInt16Vector proto WINAPI \
		  prgn: ptr SWORD,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromUInt16Vector proto WINAPI \
		  prgn: ptr USHORT,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromInt32Vector proto WINAPI \
		  prgn: ptr LONG,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromUInt32Vector proto WINAPI \
		  prgn: ptr ULONG,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromInt64Vector proto WINAPI \
		  prgn: ptr LONGLONG,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromUInt64Vector proto WINAPI \
		  prgn: ptr ULONGLONG,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromDoubleVector proto WINAPI \
		  prgn: ptr DOUBLE,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromFileTimeVector proto WINAPI \
		 prgft: ptr FILETIME,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromStringVector proto WINAPI \
		 prgsz: ptr PCWSTR,
		cElems: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromStringAsVector proto WINAPI \
		   psz: PCWSTR,
	      ppropvar: ptr PROPVARIANT



InitPropVariantFromBoolean proto WINAPI \
		  fVal: BOOL,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromInt16 proto WINAPI \
		  nVal: SWORD,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromUInt16 proto WINAPI \
		 uiVal: USHORT,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromInt32 proto WINAPI \
		  lVal: LONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromUInt32 proto WINAPI \
		 ulVal: ULONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromInt64 proto WINAPI \
		 llVal: LONGLONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromUInt64 proto WINAPI \
		ullVal: ULONGLONG,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromDouble proto WINAPI \
		dblVal: DOUBLE,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromString proto WINAPI \
		   psz: PCWSTR,
	      ppropvar: ptr PROPVARIANT


InitPropVariantFromGUIDAsBuffer proto WINAPI \
		  guid: REFGUID,
	      ppropvar: ptr PROPVARIANT


IsPropVariantVector proto WINAPI \
	       propvar: REFPROPVARIANT


IsPropVariantString proto WINAPI \
	       propvar: REFPROPVARIANT



PropVariantToBooleanWithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	      fDefault: BOOL


PropVariantToInt16WithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	      iDefault: SWORD


PropVariantToUInt16WithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	     uiDefault: USHORT


PropVariantToInt32WithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	      lDefault: LONG


PropVariantToUInt32WithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	     ulDefault: ULONG


PropVariantToInt64WithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	     llDefault: LONGLONG


PropVariantToUInt64WithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	    ullDefault: ULONGLONG


PropVariantToDoubleWithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	    dblDefault: DOUBLE


PropVariantToStringWithDefault proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	    pszDefault: LPCWSTR



PropVariantToBoolean proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		 pfRet: ptr BOOL


PropVariantToInt16 proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		 piRet: ptr SWORD


PropVariantToUInt16 proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		puiRet: ptr USHORT


PropVariantToInt32 proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		 plRet: ptr LONG


PropVariantToUInt32 proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		pulRet: ptr ULONG


PropVariantToInt64 proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		pllRet: ptr LONGLONG


PropVariantToUInt64 proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	       pullRet: ptr ULONGLONG


PropVariantToDouble proto WINAPI \
	     propvarIn: REFPROPVARIANT,
	       pdblRet: ptr DOUBLE


PropVariantToBuffer proto WINAPI \
	       propvar: REFPROPVARIANT,
		    pv: ptr void,
		    cb: UINT


PropVariantToString proto WINAPI \
	       propvar: REFPROPVARIANT,
		   psz: PWSTR,
		   cch: UINT


PropVariantToGUID proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pguid: ptr GUID

PropVariantToStringAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
	       ppszOut: ptr PWSTR

PropVariantToBSTR proto WINAPI \
	       propvar: REFPROPVARIANT,
	      pbstrOut:ptr BSTR

PropVariantToStrRet proto WINAPI \
	       propvar: REFPROPVARIANT,
	       pstrret: ptr STRRET


PropVariantToFileTime proto WINAPI \
	       propvar: REFPROPVARIANT,
	       pstfOut: PSTIME_FLAGS,
		pftOut: ptr FILETIME



PropVariantToCLSID proto WINAPI \
	       propvar: REFPROPVARIANT,
		pclsid: ptr CLSID




PropVariantGetElementCount proto WINAPI \
	       propvar: REFPROPVARIANT



PropVariantToBooleanVector proto WINAPI \
	       propvar: REFPROPVARIANT,
		  prgf: ptr BOOL,
		  crgf: ULONG,
		pcElem: ptr ULONG


PropVariantToInt16Vector proto WINAPI \
	       propvar: REFPROPVARIANT,
		  prgn: ptr SWORD,
		  crgn: ULONG,
		pcElem: ptr ULONG


PropVariantToUInt16Vector proto WINAPI \
	       propvar: REFPROPVARIANT,
		  prgn: ptr USHORT,
		  crgn: ULONG,
		pcElem: ptr ULONG


PropVariantToInt32Vector proto WINAPI \
	       propvar: REFPROPVARIANT,
		  prgn: ptr LONG,
		  crgn: ULONG,
		pcElem: ptr ULONG


PropVariantToUInt32Vector proto WINAPI \
	       propvar: REFPROPVARIANT,
		  prgn: ptr ULONG,
		  crgn: ULONG,
		pcElem: ptr ULONG


PropVariantToInt64Vector proto WINAPI \
	       propvar: REFPROPVARIANT,
		  prgn: ptr LONGLONG,
		  crgn: ULONG,
		pcElem: ptr ULONG


PropVariantToUInt64Vector proto WINAPI \
	       propvar: REFPROPVARIANT,
		  prgn: ptr ULONGLONG,
		  crgn: ULONG,
		pcElem: ptr ULONG


PropVariantToDoubleVector proto WINAPI \
	       propvar: REFPROPVARIANT,
		  prgn: ptr DOUBLE,
		  crgn: ULONG,
		pcElem: ptr ULONG


PropVariantToFileTimeVector proto WINAPI \
	       propvar: REFPROPVARIANT,
		 prgft: ptr FILETIME,
		 crgft: ULONG,
		pcElem: ptr ULONG

PropVariantToStringVector proto WINAPI \
	       propvar: REFPROPVARIANT,
		 prgsz: ptr PWSTR,
		 crgsz: ULONG,
		pcElem: ptr ULONG


PropVariantToBooleanVectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pprgf: ptr ptr BOOL,
		pcElem: ptr ULONG

PropVariantToInt16VectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pprgf: ptr ptr SWORD,
		pcElem: ptr ULONG

PropVariantToUInt16VectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pprgf: ptr ptr WORD,
		pcElem: ptr ULONG

PropVariantToInt32VectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pprgf: ptr ptr LONG,
		pcElem: ptr ULONG

PropVariantToUInt32VectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pprgf: ptr ptr ULONG,
		pcElem: ptr ULONG

PropVariantToInt64VectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pprgf: ptr ptr LONGLONG,
		pcElem: ptr ULONG

PropVariantToUInt64VectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pprgf: ptr ptr ULONGLONG,
		pcElem: ptr ULONG

PropVariantToDoubleVectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		 pprgf: ptr ptr real8,
		pcElem: ptr ULONG

PropVariantToFileTimeVectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		pprgft: ptr ptr FILETIME,
		pcElem: ptr ULONG

PropVariantToStringVectorAlloc proto WINAPI \
	       propvar: REFPROPVARIANT,
		pprgsz: ptr ptr PWSTR,
		pcElem: ptr ULONG


PropVariantGetBooleanElem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		 pfVal: ptr BOOL


PropVariantGetInt16Elem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		 pnVal: ptr SWORD


PropVariantGetUInt16Elem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		 pnVal: ptr USHORT


PropVariantGetInt32Elem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		 pnVal: ptr LONG


PropVariantGetUInt32Elem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		 pnVal: ptr ULONG


PropVariantGetInt64Elem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		 pnVal: ptr LONGLONG


PropVariantGetUInt64Elem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		 pnVal: ptr ULONGLONG


PropVariantGetDoubleElem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		 pnVal: ptr DOUBLE


PropVariantGetFileTimeElem proto WINAPI \
	       propvar: REFPROPVARIANT,
		 iElem: ULONG,
		pftVal: ptr FILETIME

PropVariantGetStringElem proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		 iElem: ULONG,
	       ppszVal: ptr PWSTR


PropVariantGetElem proto WINAPI \
	     propvarIn: REFPROPVARIANT,
		 iElem: ULONG,
	      ppropvar: ptr PROPVARIANT


ClearPropVariantArray proto WINAPI \
	     rgPropVar: ptr PROPVARIANT,
		 cVars: UINT

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum PROPVAR_COMPARE_UNIT {
    PVCU_DEFAULT = 0,
    PVCU_SECOND	 = 1,
    PVCU_MINUTE	 = 2,
    PVCU_HOUR	 = 3,
    PVCU_DAY	 = 4,
    PVCU_MONTH	 = 5,
    PVCU_YEAR	 = 6
    }

.enum PROPVAR_COMPARE_FLAGS {
    PVCF_DEFAULT		 = 0x00000000,
    PVCF_TREATEMPTYASGREATERTHAN = 0x00000001,
    PVCF_USESTRCMP		 = 0x00000002,
    PVCF_USESTRCMPC		 = 0x00000004,
    PVCF_USESTRCMPI		 = 0x00000008,
    PVCF_USESTRCMPIC		 = 0x00000010,
    PVCF_DIGITSASNUMBERS_CASESENSITIVE = 0x00000020,
    }

PropVariantCompareEx proto WINAPI \
	      propvar1: REFPROPVARIANT,
	      propvar2: REFPROPVARIANT,
		  unit: PROPVAR_COMPARE_UNIT,
		 flags: PROPVAR_COMPARE_FLAGS

PropVariantCompare proto WINAPI \
	      propvar1: REFPROPVARIANT,
	      propvar2: REFPROPVARIANT

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum PROPVAR_CHANGE_FLAGS {
    PVCHF_DEFAULT	    = 0x00000000,
    PVCHF_NOVALUEPROP	    = 0x00000001,
    PVCHF_ALPHABOOL	    = 0x00000002,
    PVCHF_NOUSEROVERRIDE    = 0x00000004,
    PVCHF_LOCALBOOL	    = 0x00000008,
    PVCHF_NOHEXSTRING	    = 0x00000010,
    }


PropVariantChangeType proto WINAPI \
	  ppropvarDest: ptr PROPVARIANT,
	    propvarSrc: REFPROPVARIANT,
		 flags: PROPVAR_CHANGE_FLAGS,
		    vt: VARTYPE


PropVariantToVariant proto WINAPI \
	      pPropVar: ptr PROPVARIANT,
		  pVar: ptr VARIANT


VariantToPropVariant proto WINAPI \
		  pVar: ptr VARIANT,
	      pPropVar: ptr PROPVARIANT


StgSerializePropVariant proto WINAPI \
	      ppropvar: ptr PROPVARIANT,
		ppProp: ptr ptr SERIALIZEDPROPERTYVALUE,
		   pcb: ptr ULONG


StgDeserializePropVariant proto WINAPI \
		 pprop: ptr SERIALIZEDPROPERTYVALUE,
		 cbMax: ULONG,
	      ppropvar: ptr PROPVARIANT


IsVarTypeFloat proto WINAPI \
		    vt: VARTYPE


IsVariantArray proto WINAPI \
		   var: REFVARIANT


IsVariantString proto WINAPI \
		   var: REFVARIANT


IsVarTypeNumber proto WINAPI \
		    vt: VARTYPE


IsVarTypeInteger proto WINAPI \
		    vt: VARTYPE


InitVariantFromResource proto WINAPI \
		 hinst: HINSTANCE,
		    id: UINT,
		  pvar: ptr VARIANT


InitVariantFromBuffer proto WINAPI \
		    pv: ptr void,
		    cb: UINT,
		  pvar: ptr VARIANT


InitVariantFromGUIDAsString proto WINAPI \
		  guid: REFGUID,
		  pvar: ptr VARIANT


InitVariantFromFileTime proto WINAPI \
		   pft: ptr FILETIME,
		  pvar: ptr VARIANT


InitVariantFromFileTimeArray proto WINAPI \
		 prgft: ptr FILETIME,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromStrRet proto WINAPI \
	       pstrret: ptr STRRET,
		  pidl: PCUITEMID_CHILD,
		  pvar: ptr VARIANT


InitVariantFromVariantArrayElem proto WINAPI \
		 varIn: REFVARIANT,
		 iElem: ULONG,
		  pvar: ptr VARIANT


InitVariantFromBooleanArray proto WINAPI \
		  prgf: ptr BOOL,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromInt16Array proto WINAPI \
		  prgn: ptr SWORD,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromUInt16Array proto WINAPI \
		  prgn: ptr USHORT,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromInt32Array proto WINAPI \
		  prgn: ptr LONG,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromUInt32Array proto WINAPI \
		  prgn: ptr ULONG,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromInt64Array proto WINAPI \
		  prgn: ptr LONGLONG,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromUInt64Array proto WINAPI \
		  prgn: ptr ULONGLONG,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromDoubleArray proto WINAPI \
		  prgn: ptr DOUBLE,
		cElems: ULONG,
		  pvar: ptr VARIANT


InitVariantFromStringArray proto WINAPI \
		 prgsz: ptr PCWSTR,
		cElems: ULONG,
		  pvar: ptr VARIANT

InitVariantFromBoolean proto WINAPI \
		  fVal: BOOL,
		  pvar: ptr VARIANT


InitVariantFromInt16 proto WINAPI \
		  iVal: SWORD,
		  pvar: ptr VARIANT


InitVariantFromUInt16 proto WINAPI \
		 uiVal: USHORT,
		  pvar: ptr VARIANT


InitVariantFromInt32 proto WINAPI \
		  lVal: LONG,
		  pvar: ptr VARIANT


InitVariantFromUInt32 proto WINAPI \
		 ulVal: ULONG,
		  pvar: ptr VARIANT


InitVariantFromInt64 proto WINAPI \
		 llVal: LONGLONG,
		  pvar: ptr VARIANT


InitVariantFromUInt64 proto WINAPI \
		ullVal: ULONGLONG,
		  pvar: ptr VARIANT


InitVariantFromDouble proto WINAPI \
		dblVal: DOUBLE,
		  pvar: ptr VARIANT


InitVariantFromString proto WINAPI \
		   psz: PCWSTR,
		  pvar: ptr VARIANT


InitVariantFromDispatch proto WINAPI \
		 pdisp: ptr IDispatch,
		  pvar: ptr VARIANT


InitVariantFromDosDateTime proto WINAPI \
		 wDate: WORD,
		 wTime: WORD,
		  pvar: ptr VARIANT


InitVariantFromGUIDAsBuffer proto WINAPI \
		  guid: REFGUID,
		  pvar: ptr VARIANT


VariantToBooleanWithDefault proto WINAPI \
		 varIn: REFVARIANT,
	      fDefault: BOOL


VariantToInt16WithDefault proto WINAPI \
		 varIn: REFVARIANT,
	      iDefault: SWORD


VariantToUInt16WithDefault proto WINAPI \
		 varIn: REFVARIANT,
	     uiDefault: USHORT


VariantToInt32WithDefault proto WINAPI \
		 varIn: REFVARIANT,
	      lDefault: LONG


VariantToUInt32WithDefault proto WINAPI \
		 varIn: REFVARIANT,
	     ulDefault: ULONG


VariantToInt64WithDefault proto WINAPI \
		 varIn: REFVARIANT,
	     llDefault: LONGLONG


VariantToUInt64WithDefault proto WINAPI \
		 varIn: REFVARIANT,
	    ullDefault: ULONGLONG


VariantToDoubleWithDefault proto WINAPI \
		 varIn: REFVARIANT,
	    dblDefault: DOUBLE


VariantToStringWithDefault proto WINAPI \
		 varIn: REFVARIANT,
	    pszDefault: LPCWSTR



VariantToBoolean proto WINAPI \
		 varIn: REFVARIANT,
		 pfRet: ptr BOOL


VariantToInt16 proto WINAPI \
		 varIn: REFVARIANT,
		 piRet: ptr SWORD


VariantToUInt16 proto WINAPI \
		 varIn: REFVARIANT,
		puiRet: ptr USHORT


VariantToInt32 proto WINAPI \
		 varIn: REFVARIANT,
		 plRet: ptr LONG


VariantToUInt32 proto WINAPI \
		 varIn: REFVARIANT,
		pulRet: ptr ULONG


VariantToInt64 proto WINAPI \
		 varIn: REFVARIANT,
		pllRet: ptr LONGLONG


VariantToUInt64 proto WINAPI \
		 varIn: REFVARIANT,
	       pullRet: ptr ULONGLONG


VariantToDouble proto WINAPI \
		 varIn: REFVARIANT,
	       pdblRet: ptr DOUBLE


VariantToBuffer proto WINAPI \
		 varIn: REFVARIANT,
		    pv: ptr void,
		    cb: UINT


VariantToGUID proto WINAPI \
		 varIn: REFVARIANT,
		 pguid: ptr GUID


VariantToString proto WINAPI \
		 varIn: REFVARIANT,
		pszBuf: PWSTR,
		cchBuf: UINT

VariantToStringAlloc proto WINAPI \
		 varIn: REFVARIANT,
	       ppszBuf: ptr PWSTR

VariantToDosDateTime proto WINAPI \
		 varIn: REFVARIANT,
		pwDate: ptr WORD,
		pwTime: ptr WORD

VariantToStrRet proto WINAPI \
		 varIn: REFVARIANT,
	       pstrret: ptr STRRET

VariantToFileTime proto WINAPI \
		 varIn: REFVARIANT,
		stfOut: PSTIME_FLAGS,
		pftOut: ptr FILETIME


VariantGetElementCount proto WINAPI \
		 varIn: REFVARIANT



VariantToBooleanArray proto WINAPI \
		   var: REFVARIANT,
		  prgf: ptr BOOL,
		  crgn: ULONG,
		pcElem: ptr ULONG


VariantToInt16Array proto WINAPI \
		   var: REFVARIANT,
		  prgn: ptr SWORD,
		  crgn: ULONG,
		pcElem: ptr ULONG


VariantToUInt16Array proto WINAPI \
		   var: REFVARIANT,
		  prgn: ptr USHORT,
		  crgn: ULONG,
		pcElem: ptr ULONG


VariantToInt32Array proto WINAPI \
		   var: REFVARIANT,
		  prgn: ptr LONG,
		  crgn: ULONG,
		pcElem: ptr ULONG


VariantToUInt32Array proto WINAPI \
		   var: REFVARIANT,
		  prgn: ptr ULONG,
		  crgn: ULONG,
		pcElem: ptr ULONG


VariantToInt64Array proto WINAPI \
		   var: REFVARIANT,
		  prgn: ptr LONGLONG,
		  crgn: ULONG,
		pcElem: ptr ULONG


VariantToUInt64Array proto WINAPI \
		   var: REFVARIANT,
		  prgn: ptr ULONGLONG,
		  crgn: ULONG,
		pcElem: ptr ULONG


VariantToDoubleArray proto WINAPI \
		   var: REFVARIANT,
		  prgn: ptr DOUBLE,
		  crgn: ULONG,
		pcElem: ptr ULONG

VariantToStringArray proto WINAPI \
		   var: REFVARIANT,
		 prgsz: ptr PWSTR,
		 crgsz: ULONG,
		pcElem: ptr ULONG

VariantToBooleanArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		 pprgf: ptr ptr BOOL,
		pcElem: ptr ULONG

VariantToInt16ArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		 pprgn: ptr ptr SWORD,
		pcElem: ptr ULONG

VariantToUInt16ArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		 pprgn: ptr ptr WORD,
		pcElem: ptr ULONG

VariantToInt32ArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		 pprgn: ptr ptr LONG,
		pcElem: ptr ULONG

VariantToUInt32ArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		 pprgn: ptr ptr ULONG,
		pcElem: ptr ULONG

VariantToInt64ArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		 pprgn: ptr ptr LONGLONG,
		pcElem: ptr ULONG

VariantToUInt64ArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		 pprgn: ptr ptr ULONGLONG,
		pcElem: ptr ULONG

VariantToDoubleArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		 pprgn: ptr ptr real8,
		pcElem: ptr ULONG

VariantToStringArrayAlloc proto WINAPI \
		   var: REFVARIANT,
		pprgsz: ptr ptr PWSTR,
		pcElem: ptr ULONG


VariantGetBooleanElem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
		 pfVal: ptr BOOL


VariantGetInt16Elem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
		 pnVal: ptr SWORD


VariantGetUInt16Elem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
		 pnVal: ptr USHORT


VariantGetInt32Elem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
		 pnVal: ptr LONG


VariantGetUInt32Elem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
		 pnVal: ptr ULONG


VariantGetInt64Elem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
		 pnVal: ptr LONGLONG


VariantGetUInt64Elem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
		 pnVal: ptr ULONGLONG


VariantGetDoubleElem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
		 pnVal: ptr DOUBLE

VariantGetStringElem proto WINAPI \
		   var: REFVARIANT,
		 iElem: ULONG,
	       ppszVal: ptr PWSTR


VariantGetElem proto WINAPI \
		 varIn: REFVARIANT,
		 iElem: ULONG,
		  pvar: ptr VARIANT


ClearVariantArray proto WINAPI \
		 pvars: ptr VARIANT,
		 cvars: UINT

VariantCompare proto WINAPI \
		  var1: REFVARIANT,
		  var2: REFVARIANT

.enum DRAWPROGRESSFLAGS {
    DPF_NONE		    = 0x0,
    DPF_MARQUEE		    = 0x1,
    DPF_MARQUEE_COMPLETE    = 0x2,
    DPF_ERROR		    = 0x4,
    DPF_WARNING		    = 0x8,
    DPF_STOPPED		    = 0x10,
    }

endif



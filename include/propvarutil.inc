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

InitPropVariantFromResource proto WINAPI :HINSTANCE, :UINT, :ptr
InitPropVariantFromBuffer proto WINAPI :ptr, :UINT, :ptr
InitPropVariantFromCLSID proto WINAPI :REFCLSID, :ptr
InitPropVariantFromGUIDAsString proto WINAPI :REFGUID, :ptr
InitPropVariantFromFileTime proto WINAPI :ptr, :ptr
InitPropVariantFromPropVariantVectorElem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
InitPropVariantVectorFromPropVariant proto WINAPI :REFPROPVARIANT, :ptr
InitPropVariantFromStrRet proto WINAPI :ptr, :PCUITEMID_CHILD, :ptr
InitPropVariantFromBooleanVector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromInt16Vector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromUInt16Vector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromInt32Vector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromUInt32Vector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromInt64Vector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromUInt64Vector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromDoubleVector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromFileTimeVector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromStringVector proto WINAPI :ptr, :ULONG, :ptr
InitPropVariantFromStringAsVector proto WINAPI :PCWSTR, :ptr
InitPropVariantFromBoolean proto WINAPI :BOOL, :ptr
InitPropVariantFromInt16 proto WINAPI :SWORD, :ptr
InitPropVariantFromUInt16 proto WINAPI :USHORT, :ptr
InitPropVariantFromInt32 proto WINAPI :LONG, :ptr
InitPropVariantFromUInt32 proto WINAPI :ULONG, :ptr
InitPropVariantFromInt64 proto WINAPI :LONGLONG, :ptr
InitPropVariantFromUInt64 proto WINAPI :ULONGLONG, :ptr
InitPropVariantFromDouble proto WINAPI :DOUBLE, :ptr
InitPropVariantFromString proto WINAPI :PCWSTR, :ptr
InitPropVariantFromGUIDAsBuffer proto WINAPI :REFGUID, :ptr
IsPropVariantVector proto WINAPI :REFPROPVARIANT
IsPropVariantString proto WINAPI :REFPROPVARIANT
PropVariantToBooleanWithDefault proto WINAPI :REFPROPVARIANT, :BOOL
PropVariantToInt16WithDefault proto WINAPI :REFPROPVARIANT, :SWORD
PropVariantToUInt16WithDefault proto WINAPI :REFPROPVARIANT, :USHORT
PropVariantToInt32WithDefault proto WINAPI :REFPROPVARIANT, :LONG
PropVariantToUInt32WithDefault proto WINAPI :REFPROPVARIANT, :ULONG
PropVariantToInt64WithDefault proto WINAPI :REFPROPVARIANT, :LONGLONG
PropVariantToUInt64WithDefault proto WINAPI :REFPROPVARIANT, :ULONGLONG
PropVariantToDoubleWithDefault proto WINAPI :REFPROPVARIANT, :DOUBLE
PropVariantToStringWithDefault proto WINAPI :REFPROPVARIANT, :LPCWSTR
PropVariantToBoolean proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToInt16 proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToUInt16 proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToInt32 proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToUInt32 proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToInt64 proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToUInt64 proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToDouble proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToBuffer proto WINAPI :REFPROPVARIANT, :ptr, :UINT
PropVariantToString proto WINAPI :REFPROPVARIANT, :PWSTR, :UINT
PropVariantToGUID proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToStringAlloc proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToBSTR proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToStrRet proto WINAPI :REFPROPVARIANT, :ptr
PropVariantToFileTime proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToCLSID proto WINAPI :REFPROPVARIANT, :ptr
PropVariantGetElementCount proto WINAPI :REFPROPVARIANT
PropVariantToBooleanVector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToInt16Vector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToUInt16Vector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToInt32Vector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToUInt32Vector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToInt64Vector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToUInt64Vector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToDoubleVector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToFileTimeVector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToStringVector proto WINAPI :REFPROPVARIANT, :ptr, :ULONG, :ptr
PropVariantToBooleanVectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToInt16VectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToUInt16VectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToInt32VectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToUInt32VectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToInt64VectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToUInt64VectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToDoubleVectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToFileTimeVectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantToStringVectorAlloc proto WINAPI :REFPROPVARIANT, :ptr, :ptr
PropVariantGetBooleanElem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetInt16Elem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetUInt16Elem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetInt32Elem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetUInt32Elem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetInt64Elem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetUInt64Elem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetDoubleElem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetFileTimeElem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetStringElem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
PropVariantGetElem proto WINAPI :REFPROPVARIANT, :ULONG, :ptr
ClearPropVariantArray proto WINAPI :ptr, :UINT

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

PropVariantCompareEx proto WINAPI :REFPROPVARIANT, :REFPROPVARIANT, :PROPVAR_COMPARE_UNIT, :PROPVAR_COMPARE_FLAGS
PropVariantCompare proto WINAPI :REFPROPVARIANT, :REFPROPVARIANT

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


PropVariantChangeType proto WINAPI :ptr, :REFPROPVARIANT, :PROPVAR_CHANGE_FLAGS, :VARTYPE
PropVariantToVariant proto WINAPI :ptr, :ptr
VariantToPropVariant proto WINAPI :ptr, :ptr
StgSerializePropVariant proto WINAPI :ptr, :ptr, :ptr
StgDeserializePropVariant proto WINAPI :ptr, :ULONG, :ptr
IsVarTypeFloat proto WINAPI :VARTYPE
IsVariantArray proto WINAPI :REFVARIANT
IsVariantString proto WINAPI :REFVARIANT
IsVarTypeNumber proto WINAPI :VARTYPE
IsVarTypeInteger proto WINAPI :VARTYPE
InitVariantFromResource proto WINAPI :HINSTANCE, :UINT, :ptr
InitVariantFromBuffer proto WINAPI :ptr, :UINT, :ptr
InitVariantFromGUIDAsString proto WINAPI :REFGUID, :ptr
InitVariantFromFileTime proto WINAPI :ptr, :ptr
InitVariantFromFileTimeArray proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromStrRet proto WINAPI :ptr, :PCUITEMID_CHILD, :ptr
InitVariantFromVariantArrayElem proto WINAPI :REFVARIANT, :ULONG, :ptr
InitVariantFromBooleanArray proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromInt16Array proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromUInt16Array proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromInt32Array proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromUInt32Array proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromInt64Array proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromUInt64Array proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromDoubleArray proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromStringArray proto WINAPI :ptr, :ULONG, :ptr
InitVariantFromBoolean proto WINAPI :BOOL, :ptr
InitVariantFromInt16 proto WINAPI :SWORD, :ptr
InitVariantFromUInt16 proto WINAPI :USHORT, :ptr
InitVariantFromInt32 proto WINAPI :LONG, :ptr
InitVariantFromUInt32 proto WINAPI :ULONG, :ptr
InitVariantFromInt64 proto WINAPI :LONGLONG, :ptr
InitVariantFromUInt64 proto WINAPI :ULONGLONG, :ptr
InitVariantFromDouble proto WINAPI :DOUBLE, :ptr
InitVariantFromString proto WINAPI :PCWSTR, :ptr
InitVariantFromDispatch proto WINAPI :ptr, :ptr
InitVariantFromDosDateTime proto WINAPI :WORD, :WORD, :ptr
InitVariantFromGUIDAsBuffer proto WINAPI :REFGUID, :ptr
VariantToBooleanWithDefault proto WINAPI :REFVARIANT, :BOOL
VariantToInt16WithDefault proto WINAPI :REFVARIANT, :SWORD
VariantToUInt16WithDefault proto WINAPI :REFVARIANT, :USHORT
VariantToInt32WithDefault proto WINAPI :REFVARIANT, :LONG
VariantToUInt32WithDefault proto WINAPI :REFVARIANT, :ULONG
VariantToInt64WithDefault proto WINAPI :REFVARIANT, :LONGLONG
VariantToUInt64WithDefault proto WINAPI :REFVARIANT, :ULONGLONG
VariantToDoubleWithDefault proto WINAPI :REFVARIANT, :DOUBLE
VariantToStringWithDefault proto WINAPI :REFVARIANT, :LPCWSTR
VariantToBoolean proto WINAPI :REFVARIANT, :ptr
VariantToInt16 proto WINAPI :REFVARIANT, :ptr
VariantToUInt16 proto WINAPI :REFVARIANT, :ptr
VariantToInt32 proto WINAPI :REFVARIANT, :ptr
VariantToUInt32 proto WINAPI :REFVARIANT, :ptr
VariantToInt64 proto WINAPI :REFVARIANT, :ptr
VariantToUInt64 proto WINAPI :REFVARIANT, :ptr
VariantToDouble proto WINAPI :REFVARIANT, :ptr
VariantToBuffer proto WINAPI :REFVARIANT, :ptr, :UINT
VariantToGUID proto WINAPI :REFVARIANT, :ptr
VariantToString proto WINAPI :REFVARIANT, :PWSTR, :UINT
VariantToStringAlloc proto WINAPI :REFVARIANT, :ptr
VariantToDosDateTime proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToStrRet proto WINAPI :REFVARIANT, :ptr
VariantToFileTime proto WINAPI :REFVARIANT, :PSTIME_FLAGS, :ptr
VariantGetElementCount proto WINAPI :REFVARIANT
VariantToBooleanArray proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToInt16Array proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToUInt16Array proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToInt32Array proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToUInt32Array proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToInt64Array proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToUInt64Array proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToDoubleArray proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToStringArray proto WINAPI :REFVARIANT, :ptr, :ULONG, :ptr
VariantToBooleanArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToInt16ArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToUInt16ArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToInt32ArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToUInt32ArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToInt64ArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToUInt64ArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToDoubleArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantToStringArrayAlloc proto WINAPI :REFVARIANT, :ptr, :ptr
VariantGetBooleanElem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetInt16Elem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetUInt16Elem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetInt32Elem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetUInt32Elem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetInt64Elem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetUInt64Elem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetDoubleElem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetStringElem proto WINAPI :REFVARIANT, :ULONG, :ptr
VariantGetElem proto WINAPI :REFVARIANT, :ULONG, :ptr

ClearVariantArray proto WINAPI :ptr, :UINT
VariantCompare proto WINAPI :REFVARIANT, :REFVARIANT

.enum DRAWPROGRESSFLAGS {
    DPF_NONE		    = 0x0,
    DPF_MARQUEE		    = 0x1,
    DPF_MARQUEE_COMPLETE    = 0x2,
    DPF_ERROR		    = 0x4,
    DPF_WARNING		    = 0x8,
    DPF_STOPPED		    = 0x10,
    }

endif

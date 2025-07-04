ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __oaidl_h__
define __oaidl_h__

include objidl.inc

ifndef __IOleAutomationTypes_INTERFACE_DEFINED__
define __IOleAutomationTypes_INTERFACE_DEFINED__

CURRENCY		typedef CY

SAFEARRAYBOUND		STRUC
cElements		ULONG ?
lLbound			LONG ?
SAFEARRAYBOUND		ENDS
LPSAFEARRAYBOUND	typedef ptr SAFEARRAYBOUND

SAFEARR_BSTR		STRUC
Size			ULONG ?
aBstr			PVOID ?;LPwireBSTR ?
SAFEARR_BSTR		ENDS

SAFEARR_UNKNOWN		STRUC
Size			ULONG ?
apUnknown		LPUNKNOWN ?
SAFEARR_UNKNOWN		ENDS

LPDISPATCH		typedef ptr IDispatch
SAFEARR_DISPATCH	STRUC
Size			ULONG ?
apDispatch		LPDISPATCH ?
SAFEARR_DISPATCH	ENDS

SAFEARR_VARIANT		STRUC
Size			ULONG ?
aVariant		PVOID ?;LPwireVARIANT ?
SAFEARR_VARIANT		ENDS

SAFEARR_BRECORD		STRUC
Size			ULONG ?
aRecord			PVOID ?;LPwireBRECORD ?
SAFEARR_BRECORD		ENDS

SAFEARR_HAVEIID		STRUC
Size			ULONG ?
apUnknown		LPUNKNOWN ?
iid			IID <>
SAFEARR_HAVEIID		ENDS

.enum SF_TYPE {
    SF_ERROR		= VT_ERROR,
    SF_I1		= VT_I1,
    SF_I2		= VT_I2,
    SF_I4		= VT_I4,
    SF_I8		= VT_I8,
    SF_BSTR		= VT_BSTR,
    SF_UNKNOWN		= VT_UNKNOWN,
    SF_DISPATCH		= VT_DISPATCH,
    SF_VARIANT		= VT_VARIANT,
    SF_RECORD		= VT_RECORD,
    SF_HAVEIID		= ( VT_UNKNOWN or VT_RESERVED )
}

SAFEARRAYUNION		STRUC
sfType			ULONG ?
UNION u; __MIDL_IOleAutomationTypes_0001
BstrStr			SAFEARR_BSTR <>
UnknownStr		SAFEARR_UNKNOWN <>
DispatchStr		SAFEARR_DISPATCH <>
VariantStr		SAFEARR_VARIANT <>
RecordStr		SAFEARR_BRECORD <>
HaveIidStr		SAFEARR_HAVEIID <>
ByteStr			db ?
WordStr			dw ?
LongStr			dd ?
HyperStr		HYPER_SIZEDARR <>
ENDS ;u
SAFEARRAYUNION		ENDS

_wireSAFEARRAY		STRUC
cDims			USHORT ?
fFeatures		USHORT ?
cbElements		ULONG ?
cLocks			ULONG ?
uArrayStructs		SAFEARRAYUNION <>
rgsabound		SAFEARRAYBOUND <>
_wireSAFEARRAY		ENDS

wireSAFEARRAY		typedef ptr _wireSAFEARRAY
wirePSAFEARRAY		typedef ptr wireSAFEARRAY

SAFEARRAY		STRUC
cDims			USHORT ?
fFeatures		USHORT ?
cbElements		ULONG ?
cLocks			ULONG ?
pvData			PVOID ?
rgsabound		SAFEARRAYBOUND <>
SAFEARRAY		ENDS

LPSAFEARRAY		typedef ptr SAFEARRAY

FADF_AUTO		equ 0x1
FADF_STATIC		equ 0x2
FADF_EMBEDDED		equ 0x4
FADF_FIXEDSIZE		equ 0x10
FADF_RECORD		equ 0x20
FADF_HAVEIID		equ 0x40
FADF_HAVEVARTYPE	equ 0x80
FADF_BSTR		equ 0x100
FADF_UNKNOWN		equ 0x200
FADF_DISPATCH		equ 0x400
FADF_VARIANT		equ 0x800
FADF_RESERVED		equ 0xf008

LPFLOAT			typedef ptr real4
LPDOUBLE		typedef ptr real8
LPVARIANT_BOOL		typedef ptr VARIANT_BOOL
LPUSHORT		typedef ptr USHORT
LPULONG			typedef ptr ULONG
LPLONGLONG		typedef ptr LONGLONG
LPULONGLONG		typedef ptr ULONGLONG

VARIANT			STRUC
UNION
 STRUC
  vt			VARTYPE ?
  wReserved1		dw ?
  wReserved2		dw ?
  wReserved3		dw ?
  UNION
   llVal		LONGLONG ?
   lVal			LONG ?
   bVal			BYTE ?
   iVal			SWORD ?
   fltVal		FLOAT ?
   dblVal		DOUBLE ?
   boolVal		VARIANT_BOOL ?
   bool			VARIANT_BOOL ?
   scode		SCODE ?
   cyVal		CY <>
   date			DATE ?
   bstrVal		BSTR ?
   punkVal		LPUNKNOWN ?
   pdispVal		LPDISPATCH ?
   parray		LPSAFEARRAY ?
   pbVal		LPBYTE ?
   piVal		PVOID ?;LPSHORT ?
   plVal		LPLONG ?
   pllVal		LPLONGLONG ?
   pfltVal		LPFLOAT ?
   pdblVal		LPDOUBLE ?
   pboolVal		LPVARIANT_BOOL ?
   pbool		LPVARIANT_BOOL ?
   pscode		PSCODE ?
   pcyVal		LPCY ?
   pdate		LPDATE ?
   pbstrVal		LPBSTR ?
   ppunkVal		LPUNKNOWN ?
   ppdispVal		LPDISPATCH ?
   pparray		LPSAFEARRAY ?
   pvarVal		PVOID ?;LPVARIANT ?
   byref		PVOID ?
   cVal			SBYTE ?
   uiVal		USHORT ?
   ulVal		ULONG ?
   ullVal		ULONGLONG ?
   intVal		SINT ?
   uintVal		UINT ?
   pdecVal		LPDECIMAL ?
   pcVal		LPSTR ?
   puiVal		LPUSHORT ?
   pulVal		LPULONG ?
   pullVal		LPULONGLONG ?
   pintVal		LPINT ?
   puintVal		LPUINT ?
   STRUC
    pvRecord		PVOID ?
    pRecInfo		PVOID ?;LPIRecordInfo ?
   ENDS
  ENDS
 ENDS
 decVal			DECIMAL <>
ENDS
VARIANT			ENDS
LPVARIANT		typedef ptr VARIANT

VARIANTARG		typedef VARIANT
LPVARIANTARG		typedef ptr VARIANT
ifndef _REFVARIANT_DEFINED
define _REFVARIANT_DEFINED
REFVARIANT		typedef ptr VARIANT
endif

wireBRECORD		STRUC
fFlags			ULONG ?
clSize			ULONG ?
pRecInfo		PVOID ?;LPIRecordInfo ?
pRecord			LPBYTE ?
wireBRECORD		ENDS

wireVARIANT		STRUC
clSize			dd ?
rpcReserved		dd ?
vt			dw ?
wReserved1		dw ?
wReserved2		dw ?
wReserved3		dw ?
UNION
 lVal			LONG ?
 bVal			db ?
 iVal			SWORD ?
 fltVal			FLOAT ?
 dblVal			DOUBLE ?
 boolVal		VARIANT_BOOL ?
 scode			SCODE ?
 cyVal			CY <>
 date			DATE ?
 bstrVal		wireBSTR ?
 punkVal		LPUNKNOWN ?
 pdispVal		LPDISPATCH ?
 parray			wireSAFEARRAY ?
 brecVal		wireBRECORD <>
 pbVal			LPBYTE ?
 piVal			PVOID ?;LPSHORT ?
 plVal			LPLONG ?
 pfltVal		LPFLOAT ?
 pdblVal		LPDOUBLE ?
 pboolVal		LPVARIANT_BOOL ?
 pscode			PSCODE ?
 pcyVal			LPCY ?
 pdate			LPDATE ?
 pbstrVal		PVOID ?;LPwireBSTR ?
 ppunkVal		LPUNKNOWN ?
 ppdispVal		LPDISPATCH ?
 pparray		PVOID ?;LPwireSAFEARRAY ?
 pvarVal		PVOID ?;LPwireVARIANT ?
 cVal			SBYTE ?
 uiVal			dw ?
 ulVal			ULONG ?
 intVal			SINT ?
 uintVal		UINT ?
 decVal			DECIMAL <>
 pdecVal		LPDECIMAL ?
 pcVal			PVOID ?;LPSBYTE ?
 puiVal			PVOID ?;LPUSHORT ?
 pulVal			PVOID ?;LPULONG ?
 pintVal		PVOID ?;LPSINT ?
 puintVal		LPUINT ?
ENDS
wireVARIANT		ENDS

DISPID			typedef LONG
MEMBERID		typedef DISPID
HREFTYPE		typedef DWORD

.enum TYPEKIND {
    TKIND_ENUM		= 0,
    TKIND_RECORD	= TKIND_ENUM + 1,
    TKIND_MODULE	= TKIND_RECORD + 1,
    TKIND_INTERFACE	= TKIND_MODULE + 1,
    TKIND_DISPATCH	= TKIND_INTERFACE + 1,
    TKIND_COCLASS	= TKIND_DISPATCH + 1,
    TKIND_ALIAS		= TKIND_COCLASS + 1,
    TKIND_UNION		= TKIND_ALIAS + 1,
    TKIND_MAX		= TKIND_UNION + 1
}

TYPEDESC		STRUC
UNION
 lptdesc		PVOID ?;ptr TYPEDESC
 lpadesc		PVOID ?;ptr ARRAYDESC
 hreftype		HREFTYPE ?
ENDS
vt			VARTYPE ?
TYPEDESC		ENDS

ARRAYDESC		STRUC
tdescElem		TYPEDESC <>
cDims			USHORT ?
rgbounds		SAFEARRAYBOUND <>
ARRAYDESC		ENDS

PARAMDESCEX		STRUC
cBytes			ULONG ?
varDefaultValue		VARIANTARG <>
PARAMDESCEX		ENDS

LPPARAMDESCEX		typedef ptr PARAMDESCEX

PARAMDESC		STRUC
pparamdescex		LPPARAMDESCEX ?
wParamFlags		USHORT ?
PARAMDESC		ENDS

LPPARAMDESC		typedef ptr PARAMDESC

PARAMFLAG_NONE		equ 0

PARAMFLAG_FIN		equ 0x1
PARAMFLAG_FOUT		equ 0x2
PARAMFLAG_FLCID		equ 0x4
PARAMFLAG_FRETVAL	equ 0x8
PARAMFLAG_FOPT		equ 0x10
PARAMFLAG_FHASDEFAULT	equ 0x20
PARAMFLAG_FHASCUSTDATA	equ 0x40

IDLDESC			STRUC
dwReserved		ULONG ?
wIDLFlags		USHORT ?
IDLDESC			ENDS

LPIDLDESC		typedef ptr IDLDESC

IDLFLAG_NONE		equ <PARAMFAG_NONE>
IDLFLAG_FIN		equ <PARAMFAG_FIN>
IDLFLAG_FOUT		equ <PARAMFAG_FOUT>
IDLFLAG_FLCID		equ <PARAMFLAG_FCID>
IDLFLAG_FRETVAL		equ <PARAMFLAG_FRETVA>

ELEMDESC		STRUC
tdesc			TYPEDESC <>
UNION
idldesc			IDLDESC <>
paramdesc		PARAMDESC <>
ENDS
ELEMDESC		ENDS
LPELEMDESC		typedef ptr ELEMDESC

TYPEATTR		STRUC
guid			GUID <>
lcid			LCID ?
dwReserved		dd ?
memidConstructor	MEMBERID ?
memidDestructor		MEMBERID ?
lpstrSchema		LPOLESTR ?
cbSizeInstance		ULONG ?
typekind		TYPEKIND ?
cFuncs			dw ?
cVars			dw ?
cImplTypes		dw ?
cbSizeVft		dw ?
cbAlignment		dw ?
wTypeFlags		dw ?
wMajorVerNum		dw ?
wMinorVerNum		dw ?
tdescAlias		TYPEDESC <>
idldescType		IDLDESC <>
TYPEATTR		ENDS

LPTYPEATTR		typedef ptr TYPEATTR

DISPPARAMS		STRUC
rgvarg			LPVARIANTARG ?
rgdispidNamedArgs	PVOID ?;LPDISPID ?
cArgs			UINT ?
cNamedArgs		UINT ?
DISPPARAMS		ENDS

EXCEPINFO		STRUC
wCode			dw ?
wReserved		dw ?
bstrSource		BSTR ?
bstrDescription		BSTR ?
bstrHelpFile		BSTR ?
dwHelpContext		dd ?
pvReserved		PVOID ?
pfnDeferredFillIn	PVOID ?;HRESULT (__stdcall *pfnDeferredFillIn)(struct tagEXCEPINFO *)
scode			SCODE ?
EXCEPINFO		ENDS
LPEXCEPINFO		typedef ptr EXCEPINFO

.enum CALLCONV {
    CC_FASTCALL		= 0,
    CC_CDECL		= 1,
    CC_MSCPASCAL	= CC_CDECL + 1,
    CC_PASCAL		= CC_MSCPASCAL,
    CC_MACPASCAL	= CC_PASCAL + 1,
    CC_STDCALL		= CC_MACPASCAL + 1,
    CC_FPFASTCALL	= CC_STDCALL + 1,
    CC_SYSCALL		= CC_FPFASTCALL + 1,
    CC_MPWCDECL		= CC_SYSCALL + 1,
    CC_MPWPASCAL	= CC_MPWCDECL + 1,
    CC_MAX		= CC_MPWPASCAL + 1
}

.enum FUNCKIND {
    FUNC_VIRTUAL	= 0,
    FUNC_PUREVIRTUAL	= FUNC_VIRTUAL + 1,
    FUNC_NONVIRTUAL	= FUNC_PUREVIRTUAL + 1,
    FUNC_STATIC		= FUNC_NONVIRTUAL + 1,
    FUNC_DISPATCH	= FUNC_STATIC + 1
}

.enum INVOKEKIND {
    INVOKE_FUNC		= 1,
    INVOKE_PROPERTYGET	= 2,
    INVOKE_PROPERTYPUT	= 4,
    INVOKE_PROPERTYPUTREF = 8
}


FUNCDESC		STRUC
memid			MEMBERID ?
lprgscode		PSCODE ?
lprgelemdescParam	LPELEMDESC ?
funckind		FUNCKIND ?
invkind			INVOKEKIND ?
callconv		CALLCONV ?
cParams			SWORD ?
cParamsOpt		SWORD ?
oVft			SWORD ?
cScodes			SWORD ?
elemdescFunc		ELEMDESC <>
wFuncFlags		dw ?
FUNCDESC		ENDS

LPFUNCDESC		typedef ptr FUNCDESC

.enum VARKIND {
    VAR_PERINSTANCE	= 0,
    VAR_STATIC		= VAR_PERINSTANCE + 1,
    VAR_CONST		= VAR_STATIC + 1,
    VAR_DISPATCH	= VAR_CONST + 1
}

IMPLTYPEFLAG_FDEFAULT	equ 0x1
IMPLTYPEFLAG_FSOURCE	equ 0x2
IMPLTYPEFLAG_FRESTRICTED equ 0x4
IMPLTYPEFLAG_FDEFAULTVTABLE equ 0x8

VARDESC			STRUC
memid			MEMBERID ?
lpstrSchema		LPOLESTR ?
UNION
 oInst			ULONG ?
 lpvarValue		LPVARIANT ?
ENDS
elemdescVar		ELEMDESC <>
wVarFlags		dw ?
varkind			VARKIND ?
VARDESC			ENDS

LPVARDESC		typedef ptr VARDESC

.enum TYPEFLAGS {
    TYPEFLAG_FAPPOBJECT		= 0x1,
    TYPEFLAG_FCANCREATE		= 0x2,
    TYPEFLAG_FLICENSED		= 0x4,
    TYPEFLAG_FPREDECLID		= 0x8,
    TYPEFLAG_FHIDDEN		= 0x10,
    TYPEFLAG_FCONTROL		= 0x20,
    TYPEFLAG_FDUAL		= 0x40,
    TYPEFLAG_FNONEXTENSIBLE	= 0x80,
    TYPEFLAG_FOLEAUTOMATION	= 0x100,
    TYPEFLAG_FRESTRICTED	= 0x200,
    TYPEFLAG_FAGGREGATABLE	= 0x400,
    TYPEFLAG_FREPLACEABLE	= 0x800,
    TYPEFLAG_FDISPATCHABLE	= 0x1000,
    TYPEFLAG_FREVERSEBIND	= 0x2000,
    TYPEFLAG_FPROXY		= 0x4000
}

.enum FUNCFLAGS {
    FUNCFLAG_FRESTRICTED	= 0x1,
    FUNCFLAG_FSOURCE		= 0x2,
    FUNCFLAG_FBINDABLE		= 0x4,
    FUNCFLAG_FREQUESTEDIT	= 0x8,
    FUNCFLAG_FDISPLAYBIND	= 0x10,
    FUNCFLAG_FDEFAULTBIND	= 0x20,
    FUNCFLAG_FHIDDEN		= 0x40,
    FUNCFLAG_FUSESGETLASTERROR	= 0x80,
    FUNCFLAG_FDEFAULTCOLLELEM	= 0x100,
    FUNCFLAG_FUIDEFAULT		= 0x200,
    FUNCFLAG_FNONBROWSABLE	= 0x400,
    FUNCFLAG_FREPLACEABLE	= 0x800,
    FUNCFLAG_FIMMEDIATEBIND	= 0x1000
}

.enum VARFLAGS {
    VARFLAG_FREADONLY		= 0x1,
    VARFLAG_FSOURCE		= 0x2,
    VARFLAG_FBINDABLE		= 0x4,
    VARFLAG_FREQUESTEDIT	= 0x8,
    VARFLAG_FDISPLAYBIND	= 0x10,
    VARFLAG_FDEFAULTBIND	= 0x20,
    VARFLAG_FHIDDEN		= 0x40,
    VARFLAG_FRESTRICTED		= 0x80,
    VARFLAG_FDEFAULTCOLLELEM	= 0x100,
    VARFLAG_FUIDEFAULT		= 0x200,
    VARFLAG_FNONBROWSABLE	= 0x400,
    VARFLAG_FREPLACEABLE	= 0x800,
    VARFLAG_FIMMEDIATEBIND	= 0x1000
}

CLEANLOCALSTORAGE	STRUC
pInterface		LPUNKNOWN ?
pStorage		PVOID ?
flags			dd ?
CLEANLOCALSTORAGE	ENDS

CUSTDATAITEM		STRUC
guid			GUID <>
varValue		VARIANTARG <>
CUSTDATAITEM		ENDS

LPCUSTDATAITEM		typedef ptr CUSTDATAITEM

CUSTDATA		STRUC
cCustData		dd ?
prgCustData		LPCUSTDATAITEM ?
CUSTDATA		ENDS

LPCUSTDATA		typedef ptr CUSTDATA

endif

ifndef __ICreateTypeInfo_INTERFACE_DEFINED__
define __ICreateTypeInfo_INTERFACE_DEFINED__

DEFINE_IIDX(ICreateTypeInfo, "00020405-0000-0000-C000-000000000046")

.comdef ICreateTypeInfo : public IUnknown

    SetGuid		proc :REFGUID
    SetTypeFlags	proc :UINT
    SetDocString	proc :LPOLESTR
    SetHelpContext	proc :DWORD
    SetVersion		proc :WORD, :WORD
    AddRefTypeInfo	proc :ptr, :ptr
    AddFuncDesc		proc :UINT, :ptr
    AddImplType		proc :UINT, :HREFTYPE
    SetImplTypeFlags	proc :UINT, :SINT
    SetAlignment	proc :WORD
    SetSchema		proc :LPOLESTR
    AddVarDesc		proc :UINT, :ptr
    SetFuncAndParamNames proc :UINT, :ptr, :UINT
    SetVarName		proc :UINT, :LPOLESTR
    SetTypeDescAlias	proc :ptr
    DefineFuncAsDllEntry proc :UINT, :LPOLESTR, :LPOLESTR
    SetFuncDocString	proc :UINT, :LPOLESTR
    SetVarDocString	proc :UINT, :LPOLESTR
    SetFuncHelpContext	proc :UINT, :DWORD
    SetVarHelpContext	proc :UINT, :DWORD
    SetMops		proc :UINT, :BSTR
    SetTypeIdldesc	proc :ptr
    LayOut		proc
   .ends

LPCREATETYPEINFO	typedef ptr ICreateTypeInfo

endif

ifndef __ICreateTypeInfo2_INTERFACE_DEFINED__
define __ICreateTypeInfo2_INTERFACE_DEFINED__

DEFINE_IIDX(ICreateTypeInfo2, "0002040E-0000-0000-C000-000000000046")

.comdef ICreateTypeInfo2 : public ICreateTypeInfo

    DeleteFuncDesc	proc :DWORD
    DeleteFuncDescByMemId proc :MEMBERID, :INVOKEKIND
    DeleteVarDesc	proc :DWORD
    DeleteVarDescByMemId proc :MEMBERID
    DeleteImplType	proc :DWORD
    SetCustData		proc :REFGUID, :ptr
    SetFuncCustData	proc :DWORD, :REFGUID, :ptr
    SetParamCustData	proc :DWORD, :DWORD, :REFGUID, :ptr
    SetVarCustData	proc :DWORD, :REFGUID, :ptr
    SetImplTypeCustData proc :DWORD, :REFGUID, :ptr
    SetHelpStringContext proc :DWORD
    SetFuncHelpStringContext proc :DWORD, :DWORD
    SetVarHelpStringContext proc :DWORD, :DWORD
    Invalidate		proc
    SetName		proc :LPOLESTR
   .ends
    LPCREATETYPEINFO2	typedef ptr ICreateTypeInfo2
endif

ifndef __ICreateTypeLib_INTERFACE_DEFINED__
define __ICreateTypeLib_INTERFACE_DEFINED__

DEFINE_IIDX(ICreateTypeLib, "00020406-0000-0000-C000-000000000046")

.comdef ICreateTypeLib : public IUnknown

    CreateTypeInfo	proc :LPOLESTR, :TYPEKIND, :ptr
    SetName		proc :LPOLESTR
    SetVersion		proc :WORD, :WORD
    SetGuid		proc :REFGUID
    SetDocString	proc :LPOLESTR
    SetHelpFileName	proc :LPOLESTR
    SetHelpContext	proc :DWORD
    SetLcid		proc :LCID
    SetLibFlags		proc :DWORD
    SaveAllChanges	proc
   .ends
    LPCREATETYPELIB	typedef ptr ICreateTypeLib
endif

ifndef __ICreateTypeLib2_INTERFACE_DEFINED__
define __ICreateTypeLib2_INTERFACE_DEFINED__

DEFINE_IIDX(ICreateTypeLib2, "0002040F-0000-0000-C000-000000000046")

.comdef ICreateTypeLib2 : public ICreateTypeLib

    DeleteTypeInfo	proc :LPOLESTR
    SetCustData		proc :REFGUID, :ptr
    SetHelpStringContext proc :DWORD
    SetHelpStringDll	proc :LPOLESTR
   .ends
    LPCREATETYPELIB2	typedef ptr ICreateTypeLib2
endif

ifndef __IDispatch_INTERFACE_DEFINED__
define __IDispatch_INTERFACE_DEFINED__

DISPID_UNKNOWN		equ ( -1 )
DISPID_VALUE		equ ( 0 )
DISPID_PROPERTYPUT	equ ( -3 )
DISPID_NEWENUM		equ ( -4 )
DISPID_EVALUATE		equ ( -5 )
DISPID_CONSTRUCTOR	equ ( -6 )
DISPID_DESTRUCTOR	equ ( -7 )
DISPID_COLLECT		equ ( -8 )

DEFINE_IIDX(IDispatch, "00020400-0000-0000-C000-000000000046")

.comdef IDispatch : public IUnknown

    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    IInvoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
   .ends

LPDISPATCH		typedef ptr IDispatch

endif

ifndef __IEnumVARIANT_INTERFACE_DEFINED__
define __IEnumVARIANT_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumVARIANT, "00020404-0000-0000-C000-000000000046")

.comdef IEnumVARIANT : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr
   .ends
    LPENUMVARIANT	typedef ptr IEnumVARIANT
endif

ifndef __ITypeComp_INTERFACE_DEFINED__
define __ITypeComp_INTERFACE_DEFINED__

.enum DESCKIND {
    DESCKIND_NONE	= 0,
    DESCKIND_FUNCDESC	= DESCKIND_NONE + 1,
    DESCKIND_VARDESC	= DESCKIND_FUNCDESC + 1,
    DESCKIND_TYPECOMP	= DESCKIND_VARDESC + 1,
    DESCKIND_IMPLICITAPPOBJ = DESCKIND_TYPECOMP + 1,
    DESCKIND_MAX	= DESCKIND_IMPLICITAPPOBJ + 1
}

BINDPTR			UNION
lpfuncdesc		LPFUNCDESC ?
lpvardesc		LPVARDESC ?
lptcomp			PVOID ?;LPITypeComp ?
BINDPTR			ENDS
LPBINDPTR		typedef ptr BINDPTR

DEFINE_IIDX(ITypeComp, "00020403-0000-0000-C000-000000000046")

.comdef ITypeComp : public IUnknown

    Bind		proc
    BindType		proc
   .ends
    LPTYPECOMP		typedef ptr ITypeComp
endif


ifndef __ITypeInfo_INTERFACE_DEFINED__
define __ITypeInfo_INTERFACE_DEFINED__

DEFINE_IIDX(ITypeInfo, "00020401-0000-0000-C000-000000000046")

.comdef ITypeInfo : public IUnknown

    GetTypeAttr		proc :ptr
    GetTypeComp		proc :ptr
    GetFuncDesc		proc :DWORD, :ptr
    GetVarDesc		proc :DWORD, :ptr
    GetNames		proc :MEMBERID, :ptr, :DWORD, :ptr
    GetRefTypeOfImplType proc :DWORD, :ptr
    GetImplTypeFlags	proc :DWORD, :ptr
    GetIDsOfNames	proc :ptr, :DWORD, :ptr
    Invoke_		proc :PVOID, :MEMBERID, :DWORD, :ptr, :ptr, :ptr, :ptr
    GetDocumentation	proc :MEMBERID, :ptr, :ptr, :ptr, :ptr
    GetDllEntry		proc :MEMBERID, :INVOKEKIND, :ptr, :ptr, :ptr
    GetRefTypeInfo	proc :HREFTYPE, :ptr
    AddressOfMember	proc :MEMBERID, :INVOKEKIND, :ptr
    CreateInstance	proc :ptr, :REFIID, :ptr
    GetMops		proc :MEMBERID, :ptr
    GetContainingTypeLib proc :ptr, :ptr
    ReleaseTypeAttr	proc :ptr
    ReleaseFuncDesc	proc :ptr
    ReleaseVarDesc	proc :ptr
   .ends
    LPTYPEINFO		typedef ptr ITypeInfo
endif

ifndef __ITypeInfo2_INTERFACE_DEFINED__
define __ITypeInfo2_INTERFACE_DEFINED__

DEFINE_IIDX(ITypeInfo2, "00020412-0000-0000-C000-000000000046")

.comdef ITypeInfo2 : public ITypeInfo

    GetTypeKind		proc :ptr
    GetTypeFlags	proc :ptr
    GetFuncIndexOfMemId proc :MEMBERID, :INVOKEKIND, :ptr
    GetVarIndexOfMemId	proc :MEMBERID, :ptr
    GetCustData		proc :REFGUID, :ptr
    GetFuncCustData	proc :DWORD, :REFGUID, :ptr
    GetParamCustData	proc :DWORD, :DWORD, :REFGUID, :ptr
    GetVarCustData	proc :DWORD, :REFGUID, :ptr
    GetImplTypeCustData proc :DWORD, :REFGUID, :ptr
    GetDocumentation2	proc :MEMBERID, :LCID, :ptr, :ptr, :ptr
    GetAllCustData	proc :ptr
    GetAllFuncCustData	proc :DWORD, :ptr
    GetAllParamCustData proc :DWORD, :DWORD, :ptr
    GetAllVarCustData	proc :DWORD, :ptr
    GetAllImplTypeCustData proc :DWORD, :ptr
   .ends
    LPTYPEINFO2		typedef ptr ITypeInfo2
endif

ifndef __ITypeLib_INTERFACE_DEFINED__
define __ITypeLib_INTERFACE_DEFINED__

.enum SYSKIND {
    SYS_WIN16		= 0,
    SYS_WIN32		= SYS_WIN16 + 1,
    SYS_MAC		= SYS_WIN32 + 1,
    SYS_WIN64		= SYS_MAC + 1
}

.enum LIBFLAGS {
    LIBFLAG_FRESTRICTED = 0x1,
    LIBFLAG_FCONTROL	= 0x2,
    LIBFLAG_FHIDDEN	= 0x4,
    LIBFLAG_FHASDISKIMAGE = 0x8
}

TLIBATTR		STRUC
guid			GUID <>
lcid			LCID ?
syskind			SYSKIND ?
wMajorVerNum		dw ?
wMinorVerNum		dw ?
wLibFlags		dw ?
TLIBATTR		ENDS

LPTLIBATTR		typedef ptr TLIBATTR

DEFINE_IIDX(ITypeLib, "00020402-0000-0000-C000-000000000046")

.comdef ITypeLib : public IUnknown

    GetTypeInfoCount	proc
    GetTypeInfo		proc :DWORD, :ptr
    GetTypeInfoType	proc :DWORD, :ptr
    GetTypeInfoOfGuid	proc :REFGUID, :ptr
    GetLibAttr		proc :ptr
    GetTypeComp		proc :ptr
    GetDocumentation	proc :DWORD, :ptr, :ptr, :ptr, :ptr
    IsName		proc :LPOLESTR, :DWORD, :ptr
    FindName		proc :LPOLESTR, :DWORD, :ptr, :ptr, :ptr
    ReleaseTLibAttr	proc :ptr
   .ends
    LPTYPELIB		typedef ptr ITypeLib
endif

ifndef __ITypeLib2_INTERFACE_DEFINED__
define __ITypeLib2_INTERFACE_DEFINED__

DEFINE_IIDX(ITypeLib2, "00020411-0000-0000-C000-000000000046")

.comdef ITypeLib2 : public ITypeLib

    GetCustData		proc :REFGUID, :ptr
    GetLibStatistics	proc :ptr, :ptr
    GetDocumentation2	proc :DWORD, :LCID, :ptr, :ptr, :ptr
    GetAllCustData	proc :ptr
   .ends
    LPTYPELIB2		typedef ptr ITypeLib2
endif

ifndef __ITypeChangeEvents_INTERFACE_DEFINED__
define __ITypeChangeEvents_INTERFACE_DEFINED__

CHANGEKIND		typedef SDWORD
CHANGEKIND_ADDMEMBER	equ 0
CHANGEKIND_DELETEMEMBER equ CHANGEKIND_ADDMEMBER + 1
CHANGEKIND_SETNAMES	equ CHANGEKIND_DELETEMEMBER + 1
CHANGEKIND_SETDOCUMENTATION equ CHANGEKIND_SETNAMES + 1
CHANGEKIND_GENERAL	equ CHANGEKIND_SETDOCUMENTATION + 1
CHANGEKIND_INVALIDATE	equ CHANGEKIND_GENERAL + 1
CHANGEKIND_CHANGEFAILED equ CHANGEKIND_INVALIDATE + 1
CHANGEKIND_MAX		equ CHANGEKIND_CHANGEFAILED + 1

DEFINE_IIDX(ITypeChangeEvents, "00020410-0000-0000-C000-000000000046")

.comdef ITypeChangeEvents : public IUnknown

    RequestTypeChange	proc :CHANGEKIND, :ptr, :LPOLESTR, :ptr
    AfterTypeChange	proc :CHANGEKIND, :ptr, :LPOLESTR
   .ends
    LPTYPECHANGEEVENTS	typedef ptr ITypeChangeEvents

endif


ifndef __IErrorInfo_INTERFACE_DEFINED__
define __IErrorInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IErrorInfo, "1CF2B120-547D-101B-8E65-08002B2BD119")

.comdef IErrorInfo : public IUnknown

    GetGUID		proc :ptr
    GetSource		proc :ptr
    GetDescription	proc :ptr
    GetHelpFile		proc :ptr
    GetHelpContext	proc :ptr
   .ends
    LPERRORINFO		typedef ptr IErrorInfo
endif

ifndef __ICreateErrorInfo_INTERFACE_DEFINED__
define __ICreateErrorInfo_INTERFACE_DEFINED__

DEFINE_IIDX(ICreateErrorInfo, "22F03340-547D-101B-8E65-08002B2BD119")

.comdef ICreateErrorInfo : public IUnknown

    SetGUID		proc :REFGUID
    SetSource		proc :LPOLESTR
    SetDescription	proc :LPOLESTR
    SetHelpFile		proc :LPOLESTR
    SetHelpContext	proc :DWORD
   .ends
    LPCREATEERRORINFO	typedef ptr ICreateErrorInfo
endif

ifndef __ISupportErrorInfo_INTERFACE_DEFINED__
define __ISupportErrorInfo_INTERFACE_DEFINED__

DEFINE_IIDX(ISupportErrorInfo, "DF0B3D60-548F-101B-8E65-08002B2BD119")

.comdef ISupportErrorInfo : public IUnknown

    InterfaceSupportsErrorInfo proc :REFIID
   .ends
    LPSUPPORTERRORINFO	typedef ptr ISupportErrorInfo
endif

ifndef __ITypeFactory_INTERFACE_DEFINED__
define __ITypeFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ITypeFactory, "0000002E-0000-0000-C000-000000000046")

.comdef ITypeFactory : public IUnknown

    CreateFromTypeInfo	proc :ptr, :REFIID, :ptr
   .ends

endif

ifndef __ITypeMarshal_INTERFACE_DEFINED__
define __ITypeMarshal_INTERFACE_DEFINED__

DEFINE_IIDX(ITypeMarshal, "0000002D-0000-0000-C000-000000000046")

.comdef ITypeMarshal : public IUnknown

    Size		proc :PVOID, :DWORD, :PVOID, :ptr
    Marshal		proc :PVOID, :DWORD, :PVOID, :DWORD, :ptr, :ptr
    Unmarshal		proc :PVOID, :DWORD, :DWORD, :ptr, :ptr
    Free		proc :PVOID
   .ends

endif

ifndef __IRecordInfo_INTERFACE_DEFINED__
define __IRecordInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IRecordInfo, "0000002F-0000-0000-C000-000000000046")

.comdef IRecordInfo : public IUnknown

    RecordInit		proc :PVOID
    RecordClear		proc :PVOID
    RecordCopy		proc :PVOID, :PVOID
    GetGuid		proc :ptr
    GetName		proc :ptr
    GetSize		proc :ptr
    GetTypeInfo		proc :ptr
    GetField		proc :PVOID, :LPCOLESTR, :ptr
    GetFieldNoCopy	proc :PVOID, :LPCOLESTR, :ptr, :ptr
    PutField		proc :DWORD, :PVOID, :LPCOLESTR, :ptr
    PutFieldNoCopy	proc :DWORD, :PVOID, :LPCOLESTR, :ptr
    GetFieldNames	proc :ptr, :ptr
    IsMatchingType	proc :ptr
    RecordCreate	proc
    RecordCreateCopy	proc :PVOID, :ptr
    RecordDestroy	proc :PVOID
   .ends
    LPRECORDINFO	typedef ptr IRecordInfo
endif

ifndef __IErrorLog_INTERFACE_DEFINED__
define __IErrorLog_INTERFACE_DEFINED__

DEFINE_IIDX(IErrorLog, "3127CA40-446E-11CE-8135-00AA004BB851")

.comdef IErrorLog : public IUnknown

    AddError		proc :ptr, :ptr
   .ends
    LPERRORLOG		typedef ptr IErrorLog
endif

ifndef __IPropertyBag_INTERFACE_DEFINED__
define __IPropertyBag_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyBag, "55272A00-42CB-11CE-8135-00AA004BB851")

.comdef IPropertyBag : public IUnknown

    Read		proc :LPCOLESTR, :ptr, :ptr
    Write		proc :LPCOLESTR, :ptr
   .ends
    LPPROPERTYBAG	typedef ptr IPropertyBag
endif

BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

CLEANLOCALSTORAGE_UserSize proto WINAPI :ptr DWORD, :DWORD, : ptr CLEANLOCALSTORAGE
CLEANLOCALSTORAGE_UserMarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr CLEANLOCALSTORAGE
CLEANLOCALSTORAGE_UserUnmarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr CLEANLOCALSTORAGE
CLEANLOCALSTORAGE_UserFree proto WINAPI :ptr DWORD, :ptr CLEANLOCALSTORAGE

VARIANT_UserSize proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree proto WINAPI :ptr, :ptr

BSTR_UserSize64 proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree64 proto WINAPI :ptr, :ptr

CLEANLOCALSTORAGE_UserSize64		proto WINAPI :ptr DWORD, :DWORD, : ptr CLEANLOCALSTORAGE
CLEANLOCALSTORAGE_UserMarshal64		proto WINAPI :ptr DWORD, :LPSTR, :ptr CLEANLOCALSTORAGE
CLEANLOCALSTORAGE_UserUnmarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr CLEANLOCALSTORAGE
CLEANLOCALSTORAGE_UserFree64		proto WINAPI :ptr DWORD, :ptr CLEANLOCALSTORAGE

VARIANT_UserSize64 proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree64 proto WINAPI :ptr, :ptr

IDispatch_Invoke_Proxy			proto WINAPI :ptr, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
IDispatch_Invoke_Stub			proto WINAPI :ptr, :DISPID, :REFIID, :LCID, :DWORD, :ptr, :ptr, :ptr, :ptr, :UINT, :ptr, :ptr

IEnumVARIANT_Next_Proxy			proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumVARIANT_Next_Stub			proto WINAPI :ptr, :ULONG, :ptr, :ptr

ITypeComp_Bind_Proxy			proto WINAPI :ptr, :LPOLESTR, :ULONG, :WORD, :ptr, :ptr, :ptr
ITypeComp_Bind_Stub			proto WINAPI :ptr, :LPOLESTR, :ULONG, :WORD, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
ITypeComp_BindType_Proxy		proto WINAPI :ptr, :LPOLESTR, :ULONG, :ptr, :ptr
ITypeComp_BindType_Stub			proto WINAPI :ptr, :LPOLESTR, :ULONG, :ptr

ITypeInfo_GetTypeAttr_Proxy		proto WINAPI :ptr, :ptr
ITypeInfo_GetTypeAttr_Stub		proto WINAPI :ptr, :ptr, :ptr
ITypeInfo_GetFuncDesc_Proxy		proto WINAPI :ptr, :UINT, :ptr
ITypeInfo_GetFuncDesc_Stub		proto WINAPI :ptr, :UINT, :ptr, :ptr
ITypeInfo_GetVarDesc_Proxy		proto WINAPI :ptr, :UINT, :ptr
ITypeInfo_GetVarDesc_Stub		proto WINAPI :ptr, :UINT, :ptr, :ptr
ITypeInfo_GetNames_Proxy		proto WINAPI :ptr, :MEMBERID, :ptr, :UINT, :ptr
ITypeInfo_GetNames_Stub			proto WINAPI :ptr, :MEMBERID, :ptr, :UINT, :ptr
ITypeInfo_GetIDsOfNames_Proxy		proto WINAPI :ptr, :ptr, :UINT, :ptr
ITypeInfo_GetIDsOfNames_Stub		proto WINAPI :ptr
ITypeInfo_Invoke_Proxy			proto WINAPI :ptr, :ptr, :MEMBERID, :WORD, :ptr, :ptr, :ptr, :ptr
ITypeInfo_Invoke_Stub			proto WINAPI :ptr
ITypeInfo_GetDocumentation_Proxy	proto WINAPI :ptr, :MEMBERID, :ptr, :ptr, :ptr, :ptr
ITypeInfo_GetDocumentation_Stub		proto WINAPI :ptr, :MEMBERID, :DWORD, :ptr, :ptr, :ptr, :ptr
ITypeInfo_GetDllEntry_Proxy		proto WINAPI :ptr, :MEMBERID, :INVOKEKIND, :ptr, :ptr, :ptr
ITypeInfo_GetDllEntry_Stub		proto WINAPI :ptr, :MEMBERID, :INVOKEKIND, :DWORD, :ptr, :ptr, :ptr
ITypeInfo_AddressOfMember_Proxy		proto WINAPI :ptr, :MEMBERID, :INVOKEKIND, :ptr
ITypeInfo_AddressOfMember_Stub		proto WINAPI :ptr
ITypeInfo_CreateInstance_Proxy		proto WINAPI :ptr, :ptr, :REFIID, :ptr
ITypeInfo_CreateInstance_Stub		proto WINAPI :ptr, :REFIID, :ptr
ITypeInfo_GetContainingTypeLib_Proxy	proto WINAPI :ptr, :ptr, :ptr
ITypeInfo_GetContainingTypeLib_Stub	proto WINAPI :ptr, :ptr, :ptr
ITypeInfo_ReleaseTypeAttr_Proxy		proto WINAPI :ptr, :ptr
ITypeInfo_ReleaseTypeAttr_Stub		proto WINAPI :ptr
ITypeInfo_ReleaseFuncDesc_Proxy		proto WINAPI :ptr, :ptr
ITypeInfo_ReleaseFuncDesc_Stub		proto WINAPI :ptr
ITypeInfo_ReleaseVarDesc_Proxy		proto WINAPI :ptr, :ptr
ITypeInfo_ReleaseVarDesc_Stub		proto WINAPI :ptr

ITypeInfo2_GetDocumentation2_Proxy	proto WINAPI :ptr, :MEMBERID, :LCID, :ptr, :ptr, :ptr
ITypeInfo2_GetDocumentation2_Stub	proto WINAPI :ptr, :MEMBERID, :LCID, :DWORD, :ptr, :ptr, :ptr

ITypeLib_GetTypeInfoCount_Proxy		proto WINAPI :ptr
ITypeLib_GetTypeInfoCount_Stub		proto WINAPI :ptr, :ptr
ITypeLib_GetLibAttr_Proxy		proto WINAPI :ptr, :ptr
ITypeLib_GetLibAttr_Stub		proto WINAPI :ptr, :ptr, :ptr
ITypeLib_GetDocumentation_Proxy		proto WINAPI :ptr, :int_t, :ptr, :ptr, :ptr, :ptr
ITypeLib_GetDocumentation_Stub		proto WINAPI :ptr, :int_t, :DWORD, :ptr, :ptr, :ptr, :ptr
ITypeLib_IsName_Proxy			proto WINAPI :ptr, :LPOLESTR, :ULONG, :ptr
ITypeLib_IsName_Stub			proto WINAPI :ptr, :LPOLESTR, :ULONG, :ptr, :ptr
ITypeLib_FindName_Proxy			proto WINAPI :ptr, :LPOLESTR, :ULONG, :ptr, :ptr, :ptr
ITypeLib_FindName_Stub			proto WINAPI :ptr, :LPOLESTR, :ULONG, :ptr, :ptr, :ptr, :ptr
ITypeLib_ReleaseTLibAttr_Proxy		proto WINAPI :ptr, :ptr
ITypeLib_ReleaseTLibAttr_Stub		proto WINAPI :ptr

ITypeLib2_GetLibStatistics_Proxy	proto WINAPI :ptr, :ptr, :ptr
ITypeLib2_GetLibStatistics_Stub		proto WINAPI :ptr, :ptr, :ptr
ITypeLib2_GetDocumentation2_Proxy	proto WINAPI :ptr, :int_t, :LCID, :ptr, :ptr, :ptr
ITypeLib2_GetDocumentation2_Stub	proto WINAPI :ptr, :int_t, :LCID, :DWORD, :ptr BSTR, :ptr, :ptr

IPropertyBag_Read_Proxy			proto WINAPI :ptr, :LPCOLESTR, :ptr VARIANT, :ptr IErrorLog
IPropertyBag_Read_Stub			proto WINAPI :ptr, :LPCOLESTR, :ptr, :ptr, :DWORD, :ptr

endif

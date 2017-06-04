ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
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
.xlist
__oaidl_h__ equ 1


ifndef __ICreateTypeInfo_FWD_DEFINED__
__ICreateTypeInfo_FWD_DEFINED__ equ 1
endif	


ifndef __ICreateTypeInfo2_FWD_DEFINED__
__ICreateTypeInfo2_FWD_DEFINED__ equ 1
endif	


ifndef __ICreateTypeLib_FWD_DEFINED__
__ICreateTypeLib_FWD_DEFINED__ equ 1
endif	


ifndef __ICreateTypeLib2_FWD_DEFINED__
__ICreateTypeLib2_FWD_DEFINED__ equ 1
endif	


ifndef __IDispatch_FWD_DEFINED__
__IDispatch_FWD_DEFINED__ equ 1
endif	


ifndef __IEnumVARIANT_FWD_DEFINED__
__IEnumVARIANT_FWD_DEFINED__ equ 1
endif	


ifndef __ITypeComp_FWD_DEFINED__
__ITypeComp_FWD_DEFINED__ equ 1
endif	


ifndef __ITypeInfo_FWD_DEFINED__
__ITypeInfo_FWD_DEFINED__ equ 1
endif	


ifndef __ITypeInfo2_FWD_DEFINED__
__ITypeInfo2_FWD_DEFINED__ equ 1
endif	


ifndef __ITypeLib_FWD_DEFINED__
__ITypeLib_FWD_DEFINED__ equ 1
endif	


ifndef __ITypeLib2_FWD_DEFINED__
__ITypeLib2_FWD_DEFINED__ equ 1
endif	


ifndef __ITypeChangeEvents_FWD_DEFINED__
__ITypeChangeEvents_FWD_DEFINED__ equ 1
endif	


ifndef __IErrorInfo_FWD_DEFINED__
__IErrorInfo_FWD_DEFINED__ equ 1
endif	


ifndef __ICreateErrorInfo_FWD_DEFINED__
__ICreateErrorInfo_FWD_DEFINED__ equ 1
endif	


ifndef __ISupportErrorInfo_FWD_DEFINED__
__ISupportErrorInfo_FWD_DEFINED__ equ 1
endif	


ifndef __ITypeFactory_FWD_DEFINED__
__ITypeFactory_FWD_DEFINED__ equ 1
endif	


ifndef __ITypeMarshal_FWD_DEFINED__
__ITypeMarshal_FWD_DEFINED__ equ 1
endif	


ifndef __IRecordInfo_FWD_DEFINED__
__IRecordInfo_FWD_DEFINED__ equ 1
endif	


include objidl.inc
.xlist

;PVOID
MIDL_user_allocate proto WINAPI \
		      : size_t

;void
MIDL_user_free proto WINAPI \
		      : PVOID


if ( _MSC_VER GE 800 )
endif

externdef		__MIDL_itf_oaidl_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_oaidl_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOleAutomationTypes_INTERFACE_DEFINED__
__IOleAutomationTypes_INTERFACE_DEFINED__ equ 1



CURRENCY		typedef CY

SAFEARRAYBOUND		STRUC
cElements		ULONG ?
lLbound			LONG ?
SAFEARRAYBOUND		ENDS

LPSAFEARRAYBOUND	typedef ptr SAFEARRAYBOUND

;wireVARIANT		 typedef ptr wireVARIANT
;wireBRECORD		 typedef ptr wireBRECORD

SAFEARR_BSTR		STRUC
_Size			ULONG ?
aBstr			PVOID ?;LPwireBSTR ?
SAFEARR_BSTR		ENDS

SAFEARR_UNKNOWN		STRUC
_Size			ULONG ?
apUnknown		LPIUnknown ?
SAFEARR_UNKNOWN		ENDS

SAFEARR_DISPATCH	STRUC
_Size			ULONG ?
apDispatch		PVOID ?;LPIDispatch ?
SAFEARR_DISPATCH	ENDS

SAFEARR_VARIANT		STRUC
_Size			ULONG ?
aVariant		PVOID ?;LPwireVARIANT ?
SAFEARR_VARIANT		ENDS

SAFEARR_BRECORD		STRUC
_Size			ULONG ?
aRecord			PVOID ?;LPwireBRECORD ?
SAFEARR_BRECORD		ENDS

SAFEARR_HAVEIID		STRUC
_Size			ULONG ?
apUnknown		LPIUnknown ?
iid			IID <>
SAFEARR_HAVEIID		ENDS

;tagSF_TYPE		typedef SDWORD
SF_ERROR		equ VT_ERROR
SF_I1			equ VT_I1
SF_I2			equ VT_I2
SF_I4			equ VT_I4
SF_I8			equ VT_I8
SF_BSTR			equ VT_BSTR
SF_UNKNOWN		equ VT_UNKNOWN
SF_DISPATCH		equ VT_DISPATCH
SF_VARIANT		equ VT_VARIANT
SF_RECORD		equ VT_RECORD
SF_HAVEIID		equ VT_UNKNOWN | VT_RESERVED

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

S_wireSAFEARRAY		 STRUC
cDims			USHORT ?
fFeatures		USHORT ?
cbElements		ULONG ?
cLocks			ULONG ?
uArrayStructs		SAFEARRAYUNION <>
rgsabound		SAFEARRAYBOUND <>
S_wireSAFEARRAY		ENDS

wireSAFEARRAY		typedef ptr S_wireSAFEARRAY
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

if (__STDC__ AND NOT defined(_FORCENAMELESSUNION)) OR defined(NONAMELESSUNION)
__VARIANT_NAME_1	equ <n1>
__VARIANT_NAME_2	equ <n2>
__VARIANT_NAME_3	equ <n3>
__VARIANT_NAME_4	equ <brecVal>
else
__tagVARIANT		equ 1
__VARIANT_NAME_1	equ 1
__VARIANT_NAME_2	equ 1
__VARIANT_NAME_3	equ 1
__tagBRECORD		equ 1
__VARIANT_NAME_4	equ 1
endif
;VARIANT		 typedef VARIANT

VARIANT			STRUC
UNION __VARIANT_NAME_1
 STRUC __VARIANT_NAME_2
  vt			VARTYPE ?
  wReserved1		dw ?
  wReserved2		dw ?
  wReserved3		dw ?
  UNION __VARIANT_NAME_3
   lVal			LONG ?
   bVal			db ?
   iVal			SWORD ?
   fltVal		FLOAT ?
   dblVal		DOUBLE ?
   boolVal		VARIANT_BOOL ?
   bool			VARIANT_BOOL ?
   scode		SCODE ?
   cyVal		CY <>
   date			DATE ?
   bstrVal		BSTR ?
   punkVal		LPIUnknown ?
   pdispVal		PVOID ?;LPIDispatch ?
   parray		LPSAFEARRAY ?
   pbVal		LPBYTE ?
   piVal		PVOID ?;LPSHORT ?
   plVal		LPLONG ?
   pfltVal		LPFLOAT ?
   pdblVal		LPDOUBLE ?
   pboolVal		LPVARIANT_BOOL ?
   pbool		PVOID ?;LP_VARIANT_BOOL ?
   pscode		LPSCODE ?
   pcyVal		LPCY ?
   pdate		LPDATE ?
   pbstrVal		LPBSTR ?
   ppunkVal		LPIUnknown ?
   ppdispVal		PVOID ?;LPIDispatch ?
   pparray		LPSAFEARRAY ?
   pvarVal		PVOID ?;LPVARIANT ?
   byref		PVOID ?
   cVal			SBYTE ?
   uiVal		dw ?
   ulVal		ULONG ?
   intVal		SINT ?
   uintVal		UINT ?
   pdecVal		LPDECIMAL ?
   pcVal		PVOID ?;LPSBYTE ?
   puiVal		PVOID ?;LPUSHORT ?
   pulVal		PVOID ?;LPULONG ?
   pintVal		PVOID ?;LPSINT ?
   puintVal		LPUINT ?
   STRUC __VARIANT_NAME_4
    pvRecord		PVOID ?
    pRecInfo		PVOID ?;LPIRecordInfo ?
   ENDS ; __VARIANT_NAME_4
  ENDS ; __VARIANT_NAME_3
 ENDS ; __VARIANT_NAME_2
 decVal			DECIMAL <>
ENDS ; __VARIANT_NAME_1
VARIANT			ENDS
LPVARIANT		typedef ptr VARIANT

VARIANTARG		typedef VARIANT

LPVARIANTARG		typedef ptr VARIANT

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
 punkVal		LPIUnknown ?
 pdispVal		PVOID ?;LPIDispatch ?
 parray			wireSAFEARRAY ?
 brecVal		wireBRECORD <>
 pbVal			LPBYTE ?
 piVal			PVOID ?;LPSHORT ?
 plVal			LPLONG ?
 pfltVal		LPFLOAT ?
 pdblVal		LPDOUBLE ?
 pboolVal		LPVARIANT_BOOL ?
 pscode			LPSCODE ?
 pcyVal			LPCY ?
 pdate			LPDATE ?
 pbstrVal		PVOID ?;LPwireBSTR ?
 ppunkVal		LPIUnknown ?
 ppdispVal		PVOID ?;LPIDispatch ?
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

TYPEKIND		typedef SDWORD
TKIND_ENUM		equ 0
TKIND_RECORD		equ TKIND_ENUM + 1
TKIND_MODULE		equ TKIND_RECORD + 1
TKIND_INTERFACE		equ TKIND_MODULE + 1
TKIND_DISPATCH		equ TKIND_INTERFACE + 1
TKIND_COCLASS		equ TKIND_DISPATCH + 1
TKIND_ALIAS		equ TKIND_COCLASS + 1
TKIND_UNION		equ TKIND_ALIAS + 1
TKIND_MAX		equ TKIND_UNION + 1

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

if 0
ELEMDESC		STRUC
tdesc			TYPEDESC ?
paramdesc		PARAMDESC ?
ELEMDESC		ENDS

else 
ELEMDESC		STRUC
tdesc			TYPEDESC <>	
UNION ; {
idldesc			IDLDESC <>	
paramdesc		PARAMDESC <>	
ENDS ;
ELEMDESC		ENDS
LPELEMDESC		typedef ptr ELEMDESC
endif 
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

if 0
EXCEPINFO		STRUC
wCode			dw ?
wReserved		dw ?
bstrSource		BSTR ?
bstrDescription		BSTR ?
bstrHelpFile		BSTR ?
dwHelpContext		dd ?
pvReserved		ULONG ?
pfnDeferredFillIn	ULONG ?
scode			SCODE ?
EXCEPINFO		ENDS

else 
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
endif 
CALLCONV		typedef SDWORD
CC_FASTCALL		equ 0
CC_CDECL		equ 1
CC_MSCPASCAL		equ CC_CDECL + 1
CC_PASCAL		equ CC_MSCPASCAL
CC_MACPASCAL		equ CC_PASCAL + 1
CC_STDCALL		equ CC_MACPASCAL + 1
CC_FPFASTCALL		equ CC_STDCALL + 1
CC_SYSCALL		equ CC_FPFASTCALL + 1
CC_MPWCDECL		equ CC_SYSCALL + 1
CC_MPWPASCAL		equ CC_MPWCDECL + 1
CC_MAX			equ CC_MPWPASCAL + 1

FUNCKIND		typedef SDWORD
FUNC_VIRTUAL		equ 0
FUNC_PUREVIRTUAL	equ FUNC_VIRTUAL + 1
FUNC_NONVIRTUAL		equ FUNC_PUREVIRTUAL + 1
FUNC_STATIC		equ FUNC_NONVIRTUAL + 1
FUNC_DISPATCH		equ FUNC_STATIC + 1

INVOKEKIND		typedef SDWORD
INVOKE_FUNC		equ 1
INVOKE_PROPERTYGET	equ 2
INVOKE_PROPERTYPUT	equ 4
INVOKE_PROPERTYPUTREF	equ 8

FUNCDESC		STRUC
memid			MEMBERID ?
lprgscode		LPSCODE ?
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

VARKIND			typedef SDWORD
VAR_PERINSTANCE		equ 0
VAR_STATIC		equ VAR_PERINSTANCE + 1
VAR_CONST		equ VAR_STATIC + 1
VAR_DISPATCH		equ VAR_CONST + 1

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

;tagTYPEFLAGS		typedef SDWORD
TYPEFLAG_FAPPOBJECT	equ 0x1
TYPEFLAG_FCANCREATE	equ 0x2
TYPEFLAG_FLICENSED	equ 0x4
TYPEFLAG_FPREDECLID	equ 0x8
TYPEFLAG_FHIDDEN	equ 0x10
TYPEFLAG_FCONTROL	equ 0x20
TYPEFLAG_FDUAL		equ 0x40
TYPEFLAG_FNONEXTENSIBLE equ 0x80
TYPEFLAG_FOLEAUTOMATION equ 0x100
TYPEFLAG_FRESTRICTED	equ 0x200
TYPEFLAG_FAGGREGATABLE	equ 0x400
TYPEFLAG_FREPLACEABLE	equ 0x800
TYPEFLAG_FDISPATCHABLE	equ 0x1000
TYPEFLAG_FREVERSEBIND	equ 0x2000

;tagFUNCFLAGS		typedef SDWORD
FUNCFLAG_FRESTRICTED	equ 0x1
FUNCFLAG_FSOURCE	equ 0x2
FUNCFLAG_FBINDABLE	equ 0x4
FUNCFLAG_FREQUESTEDIT	equ 0x8
FUNCFLAG_FDISPLAYBIND	equ 0x10
FUNCFLAG_FDEFAULTBIND	equ 0x20
FUNCFLAG_FHIDDEN	equ 0x40
FUNCFLAG_FUSESGETLASTERROR equ 0x80
FUNCFLAG_FDEFAULTCOLLELEM equ 0x100
FUNCFLAG_FUIDEFAULT	equ 0x200
FUNCFLAG_FNONBROWSABLE	equ 0x400
FUNCFLAG_FREPLACEABLE	equ 0x800
FUNCFLAG_FIMMEDIATEBIND equ 0x1000

;tagVARFLAGS		typedef SDWORD
VARFLAG_FREADONLY	equ 0x1
VARFLAG_FSOURCE		equ 0x2
VARFLAG_FBINDABLE	equ 0x4
VARFLAG_FREQUESTEDIT	equ 0x8
VARFLAG_FDISPLAYBIND	equ 0x10
VARFLAG_FDEFAULTBIND	equ 0x20
VARFLAG_FHIDDEN		equ 0x40
VARFLAG_FRESTRICTED	equ 0x80
VARFLAG_FDEFAULTCOLLELEM equ 0x100
VARFLAG_FUIDEFAULT	equ 0x200
VARFLAG_FNONBROWSABLE	equ 0x400
VARFLAG_FREPLACEABLE	equ 0x800
VARFLAG_FIMMEDIATEBIND	equ 0x1000

CLEANLOCALSTORAGE	STRUC
pInterface		LPIUnknown ?
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



externdef		IOleAutomationTypes_v1_0_c_ifspec:RPC_IF_HANDLE
externdef		IOleAutomationTypes_v1_0_s_ifspec:RPC_IF_HANDLE
endif 

ifndef __ICreateTypeInfo_INTERFACE_DEFINED__
__ICreateTypeInfo_INTERFACE_DEFINED__ equ 1



LPCREATETYPEINFO	typedef ptr ICreateTypeInfo


externdef		IID_ICreateTypeInfo:IID


ICreateTypeInfoVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		  riid: REFIID

    QueryInterface60@MP typedef ptr QueryInterface60@CT
	 QueryInterface QueryInterface60@MP ?

	    AddRef60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo

	    AddRef60@MP typedef ptr AddRef60@CT
		 AddRef AddRef60@MP ?

	   Release60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo

	   Release60@MP typedef ptr Release60@CT
		Release Release60@MP ?

	   SetGuid60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		  guid: REFGUID

	   SetGuid60@MP typedef ptr SetGuid60@CT
		SetGuid SetGuid60@MP ?

      SetTypeFlags60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
	    uTypeFlags: UINT

      SetTypeFlags60@MP typedef ptr SetTypeFlags60@CT
	   SetTypeFlags SetTypeFlags60@MP ?

      SetDocString60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
	       pStrDoc: LPOLESTR

      SetDocString60@MP typedef ptr SetDocString60@CT
	   SetDocString SetDocString60@MP ?

    SetHelpContext60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
	 dwHelpContext: DWORD

    SetHelpContext60@MP typedef ptr SetHelpContext60@CT
	 SetHelpContext SetHelpContext60@MP ?

	SetVersion60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
	  wMajorVerNum: WORD,
	  wMinorVerNum: WORD

	SetVersion60@MP typedef ptr SetVersion60@CT
	     SetVersion SetVersion60@MP ?

    AddRefTypeInfo60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		pTInfo: ptr ITypeInfo,
	     phRefType: ptr HREFTYPE

    AddRefTypeInfo60@MP typedef ptr AddRefTypeInfo60@CT
	 AddRefTypeInfo AddRefTypeInfo60@MP ?

       AddFuncDesc60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	     pFuncDesc: ptr FUNCDESC

       AddFuncDesc60@MP typedef ptr AddFuncDesc60@CT
	    AddFuncDesc AddFuncDesc60@MP ?

       AddImplType60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	      hRefType: HREFTYPE

       AddImplType60@MP typedef ptr AddImplType60@CT
	    AddImplType AddImplType60@MP ?

  SetImplTypeFlags60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	 implTypeFlags: SINT

  SetImplTypeFlags60@MP typedef ptr SetImplTypeFlags60@CT
       SetImplTypeFlags SetImplTypeFlags60@MP ?

      SetAlignment60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
	   cbAlignment: WORD

      SetAlignment60@MP typedef ptr SetAlignment60@CT
	   SetAlignment SetAlignment60@MP ?

	 SetSchema60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
	    pStrSchema: LPOLESTR

	 SetSchema60@MP typedef ptr SetSchema60@CT
	      SetSchema SetSchema60@MP ?

	AddVarDesc60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	      pVarDesc: ptr VARDESC

	AddVarDesc60@MP typedef ptr AddVarDesc60@CT
	     AddVarDesc AddVarDesc60@MP ?

SetFuncAndParamNames60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT

SetFuncAndParamNames60@MP typedef ptr SetFuncAndParamNames60@CT
   SetFuncAndParamNames SetFuncAndParamNames60@MP ?

	SetVarName60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
		szName: LPOLESTR

	SetVarName60@MP typedef ptr SetVarName60@CT
	     SetVarName SetVarName60@MP ?

  SetTypeDescAlias60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
	   pTDescAlias: ptr TYPEDESC

  SetTypeDescAlias60@MP typedef ptr SetTypeDescAlias60@CT
       SetTypeDescAlias SetTypeDescAlias60@MP ?

DefineFuncAsDllEntry60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	     szDllName: LPOLESTR,
	    szProcName: LPOLESTR

DefineFuncAsDllEntry60@MP typedef ptr DefineFuncAsDllEntry60@CT
   DefineFuncAsDllEntry DefineFuncAsDllEntry60@MP ?

  SetFuncDocString60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	   szDocString: LPOLESTR

  SetFuncDocString60@MP typedef ptr SetFuncDocString60@CT
       SetFuncDocString SetFuncDocString60@MP ?

   SetVarDocString60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	   szDocString: LPOLESTR

   SetVarDocString60@MP typedef ptr SetVarDocString60@CT
	SetVarDocString SetVarDocString60@MP ?

SetFuncHelpContext60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	 dwHelpContext: DWORD

SetFuncHelpContext60@MP typedef ptr SetFuncHelpContext60@CT
     SetFuncHelpContext SetFuncHelpContext60@MP ?

 SetVarHelpContext60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	 dwHelpContext: DWORD

 SetVarHelpContext60@MP typedef ptr SetVarHelpContext60@CT
      SetVarHelpContext SetVarHelpContext60@MP ?

	   SetMops60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	      bstrMops: BSTR

	   SetMops60@MP typedef ptr SetMops60@CT
		SetMops SetMops60@MP ?

    SetTypeIdldesc60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo,
	      pIdlDesc: ptr IDLDESC

    SetTypeIdldesc60@MP typedef ptr SetTypeIdldesc60@CT
	 SetTypeIdldesc SetTypeIdldesc60@MP ?

	    LayOut60@CT typedef proto \
		 pThis: ptr ICreateTypeInfo

	    LayOut60@MP typedef ptr LayOut60@CT
		 LayOut LayOut60@MP ?

	END_INTERFACE

ICreateTypeInfoVtbl	ENDS

LPICreateTypeInfoVtbl	typedef ptr ICreateTypeInfoVtbl
ICreateTypeInfo		STRUC
lpVtbl			LPICreateTypeInfoVtbl ?
ICreateTypeInfo		ENDS






;HRESULT
ICreateTypeInfo_SetGuid_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		  guid: REFGUID



;void
ICreateTypeInfo_SetGuid_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetTypeFlags_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
	    uTypeFlags: UINT



;void
ICreateTypeInfo_SetTypeFlags_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetDocString_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
	       pStrDoc: LPOLESTR



;void
ICreateTypeInfo_SetDocString_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetHelpContext_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
	 dwHelpContext: DWORD



;void
ICreateTypeInfo_SetHelpContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetVersion_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
	  wMajorVerNum: WORD,
	  wMinorVerNum: WORD



;void
ICreateTypeInfo_SetVersion_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_AddRefTypeInfo_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		pTInfo: ptr ITypeInfo,
	     phRefType: ptr HREFTYPE



;void
ICreateTypeInfo_AddRefTypeInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_AddFuncDesc_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	     pFuncDesc: ptr FUNCDESC



;void
ICreateTypeInfo_AddFuncDesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_AddImplType_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	      hRefType: HREFTYPE



;void
ICreateTypeInfo_AddImplType_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetImplTypeFlags_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	 implTypeFlags: SINT



;void
ICreateTypeInfo_SetImplTypeFlags_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetAlignment_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
	   cbAlignment: WORD



;void
ICreateTypeInfo_SetAlignment_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetSchema_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
	    pStrSchema: LPOLESTR



;void
ICreateTypeInfo_SetSchema_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_AddVarDesc_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	      pVarDesc: ptr VARDESC



;void
ICreateTypeInfo_AddVarDesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetFuncAndParamNames_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT



;void
ICreateTypeInfo_SetFuncAndParamNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetVarName_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
		szName: LPOLESTR



;void
ICreateTypeInfo_SetVarName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetTypeDescAlias_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
	   pTDescAlias: ptr TYPEDESC



;void
ICreateTypeInfo_SetTypeDescAlias_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_DefineFuncAsDllEntry_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	     szDllName: LPOLESTR,
	    szProcName: LPOLESTR



;void
ICreateTypeInfo_DefineFuncAsDllEntry_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetFuncDocString_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	   szDocString: LPOLESTR



;void
ICreateTypeInfo_SetFuncDocString_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetVarDocString_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	   szDocString: LPOLESTR



;void
ICreateTypeInfo_SetVarDocString_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetFuncHelpContext_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	 dwHelpContext: DWORD



;void
ICreateTypeInfo_SetFuncHelpContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetVarHelpContext_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	 dwHelpContext: DWORD



;void
ICreateTypeInfo_SetVarHelpContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetMops_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
		 index: UINT,
	      bstrMops: BSTR



;void
ICreateTypeInfo_SetMops_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_SetTypeIdldesc_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo,
	      pIdlDesc: ptr IDLDESC



;void
ICreateTypeInfo_SetTypeIdldesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo_LayOut_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo



;void
ICreateTypeInfo_LayOut_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ICreateTypeInfo2_INTERFACE_DEFINED__
__ICreateTypeInfo2_INTERFACE_DEFINED__ equ 1



LPCREATETYPEINFO2	typedef ptr ICreateTypeInfo2


externdef		IID_ICreateTypeInfo2:IID


ICreateTypeInfo2Vtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		  riid: REFIID

    QueryInterface61@MP typedef ptr QueryInterface61@CT
	 QueryInterface QueryInterface61@MP ?

	    AddRef61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2

	    AddRef61@MP typedef ptr AddRef61@CT
		 AddRef AddRef61@MP ?

	   Release61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2

	   Release61@MP typedef ptr Release61@CT
		Release Release61@MP ?

	   SetGuid61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		  guid: REFGUID

	   SetGuid61@MP typedef ptr SetGuid61@CT
		SetGuid SetGuid61@MP ?

      SetTypeFlags61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	    uTypeFlags: UINT

      SetTypeFlags61@MP typedef ptr SetTypeFlags61@CT
	   SetTypeFlags SetTypeFlags61@MP ?

      SetDocString61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	       pStrDoc: LPOLESTR

      SetDocString61@MP typedef ptr SetDocString61@CT
	   SetDocString SetDocString61@MP ?

    SetHelpContext61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	 dwHelpContext: DWORD

    SetHelpContext61@MP typedef ptr SetHelpContext61@CT
	 SetHelpContext SetHelpContext61@MP ?

	SetVersion61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	  wMajorVerNum: WORD,
	  wMinorVerNum: WORD

	SetVersion61@MP typedef ptr SetVersion61@CT
	     SetVersion SetVersion61@MP ?

    AddRefTypeInfo61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		pTInfo: ptr ITypeInfo,
	     phRefType: ptr HREFTYPE

    AddRefTypeInfo61@MP typedef ptr AddRefTypeInfo61@CT
	 AddRefTypeInfo AddRefTypeInfo61@MP ?

       AddFuncDesc61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	     pFuncDesc: ptr FUNCDESC

       AddFuncDesc61@MP typedef ptr AddFuncDesc61@CT
	    AddFuncDesc AddFuncDesc61@MP ?

       AddImplType61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	      hRefType: HREFTYPE

       AddImplType61@MP typedef ptr AddImplType61@CT
	    AddImplType AddImplType61@MP ?

  SetImplTypeFlags61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	 implTypeFlags: SINT

  SetImplTypeFlags61@MP typedef ptr SetImplTypeFlags61@CT
       SetImplTypeFlags SetImplTypeFlags61@MP ?

      SetAlignment61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	   cbAlignment: WORD

      SetAlignment61@MP typedef ptr SetAlignment61@CT
	   SetAlignment SetAlignment61@MP ?

	 SetSchema61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	    pStrSchema: LPOLESTR

	 SetSchema61@MP typedef ptr SetSchema61@CT
	      SetSchema SetSchema61@MP ?

	AddVarDesc61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	      pVarDesc: ptr VARDESC

	AddVarDesc61@MP typedef ptr AddVarDesc61@CT
	     AddVarDesc AddVarDesc61@MP ?

SetFuncAndParamNames61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT

SetFuncAndParamNames61@MP typedef ptr SetFuncAndParamNames61@CT
   SetFuncAndParamNames SetFuncAndParamNames61@MP ?

	SetVarName61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
		szName: LPOLESTR

	SetVarName61@MP typedef ptr SetVarName61@CT
	     SetVarName SetVarName61@MP ?

  SetTypeDescAlias61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	   pTDescAlias: ptr TYPEDESC

  SetTypeDescAlias61@MP typedef ptr SetTypeDescAlias61@CT
       SetTypeDescAlias SetTypeDescAlias61@MP ?

DefineFuncAsDllEntry61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	     szDllName: LPOLESTR,
	    szProcName: LPOLESTR

DefineFuncAsDllEntry61@MP typedef ptr DefineFuncAsDllEntry61@CT
   DefineFuncAsDllEntry DefineFuncAsDllEntry61@MP ?

  SetFuncDocString61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	   szDocString: LPOLESTR

  SetFuncDocString61@MP typedef ptr SetFuncDocString61@CT
       SetFuncDocString SetFuncDocString61@MP ?

   SetVarDocString61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	   szDocString: LPOLESTR

   SetVarDocString61@MP typedef ptr SetVarDocString61@CT
	SetVarDocString SetVarDocString61@MP ?

SetFuncHelpContext61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	 dwHelpContext: DWORD

SetFuncHelpContext61@MP typedef ptr SetFuncHelpContext61@CT
     SetFuncHelpContext SetFuncHelpContext61@MP ?

 SetVarHelpContext61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	 dwHelpContext: DWORD

 SetVarHelpContext61@MP typedef ptr SetVarHelpContext61@CT
      SetVarHelpContext SetVarHelpContext61@MP ?

	   SetMops61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
	      bstrMops: BSTR

	   SetMops61@MP typedef ptr SetMops61@CT
		SetMops SetMops61@MP ?

    SetTypeIdldesc61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	      pIdlDesc: ptr IDLDESC

    SetTypeIdldesc61@MP typedef ptr SetTypeIdldesc61@CT
	 SetTypeIdldesc SetTypeIdldesc61@MP ?

	    LayOut61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2

	    LayOut61@MP typedef ptr LayOut61@CT
		 LayOut LayOut61@MP ?

    DeleteFuncDesc61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT

    DeleteFuncDesc61@MP typedef ptr DeleteFuncDesc61@CT
	 DeleteFuncDesc DeleteFuncDesc61@MP ?

DeleteFuncDescByMemId61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 memid: MEMBERID,
	       invKind: INVOKEKIND

DeleteFuncDescByMemId61@MP typedef ptr DeleteFuncDescByMemId61@CT
  DeleteFuncDescByMemId DeleteFuncDescByMemId61@MP ?

     DeleteVarDesc61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT

     DeleteVarDesc61@MP typedef ptr DeleteVarDesc61@CT
	  DeleteVarDesc DeleteVarDesc61@MP ?

DeleteVarDescByMemId61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 memid: MEMBERID

DeleteVarDescByMemId61@MP typedef ptr DeleteVarDescByMemId61@CT
   DeleteVarDescByMemId DeleteVarDescByMemId61@MP ?

    DeleteImplType61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT

    DeleteImplType61@MP typedef ptr DeleteImplType61@CT
	 DeleteImplType DeleteImplType61@MP ?

       SetCustData61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

       SetCustData61@MP typedef ptr SetCustData61@CT
	    SetCustData SetCustData61@MP ?

   SetFuncCustData61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

   SetFuncCustData61@MP typedef ptr SetFuncCustData61@CT
	SetFuncCustData SetFuncCustData61@MP ?

  SetParamCustData61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
	     indexFunc: UINT,
	    indexParam: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

  SetParamCustData61@MP typedef ptr SetParamCustData61@CT
       SetParamCustData SetParamCustData61@MP ?

    SetVarCustData61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

    SetVarCustData61@MP typedef ptr SetVarCustData61@CT
	 SetVarCustData SetVarCustData61@MP ?

SetImplTypeCustData61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

SetImplTypeCustData61@MP typedef ptr SetImplTypeCustData61@CT
    SetImplTypeCustData SetImplTypeCustData61@MP ?

SetHelpStringContext61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
   dwHelpStringContext: ULONG

SetHelpStringContext61@MP typedef ptr SetHelpStringContext61@CT
   SetHelpStringContext SetHelpStringContext61@MP ?

SetFuncHelpStringContext61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
   dwHelpStringContext: ULONG

SetFuncHelpStringContext61@MP typedef ptr SetFuncHelpStringContext61@CT
SetFuncHelpStringContext SetFuncHelpStringContext61@MP ?

SetVarHelpStringContext61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
   dwHelpStringContext: ULONG

SetVarHelpStringContext61@MP typedef ptr SetVarHelpStringContext61@CT
SetVarHelpStringContext SetVarHelpStringContext61@MP ?

	Invalidate61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2

	Invalidate61@MP typedef ptr Invalidate61@CT
	     Invalidate Invalidate61@MP ?

	   SetName61@CT typedef proto \
		 pThis: ptr ICreateTypeInfo2,
		szName: LPOLESTR

	   SetName61@MP typedef ptr SetName61@CT
		SetName SetName61@MP ?

	END_INTERFACE

ICreateTypeInfo2Vtbl	ENDS

LPICreateTypeInfo2Vtbl	typedef ptr ICreateTypeInfo2Vtbl
ICreateTypeInfo2	STRUC
lpVtbl			LPICreateTypeInfo2Vtbl ?
ICreateTypeInfo2	ENDS






;HRESULT
ICreateTypeInfo2_DeleteFuncDesc_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT



;void
ICreateTypeInfo2_DeleteFuncDesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_DeleteFuncDescByMemId_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 memid: MEMBERID,
	       invKind: INVOKEKIND



;void
ICreateTypeInfo2_DeleteFuncDescByMemId_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_DeleteVarDesc_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT



;void
ICreateTypeInfo2_DeleteVarDesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_DeleteVarDescByMemId_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 memid: MEMBERID



;void
ICreateTypeInfo2_DeleteVarDescByMemId_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_DeleteImplType_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT



;void
ICreateTypeInfo2_DeleteImplType_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetCustData_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ICreateTypeInfo2_SetCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetFuncCustData_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ICreateTypeInfo2_SetFuncCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetParamCustData_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
	     indexFunc: UINT,
	    indexParam: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ICreateTypeInfo2_SetParamCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetVarCustData_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ICreateTypeInfo2_SetVarCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetImplTypeCustData_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ICreateTypeInfo2_SetImplTypeCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetHelpStringContext_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
   dwHelpStringContext: ULONG



;void
ICreateTypeInfo2_SetHelpStringContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetFuncHelpStringContext_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
   dwHelpStringContext: ULONG



;void
ICreateTypeInfo2_SetFuncHelpStringContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetVarHelpStringContext_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		 index: UINT,
   dwHelpStringContext: ULONG



;void
ICreateTypeInfo2_SetVarHelpStringContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_Invalidate_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2



;void
ICreateTypeInfo2_Invalidate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeInfo2_SetName_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeInfo2,
		szName: LPOLESTR



;void
ICreateTypeInfo2_SetName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ICreateTypeLib_INTERFACE_DEFINED__
__ICreateTypeLib_INTERFACE_DEFINED__ equ 1



LPCREATETYPELIB		typedef ptr ICreateTypeLib


externdef		IID_ICreateTypeLib:IID


ICreateTypeLibVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
		  riid: REFIID

    QueryInterface62@MP typedef ptr QueryInterface62@CT
	 QueryInterface QueryInterface62@MP ?

	    AddRef62@CT typedef proto \
		 pThis: ptr ICreateTypeLib

	    AddRef62@MP typedef ptr AddRef62@CT
		 AddRef AddRef62@MP ?

	   Release62@CT typedef proto \
		 pThis: ptr ICreateTypeLib

	   Release62@MP typedef ptr Release62@CT
		Release Release62@MP ?

    CreateTypeInfo62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
		szName: LPOLESTR,
		 tkind: TYPEKIND,
	      ppCTInfo: ptr ICreateTypeInfo

    CreateTypeInfo62@MP typedef ptr CreateTypeInfo62@CT
	 CreateTypeInfo CreateTypeInfo62@MP ?

	   SetName62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
		szName: LPOLESTR

	   SetName62@MP typedef ptr SetName62@CT
		SetName SetName62@MP ?

	SetVersion62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
	  wMajorVerNum: WORD,
	  wMinorVerNum: WORD

	SetVersion62@MP typedef ptr SetVersion62@CT
	     SetVersion SetVersion62@MP ?

	   SetGuid62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
		  guid: REFGUID

	   SetGuid62@MP typedef ptr SetGuid62@CT
		SetGuid SetGuid62@MP ?

      SetDocString62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
		 szDoc: LPOLESTR

      SetDocString62@MP typedef ptr SetDocString62@CT
	   SetDocString SetDocString62@MP ?

   SetHelpFileName62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
	szHelpFileName: LPOLESTR

   SetHelpFileName62@MP typedef ptr SetHelpFileName62@CT
	SetHelpFileName SetHelpFileName62@MP ?

    SetHelpContext62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
	 dwHelpContext: DWORD

    SetHelpContext62@MP typedef ptr SetHelpContext62@CT
	 SetHelpContext SetHelpContext62@MP ?

	   SetLcid62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
		  lcid: LCID

	   SetLcid62@MP typedef ptr SetLcid62@CT
		SetLcid SetLcid62@MP ?

       SetLibFlags62@CT typedef proto \
		 pThis: ptr ICreateTypeLib,
	     uLibFlags: UINT

       SetLibFlags62@MP typedef ptr SetLibFlags62@CT
	    SetLibFlags SetLibFlags62@MP ?

    SaveAllChanges62@CT typedef proto \
		 pThis: ptr ICreateTypeLib

    SaveAllChanges62@MP typedef ptr SaveAllChanges62@CT
	 SaveAllChanges SaveAllChanges62@MP ?

	END_INTERFACE

ICreateTypeLibVtbl	ENDS

LPICreateTypeLibVtbl	typedef ptr ICreateTypeLibVtbl
ICreateTypeLib		STRUC
lpVtbl			LPICreateTypeLibVtbl ?
ICreateTypeLib		ENDS






;HRESULT
ICreateTypeLib_CreateTypeInfo_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
		szName: LPOLESTR,
		 tkind: TYPEKIND,
	      ppCTInfo: ptr ICreateTypeInfo



;void
ICreateTypeLib_CreateTypeInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SetName_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
		szName: LPOLESTR



;void
ICreateTypeLib_SetName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SetVersion_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
	  wMajorVerNum: WORD,
	  wMinorVerNum: WORD



;void
ICreateTypeLib_SetVersion_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SetGuid_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
		  guid: REFGUID



;void
ICreateTypeLib_SetGuid_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SetDocString_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
		 szDoc: LPOLESTR



;void
ICreateTypeLib_SetDocString_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SetHelpFileName_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
	szHelpFileName: LPOLESTR



;void
ICreateTypeLib_SetHelpFileName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SetHelpContext_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
	 dwHelpContext: DWORD



;void
ICreateTypeLib_SetHelpContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SetLcid_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
		  lcid: LCID



;void
ICreateTypeLib_SetLcid_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SetLibFlags_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib,
	     uLibFlags: UINT



;void
ICreateTypeLib_SetLibFlags_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib_SaveAllChanges_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib



;void
ICreateTypeLib_SaveAllChanges_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ICreateTypeLib2_INTERFACE_DEFINED__
__ICreateTypeLib2_INTERFACE_DEFINED__ equ 1



LPCREATETYPELIB2	typedef ptr ICreateTypeLib2


externdef		IID_ICreateTypeLib2:IID


ICreateTypeLib2Vtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
		  riid: REFIID

    QueryInterface63@MP typedef ptr QueryInterface63@CT
	 QueryInterface QueryInterface63@MP ?

	    AddRef63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2

	    AddRef63@MP typedef ptr AddRef63@CT
		 AddRef AddRef63@MP ?

	   Release63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2

	   Release63@MP typedef ptr Release63@CT
		Release Release63@MP ?

    CreateTypeInfo63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
		szName: LPOLESTR,
		 tkind: TYPEKIND,
	      ppCTInfo: ptr ICreateTypeInfo

    CreateTypeInfo63@MP typedef ptr CreateTypeInfo63@CT
	 CreateTypeInfo CreateTypeInfo63@MP ?

	   SetName63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
		szName: LPOLESTR

	   SetName63@MP typedef ptr SetName63@CT
		SetName SetName63@MP ?

	SetVersion63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
	  wMajorVerNum: WORD,
	  wMinorVerNum: WORD

	SetVersion63@MP typedef ptr SetVersion63@CT
	     SetVersion SetVersion63@MP ?

	   SetGuid63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
		  guid: REFGUID

	   SetGuid63@MP typedef ptr SetGuid63@CT
		SetGuid SetGuid63@MP ?

      SetDocString63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
		 szDoc: LPOLESTR

      SetDocString63@MP typedef ptr SetDocString63@CT
	   SetDocString SetDocString63@MP ?

   SetHelpFileName63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
	szHelpFileName: LPOLESTR

   SetHelpFileName63@MP typedef ptr SetHelpFileName63@CT
	SetHelpFileName SetHelpFileName63@MP ?

    SetHelpContext63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
	 dwHelpContext: DWORD

    SetHelpContext63@MP typedef ptr SetHelpContext63@CT
	 SetHelpContext SetHelpContext63@MP ?

	   SetLcid63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
		  lcid: LCID

	   SetLcid63@MP typedef ptr SetLcid63@CT
		SetLcid SetLcid63@MP ?

       SetLibFlags63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
	     uLibFlags: UINT

       SetLibFlags63@MP typedef ptr SetLibFlags63@CT
	    SetLibFlags SetLibFlags63@MP ?

    SaveAllChanges63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2

    SaveAllChanges63@MP typedef ptr SaveAllChanges63@CT
	 SaveAllChanges SaveAllChanges63@MP ?

    DeleteTypeInfo63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
		szName: LPOLESTR

    DeleteTypeInfo63@MP typedef ptr DeleteTypeInfo63@CT
	 DeleteTypeInfo DeleteTypeInfo63@MP ?

       SetCustData63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

       SetCustData63@MP typedef ptr SetCustData63@CT
	    SetCustData SetCustData63@MP ?

SetHelpStringContext63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
   dwHelpStringContext: ULONG

SetHelpStringContext63@MP typedef ptr SetHelpStringContext63@CT
   SetHelpStringContext SetHelpStringContext63@MP ?

  SetHelpStringDll63@CT typedef proto \
		 pThis: ptr ICreateTypeLib2,
	    szFileName: LPOLESTR

  SetHelpStringDll63@MP typedef ptr SetHelpStringDll63@CT
       SetHelpStringDll SetHelpStringDll63@MP ?

	END_INTERFACE

ICreateTypeLib2Vtbl	ENDS

LPICreateTypeLib2Vtbl	typedef ptr ICreateTypeLib2Vtbl
ICreateTypeLib2		STRUC
lpVtbl			LPICreateTypeLib2Vtbl ?
ICreateTypeLib2		ENDS






;HRESULT
ICreateTypeLib2_DeleteTypeInfo_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib2,
		szName: LPOLESTR



;void
ICreateTypeLib2_DeleteTypeInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib2_SetCustData_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib2,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ICreateTypeLib2_SetCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib2_SetHelpStringContext_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib2,
   dwHelpStringContext: ULONG



;void
ICreateTypeLib2_SetHelpStringContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateTypeLib2_SetHelpStringDll_Proxy proto WINAPI \
		 pThis: ptr ICreateTypeLib2,
	    szFileName: LPOLESTR



;void
ICreateTypeLib2_SetHelpStringDll_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IDispatch_INTERFACE_DEFINED__
__IDispatch_INTERFACE_DEFINED__ equ 1



LPDISPATCH		typedef ptr IDispatch

DISPID_UNKNOWN		equ ( -1 )

DISPID_VALUE		equ ( 0 )

DISPID_PROPERTYPUT	equ ( -3 )

DISPID_NEWENUM		equ ( -4 )

DISPID_EVALUATE		equ ( -5 )

DISPID_CONSTRUCTOR	equ ( -6 )

DISPID_DESTRUCTOR	equ ( -7 )

DISPID_COLLECT		equ ( -8 )


externdef		IID_IDispatch:IID


IDispatchVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface64@CT typedef proto \
		 pThis: ptr IDispatch,
		  riid: REFIID

    QueryInterface64@MP typedef ptr QueryInterface64@CT
	 QueryInterface QueryInterface64@MP ?

	    AddRef64@CT typedef proto \
		 pThis: ptr IDispatch

	    AddRef64@MP typedef ptr AddRef64@CT
		 AddRef AddRef64@MP ?

	   Release64@CT typedef proto \
		 pThis: ptr IDispatch

	   Release64@MP typedef ptr Release64@CT
		Release Release64@MP ?

  GetTypeInfoCount64@CT typedef proto \
		 pThis: ptr IDispatch,
	       pctinfo: ptr UINT

  GetTypeInfoCount64@MP typedef ptr GetTypeInfoCount64@CT
       GetTypeInfoCount GetTypeInfoCount64@MP ?

       GetTypeInfo64@CT typedef proto \
		 pThis: ptr IDispatch,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo64@MP typedef ptr GetTypeInfo64@CT
	    GetTypeInfo GetTypeInfo64@MP ?

     GetIDsOfNames64@CT typedef proto \
		 pThis: ptr IDispatch,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames64@MP typedef ptr GetIDsOfNames64@CT
	  GetIDsOfNames GetIDsOfNames64@MP ?

	   _Invoke64@CT typedef proto \
		 pThis: ptr IDispatch,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke64@MP typedef ptr _Invoke64@CT
		_Invoke _Invoke64@MP ?

	END_INTERFACE

IDispatchVtbl		ENDS

LPIDispatchVtbl		typedef ptr IDispatchVtbl
IDispatch		STRUC
lpVtbl			LPIDispatchVtbl ?
IDispatch		ENDS






;HRESULT
IDispatch_GetTypeInfoCount_Proxy proto WINAPI \
		 pThis: ptr IDispatch,
	       pctinfo: ptr UINT



;void
IDispatch_GetTypeInfoCount_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IDispatch_GetTypeInfo_Proxy proto WINAPI \
		 pThis: ptr IDispatch,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo



;void
IDispatch_GetTypeInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IDispatch_GetIDsOfNames_Proxy proto WINAPI \
		 pThis: ptr IDispatch,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID



;void
IDispatch_GetIDsOfNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IDispatch_RemoteInvoke_Proxy proto WINAPI \
		 pThis: ptr IDispatch,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
	       dwFlags: DWORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	       pArgErr: ptr UINT,
	       cVarRef: UINT,
	   rgVarRefIdx: ptr UINT,
	      rgVarRef: ptr VARIANTARG



;void
IDispatch_RemoteInvoke_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IEnumVARIANT_INTERFACE_DEFINED__
__IEnumVARIANT_INTERFACE_DEFINED__ equ 1



LPENUMVARIANT		typedef ptr IEnumVARIANT


externdef		IID_IEnumVARIANT:IID


IEnumVARIANTVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface65@CT typedef proto \
		 pThis: ptr IEnumVARIANT,
		  riid: REFIID

    QueryInterface65@MP typedef ptr QueryInterface65@CT
	 QueryInterface QueryInterface65@MP ?

	    AddRef65@CT typedef proto \
		 pThis: ptr IEnumVARIANT

	    AddRef65@MP typedef ptr AddRef65@CT
		 AddRef AddRef65@MP ?

	   Release65@CT typedef proto \
		 pThis: ptr IEnumVARIANT

	   Release65@MP typedef ptr Release65@CT
		Release Release65@MP ?

	      Next65@CT typedef proto \
		 pThis: ptr IEnumVARIANT,
		  celt: ULONG,
		 rgVar: ptr VARIANT,
	  pCeltFetched: ptr ULONG

	      Next65@MP typedef ptr Next65@CT
		   Next Next65@MP ?

	      Skip65@CT typedef proto \
		 pThis: ptr IEnumVARIANT,
		  celt: ULONG

	      Skip65@MP typedef ptr Skip65@CT
		   Skip Skip65@MP ?

	     Reset65@CT typedef proto \
		 pThis: ptr IEnumVARIANT

	     Reset65@MP typedef ptr Reset65@CT
		  Reset Reset65@MP ?

	     Clone65@CT typedef proto \
		 pThis: ptr IEnumVARIANT,
		ppEnum: ptr IEnumVARIANT

	     Clone65@MP typedef ptr Clone65@CT
		  Clone Clone65@MP ?

	END_INTERFACE

IEnumVARIANTVtbl	ENDS

LPIEnumVARIANTVtbl	typedef ptr IEnumVARIANTVtbl
IEnumVARIANT		STRUC
lpVtbl			LPIEnumVARIANTVtbl ?
IEnumVARIANT		ENDS






;HRESULT
IEnumVARIANT_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumVARIANT,
		  celt: ULONG,
		 rgVar: ptr VARIANT,
	  pCeltFetched: ptr ULONG



;void
IEnumVARIANT_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IEnumVARIANT_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumVARIANT,
		  celt: ULONG



;void
IEnumVARIANT_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IEnumVARIANT_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumVARIANT



;void
IEnumVARIANT_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IEnumVARIANT_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumVARIANT,
		ppEnum: ptr IEnumVARIANT



;void
IEnumVARIANT_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ITypeComp_INTERFACE_DEFINED__
__ITypeComp_INTERFACE_DEFINED__ equ 1



LPTYPECOMP		typedef ptr ITypeComp

;tagDESCKIND		typedef SDWORD
DESCKIND_NONE		equ 0
DESCKIND_FUNCDESC	equ DESCKIND_NONE + 1
DESCKIND_VARDESC	equ DESCKIND_FUNCDESC + 1
DESCKIND_TYPECOMP	equ DESCKIND_VARDESC + 1
DESCKIND_IMPLICITAPPOBJ equ DESCKIND_TYPECOMP + 1
DESCKIND_MAX		equ DESCKIND_IMPLICITAPPOBJ + 1

BINDPTR			UNION
lpfuncdesc		LPFUNCDESC ?
lpvardesc		LPVARDESC ?
lptcomp			PVOID ?;LPITypeComp ?
BINDPTR			ENDS
LPBINDPTR		typedef ptr BINDPTR

externdef		IID_ITypeComp:IID


ITypeCompVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface66@CT typedef proto \
		 pThis: ptr ITypeComp,
		  riid: REFIID

    QueryInterface66@MP typedef ptr QueryInterface66@CT
	 QueryInterface QueryInterface66@MP ?

	    AddRef66@CT typedef proto \
		 pThis: ptr ITypeComp

	    AddRef66@MP typedef ptr AddRef66@CT
		 AddRef AddRef66@MP ?

	   Release66@CT typedef proto \
		 pThis: ptr ITypeComp

	   Release66@MP typedef ptr Release66@CT
		Release Release66@MP ?

	      Bind66@CT typedef proto \
		 pThis: ptr ITypeComp,
		szName: LPOLESTR,
	      lHashVal: ULONG,
		wFlags: WORD,
	       ppTInfo: ptr ITypeInfo,
	     pDescKind: ptr DESCKIND,
	      pBindPtr: ptr BINDPTR

	      Bind66@MP typedef ptr Bind66@CT
		   Bind Bind66@MP ?

	  BindType66@CT typedef proto \
		 pThis: ptr ITypeComp,
		szName: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo,
	       ppTComp: ptr ITypeComp

	  BindType66@MP typedef ptr BindType66@CT
	       BindType BindType66@MP ?

	END_INTERFACE

ITypeCompVtbl		ENDS

LPITypeCompVtbl		typedef ptr ITypeCompVtbl
ITypeComp		STRUC
lpVtbl			LPITypeCompVtbl ?
ITypeComp		ENDS






;HRESULT
ITypeComp_RemoteBind_Proxy proto WINAPI \
		 pThis: ptr ITypeComp,
		szName: LPOLESTR,
	      lHashVal: ULONG,
		wFlags: WORD,
	       ppTInfo: ptr ITypeInfo,
	     pDescKind: ptr DESCKIND,
	    ppFuncDesc: ptr LPFUNCDESC,
	     ppVarDesc: ptr LPVARDESC,
	    ppTypeComp: ptr ITypeComp,
		pDummy: ptr CLEANLOCALSTORAGE



;void
ITypeComp_RemoteBind_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeComp_RemoteBindType_Proxy proto WINAPI \
		 pThis: ptr ITypeComp,
		szName: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo



;void
ITypeComp_RemoteBindType_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ITypeInfo_INTERFACE_DEFINED__
__ITypeInfo_INTERFACE_DEFINED__ equ 1



LPTYPEINFO		typedef ptr ITypeInfo


externdef		IID_ITypeInfo:IID


ITypeInfoVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		  riid: REFIID

    QueryInterface67@MP typedef ptr QueryInterface67@CT
	 QueryInterface QueryInterface67@MP ?

	    AddRef67@CT typedef proto \
		 pThis: ptr ITypeInfo

	    AddRef67@MP typedef ptr AddRef67@CT
		 AddRef AddRef67@MP ?

	   Release67@CT typedef proto \
		 pThis: ptr ITypeInfo

	   Release67@MP typedef ptr Release67@CT
		Release Release67@MP ?

       GetTypeAttr67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	    ppTypeAttr: ptr TYPEATTR

       GetTypeAttr67@MP typedef ptr GetTypeAttr67@CT
	    GetTypeAttr GetTypeAttr67@MP ?

       GetTypeComp67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	       ppTComp: ptr ITypeComp

       GetTypeComp67@MP typedef ptr GetTypeComp67@CT
	    GetTypeComp GetTypeComp67@MP ?

       GetFuncDesc67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	    ppFuncDesc: ptr FUNCDESC

       GetFuncDesc67@MP typedef ptr GetFuncDesc67@CT
	    GetFuncDesc GetFuncDesc67@MP ?

	GetVarDesc67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	     ppVarDesc: ptr VARDESC

	GetVarDesc67@MP typedef ptr GetVarDesc67@CT
	     GetVarDesc GetVarDesc67@MP ?

	  GetNames67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	   rgBstrNames: ptr BSTR,
	     cMaxNames: UINT,
	       pcNames: ptr UINT

	  GetNames67@MP typedef ptr GetNames67@CT
	       GetNames GetNames67@MP ?

GetRefTypeOfImplType67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	      pRefType: ptr HREFTYPE

GetRefTypeOfImplType67@MP typedef ptr GetRefTypeOfImplType67@CT
   GetRefTypeOfImplType GetRefTypeOfImplType67@MP ?

  GetImplTypeFlags67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	pImplTypeFlags: ptr SINT

  GetImplTypeFlags67@MP typedef ptr GetImplTypeFlags67@CT
       GetImplTypeFlags GetImplTypeFlags67@MP ?

     GetIDsOfNames67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		pMemId: ptr MEMBERID

     GetIDsOfNames67@MP typedef ptr GetIDsOfNames67@CT
	  GetIDsOfNames GetIDsOfNames67@MP ?

	   _Invoke67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	    pvInstance: PVOID,
		 memid: MEMBERID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke67@MP typedef ptr _Invoke67@CT
		_Invoke _Invoke67@MP ?

  GetDocumentation67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR

  GetDocumentation67@MP typedef ptr GetDocumentation67@CT
       GetDocumentation GetDocumentation67@MP ?

       GetDllEntry67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
	  pBstrDllName: ptr BSTR,
	     pBstrName: ptr BSTR,
	     pwOrdinal: ptr WORD

       GetDllEntry67@MP typedef ptr GetDllEntry67@CT
	    GetDllEntry GetDllEntry67@MP ?

    GetRefTypeInfo67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	      hRefType: HREFTYPE,
	       ppTInfo: ptr ITypeInfo

    GetRefTypeInfo67@MP typedef ptr GetRefTypeInfo67@CT
	 GetRefTypeInfo GetRefTypeInfo67@MP ?

   AddressOfMember67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
		   ppv: ptr PVOID

   AddressOfMember67@MP typedef ptr AddressOfMember67@CT
	AddressOfMember AddressOfMember67@MP ?

    CreateInstance67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID,
		ppvObj: ptr PVOID

    CreateInstance67@MP typedef ptr CreateInstance67@CT
	 CreateInstance CreateInstance67@MP ?

	   GetMops67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	     pBstrMops: ptr BSTR

	   GetMops67@MP typedef ptr GetMops67@CT
		GetMops GetMops67@MP ?

GetContainingTypeLib67@CT typedef proto \
		 pThis: ptr ITypeInfo,
		ppTLib: ptr ITypeLib,
		pIndex: ptr UINT

GetContainingTypeLib67@MP typedef ptr GetContainingTypeLib67@CT
   GetContainingTypeLib GetContainingTypeLib67@MP ?

   ReleaseTypeAttr67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	     pTypeAttr: ptr TYPEATTR

   ReleaseTypeAttr67@MP typedef ptr ReleaseTypeAttr67@CT
	ReleaseTypeAttr ReleaseTypeAttr67@MP ?

   ReleaseFuncDesc67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	     pFuncDesc: ptr FUNCDESC

   ReleaseFuncDesc67@MP typedef ptr ReleaseFuncDesc67@CT
	ReleaseFuncDesc ReleaseFuncDesc67@MP ?

    ReleaseVarDesc67@CT typedef proto \
		 pThis: ptr ITypeInfo,
	      pVarDesc: ptr VARDESC

    ReleaseVarDesc67@MP typedef ptr ReleaseVarDesc67@CT
	 ReleaseVarDesc ReleaseVarDesc67@MP ?

	END_INTERFACE

ITypeInfoVtbl		ENDS

LPITypeInfoVtbl		typedef ptr ITypeInfoVtbl
ITypeInfo		STRUC
lpVtbl			LPITypeInfoVtbl ?
ITypeInfo		ENDS






;HRESULT
ITypeInfo_RemoteGetTypeAttr_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	    ppTypeAttr: ptr LPTYPEATTR,
		pDummy: ptr CLEANLOCALSTORAGE



;void
ITypeInfo_RemoteGetTypeAttr_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_GetTypeComp_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	       ppTComp: ptr ITypeComp



;void
ITypeInfo_GetTypeComp_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_RemoteGetFuncDesc_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	    ppFuncDesc: ptr LPFUNCDESC,
		pDummy: ptr CLEANLOCALSTORAGE



;void
ITypeInfo_RemoteGetFuncDesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_RemoteGetVarDesc_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	     ppVarDesc: ptr LPVARDESC,
		pDummy: ptr CLEANLOCALSTORAGE



;void
ITypeInfo_RemoteGetVarDesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_RemoteGetNames_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	   rgBstrNames: ptr BSTR,
	     cMaxNames: UINT,
	       pcNames: ptr UINT



;void
ITypeInfo_RemoteGetNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_GetRefTypeOfImplType_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	      pRefType: ptr HREFTYPE



;void
ITypeInfo_GetRefTypeOfImplType_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_GetImplTypeFlags_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	pImplTypeFlags: ptr SINT



;void
ITypeInfo_GetImplTypeFlags_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_LocalGetIDsOfNames_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo



;void
ITypeInfo_LocalGetIDsOfNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_LocalInvoke_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo



;void
ITypeInfo_LocalInvoke_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_RemoteGetDocumentation_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	   refPtrFlags: DWORD,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR



;void
ITypeInfo_RemoteGetDocumentation_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_RemoteGetDllEntry_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
	   refPtrFlags: DWORD,
	  pBstrDllName: ptr BSTR,
	     pBstrName: ptr BSTR,
	     pwOrdinal: ptr WORD



;void
ITypeInfo_RemoteGetDllEntry_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_GetRefTypeInfo_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	      hRefType: HREFTYPE,
	       ppTInfo: ptr ITypeInfo



;void
ITypeInfo_GetRefTypeInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_LocalAddressOfMember_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo



;void
ITypeInfo_LocalAddressOfMember_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_RemoteCreateInstance_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		  riid: REFIID,
		ppvObj: ptr IUnknown



;void
ITypeInfo_RemoteCreateInstance_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_GetMops_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	     pBstrMops: ptr BSTR



;void
ITypeInfo_GetMops_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_RemoteGetContainingTypeLib_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		ppTLib: ptr ITypeLib,
		pIndex: ptr UINT



;void
ITypeInfo_RemoteGetContainingTypeLib_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_LocalReleaseTypeAttr_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo



;void
ITypeInfo_LocalReleaseTypeAttr_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_LocalReleaseFuncDesc_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo



;void
ITypeInfo_LocalReleaseFuncDesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo_LocalReleaseVarDesc_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo



;void
ITypeInfo_LocalReleaseVarDesc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ITypeInfo2_INTERFACE_DEFINED__
__ITypeInfo2_INTERFACE_DEFINED__ equ 1



LPTYPEINFO2		typedef ptr ITypeInfo2


externdef		IID_ITypeInfo2:IID


ITypeInfo2Vtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		  riid: REFIID

    QueryInterface68@MP typedef ptr QueryInterface68@CT
	 QueryInterface QueryInterface68@MP ?

	    AddRef68@CT typedef proto \
		 pThis: ptr ITypeInfo2

	    AddRef68@MP typedef ptr AddRef68@CT
		 AddRef AddRef68@MP ?

	   Release68@CT typedef proto \
		 pThis: ptr ITypeInfo2

	   Release68@MP typedef ptr Release68@CT
		Release Release68@MP ?

       GetTypeAttr68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	    ppTypeAttr: ptr TYPEATTR

       GetTypeAttr68@MP typedef ptr GetTypeAttr68@CT
	    GetTypeAttr GetTypeAttr68@MP ?

       GetTypeComp68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	       ppTComp: ptr ITypeComp

       GetTypeComp68@MP typedef ptr GetTypeComp68@CT
	    GetTypeComp GetTypeComp68@MP ?

       GetFuncDesc68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	    ppFuncDesc: ptr FUNCDESC

       GetFuncDesc68@MP typedef ptr GetFuncDesc68@CT
	    GetFuncDesc GetFuncDesc68@MP ?

	GetVarDesc68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	     ppVarDesc: ptr VARDESC

	GetVarDesc68@MP typedef ptr GetVarDesc68@CT
	     GetVarDesc GetVarDesc68@MP ?

	  GetNames68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	   rgBstrNames: ptr BSTR,
	     cMaxNames: UINT,
	       pcNames: ptr UINT

	  GetNames68@MP typedef ptr GetNames68@CT
	       GetNames GetNames68@MP ?

GetRefTypeOfImplType68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	      pRefType: ptr HREFTYPE

GetRefTypeOfImplType68@MP typedef ptr GetRefTypeOfImplType68@CT
   GetRefTypeOfImplType GetRefTypeOfImplType68@MP ?

  GetImplTypeFlags68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	pImplTypeFlags: ptr SINT

  GetImplTypeFlags68@MP typedef ptr GetImplTypeFlags68@CT
       GetImplTypeFlags GetImplTypeFlags68@MP ?

     GetIDsOfNames68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		pMemId: ptr MEMBERID

     GetIDsOfNames68@MP typedef ptr GetIDsOfNames68@CT
	  GetIDsOfNames GetIDsOfNames68@MP ?

	   _Invoke68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	    pvInstance: PVOID,
		 memid: MEMBERID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke68@MP typedef ptr _Invoke68@CT
		_Invoke _Invoke68@MP ?

  GetDocumentation68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR

  GetDocumentation68@MP typedef ptr GetDocumentation68@CT
       GetDocumentation GetDocumentation68@MP ?

       GetDllEntry68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
	  pBstrDllName: ptr BSTR,
	     pBstrName: ptr BSTR,
	     pwOrdinal: ptr WORD

       GetDllEntry68@MP typedef ptr GetDllEntry68@CT
	    GetDllEntry GetDllEntry68@MP ?

    GetRefTypeInfo68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	      hRefType: HREFTYPE,
	       ppTInfo: ptr ITypeInfo

    GetRefTypeInfo68@MP typedef ptr GetRefTypeInfo68@CT
	 GetRefTypeInfo GetRefTypeInfo68@MP ?

   AddressOfMember68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
		   ppv: ptr PVOID

   AddressOfMember68@MP typedef ptr AddressOfMember68@CT
	AddressOfMember AddressOfMember68@MP ?

    CreateInstance68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID,
		ppvObj: ptr PVOID

    CreateInstance68@MP typedef ptr CreateInstance68@CT
	 CreateInstance CreateInstance68@MP ?

	   GetMops68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	     pBstrMops: ptr BSTR

	   GetMops68@MP typedef ptr GetMops68@CT
		GetMops GetMops68@MP ?

GetContainingTypeLib68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		ppTLib: ptr ITypeLib,
		pIndex: ptr UINT

GetContainingTypeLib68@MP typedef ptr GetContainingTypeLib68@CT
   GetContainingTypeLib GetContainingTypeLib68@MP ?

   ReleaseTypeAttr68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	     pTypeAttr: ptr TYPEATTR

   ReleaseTypeAttr68@MP typedef ptr ReleaseTypeAttr68@CT
	ReleaseTypeAttr ReleaseTypeAttr68@MP ?

   ReleaseFuncDesc68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	     pFuncDesc: ptr FUNCDESC

   ReleaseFuncDesc68@MP typedef ptr ReleaseFuncDesc68@CT
	ReleaseFuncDesc ReleaseFuncDesc68@MP ?

    ReleaseVarDesc68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	      pVarDesc: ptr VARDESC

    ReleaseVarDesc68@MP typedef ptr ReleaseVarDesc68@CT
	 ReleaseVarDesc ReleaseVarDesc68@MP ?

       GetTypeKind68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	     pTypeKind: ptr TYPEKIND

       GetTypeKind68@MP typedef ptr GetTypeKind68@CT
	    GetTypeKind GetTypeKind68@MP ?

      GetTypeFlags68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	    pTypeFlags: ptr ULONG

      GetTypeFlags68@MP typedef ptr GetTypeFlags68@CT
	   GetTypeFlags GetTypeFlags68@MP ?

GetFuncIndexOfMemId68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
	    pFuncIndex: ptr UINT

GetFuncIndexOfMemId68@MP typedef ptr GetFuncIndexOfMemId68@CT
    GetFuncIndexOfMemId GetFuncIndexOfMemId68@MP ?

GetVarIndexOfMemId68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	     pVarIndex: ptr UINT

GetVarIndexOfMemId68@MP typedef ptr GetVarIndexOfMemId68@CT
     GetVarIndexOfMemId GetVarIndexOfMemId68@MP ?

       GetCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

       GetCustData68@MP typedef ptr GetCustData68@CT
	    GetCustData GetCustData68@MP ?

   GetFuncCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

   GetFuncCustData68@MP typedef ptr GetFuncCustData68@CT
	GetFuncCustData GetFuncCustData68@MP ?

  GetParamCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	     indexFunc: UINT,
	    indexParam: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

  GetParamCustData68@MP typedef ptr GetParamCustData68@CT
       GetParamCustData GetParamCustData68@MP ?

    GetVarCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

    GetVarCustData68@MP typedef ptr GetVarCustData68@CT
	 GetVarCustData GetVarCustData68@MP ?

GetImplTypeCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

GetImplTypeCustData68@MP typedef ptr GetImplTypeCustData68@CT
    GetImplTypeCustData GetImplTypeCustData68@MP ?

 GetDocumentation268@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
		  lcid: LCID,
       pbstrHelpString: ptr BSTR,
  pdwHelpStringContext: ptr DWORD,
    pbstrHelpStringDll: ptr BSTR

 GetDocumentation268@MP typedef ptr GetDocumentation268@CT
      GetDocumentation2 GetDocumentation268@MP ?

    GetAllCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	     pCustData: ptr CUSTDATA

    GetAllCustData68@MP typedef ptr GetAllCustData68@CT
	 GetAllCustData GetAllCustData68@MP ?

GetAllFuncCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	     pCustData: ptr CUSTDATA

GetAllFuncCustData68@MP typedef ptr GetAllFuncCustData68@CT
     GetAllFuncCustData GetAllFuncCustData68@MP ?

GetAllParamCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
	     indexFunc: UINT,
	    indexParam: UINT,
	     pCustData: ptr CUSTDATA

GetAllParamCustData68@MP typedef ptr GetAllParamCustData68@CT
    GetAllParamCustData GetAllParamCustData68@MP ?

 GetAllVarCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	     pCustData: ptr CUSTDATA

 GetAllVarCustData68@MP typedef ptr GetAllVarCustData68@CT
      GetAllVarCustData GetAllVarCustData68@MP ?

GetAllImplTypeCustData68@CT typedef proto \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	     pCustData: ptr CUSTDATA

GetAllImplTypeCustData68@MP typedef ptr GetAllImplTypeCustData68@CT
 GetAllImplTypeCustData GetAllImplTypeCustData68@MP ?

	END_INTERFACE

ITypeInfo2Vtbl		ENDS

LPITypeInfo2Vtbl	typedef ptr ITypeInfo2Vtbl
ITypeInfo2		STRUC
lpVtbl			LPITypeInfo2Vtbl ?
ITypeInfo2		ENDS






;HRESULT
ITypeInfo2_GetTypeKind_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
	     pTypeKind: ptr TYPEKIND



;void
ITypeInfo2_GetTypeKind_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetTypeFlags_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
	    pTypeFlags: ptr ULONG



;void
ITypeInfo2_GetTypeFlags_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetFuncIndexOfMemId_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
	    pFuncIndex: ptr UINT



;void
ITypeInfo2_GetFuncIndexOfMemId_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetVarIndexOfMemId_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
	     pVarIndex: ptr UINT



;void
ITypeInfo2_GetVarIndexOfMemId_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ITypeInfo2_GetCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetFuncCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ITypeInfo2_GetFuncCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetParamCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
	     indexFunc: UINT,
	    indexParam: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ITypeInfo2_GetParamCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetVarCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ITypeInfo2_GetVarCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetImplTypeCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ITypeInfo2_GetImplTypeCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_RemoteGetDocumentation2_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
		  lcid: LCID,
	   refPtrFlags: DWORD,
       pbstrHelpString: ptr BSTR,
  pdwHelpStringContext: ptr DWORD,
    pbstrHelpStringDll: ptr BSTR



;void
ITypeInfo2_RemoteGetDocumentation2_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetAllCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
	     pCustData: ptr CUSTDATA



;void
ITypeInfo2_GetAllCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetAllFuncCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	     pCustData: ptr CUSTDATA



;void
ITypeInfo2_GetAllFuncCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetAllParamCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
	     indexFunc: UINT,
	    indexParam: UINT,
	     pCustData: ptr CUSTDATA



;void
ITypeInfo2_GetAllParamCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetAllVarCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	     pCustData: ptr CUSTDATA



;void
ITypeInfo2_GetAllVarCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeInfo2_GetAllImplTypeCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 index: UINT,
	     pCustData: ptr CUSTDATA



;void
ITypeInfo2_GetAllImplTypeCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ITypeLib_INTERFACE_DEFINED__
__ITypeLib_INTERFACE_DEFINED__ equ 1



SYSKIND			typedef SDWORD
SYS_WIN16		equ 0
SYS_WIN32		equ SYS_WIN16 + 1
SYS_MAC			equ SYS_WIN32 + 1

;tagLIBFLAGS		typedef SDWORD
LIBFLAG_FRESTRICTED	equ 0x1
LIBFLAG_FCONTROL	equ 0x2
LIBFLAG_FHIDDEN		equ 0x4
LIBFLAG_FHASDISKIMAGE	equ 0x8

LPTYPELIB		typedef ptr ITypeLib

TLIBATTR		STRUC
guid			GUID <>
lcid			LCID ?
syskind			SYSKIND ?
wMajorVerNum		dw ?
wMinorVerNum		dw ?
wLibFlags		dw ?
TLIBATTR		ENDS

LPTLIBATTR		typedef ptr TLIBATTR


externdef		IID_ITypeLib:IID


ITypeLibVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface69@CT typedef proto \
		 pThis: ptr ITypeLib,
		  riid: REFIID

    QueryInterface69@MP typedef ptr QueryInterface69@CT
	 QueryInterface QueryInterface69@MP ?

	    AddRef69@CT typedef proto \
		 pThis: ptr ITypeLib

	    AddRef69@MP typedef ptr AddRef69@CT
		 AddRef AddRef69@MP ?

	   Release69@CT typedef proto \
		 pThis: ptr ITypeLib

	   Release69@MP typedef ptr Release69@CT
		Release Release69@MP ?

  GetTypeInfoCount69@CT typedef proto \
		 pThis: ptr ITypeLib

  GetTypeInfoCount69@MP typedef ptr GetTypeInfoCount69@CT
       GetTypeInfoCount GetTypeInfoCount69@MP ?

       GetTypeInfo69@CT typedef proto \
		 pThis: ptr ITypeLib,
		 index: UINT,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo69@MP typedef ptr GetTypeInfo69@CT
	    GetTypeInfo GetTypeInfo69@MP ?

   GetTypeInfoType69@CT typedef proto \
		 pThis: ptr ITypeLib,
		 index: UINT,
		pTKind: ptr TYPEKIND

   GetTypeInfoType69@MP typedef ptr GetTypeInfoType69@CT
	GetTypeInfoType GetTypeInfoType69@MP ?

 GetTypeInfoOfGuid69@CT typedef proto \
		 pThis: ptr ITypeLib,
		  guid: REFGUID,
	       ppTinfo: ptr ITypeInfo

 GetTypeInfoOfGuid69@MP typedef ptr GetTypeInfoOfGuid69@CT
      GetTypeInfoOfGuid GetTypeInfoOfGuid69@MP ?

	GetLibAttr69@CT typedef proto \
		 pThis: ptr ITypeLib,
	    ppTLibAttr: ptr TLIBATTR

	GetLibAttr69@MP typedef ptr GetLibAttr69@CT
	     GetLibAttr GetLibAttr69@MP ?

       GetTypeComp69@CT typedef proto \
		 pThis: ptr ITypeLib,
	       ppTComp: ptr ITypeComp

       GetTypeComp69@MP typedef ptr GetTypeComp69@CT
	    GetTypeComp GetTypeComp69@MP ?

  GetDocumentation69@CT typedef proto \
		 pThis: ptr ITypeLib,
		 index: SINT,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR

  GetDocumentation69@MP typedef ptr GetDocumentation69@CT
       GetDocumentation GetDocumentation69@MP ?

	    IsName69@CT typedef proto \
		 pThis: ptr ITypeLib,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
		pfName: ptr BOOL

	    IsName69@MP typedef ptr IsName69@CT
		 IsName IsName69@MP ?

	  FindName69@CT typedef proto \
		 pThis: ptr ITypeLib,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo,
	       rgMemId: ptr MEMBERID,
	       pcFound: ptr USHORT

	  FindName69@MP typedef ptr FindName69@CT
	       FindName FindName69@MP ?

   ReleaseTLibAttr69@CT typedef proto \
		 pThis: ptr ITypeLib,
	     pTLibAttr: ptr TLIBATTR

   ReleaseTLibAttr69@MP typedef ptr ReleaseTLibAttr69@CT
	ReleaseTLibAttr ReleaseTLibAttr69@MP ?

	END_INTERFACE

ITypeLibVtbl		ENDS

LPITypeLibVtbl		typedef ptr ITypeLibVtbl
ITypeLib		STRUC
lpVtbl			LPITypeLibVtbl ?
ITypeLib		ENDS






;HRESULT
ITypeLib_RemoteGetTypeInfoCount_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	       pcTInfo: ptr UINT



;void
ITypeLib_RemoteGetTypeInfoCount_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_GetTypeInfo_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
		 index: UINT,
	       ppTInfo: ptr ITypeInfo



;void
ITypeLib_GetTypeInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_GetTypeInfoType_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
		 index: UINT,
		pTKind: ptr TYPEKIND



;void
ITypeLib_GetTypeInfoType_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_GetTypeInfoOfGuid_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
		  guid: REFGUID,
	       ppTinfo: ptr ITypeInfo



;void
ITypeLib_GetTypeInfoOfGuid_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_RemoteGetLibAttr_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	    ppTLibAttr: ptr LPTLIBATTR,
		pDummy: ptr CLEANLOCALSTORAGE



;void
ITypeLib_RemoteGetLibAttr_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_GetTypeComp_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	       ppTComp: ptr ITypeComp



;void
ITypeLib_GetTypeComp_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_RemoteGetDocumentation_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
		 index: SINT,
	   refPtrFlags: DWORD,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR



;void
ITypeLib_RemoteGetDocumentation_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_RemoteIsName_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
		pfName: ptr BOOL,
	  pBstrLibName: ptr BSTR



;void
ITypeLib_RemoteIsName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_RemoteFindName_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo,
	       rgMemId: ptr MEMBERID,
	       pcFound: ptr USHORT,
	  pBstrLibName: ptr BSTR



;void
ITypeLib_RemoteFindName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib_LocalReleaseTLibAttr_Proxy proto WINAPI \
		 pThis: ptr ITypeLib



;void
ITypeLib_LocalReleaseTLibAttr_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ITypeLib2_INTERFACE_DEFINED__
__ITypeLib2_INTERFACE_DEFINED__ equ 1



LPTYPELIB2		typedef ptr ITypeLib2


externdef		IID_ITypeLib2:IID


ITypeLib2Vtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface70@CT typedef proto \
		 pThis: ptr ITypeLib2,
		  riid: REFIID

    QueryInterface70@MP typedef ptr QueryInterface70@CT
	 QueryInterface QueryInterface70@MP ?

	    AddRef70@CT typedef proto \
		 pThis: ptr ITypeLib2

	    AddRef70@MP typedef ptr AddRef70@CT
		 AddRef AddRef70@MP ?

	   Release70@CT typedef proto \
		 pThis: ptr ITypeLib2

	   Release70@MP typedef ptr Release70@CT
		Release Release70@MP ?

  GetTypeInfoCount70@CT typedef proto \
		 pThis: ptr ITypeLib2

  GetTypeInfoCount70@MP typedef ptr GetTypeInfoCount70@CT
       GetTypeInfoCount GetTypeInfoCount70@MP ?

       GetTypeInfo70@CT typedef proto \
		 pThis: ptr ITypeLib2,
		 index: UINT,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo70@MP typedef ptr GetTypeInfo70@CT
	    GetTypeInfo GetTypeInfo70@MP ?

   GetTypeInfoType70@CT typedef proto \
		 pThis: ptr ITypeLib2,
		 index: UINT,
		pTKind: ptr TYPEKIND

   GetTypeInfoType70@MP typedef ptr GetTypeInfoType70@CT
	GetTypeInfoType GetTypeInfoType70@MP ?

 GetTypeInfoOfGuid70@CT typedef proto \
		 pThis: ptr ITypeLib2,
		  guid: REFGUID,
	       ppTinfo: ptr ITypeInfo

 GetTypeInfoOfGuid70@MP typedef ptr GetTypeInfoOfGuid70@CT
      GetTypeInfoOfGuid GetTypeInfoOfGuid70@MP ?

	GetLibAttr70@CT typedef proto \
		 pThis: ptr ITypeLib2,
	    ppTLibAttr: ptr TLIBATTR

	GetLibAttr70@MP typedef ptr GetLibAttr70@CT
	     GetLibAttr GetLibAttr70@MP ?

       GetTypeComp70@CT typedef proto \
		 pThis: ptr ITypeLib2,
	       ppTComp: ptr ITypeComp

       GetTypeComp70@MP typedef ptr GetTypeComp70@CT
	    GetTypeComp GetTypeComp70@MP ?

  GetDocumentation70@CT typedef proto \
		 pThis: ptr ITypeLib2,
		 index: SINT,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR

  GetDocumentation70@MP typedef ptr GetDocumentation70@CT
       GetDocumentation GetDocumentation70@MP ?

	    IsName70@CT typedef proto \
		 pThis: ptr ITypeLib2,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
		pfName: ptr BOOL

	    IsName70@MP typedef ptr IsName70@CT
		 IsName IsName70@MP ?

	  FindName70@CT typedef proto \
		 pThis: ptr ITypeLib2,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo,
	       rgMemId: ptr MEMBERID,
	       pcFound: ptr USHORT

	  FindName70@MP typedef ptr FindName70@CT
	       FindName FindName70@MP ?

   ReleaseTLibAttr70@CT typedef proto \
		 pThis: ptr ITypeLib2,
	     pTLibAttr: ptr TLIBATTR

   ReleaseTLibAttr70@MP typedef ptr ReleaseTLibAttr70@CT
	ReleaseTLibAttr ReleaseTLibAttr70@MP ?

       GetCustData70@CT typedef proto \
		 pThis: ptr ITypeLib2,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT

       GetCustData70@MP typedef ptr GetCustData70@CT
	    GetCustData GetCustData70@MP ?

  GetLibStatistics70@CT typedef proto \
		 pThis: ptr ITypeLib2,
	 pcUniqueNames: ptr ULONG,
       pcchUniqueNames: ptr ULONG

  GetLibStatistics70@MP typedef ptr GetLibStatistics70@CT
       GetLibStatistics GetLibStatistics70@MP ?

 GetDocumentation270@CT typedef proto \
		 pThis: ptr ITypeLib2,
		 index: SINT,
		  lcid: LCID,
       pbstrHelpString: ptr BSTR,
  pdwHelpStringContext: ptr DWORD,
    pbstrHelpStringDll: ptr BSTR

 GetDocumentation270@MP typedef ptr GetDocumentation270@CT
      GetDocumentation2 GetDocumentation270@MP ?

    GetAllCustData70@CT typedef proto \
		 pThis: ptr ITypeLib2,
	     pCustData: ptr CUSTDATA

    GetAllCustData70@MP typedef ptr GetAllCustData70@CT
	 GetAllCustData GetAllCustData70@MP ?

	END_INTERFACE

ITypeLib2Vtbl		ENDS

LPITypeLib2Vtbl		typedef ptr ITypeLib2Vtbl
ITypeLib2		STRUC
lpVtbl			LPITypeLib2Vtbl ?
ITypeLib2		ENDS






;HRESULT
ITypeLib2_GetCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeLib2,
		  guid: REFGUID,
	       pVarVal: ptr VARIANT



;void
ITypeLib2_GetCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib2_RemoteGetLibStatistics_Proxy proto WINAPI \
		 pThis: ptr ITypeLib2,
	 pcUniqueNames: ptr ULONG,
       pcchUniqueNames: ptr ULONG



;void
ITypeLib2_RemoteGetLibStatistics_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib2_RemoteGetDocumentation2_Proxy proto WINAPI \
		 pThis: ptr ITypeLib2,
		 index: SINT,
		  lcid: LCID,
	   refPtrFlags: DWORD,
       pbstrHelpString: ptr BSTR,
  pdwHelpStringContext: ptr DWORD,
    pbstrHelpStringDll: ptr BSTR



;void
ITypeLib2_RemoteGetDocumentation2_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeLib2_GetAllCustData_Proxy proto WINAPI \
		 pThis: ptr ITypeLib2,
	     pCustData: ptr CUSTDATA



;void
ITypeLib2_GetAllCustData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ITypeChangeEvents_INTERFACE_DEFINED__
__ITypeChangeEvents_INTERFACE_DEFINED__ equ 1



LPTYPECHANGEEVENTS	typedef ptr ITypeChangeEvents

CHANGEKIND		typedef SDWORD
CHANGEKIND_ADDMEMBER	equ 0
CHANGEKIND_DELETEMEMBER equ CHANGEKIND_ADDMEMBER + 1
CHANGEKIND_SETNAMES	equ CHANGEKIND_DELETEMEMBER + 1
CHANGEKIND_SETDOCUMENTATION equ CHANGEKIND_SETNAMES + 1
CHANGEKIND_GENERAL	equ CHANGEKIND_SETDOCUMENTATION + 1
CHANGEKIND_INVALIDATE	equ CHANGEKIND_GENERAL + 1
CHANGEKIND_CHANGEFAILED equ CHANGEKIND_INVALIDATE + 1
CHANGEKIND_MAX		equ CHANGEKIND_CHANGEFAILED + 1


externdef		IID_ITypeChangeEvents:IID


ITypeChangeEventsVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface71@CT typedef proto \
		 pThis: ptr ITypeChangeEvents,
		  riid: REFIID

    QueryInterface71@MP typedef ptr QueryInterface71@CT
	 QueryInterface QueryInterface71@MP ?

	    AddRef71@CT typedef proto \
		 pThis: ptr ITypeChangeEvents

	    AddRef71@MP typedef ptr AddRef71@CT
		 AddRef AddRef71@MP ?

	   Release71@CT typedef proto \
		 pThis: ptr ITypeChangeEvents

	   Release71@MP typedef ptr Release71@CT
		Release Release71@MP ?

 RequestTypeChange71@CT typedef proto \
		 pThis: ptr ITypeChangeEvents,
	    changeKind: CHANGEKIND,
	  pTInfoBefore: ptr ITypeInfo,
	      pStrName: LPOLESTR,
	      pfCancel: ptr SINT

 RequestTypeChange71@MP typedef ptr RequestTypeChange71@CT
      RequestTypeChange RequestTypeChange71@MP ?

   AfterTypeChange71@CT typedef proto \
		 pThis: ptr ITypeChangeEvents,
	    changeKind: CHANGEKIND,
	   pTInfoAfter: ptr ITypeInfo,
	      pStrName: LPOLESTR

   AfterTypeChange71@MP typedef ptr AfterTypeChange71@CT
	AfterTypeChange AfterTypeChange71@MP ?

	END_INTERFACE

ITypeChangeEventsVtbl	ENDS

LPITypeChangeEventsVtbl typedef ptr ITypeChangeEventsVtbl
ITypeChangeEvents	STRUC
lpVtbl			LPITypeChangeEventsVtbl ?
ITypeChangeEvents	ENDS






;HRESULT
ITypeChangeEvents_RequestTypeChange_Proxy proto WINAPI \
		 pThis: ptr ITypeChangeEvents,
	    changeKind: CHANGEKIND,
	  pTInfoBefore: ptr ITypeInfo,
	      pStrName: LPOLESTR,
	      pfCancel: ptr SINT



;void
ITypeChangeEvents_RequestTypeChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeChangeEvents_AfterTypeChange_Proxy proto WINAPI \
		 pThis: ptr ITypeChangeEvents,
	    changeKind: CHANGEKIND,
	   pTInfoAfter: ptr ITypeInfo,
	      pStrName: LPOLESTR



;void
ITypeChangeEvents_AfterTypeChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IErrorInfo_INTERFACE_DEFINED__
__IErrorInfo_INTERFACE_DEFINED__ equ 1



LPERRORINFO		typedef ptr IErrorInfo


externdef		IID_IErrorInfo:IID


IErrorInfoVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface72@CT typedef proto \
		 pThis: ptr IErrorInfo,
		  riid: REFIID

    QueryInterface72@MP typedef ptr QueryInterface72@CT
	 QueryInterface QueryInterface72@MP ?

	    AddRef72@CT typedef proto \
		 pThis: ptr IErrorInfo

	    AddRef72@MP typedef ptr AddRef72@CT
		 AddRef AddRef72@MP ?

	   Release72@CT typedef proto \
		 pThis: ptr IErrorInfo

	   Release72@MP typedef ptr Release72@CT
		Release Release72@MP ?

	   GetGUID72@CT typedef proto \
		 pThis: ptr IErrorInfo,
		 pGUID: ptr GUID

	   GetGUID72@MP typedef ptr GetGUID72@CT
		GetGUID GetGUID72@MP ?

	 GetSource72@CT typedef proto \
		 pThis: ptr IErrorInfo,
	   pBstrSource: ptr BSTR

	 GetSource72@MP typedef ptr GetSource72@CT
	      GetSource GetSource72@MP ?

    GetDescription72@CT typedef proto \
		 pThis: ptr IErrorInfo,
      pBstrDescription: ptr BSTR

    GetDescription72@MP typedef ptr GetDescription72@CT
	 GetDescription GetDescription72@MP ?

       GetHelpFile72@CT typedef proto \
		 pThis: ptr IErrorInfo,
	 pBstrHelpFile: ptr BSTR

       GetHelpFile72@MP typedef ptr GetHelpFile72@CT
	    GetHelpFile GetHelpFile72@MP ?

    GetHelpContext72@CT typedef proto \
		 pThis: ptr IErrorInfo,
	pdwHelpContext: ptr DWORD

    GetHelpContext72@MP typedef ptr GetHelpContext72@CT
	 GetHelpContext GetHelpContext72@MP ?

	END_INTERFACE

IErrorInfoVtbl		ENDS

LPIErrorInfoVtbl	typedef ptr IErrorInfoVtbl
IErrorInfo		STRUC
lpVtbl			LPIErrorInfoVtbl ?
IErrorInfo		ENDS






;HRESULT
IErrorInfo_GetGUID_Proxy proto WINAPI \
		 pThis: ptr IErrorInfo,
		 pGUID: ptr GUID



;void
IErrorInfo_GetGUID_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IErrorInfo_GetSource_Proxy proto WINAPI \
		 pThis: ptr IErrorInfo,
	   pBstrSource: ptr BSTR



;void
IErrorInfo_GetSource_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IErrorInfo_GetDescription_Proxy proto WINAPI \
		 pThis: ptr IErrorInfo,
      pBstrDescription: ptr BSTR



;void
IErrorInfo_GetDescription_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IErrorInfo_GetHelpFile_Proxy proto WINAPI \
		 pThis: ptr IErrorInfo,
	 pBstrHelpFile: ptr BSTR



;void
IErrorInfo_GetHelpFile_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IErrorInfo_GetHelpContext_Proxy proto WINAPI \
		 pThis: ptr IErrorInfo,
	pdwHelpContext: ptr DWORD



;void
IErrorInfo_GetHelpContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ICreateErrorInfo_INTERFACE_DEFINED__
__ICreateErrorInfo_INTERFACE_DEFINED__ equ 1



LPCREATEERRORINFO	typedef ptr ICreateErrorInfo


externdef		IID_ICreateErrorInfo:IID


ICreateErrorInfoVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface73@CT typedef proto \
		 pThis: ptr ICreateErrorInfo,
		  riid: REFIID

    QueryInterface73@MP typedef ptr QueryInterface73@CT
	 QueryInterface QueryInterface73@MP ?

	    AddRef73@CT typedef proto \
		 pThis: ptr ICreateErrorInfo

	    AddRef73@MP typedef ptr AddRef73@CT
		 AddRef AddRef73@MP ?

	   Release73@CT typedef proto \
		 pThis: ptr ICreateErrorInfo

	   Release73@MP typedef ptr Release73@CT
		Release Release73@MP ?

	   SetGUID73@CT typedef proto \
		 pThis: ptr ICreateErrorInfo,
		 rguid: REFGUID

	   SetGUID73@MP typedef ptr SetGUID73@CT
		SetGUID SetGUID73@MP ?

	 SetSource73@CT typedef proto \
		 pThis: ptr ICreateErrorInfo,
	      szSource: LPOLESTR

	 SetSource73@MP typedef ptr SetSource73@CT
	      SetSource SetSource73@MP ?

    SetDescription73@CT typedef proto \
		 pThis: ptr ICreateErrorInfo,
	 szDescription: LPOLESTR

    SetDescription73@MP typedef ptr SetDescription73@CT
	 SetDescription SetDescription73@MP ?

       SetHelpFile73@CT typedef proto \
		 pThis: ptr ICreateErrorInfo,
	    szHelpFile: LPOLESTR

       SetHelpFile73@MP typedef ptr SetHelpFile73@CT
	    SetHelpFile SetHelpFile73@MP ?

    SetHelpContext73@CT typedef proto \
		 pThis: ptr ICreateErrorInfo,
	 dwHelpContext: DWORD

    SetHelpContext73@MP typedef ptr SetHelpContext73@CT
	 SetHelpContext SetHelpContext73@MP ?

	END_INTERFACE

ICreateErrorInfoVtbl	ENDS

LPICreateErrorInfoVtbl	typedef ptr ICreateErrorInfoVtbl
ICreateErrorInfo	STRUC
lpVtbl			LPICreateErrorInfoVtbl ?
ICreateErrorInfo	ENDS






;HRESULT
ICreateErrorInfo_SetGUID_Proxy proto WINAPI \
		 pThis: ptr ICreateErrorInfo,
		 rguid: REFGUID



;void
ICreateErrorInfo_SetGUID_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateErrorInfo_SetSource_Proxy proto WINAPI \
		 pThis: ptr ICreateErrorInfo,
	      szSource: LPOLESTR



;void
ICreateErrorInfo_SetSource_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateErrorInfo_SetDescription_Proxy proto WINAPI \
		 pThis: ptr ICreateErrorInfo,
	 szDescription: LPOLESTR



;void
ICreateErrorInfo_SetDescription_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateErrorInfo_SetHelpFile_Proxy proto WINAPI \
		 pThis: ptr ICreateErrorInfo,
	    szHelpFile: LPOLESTR



;void
ICreateErrorInfo_SetHelpFile_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ICreateErrorInfo_SetHelpContext_Proxy proto WINAPI \
		 pThis: ptr ICreateErrorInfo,
	 dwHelpContext: DWORD



;void
ICreateErrorInfo_SetHelpContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ISupportErrorInfo_INTERFACE_DEFINED__
__ISupportErrorInfo_INTERFACE_DEFINED__ equ 1



LPSUPPORTERRORINFO	typedef ptr ISupportErrorInfo


externdef		IID_ISupportErrorInfo:IID


ISupportErrorInfoVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface74@CT typedef proto \
		 pThis: ptr ISupportErrorInfo,
		  riid: REFIID

    QueryInterface74@MP typedef ptr QueryInterface74@CT
	 QueryInterface QueryInterface74@MP ?

	    AddRef74@CT typedef proto \
		 pThis: ptr ISupportErrorInfo

	    AddRef74@MP typedef ptr AddRef74@CT
		 AddRef AddRef74@MP ?

	   Release74@CT typedef proto \
		 pThis: ptr ISupportErrorInfo

	   Release74@MP typedef ptr Release74@CT
		Release Release74@MP ?

InterfaceSupportsErrorInfo74@CT typedef proto \
		 pThis: ptr ISupportErrorInfo,
		  riid: REFIID

InterfaceSupportsErrorInfo74@MP typedef ptr InterfaceSupportsErrorInfo74@CT
InterfaceSupportsErrorInfo InterfaceSupportsErrorInfo74@MP ?

	END_INTERFACE

ISupportErrorInfoVtbl	ENDS

LPISupportErrorInfoVtbl typedef ptr ISupportErrorInfoVtbl
ISupportErrorInfo	STRUC
lpVtbl			LPISupportErrorInfoVtbl ?
ISupportErrorInfo	ENDS






;HRESULT
ISupportErrorInfo_InterfaceSupportsErrorInfo_Proxy proto WINAPI \
		 pThis: ptr ISupportErrorInfo,
		  riid: REFIID



;void
ISupportErrorInfo_InterfaceSupportsErrorInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ITypeFactory_INTERFACE_DEFINED__
__ITypeFactory_INTERFACE_DEFINED__ equ 1




externdef		IID_ITypeFactory:IID


ITypeFactoryVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface75@CT typedef proto \
		 pThis: ptr ITypeFactory,
		  riid: REFIID

    QueryInterface75@MP typedef ptr QueryInterface75@CT
	 QueryInterface QueryInterface75@MP ?

	    AddRef75@CT typedef proto \
		 pThis: ptr ITypeFactory

	    AddRef75@MP typedef ptr AddRef75@CT
		 AddRef AddRef75@MP ?

	   Release75@CT typedef proto \
		 pThis: ptr ITypeFactory

	   Release75@MP typedef ptr Release75@CT
		Release Release75@MP ?

CreateFromTypeInfo75@CT typedef proto \
		 pThis: ptr ITypeFactory,
	     pTypeInfo: ptr ITypeInfo,
		  riid: REFIID,
		   ppv: ptr IUnknown

CreateFromTypeInfo75@MP typedef ptr CreateFromTypeInfo75@CT
     CreateFromTypeInfo CreateFromTypeInfo75@MP ?

	END_INTERFACE

ITypeFactoryVtbl	ENDS

LPITypeFactoryVtbl	typedef ptr ITypeFactoryVtbl
ITypeFactory		STRUC
lpVtbl			LPITypeFactoryVtbl ?
ITypeFactory		ENDS






;HRESULT
ITypeFactory_CreateFromTypeInfo_Proxy proto WINAPI \
		 pThis: ptr ITypeFactory,
	     pTypeInfo: ptr ITypeInfo,
		  riid: REFIID,
		   ppv: ptr IUnknown



;void
ITypeFactory_CreateFromTypeInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __ITypeMarshal_INTERFACE_DEFINED__
__ITypeMarshal_INTERFACE_DEFINED__ equ 1




externdef		IID_ITypeMarshal:IID


ITypeMarshalVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface76@CT typedef proto \
		 pThis: ptr ITypeMarshal,
		  riid: REFIID

    QueryInterface76@MP typedef ptr QueryInterface76@CT
	 QueryInterface QueryInterface76@MP ?

	    AddRef76@CT typedef proto \
		 pThis: ptr ITypeMarshal

	    AddRef76@MP typedef ptr AddRef76@CT
		 AddRef AddRef76@MP ?

	   Release76@CT typedef proto \
		 pThis: ptr ITypeMarshal

	   Release76@MP typedef ptr Release76@CT
		Release Release76@MP ?

	     _Size76@CT typedef proto \
		 pThis: ptr ITypeMarshal,
		pvType: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
		 pSize: ptr ULONG

	     _Size76@MP typedef ptr _Size76@CT
		  _Size _Size76@MP ?

	   Marshal76@CT typedef proto \
		 pThis: ptr ITypeMarshal,
		pvType: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	cbBufferLength: ULONG,
	       pBuffer: ptr BYTE,
	    pcbWritten: ptr ULONG

	   Marshal76@MP typedef ptr Marshal76@CT
		Marshal Marshal76@MP ?

	 Unmarshal76@CT typedef proto \
		 pThis: ptr ITypeMarshal,
		pvType: PVOID,
	       dwFlags: DWORD,
	cbBufferLength: ULONG,
	       pBuffer: ptr BYTE,
	       pcbRead: ptr ULONG

	 Unmarshal76@MP typedef ptr Unmarshal76@CT
	      Unmarshal Unmarshal76@MP ?

	      Free76@CT typedef proto \
		 pThis: ptr ITypeMarshal,
		pvType: PVOID

	      Free76@MP typedef ptr Free76@CT
		   Free Free76@MP ?

	END_INTERFACE

ITypeMarshalVtbl	ENDS

LPITypeMarshalVtbl	typedef ptr ITypeMarshalVtbl
ITypeMarshal		STRUC
lpVtbl			LPITypeMarshalVtbl ?
ITypeMarshal		ENDS






;HRESULT
ITypeMarshal_Size_Proxy proto WINAPI \
		 pThis: ptr ITypeMarshal,
		pvType: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
		 pSize: ptr ULONG



;void
ITypeMarshal_Size_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeMarshal_Marshal_Proxy proto WINAPI \
		 pThis: ptr ITypeMarshal,
		pvType: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	cbBufferLength: ULONG,
	       pBuffer: ptr BYTE,
	    pcbWritten: ptr ULONG



;void
ITypeMarshal_Marshal_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeMarshal_Unmarshal_Proxy proto WINAPI \
		 pThis: ptr ITypeMarshal,
		pvType: PVOID,
	       dwFlags: DWORD,
	cbBufferLength: ULONG,
	       pBuffer: ptr BYTE,
	       pcbRead: ptr ULONG



;void
ITypeMarshal_Unmarshal_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
ITypeMarshal_Free_Proxy proto WINAPI \
		 pThis: ptr ITypeMarshal,
		pvType: PVOID



;void
ITypeMarshal_Free_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IRecordInfo_INTERFACE_DEFINED__
__IRecordInfo_INTERFACE_DEFINED__ equ 1



LPRECORDINFO		typedef ptr IRecordInfo


externdef		IID_IRecordInfo:IID


IRecordInfoVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface77@CT typedef proto \
		 pThis: ptr IRecordInfo,
		  riid: REFIID

    QueryInterface77@MP typedef ptr QueryInterface77@CT
	 QueryInterface QueryInterface77@MP ?

	    AddRef77@CT typedef proto \
		 pThis: ptr IRecordInfo

	    AddRef77@MP typedef ptr AddRef77@CT
		 AddRef AddRef77@MP ?

	   Release77@CT typedef proto \
		 pThis: ptr IRecordInfo

	   Release77@MP typedef ptr Release77@CT
		Release Release77@MP ?

	RecordInit77@CT typedef proto \
		 pThis: ptr IRecordInfo,
		 pvNew: PVOID

	RecordInit77@MP typedef ptr RecordInit77@CT
	     RecordInit RecordInit77@MP ?

       RecordClear77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	    pvExisting: PVOID

       RecordClear77@MP typedef ptr RecordClear77@CT
	    RecordClear RecordClear77@MP ?

	RecordCopy77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	    pvExisting: PVOID,
		 pvNew: PVOID

	RecordCopy77@MP typedef ptr RecordCopy77@CT
	     RecordCopy RecordCopy77@MP ?

	   GetGuid77@CT typedef proto \
		 pThis: ptr IRecordInfo,
		 pguid: ptr GUID

	   GetGuid77@MP typedef ptr GetGuid77@CT
		GetGuid GetGuid77@MP ?

	   GetName77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	     pbstrName: ptr BSTR

	   GetName77@MP typedef ptr GetName77@CT
		GetName GetName77@MP ?

	   GetSize77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	       pcbSize: ptr ULONG

	   GetSize77@MP typedef ptr GetSize77@CT
		GetSize GetSize77@MP ?

       GetTypeInfo77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	    ppTypeInfo: ptr ITypeInfo

       GetTypeInfo77@MP typedef ptr GetTypeInfo77@CT
	    GetTypeInfo GetTypeInfo77@MP ?

	  GetField77@CT typedef proto \
		 pThis: ptr IRecordInfo,
		pvData: PVOID,
	   szFieldName: LPCOLESTR,
	     pvarField: ptr VARIANT

	  GetField77@MP typedef ptr GetField77@CT
	       GetField GetField77@MP ?

    GetFieldNoCopy77@CT typedef proto \
		 pThis: ptr IRecordInfo,
		pvData: PVOID,
	   szFieldName: LPCOLESTR,
	     pvarField: ptr VARIANT,
	 ppvDataCArray: ptr PVOID

    GetFieldNoCopy77@MP typedef ptr GetFieldNoCopy77@CT
	 GetFieldNoCopy GetFieldNoCopy77@MP ?

	  PutField77@CT typedef proto \
		 pThis: ptr IRecordInfo,
		wFlags: ULONG,
		pvData: PVOID,
	   szFieldName: LPCOLESTR,
	     pvarField: ptr VARIANT

	  PutField77@MP typedef ptr PutField77@CT
	       PutField PutField77@MP ?

    PutFieldNoCopy77@CT typedef proto \
		 pThis: ptr IRecordInfo,
		wFlags: ULONG,
		pvData: PVOID,
	   szFieldName: LPCOLESTR,
	     pvarField: ptr VARIANT

    PutFieldNoCopy77@MP typedef ptr PutFieldNoCopy77@CT
	 PutFieldNoCopy PutFieldNoCopy77@MP ?

     GetFieldNames77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	       pcNames: ptr ULONG,
	   rgBstrNames: ptr BSTR

     GetFieldNames77@MP typedef ptr GetFieldNames77@CT
	  GetFieldNames GetFieldNames77@MP ?

    IsMatchingType77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	   pRecordInfo: ptr IRecordInfo

    IsMatchingType77@MP typedef ptr IsMatchingType77@CT
	 IsMatchingType IsMatchingType77@MP ?

      RecordCreate77@CT typedef proto \
		 pThis: ptr IRecordInfo

      RecordCreate77@MP typedef ptr RecordCreate77@CT
	   RecordCreate RecordCreate77@MP ?

  RecordCreateCopy77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	      pvSource: PVOID,
	       ppvDest: ptr PVOID

  RecordCreateCopy77@MP typedef ptr RecordCreateCopy77@CT
       RecordCreateCopy RecordCreateCopy77@MP ?

     RecordDestroy77@CT typedef proto \
		 pThis: ptr IRecordInfo,
	      pvRecord: PVOID

     RecordDestroy77@MP typedef ptr RecordDestroy77@CT
	  RecordDestroy RecordDestroy77@MP ?

	END_INTERFACE

IRecordInfoVtbl		ENDS

LPIRecordInfoVtbl	typedef ptr IRecordInfoVtbl
IRecordInfo		STRUC
lpVtbl			LPIRecordInfoVtbl ?
IRecordInfo		ENDS






;HRESULT
IRecordInfo_RecordInit_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
		 pvNew: PVOID



;void
IRecordInfo_RecordInit_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_RecordClear_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	    pvExisting: PVOID



;void
IRecordInfo_RecordClear_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_RecordCopy_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	    pvExisting: PVOID,
		 pvNew: PVOID



;void
IRecordInfo_RecordCopy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_GetGuid_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
		 pguid: ptr GUID



;void
IRecordInfo_GetGuid_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_GetName_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	     pbstrName: ptr BSTR



;void
IRecordInfo_GetName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_GetSize_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	       pcbSize: ptr ULONG



;void
IRecordInfo_GetSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_GetTypeInfo_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	    ppTypeInfo: ptr ITypeInfo



;void
IRecordInfo_GetTypeInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_GetField_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
		pvData: PVOID,
	   szFieldName: LPCOLESTR,
	     pvarField: ptr VARIANT



;void
IRecordInfo_GetField_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_GetFieldNoCopy_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
		pvData: PVOID,
	   szFieldName: LPCOLESTR,
	     pvarField: ptr VARIANT,
	 ppvDataCArray: ptr PVOID



;void
IRecordInfo_GetFieldNoCopy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_PutField_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
		wFlags: ULONG,
		pvData: PVOID,
	   szFieldName: LPCOLESTR,
	     pvarField: ptr VARIANT



;void
IRecordInfo_PutField_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_PutFieldNoCopy_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
		wFlags: ULONG,
		pvData: PVOID,
	   szFieldName: LPCOLESTR,
	     pvarField: ptr VARIANT



;void
IRecordInfo_PutFieldNoCopy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_GetFieldNames_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	       pcNames: ptr ULONG,
	   rgBstrNames: ptr BSTR



;void
IRecordInfo_GetFieldNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;BOOL
IRecordInfo_IsMatchingType_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	   pRecordInfo: ptr IRecordInfo



;void
IRecordInfo_IsMatchingType_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;PVOID
IRecordInfo_RecordCreate_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo



;void
IRecordInfo_RecordCreate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_RecordCreateCopy_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	      pvSource: PVOID,
	       ppvDest: ptr PVOID



;void
IRecordInfo_RecordCreateCopy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IRecordInfo_RecordDestroy_Proxy proto WINAPI \
		 pThis: ptr IRecordInfo,
	      pvRecord: PVOID



;void
IRecordInfo_RecordDestroy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif	

if ( _MSC_VER GE 800 )
;pragma warning(default:4201) 
endif

externdef		__MIDL_itf_oaidl_0092_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_oaidl_0092_v0_0_s_ifspec:RPC_IF_HANDLE


;DWORD
BSTR_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr BSTR
;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR
;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR
;void
BSTR_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr BSTR

;DWORD
CLEANLOCALSTORAGE_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr CLEANLOCALSTORAGE

;LPBYTE
CLEANLOCALSTORAGE_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr CLEANLOCALSTORAGE

;LPBYTE
CLEANLOCALSTORAGE_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr CLEANLOCALSTORAGE

;void
CLEANLOCALSTORAGE_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr CLEANLOCALSTORAGE


;DWORD
VARIANT_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr VARIANT

;LPBYTE
VARIANT_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;LPBYTE
VARIANT_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr VARIANT


;HRESULT
IDispatch_Invoke_Proxy proto WINAPI \
		 pThis: ptr IDispatch,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT



;HRESULT
IDispatch_Invoke_Stub proto WINAPI \
		 pThis: ptr IDispatch,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
	       dwFlags: DWORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	       pArgErr: ptr UINT,
	       cVarRef: UINT,
	   rgVarRefIdx: ptr UINT,
	      rgVarRef: ptr VARIANTARG


;HRESULT
IEnumVARIANT_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumVARIANT,
		  celt: ULONG,
		 rgVar: ptr VARIANT,
	  pCeltFetched: ptr ULONG



;HRESULT
IEnumVARIANT_Next_Stub proto WINAPI \
		 pThis: ptr IEnumVARIANT,
		  celt: ULONG,
		 rgVar: ptr VARIANT,
	  pCeltFetched: ptr ULONG


;HRESULT
ITypeComp_Bind_Proxy proto WINAPI \
		 pThis: ptr ITypeComp,
		szName: LPOLESTR,
	      lHashVal: ULONG,
		wFlags: WORD,
	       ppTInfo: ptr ITypeInfo,
	     pDescKind: ptr DESCKIND,
	      pBindPtr: ptr BINDPTR



;HRESULT
ITypeComp_Bind_Stub proto WINAPI \
		 pThis: ptr ITypeComp,
		szName: LPOLESTR,
	      lHashVal: ULONG,
		wFlags: WORD,
	       ppTInfo: ptr ITypeInfo,
	     pDescKind: ptr DESCKIND,
	    ppFuncDesc: ptr LPFUNCDESC,
	     ppVarDesc: ptr LPVARDESC,
	    ppTypeComp: ptr ITypeComp,
		pDummy: ptr CLEANLOCALSTORAGE


;HRESULT
ITypeComp_BindType_Proxy proto WINAPI \
		 pThis: ptr ITypeComp,
		szName: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo,
	       ppTComp: ptr ITypeComp



;HRESULT
ITypeComp_BindType_Stub proto WINAPI \
		 pThis: ptr ITypeComp,
		szName: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo


;HRESULT
ITypeInfo_GetTypeAttr_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	    ppTypeAttr: ptr TYPEATTR



;HRESULT
ITypeInfo_GetTypeAttr_Stub proto WINAPI \
		 pThis: ptr ITypeInfo,
	    ppTypeAttr: ptr LPTYPEATTR,
		pDummy: ptr CLEANLOCALSTORAGE


;HRESULT
ITypeInfo_GetFuncDesc_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	    ppFuncDesc: ptr FUNCDESC



;HRESULT
ITypeInfo_GetFuncDesc_Stub proto WINAPI \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	    ppFuncDesc: ptr LPFUNCDESC,
		pDummy: ptr CLEANLOCALSTORAGE


;HRESULT
ITypeInfo_GetVarDesc_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	     ppVarDesc: ptr VARDESC



;HRESULT
ITypeInfo_GetVarDesc_Stub proto WINAPI \
		 pThis: ptr ITypeInfo,
		 index: UINT,
	     ppVarDesc: ptr LPVARDESC,
		pDummy: ptr CLEANLOCALSTORAGE


;HRESULT
ITypeInfo_GetNames_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	   rgBstrNames: ptr BSTR,
	     cMaxNames: UINT,
	       pcNames: ptr UINT



;HRESULT
ITypeInfo_GetNames_Stub proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	   rgBstrNames: ptr BSTR,
	     cMaxNames: UINT,
	       pcNames: ptr UINT


;HRESULT
ITypeInfo_GetIDsOfNames_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		pMemId: ptr MEMBERID



;HRESULT
ITypeInfo_GetIDsOfNames_Stub proto WINAPI \
		 pThis: ptr ITypeInfo


;HRESULT
ITypeInfo_Invoke_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	    pvInstance: PVOID,
		 memid: MEMBERID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT



;HRESULT
ITypeInfo_Invoke_Stub proto WINAPI \
		 pThis: ptr ITypeInfo


;HRESULT
ITypeInfo_GetDocumentation_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR



;HRESULT
ITypeInfo_GetDocumentation_Stub proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	   refPtrFlags: DWORD,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR


;HRESULT
ITypeInfo_GetDllEntry_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
	  pBstrDllName: ptr BSTR,
	     pBstrName: ptr BSTR,
	     pwOrdinal: ptr WORD



;HRESULT
ITypeInfo_GetDllEntry_Stub proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
	   refPtrFlags: DWORD,
	  pBstrDllName: ptr BSTR,
	     pBstrName: ptr BSTR,
	     pwOrdinal: ptr WORD


;HRESULT
ITypeInfo_AddressOfMember_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		 memid: MEMBERID,
	       invKind: INVOKEKIND,
		   ppv: ptr PVOID



;HRESULT
ITypeInfo_AddressOfMember_Stub proto WINAPI \
		 pThis: ptr ITypeInfo


;HRESULT
ITypeInfo_CreateInstance_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID,
		ppvObj: ptr PVOID



;HRESULT
ITypeInfo_CreateInstance_Stub proto WINAPI \
		 pThis: ptr ITypeInfo,
		  riid: REFIID,
		ppvObj: ptr IUnknown


;HRESULT
ITypeInfo_GetContainingTypeLib_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
		ppTLib: ptr ITypeLib,
		pIndex: ptr UINT



;HRESULT
ITypeInfo_GetContainingTypeLib_Stub proto WINAPI \
		 pThis: ptr ITypeInfo,
		ppTLib: ptr ITypeLib,
		pIndex: ptr UINT


;void
ITypeInfo_ReleaseTypeAttr_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	     pTypeAttr: ptr TYPEATTR



;HRESULT
ITypeInfo_ReleaseTypeAttr_Stub proto WINAPI \
		 pThis: ptr ITypeInfo


;void
ITypeInfo_ReleaseFuncDesc_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	     pFuncDesc: ptr FUNCDESC



;HRESULT
ITypeInfo_ReleaseFuncDesc_Stub proto WINAPI \
		 pThis: ptr ITypeInfo


;void
ITypeInfo_ReleaseVarDesc_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo,
	      pVarDesc: ptr VARDESC



;HRESULT
ITypeInfo_ReleaseVarDesc_Stub proto WINAPI \
		 pThis: ptr ITypeInfo


;HRESULT
ITypeInfo2_GetDocumentation2_Proxy proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
		  lcid: LCID,
       pbstrHelpString: ptr BSTR,
  pdwHelpStringContext: ptr DWORD,
    pbstrHelpStringDll: ptr BSTR



;HRESULT
ITypeInfo2_GetDocumentation2_Stub proto WINAPI \
		 pThis: ptr ITypeInfo2,
		 memid: MEMBERID,
		  lcid: LCID,
	   refPtrFlags: DWORD,
       pbstrHelpString: ptr BSTR,
  pdwHelpStringContext: ptr DWORD,
    pbstrHelpStringDll: ptr BSTR


;UINT
ITypeLib_GetTypeInfoCount_Proxy proto WINAPI \
		 pThis: ptr ITypeLib



;HRESULT
ITypeLib_GetTypeInfoCount_Stub proto WINAPI \
		 pThis: ptr ITypeLib,
	       pcTInfo: ptr UINT


;HRESULT
ITypeLib_GetLibAttr_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	    ppTLibAttr: ptr TLIBATTR



;HRESULT
ITypeLib_GetLibAttr_Stub proto WINAPI \
		 pThis: ptr ITypeLib,
	    ppTLibAttr: ptr LPTLIBATTR,
		pDummy: ptr CLEANLOCALSTORAGE


;HRESULT
ITypeLib_GetDocumentation_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
		 index: SINT,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR



;HRESULT
ITypeLib_GetDocumentation_Stub proto WINAPI \
		 pThis: ptr ITypeLib,
		 index: SINT,
	   refPtrFlags: DWORD,
	     pBstrName: ptr BSTR,
	pBstrDocString: ptr BSTR,
	pdwHelpContext: ptr DWORD,
	 pBstrHelpFile: ptr BSTR


;HRESULT
ITypeLib_IsName_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
		pfName: ptr BOOL



;HRESULT
ITypeLib_IsName_Stub proto WINAPI \
		 pThis: ptr ITypeLib,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
		pfName: ptr BOOL,
	  pBstrLibName: ptr BSTR


;HRESULT
ITypeLib_FindName_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo,
	       rgMemId: ptr MEMBERID,
	       pcFound: ptr USHORT



;HRESULT
ITypeLib_FindName_Stub proto WINAPI \
		 pThis: ptr ITypeLib,
	     szNameBuf: LPOLESTR,
	      lHashVal: ULONG,
	       ppTInfo: ptr ITypeInfo,
	       rgMemId: ptr MEMBERID,
	       pcFound: ptr USHORT,
	  pBstrLibName: ptr BSTR


;void
ITypeLib_ReleaseTLibAttr_Proxy proto WINAPI \
		 pThis: ptr ITypeLib,
	     pTLibAttr: ptr TLIBATTR



;HRESULT
ITypeLib_ReleaseTLibAttr_Stub proto WINAPI \
		 pThis: ptr ITypeLib


;HRESULT
ITypeLib2_GetLibStatistics_Proxy proto WINAPI \
		 pThis: ptr ITypeLib2,
	 pcUniqueNames: ptr ULONG,
       pcchUniqueNames: ptr ULONG



;HRESULT
ITypeLib2_GetLibStatistics_Stub proto WINAPI \
		 pThis: ptr ITypeLib2,
	 pcUniqueNames: ptr ULONG,
       pcchUniqueNames: ptr ULONG


;HRESULT
ITypeLib2_GetDocumentation2_Proxy proto WINAPI \
		 pThis: ptr ITypeLib2,
		 index: SINT,
		  lcid: LCID,
       pbstrHelpString: ptr BSTR,
  pdwHelpStringContext: ptr DWORD,
    pbstrHelpStringDll: ptr BSTR



;HRESULT
ITypeLib2_GetDocumentation2_Stub proto WINAPI \
		 pThis: ptr ITypeLib2,
		 index: SINT,
		  lcid: LCID,
	   refPtrFlags: DWORD,
       pbstrHelpString: ptr BSTR,
  pdwHelpStringContext: ptr DWORD,
    pbstrHelpStringDll: ptr BSTR



.list
endif

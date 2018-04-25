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
__oaidl_h__ equ <>

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

;PVOID
MIDL_user_allocate proto WINAPI \
		      : size_t

;void
MIDL_user_free proto WINAPI \
		      : PVOID

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

S_wireSAFEARRAY		STRUC
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
UNION ;__VARIANT_NAME_1
 STRUC ;__VARIANT_NAME_2
  vt			VARTYPE ?
  wReserved1		dw ?
  wReserved2		dw ?
  wReserved3		dw ?
  UNION ;__VARIANT_NAME_3
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
   STRUC ;__VARIANT_NAME_4
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

externdef		IID_ICreateTypeInfo:IID
.comdef ICreateTypeInfo
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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


.comdef ICreateTypeInfo2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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


.comdef ICreateTypeLib
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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


.comdef ICreateTypeLib2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
    DeleteTypeInfo	proc :LPOLESTR
    SetCustData		proc :REFGUID, :ptr
    SetHelpStringContext proc :DWORD
    SetHelpStringDll	proc :LPOLESTR
    .ends

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

.comdef IDispatch
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    .ends

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


.comdef IEnumVARIANT
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr
    .ends

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

.comdef ITypeComp
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Bind		proc
    BindType		proc
    .ends

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

.comdef ITypeInfo
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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


.comdef ITypeInfo2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeAttr		proc :ptr
    GetTypeComp		proc :ptr
    GetFuncDesc		proc :DWORD, :ptr
    GetVarDesc		proc :DWORD, :ptr
    GetNames		proc :MEMBERID, :ptr, :DWORD, :ptr
    GetRefTypeOfImplType proc :DWORD, :ptr
    GetImplTypeFlags	proc :DWORD, :ptr
    GetIDsOfNames	proc :ptr, :DWORD, :ptr
    Invoke_		proc :PVOID, :MEMBERID, :WORD, :ptr, :ptr, :ptr, :ptr
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

.comdef ITypeLib
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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

.comdef ITypeLib2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
    GetCustData		proc :REFGUID, :ptr
    GetLibStatistics	proc :ptr, :ptr
    GetDocumentation2	proc :DWORD, :LCID, :ptr, :ptr, :ptr
    GetAllCustData	proc :ptr
    .ends

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

.comdef ITypeChangeEvents
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    RequestTypeChange	proc :CHANGEKIND, :ptr, :LPOLESTR, :ptr
    AfterTypeChange	proc :CHANGEKIND, :ptr, :LPOLESTR
    .ends

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

.comdef IErrorInfo
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetGUID		proc :ptr
    GetSource		proc :ptr
    GetDescription	proc :ptr
    GetHelpFile		proc :ptr
    GetHelpContext	proc :ptr
    .ends

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


.comdef ICreateErrorInfo
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetGUID		proc :REFGUID
    SetSource		proc :LPOLESTR
    SetDescription	proc :LPOLESTR
    SetHelpFile		proc :LPOLESTR
    SetHelpContext	proc :DWORD
    .ends

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

.comdef ISupportErrorInfo
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InterfaceSupportsErrorInfo proc :REFIID
    .ends

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

.comdef ITypeFactory
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateFromTypeInfo	proc :ptr, :REFIID, :ptr
    .ends

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

.comdef ITypeMarshal
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    _Size		proc :PVOID, :DWORD, :PVOID, :ptr
    Marshal		proc :PVOID, :DWORD, :PVOID, :DWORD, :ptr, :ptr
    Unmarshal		proc :PVOID, :DWORD, :DWORD, :ptr, :ptr
    Free		proc :PVOID
    .ends

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

.comdef IRecordInfo
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    RecordInit		proc :PVOID
    RecordClear		proc :PVOID
    RecordCopy		proc :PVOID, :PVOID
    GetGuid		proc :ptr
    GetName		proc :ptr
    GetSize		proc :ptr
    GetTypeInfo		proc :ptr
    GetField		proc :PVOID, :LPCOLESTR, :ptr
    GetFieldNoCopy	proc :PVOID, :LPCOLESTR, :ptr, :ptr
    PutField		proc :DWORD, :PVOID, :LPCOLESTR, :ptr VARIANT
    PutFieldNoCopy	proc :DWORD, :PVOID, :LPCOLESTR, :ptr
    GetFieldNames	proc :ptr, :ptr
    IsMatchingType	proc :ptr
    RecordCreate	proc
    RecordCreateCopy	proc :PVOID, :ptr
    RecordDestroy	proc :PVOID
    .ends

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


endif

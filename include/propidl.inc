ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __propidl_h__
__propidl_h__ equ 1
.xlist

ifndef __IPropertyStorage_FWD_DEFINED__
__IPropertyStorage_FWD_DEFINED__ equ 1
endif
ifndef __IPropertySetStorage_FWD_DEFINED__
__IPropertySetStorage_FWD_DEFINED__ equ 1
endif
ifndef __IEnumSTATPROPSTG_FWD_DEFINED__
__IEnumSTATPROPSTG_FWD_DEFINED__ equ 1
endif
ifndef __IEnumSTATPROPSETSTG_FWD_DEFINED__
__IEnumSTATPROPSETSTG_FWD_DEFINED__ equ 1
endif

include objidl.inc
include oaidl.inc
.xlist

VERSIONEDSTREAM		STRUC
guidVersion		GUID <>
pStream			LPIStream ?
VERSIONEDSTREAM		ENDS

LPVERSIONEDSTREAM	typedef ptr VersionedStream


PROPSETFLAG_DEFAULT	equ ( 0 )
PROPSETFLAG_NONSIMPLE	equ ( 1 )
PROPSETFLAG_ANSI	equ ( 2 )
PROPSETFLAG_UNBUFFERED	equ ( 4 )
PROPSETFLAG_CASE_SENSITIVE equ ( 8 )
PROPSET_BEHAVIOR_CASE_SENSITIVE equ ( 1 )

ifdef MIDL_PASS
PROPVARIANT		typedef _inner_PROPVARIANT
else
;PROPVARIANT		typedef PROPVARIANT
endif

LPCHAR			typedef ptr sbyte
LPUCHAR			typedef ptr byte
LPSHORT			typedef ptr sword
LPUSHORT		typedef ptr word
LPULONG			typedef ptr dword

CAC			STRUC
cElems			ULONG ?
pElems			LPCHAR ?
CAC			ENDS

CAUB			STRUC
cElems			ULONG ?
pElems			LPUCHAR ?
CAUB			ENDS

CAI			STRUC
cElems			ULONG ?
pElems			LPSHORT ?
CAI			ENDS

CAUI			STRUC
cElems			ULONG ?
pElems			LPUSHORT ?
CAUI			ENDS

CAL			STRUC
cElems			ULONG ?
pElems			LPLONG ?
CAL			ENDS

CAUL			STRUC
cElems			ULONG ?
pElems			LPULONG ?
CAUL			ENDS

CAFLT			STRUC
cElems			ULONG ?
pElems			LPFLOAT ?
CAFLT			ENDS

CADBL			STRUC
cElems			ULONG ?
pElems			LPDOUBLE ?
CADBL			ENDS

CACY			STRUC
cElems			ULONG ?
pElems			LPCY ?
CACY			ENDS

CADATE			STRUC
cElems			ULONG ?
pElems			LPDATE ?
CADATE			ENDS

CABSTR			STRUC
cElems			ULONG ?
pElems			LPBSTR ?
CABSTR			ENDS

CABSTRBLOB		STRUC
cElems			ULONG ?
pElems			LPBSTRBLOB ?
CABSTRBLOB		ENDS

CABOOL			STRUC
cElems			ULONG ?
pElems			LPVARIANT_BOOL ?
CABOOL			ENDS

CASCODE			STRUC
cElems			ULONG ?
pElems			LPSCODE ?
CASCODE			ENDS

CAPROPVARIANT		STRUC
cElems			ULONG ?
pElems			LPPROPVARIANT ?
CAPROPVARIANT		ENDS

CAH			STRUC
cElems			ULONG ?
pElems			LPLARGE_INTEGER ?
CAH			ENDS

CAUH			STRUC
cElems			ULONG ?
pElems			LPULARGE_INTEGER ?
CAUH			ENDS

CALPSTR			STRUC
cElems			ULONG ?
pElems			LPSTR ?
CALPSTR			ENDS

CALPWSTR		STRUC
cElems			ULONG ?
pElems			LPWSTR ?
CALPWSTR		ENDS

CAFILETIME		STRUC
cElems			ULONG ?
pElems			LPFILETIME ?
CAFILETIME		ENDS

CACLIPDATA		STRUC
cElems			ULONG ?
pElems			LPCLIPDATA ?
CACLIPDATA		ENDS

CACLSID			STRUC
cElems			ULONG ?
pElems			LPCLSID ?
CACLSID			ENDS

ifdef MIDL_PASS
PROPVAR_PAD1		typedef BYTE
PROPVAR_PAD2		typedef BYTE
PROPVAR_PAD3		typedef ULONG
else
PROPVAR_PAD1		typedef WORD
PROPVAR_PAD2		typedef WORD
PROPVAR_PAD3		typedef WORD
tag_inner_PROPVARIANT equ 1
endif

if NOT defined(_MSC_EXTENSIONS)
;struct tagPROPVARIANT;
else
ifndef MIDL_PASS
PROPVARIANT		STRUC
UNION ; {
endif
_inner_PROPVARIANT	STRUC
vt			VARTYPE ?
wReserved1		PROPVAR_PAD1 ?
wReserved2		PROPVAR_PAD2 ?
wReserved3		PROPVAR_PAD3 ?
UNION ; {
cVal			CHAR ?
bVal			UCHAR ?
iVal			SHORT ?
uiVal			USHORT ?
lVal			LONG ?
ulVal			ULONG ?
intVal			SINT ?
uintVal			UINT ?
hVal			LARGE_INTEGER ?
uhVal			ULARGE_INTEGER ?
fltVal			FLOAT ?
dblVal			DOUBLE ?
boolVal			VARIANT_BOOL ?
bool			_VARIANT_BOOL ?
scode			SCODE ?
cyVal			CY ?
date			DATE ?
filetime		FILETIME ?
puuid			LPCLSID ?
pclipdata		LPCLIPDATA ?
bstrVal			BSTR ?
bstrblobVal		BSTRBLOB ?
blob			BLOB ?
pszVal			LPSTR ?
pwszVal			LPWSTR ?
punkVal			LPIUnknown ?
pdispVal		LPIDispatch ?
pStream			LPIStream ?
pStorage		LPIStorage ?
pVersionedStream	LPVERSIONEDSTREAM ?
parray			LPSAFEARRAY ?
cac			CAC ?
caub			CAUB ?
cai			CAI ?
caui			CAUI ?
cal			CAL ?
caul			CAUL ?
cah			CAH ?
cauh			CAUH ?
caflt			CAFLT ?
cadbl			CADBL ?
cabool			CABOOL ?
cascode			CASCODE ?
cacy			CACY ?
cadate			CADATE ?
cafiletime		CAFILETIME ?
cauuid			CACLSID ?
caclipdata		CACLIPDATA ?
cabstr			CABSTR ?
cabstrblob		CABSTRBLOB ?
calpstr			CALPSTR ?
calpwstr		CALPWSTR ?
capropvar		CAPROPVARIANT ?
pcVal			LPSTR ?
pbVal			LPUCHAR ?
piVal			LPSHORT ?
puiVal			LPUSHORT ?
plVal			LPLONG ?
pulVal			LPULONG ?
pintVal			LPINT ?
puintVal		LPUINT ?
pfltVal			LPFLOAT ?
pdblVal			LPDOUBLE ?
pboolVal		LPVARIANT_BOOL ?
pdecVal			LPDECIMAL ?
pscode			LPSCODE ?
pcyVal			LPCY ?
pdate			LPDATE ?
pbstrVal		LPBSTR ?
ppunkVal		LPIUnknown ?
ppdispVal		LPIDispatch ?
pparray			LPLPSAFEARRAY ?
pvarVal			LPPROPVARIANT ?
ENDS ;
_inner_PROPVARIANT	ENDS
ifndef MIDL_PASS
decVal			DECIMAL ?
ENDS
PROPVARIANT		ENDS
endif
endif

ifdef MIDL_PASS
LPPROPVARIANT		typedef ptr _inner_PROPVARIANT
REFPROPVARIANT		typedef ptr PROPVARIANT
else
LPPROPVARIANT		typedef ptr PROPVARIANT
ifndef _REFPROPVARIANT_DEFINED
_REFPROPVARIANT_DEFINED equ 1
REFPROPVARIANT		typedef ptr PROPVARIANT
endif

endif

PID_DICTIONARY		equ ( 0 )
PID_CODEPAGE		equ ( 0x1 )
PID_FIRST_USABLE	equ ( 0x2 )
PID_FIRST_NAME_DEFAULT	equ ( 0xfff )
PID_LOCALE		equ ( 0x80000000 )
PID_MODIFY_TIME		equ ( 0x80000001 )
PID_SECURITY		equ ( 0x80000002 )
PID_BEHAVIOR		equ ( 0x80000003 )
PID_ILLEGAL		equ ( 0xffffffff )

PID_MIN_READONLY	equ ( 0x80000000 )
PID_MAX_READONLY	equ ( 0xbfffffff )


PIDDI_THUMBNAIL		equ 0x00000002


PIDSI_TITLE		equ 0x00000002
PIDSI_SUBJECT		equ 0x00000003
PIDSI_AUTHOR		equ 0x00000004
PIDSI_KEYWORDS		equ 0x00000005
PIDSI_COMMENTS		equ 0x00000006
PIDSI_TEMPLATE		equ 0x00000007
PIDSI_LASTAUTHOR	equ 0x00000008
PIDSI_REVNUMBER		equ 0x00000009
PIDSI_EDITTIME		equ 0x0000000a
PIDSI_LASTPRINTED	equ 0x0000000b
PIDSI_CREATE_DTM	equ 0x0000000c
PIDSI_LASTSAVE_DTM	equ 0x0000000d
PIDSI_PAGECOUNT		equ 0x0000000e
PIDSI_WORDCOUNT		equ 0x0000000f
PIDSI_CHARCOUNT		equ 0x00000010
PIDSI_THUMBNAIL		equ 0x00000011
PIDSI_APPNAME		equ 0x00000012
PIDSI_DOC_SECURITY	equ 0x00000013


PIDDSI_CATEGORY		equ 0x00000002
PIDDSI_PRESFORMAT	equ 0x00000003
PIDDSI_BYTECOUNT	equ 0x00000004
PIDDSI_LINECOUNT	equ 0x00000005
PIDDSI_PARCOUNT		equ 0x00000006
PIDDSI_SLIDECOUNT	equ 0x00000007
PIDDSI_NOTECOUNT	equ 0x00000008
PIDDSI_HIDDENCOUNT	equ 0x00000009
PIDDSI_MMCLIPCOUNT	equ 0x0000000A
PIDDSI_SCALE		equ 0x0000000B
PIDDSI_HEADINGPAIR	equ 0x0000000C
PIDDSI_DOCPARTS		equ 0x0000000D
PIDDSI_MANAGER		equ 0x0000000E
PIDDSI_COMPANY		equ 0x0000000F
PIDDSI_LINKSDIRTY	equ 0x00000010



PIDMSI_EDITOR		equ 0x00000002
PIDMSI_SUPPLIER		equ 0x00000003
PIDMSI_SOURCE		equ 0x00000004
PIDMSI_SEQUENCE_NO	equ 0x00000005
PIDMSI_PROJECT		equ 0x00000006
PIDMSI_STATUS		equ 0x00000007
PIDMSI_OWNER		equ 0x00000008
PIDMSI_RATING		equ 0x00000009
PIDMSI_PRODUCTION	equ 0x0000000A
PIDMSI_COPYRIGHT	equ 0x0000000B


PIDMSI_STATUS_VALUE	typedef SDWORD
PIDMSI_STATUS_NORMAL	equ 0
PIDMSI_STATUS_NEW	equ ( PIDMSI_STATUS_NORMAL + 1 )
PIDMSI_STATUS_PRELIM	equ ( PIDMSI_STATUS_NEW + 1 )
PIDMSI_STATUS_DRAFT	equ ( PIDMSI_STATUS_PRELIM + 1 )
PIDMSI_STATUS_INPROGRESS equ ( PIDMSI_STATUS_DRAFT + 1 )
PIDMSI_STATUS_EDIT	equ ( PIDMSI_STATUS_INPROGRESS + 1 )
PIDMSI_STATUS_REVIEW	equ ( PIDMSI_STATUS_EDIT + 1 )
PIDMSI_STATUS_PROOF	equ ( PIDMSI_STATUS_REVIEW + 1 )
PIDMSI_STATUS_FINAL	equ ( PIDMSI_STATUS_PROOF + 1 )
PIDMSI_STATUS_OTHER	equ 0x7fff
PRSPEC_INVALID		equ ( 0xffffffff )

PRSPEC_LPWSTR		equ ( 0 )
PRSPEC_PROPID		equ ( 1 )

PROPSPEC		STRUC
ulKind			ULONG ?
UNION
 propid			PROPID ?
 lpwstr			LPOLESTR ?
ENDS
PROPSPEC		ENDS

STATPROPSTG		STRUC
lpwstrName		LPOLESTR ?
propid			PROPID ?
vt			VARTYPE ?
STATPROPSTG		ENDS

PROPSETHDR_OSVER_KIND macro dwOSVer
	exitm<HIWORD( (dwOSVer) )>
	endm
PROPSETHDR_OSVER_MAJOR macro dwOSVer
	exitm<LOBYTE(LOWORD( (dwOSVer) ))>
	endm
PROPSETHDR_OSVER_MINOR macro dwOSVer
	exitm<HIBYTE(LOWORD( (dwOSVer) ))>
	endm
PROPSETHDR_OSVERSION_UNKNOWN equ 0xFFFFFFFF
STATPROPSETSTG		STRUC
fmtid			FMTID <>
clsid			CLSID <>
grfFlags		dd ?
mtime			FILETIME <>
ctime			FILETIME <>
atime			FILETIME <>
dwOSVersion		dd ?
STATPROPSETSTG		ENDS

externdef		__MIDL_itf_propidl_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propidl_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPropertyStorage_INTERFACE_DEFINED__
__IPropertyStorage_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyStorage:IID
IPropertyStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ReadMultiple, :ULONG, :PROPSPEC, :PROPVARIANT
	STDMETHOD	WriteMultiple, :ULONG, :PROPSPEC, :PROPVARIANT, :PROPID
	STDMETHOD	DeleteMultiple, :ULONG, :PROPSPEC
	STDMETHOD	ReadPropertyNames, :ULONG, :PROPID, :LPOLESTR
	STDMETHOD	WritePropertyNames, :ULONG, :PROPID, :LPOLESTR
	STDMETHOD	DeletePropertyNames, :ULONG, :PROPID
	STDMETHOD	Commit, :DWORD
	STDMETHOD	Revert
	STDMETHOD	Enum, :ptr
	STDMETHOD	SetTimes, :ptr, :ptr, :ptr
	STDMETHOD	SetClass, :REFCLSID
	STDMETHOD	Stat, :ptr
IPropertyStorageVtbl ends
IPropertyStorage struct
	lpVtbl		PVOID ?
IPropertyStorage ends

endif

ifndef __IPropertySetStorage_INTERFACE_DEFINED__
__IPropertySetStorage_INTERFACE_DEFINED__ equ 1


externdef		IID_IPropertySetStorage:IID
IPropertySetStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Create, :REFFMTID, :ptr, :DWORD, :DWORD, :ptr
	STDMETHOD	Open, :REFFMTID, :DWORD, :ptr
	STDMETHOD	Delete, :REFFMTID
	STDMETHOD	Enum, :ptr
IPropertySetStorageVtbl ends
IPropertySetStorage struct
	lpVtbl		PVOID ?
IPropertySetStorage ends
LPPROPERTYSETSTORAGE	typedef ptr IPropertySetStorage

endif

ifndef __IEnumSTATPROPSTG_INTERFACE_DEFINED__
__IEnumSTATPROPSTG_INTERFACE_DEFINED__ equ 1


externdef		IID_IEnumSTATPROPSTG:IID
IEnumSTATPROPSTGVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumSTATPROPSTGVtbl ends
IEnumSTATPROPSTG struct
	lpVtbl		PVOID ?
IEnumSTATPROPSTG ends
LPENUMSTATPROPSTG	typedef ptr IEnumSTATPROPSTG

;HRESULT
IEnumSTATPROPSTG_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: ptr ULONG

;void
IEnumSTATPROPSTG_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


endif

ifndef __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__
__IEnumSTATPROPSETSTG_INTERFACE_DEFINED__ equ 1


externdef		IID_IEnumSTATPROPSETSTG:IID
IEnumSTATPROPSETSTGVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumSTATPROPSETSTGVtbl ends
IEnumSTATPROPSETSTG struct
	lpVtbl		PVOID ?
IEnumSTATPROPSETSTG ends
LPENUMSTATPROPSETSTG	typedef ptr IEnumSTATPROPSETSTG

;HRESULT
IEnumSTATPROPSETSTG_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: ptr ULONG

;void
IEnumSTATPROPSETSTG_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


endif




LPPROPERTYSTORAGE	typedef ptr IPropertyStorage

;WINOLEAPI
PropVariantCopy proto WINAPI \
	      pvarDest: ptr PROPVARIANT,
	       pvarSrc: ptr PROPVARIANT
;WINOLEAPI
PropVariantClear proto WINAPI \
	       pvar: ptr PROPVARIANT
;WINOLEAPI
FreePropVariantArray proto WINAPI \
	  cVariants: ULONG,
	     rgvars: ptr PROPVARIANT

if defined(_MSC_EXTENSIONS)


_PROPVARIANTINIT_DEFINED_ equ 1

PropVariantInit macro pvar
	exitm<memset ( (pvar), 0, sizeof(PROPVARIANT) )>
	endm

endif


ifndef _STGCREATEPROPSTG_DEFINED_

;WINOLEAPI
StgCreatePropStg proto WINAPI \
	       pUnk: ptr IUnknown,
	      fmtid: REFFMTID,
	     pclsid: ptr CLSID,
	   grfFlags: DWORD,
	 dwReserved: DWORD,
	  ppPropStg: ptr IPropertyStorage

;WINOLEAPI
StgOpenPropStg proto WINAPI \
	       pUnk: ptr IUnknown,
	      fmtid: REFFMTID,
	   grfFlags: DWORD,
	 dwReserved: DWORD,
	  ppPropStg: ptr IPropertyStorage

;WINOLEAPI
StgCreatePropSetStg proto WINAPI \
	   pStorage: ptr IStorage,
	 dwReserved: DWORD,
       ppPropSetStg: ptr IPropertySetStorage

CCH_MAX_PROPSTG_NAME	equ 31

;WINOLEAPI
FmtIdToPropStgName proto WINAPI \
	     pfmtid: ptr FMTID,
	    oszName: LPOLESTR

;WINOLEAPI
PropStgNameToFmtId proto WINAPI \
	    oszName: LPOLESTR,
	     pfmtid: ptr FMTID

endif

ifndef _SERIALIZEDPROPERTYVALUE_DEFINED_
_SERIALIZEDPROPERTYVALUE_DEFINED_ equ 1
SERIALIZEDPROPERTYVALUE STRUC
dwType			dd ?
rgb			db 1 dup(?)
SERIALIZEDPROPERTYVALUE ENDS
endif

;DWORD
StgConvertVariantToProperty proto WINAPI \
		  pvar: ptr PROPVARIANT,
	      CodePage: USHORT,
		 pprop: ptr SERIALIZEDPROPERTYVALUE,
		   pcb: ptr ULONG,
		   pid: PROPID,
	     fReserved: BOOLEAN,
	    pcIndirect: ptr ULONG


externdef		__MIDL_itf_propidl_0000_0004_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_propidl_0000_0004_v0_0_s_ifspec:RPC_IF_HANDLE


;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
LPSAFEARRAY_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;void
LPSAFEARRAY_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY


;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
LPSAFEARRAY_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;void
LPSAFEARRAY_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY


;HRESULT
IEnumSTATPROPSTG_Next_Proxy proto WINAPI \
		 _This: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: ptr ULONG



;HRESULT
IEnumSTATPROPSTG_Next_Stub proto WINAPI \
		 _This: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: ptr ULONG


;HRESULT
IEnumSTATPROPSETSTG_Next_Proxy proto WINAPI \
		 _This: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: ptr ULONG



;HRESULT
IEnumSTATPROPSETSTG_Next_Stub proto WINAPI \
		 _This: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: ptr ULONG

endif


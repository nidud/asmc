ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __propidlbase_h__
define __propidlbase_h__

ifndef __objidl_h__
include objidl.inc
endif
ifndef __oaidl_h__
include oaidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

ifndef _PROPIDLBASE_

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

VERSIONEDSTREAM struct
guidVersion	GUID <>
pStream		LPSTREAM ?
VERSIONEDSTREAM ends
LPVERSIONEDSTREAM typedef ptr VERSIONEDSTREAM

define	PROPSETFLAG_DEFAULT		0
define	PROPSETFLAG_NONSIMPLE		1
define	PROPSETFLAG_ANSI		2
define	PROPSETFLAG_UNBUFFERED		4
define	PROPSETFLAG_CASE_SENSITIVE	8
define	PROPSET_BEHAVIOR_CASE_SENSITIVE 1

LPCHAR		typedef ptr sbyte
LPUCHAR		typedef ptr byte
LPSHORT		typedef ptr sword
LPUSHORT	typedef ptr word
LPULONG		typedef ptr dword
LPPROPVARIANT	typedef ptr PROPVARIANT

.pragma pack(push, size_t)

CAC		struct
cElems		dd ?
pElems		LPCHAR ?
CAC		ends
CAUB		struct
cElems		dd ?
pElems		LPUCHAR ?
CAUB		ends
CAI		struct
cElems		dd ?
pElems		LPSHORT ?
CAI		ends
CAUI		struct
cElems		dd ?
pElems		LPUSHORT ?
CAUI		ends
CAL		struct
cElems		dd ?
pElems		LPLONG ?
CAL		ends
CAUL		struct
cElems		dd ?
pElems		LPULONG ?
CAUL		ends
CAFLT		struct
cElems		dd ?
pElems		LPFLOAT ?
CAFLT		ends
CADBL		struct
cElems		dd ?
pElems		LPDOUBLE ?
CADBL		ends
CACY		struct
cElems		dd ?
pElems		LPCY ?
CACY		ends
CADATE		struct
cElems		dd ?
pElems		LPDATE ?
CADATE		ends
CABSTR		struct
cElems		dd ?
pElems		LPBSTR ?
CABSTR		ends
CABSTRBLOB	struct
cElems		dd ?
pElems		LPBSTRBLOB ?
CABSTRBLOB	ends
CABOOL		struct
cElems		dd ?
pElems		LPVARIANT_BOOL ?
CABOOL		ends
CASCODE		struct
cElems		dd ?
pElems		PSCODE ?
CASCODE		ends
CAPROPVARIANT	struct
cElems		dd ?
pElems		LPPROPVARIANT ?
CAPROPVARIANT	ends
CAH		struct
cElems		dd ?
pElems		PLARGE_INTEGER ?
CAH		ends
CAUH		struct
cElems		dd ?
pElems		PULARGE_INTEGER ?
CAUH		ends
CALPSTR		struct
cElems		dd ?
pElems		LPSTR ?
CALPSTR		ends
CALPWSTR	struct
cElems		dd ?
pElems		LPWSTR ?
CALPWSTR	ends
CAFILETIME	struct
cElems		dd ?
pElems		LPFILETIME ?
CAFILETIME	ends
CACLIPDATA	struct
cElems		dd ?
pElems		LPCLIPDATA ?
CACLIPDATA	ends
CACLSID		struct
cElems		dd ?
pElems		LPCLSID ?
CACLSID		ends

ifdef _MSC_EXTENSIONS

PROPVARIANT	struct
union
 struct
  vt		dw ?
  wReserved1	dw ?
  wReserved2	dw ?
  wReserved3	dw ?
  union
   bVal		db ?
   iVal		SWORD ?
   uiVal	dw ?
   lVal		SDWORD ?
   ulVal	dd ?
   intVal	SDWORD ?
   uintVal	dd ?
   hVal		SQWORD ?
   uhVal	dq ?
   fltVal	REAL4 ?
   dblVal	REAL8 ?
   boolVal	SWORD ?
   scode	SCODE ?
   cyVal	CY <>
   date		DATE ?
   filetime	FILETIME <>
   puuid	LPCLSID ?
   pclipdata	LPCLIPDATA ?
   bstrVal	BSTR ?
   bstrblobVal	BSTRBLOB <>
   blob		BLOB <>
   pszVal	LPSTR ?
   pwszVal	LPWSTR ?
   punkVal	LPUNKNOWN ?
   pdispVal	LPDISPATCH ?
   pStream	LPSTREAM ?
   pStorage	LPSTORAGE ?
   pVersionedStream LPVERSIONEDSTREAM ?
   parray	LPSAFEARRAY ?
   cac		CAC <>
   caub		CAUB <>
   cai		CAI <>
   caui		CAUI <>
   cal		CAL <>
   caul		CAUL <>
   cah		CAH <>
   cauh		CAUH <>
   caflt	CAFLT <>
   cadbl	CADBL <>
   cabool	CABOOL <>
   cascode	CASCODE <>
   cacy		CACY <>
   cadate	CADATE <>
   cafiletime	CAFILETIME <>
   cauuid	CACLSID <>
   caclipdata	CACLIPDATA <>
   cabstr	CABSTR <>
   cabstrblob	CABSTRBLOB <>
   calpstr	CALPSTR <>
   calpwstr	CALPWSTR <>
   capropvar	CAPROPVARIANT <>
   pcVal	LPSTR ?
   pbVal	LPUCHAR ?
   piVal	LPSHORT ?
   puiVal	LPUSHORT ?
   plVal	LPLONG ?
   pulVal	LPULONG ?
   pintVal	LPINT ?
   puintVal	LPUINT ?
   pfltVal	LPFLOAT ?
   pdblVal	LPDOUBLE ?
   pboolVal	LPVARIANT_BOOL ?
   pdecVal	LPDECIMAL ?
   pscode	PSCODE ?
   pcyVal	LPCY ?
   pdate	LPDATE ?
   pbstrVal	LPBSTR ?
   ppunkVal	LPUNKNOWN ?
   ppdispVal	LPDISPATCH ?
   pparray	LPSAFEARRAY ?
   pvarVal	LPPROPVARIANT ?
  ends
 ends
ends
decVal		DECIMAL <>
PROPVARIANT	ends

endif

.pragma pack(pop)

ifndef _REFPROPVARIANT_DEFINED
define _REFPROPVARIANT_DEFINED
REFPROPVARIANT	typedef ptr PROPVARIANT
endif

define	PID_DICTIONARY		0
define	PID_CODEPAGE		0x1
define	PID_FIRST_USABLE	0x2
define	PID_FIRST_NAME_DEFAULT	0xfff
define	PID_LOCALE		0x80000000
define	PID_MODIFY_TIME		0x80000001
define	PID_SECURITY		0x80000002
define	PID_BEHAVIOR		0x80000003
define	PID_ILLEGAL		0xffffffff
define	PID_MIN_READONLY	0x80000000
define	PID_MAX_READONLY	0xbfffffff
define	PRSPEC_INVALID		0xffffffff
define	PRSPEC_LPWSTR		0
define	PRSPEC_PROPID		1

PROPSPEC	struct
ulKind		dd ?
union
 propid		PROPID ?
 lpwstr		LPOLESTR ?
ends
PROPSPEC	ends

STATPROPSTG	struct
lpwstrName	LPOLESTR ?
propid		PROPID ?
vt		VARTYPE ?
STATPROPSTG	ends

PROPSETHDR_OSVER_KIND macro dwOSVer
  exitm<HIWORD(dwOSVer)>
  endm
PROPSETHDR_OSVER_MAJOR macro dwOSVer
  exitm<LOBYTE(LOWORD(dwOSVer))>
  endm
PROPSETHDR_OSVER_MINOR macro dwOSVer
  exitm<HIBYTE(LOWORD(dwOSVer))>
  endm

define PROPSETHDR_OSVERSION_UNKNOWN 0xFFFFFFFF

STATPROPSETSTG	struct
fmtid		FMTID <>
clsid		CLSID <>
grfFlags	DWORD ?
mtime		FILETIME <>
ctime		FILETIME <>
atime		FILETIME <>
dwOSVersion	DWORD ?
STATPROPSETSTG	ends

ifndef __IPropertyStorage_INTERFACE_DEFINED__
define __IPropertyStorage_INTERFACE_DEFINED__
DEFINE_IIDX(IPropertyStorage, "00000138-0000-0000-C000-000000000046")

.comdef IPropertyStorage : public IUnknown

    ReadMultiple	proc :ULONG, :PROPSPEC, :PROPVARIANT
    WriteMultiple	proc :ULONG, :PROPSPEC, :PROPVARIANT, :PROPID
    DeleteMultiple	proc :ULONG, :PROPSPEC
    ReadPropertyNames	proc :ULONG, :PROPID, :LPOLESTR
    WritePropertyNames	proc :ULONG, :PROPID, :LPOLESTR
    DeletePropertyNames proc :ULONG, :PROPID
    Commit		proc :DWORD
    Revert		proc
    Enum		proc :ptr
    SetTimes		proc :ptr, :ptr, :ptr
    SetClass		proc :REFCLSID
    Stat		proc :ptr
   .ends

endif

ifndef __IPropertySetStorage_INTERFACE_DEFINED__
define __IPropertySetStorage_INTERFACE_DEFINED__
DEFINE_IIDX(IPropertySetStorage, "0000013A-0000-0000-C000-000000000046")

.comdef IPropertySetStorage : public IUnknown

    Create		proc :REFFMTID, :ptr, :DWORD, :DWORD, :ptr
    Open		proc :REFFMTID, :DWORD, :ptr
    Delete		proc :REFFMTID
    Enum		proc :ptr
   .ends

LPPROPERTYSETSTORAGE	typedef ptr IPropertySetStorage

endif

ifndef __IEnumSTATPROPSTG_INTERFACE_DEFINED__
define __IEnumSTATPROPSTG_INTERFACE_DEFINED__
DEFINE_IIDX(IEnumSTATPROPSTG, "00000139-0000-0000-C000-000000000046")

.comdef IEnumSTATPROPSTG : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

LPENUMSTATPROPSTG	typedef ptr IEnumSTATPROPSTG

endif

ifndef __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__
define __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__
DEFINE_IIDX(IEnumSTATPROPSETSTG, "0000013B-0000-0000-C000-000000000046")

.comdef IEnumSTATPROPSETSTG : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

LPENUMSTATPROPSETSTG	typedef ptr IEnumSTATPROPSETSTG

endif

LPPROPERTYSTORAGE	typedef ptr IPropertyStorage

endif

define _PROPIDLBASE_
endif

endif

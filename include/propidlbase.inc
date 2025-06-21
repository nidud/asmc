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

ifndef __propidlbase_h__
define __propidlbase_h__

include objidl.inc
include oaidl.inc
include winapifamily.inc

if ( _MSC_VER ge 800 )

ifndef _PROPIDLBASE_

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

tagVersionedStream	struct
guidVersion		GUID <>
pStream			LPSTREAM ?
tagVersionedStream	ends
VERSIONEDSTREAM		typedef tagVersionedStream
LPVERSIONEDSTREAM	typedef ptr tagVersionedStream

define	PROPSETFLAG_DEFAULT	( 0 )
define	PROPSETFLAG_NONSIMPLE	( 1 )
define	PROPSETFLAG_ANSI	( 2 )
define	PROPSETFLAG_UNBUFFERED	( 4 )
define	PROPSETFLAG_CASE_SENSITIVE	( 8 )
define	PROPSET_BEHAVIOR_CASE_SENSITIVE ( 1 )

LPCHAR			typedef ptr sbyte
LPUCHAR			typedef ptr byte
LPSHORT			typedef ptr sword
LPUSHORT		typedef ptr word
LPULONG			typedef ptr dword

.pragma pack(push, size_t)

tagCAC			struct
cElems			DD ?
pElems			LPCHAR ?
tagCAC			ends
CAC			typedef tagCAC

tagCAUB			struct
cElems			DD ?
pElems			LPUCHAR ?
tagCAUB			ends
CAUB			typedef tagCAUB

tagCAI			struct
cElems			DD ?
pElems			LPSHORT ?
tagCAI			ends
CAI			typedef tagCAI

tagCAUI			struct
cElems			DD ?
pElems			LPUSHORT ?
tagCAUI			ends
CAUI			typedef tagCAUI

tagCAL			struct
cElems			DD ?
pElems			LPLONG ?
tagCAL			ends
CAL			typedef tagCAL

tagCAUL			struct
cElems			DD ?
pElems			LPULONG ?
tagCAUL			ends
CAUL			typedef tagCAUL

tagCAFLT		struct
cElems			DD ?
pElems			LPFLOAT ?
tagCAFLT		ends
CAFLT			typedef tagCAFLT

tagCADBL		struct
cElems			DD ?
pElems			LPDOUBLE ?
tagCADBL		ends
CADBL			typedef tagCADBL

tagCACY			struct
cElems			DD ?
pElems			LPCY ?
tagCACY			ends
CACY			typedef tagCACY

tagCADATE		struct
cElems			DD ?
pElems			LPDATE ?
tagCADATE		ends
CADATE			typedef tagCADATE

tagCABSTR		struct
cElems			DD ?
pElems			LPBSTR ?
tagCABSTR		ends
CABSTR			typedef tagCABSTR

tagCABSTRBLOB		struct
cElems			DD ?
pElems			LPBSTRBLOB ?
tagCABSTRBLOB		ends
CABSTRBLOB		typedef tagCABSTRBLOB

tagCABOOL		struct
cElems			DD ?
pElems			LPVARIANT_BOOL ?
tagCABOOL		ends
CABOOL			typedef tagCABOOL

tagCASCODE		struct
cElems			DD ?
pElems			PSCODE ?
tagCASCODE		ends
CASCODE			typedef tagCASCODE

tagCAPROPVARIANT	struct
cElems			DD ?
pElems			PVOID ? ; LPPROPVARIANT
tagCAPROPVARIANT	ends
CAPROPVARIANT		typedef tagCAPROPVARIANT

tagCAH			struct
cElems			DD ?
pElems			PLARGE_INTEGER ?
tagCAH			ends
CAH			typedef tagCAH

tagCAUH			struct
cElems			DD ?
pElems			PULARGE_INTEGER ?
tagCAUH			ends
CAUH			typedef tagCAUH

tagCALPSTR		struct
cElems			DD ?
pElems			LPSTR ?
tagCALPSTR		ends
CALPSTR			typedef tagCALPSTR

tagCALPWSTR		struct
cElems			DD ?
pElems			LPWSTR ?
tagCALPWSTR		ends
CALPWSTR		typedef tagCALPWSTR

tagCAFILETIME		struct
cElems			DD ?
pElems			LPFILETIME ?
tagCAFILETIME		ends
CAFILETIME		typedef tagCAFILETIME

tagCACLIPDATA		struct
cElems			DD ?
pElems			LPCLIPDATA ?
tagCACLIPDATA		ends
CACLIPDATA		typedef tagCACLIPDATA

tagCACLSID		struct
cElems			DD ?
pElems			LPCLSID ?
tagCACLSID		ends
CACLSID			typedef tagCACLSID

ifdef _MSC_EXTENSIONS

LPPROPVARIANT		typedef ptr tagPROPVARIANT

tagPROPVARIANT		struct
union
 struct
  vt			WORD ?
  wReserved1		WORD ?
  wReserved2		WORD ?
  wReserved3		WORD ?
  union
   bVal			BYTE ?
   iVal			SWORD ?
   uiVal		WORD ?
   lVal			SDWORD ?
   ulVal		DWORD ?
   intVal		SDWORD ?
   uintVal		DWORD ?
   hVal			SQWORD ?
   uhVal		QWORD ?
   fltVal		REAL4 ?
   dblVal		REAL8 ?
   boolVal		SWORD ?
   scode		SCODE ?
   cyVal		CY <>
   date			DATE ?
   filetime		FILETIME <>
   puuid		LPCLSID ?
   pclipdata		LPCLIPDATA ?
   bstrVal		BSTR ?
   bstrblobVal		BSTRBLOB <>
   blob			BLOB <>
   pszVal		LPSTR ?
   pwszVal		LPWSTR ?
   punkVal		LPUNKNOWN ?
   pdispVal		LPDISPATCH ?
   pStream		LPSTREAM ?
   pStorage		LPSTORAGE ?
   pVersionedStream	LPVERSIONEDSTREAM ?
   parray		LPSAFEARRAY ?
   cac			CAC <>
   caub			CAUB <>
   cai			CAI <>
   caui			CAUI <>
   cal			CAL <>
   caul			CAUL <>
   cah			CAH <>
   cauh			CAUH <>
   caflt		CAFLT <>
   cadbl		CADBL <>
   cabool		CABOOL <>
   cascode		CASCODE <>
   cacy			CACY <>
   cadate		CADATE <>
   cafiletime		CAFILETIME <>
   cauuid		CACLSID <>
   caclipdata		CACLIPDATA <>
   cabstr		CABSTR <>
   cabstrblob		CABSTRBLOB <>
   calpstr		CALPSTR <>
   calpwstr		CALPWSTR <>
   capropvar		CAPROPVARIANT <>
   pcVal		LPSTR ?
   pbVal		LPUCHAR ?
   piVal		LPSHORT ?
   puiVal		LPUSHORT ?
   plVal		LPLONG ?
   pulVal		LPULONG ?
   pintVal		LPINT ?
   puintVal		LPUINT ?
   pfltVal		LPFLOAT ?
   pdblVal		LPDOUBLE ?
   pboolVal		LPVARIANT_BOOL ?
   pdecVal		LPDECIMAL ?
   pscode		PSCODE ?
   pcyVal		LPCY ?
   pdate		LPDATE ?
   pbstrVal		LPBSTR ?
   ppunkVal		LPUNKNOWN ?
   ppdispVal		LPDISPATCH ?
   pparray		LPSAFEARRAY ?
   pvarVal		LPPROPVARIANT ?
  ends
 ends
ends
decVal			DECIMAL <>
tagPROPVARIANT		ends
PROPVARIANT		typedef tagPROPVARIANT

endif

.pragma pack(pop)

ifndef _REFPROPVARIANT_DEFINED
define _REFPROPVARIANT_DEFINED
REFPROPVARIANT		typedef ptr PROPVARIANT
endif

endif

define	PID_DICTIONARY	( 0 )
define	PID_CODEPAGE	( 0x1 )
define	PID_FIRST_USABLE	( 0x2 )
define	PID_FIRST_NAME_DEFAULT	( 0xfff )
define	PID_LOCALE	( 0x80000000 )
define	PID_MODIFY_TIME ( 0x80000001 )
define	PID_SECURITY	( 0x80000002 )
define	PID_BEHAVIOR	( 0x80000003 )
define	PID_ILLEGAL	( 0xffffffff )
define	PID_MIN_READONLY	( 0x80000000 )
define	PID_MAX_READONLY	( 0xbfffffff )
define	PRSPEC_INVALID	( 0xffffffff )
define	PRSPEC_LPWSTR	( 0 )
define	PRSPEC_PROPID	( 1 )

tagPROPSPEC		struct
ulKind			ULONG ?
union
 propid			PROPID ?
 lpwstr			LPOLESTR ?
ends
tagPROPSPEC		ends
PROPSPEC		typedef tagPROPSPEC

tagSTATPROPSTG		struct
lpwstrName		LPOLESTR ?
propid			PROPID ?
vt			VARTYPE ?
tagSTATPROPSTG		ends
STATPROPSTG		typedef tagSTATPROPSTG

PROPSETHDR_OSVER_KIND macro dwOSVer
  exitm<HIWORD( (dwOSVer) )>
  endm
PROPSETHDR_OSVER_MAJOR macro dwOSVer
  exitm<LOBYTE(LOWORD( (dwOSVer) ))>
  endm
PROPSETHDR_OSVER_MINOR macro dwOSVer
  exitm<HIBYTE(LOWORD( (dwOSVer) ))>
  endm

define PROPSETHDR_OSVERSION_UNKNOWN	   0xFFFFFFFF

tagSTATPROPSETSTG	struct
fmtid			FMTID <>
clsid			CLSID <>
grfFlags		DWORD ?
mtime			FILETIME <>
ctime			FILETIME <>
atime			FILETIME <>
dwOSVersion		DWORD ?
tagSTATPROPSETSTG	ends
STATPROPSETSTG		typedef tagSTATPROPSETSTG

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

IEnumSTATPROPSTG_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATPROPSTG_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

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

IEnumSTATPROPSETSTG_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATPROPSETSTG_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

LPPROPERTYSTORAGE	typedef ptr IPropertyStorage

endif

define _PROPIDLBASE_
endif

BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

LPSAFEARRAY_UserSize proto WINAPI :ptr, :dword, :ptr
LPSAFEARRAY_UserMarshal proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserFree proto WINAPI :ptr, :ptr

BSTR_UserSize64 proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree64 proto WINAPI :ptr, :ptr

LPSAFEARRAY_UserSize64 proto WINAPI :ptr, :dword, :ptr
LPSAFEARRAY_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserFree64 proto WINAPI :ptr, :ptr

IEnumSTATPROPSTG_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATPROPSTG_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATPROPSETSTG_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATPROPSETSTG_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr

endif


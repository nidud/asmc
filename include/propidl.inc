ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif

ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __propidl_h__
define __propidl_h__

include objidl.inc
include oaidl.inc

if ( _MSC_VER ge 800 )

include winapifamily.inc

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
pElems			LPSCODE ?
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
   pscode		LPSCODE ?
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

LPPROPVARIANT		typedef ptr tagPROPVARIANT

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

include coml2api.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

define PIDDI_THUMBNAIL		0x00000002

define PIDSI_TITLE		0x00000002
define PIDSI_SUBJECT		0x00000003
define PIDSI_AUTHOR		0x00000004
define PIDSI_KEYWORDS		0x00000005
define PIDSI_COMMENTS		0x00000006
define PIDSI_TEMPLATE		0x00000007
define PIDSI_LASTAUTHOR		0x00000008
define PIDSI_REVNUMBER		0x00000009
define PIDSI_EDITTIME		0x0000000a
define PIDSI_LASTPRINTED	0x0000000b
define PIDSI_CREATE_DTM		0x0000000c
define PIDSI_LASTSAVE_DTM	0x0000000d
define PIDSI_PAGECOUNT		0x0000000e
define PIDSI_WORDCOUNT		0x0000000f
define PIDSI_CHARCOUNT		0x00000010
define PIDSI_THUMBNAIL		0x00000011
define PIDSI_APPNAME		0x00000012
define PIDSI_DOC_SECURITY	0x00000013

define PIDDSI_CATEGORY		0x00000002
define PIDDSI_PRESFORMAT	0x00000003
define PIDDSI_BYTECOUNT		0x00000004
define PIDDSI_LINECOUNT		0x00000005
define PIDDSI_PARCOUNT		0x00000006
define PIDDSI_SLIDECOUNT	0x00000007
define PIDDSI_NOTECOUNT		0x00000008
define PIDDSI_HIDDENCOUNT	0x00000009
define PIDDSI_MMCLIPCOUNT	0x0000000A
define PIDDSI_SCALE		0x0000000B
define PIDDSI_HEADINGPAIR	0x0000000C
define PIDDSI_DOCPARTS		0x0000000D
define PIDDSI_MANAGER		0x0000000E
define PIDDSI_COMPANY		0x0000000F
define PIDDSI_LINKSDIRTY	0x00000010

define PIDMSI_EDITOR		0x00000002
define PIDMSI_SUPPLIER		0x00000003
define PIDMSI_SOURCE		0x00000004
define PIDMSI_SEQUENCE_NO	0x00000005
define PIDMSI_PROJECT		0x00000006
define PIDMSI_STATUS		0x00000007
define PIDMSI_OWNER		0x00000008
define PIDMSI_RATING		0x00000009
define PIDMSI_PRODUCTION	0x0000000A
define PIDMSI_COPYRIGHT		0x0000000B

.enum PIDMSI_STATUS_VALUE {
    PIDMSI_STATUS_NORMAL	= 0,
    PIDMSI_STATUS_NEW		= ( PIDMSI_STATUS_NORMAL + 1 ),
    PIDMSI_STATUS_PRELIM	= ( PIDMSI_STATUS_NEW + 1 ),
    PIDMSI_STATUS_DRAFT		= ( PIDMSI_STATUS_PRELIM + 1 ),
    PIDMSI_STATUS_INPROGRESS	= ( PIDMSI_STATUS_DRAFT + 1 ) ,
    PIDMSI_STATUS_EDIT		= ( PIDMSI_STATUS_INPROGRESS + 1 ),
    PIDMSI_STATUS_REVIEW	= ( PIDMSI_STATUS_EDIT + 1 ),
    PIDMSI_STATUS_PROOF		= ( PIDMSI_STATUS_REVIEW + 1 ),
    PIDMSI_STATUS_FINAL		= ( PIDMSI_STATUS_PROOF + 1 ),
    PIDMSI_STATUS_OTHER		= 0x7fff
    }
endif

.pragma comment(lib, ole32)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

PropVariantCopy proto WINAPI :ptr, :ptr
PropVariantClear proto WINAPI :ptr
FreePropVariantArray proto WINAPI :ULONG, :ptr

ifdef _MSC_EXTENSIONS
define _PROPVARIANTINIT_DEFINED_

PropVariantInit proto fastcall pvar:ptr {
  memset(pvar, 0, sizeof(PROPVARIANT) )
  }
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef _SERIALIZEDPROPERTYVALUE_DEFINED_
define _SERIALIZEDPROPERTYVALUE_DEFINED_
tagSERIALIZEDPROPERTYVALUE struct
dwType			DWORD ?
rgb			BYTE 1 dup(?)
tagSERIALIZEDPROPERTYVALUE ends
SERIALIZEDPROPERTYVALUE typedef tagSERIALIZEDPROPERTYVALUE
endif

StgConvertVariantToProperty proto WINAPI :ptr, :USHORT, :ptr, :ptr, :PROPID, :BOOLEAN, :ptr

ifdef __cplusplus
StgConvertPropertyToVariant proto WINAPI :ptr, :USHORT, :ptr, :ptr
endif

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

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

ifndef __objidl_h__
define __objidl_h__

include unknwn.inc
include winapifamily.inc

if(NTDDI_VERSION ge NTDDI_VISTA and not defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0600
endif
if(NTDDI_VERSION ge NTDDI_WS03 and not defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0502
endif
if(NTDDI_VERSION ge NTDDI_WINXP and not defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0501
endif
if(NTDDI_VERSION ge NTDDI_WIN2K and not defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0500
endif

include limits.inc

ifndef _OBJIDLBASE_
include objidlbase
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IMallocSpy_INTERFACE_DEFINED__
define __IMallocSpy_INTERFACE_DEFINED__

LPMALLOCSPY		typedef ptr IMallocSpy

DEFINE_IIDX(IMallocSpy, "0000001d-0000-0000-C000-000000000046")

.comdef IMallocSpy : public IUnknown

    PreAlloc		proc :SIZE_T
    PostAlloc		proc :ptr
    PreFree		proc :ptr, :BOOL
    PostFree		proc :BOOL
    PreRealloc		proc :ptr, :SIZE_T, :ptr ptr, :BOOL
    PostRealloc		proc :ptr, :BOOL
    PreGetSize		proc :ptr, :BOOL
    PostGetSize		proc :SIZE_T, :BOOL
    PreDidAlloc		proc :ptr, :BOOL
    PostDidAlloc	proc :ptr, :BOOL, :int_t
    PreHeapMinimize	proc
    PostHeapMinimize	proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IBindCtx_INTERFACE_DEFINED__
define __IBindCtx_INTERFACE_DEFINED__

LPBC			typedef ptr IBindCtx
LPBINDCTX		typedef ptr IBindCtx

tagBIND_OPTS		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
tagBIND_OPTS		ends
BIND_OPTS		typedef tagBIND_OPTS
LPBIND_OPTS		typedef ptr tagBIND_OPTS

tagBIND_OPTS2		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
dwTrackFlags		DWORD ?
dwClassContext		DWORD ?
locale			LCID ?
pServerInfo		ptr COSERVERINFO ?
tagBIND_OPTS2		ends
BIND_OPTS2		typedef tagBIND_OPTS2

LPBIND_OPTS2		typedef ptr tagBIND_OPTS2

tagBIND_OPTS3		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
dwTrackFlags		DWORD ?
dwClassContext		DWORD ?
locale			LCID ?
pServerInfo		ptr COSERVERINFO ?
hwnd			HWND ?
tagBIND_OPTS3		ends
BIND_OPTS3		typedef tagBIND_OPTS3
LPBIND_OPTS3		typedef ptr tagBIND_OPTS3

.enum BIND_FLAGS {
	BIND_MAYBOTHERUSER	= 1,
	BIND_JUSTTESTEXISTENCE	= 2
    }

DEFINE_IIDX(IBindCtx, "0000000e-0000-0000-C000-000000000046")

.comdef IBindCtx : public IUnknown
    RegisterObjectBound proc :ptr
    RevokeObjectBound	proc :ptr
    ReleaseBoundObjects proc
    SetBindOptions	proc :ptr
    GetBindOptions	proc :ptr
    GetRunningObjectTable proc :ptr ptr
    RegisterObjectParam proc :LPOLESTR, :ptr
    GetObjectParam	proc :LPOLESTR, :ptr ptr
    EnumObjectParam	proc :ptr ptr
    RevokeObjectParam	proc :LPOLESTR
   .ends

IBindCtx_RemoteSetBindOptions_Proxy proto WINAPI :ptr, :ptr
IBindCtx_RemoteSetBindOptions_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IBindCtx_RemoteGetBindOptions_Proxy proto WINAPI :ptr, :ptr
IBindCtx_RemoteGetBindOptions_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IEnumMoniker_INTERFACE_DEFINED__
define __IEnumMoniker_INTERFACE_DEFINED__

LPENUMMONIKER		typedef ptr IEnumMoniker

DEFINE_IIDX(IEnumMoniker, "00000102-0000-0000-C000-000000000046")

.comdef IEnumMoniker : public IUnknown

    Next		proc :ULONG, :ptr ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumMoniker_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumMoniker_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IRunnableObject_INTERFACE_DEFINED__
define __IRunnableObject_INTERFACE_DEFINED__

LPRUNNABLEOBJECT	typedef ptr IRunnableObject

DEFINE_IIDX(IRunnableObject, "00000126-0000-0000-C000-000000000046")

.comdef IRunnableObject : public IUnknown

    GetRunningClass	proc :LPCLSID
    Run			proc :LPBINDCTX
    IsRunning		proc
    LockRunning		proc :BOOL, :BOOL
    SetContainedObject	proc :BOOL
   .ends

IRunnableObject_RemoteIsRunning_Proxy proto WINAPI :ptr
IRunnableObject_RemoteIsRunning_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IRunningObjectTable_INTERFACE_DEFINED__
define __IRunningObjectTable_INTERFACE_DEFINED__

LPRUNNINGOBJECTTABLE	typedef ptr IRunningObjectTable

DEFINE_IIDX(IRunningObjectTable, "00000010-0000-0000-C000-000000000046")

.comdef IRunningObjectTable : public IUnknown

    Register		proc :DWORD, :ptr, :ptr, :ptr
    Revoke		proc :DWORD
    IsRunning		proc :ptr
    GetObject		proc :ptr, :ptr ptr
    NoteChangeTime	proc :DWORD, :ptr
    GetTimeOfLastChange proc :ptr, :ptr
    EnumRunning		proc :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IPersist_INTERFACE_DEFINED__
define __IPersist_INTERFACE_DEFINED__

LPPERSIST		typedef ptr IPersist

DEFINE_IIDX(IPersist, "0000010c-0000-0000-C000-000000000046")

.comdef IPersist : public IUnknown

    GetClassID		proc :ptr
   .ends

endif

ifndef __IPersistStream_INTERFACE_DEFINED__
define __IPersistStream_INTERFACE_DEFINED__

LPPERSISTSTREAM		typedef ptr IPersistStream

DEFINE_IIDX(IPersistStream, "00000109-0000-0000-C000-000000000046")

.comdef IPersistStream : public IPersist

    IsDirty		proc
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    GetSizeMax		proc :ptr
   .ends

endif

ifndef __IMoniker_INTERFACE_DEFINED__
define __IMoniker_INTERFACE_DEFINED__

LPMONIKER		typedef ptr IMoniker

.enum MKSYS {
	MKSYS_NONE	= 0,
	MKSYS_GENERICCOMPOSITE	= 1,
	MKSYS_FILEMONIKER	= 2,
	MKSYS_ANTIMONIKER	= 3,
	MKSYS_ITEMMONIKER	= 4,
	MKSYS_POINTERMONIKER	= 5,
	MKSYS_CLASSMONIKER	= 7,
	MKSYS_OBJREFMONIKER	= 8,
	MKSYS_SESSIONMONIKER	= 9,
	MKSYS_LUAMONIKER	= 10
    }

.enum MKRREDUCE {
	MKRREDUCE_ONE	= ( 3 shl 16 ) ,
	MKRREDUCE_TOUSER	= ( 2 shl 16 ) ,
	MKRREDUCE_THROUGHUSER	= ( 1 shl 16 ) ,
	MKRREDUCE_ALL	= 0
    }

DEFINE_IIDX(IMoniker, "0000000f-0000-0000-C000-000000000046")

.comdef IMoniker : public IPersistStream

    BindToObject	proc :ptr, :ptr, :REFIID, :ptr ptr
    BindToStorage	proc :ptr, :ptr, :REFIID, :ptr ptr
    Reduce		proc :ptr, :DWORD, :ptr ptr, :ptr ptr
    ComposeWith		proc :ptr, :BOOL, :ptr ptr
    Enum		proc :BOOL, :ptr ptr
    IsEqual		proc :ptr
    Hash		proc :ptr
    IsRunning		proc :ptr, :ptr, :ptr
    GetTimeOfLastChange proc :ptr, :ptr, :ptr
    Inverse		proc :ptr ptr
    CommonPrefixWith	proc :ptr, :ptr ptr
    RelativePathTo	proc :ptr, :ptr ptr
    GetDisplayName	proc :ptr, :ptr, :ptr
    ParseDisplayName	proc :ptr, :ptr, :LPOLESTR, :ptr, :ptr ptr
    IsSystemMoniker	proc :ptr
   .ends

IMoniker_RemoteBindToObject_Proxy proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_RemoteBindToObject_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IMoniker_RemoteBindToStorage_Proxy proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_RemoteBindToStorage_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IROTData_INTERFACE_DEFINED__
define __IROTData_INTERFACE_DEFINED__

DEFINE_IIDX(IROTData, "f29f6bc0-5021-11ce-aa15-00006901293f")

.comdef IROTData : public IUnknown

    GetComparisonData	proc :ptr, :ULONG, :ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IEnumSTATSTG_INTERFACE_DEFINED__
define __IEnumSTATSTG_INTERFACE_DEFINED__

LPENUMSTATSTG		typedef ptr IEnumSTATSTG

DEFINE_IIDX(IEnumSTATSTG, "0000000d-0000-0000-C000-000000000046")

.comdef IEnumSTATSTG : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumSTATSTG_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATSTG_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IStorage_INTERFACE_DEFINED__
define __IStorage_INTERFACE_DEFINED__

LPSTORAGE		typedef ptr IStorage

tagRemSNB		struct
ulCntStr		ULONG ?
ulCntChar		ULONG ?
rgString		OLECHAR 1 dup(?)
tagRemSNB		ends
RemSNB			typedef tagRemSNB

wireSNB			typedef ptr RemSNB

SNB			typedef ptr LPOLESTR

DEFINE_IIDX(IStorage, "0000000b-0000-0000-C000-000000000046")

.comdef IStorage : public IUnknown

    CreateStream	proc :ptr, :DWORD, :DWORD, :DWORD, :ptr ptr
    OpenStream		proc :ptr, :ptr, :DWORD, :DWORD, :ptr ptr
    CreateStorage	proc :ptr, :DWORD, :DWORD, :DWORD, :ptr ptr
    OpenStorage		proc :ptr, :ptr, :DWORD, :SNB, :DWORD, :ptr ptr
    CopyTo		proc :DWORD, :ptr, :SNB, :ptr
    MoveElementTo	proc :ptr, :ptr, :ptr, :DWORD
    Commit		proc :DWORD
    Revert		proc
    EnumElements	proc :DWORD, :ptr, :DWORD, :ptr ptr
    DestroyElement	proc :ptr
    RenameElement	proc :ptr, :ptr
    SetElementTimes	proc :ptr, :ptr, :ptr, :ptr
    SetClass		proc :REFCLSID
    SetStateBits	proc :DWORD, :DWORD
    Stat		proc :ptr, :DWORD
   .ends

IStorage_RemoteOpenStream_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr, :DWORD, :DWORD, :ptr ptr
IStorage_RemoteOpenStream_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IStorage_RemoteCopyTo_Proxy proto WINAPI :ptr, :DWORD, :ptr, :SNB, :ptr
IStorage_RemoteCopyTo_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IStorage_RemoteEnumElements_Proxy proto WINAPI :ptr, :DWORD, :ULONG, :ptr, :DWORD, :ptr ptr
IStorage_RemoteEnumElements_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IPersistFile_INTERFACE_DEFINED__
define __IPersistFile_INTERFACE_DEFINED__

LPPERSISTFILE		typedef ptr IPersistFile

DEFINE_IIDX(IPersistFile, "0000010b-0000-0000-C000-000000000046")

.comdef IPersistFile : public IPersist

    IsDirty		proc
    Load		proc :LPCOLESTR, :DWORD
    Save		proc :LPCOLESTR, :BOOL
    SaveCompleted	proc :LPCOLESTR
    GetCurFile		proc :ptr
   .ends

endif

ifndef __IPersistStorage_INTERFACE_DEFINED__
define __IPersistStorage_INTERFACE_DEFINED__

LPPERSISTSTORAGE	typedef ptr IPersistStorage

DEFINE_IIDX(IPersistStorage, "0000010a-0000-0000-C000-000000000046")

.comdef IPersistStorage : public IPersist

    IsDirty		proc
    InitNew		proc :ptr
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    SaveCompleted	proc :ptr
    HandsOffStorage	proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __ILockBytes_INTERFACE_DEFINED__
define __ILockBytes_INTERFACE_DEFINED__

LPLOCKBYTES		typedef ptr ILockBytes

DEFINE_IIDX(ILockBytes, "0000000a-0000-0000-C000-000000000046")

.comdef ILockBytes : public IUnknown

    ReadAt		proc :ULARGE_INTEGER, :ptr, :ULONG, :ptr
    WriteAt		proc :ULARGE_INTEGER, :ptr, :ULONG, :ptr
    Flush		proc
    SetSize		proc :ULARGE_INTEGER
    LockRegion		proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    UnlockRegion	proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    Stat		proc :ptr, :DWORD
   .ends

ILockBytes_RemoteReadAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_RemoteReadAt_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
ILockBytes_RemoteWriteAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_RemoteWriteAt_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IEnumFORMATETC_INTERFACE_DEFINED__
define __IEnumFORMATETC_INTERFACE_DEFINED__

LPENUMFORMATETC		typedef ptr IEnumFORMATETC

tagDVTARGETDEVICE	struct
tdSize			DWORD ?
tdDriverNameOffset	WORD ?
tdDeviceNameOffset	WORD ?
tdPortNameOffset	WORD ?
tdExtDevmodeOffset	WORD ?
tdData			BYTE 1 dup(?)
tagDVTARGETDEVICE	ends
DVTARGETDEVICE		typedef tagDVTARGETDEVICE

LPCLIPFORMAT		typedef ptr CLIPFORMAT

tagFORMATETC		struct
cfFormat		CLIPFORMAT ?
ptd			ptr DVTARGETDEVICE ?
dwAspect		DWORD ?
lindex			LONG ?
tymed			DWORD ?
tagFORMATETC		ends
FORMATETC		typedef tagFORMATETC

LPFORMATETC		typedef ptr tagFORMATETC

DEFINE_IIDX(IEnumFORMATETC, "00000103-0000-0000-C000-000000000046")

.comdef IEnumFORMATETC : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumFORMATETC_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumFORMATETC_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IEnumSTATDATA_INTERFACE_DEFINED__
define __IEnumSTATDATA_INTERFACE_DEFINED__

LPENUMSTATDATA		typedef ptr IEnumSTATDATA

.enum ADVF {
	ADVF_NODATA	= 1,
	ADVF_PRIMEFIRST = 2,
	ADVF_ONLYONCE	= 4,
	ADVF_DATAONSTOP = 64,
	ADVFCACHE_NOHANDLER	= 8,
	ADVFCACHE_FORCEBUILTIN	= 16,
	ADVFCACHE_ONSAVE	= 32
    }

tagSTATDATA		struct
formatetc		FORMATETC <>
advf			DWORD ?
pAdvSink		ptr IAdviseSink ?
dwConnection		DWORD ?
tagSTATDATA		ends
STATDATA		typedef tagSTATDATA
LPSTATDATA		typedef ptr STATDATA

DEFINE_IIDX(IEnumSTATDATA, "00000105-0000-0000-C000-000000000046")

.comdef IEnumSTATDATA : public IUnknown
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumSTATDATA_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATDATA_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IRootStorage_INTERFACE_DEFINED__
define __IRootStorage_INTERFACE_DEFINED__

LPROOTSTORAGE		typedef ptr IRootStorage

DEFINE_IIDX(IRootStorage, "00000012-0000-0000-C000-000000000046")

.comdef IRootStorage : public IUnknown

    SwitchToFile	proc :LPOLESTR
   .ends

endif

ifndef __IAdviseSink_INTERFACE_DEFINED__
define __IAdviseSink_INTERFACE_DEFINED__

LPADVISESINK		typedef ptr IAdviseSink

.enum TYMED {
	TYMED_HGLOBAL	= 1,
	TYMED_FILE	= 2,
	TYMED_ISTREAM	= 4,
	TYMED_ISTORAGE	= 8,
	TYMED_GDI	= 16,
	TYMED_MFPICT	= 32,
	TYMED_ENHMF	= 64,
	TYMED_NULL	= 0
    }

tagRemSTGMEDIUM		struct
tymed			DWORD ?
dwHandleType		DWORD ?
pData			ULONG ?
pUnkForRelease		ULONG ?
cbData			ULONG ?
data			byte 1 dup(?)
tagRemSTGMEDIUM		ends
RemSTGMEDIUM		typedef tagRemSTGMEDIUM


tagSTGMEDIUM		struct
tymed			DWORD ?
union u
 hBitmap		HBITMAP ?
 hMetaFilePict		HMETAFILEPICT ?
 hEnhMetaFile		HENHMETAFILE ?
 hGlobal		HGLOBAL ?
 lpszFileName		LPOLESTR ?
 pstm			LPSTREAM ?
 pstg			LPSTORAGE ?
ends
pUnkForRelease		LPUNKNOWN ?
tagSTGMEDIUM		ends
uSTGMEDIUM		typedef tagSTGMEDIUM

GDI_OBJECT		struct
ObjectType		DWORD ?
union u
 hBitmap		wireHBITMAP ?
 hPalette		wireHPALETTE ?
 hGeneric		wireHGLOBAL ?
ends
GDI_OBJECT		ends
LPGDI_OBJECT		typedef ptr GDI_OBJECT

userSTGMEDIUM		struct
struct
 tymed			DWORD ?
 union u
  hHEnhMetaFile		wireHENHMETAFILE ?
  hGdiHandle		ptr GDI_OBJECT ?
  hGlobal		wireHGLOBAL ?
  lpszFileName		LPOLESTR ?
  pstm			UP_BYTE_BLOB ?
  pstg			UP_BYTE_BLOB ?
 ends
ends
pUnkForRelease		LPUNKNOWN ?
userSTGMEDIUM		ends
wireSTGMEDIUM		typedef ptr userSTGMEDIUM
STGMEDIUM		typedef uSTGMEDIUM
wireASYNC_STGMEDIUM	typedef ptr userSTGMEDIUM
ASYNC_STGMEDIUM		typedef STGMEDIUM
LPSTGMEDIUM		typedef ptr STGMEDIUM

userFLAG_STGMEDIUM	struct
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			userSTGMEDIUM <>
userFLAG_STGMEDIUM	ends
wireFLAG_STGMEDIUM	typedef ptr userFLAG_STGMEDIUM

FLAG_STGMEDIUM		struct
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			STGMEDIUM <>
FLAG_STGMEDIUM		ends


DEFINE_IIDX(IAdviseSink, "0000010f-0000-0000-C000-000000000046")

.comdef IAdviseSink : public IUnknown

    OnDataChange	proc :ptr, :ptr
    OnViewChange	proc :DWORD, :LONG
    OnRename		proc :ptr
    OnSave		proc
    OnClose		proc
   .ends

IAdviseSink_RemoteOnDataChange_Proxy proto WINAPI :ptr, :ptr, :ptr
IAdviseSink_RemoteOnDataChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IAdviseSink_RemoteOnViewChange_Proxy proto WINAPI :ptr, :DWORD, :LONG
IAdviseSink_RemoteOnViewChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IAdviseSink_RemoteOnRename_Proxy proto WINAPI :ptr, :ptr
IAdviseSink_RemoteOnRename_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IAdviseSink_RemoteOnSave_Proxy proto WINAPI :ptr
IAdviseSink_RemoteOnSave_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IAdviseSink_RemoteOnClose_Proxy proto WINAPI :ptr
IAdviseSink_RemoteOnClose_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __AsyncIAdviseSink_INTERFACE_DEFINED__
define __AsyncIAdviseSink_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIAdviseSink, "00000150-0000-0000-C000-000000000046")

.comdef AsyncIAdviseSink : public IUnknown

    Begin_OnDataChange	proc :ptr, :ptr
    Finish_OnDataChange proc
    Begin_OnViewChange	proc :DWORD, :LONG
    Finish_OnViewChange proc
    Begin_OnRename	proc :ptr
    Finish_OnRename	proc
    Begin_OnSave	proc
    Finish_OnSave	proc
    Begin_OnClose	proc
    Finish_OnClose	proc
   .ends

AsyncIAdviseSink_Begin_RemoteOnDataChange_Proxy proto WINAPI :ptr, :ptr, :ptr
AsyncIAdviseSink_Begin_RemoteOnDataChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnDataChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnDataChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Begin_RemoteOnViewChange_Proxy proto WINAPI :ptr, :DWORD, :LONG
AsyncIAdviseSink_Begin_RemoteOnViewChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnViewChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnViewChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Begin_RemoteOnRename_Proxy proto WINAPI :ptr, :ptr
AsyncIAdviseSink_Begin_RemoteOnRename_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnRename_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnRename_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Begin_RemoteOnSave_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Begin_RemoteOnSave_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnSave_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnSave_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Begin_RemoteOnClose_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Begin_RemoteOnClose_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnClose_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnClose_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IAdviseSink2_INTERFACE_DEFINED__
define __IAdviseSink2_INTERFACE_DEFINED__

DEFINE_IIDX(IAdviseSink2, "00000125-0000-0000-C000-000000000046")

.comdef IAdviseSink2 : public IAdviseSink

    OnLinkSrcChange	proc :ptr
   .ends

LPADVISESINK2		typedef ptr IAdviseSink2

IAdviseSink2_RemoteOnLinkSrcChange_Proxy proto WINAPI :ptr, :ptr
IAdviseSink2_RemoteOnLinkSrcChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __AsyncIAdviseSink2_INTERFACE_DEFINED__
define __AsyncIAdviseSink2_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIAdviseSink2, "00000151-0000-0000-C000-000000000046")

.comdef AsyncIAdviseSink2 : public AsyncIAdviseSink

    Begin_OnLinkSrcChange proc :ptr
    Finish_OnLinkSrcChange proc
   .ends

AsyncIAdviseSink2_Begin_RemoteOnLinkSrcChange_Proxy proto WINAPI :ptr, :ptr
AsyncIAdviseSink2_Begin_RemoteOnLinkSrcChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink2_Finish_RemoteOnLinkSrcChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink2_Finish_RemoteOnLinkSrcChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IDataObject_INTERFACE_DEFINED__
define __IDataObject_INTERFACE_DEFINED__

.enum DATADIR {
	DATADIR_GET	= 1,
	DATADIR_SET	= 2
    }

DEFINE_IIDX(IDataObject, "0000010e-0000-0000-C000-000000000046")

.comdef IDataObject : public IUnknown

    GetData		proc :ptr, :ptr
    GetDataHere		proc :ptr, :ptr
    QueryGetData	proc :ptr
    GetCanonicalFormatEtc proc :ptr, :ptr
    SetData		proc :ptr, :ptr, :BOOL
    EnumFormatEtc	proc :DWORD, :ptr ptr
    DAdvise		proc :ptr, :DWORD, :ptr, :ptr
    DUnadvise		proc :DWORD
    EnumDAdvise		proc :ptr ptr
   .ends

LPDATAOBJECT		typedef ptr IDataObject

IDataObject_RemoteGetData_Proxy proto WINAPI :ptr, :ptr, :ptr
IDataObject_RemoteGetData_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IDataObject_RemoteGetDataHere_Proxy proto WINAPI :ptr, :ptr, :ptr
IDataObject_RemoteGetDataHere_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IDataObject_RemoteSetData_Proxy proto WINAPI :ptr, :ptr, :ptr, :BOOL
IDataObject_RemoteSetData_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IDataAdviseHolder_INTERFACE_DEFINED__
define __IDataAdviseHolder_INTERFACE_DEFINED__

DEFINE_IIDX(IDataAdviseHolder, "00000110-0000-0000-C000-000000000046")

.comdef IDataAdviseHolder : public IUnknown

    Advise		proc :ptr, :ptr, :DWORD, :ptr, :ptr
    Unadvise		proc :DWORD
    EnumAdvise		proc :ptr ptr
    SendOnDataChange	proc :ptr, :DWORD, :DWORD
   .ends

LPDATAADVISEHOLDER	typedef ptr IDataAdviseHolder

endif

ifndef __IMessageFilter_INTERFACE_DEFINED__
define __IMessageFilter_INTERFACE_DEFINED__

.enum CALLTYPE {
	CALLTYPE_TOPLEVEL	= 1,
	CALLTYPE_NESTED = 2,
	CALLTYPE_ASYNC	= 3,
	CALLTYPE_TOPLEVEL_CALLPENDING	= 4,
	CALLTYPE_ASYNC_CALLPENDING	= 5
    }

.enum SERVERCALL {
	SERVERCALL_ISHANDLED	= 0,
	SERVERCALL_REJECTED	= 1,
	SERVERCALL_RETRYLATER	= 2
    }

.enum PENDINGTYPE {
	PENDINGTYPE_TOPLEVEL	= 1,
	PENDINGTYPE_NESTED	= 2
    }

.enum PENDINGMSG {
	PENDINGMSG_CANCELCALL	= 0,
	PENDINGMSG_WAITNOPROCESS	= 1,
	PENDINGMSG_WAITDEFPROCESS	= 2
    }

tagINTERFACEINFO	struct
pUnk			LPUNKNOWN ?
iid			IID <>
wMethod			WORD ?
tagINTERFACEINFO	ends
INTERFACEINFO		typedef tagINTERFACEINFO
LPINTERFACEINFO		typedef ptr tagINTERFACEINFO

DEFINE_IIDX(IMessageFilter, "00000016-0000-0000-C000-000000000046")

.comdef IMessageFilter : public IUnknown

    HandleInComingCall	proc :DWORD, :HTASK, :DWORD, :LPINTERFACEINFO
    RetryRejectedCall	proc :HTASK, :DWORD, :DWORD
    MessagePending	proc :HTASK, :DWORD, :DWORD
   .ends

LPMESSAGEFILTER		typedef ptr IMessageFilter

endif

externdef FMTID_SummaryInformation:FMTID
externdef FMTID_DocSummaryInformation:FMTID
externdef FMTID_UserDefinedProperties:FMTID
externdef FMTID_DiscardableInformation:FMTID
externdef FMTID_ImageSummaryInformation:FMTID
externdef FMTID_AudioSummaryInformation:FMTID
externdef FMTID_VideoSummaryInformation:FMTID
externdef FMTID_MediaFileSummaryInformation:FMTID

ifndef __IClassActivator_INTERFACE_DEFINED__
define __IClassActivator_INTERFACE_DEFINED__

DEFINE_IIDX(IClassActivator, "00000140-0000-0000-C000-000000000046")

.comdef IClassActivator : public IUnknown

    GetClassObject	proc :REFCLSID, :DWORD, :LCID, :REFIID, :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifndef __IFillLockBytes_INTERFACE_DEFINED__
define __IFillLockBytes_INTERFACE_DEFINED__

DEFINE_IIDX(IFillLockBytes, "99caf010-415e-11cf-8814-00aa00b569f5")

.comdef IFillLockBytes : public IUnknown

    FillAppend		proc :ptr, :ULONG, :ptr
    FillAt		proc :ULARGE_INTEGER, :ptr, :ULONG, :ptr
    SetFillSize		proc :ULARGE_INTEGER
    Terminate		proc :BOOL
   .ends

IFillLockBytes_RemoteFillAppend_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
IFillLockBytes_RemoteFillAppend_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IFillLockBytes_RemoteFillAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
IFillLockBytes_RemoteFillAt_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IProgressNotify_INTERFACE_DEFINED__
define __IProgressNotify_INTERFACE_DEFINED__

DEFINE_IIDX(IProgressNotify, "a9d758a0-4617-11cf-95fc-00aa00680db4")

.comdef IProgressNotify : public IUnknown

    OnProgress		proc :DWORD, :DWORD, :BOOL, :BOOL
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifndef __ILayoutStorage_INTERFACE_DEFINED__
define __ILayoutStorage_INTERFACE_DEFINED__

tagStorageLayout	struct
LayoutType		DWORD ?
pwcsElementName		ptr OLECHAR ?
cOffset			LARGE_INTEGER <>
cBytes			LARGE_INTEGER <>
tagStorageLayout	ends
StorageLayout		typedef tagStorageLayout

DEFINE_IIDX(ILayoutStorage, "0e6d4d90-6738-11cf-9608-00aa00680db4")

.comdef ILayoutStorage : public IUnknown

    LayoutScript	proc :ptr, :DWORD, :DWORD
    BeginMonitor	proc
    EndMonitor		proc
    ReLayoutDocfile	proc :ptr
    ReLayoutDocfileOnILockBytes proc :ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IBlockingLock_INTERFACE_DEFINED__
define __IBlockingLock_INTERFACE_DEFINED__

DEFINE_IIDX(IBlockingLock, "30f3d47a-6447-11d1-8e3c-00c04fb9386d")

.comdef IBlockingLock : public IUnknown

    _Lock		proc :DWORD
    Unlock		proc
   .ends

endif

ifndef __ITimeAndNoticeControl_INTERFACE_DEFINED__
define __ITimeAndNoticeControl_INTERFACE_DEFINED__

DEFINE_IIDX(ITimeAndNoticeControl, "bc0bf6ae-8878-11d1-83e9-00c04fc2c6d4")

.comdef ITimeAndNoticeControl : public IUnknown

    SuppressChanges	proc :DWORD, :DWORD
   .ends

endif

ifndef __IOplockStorage_INTERFACE_DEFINED__
define __IOplockStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IOplockStorage, "8d19c834-8879-11d1-83e9-00c04fc2c6d4")

.comdef IOplockStorage : public IUnknown

    CreateStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr ptr
    OpenStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifndef __IDirectWriterLock_INTERFACE_DEFINED__
define __IDirectWriterLock_INTERFACE_DEFINED__

DEFINE_IIDX(IDirectWriterLock, "0e6d4d92-6738-11cf-9608-00aa00680db4")

.comdef IDirectWriterLock : public IUnknown

    WaitForWriteAccess	proc :DWORD
    ReleaseWriteAccess	proc
    HaveWriteAccess	proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IUrlMon_INTERFACE_DEFINED__
define __IUrlMon_INTERFACE_DEFINED__

DEFINE_IIDX(IUrlMon, "00000026-0000-0000-C000-000000000046")

.comdef IUrlMon : public IUnknown

    AsyncGetClassBits	proc :REFCLSID, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD, :LPCWSTR, :ptr, :DWORD, :REFIID, :DWORD
   .ends

endif

ifndef __IForegroundTransfer_INTERFACE_DEFINED__
define __IForegroundTransfer_INTERFACE_DEFINED__

DEFINE_IIDX(IForegroundTransfer, "00000145-0000-0000-C000-000000000046")

.comdef IForegroundTransfer : public IUnknown

    AllowForegroundTransfer proc :ptr
   .ends

endif

ifndef __IThumbnailExtractor_INTERFACE_DEFINED__
define __IThumbnailExtractor_INTERFACE_DEFINED__

DEFINE_IIDX(IThumbnailExtractor, "969dc708-5c76-11d1-8d86-0000f804b057")

.comdef IThumbnailExtractor : public IUnknown

    ExtractThumbnail	proc :ptr, :ULONG, :ULONG, :ptr, :ptr, :ptr
    OnFileUpdated	proc :ptr
   .ends

endif

ifndef __IDummyHICONIncluder_INTERFACE_DEFINED__
define __IDummyHICONIncluder_INTERFACE_DEFINED__

DEFINE_IIDX(IDummyHICONIncluder, "947990de-cc28-11d2-a0f7-00805f858fb1")

.comdef IDummyHICONIncluder : public IUnknown

    Dummy		proc :HICON, :HDC
   .ends

endif

.enum ApplicationType {
	ServerApplication	= 0,
	LibraryApplication	= ( ServerApplication + 1 )
    }

.enum ShutdownType {
	IdleShutdown	= 0,
	ForcedShutdown	= ( IdleShutdown + 1 )
    }

ifndef __IProcessLock_INTERFACE_DEFINED__
define __IProcessLock_INTERFACE_DEFINED__

DEFINE_IIDX(IProcessLock, "000001d5-0000-0000-C000-000000000046")

.comdef IProcessLock : public IUnknown

    AddRefOnProcess	proc
    ReleaseRefOnProcess proc
   .ends

endif

ifndef __ISurrogateService_INTERFACE_DEFINED__
define __ISurrogateService_INTERFACE_DEFINED__

DEFINE_IIDX(ISurrogateService, "000001d4-0000-0000-C000-000000000046")

.comdef ISurrogateService : public IUnknown

    Init		proc :REFGUID, :ptr, :ptr
    ApplicationLaunch	proc :REFGUID, :ApplicationType
    ApplicationFree	proc :REFGUID
    CatalogRefresh	proc :ULONG
    ProcessShutdown	proc :ShutdownType
   .ends

endif

if  (_WIN32_WINNT ge 0x0501 )

ifndef __IInitializeSpy_INTERFACE_DEFINED__
define __IInitializeSpy_INTERFACE_DEFINED__

DEFINE_IIDX(IInitializeSpy, "00000034-0000-0000-C000-000000000046")

.comdef IInitializeSpy : public IUnknown

    PreInitialize	proc :DWORD, :DWORD
    PostInitialize	proc :HRESULT, :DWORD, :DWORD
    PreUninitialize	proc :DWORD
    PostUninitialize	proc :DWORD
   .ends

LPINITIALIZESPY		typedef ptr IInitializeSpy

endif

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifndef __IApartmentShutdown_INTERFACE_DEFINED__
define __IApartmentShutdown_INTERFACE_DEFINED__

DEFINE_IIDX(IApartmentShutdown, "A2F05A09-27A2-42B5-BC0E-AC163EF49D9B")

.comdef IApartmentShutdown : public IUnknown

    OnUninitialize	proc :UINT64
   .ends

endif

endif

ASYNC_STGMEDIUM_UserSize proto WINAPI :ptr, :dword, :ptr
ASYNC_STGMEDIUM_UserMarshal proto WINAPI :ptr, :ptr, :ptr
ASYNC_STGMEDIUM_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
ASYNC_STGMEDIUM_UserFree proto WINAPI :ptr, :ptr

CLIPFORMAT_UserSize proto WINAPI :ptr, :dword, :ptr
CLIPFORMAT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserFree proto WINAPI :ptr, :ptr

FLAG_STGMEDIUM_UserSize proto WINAPI :ptr, :dword, :ptr
FLAG_STGMEDIUM_UserMarshal proto WINAPI :ptr, :ptr, :ptr
FLAG_STGMEDIUM_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
FLAG_STGMEDIUM_UserFree proto WINAPI :ptr, :ptr

HBITMAP_UserSize proto WINAPI :ptr, :dword, :ptr
HBITMAP_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserFree proto WINAPI :ptr, :ptr

HDC_UserSize proto WINAPI :ptr, :dword, :ptr
HDC_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HDC_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HDC_UserFree proto WINAPI :ptr, :ptr

HICON_UserSize proto WINAPI :ptr, :dword, :ptr
HICON_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HICON_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HICON_UserFree proto WINAPI :ptr, :ptr

SNB_UserSize proto WINAPI :ptr, :dword, :ptr
SNB_UserMarshal proto WINAPI :ptr, :ptr, :ptr
SNB_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
SNB_UserFree proto WINAPI :ptr, :ptr

STGMEDIUM_UserSize proto WINAPI :ptr, :dword, :ptr
STGMEDIUM_UserMarshal proto WINAPI :ptr, :ptr, :ptr
STGMEDIUM_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
STGMEDIUM_UserFree proto WINAPI :ptr, :ptr

ASYNC_STGMEDIUM_UserSize64 proto WINAPI :ptr, :dword, :ptr
ASYNC_STGMEDIUM_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
ASYNC_STGMEDIUM_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
ASYNC_STGMEDIUM_UserFree64 proto WINAPI :ptr, :ptr

CLIPFORMAT_UserSize64 proto WINAPI :ptr, :dword, :ptr
CLIPFORMAT_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserFree64 proto WINAPI :ptr, :ptr

FLAG_STGMEDIUM_UserSize64 proto WINAPI :ptr, :dword, :ptr
FLAG_STGMEDIUM_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
FLAG_STGMEDIUM_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
FLAG_STGMEDIUM_UserFree64 proto WINAPI :ptr, :ptr

HBITMAP_UserSize64 proto WINAPI :ptr, :dword, :ptr
HBITMAP_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserFree64 proto WINAPI :ptr, :ptr

HDC_UserSize64 proto WINAPI :ptr, :dword, :ptr
HDC_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HDC_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HDC_UserFree64 proto WINAPI :ptr, :ptr

HICON_UserSize64 proto WINAPI :ptr, :dword, :ptr
HICON_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HICON_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HICON_UserFree64 proto WINAPI :ptr, :ptr

SNB_UserSize64 proto WINAPI :ptr, :dword, :ptr
SNB_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
SNB_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
SNB_UserFree64 proto WINAPI :ptr, :ptr

STGMEDIUM_UserSize64 proto WINAPI :ptr, :dword, :ptr
STGMEDIUM_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
STGMEDIUM_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
STGMEDIUM_UserFree64 proto WINAPI :ptr, :ptr

IEnumUnknown_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumUnknown_Next_Stub proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumString_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumString_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr
ISequentialStream_Read_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
ISequentialStream_Read_Stub proto WINAPI :ptr, :ptr, :ULONG, :ptr
ISequentialStream_Write_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
ISequentialStream_Write_Stub proto WINAPI :ptr, :ptr, :ULONG, :ptr
IStream_Seek_Proxy proto WINAPI :ptr, :LARGE_INTEGER, :DWORD, :ptr
IStream_Seek_Stub proto WINAPI :ptr, :LARGE_INTEGER, :DWORD, :ptr
IStream_CopyTo_Proxy proto WINAPI :ptr, :ptr, :ULARGE_INTEGER, :ptr, :ptr
IStream_CopyTo_Stub proto WINAPI :ptr, :ptr, :ULARGE_INTEGER, :ptr, :ptr

IBindCtx_SetBindOptions_Proxy proto WINAPI :ptr, :ptr
IBindCtx_SetBindOptions_Stub proto WINAPI :ptr, :ptr
IBindCtx_GetBindOptions_Proxy proto WINAPI :ptr, :ptr
IBindCtx_GetBindOptions_Stub proto WINAPI :ptr, :ptr

IEnumMoniker_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumMoniker_Next_Stub proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr

IRunnableObject_IsRunning_Proxy proto WINAPI :ptr
IRunnableObject_IsRunning_Stub proto WINAPI :ptr

IMoniker_BindToObject_Proxy proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_BindToObject_Stub proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_BindToStorage_Proxy proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_BindToStorage_Stub proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr

IEnumSTATSTG_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATSTG_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr

IStorage_OpenStream_Proxy proto WINAPI :ptr, :ptr, :ptr, :DWORD, :DWORD, :ptr ptr
IStorage_OpenStream_Stub proto WINAPI :ptr, :ptr, :ULONG, :ptr, :DWORD, :DWORD, :ptr ptr
IStorage_CopyTo_Proxy proto WINAPI :ptr, :DWORD, :ptr, :SNB, :ptr
IStorage_CopyTo_Stub proto WINAPI :ptr, :DWORD, :ptr, :SNB, :ptr
IStorage_EnumElements_Proxy proto WINAPI :ptr, :DWORD, :ptr, :DWORD, :ptr ptr
IStorage_EnumElements_Stub proto WINAPI :ptr, :DWORD, :ULONG, :ptr, :DWORD, :ptr ptr

ILockBytes_ReadAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_ReadAt_Stub proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_WriteAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_WriteAt_Stub proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr

IEnumFORMATETC_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumFORMATETC_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATDATA_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATDATA_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr

IAdviseSink_OnDataChange_Proxy proto WINAPI :ptr, :ptr, :ptr
IAdviseSink_OnDataChange_Stub proto WINAPI :ptr, :ptr, :ptr
IAdviseSink_OnViewChange_Proxy proto WINAPI :ptr, :DWORD, :LONG
IAdviseSink_OnViewChange_Stub proto WINAPI :ptr, :DWORD, :LONG
IAdviseSink_OnRename_Proxy proto WINAPI :ptr, :ptr
IAdviseSink_OnRename_Stub proto WINAPI :ptr, :ptr
IAdviseSink_OnSave_Proxy proto WINAPI :ptr
IAdviseSink_OnSave_Stub proto WINAPI :ptr
IAdviseSink_OnClose_Proxy proto WINAPI :ptr
IAdviseSink_OnClose_Stub proto WINAPI :ptr

AsyncIAdviseSink_Begin_OnDataChange_Proxy proto WINAPI :ptr, :ptr, :ptr
AsyncIAdviseSink_Begin_OnDataChange_Stub proto WINAPI :ptr, :ptr, :ptr
AsyncIAdviseSink_Finish_OnDataChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnDataChange_Stub proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnViewChange_Proxy proto WINAPI :ptr, :DWORD, :LONG
AsyncIAdviseSink_Begin_OnViewChange_Stub proto WINAPI :ptr, :DWORD, :LONG
AsyncIAdviseSink_Finish_OnViewChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnViewChange_Stub proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnRename_Proxy proto WINAPI :ptr, :ptr
AsyncIAdviseSink_Begin_OnRename_Stub proto WINAPI :ptr, :ptr
AsyncIAdviseSink_Finish_OnRename_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnRename_Stub proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnSave_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnSave_Stub proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnSave_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnSave_Stub proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnClose_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnClose_Stub proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnClose_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnClose_Stub proto WINAPI :ptr

IAdviseSink2_OnLinkSrcChange_Proxy proto WINAPI :ptr, :ptr
IAdviseSink2_OnLinkSrcChange_Stub proto WINAPI :ptr, :ptr

AsyncIAdviseSink2_Begin_OnLinkSrcChange_Proxy proto WINAPI :ptr, :ptr
AsyncIAdviseSink2_Begin_OnLinkSrcChange_Stub proto WINAPI :ptr, :ptr
AsyncIAdviseSink2_Finish_OnLinkSrcChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink2_Finish_OnLinkSrcChange_Stub proto WINAPI :ptr

IDataObject_GetData_Proxy proto WINAPI :ptr, :ptr, :ptr
IDataObject_GetData_Stub proto WINAPI :ptr, :ptr, :ptr
IDataObject_GetDataHere_Proxy proto WINAPI :ptr, :ptr, :ptr
IDataObject_GetDataHere_Stub proto WINAPI :ptr, :ptr, :ptr
IDataObject_SetData_Proxy proto WINAPI :ptr, :ptr, :ptr, :BOOL
IDataObject_SetData_Stub proto WINAPI :ptr, :ptr, :ptr, :BOOL

IFillLockBytes_FillAppend_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
IFillLockBytes_FillAppend_Stub proto WINAPI :ptr, :ptr, :ULONG, :ptr
IFillLockBytes_FillAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
IFillLockBytes_FillAt_Stub proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr

endif

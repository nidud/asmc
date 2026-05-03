ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __objidl_h__
define __objidl_h__
ifndef __unknwn_h__
include unknwn.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

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

ifndef _LIMITS_
include limits.inc
endif
ifndef _OBJIDLBASE_
include objidlbase
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IMallocSpy_INTERFACE_DEFINED__
define __IMallocSpy_INTERFACE_DEFINED__

LPMALLOCSPY		typedef ptr IMallocSpy

DEFINE_IIDX(IMallocSpy, "0000001d-0000-0000-C000-000000000046")

.comdef IMallocSpy : public IUnknown

    PreAlloc		proc :size_t
    PostAlloc		proc :ptr
    PreFree		proc :ptr, :BOOL
    PostFree		proc :BOOL
    PreRealloc		proc :ptr, :size_t, :ptr, :BOOL
    PostRealloc		proc :ptr, :BOOL
    PreGetSize		proc :ptr, :BOOL
    PostGetSize		proc :size_t, :BOOL
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

BIND_OPTS		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
BIND_OPTS		ends
LPBIND_OPTS		typedef ptr BIND_OPTS

BIND_OPTS2		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
dwTrackFlags		DWORD ?
dwClassContext		DWORD ?
locale			LCID ?
pServerInfo		ptr COSERVERINFO ?
BIND_OPTS2		ends
LPBIND_OPTS2		typedef ptr BIND_OPTS2

BIND_OPTS3		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
dwTrackFlags		DWORD ?
dwClassContext		DWORD ?
locale			LCID ?
pServerInfo		ptr COSERVERINFO ?
hwnd			HWND ?
BIND_OPTS3		ends
LPBIND_OPTS3		typedef ptr BIND_OPTS3

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
    GetRunningObjectTable proc :ptr
    RegisterObjectParam proc :LPOLESTR, :ptr
    GetObjectParam	proc :LPOLESTR, :ptr
    EnumObjectParam	proc :ptr
    RevokeObjectParam	proc :LPOLESTR
   .ends

endif

ifndef __IEnumMoniker_INTERFACE_DEFINED__
define __IEnumMoniker_INTERFACE_DEFINED__

LPENUMMONIKER		typedef ptr IEnumMoniker

DEFINE_IIDX(IEnumMoniker, "00000102-0000-0000-C000-000000000046")

.comdef IEnumMoniker : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

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

endif

ifndef __IRunningObjectTable_INTERFACE_DEFINED__
define __IRunningObjectTable_INTERFACE_DEFINED__

LPRUNNINGOBJECTTABLE	typedef ptr IRunningObjectTable

DEFINE_IIDX(IRunningObjectTable, "00000010-0000-0000-C000-000000000046")

.comdef IRunningObjectTable : public IUnknown

    Register		proc :DWORD, :ptr, :ptr, :ptr
    Revoke		proc :DWORD
    IsRunning		proc :ptr
    GetObject		proc :ptr, :ptr
    NoteChangeTime	proc :DWORD, :ptr
    GetTimeOfLastChange proc :ptr, :ptr
    EnumRunning		proc :ptr
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

    BindToObject	proc :ptr, :ptr, :REFIID, :ptr
    BindToStorage	proc :ptr, :ptr, :REFIID, :ptr
    Reduce		proc :ptr, :DWORD, :ptr, :ptr
    ComposeWith		proc :ptr, :BOOL, :ptr
    Enum		proc :BOOL, :ptr
    IsEqual		proc :ptr
    Hash		proc :ptr
    IsRunning		proc :ptr, :ptr, :ptr
    GetTimeOfLastChange proc :ptr, :ptr, :ptr
    Inverse		proc :ptr
    CommonPrefixWith	proc :ptr, :ptr
    RelativePathTo	proc :ptr, :ptr
    GetDisplayName	proc :ptr, :ptr, :ptr
    ParseDisplayName	proc :ptr, :ptr, :LPOLESTR, :ptr, :ptr
    IsSystemMoniker	proc :ptr
   .ends

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
    Clone		proc :ptr
   .ends

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

    CreateStream	proc :ptr, :DWORD, :DWORD, :DWORD, :ptr
    OpenStream		proc :ptr, :ptr, :DWORD, :DWORD, :ptr
    CreateStorage	proc :ptr, :DWORD, :DWORD, :DWORD, :ptr
    OpenStorage		proc :ptr, :ptr, :DWORD, :SNB, :DWORD, :ptr
    CopyTo		proc :DWORD, :ptr, :SNB, :ptr
    MoveElementTo	proc :ptr, :ptr, :ptr, :DWORD
    Commit		proc :DWORD
    Revert		proc
    EnumElements	proc :DWORD, :ptr, :DWORD, :ptr
    DestroyElement	proc :ptr
    RenameElement	proc :ptr, :ptr
    SetElementTimes	proc :ptr, :ptr, :ptr, :ptr
    SetClass		proc :REFCLSID
    SetStateBits	proc :DWORD, :DWORD
    Stat		proc :ptr, :DWORD
   .ends

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

endif

ifndef __IEnumFORMATETC_INTERFACE_DEFINED__
define __IEnumFORMATETC_INTERFACE_DEFINED__

LPENUMFORMATETC		typedef ptr IEnumFORMATETC

DVTARGETDEVICE		struct
tdSize			DWORD ?
tdDriverNameOffset	WORD ?
tdDeviceNameOffset	WORD ?
tdPortNameOffset	WORD ?
tdExtDevmodeOffset	WORD ?
tdData			BYTE 1 dup(?)
DVTARGETDEVICE		ends
LPDVTARGETDEVICE	typedef ptr DVTARGETDEVICE

LPCLIPFORMAT		typedef ptr CLIPFORMAT

FORMATETC		struct
cfFormat		CLIPFORMAT ?
ptd			LPDVTARGETDEVICE ?
dwAspect		DWORD ?
lindex			LONG ?
tymed			DWORD ?
FORMATETC		ends
LPFORMATETC		typedef ptr FORMATETC

DEFINE_IIDX(IEnumFORMATETC, "00000103-0000-0000-C000-000000000046")

.comdef IEnumFORMATETC : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

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

STATDATA		struct
formatetc		FORMATETC <>
advf			DWORD ?
pAdvSink		ptr IAdviseSink ?
dwConnection		DWORD ?
STATDATA		ends
LPSTATDATA		typedef ptr STATDATA

DEFINE_IIDX(IEnumSTATDATA, "00000105-0000-0000-C000-000000000046")

.comdef IEnumSTATDATA : public IUnknown
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

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

RemSTGMEDIUM		struct
tymed			DWORD ?
dwHandleType		DWORD ?
pData			ULONG ?
pUnkForRelease		ULONG ?
cbData			ULONG ?
data			byte 1 dup(?)
RemSTGMEDIUM		ends

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

endif

ifndef __AsyncIAdviseSink2_INTERFACE_DEFINED__
define __AsyncIAdviseSink2_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIAdviseSink2, "00000151-0000-0000-C000-000000000046")

.comdef AsyncIAdviseSink2 : public AsyncIAdviseSink

    Begin_OnLinkSrcChange proc :ptr
    Finish_OnLinkSrcChange proc
   .ends

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
    EnumFormatEtc	proc :DWORD, :ptr
    DAdvise		proc :ptr, :DWORD, :ptr, :ptr
    DUnadvise		proc :DWORD
    EnumDAdvise		proc :ptr
   .ends

LPDATAOBJECT		typedef ptr IDataObject

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IDataAdviseHolder_INTERFACE_DEFINED__
define __IDataAdviseHolder_INTERFACE_DEFINED__

DEFINE_IIDX(IDataAdviseHolder, "00000110-0000-0000-C000-000000000046")

.comdef IDataAdviseHolder : public IUnknown

    Advise		proc :ptr, :ptr, :DWORD, :ptr, :ptr
    Unadvise		proc :DWORD
    EnumAdvise		proc :ptr
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
	SERVERCALL_ISHANDLED,
	SERVERCALL_REJECTED,
	SERVERCALL_RETRYLATER
	}

.enum PENDINGTYPE {
	PENDINGTYPE_TOPLEVEL	= 1,
	PENDINGTYPE_NESTED	= 2
	}

.enum PENDINGMSG {
	PENDINGMSG_CANCELCALL,
	PENDINGMSG_WAITNOPROCESS,
	PENDINGMSG_WAITDEFPROCESS
	}

INTERFACEINFO		struct
pUnk			LPUNKNOWN ?
iid			IID <>
wMethod			WORD ?
INTERFACEINFO		ends
LPINTERFACEINFO		typedef ptr INTERFACEINFO

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

    GetClassObject	proc :REFCLSID, :DWORD, :LCID, :REFIID, :ptr
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

    CreateStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr
    OpenStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr
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
	ServerApplication,
	LibraryApplication
	}

.enum ShutdownType {
	IdleShutdown,
	ForcedShutdown
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

endif

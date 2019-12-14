ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
 .err <this stub requires an updated version of rpcndr>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __objidl_h__
__objidl_h__ equ <>

ifndef __IMarshal_FWD_DEFINED__
__IMarshal_FWD_DEFINED__ equ 1
endif
ifndef __IMalloc_FWD_DEFINED__
__IMalloc_FWD_DEFINED__ equ 1
endif
ifndef __IMallocSpy_FWD_DEFINED__
__IMallocSpy_FWD_DEFINED__ equ 1
endif
ifndef __IStdMarshalInfo_FWD_DEFINED__
__IStdMarshalInfo_FWD_DEFINED__ equ 1
endif
ifndef __IExternalConnection_FWD_DEFINED__
__IExternalConnection_FWD_DEFINED__ equ 1
endif
ifndef __IMultiQI_FWD_DEFINED__
__IMultiQI_FWD_DEFINED__ equ 1
endif
ifndef __IEnumUnknown_FWD_DEFINED__
__IEnumUnknown_FWD_DEFINED__ equ 1
endif
ifndef __IBindCtx_FWD_DEFINED__
__IBindCtx_FWD_DEFINED__ equ 1
endif
ifndef __IEnumMoniker_FWD_DEFINED__
__IEnumMoniker_FWD_DEFINED__ equ 1
endif
ifndef __IRunnableObject_FWD_DEFINED__
__IRunnableObject_FWD_DEFINED__ equ 1
endif
ifndef __IRunningObjectTable_FWD_DEFINED__
__IRunningObjectTable_FWD_DEFINED__ equ 1
endif
ifndef __IPersist_FWD_DEFINED__
__IPersist_FWD_DEFINED__ equ 1
endif
ifndef __IPersistStream_FWD_DEFINED__
__IPersistStream_FWD_DEFINED__ equ 1
endif
ifndef __IMoniker_FWD_DEFINED__
__IMoniker_FWD_DEFINED__ equ 1
endif
ifndef __IROTData_FWD_DEFINED__
__IROTData_FWD_DEFINED__ equ 1
endif
ifndef __IEnumString_FWD_DEFINED__
__IEnumString_FWD_DEFINED__ equ 1
endif
ifndef __ISequentialStream_FWD_DEFINED__
__ISequentialStream_FWD_DEFINED__ equ 1
endif
ifndef __IStream_FWD_DEFINED__
__IStream_FWD_DEFINED__ equ 1
endif
ifndef __IEnumSTATSTG_FWD_DEFINED__
__IEnumSTATSTG_FWD_DEFINED__ equ 1
endif
ifndef __IStorage_FWD_DEFINED__
__IStorage_FWD_DEFINED__ equ 1
endif
ifndef __IPersistFile_FWD_DEFINED__
__IPersistFile_FWD_DEFINED__ equ 1
endif
ifndef __IPersistStorage_FWD_DEFINED__
__IPersistStorage_FWD_DEFINED__ equ 1
endif
ifndef __ILockBytes_FWD_DEFINED__
__ILockBytes_FWD_DEFINED__ equ 1
endif
ifndef __IEnumFORMATETC_FWD_DEFINED__
__IEnumFORMATETC_FWD_DEFINED__ equ 1
endif
ifndef __IEnumSTATDATA_FWD_DEFINED__
__IEnumSTATDATA_FWD_DEFINED__ equ 1
endif
ifndef __IRootStorage_FWD_DEFINED__
__IRootStorage_FWD_DEFINED__ equ 1
endif
ifndef __IAdviseSink_FWD_DEFINED__
__IAdviseSink_FWD_DEFINED__ equ 1
endif
ifndef __IAdviseSink2_FWD_DEFINED__
__IAdviseSink2_FWD_DEFINED__ equ 1
endif
ifndef __IDataObject_FWD_DEFINED__
__IDataObject_FWD_DEFINED__ equ 1
endif
ifndef __IDataAdviseHolder_FWD_DEFINED__
__IDataAdviseHolder_FWD_DEFINED__ equ 1
endif
ifndef __IMessageFilter_FWD_DEFINED__
__IMessageFilter_FWD_DEFINED__ equ 1
endif
ifndef __IRpcChannelBuffer_FWD_DEFINED__
__IRpcChannelBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IRpcChannelBuffer2_FWD_DEFINED__
__IRpcChannelBuffer2_FWD_DEFINED__ equ 1
endif
ifndef __IRpcChannelBuffer3_FWD_DEFINED__
__IRpcChannelBuffer3_FWD_DEFINED__ equ 1
endif
ifndef __IRpcProxyBuffer_FWD_DEFINED__
__IRpcProxyBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IRpcStubBuffer_FWD_DEFINED__
__IRpcStubBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IPSFactoryBuffer_FWD_DEFINED__
__IPSFactoryBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IChannelHook_FWD_DEFINED__
__IChannelHook_FWD_DEFINED__ equ 1
endif
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
ifndef __IClientSecurity_FWD_DEFINED__
__IClientSecurity_FWD_DEFINED__ equ 1
endif
ifndef __IServerSecurity_FWD_DEFINED__
__IServerSecurity_FWD_DEFINED__ equ 1
endif
ifndef __IClassActivator_FWD_DEFINED__
__IClassActivator_FWD_DEFINED__ equ 1
endif
ifndef __IRpcOptions_FWD_DEFINED__
__IRpcOptions_FWD_DEFINED__ equ 1
endif
ifndef __IComBinding_FWD_DEFINED__
__IComBinding_FWD_DEFINED__ equ 1
endif
ifndef __IFillLockBytes_FWD_DEFINED__
__IFillLockBytes_FWD_DEFINED__ equ 1
endif
ifndef __IProgressNotify_FWD_DEFINED__
__IProgressNotify_FWD_DEFINED__ equ 1
endif
ifndef __ILayoutStorage_FWD_DEFINED__
__ILayoutStorage_FWD_DEFINED__ equ 1
endif
ifndef __ISurrogate_FWD_DEFINED__
__ISurrogate_FWD_DEFINED__ equ 1
endif
ifndef __IGlobalInterfaceTable_FWD_DEFINED__
__IGlobalInterfaceTable_FWD_DEFINED__ equ 1
endif
ifndef __IDirectWriterLock_FWD_DEFINED__
__IDirectWriterLock_FWD_DEFINED__ equ 1
endif
ifndef __ISynchronize_FWD_DEFINED__
__ISynchronize_FWD_DEFINED__ equ 1
endif
ifndef __ISynchronizeMutex_FWD_DEFINED__
__ISynchronizeMutex_FWD_DEFINED__ equ 1
endif
ifndef __IAsyncSetup_FWD_DEFINED__
__IAsyncSetup_FWD_DEFINED__ equ 1
endif
ifndef __ICancelMethodCalls_FWD_DEFINED__
__ICancelMethodCalls_FWD_DEFINED__ equ 1
endif
ifndef __IAsyncManager_FWD_DEFINED__
__IAsyncManager_FWD_DEFINED__ equ 1
endif
ifndef __IWaitMultiple_FWD_DEFINED__
__IWaitMultiple_FWD_DEFINED__ equ 1
endif
ifndef __ISynchronizeEvent_FWD_DEFINED__
__ISynchronizeEvent_FWD_DEFINED__ equ 1
endif
ifndef __IUrlMon_FWD_DEFINED__
__IUrlMon_FWD_DEFINED__ equ 1
endif
ifndef __IClassAccess_FWD_DEFINED__
__IClassAccess_FWD_DEFINED__ equ 1
endif
ifndef __IClassRefresh_FWD_DEFINED__
__IClassRefresh_FWD_DEFINED__ equ 1
endif
ifndef __IEnumPackage_FWD_DEFINED__
__IEnumPackage_FWD_DEFINED__ equ 1
endif
ifndef __IEnumClass_FWD_DEFINED__
__IEnumClass_FWD_DEFINED__ equ 1
endif
ifndef __IClassAdmin_FWD_DEFINED__
__IClassAdmin_FWD_DEFINED__ equ 1
endif

include unknwn.inc

;void
MIDL_user_free proto WINAPI \
		      : PVOID

SRVINFO			typedef SDWORD
SRVINFO_F_COSERVERINFO	equ 0
SRVINFO_F_COSERVERINFO2 equ 1

LPCOAUTHINFO		typedef ptr COAUTHINFO

COSERVERINFO		STRUC
dwReserved1		dd ?
pwszName		LPWSTR ?
pAuthInfo		LPCOAUTHINFO ?
dwReserved2		dd ?
COSERVERINFO		ENDS

LPIUnknown		typedef ptr IUnknown

COSERVERINFO2		STRUC
dwFlags			dd ?
pwszName		LPWSTR ?
pAuthInfo		LPCOAUTHINFO ?
ppCall			LPIUnknown ?
pwszCodeURL		LPWSTR ?
dwFileVersionMS		dd ?
dwFileVersionLS		dd ?
pwszContentType		LPWSTR ?
COSERVERINFO2		ENDS

ifndef DEFINE_IIDX
DEFINE_IIDX macro name, x
    DEFINE_GUID(IID_&name&, \
	@CatStr(<0x>, @SubStr(x, 2,8)), \
	@CatStr(<0x>, @SubStr(x,11,4)), \
	@CatStr(<0x>, @SubStr(x,16,4)), \
	@CatStr(<0x>, @SubStr(x,21,2)), \
	@CatStr(<0x>, @SubStr(x,23,2)), \
	@CatStr(<0x>, @SubStr(x,26,2)), \
	@CatStr(<0x>, @SubStr(x,28,2)), \
	@CatStr(<0x>, @SubStr(x,30,2)), \
	@CatStr(<0x>, @SubStr(x,32,2)), \
	@CatStr(<0x>, @SubStr(x,34,2)), \
	@CatStr(<0x>, @SubStr(x,36,2)))
	exitm<>
	endm
endif

ifndef __IMarshal_INTERFACE_DEFINED__
__IMarshal_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMarshal, "00000003-0000-0000-C000-000000000046")

.comdef IMarshal : public IUnknown

    GetUnmarshalClass	proc :REFIID, :ptr ,:DWORD, :ptr, :DWORD, :ptr
    GetMarshalSizeMax	proc :REFIID, :ptr ,:DWORD, :ptr, :DWORD, :ptr
    MarshalInterface	proc :ptr, :REFIID, :ptr, :DWORD, :ptr, :DWORD
    UnmarshalInterface	proc :ptr, :REFIID, :ptr
    ReleaseMarshalData	proc :ptr
    DisconnectObject	proc :DWORD

    .ends

LPMARSHAL		typedef ptr IMarshal

endif

DEFINE_IIDX(IMarshal2, "000001cf-0000-0000-C000-000000000046")

.comdef IMarshal2 : public IUnknown

    GetUnmarshalClass	proc :REFIID, :ptr ,:DWORD, :ptr, :DWORD, :ptr
    GetMarshalSizeMax	proc :REFIID, :ptr ,:DWORD, :ptr, :DWORD, :ptr
    MarshalInterface	proc :ptr, :REFIID, :ptr, :DWORD, :ptr, :DWORD
    UnmarshalInterface	proc :ptr, :REFIID, :ptr
    ReleaseMarshalData	proc :ptr
    DisconnectObject	proc :DWORD

    .ends

LPMARSHAL2		typedef ptr IMarshal2

ifndef __IMalloc_INTERFACE_DEFINED__
__IMalloc_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMalloc, "00000002-0000-0000-C000-000000000046")

.comdef IMalloc : public IUnknown

    Alloc		proc :DWORD
    Realloc		proc :ptr ,:DWORD
    Free		proc :ptr
    GetSize		proc :ptr
    DidAlloc		proc :ptr
    HeapMinimize	proc

    .ends

LPMALLOC		typedef ptr IMalloc

endif


ifndef __IMallocSpy_INTERFACE_DEFINED__
__IMallocSpy_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMallocSpy, "0000001d-0000-0000-C000-000000000046")

.comdef IMallocSpy : public IUnknown

    PreAlloc		proc :DWORD
    PostAlloc		proc :ptr
    PreFree		proc :ptr, :BOOL
    PostFree		proc :BOOL
    PreRealloc		proc :ptr, :DWORD, :ptr, :BOOL
    PostRealloc		proc :ptr, :BOOL
    PreGetSize		proc :ptr, :BOOL
    PostGetSize		proc :DWORD, :BOOL
    PreDidAlloc		proc :ptr, :BOOL
    PostDidAlloc	proc :ptr, :BOOL, :DWORD
    PreHeapMinimize	proc
    PostHeapMinimize	proc

    .ends

LPMALLOCSPY		typedef ptr IMallocSpy

endif

ifndef __IStdMarshalInfo_INTERFACE_DEFINED__
__IStdMarshalInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IStdMarshalInfo, "00000018-0000-0000-C000-000000000046")

.comdef IStdMarshalInfo : public IUnknown

    GetClassForHandler	proc :DWORD, :ptr, :ptr

    .ends

LPSTDMARSHALINFO	typedef ptr IStdMarshalInfo

endif

ifndef __IExternalConnection_INTERFACE_DEFINED__
__IExternalConnection_INTERFACE_DEFINED__ equ 1

tagEXTCONN		typedef SDWORD
EXTCONN_STRONG		equ 0x1
EXTCONN_WEAK		equ 0x2
EXTCONN_CALLABLE	equ 0x4

DEFINE_IIDX(IExternalConnection, "00000019-0000-0000-C000-000000000046")

.comdef IExternalConnection : public IUnknown

    AddConnection	proc :DWORD, :DWORD
    ReleaseConnection	proc :DWORD, :DWORD, :BOOL

    .ends

LPEXTERNALCONNECTION	typedef ptr IExternalConnection

endif

ifndef __IMultiQI_INTERFACE_DEFINED__
__IMultiQI_INTERFACE_DEFINED__ equ 1

MULTI_QI		STRUC
pIID			LPIID ?
pItf			LPIUnknown ?
hr			HRESULT ?
MULTI_QI		ENDS

DEFINE_IIDX(IMultiQI, "00000020-0000-0000-C000-000000000046")

.comdef IMultiQI : public IUnknown

    QueryMultipleInterfaces proc :DWORD, :ptr

    .ends

LPMULTIQI		typedef ptr IMultiQI

endif

DEFINE_IIDX(AsyncIMultiQI, "000e0020-0000-0000-C000-000000000046")

.comdef AsyncIMultiQI : public IUnknown

    Begin_QueryMultipleInterfaces proc :ULONG, :ptr MULTI_QI
    Finish_QueryMultipleInterfaces proc :ptr MULTI_QI

    .ends

DEFINE_IIDX(IInternalUnknown, "00000021-0000-0000-C000-000000000046")

.comdef IInternalUnknown : public IUnknown

    QueryInternalInterface proc :REFIID, :ptr

    .ends

ifndef __IEnumUnknown_INTERFACE_DEFINED__
__IEnumUnknown_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumUnknown, "00000100-0000-0000-C000-000000000046")

.comdef IEnumUnknown : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr

    .ends

LPENUMUNKNOWN		typedef ptr IEnumUnknown

endif

ifndef __IBindCtx_INTERFACE_DEFINED__
__IBindCtx_INTERFACE_DEFINED__ equ 1

BIND_OPTS		STRUC
cbStruct		dd ?
grfFlags		dd ?
grfMode			dd ?
dwTickCountDeadline	dd ?
BIND_OPTS		ENDS
LPBIND_OPTS		typedef ptr BIND_OPTS

LPCOSERVERINFO		typedef ptr COSERVERINFO

BIND_OPTS2		STRUC
cbStruct		dd ?
grfFlags		dd ?
grfMode			dd ?
dwTickCountDeadline	dd ?
dwTrackFlags		dd ?
dwClassContext		dd ?
locale			LCID ?
pServerInfo		LPCOSERVERINFO ?
BIND_OPTS2		ENDS
LPBIND_OPTS2		typedef ptr BIND_OPTS2

tagBIND_FLAGS		typedef SDWORD
BIND_MAYBOTHERUSER	equ 1
BIND_JUSTTESTEXISTENCE	equ 2

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

LPBC			typedef ptr IBindCtx
LPBINDCTX		typedef ptr IBindCtx

endif

ifndef __IEnumMoniker_INTERFACE_DEFINED__
__IEnumMoniker_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumMoniker, "00000102-0000-0000-C000-000000000046")

.comdef IEnumMoniker : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr

    .ends

LPENUMMONIKER		typedef ptr IEnumMoniker

endif

ifndef __IRunnableObject_INTERFACE_DEFINED__
__IRunnableObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRunnableObject, "00000126-0000-0000-C000-000000000046")

.comdef IRunnableObject : public IUnknown

    GetRunningClass	proc :LPCLSID
    Run			proc :LPBINDCTX
    IsRunning		proc
    LockRunning		proc :BOOL, :BOOL
    SetContainedObject	proc :BOOL

    .ends

LPRUNNABLEOBJECT	typedef ptr IRunnableObject

endif

ifndef __IRunningObjectTable_INTERFACE_DEFINED__
__IRunningObjectTable_INTERFACE_DEFINED__ equ 1

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

LPRUNNINGOBJECTTABLE	typedef ptr IRunningObjectTable

endif

ifndef __IPersist_INTERFACE_DEFINED__
__IPersist_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersist, "0000010c-0000-0000-C000-000000000046")

.comdef IPersist : public IUnknown

    GetClassID		proc :ptr

    .ends

LPPERSIST		typedef ptr IPersist

endif

ifndef __IPersistStream_INTERFACE_DEFINED__
__IPersistStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistStream, "00000109-0000-0000-C000-000000000046")

.comdef IPersistStream : public IUnknown

    GetClassID		proc :ptr
    IsDirty		proc
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    GetSizeMax		proc :ptr

    .ends

LPPERSISTSTREAM		typedef ptr IPersistStream

endif

ifndef __IMoniker_INTERFACE_DEFINED__
__IMoniker_INTERFACE_DEFINED__ equ 1

tagMKSYS		typedef SDWORD
MKSYS_NONE		equ 0
MKSYS_GENERICCOMPOSITE	equ 1
MKSYS_FILEMONIKER	equ 2
MKSYS_ANTIMONIKER	equ 3
MKSYS_ITEMMONIKER	equ 4
MKSYS_POINTERMONIKER	equ 5
MKSYS_CLASSMONIKER	equ 7

tagMKREDUCE		typedef SDWORD
MKRREDUCE_ONE		equ 3 SHL 16
MKRREDUCE_TOUSER	equ 2 SHL 16
MKRREDUCE_THROUGHUSER	equ 1 SHL 16
MKRREDUCE_ALL		equ 0

DEFINE_IIDX(IMoniker, "0000000f-0000-0000-C000-000000000046")

.comdef IMoniker : public IUnknown

    GetClassID		proc :ptr
    IsDirty		proc
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    GetSizeMax		proc :ptr
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

LPMONIKER		typedef ptr IMoniker

endif

ifndef __IROTData_INTERFACE_DEFINED__
__IROTData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IROTData, "f29f6bc0-5021-11ce-aa15-00006901293f")

.comdef IROTData : public IUnknown

    GetComparisonData	proc :ptr, :DWORD, :ptr

    .ends

endif

ifndef __IEnumString_INTERFACE_DEFINED__
__IEnumString_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumString, "00000101-0000-0000-C000-000000000046")

.comdef IEnumString : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr

    .ends

LPENUMSTRING		typedef ptr IEnumString

endif

ifndef __ISequentialStream_INTERFACE_DEFINED__
__ISequentialStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISequentialStream, "0c733a30-2a1c-11ce-ade5-00aa0044773d")

.comdef ISequentialStream : public IUnknown

    Read		proc :ptr, :DWORD, :ptr
    Write		proc :ptr, :DWORD, :ptr

    .ends

endif

ifndef __IStream_INTERFACE_DEFINED__
__IStream_INTERFACE_DEFINED__ equ 1

STATSTG			STRUC
pwcsName		LPOLESTR ?
type			dd ?
cbSize			ULARGE_INTEGER <>
mtime			FILETIME <>
ctime			FILETIME <>
atime			FILETIME <>
grfMode			dd ?
grfLocksSupported	dd ?
clsid			CLSID <>
grfStateBits		dd ?
reserved		dd ?
STATSTG			ENDS

STGTY			typedef SDWORD
STGTY_STORAGE		equ 1
STGTY_STREAM		equ 2
STGTY_LOCKBYTES		equ 3
STGTY_PROPERTY		equ 4

STREAM_SEEK		typedef SDWORD
STREAM_SEEK_SET		equ 0
STREAM_SEEK_CUR		equ 1
STREAM_SEEK_END		equ 2

LOCKTYPE		typedef SDWORD
LOCK_WRITE		equ 1
LOCK_EXCLUSIVE		equ 2
LOCK_ONLYONCE		equ 4

DEFINE_IIDX(IStream, "0000000c-0000-0000-C000-000000000046")

.comdef IStream : public IUnknown

    Read		proc :ptr, :DWORD, :ptr
    Write		proc :ptr, :DWORD, :ptr
    Seek		proc :LARGE_INTEGER, :DWORD, :ptr
    SetSize		proc :ULARGE_INTEGER
    CopyTo		proc :ptr, :ULARGE_INTEGER, :ptr, :ptr
    Commit		proc :DWORD
    Revert		proc
    LockRegion		proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    UnlockRegion	proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    Stat		proc :ptr, :DWORD
    Clone		proc :ptr

    .ends

LPSTREAM		typedef ptr IStream

endif

ifndef __IEnumSTATSTG_INTERFACE_DEFINED__
__IEnumSTATSTG_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumSTATSTG, "0000000d-0000-0000-C000-000000000046")

.comdef IEnumSTATSTG : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr

    .ends

LPENUMSTATSTG		typedef ptr IEnumSTATSTG

endif

ifndef __IStorage_INTERFACE_DEFINED__
__IStorage_INTERFACE_DEFINED__ equ 1

RemSNB			STRUC
ulCntStr		dd ?
ulCntChar		dd ?
rgString		OLECHAR ?
RemSNB			ENDS

wireSNB			typedef ptr RemSNB
SNB			typedef ptr OLECHAR

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

LPSTORAGE		typedef ptr IStorage

endif

ifndef __IPersistFile_INTERFACE_DEFINED__
__IPersistFile_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IPersistFile,	0x0000010b,0,0,0xC0,0,0,0,0,0,0,0x46)

.comdef IPersistFile : public IUnknown

    GetClassID		proc :ptr
    IsDirty		proc
    Load		proc :LPCOLESTR, :DWORD
    Save		proc :LPCOLESTR, :BOOL
    SaveCompleted	proc :LPCOLESTR
    GetCurFile		proc :ptr

    .ends

LPPERSISTFILE		typedef ptr IPersistFile

endif

ifndef __IPersistStorage_INTERFACE_DEFINED__
__IPersistStorage_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistStorage, "0000010a-0000-0000-C000-000000000046")

.comdef IPersistStorage : public IUnknown

    GetClassID		proc :ptr
    IsDirty		proc
    InitNew		proc :ptr
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    SaveCompleted	proc :ptr
    HandsOffStorage	proc

    .ends

LPPERSISTSTORAGE	typedef ptr IPersistStorage

endif

ifndef __ILockBytes_INTERFACE_DEFINED__
__ILockBytes_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ILockBytes, "0000000a-0000-0000-C000-000000000046")

.comdef ILockBytes : public IUnknown

    ReadAt		proc :ULARGE_INTEGER, :ptr, :DWORD, :ptr
    WriteAt		proc :ULARGE_INTEGER, :ptr, :DWORD, :ptr
    Flush		proc
    SetSize		proc :ULARGE_INTEGER
    LockRegion		proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    UnlockRegion	proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    Stat		proc :ptr, :DWORD

    .ends

LPLOCKBYTES		typedef ptr ILockBytes

endif

ifndef __IEnumFORMATETC_INTERFACE_DEFINED__
__IEnumFORMATETC_INTERFACE_DEFINED__ equ 1

DVTARGETDEVICE		STRUC
tdSize			dd ?
tdDriverNameOffset	dw ?
tdDeviceNameOffset	dw ?
tdPortNameOffset	dw ?
tdExtDevmodeOffset	dw ?
tdData			db ?
DVTARGETDEVICE		ENDS
LPDVTARGETDEVICE	typedef ptr DVTARGETDEVICE

LPCLIPFORMAT		typedef ptr CLIPFORMAT

FORMATETC		STRUC
cfFormat		CLIPFORMAT ?
ptd			LPDVTARGETDEVICE ?
dwAspect		dd ?
lindex			LONG ?
tymed			dd ?
FORMATETC		ENDS
LPFORMATETC		typedef ptr FORMATETC

DEFINE_IIDX(IEnumFORMATETC, "00000103-0000-0000-C000-000000000046")

.comdef IEnumFORMATETC : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr

    .ends

LPENUMFORMATETC		typedef ptr IEnumFORMATETC

endif

ifndef __IEnumSTATDATA_INTERFACE_DEFINED__
__IEnumSTATDATA_INTERFACE_DEFINED__ equ 1

ADVF			typedef SDWORD
ADVF_NODATA		equ 1
ADVF_PRIMEFIRST		equ 2
ADVF_ONLYONCE		equ 4
ADVF_DATAONSTOP		equ 64
ADVFCACHE_NOHANDLER	equ 8
ADVFCACHE_FORCEBUILTIN	equ 16
ADVFCACHE_ONSAVE	equ 32

LPIAdviseSink		typedef ptr IAdviseSink

STATDATA		STRUC
formatetc		FORMATETC <>
advf			dd ?
pAdvSink		LPIAdviseSink ?
dwConnection		dd ?
STATDATA		ENDS
LPSTATDATA		typedef ptr STATDATA

DEFINE_IIDX(IEnumSTATDATA, "00000105-0000-0000-C000-000000000046")

.comdef IEnumSTATDATA : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr

    .ends

LPENUMSTATDATA		typedef ptr IEnumSTATDATA

endif

ifndef __IRootStorage_INTERFACE_DEFINED__
__IRootStorage_INTERFACE_DEFINED__ equ 1

.comdef IRootStorage : public IUnknown

    SwitchToFile	proc :LPOLESTR

    .ends

LPROOTSTORAGE		typedef ptr IRootStorage

DEFINE_IIDX(IRootStorage, "00000012-0000-0000-C000-000000000046")

endif

ifndef __IAdviseSink_INTERFACE_DEFINED__
__IAdviseSink_INTERFACE_DEFINED__ equ 1

TYMED			typedef SDWORD
TYMED_HGLOBAL		equ 1
TYMED_FILE		equ 2
TYMED_ISTREAM		equ 4
TYMED_ISTORAGE		equ 8
TYMED_GDI		equ 16
TYMED_MFPICT		equ 32
TYMED_ENHMF		equ 64
TYMED_NULL		equ 0

RemSTGMEDIUM		STRUC
tymed			dd ?
dwHandleType		dd ?
pData			dd ?
pUnkForRelease		dd ?
cbData			dd ?
data_			db ?
RemSTGMEDIUM		ENDS

ifdef NONAMELESSUNION
uSTGMEDIUM		STRUC
tymed			dd ?
UNION u
 hBitmap		HBITMAP ?
 hMetaFilePict		HMETAFILEPICT ?
 hEnhMetaFile		HENHMETAFILE ?
 hGlobal		HGLOBAL ?
 lpszFileName		LPOLESTR ?
 pstm			LPIStream ?
 pstg			LPIStorage ?
ENDS
pUnkForRelease		LPIUnknown ?
uSTGMEDIUM		ENDS
else
LPIStream		typedef ptr IStream
LPIStorage		typedef ptr IStorage
uSTGMEDIUM		STRUC
tymed			dd ?
UNION ;u
 hBitmap		HBITMAP ?
 hMetaFilePict		HMETAFILEPICT ?
 hEnhMetaFile		HENHMETAFILE ?
 hGlobal		HGLOBAL ?
 lpszFileName		LPOLESTR ?
 pstm			LPIStream ?
 pstg			LPIStorage ?
ENDS
pUnkForRelease		LPIUnknown ?
uSTGMEDIUM		ENDS
endif

GDI_OBJECT		STRUC
ObjectType		dd ?
UNION u
 hBitmap		wireHBITMAP ?
 hPalette		wireHPALETTE ?
ENDS
GDI_OBJECT		ENDS

LPGDI_OBJECT		typedef ptr GDI_OBJECT

userSTGMEDIUM		STRUC
STRUC STGMEDIUM_UNION
 tymed			dd ?
 UNION u
  hMetaFilePict		wireHMETAFILEPICT ?
  hHEnhMetaFile		wireHENHMETAFILE ?
  hGdiHandle		LPGDI_OBJECT ?
  hGlobal		wireHGLOBAL ?
  lpszFileName		LPOLESTR ?
  pstm			LPBYTE ?
  pstg			LPBYTE ?
 ENDS
ENDS
pUnkForRelease		LPIUnknown ?
userSTGMEDIUM		ENDS

wireSTGMEDIUM		typedef ptr userSTGMEDIUM
STGMEDIUM		typedef uSTGMEDIUM
wireASYNC_STGMEDIUM	typedef ptr userSTGMEDIUM
ASYNC_STGMEDIUM		typedef STGMEDIUM
LPSTGMEDIUM		typedef ptr STGMEDIUM

userFLAG_STGMEDIUM	STRUC
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			userSTGMEDIUM <>
userFLAG_STGMEDIUM	ENDS
wireFLAG_STGMEDIUM	typedef ptr userFLAG_STGMEDIUM

FLAG_STGMEDIUM		STRUC
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			STGMEDIUM <>
FLAG_STGMEDIUM		ENDS

DEFINE_IIDX(IAdviseSink, "0000010f-0000-0000-C000-000000000046")

.comdef IAdviseSink : public IUnknown

    OnDataChange	proc :ptr, :ptr
    OnViewChange	proc :DWORD, :SDWORD
    OnRename		proc :ptr
    OnSave		proc
    OnClose		proc

    .ends

LPADVISESINK		typedef ptr IAdviseSink

endif

DEFINE_IIDX(AsyncIAdviseSink, "00000150-0000-0000-C000-000000000046")

.comdef AsyncIAdviseSink : public IUnknown

    Begin_OnDataChange	proc :ptr FORMATETC, :ptr STGMEDIUM
    Finish_OnDataChange proc
    Begin_OnViewChange	proc :DWORD, :LONG
    Finish_OnViewChange proc
    Begin_OnRename	proc :ptr IMoniker
    Finish_OnRename	proc
    Begin_OnSave	proc
    Finish_OnSave	proc
    Begin_OnClose	proc
    Finish_OnClose	proc

    .ends

ifndef __IAdviseSink2_INTERFACE_DEFINED__
__IAdviseSink2_INTERFACE_DEFINED__ equ 1

.comdef IAdviseSink2 : public IUnknown

    OnDataChange	proc :ptr, :ptr
    OnViewChange	proc :DWORD, :SDWORD
    OnRename		proc :ptr
    OnSave		proc
    OnClose		proc
    OnLinkSrcChange	proc :ptr

    .ends

LPADVISESINK2		typedef ptr IAdviseSink2

DEFINE_IIDX(IAdviseSink2, "00000125-0000-0000-C000-000000000046")

endif

DEFINE_IIDX(AsyncIAdviseSink2, "00000151-0000-0000-C000-000000000046")

.comdef AsyncIAdviseSink2 : public IUnknown

    Begin_OnDataChange	proc :ptr FORMATETC, :ptr STGMEDIUM
    Finish_OnDataChange proc
    Begin_OnViewChange	proc :DWORD, :LONG
    Finish_OnViewChange proc
    Begin_OnRename	proc :ptr IMoniker
    Finish_OnRename	proc
    Begin_OnSave	proc
    Finish_OnSave	proc
    Begin_OnClose	proc
    Finish_OnClose	proc
    Begin_OnLinkSrcChange proc :ptr IMoniker
    Finish_OnLinkSrcChange proc

    .ends

ifndef __IDataObject_INTERFACE_DEFINED__
__IDataObject_INTERFACE_DEFINED__ equ 1

DATADIR			typedef SDWORD
DATADIR_GET		equ 1
DATADIR_SET		equ 2

DEFINE_IIDX(IDataObject, "0000010e-0000-0000-C000-000000000046")

.comdef IDataObject : public IUnknown

    GetData		proc :ptr, :ptr
    GetDataHere		proc :ptr, :ptr
    QueryGetData	proc :ptr
    GetCanonicalFormatEtc proc :ptr, :ptr
    SetData		proc :ptr, :ptr, :BOOL
    EnumFormatEtc	proc :dword, :ptr ptr
    DAdvise		proc :ptr, :dword, :ptr, :ptr
    DUnadvise		proc :DWORD
    EnumDAdvise		proc :ptr ptr

    .ends

LPDATAOBJECT		typedef ptr IDataObject

endif

ifndef __IDataAdviseHolder_INTERFACE_DEFINED__
__IDataAdviseHolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDataAdviseHolder, "00000110-0000-0000-C000-000000000046")

.comdef IDataAdviseHolder : public IUnknown

    Advise		proc :ptr IDataObject, :ptr FORMATETC, :DWORD, :ptr IAdviseSink, :ptr DWORD
    Unadvise		proc :DWORD
    EnumAdvise		proc :ptr ptr IEnumSTATDATA
    SendOnDataChange	proc :ptr IDataObject, :DWORD, :DWORD

    .ends

LPDATAADVISEHOLDER	typedef ptr IDataAdviseHolder

endif

ifndef __IMessageFilter_INTERFACE_DEFINED__
__IMessageFilter_INTERFACE_DEFINED__ equ 1

CALLTYPE		typedef SDWORD
CALLTYPE_TOPLEVEL		equ 1
CALLTYPE_NESTED			equ 2
CALLTYPE_ASYNC			equ 3
CALLTYPE_TOPLEVEL_CALLPENDING	equ 4
CALLTYPE_ASYNC_CALLPENDING	equ 5

SERVERCALL		typedef SDWORD
SERVERCALL_ISHANDLED		equ 0
SERVERCALL_REJECTED		equ 1
SERVERCALL_RETRYLATER		equ 2

PENDINGTYPE		typedef SDWORD
PENDINGTYPE_TOPLEVEL		equ 1
PENDINGTYPE_NESTED		equ 2

PENDINGMSG		typedef SDWORD
PENDINGMSG_CANCELCALL		equ 0
PENDINGMSG_WAITNOPROCESS	equ 1
PENDINGMSG_WAITDEFPROCESS	equ 2

INTERFACEINFO		STRUC
pUnk			LPIUnknown ?
iid			IID <>
wMethod			dw ?
INTERFACEINFO		ENDS
LPINTERFACEINFO		typedef ptr INTERFACEINFO

DEFINE_IIDX(IMessageFilter, "00000016-0000-0000-C000-000000000046")

.comdef IMessageFilter : public IUnknown

    HandleInComingCall	proc :DWORD, :HTASK, :DWORD, :LPINTERFACEINFO
    RetryRejectedCall	proc :HTASK, :DWORD, :DWORD
    MessagePending	proc :HTASK, :DWORD, :DWORD

    .ends

LPMESSAGEFILTER		typedef ptr IMessageFilter

endif

ifndef __IRpcChannelBuffer_INTERFACE_DEFINED__
__IRpcChannelBuffer_INTERFACE_DEFINED__ equ 1

RPCOLEDATAREP		typedef DWORD

RPCOLEMESSAGE		STRUC
reserved1		PVOID ?
dataRepresentation	RPCOLEDATAREP ?
Buffer			PVOID ?
cbBuffer		ULONG ?
iMethod			ULONG ?
reserved2		PVOID 5 dup(?)
rpcFlags		ULONG ?
RPCOLEMESSAGE		ENDS

PRPCOLEMESSAGE		typedef ptr RPCOLEMESSAGE

DEFINE_IIDX(IRpcChannelBuffer, "D5F56B60-593B-101A-B569-08002B2DBF7A")

.comdef IRpcChannelBuffer : public IUnknown

    GetBuffer		proc :ptr, :REFIID
    SendReceive		proc :ptr, :ptr
    FreeBuffer		proc :ptr
    GetDestCtx		proc :ptr, :ptr
    IsConnected		proc

    .ends

endif

ifndef __IRpcChannelBuffer2_INTERFACE_DEFINED__
__IRpcChannelBuffer2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcChannelBuffer2, "594f31d0-7f19-11d0-b194-00a0c90dc8bf")

.comdef IRpcChannelBuffer2 : public IUnknown

    GetBuffer		proc :ptr, :REFIID
    SendReceive		proc :ptr, :ptr
    FreeBuffer		proc :ptr
    GetDestCtx		proc :ptr, :ptr
    IsConnected		proc
    GetProtocolVersion	proc :ptr

    .ends

endif

DEFINE_IIDX(IAsyncRpcChannelBuffer, "a5029fb6-3c34-11d1-9c99-00c04fb998aa")

.comdef IAsyncRpcChannelBuffer : public IUnknown

    GetBuffer		proc :ptr, :REFIID
    SendReceive		proc :ptr, :ptr
    FreeBuffer		proc :ptr
    GetDestCtx		proc :ptr, :ptr
    IsConnected		proc
    GetProtocolVersion	proc :ptr
    Send		proc :ptr RPCOLEMESSAGE, :ptr ISynchronize, :ptr ULONG
    Receive		proc :ptr RPCOLEMESSAGE, :ptr ULONG
    GetDestCtxEx	proc :ptr RPCOLEMESSAGE, :ptr DWORD, :ptr

    .ends

ifndef __IRpcChannelBuffer3_INTERFACE_DEFINED__
__IRpcChannelBuffer3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcChannelBuffer3, "25B15600-0115-11d0-BF0D-00AA00B8DFD2")

.comdef IRpcChannelBuffer3 : public IUnknown

    GetBuffer		proc :ptr, :REFIID
    SendReceive		proc :ptr, :ptr
    FreeBuffer		proc :ptr
    GetDestCtx		proc :ptr, :ptr
    IsConnected		proc
    GetProtocolVersion	proc :ptr
    Send		proc :ptr, :ptr
    Receive		proc :ptr, :DWORD, :ptr
    Cancel		proc :ptr
    GetCallContext	proc :ptr, :REFIID, :ptr
    GetDestCtxEx	proc :ptr, :ptr, :ptr
    GetState		proc :ptr, :ptr
    RegisterAsync	proc :ptr, :ptr

    .ends

endif

DEFINE_IIDX(IRpcSyntaxNegotiate, "58a08519-24c8-4935-b482-3fd823333a4f")

.comdef IRpcSyntaxNegotiate : public IUnknown

    NegotiateSyntax	proc :ptr RPCOLEMESSAGE

    .ends

ifndef __IRpcProxyBuffer_INTERFACE_DEFINED__
__IRpcProxyBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcProxyBuffer, "D5F56A34-593B-101A-B569-08002B2DBF7A")

.comdef IRpcProxyBuffer : public IUnknown

    Connect		proc :ptr
    Disconnect		proc

    .ends

endif

ifndef __IRpcStubBuffer_INTERFACE_DEFINED__
__IRpcStubBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcStubBuffer, "D5F56AFC-593B-101A-B569-08002B2DBF7A")

.comdef IRpcStubBuffer : public IUnknown

    Connect		proc :ptr
    Disconnect		proc
    _Invoke		proc :ptr, :ptr
    IsIIDSupported	proc :REFIID
    CountRefs		proc
    DebugServerQueryInterface proc :ptr
    DebugServerRelease	proc :ptr

    .ends

CALLBACK(IRpcStubBuffer_IsIIDSupported_Proxy, :ptr IRpcStubBuffer, :REFIID)

endif

ifndef __IPSFactoryBuffer_INTERFACE_DEFINED__
__IPSFactoryBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPSFactoryBuffer, "D5F569D0-593B-101A-B569-08002B2DBF7A")

.comdef IPSFactoryBuffer : public IUnknown

    CreateProxy		proc :ptr, :REFIID, :ptr, :ptr
    CreateStub		proc :REFIID, :ptr, :ptr

    .ends

endif

if  (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)
SChannelHookCallInfo	STRUC
iid			IID <>
cbSize			dd ?
uCausality		GUID <>
dwServerPid		dd ?
iMethod			dd ?
pObject			PVOID ?
SChannelHookCallInfo	ENDS

ifndef __IChannelHook_INTERFACE_DEFINED__
__IChannelHook_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IChannelHook, "1008c4a0-7613-11cf-9af1-0020af6e72f4")

.comdef IChannelHook : public IUnknown

    ClientGetSize	proc :REFGUID, :REFIID, :ptr
    ClientFillBuffer	proc :REFGUID, :REFIID, :ptr, :ptr
    ClientNotify	proc :REFGUID, :REFIID, :DWORD, :ptr, :DWORD, :HRESULT
    ServerNotify	proc :REFGUID, :REFIID, :DWORD, :ptr, :DWORD
    ServerGetSize	proc :REFGUID, :REFIID, :HRESULT, :ptr
    ServerFillBuffer	proc :REFGUID, :REFIID, :ptr, :ptr, :HRESULT

    .ends

endif
endif

ifndef __IPropertyStorage_INTERFACE_DEFINED__
__IPropertyStorage_INTERFACE_DEFINED__ equ 1

externdef		FMTID_SummaryInformation:FMTID
externdef		FMTID_DocSummaryInformation:FMTID
externdef		FMTID_UserDefinedProperties:FMTID

PROPSETFLAG_DEFAULT	equ 0
PROPSETFLAG_NONSIMPLE	equ 1
PROPSETFLAG_ANSI	equ 2

PROPSETFLAG_UNBUFFERED	equ 4

CAUB			STRUC
cElems			ULONG ?
pElems			LPBYTE ?
CAUB			ENDS

LPSWORD			typedef ptr SWORD

CAI			STRUC
cElems			ULONG ?
pElems			PSHORT ?
CAI			ENDS

CAUI			STRUC
cElems			ULONG ?
pElems			LPWORD ?
CAUI			ENDS

CAL			STRUC
cElems			ULONG ?
pElems			LPLONG ?
CAL			ENDS

CAUL			STRUC
cElems			ULONG ?
pElems			LPDWORD ?
CAUL			ENDS

LPFLOAT			typedef ptr REAL4
CAFLT			STRUC
cElems			ULONG ?
pElems			LPFLOAT ?
CAFLT			ENDS

LPDOUBLE		typedef ptr DOUBLE

CADBL			STRUC
cElems			ULONG ?
pElems			LPDOUBLE ?
CADBL			ENDS

CACY			STRUC
cElems			ULONG ?
pElems			LPCY ?
CACY			ENDS

LPDATE			typedef ptr DATE

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

LPVARIANT_BOOL		typedef ptr VARIANT_BOOL
CABOOL			STRUC
cElems			ULONG ?
pElems			LPVARIANT_BOOL ?
CABOOL			ENDS

LPSCODE			typedef ptr SCODE
CASCODE			STRUC
cElems			ULONG ?
pElems			LPSCODE ?
CASCODE			ENDS

LPPROPVARIANT		typedef ptr PROPVARIANT
CAPROPVARIANT		STRUC
cElems			ULONG ?
pElems			LPPROPVARIANT ?
CAPROPVARIANT		ENDS

LPLARGE_INTEGER		typedef ptr LARGE_INTEGER
CAH			STRUC
cElems			ULONG ?
pElems			LPLARGE_INTEGER ?
CAH			ENDS

LPULARGE_INTEGER	typedef ptr ULARGE_INTEGER
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

LPCLIPDATA		typedef ptr CLIPDATA
CACLIPDATA		STRUC
cElems			ULONG ?
pElems			LPCLIPDATA ?
CACLIPDATA		ENDS

CACLSID			STRUC
cElems			ULONG ?
pElems			LPCLSID ?
CACLSID			ENDS

PROPVARIANT		STRUC
vt			VARTYPE ?
wReserved1		dw ?
wReserved2		dw ?
wReserved3		dw ?
UNION
bVal			db ?
iVal			sword ?
uiVal			dw ?
boolVal			VARIANT_BOOL ?
bool			VARIANT_BOOL ?
lVal			LONG ?
ulVal			ULONG ?
fltVal			REAL4 ?
scode			SCODE ?
hVal			LARGE_INTEGER <>
uhVal			ULARGE_INTEGER <>
dblVal			DOUBLE ?
cyVal			CY <>
date			DATE ?
filetime		FILETIME <>
puuid			LPCLSID ?
blob			BLOB <>
pclipdata		LPCLIPDATA ?
pStream			LPIStream ?
pStorage		LPIStorage ?
bstrVal			BSTR ?
bstrblobVal		BSTRBLOB <>
pszVal			LPSTR ?
pwszVal			LPWSTR ?
caub			CAUB <>
cai			CAI <>
caui			CAUI <>
cabool			CABOOL <>
cal			CAL <>
caul			CAUL <>
caflt			CAFLT <>
cascode			CASCODE <>
cah			CAH <>
cauh			CAUH <>
cadbl			CADBL <>
cacy			CACY <>
cadate			CADATE <>
cafiletime		CAFILETIME <>
cauuid			CACLSID <>
caclipdata		CACLIPDATA <>
cabstr			CABSTR <>
cabstrblob		CABSTRBLOB <>
calpstr			CALPSTR <>
calpwstr		CALPWSTR <>
capropvar		CAPROPVARIANT <>
ENDS
PROPVARIANT		ENDS

LPPROPVARIANT		typedef ptr PROPVARIANT

PID_DICTIONARY		equ 0
PID_CODEPAGE		equ 0x1
PID_FIRST_USABLE	equ 0x2
PID_FIRST_NAME_DEFAULT	equ 0xfff
PID_LOCALE		equ 0x80000000
PID_MODIFY_TIME		equ 0x80000001
PID_SECURITY		equ 0x80000002
PID_ILLEGAL		equ 0xffffffff


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
PRSPEC_INVALID		equ 0xffffffff

PRSPEC_LPWSTR		equ 0
PRSPEC_PROPID		equ 1

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

LPPROPERTYSTORAGE	typedef ptr IPropertyStorage
externdef		IID_IPropertyStorage:IID

endif

ifndef __IPropertySetStorage_INTERFACE_DEFINED__
__IPropertySetStorage_INTERFACE_DEFINED__ equ 1

.comdef IPropertySetStorage : public IUnknown

    .ends

LPPROPERTYSETSTORAGE	typedef ptr IPropertySetStorage
externdef		IID_IPropertySetStorage:IID

endif

ifndef __IEnumSTATPROPSTG_INTERFACE_DEFINED__
__IEnumSTATPROPSTG_INTERFACE_DEFINED__ equ 1

.comdef IEnumSTATPROPSTG : public IUnknown

    .ends

LPENUMSTATPROPSTG	typedef ptr IEnumSTATPROPSTG
externdef		IID_IEnumSTATPROPSTG:IID

endif

ifndef __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__
__IEnumSTATPROPSETSTG_INTERFACE_DEFINED__ equ 1

.comdef IEnumSTATPROPSETSTG : public IUnknown

    .ends

LPENUMSTATPROPSETSTG	typedef ptr IEnumSTATPROPSETSTG
externdef		IID_IEnumSTATPROPSETSTG:IID

endif

PropVariantCopy proto WINAPI \
	      pvarDest: ptr PROPVARIANT,
	       pvarSrc: ptr PROPVARIANT

PropVariantClear proto WINAPI \
		  pvar: ptr PROPVARIANT

FreePropVariantArray proto WINAPI \
	     cVariants: ULONG,
		rgvars: ptr PROPVARIANT

_PROPVARIANTINIT_DEFINED_ equ 1
PropVariantInit macro pvar
	exitm<memset ( pvar, 0, PROPVARIANT )>
	endm


ifndef _STGCREATEPROPSTG_DEFINED_
;WINOLEAPI
StgCreatePropStg proto WINAPI \
		  pUnk: ptr IUnknown,
		 fmtid: REFFMTID,
		pclsid: ptr CLSID,
	      grfFlags: DWORD,
	    dwReserved: DWORD,
	     ppPropStg: ptr IPropertyStorage

StgOpenPropStg proto WINAPI \
		  pUnk: ptr IUnknown,
		 fmtid: REFFMTID,
	      grfFlags: DWORD,
	    dwReserved: DWORD,
	     ppPropStg: ptr IPropertyStorage

StgCreatePropSetStg proto WINAPI \
	      pStorage: ptr IStorage,
	    dwReserved: DWORD,
	  ppPropSetStg: ptr IPropertySetStorage


CCH_MAX_PROPSTG_NAME	equ 31
;WINOLEAPI
FmtIdToPropStgName proto WINAPI \
		pfmtid: ptr FMTID,
	       oszName: LPOLESTR

PropStgNameToFmtId proto WINAPI \
	       oszName: LPOLESTR,
		pfmtid: ptr FMTID

endif

if  (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

ifndef __IClientSecurity_INTERFACE_DEFINED__
__IClientSecurity_INTERFACE_DEFINED__ equ 1

LPOLECHAR		typedef ptr OLECHAR

SOLE_AUTHENTICATION_SERVICE STRUC
dwAuthnSvc		dd ?
dwAuthzSvc		dd ?
pPrincipalName		LPOLECHAR ?
hr			HRESULT ?
SOLE_AUTHENTICATION_SERVICE ENDS

PSOLE_AUTHENTICATION_SERVICE typedef ptr SOLE_AUTHENTICATION_SERVICE

EOLE_AUTHENTICATION_CAPABILITIES typedef SDWORD
EOAC_NONE		equ 0
EOAC_MUTUAL_AUTH	equ 0x1
EOAC_CLOAKING		equ 0x10
EOAC_SECURE_REFS	equ 0x2
EOAC_ACCESS_CONTROL	equ 0x4
EOAC_APPID		equ 0x8

DEFINE_IIDX(IClientSecurity, "0000013D-0000-0000-C000-000000000046")

.comdef IClientSecurity : public IUnknown

    QueryBlanket	proc  :ptr IUnknown, :ptr DWORD, :ptr DWORD, :ptr ptr OLECHAR, :ptr DWORD, :ptr DWORD, :ptr ptr, :ptr DWORD
    SetBlanket		proc  :ptr IUnknown, :DWORD, :DWORD, :ptr OLECHAR, :DWORD, :DWORD, :ptr, :DWORD
    CopyProxy		proc  :ptr IUnknown, :ptr ptr IUnknown

    .ends

endif

ifndef __IServerSecurity_INTERFACE_DEFINED__
__IServerSecurity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServerSecurity, "0000013E-0000-0000-C000-000000000046")

.comdef IServerSecurity : public IUnknown

    QueryBlanket	proc :ptr DWORD, :ptr DWORD, :ptr ptr OLECHAR, :ptr DWORD, :ptr DWORD, :ptr ptr, :ptr DWORD
    ImpersonateClient	proc
    RevertToSelf	proc
    IsImpersonating	proc

    .ends

endif

ifndef __IClassActivator_INTERFACE_DEFINED__
__IClassActivator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IClassActivator, "00000140-0000-0000-C000-000000000046")

.comdef IClassActivator : public IUnknown

    GetClassObject	proc :REFCLSID, :DWORD, :LCID, :REFIID, :ptr ptr

    .ends

endif

RPCOPT_PROPERTIES	typedef sdword
COMBND_RPCTIMEOUT	equ 0x1
COMBND_SERVER_LOCALITY	equ 0x2

RPCOPT_SERVER_LOCALITY_VALUES typedef sdword
SERVER_LOCALITY_PROCESS_LOCAL equ 0
SERVER_LOCALITY_MACHINE_LOCAL equ 1
SERVER_LOCALITY_REMOTE	equ 2

ifndef __IRpcOptions_INTERFACE_DEFINED__
__IRpcOptions_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcOptions, "00000144-0000-0000-C000-000000000046")

.comdef IRpcOptions : public IUnknown

    Set			proc :ptr IUnknown, :RPCOPT_PROPERTIES, :ULONG_PTR
    Query		proc :ptr IUnknown, :RPCOPT_PROPERTIES, :ptr ULONG_PTR

    .ends

endif

COMBND_RPCSTRINGS	equ 0x1

GLOBALOPT_PROPERTIES	typedef SDWORD
COMGLB_EXCEPTION_HANDLING equ 1
COMGLB_APPID		equ 2
COMGLB_RPC_THREADPOOL_SETTING equ 3

GLOBALOPT_EH_VALUES	typedef SDWORD
COMGLB_EXCEPTION_HANDLE equ 0
COMGLB_EXCEPTION_DONOT_HANDLE_FATAL equ 1
COMGLB_EXCEPTION_DONOT_HANDLE equ COMGLB_EXCEPTION_DONOT_HANDLE_FATAL
COMGLB_EXCEPTION_DONOT_HANDLE_ANY equ 2

GLOBALOPT_RPCTP_VALUES	typedef SDWORD
COMGLB_RPC_THREADPOOL_SETTING_DEFAULT_POOL equ 0
COMGLB_RPC_THREADPOOL_SETTING_PRIVATE_POOL equ 1

DEFINE_IIDX(IGlobalOptions, "0000015B-0000-0000-C000-000000000046")

.comdef IGlobalOptions : public IUnknown

    Set			proc :GLOBALOPT_PROPERTIES, :ULONG_PTR
    Query		proc :GLOBALOPT_PROPERTIES, :ptr ULONG_PTR

    .ends

ifndef __IComBinding_INTERFACE_DEFINED__
__IComBinding_INTERFACE_DEFINED__ equ 1

externdef		IID_IComBinding:IID

.comdef IComBinding : public IUnknown

    InitBinding		proc :DWORD, :DWORD, :DWORD, :DWORD, :LPOLESTR
    QueryBinding	proc :ptr, :ptr, :ptr, :ptr, :ptr

    .ends

endif
endif

ifndef __IFillLockBytes_INTERFACE_DEFINED__
__IFillLockBytes_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFillLockBytes, "99caf010-415e-11cf-8814-00aa00b569f5")

.comdef IFillLockBytes : public IUnknown

    FillAppend		proc :ptr, :ULONG, :ptr ULONG
    FillAt		proc :ULARGE_INTEGER, :ptr, :ULONG, :ptr ULONG
    SetFillSize		proc :ULARGE_INTEGER
    Terminate		proc :BOOL

    .ends

endif

ifndef __IProgressNotify_INTERFACE_DEFINED__
__IProgressNotify_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IProgressNotify, "a9d758a0-4617-11cf-95fc-00aa00680db4")

.comdef IProgressNotify : public IUnknown

    OnProgress		proc :DWORD, :DWORD, :BOOL, :BOOL

    .ends

endif

ifndef __ILayoutStorage_INTERFACE_DEFINED__
__ILayoutStorage_INTERFACE_DEFINED__ equ 1

StorageLayout		STRUC
LayoutType		dd ?
pwcsElementName		LPOLECHAR ?
cOffset			LARGE_INTEGER <>
cBytes			LARGE_INTEGER <>
StorageLayout		ENDS

DEFINE_IIDX(ILayoutStorage, "0e6d4d90-6738-11cf-9608-00aa00680db4")

.comdef ILayoutStorage : public IUnknown

    LayoutScript	proc :ptr, :DWORD, :DWORD
    BeginMonitor	proc
    EndMonitor		proc
    ReLayoutDocfile	proc :ptr
    ReLayoutDocfileOnILockBytes proc :ptr

    .ends

endif

ifndef __IBlockingLock_INTERFACE_DEFINED__
__IBlockingLock_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IBlockingLock, "30f3d47a-6447-11d1-8e3c-00c04fb9386d")

.comdef IBlockingLock : public IUnknown

    _Lock		proc :DWORD
    Unlock		proc

    .ends

endif

ifndef __ITimeAndNoticeControl_INTERFACE_DEFINED__
__ITimeAndNoticeControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITimeAndNoticeControl, "bc0bf6ae-8878-11d1-83e9-00c04fc2c6d4")

.comdef ITimeAndNoticeControl : public IUnknown

    SuppressChanges	proc :DWORD, :DWORD

    .ends

endif

ifndef __IOplockStorage_INTERFACE_DEFINED__
__IOplockStorage_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOplockStorage, "8d19c834-8879-11d1-83e9-00c04fc2c6d4")

.comdef IOplockStorage : public IUnknown

    CreateStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr ptr
    OpenStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr ptr

    .ends

endif

ifndef __ISurrogate_INTERFACE_DEFINED__
__ISurrogate_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISurrogate, "00000022-0000-0000-C000-000000000046")

.comdef ISurrogate : public IUnknown

    LoadDllServer	proc :REFCLSID
    FreeSurrogate	proc

    .ends

LPSURROGATE		typedef ptr ISurrogate

endif

ifndef __IGlobalInterfaceTable_INTERFACE_DEFINED__
__IGlobalInterfaceTable_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IGlobalInterfaceTable, "00000146-0000-0000-C000-000000000046")

.comdef IGlobalInterfaceTable : public IUnknown

    RegisterInterfaceInGlobal proc :ptr, :REFIID, :ptr DWORD
    RevokeInterfaceFromGlobal proc :DWORD
    GetInterfaceFromGlobal proc :DWORD, :REFIID, :ptr ptr

    .ends

LPGLOBALINTERFACETABLE	typedef ptr IGlobalInterfaceTable

endif

ifndef __IDirectWriterLock_INTERFACE_DEFINED__
__IDirectWriterLock_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectWriterLock, "0e6d4d92-6738-11cf-9608-00aa00680db4")

.comdef IDirectWriterLock : public IUnknown

    WaitForWriteAccess	proc :DWORD
    ReleaseWriteAccess	proc
    HaveWriteAccess	proc

    .ends

endif

ifndef __ISynchronize_INTERFACE_DEFINED__
__ISynchronize_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronize, "00000030-0000-0000-C000-000000000046")

.comdef ISynchronize : public IUnknown

    _Wait		proc :DWORD, :DWORD
    Signal		proc
    Reset		proc

    .ends

endif

ifndef __ISynchronizeHandle_INTERFACE_DEFINED__
__ISynchronizeHandle_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronizeHandle, "00000031-0000-0000-C000-000000000046")

.comdef ISynchronizeHandle : public IUnknown

    GetHandle		proc :ptr HANDLE

    .ends

endif

ifndef __ISynchronizeMutex_INTERFACE_DEFINED__
__ISynchronizeMutex_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronizeMutex, "00000025-0000-0000-C000-000000000046")

.comdef ISynchronizeMutex : public IUnknown

    _Wait		proc :DWORD, :DWORD
    Signal		proc
    Reset		proc
    ReleaseMutex	proc

    .ends

endif

ifndef __IAsyncSetup_INTERFACE_DEFINED__
__IAsyncSetup_INTERFACE_DEFINED__ equ 1

externdef		IID_IAsyncSetup:IID

.comdef IAsyncSetup : public IUnknown

    GetAsyncManager	proc :REFIID, :ptr, :DWORD, :ptr, :ptr

    .ends

endif

ifndef __ICancelMethodCalls_INTERFACE_DEFINED__
__ICancelMethodCalls_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICancelMethodCalls, "00000029-0000-0000-C000-000000000046")

.comdef ICancelMethodCalls : public IUnknown

    Cancel		proc :ULONG
    TestCancel		proc

    .ends

LPCANCELMETHODCALLS	typedef ptr ICancelMethodCalls

endif

ifndef __IAsyncManager_INTERFACE_DEFINED__
__IAsyncManager_INTERFACE_DEFINED__ equ 1

DCOM_NONE		equ 0
DCOM_CALL_COMPLETE	equ 0x1
DCOM_CALL_CANCELED	equ 0x2

DEFINE_IIDX(IAsyncManager, "0000002A-0000-0000-C000-000000000046")

.comdef IAsyncManager : public IUnknown

    CompleteCall	proc :HRESULT
    GetCallContext	proc :REFIID, :ptr
    GetState		proc :ptr

    .ends

endif

ifndef __ICallFactory_INTERFACE_DEFINED__
__ICallFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICallFactory, "1c733a30-2a1c-11ce-ade5-00aa0044773d")

.comdef ICallFactory : public IUnknown

    CreateCall		proc :REFIID, :ptr IUnknown, :REFIID, :ptr ptr IUnknown

    .ends

endif

ifndef __IRpcHelper_INTERFACE_DEFINED__
__IRpcHelper_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcHelper, "00000149-0000-0000-C000-000000000046")

.comdef IRpcHelper : public IUnknown

    GetDCOMProtocolVersion proc :ptr DWORD
    GetIIDFromOBJREF	proc :ptr, :ptr ptr IID

    .ends
endif

ifndef __IReleaseMarshalBuffers_INTERFACE_DEFINED__
__IReleaseMarshalBuffers_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IReleaseMarshalBuffers, "eb0cb9e8-7996-11d2-872e-0000f8080859")

.comdef IReleaseMarshalBuffers : public IUnknown

    ReleaseMarshalBuffer proc :ptr RPCOLEMESSAGE, :DWORD, :ptr IUnknown

    .ends

endif

ifndef __IWaitMultiple_INTERFACE_DEFINED__
__IWaitMultiple_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWaitMultiple, "0000002B-0000-0000-C000-000000000046")

.comdef IWaitMultiple : public IUnknown

    WaitMultiple	proc :DWORD, :ptr
    AddSynchronize	proc :ptr

    .ends

endif

ifndef __IUrlMon_INTERFACE_DEFINED__
__IUrlMon_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUrlMon, "00000026-0000-0000-C000-000000000046")

.comdef IUrlMon : public IUnknown

    AsyncGetClassBits	proc :REFCLSID, :LPWSTR, :LPWSTR, :DWORD, :DWORD, :LPWSTR, :ptr, :DWORD, :REFIID, :DWORD

    .ends

endif

ifndef __IForegroundTransfer_INTERFACE_DEFINED__
__IForegroundTransfer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IForegroundTransfer, "00000145-0000-0000-C000-000000000046")

.comdef IForegroundTransfer : public IUnknown

    AllowForegroundTransfer proc :ptr

    .ends

endif

ifndef __IAddrTrackingControl_INTERFACE_DEFINED__
__IAddrTrackingControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAddrTrackingControl, "00000147-0000-0000-C000-000000000046")

.comdef IAddrTrackingControl : public IUnknown

    EnableCOMDynamicAddrTracking proc
    DisableCOMDynamicAddrTracking proc

    .ends

LPADDRTRACKINGCONTROL	typedef ptr IAddrTrackingControl

endif

ifndef __IAddrExclusionControl_INTERFACE_DEFINED__
__IAddrExclusionControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAddrExclusionControl, "00000148-0000-0000-C000-000000000046")

.comdef IAddrExclusionControl : public IUnknown

    GetCurrentAddrExclusionList proc :REFIID, :ptr ptr
    UpdateAddrExclusionList proc :ptr IUnknown

    .ends

LPADDREXCLUSIONCONTROL	typedef ptr IAddrExclusionControl

endif

ifndef __IPipeByte_INTERFACE_DEFINED__
__IPipeByte_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPipeByte, "DB2F3ACA-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeByte : public IUnknown

    Pull		proc :ptr BYTE, :ULONG, :ptr ULONG
    _Push		proc :ptr BYTE, :ULONG

    .ends

endif

ifndef __AsyncIPipeByte_INTERFACE_DEFINED__
__AsyncIPipeByte_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(AsyncIPipeByte, "DB2F3ACB-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeByte : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr BYTE, :ptr ULONG
    Begin_Push		proc :ptr BYTE, :ULONG
    Finish_Push		proc

    .ends

endif

ifndef __IPipeLong_INTERFACE_DEFINED__
__IPipeLong_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPipeLong, "DB2F3ACC-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeLong : public IUnknown

    Pull		proc :ptr LONG, :ULONG, :ptr ULONG
    _Push		proc :ptr LONG, :ULONG

    .ends

endif

ifndef __AsyncIPipeLong_INTERFACE_DEFINED__
__AsyncIPipeLong_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(AsyncIPipeLong, "DB2F3ACD-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeLong : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr LONG, :ptr ULONG
    Begin_Push		proc :ptr LONG, :ULONG
    Finish_Push		proc

    .ends

endif

ifndef __IPipeDouble_INTERFACE_DEFINED__
__IPipeDouble_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPipeDouble, "DB2F3ACE-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeDouble : public IUnknown

    Pull		proc :ptr real8, :ULONG, :ptr ULONG
    _Push		proc :ptr real8, :ULONG

    .ends

endif

ifndef __AsyncIPipeDouble_INTERFACE_DEFINED__
__AsyncIPipeDouble_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(AsyncIPipeDouble, "DB2F3ACF-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeDouble : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr real8, :ptr ULONG
    Begin_Push		proc :ptr real8, :ptr ULONG
    Finish_Push		proc

    .ends

endif

ifndef __IThumbnailExtractor_INTERFACE_DEFINED__
__IThumbnailExtractor_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IThumbnailExtractor, "969dc708-5c76-11d1-8d86-0000f804b057")

.comdef IThumbnailExtractor : public IUnknown

    ExtractThumbnail	proc :ptr IStorage, :ULONG, :ULONG, :ptr ULONG, :ptr ULONG, :ptr HBITMAP
    OnFileUpdated	proc :ptr IStorage

    .ends

endif

ifndef __IDummyHICONIncluder_INTERFACE_DEFINED__
__IDummyHICONIncluder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDummyHICONIncluder, "947990de-cc28-11d2-a0f7-00805f858fb1")

.comdef IDummyHICONIncluder : public IUnknown

    Dummy		proc :HICON, :HDC

    .ends

endif

if defined(USE_COM_CONTEXT_DEF) or defined(BUILDTYPE_COMSVCS) or defined(_OLE32_)

CPFLAGS			typedef DWORD

ContextProperty		STRUC
policyId		GUID <>
flags			CPFLAGS ?
pUnk			LPIUnknown ?
ContextProperty		ENDS

ifndef __IEnumContextProps_INTERFACE_DEFINED__
__IEnumContextProps_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumContextProps, "000001c1-0000-0000-C000-000000000046")

.comdef IEnumContextProps : public IUnknown

    Next		proc :ULONG, :ptr, :ptr ULONG
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr IEnumContextProps
    Count		proc :ptr ULONG

    .ends

LPENUMCONTEXTPROPS	typedef ptr IEnumContextProps

endif

ifndef __IContext_INTERFACE_DEFINED__
__IContext_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContext, "000001c0-0000-0000-C000-000000000046")

.comdef IContext : public IUnknown

    SetProperty		proc :REFGUID, :CPFLAGS, :ptr IUnknown
    RemoveProperty	proc :REFGUID
    GetProperty		proc :REFGUID, :ptr CPFLAGS, :ptr ptr IUnknown
    EnumContextProps	proc :ptr ptr IEnumContextProps

    .ends

endif

if not defined(BUILDTYPE_COMSVCS) and not defined(_OLE32_)

ifndef __IObjContext_INTERFACE_DEFINED__
__IObjContext_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjContext, "000001c6-0000-0000-C000-000000000046")

.comdef IObjContext : public IUnknown

    SetProperty		proc :REFGUID, :CPFLAGS, :ptr IUnknown
    RemoveProperty	proc :REFGUID
    GetProperty		proc :REFGUID, :ptr CPFLAGS, :ptr ptr IUnknown
    EnumContextProps	proc :ptr ptr IEnumContextProps
    Reserved1		proc
    Reserved2		proc
    Reserved3		proc
    Reserved4		proc
    Reserved5		proc
    Reserved6		proc
    Reserved7		proc

    .ends

endif

endif
endif

ApplicationType		typedef sdword
ServerApplication	equ 0
LibraryApplication	equ ( ServerApplication + 1 )

ShutdownType		typedef sdword
IdleShutdown		equ 0
ForcedShutdown		equ ( IdleShutdown + 1 )

ifndef __IProcessLock_INTERFACE_DEFINED__
__IProcessLock_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IProcessLock, "000001d5-0000-0000-C000-000000000046")

.comdef IProcessLock : public IUnknown

    AddRefOnProcess	proc
    ReleaseRefOnProcess proc

    .ends

endif

ifndef __ISurrogateService_INTERFACE_DEFINED__
__ISurrogateService_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISurrogateService, "000001d4-0000-0000-C000-000000000046")

.comdef ISurrogateService : public IUnknown

    Init		proc :REFGUID, :ptr IProcessLock, :ptr BOOL
    ApplicationLaunch	proc :REFGUID, :ptr
    ApplicationFree	proc :REFGUID
    CatalogRefresh	proc :ULONG
    ProcessShutdown	proc :ptr

    .ends

endif

APTTYPEQUALIFIER	typedef SDWORD
APTTYPEQUALIFIER_NONE	equ 0
APTTYPEQUALIFIER_IMPLICIT_MTA equ 1
APTTYPEQUALIFIER_NA_ON_MTA equ 2
APTTYPEQUALIFIER_NA_ON_STA equ 3
APTTYPEQUALIFIER_NA_ON_IMPLICIT_MTA equ 4
APTTYPEQUALIFIER_NA_ON_MAINSTA	equ 5

APTTYPE			typedef SDWORD
APTTYPE_CURRENT		equ -1
APTTYPE_STA		equ 0
APTTYPE_MTA		equ 1
APTTYPE_NA		equ 2
APTTYPE_MAINSTA		equ 3

THDTYPE			typedef SDWORD
THDTYPE_BLOCKMESSAGES	equ 0
THDTYPE_PROCESSMESSAGES equ 1

APARTMENTID		typedef DWORD

ifndef __IComThreadingInfo_INTERFACE_DEFINED__
__IComThreadingInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComThreadingInfo, "000001ce-0000-0000-C000-000000000046")

.comdef IComThreadingInfo : public IUnknown

    GetCurrentApartmentType proc :ptr APTTYPE
    GetCurrentThreadType proc :ptr THDTYPE
    GetCurrentLogicalThreadId proc :ptr GUID
    SetCurrentLogicalThreadId proc :REFGUID

    .ends

endif

ifndef __IProcessInitControl_INTERFACE_DEFINED__
__IProcessInitControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IProcessInitControl, "72380d55-8d2b-43a3-8513-2b6ef31434e9")

.comdef IProcessInitControl : public IUnknown

    ResetInitializerTimeout proc :DWORD

    .ends

endif

if ( _WIN32_WINNT GE 0x0501 )
ifndef __IInitializeSpy_INTERFACE_DEFINED__
__IInitializeSpy_INTERFACE_DEFINED__ equ 1

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

ifndef __ISynchronizeEvent_INTERFACE_DEFINED__
__ISynchronizeEvent_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronizeEvent, "00000032-0000-0000-C000-000000000046")

.comdef ISynchronizeEvent : public IUnknown

    GetHandle		proc :ptr
    SetEventHandle	proc :ptr HANDLE

    .ends

endif

ifndef __ISynchronizeContainer_INTERFACE_DEFINED__
__ISynchronizeContainer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronizeContainer, "00000033-0000-0000-C000-000000000046")

.comdef ISynchronizeContainer : public IUnknown

    AddSynchronize	proc :ptr ISynchronize
    WaitMultiple	proc :DWORD, :DWORD, :ptr ptr ISynchronize

    .ends

endif

ifndef __IClassAccess_INTERFACE_DEFINED__
__IClassAccess_INTERFACE_DEFINED__ equ 1

LPPUBLISHEDAPPINFO	typedef ptr PUBLISHEDAPPINFO

PUBLISHEDINFOLIST	STRUC
cPublApps		dd ?
pPublAppInfo		LPPUBLISHEDAPPINFO ?
PUBLISHEDINFOLIST	ENDS

externdef		IID_IClassAccess:IID

.comdef IClassAccess : public IUnknown

    GetClassInfo	proc :REFCLSID, :QUERYCONTEXT, :ptr
    GetClassSpecInfo	proc :ptr, :QUERYCONTEXT, :ptr
    GetInstallablePackages proc :DWORD, :ptr

    .ends

endif

ifndef __IClassRefresh_INTERFACE_DEFINED__
__IClassRefresh_INTERFACE_DEFINED__ equ 1

LPPACKAGEINFO		typedef ptr PACKAGEINFO

PACKAGEINFOLIST		STRUC
cPackInfo		dd ?
pPackageInfo		LPPACKAGEINFO ?
PACKAGEINFOLIST		ENDS

externdef		IID_IClassRefresh:IID

.comdef IClassRefresh : public IUnknown

    GetUpgrades		proc :ULONG, :ptr, :CSPLATFORM, :LCID, :ptr
    CommitUpgrades	proc

    .ends

endif

CLASSDETAIL		STRUC
Clsid			CLSID <>
pszDesc			LPOLESTR ?
pszIconPath		LPOLESTR ?
TreatAsClsid		CLSID <>
AutoConvertClsid	CLSID <>
cFileExt		dd ?
prgFileExt		LPOLESTR ?
pMimeType		LPOLESTR ?
pDefaultProgId		LPOLESTR ?
cOtherProgId		dd ?
prgOtherProgId		LPOLESTR ?
CLASSDETAIL		ENDS

ifndef _LPCSADMNENUM_DEFINED
_LPCSADMNENUM_DEFINED equ 1

ifndef __IEnumPackage_INTERFACE_DEFINED__
__IEnumPackage_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumPackage:IID

.comdef IEnumPackage : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr

    .ends

endif

ifndef __IEnumClass_INTERFACE_DEFINED__
__IEnumClass_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumClass:IID

.comdef IEnumClass : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr

    .ends

endif
endif

ifndef __IClassAdmin_INTERFACE_DEFINED__
__IClassAdmin_INTERFACE_DEFINED__ equ 1

externdef		IID_IClassAdmin:IID

.comdef IClassAdmin : public IUnknown

    NewClass		proc :ptr
    DeleteClass		proc :REFCLSID
    NewInterface	proc :REFIID, :LPOLESTR, :REFCLSID, :REFCLSID
    DeleteInterface	proc :REFIID
    NewPackage		proc :ptr
    DeletePackage	proc :LPOLESTR
    GetClassesEnum	proc :ptr
    GetPackagesEnum	proc :REFCLSID, :LPOLESTR, :CSPLATFORM, :DWORD, :LCID, :ptr
    GetClassDetails	proc :REFCLSID, :ptr
    GetIidDetails	proc :REFIID, :ptr, :ptr, :ptr
    GetPackageDetails	proc :LPOLESTR, :ptr

    .ends

endif

;DWORD
ASYNC_STGMEDIUM_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr ASYNC_STGMEDIUM
;LPSTR
ASYNC_STGMEDIUM_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr ASYNC_STGMEDIUM
;LPSTR
ASYNC_STGMEDIUM_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr ASYNC_STGMEDIUM
;void
ASYNC_STGMEDIUM_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr ASYNC_STGMEDIUM

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
CLIPFORMAT_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr CLIPFORMAT
;LPSTR
CLIPFORMAT_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT
;LPSTR
CLIPFORMAT_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT
;void
CLIPFORMAT_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr CLIPFORMAT

;DWORD
FLAG_STGMEDIUM_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr FLAG_STGMEDIUM
;LPSTR
FLAG_STGMEDIUM_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr FLAG_STGMEDIUM
;LPSTR
FLAG_STGMEDIUM_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr FLAG_STGMEDIUM
;void
FLAG_STGMEDIUM_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr FLAG_STGMEDIUM

;DWORD
SNB_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr SNB
;LPSTR
SNB_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr SNB
;LPSTR
SNB_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr SNB
;void
SNB_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr SNB

;DWORD
STGMEDIUM_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr STGMEDIUM
;LPSTR
STGMEDIUM_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr STGMEDIUM
;LPSTR
STGMEDIUM_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr STGMEDIUM
;void
STGMEDIUM_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr STGMEDIUM

endif

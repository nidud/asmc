
define INC_OLE2
define STRICT

include stdio.inc
include windows.inc
include tchar.inc

;; simple class-factory: only knows how to create CSimpleObject instances

.class CClassFactory : public IClassFactory
    CClassFactory proc
   .ENDS

;; simple object supporting a dummy IStream

.class CSimpleObject : public IStream

    m_cRef LONG ?

    ;; constructors/destructors

    CSimpleObject   proc
    delete          proc
   .ENDS

.data
 CLSID_SimpleObject GUID {0x5e9ddec7,0x5767,0x11cf,{0xbe,0xab,0x0,0xaa,0x0,0x6c,0x36,0x6}}
ifdef __PE__
 IID_IClassFactory  GUID _IID_IClassFactory
 IID_IStream        GUID _IID_IStream
 IID_IUnknown       GUID _IID_IUnknown
endif
 hevtDone HANDLE 0

.code

Message proc szPrefix:LPTSTR, hr:HRESULT

  local szMessage:LPTSTR

    ldr edx,hr
    .if edx == S_OK
        wprintf(ldr(szPrefix))
        wprintf(L"\n")
       .return
    .endif
    .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)
        mov hr,HRESULT_CODE(edx)
    .endif
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER or \
        FORMAT_MESSAGE_FROM_SYSTEM or \
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), ;;The user default language
        &szMessage,
        0,
        NULL)
    wprintf(L"%s: %s(%lx)\n", szPrefix, szMessage, hr)
    LocalFree(szMessage)
    ret
    endp

    assume class:rcx

CSimpleObject::QueryInterface proc riid:REFIID, ppv:ptr ptr

    .if ( ldr(ppv) == NULL )
        .return( E_INVALIDARG )
    .endif
    ldr rdx,riid
    mov rax,[rdx] ; lower part..
    ldr rdx,ppv
    .if ( rax == qword ptr IID_IUnknown || rax == qword ptr IID_IStream )
        mov [rdx],rcx
        AddRef()
       .return( S_OK )
    .endif
    xor eax,eax
    mov [rdx],rax
    mov eax,E_NOINTERFACE
    ret
    endp


CSimpleObject::AddRef proc
    .return InterlockedIncrement( &m_cRef )
    endp


CSimpleObject::Release proc
    .ifd ( InterlockedDecrement( &m_cRef ) == 0 )
        delete()
       .return( 0 )
    .endif
    .return( 1 )
    endp


CSimpleObject::Read proc pv:ptr, cb:ULONG, pcbRead:ptr ULONG

    Message(L"Server: IStream:Read", S_OK)

    mov rdx,pv
    mov ecx,cb
    .if ( !rdx && ecx )
        .return( E_INVALIDARG )
    .endif

    ;; fill the buffer with FF's. we could read it from somewhere.

    .if ecx
        mov  al,0xFF
        xchg rdi,rdx
        rep  stosb
        mov  rdi,rdx
    .endif
    mov rdx,pcbRead
    .if rdx
        mov [rdx],cb
    .endif
    .return S_OK
    endp


CSimpleObject::Write proc pv:ptr, cb:ULONG, pcbWritten:ptr ULONG

    Message(L"Server: IStream:Write", S_OK)
    mov rdx,pv
    mov ecx,cb
    .if ( !rdx && ecx )
        .return( E_INVALIDARG )
    .endif

    ;; ignore the data, but we could examine it or put it somewhere

    mov rdx,pcbWritten
    .if rdx
        mov [rdx],ecx
    .endif
    .return S_OK
    endp


CSimpleObject::Seek proc dbMove:LARGE_INTEGER, dwOrigin:DWORD, pbNewPosition:ptr ULARGE_INTEGER
    .return( E_FAIL )
    endp
CSimpleObject::SetSize proc cbNewSize:ULARGE_INTEGER
    .return( E_FAIL )
    endp
CSimpleObject::CopyTo proc pstm:ptr IStream, cb:ULARGE_INTEGER, pcbRead:ptr ULARGE_INTEGER, pcbWritten:ptr ULARGE_INTEGER
    .return( E_FAIL )
    endp
CSimpleObject::Commit proc grfCommitFlags:DWORD
    .return( E_FAIL )
    endp
CSimpleObject::Revert proc
    .return( E_FAIL )
    endp
CSimpleObject::LockRegion proc bOffset:ULARGE_INTEGER, cb:ULARGE_INTEGER, dwLockType:DWORD
    .return( E_FAIL )
    endp
CSimpleObject::UnlockRegion proc bOffset:ULARGE_INTEGER, cb:ULARGE_INTEGER, dwLockType:DWORD
    .return( E_FAIL )
    endp
CSimpleObject::Stat proc pstatstg:ptr STATSTG, grfStatFlag:DWORD
    .return( E_FAIL )
    endp
CSimpleObject::Clone proc ppstm:ptr ptr IStream
    .return( E_FAIL )
    endp

CSimpleObject::delete proc
    SetEvent(hevtDone)
    CoTaskMemFree(this)
    ret
    endp


CSimpleObject::CSimpleObject proc
    @ComAlloc(CSimpleObject)
    mov [rax].CSimpleObject.m_cRef,1
    ret
    endp


CClassFactory::QueryInterface proc riid:REFIID, ppv:ptr ptr

    .if (r8 == NULL)
        .return E_INVALIDARG
    .endif
    mov rax,[rdx]
    .if (rax == qword ptr IID_IClassFactory || rax == qword ptr IID_IUnknown)
        mov [r8],rcx
        AddRef()
       .return S_OK
    .endif
    mov qword ptr [r8],NULL
    .return E_NOINTERFACE
    endp


CClassFactory::AddRef proc
    .return 1
    endp

CClassFactory::Release proc
    .return 1
    endp


CClassFactory::CreateInstance proc punkOuter:LPUNKNOWN, riid:REFIID, ppv:ptr ptr

  local punk:LPUNKNOWN
  local hr:HRESULT

    xor eax,eax
    mov [r9],rax
    .if ( rdx != NULL )
        .return CLASS_E_NOAGGREGATION
    .endif
    Message(L"Server: IClassFactory:CreateInstance", S_OK)
    mov punk,CSimpleObject()
    .if ( rax == NULL )
        .return E_OUTOFMEMORY
    .endif
    mov hr,punk.QueryInterface(riid, ppv)
    punk.Release()
    .return hr
    endp


CClassFactory::LockServer proc fLock:BOOL
    .return E_FAIL
    endp


CClassFactory::CClassFactory proc
    @ComAlloc(CClassFactory)
    ret
    endp


main proc

  local hr:HRESULT, dwRegister:DWORD, pFactory:ptr CClassFactory

    ;; create the thread which is signaled when the instance is deleted

    mov hevtDone,CreateEvent(NULL, FALSE, FALSE, NULL)
    .if ( rax == NULL )
        mov hr,HRESULT_FROM_WIN32R(GetLastError())
        Message(L"Server: CreateEvent", hr)
        exit(hr)
    .endif

    ;; initialize COM for free-threading

    mov hr,CoInitializeEx(NULL, COINIT_MULTITHREADED)
    .if (FAILED(hr))
        Message(L"Server: CoInitializeEx", hr)
        exit(hr)
    .endif

    ;; register the class-object with OLE

    mov pFactory,CClassFactory()
    mov hr,CoRegisterClassObject(&CLSID_SimpleObject, pFactory, CLSCTX_SERVER, REGCLS_SINGLEUSE, &dwRegister)
    .if (FAILED(hr))
        Message(L"Server: CoRegisterClassObject", hr)
        exit(hr)
    .endif
    Message(L"Server: Waiting", S_OK)

    ;; wait until an object is created and deleted.

    WaitForSingleObject(hevtDone, INFINITE)
    CloseHandle(hevtDone)
    CoTaskMemFree(pFactory)
    CoUninitialize()
    Message(L"Server: Done", S_OK)
    .return S_OK
    endp

    end _tstart

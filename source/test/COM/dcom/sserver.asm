;;
;;  This is the server-portion of the SIMPLE Network OLE sample. This
;; application implements the CLSID_SimpleObject class as a LocalServer.
;; Instances of this class support a limited form of the IStream interface --
;; calls to IStream::Read and IStream::Write will "succeed" (they do nothing),
;; and calls on any other methods fail with E_NOTIMPL.
;;
;;  The purpose of this sample is to demonstrate what is minimally required
;; to implement an object that can be used by clients (both those on the same
;; machine using OLE and those using Network OLE across the network).
;;
;; Instructions:
;;
;;  To use this sample:
;;   * build it using the MAKE command. MAKE will create SSERVER.EXE and
;;     SCLIENT.EXE.
;;   * edit the SSERVER.REG file to make the LocalServer32 key point to the
;;     location of SSERVER.EXE, and run the INSTALL.BAT command (it simply
;;     performs REGEDIT SSERVER.REG)
;;   * run SSERVER.EXE. it should display the message "Waiting..."
;;   * run SCLIENT.EXE on the same machine using no command-line arguments,
;;     or from another machine using the machine-name (UNC or DNS) as the sole
;;     command-line argument. it will connect to the server, perform some read
;;     and write calls, and disconnect. both SSERVER.EXE and SCLIENT.EXE will
;;     automatically terminate. both applications will display some status text.
;;   * you can also run SCLIENT.EXE from a different machine without having first
;;     run SSERVER.EXE on the machine. in this case, SSERVER.EXE will be launched
;;     by OLE in the background and you will be able to watch the output of
;;     SCLIENT.EXE but the output of SSERVER.EXE will be hidden.
;;   * to examine the automatic launch-security features of Network OLE, try
;;     using the '...\CLSID\{...}\LaunchPermission = Y' key commented out in
;;     the SSERVER.REG file and reinstalling it. by setting different read-access
;;     privileges on this key (using the Security/Permissions... dialog in the
;;     REGEDT32 registry tool built into the system) you can allow other
;;     users to run the SCLIENT.EXE program from their accounts.
;;

INC_OLE2    equ 1
STRICT      equ 1

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
 CLSID_SimpleObject GUID { 0x5e9ddec7, 0x5767, 0x11cf, { 0xbe, 0xab, 0x0, 0xaa, 0x0, 0x6c, 0x36, 0x6 } }
ifdef __PE__
 IID_IClassFactory  GUID _IID_IClassFactory
 IID_IUnknown       GUID _IID_IUnknown
endif
 hevtDone HANDLE 0

.code

;;
;; Message
;;
;;  Formats and displays a message to the console.
;;

Message proc szPrefix:LPTSTR, hr:HRESULT

  local szMessage:LPTSTR

    .if edx == S_OK

        wprintf(rcx)
        wprintf(L"\n")
        .return
    .endif

    .if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS)

        mov hr,HRESULT_CODE(hr)
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
        NULL )

    wprintf(L"%s: %s(%lx)\n", szPrefix, szMessage, hr)

    LocalFree(szMessage)
    ret

Message endp

;;
;; class CSimpleObject
;;
    assume rcx:ptr CSimpleObject

;;
;; CSimpleObject::QueryInterface
;;

CSimpleObject::QueryInterface proc riid:REFIID, ppv:ptr ptr

    .return E_INVALIDARG .if (r8 == NULL)

    mov rax,[rdx] ; lower part..

    .if (rax == qword ptr IID_IClassFactory || rax == qword ptr IID_IUnknown)

        mov [r8],rcx
        [rcx].AddRef()

        .return S_OK
    .endif

    mov qword ptr [r8],NULL

    .return E_NOINTERFACE

CSimpleObject::QueryInterface endp


CSimpleObject::AddRef proc

    .return InterlockedIncrement( &[rcx].m_cRef )

CSimpleObject::AddRef endp


CSimpleObject::Release proc

    .if InterlockedDecrement( &[rcx].m_cRef ) == 0

        this.delete()

        .return 0
    .endif

    .return 1

CSimpleObject::Release endp


;;
;; CSimpleObject::Read
;;

CSimpleObject::Read proc pv:ptr, cb:ULONG, pcbRead:ptr ULONG

    Message(L"Server: IStream:Read", S_OK)

    .return E_INVALIDARG .if (!pv && cb != 0)

    ;; fill the buffer with FF's. we could read it from somewhere.

    mov ecx,cb
    .if ecx
        mov     rdx,pv
        mov     al,0xFF
        xchg    rdi,rdx
        rep     stosb
        mov     rdi,rdx
    .endif

    mov rdx,pcbRead
    .if rdx

        mov [rdx],cb
    .endif

    .return S_OK

CSimpleObject::Read endp


;;
;; CSimpleObject::Write
;;

CSimpleObject::Write proc pv:ptr, cb:ULONG, pcbWritten:ptr ULONG

    Message(L"Server: IStream:Write", S_OK)

    .return E_INVALIDARG .if (!pv && cb != 0)

    ;; ignore the data, but we could examine it or put it somewhere

    mov rdx,pcbWritten
    .if rdx

        mov [rdx],cb
    .endif

    .return S_OK

CSimpleObject::Write endp


CSimpleObject::Seek proc dbMove:LARGE_INTEGER, dwOrigin:DWORD, pbNewPosition:ptr ULARGE_INTEGER
CSimpleObject::Seek endp

CSimpleObject::SetSize proc cbNewSize:ULARGE_INTEGER
CSimpleObject::SetSize endp

CSimpleObject::CopyTo proc pstm:ptr IStream, cb:ULARGE_INTEGER, pcbRead:ptr ULARGE_INTEGER, pcbWritten:ptr ULARGE_INTEGER
CSimpleObject::CopyTo endp

CSimpleObject::Commit proc grfCommitFlags:DWORD
CSimpleObject::Commit endp

CSimpleObject::Revert proc
CSimpleObject::Revert endp

CSimpleObject::LockRegion proc bOffset:ULARGE_INTEGER, cb:ULARGE_INTEGER, dwLockType:DWORD
CSimpleObject::LockRegion endp

CSimpleObject::UnlockRegion proc bOffset:ULARGE_INTEGER, cb:ULARGE_INTEGER, dwLockType:DWORD
CSimpleObject::UnlockRegion endp

CSimpleObject::Stat proc pstatstg:ptr STATSTG, grfStatFlag:DWORD
CSimpleObject::Stat endp

CSimpleObject::Clone proc ppstm:ptr ptr IStream
    .return E_FAIL
CSimpleObject::Clone endp


CSimpleObject::delete proc

    SetEvent(hevtDone)
    HeapFree(GetProcessHeap(), 0, this)
    ret

CSimpleObject::delete endp

    assume rcx:nothing


CSimpleObject::CSimpleObject proc

    .if HeapAlloc(GetProcessHeap(), 0, CSimpleObject + CSimpleObjectVtbl)

        mov [rax].CSimpleObject.m_cRef,1
        lea rdx,[rax+CSimpleObject]
        mov [rax],rdx

        for q,<Release,AddRef,QueryInterface,Read,Write,Seek,SetSize,CopyTo,
               Commit,Revert,LockRegion,UnlockRegion,Stat,Clone,delete>

            lea rcx,CSimpleObject_&q
            mov [rdx].CSimpleObjectVtbl.&q,rcx
            endm
    .endif
     ret

CSimpleObject::CSimpleObject endp


;;
;; CClassFactory::QueryInterface
;;

CClassFactory::QueryInterface proc riid:REFIID, ppv:ptr ptr

    .if (r8 == NULL)
        .return E_INVALIDARG
    .endif
    mov rax,[rdx]
    .if (rax == qword ptr IID_IClassFactory || rax == qword ptr IID_IUnknown)

        mov [r8],rcx
        this.AddRef()

        .return S_OK
    .endif

    mov qword ptr [r8],NULL
    .return E_NOINTERFACE

CClassFactory::QueryInterface endp


CClassFactory::AddRef proc

    .return 1

CClassFactory::AddRef endp


CClassFactory::Release proc

    .return 1

CClassFactory::Release endp


;;
;; CClassFactory::CreateInstance
;;

CClassFactory::CreateInstance proc punkOuter:LPUNKNOWN, riid:REFIID, ppv:ptr ptr

  local punk:LPUNKNOWN
  local hr:HRESULT

    mov qword ptr [r9],NULL

    .return CLASS_E_NOAGGREGATION .if (rdx != NULL)

    Message(L"Server: IClassFactory:CreateInstance", S_OK)

    mov punk,CSimpleObject()

    .return E_OUTOFMEMORY .if (rax == NULL)

    mov hr,punk.QueryInterface(riid, ppv)

    punk.Release()

    .return hr

CClassFactory::CreateInstance endp


CClassFactory::LockServer proc fLock:BOOL

    .return E_FAIL

CClassFactory::LockServer endp


CClassFactory::CClassFactory proc

    .if HeapAlloc(GetProcessHeap(), 0, CClassFactory + CClassFactoryVtbl)

        lea rcx,[rax+CClassFactory]
        mov [rax],rcx
        for q,<Release,AddRef,QueryInterface,CreateInstance,LockServer>
            lea rdx,CClassFactory_&q
            mov [rcx].CClassFactoryVtbl.&q,rdx
            endm
    .endif
     ret

CClassFactory::CClassFactory endp


;;
;; main
;;

main proc

  local hr:HRESULT
  local dwRegister:DWORD

    ;; create the thread which is signaled when the instance is deleted

    mov hevtDone,CreateEvent(NULL, FALSE, FALSE, NULL)
    .if (hevtDone == NULL)

        GetLastError()
        mov hr,HRESULT_FROM_WIN32(eax)
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

    mov rdx,CClassFactory()
    mov hr,CoRegisterClassObject(&CLSID_SimpleObject, rdx,
        CLSCTX_SERVER, REGCLS_SINGLEUSE, &dwRegister)

    .if (FAILED(hr))

        Message(L"Server: CoRegisterClassObject", hr)
        exit(hr)
    .endif

    Message(L"Server: Waiting", S_OK)

    ;; wait until an object is created and deleted.

    WaitForSingleObject(hevtDone, INFINITE)

    CloseHandle(hevtDone)

    CoUninitialize()
    Message(L"Server: Done", S_OK)
    ret

main endp

    end _tstart

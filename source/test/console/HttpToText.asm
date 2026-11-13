;; https://learn.microsoft.com/en-us/previous-versions/aspnet/jj889717(v=vs.118)
;; https://learn.microsoft.com/en-us/uwp/api/windows.data.html.htmlutilities.converttotext?view=winrt-22621

ifdef _LIBCMT
.pragma comment(linker,"/defaultlib:libcmtd")
.pragma comment(linker,"/defaultlib:\asmc\lib\x64\combase")
.pragma comment(linker,"/defaultlib:legacy_stdio_definitions")
endif

include windows.inc
include winrt/roapi.inc
include winrt/windows.management.deployment.inc
include winrt/windows.data.html.inc
include winrt/windows.web.http.inc
include stdio.inc
include stringapiset.inc
include tchar.inc

option dllimport:none

.class ProgressHandler : public IUnknown
    m_refCount      int_t ?
    m_pEvent        ptr HANDLE ?
    m_pStatus       ptr AsyncStatus ?
    ProgressHandler proc :ptr HANDLE, :ptr AsyncStatus
    IInvoke         proc :ptr IAsyncActionWithProgress, :AsyncStatus
   .ends

.data
 DECLARE_IID(IUnknown)
 DECLARE_IID(__FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress)
 DECLARE_IID(IUriRuntimeClassFactory)
 DECLARE_IID(IHtmlUtilities)

.code

CreateIUri proc url:wstring_t, instance:ptr ptr Windows::Foundation::IUriRuntimeClass

    .new uri:HSTRING = NULL
    .new hr:HRESULT = WindowsCreateString(url, wcslen(url), &uri)
    .if (SUCCEEDED(hr))
       .new foundationUri:HSTRING = NULL
        mov hr,WindowsCreateString(RuntimeClass_Windows_Foundation_Uri,
                wcslen(RuntimeClass_Windows_Foundation_Uri), &foundationUri)
        .if (SUCCEEDED(hr))
           .new classFactory:ptr Windows::Foundation::IUriRuntimeClassFactory = nullptr
            mov hr,RoGetActivationFactory(foundationUri, &IID_IUriRuntimeClassFactory, &classFactory)
            .if (SUCCEEDED(hr))
                mov hr,classFactory.CreateUri(uri, instance)
                classFactory.Release()
            .endif
            WindowsDeleteString(foundationUri)
        .endif
        WindowsDeleteString(uri)
    .endif
    .return(hr)
    endp


CreateHtml proc instance:ptr ptr Windows::Data::Html::IHtmlUtilities

    .new uri:HSTRING = NULL
    .new hr:HRESULT = WindowsCreateString(RuntimeClass_Windows_Data_Html_HtmlUtilities,
            wcslen(RuntimeClass_Windows_Data_Html_HtmlUtilities), &uri)

    .if (SUCCEEDED(hr))
        mov hr,RoGetActivationFactory(uri, &IID_IHtmlUtilities, instance)
        WindowsDeleteString(uri)
    .endif
    .return(hr)
    endp


CreateHttp proc instance:ptr ptr Windows::Web::Http::IHttpClient

    .new uri:HSTRING = NULL
    .new hr:HRESULT = WindowsCreateString(RuntimeClass_Windows_Web_Http_HttpClient,
            wcslen(RuntimeClass_Windows_Web_Http_HttpClient), &uri)

    .if (SUCCEEDED(hr))
        mov hr,RoActivateInstance(uri, instance)
        WindowsDeleteString(uri)
    .endif
    .return(hr)
    endp


CreateFiles proc h_html:HSTRING, h_text:HSTRING, name:wstring_t

   .new wlen:size_t
   .new blen:UINT32
   .new h:HANDLE
   .new file[256]:wchar_t
   .new h_len:UINT32 = 0
   .new t_len:UINT32 = 0
   .new html:wstring_t = WindowsGetStringRawBuffer(h_html, &h_len)
   .new text:wstring_t = WindowsGetStringRawBuffer(h_text, &t_len)
    imul eax,h_len,2
   .new size:UINT32 = eax
   .new buff:string_t = HeapAlloc(GetProcessHeap(), 0, size)
   .new hr:HRESULT = S_OK

    .if ( buff == NULL )
        mov hr,E_OUTOFMEMORY
    .endif

    .if (SUCCEEDED(hr))

        mov blen,WideCharToMultiByte(CP_ACP, 0, html, h_len, buff, size, nullptr, nullptr)
        mov h,CreateFile(wcscat(wcscpy(&file, name), ".htm"), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0)

        .if ( h == INVALID_HANDLE_VALUE )
            mov hr,E_HANDLE
        .else
            wprintf("Writing file %s (%d)\n", &file, blen)
            WriteFile(h, buff, blen, &wlen, 0)
            CloseHandle(h)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov blen,WideCharToMultiByte(CP_ACP, 0, text, t_len, buff, size, nullptr, nullptr)
        mov h,CreateFile(wcscat(wcscpy(&file, name), ".txt"), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0)
        .if ( h == INVALID_HANDLE_VALUE )
            mov hr,E_HANDLE
        .else
            wprintf("Writing file %s (%d)\n", &file, blen)
            WriteFile(h, buff, blen, &wlen, 0)
            CloseHandle(h)
        .endif
    .endif
    .if ( buff )
        HeapFree(GetProcessHeap(), 0, buff)
    .endif
    .return(hr)
    endp


HttpToText proc url:wstring_t, file:wstring_t

    .new html:ptr Windows::Data::Html::IHtmlUtilities = nullptr
    .new http:ptr ptr Windows::Web::Http::IHttpClient = nullptr
    .new uri:ptr Windows::Foundation::IUriRuntimeClass = nullptr
    .new hr:HRESULT = CreateIUri(url, &uri)

    .if (SUCCEEDED(hr))

        .new completedEvent:HANDLE = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS)
        .if ( completedEvent == nullptr )
            mov hr,E_FAIL
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,CreateHtml(&html)
        .if (SUCCEEDED(hr))
            mov hr,CreateHttp(&http)
            .if (SUCCEEDED(hr))
               .new async:ptr __FIAsyncOperationWithProgress_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress
                mov hr,http.GetStringAsync(uri, &async)
                .if (SUCCEEDED(hr))
                   .new Status:AsyncStatus = 0
                   .new progressHandler:ptr ProgressHandler(&completedEvent, &Status)
                    mov hr,async.put_Completed(progressHandler)
                    .if (SUCCEEDED(hr))
                        WaitForSingleObject(completedEvent, INFINITE)
                       .new res:HSTRING
                        mov hr,async.GetResults(&res)
                        .if (SUCCEEDED(hr))
                           .new string:HSTRING = nullptr
                            mov hr,html.ConvertToText(res, &string)
                            .if (SUCCEEDED(hr))
                                mov hr,CreateFiles(res, string, file)
                            .endif
                        .endif
                    .endif
                    async.Release()
                .endif
                http.Release()
            .endif
            html.Release()
        .endif
        uri.Release()
    .endif
    .return( hr )
    endp


wmain proc argc:int_t, argv:ptr wstring_t

    .new file:ptr wchar_t = "url"
    .new hr:HRESULT = E_INVALIDARG
    .if ( ecx < 2 )
        wprintf("Usage: %s <url> [[file_name]]\n", [rdx])
    .else
        .if ( ecx == 3 )
            mov file,[rcx+16]
        .endif
        mov hr,RoInitialize(RO_INIT_MULTITHREADED)
    .endif
    .if (SUCCEEDED(hr))
        mov rcx,argv
        mov hr,HttpToText([rcx+8], file)
        RoUninitialize()
    .endif
    .if (FAILED(hr))
       .new szMessage:ptr wchar_t
        mov edx,hr
        .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)
            mov hr,HRESULT_CODE(edx)
        .endif
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER or \
            FORMAT_MESSAGE_FROM_SYSTEM or \
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &szMessage,
            0,
            NULL)
        wprintf("\nError code: %08X\n\n%s", hr, szMessage)
        LocalFree(szMessage)
    .endif
    .return(0)
    endp


   assume class:rbx

ProgressHandler::QueryInterface proc uses rsi rdi riid:LPIID, ppv:ptr ptr
    ldr rsi,riid
    ldr rdi,ppv
    .ifd !IsEqualGUID(rsi, &IID___FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress)
        IsEqualGUID(rsi, &IID_IUnknown)
    .endif
    .if ( eax )
        mov [rdi],rbx
        lock inc m_refCount
       .return( S_OK )
    .endif
    .return( E_NOINTERFACE )
    endp


ProgressHandler::AddRef proc
    .return InterlockedIncrement(&m_refCount)
    endp

ProgressHandler::Release proc
    .if ( InterlockedDecrement(&m_refCount) == 0 )
        free(rbx)
        xor eax,eax
    .endif
    ret
    endp


ProgressHandler::IInvoke proc asyncInfo:ptr IAsyncActionWithProgress, status:AsyncStatus
    ldr edx,status
    mov rax,m_pStatus
    mov [rax],edx
    .if ( edx >= AsyncStatus_Completed )
        mov rcx,m_pEvent
        SetEvent([rcx])
    .endif
    .return(S_OK)
    endp


ProgressHandler::ProgressHandler proc pEvent:ptr HANDLE, pStatus:ptr AsyncStatus
    .if @ComAlloc(ProgressHandler)
        mov rbx,rax
        mov rdx,pStatus
        mov m_pStatus,rdx
        mov rdx,pEvent
        mov m_pEvent,rdx
    .endif
    ret
    endp

    end _tstart

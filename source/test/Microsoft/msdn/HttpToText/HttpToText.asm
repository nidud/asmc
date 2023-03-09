; HTTPTOTEXT.ASM--
;
; https://learn.microsoft.com/en-us/previous-versions/aspnet/jj889717(v=vs.118)
; https://learn.microsoft.com/en-us/uwp/api/windows.data.html.htmlutilities.converttotext?view=winrt-22621
;

ifdef _LIBCMT
.pragma comment(linker,"/defaultlib:libcmtd")
.pragma comment(linker,"/defaultlib:\asmc\lib\x64\combase")
.pragma comment(linker,"/defaultlib:legacy_stdio_definitions")
endif

include windows.inc
include winrt/roapi.inc
include winrt/windows.management.deployment.inc
include winrt/windows.Data.Html.inc
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
 IID_IUnknown                   GUID {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
 IID_Progress                   GUID {0x98ab9acb,0x38db,0x588f,{0xa5,0xf9,0x9f,0x48,0x4b,0x22,0x00,0xcd}}
 IID_IUriRuntimeClassFactory    GUID {0x44A9796F,0x723E,0x4FDF,{0xA2,0x18,0x03,0x3E,0x75,0xB0,0xC0,0x84}}
 IID_IHtmlUtilities             GUID {0xFEC00ADD,0x2399,0x4FAC,{0xB5,0xA7,0x05,0xE9,0xAC,0xD7,0x18,0x1D}}

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

CreateIUri endp


CreateHtml proc instance:ptr ptr Windows::Data::Html::IHtmlUtilities

    .new uri:HSTRING = NULL
    .new hr:HRESULT = WindowsCreateString(RuntimeClass_Windows_Data_Html_HtmlUtilities,
            wcslen(RuntimeClass_Windows_Data_Html_HtmlUtilities), &uri)

    .if (SUCCEEDED(hr))

        mov hr,RoGetActivationFactory(uri, &IID_IHtmlUtilities, instance)
        WindowsDeleteString(uri)
    .endif
    .return(hr)

CreateHtml endp


CreateHttp proc instance:ptr ptr Windows::Web::Http::IHttpClient

    .new uri:HSTRING = NULL
    .new hr:HRESULT = WindowsCreateString(RuntimeClass_Windows_Web_Http_HttpClient,
            wcslen(RuntimeClass_Windows_Web_Http_HttpClient), &uri)

    .if (SUCCEEDED(hr))

        mov hr,RoActivateInstance(uri, instance)
        WindowsDeleteString(uri)
    .endif
    .return(hr)

CreateHttp endp


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

CreateFiles endp


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

HttpToText endp


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

wmain endp


   assume rcx:ptr ProgressHandler

ProgressHandler::QueryInterface proc riid:LPIID, ppv:ptr ptr

    UNREFERENCED_PARAMETER(this)
    UNREFERENCED_PARAMETER(riid)

    mov rax,[rdx]
    mov rdx,[rdx+8]
    .if ( ( rax == qword ptr IID_Progress && rdx == qword ptr IID_Progress[8] ) ||
          ( rax == qword ptr IID_IUnknown && rdx == qword ptr IID_IUnknown[8] ) )

        mov [r8],rcx
        lock inc [rcx].m_refCount
       .return( S_OK )
    .endif
    .return( E_NOINTERFACE )

ProgressHandler::QueryInterface endp


ProgressHandler::AddRef proc

    UNREFERENCED_PARAMETER(this)

    .return InterlockedIncrement(&[rcx].m_refCount)

ProgressHandler::AddRef endp


ProgressHandler::Release proc

    UNREFERENCED_PARAMETER(this)

    .if ( InterlockedDecrement(&[rcx].m_refCount) == 0 )

        free(this)
        xor eax,eax
    .endif
    ret

ProgressHandler::Release endp


ProgressHandler::IInvoke proc asyncInfo:ptr IAsyncActionWithProgress, status:AsyncStatus

    UNREFERENCED_PARAMETER(this)
    UNREFERENCED_PARAMETER(asyncInfo)
    UNREFERENCED_PARAMETER(status)

    mov rax,[rcx].m_pStatus
    mov [rax],r8d

    .if ( r8d >= AsyncStatus_Completed )

        mov rcx,[rcx].m_pEvent
        SetEvent([rcx])
    .endif
    .return(S_OK)

ProgressHandler::IInvoke endp


ProgressHandler::ProgressHandler proc pEvent:ptr HANDLE, pStatus:ptr AsyncStatus

    @ComAlloc(ProgressHandler)

    mov rdx,pStatus
    mov [rax].ProgressHandler.m_pStatus,rdx
    mov rdx,pEvent
    mov [rax].ProgressHandler.m_pEvent,rdx
    ret

ProgressHandler::ProgressHandler endp

    end _tstart

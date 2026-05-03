include AmsiStream.inc
include stdio.inc
include tchar.inc

    .data
    SampleStream     wchar_t "Hello, world",0
    AppName          wchar_t "Contoso Script Engine v3.4.9999.0",0
    zAppName         equ $ - AppName
ifdef _MSVCRT
    IID_IAntimalware IID _IID_IAntimalware
    CAntimalware     IID _CAntimalware
endif

    .code

    assume class:rbx

CAmsiStreamBase::QueryInterface proc riid:LPIID, ppv:ptr ptr
    mov eax,E_INVALIDARG
    ret
    endp

CAmsiStreamBase::AddRef proc
    xor eax,eax
    ret
    endp

CAmsiStreamBase::Release proc
    free(m_contentName)
    ret
    endp


CAmsiStreamBase::CopyAttribute proc resultData:ptr, resultSize:size_t,
        bufferSize:ULONG, buffer:PBYTE, actualSize:ptr ULONG

    mov rax,actualSize
    mov [rax],r8d
    .if (r9 < r8)
        mov eax,E_NOT_SUFFICIENT_BUFFER
    .else
        memcpy_s(buffer, bufferSize, resultData, resultSize)
        mov eax,S_OK
    .endif
    ret
    endp

CAmsiStreamBase::SetContentName proc name:PWSTR

    mov m_contentName,_wcsdup(rdx)
    and rax,rax
    mov eax,S_OK
    mov edx,E_OUTOFMEMORY
    cmovz eax,edx
    ret
    endp

CAmsiStreamBase::BaseGetAttribute proc attribute:AMSI_ATTRIBUTE,
        bufferSize:ULONG, buffer:PBYTE, actualSize:ptr ULONG

    ;;
    ;; Return Values:
    ;;   S_OK: SUCCESS
    ;;   E_NOTIMPL: attribute not supported
    ;;   E_NOT_SUFFICIENT_BUFFER: need a larger buffer, required size in *retSize
    ;;   E_INVALIDARG: bad arguments
    ;;   E_NOT_VALID_STATE: object not initialized
    ;;

    wprintf(L"GetAttribute() called with: attribute = %u, bufferSize = %u\n", edx, r8d)
    mov rdx,actualSize
    .ifs (rdx == NULL || (buffer == NULL && bufferSize > 0))
        .return E_INVALIDARG
    .endif
    mov ULONG ptr [rdx],0
    .switch attribute
    .case AMSI_ATTRIBUTE_CONTENT_SIZE
        CopyAttribute(&m_contentSize, ULONGLONG, bufferSize, buffer, actualSize)
       .endc
    .case AMSI_ATTRIBUTE_CONTENT_NAME
        lea r8,[wcslen(m_contentName)+1]
        add r8,r8
        CopyAttribute(m_contentName, r8, bufferSize, buffer, actualSize)
       .endc
    .case AMSI_ATTRIBUTE_APP_NAME
        CopyAttribute(&AppName, zAppName, bufferSize, buffer, actualSize)
       .endc
    .case AMSI_ATTRIBUTE_SESSION
       .new session:HAMSISESSION ;; no session for file stream
        mov session,NULL
        CopyAttribute(&session, sizeof(session), bufferSize, buffer, actualSize)
       .endc
    .default
        mov eax,E_NOTIMPL ;; unsupport attribute
    .endsw
    ret
    endp

;; CAmsiMemoryStream

CAmsiMemoryStream::GetAttribute proc attribute:AMSI_ATTRIBUTE,
        bufferSize:ULONG, buffer:PBYTE, actualSize:ptr ULONG

  local contentAddress:ptr
  local hr:HRESULT

    mov hr,BaseGetAttribute(attribute, bufferSize, buffer, actualSize)
    .if hr == E_NOTIMPL
        .switch attribute
        .case AMSI_ATTRIBUTE_CONTENT_ADDRESS
            mov contentAddress,&SampleStream
            CopyAttribute(&contentAddress, sizeof(contentAddress), bufferSize, buffer, actualSize)
        .endsw
    .endif
    ret
    endp


CAmsiMemoryStream::Read proc position:ULONGLONG, size:ULONG,
        buffer:PBYTE, readSize:ptr ULONG

   .new hr:HRESULT = S_OK
    wprintf(L"Read() called with: position = %I64u, size = %u\n", rdx, r8d)
    mov rdx,readSize
    mov ULONG ptr [rdx],0
    .if position >= m_contentSize
        wprintf(L"Reading beyond end of stream\n")
        mov hr,HRESULT_FROM_WIN32(ERROR_HANDLE_EOF)
    .else
        mov rax,m_contentSize
        sub rax,position
        mov edx,size
        .if rdx > rax
            mov edx,eax
        .endif
        mov r8,readSize
        mov [r8],edx
        mov size,edx
        lea r8,SampleStream
        add r8,position
        memcpy_s(buffer, size, r8, size)
        mov hr,S_OK
    .endif
    mov eax,hr
    ret
    endp


CAmsiMemoryStream::CAmsiMemoryStream proc

    .if @ComAlloc(CAmsiMemoryStream)

        mov rbx,rax
        mov m_contentSize,12
        SetContentName("Sample content.txt")
        mov rax,rbx
    .endif
    ret
    endp

;;CAmsiFileStream

CAmsiFileStream::Read proc position:ULONGLONG, size:ULONG, buffer:PBYTE, readSize:ptr ULONG

  local hr:HRESULT
ifdef __OVERLAPPED
  local o:OVERLAPPED

    mov o.Pointer,rdx
    mov o.Internal,0
    mov o.InternalHigh,0
endif
    mov hr,S_OK
    wprintf(L"Read() called with: position = %I64u, size = %u\n", rdx, r8d)
ifdef __OVERLAPPED
    .if !ReadFile(m_fileHandle, buffer, size, readSize, &o)
else
    .if !ReadFile(m_fileHandle, buffer, size, readSize, NULL)
endif
        mov hr,HRESULT_FROM_WIN32R(GetLastError())
        wprintf(L"ReadFile failed with 0x%x\n", hr)
    .endif
    .return hr
    endp


CAmsiFileStream::GetAttribute proc attribute:AMSI_ATTRIBUTE, bufferSize:ULONG, buffer:PBYTE, actualSize:ptr ULONG
    BaseGetAttribute(ldr(attribute), ldr(bufferSize), ldr(buffer), actualSize)
    ret
    endp


CAmsiFileStream::CAmsiFileStream proc fileName:LPCWSTR

  local fileSize:LARGE_INTEGER

    .if @ComAlloc(CAmsiFileStream)

        mov rbx,rax
        .if FAILED(SetContentName(fileName))
            .return( 0 )
        .endif
        mov m_fileHandle,CreateFileW(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, NULL)
        .if ( rax == -1 )
            wprintf(L"Unable to open file %s, hr = 0x%x\n", fileName, HRESULT_FROM_WIN32R(GetLastError()))
            .return( 0 )
        .endif
        .ifd !GetFileSizeEx(m_fileHandle, &fileSize)
            wprintf(L"GetFileSizeEx failed with 0x%x\n", HRESULT_FROM_WIN32R(GetLastError()))
            .return 0
        .endif
        wprintf(L"CAmsiFileStream() handle: %p\n", m_fileHandle)
        mov m_contentSize,fileSize.QuadPart
        mov rax,rbx
    .endif
    ret
    endp


CStreamScanner proc antimalware:ptr IAntimalware, stream:ptr IAmsiStream

  local hr:HRESULT
  local name:PWSTR
  local provider:ptr IAntimalwareProvider
  local r:AMSI_RESULT

    wprintf(L"Calling antimalware->Scan() ...\n")
    mov rcx,antimalware
    mov hr,[rcx].IAntimalware.Scan(stream, &r, &provider)

    .if (SUCCEEDED(hr))

        wprintf(L"Scan result is %u. IsMalware: %d\n", r, AmsiResultIsMalware(r))
        .if provider

            mov hr,provider.DisplayName(&name)
            .if (SUCCEEDED(hr))

                wprintf(L"Provider display name: %s\n", name)
                CoTaskMemFree(name)
            .else
                wprintf(L"DisplayName failed with 0x%x", hr)
            .endif
        .endif
    .endif
    mov eax,hr
    ret
    endp


ScanArguments proc uses rsi rdi rbx argc:SINT, argv:ptr ptr wchar_t

  local hr:HRESULT
  local m_antimalware:ptr IAntimalware

    mov hr,CoCreateInstance(&CAntimalware, NULL, CLSCTX_INPROC_SERVER, &IID_IAntimalware, &m_antimalware)
    .return hr .if FAILED(eax)

    .if argc < 2

        ;; Scan a single memory stream.
        wprintf(L"Creating memory stream object\n")

       .new memoryStream:ptr CAmsiMemoryStream()
       .return E_OUTOFMEMORY .if rax == NULL

        mov hr,CStreamScanner(m_antimalware, memoryStream)
        .if (FAILED(hr))

            .return hr
        .endif

    .else

        ;; Scan the files passed on the command line.

        .for rsi = argv, ebx = 1: ebx < argc: ebx++

            mov rdi,[rsi+rbx*8]
            wprintf(L"Creating stream object with file name: %s\n", rdi)

            .new fileStream:ptr CAmsiFileStream(rdi)

            .return E_OUTOFMEMORY .if rax == NULL

            mov hr,CStreamScanner(m_antimalware, fileStream)
            .if (FAILED(hr))
                .return hr
            .endif
        .endf
    .endif
    .return S_OK
    endp


wmain proc argc:SINT, argv:ptr ptr WCHAR
    .new hr:HRESULT = CoInitializeEx( NULL, COINIT_MULTITHREADED )
    .if (SUCCEEDED(hr))
        mov hr,ScanArguments(argc, argv)
        CoUninitialize()
    .endif
    wprintf( L"Leaving with hr = 0x%x\n", hr )
    .return 0
    endp

    end _tstart

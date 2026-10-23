include windows.inc
include winrt/roapi.inc
include winrt/Windows.ApplicationModel.datatransfer.inc
include stdio.inc
include tchar.inc

.code

ClipboardContentOptions proc
   .new hr:HRESULT
   .new hsClipboard:HSTRING = NULL
   .new pClipboard:ptr Windows::ApplicationModel::DataTransfer::IClipboardContentOptions = NULL
   .new strClass:LPWSTR = RuntimeClass_Windows_ApplicationModel_DataTransfer_ClipboardContentOptions
    wcslen(strClass)
    mov hr,WindowsCreateString(strClass, ecx, &hsClipboard)
    .if (SUCCEEDED(hr))
        mov hr,RoActivateInstance(hsClipboard, &pClipboard)
    .endif
    .if (SUCCEEDED(hr))
       .new IsRoamable:BOOL = false
       .new IsAllowedInHistory:BOOL = false
        mov hr,pClipboard.get_IsRoamable(&IsRoamable)
        .if (SUCCEEDED(hr))
            mov hr,pClipboard.get_IsAllowedInHistory(&IsAllowedInHistory)
        .endif
        _tprintf(" ClipboardContentOptions:\n")
        _tprintf("  IsRoamable:         %d\n", IsRoamable)
        _tprintf("  IsAllowedInHistory: %d\n", IsAllowedInHistory)
    .endif
    .if ( hsClipboard )
        WindowsDeleteString(hsClipboard)
    .endif
    .if ( pClipboard )
        pClipboard.Release()
    .endif
    .return(hr)
    endp

ErrorMessage proc hr:HRESULT
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
    _tprintf("Error code: %08X\n\n%s", hr, szMessage)
    LocalFree(szMessage)
    .return(hr)
    endp

_tmain proc
    .new hr:HRESULT = RoInitialize(RO_INIT_MULTITHREADED)
    .if (SUCCEEDED(hr))
        mov hr,ClipboardContentOptions()
        RoUninitialize()
    .endif
    .if (FAILED(hr))
        .return ErrorMessage(hr)
    .endif
    .return(0)
    endp

    end _tstart

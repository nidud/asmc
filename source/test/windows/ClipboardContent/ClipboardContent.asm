; CLIPBOARDCONTENT.ASM--
;

include windows.inc
include roapi.inc
include Windows.ApplicationModel.DataTransfer.inc
include stdio.inc
include tchar.inc

.code

ClipboardContentOptions proc

    .new hsClipboard:HSTRING = NULL
    .new pClipboard:ptr Windows::ApplicationModel::DataTransfer::IClipboardContentOptions = NULL
    .new hr:HRESULT = WindowsCreateString(RuntimeClass_Windows_ApplicationModel_DataTransfer_ClipboardContentOptions,
            wcslen(RuntimeClass_Windows_ApplicationModel_DataTransfer_ClipboardContentOptions), &hsClipboard)

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
        wprintf(" ClipboardContentOptions:\n")
        wprintf("  IsRoamable:         %d\n", IsRoamable)
        wprintf("  IsAllowedInHistory: %d\n", IsAllowedInHistory)
    .endif

    .if ( hsClipboard )
        WindowsDeleteString(hsClipboard)
    .endif
    .if ( pClipboard )
        pClipboard.Release()
    .endif
    .return(hr)

ClipboardContentOptions endp


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

    wprintf("Error code: %08X\n\n%s", hr, szMessage)
    LocalFree(szMessage)
   .return(hr)

ErrorMessage endp


wmain proc

    .new hr:HRESULT = RoInitialize(RO_INIT_MULTITHREADED)
    .if (SUCCEEDED(hr))

        mov hr,ClipboardContentOptions()
        RoUninitialize()
    .endif
    .if (FAILED(hr))
        .return ErrorMessage(hr)
    .endif
    .return(0)

wmain endp

    end _tstart

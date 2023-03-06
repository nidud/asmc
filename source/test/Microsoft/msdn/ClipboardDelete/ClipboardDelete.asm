; CLIPBOARDDELETE.ASM--
;
; Call method to remove all historical items
;

include windows.inc
include winrt/roapi.inc
include winrt/Windows.ApplicationModel.DataTransfer.inc
include stdio.inc
include tchar.inc

.code

ClipboardDelete proc

    .new hsClipboard:HSTRING = NULL
    .new IID_IClipboardStatics2:GUID = {0xd2ac1b6a,0xd29f,0x554b,{0xb3,0x03,0xf0,0x45,0x23,0x45,0xfe,0x02}}
    .new pClipboard:ptr Windows::ApplicationModel::DataTransfer::IClipboardStatics2 = NULL
    .new hr:HRESULT = WindowsCreateString(RuntimeClass_Windows_ApplicationModel_DataTransfer_Clipboard,
            wcslen(RuntimeClass_Windows_ApplicationModel_DataTransfer_Clipboard), &hsClipboard)

    .if (SUCCEEDED(hr))

        mov hr,RoGetActivationFactory(hsClipboard, &IID_IClipboardStatics2, &pClipboard)
    .endif

    .if (SUCCEEDED(hr))

       .new Enabled:BOOL = false
        mov hr,pClipboard.IsHistoryEnabled(&Enabled)

        .if (SUCCEEDED(hr) && !Enabled)

            mov hr,E_NOTIMPL
            wprintf("Windows 10 clipboard history not enabled: Use Win + V keyboard shortcut to enable.\n" )
        .endif
    .endif

    .if (SUCCEEDED(hr))

       .new result:BOOL = false
        mov hr,pClipboard.ClearHistory(&result)

        .if (SUCCEEDED(hr) && result == false )

            mov hr,E_FAIL
        .endif
    .endif

    .if (SUCCEEDED(hr))

        wprintf("Clipboard history was successfully deleted. Use the Win + V keyboard shortcut to confirm.\n" )
    .endif

    .if ( hsClipboard )
        WindowsDeleteString(hsClipboard)
    .endif
    SafeRelease(pClipboard)
   .return(hr)

ClipboardDelete endp


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

    .new hr:HRESULT = RoInitialize(RO_INIT_SINGLETHREADED)
    .if (SUCCEEDED(hr))

        mov hr,ClipboardDelete()
        RoUninitialize()
    .endif
    .if (FAILED(hr))
        .return ErrorMessage(hr)
    .endif
    .return(0)

wmain endp

    end _tstart

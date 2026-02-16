; ENUMCLIPBOARD.ASM--
;
; Accessing Clipboard History
;
; https://blog.mzikmund.com/2020/09/accessing-clipboard-history-in-uwp/
; https://devblogs.microsoft.com/oldnewthing/20230302-00/?p=107889
;

include windows.inc
include roapi.inc
include Windows.ApplicationModel.DataTransfer.inc
include stdio.inc
include tchar.inc

.code

GetClipboardHistory proc p:ptr ptr Windows::ApplicationModel::DataTransfer::IClipboardHistoryItemsResult

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
       .new pAsync:ptr __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CClipboardHistoryItemsResult = NULL
        mov hr,pClipboard.GetHistoryItemsAsync(&pAsync)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,pAsync.GetResults(p)
    .endif
    .if ( hsClipboard )
        WindowsDeleteString(hsClipboard)
    .endif
    SafeRelease(pAsync)
    SafeRelease(pClipboard)
   .return(hr)
    endp


GetTextFormat proc format:ptr HSTRING

   .new hsFormat:HSTRING = NULL
   .new IID_IStandardDataFormatsStatics:GUID = {0x7ed681a1,0xa880,0x40c9,{0xb4,0xed,0x0b,0xee,0x1e,0x15,0xf5,0x49}}
   .new hr:HRESULT = WindowsCreateString(RuntimeClass_Windows_ApplicationModel_DataTransfer_StandardDataFormats,
            wcslen(RuntimeClass_Windows_ApplicationModel_DataTransfer_StandardDataFormats), &hsFormat)

    .if (SUCCEEDED(hr))

       .new pDataFormats:ptr Windows::ApplicationModel::DataTransfer::IStandardDataFormatsStatics = NULL
        mov hr,RoGetActivationFactory(hsFormat, &IID_IStandardDataFormatsStatics, &pDataFormats)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pDataFormats.get_Text(format)
    .endif

    .if ( hsFormat )

        WindowsDeleteString(hsFormat)
    .endif

    .if ( pDataFormats )

        pDataFormats.Release()
    .endif
    .return(hr)
    endp


DumpClipboardHistoryAsync proc uses rbx

    .new result:ptr Windows::ApplicationModel::DataTransfer::IClipboardHistoryItemsResult = NULL
    .new formatId:HSTRING = NULL
    .new hr:HRESULT = GetClipboardHistory(&result)

    .if (SUCCEEDED(hr))
        mov hr,GetTextFormat(&formatId)
    .endif

    .if (SUCCEEDED(hr))

       .new items:ptr __FIVectorView_1_Windows__CApplicationModel__CDataTransfer__CClipboardHistoryItem = NULL
       .new value:Windows::ApplicationModel::DataTransfer::ClipboardHistoryItemsResultStatus = 0
        mov hr,result.get_Status(&value)

        .if (SUCCEEDED(hr))
            .if ( value == Windows::ApplicationModel::DataTransfer::ClipboardHistoryItemsResultStatus_Success )
                mov hr,result.get_Items(&items)
            .else
                mov hr,E_FAIL
            .endif
        .endif
    .endif

    .if (SUCCEEDED(hr))

       .new count:UINT32 = 0
        mov hr,items.get_Size(&count)
    .endif

    .if (SUCCEEDED(hr))

        .new item:ptr Windows::ApplicationModel::DataTransfer::IClipboardHistoryItem
        .new content:ptr Windows::ApplicationModel::DataTransfer::IDataPackageView
        .new hsId:HSTRING
        .new hsText:HSTRING
        .new sText:LPWSTR
        .new sId:LPWSTR
        .new length:UINT32
        .new isText:BOOL
        .new pText:ptr __FIAsyncOperation_1_HSTRING

        .for ( ebx = 0 : ebx < count : ebx++ )

            mov hr,items.GetAt(ebx, &item)
            .if (SUCCEEDED(hr))

                mov hr,item.get_Id(&hsId)
                .if (SUCCEEDED(hr))

                    mov sId,WindowsGetStringRawBuffer(hsId, &length)
                    mov hr,item.get_Content(&content)
                    .if (SUCCEEDED(hr))

                        mov hr,content.Contains(formatId, &isText)
                        .if (SUCCEEDED(hr))

                            .if ( isText )

                                mov hr,content.GetTextAsync(&pText)
                                .if (SUCCEEDED(hr))

                                    mov hr,pText.GetResults(&hsText)
                                    .if (SUCCEEDED(hr))

                                        mov sText,WindowsGetStringRawBuffer(hsText, &length)
                                        wprintf("%s: %s\n", sId, sText)
                                    .endif
                                    pText.Release()
                                .endif
                            .else
                                wprintf("%s: (no text content)\n", sId)
                            .endif
                        .endif
                        content.Release()
                    .endif
                .endif
                item.Release()
            .endif
        .endf
    .endif
    SafeRelease(items)
    SafeRelease(result)
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

    wprintf("Error code: %08X\n\n%s", hr, szMessage)
    LocalFree(szMessage)
   .return(hr)
    endp


wmain proc
    .new hr:HRESULT = RoInitialize(RO_INIT_SINGLETHREADED)
    .if (SUCCEEDED(hr))
        mov hr,DumpClipboardHistoryAsync()
        RoUninitialize()
    .endif
    .if (FAILED(hr))
        .return ErrorMessage(hr)
    .endif
    .return(0)
    endp

    end _tstart

include stdio.inc
include msxml6.inc
include tchar.inc

ifdef __PE__
.data
 CLSID_DOMDocument60 GUID _CLSID_DOMDocument60
 IID_IXMLDOMDocument GUID _IID_IXMLDOMDocument
endif
.code

CHK_HR proto watcall stmt:HRESULT {
    mov hr,stmt
    .if (FAILED(hr))
        jmp CleanUp
    .endif
    }

CHK_ALLOC proto fastcall p:abs {
    .if ( p == NULL )

        mov hr,E_OUTOFMEMORY
        jmp CleanUp
    .endif
    }

; Helper function to create a DOM instance.

CreateAndInitDOM proc ppDoc:ptr ptr IXMLDOMDocument

    .new hr:HRESULT = CoCreateInstance(
            &CLSID_DOMDocument60,
            NULL,
            CLSCTX_INPROC_SERVER,
            &IID_IXMLDOMDocument,
            ppDoc)

    .if (SUCCEEDED(hr))

        ; these methods should not fail so don't inspect result

        mov rcx,ppDoc
       .new p:ptr IXMLDOMDocument = [rcx]
        p.put_async(VARIANT_FALSE)
        p.put_validateOnParse(VARIANT_FALSE)
        p.put_resolveExternals(VARIANT_FALSE)
    .endif
    .return hr

CreateAndInitDOM endp

; Helper function to create a VT_BSTR variant from a null terminated string.

VariantFromString proc wszValue:PCWSTR, Variant:ptr VARIANT

    .if ( SysAllocString(wszValue) == NULL )
        .return E_OUTOFMEMORY
    .endif
    mov rcx,Variant
    mov [rcx].VARIANT.vt,VT_BSTR
    mov [rcx].VARIANT.bstrVal,rax
   .return S_OK

VariantFromString endp

saveDOM proc

   .new hr:HRESULT = S_OK
   .new pXMLDom:ptr IXMLDOMDocument = NULL
   .new pXMLErr:ptr IXMLDOMParseError = NULL
   .new bstrXML:BSTR = NULL
   .new bstrErr:BSTR = NULL
   .new varStatus:VARIANT_BOOL
   .new varFileName:VARIANT

    VariantInit(&varFileName)

    CHK_HR(CreateAndInitDOM(&pXMLDom))

    mov bstrXML,SysAllocString(L"<r>\n<t>top</t>\n<b>bottom</b>\n</r>")
    CHK_ALLOC(bstrXML)
    CHK_HR(pXMLDom.loadXML(bstrXML, &varStatus))

    .if ( varStatus == VARIANT_TRUE )

        CHK_HR(pXMLDom.get_xml(&bstrXML))
        wprintf(L"XML DOM loaded from app:\n%s\n", bstrXML)

        VariantFromString(L"myData.xml", &varFileName)
        CHK_HR(pXMLDom.save(varFileName))
        wprintf(L"XML DOM saved to myData.xml\n")

    .else

        ; Failed to load xml, get last parsing error
        CHK_HR(pXMLDom.get_parseError(&pXMLErr))
        CHK_HR(pXMLErr.get_reason(&bstrErr))
        wprintf(L"Failed to load DOM from xml string. %s\n", bstrErr)
    .endif

CleanUp:
    SafeRelease(pXMLDom)
    SafeRelease(pXMLErr)
    SysFreeString(bstrXML)
    SysFreeString(bstrErr)
    VariantClear(&varFileName)
   .return hr

saveDOM endp

wmain proc

    .new hr:HRESULT = CoInitialize(NULL)
    .if (SUCCEEDED(hr))

        mov hr,saveDOM()
        .if (FAILED(hr))
            wprintf(L"Failed.\n")
        .endif
        CoUninitialize()
    .endif
    .return 0

wmain endp

    end _tstart


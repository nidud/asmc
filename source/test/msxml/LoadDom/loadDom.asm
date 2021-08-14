; XML DOM load sample
;
; Demonstrates how to create an XML DOM instance and load its content from an
; external XML data file.
;
; Operating system requirements
; -----------------------------
;
; Client Windows 8.1
; Server Windows Server 2012 R2
;
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

VariantFromString proc wszValue:PCWSTR, Variant:ptr VARIANT

    .if ( SysAllocString(wszValue) == NULL )
        .return E_OUTOFMEMORY
    .endif
    mov rcx,Variant
    mov [rcx].VARIANT.vt,VT_BSTR
    mov [rcx].VARIANT.bstrVal,rax
   .return S_OK

VariantFromString endp


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


loadDOM proc

    .new hr:HRESULT = S_OK
    .new pXMLDom:ptr IXMLDOMDocument = NULL
    .new pXMLErr:ptr IXMLDOMParseError = NULL
    .new bstrXML:BSTR = NULL
    .new bstrErr:BSTR = NULL
    .new varStatus:VARIANT_BOOL
    .new varFileName:VARIANT

    VariantInit(&varFileName)

    CHK_HR(CreateAndInitDOM(&pXMLDom))

    ; XML file name to load

    CHK_HR(VariantFromString(L"stocks.xml", &varFileName))
    CHK_HR(pXMLDom.load(varFileName, &varStatus))
    .if (varStatus == VARIANT_TRUE)

        CHK_HR(pXMLDom.get_xml(&bstrXML))
        wprintf(L"XML DOM loaded from stocks.xml:\n%s\n", bstrXML)

    .else

        ; Failed to load xml, get last parsing error

        CHK_HR(pXMLDom.get_parseError(&pXMLErr))
        CHK_HR(pXMLErr.get_reason(&bstrErr))
        wprintf(L"Failed to load DOM from stocks.xml. %s\n", bstrErr)
    .endif

CleanUp:
    SafeRelease(pXMLDom)
    SafeRelease(pXMLErr)
    SysFreeString(bstrXML)
    SysFreeString(bstrErr)
    VariantClear(&varFileName)
    ret

loadDOM endp

wmain proc

    .if(SUCCEEDED(CoInitialize(NULL)))

        loadDOM()
        CoUninitialize()
    .endif
    .return 0

wmain endp

    end _tstart


include stdio.inc
include msxml6.inc
include tchar.inc

ifdef __PE__
.data
 CLSID_DOMDocument60 GUID _CLSID_DOMDocument60
 IID_IXMLDOMDocument GUID _IID_IXMLDOMDocument
 IID_IDispatch       GUID _IID_IDispatch
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

LoadXMLFile proc pXMLDom:ptr IXMLDOMDocument, lpszXMLFile:LPCWSTR

    .new hr:HRESULT = S_OK
    .new varStatus:VARIANT_BOOL
    .new varFileName:VARIANT
    .new pXMLErr:ptr IXMLDOMParseError = NULL
    .new bstrErr:BSTR = NULL

    VariantInit(&varFileName)
    CHK_HR(VariantFromString(lpszXMLFile, &varFileName))
    CHK_HR(pXMLDom.load(varFileName, &varStatus))

    ; load xml failed

    .if ( varStatus != VARIANT_TRUE )

        CHK_HR(pXMLDom.get_parseError(&pXMLErr))
        CHK_HR(pXMLErr.get_reason(&bstrErr))
        mov hr,E_FAIL
        wprintf(L"Failed to load %s:\n%s\n", lpszXMLFile, bstrErr)
    .endif

CleanUp:
    SafeRelease(pXMLErr)
    SysFreeString(bstrErr)
    VariantClear(&varFileName)
    ret

LoadXMLFile endp

; Helper function to transform DOM to a string.

TransformDOM2Str proc pXMLDom:ptr IXMLDOMDocument, pXSLDoc:ptr IXMLDOMDocument

    .new hr:HRESULT = S_OK
    .new bstrResult:BSTR = NULL
    CHK_HR(pXMLDom.transformNode(pXSLDoc, &bstrResult))
    wprintf(L"Output from transformNode:\n%s\n", bstrResult)

CleanUp:
    SysFreeString(bstrResult)
   .return hr

TransformDOM2Str endp

; Helper function to transform DOM to an object.

TransformDOM2Obj proc pXMLDom:ptr IXMLDOMDocument, pXSLDoc:ptr IXMLDOMDocument

    .new hr:HRESULT = S_OK
    .new bstrXML:BSTR = NULL
    .new pXMLOut:ptr IXMLDOMDocument = NULL
    .new pDisp:ptr IDispatch = NULL
    .new varDisp:VARIANT
    .new varFileName:VARIANT

    VariantInit(&varDisp)
    VariantInit(&varFileName)

    CHK_HR(CreateAndInitDOM(&pXMLOut))
    CHK_HR(pXMLOut.QueryInterface(&IID_IDispatch, &pDisp))

    mov V_VT(&varDisp),VT_DISPATCH
    mov V_DISPATCH(rcx),pDisp
    mov pDisp,NULL

    CHK_HR(pXMLDom.transformNodeToObject(pXSLDoc, varDisp))
    CHK_HR(pXMLOut.get_xml(&bstrXML))
    wprintf(L"Output from transformNodeToObject:\n%s\n", bstrXML)

    ; save to stocks.htm
    CHK_HR(VariantFromString(L"stocks.htm", &varFileName))
    CHK_HR(pXMLOut.save(varFileName))
    wprintf(L"The above output is also saved in stocks.htm.\n")

CleanUp:
    VariantClear(&varDisp)
    VariantClear(&varFileName)
    SysFreeString(bstrXML)
    SafeRelease(pXMLOut)
    .return hr

TransformDOM2Obj endp

XSLT proc

    .new hr:HRESULT = S_OK
    .new pXMLDom:ptr IXMLDOMDocument = NULL
    .new pXSLDoc:ptr IXMLDOMDocument = NULL

    CHK_HR(CreateAndInitDOM(&pXMLDom))
    CHK_HR(LoadXMLFile(pXMLDom, L"stocks.xml"))
    CHK_HR(CreateAndInitDOM(&pXSLDoc))
    CHK_HR(LoadXMLFile(pXSLDoc, L"stocks.xsl"))

    ; Transform dom to a string:
    CHK_HR(TransformDOM2Str(pXMLDom, pXSLDoc))
    ; Transform dom to another dom object:
    CHK_HR(TransformDOM2Obj(pXMLDom, pXSLDoc))

CleanUp:
    SafeRelease(pXSLDoc)
    SafeRelease(pXMLDom)
    ret

XSLT endp

wmain proc

    .if(SUCCEEDED(CoInitialize(NULL)))

        XSLT()
        CoUninitialize()
    .endif
    .return 0

wmain endp

    end _tstart


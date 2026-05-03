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

VariantFromString proc wszValue:PCWSTR, Variant:ptr VARIANT

    .if ( SysAllocString(wszValue) == NULL )
        .return E_OUTOFMEMORY
    .endif
    mov rcx,Variant
    mov [rcx].VARIANT.vt,VT_BSTR
    mov [rcx].VARIANT.bstrVal,rax
   .return S_OK

VariantFromString endp

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
        p.put_preserveWhiteSpace(VARIANT_TRUE)
    .endif
    .return hr

CreateAndInitDOM endp

; Helper function to display parse error.
; It returns error code of the parse error.

ReportParseError proc pDoc:ptr IXMLDOMDocument, pwszDesc:ptr WCHAR

   .new hr:HRESULT = S_OK
   .new hrRet:HRESULT = E_FAIL ; Default error code if failed to get from parse error.
   .new pXMLErr:ptr IXMLDOMParseError = NULL
   .new bstrReason:BSTR = NULL

    CHK_HR(pDoc.get_parseError(&pXMLErr))
    CHK_HR(pXMLErr.get_errorCode(&hrRet))
    CHK_HR(pXMLErr.get_reason(&bstrReason))
    wprintf(L"%s\n%s\n", pwszDesc, bstrReason)

CleanUp:
    SafeRelease(pXMLErr)
    SysFreeString(bstrReason)
   .return hrRet
ReportParseError endp

queryNodes proc uses rbx

   .new hr:HRESULT = S_OK
   .new pXMLDom:ptr IXMLDOMDocument = NULL
   .new pNodes:ptr IXMLDOMNodeList = NULL
   .new pNode:ptr IXMLDOMNode = NULL

   .new bstrQuery1:BSTR = NULL
   .new bstrQuery2:BSTR = NULL
   .new bstrNodeName:BSTR = NULL
   .new bstrNodeValue:BSTR = NULL
   .new varStatus:VARIANT_BOOL
   .new varFileName:VARIANT

    VariantInit(&varFileName)

    CHK_HR(CreateAndInitDOM(&pXMLDom))

    CHK_HR(VariantFromString(L"stocks.xml", &varFileName))
    CHK_HR(pXMLDom.load(varFileName, &varStatus))
    .if ( varStatus != VARIANT_TRUE )

        CHK_HR(ReportParseError(pXMLDom, L"Failed to load DOM from stocks.xml."))
    .endif

    ; Query a single node.
    mov bstrQuery1,SysAllocString(L"//stock[1]/*")
    CHK_ALLOC(bstrQuery1)
    CHK_HR(pXMLDom.selectSingleNode(bstrQuery1, &pNode))
    .if ( pNode )

        wprintf(L"Result from selectSingleNode:\n")
        CHK_HR(pNode.get_nodeName(&bstrNodeName))
        wprintf(L"Node, <%s>:\n", bstrNodeName)
        SysFreeString(bstrNodeName)

        CHK_HR(pNode.get_xml(&bstrNodeValue))
        wprintf(L"\t%s\n\n", bstrNodeValue)
        SysFreeString(bstrNodeValue)
        SafeRelease(pNode)

    .else

        CHK_HR(ReportParseError(pXMLDom, L"Error while calling selectSingleNode."))
    .endif

    ; Query a node-set.
    mov bstrQuery2,SysAllocString(L"//stock[1]/*")
    CHK_ALLOC(bstrQuery2)
    CHK_HR(pXMLDom.selectNodes(bstrQuery2, &pNodes))
    .if ( pNodes )

        wprintf(L"Results from selectNodes:\n")
        ; get the length of node-set
       .new length:LONG
        CHK_HR(pNodes.get_length(&length))
        .for ( ebx = 0: ebx < length: ebx++ )

            CHK_HR(pNodes.get_item(ebx, &pNode))
            CHK_HR(pNode.get_nodeName(&bstrNodeName))
            wprintf(L"Node (%d), <%s>:\n", ebx, bstrNodeName)
            SysFreeString(bstrNodeName)

            CHK_HR(pNode.get_xml(&bstrNodeValue))
            wprintf(L"\t%s\n", bstrNodeValue)
            SysFreeString(bstrNodeValue)
            SafeRelease(pNode)
        .endf

    .else

        CHK_HR(ReportParseError(pXMLDom, L"Error while calling selectNodes."))
    .endif

CleanUp:
    SafeRelease(pXMLDom)
    SafeRelease(pNodes)
    SafeRelease(pNode)
    SysFreeString(bstrQuery1)
    SysFreeString(bstrQuery2)
    SysFreeString(bstrNodeName)
    SysFreeString(bstrNodeValue)
    VariantClear(&varFileName)
   .return hr
queryNodes endp

wmain proc

    .if (SUCCEEDED(CoInitialize(NULL)))

        .if(FAILED(queryNodes()))

            wprintf(L"Failed.\n")
        .endif
        CoUninitialize()
    .endif
    .return 0

wmain endp

    end _tstart


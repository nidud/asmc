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
    .return( S_OK )
    endp

; Helper function to create a DOM instance.

CreateAndInitDOM proc ppDoc:ptr ptr IXMLDOMDocument

    .new hr:HRESULT = CoCreateInstance(&CLSID_DOMDocument60, NULL,
            CLSCTX_INPROC_SERVER, &IID_IXMLDOMDocument, ppDoc)

    .if (SUCCEEDED(hr))

        ; these methods should not fail so don't inspect result

        mov rcx,ppDoc
       .new p:ptr IXMLDOMDocument = [rcx]
        p.put_async(VARIANT_FALSE)
        p.put_validateOnParse(VARIANT_FALSE)
        p.put_resolveExternals(VARIANT_FALSE)
        p.put_preserveWhiteSpace(VARIANT_TRUE)
    .endif
    .return( hr )
    endp

; Helper that allocates the BSTR param for the caller.

CreateElement proc pXMLDom:ptr IXMLDOMDocument, wszName:PCWSTR, ppElement:ptr ptr IXMLDOMElement

   .new hr:HRESULT = S_OK

    xor eax,eax
    mov rcx,ppElement
    mov [rcx],rax
   .new bstrName:BSTR = SysAllocString(wszName)
    CHK_ALLOC(bstrName)
    CHK_HR(pXMLDom.createElement(bstrName, ppElement))
CleanUp:
    SysFreeString(bstrName)
    .return( hr )
    endp

; Helper function to append a child to a parent node.

AppendChildToParent proc pChild:ptr IXMLDOMNode, pParent:ptr IXMLDOMNode

   .new hr:HRESULT = S_OK
   .new pChildOut:ptr IXMLDOMNode = NULL
    CHK_HR(pParent.appendChild(pChild, &pChildOut))
CleanUp:
    SafeRelease(pChildOut)
    .return( hr )
    endp

; Helper function to create and add a processing instruction to a document node.

CreateAndAddPINode proc pDom:ptr IXMLDOMDocument, wszTarget:PCWSTR, wszData:PCWSTR

   .new hr:HRESULT = S_OK
   .new pPI:ptr IXMLDOMProcessingInstruction = NULL
   .new bstrTarget:BSTR = SysAllocString(wszTarget)
   .new bstrData:BSTR = SysAllocString(wszData)
    CHK_ALLOC(bstrTarget)
    CHK_ALLOC(bstrData)
    CHK_HR(pDom.createProcessingInstruction(bstrTarget, bstrData, &pPI))
    CHK_HR(AppendChildToParent(pPI, pDom))

CleanUp:
    SafeRelease(pPI)
    SysFreeString(bstrTarget)
    SysFreeString(bstrData)
   .return hr
    endp

; Helper function to create and add a comment to a document node.

CreateAndAddCommentNode proc pDom:ptr IXMLDOMDocument, wszComment:PCWSTR

   .new hr:HRESULT = S_OK
   .new pComment:ptr IXMLDOMComment = NULL

   .new bstrComment:BSTR = SysAllocString(wszComment)
    CHK_ALLOC(bstrComment)
    CHK_HR(pDom.createComment(bstrComment, &pComment))
    CHK_HR(AppendChildToParent(pComment, pDom))
CleanUp:
    SafeRelease(pComment)
    SysFreeString(bstrComment)
    .return( hr )
    endp

; Helper function to create and add an attribute to a parent node.

CreateAndAddAttributeNode proc pDom:ptr IXMLDOMDocument, wszName:PCWSTR,
        wszValue:PCWSTR, pParent:ptr IXMLDOMElement

   .new hr:HRESULT = S_OK
   .new pAttribute:ptr IXMLDOMAttribute = NULL
   .new pAttributeOut:ptr IXMLDOMAttribute = NULL ; Out param that is not used
   .new bstrName:BSTR = NULL
   .new varValue:VARIANT

    VariantInit(&varValue)
    mov bstrName,SysAllocString(wszName)
    CHK_ALLOC(bstrName)
    CHK_HR(VariantFromString(wszValue, &varValue))
    CHK_HR(pDom.createAttribute(bstrName, &pAttribute))
    CHK_HR(pAttribute.put_value(varValue))
    CHK_HR(pParent.setAttributeNode(pAttribute, &pAttributeOut))

CleanUp:
    SafeRelease(pAttribute)
    SafeRelease(pAttributeOut)
    SysFreeString(bstrName)
    VariantClear(&varValue)
    .return( hr )
    endp

; Helper function to create and append a text node to a parent node.

CreateAndAddTextNode proc pDom:ptr IXMLDOMDocument, wszText:PCWSTR, pParent:ptr IXMLDOMNode

   .new hr:HRESULT = S_OK
   .new pText:ptr IXMLDOMText = NULL

   .new bstrText:BSTR = SysAllocString(wszText)
    CHK_ALLOC(bstrText)
    CHK_HR(pDom.createTextNode(bstrText, &pText))
    CHK_HR(AppendChildToParent(pText, pParent))
CleanUp:
    SafeRelease(pText)
    SysFreeString(bstrText)
    .return( hr )
    endp

; Helper function to create and append a CDATA node to a parent node.

CreateAndAddCDATANode proc pDom:ptr IXMLDOMDocument, wszCDATA:PCWSTR, pParent:ptr IXMLDOMNode

   .new hr:HRESULT = S_OK
   .new pCDATA:ptr IXMLDOMCDATASection = NULL

   .new bstrCDATA:BSTR = SysAllocString(wszCDATA)
    CHK_ALLOC(bstrCDATA)
    CHK_HR(pDom.createCDATASection(bstrCDATA, &pCDATA))
    CHK_HR(AppendChildToParent(pCDATA, pParent))
CleanUp:
    SafeRelease(pCDATA)
    SysFreeString(bstrCDATA)
    .return( hr )
    endp

; Helper function to create and append an element node to a parent node, and pass the newly created
; element node to caller if it wants.

CreateAndAddElementNode proc pDom:ptr IXMLDOMDocument, wszName:PCWSTR,
        wszNewline:PCWSTR, pParent:ptr IXMLDOMNode, ppElement:ptr ptr IXMLDOMElement

   .new hr:HRESULT = S_OK
   .new pElement:ptr IXMLDOMElement = NULL

    CHK_HR(CreateElement(pDom, wszName, &pElement))
    ; Add NEWLINE+TAB for identation before this element.
    CHK_HR(CreateAndAddTextNode(pDom, wszNewline, pParent))
    ; Append this element to parent.
    CHK_HR(AppendChildToParent(pElement, pParent))

CleanUp:
    mov rcx,ppElement
    .if ( rcx )
        mov [rcx],pElement ; Caller is repsonsible to release this element.
    .else
        SafeRelease(pElement) ; Caller is not interested on this element, so release it.
    .endif
    .return( hr )
    endp

dynamDOM proc

   .new hr:HRESULT = S_OK
   .new pXMLDom:ptr IXMLDOMDocument = NULL
   .new pRoot:ptr IXMLDOMElement = NULL
   .new pNode:ptr IXMLDOMElement = NULL
   .new pSubNode:ptr IXMLDOMElement = NULL
   .new pDF:ptr IXMLDOMDocumentFragment = NULL

   .new bstrXML:BSTR = NULL
   .new varFileName:VARIANT
    VariantInit(&varFileName)

    CHK_HR(CreateAndInitDOM(&pXMLDom))

    ; Create a processing instruction element.
    CHK_HR(CreateAndAddPINode(pXMLDom, L"xml", L"version='1.0'"))

    ; Create a comment element.
    CHK_HR(CreateAndAddCommentNode(pXMLDom, L"sample xml file created using XML DOM object."))

    ; Create the root element.
    CHK_HR(CreateElement(pXMLDom, L"root", &pRoot))

    ; Create an attribute for the <root> element, with name "created" and value "using dom".
    CHK_HR(CreateAndAddAttributeNode(pXMLDom, L"created", L"using dom", pRoot))

    ; Next, we will create and add three nodes to the <root> element.
    ; Create a <node1> to hold text content.
    CHK_HR(CreateAndAddElementNode(pXMLDom, L"node1", L"\n\t", pRoot, &pNode))
    CHK_HR(CreateAndAddTextNode(pXMLDom, L"some character data", pNode))
    SafeRelease(pNode)

    ; Create a <node2> to hold a CDATA section.
    CHK_HR(CreateAndAddElementNode(pXMLDom, L"node2", L"\n\t", pRoot, &pNode))
    CHK_HR(CreateAndAddCDATANode(pXMLDom, L"<some mark-up text>", pNode))
    SafeRelease(pNode)

    ; Create <node3> to hold a doc fragment with three sub-elements.
    CHK_HR(CreateAndAddElementNode(pXMLDom, L"node3", L"\n\t", pRoot, &pNode))

    ; Create a document fragment to hold three sub-elements.
    CHK_HR(pXMLDom.createDocumentFragment(&pDF))

    ; Create 3 subnodes.
    CHK_HR(CreateAndAddElementNode(pXMLDom, L"subNode1", L"\n\t\t", pDF, NULL))
    CHK_HR(CreateAndAddElementNode(pXMLDom, L"subNode2", L"\n\t\t", pDF, NULL))
    CHK_HR(CreateAndAddElementNode(pXMLDom, L"subNode3", L"\n\t\t", pDF, NULL))
    CHK_HR(CreateAndAddTextNode(pXMLDom, L"\n\t", pDF))

    ; Append pDF to <node3>.
    CHK_HR(AppendChildToParent(pDF, pNode))
    SafeRelease(pNode)

    ; Add NEWLINE for identation before </root>.
    CHK_HR(CreateAndAddTextNode(pXMLDom, L"\n", pRoot))
    ; add <root> to document
    CHK_HR(AppendChildToParent(pRoot, pXMLDom))

    CHK_HR(pXMLDom.get_xml(&bstrXML))
    wprintf(L"Dynamically created DOM:\n%s\n", bstrXML)

    CHK_HR(VariantFromString(L"dynamDOM.xml", &varFileName))
    CHK_HR(pXMLDom.save(varFileName))
    wprintf(L"DOM saved to dynamDOM.xml\n")

CleanUp:
    SafeRelease(pXMLDom)
    SafeRelease(pRoot)
    SafeRelease(pNode)
    SafeRelease(pDF)
    SafeRelease(pSubNode)
    SysFreeString(bstrXML)
    VariantClear(&varFileName)
    ret
    endp

wmain proc
    .if (SUCCEEDED(CoInitialize(NULL)))
        dynamDOM()
        CoUninitialize()
    .endif
    .return 0
    endp

    end _tstart

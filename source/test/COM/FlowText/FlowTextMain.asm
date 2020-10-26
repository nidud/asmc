include common.inc

include LayoutToCanvasBuilder.inc

TEXT_STRING equ < \
    "The XML Paper Specification (XPS) provides users and developers with a "   \
    "robust, open and trustworthy format for electronic paper. The XML Paper "  \
    "Specification describes electronic paper in a way that can be read by "    \
    "hardware, read by software, and read by people. XPS documents print "      \
    "better, can be shared easier, are more secure and can be archived with "   \
    "confidence." >

.code

;;
;; This method creates DWrite text layout with several different glyph runs
;; NOTE: Modification in this method will exercise various code paths in sample.
;; Interesting cases: sideways, right-to-left, non-english unicode string, etc.
;;

MakeTextLayout proc ppTextLayout:ptr ptr IDWriteTextLayout

  local hr                  : HRESULT
  local pDWriteFactory      : ptr IDWriteFactory
  local pTextFormat         : ptr IDWriteTextFormat
  local pResultLayout       : ptr IDWriteTextLayout
  local modifyFormatRange   : DWRITE_TEXT_RANGE

    xor eax,eax
    mov hr,eax
    mov pDWriteFactory,rax
    mov pTextFormat,rax
    mov pResultLayout,rax
    mov modifyFormatRange.length,20

    mov hr,DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            &IID_IDWriteFactory,
            &pDWriteFactory
            )

    .if (SUCCEEDED(hr))

        mov hr,pDWriteFactory.CreateTextFormat(
                L"Arial",
                NULL, ;;__maybenull IDWriteFontCollection* fontCollection,
                DWRITE_FONT_WEIGHT_REGULAR,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                12.0,
                L"en-US", ;;localeName,
                &pTextFormat
                );
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pTextFormat.SetWordWrapping( DWRITE_WORD_WRAPPING_WRAP )
    .endif

    .if (SUCCEEDED(hr))

        mov r8d,wcslen(TEXT_STRING)
        mov hr,pDWriteFactory.CreateTextLayout(
                TEXT_STRING, ;; at least 100 characters
                r8d,
                pTextFormat,
                400.0, ;; limit text width to cause line breaks if text is long enough
                400.0,
                &pResultLayout
                )
    .endif

    .if (SUCCEEDED(hr))

        mov modifyFormatRange.startPosition,10
        mov hr,pResultLayout.SetFontSize( 16.0, modifyFormatRange )
    .endif

    .if (SUCCEEDED(hr))

        mov modifyFormatRange.startPosition,35
        mov hr,pResultLayout.SetFontFamilyName( L"Courier New", modifyFormatRange )
    .endif

    .if (SUCCEEDED(hr))

        mov modifyFormatRange.startPosition,60
        mov hr,pResultLayout.SetFontStyle( DWRITE_FONT_STYLE_ITALIC, modifyFormatRange )
    .endif

    .if (SUCCEEDED(hr))

        mov modifyFormatRange.startPosition,85
        mov hr,pResultLayout.SetUnderline( TRUE, modifyFormatRange )
    .endif

    .if (SUCCEEDED(hr))

        mov modifyFormatRange.startPosition,110
        mov hr,pResultLayout.SetStrikethrough( TRUE, modifyFormatRange )
    .endif

    .if (SUCCEEDED(hr))

        mov rax,ppTextLayout
        mov rcx,pResultLayout
        mov [rax],rcx

        [rcx].IDWriteTextLayout.AddRef()
    .endif

    ;; cleanup resources
    .if (pResultLayout)

        pResultLayout.Release()
        mov pResultLayout,NULL
    .endif
    .if (pTextFormat)

        pTextFormat.Release()
        mov pTextFormat,NULL
    .endif
    .if (pDWriteFactory)

        pDWriteFactory.Release()
        mov pDWriteFactory,NULL
    .endif

    .return hr

MakeTextLayout endp

;;
;; This method saves XPS OM canvas to one page XPS file on Desktop.
;;

SaveCanvasToXpsViaPackage proc uses rdi \
    xpsFactory:ptr IXpsOMObjectFactory,
    canvas:ptr IXpsOMCanvas


    local hr                : HRESULT

    local xpsPackage        : ptr IXpsOMPackage
    local xpsFDS            : ptr IXpsOMDocumentSequence
    local fixedDocuments    : ptr IXpsOMDocumentCollection
    local xpsFD             : ptr IXpsOMDocument
    local pageRefs          : ptr IXpsOMPageReferenceCollection
    local xpsPageRef        : ptr IXpsOMPageReference
    local xpsPage           : ptr IXpsOMPage
    local opcPartUri        : ptr IOpcPartUri
    local pageVisuals       : ptr IXpsOMVisualCollection
    local pageSize          : XPS_SIZE
    local szDesktopPath[MAX_PATH]:WCHAR

    lea rdi,szDesktopPath
    xor eax,eax
    mov ecx,@ReservedStack
    rep stosb
    mov pageSize.width,400.0
    mov pageSize.height,600.0

    ;; Create trunk elements of XPS object model
    mov hr,xpsFactory.CreatePackage( &xpsPackage )

    .if (SUCCEEDED(hr))

        mov hr,xpsFactory.CreatePartUri( "/FixedDocumentSequence.fdseq", &opcPartUri )
    .endif

    .if (SUCCEEDED(hr))

        mov hr,xpsFactory.CreateDocumentSequence( opcPartUri, &xpsFDS )
        opcPartUri.Release()
        mov opcPartUri,NULL
    .endif

    .if (SUCCEEDED(hr))

        mov hr,xpsFactory.CreatePartUri( "/Documents/1/FixedDocument.fdoc", &opcPartUri )
    .endif

    .if (SUCCEEDED(hr))

        mov hr,xpsFactory.CreateDocument( opcPartUri, &xpsFD )
        opcPartUri.Release()
        mov opcPartUri,NULL
    .endif

    .if (SUCCEEDED(hr))

        mov hr,xpsFactory.CreatePageReference( &pageSize, &xpsPageRef )
    .endif

    .if (SUCCEEDED(hr))

        mov hr,xpsFactory.CreatePartUri( "/Documents/1/Pages/1.fpage", &opcPartUri )
    .endif

    .if (SUCCEEDED(hr))

        mov hr,xpsFactory.CreatePage(
                &pageSize,
                NULL, ;; language
                opcPartUri,
                &xpsPage
                )
        opcPartUri.Release()
        mov opcPartUri,NULL
    .endif

    ;; Chain document trunk objects from package root to fixed page
    .if (SUCCEEDED(hr))

        mov hr,xpsPackage.SetDocumentSequence( xpsFDS )
    .endif
    .if (SUCCEEDED(hr))

        mov hr,xpsFDS.GetDocuments( &fixedDocuments )
    .endif
    .if (SUCCEEDED(hr))

        mov hr,fixedDocuments.Append( xpsFD )
    .endif
    .if (SUCCEEDED(hr))

        mov hr,xpsFD.GetPageReferences( &pageRefs )
    .endif
    .if (SUCCEEDED(hr))

        mov hr,pageRefs.Append( xpsPageRef )
    .endif
    .if (SUCCEEDED(hr))

        mov hr,xpsPageRef.SetPage( xpsPage )
    .endif
    .if (SUCCEEDED(hr))

        mov hr,xpsPage.SetLanguage(L"en-US")
    .endif

    ;; Add canvas to page visuals
    .if (SUCCEEDED(hr))

        mov hr,xpsPage.GetVisuals( &pageVisuals )
    .endif
    .if (SUCCEEDED(hr))

        mov hr,pageVisuals.Append( canvas )
    .endif
if 1 ; Create in local directory
    wcscpy(&szDesktopPath, "SDKSample_FlowText_Output.xps")
else
    ;; Save XPS OM to file
    .if (SUCCEEDED(hr))

        mov hr,SHGetFolderPath(0, CSIDL_DESKTOPDIRECTORY, 0, SHGFP_TYPE_CURRENT, &szDesktopPath)
    .endif
    .if (SUCCEEDED(hr))

        mov hr,StringCchCat(&szDesktopPath, ARRAYSIZE(szDesktopPath), L"\\SDKSample_FlowText_Output.xps")
    .endif
endif
    .if (SUCCEEDED(hr))

        mov hr,xpsPackage.WriteToFile(
                &szDesktopPath,
                NULL, ;; LPSECURITY_ATTRIBUTES
                FILE_ATTRIBUTE_NORMAL,
                FALSE ;; optimizeMarkupSize
                )
    .endif

    ;; release resources
    .if (xpsPackage)

        xpsPackage.Release()
        mov xpsPackage,NULL
    .endif
    .if (xpsFDS)

        xpsFDS.Release()
        mov xpsFDS,NULL
    .endif
    .if (fixedDocuments)

        fixedDocuments.Release()
        mov fixedDocuments,NULL
    .endif
    .if (xpsFD)

        xpsFD.Release()
        mov xpsFD,NULL
    .endif
    .if (pageRefs)

        pageRefs.Release()
        mov pageRefs,NULL
    .endif
    .if (xpsPageRef)

        xpsPageRef.Release()
        mov xpsPageRef,NULL
    .endif
    .if (xpsPage)

        xpsPage.Release()
        mov xpsPage,NULL
    .endif
    .if (opcPartUri)

        opcPartUri.Release()
        mov opcPartUri,NULL
    .endif
    .if (pageVisuals)

        pageVisuals.Release()
        mov pageVisuals,NULL
    .endif

    .return hr

SaveCanvasToXpsViaPackage endp


wmain proc

  local hr              : HRESULT
  local bCOMInitialized : BOOL
  local xpsFactory      : ptr IXpsOMObjectFactory
  local textLayout      : ptr IDWriteTextLayout
  local pCanvasBuilder  : ptr LayoutToCanvasBuilder

    mov hr,S_OK
    mov bCOMInitialized,0
    mov xpsFactory,NULL
    mov textLayout,NULL
    mov pCanvasBuilder,NULL

    mov hr,CoInitialize(0)

    .if (SUCCEEDED(hr))

        mov bCOMInitialized,TRUE
        mov hr,CoCreateInstance(
                &CLSID_XpsOMObjectFactory,
                NULL,
                CLSCTX_INPROC_SERVER,
                &IID_IXpsOMObjectFactory,
                &xpsFactory)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,MakeTextLayout(&textLayout)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,CreateInstance( xpsFactory, &pCanvasBuilder )
    .endif

    .if (SUCCEEDED(hr))

        mov hr,textLayout.Draw(
                NULL, ;;clientDrawingContext
                pCanvasBuilder, ;; IDWriteTextRenderer implementation
                15.0, ;; originX
                15.0 ;; originY
                )
    .endif

    .if (SUCCEEDED(hr))

        mov hr,SaveCanvasToXpsViaPackage(
                xpsFactory,
                pCanvasBuilder.GetCanvas()
                )
        ;; pCanvasBuilder->GetResources()  -  xpsPartResources object is also available if streaming serialization is preferred
    .endif

    ;; release resources
    .if (pCanvasBuilder)

        pCanvasBuilder.Release()
        mov pCanvasBuilder,NULL
    .endif
    .if (textLayout)

        textLayout.Release()
        mov textLayout,NULL
    .endif
    .if (xpsFactory)

        xpsFactory.Release()
        mov xpsFactory,NULL
    .endif
    .if (bCOMInitialized)

        CoUninitialize()
        mov bCOMInitialized,FALSE
    .endif

    mov eax,hr
    xor eax,1
    ret

wmain endp

    end

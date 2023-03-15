
ifndef _WIN32_WINNT
_WIN32_WINNT equ 0x0601 ;; Specifies that the minimum required platform is Windows 7.
endif
NOMINMAX equ 1

include stdio.inc
include windows.inc
include XpsObjectModel.inc

include StrSafe.inc
include shlobj.inc

IDR_RC_PACKAGE_DATA1 equ 101
RC_PACKAGE_DATA      equ 257


CCHOF equ <lengthof>

.code

_com_issue_error proc hr:HRESULT

    fwprintf(stderr, L"ERROR: _com_issue_error called with HRESULT 0x%X\n", hr)

    ;; _exit terminates the process immediately, without calling any C++
    ;; destructors.

    _exit(1)
    ret

_com_issue_error endp


LoadAttachedResourceToMemory proc \
    streamResourceId    : LPCTSTR,
    lpType              : LPCTSTR,
    ppData              : ptr PVOID,
    pdwSize             : PDWORD

  local dwSize          : DWORD,
        hData           : HGLOBAL,  ;; Not really HGlobal. See MSDN's LockResource for details.
        pData           : PVOID,    ;; Doesn't need to be released.
        hr              : HRESULT,
        hTestModule     : HMODULE,
        hRes            : HRSRC

    mov dwSize,0
    mov hData,NULL
    mov pData,NULL
    mov hr,S_OK
    mov hTestModule,NULL
    mov hRes,FindResource(hTestModule, streamResourceId, lpType)

    .if (!hRes)

        mov hr,E_FAIL
    .endif

    .if ( SUCCEEDED (hr) )

        mov hData,LoadResource(hTestModule, hRes)
        .if (!hData)

            mov hr,E_FAIL
        .endif
    .endif

    .if ( SUCCEEDED(hr) )

        mov dwSize,SizeofResource(hTestModule, hRes)
        .if (dwSize <= 0)

            mov hr,E_FAIL
        .endif
    .endif

    .if ( SUCCEEDED(hr) )

        mov pData,LockResource(hData)
        .if (!pData)

            mov hr,E_FAIL
        .endif
    .endif

    mov rcx,ppData
    mov rax,pData
    mov [rcx],rax

    mov rcx,pdwSize
    mov eax,dwSize
    mov [rcx],eax

    .return hr

LoadAttachedResourceToMemory endp


GetReadStreamFromAttachedResource proc \
    lpName          : LPCTSTR,
    lpType          : LPCTSTR,
    ppReadStream    : ptr ptr IStream,
    pdwSize         : PDWORD

  local pBuf        : PVOID
  local pData       : PVOID
  local hr          : HRESULT
  local pReadStream : ptr IStream

    mov pBuf,NULL
    mov pData,NULL
    mov pReadStream,NULL
    mov hr,LoadAttachedResourceToMemory(rcx, rdx, &pData, r9)

    .if (SUCCEEDED(hr) && pData)

        .if ( pData )

            mov rcx,pdwSize
            mov pBuf,GlobalLock(GlobalAlloc(GMEM_MOVEABLE, [rcx]))
        .endif

        .if ( pBuf )

            mov rcx,pdwSize
            mov edx,[rcx]
            CopyMemory(pBuf, pData, edx)
        .endif

        .if ( pBuf && pData )

            mov hr,CreateStreamOnHGlobal(pBuf, TRUE, &pReadStream)
        .endif
    .endif

    .if (FAILED(hr) )

        .if ( pBuf )

            GlobalFree(pBuf)
        .endif

    .else
        mov rcx,ppReadStream
        mov rax,pReadStream
        mov [rcx],rax
    .endif
    .return hr

GetReadStreamFromAttachedResource endp


GetXpsFactory proc factory:ptr ptr IXpsOMObjectFactory

    .return CoCreateInstance(
                &CLSID_XpsOMObjectFactory,
                NULL,
                CLSCTX_INPROC_SERVER,
                &IID_IXpsOMObjectFactory,
                factory
                )

GetXpsFactory endp


LoadXpsPackage proc \
    xpsStreamResourceId : WORD,
    pXpsFactory         : ptr IXpsOMObjectFactory,
    ppXpsPackage        : ptr ptr IXpsOMPackage

  local hr      : HRESULT,
        pStream : ptr IStream,
        size    : DWORD

    mov pStream,NULL
    mov hr,GetReadStreamFromAttachedResource(
            rcx,
            RC_PACKAGE_DATA,
            &pStream,
            &size)

    .if ( SUCCEEDED(hr) )

        mov hr, pXpsFactory.CreatePackageFromStream(
                    pStream,
                    FALSE,
                    ppXpsPackage)
    .endif

    .if ( pStream )

        pStream.Release()
        mov pStream,NULL
    .endif

    .return hr

LoadXpsPackage endp


FindFirstPageReference proc \
    pXpsFactory         : ptr IXpsOMObjectFactory,
    pXpsPackage         : ptr IXpsOMPackage,
    ppXpsPageReference  : ptr ptr IXpsOMPageReference

  local hr                    : HRESULT,
        pXpsDocSeq            : ptr IXpsOMDocumentSequence,
        pXpsDocCollection     : ptr IXpsOMDocumentCollection,
        pXpsDocument          : ptr IXpsOMDocument,
        pXpsPageRefCollection : ptr IXpsOMPageReferenceCollection


    mov hr,pXpsPackage.GetDocumentSequence(&pXpsDocSeq)

    .if (SUCCEEDED(hr) )

        mov hr,pXpsDocSeq.GetDocuments(&pXpsDocCollection)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,pXpsDocCollection.GetAt(0, &pXpsDocument)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,pXpsDocument.GetPageReferences(&pXpsPageRefCollection)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,pXpsPageRefCollection.GetAt(0, ppXpsPageReference)
    .endif


    .if ( pXpsPageRefCollection )

        pXpsPageRefCollection.Release()
        mov pXpsPageRefCollection,NULL
    .endif

    .if ( pXpsDocument )

        pXpsDocument.Release()
        mov pXpsDocument,NULL
    .endif

    .if ( pXpsDocCollection )

        pXpsDocCollection.Release()
        mov pXpsDocCollection,NULL
    .endif

    .if ( pXpsDocSeq )

        pXpsDocSeq.Release()
        mov pXpsDocSeq,NULL
    .endif

    .return hr

FindFirstPageReference endp


CreateWaterMark proc \
    pXpsFactory         : ptr IXpsOMObjectFactory,
    pXpsFontResource    : ptr IXpsOMFontResource,
    ppXpsCanvas         : ptr ptr IXpsOMCanvas

  local hr                  : HRESULT,
        pXpsGlyphs          : ptr IXpsOMGlyphs,
        pXpsGlyphsEditor    : ptr IXpsOMGlyphsEditor,
        pXpsSolidColor      : ptr IXpsOMSolidColorBrush,
        pXpsVisualCollection: ptr IXpsOMVisualCollection

    .data
     glyphOrigin XPS_POINT { 50.0, 500.0 }
     fontRenderingSize FLOAT 48.0
    .code

    mov hr,pXpsFactory.CreateGlyphs(pXpsFontResource, &pXpsGlyphs)

    .if (SUCCEEDED(hr))

        mov hr,pXpsGlyphs.GetGlyphsEditor(&pXpsGlyphsEditor)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pXpsGlyphsEditor.SetUnicodeString(L"Draft")
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pXpsGlyphsEditor.ApplyEdits()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pXpsGlyphs.SetOrigin(&glyphOrigin)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pXpsGlyphs.SetFontRenderingEmSize(fontRenderingSize)
    .endif

    .if (SUCCEEDED(hr))

       .new blackColor:XPS_COLOR
        mov blackColor.colorType,        XPS_COLOR_TYPE_SRGB
        mov blackColor.value.sRGB.alpha, 0xff ;; Opaque
        mov blackColor.value.sRGB.red,   0x00
        mov blackColor.value.sRGB.green, 0x00
        mov blackColor.value.sRGB.blue,  0x00
        mov hr,pXpsFactory.CreateSolidColorBrush(&blackColor, NULL, &pXpsSolidColor)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pXpsGlyphs.SetFillBrushLocal(pXpsSolidColor)
    .endif

    .if ( SUCCEEDED(hr))

        mov hr,pXpsFactory.CreateCanvas(ppXpsCanvas)
    .endif

    ;; Next 2 steps add Glyph to Canvas
    .if (SUCCEEDED(hr))

        mov rax,ppXpsCanvas
        mov rcx,[rax]
        mov hr,[rcx].IXpsOMCanvas.GetVisuals(&pXpsVisualCollection)
    .endif

    .if ( SUCCEEDED(hr))

        mov hr,pXpsVisualCollection.Append(pXpsGlyphs)
    .endif

    .if ( pXpsSolidColor )

        pXpsSolidColor.Release()
        mov pXpsSolidColor,NULL
    .endif

    .if ( pXpsGlyphsEditor )

        pXpsGlyphsEditor.Release()
        mov pXpsGlyphsEditor,NULL
    .endif

    .if ( pXpsGlyphs )

        pXpsGlyphs.Release()
        mov pXpsGlyphs,NULL
    .endif

    .if ( pXpsVisualCollection )

        pXpsVisualCollection.Release()
        mov pXpsVisualCollection,NULL
    .endif

    .return hr

CreateWaterMark endp


AddWatermarkToPage proc \
    pXpsPage    : ptr IXpsOMPage,
    pXpsCanvas  : ptr IXpsOMCanvas

  local pVisualCollection : ptr IXpsOMVisualCollection,
        hr                : HRESULT

    mov pVisualCollection,NULL
    mov hr,pXpsPage.GetVisuals(&pVisualCollection)

    .if ( SUCCEEDED(hr) )

        mov hr,pVisualCollection.Append(pXpsCanvas)
    .endif

    .if ( pVisualCollection )

        pVisualCollection.Release()
        mov pVisualCollection,NULL
    .endif

    .return hr

AddWatermarkToPage endp


GetFontResource proc \
    pXpsPageReference   : ptr IXpsOMPageReference,
    ppXpsFontResource   : ptr ptr IXpsOMFontResource


  local hr                    : HRESULT,
        pXpsPartResources     : ptr IXpsOMPartResources,
        pXpsFontResCollection : ptr IXpsOMFontResourceCollection

    .if (SUCCEEDED(hr))

        mov hr,pXpsPageReference.CollectPartResources(&pXpsPartResources)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,pXpsPartResources.GetFontResources(&pXpsFontResCollection)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,pXpsFontResCollection.GetAt(0, ppXpsFontResource)
    .endif

    .if ( pXpsFontResCollection )

        pXpsFontResCollection.Release()
        mov pXpsFontResCollection,NULL
    .endif

    .if ( pXpsPartResources )

        pXpsPartResources.Release()
        mov pXpsPartResources,NULL
    .endif

    .return hr

GetFontResource endp


SerializePackage proc pXpsPackage:ptr IXpsOMPackage


  local szDesktopPath[MAX_PATH]:WCHAR,
        hr:HRESULT

    mov hr,SHGetFolderPath(0, CSIDL_DESKTOPDIRECTORY, 0, SHGFP_TYPE_CURRENT, &szDesktopPath)
    .if ( SUCCEEDED(hr) )
        mov hr,StringCchCat(&szDesktopPath, CCHOF(szDesktopPath), L"\\SDKSample_XpsLoadModifySave.xps")
    .endif
    .if ( SUCCEEDED(hr) )
        mov hr,pXpsPackage.WriteToFile(&szDesktopPath, NULL, FILE_ATTRIBUTE_NORMAL, FALSE)
    .endif
    .return hr

SerializePackage endp


wmain proc argc:int_t, argv:ptr ptr wchar_t

  local hr                : HRESULT,
        pXpsCanvas        : ptr IXpsOMCanvas,
        pXpsPackage       : ptr IXpsOMPackage,
        pXpsFactory       : ptr IXpsOMObjectFactory,
        pXpsPage          : ptr IXpsOMPage,
        pXpsPageReference : ptr IXpsOMPageReference,
        pXpsFontResource  : ptr IXpsOMFontResource


    mov hr,CoInitializeEx(0, COINIT_MULTITHREADED)
    .if (FAILED(hr))

        fwprintf(stderr, L"ERROR: CoInitializeEx failed with HRESULT 0x%X\n", hr)
        .return 1
    .endif

    mov hr,GetXpsFactory(&pXpsFactory)
    .if (!SUCCEEDED(hr))

        fwprintf(stderr, L"ERROR: Could not create XPS OM Object Factory.\n")

    .else

        mov hr,LoadXpsPackage(IDR_RC_PACKAGE_DATA1,
                pXpsFactory,
                &pXpsPackage)
    .endif

    .if ( !SUCCEEDED(hr) )

        fwprintf(stderr, L"ERROR: Could not load xps package.\n")

    .else

        mov hr,FindFirstPageReference(pXpsFactory, pXpsPackage, &pXpsPageReference)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,GetFontResource(pXpsPageReference, &pXpsFontResource)
    .endif

    .if ( SUCCEEDED(hr) )

         mov hr,CreateWaterMark(pXpsFactory, pXpsFontResource, &pXpsCanvas)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,pXpsPageReference.GetPage(&pXpsPage)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,AddWatermarkToPage(pXpsPage, pXpsCanvas)
    .endif

    .if (SUCCEEDED(hr) )

        mov hr,SerializePackage(pXpsPackage)
    .endif

    .if ( pXpsPage )

        pXpsPage.Release()
        mov pXpsPage,NULL
    .endif

    .if ( pXpsPageReference )

        pXpsPageReference.Release()
        mov pXpsPageReference,NULL
    .endif

    .if ( pXpsFontResource )

        pXpsFontResource.Release()
        mov pXpsFontResource,NULL
    .endif


    .if ( pXpsCanvas )

        pXpsCanvas.Release()
        mov pXpsCanvas,NULL
    .endif


    .if ( pXpsPackage )

        pXpsPackage.Release()
        mov pXpsPackage,NULL
    .endif

    .if ( pXpsFactory )

        pXpsFactory.Release()
        mov pXpsFactory,NULL
    .endif

    CoUninitialize()
    mov eax,1
    .if SUCCEEDED(hr)
        xor eax,eax
    .endif
    ret

wmain endp

    end

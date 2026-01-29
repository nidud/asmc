
include common.inc
include LayoutToCanvasBuilder.inc

g_layoutBrushKey equ <L"textLayoutBrush">

.code

;;
;; Static utility function converting DWRITE_GLYPH_RUN_DESCRIPTION::clusterMap
;; to XPS OM array of XPS_GLYPH_MAPPING structures
;;

ClusterMapToMappingArray proc uses rsi rdi rbx \
    clusterMap              : ptr UINT16,
    mapLen                  : UINT32, ;; number of elements in clusterMap array
    glyphsArrayLen          : UINT32, ;; number of elements in glyphs array
    resultMaxCount          : UINT32, ;; size of output buffer resultGlyphMapping (max number of elements)
    resultGlyphMapping      : ptr XPS_GLYPH_MAPPING, ;; output buffer
    resultGlyphMappingCount : ptr UINT32;; number of elements returned in resultGlyphMapping

    ;; assumption:
    ;; clusterMap[0] <= clusterMap[1] <= ... <= clusterMap[mapLen-1] < glyphsArrayLen

  local hr      : HRESULT
  local i       : UINT32 ;; number of elements added to resultGlyphMapping array
  local mapPos  : UINT32 ;; position in clusterMap array

    mov rsi,rcx
    xor eax,eax
    mov rcx,resultGlyphMappingCount
    mov hr,eax
    mov i,eax
    mov mapPos,eax
    mov [rcx],eax

    .while (mapPos < mapLen && i < resultMaxCount)

        mov edi,1 ; codePointRangeLen
        mov ebx,1 ; glyphIndexRangeLen
        mov edx,mapPos

        .while 1
            lea rax,[rdx+rdi]
            .break .if eax >= mapLen
            mov ax,[rsi+rax*2]
            .break .if ax != [rsi+rdx*2]
            inc edi
        .endw

        lea rax,[rdx+rdi]
        .if eax == mapLen

            ;; end of cluster map
            mov ebx,glyphsArrayLen
            movzx ecx,word ptr [rsi+rdx*2]
            sub ebx,ecx
        .else
            movzx ebx,word ptr [rsi+rax*2]
            movzx eax,word ptr [rsi+rdx*2]
            sub ebx,eax
        .endif

        .if (edi > 1 || ebx > 1)

            ;; Add mapping entry for 1 : N, N : 1 and M : N  code point to glyph index clusters

            mov  ecx,i
            imul r8d,ecx,XPS_GLYPH_MAPPING
            add  r8,resultGlyphMapping
            movzx eax,word ptr [rsi+rdx*2]

            mov [r8].XPS_GLYPH_MAPPING.unicodeStringStart,edx
            mov [r8].XPS_GLYPH_MAPPING.unicodeStringLength,di
            mov [r8].XPS_GLYPH_MAPPING.glyphIndicesStart,eax
            mov [r8].XPS_GLYPH_MAPPING.glyphIndicesLength,bx
            inc i
        .endif
        add edx,edi
        mov mapPos,edx
    .endw
    .if (mapPos < mapLen && i >= resultMaxCount)
        mov hr,HRESULT_FROM_WIN32(ERROR_MORE_DATA)
    .endif
    mov rcx,resultGlyphMappingCount
    mov eax,i
    mov [rcx] ,eax
    mov eax,hr
    ret
    endp

    assume class:rbx

LayoutToCanvasBuilder::LayoutToCanvasBuilder proc xpsFactory:ptr IXpsOMObjectFactory
    mov rbx,@ComAlloc(LayoutToCanvasBuilder)
    inc _refCount
    mov _xpsFactory,xpsFactory
    AddRef()
    mov rax,rbx
    ret
    endp

;;
;; This internal method creates empty canvas with resource dictionary holding
;; one solid color brush. It also creates empty IXpsOMPartResources object.
;;

LayoutToCanvasBuilder::CreateRootCanvasAndResources proc

    local hr:HRESULT
    local canvasDictionary:ptr IXpsOMDictionary
    local blueSolidBrush:ptr IXpsOMSolidColorBrush

    mov canvasDictionary,NULL
    mov blueSolidBrush,NULL
    mov hr,_xpsFactory.CreateCanvas( &_xpsCanvas )
    .if (SUCCEEDED(hr))
        mov hr,_xpsFactory.CreatePartResources( &_xpsResources )
    .endif

    ;; Create dictionary and add to canvas
    .if (SUCCEEDED(hr))
        mov hr,_xpsFactory.CreateDictionary( &canvasDictionary )
    .endif
    .if (SUCCEEDED(hr))
        mov hr,_xpsCanvas.SetDictionaryLocal( canvasDictionary )
    .endif

    ;; Create solid color brush and add to canvas dictionary

    .if (SUCCEEDED(hr))

       .new rgbBlue:XPS_COLOR = { XPS_COLOR_TYPE_SRGB, { { 0xFF, 0, 0, 0xFF } } }
        mov hr,_xpsFactory.CreateSolidColorBrush(
                &rgbBlue,
                NULL, ;; no color profile for this color type
                &blueSolidBrush
                )
    .endif

    .if (SUCCEEDED(hr))
        mov hr,canvasDictionary.Append(g_layoutBrushKey, blueSolidBrush)
    .endif

    ;; cleanup
    SafeRelease(blueSolidBrush)
    SafeRelease(canvasDictionary)
    .return hr
    endp

LayoutToCanvasBuilder::delete proc uses rsi rdi

    lea rsi,_fontMap
    .for ( edi = 0 : edi < _fontMapSize : edi++, rsi += FontMapEntry )
        mov rcx,[rsi].FontMapEntry.fontResource
        [rcx].IXpsOMFontResource.Release()
    .endf
    mov _fontMapSize,0
    .if _xpsFactory
        _xpsFactory.Release()
        mov _xpsFactory,NULL
    .endif
    .if _xpsCanvas
        _xpsCanvas.Release()
        mov _xpsCanvas,NULL
    .endif
    .if _xpsResources
        _xpsResources.Release()
        mov _xpsResources,NULL
    .endif
    ret
    endp


CreateInstance proc xpsFactory:ptr IXpsOMObjectFactory, ppNewInstance:ptr ptr LayoutToCanvasBuilder

  local hr:HRESULT, pResult:ptr LayoutToCanvasBuilder

    mov hr,S_OK
    mov pResult,LayoutToCanvasBuilder(xpsFactory)
    .if rax == NULL
        mov hr,E_OUTOFMEMORY
    .endif
    .if (SUCCEEDED(hr))
        mov hr,pResult.CreateRootCanvasAndResources()
    .endif
    .if (SUCCEEDED(hr))
        mov rax,ppNewInstance
        mov rcx,pResult
        mov [rax],rcx
        [rcx].LayoutToCanvasBuilder.AddRef()
    .endif
    .if (pResult)
        pResult.Release()
        mov pResult,NULL
    .endif
    .return hr
    endp

LayoutToCanvasBuilder::GetCanvas proc
    .return _xpsCanvas
    endp

LayoutToCanvasBuilder::GetResources proc
    .return _xpsResources
    endp

LayoutToCanvasBuilder::QueryInterface proc riid:REFIID, ppvObject:ptr ptr

    .return E_POINTER .if r8 == NULL

    xor eax,eax
    mov [r8],rax
    mov rax,[rdx]
    .if ( rax == qword ptr IID_IUnknown || rax == qword ptr IID_IDWritePixelSnapping ||
          rax == qword ptr IID_IDWriteTextRenderer )

        AddRef()
        mov rcx,ppvObject
        mov [rcx],rbx
        .return S_OK
    .endif
    .return E_NOINTERFACE
    endp


LayoutToCanvasBuilder::AddRef proc
    inc _refCount
    ret
    endp


LayoutToCanvasBuilder::Release proc uses rsi
    dec _refCount
    mov esi,_refCount
    .if ( esi == 0 )
        delete()
    .endif
    mov eax,esi
    ret
    endp


;; IDWritePixelSnapping methods

LayoutToCanvasBuilder::IsPixelSnappingDisabled proc clientDrawingContext:ptr, isDisabled:ptr BOOL
    xor eax,eax
    mov [r8],eax
    ret
    endp

;;
;; returns identity matrix - our abstract coordinates are device independent
;; pixels.
;;

LayoutToCanvasBuilder::GetCurrentTransform proc clientDrawingContext:ptr, transform:ptr DWRITE_MATRIX
    xor eax,eax
    mov [r8].DWRITE_MATRIX.m11,1.0
    mov [r8].DWRITE_MATRIX.m22,1.0
    mov [r8].DWRITE_MATRIX.m12,eax
    mov [r8].DWRITE_MATRIX.m21,eax
    mov [r8].DWRITE_MATRIX.x,eax
    mov [r8].DWRITE_MATRIX.y,eax
    ret
    endp

;;
;; Returns 1.0 because we use DIP pixels
;;

LayoutToCanvasBuilder::GetPixelsPerDip proc clientDrawingContext:ptr, pixelsPerDip:ptr FLOAT

    ;; DIP used in XPS (96 DPI)

    mov eax,1.0
    mov [r8],eax
    .return S_OK
    endp

;; IDWriteTextRenderer

    assume rsi:ptr DWRITE_GLYPH_RUN

LayoutToCanvasBuilder::DrawGlyphRun proc uses rsi rdi \
    clientDrawingContext: ptr,
    baselineOriginX     : FLOAT,
    baselineOriginY     : FLOAT,
    measuringMode       : DWRITE_MEASURING_MODE,
    glyphRun            : ptr DWRITE_GLYPH_RUN,
    glyphRunDescription : ptr DWRITE_GLYPH_RUN_DESCRIPTION,
    clientDrawingEffect : ptr IUnknown

  local hr              : HRESULT
  local fontFaceType    : DWRITE_FONT_FACE_TYPE

    ;; supported font types in xps

    mov fontFaceType,glyphRun.fontFace.GetType()
    mov hr,S_OK

    .if ( eax != DWRITE_FONT_FACE_TYPE_CFF &&
          eax != DWRITE_FONT_FACE_TYPE_TRUETYPE &&
          eax != DWRITE_FONT_FACE_TYPE_TRUETYPE_COLLECTION )

        ;; XPS does not support this type of font - just ignore this glyph run.

    .else

       .new positionScale    : FLOAT
       .new fontResource     : ptr IXpsOMFontResource       = NULL
       .new xpsGlyphs        : ptr IXpsOMGlyphs             = NULL
       .new canvasVisuals    : ptr IXpsOMVisualCollection   = NULL
       .new xpsGlyphsEditor  : ptr IXpsOMGlyphsEditor       = NULL
       .new glyphIndexVector : ptr XPS_GLYPH_INDEX          = NULL
       .new pszUnicodeString : PWSTR                        = NULL

        mov rsi,glyphRun
        movss xmm0,100.0
        divss xmm0,[rsi].fontEmSize
        movss positionScale,xmm0

        ;; Find or create XPS font resource for this font face
        .if (SUCCEEDED(hr))
            mov hr,FindOrCreateFontResource( [rsi].fontFace, &fontResource )
        .endif
        .if (SUCCEEDED(hr))
            mov hr,_xpsFactory.CreateGlyphs( fontResource, &xpsGlyphs )
        .endif
        ;; Add new Glyphs element to canvas
        .if (SUCCEEDED(hr))
            mov hr,_xpsCanvas.GetVisuals( &canvasVisuals )
        .endif
        .if (SUCCEEDED(hr))
            mov hr,canvasVisuals.Append( xpsGlyphs )
        .endif
        ;; Now set Glyphs properties
        .if (SUCCEEDED(hr))
           .new glyphsBaselineOrigin:XPS_POINT = { baselineOriginX, baselineOriginY }
            mov hr,xpsGlyphs.SetOrigin( &glyphsBaselineOrigin )
        .endif
        .if (SUCCEEDED(hr))
            mov hr,xpsGlyphs.SetFontRenderingEmSize( [rsi].fontEmSize )
        .endif
        .if (SUCCEEDED(hr))
            mov hr,xpsGlyphs.SetFillBrushLookup( g_layoutBrushKey )
        .endif
        .if ( SUCCEEDED(hr) && fontFaceType == DWRITE_FONT_FACE_TYPE_TRUETYPE_COLLECTION )
            ;; set font face index
            glyphRun.fontFace.GetIndex()
            mov hr,xpsGlyphs.SetFontFaceIndex( ax )
        .endif
        .if (SUCCEEDED(hr))
            glyphRun.fontFace.GetSimulations()
            .if ( eax & DWRITE_FONT_SIMULATIONS_BOLD )
                .if ( eax & DWRITE_FONT_SIMULATIONS_OBLIQUE )
                    mov hr,xpsGlyphs.SetStyleSimulations( XPS_STYLE_SIMULATION_BOLDITALIC )
                .else
                    mov hr,xpsGlyphs.SetStyleSimulations( XPS_STYLE_SIMULATION_BOLD )
                .endif
            .else
                .if ( eax & DWRITE_FONT_SIMULATIONS_OBLIQUE )
                    mov hr,xpsGlyphs.SetStyleSimulations( XPS_STYLE_SIMULATION_ITALIC )
                .endif
            .endif
        .endif

        ;; The rest of the properties must be set through glyphs editor
        ;; interface because of interdependencies

        .if (SUCCEEDED(hr))
            mov hr,xpsGlyphs.GetGlyphsEditor( &xpsGlyphsEditor )
        .endif
        .if (SUCCEEDED(hr))
            imul ecx,[rsi].glyphCount,XPS_GLYPH_INDEX
            mov glyphIndexVector,CoTaskMemAlloc(ecx)
            .if (!glyphIndexVector)
                mov hr,E_OUTOFMEMORY
            .endif
        .endif

        .if (SUCCEEDED(hr))

            .for ( edi = 0: edi < [rsi].glyphCount: edi++ )

                ;; NOTE: these values may need extra adjustment depending on
                ;; transformation, IsSideways and bidiLevel

                imul    ecx,edi,XPS_GLYPH_INDEX
                add     rcx,glyphIndexVector
                mov     rdx,[rsi].glyphIndices
                movzx   eax,word ptr [rdx+rdi*2]
                mov     [rcx].XPS_GLYPH_INDEX.index,eax

                ;; advanceWidth, horizontal and vertical offset in Indices
                ;; attribute in XPS Glyphs element are in 1/100 of font em size.

                mov     rdx,[rsi].glyphAdvances
                movss   xmm0,[rdx+rdi*4]
                mulss   xmm0,positionScale
                movss   [rcx].XPS_GLYPH_INDEX.advanceWidth,xmm0

                mov rdx,[rsi].glyphOffsets
                .if rdx
                    imul    eax,edi,DWRITE_GLYPH_OFFSET
                    movss   xmm0,[rdx+rax].DWRITE_GLYPH_OFFSET.advanceOffset
                    mulss   xmm0,positionScale
                    movss   [rcx].XPS_GLYPH_INDEX.horizontalOffset,xmm0
                    movss   xmm0,[rdx+rax].DWRITE_GLYPH_OFFSET.ascenderOffset
                    mulss   xmm0,positionScale
                    movss   [rcx].XPS_GLYPH_INDEX.verticalOffset,xmm0
                .else
                    mov     [rcx].XPS_GLYPH_INDEX.horizontalOffset,0
                    mov     [rcx].XPS_GLYPH_INDEX.verticalOffset,0
                .endif
            .endf
            mov hr,xpsGlyphsEditor.SetGlyphIndices([rsi].glyphCount, glyphIndexVector)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,xpsGlyphsEditor.SetIsSideways( [rsi].isSideways )
        .endif
        .if (SUCCEEDED(hr))
            mov hr,xpsGlyphsEditor.SetBidiLevel( [rsi].bidiLevel )
        .endif

        ;; Check for unicode string and cluster map

        mov rcx,glyphRunDescription

        .if (SUCCEEDED(hr) &&
            [rcx].DWRITE_GLYPH_RUN_DESCRIPTION.string &&
            [rcx].DWRITE_GLYPH_RUN_DESCRIPTION.stringLength > 0)

            ;; IXpsOMGlyphsEditor::SetUnicodeString expects null terminated
            ;; string but glyphRunDescription.string may not be so terminated.

            mov ecx,[rcx].DWRITE_GLYPH_RUN_DESCRIPTION.stringLength
            inc ecx
            shl ecx,1

            mov pszUnicodeString,CoTaskMemAlloc(ecx)
            .if ( !pszUnicodeString )
                mov hr,E_OUTOFMEMORY
            .endif
            .if (SUCCEEDED(hr))
                mov rcx,glyphRunDescription
                mov edx,[rcx].DWRITE_GLYPH_RUN_DESCRIPTION.stringLength
                mov r9d,edx
                inc edx
                mov r8,[rcx].DWRITE_GLYPH_RUN_DESCRIPTION.string
                mov hr,StringCchCopyN(pszUnicodeString, rdx, r8, r9)
            .endif
            .if (SUCCEEDED(hr))
                mov hr,xpsGlyphsEditor.SetUnicodeString( pszUnicodeString )
            .endif

            ;; fill in glyph mapping array and call xpsGlyphsEditor.SetGlyphMappings

            mov rcx,glyphRunDescription
            .if (SUCCEEDED(hr) && \
                [rcx].DWRITE_GLYPH_RUN_DESCRIPTION.clusterMap)

                ;;
                ;; This sample uses GLYPH_MAPPING_MAX_COUNT constant to limit
                ;; number of non-trivial (1:N, N:1 or M:N) mappings between
                ;; unicode codepoints and glyph indexes for each glyph run.
                ;; Complete implementation should handle ERROR_MORE_DATA result
                ;; from ClusterMapToMappingArray function.
                ;;

               .new glyphMapVector[GLYPH_MAPPING_MAX_COUNT]:XPS_GLYPH_MAPPING
               .new glyphMappingCount:UINT32 = 0

                mov hr,ClusterMapToMappingArray(
                        [rcx].DWRITE_GLYPH_RUN_DESCRIPTION.clusterMap,
                        [rcx].DWRITE_GLYPH_RUN_DESCRIPTION.stringLength,
                        [rsi].glyphCount,
                        GLYPH_MAPPING_MAX_COUNT,
                        &glyphMapVector,
                        &glyphMappingCount
                        )

                .if (SUCCEEDED(hr) && glyphMappingCount > 0)
                    mov hr,xpsGlyphsEditor.SetGlyphMappings(
                            glyphMappingCount,
                            &glyphMapVector
                            )
                .endif
            .endif
        .endif
        .if (SUCCEEDED(hr))
            mov hr,xpsGlyphsEditor.ApplyEdits()
        .endif

        ;; release local resources here
        .if (pszUnicodeString)
            CoTaskMemFree(pszUnicodeString)
            mov pszUnicodeString,NULL
        .endif
        .if (glyphIndexVector)
            CoTaskMemFree(glyphIndexVector)
            mov glyphIndexVector,NULL
        .endif
        SafeRelease(fontResource)
        SafeRelease(xpsGlyphs)
        SafeRelease(canvasVisuals)
        SafeRelease(xpsGlyphsEditor)
    .endif
    .return hr
    endp

    assume rsi:nothing

LayoutToCanvasBuilder::DrawUnderline proc clientDrawingContext:ptr, baselineOriginX:FLOAT, baselineOriginY:FLOAT,
    underline:ptr DWRITE_UNDERLINE, clientDrawingEffect:ptr IUnknown

  local begin:XPS_POINT, _end:XPS_POINT

    mov r10,underline
    movss xmm0,[r10].DWRITE_UNDERLINE.offs
    addss xmm0,xmm3
    movss begin.x,xmm2
    movss begin.y,xmm0
    addss xmm2,[r10].DWRITE_UNDERLINE.width
    movss _end.x,xmm2
    movss _end.y,xmm0
    AddLinePath( &begin, &_end, [r10].DWRITE_UNDERLINE.thickness )
    ret
    endp


LayoutToCanvasBuilder::DrawStrikethrough proc clientDrawingContext:ptr, baselineOriginX:FLOAT, baselineOriginY:FLOAT,
    strikethrough:ptr DWRITE_STRIKETHROUGH, clientDrawingEffect:ptr IUnknown

  local begin:XPS_POINT, _end:XPS_POINT

    mov r10,strikethrough
    addss xmm3,[r10].DWRITE_STRIKETHROUGH.offs
    movss begin.x,xmm2
    movss begin.y,xmm3
    addss xmm2,[r10].DWRITE_STRIKETHROUGH.width
    movss _end.x,xmm2
    movss _end.y,xmm3
    AddLinePath(&begin, &_end, [r10].DWRITE_STRIKETHROUGH.thickness)
    ret
    endp

;;
;; NOTE: This method is not implemented ! Does nothing.
;;

LayoutToCanvasBuilder::DrawInlineObject proc clientDrawingContext:ptr, originX:FLOAT, originY:FLOAT,
    inlineObject:ptr IDWriteInlineObject, isSideways:BOOL, isRightToLeft:BOOL, clientDrawingEffect:ptr IUnknown
    .return S_OK
    endp

;;
;; This method looks for font file object (by COM identity) in resource map. If
;; found, the corresponding XPS font resource is used. If not, a new font
;; resource is created and font file data is copied to new XPS font resource.
;;

LayoutToCanvasBuilder::FindOrCreateFontResource proc uses rsi rdi fontFace:ptr IDWriteFontFace,
    ppXpsFontResource:ptr ptr IXpsOMFontResource

  local hr:HRESULT
  local numFiles:UINT32
  local fontFileKey:UINT_PTR ;; we will use IDWriteFontFile COM object identity
                             ;; to detect equal fonts
  local fontFile:ptr IDWriteFontFile
  local pUnk:ptr IUnknown

    xor eax,eax
    mov [r8],rax ;; reset output argument
    mov hr,eax
    mov numFiles,1
    mov fontFileKey,rax
    mov fontFile,rax
    mov pUnk,rax
    mov hr,fontFace.GetFiles(&numFiles, &fontFile)

    .if (SUCCEEDED(hr))

        .if (numFiles != 1)

            ;; Font face type is verified by caller. It can not be stored in
            ;; more that one file.

            mov hr,E_UNEXPECTED
        .endif
    .endif

    .if (SUCCEEDED(hr))
        mov hr,fontFile.QueryInterface( &IID_IUnknown, &pUnk )
    .endif
    .if (SUCCEEDED(hr))
        mov fontFileKey,pUnk
        .if pUnk
            pUnk.Release()
            mov pUnk,NULL
        .endif

        lea rsi,_fontMap
        .for (edi = 0: edi < _fontMapSize: edi++, rsi += FontMapEntry)

            mov rax,[rsi].FontMapEntry.key
            .if ( rax == fontFileKey )

                ;; font is already in map and _xpsResources collection

                mov rcx,[rsi].FontMapEntry.fontResource
                mov rax,ppXpsFontResource
                mov [rax],rcx
                [rcx].IXpsOMFontResource.AddRef()
               .break
            .endif
        .endf
    .endif

    mov rcx,ppXpsFontResource
    mov rax,[rcx]

    .if rax

        ;; Nothing more to do - output argument is set and hr is S_OK.

    .else

        ;; This is a new font file. We have to create XPS resource for it.

        ;; First, create temporary storage with IStream implementation for font
        ;; bytes. HGLOBAL memory is used in this sample.
        ;; NOTE: Font data may be large - temp file is recommended for complete
        ;; implementation.

        xor eax,eax
       .new fontResourceStream  : ptr IStream = rax
       .new fontFileLoader      : ptr IDWriteFontFileLoader = rax
       .new fontFileStream      : ptr IDWriteFontFileStream = rax
       .new fontPartUri         : ptr IOpcPartUri = rax
       .new pNewFontResource    : ptr IXpsOMFontResource = rax
       .new fontResources       : ptr IXpsOMFontResourceCollection = rax

       .new fontFileRef         : ptr = rax
       .new fontFileRefSize     : UINT32 = eax
       .new bytesLeft           : UINT64 = rax
       .new readOffset          : UINT64 = rax

        .if (SUCCEEDED(hr))

            mov hr,CreateStreamOnHGlobal( ;; Win32 API
                    NULL, ;; let implementation take care of memory
                    TRUE, ;; release memory when done
                    &fontResourceStream
                    )
        .endif

        ;; Copy font data to temporary storage
        .if (SUCCEEDED(hr))
            mov hr,fontFile.GetReferenceKey(&fontFileRef, &fontFileRefSize)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,fontFile.GetLoader(&fontFileLoader)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,fontFileLoader.CreateStreamFromKey(
                    fontFileRef,
                    fontFileRefSize,
                    &fontFileStream
                    )
            fontFileLoader.Release()
            mov fontFileLoader,NULL
        .endif
        .if (SUCCEEDED(hr))
            mov hr,fontFileStream.GetFileSize(&bytesLeft)
        .endif

        .if (SUCCEEDED(hr))

            .while (bytesLeft && SUCCEEDED(hr))

               xor eax,eax
               .new fragment:ptr = rax
               .new fragmentContext:ptr = rax
               .new bFragmentContextAcquired:BOOL = eax
               .new readSize:UINT64

                mov     rax,bytesLeft
                mov     ecx,16384
                cmp     rax,rcx
                cmova   rax,rcx
                mov     readSize,rax
                mov hr,fontFileStream.ReadFileFragment(
                        &fragment,
                        readOffset,
                        readSize,
                        &fragmentContext
                        )

                .if (SUCCEEDED(hr))

                    mov bFragmentContextAcquired,TRUE
                    mov r8,readSize
                    mov hr,fontResourceStream.Write(
                            fragment,
                            r8d,
                            NULL
                            )
                .endif

                .if (SUCCEEDED(hr))
                    sub bytesLeft,readSize
                    add readOffset,readSize
                .endif
                .if (bFragmentContextAcquired)
                    fontFileStream.ReleaseFileFragment(fragmentContext)
                .endif
            .endw
            fontFileStream.Release()
            mov fontFileStream,NULL
        .endif

        .if (SUCCEEDED(hr))

            ;LARGE_INTEGER liZero = {0};
            mov hr,fontResourceStream.Seek(0, STREAM_SEEK_SET, NULL)
        .endif

        ;; Create new part URI for this resource
        .if (SUCCEEDED(hr))
            mov hr,GenerateNewFontPartUri(&fontPartUri)
        .endif

        ;; NOTE: See XPS spec section 2.1.7.2
        ;; This sample will obfuscate all font resources. It is allowed by XPS
        ;; specification. This sample does not set RestrictedFont relationship
        ;; for any font resource! This may result in incorrect XPS file if one
        ;; or more fonts have Print&Preview flag!

        .if (SUCCEEDED(hr))

            mov hr,_xpsFactory.CreateFontResource(
                    fontResourceStream,
                    XPS_FONT_EMBEDDING_OBFUSCATED,
                    fontPartUri,
                    FALSE, ;;isObfSourceStream
                    &pNewFontResource
                    )
        .endif

        ;; New font resource must be added to map and fonts collection before
        ;; returning it to caller

        .if (SUCCEEDED(hr))
            mov hr,_xpsResources.GetFontResources(&fontResources)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,fontResources.Append(pNewFontResource)
        .endif

        .if (SUCCEEDED(hr))

            .if (_fontMapSize < FONT_MAP_MAX_SIZE)

                mov  eax,_fontMapSize
                lea  rsi,_fontMap
                imul ecx,eax,FontMapEntry
                mov  [rsi+rcx].FontMapEntry.key,fontFileKey
                mov  [rsi+rcx].FontMapEntry.fontResource,pNewFontResource

                [rax].IXpsOMFontResource.AddRef()
                inc _fontMapSize

            .else

                ;;
                ;; Do nothing here.
                ;;
                ;; NOTE:
                ;; This sample limits number of entries with FONT_MAP_MAX_SIZE
                ;; constant. If _fontMap is full and the same font file is used
                ;; in another glyph run, it may be added as a new font resource
                ;; part in XPS. This may result in large XPS file!
                ;; Complete implementation should dynamically increase _fontMap
                ;; array size to avoid font data duplication.
                ;;
            .endif

            mov rax,ppXpsFontResource
            mov rcx,pNewFontResource
            mov [rax],rcx
            [rcx].IXpsOMFontResource.AddRef()

        .endif

        ;; release objects used for converting DWrite font file to XPS font
        ;; resource

        SafeRelease(fontResourceStream)
        SafeRelease(fontFileLoader)
        SafeRelease(fontFileStream)
        SafeRelease(fontPartUri)
        SafeRelease(pNewFontResource)
        SafeRelease(fontResources)
    .endif
    SafeRelease(fontFile)
    SafeRelease(pUnk)
    .return hr
    endp

;;
;;  Returns IOpcPartUri object built from URI '/Resources/Fonts/__guid__.odttf'
;;

LayoutToCanvasBuilder::GenerateNewFontPartUri proc ppPartUri : ptr ptr IOpcPartUri

  local hr:HRESULT
  local guid:GUID
  local guidString[128]:WCHAR
  local uriString[256]:WCHAR

    mov guidString,0
    mov uriString,0
    mov hr,CoCreateGuid(&guid)

    .if (SUCCEEDED(hr))
        mov hr,StringFromGUID2( &guid, &guidString, ARRAYSIZE(guidString) )
    .endif
    .if (SUCCEEDED(hr))
        mov hr,StringCchCopy( &uriString, ARRAYSIZE(uriString), L"/Resources/Fonts/" )
    .endif

    .if (SUCCEEDED(hr))

        ;; guid string start and ends with curly brackets so they are removed

        wcslen(&guidString)
        lea r9,[rax-2]
        lea r8,guidString
        add r8,2
        mov hr,StringCchCatN( &uriString, ARRAYSIZE(uriString), r8, r9)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,StringCchCat( &uriString,  ARRAYSIZE(uriString), L".odttf" )
    .endif
    .if (SUCCEEDED(hr))
        mov hr,_xpsFactory.CreatePartUri( &uriString, ppPartUri )
    .endif
    .return hr
    endp

;;
;; This methods creates a line path and adds it to current canvas visuals.
;; It is used by callback methods DrawUnderline and DrawStrikethrough.
;;

LayoutToCanvasBuilder::AddLinePath proc beginPoint:ptr XPS_POINT, endPoint:ptr XPS_POINT, thickness:FLOAT

  local hr              : HRESULT,
        canvasVisuals   : ptr IXpsOMVisualCollection,
        linePath        : ptr IXpsOMPath,
        lineGeom        : ptr IXpsOMGeometry,
        geomFigures     : ptr IXpsOMGeometryFigureCollection,
        lineFigure      : ptr IXpsOMGeometryFigure

    ;; Create Path element and add to canvas

    mov hr,_xpsFactory.CreatePath(&linePath)
    .if (SUCCEEDED(hr))
        mov hr,_xpsCanvas.GetVisuals(&canvasVisuals)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,canvasVisuals.Append(linePath)
    .endif

    ;; Set necessary path properties
    .if (SUCCEEDED(hr))
        mov hr,linePath.SetStrokeBrushLookup(g_layoutBrushKey)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,linePath.SetSnapsToPixels(TRUE)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,linePath.SetStrokeThickness(thickness)
    .endif

    ;; Create geometry and assign it to Path.Data property
    .if (SUCCEEDED(hr))
        mov hr,_xpsFactory.CreateGeometry(&lineGeom)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,linePath.SetGeometryLocal( lineGeom )
    .endif

    ;; create geometry figure and add it to geometry
    .if (SUCCEEDED(hr))
        mov hr,_xpsFactory.CreateGeometryFigure( beginPoint, &lineFigure )
    .endif
    .if (SUCCEEDED(hr))
        mov hr,lineGeom.GetFigures( &geomFigures )
    .endif
    .if (SUCCEEDED(hr))
        mov hr,geomFigures.Append( lineFigure )
    .endif

    ;; set line segment in figure

    .if (SUCCEEDED(hr))

       .new segmType:XPS_SEGMENT_TYPE = XPS_SEGMENT_TYPE_LINE
       .new segmentData[2]:FLOAT
       .new segmStroke:BOOL = TRUE

        mov rcx,endPoint
        mov segmentData[0],[rcx].XPS_POINT.x
        mov segmentData[4],[rcx].XPS_POINT.y

        mov hr,lineFigure.SetSegments(
                1, ;; segment count
                2, ;; segment data count
                &segmType, ;; segment types array (1 element)
                &segmentData,
                &segmStroke ;; segment stroke array (1 element)
                )
    .endif

    ;; line figure is not closed or filled
    .if (SUCCEEDED(hr))
        mov hr,lineFigure.SetIsClosed( FALSE )
    .endif
    .if (SUCCEEDED(hr))
        mov hr,lineFigure.SetIsFilled( FALSE )
    .endif
    SafeRelease(canvasVisuals)
    SafeRelease(linePath)
    SafeRelease(lineGeom)
    SafeRelease(geomFigures)
    SafeRelease(lineFigure)
    .return hr
    endp

    end

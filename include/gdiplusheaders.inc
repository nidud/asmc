ifndef _GDIPLUSHEADERS_H
define _GDIPLUSHEADERS_H

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

; Region();
; Region(RectF& rect);
; Region(Rect& rect);
; Region(GraphicsPath* path);
; Region(BYTE* regionData, IN INT size);
; Region(HRGN hRgn);
; static Region* FromHRGN(IN HRGN hRgn);

.template Region fastcall

    nativeRegion    ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .static Region :abs, :abs {
    ifb <_1>
        GdipCreateRegion(addr this.nativeRegion)
    elseifnb <_2>
        GdipCreateRegionRgnData(_1, _2, addr this.nativeRegion)
    elseifidn <Rect>,typeid(_1)
        GdipCreateRegionRectI(addr _1, addr this.nativeRegion)
    elseifidn <RectF>,typeid(_1)
        GdipCreateRegionRect(addr _1, addr this.nativeRegion)
    elseifidn <ptrRect>,typeid(_1)
        GdipCreateRegionRectI(_1, addr this.nativeRegion)
    elseifidn <ptrRectF>,typeid(_1)
        GdipCreateRegionRect(_1, addr this.nativeRegion)
    elseifidn <ptrGraphicsPath>,typeid(_1)
        LOADARGPTRCX(_1)
        GdipCreateRegionPath([rcx].GraphicsPath.nativePath, addr this.nativeRegion)
    elseifidn <ptrHRGN__>,typeid(_1)
        GdipCreateRegionHrgn(_1, addr this.nativeRegion)
    elseifidn <ptrRegion>,typeid(_1)
        LOADARGPTRCX(_1)
        this.SetNativeRegion([rcx].Region.nativeRegion)
        mov eax,Ok
    endif
        mov this.lastResult,eax
        }

    .static SetStatus watcall state:size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static FromHRGN :abs {
        this.SetStatus(GdipCreateRegionHrgn(_1, addr this.nativeRegion))
        }

    .static Release {
        GdipDeleteRegion(this.nativeRegion)
        }
    .static SetNativeRegion :ptr Region {
        mov this.nativeRegion,_1
        }

    .static Clone {
      local clone
       .new clone:Region
        clone.SetStatus(GdipCloneRegion(this.nativeRegion, addr clone.nativeRegion))
        lea rax,clone
        }

    .static MakeInfinite {
        this.SetStatus(GdipSetInfinite(this.nativeRegion))
        }

    .static MakeEmpty {
        this.SetStatus(GdipSetEmpty(this.nativeRegion))
        }

    .static GetDataSize {
        mov this.scratch,eax
        this.SetStatus(GdipGetRegionDataSize(this.nativeRegion, addr this.scratch))
        mov eax,this.scratch
        }

    ;; buffer     - where to put the data
    ;; bufferSize - how big the buffer is (should be at least as big as GetDataSize())
    ;; sizeFilled - if not NULL, this is an OUT param that says how many bytes
    ;;              of data were written to the buffer.

    .static GetData buffer:abs, bufferSize:abs, sizeFilled:abs {
        this.SetStatus(GdipGetRegionData(this.nativeRegion, buffer, bufferSize, sizeFilled))
        }

    Region_Combine macro this, _1, mode
      ifidn <Rect>,typeid(_1)
        this.SetStatus(GdipCombineRegionRectI(this.nativeRegion, addr _1, mode))
      elseifidn <RectF>,typeid(_1)
        this.SetStatus(GdipCombineRegionRect(this.nativeRegion, addr _1, mode))
      elseifidn <ptrGraphicsPath>,typeid(_1)
        LOADARGPTRDX(_1)
        this.SetStatus(GdipCombineRegionPath(this.nativeRegion, [rdx].GraphicsPath.nativePath, mode))
      elseifidn <ptrRegion>,typeid(_1)
        LOADARGPTRDX(_1)
        this.SetStatus(GdipCombineRegionRegion(this.nativeRegion, [rdx].Region.nativeRegion, mode))
      else
        .err <error _1>
      endif
        this.SetStatus()
        exitm<>
        endm

    .static Intersect :abs {
        Region_Combine(this, _1, CombineModeIntersect)
        }
    .static _Union :abs {
        Region_Combine(this, _1, CombineModeUnion)
        }
    .static _Xor :abs {
        Region_Combine(this, _1, CombineModeXor)
        }
    .static Exclude :abs {
        Region_Combine(this, _1, CombineModeExclude)
        }
    .static Complement :abs {
        Region_Combine(this, _1, CombineModeComplement)
        }

    .static Translate x:abs, y:abs {
        typeid(Region_Translate_, x)(this, x, y)
        this.SetStatus()
        }

    .static Transform :ptr Matrix {
        this.SetStatus(GdipTransformRegion(this.nativeRegion, [_1].Matrix.nativeMatrix))
        }

    .static GetBounds :abs, :ptr Graphics {
        typeid(Region_GetBounds_, _1)(_1, _2, this)
        this.SetStatus()
        }

    .static GetHRGN :ptr Graphics {
        this.SetStatus(GdipGetRegionHRgn(this.nativeRegion, [_1].Graphics.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static IsEmpty :ptr Graphics {
        this.SetStatus(GdipIsEmptyRegion(this.nativeRegion, [_1].Graphics.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static IsInfinite :ptr Graphics {
        this.SetStatus(GdipIsInfiniteRegion(this.nativeRegion, [_1].Graphics.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .inline IsVisible :abs, :vararg {
        typeid(Region_IsVisible_, _1)(this, _1, _2)
        this.SetStatus()
        mov eax,this.scratch
        }

    .static Equals :ptr Region, :ptr Graphics {
        this.SetStatus(GdipIsEqualRegion(this.nativeRegion, [_1].Region.nativeRegion, [_2].Graphics.nativeGraphics, addr this.scratch))
        }

    .static GetRegionScansCount :ptr Matrix {
        this.SetStatus(GdipGetRegionScansCount(this.nativeRegion,  addr this.scratch, [_1].Matrix.nativeMatrix))
        mov eax,this.scratch
        }

    .static GetRegionScans :ptr Matrix, :abs, :abs {
      ifidn <RectF>,typeid(_2)
        GdipGetRegionScans(this.nativeRegion, addr _2, _3, [_1].Matrix.nativeMatrix)
      elseifidn <Rect>,typeid(_2)
        GdipGetRegionScansI(this.nativeRegion, addr _2, _3, [_1].Matrix.nativeMatrix)
      else
        .err <error _2>
      endif
        this.SetStatus()
        }

    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .ends

define Region_Translate_flt   <Region_Translate_real4>
define Region_Translate_oword <Region_Translate_real4>
define Region_Translate_imm   <Region_Translate_sdword>
define Region_Translate_dword <Region_Translate_sdword>

Region_Translate_real4 macro this, x, y
    exitm<GdipTranslateRegion(this.nativeRegion, x, y)>
    endm
Region_Translate_sdword macro this, x, y
    exitm<GdipTranslateRegionI(this.nativeRegion, x, y)>
    endm

Region_GetBounds_ptrRect proto fastcall rect:abs, g:abs, this:abs {
    GdipGetRegionBoundsI(this.nativeRegion, [rdx].Graphics.nativeGraphics, rect)
    }
Region_GetBounds_ptrRectF proto fastcall rect:abs, g:abs, this:abs {
    GdipGetRegionBounds(this.nativeRegion, [rdx].Graphics.nativeGraphics, rect)
    }

define Region_IsVisible_flt   <Region_IsVisible_real4>
define Region_IsVisible_oword <Region_IsVisible_real4>
define Region_IsVisible_imm   <Region_IsVisible_sdword>
define Region_IsVisible_dword <Region_IsVisible_sdword>

Region_IsVisible_real4 macro this, x, y, width:=<NULL>, height, g:=<NULL>
ifb <height>
    .if LOADARGPTRCX(width)
        mov rcx,[rcx].Graphics.nativeGraphics
    .endif
    exitm<GdipIsVisibleRegionPoint(this.nativeRegion, x, y, rcx, addr this.scratch)>
else
    .if LOADARGPTRCX(g)
        mov rcx,[rcx].Graphics.nativeGraphics
    .endif
    exitm<GdipIsVisibleRegionRect(this.nativeRegion, x, y, width, height, rcx, addr this.scratch)>
endif
    endm

Region_IsVisible_sdword macro this, x, y, width:=<NULL>, height, g:=<NULL>
ifb <height>
    .if LOADARGPTRCX(width)
        mov rcx,[rcx].Graphics.nativeGraphics
    .endif
    exitm<GdipIsVisibleRegionPointI(this.nativeRegion, x, y, rcx, addr this.scratch)>
else
    .if LOADARGPTRCX(g)
        mov rcx,[rcx].Graphics.nativeGraphics
    .endif
    exitm<GdipIsVisibleRegionRectI(this.nativeRegion, x, y, width, height, rcx, addr this.scratch)>
endif
    endm

Region_IsVisible_PointF macro this, point, g:=<NULL>
    exitm<Region_IsVisible_real4(this, point.X, point.Y, g)>
    endm
Region_IsVisible_Point macro this, point, g:=<NULL>
    exitm<Region_IsVisible_sdword(this, point.X, point.Y, g)>
    endm
Region_IsVisible_RectF macro this, rect, g:=<NULL>
    exitm<Region_IsVisible_real4(this, rect.X, rect.Y, rect.Width, rect.Height, g)>
    endm
Region_IsVisible_Rect macro this, rect, g:=<NULL>
    exitm<Region_IsVisible_sdword(this, rect.X, rect.Y, rect.Width, rect.Height, g)>
    endm

;;--------------------------------------------------------------------------
;; FontFamily
;;
;; FontFamily() : nativeFamily(NULL), lastResult(Ok)
;; FontFamily(WCHAR*, FontCollection = NULL)
;; FontFamily(FontFamily *, Status)
;;
;;--------------------------------------------------------------------------

.template FontFamily fastcall

    nativeFamily    ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .static FontFamily :abs, :abs=<0> {
      ifb <_1>
        mov eax,Ok
        mov this.nativeFamily,NULL
      elseifidn <ptrword>,typeid(_1)
        .if LOADARGPTRDX(_2)
            mov rdx,[rdx].FontCollection.nativeFontCollection
        .endif
        GdipCreateFontFamilyFromName(_1, rdx, addr this.nativeFamily)
      else
        mov this.nativeFamily,_1
        mov this.lastResult,_2
      endif
        mov this.lastResult,eax
        }

    .static SetStatus watcall state:size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static Release {
        GdipDeleteFontFamily(this.nativeFamily)
        }

    .static GenericSansSerif {
        GdipGetGenericFontFamilySansSerif(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    .static GenericSerif {
        GdipGetGenericFontFamilySerif(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    .static GenericMonospace {
        GdipGetGenericFontFamilyMonospace(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    .inline GetFamilyName :abs, :abs, :vararg {
        GdipGetFamilyName(this.nativeFamily, _1, _2)
        this.SetStatus()
        }

    .static Clone {
      local clone
       .new clone:FontFamily
        GdipCloneRegion(this.nativeFamily, addr clone.nativeFamily)
        clone.SetStatus()
        lea rax,clone
        }

    .static IsAvailable {
        xor     eax,eax
        cmp     rax,this.nativeFamily
        setnz   al
        }

    .static IsStyleAvailable :abs {
        this.SetStatus(GdipIsStyleAvailable(this.nativeFamily, _1, addr this.scratch))
        .if eax
            mov this.scratch,FALSE
        .endif
        mov eax,this.scratch
        }

    .static GetEmHeight :abs {
        this.SetStatus(GdipGetEmHeight(this.nativeFamily, _1, addr this.scratch))
        }

    .static GetCellAscent :abs {
        this.SetStatus(GdipGetCellAscent(this.nativeFamily, _1, addr this.scratch))
        }

    .static GetCellDescent :abs {
        this.SetStatus(GdipGetCellDescent(this.nativeFamily, _1, addr this.scratch))
        }

    .static GetLineSpacing :abs {
        this.SetStatus(GdipGetLineSpacing(this.nativeFamily, _1, addr this.scratch))
        }

    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .ends

externdef GenericSansSerifFontFamily        :ptr FontFamily
externdef GenericSerifFontFamily            :ptr FontFamily
externdef GenericMonospaceFontFamily        :ptr FontFamily

externdef GenericSansSerifFontFamilyBuffer  :FontFamily
externdef GenericSerifFontFamilyBuffer      :FontFamily
externdef GenericMonospaceFontFamilyBuffer  :FontFamily


;;--------------------------------------------------------------------------
;; Font
;;
;; Font(HDC)
;; Font(HDC, LOGFONTA*)
;; Font(HDC, LOGFONTW*)
;; Font(HDC, HFONT)
;; Font(FontFamily*, REAL, int, Unit)
;; Font(WCHAR*, REAL, int, Unit, FontCollection*)
;;
;;--------------------------------------------------------------------------

.template Font fastcall

    nativeFont  ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .static Font :abs, :abs, :abs=<FontStyleRegular>, :abs=<UnitPoint>, :abs=<NULL> {
      ifb <_2>
        GdipCreateFontFromDC(_1, addr this.nativeFont)
      elseifidn <ptrLOGFONTA>,typeid(_2)
        GdipCreateFontFromLogfontA(_1, _2, addr this.nativeFont)
      elseifidn <ptrLOGFONTW>,typeid(_2)
        GdipCreateFontFromLogfontW(_1, _2, addr this.nativeFont)
      elseifidn <ptrHFONT__>,typeid(_2)
        .new lf:LOGFONTA
        .new hdc:HDC =_1
        .ifd GetObjectA(_2, LOGFONTA, addr lf)
            GdipCreateFontFromLogfontA(hdc, addr lf, addr this.nativeFont)
        .else
            GdipCreateFontFromDC(hdc, addr this.nativeFont)
        .endif
      elseifidn <ptrFontFamily>,typeid(_1)
        .if LOADARGPTRCX(_1)
            mov rcx,[rcx].FontFamily.nativeFamily
        .endif
        GdipCreateFont(rcx, _2, _3, _4, addr this.nativeFont)
      elseifidn <ptrword>,typeid(_1)
       .new emSize:REAL = _2
       .new family:FontFamily(_1, _5)
        mov this.lastResult,eax
        .repeat
            .if eax != Ok
                family.GenericSansSerif()
                .break.if eax != Ok
            .endif
            GdipCreateFont(family.nativeFamily, emSize, _3, _4, addr this.nativeFont)
            .if eax != Ok
                mov this.lastResult,eax
                family.GenericSansSerif()
                .break.if eax != Ok
                GdipCreateFont(family.nativeFamily, emSize, _3, _4, addr this.nativeFont)
            .endif
        .until 1
      elseifidn <ptrFont>,typeid(_1)
        mov this.nativeFamily,_1
        mov this.lastResult,Ok
      else
        .err <_2>
      endif
        mov this.lastResult,eax
        }

    .static Release {
        GdipDeleteFont(this.nativeFont)
        }

    .static SetNativeFont :ptr Font {
        mov this.nativeFont,_1
        }

    .static SetStatus watcall state:size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static GetLogFontA :ptr Graphics, :abs {
        .if _1
            mov _1,[_1].Graphics.nativeGraphics
        .endif
        this.SetStatus(GdipGetLogFontA(this.nativeFont, _1, _2))
        }

    .static GetLogFontW :ptr Graphics, :abs {
        .if _1
            mov _1,[_1].Graphics.nativeGraphics
        .endif
        this.SetStatus(GdipGetLogFontW(this.nativeFont, _1, _2))
        }

    .static Clone {
       .new clone:Font
        clone.SetStatus(GdipCloneFont(this.nativeFont, addr clone.nativeFont))
        lea rax,clone
        }

    .static IsAvailable {
        xor eax,eax
        cmp rax,this.nativeFont
        setnz al
        }

    .static GetStyle {
        this.SetStatus(GdipGetFontStyle(this.nativeFont, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetSize {
        this.SetStatus(GdipGetFontSize(this.nativeFont, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetUnit {
        this.SetStatus(GdipGetFontUnit(this.nativeFont, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetLastStatus {
        this.SetStatus()
        }

    .static GetHeight :abs {
      ifidn <ptrGraphics>,typeid(_1)
        .if LOADARGPTRDX(_1)
            mov rdx,[rdx].Graphics.nativeGraphics
        .endif
        this.SetStatus(GdipGetFontHeight(this.nativeFont, rdx, addr this.scratch))
      else
        this.SetStatus(GdipGetFontHeightGivenDPI(this.nativeFont, _1, addr this.scratch))
      endif
        mov eax,this.scratch
        }

    .static GetFamily :ptr FontFamily {
        mov eax,InvalidParameter
        .if _1
           .new fontfamily:ptr FontFamily
            mov fontfamily,_1
            .ifd GdipGetFamily(this.nativeFont, addr [_1].FontFamily.nativeFamily)
                mov rdx,fontfamily
                mov [rdx].FontFamily.lastResult,eax
            .endif
        .endif
        this.SetStatus()
        }

    .ends

;;--------------------------------------------------------------------------
;; Font Collection
;;--------------------------------------------------------------------------

.template FontCollection fastcall

    nativeFontCollection    ptr_t ?
    lastResult              Status ?

    .static FontCollection {
        mov this.nativeFontCollection,NULL
        }

    .static Release {}

    .static SetStatus watcall state:size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static GetFamilyCount {
       .new numFound:int_t = 0
        GdipGetFontCollectionFamilyCount(this.nativeFontCollection, addr numFound)
        mov eax,numFound
        }

    .static GetFamilies :int_t, :ptr FontFamily, :abs {
      local nativeFamilyList, numSought, gpfamilies, numFound, fontcollection, i
       .new nativeFamilyList:ptr ptr FontFamily
       .new numSought:int_t = _1
       .new gpfamilies:ptr FontFamily = _2
       .new numFound:ptr int_t
       .new fontcollection:ptr FontCollection
       .new i:int_t
        mov numFound,LOADARGPTRAX(_3)
        .repeat
            .ifs ( numSought <= 0 || gpfamilies == NULL || numFound == NULL)
                mov eax,InvalidParameter
                mov this.lastResult,eax
               .break
            .endif
            mov dword ptr [rax],0
            imul ecx,numSought,size_t
            mov nativeFamilyList,GdipAlloc(rcx)
            .if ( rax == NULL )
                mov eax,OutOfMemory
                mov this.lastResult,eax
               .break
            .endif
            .ifd ( GdipGetFontCollectionFamilyList(this.nativeFontCollection, numSought, rax, numFound) == Ok )
                .for ( i = 0 : : i++ )
                    mov rax,numFound
                    mov eax,[rax]
                    .break .if eax <= i
                    imul ecx,i,size_t
                    imul edx,i,FontFamily
                    add  rcx,nativeFamilyList
                    add  rdx,gpfamilies
                    GdipCloneFontFamily([rcx], addr [rdx].FontFamily.nativeFamily)
                .endf
                xor eax,eax
            .endif
            GdipFree(nativeFamilyList)
        .until 1
        }

    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .ends


.template InstalledFontCollection fastcall : public FontCollection

    .static InstalledFontCollection {
        mov this.nativeFontCollection,NULL
        }
    .ends


.template PrivateFontCollection fastcall : public FontCollection

    .static PrivateFontCollection {
        mov this.nativeFontCollection,NULL
        }
    .static AddFontFile :ptr WCHAR {
        .ifd GdipPrivateAddFontFile(this.nativeFontCollection, _1)
            mov this.lastResult,eax
        .endif
        }
    .static AddMemoryFont :ptr, :int_t {
        .ifd GdipPrivateAddMemoryFont(this.nativeFontCollection, _1, _2)
            mov this.lastResult,eax
        .endif
        }
    .ends


;;--------------------------------------------------------------------------
;; Abstract base class for Image and Metafile
;;--------------------------------------------------------------------------

.template ImageBase fastcall

    nativeImage     ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .static SetStatus watcall state:size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static Release {
        GdipDisposeImage(this.nativeImage)
        }

    .static Save filename:abs, clsidEncoder:abs, encoderParams:abs=<NULL> {
    ifidn <ptrIStream>,typeid(filename)
        GdipSaveImageToStream(this.nativeImage, filename, clsidEncoder, encoderParams)
    else
        GdipSaveImageToFile(this.nativeImage, filename, clsidEncoder, encoderParams)
    endif
        this.SetStatus()
        }

    .static SaveAdd newImage:abs, encoderParams:abs {
    ifb <encoderParams>
        GdipSaveAdd(this.nativeImage, newImage)
    else
        mov eax,InvalidParameter
        .if LOADARGPTRDX(newImage)
            GdipSaveAddImage(this.nativeImage, [rdx].Image.nativeImage, encoderParams)
        .endif
    endif
        }

    .static GetType {
        mov this.scratch,ImageTypeUnknown
        GdipGetImageType(this.nativeImage, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetPhysicalDimension size:ptr SizeF {
        mov eax,InvalidParameter
        .if size
            GdipGetImageDimension(this.nativeImage, &[size].SizeF.Width, &[size].SizeF.Height)
        .endif
        this.SetStatus()
        }

    .static GetBounds srcRect:abs, srcUnit:abs {
        this.SetStatus(GdipGetImageBounds(this.nativeImage, srcRect, srcUnit))
        }

    .static GetWidth {
        mov this.scratch,0
        GdipGetImageWidth(this.nativeImage, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetHeight {
        mov this.scratch,0
        GdipGetImageHeight(this.nativeImage, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetHorizontalResolution {
        mov this.scratch,0
        GdipGetImageHorizontalResolution(this.nativeImage, addr this.scratch)
        movss xmm0,this.scratch
        }

    .static GetVerticalResolution {
        mov this.scratch,0
        GdipGetImageVerticalResolution(this.nativeImage, addr this.scratch)
        movss xmm0,this.scratch
        }

    .static GetFlags {
        mov this.scratch,0
        GdipGetImageFlags(this.nativeImage, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetRawFormat format:abs {
        this.SetStatus(GdipGetImageRawFormat(this.nativeImage, format))
        }

    .static GetPixelFormat {
        GdipGetImagePixelFormat(this.nativeImage, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetPaletteSize {
        mov this.scratch,0
        GdipGetImagePaletteSize(this.nativeImage, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetPalette palette:abs, size:abs {
        this.SetStatus(GdipGetImagePalette(this.nativeImage, palette, size))
        }

    .static SetPalette palette:abs {
        this.SetStatus(GdipSetImagePalette(this.nativeImage, palette))
        }

    .static GetThumbnailImage thumbWidth:abs, thumbHeight:abs, callback:abs=<NULL>, callbackData:abs=<NULL> {
       .new thumbimage:Image
        GdipGetImageThumbnail(this.nativeImage, thumbWidth, thumbHeight, addr thumbimage.nativeImage, callback, callbackData)
        mov thumbimage.lastResult,eax
        lea rax,thumbimage
        }

    .static GetFrameDimensionsCount {
        mov this.scratch,0
        GdipImageGetFrameDimensionsCount(this.nativeImage, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetFrameDimensionsList dimensionIDs:abs, count:abs {
        this.SetStatus(GdipImageGetFrameDimensionsList(this.nativeImage, dimensionIDs, count))
        }

    .static GetFrameCount dimensionID:abs {
        mov this.scratch,0
        this.SetStatus(GdipImageGetFrameCount(this.nativeImage, dimensionID, addr this.scratch))
        mov eax,this.scratch
        }

    .static SelectActiveFrame dimensionID:abs, frameIndex:abs {
        this.SetStatus(GdipImageSelectActiveFrame(this.nativeImage, dimensionID, frameIndex))
        }

    .static RotateFlip rotateFlipType:abs {
        this.SetStatus(GdipImageRotateFlip(this.nativeImage, rotateFlipType))
        }

    .static GetPropertyCount {
        mov this.scratch,0
        this.SetStatus(GdipGetPropertyCount(this.nativeImage, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetPropertyIdList numOfProperty:abs, list:abs {
        this.SetStatus(GdipGetPropertyIdList(this.nativeImage, numOfProperty, list))
        }

    .static GetPropertyItemSize propId:abs {
        mov this.scratch,0
        GdipGetPropertyItemSize(this.nativeImage, propId, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetPropertyItem propId:abs, propSize:abs, buffer:abs {
        this.SetStatus(GdipGetPropertyItem(this.nativeImage, propId, propSize, buffer))
        }

    .static GetPropertySize totalBufferSize:abs, numProperties:abs {
        this.SetStatus(GdipGetPropertySize(this.nativeImage, totalBufferSize, numProperties))
        }

    .static GetAllPropertyItems totalBufferSize:abs, numProperties:abs, allItems:abs {
        mov eax,InvalidParameter
        .if LOADARGPTRCX(allItems)
            GdipGetAllPropertyItems(this.nativeImage, totalBufferSize, numProperties, rcx)
        .endif
        this.SetStatus()
        }

    .static RemovePropertyItem propId:abs {
        this.SetStatus(GdipRemovePropertyItem(this.nativeImage, propId))
        }

    .static SetPropertyItem item:abs {
        this.SetStatus(GdipSetPropertyItem(this.nativeImage, item))
        }

    .static GetEncoderParameterListSize clsidEncoder:abs {
        mov this.scratch,0
        GdipGetEncoderParameterListSize(this.nativeImage, clsidEncoder, addr this.scratch)
        mov eax,this.scratch
        }

    .static GetEncoderParameterList clsidEncoder:abs, size:abs, buffer:abs {
        this.SetStatus(GdipGetEncoderParameterList(this.nativeImage, clsidEncoder, size, buffer))
        }

if (GDIPVER GE 0x0110)
    .static FindFirstItem :abs {
        this.SetStatus(GdipFindFirstImageItem(this.nativeImage, _1))
        }
    .static FindNextItem :abs {
        this.SetStatus(GdipFindNextImageItem(this.nativeImage, _1))
        }
    .static GetItemData :abs {
        this.SetStatus(GdipGetImageItemData(this.nativeImage, _1))
        }
    .static SetAbort :abs {
        this.SetStatus(GdipImageSetAbort(this.nativeImage, _1))
        }
endif

    .static SetNativeImage :ptr Image {
        mov this.nativeImage,_1
        }

    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    .ends


; Image(WCHAR*, BOOL = FALSE)
; Image(IStream*, BOOL = FALSE)

.template Image fastcall : public ImageBase

    .static Image filename:abs, useEmbeddedColorManagement:abs=<FALSE> {
        mov this.nativeImage,NULL
      ifidn <ptrIStream>,typeid(filename)
        if useEmbeddedColorManagement
            GdipLoadImageFromStreamICM(filename, addr this.nativeImage)
        else
            GdipLoadImageFromStream(filename, addr this.nativeImage)
        endif
      else
        if useEmbeddedColorManagement
            GdipLoadImageFromFileICM(filename, addr this.nativeImage)
        else
            GdipLoadImageFromFile(filename, addr this.nativeImage)
        endif
      endif
        mov this.lastResult,eax
        }

    .static FromFile filename:abs, useEmbeddedColorManagement:abs=<FALSE> {
      if useEmbeddedColorManagement
        GdipLoadImageFromFileICM(filename, addr this.nativeImage)
      else
        GdipLoadImageFromFile(filename, addr this.nativeImage)
      endif
        mov this.lastResult,eax
        }

    .static FromStream stream:abs, useEmbeddedColorManagement:abs=<FALSE> {
        if useEmbeddedColorManagement
            GdipLoadImageFromStreamICM(stream, addr this.nativeImage)
        else
            GdipLoadImageFromStream(stream, addr this.nativeImage)
        endif
        mov this.lastResult,eax
        }

    .static Clone {
       .new clone:Image
        GdipCloneImage(this.nativeImage, addr clone.nativeImage)
        mov clone.lastResult,eax
        lea rax,clone
        }
    .ends
    GpImage typedef Image


; Bitmap(WCHAR*, BOOL = FALSE)
; Bitmap(IStream*, BOOL = FALSE)
; Bitmap(INT, INT, INT, PixelFormat, BYTE*)
; Bitmap(INT, INT, PixelFormat = PixelFormat32bppARGB)
; Bitmap(INT, INT, Graphics*)
; Bitmap(IDirectDrawSurface7*)
; Bitmap(BITMAPINFO*, VOID*)
; Bitmap(HBITMAP, HPALETTE)
; Bitmap(HICON)
; Bitmap(HINSTANCE, WCHAR*)

.template Bitmap fastcall : public ImageBase

    .static Bitmap :abs, :abs=<FALSE>, :abs=<PixelFormat32bppARGB>, :abs, :abs {
    ifb <_1>
        mov this.nativeImage,NULL
        mov this.lastResult,NotImplemented
    elseifidn <ptrword>,typeid(_1)
        if _2
            GdipCreateBitmapFromFileICM(_1, addr this.nativeImage)
        else
            GdipCreateBitmapFromFile(_1, addr this.nativeImage)
        endif
    elseifidn <ptrIStream>,typeid(_1)
        if _2
            GdipCreateBitmapFromStreamICM(_1, addr this.nativeImage)
        else
            GdipCreateBitmapFromStream(_1, addr this.nativeImage)
        endif
    elseifidn <ptrIDirectDrawSurface7>,typeid(_1)
        GdipCreateBitmapFromDirectDrawSurface(_1, addr this.nativeImage)
    elseifidn <ptrHICON__>,typeid(_1)
        GdipCreateBitmapFromHICON(_1, addr this.nativeImage)
    elseifidn <ptrBITMAPINFO>,typeid(_1)
        GdipCreateBitmapFromGdiDib(_1, _2, addr this.nativeImage)
    elseifidn <ptrHINSTANCE__>,typeid(_1)
        GdipCreateBitmapFromResource(_1, _2, addr this.nativeImage)
    elseifidn <ptrHBITMAP__>,typeid(_1)
        GdipCreateBitmapFromHBITMAP(_1, _2, addr this.nativeImage)
    elseifidn <ptrGraphics>,typeid(_3)
        LOADARGPTRCX(_3)
        GdipCreateBitmapFromGraphics(_1, _2, [rcx].Graphics.nativeGraphics, addr this.nativeImage)
    elseifb <_4>
        GdipCreateBitmapFromScan0(_1, _2, 0, _3, NULL, addr this.nativeImage)
    else
        GdipCreateBitmapFromScan0(_1, _2, _3, _4, _5, addr this.nativeImage)
    endif
        mov this.lastResult,eax
        }

    .static FromFile filename:abs, useEmbeddedColorManagement:abs=<FALSE> {
        if useEmbeddedColorManagement
            GdipCreateBitmapFromFileICM(filename, addr this.nativeImage)
        else
            GdipCreateBitmapFromFile(filename, addr this.nativeImage)
        endif
        mov this.lastResult,eax
        }

    .static FromStream stream:abs, useEmbeddedColorManagement:abs=<FALSE> {
        if useEmbeddedColorManagement
            GdipCreateBitmapFromStreamICM(stream, addr this.nativeImage)
        else
            GdipCreateBitmapFromStream(stream, addr this.nativeImage)
        endif
        mov this.lastResult,eax
        }

    .static Clone :abs, :abs, :abs, :abs, :abs {
       .new clone:Image
    ifidn <sdword>,typeid(_1)
        GdipCloneBitmapAreaI(_1, _2, _3, _4, _5, this.nativeImage, addr clone.nativeImage)
    elseifidn <imm>,typeid(_1)
        GdipCloneBitmapAreaI(_1, _2, _3, _4, _5, this.nativeImage, addr clone.nativeImage)
    elseifidn <real4>,typeid(_1)
        GdipCloneBitmapArea(_1, _2, _3, _4, _5, this.nativeImage, addr clone.nativeImage)
    elseifidn <flt>,typeid(_1)
        GdipCloneBitmapArea(_1, _2, _3, _4, _5, this.nativeImage, addr clone.nativeImage)
    elseifidn <RectF>,typeid(_1)
        GdipCloneBitmapArea(_1.X, _1.Y, _1.Width, _1.Height, _2, this.nativeImage, addr clone.nativeImage)
    elseifidn <Rect>,typeid(_1)
        GdipCloneBitmapAreaI(_1.X, _1.Y, _1.Width, _1.Height, _2, this.nativeImage, addr clone.nativeImage)
    else
        .err <_1>
    endif
        mov clone.lastResult,eax
        lea rax,clone
        }

    .static LockBits rect:abs, flags:abs, format:abs, lockedBitmapData:abs {
        this.SetStatus(GdipBitmapLockBits(this.nativeImage, rect, flags, format, lockedBitmapData))
        }

    .static UnlockBits lockedBitmapData:abs {
        this.SetStatus(GdipBitmapUnlockBits(this.nativeImage, lockedBitmapData))
        }

    .static GetPixel x:abs, y:abs, color:abs {
        this.SetStatus(GdipBitmapGetPixel(this.nativeImage, x, y, color))
        }

    .static SetPixel x:abs, y:abs, color:abs {
        this.SetStatus(GdipBitmapSetPixel(this.nativeImage, x, y, color))
        }

if (GDIPVER GE 0x0110)

    .static ConvertFormat format:abs, dithertype:abs, palettetype:abs, palette:abs, alphaThresholdPercent:abs {
        this.SetStatus(GdipBitmapConvertFormat(this.nativeImage, format, dithertype, palettetype, palette, alphaThresholdPercent))
        }

    ;; The palette must be allocated and count must be set to the number of
    ;; entries in the palette. If there are not enough, the API will fail.

    .static InitializePalette :abs,  ;; Palette to initialize.
                              :abs,  ;; palette enumeration type.
                              :abs,  ;; how many optimal colors
                              :abs,  ;; add a transparent color to the palette.
                              :abs { ;; optional bitmap for median cut.
        .if LOADARGPTRAX(_3)
            mov rax,[rax].Image.nativeImage
        .endif
        this.SetStatus(GdipInitializePalette(_1, _2, _3, _4, rax))
        }

    ; ApplyEffect(Effect *effect, RECT *ROI);
    ; ApplyEffect(Bitmap **inputs, INT numInputs, Effect *effect, RECT *ROI, RECT *outputRect, Bitmap **output);

    .static ApplyEffect inputs:ptr, numInputs:abs, effect:abs, ROI:abs, outputRect:abs, output:abs {
      local s,d,b,outputNative,nativeInputs
       .new s:ptr = rsi
       .new d:ptr = rdi
        mov rdi,rcx
    ifb <effect>
        mov rsi,LOADARGPTRAX(numInputs) ; ROI
        .if [rdi].Effect.auxData
            GdipFree([rdi].Effect.auxData)
            mov [rdi].Effect.auxData,NULL
            mov [rdi].Effect.auxDataSize,0
        .endif
        GdipBitmapApplyEffect(this.nativeImage, [rdi].Effect.nativeEffect, rsi,
            [rdi].Effect.useAuxData, &[rdi].Effect.auxData, &[rdi].Effect.auxDataSize)
    else
       .new b:ptr = rbx
        mov ebx,numInputs
        mov rsi,LOADARGPTRAX(effect)
        .repeat
            .ifs ebx < 0
                mov ebx,InvalidParameter
               .break
            .endif
            .new outputNative:ptr Bitmap = NULL
            .new nativeInputs:ptr ptr Bitmap
            mov nativeInputs,GdipAlloc(&[rbx*size_t])
            .if rax == NULL
                mov eax,OutOfMemory
               .break
            .endif
            .for ( rdx = rax, ecx = 0 : ecx < ebx : ecx++ )
                mov [rdx+rcx*size_t],[rdi+rcx*size_t].Bitmap.nativeImage
            .endf
            .if [rsi].Effect.auxData
                GdipFree([rsi].Effect.auxData)
                mov [rsi].Effect.auxData,NULL
                mov [rsi].Effect.auxDataSize,0
            .endif
            mov ebx,GdipBitmapCreateApplyEffect(nativeInputs, numInputs, [rsi].Effect.nativeEffect,
                        ROI, outputRect, &outputNative, [rsi].Effect.useAuxData,
                        &[rsi].Effect.auxData, &[rsi].Effect.auxDataSize)
            .if eax == Ok && outputNative
                .if GdipAlloc(Bitmap) == NULL
                    GdipDisposeImage(outputNative)
                    mov eax,OutOfMemory
                   .break
                .endif
                mov rdx,output
                mov [rdx],rax
                mov rdx,outputNative
                mov [rax].Bitmap.nativeImage,rdx
            .else
                mov rdx,output
                xor eax,eax
                mov [rdx],rax
            .endif
            GdipFree(nativeInputs)
            mov eax,ebx
        .until 1
        mov rbx,b
    endif
        mov rsi,s
        mov rdi,d
        }

    .static GetHistogram format:abs, NumberOfEntries:abs, channel0:abs, channel1:abs, channel2:abs, channel3:abs {
        GdipBitmapGetHistogram(this.nativeImage, format, NumberOfEntries, channel0, channel1, channel2, channel3)
        }
    .static GetHistogramSize format:abs, NumberOfEntries:abs {
        GdipBitmapGetHistogramSize(format, NumberOfEntries)
        }
endif

    .static SetResolution xdpi:abs, ydpi:abs {
        this.SetStatus(GdipBitmapSetResolution(this.nativeImage, xdpi, ydpi))
        }
    .static GetHBITMAP colorBackground:abs, hbmReturn:abs {
        this.SetStatus(GdipCreateHBITMAPFromBitmap(this.nativeImage, hbmReturn, colorBackground))
        }
    .static GetHICON hicon:abs {
        this.SetStatus(GdipCreateHICONFromBitmap(this.nativeImage, hicon))
        }
    .ends
    GpBitmap typedef Bitmap


;
; CustomLineCap(GraphicsPath* fillPath, GraphicsPath* strokePath, LineCap baseCap = LineCapFlat, REAL baseInset = 0);
;
.template CustomLineCap fastcall

    nativeCap   ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .static CustomLineCap :ptr GraphicsPath, :ptr GraphicsPath, :abs=<LineCapFlat>, :abs=<0.0> {
        .if rcx
            mov rcx,[rcx].GraphicsPath.nativePath
        .endif
        .if rdx
            mov rdx,[rdx].GraphicsPath.nativePath
        .endif
        GdipCreateCustomLineCap(rcx, rdx, _3, _4, addr this.nativeCap)
        mov this.lastResult,eax
        }

    .static Release {
        GdipDeleteCustomLineCap(this.nativeCap)
        }

    .static SetNativeCap :ptr CustomLineCap {
        mov this.nativeCap,_1
        }

    .static SetStatus watcall state:size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static Clone {
       .new clone:CustomLineCap
        GdipCloneCustomLineCap(this.nativeCap, addr clone.nativeCap)
        mov clone.lastResult,eax
        lea rax,clone
        }

    ;; This changes both the start and end cap.

    .static SetStrokeCap strokeCap:abs {
        this.SetStrokeCaps(strokeCap, strokeCap)
        }
    .static SetStrokeCaps  startCap:abs, endCap:abs {
        this.SetStatus(GdipSetCustomLineCapStrokeCaps(this.nativeCap, startCap, endCap))
        }
    .static GetStrokeCaps startCap:abs, endCap:abs {
        this.SetStatus(GdipGetCustomLineCapStrokeCaps(this.nativeCap, startCap, endCap))
        }
    .static SetStrokeJoin lineJoin:abs {
        this.SetStatus(GdipSetCustomLineCapStrokeJoin(this.nativeCap, lineJoin))
        }
    .static GetStrokeJoin {
        this.SetStatus(GdipGetCustomLineCapStrokeJoin(this.nativeCap, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetBaseCap baseCap:abs {
        this.SetStatus(GdipSetCustomLineCapBaseCap(this.nativeCap, baseCap))
        }
    .static GetBaseCap {
        this.SetStatus(GdipGetCustomLineCapBaseCap(this.nativeCap, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetBaseInset inset:abs {
        this.SetStatus(GdipSetCustomLineCapBaseInset(this.nativeCap, inset))
        }
    .static GetBaseInset {
        this.SetStatus(GdipGetCustomLineCapBaseInset(this.nativeCap, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetWidthScale widthScale:abs {
        this.SetStatus(GdipSetCustomLineCapWidthScale(this.nativeCap, widthScale))
        }
    .static GetWidthScale {
        this.SetStatus(GdipGetCustomLineCapWidthScale(this.nativeCap, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .ends
    GpCustomLineCap typedef CustomLineCap


.template CachedBitmap fastcall : public ImageBase

    .static CachedBitmap :ptr Bitmap, :ptr Graphics {
        GdipCreateCachedBitmap([_1].Bitmap.nativeImage, [_2].Graphics.nativeGraphics, addr this.nativeImage)
        mov this.lastResult,eax
        }
    .ends

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Metafile(HMETAFILE, WmfPlaceableFileHeader*, BOOL = FALSE)
; Metafile(HENHMETAFILE, BOOL = FALSE)
; Metafile(WCHAR*)
; Metafile(WCHAR*, WmfPlaceableFileHeader*)
; Metafile(WCHAR*, HDC, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(WCHAR*, HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(WCHAR*, HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(IStream*)
; Metafile(IStream*, HDC, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(IStream*, HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(IStream*, HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(HDC, EmfType, WCHAR*)
; Metafile(HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
;
; Metafile::GetMetafileHeader(HMETAFILE, WmfPlaceableFileHeader*, MetafileHeader*)
; Metafile::GetMetafileHeader(HENHMETAFILE, MetafileHeader*)
; Metafile::GetMetafileHeader(WCHAR*, MetafileHeader*)
; Metafile::GetMetafileHeader(IStream*, MetafileHeader*)
; Metafile::GetMetafileHeader(MetafileHeader*)
;
.template Metafile fastcall : public ImageBase

    .inline Metafile :abs, :vararg {
        typeid(Metafile_, _1)(this, _1, _2)
        mov this.lastResult,eax
        }

    .inline GetMetafileHeader :abs, :vararg {
        typeid(Metafile_GetMetafileHeader_, _1)(this, _1, _2)
        this.SetStatus()
        }

    ; Once this method is called, the Metafile object is in an invalid state
    ; and can no longer be used.  It is the responsiblity of the caller to
    ; invoke DeleteEnhMetaFile to delete this hEmf.

    .static GetHENHMETAFILE {
       .new hEmf:HENHMETAFILE
        this.SetStatus(GdipGetHemfFromMetafile(this.nativeImage, &hEmf))
        mov rax,hEmf
        }

    ; Used in conjuction with Graphics::EnumerateMetafile to play an EMF+
    ; The data must be DWORD aligned if it's an EMF or EMF+.  It must be
    ; WORD aligned if it's a WMF.
    ; PlayRecord(EmfPlusRecordType, UINT, UINT, BYTE*)

    .static PlayRecord recordType:abs, flags:abs, dataSize:abs, data:abs {
        this.SetStatus(GdipPlayMetafileRecord(this.nativeImage, recordType, flags, dataSize, data))
        }

    ; If you're using a printer HDC for the metafile, but you want the
    ; metafile rasterized at screen resolution, then use this API to set
    ; the rasterization dpi of the metafile to the screen resolution,
    ; e.g. 96 dpi or 120 dpi.

    .static SetDownLevelRasterizationLimit metafileRasterizationLimitDpi:abs {
        this.SetStatus(GdipSetMetafileDownLevelRasterizationLimit(this.nativeImage,  metafileRasterizationLimitDpi))
        }

    .static GetDownLevelRasterizationLimit {
        mov this.scratch,0
        this.SetStatus(GdipGetMetafileDownLevelRasterizationLimit(this.nativeImage, addr this.scratch))
        mov eax,this.scratch
        }

    .static EmfToWmfBits hemf:abs, cbData16:abs, pData16:abs, iMapMode:abs=<MM_ANISOTROPIC>, eFlags:abs=<EmfToWmfBitsFlagsDefault> {
        this.SetStatus(GdipEmfToWmfBits(hemf, cbData16, pData16, iMapMode, eFlags))
        }

if (GDIPVER GE 0x0110)
    .inline ConvertToEmfPlus :ptr Graphics, :abs, :vararg {
        mov rcx,[_1].Graphics.nativeGraphics
        typeid(Metafile_ConvertToEmfPlus_, _2)(this, rcx, _2, _3)
        this.SetStatus()
        }
endif
    .ends

;
; Playback a metafile from a HMETAFILE
; If deleteWmf is TRUE, then when the metafile is deleted,
; the hWmf will also be deleted.  Otherwise, it won't be.
;
Metafile_ptrHMETAFILE__ macro this, _1, _2, _3:=<FALSE>
    exitm<GdipCreateMetafileFromWmf(_1, _3, _2, addr this.nativeImage)>
    endm
;
; Playback a metafile from a HENHMETAFILE
; If deleteEmf is TRUE, then when the metafile is deleted,
; the hEmf will also be deleted.  Otherwise, it won't be.
;
Metafile_ptrHENHMETAFILE__ macro this, _1, _2:=<FALSE>
    exitm<GdipCreateMetafileFromEmf(_1, _2, addr this.nativeImage)>
    endm
;
; Playback a WMF metafile from a file.
;
Metafile_ptrword macro this, _1, _2, _3:vararg
ifb <_2>
    exitm<GdipCreateMetafileFromFile(_1, addr this.nativeImage)>
else
%   exitm<typeid(Metafile_ptrword_, _2)(this, _1, _2, _3)>
endif
    endm
Metafile_ptrword_ptrWmfPlaceableFileHeader macro this, _1, _2, _3
    exitm<GdipCreateMetafileFromWmfFile(_1, _2, addr this.nativeImage)>
    endm
Metafile_ptrword_ptrHDC__ macro this, _1, _2, _3, _4:vararg
ifb <_3>
    exitm<GdipRecordMetafileFileName(_1, _2, EmfTypeEmfPlusDual, NULL, MetafileFrameUnitGdi, NULL, addr this.nativeImage)>
else
%   exitm<typeid(Metafile_ptrword_HDC_, _3)(this, _1, _2, _3, _4)>
endif
    endm
Metafile_ptrword_HDC_imm macro this, _1, _2, _3:=<EmfTypeEmfPlusDual>, _4:=<NULL>
    exitm<GdipRecordMetafileFileName(_1, _2, _3, NULL, MetafileFrameUnitGdi, _4, addr this.nativeImage)>
    endm
Metafile_ptrword_HDC_ptrRectF macro this, _1, _2, _3, _4, _5, _6
    exitm<GdipRecordMetafileFileName(_1, _2, _5, _3, _4, _6, addr this.nativeImage)>
    endm
Metafile_ptrword_HDC_ptrRect macro this, _1, _2, _3, _4:=<MetafileFrameUnitGdi>, _5:=<EmfTypeEmfPlusDual>, _6:=<NULL>
    exitm<GdipRecordMetafileFileName(_1, _2, _5, _3, _4, _6, addr this.nativeImage)>
    endm
Metafile_ptrIStream macro this, _1, _2, _3, _4:vararg
ifb <_2>
    exitm<GdipCreateMetafileFromStream(_1, addr this.nativeImage)>
else
%   exitm<typeid(Metafile_IStream_HDC_, _3)(this, _1, _2, _3, _4)>
endif
    endm
Metafile_IStream_HDC_imm macro this, _1, _2, _3:=<EmfTypeEmfPlusDual>, _4:=<NULL>
    exitm<GdipRecordMetafileStream(_1, _2, _3, NULL, MetafileFrameUnitGdi, _4, addr this.nativeImage)>
    endm
Metafile_IStream_HDC_ptrRectF macro this, _1, _2, _3, _4:=<MetafileFrameUnitGdi>, _5:=<EmfTypeEmfPlusDual>, _6:=<NULL>
    exitm<GdipRecordMetafileStream(_1, _2, _5, _3, _4, _6, addr this.nativeImage)>
    endm
Metafile_IStream_HDC_ptrRect macro this, _1, _2, _3, _4:=<MetafileFrameUnitGdi>, _5:=<EmfTypeEmfPlusDual>, _6:=<NULL>
    exitm<GdipRecordMetafileStreamI(_1, _2, _5, _3, _4, _6, addr this.nativeImage)>
    endm
;
; Record a metafile to memory.
;
Metafile_ptrHDC__ macro this, _1, _2, _3:vararg
%   exitm<typeid(Metafile_HDC_, _2)(this, _1, _2, _3)>
    endm
Metafile_HDC_imm macro this, _1, _2:=<EmfTypeEmfPlusDual>, _3:=<NULL>
    exitm<GdipRecordMetafile(_1, _2, NULL, MetafileFrameUnitGdi,  _3, addr this.nativeImage)>
    endm
Metafile_HDC_ptrRectF macro this, _1, _2, _3:=<MetafileFrameUnitGdi>, _4:=<EmfTypeEmfPlusDual>, _5:=<NULL>
    exitm<GdipRecordMetafile(_1, _4, _2, _3, _5, addr this.nativeImage)>
    endm
Metafile_HDC_ptrRect macro this, _1, _2, _3:=<MetafileFrameUnitGdi>, _4:=<EmfTypeEmfPlusDual>, _5:=<NULL>
    exitm<GdipRecordMetafileI(_1, _4, _2, _3, _5, addr this.nativeImage)>
    endm


Metafile_GetMetafileHeader_ptrHMETAFILE__ macro this, _1, _2, _3:vararg
%   exitm<typeid(Metafile_GetMetafileHeader_HMETAFILE_, _2)(this, _1, _2, _3)>
    endm
Metafile_GetMetafileHeader_ptrHENHMETAFILE__ macro this, _1, _2, _3:vararg
%   exitm<typeid(Metafile_GetMetafileHeader_HENHMETAFILE_, _2)(this, _1, _2, _3)>
    endm
Metafile_GetMetafileHeader_HMETAFILE_ptrWmfPlaceableFileHeader macro this, _1, _2, _3;, _4:vararg
    exitm<GdipGetMetafileHeaderFromWmf(_1, _2, _3)>
    endm
Metafile_GetMetafileHeader_HENHMETAFILE_ptrMetafileHeader macro this, _1, _2, _3:vararg
    exitm<GdipGetMetafileHeaderFromEmf(_1, _2)>
    endm
Metafile_GetMetafileHeader_ptrword macro this, _1, _2, _3:vararg
    exitm<GdipGetMetafileHeaderFromFile(_1, _2)>
    endm
Metafile_GetMetafileHeader_ptrIStream macro this, _1, _2, _3:vararg
    exitm<GdipGetMetafileHeaderFromStream(_1, _2)>
    endm
Metafile_GetMetafileHeader_ptrMetafileHeader macro this, _1, _2:vararg
    exitm<GdipGetMetafileHeaderFromMetafile(this.nativeImage, _1)>
    endm

; ConvertToEmfPlus(Graphics* refGraphics, INT* conversionFailureFlag = NULL, EmfType emfType = EmfTypeEmfPlusOnly, WCHAR* description = NULL );
; ConvertToEmfPlus(Graphics* refGraphics, WCHAR* filename, INT* conversionFailureFlag = NULL, EmfType emfType = EmfTypeEmfPlusOnly, WCHAR* description = NULL);
; ConvertToEmfPlus(Graphics* refGraphics, IStream* stream, INT* conversionFailureFlag = NULL, EmfType emfType = EmfTypeEmfPlusOnly, WCHAR* description = NULL);

Metafile_ConvertToEmfPlus_ptrsdword macro this, g, conversionFailureFlag:=<NULL>, emfType:=<EmfTypeEmfPlusOnly>, description:=<NULL>
    exitm<GdipConvertToEmfPlus(g, this.nativeImage, conversionFailureFlag, emfType, description, addr this.nativeImage)>
    endm
Metafile_ConvertToEmfPlus_ptrword macro this, g, filename, conversionFailureFlag:=<NULL>, emfType:=<EmfTypeEmfPlusOnly>, description:=<NULL>
    exitm<GdipConvertToEmfPlusToFile(g, this.nativeImage, filename, conversionFailureFlag, emfType, description, addr this.nativeImage)>
    endm
Metafile_ConvertToEmfPlus_ptrIStream macro this, g, stream, conversionFailureFlag:=<NULL>, emfType:=<EmfTypeEmfPlusOnly>, description:=<NULL>
    exitm<GdipConvertToEmfPlusToStream(g, this.nativeImage, stream, conversionFailureFlag, emfType, description, addr this.nativeImage)>
    endm

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

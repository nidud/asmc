ifndef _GDIPLUSHEADERS_H
_GDIPLUSHEADERS_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template Region

    nativeRegion    ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .inline Region :abs, :vararg {
        ifb <_1>
            GdipCreateRegion(addr this.nativeRegion)
        else
            this.typeid(Region, _1)(_1, _2)
        endif
        mov this.lastResult,eax
        }
    .inline RegionPRect :ptr Rect, :vararg {
        mov rcx,rdx
        GdipCreateRegionRectI(rcx, addr this.nativeRegion)
        }
    .inline RegionPRectF :ptr RectF, :vararg {
        mov rcx,rdx
        GdipCreateRegionRect(rcx, addr this.nativeRegion)
        }
    .inline RegionPGraphicsPath :ptr GraphicsPath, :vararg {
        mov rcx,[rdx].GraphicsPath.nativePath
        GdipCreateRegionPath(rcx, addr this.nativeRegion)
        }
    .inline RegionPBYTE :ptr BYTE, :int_t, :vararg {
        mov rcx,rdx
        mov edx,r8d
        GdipCreateRegionRgnData(rcx, edx, addr this.nativeRegion)
        }
    .inline RegionPVOID :HRGN, :vararg {
        mov rcx,rdx
        GdipCreateRegionHrgn(rcx, addr this.nativeRegion)
        }
    .inline RegionPRegion :ptr Region, :vararg {
        this.SetNativeRegion([rdx].Region.nativeRegion)
        }

    .inline FromHRGN :HRGN, :vararg {
        mov rcx,rdx
        GdipCreateRegionHrgn(rcx, addr this.nativeRegion)
        this.SetStatus()
        }

    .inline Release :vararg {
        GdipDeleteRegion(this.nativeRegion)
        }

    .inline SetStatus :vararg {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,this.lastResult
        mov this.lastResult,eax
        }

    .inline SetNativeRegion :ptr Region, :vararg {
        mov this.nativeRegion,rdx
        }

    .inline Clone :vararg {

        .new clone:Region

        GdipCloneRegion(this.nativeRegion, addr clone.nativeRegion)
        clone.SetStatus()
        lea rax,clone
        }

    .inline MakeInfinite :vararg {
        GdipSetInfinite(this.nativeRegion)
        this.SetStatus()
        }

    .inline MakeEmpty :vararg {
        GdipSetEmpty(this.nativeRegion)
        this.SetStatus()
        }

    .inline GetDataSize :vararg {
        mov this.scratch,eax
        GdipGetRegionDataSize(this.nativeRegion, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    ;; buffer     - where to put the data
    ;; bufferSize - how big the buffer is (should be at least as big as GetDataSize())
    ;; sizeFilled - if not NULL, this is an OUT param that says how many bytes
    ;;              of data were written to the buffer.

    .inline GetData :abs, :abs, :abs, :vararg {
        GdipGetRegionData(this.nativeRegion, _1, _2, _3)
        this.SetStatus()
        }

region_combine macro token, name, mode
    .inline token :abs, :vararg {
        this.typeid(name, _1)(_1, _2)
        this.SetStatus()
        }
    .inline &name&PRect :abs, :vararg {
        GdipCombineRegionRectI(this.nativeRegion, _1, mode)
        }
    .inline &name&PRectF :abs, :vararg {
        GdipCombineRegionRect(this.nativeRegion, _1, mode)
        }
    .inline &name&PGraphicsPath :ptr GraphicsPath, :vararg {
        GdipCombineRegionPath(this.nativeRegion, [rdx].GraphicsPath.nativePath, mode)
        }
    .inline &name&PRegion :ptr Region, :vararg {
        GdipCombineRegionRegion(this.nativeRegion, [rdx].Region.nativeRegion, mode)
        }
    exitm<>
    endm
    region_combine(Intersect,   Intersect,  CombineModeIntersect)
    region_combine(_Union,      Union,      CombineModeUnion)
    region_combine(_Xor,        Xor,        CombineModeXor)
    region_combine(Exclude,     Exclude,    CombineModeExclude)
    region_combine(Complement,  Complement, CombineModeComplement)

    .inline Translate :abs, :vararg {
        this.typeid(Translate, _1)(_1, _2)
        this.SetStatus()
        }
    .inline TranslateIMMFLT :abs, :abs, :vararg {
        GdipTranslateRegion(this.nativeRegion, _1, _2)
        }
    .inline TranslateIMM32 :abs, :abs, :vararg {
        GdipTranslateRegionI(this.nativeRegion, _1, _2)
        }

    .inline Transform :ptr Matrix, :vararg {
        GdipTransformRegion(this.nativeRegion, [rdx].Matrix.nativeMatrix)
        this.SetStatus()
        }

    .inline GetBounds :abs, :vararg {
        this.typeid(GetBounds, _1)(_1, _2)
        this.SetStatus()
        }
    .inline GetBoundsPRect :ptr Rect, :ptr Graphics, :vararg {
        xchg rdx,r8
        GdipGetRegionBoundsI(this.nativeRegion, [rdx].Graphics.nativeGraphics, r8)
        }
    .inline GetBoundsPRectF :ptr RectF, :ptr Graphics, :vararg {
        xchg rdx,r8
        GdipGetRegionBounds(this.nativeRegion, [rdx].Graphics.nativeGraphics, r8)
        }

    .inline GetHRGN :ptr Graphics, :vararg {
        GdipGetRegionHRgn(this.nativeRegion, [rdx].Graphics.nativeGraphics, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline IsEmpty :ptr Graphics, :vararg {
        GdipIsEmptyRegion(this.nativeRegion, [rdx].Graphics.nativeGraphics, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline IsInfinite :ptr Graphics, :vararg {
        GdipIsInfiniteRegion(this.nativeRegion, [rdx].Graphics.nativeGraphics, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline IsVisible :abs, :vararg {
        this.typeid(IsVisible, _1)(_1, _2)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline IsVisiblePRect :ptr Rect, :ptr Graphics, :vararg {
        .if r8
            mov r8,[r8].Graphics.nativeGraphics
        .endif
        GdipIsVisibleRegionRectI(this.nativeRegion, [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, r8, addr this.scratch)
        }
    .inline IsVisiblePRectF :ptr RectF, :ptr Graphics, :vararg {
        .if r8
            mov r8,[r8].Graphics.nativeGraphics
        .endif
        GdipIsVisibleRegionRect(this.nativeRegion, [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, r8, addr this.scratch)
        }
    .inline IsVisiblePPoint :ptr Point, :ptr Graphics, :vararg {
        .if r8
            mov r8,[r8].Graphics.nativeGraphics
        .endif
        GdipIsVisibleRegionPointI(this.nativeRegion, [rdx].Point.X, [rdx].Point.Y, r8, addr this.scratch)
        }
    .inline IsVisiblePPointF :ptr PointF, :ptr Graphics, :vararg {
        .if r8
            mov r8,[r8].Graphics.nativeGraphics
        .endif
        GdipIsVisibleRegionPoint(this.nativeRegion, [rdx].PointF.X, [rdx].PointF.Y, r8, addr this.scratch)
        }

    ; IsVisible(INT, INT, ...)
    .inline IsVisibleIMM32 :abs, :abs, :abs, :vararg {
        ifb <_3>
            ; IsVisible(INT, INT)
            GdipIsVisibleRegionPointI(this.nativeRegion, _1, _2, NULL, addr this.scratch)
        else
            this.typeid(IsVisibleIMM32, _3)(_1, _2, _3, _4)
        endif
        }
    ; IsVisible(INT, INT, Graphics*)
    .inline IsVisibleIMM32PGraphics :abs, :abs, :ptr Graphics, :vararg {
        .if r9
            mov r9,[r9].Graphics.nativeGraphics
        .endif
        GdipIsVisibleRegionPointI(this.nativeRegion, _1, _2, r9, addr this.scratch)
        }
    ; IsVisible(INT, INT, INT, INT, Graphics*)
    .inline IsVisibleIMM32IMM32 :abs, :abs, :abs, :abs, :ptr Graphics, :vararg {
        mov r10,[rsp+8*5]
        .if r10
            mov r10,[r10].Graphics.nativeGraphics
        .endif
        GdipIsVisibleRegionRectI(this.nativeRegion, _1, _2, _3, _4, r10, addr this.scratch)
        }
    .inline IsVisibleREG32 :vararg { this.IsVisibleIMM32(_1) }
    .inline IsVisibleSDWORD :vararg { this.IsVisibleIMM32(_1) }

    ; IsVisible(REAL, REAL, ...)
    .inline IsVisibleIMMFLT :abs, :abs, :abs, :vararg {
        ifb <_3>
            ; IsVisible(REAL, REAL)
            GdipIsVisibleRegionPoint(this.nativeRegion, _1, _2, NULL, addr this.scratch)
        else
            this.typeid(IsVisibleIMMFLT, _3)(_1, _2, _3, _4)
        endif
        }
    ; IsVisible(REAL, REAL, Graphics*)
    .inline IsVisibleIMMFLTPGraphics :abs, :abs, :ptr Graphics, :vararg {
        .if r9
            mov r9,[r9].Graphics.nativeGraphics
        .endif
        GdipIsVisibleRegionPoint(this.nativeRegion, _1, _2, r9, addr this.scratch)
        }
    ; IsVisible(REAL, REAL, REAL, REAL, Graphics*)
    .inline IsVisibleIMMFLTIMMFLT :abs, :abs, :abs, :abs, :ptr Graphics, :vararg {
        mov r10,[rsp+8*5]
        .if r10
            mov r10,[r10].Graphics.nativeGraphics
        .endif
        GdipIsVisibleRegionRect(this.nativeRegion, _1, _2, _3, _4, r10, addr this.scratch)
        }
    .inline IsVisibleREG128 :vararg { this.IsVisibleIMMFLT(_1) }
    .inline IsVisibleREGeal4 :vararg { this.IsVisibleIMMFLT(_1) }

    .inline Equals :ptr Region, :ptr Graphics, :vararg {
        GdipIsEqualRegion(this.nativeRegion, [rdx].Region.nativeRegion, [r8].Graphics.nativeGraphics, addr this.scratch)
        this.SetStatus()
        }

    .inline GetRegionScansCount :ptr Matrix, :vararg {
        GdipGetRegionScansCount(this.nativeRegion,  addr this.scratch, [rdx].Matrix.nativeMatrix)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetRegionScans :abs, :abs, :vararg {
        this.typeid(GetRegionScans, _2)(_1, _2, _3)
        this.SetStatus()
        }
    .inline GetRegionScansPRectF :ptr Matrix, :ptr Rect, :ptr int_t, :vararg {
        xchg r9,rdx
        xchg r8,rdx
        GdipGetRegionScans(this.nativeRegion, rdx, r8, [r9].Matrix.nativeMatrix)
        }
    .inline GetRegionScansPRect :ptr Matrix, :ptr Rect, :ptr int_t, :vararg {
        xchg r9,rdx
        xchg r8,rdx
        GdipGetRegionScansI(this.nativeRegion, rdx, r8, [r9].Matrix.nativeMatrix)
        }
    .inline GetLastStatus :vararg {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .ends

;;--------------------------------------------------------------------------
;; FontFamily
;;
;; FontFamily() : nativeFamily(NULL), lastResult(Ok)
;; FontFamily(WCHAR*, FontCollection = NULL)
;; FontFamily(FontFamily *, Status)
;;
;;--------------------------------------------------------------------------

.template FontFamily

    nativeFamily    ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .inline FontFamily :abs, :vararg {
        ifb <_1>
            mov eax,Ok
            mov this.nativeFamily,NULL
        else
            this.typeid(FontFamily, _1)(_1, _2)
        endif
        mov this.lastResult,eax
        }
    .inline FontFamilyPWORD :ptr word, :abs, :vararg {
        mov rcx,rdx
        ifb <_2>
            xor edx,edx
        else
            mov rdx,_2
        endif
        .if rdx
            mov rdx,[rdx].FontCollection.nativeFontCollection
        .endif
        GdipCreateFontFamilyFromName(rcx, rdx, addr this.nativeFamily)
        }
    .inline FontFamilyPFontFamily :ptr FontFamily, :vararg {
        mov this.nativeFamily,_1
        mov this.lastResult,Ok
        }

    .inline SetStatus :vararg {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,this.lastResult
        mov this.lastResult,eax
        }

    .inline Release {
        GdipDeleteFontFamily([this].FontFamily.nativeFamily)
        }

    .inline GenericSansSerif :vararg {
        GdipGetGenericFontFamilySansSerif(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    .inline GenericSerif :vararg {
        GdipGetGenericFontFamilySerif(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    .inline GenericMonospace :vararg {
        GdipGetGenericFontFamilyMonospace(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    .inline GetFamilyName :abs, :abs, :vararg {
        GdipGetFamilyName(this.nativeFamily, _1, _2)
        this.SetStatus()
        }

    .inline Clone :vararg {

        .new clone:FontFamily

        GdipCloneRegion(this.nativeFamily, addr clone.nativeFamily)
        clone.SetStatus()
        lea rax,clone
        }

    .inline IsAvailable :vararg {
        mov     ecx,1
        xor     eax,eax
        cmp     rax,this.nativeFamily
        cmovnz  eax,ecx
        }

    .inline IsStyleAvailable :abs, :vararg {
        GdipIsStyleAvailable(this.nativeFamily, _1, addr this.scratch)
        this.SetStatus()
        .if eax
            mov this.scratch,FALSE
        .endif
        mov eax,this.scratch
        }

    .inline GetEmHeight :abs, :vararg {
        GdipGetEmHeight(this.nativeFamily, _1, addr this.scratch)
        this.SetStatus()
        }
    .inline GetCellAscent :abs, :vararg {
        GdipGetCellAscent(this.nativeFamily, _1, addr this.scratch)
        this.SetStatus()
        }
    .inline GetCellDescent :abs, :vararg {
        GdipGetCellDescent(this.nativeFamily, _1, addr this.scratch)
        this.SetStatus()
        }
    .inline GetLineSpacing :abs, :vararg {
        GdipGetLineSpacing(this.nativeFamily, _1, addr this.scratch)
        this.SetStatus()
        }

    .inline GetLastStatus :vararg {
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

.template Font

    nativeFont  ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .inline Font :abs, :abs, :vararg {
        ifb <_2>
            GdipCreateFontFromDC(_1, addr this.nativeFont)
        else
            this.typeid(Font, _1)(_1, _2, _3)
        endif
        mov this.lastResult,eax
        }

    .inline FontHDC :abs, :abs, :vararg {
        this.typeid(Font, _2)(_1, _2)
        }
    .inline FontPVOID :HDC, :HFONT, :vararg {
        .if r8
            .new lf:LOGFONTA
            .new hdc:HDC
             mov hdc,rdx
             mov rcx,r8
            .if GetObjectA(rcx, LOGFONTA, addr lf)
                GdipCreateFontFromLogfontA(hdc, addr lf, addr this.nativeFont)
            .else
                GdipCreateFontFromDC(hdc, addr this.nativeFont)
            .endif
        .else
            mov rcx,rdx
            GdipCreateFontFromDC(rcx, addr this.nativeFont)
        .endif
        }
    .inline FontPLOGFONTW :HDC, :ptr LOGFONTW, :vararg {
        mov rcx,rdx
        .if r8
            mov rdx,r8
            GdipCreateFontFromLogfontW(rcx, rdx, addr this.nativeFont)
        .else
            GdipCreateFontFromDC(rcx, addr this.nativeFont)
        .endif
        }
    .inline FontPLOGFONTA :HDC, :ptr LOGFONTA, :vararg {
        mov rcx,rdx
        .if r8
            mov rdx,r8
            GdipCreateFontFromLogfontA(rcx, rdx, addr this.nativeFont)
        .else
            GdipCreateFontFromDC(rcx, addr this.nativeFont)
        .endif
        }
    .inline FontPFontFamily :ptr FontFamily, :abs, :abs=<FontStyleRegular>, :abs=<UnitPoint>, :vararg {
        mov rcx,rdx
        .if ecx
            mov rcx,[rcx].FontFamily.nativeFamily
        .endif
        GdipCreateFont(rcx, _2, _3, _4, addr this.nativeFont)
        }

    .inline FontPWORD :abs, :abs, :abs=<FontStyleRegular>, :abs=<UnitPoint>, :abs=<NULL>, :vararg {

        .new emSize:REAL

        mov emSize,_2

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
        }


    .inline FontPFont :ptr Font, :Status {
        mov [this].Font.nativeFamily,_1
        mov [this].Font.lastResult,_2
        }

    .inline Release {
        GdipDeleteFont([this].Font.nativeFont)
        }

    .inline SetNativeFont :ptr Font {
        mov [this].Font.nativeFont,_1
        }

    .inline SetStatus :vararg {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,this.lastResult
        mov this.lastResult,eax
        }

    .inline GetLogFontA :ptr Graphics, :abs, :vararg {
        .if rdx
            mov rdx,[rdx].Graphics.nativeGraphics
        .endif
        GdipGetLogFontA(this.nativeFont, rdx, _2)
        this.SetStatus()
        }
    .inline GetLogFontW :ptr Graphics, :abs, :vararg {
        .if rdx
            mov rdx,[rdx].Graphics.nativeGraphics
        .endif
        GdipGetLogFontW(this.nativeFont, rdx, _2)
        this.SetStatus()
        }

    .inline Clone :vararg {

        .new clone:Font

        GdipCloneFont(this.nativeFont, addr clone.nativeFont)
        clone.SetStatus()
        lea rax,clone
        }

    .inline IsAvailable {
        xor eax,eax
        .if rax != [this].Font.nativeFont
            inc eax
        .endif
        }
    .inline GetStyle :vararg {
        GdipGetFontStyle(this.nativeFont, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline GetSize :vararg {
        GdipGetFontSize(this.nativeFont, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline GetUnit :vararg {
        GdipGetFontUnit(this.nativeFont, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline GetLastStatus :vararg {
        this.SetStatus()
        }

    .inline GetHeight :abs, :vararg {
        this.typeid(GetHeight, _1)(_1, _2)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline GetHeightPGraphics :ptr Graphics, :vararg {
        .if rdx
            mov rdx,[rdx].Graphics.nativeGraphics
        .endif
        GdipGetFontHeight(this.nativeFont, rdx, addr this.scratch)
        }
    .inline GetHeightIMMFLT :abs, :vararg {
        GdipGetFontHeightGivenDPI(this.nativeFont, _1, addr this.scratch)
        }

    .inline GetFamily :ptr FontFamily, :vararg {
        mov eax,InvalidParameter
        .if rdx
            .new fontfamily:ptr FontFamily
            mov fontfamily,rdx
            .ifd GdipGetFamily(this.nativeFont, addr [rdx].FontFamily.nativeFamily)
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

.template FontCollection

    nativeFontCollection    ptr_t ?
    lastResult              Status ?

    .inline FontCollection {
        mov [this].FontCollection.nativeFontCollection,NULL
        }
    .inline Release {}

    .inline SetStatus :abs {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,[this].FontCollection.lastResult
        mov [this].FontCollection.lastResult,eax
        }

    .inline GetFamilyCount {

        .new numFound:int_t

        mov numFound,0
        GdipGetFontCollectionFamilyCount([this].FontCollection.nativeFontCollection, &numFound)
        mov eax,numFound
        }

    .inline GetFamilies :int_t, :ptr FontFamily, :ptr int_t {

        .repeat

            .ifs (edx <= 0 || r8 == NULL || r9 == NULL)

                mov eax,InvalidParameter
                mov [this].FontCollection.lastResult,eax
                .break
            .endif

            mov dword ptr [r9],0

            .new nativeFamilyList:ptr ptr FontFamily
            .new numSought:int_t
            .new gpfamilies:ptr FontFamily
            .new numFound:ptr int_t
            .new fontcollection:ptr FontCollection
            .new count:int_t

            mov fontcollection,rcx
            mov nativeFamilyList,rsi
            mov gpfamilies,rdi
            mov numFound,rbx

            mov rbx,r9
            mov rdi,r8
            mov numSought,edx
            mov rsi,GdipAlloc( &[rdx*8] )
            mov rcx,fontcollection

            .if rax == NULL

                mov eax,OutOfMemory
                mov [rcx].FontCollection.lastResult,eax
                mov rsi,nativeFamilyList
                mov rdi,gpfamilies
                mov rbx,numFound

                .break
            .endif

            .ifd !GdipGetFontCollectionFamilyList([rcx].FontCollection.nativeFontCollection, numSought, rsi, rbx)

                mov count,[rbx]
                .for ebx = 0: ebx < count: ebx++

                    imul ecx,ebx,8
                    imul edx,ebx,FontFamily

                    GdipCloneFontFamily([rsi+rcx], addr [rdi+rdx].FontFamily.nativeFamily)
                .endf
                xor eax,eax
            .endif
            mov fontcollection,rax
            GdipFree(rsi)
            mov rax,fontcollection
            mov rsi,nativeFamilyList
            mov rdi,gpfamilies
            mov rbx,numFound
        .until 1
        }

    .inline GetLastStatus {
        mov eax,[this].FontCollection.lastResult
        mov [this].FontCollection.lastResult,Ok
        }
    .ends


.template InstalledFontCollection : public FontCollection

    .inline InstalledFontCollection {
        FontCollection_FontCollection(this)
        }
    .ends


.template PrivateFontCollection : public FontCollection

    .inline PrivateFontCollection {
        FontCollection_FontCollection(this)
        }

    .inline AddFontFile :ptr WCHAR {

       .new fontcollection:ptr FontCollection

        mov fontcollection,this
        .ifd GdipPrivateAddFontFile([this].FontCollection.nativeFontCollection, rdx)
            mov rcx,fontcollection
            mov [rcx].FontCollection.lastResult,eax
        .endif
        }

    .inline AddMemoryFont :ptr, :int_t {

       .new fontcollection:ptr FontCollection

        mov fontcollection,this
        .ifd GdipPrivateAddMemoryFont([this].FontCollection.nativeFontCollection, rdx, r8d)
            mov rcx,fontcollection
            mov [rcx].FontCollection.lastResult,eax
        .endif
        }
    .ends


;;--------------------------------------------------------------------------
;; Abstract base class for Image and Metafile
;;--------------------------------------------------------------------------

.template ImageBase

    nativeImage     ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .inline Release :vararg {
        GdipDisposeImage(this.nativeImage)
        }

    .inline Save :abs, :vararg {
        this.typeid(Save, _1)(_1, _2)
        this.SetStatus()
        }
    .inline SavePWORD :abs, :abs, :abs=<0>, :vararg {
        GdipSaveImageToFile(this.nativeImage, _1, _2, _3)
        }
    .inline SavePIStream :abs, :abs, :abs=<0>, :vararg {
        GdipSaveImageToStream(this.nativeImage, _1, _2, _3)
        }

    .inline SaveAdd :abs, :vararg {
        this.typeid(SaveAdd, _1)(_1, _2)
        this.SetStatus()
        }
    .inline SaveAddPEncoderParameters :vararg {
        GdipSaveAdd(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline SaveAddPImage :ptr Image, :ptr EncoderParameters, :vararg {
        mov eax,InvalidParameter
        .if rdx
            mov rdx,[rdx].Image.nativeImage
            GdipSaveAddImage(this.nativeImage, rdx, r8)
        .endif
        this.SetStatus()
        }

    .inline GetType :vararg {
        mov this.scratch,ImageTypeUnknown
        GdipGetImageType(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetPhysicalDimension :ptr SizeF, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetImageDimension(this.nativeImage, &[rdx].SizeF.Width, &[rdx].SizeF.Height)
        .endif
        this.SetStatus()
        }

    .inline GetBounds :vararg {
        GdipGetImageBounds(this.nativeImage, _1)
        this.SetStatus()
        }

    .inline GetWidth :vararg {
        mov this.scratch,0
        GdipGetImageWidth(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetHeight :vararg {
        mov this.scratch,0
        GdipGetImageHeight(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetHorizontalResolution :vararg {
        mov this.scratch,0
        GdipGetImageHorizontalResolution(this.nativeImage, addr this.scratch)
        this.SetStatus()
        movss xmm0,this.scratch
        }

    .inline GetVerticalResolution :vararg {
        mov this.scratch,0
        GdipGetImageVerticalResolution(this.nativeImage, addr this.scratch)
        this.SetStatus()
        movss xmm0,this.scratch
        }

    .inline GetFlags :vararg {
        mov this.scratch,0
        GdipGetImageFlags(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetRawFormat :vararg {
        GdipGetImageRawFormat(this.nativeImage, _1)
        this.SetStatus()
        }

    .inline GetPixelFormat :vararg {
        GdipGetImagePixelFormat(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetPaletteSize :vararg {
        mov this.scratch,0
        GdipGetImagePaletteSize(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetPalette :vararg {
        GdipGetImagePalette(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline SetPalette :vararg {
        GdipSetImagePalette(this.nativeImage, _1)
        this.SetStatus()
        }

    .inline GetThumbnailImage :abs, :abs, :abs=<0>, :abs=<0>, :vararg {

        .new thumbimage:Image

        GdipGetImageThumbnail(this.nativeImage, _1, _2, addr thumbimage.nativeImage, _3, _4)
        mov thumbimage.lastResult,eax
        lea rax,thumbimage
        }

    .inline GetFrameDimensionsCount :vararg {
        mov this.scratch,0
        GdipImageGetFrameDimensionsCount(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline GetFrameDimensionsList :vararg {
        GdipImageGetFrameDimensionsList(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline GetFrameCount :vararg {
        mov this.scratch,0
        GdipImageGetFrameCount(this.nativeImage, _1, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline SelectActiveFrame :vararg {
        GdipImageSelectActiveFrame(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline RotateFlip :vararg {
        GdipImageRotateFlip(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline GetPropertyCount :vararg {
        mov this.scratch,0
        GdipGetPropertyCount(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline GetPropertyIdList :vararg {
        GdipGetPropertyIdList(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline GetPropertyItemSize :vararg {
        mov this.scratch,0
        GdipGetPropertyItemSize(this.nativeImage, _1, addr this.scratch)
        mov eax,this.scratch
        }
    .inline GetPropertyItem :vararg {
        GdipGetPropertyItem(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline GetPropertySize :vararg {
        GdipGetPropertySize(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline GetAllPropertyItems :abs, :abs, :ptr PropertyItem, :vararg {
        mov eax,InvalidParameter
        .if r9
            GdipGetAllPropertyItems(this.nativeImage, _1, _2, r9)
        .endif
        this.SetStatus()
        }
    .inline RemovePropertyItem :vararg {
        GdipRemovePropertyItem(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline SetPropertyItem :vararg {
        GdipSetPropertyItem(this.nativeImage, _1)
        this.SetStatus()
        }

    .inline GetEncoderParameterListSize :vararg {
        mov this.scratch,0
        GdipGetEncoderParameterListSize(this.nativeImage, _1, addr this.scratch)
        mov eax,this.scratch
        }
    .inline GetEncoderParameterList :vararg {
        GdipGetEncoderParameterList(this.nativeImage, _1)
        this.SetStatus()
        }
if (GDIPVER GE 0x0110)
    .inline FindFirstItem :vararg {
        GdipFindFirstImageItem(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline FindNextItem :vararg {
        GdipFindNextImageItem(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline GetItemData :vararg {
        GdipGetImageItemData(this.nativeImage, _1)
        this.SetStatus()
        }
    .inline SetAbort :vararg {
        GdipImageSetAbort(this.nativeImage, _1)
        this.SetStatus()
        }
endif

    .inline SetNativeImage :ptr Image, :vararg {
        mov this.nativeImage,rdx
        }

    .inline SetStatus :vararg {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,this.lastResult
        mov this.lastResult,eax
        }
    .inline GetLastStatus :vararg {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    .ends


; Image(WCHAR*, BOOL = FALSE)
; Image(IStream*, BOOL = FALSE)

.template Image : public ImageBase

    .inline Image :abs, :vararg {
        mov this.nativeImage,NULL
        this.typeid(Image, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .inline ImagePWORD :ptr WCHAR, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        if _2
            GdipLoadImageFromFileICM(rcx, addr this.nativeImage)
        else
            GdipLoadImageFromFile(rcx, addr this.nativeImage)
        endif
        }
    .inline ImagePIStream :ptr IStream, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        if _2
            GdipLoadImageFromStreamICM(rcx, addr this.nativeImage)
        else
            GdipLoadImageFromStream(rcx, addr this.nativeImage)
        endif
        }
    .inline FromFile :vararg {
        this.ImagePWORD(_1)
        mov this.lastResult,eax
        }
    .inline FromStream :vararg {
        this.ImagePIStream(_1)
        mov this.lastResult,eax
        }

    .inline Clone :vararg {

       .new clone:Image

        GdipCloneImage(this.nativeImage, addr clone.nativeImage)
        mov clone.lastResult,eax
        this.SetStatus()
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

.template Bitmap : public ImageBase

    .inline Bitmap :abs, :vararg {
        ifb <_1>
            mov this.nativeImage,NULL
            mov this.lastResult,NotImplemented
        else
            this.typeid(Bitmap, _1)(_1, _2)
            mov this.lastResult,eax
        endif
        }
    .inline BitmapPWORD :ptr WCHAR, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        if _2
            GdipCreateBitmapFromFileICM(rcx, addr this.nativeImage)
        else
            GdipCreateBitmapFromFile(rcx, addr this.nativeImage)
        endif
        }
    .inline BitmapPIStream :ptr IStream, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        if _2
            GdipCreateBitmapFromStreamICM(rcx, addr this.nativeImage)
        else
            GdipCreateBitmapFromStream(rcx, addr this.nativeImage)
        endif
        }

    .inline BitmapIMM32 :abs, :abs, :abs, :vararg {
        this.typeid(BitmapIMM32, _3)(_1, _2, _3, _4)
        }
    .inline BitmapSDWORD :abs, :abs, :abs, :vararg {
        this.typeid(BitmapIMM32, _3)(_1, _2, _3, _4)
        }
    .inline BitmapDWORD :abs, :abs, :abs, :vararg {
        this.typeid(BitmapIMM32, _3)(_1, _2, _3, _4)
        }
    .inline BitmapREG32 :abs, :abs, :abs, :vararg {
        this.typeid(BitmapREG32, _3)(_1, _2, _3, _4)
        }
    .inline BitmapIMM32IMM32 :abs, :abs, :abs, :abs, :vararg {
        ifb <_4>
            GdipCreateBitmapFromScan0(_1, _2, 0, _3, NULL, addr this.nativeImage)
        else
            GdipCreateBitmapFromScan0(_1, _2, _3, _4, _5, addr this.nativeImage)
        endif
        }
    .inline BitmapIMM32DWORD :abs, :abs, :abs, :abs, :vararg {
        this.BitmapIMM32IMM32(_1, _2, _3, _4, _5)
        }

    .inline BitmapREG32REG32 :abs, :abs, :abs, :abs, :vararg {
        mov ecx,_1
        mov edx,_2
        mov r8d,_3
        ifb <_4>
            GdipCreateBitmapFromScan0(ecx, edx, 0, r8d, NULL, addr this.nativeImage)
        else
            GdipCreateBitmapFromScan0(ecx, edx, r8d, _4, _5, addr this.nativeImage)
        endif
        }
    .inline BitmapIMM32PGraphics :int_t, :int_t, :ptr Graphics, :vararg {
        mov ecx,edx
        mov edx,r8d
        mov r8,r9
        GdipCreateBitmapFromGraphics(ecx, edx, [r8].Graphics.nativeGraphics, addr this.nativeImage)
        }
    .inline BitmapPIDirectDrawSurface7 :ptr IDirectDrawSurface7, :vararg {
        mov rcx,rdx
        GdipCreateBitmapFromDirectDrawSurface(rcx, addr this.nativeImage)
        }
    .inline BitmapPBITMAPINFO :ptr BITMAPINFO, :ptr, :vararg {
        mov rcx,rdx
        mov rdx,r8
        GdipCreateBitmapFromGdiDib(rcx, rdx, addr this.nativeImage)
        }

    .inline BitmapPVOID :abs, :abs, :vararg {
        mov rcx,_1
        ifb <_2>
            GdipCreateBitmapFromHICON(rcx, addr this.nativeImage)
        else
            this.typeid(BitmapPVOID, _2)(_1, _2, _3)
        endif
        }
    .inline BitmapPVOIDPVOID :HBITMAP, :HPALETTE, :vararg {
        mov rdx,r8
        GdipCreateBitmapFromHBITMAP(rcx, rdx, addr this.nativeImage)
        }
    .inline BitmapPVOIDPWORD :HINSTANCE, :ptr WCHAR, :vararg {
        mov rdx,r8
        GdipCreateBitmapFromResource(rcx, rdx, addr this.nativeImage)
        }

    undef Bitmap_FromFile
    .inline FromFile :vararg {
        this.BitmapPWORD(_1)
        mov this.lastResult,eax
        }

    .inline FromStream :vararg {
        this.BitmapPIStream(_1)
        mov this.lastResult,eax
        }

    .inline Clone :abs, :vararg {
        this.typeid(Clone, _1)(_1, _2)
        }

    .inline CloneIMM32 :abs, :abs, :abs, :abs, :abs, :vararg {

       .new clone:Bitmap

        mov ecx,_1
        GdipCloneBitmapAreaI(ecx, _2, _3, _4, _5, this.nativeImage, addr clone.nativeImage)
        mov clone.lastResult,eax
        lea rax,clone
        }

    .inline ClonePRect :ptr Rect, :abs, :vararg {
        this.CloneIMM32([rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }

    .inline CloneIMMFLT :abs, :abs, :abs, :abs, :abs, :vararg {

       .new clone:Bitmap

        GdipCloneBitmapArea(_1, _2, _3, _4, r10d, this.nativeImage, addr clone.nativeImage)
        mov clone.lastResult,eax
        lea rax,clone
        }
    .inline ClonePRectF :ptr RectF, :abs, :vararg {
        this.CloneIMMFLT([rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, _2)
        }

    .inline LockBits :vararg {
        GdipBitmapLockBits(this.nativeImage, _1)
        this.SetStatus()
        }

    .inline UnlockBits :vararg {
        GdipBitmapUnlockBits(this.nativeImage, _1)
        this.SetStatus()
        }

    .inline GetPixel :abs, :abs, :ptr Color, :vararg {
        GdipBitmapGetPixel(this.nativeImage, _1, _2, r9)
        this.SetStatus()
        }

    .inline SetPixel :vararg {
        GdipBitmapSetPixel(this.nativeImage, _1)
        this.SetStatus()
        }

if (GDIPVER GE 0x0110)
    .inline ConvertFormat :vararg {
        GdipBitmapConvertFormat(this.nativeImage, _1)
        this.SetStatus()
        }

    ;; The palette must be allocated and count must be set to the number of
    ;; entries in the palette. If there are not enough, the API will fail.

    .inline InitializePalette :ptr ColorPalette,  ;; Palette to initialize.
                                :abs,               ;; palette enumeration type.
                                :abs,               ;; how many optimal colors
                                :abs,               ;; add a transparent color to the palette.
                                :ptr Bitmap,        ;; optional bitmap for median cut.
                                :vararg {
        mov rcx,rdx
        mov rax,[rsp+8*5]
        .if rax
            mov rax,[rax].Image.nativeImage
        .endif
        GdipInitializePalette(rcx, _2, _3, _4, rax)
        this.SetStatus()
        }

    .inline ApplyEffect :abs, :vararg {
        this.typeid(ApplyEffect, _1)(_1, _2)
        }

    .inline ApplyEffectPEffect :ptr Effect, :ptr RECT, :vararg {

       .new effect:ptr Effect
       .new ROI:ptr RECT

        mov effect,rdx
        mov ROI,r8

        .if [rdx].Effect.auxData

            GdipFree([rdx].Effect.auxData)
            mov rdx,effect
            mov [rdx].Effect.auxData,NULL
            mov [rdx].Effect.auxDataSize,0
        .endif
        GdipBitmapApplyEffect(this.nativeImage, [rdx].Effect.nativeEffect, ROI,\
                [rdx].Effect.useAuxData, &[rdx].Effect.auxData,  &[rdx].Effect.auxDataSize)
        }

    .inline ApplyEffectPBitmap :ptr ptr Bitmap, :int_t, :ptr Effect, :ptr RECT, :ptr RECT, :ptr ptr Bitmap {

        .repeat

            .ifs _2 < 0

                mov eax,InvalidParameter
                .break
            .endif

            .new inputs:ptr ptr Bitmap
            .new numInputs:SINT
            .new effect:ptr Effect
            .new ROI:ptr RECT               ;; optional parameter.
            .new outputRect:ptr RECT        ;; optional parameter.
            .new output:ptr ptr Bitmap
            .new status:Status

            .new outputNative:ptr Bitmap
            .new nativeInputs:ptr ptr Bitmap

            mov inputs,_1
            mov numInputs,_2
            mov effect,_3
            mov ROI,_4
            mov outputRect,_5
            mov output,_6

            mov outputNative,NULL
            mov nativeInputs,GdipAlloc(&[_2*size_t])

            .if rax == NULL

                mov eax,OutOfMemory
                .break
            .endif

            .for (rdx = rax, r8 = inputs, ecx = 0: ecx < numInputs: ecx++)

                mov [rdx+rcx*8],[r8+rcx*8].Bitmap.nativeImage
            .endf

            mov r8,effect
            .if [r8].Effect.auxData

                GdipFree([r8].Effect.auxData)
                mov r8,effect
                mov [r8].Effect.auxData,NULL
                mov [r8].Effect.auxDataSize,0
            .endif

            GdipBitmapCreateApplyEffect( nativeInputs, numInputs, [r8].Effect.nativeEffect,\
                ROI, outputRect, &outputNative, [r8].Effect.useAuxData,\
                &[r8].Effect.auxData, &[r8].Effect.auxDataSize )

            mov status,eax
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
            mov eax,status
        .until 1
        }

    .inline GetHistogram :abs, :abs, :abs, :abs, :abs, :abs {
        GdipBitmapGetHistogram([this].Image.nativeImage, _1, _2, _3, _4, _5, _6)
        }

    .inline GetHistogramSize :abs, :abs {
        GdipBitmapGetHistogramSize(_1, _2)
        }
endif

    .inline SetResolution :vararg {
        GdipBitmapSetResolution(this.nativeImage, _1)
        this.SetStatus()
        }

    .inline GetHBITMAP :ARGB, :ptr HBITMAP, :vararg {
        xchg rdx,r8
        GdipCreateHBITMAPFromBitmap(this.nativeImage, rdx, r8d)
        this.SetStatus()
        }

    .inline GetHICON :ptr HICON, :vararg {
        GdipCreateHICONFromBitmap(this.nativeImage, rdx)
        this.SetStatus()
        }

    .ends
    GpBitmap typedef Bitmap


.template CustomLineCap

    GpCustomLineCap typedef CustomLineCap

    nativeCap   ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .inline CustomLineCap :ptr GraphicsPath, :ptr GraphicsPath, :abs, :abs, :vararg {
        mov rcx,rdx
        mov rdx,r8
        .if rcx
            mov rcx,[rcx]
        .endif
        .if rdx
            mov rdx,[rdx]
        .endif
        GdipCreateCustomLineCap([rcx].GraphicsPath.nativePath, [rdx].GraphicsPath.nativePath, _3, _4, addr this.nativeCap)
        mov this.lastResult,eax
        }

    .inline Release {
        GdipDeleteCustomLineCap([this].CustomLineCap.nativeCap)
        }

    .inline SetNativeCap :ptr CustomLineCap {
        mov [this].CustomLineCap.nativeCap,_1
        }

    .inline SetStatus :vararg {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,this.lastResult
        mov this.lastResult,eax
        }

    .inline Clone :vararg {

       .new clone:CustomLineCap

        GdipCloneCustomLineCap(this.nativeCap, addr clone.nativeCap)
        mov clone.lastResult,eax
        lea rax,clone
        }

    ;; This changes both the start and end cap.

    .inline SetStrokeCap :abs, :vararg {
        this.SetStrokeCaps(_1, _1)
        }

    .inline SetStrokeCaps  :abs, :abs, :vararg {
        GdipSetCustomLineCapStrokeCaps(this.nativeCap, _1, _2)
        this.SetStatus()
        }

    .inline GetStrokeCaps :abs, :abs, :vararg {
        GdipGetCustomLineCapStrokeCaps(this.nativeCap, _1, _2)
        this.SetStatus()
        }
    .inline SetStrokeJoin :abs, :vararg {
        GdipSetCustomLineCapStrokeJoin(this.nativeCap, _1)
        this.SetStatus()
        }
    .inline GetStrokeJoin :vararg {
        GdipGetCustomLineCapStrokeJoin(this.nativeCap, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline SetBaseCap :abs, :vararg {
        GdipSetCustomLineCapBaseCap(this.nativeCap, _1)
        this.SetStatus()
        }
    .inline GetBaseCap :vararg {
        GdipGetCustomLineCapBaseCap(this.nativeCap, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline SetBaseInset :abs, :vararg {
        GdipSetCustomLineCapBaseInset(this.nativeCap, _1)
        this.SetStatus()
        }
    .inline GetBaseInset :vararg {
        GdipGetCustomLineCapBaseInset(this.nativeCap, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline SetWidthScale :abs, :vararg {
        GdipSetCustomLineCapWidthScale(this.nativeCap, _1)
        this.SetStatus()
        }
    .inline GetWidthScale :vararg {
        GdipGetCustomLineCapWidthScale(this.nativeCap, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetLastStatus {
        mov eax,[this].CustomLineCap.lastResult
        mov [this].CustomLineCap.lastResult,Ok
        }
    .ends


.template CachedBitmap

    nativeCachedBitmap ptr_t ?
    lastResult      Status ?

    .inline CachedBitmap :ptr Bitmap, :ptr Graphics, :vararg {
        mov rcx,rdx
        mov rdx,r8
        GdipCreateCachedBitmap([rcx].Bitmap.nativeImage, [rdx].Graphics.nativeGraphics, addr this.nativeCachedBitmap)
        mov this.lastResult,eax
        }
    .inline Release {
        GdipDeleteCachedBitmap([this].CachedBitmap.nativeCachedBitmap)
        }

    .inline GetLastStatus {
        mov eax,[this].CachedBitmap.lastResult
        mov [this].CachedBitmap.lastResult,Ok
        }
    .ends


; Metafile(HMETAFILE, WmfPlaceableFileHeader*, BOOL = FALSE)
; Metafile(HENHMETAFILE, BOOL = FALSE)
; Metafile(WCHAR*)
; Metafile(WCHAR*, WmfPlaceableFileHeader*)
; Metafile(IStream*)
; Metafile(HDC, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(WCHAR*, HDC, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(WCHAR*, HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(WCHAR*, HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(IStream*, HDC, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(IStream*, HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)
; Metafile(IStream*, HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

.template Metafile : public ImageBase

    .inline Metafile :abs, :vararg {
        this.typeid(Metafile, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .inline MetafilePVOID :abs, :abs, :vararg {
        this.typeid(MetafilePVOID, _2)(_1, _2, _3)
        }

    ;; Playback a metafile from a HMETAFILE
    ;; If deleteWmf is TRUE, then when the metafile is deleted,
    ;; the hWmf will also be deleted.  Otherwise, it won't be.
    ;; Metafile(HMETAFILE, WmfPlaceableFileHeader*, BOOL = FALSE)

    .inline MetafilePVOIDPWmfPlaceableFileHeader :abs, :abs, :abs=<FALSE>, :vararg {
        GdipCreateMetafileFromWmf(_1, _3, _2, addr this.nativeImage)
        }

    ;; Playback a metafile from a HENHMETAFILE
    ;; If deleteEmf is TRUE, then when the metafile is deleted,
    ;; the hEmf will also be deleted.  Otherwise, it won't be.
    ;; Metafile(HENHMETAFILE, BOOL = FALSE)

    .inline MetafilePVOIDIMM32 :abs, :abs, :abs, :vararg {
        ifb <_3>
            ifb <_2>
                GdipCreateMetafileFromEmf(_1, FALSE, addr this.nativeImage)
            else
                GdipCreateMetafileFromEmf(_1, _2, addr this.nativeImage)
            endif
        else
            this.typeid(MetafilePVOIDIMM32, _3)(_1, _2, _3, _4)
        endif
        }

    ;; Metafile(WCHAR*)

    .inline MetafilePWORD :abs, :abs, :vararg {
        ifb <_2>
            GdipCreateMetafileFromFile(_1, addr this.nativeImage)
        else
            this.typeid(MetafilePWORD, _2)(_1, _2, _3)
        endif
        }

    ;; Playback a WMF metafile from a file.
    ;; Metafile(WCHAR*, WmfPlaceableFileHeader*)

    .inline MetafilePWORDPWmfPlaceableFileHeader :abs, :abs, :vararg {
        GdipCreateMetafileFromWmfFile(_1, _2, addr this.nativeImage)
        }

    ;; Metafile(IStream*)

    .inline MetafilePIStream :abs, :abs, :vararg {
        ifb <_2>
            GdipCreateMetafileFromStream(_1, addr this.nativeImage)
        else
            this.typeid(MetafilePIStream, _2)(_1, _2, _3)
        endif
        }

    ;; Record a metafile to memory.
    ;; Metafile(HDC, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePVOIDIMM32PWORD :abs, :abs=<EmfTypeEmfPlusDual>, :abs, :vararg {
        GdipRecordMetafile(_1, _2, NULL, MetafileFrameUnitGdi,  _3, addr this.nativeImage)
        }

    ;; Record a metafile to memory.
    ;; Metafile(HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePVOIDPRectF :abs, :abs, :abs=<MetafileFrameUnitGdi>, :abs=<EmfTypeEmfPlusDual>, :abs=<NULL>, :vararg {
        GdipRecordMetafile(_1, _4, _2, _3, _5, addr this.nativeImage)
        }

    ;; Record a metafile to memory.
    ;; Metafile(HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePVOIDPRect :abs, :abs, :abs=<MetafileFrameUnitGdi>, :abs=<EmfTypeEmfPlusDual>, :abs=<NULL>, :vararg {
        GdipRecordMetafileI(_1, _4, _2, _3, _5, addr this.nativeImage)
        }

    .inline MetafilePWORDPVOID :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipRecordMetafileFileName(_1, _2, EmfTypeEmfPlusDual, NULL, MetafileFrameUnitGdi, NULL, addr this.nativeImage)
        else
            this.typeid(MetafilePWORDPVOID, _3)(_1, _2, _3, _4)
        endif
        }

    ;; Metafile(WCHAR*, HDC, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePWORDPVOIDIMM32 :abs, :abs, :abs=<EmfTypeEmfPlusDual>, :abs=<NULL>, :vararg {
        GdipRecordMetafileFileName(_1, _2, _3, NULL, MetafileFrameUnitGdi, _4, addr this.nativeImage)
        }

    ;; Metafile(WCHAR*, HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePWORDPVOIDPRectF :abs, :abs, :abs, :abs, :abs, :abs, :vararg {
        GdipRecordMetafileFileName(_1, _2, _5, _3, _4, _6, addr this.nativeImage)
        }

    ;; Metafile(WCHAR*, HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePWORDPVOIDPRect :abs, :abs, :abs, :abs=<MetafileFrameUnitGdi>, :abs=<EmfTypeEmfPlusDual>, :abs=<NULL>, :vararg {
        GdipRecordMetafileFileName(_1, _2, _5, _3, _4, _6, addr this.nativeImage)
        }


    .inline MetafilePIStreamPVOID :abs, :abs, :abs, :vararg {
        this.typeid(MetafilePIStreamPVOID, _3)(_1, _2, _3, _4)
        }

    ;; Metafile(IStream*, HDC, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePIStreamPVOIDIMM32 :abs, :abs, :abs=<EmfTypeEmfPlusDual>, :abs=<NULL>, :vararg {
        GdipRecordMetafileStream(_1, _2, _3, NULL, MetafileFrameUnitGdi, _4, addr this.nativeImage)
        }

    ;; Metafile(IStream*, HDC, RectF*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePIStreamPVOIDPRectF :abs, :abs, :abs, :abs=<MetafileFrameUnitGdi>, :abs=<EmfTypeEmfPlusDual>, :abs=<NULL>, :vararg {
        GdipRecordMetafileStream(_1, _2, _5, _3, _4, _6, addr this.nativeImage)
        }

    ;; Metafile(IStream*, HDC, Rect*, MetafileFrameUnit = MetafileFrameUnitGdi, EmfType = EmfTypeEmfPlusDual, WCHAR* = NULL)

    .inline MetafilePIStreamPVOIDPRect :abs, :abs, :abs, :abs=<MetafileFrameUnitGdi>, :abs=<EmfTypeEmfPlusDual>, :abs=<NULL>, :vararg {
        GdipRecordMetafileStreamI(_1, _2, _5, _3, _4, _6, addr this.nativeImage)
        }

    .inline GetMetafileHeader :abs, :vararg {
        this.typeid(GetMetafileHeader, _1)(_1, _2)
        this.SetStatus()
        }
    .inline GetMetafileHeaderPVOID :abs, :abs, :vararg {
        this.typeid(GetMetafileHeaderPVOID, _2)(_1, _2, _3)
        }

    ;; GetMetafileHeader(HMETAFILE, WmfPlaceableFileHeader*, MetafileHeader*)

    .inline GetMetafileHeaderPVOIDPWmfPlaceableFileHeader :abs, :abs, :abs, :vararg {
        GdipGetMetafileHeaderFromWmf(_1, _2, _3)
        }

    ;; GetMetafileHeader(HENHMETAFILE, MetafileHeader*)

    .inline GetMetafileHeaderPVOIDPMetafileHeader :abs, :abs, :vararg {
        GdipGetMetafileHeaderFromEmf(_1, _2)
        }

    ;; GetMetafileHeader(WCHAR*, MetafileHeader*)

    .inline GetMetafileHeaderPWORD :abs, :abs, :vararg {
        GdipGetMetafileHeaderFromFile(_1, _2)
        }

    ;; GetMetafileHeader(IStream*, MetafileHeader*)

    .inline GetMetafileHeaderPIStream :abs, :abs, :vararg {
        GdipGetMetafileHeaderFromStream(_1, _2)
        }

    ;; GetMetafileHeader(MetafileHeader*)

    .inline GetMetafileHeaderPMetafileHeader :abs, :vararg {
        GdipGetMetafileHeaderFromMetafile(this.nativeImage, _1)
        }

    ;; Once this method is called, the Metafile object is in an invalid state
    ;; and can no longer be used.  It is the responsiblity of the caller to
    ;; invoke DeleteEnhMetaFile to delete this hEmf.

    .inline GetHENHMETAFILE :vararg {

        .new hEmf:HENHMETAFILE

        GdipGetHemfFromMetafile(this.nativeImage, &hEmf)
        this.SetStatus()
        mov rax,hEmf
        }

    ;; Used in conjuction with Graphics::EnumerateMetafile to play an EMF+
    ;; The data must be DWORD aligned if it's an EMF or EMF+.  It must be
    ;; WORD aligned if it's a WMF.
    ;; PlayRecord(EmfPlusRecordType, UINT, UINT, BYTE*)

    .inline PlayRecord :abs, :abs, :abs, :abs, :vararg {
        GdipPlayMetafileRecord(this.nativeImage, _1, _2, _3, _4)
        this.SetStatus()
        }

    ;; If you're using a printer HDC for the metafile, but you want the
    ;; metafile rasterized at screen resolution, then use this API to set
    ;; the rasterization dpi of the metafile to the screen resolution,
    ;; e.g. 96 dpi or 120 dpi.

    .inline SetDownLevelRasterizationLimit :abs, :vararg {
        GdipSetMetafileDownLevelRasterizationLimit(this.nativeImage,  _1)
        this.SetStatus()
        }

    .inline GetDownLevelRasterizationLimit :vararg {
        mov this.scratch,0
        GdipGetMetafileDownLevelRasterizationLimit(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline EmfToWmfBits :abs, :abs, :abs, :abs, :abs, :vararg {
        GdipEmfToWmfBits(_1, _2, _3, _4, _5)
        this.SetStatus()
        }

if (GDIPVER GE 0x0110)

    .inline ConvertToEmfPlus :ptr Graphics, :abs, :vararg {
        mov rcx,rdx
        this.typeid(ConvertToEmfPlus, _2)(rdx, _2, _3)
        this.SetStatus()
        }

    .inline ConvertToEmfPlusPSDWORD :abs, :vararg {
        GdipConvertToEmfPlus([rcx].Graphics.nativeGraphics, this.nativeImage, _2, addr this.nativeImage)
        }
    .inline ConvertToEmfPlusPWORD :abs, :vararg {
        GdipConvertToEmfPlusToFile([rcx].Graphics.nativeGraphics, this.nativeImage, _2, addr this.nativeImage)
        }
    .inline ConvertToEmfPlusPIStream :abs, :vararg {
        GdipConvertToEmfPlusToStream([rcx].Graphics.nativeGraphics, this.nativeImage, _2, addr this.nativeImage)
        }
endif

    .inline SetStatus :vararg {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,this.lastResult
        mov this.lastResult,eax
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

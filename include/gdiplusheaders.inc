ifndef _GDIPLUSHEADERS_H
_GDIPLUSHEADERS_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template Region

    nativeRegion    ptr_t ?
    lastResult      Status ?

    Region          proc
    Region1         proc :ptr Rect
    Region2         proc :ptr RectF
    Region3         proc :ptr GraphicsPath
    Region4         proc :ptr BYTE, :int_t
    Region5         proc :HRGN
    FromHRGN        proc :HRGN
    Release         proc

    SetStatus       proc :Status
    SetNativeRegion proc :ptr Region

    Clone           proc

    MakeInfinite    proc
    MakeEmpty       proc

    GetDataSize     proc

    ;; buffer     - where to put the data
    ;; bufferSize - how big the buffer is (should be at least as big as GetDataSize())
    ;; sizeFilled - if not NULL, this is an OUT param that says how many bytes
    ;;              of data were written to the buffer.

    GetData         proc :ptr, :UINT, :ptr UINT

    Intersect1      proc :ptr Rect
    Intersect2      proc :ptr RectF
    Intersect3      proc :ptr GraphicsPath
    Intersect4      proc :ptr Region
    Union1          proc :ptr Rect
    Union2          proc :ptr RectF
    Union3          proc :ptr GraphicsPath
    Union4          proc :ptr Region
    Xor1            proc :ptr Rect
    Xor2            proc :ptr RectF
    Xor3            proc :ptr GraphicsPath
    Xor4            proc :ptr Region
    Exclude1        proc :ptr Rect
    Exclude2        proc :ptr RectF
    Exclude3        proc :ptr GraphicsPath
    Exclude4        proc :ptr Region
    Complement1     proc :ptr Rect
    Complement2     proc :ptr RectF
    Complement3     proc :ptr GraphicsPath
    Complement4     proc :ptr Region
    Translate2      proc :REAL, :REAL
    Translate1      proc :int_t, :int_t
    Transform       proc :ptr Matrix

    GetBounds1      proc :ptr Rect, :ptr Graphics
    GetBounds2      proc :ptr RectF, :ptr Graphics

    GetHRGN         proc :ptr Graphics

    IsEmpty         proc :ptr Graphics
    IsInfinite      proc :ptr Graphics

    IsVisible1      proc :ptr Rect, :ptr Graphics
    IsVisible2      proc :ptr RectF, :ptr Graphics

    IsVisible3      proc :ptr Point, :ptr Graphics
    IsVisible4      proc :ptr PointF, :ptr Graphics

    IsVisible5      proc :int_t, :int_t, :ptr Graphics
    IsVisible6      proc :REAL, :REAL, :ptr Graphics
    IsVisible7      proc :int_t, :int_t, :int_t, :int_t, :ptr Graphics

    IsVisible8      proc :REAL, :REAL, :REAL, :REAL, :ptr Graphics

    Equals          proc :ptr Region, :ptr Graphics

    GetRegionScansCount proc :ptr Matrix
    GetRegionScansRect2 proc :ptr Matrix, :ptr RectF, :ptr int_t
    GetRegionScansRect1 proc :ptr Matrix, :ptr Rect, :ptr int_t
    GetLastStatus       proc

    .ends


;;--------------------------------------------------------------------------
;; FontFamily
;;
;; FontFamily() : nativeFamily(NULL), lastResult(Ok)
;; FontFamily(WCHAR*, FontCollection = NULL)
;; FontFamily(FontFamily *, Status)
;;
;;--------------------------------------------------------------------------

.template FontFamily ;: public GdiplusBase

    nativeFamily    ptr_t ?
    lastResult      Status ?

    .operator FontFamily :abs, :vararg {
        ifb <_1>
            mov this.nativeFamily,NULL
        else
            this.typeid(Font, _1)(_1, _2)
        endif
        mov this.lastResult,eax
        }
    .operator Font?pword :ptr word, :abs=<NULL>, :vararg {
        mov rcx,rdx
        mov rdx,_2
        .if rdx
            mov rdx,[rdx].FontCollection.nativeFontCollection
        .endif
        GdipCreateFontFamilyFromName(rcx, rdx, addr this.nativeFamily)
        }
    .operator Font?pFontFamily :ptr FontFamily, :vararg {
        mov this.nativeFamily,_1
        mov this.lastResult,Ok
        }

    SetStatus   proc :Status

    .operator Release :vararg {
        GdipDeleteFontFamily(this.nativeFamily)
        }

    .operator GenericSansSerif :vararg {
        GdipGetGenericFontFamilySansSerif(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    .operator GenericSerif :vararg {
        GdipGetGenericFontFamilySerif(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    .operator GenericMonospace :vararg {
        GdipGetGenericFontFamilyMonospace(addr this.nativeFamily)
        mov this.lastResult,eax
        }

    GetFamilyName       proc :LPWSTR, :LANGID

    Clone               proc

    .operator IsAvailable :vararg {
        mov ecx,1
        xor eax,eax
        cmp rax,this.nativeFamily
        cmovnz eax,ecx
        }

    IsStyleAvailable    proc :int_t

    GetEmHeight         proc :int_t
    GetCellAscent       proc :int_t
    GetCellDescent      proc :int_t
    GetLineSpacing      proc :int_t

    GetLastStatus       proc

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

.template Font ;: public GdiplusBase

    nativeFont  ptr_t ?
    lastResult  Status ?

    .operator Font :abs, :abs, :vararg {
        ifb <_2>
            GdipCreateFontFromDC(_1, addr this.nativeFont)
        else
            this.typeid(Font, _1)(_1, _2, _3)
        endif
        mov this.lastResult,eax
        }

    .operator Font?HDC :abs, :abs, :vararg {
        this.typeid(Font, _2)(_1, _2)
        }
    .operator Font?pvoid :HDC, :HFONT, :vararg {
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
    .operator Font?pLOGFONTW :HDC, :ptr LOGFONTW, :vararg {
        mov rcx,rdx
        .if r8
            mov rdx,r8
            GdipCreateFontFromLogfontW(rcx, rdx, addr this.nativeFont)
        .else
            GdipCreateFontFromDC(rcx, addr this.nativeFont)
        .endif
        }
    .operator Font?pLOGFONTA :HDC, :ptr LOGFONTA, :vararg {
        mov rcx,rdx
        .if r8
            mov rdx,r8
            GdipCreateFontFromLogfontA(rcx, rdx, addr this.nativeFont)
        .else
            GdipCreateFontFromDC(rcx, addr this.nativeFont)
        .endif
        }
    .operator Font?pFontFamily :ptr FontFamily, :vararg {
        mov rcx,rdx
        .if ecx
            mov rcx,[rcx].FontFamily.nativeFamily
        .endif
        GdipCreateFont(rcx, _1, addr this.nativeFont)
        }

    .operator Font?pword :abs, :abs, :abs=<FontStyleRegular>, :abs=<UnitPoint>, :abs=<NULL>, :vararg {

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


    .operator Font?pFont :ptr Font, :Status {
        mov     [this].Font.nativeFamily,_1
        mov     [this].Font.lastResult,_2
        }

    .operator Release  { }

    SetNativeFont       proc :ptr Font
    SetStatus           proc :Status

    GetLogFontA         proc :ptr Graphics, :ptr LOGFONTA
    GetLogFontW         proc :ptr Graphics, :ptr LOGFONTW

    Clone               proc

    IsAvailable         proc
    GetStyle            proc
    GetSize             proc
    GetUnit             proc
    GetLastStatus       proc
    GetHeight           proc :ptr
    GetHeightF          proc :REAL

    GetFamily           proc :ptr FontFamily

    .ends

;;--------------------------------------------------------------------------
;; Font Collection
;;--------------------------------------------------------------------------

.template FontCollection ;: public GdiplusBase

    nativeFontCollection    ptr_t ?
    lastResult              Status ?

    .operator = :ptr FontCollection, :Status {
        mov     [this].FontCollection.nativeFontCollection,_1
        mov     [this].FontCollection.lastResult,_2
        retm    <this>
        }

    SetStatus       proc :Status
    FontCollection  proc
    Release         proc
    GetFamilyCount  proc
    GetFamilies     proc :int_t, :ptr FontFamily, :ptr int_t
    GetLastStatus   proc
    .ends



.template InstalledFontCollection : public FontCollection

    InstalledFontCollection proc
    .ends


.template PrivateFontCollection : public FontCollection

    PrivateFontCollection proc

    AddFontFile     proc :ptr WCHAR
    AddMemoryFont   proc :ptr, :int_t
    .ends


;;--------------------------------------------------------------------------
;; Abstract base class for Image and Metafile
;;--------------------------------------------------------------------------

.template Image

    GpImage typedef Image

    nativeImage     ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    ; Image(WCHAR*, BOOL = FALSE)
    ; Image(IStream*, BOOL = FALSE)

    .operator Image :abs, :vararg {
        mov this.nativeImage,NULL
        this.typeid(Image, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .operator Image?pword :ptr WCHAR, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        if _2
            GdipLoadImageFromFileICM(rcx, addr this.nativeImage)
        else
            GdipLoadImageFromFile(rcx, addr this.nativeImage)
        endif
        }
    .operator Image?pIStream :ptr IStream, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        if _2
            GdipLoadImageFromStreamICM(rcx, addr this.nativeImage)
        else
            GdipLoadImageFromStream(rcx, addr this.nativeImage)
        endif
        }

    .operator Release :vararg {
        GdipDisposeImage(this.nativeImage)
        }

    .operator FromFile :vararg {
        this.Image?pword(_1)
        mov this.lastResult,eax
        }

    .operator FromStream :vararg {
        this.Image?pIStream(_1)
        mov this.lastResult,eax
        }

    .operator Clone :vararg {

        .new clone:Image

        GdipCloneImage(this.nativeImage, addr clone.nativeImage)
        mov clone.lastResult,eax
        this.SetStatus()
        lea rax,clone
        }

    .operator Save :abs, :vararg {
        this.typeid(Save, _1)(_1, _2)
        this.SetStatus()
        }
    .operator Save?pword :abs, :abs, :abs=<0>, :vararg {
        GdipSaveImageToFile(this.nativeImage, _1, _2, _3)
        }
    .operator Save?pIStream :abs, :abs, :abs=<0>, :vararg {
        GdipSaveImageToStream(this.nativeImage, _1, _2, _3)
        }

    .operator SaveAdd :abs, :vararg {
        this.typeid(SaveAdd, _1)(_1, _2)
        this.SetStatus()
        }
    .operator SaveAdd?pEncoderParameters :vararg {
        GdipSaveAdd(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator SaveAdd?pImage :ptr Image, :ptr EncoderParameters, :vararg {
        mov eax,InvalidParameter
        .if rdx
            mov rdx,[rdx].Image.nativeImage
            GdipSaveAddImage(this.nativeImage, rdx, r8)
        .endif
        this.SetStatus()
        }

    .operator GetType :vararg {
        mov this.scratch,ImageTypeUnknown
        GdipGetImageType(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetPhysicalDimension :ptr SizeF, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetImageDimension(this.nativeImage, &[rdx].SizeF.Width, &[rdx].SizeF.Height)
        .endif
        this.SetStatus()
        }

    .operator GetBounds :vararg {
        GdipGetImageBounds(this.nativeImage, _1)
        this.SetStatus()
        }

    .operator GetWidth :vararg {
        mov this.scratch,0
        GdipGetImageWidth(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetHeight :vararg {
        mov this.scratch,0
        GdipGetImageHeight(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetHorizontalResolution :vararg {
        mov this.scratch,0
        GdipGetImageHorizontalResolution(this.nativeImage, addr this.scratch)
        this.SetStatus()
        movss xmm0,this.scratch
        }

    .operator GetVerticalResolution :vararg {
        mov this.scratch,0
        GdipGetImageVerticalResolution(this.nativeImage, addr this.scratch)
        this.SetStatus()
        movss xmm0,this.scratch
        }

    .operator GetFlags :vararg {
        mov this.scratch,0
        GdipGetImageFlags(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetRawFormat :vararg {
        GdipGetImageRawFormat(this.nativeImage, _1)
        this.SetStatus()
        }

    .operator GetPixelFormat :vararg {
        GdipGetImagePixelFormat(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetPaletteSize :vararg {
        mov this.scratch,0
        GdipGetImagePaletteSize(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetPalette :vararg {
        GdipGetImagePalette(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator SetPalette :vararg {
        GdipSetImagePalette(this.nativeImage, _1)
        this.SetStatus()
        }

    .operator GetThumbnailImage :abs, :abs, :abs=<0>, :abs=<0>, :vararg {

        .new thumbimage:Image

        GdipGetImageThumbnail(this.nativeImage, _1, _2, addr thumbimage.nativeImage, _3, _4)
        mov thumbimage.lastResult,eax
        lea rax,thumbimage
        }

    .operator GetFrameDimensionsCount :vararg {
        mov this.scratch,0
        GdipImageGetFrameDimensionsCount(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .operator GetFrameDimensionsList :vararg {
        GdipImageGetFrameDimensionsList(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator GetFrameCount :vararg {
        mov this.scratch,0
        GdipImageGetFrameCount(this.nativeImage, _1, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .operator SelectActiveFrame :vararg {
        GdipImageSelectActiveFrame(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator RotateFlip :vararg {
        GdipImageRotateFlip(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator GetPropertyCount :vararg {
        mov this.scratch,0
        GdipGetPropertyCount(this.nativeImage, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .operator GetPropertyIdList :vararg {
        GdipGetPropertyIdList(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator GetPropertyItemSize :vararg {
        mov this.scratch,0
        GdipGetPropertyItemSize(this.nativeImage, _1, addr this.scratch)
        mov eax,this.scratch
        }
    .operator GetPropertyItem :vararg {
        GdipGetPropertyItem(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator GetPropertySize :vararg {
        GdipGetPropertySize(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator GetAllPropertyItems :abs, :abs, :ptr PropertyItem, :vararg {
        mov eax,InvalidParameter
        .if r9
            GdipGetAllPropertyItems(this.nativeImage, _1, _2, r9)
        .endif
        this.SetStatus()
        }
    .operator RemovePropertyItem :vararg {
        GdipRemovePropertyItem(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator SetPropertyItem :vararg {
        GdipSetPropertyItem(this.nativeImage, _1)
        this.SetStatus()
        }

    .operator GetEncoderParameterListSize :vararg {
        mov this.scratch,0
        GdipGetEncoderParameterListSize(this.nativeImage, _1, addr this.scratch)
        mov eax,this.scratch
        }
    .operator GetEncoderParameterList :vararg {
        GdipGetEncoderParameterList(this.nativeImage, _1)
        this.SetStatus()
        }
if (GDIPVER GE 0x0110)
    .operator FindFirstItem :vararg {
        GdipFindFirstImageItem(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator FindNextItem :vararg {
        GdipFindNextImageItem(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator GetItemData :vararg {
        GdipGetImageItemData(this.nativeImage, _1)
        this.SetStatus()
        }
    .operator SetAbort :vararg {
        GdipImageSetAbort(this.nativeImage, _1)
        this.SetStatus()
        }
endif

    .operator SetNativeImage :ptr Image, :vararg {
        mov this.nativeImage,rdx
        }

    .operator SetStatus :vararg {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,this.lastResult
        mov this.lastResult,eax
        }
    .operator GetLastStatus :vararg {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    .ends

IMAGE_INLINE macro class
    .operator Release :vararg {
        Image_Release(this)
        }
    .operator Save :vararg {
        Image_Save(this, _1)
        }
    .operator Save?pword :vararg {
        Image_Save?pword(this, _1)
        }
    .operator Save?pIStream :vararg {
        Image_Save?pIStream(this, _1)
        }
    .operator SaveAdd :vararg {
        Image_SaveAdd(this, _1)
        }
    .operator SaveAdd?pEncoderParameters :vararg {
        Image_SaveAdd?pEncoderParameters(this, _1)
        }
    .operator SaveAdd?pImage :ptr Image, :vararg {
        Image_SaveAdd?pImage(this, _1)
        }
    .operator GetType :vararg {
        Image_GetType(this)
        }
    .operator GetPhysicalDimension :vararg {
        Image_GetPhysicalDimension(this, _1)
        }
    .operator GetBounds :vararg {
        Image_GetBounds(this, _1)
        }
    .operator GetWidth :vararg {
        Image_GetWidth(this)
        }
    .operator GetHeight :vararg {
        Image_GetHeight(this)
        }
    .operator GetHorizontalResolution :vararg {
        Image_GetHorizontalResolution(this)
        }
    .operator GetVerticalResolution :vararg {
        Image_GetVerticalResolution(this)
        }
    .operator GetFlags :vararg {
        Image_GetFlags(this)
        }
    .operator GetRawFormat :vararg {
        Image_GetRawFormat(this, _1)
        }
    .operator GetPixelFormat :vararg {
        Image_GetPixelFormat(this)
        }
    .operator GetPaletteSize :vararg {
        Image_GetPaletteSize(this)
        }
    .operator GetPalette :vararg {
        Image_GetPalette(this, _1)
        }
    .operator SetPalette :vararg {
        Image_SetPalette(this, _1)
        }
    .operator GetThumbnailImage :vararg {
        Image_GetThumbnailImage(this, _1)
        }
    .operator GetFrameDimensionsCount :vararg {
        Image_GetFrameDimensionsCount(this)
        }
    .operator GetFrameDimensionsList :vararg {
        Image_GetFrameDimensionsList(this, _1)
        }
    .operator GetFrameCount :vararg {
        Image_GetFrameCount(this, _1)
        }
    .operator SelectActiveFrame :vararg {
        Image_SelectActiveFrame(this, _1)
        }
    .operator RotateFlip :vararg {
        Image_RotateFlip(this, _1)
        }
    .operator GetPropertyCount :vararg {
        Image_GetPropertyCount(this)
        }
    .operator GetPropertyIdList :vararg {
        Image_GetPropertyIdList(this, _1)
        }
    .operator GetPropertyItemSize :vararg {
        Image_GetPropertyItemSize(this, _1)
        }
    .operator GetPropertyItem :vararg {
        Image_GetPropertyItem(this, _1)
        }
    .operator GetPropertySize :vararg {
        Image_GetPropertySize(this, _1)
        }
    .operator GetAllPropertyItems :vararg {
        Image_GetAllPropertyItems(this, _1)
        }
    .operator RemovePropertyItem :vararg {
        Image_RemovePropertyItem(this, _1)
        }
    .operator SetPropertyItem :vararg {
        Image_SetPropertyItem(this, _1)
        }
    .operator GetEncoderParameterListSize :vararg {
        Image_GetEncoderParameterListSize(this, _1)
        }
    .operator GetEncoderParameterList :vararg {
        Image_GetEncoderParameterList(this, _1)
        }
if (GDIPVER GE 0x0110)
    .operator FindFirstItem :vararg {
        Image_FindFirstItem(this, _1)
        }
    .operator FindNextItem :vararg {
        Image_FindNextItem(this, _1)
        }
    .operator GetItemData :vararg {
        Image_GetItemData(this, _1)
        }
    .operator SetAbort :vararg {
        Image_SetAbort(this, _1)
        }
endif
    .operator SetNativeImage :vararg {
        Image_SetNativeImage(this, _1)
        }
    .operator SetStatus :vararg {
        Image_SetStatus(this, _1)
        }
    .operator GetLastStatus :vararg {
        Image_GetLastStatus(this)
        }
    exitm<>
    endm


.template Bitmap

    nativeImage     ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    IMAGE_INLINE(Bitmap)

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


    .operator Bitmap :abs, :vararg {
        ifb <_1>
            mov this.nativeImage,NULL
            mov this.lastResult,NotImplemented
        else
            this.typeid(Bitmap, _1)(_1, _2)
            mov this.lastResult,eax
        endif
        }
    .operator Bitmap?pword :ptr WCHAR, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        if _2
            GdipCreateBitmapFromFileICM(rcx, addr this.nativeImage)
        else
            GdipCreateBitmapFromFile(rcx, addr this.nativeImage)
        endif
        }
    .operator Bitmap?pIStream :ptr IStream, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        if _2
            GdipCreateBitmapFromStreamICM(rcx, addr this.nativeImage)
        else
            GdipCreateBitmapFromStream(rcx, addr this.nativeImage)
        endif
        }

    .operator Bitmap?i32 :abs, :abs, :abs, :vararg {
        this.typeid(Bitmap?i32, _3)(_1, _2, _3, _4)
        }
    .operator Bitmap?sdword :abs, :abs, :abs, :vararg {
        this.typeid(Bitmap?i32, _3)(_1, _2, _3, _4)
        }
    .operator Bitmap?r32 :abs, :abs, :abs, :vararg {
        this.typeid(Bitmap?r32, _3)(_1, _2, _3, _4)
        }
    .operator Bitmap?i32?i32 :abs, :abs, :abs, :abs, :vararg {
        ifb <_4>
            GdipCreateBitmapFromScan0(_1, _2, 0, _3, NULL, addr this.nativeImage)
        else
            GdipCreateBitmapFromScan0(_1, _2, _3, _4, _5, addr this.nativeImage)
        endif
        }
    .operator Bitmap?r32?r32 :abs, :abs, :abs, :abs, :vararg {
        mov ecx,_1
        mov edx,_2
        mov r8d,_3
        ifb <_4>
            GdipCreateBitmapFromScan0(ecx, edx, 0, r8d, NULL, addr this.nativeImage)
        else
            GdipCreateBitmapFromScan0(ecx, edx, r8d, _4, _5, addr this.nativeImage)
        endif
        }
    .operator Bitmap?i32?pGraphics :int_t, :int_t, :ptr Graphics, :vararg {
        mov ecx,edx
        mov edx,r8d
        mov r8,r9
        GdipCreateBitmapFromGraphics(ecx, edx, [r8].Graphics.nativeGraphics, addr this.nativeImage)
        }
    .operator Bitmap?pIDirectDrawSurface7 :ptr IDirectDrawSurface7, :vararg {
        mov rcx,rdx
        GdipCreateBitmapFromDirectDrawSurface(rcx, addr this.nativeImage)
        }
    .operator Bitmap?pBITMAPINFO :ptr BITMAPINFO, :ptr, :vararg {
        mov rcx,rdx
        mov rdx,r8
        GdipCreateBitmapFromGdiDib(rcx, rdx, addr this.nativeImage)
        }

    .operator Bitmap?pvoid :abs, :abs, :vararg {
        mov rcx,_1
        ifb <_2>
            GdipCreateBitmapFromHICON(rcx, addr this.nativeImage)
        else
            this.typeid(Bitmap?pvoid, _2)(_1, _2, _3)
        endif
        }
    .operator Bitmap?pvoid?pvoid :HBITMAP, :HPALETTE, :vararg {
        mov rdx,r8
        GdipCreateBitmapFromHBITMAP(rcx, rdx, addr this.nativeImage)
        }
    .operator Bitmap?pvoid?pword :HINSTANCE, :ptr WCHAR, :vararg {
        mov rdx,r8
        GdipCreateBitmapFromResource(rcx, rdx, addr this.nativeImage)
        }

    .operator FromFile :vararg {
        this.Bitmap?pword(_1)
        mov this.lastResult,eax
        }

    .operator FromStream :vararg {
        this.Bitmap?pIStream(_1)
        mov this.lastResult,eax
        }

    .operator Clone :abs, :vararg {
        this.typeid(Clone, _1)(_1, _2)
        }

    .operator Clone?i32 :abs, :abs, :abs, :abs, :abs, :vararg {

       .new clone:Bitmap

        mov ecx,_1
        GdipCloneBitmapAreaI(ecx, _2, _3, _4, _5, this.nativeImage, addr clone.nativeImage)
        mov clone.lastResult,eax
        lea rax,clone
        }

    .operator Clone?pRect :ptr Rect, :abs, :vararg {
        this.Clone?i32([rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }

    .operator Clone?flt :abs, :abs, :abs, :abs, :abs, :vararg {

       .new clone:Bitmap

        GdipCloneBitmapArea(_1, _2, _3, _4, r10d, this.nativeImage, addr clone.nativeImage)
        mov clone.lastResult,eax
        lea rax,clone
        }
    .operator Clone?pRectF :ptr RectF, :abs, :vararg {
        this.Clone?flt([rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, _2)
        }

    .operator LockBits :vararg {
        GdipBitmapLockBits(this.nativeImage, _1)
        this.SetStatus()
        }

    .operator UnlockBits :vararg {
        GdipBitmapUnlockBits(this.nativeImage, _1)
        this.SetStatus()
        }

    .operator GetPixel :abs, :abs, :ptr Color, :vararg {
        GdipBitmapGetPixel(this.nativeImage, _1, _2, r9)
        this.SetStatus()
        }

    .operator SetPixel :vararg {
        GdipBitmapSetPixel(this.nativeImage, _1)
        this.SetStatus()
        }

if (GDIPVER GE 0x0110)
    .operator ConvertFormat :vararg {
        GdipBitmapConvertFormat(this.nativeImage, _1)
        this.SetStatus()
        }

    ;; The palette must be allocated and count must be set to the number of
    ;; entries in the palette. If there are not enough, the API will fail.

    .operator InitializePalette :ptr ColorPalette,  ;; Palette to initialize.
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

    .operator ApplyEffect :abs, :vararg {
        this.typeid(ApplyEffect, _1)(_1, _2)
        }

    .operator ApplyEffect?pEffect :ptr Effect, :ptr RECT, :vararg {

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

    .operator ApplyEffect?pBitmap :ptr ptr Bitmap, :int_t, :ptr Effect, :ptr RECT, :ptr RECT, :ptr ptr Bitmap {

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

    .operator GetHistogram :abs, :abs, :abs, :abs, :abs, :abs {
        GdipBitmapGetHistogram([this].Image.nativeImage, _1, _2, _3, _4, _5, _6)
        }

    .operator GetHistogramSize :abs, :abs {
        GdipBitmapGetHistogramSize(_1, _2)
        }
endif

    .operator SetResolution :vararg {
        GdipBitmapSetResolution(this.nativeImage, _1)
        this.SetStatus()
        }

    .operator GetHBITMAP :ARGB, :ptr HBITMAP, :vararg {
        xchg rdx,r8
        GdipCreateHBITMAPFromBitmap(this.nativeImage, rdx, r8d)
        this.SetStatus()
        }

    .operator GetHICON :ptr HICON, :vararg {
        GdipCreateHICONFromBitmap(this.nativeImage, rdx)
        this.SetStatus()
        }

    .ends
    GpBitmap typedef Bitmap

.template CustomLineCap

    GpCustomLineCap typedef CustomLineCap

    nativeCap   ptr_t ?
    lastResult  Status ?

    CustomLineCap proc

    CustomLineCap2 proc :ptr CustomLineCap
    .operator = :ptr CustomLineCap

    .operator CustomLineCap3 :ptr GpCustomLineCap, :Status {
        mov lastResult = _2
        SetNativeCap(_1)
        }

    .operator SetNativeCap :ptr GpCustomLineCap {
        mov [this].CustomLineCap.nativeCap,_1
        }

    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].CustomLineCap.lastResult,eax
        .endif
        retm <eax>
        }

    CustomLineCap4 proc :ptr GraphicsPath, :ptr GraphicsPath, :LineCap, :REAL

    Release         proc
    Clone           proc

    ;; This changes both the start and end cap.

    .operator SetStrokeCap :LineCap {
        exitm<SetStrokeCaps(strokeCap, strokeCap)>
        }

    SetStrokeCaps   proc :LineCap, :LineCap
    GetStrokeCaps   proc :ptr LineCap, :ptr LineCap
    SetStrokeJoin   proc :LineJoin
    GetStrokeJoin   proc
    SetBaseCap      proc :LineCap
    GetBaseCap      proc
    SetBaseInset    proc :REAL
    GetBaseInset    proc
    SetWidthScale   proc :REAL
    GetWidthScale   proc
    GetLastStatus   proc

    .ends

.template CachedBitmap ;: public GdiplusBase

    nativeCachedBitmap ptr_t ?
    lastResult      Status ?

    CachedBitmap    proc :ptr Bitmap, :ptr Graphics
    Release         proc

    GetLastStatus   proc

    CachedBitmap2   proc :ptr CachedBitmap
    .operator       = :ptr CachedBitmap

    .ends

.template Metafile : public Image

    IMAGE_INLINE(Metafile)

    Metafile2 proc :ptr Metafile
    .operator = :ptr Metafile

    ;; Playback a metafile from a HMETAFILE
    ;; If deleteWmf is TRUE, then when the metafile is deleted,
    ;; the hWmf will also be deleted.  Otherwise, it won't be.

    Metafile3 proc :HMETAFILE, :ptr WmfPlaceableFileHeader, :BOOL ; deleteWmf = FALSE

    ;; Playback a metafile from a HENHMETAFILE
    ;; If deleteEmf is TRUE, then when the metafile is deleted,
    ;; the hEmf will also be deleted.  Otherwise, it won't be.

    Metafile4 proc :HENHMETAFILE, :BOOL ; deleteEmf = FALSE

    Metafile5 proc :ptr WCHAR

    ;; Playback a WMF metafile from a file.

    Metafile6 proc :ptr WCHAR, :ptr WmfPlaceableFileHeader
    Metafile7 proc :ptr IStream

    ;; Record a metafile to memory.

    Metafile8 proc :HDC, :EmfType, :ptr WCHAR

    ;; Record a metafile to memory.

    Metafile9 proc :HDC, :ptr RectF, :MetafileFrameUnit, :EmfType, :ptr WCHAR

    ;; Record a metafile to memory.

    Metafile10 proc :HDC, :ptr Rect, :MetafileFrameUnit, :EmfType, :ptr WCHAR

    Metafile11 proc :ptr WCHAR, :HDC, :EmfType, :ptr WCHAR

    Metafile12 proc :ptr WCHAR, :HDC, :ptr RectF, :MetafileFrameUnit, :EmfType, :ptr WCHAR

    Metafile13 proc :ptr WCHAR, :HDC, :ptr Rect, :MetafileFrameUnit, :EmfType, :ptr WCHAR

    Metafile14 proc :ptr IStream, :HDC, :EmfType, :ptr WCHAR

    Metafile15 proc :ptr IStream, :HDC, :ptr RectF, :MetafileFrameUnit, :EmfType, :ptr WCHAR

    Metafile16 proc :ptr IStream, :HDC, :ptr Rect, :MetafileFrameUnit, :EmfType, :ptr WCHAR


    GetMetafileHeader proc :HMETAFILE, :ptr WmfPlaceableFileHeader, :ptr MetafileHeader
    GetMetafileHeader2 proc :HENHMETAFILE, :ptr MetafileHeader
    GetMetafileHeader3 proc :ptr WCHAR, :ptr MetafileHeader
    GetMetafileHeader4 proc :ptr IStream, :ptr MetafileHeader
    GetMetafileHeader5 proc :ptr MetafileHeader

    ;; Once this method is called, the Metafile object is in an invalid state
    ;; and can no longer be used.  It is the responsiblity of the caller to
    ;; invoke DeleteEnhMetaFile to delete this hEmf.

    GetHENHMETAFILE proc

    ;; Used in conjuction with Graphics::EnumerateMetafile to play an EMF+
    ;; The data must be DWORD aligned if it's an EMF or EMF+.  It must be
    ;; WORD aligned if it's a WMF.

    PlayRecord proc :EmfPlusRecordType, :UINT, :UINT, :ptr BYTE

    ;; If you're using a printer HDC for the metafile, but you want the
    ;; metafile rasterized at screen resolution, then use this API to set
    ;; the rasterization dpi of the metafile to the screen resolution,
    ;; e.g. 96 dpi or 120 dpi.

    SetDownLevelRasterizationLimit proc :UINT

    GetDownLevelRasterizationLimit proc

    EmfToWmfBits proc :HENHMETAFILE, :UINT, :LPBYTE, :SINT, :SINT

if (GDIPVER GE 0x0110)
    ConvertToEmfPlus proc :ptr Graphics, :ptr SINT, :EmfType, :ptr WCHAR
    ConvertToEmfPlus2 proc :ptr Graphics, :ptr WCHAR, :ptr SINT, :EmfType, :ptr WCHAR
    ConvertToEmfPlus3 proc :ptr Graphics, :ptr IStream, :ptr SINT, :EmfType, :ptr WCHAR
endif

    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif


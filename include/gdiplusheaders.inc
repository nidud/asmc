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
;;--------------------------------------------------------------------------

.template FontFamily ;: public GdiplusBase

    nativeFamily    ptr_t ?
    lastResult      Status ?

    .operator FontFamily {

        .if GdipAlloc( FontFamily )

            mov [rax].FontFamily.nativeFamily,NULL
            mov [rax].FontFamily.lastResult,Ok
        .endif
        retm <rax>
        }

    .operator = :ptr FontFamily {
        mov     [this].FontFamily.nativeFamily,_1
        mov     [this].FontFamily.lastResult,Ok
        retm    <this>
        }

    SetStatus   proc :Status

    ;FontFamily  proc :ptr FontFamily, :Status
    ;FontFamily  proc
    ;FontFamily  proc :ptr WCHAR, :ptr FontCollection

    Release             proc

    GenericSansSerif    proc
    GenericSerif        proc
    GenericMonospace    proc

    GetFamilyName       proc :LPWSTR, :LANGID

    Clone               proc

    .operator IsAvailable {
        xor eax,eax
        .if rax != [this].FontFamily.nativeFamily
            inc eax
        .endif
        retm<eax>
        }

    IsStyleAvailable    proc :int_t

    GetEmHeight         proc :int_t
    GetCellAscent       proc :int_t
    GetCellDescent      proc :int_t
    GetLineSpacing      proc :int_t

    GetLastStatus       proc

    .ends

if 0
    .data
    GenericSansSerifFontFamily ptr_t NULL
    GenericSerifFontFamily     ptr_t NULL
    GenericMonospaceFontFamily ptr_t NULL

    GenericSansSerifFontFamilyBuffer db sizeof(FontFamily) dup(0)
    GenericSerifFontFamilyBuffer     db sizeof(FontFamily) dup(0)
    GenericMonospaceFontFamilyBuffer db sizeof(FontFamily) dup(0)
endif
externdef GenericSansSerifFontFamily        :ptr FontFamily
externdef GenericSerifFontFamily            :ptr FontFamily
externdef GenericMonospaceFontFamily        :ptr FontFamily

externdef GenericSansSerifFontFamilyBuffer  :FontFamily
externdef GenericSerifFontFamilyBuffer      :FontFamily
externdef GenericMonospaceFontFamilyBuffer  :FontFamily


;;--------------------------------------------------------------------------
;; Font
;;--------------------------------------------------------------------------

.template Font ;: public GdiplusBase

    nativeFont  ptr_t ?
    lastResult  Status ?

    .operator Font {

        .if GdipAlloc( Font )

            mov [rax].Font.nativeFont,NULL
            mov [rax].Font.lastResult,Ok
        .endif
        retm <rax>
        }

    .operator = :ptr Font, :Status {
        mov     [this].Font.nativeFamily,_1
        mov     [this].Font.lastResult,_2
        retm    <this>
        }

    Release             proc

    SetNativeFont       proc :ptr Font
    SetStatus           proc :Status

    Font1               proc :HDC
    Font2               proc :HDC, :ptr LOGFONTA
    Font3               proc :HDC, :ptr LOGFONTW
    Font4               proc :HDC, :HFONT
    Font5               proc :ptr FontFamily, :REAL, :int_t, :Unit
    Font6               proc :ptr WCHAR, :REAL, :int_t, :Unit, :ptr FontCollection

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
    loadStatus      Status ?
    memState        Status ?

    .operator Image {

        .new image:ptr Image

        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !GdipAlloc(Image)
                mov [rax].Image.memState,Ok
            .else
                mov [rax].Image.memState,NotImplemented
            .endif
            mov [rax].Image.nativeImage,NULL
            mov [rax].Image.lastResult,NotImplemented
        .until 1
        retm<rax>
    }

    .operator Release {

        mov image,this

        GdipDisposeImage([this].Image.nativeImage)

        mov this,image
        .if [this].Image.memState != NotImplemented

            GdipFree(this)
        .endif
        exitm<>
    }

    .operator FromFile :ptr WCHAR, :BOOL {

        mov image,this
        mov [this].Image.nativeImage,NULL

        xchg this,_1
        .if _2
            GdipLoadImageFromFileICM(this, &[_1].Image.nativeImage)
        .else
            GdipLoadImageFromFile(this, &[_1].Image.nativeImage)
        .endif
        exitm<image.SetStatus(eax)>
        }

    .operator FromStream :ptr IStream, :BOOL {   ; useEmbeddedColorManagement = FALSE

        mov image,this
        mov [this].Image.nativeImage,NULL

        xchg this,_1
        .if _2
            GdipLoadImageFromStreamICM(this, &[_1].Image.nativeImage)
        .else
            GdipLoadImageFromStream(this, &[_1].Image.nativeImage)
        .endif
        exitm<image.SetStatus(eax)>
        }

    .operator Clone {

        .new clone:ptr Image

        mov image,this
        mov clone,Image()
        .if rax
            mov this,image
            GdipCloneImage([this].Image.nativeImage, &[rax].Image.nativeImage)
            image.SetStatus(eax)
            mov edx,eax
            mov rax,clone
            mov [rax].Image.lastResult,edx
        .endif
        retm<rax>
        }

    .operator Save :ptr WCHAR, :ptr CLSID, :ptr EncoderParameters {
        mov image,this
        GdipSaveImageToFile([this].Image.nativeImage, _1, _2, _3)
        exitm<image.SetStatus(eax)>
        }

    Save2           proc :ptr IStream, :ptr CLSID, :ptr EncoderParameters
    SaveAdd         proc :ptr EncoderParameters
    SaveAdd2        proc :ptr Image, :ptr EncoderParameters

    GetType         proc
    GetPhysicalDimension proc :ptr SizeF
    GetBounds       proc :ptr RectF, :ptr Unit

    GetWidth        proc
    GetHeight       proc
    GetHorizontalResolution proc
    GetVerticalResolution proc
    GetFlags        proc
    GetRawFormat    proc :ptr GUID
    GetPixelFormat  proc

    GetPaletteSize  proc
    GetPalette      proc :ptr ColorPalette, :int_t
    SetPalette      proc :ptr ColorPalette

    GetThumbnailImage proc :UINT, :UINT, :GetThumbnailImageAbort, :ptr
    GetFrameDimensionsCount proc
    GetFrameDimensionsList proc :ptr GUID, :UINT
    GetFrameCount   proc :GUID
    SelectActiveFrame proc :ptr GUID, :UINT
    RotateFlip      proc :RotateFlipType
    GetPropertyCount proc
    GetPropertyIdList proc :UINT, :ptr
    GetPropertyItemSize proc :PROPID
    GetPropertyItem proc :PROPID, :UINT, :ptr PropertyItem
    GetPropertySize proc :ptr UINT, :ptr UINT
    GetAllPropertyItems proc :UINT, :UINT, :ptr PropertyItem
    RemovePropertyItem proc :PROPID
    SetPropertyItem proc :ptr PropertyItem

    GetEncoderParameterListSize proc :ptr CLSID
    GetEncoderParameterList proc :ptr CLSID, :UINT, :ptr EncoderParameters
if (GDIPVER GE 0x0110)
    FindFirstItem   proc :ptr ImageItemData
    FindNextItem    proc :ptr ImageItemData
    GetItemData     proc :ptr ImageItemData
    SetAbort        proc :ptr GdiplusAbort
endif

    SetNativeImage  proc :ptr Image

    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].Image.lastResult,eax
        .endif
        retm <eax>
        }

    GetLastStatus   proc

    .ends

.template Bitmap : public Image

    .operator Bitmap {
        exitm<[this].Image.Image()>
        }
    .operator FromFile :ptr WCHAR, :BOOL {
        exitm<[this].Image.FromFile(_1, _2)>
        }
    .operator Release {
        exitm<[this].Image.Release()>
        }

    Bitmap2         proc :ptr GpBitmap
    Bitmap3         proc :ptr WCHAR, :BOOL ; useEmbeddedColorManagement = FALSE
    Bitmap4         proc :ptr IStream, :BOOL ; useEmbeddedColorManagement = FALSE

    Bitmap5         proc :int_t, :int_t, :int_t, :PixelFormat, :ptr BYTE
    Bitmap6         proc :int_t, :int_t, :PixelFormat
    Bitmap7         proc :int_t, :int_t, :ptr Graphics

    Clone1          proc :ptr Rect, :PixelFormat
    Clone2          proc :int_t, :int_t, :int_t, :int_t, :PixelFormat
    Clone3          proc :ptr RectF, :PixelFormat
    Clone4          proc :REAL, :REAL, :REAL, :REAL, :PixelFormat

    LockBits        proc :ptr Rect, :UINT, :PixelFormat, :ptr BitmapData
    UnlockBits      proc :ptr BitmapData
    GetPixel        proc :int_t, :int_t, :ptr Color
    SetPixel        proc :int_t, :int_t, :ptr Color

if (GDIPVER GE 0x0110)
    ConvertFormat   proc :PixelFormat, :DitherType, :PaletteType, :ptr ColorPalette, :REAL

    ;; The palette must be allocated and count must be set to the number of
    ;; entries in the palette. If there are not enough, the API will fail.

    InitializePalette proc  :ptr ColorPalette,  ;; Palette to initialize.
                            :PaletteType,       ;; palette enumeration type.
                            :int_t,             ;; how many optimal colors
                            :BOOL,              ;; add a transparent color to the palette.
                            :ptr Bitmap         ;; optional bitmap for median cut.

    ApplyEffect     proc :ptr Effect, :ptr RECT

    ApplyEffect2    proc    :ptr ptr Bitmap,
                            :int_t,
                            :ptr Effect,
                            :ptr RECT, ;; optional parameter.
                            :ptr RECT, ;; optional parameter.
                            :ptr ptr Bitmap

    GetHistogram    proc :HistogramFormat, :UINT, :ptr UINT, :ptr UINT, :ptr UINT, :ptr UINT

    GetHistogramSize proc :HistogramFormat, :ptr UINT
endif

    SetResolution   proc :REAL, :REAL

    Bitmap8         proc :ptr IDirectDrawSurface7
    Bitmap9         proc :ptr BITMAPINFO, :ptr
    Bitmap10        proc :HBITMAP, :HPALETTE
    Bitmap11        proc :HICON
    Bitmap12        proc :HINSTANCE, :ptr WCHAR
    FromDirectDrawSurface7 proc :ptr IDirectDrawSurface7
    FromBITMAPINFO  proc :ptr BITMAPINFO, :ptr
    FromHBITMAP     proc :HBITMAP, :HPALETTE
    FromHICON       proc :HICON
    FromResource    proc :HINSTANCE, :ptr WCHAR

    .operator GetHBITMAP :ptr Color, :ptr HBITMAP {
        mov image,this
        xchg _1,_2
        .if _2
            mov r8d,[_2].Color.Argb
        .endif
        GdipCreateHBITMAPFromBitmap([this].Image.nativeImage, _1, r8d)
        exitm<image.SetStatus(eax)>
        }

    .operator GetHICON :ptr HICON {
        mov image,this
        GdipCreateHICONFromBitmap([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }

    .ends
    GpBitmap typedef Bitmap

.template CustomLineCap ;: public GdiplusBase

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

    .operator Metafile {
        exitm<Image_Image(0)>
        }
    .operator SetStatus :Status {
        exitm<Image_SetStatus(this, _1)>
        }
    .operator SetNativeImage :ptr Image {
        mov [this].Image.nativeImage,_1
        retm <this>
        }


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


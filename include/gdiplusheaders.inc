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

    .operator FromStream :ptr IStream, :BOOL {

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
    .operator Save2 :ptr IStream, :ptr CLSID, :ptr EncoderParameters {
        mov image,this
        GdipSaveImageToStream([this].Image.nativeImage, _1, _2, _3)
        exitm<image.SetStatus(eax)>
        }

    .operator SaveAdd :ptr EncoderParameters {
        mov image,this
        GdipSaveAdd([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }
    .operator SaveAdd2 :ptr Image, :ptr EncoderParameters {
        mov image,this
        mov eax,InvalidParameter
        .if _1
            mov _1,[_1].Image.nativeImage
            GdipSaveAddImage([this].Image.nativeImage, _1, _2)
        .endif
        exitm<image.SetStatus(eax)>
        }

    .operator GetType {

        .new type:ImageType

        mov type,ImageTypeUnknown
        mov image,this
        GdipGetImageType([this].Image.nativeImage, &type)
        image.SetStatus(eax)
        mov eax,type
        retm <eax>
        }

    .operator GetPhysicalDimension :ptr SizeF {

        mov image,this
        .repeat

            .if (_1 == NULL)
                image.SetStatus(InvalidParameter)
                .break
            .endif

            .new sizef:ptr SizeF
            .new width:REAL
            .new height:REAL

            mov sizef,_1
            GdipGetImageDimension([this].Image.nativeImage, &width, &height)
            image.SetStatus(eax)
            mov _1,sizef
            mov r8d,width
            mov [_1].SizeF.Width,r8d
            mov r8d,height
            mov [_1].SizeF.Height,r8d
        .until 1
        retm <eax>
        }

    .operator GetBounds :ptr RectF, :ptr Unit {
        mov image,this
        GdipGetImageBounds([this].Image.nativeImage, _1, _2)
        exitm<image.SetStatus(eax)>
        }

    .operator GetWidth {

        .new width:UINT

        mov image,this
        mov width,0

        GdipGetImageWidth([this].Image.nativeImage, &width)
        image.SetStatus(eax)
        mov eax,width
        retm <eax>
        }

    .operator GetHeight {

        .new height:UINT

        mov image,this
        mov height,0

        GdipGetImageHeight([this].Image.nativeImage, &height)
        image.SetStatus(eax)
        mov eax,height
        retm <eax>
        }

    .operator GetHorizontalResolution {

        .new resolution:REAL

        mov resolution,0.0
        mov image,this
        GdipGetImageHorizontalResolution([this].Image.nativeImage, &resolution)
        image.SetStatus(eax)
        movss xmm0,resolution
        retm <xmm0>
        }

    .operator GetVerticalResolution {

        .new resolution:REAL

        mov resolution,0.0
        mov image,this
        GdipGetImageVerticalResolution([this].Image.nativeImage, &resolution)
        image.SetStatus(eax)
        movss xmm0,resolution
        retm <xmm0>
        }

    .operator GetFlags {

        .new flags:UINT

        mov image,this
        mov flags,0

        GdipGetImageFlags([this].Image.nativeImage, &flags)
        image.SetStatus(eax)
        mov eax,flags
        retm <eax>
        }

    .operator GetRawFormat :ptr GUID {
        mov image,this
        GdipGetImageRawFormat([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }

    .operator GetPixelFormat {

        .new format:PixelFormat

        mov image,this
        GdipGetImagePixelFormat([this].Image.nativeImage, &format)
        image.SetStatus(eax)
        mov eax,format
        retm <eax>
        }

    .operator GetPaletteSize {

        .new size:SINT

        mov size,0
        mov image,this
        GdipGetImagePaletteSize([this].Image.nativeImage, &size)
        image.SetStatus(eax)
        mov eax,size
        retm <eax>
        }

    .operator GetPalette :ptr ColorPalette, :int_t {
        mov image,this
        GdipGetImagePalette([this].Image.nativeImage, _1, _2)
        exitm<image.SetStatus(eax)>
        }
    .operator SetPalette :ptr ColorPalette {
        mov image,this
        GdipSetImagePalette([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }

    .operator GetThumbnailImage :UINT, :UINT, :GetThumbnailImageAbort, :ptr {

        .new thumbimage:ptr Image

        mov thumbimage,this
        mov image,NULL
        GdipGetImageThumbnail([this].Image.nativeImage, _1, _2, &image, _3, _4)
        thumbimage.SetStatus(eax)
        .if Image()
            mov rdx,image
            mov [rax].Image.nativeImage,rdx
            mov rcx,thumbimage
            mov edx,[rcx].Image.lastResult
            mov [rax].Image.lastResult,edx
        .else
            GdipDisposeImage(thumbimage)
            xor eax,eax
        .endif
        retm <rax>
        }

    .operator GetFrameDimensionsCount {

        .new count:UINT

        mov count,0
        mov image,this
        GdipImageGetFrameDimensionsCount([this].Image.nativeImage, &count)
        image.SetStatus(eax)
        mov eax,count
        retm <rax>
        }
    .operator GetFrameDimensionsList :ptr GUID, :UINT {
        mov image,this
        GdipImageGetFrameDimensionsList([this].Image.nativeImage, _1, _2)
        exitm<image.SetStatus(eax)>
        }
    .operator GetFrameCount :ptr GUID {

        .new count:UINT

        mov count,0
        mov image,this
        GdipImageGetFrameCount([this].Image.nativeImage, _1, &count)
        image.SetStatus(eax)
        mov eax,count
        retm <rax>
        }
    .operator SelectActiveFrame :ptr GUID, :UINT {
        mov image,this
        GdipImageSelectActiveFrame([this].Image.nativeImage, _1, _2)
        exitm<image.SetStatus(eax)>
        }
    .operator RotateFlip :RotateFlipType {
        mov image,this
        GdipImageRotateFlip([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }
    .operator GetPropertyCount {

        .new numProperty:UINT

        mov numProperty,0
        mov image,this
        GdipGetPropertyCount([this].Image.nativeImage, &numProperty)
        image.SetStatus(eax)
        mov eax,numProperty
        retm <rax>
        }
    .operator GetPropertyIdList :UINT, :ptr {
        mov image,this
        GdipGetPropertyIdList([this].Image.nativeImage, _1, _2)
        exitm<image.SetStatus(eax)>
        }
    .operator GetPropertyItemSize :PROPID {

        .new size:UINT

        mov size,0
        mov image,this
        GdipGetPropertyItemSize([this].Image.nativeImage, _1, &size)
        mov eax,size
        retm <rax>
        }
    .operator GetPropertyItem :PROPID, :UINT, :ptr PropertyItem {
        mov image,this
        GdipGetPropertyItem([this].Image.nativeImage, _1, _2, _3)
        exitm<image.SetStatus(eax)>
        }
    .operator GetPropertySize :ptr UINT, :ptr UINT {
        mov image,this
        GdipGetPropertySize([this].Image.nativeImage, _1, _2)
        exitm<image.SetStatus(eax)>
        }
    .operator GetAllPropertyItems :UINT, :UINT, :ptr PropertyItem {
        mov image,this
        .if _3 == NULL
            image.SetStatus(InvalidParameter)
        .else
            GdipGetAllPropertyItems([this].Image.nativeImage, _1, _2, _3)
            image.SetStatus(eax)
        .endif
        retm <rax>
        }
    .operator RemovePropertyItem :PROPID {
        mov image,this
        GdipRemovePropertyItem([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }
    .operator SetPropertyItem :ptr PropertyItem {
        mov image,this
        GdipSetPropertyItem([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }

    .operator GetEncoderParameterListSize :ptr CLSID {

        .new size:UINT

        mov size,0
        mov image,this
        GdipGetEncoderParameterListSize([this].Image.nativeImage, _1, &size)
        mov eax,size
        retm <rax>
        }
    .operator GetEncoderParameterList :ptr CLSID, :UINT, :ptr EncoderParameters {
        mov image,this
        GdipGetEncoderParameterList([this].Image.nativeImage, _1, _2, _3)
        exitm<image.SetStatus(eax)>
        }
if (GDIPVER GE 0x0110)
    .operator FindFirstItem :ptr ImageItemData {
        mov image,this
        GdipFindFirstImageItem([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }
    .operator FindNextItem :ptr ImageItemData {
        mov image,this
        GdipFindNextImageItem([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }
    .operator GetItemData :ptr ImageItemData {
        mov image,this
        GdipGetImageItemData([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }
    .operator SetAbort :ptr GdiplusAbort {
        mov image,this
        GdipImageSetAbort([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }
endif

    .operator SetNativeImage :ptr Image {
        mov [this].Image.nativeImage,_1
        exitm<>
        }

    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].Image.lastResult,eax
        .endif
        retm <eax>
        }
    .operator GetLastStatus {
        mov eax,[this].Image.lastResult
        mov [this].Image.lastResult,Ok
        retm <eax>
        }

    .ends

IMAGE_INLINE macro class
    .operator class {
        exitm<[this].Image.Image()>
        }
    .operator Release {
        exitm<[this].Image.Release()>
        }
if 0
    .operator FromFile :ptr WCHAR, :BOOL {
        exitm<[this].Image.FromFile(_1, _2)>
        }
    .operator FromStream :ptr IStream, :BOOL {
        exitm<[this].Image.FromStream(_1, _2)>
        }
endif
    .operator Clone {
        exitm<[this].Image.Clone()>
        }
    .operator Save :ptr WCHAR, :ptr CLSID, :ptr EncoderParameters {
        exitm<[this].Image.Save(_1, _2, _3)>
        }
    .operator Save2 :ptr IStream, :ptr CLSID, :ptr EncoderParameters {
        exitm<[this].Image.Save2(_1, _2, _3)>
        }
    .operator SaveAdd :ptr EncoderParameters {
        exitm<[this].Image.SaveAdd(_1)>
        }
    .operator SaveAdd2 :ptr Image, :ptr EncoderParameters {
        exitm<[this].Image.SaveAdd2(_1, _2)>
        }

    .operator GetType {
        exitm<[this].Image.GetType()>
        }
    .operator GetPhysicalDimension :ptr SizeF {
        exitm<[this].Image.GetPhysicalDimension(_1)>
        }
    .operator GetBounds :ptr RectF, :ptr Unit {
        exitm<[this].Image.GetBounds(_1, _2)>
        }
    .operator GetWidth {
        exitm<[this].Image.GetWidth()>
        }
    .operator GetHeight {
        exitm<[this].Image.GetHeight()>
        }
    .operator GetHorizontalResolution {
        exitm<[this].Image.GetHorizontalResolution()>
        }
    .operator GetVerticalResolution {
        exitm<[this].Image.GetVerticalResolution()>
        }
    .operator GetFlags {
        exitm<[this].Image.GetFlags()>
        }
    .operator GetRawFormat :ptr GUID {
        exitm<[this].Image.GetRawFormat(_1)>
        }
    .operator GetPixelFormat {
        exitm<[this].Image.GetPixelFormat()>
        }
    .operator GetPaletteSize {
        exitm<[this].Image.GetPaletteSize()>
        }
    .operator GetPalette :ptr ColorPalette, :int_t {
        exitm<[this].Image.GetPalette(_1, _2)>
        }
    .operator SetPalette :ptr ColorPalette {
        exitm<[this].Image.SetPalette(_1)>
        }
    .operator GetThumbnailImage :UINT, :UINT, :GetThumbnailImageAbort, :ptr {
        exitm<[this].Image.GetThumbnailImage(_1, _2, _3, _4)>
        }
    .operator GetFrameDimensionsCount {
        exitm<[this].Image.GetFrameDimensionsCount()>
        }
    .operator GetFrameDimensionsList :ptr GUID, :UINT {
        exitm<[this].Image.GetFrameDimensionsList(_1, _2)>
        }
    .operator GetFrameCount :ptr GUID {
        exitm<[this].Image.GetFrameCount(_1)>
        }
    .operator SelectActiveFrame :ptr GUID, :UINT {
        exitm<[this].Image.SelectActiveFrame(_1, _2)>
        }
    .operator RotateFlip :RotateFlipType {
        exitm<[this].Image.RotateFlip(_1)>
        }
    .operator GetPropertyCount {
        exitm<[this].Image.GetPropertyCount()>
        }
    .operator GetPropertyIdList :UINT, :ptr {
        exitm<[this].Image.GetPropertyIdList(_1, _2)>
        }
    .operator GetPropertyItemSize :PROPID {
        exitm<[this].Image.GetPropertyItemSize(_1)>
        }
    .operator GetPropertyItem :PROPID, :UINT, :ptr PropertyItem {
        exitm<[this].Image.GetPropertyItem(_1, _2, _3)>
        }
    .operator GetPropertySize :ptr UINT, :ptr UINT {
        exitm<[this].Image.GetPropertySize(_1, _2)>
        }
    .operator GetAllPropertyItems :UINT, :UINT, :ptr PropertyItem {
        exitm<[this].Image.GetAllPropertyItems(_1, _2, _3)>
        }
    .operator RemovePropertyItem :PROPID {
        exitm<[this].Image.RemovePropertyItem(_1)>
        }
    .operator SetPropertyItem :ptr PropertyItem {
        exitm<[this].Image.SetPropertyItem(_1)>
        }
    .operator GetEncoderParameterListSize :ptr CLSID {
        exitm<[this].Image.GetEncoderParameterListSize(_1)>
        }
    .operator GetEncoderParameterList :ptr CLSID, :UINT, :ptr EncoderParameters {
        exitm<[this].Image.GetEncoderParameterList(_1, _2, _3)>
        }
if (GDIPVER GE 0x0110)
    .operator FindFirstItem :ptr ImageItemData {
        exitm<[this].Image.FindFirstItem(_1)>
        }
    .operator FindNextItem :ptr ImageItemData {
        exitm<[this].Image.FindNextItem(_1)>
        }
    .operator GetItemData :ptr ImageItemData {
        exitm<[this].Image.GetItemData(_1)>
        }
    .operator SetAbort :ptr GdiplusAbort {
        exitm<[this].Image.SetAbort(_1)>
        }
endif
    .operator SetNativeImage :ptr Image {
        exitm<[this].Image.SetNativeImage(_1)>
        }
    .operator SetStatus :Status {
        exitm<[this].Image.SetStatus(_1)>
        }
    .operator GetLastStatus {
        exitm<[this].Image.GetLastStatus()>
        }
    exitm<>
    endm


.template Bitmap : public Image

    IMAGE_INLINE(Bitmap)

    .operator FromFile :ptr WCHAR, :BOOL {

        mov image,this
        mov [this].Image.nativeImage,NULL

        xchg this,_1
        .if _2
            GdipCreateBitmapFromFileICM(this, &[_1].Image.nativeImage)
        .else
            GdipCreateBitmapFromFile(this, &[_1].Image.nativeImage)
        .endif
        exitm<image.SetStatus(eax)>
        }

    .operator FromStream :ptr IStream, :BOOL {
        mov image,this
        xchg this,_1
        .if _2
            GdipCreateBitmapFromStreamICM(this, &[_1].Image.nativeImage)
        .else
            GdipCreateBitmapFromStream(this, &[_1].Image.nativeImage)
        .endif
        exitm<image.SetStatus(eax)>
        }

    .operator FromScan0 :int_t, :int_t, :int_t, :PixelFormat, :ptr BYTE {
        mov image,this
        mov rax,this
        mov r10,_5
        mov ecx,_1
        mov edx,_2
        mov r8d,_3
        mov r9d,_4
        GdipCreateBitmapFromScan0(ecx, edx, r8d, r9d, r10, rax)
        exitm<image.SetStatus(eax)>
        }

    .operator FromScan02 :int_t, :int_t, :PixelFormat {
        mov image,this
        mov rax,this
        mov ecx,_1
        mov edx,_2
        GdipCreateBitmapFromScan0(ecx, edx, 0, _3, NULL, rax)
        exitm<image.SetStatus(eax)>
        }

    .operator FromGraphics :int_t, :int_t, :ptr Graphics {
        mov image,this
        mov rax,this
        mov ecx,_1
        mov edx,_2
        mov r10,_3
        GdipCreateBitmapFromGraphics(ecx, edx, [r10].Graphics.nativeGraphics, rax)
        exitm<image.SetStatus(eax)>
        }

    .operator FromDirectDrawSurface7 :ptr IDirectDrawSurface7 {
        mov image,this
        xchg this,_1
        GdipCreateBitmapFromDirectDrawSurface(this, _1)
        exitm<image.SetStatus(eax)>
        }

    .operator FromBITMAPINFO :ptr BITMAPINFO, :ptr {
        mov image,this
        xchg this,_2
        xchg _1,this
        GdipCreateBitmapFromGdiDib(this, _1, _2)
        exitm<image.SetStatus(eax)>
        }

    .operator FromHBITMAP :HBITMAP, :HPALETTE {
        mov image,this
        xchg this,_2
        xchg _1,this
        GdipCreateBitmapFromHBITMAP(this, _1, _2)
        exitm<image.SetStatus(eax)>
        }

    .operator FromHICON :HICON {
        mov image,this
        xchg this,_1
        GdipCreateBitmapFromHICON(this, _1)
        exitm<image.SetStatus(eax)>
        }

    .operator FromResource :HINSTANCE, :ptr WCHAR {
        mov image,this
        xchg this,_2
        xchg _1,this
        GdipCreateBitmapFromResource(this, _1, _2)
        exitm<image.SetStatus(eax)>
        }

    .operator CloneI :int_t, :int_t, :int_t, :int_t, :PixelFormat {

        .new gpdstBitmap:ptr Bitmap

        mov r11,this
        mov ecx,_1
        mov edx,_2
        mov r8d,_3
        mov r9d,_4
        mov r10d,_5
        mov gpdstBitmap,NULL

        .if GdipCloneBitmapAreaI(ecx, edx, r8d, r9d, r10d, [r11].Image.nativeImage, &gpdstBitmap) == Ok

            .if Bitmap()

                mov rdx,gpdstBitmap
                mov [rax].Image.nativeImage,rdx
                mov [rax].Image.lastResult,Ok

            .else

                GdipDisposeImage(gpdstBitmap)
                xor eax,eax
            .endif
        .endif
        retm <rax>
        }

    .operator Clone1 :ptr Rect, :PixelFormat {
        exitm<[this].Bitmap.CloneI([_1].Rect.X, [_1].Rect.Y, [_1].Rect.Width, [_1].Rect.Height, _2)>
        }

    .operator CloneF :REAL, :REAL, :REAL, :REAL, :PixelFormat {

        .new gpdstBitmap:ptr Bitmap

        movaps xmm0,_1
        movaps xmm1,_2
        movaps xmm2,_3
        movaps xmm3,_4
        mov r10d,_5
        mov gpdstBitmap,NULL

        .if GdipCloneBitmapArea(xmm0, xmm1, xmm2, xmm3, r10d, [this].Image.nativeImage, &gpdstBitmap) == Ok

            .if Bitmap()

                mov rdx,gpdstBitmap
                mov [rax].Image.nativeImage,rdx
                mov [rax].Image.lastResult,Ok

            .else

                GdipDisposeImage(gpdstBitmap)
                xor eax,eax
            .endif
        .endif
        retm <rax>
        }

    .operator Clone2 :ptr RectF, :PixelFormat {
        exitm<[this].Bitmap.CloneF([_1].RectF.X, [_1].RectF.Y, [_1].RectF.Width, [_1].RectF.Height, _2)>
        }

    .operator LockBits :ptr Rect, :UINT, :PixelFormat, :ptr BitmapData {
        mov image,this
        GdipBitmapLockBits([this].Image.nativeImage, _1, _2, _3, _4)
        exitm<image.SetStatus(eax)>
        }

    .operator UnlockBits :ptr BitmapData {
        mov image,this
        GdipBitmapUnlockBits([this].Image.nativeImage, _1)
        exitm<image.SetStatus(eax)>
        }

    .operator GetPixel :int_t, :int_t, :ptr Color {

        .new argb:ARGB
        .new color:ptr Color

        mov color,_3
        mov image,this
        GdipBitmapGetPixel([this].Image.nativeImage, _1, _2, &argb)
        image.SetStatus(eax)
        .if eax == Ok
            color.SetValue(argb)
            mov this,image
        .endif
        mov eax,[this].Image.lastResult
        retm <eax>
        }

    .operator SetPixel :int_t, :int_t, :ptr Color {
        mov image,this
        GdipBitmapSetPixel([this].Image.nativeImage, _1, _2, [_3].Color.Argb)
        exitm<image.SetStatus(eax)>
        }

if (GDIPVER GE 0x0110)
    .operator ConvertFormat :PixelFormat, :DitherType, :PaletteType, :ptr ColorPalette, :REAL {
        mov image,this
        GdipBitmapConvertFormat([this].Image.nativeImage, _1, _2, _3, _4, _5)
        exitm<image.SetStatus(eax)>
        }

    ;; The palette must be allocated and count must be set to the number of
    ;; entries in the palette. If there are not enough, the API will fail.

    .operator InitializePalette :ptr ColorPalette,  ;; Palette to initialize.
                                :PaletteType,       ;; palette enumeration type.
                                :int_t,             ;; how many optimal colors
                                :BOOL,              ;; add a transparent color to the palette.
                                :ptr Bitmap {       ;; optional bitmap for median cut.
        mov image,this
        mov this,_1
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_4
        mov r10,_5
        .if r10
            mov r10,[r10].Image.nativeImage
        .endif
        GdipInitializePalette(this, edx, r8d, r9d, r10)
        exitm<image.SetStatus(eax)>
        }

    .operator ApplyEffect :ptr Effect, :ptr RECT {

        .new effect:ptr Effect
        .new ROI:ptr RECT

        mov image,this
        mov effect,_1
        mov ROI,_2

        .if [_1].Effect.auxData

            GdipFree([_1].Effect.auxData)
            mov _1,effect
            mov [_1].Effect.auxData,NULL
            mov [_1].Effect.auxDataSize,0
            mov this,image
        .endif
        GdipBitmapApplyEffect([this].Image.nativeImage, [_1].Effect.nativeEffect, ROI,\
                [_1].Effect.useAuxData, &[_1].Effect.auxData,  &[_1].Effect.auxDataSize)
        retm <eax>
        }

    .operator ApplyEffect2  :ptr ptr Bitmap,
                            :int_t,
                            :ptr Effect,
                            :ptr RECT,      ;; optional parameter.
                            :ptr RECT,      ;; optional parameter.
                            :ptr ptr Bitmap {

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
            .if ((eax == Ok) && outputNative)
                .if Bitmap() == NULL

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
        retm <eax>
        }

    .operator GetHistogram :HistogramFormat, :UINT, :ptr UINT, :ptr UINT, :ptr UINT, :ptr UINT {
        exitm<GdipBitmapGetHistogram([this].Image.nativeImage, _1, _2, _3, _4, _5, _6)>
        }

    .operator GetHistogramSize :HistogramFormat, :ptr UINT {
        mov ecx,edx
        exitm<GdipBitmapGetHistogramSize(ecx, _2)>
        }
endif

    .operator SetResolution :REAL, :REAL {
        mov image,this
        GdipBitmapSetResolution([this].Image.nativeImage, _1, _2)
        exitm<image.SetStatus(eax)>
        }

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


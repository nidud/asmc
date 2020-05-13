ifndef _GDIPLUSBRUSH_H
_GDIPLUSBRUSH_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Abstract base class for various brush types
;;--------------------------------------------------------------------------

.template Brush

    nativeBrush ptr_t ?
    lastResult  Status ?
    memState    Status ?

    .operator Brush {

        .new brush:ptr Brush

        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !GdipAlloc(Brush)
                mov [rax].Brush.memState,Ok
            .else
                mov [rax].Brush.memState,NotImplemented
            .endif
            mov [rax].Brush.nativeBrush,NULL
            mov [rax].Brush.lastResult,NotImplemented
        .until 1
        retm<rax>
        }

    .operator Release {

        mov brush,this

        GdipDeleteBrush([this].Brush.nativeBrush)

        mov this,brush
        .if [this].Brush.memState != NotImplemented

            GdipFree(this)
        .endif
        exitm<>
        }

    .operator SetNativeBrush :ptr Brush {
        mov [this].Brush.nativeBrush,_1
        exitm<>
        }

    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].Brush.lastResult,eax
        .endif
        retm <eax>
        }

    .operator GetStatus {
        mov eax,[this].Brush.lastResult
        retm<eax>
        }

    .operator Clone {

        .new clone:ptr Brush

        mov brush,this
        mov clone,Brush()
        .if rax
            mov this,brush
            GdipCloneBrush([this].Brush.nativeBrush, &[rax].Brush.nativeBrush)
            brush.SetStatus(eax)
            clone.SetStatus(eax)
            mov rax,clone
        .endif
        retm<rax>
        }

    .operator GetType {

        .new type:BrushType

        mov type,-1
        mov brush,this

        GdipGetBrushType([this].Brush.nativeBrush, &type)
        brush.SetStatus(eax)

        mov eax,type
        retm<eax>
        }

    .operator GetLastStatus {
        mov eax,[this].Brush.lastResult
        mov [this].Brush.lastResult,Ok
        retm<eax>
        }
    .ends
    GpBrush typedef Brush

BRUSH_OPERATOR macro class
    &class&_Brush macro this
        exitm<Brush_Brush(this)>
        endm
    &class&_Release macro this
        exitm<Brush_Release(this)>
        endm
    &class&_SetNativeBrush macro this, _1
        exitm<Brush_SetNativeBrush(this, _1)>
        endm
    &class&_SetStatus macro this, _1
        exitm<Brush_SetStatus(this, _1)>
        endm
    &class&_GetStatus macro this
        exitm<Brush_GetStatus(this)>
        endm
    &class&_Clone macro this
        exitm<Brush_Clone(this)>
        endm
    &class&_GetType macro this
        exitm<Brush_GetType(this)>
        endm
    &class&_GetLastStatus macro this
        exitm<Brush_GetLastStatus(this)>
        endm
    exitm<>
    endm

;;--------------------------------------------------------------------------
;; Solid Fill Brush Object
;;--------------------------------------------------------------------------

.template SolidBrush : public Brush

    BRUSH_OPERATOR(SolidBrush)

    .operator SolidBrush :ARGB {

        .new argb:ARGB

        mov argb,_1
        .if Brush_Brush(this)

            mov brush,rax
            GdipCreateSolidFill(argb, rax)
            brush.SetStatus(eax)
            mov rax,this
        .endif
        retm <rax>
        }

    .operator GetColor :ptr ARGB {
        mov brush,this
        .if _1 == NULL
            mov eax,InvalidParameter
        .else
            GdipGetSolidFillColor([this].Brush.nativeBrush, _1)
        .endif
        exitm<brush.SetStatus(eax)>
        }

    .operator SetColor :ARGB {
        mov brush,this
        GdipSetSolidFillColor([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }
    .ends

;;--------------------------------------------------------------------------
;; Texture Brush Fill Object
;;--------------------------------------------------------------------------

.template TextureBrush : public Brush

    BRUSH_OPERATOR(TextureBrush)

    .operator TextureBrush {
        exitm<Brush_Brush(this)>
        }

    .operator Create :ptr Image, :WrapMode {
        mov brush,this
        mov [this].Brush.nativeBrush,NULL
        mov rax,_1
        mov edx,_2
        GdipCreateTexture([rax].Image.nativeImage, edx, &[this].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    ;; When creating a texture brush from a metafile image, the dstRect
    ;; is used to specify the size that the metafile image should be
    ;; rendered at in the device units of the destination graphics.
    ;; It is NOT used to crop the metafile image, so only the width
    ;; and height values matter for metafiles.

    .operator CreateIA :ptr Image, :ptr RectF, :ptr ImageAttributes {
        mov brush,this
        mov [this].Brush.nativeBrush,NULL
        mov r10,this
        mov this,[_1].Image.nativeImage
        xor _1,_1
        .if _3
            mov _1,[_3].ImageAttributes.nativeImageAttr
        .endif
        GdipCreateTextureIA(this, _1, [_2].RectF.X, [_2].RectF.Y, \
                [_2].RectF.Width, [_2].RectF.Height, &[r10].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator CreateIAI :ptr Image, :ptr Rect, :ptr ImageAttributes {
        mov brush,this
        mov [this].Brush.nativeBrush,NULL
        mov r10,this
        mov this,[_1].Image.nativeImage
        xor _1,_1
        .if _3
            mov _1,[_3].ImageAttributes.nativeImageAttr
        .endif
        GdipCreateTextureIAI(this, _1, [_2].RectF.X, [_2].RectF.Y, \
                [_2].RectF.Width, [_2].RectF.Height, &[r10].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator Create2 :ptr Image, :WrapMode, :REAL, :REAL, :REAL, :REAL {
        mov brush,this
        mov [this].Brush.nativeBrush,NULL
        mov r10,this
        mov rcx,_1
        mov edx,_2
        GdipCreateTexture2([rcx].Image.nativeImage, edx, _3, _4, _5, _6, &[r10].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator Create2I :ptr Image, :WrapMode, :int_t, :int_t, :int_t, :int_t {
        mov brush,this
        mov [this].Brush.nativeBrush,NULL
        mov r10,this
        mov rcx,_1
        mov edx,_2
        mov r8d,_3
        GdipCreateTexture2I([rcx].Image.nativeImage, edx, r8d, _4, _5, _6, &[r10].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator Create2R :ptr Image, :WrapMode, :ptr RectF {
        exitm<[this].TextureBrush.Create2(_1, _2, [_3].RectF.X, [_3].RectF.Y, [_3].RectF.Width, [_3].RectF.Height)>
        }
    .operator Create2IR :ptr Image, :WrapMode, :ptr Rect {
        exitm<[this].TextureBrush.Create2I(_1, _2, [_3].Rect.X, [_3].Rect.Y, [_3].Rect.Width, [_3].Rect.Height)>
        }

    .operator SetTransform :ptr Matrix {
        mov brush,this
        GdipSetTextureTransform([this].Brush.nativeBrush, [_1].Matrix.nativeMatrix)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetTransform :ptr Matrix {
        mov brush,this
        GdipGetTextureTransform([this].Brush.nativeBrush, [_1].Matrix.nativeMatrix)
        exitm<brush.SetStatus(eax)>
        }

    .operator ResetTransform {
        mov brush,this
        GdipResetTextureTransform([this].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator MultiplyTransform :ptr Matrix, :MatrixOrder {
        mov brush,this
        GdipMultiplyTextureTransform([this].Brush.nativeBrush, [_1].Matrix.nativeMatrix, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator TranslateTransform :REAL, :REAL, :MatrixOrder {
        mov brush,this
        GdipTranslateTextureTransform([this].Brush.nativeBrush, _1, _2, _3)
        exitm<brush.SetStatus(eax)>
        }

    .operator ScaleTransform :REAL, :REAL, :MatrixOrder {
        mov brush,this
        GdipScaleTextureTransform([this].Brush.nativeBrush, _1, _2, _3)
        exitm<brush.SetStatus(eax)>
        }

    .operator RotateTransform :REAL, :MatrixOrder {
        mov brush,this
        GdipRotateTextureTransform([this].Brush.nativeBrush, _1, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetWrapMode :WrapMode {
        mov brush,this
        GdipSetTextureWrapMode([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetWrapMode {

        .new wrapMode:WrapMode

        mov brush,this
        GdipGetTextureWrapMode([this].Brush.nativeBrush, &wrapMode)
        brush.SetStatus(eax)
        mov eax,wrapMode
        retm<eax>
        }

    .operator GetImage {

        .new image:ptr Image

        mov brush,this
        .if Image()

            mov this,brush
            mov image,rax
            GdipGetTextureImage([this].Brush.nativeBrush, rax)
            image.SetStatus(eax)
            mov rax,this
        .endif
        retm <rax>
        }
    .ends

;;--------------------------------------------------------------------------
;; Linear Gradient Brush Object
;;--------------------------------------------------------------------------

.template LinearGradientBrush : public Brush

    BRUSH_OPERATOR(LinearGradientBrush)

    .operator LinearGradientBrush {
        exitm<Brush_Brush(this)>
        }

    .operator Create :ptr PointF, :ptr PointF, :ARGB, :ARGB {
        mov brush,this
        mov rax,this
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        mov r9d,_4
        GdipCreateLineBrush(rcx, rdx, r8d, r9d, WrapModeTile, &[rax].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator CreateI :ptr Point, :ptr Point, :ARGB, :ARGB {
        mov brush,this
        mov rax,this
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        mov r9d,_4
        GdipCreateLineBrushI(rcx, rdx, r8d, r9d, WrapModeTile, &[rax].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator CreateFromRect :ptr RectF, :ARGB, :ARGB, :LinearGradientMode {
        mov brush,this
        mov rax,this
        mov rcx,rdx
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_4
        GdipCreateLineBrushFromRect(rcx, edx, r8d, r9d, WrapModeTile, &[rax].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator CreateFromRectI :ptr Rect, :ARGB, :ARGB, :LinearGradientMode {
        mov brush,this
        mov rax,this
        mov rcx,rdx
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_4
        GdipCreateLineBrushFromRectI(rcx, edx, r8d, r9d, WrapModeTile, &[rax].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator CreateFromRectWithAngle :ptr RectF, :ARGB, :ARGB, :REAL, :BOOL {
        mov brush,this
        mov rax,this
        mov rcx,rdx
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_5
        GdipCreateLineBrushFromRectWithAngle(rcx, edx, r8d, _4, r9d, WrapModeTile, rax)
        exitm<brush.SetStatus(eax)>
        }

    .operator CreateFromRectWithAngleI :ptr Rect, :ARGB, :ARGB, :REAL, :BOOL {
        mov brush,this
        mov rax,this
        mov rcx,rdx
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_5
        GdipCreateLineBrushFromRectWithAngleI(rcx, edx, r8d, _4, r9d, WrapModeTile, rax)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetLinearColors :ARGB, :ARGB {
        mov brush,this
        GdipSetLineColors([this].Brush.nativeBrush, _1, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetLinearColors :ptr ARGB {
        mov brush,this
        .if _1 == NULL
            mov eax,InvalidParameter
        .else
            GdipGetLineColors([this].Brush.nativeBrush, _1)
        .endif
        exitm<brush.SetStatus(eax)>
        }

    .operator GetRectangle :ptr RectF {
        mov brush,this
        GdipGetLineRect([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetRectangleI :ptr Rect {
        mov brush,this
        GdipGetLineRectI([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetGammaCorrection :BOOL {
        mov brush,this
        GdipSetLineGammaCorrection([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetGammaCorrection {

        .new useGammaCorrection:BOOL

        mov brush,this
        GdipGetLineGammaCorrection([this].Brush.nativeBrush, &useGammaCorrection)
        brush.SetStatus(eax)
        mov eax,useGammaCorrection
        retm <eax>
        }

    .operator GetBlendCount {

        .new count:int_t

        mov brush,this
        mov count,0
        GdipGetLineBlendCount( [this].Brush.nativeBrush, &count )
        brush.SetStatus(eax)
        mov eax,count
        retm <eax>
        }

    .operator SetBlend :ptr REAL, :ptr REAL, :int_t {
        mov brush,this
        GdipSetLineBlend( [this].Brush.nativeBrush, _1, _2, _3 )
        exitm<brush.SetStatus(eax)>
        }

    .operator GetBlend :ptr REAL, :ptr REAL, :int_t {
        mov brush,this
        GdipGetLineBlend( [this].Brush.nativeBrush, _1, _2, _3 )
        exitm<brush.SetStatus(eax)>
        }

    .operator GetInterpolationColorCount {

        .new count:int_t

        mov brush,this
        mov count,0
        GdipGetLinePresetBlendCount( [this].Brush.nativeBrush, &count )
        brush.SetStatus(eax)

        mov eax,count
        retm <eax>
        }

    .operator SetInterpolationColors :ptr ARGB, :ptr REAL, :int_t {
        mov brush,this
        .ifs _3 <= 0 || !_1
            mov eax,InvalidParameter
        .else
            GdipSetLinePresetBlend([this].Brush.nativeBrush, _1, _2, _3)
        .endif
        exitm<brush.SetStatus(eax)>
        }

    .operator GetInterpolationColors :ptr ARGB, :ptr REAL, :int_t {
        mov brush,this
        .ifs _3 <= 0 || !_1
            mov eax,InvalidParameter
        .else
            GdipGetLinePresetBlend([this].Brush.nativeBrush, _1, _2, _3)
        .endif
        exitm<brush.SetStatus(eax)>
        }

    .operator SetBlendBellShape :REAL, :REAL {
        mov brush,this
        GdipSetLineSigmaBlend( [this].Brush.nativeBrush, _1, _2 )
        exitm<brush.SetStatus(eax)>
        }

    .operator SetBlendTriangularShape :REAL, :REAL {
        mov brush,this
        GdipSetLineLinearBlend( [this].Brush.nativeBrush, _1, _2 )
        exitm<brush.SetStatus(eax)>
        }

    .operator SetTransform :ptr Matrix {
        mov brush,this
        GdipSetLineTransform( [this].Brush.nativeBrush, [_1].Matrix.nativeMatrix )
        exitm<brush.SetStatus(eax)>
        }

    .operator GetTransform :ptr Matrix {
        mov brush,this
        GdipGetLineTransform( [this].Brush.nativeBrush, [_1].Matrix.nativeMatrix )
        exitm<brush.SetStatus(eax)>
        }

    .operator ResetTransform {
        mov brush,this
        GdipResetLineTransform( [this].Brush.nativeBrush )
        exitm<brush.SetStatus(eax)>
        }

    .operator MultiplyTransform :ptr Matrix, :MatrixOrder {
        mov brush,this
        GdipMultiplyLineTransform( [this].Brush.nativeBrush, [_1].Matrix.nativeMatrix, _2 )
        exitm<brush.SetStatus(eax)>
        }

    .operator TranslateTransform :REAL, :REAL, :MatrixOrder {
        mov brush,this
        GdipTranslateLineTransform( [this].Brush.nativeBrush, _1, _2, _3 )
        exitm<brush.SetStatus(eax)>
        }

    .operator ScaleTransform :REAL, :REAL, :MatrixOrder {
        mov brush,this
        GdipScaleLineTransform( [this].Brush.nativeBrush, _1, _2, _3 )
        exitm<brush.SetStatus(eax)>
        }

    .operator RotateTransform :REAL, :MatrixOrder {
        mov brush,this
        GdipRotateLineTransform( [this].Brush.nativeBrush, _1, _2 )
        exitm<brush.SetStatus(eax)>
        }

    .operator SetWrapMode :WrapMode {
        mov brush,this
        GdipSetLineWrapMode( [this].Brush.nativeBrush, _1 )
        exitm<brush.SetStatus(eax)>
        }

    .operator GetWrapMode {

        .new wrapMode:WrapMode

        mov brush,this
        GdipGetLineWrapMode( [this].Brush.nativeBrush, &wrapMode )
        brush.SetStatus(eax)
        mov eax,wrapMode
        retm <eax>
        }
    .ends


;;--------------------------------------------------------------------------
;; PathGradientBrush object is defined
;; in gdipluspath.h.
;;--------------------------------------------------------------------------

;;--------------------------------------------------------------------------
;; Hatch Brush Object
;;--------------------------------------------------------------------------

.template HatchBrush : public Brush

    BRUSH_OPERATOR(HatchBrush)

    .operator HatchBrush :abs, :abs, :abs {

        .if Brush_Brush(this)

            mov brush,rax
            GdipCreateHatchBrush(_1, _2, _3, &[rax].Brush.nativeBrush)
            brush.SetStatus(eax)
            mov rax,this
        .endif
        retm <rax>
        }

    .operator GetHatchStyle {

        .new hatchstyle:HatchStyle

        mov brush,this
        GdipGetHatchStyle([this].Brush.nativeBrush, &hatchstyle)
        brush.SetStatus(eax)

        mov eax,hatchstyle
        retm <eax>
        }

    .operator GetForegroundColor :ptr Color {

        mov brush,this

        .if _1 == NULL

            brush.SetStatus(InvalidParameter)

        .else

            .new argb:ARGB
            .new color:ptr Color
            .new status:Status

            mov color,_1
            mov status,GdipGetHatchForegroundColor( [this].Brush.nativeBrush, &argb )
            color.SetValue(argb)
            brush.SetStatus(status)

        .endif

        retm <eax>
        }

    .operator GetBackgroundColor :ptr Color {

        mov brush,this

        .if _1 == NULL

            brush.SetStatus(InvalidParameter)

        .else

            .new argb:ARGB
            .new color:ptr Color
            .new status:Status

            mov color,_1
            mov status,GdipGetHatchBackgroundColor( [this].Brush.nativeBrush, &argb )
            color.SetValue(argb)
            brush.SetStatus(status)

        .endif

        retm <eax>
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

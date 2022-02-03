ifndef _GDIPLUSBRUSH_H
define _GDIPLUSBRUSH_H
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Abstract base class for various brush types
;;--------------------------------------------------------------------------

.template Brush fastcall

    nativeBrush ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .static Brush {
        mov this.nativeBrush,NULL
        mov this.lastResult,NotImplemented
        }

    .static Release {
        GdipDeleteBrush(this.nativeBrush)
        }
    .static SetNativeBrush :ptr Brush {
        mov this.nativeBrush,_1
        }
    .static SetStatus watcall :size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }
    .static GetStatus {
        mov eax,this.lastResult
        }
    .static Clone :ptr Brush {
        GdipCloneBrush(this.nativeBrush, &[_1].Brush.nativeBrush)
        }
    .static GetType {
        mov this.scratch,-1
        this.SetStatus(GdipGetBrushType(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .ends
    GpBrush typedef Brush


;;--------------------------------------------------------------------------
;; Solid Fill Brush Object
;;
;; SolidBrush(ARGB)
;;
;;--------------------------------------------------------------------------

.template SolidBrush fastcall : public Brush

    .static SolidBrush :abs {
        GdipCreateSolidFill(_1, addr this.nativeBrush)
        mov this.lastResult,eax
        }
    .static GetColor :ptr ARGB {
        mov eax,InvalidParameter
        .if _1
            GdipGetSolidFillColor(this.nativeBrush, _1)
        .endif
        this.SetStatus()
        }
    .static SetColor :abs {
        this.SetStatus(GdipSetSolidFillColor(this.nativeBrush, _1))
        }
    .ends

;;--------------------------------------------------------------------------
;; Texture Brush Fill Object
;;
;; TextureBrush(Image*, WrapMode = WrapModeTile)
;; TextureBrush(Image*, WrapMode, RectF&)
;; TextureBrush(Image*, RectF&, ImageAttributes * = NULL)
;; TextureBrush(Image*, Rect&, ImageAttributes * = NULL)
;; TextureBrush(Image*, WrapMode, Rect&)
;; TextureBrush(Image*, WrapMode, REAL, REAL, REAL, REAL)
;; TextureBrush(Image*, WrapMode, INT, INT, INT, INT)
;;
;;--------------------------------------------------------------------------

.template TextureBrush fastcall : public Brush

    ;; When creating a texture brush from a metafile image, the dstRect
    ;; is used to specify the size that the metafile image should be
    ;; rendered at in the device units of the destination graphics.
    ;; It is NOT used to crop the metafile image, so only the width
    ;; and height values matter for metafiles.

    .static TextureBrush :ptr Image, :abs=<WrapModeTile>, :abs=<NULL>, :abs, :abs, :abs {
        mov this.nativeBrush,NULL
      ifidn <ptrRect>,typeid(_2)
        .err <_2>
      elseifidn <ptrRectF>,typeid(_2)
        .err <_2>
      elseifidn <ptrRect>,typeid(_3)
        .err <_3>
      elseifidn <ptrRectF>,typeid(_3)
        .err <_3>
      elseifidn <Rect>,typeid(_2)
        .if LOADARGPTRDX(_3)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipCreateTextureIAI([rcx].Image.nativeImage, rdx, _2.X, _2.Y, _2.Width, _2.Height, addr this.nativeBrush)
      elseifidn <RectF>,typeid(_2)
        .if LOADARGPTRDX(_3)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipCreateTextureIA([rcx].Image.nativeImage, rdx, _2.X, _2.Y, _2.Width, _2.Height, addr this.nativeBrush)
      elseifidn <Rect>,typeid(_3)
        GdipCreateTexture2I([rcx].Image.nativeImage, _2, _3.X, _3.Y, _3.Width, _3.Height, addr this.nativeBrush)
      elseifidn <RectF>,typeid(_3)
        GdipCreateTexture2([rcx].Image.nativeImage, _2, _3.X, _3.Y, _3.Width, _3.Height, addr this.nativeBrush)
      elseifb <_4>
        GdipCreateTexture([_1].Image.nativeImage, _2, addr this.nativeBrush)
      elseifidn <flt>,typeid(_3)
        GdipCreateTexture2([rcx].Image.nativeImage, _2, _3, _4, _5, _6, addr this.nativeBrush)
      elseifidn <real4>,typeid(_3)
        GdipCreateTexture2([rcx].Image.nativeImage, _2, _3, _4, _5, _6, addr this.nativeBrush)
      elseifidn <oword>,typeid(_3)
        GdipCreateTexture2([rcx].Image.nativeImage, _2, _3, _4, _5, _6, addr this.nativeBrush)
      else
        GdipCreateTexture2I([rcx].Image.nativeImage, _2, _3, _4, _5, _6, addr this.nativeBrush)
      endif
        mov this.lastResult,eax
        }


    .static SetTransform :ptr Matrix {
        this.SetStatus(GdipSetTextureTransform(this.nativeBrush, [_1].Matrix.nativeMatrix))
        }
    .static GetTransform :ptr Matrix {
        this.SetStatus(GdipGetTextureTransform(this.nativeBrush, [_1].Matrix.nativeMatrix))
        }
    .static ResetTransform {
        this.SetStatus(GdipResetTextureTransform(this.nativeBrush))
        }
    .static MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipMultiplyTextureTransform(this.nativeBrush, [_1].Matrix.nativeMatrix, _2))
        }
    .static TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipTranslateTextureTransform(this.nativeBrush, _1, _2, _3))
        }
    .static ScaleTransform :abs, :abs, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipScaleTextureTransform(this.nativeBrush, _1, _2, _3))
        }
    .static RotateTransform :abs, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipRotateTextureTransform(this.nativeBrush, _1, _2))
        }
    .static SetWrapMode :abs {
        this.SetStatus(GdipSetTextureWrapMode(this.nativeBrush, _1))
        }
    .static GetWrapMode {
        this.SetStatus(GdipGetTextureWrapMode(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetImage :abs {
        this.SetStatus(GdipGetTextureImage(this.nativeBrush, addr _1))
        lea rax,_1
        }
    .ends

;;--------------------------------------------------------------------------
;; Linear Gradient Brush Object
;;
;; LinearGradientBrush(PointF&, PointF&, ARGB, ARGB)
;; LinearGradientBrush(Point&, Point&, ARGB, ARGB)
;; LinearGradientBrush(RectF&, ARGB, ARGB, LinearGradientMode)
;; LinearGradientBrush(Rect&, ARGB, ARGB, LinearGradientMode)
;; LinearGradientBrush(RectF&, ARGB, ARGB, REAL, BOOL isAngleScalable = FALSE)
;; LinearGradientBrush(Rect&, ARGB, ARGB, REAL, BOOL isAngleScalable = FALSE)
;;
;;--------------------------------------------------------------------------

.template LinearGradientBrush fastcall : public Brush

    .static LinearGradientBrush :abs, :abs, :abs, :abs, :abs=<FALSE> {
      ifidn <PointF>,typeid(_1)
        GdipCreateLineBrush(addr _1, addr _2, _3, _4, WrapModeTile, addr this.nativeBrush)
      elseifidn <Point>,typeid(_1)
        GdipCreateLineBrushI(addr _1, addr _2, _3, _4, WrapModeTile, addr this.nativeBrush)
      elseifidn <RectF>,typeid(_1)
       ifidn <imm>,typeid(_4)
        GdipCreateLineBrushFromRect(addr _1, _2, _3, _4, WrapModeTile, addr this.nativeBrush)
       else
        GdipCreateLineBrushFromRectWithAngle(addr _1, _2, _3, _4, _5, WrapModeTile, addr this.nativeBrush)
       endif
      elseifidn <Rect>,typeid(_1)
       ifidn <imm>,typeid(_4)
        GdipCreateLineBrushFromRect(addr _1, _2, _3, _4, WrapModeTile, addr this.nativeBrush)
       else
        GdipCreateLineBrushFromRectWithAngle(addr _1, _2, _3, _4, _5, WrapModeTile, addr this.nativeBrush)
       endif
      else
        .err <_1>
      endif
        mov this.lastResult,eax
        }

    .static SetLinearColors :abs, :abs {
        this.SetStatus(GdipSetLineColors(this.nativeBrush, _1, _2))
        }
    .static GetLinearColors :ptr ARGB {
        mov eax,InvalidParameter
        .if _1
            GdipGetLineColors(this.nativeBrush, _1)
        .endif
        this.SetStatus()
        }

    ; GetRectangle(RectF* rect)
    ; GetRectangle(Rect* rect)

    .static GetRectangle :abs {
      ifidn <ptrRectF>,typeid(_1)
        this.SetStatus(GdipGetLineRect(this.nativeBrush, _1))
      elseifidn <ptrRect>,typeid(_1)
        this.SetStatus(GdipGetLineRectI(this.nativeBrush, _1))
      else
        .err <_1>
      endif
        }

    .static SetGammaCorrection useGammaCorrection:abs {
        this.SetStatus(GdipSetLineGammaCorrection(this.nativeBrush, useGammaCorrection))
        }
    .static GetGammaCorrection {
        this.SetStatus(GdipGetLineGammaCorrection(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetBlendCount {
        mov this.scratch,0
        this.SetStatus(GdipGetLineBlendCount(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetBlend blendFactors:abs, blendPositions:abs, count:abs {
        this.SetStatus(GdipSetLineBlend(this.nativeBrush, blendFactors, blendPositions, count))
        }
    .static GetBlend blendFactors:abs, blendPositions:abs, count:abs {
        this.SetStatus(GdipGetLineBlend(this.nativeBrush, blendFactors, blendPositions, count))
        }
    .static GetInterpolationColorCount {
        mov this.scratch,0
        this.SetStatus(GdipGetLinePresetBlendCount(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetInterpolationColors :ptr ARGB, :abs, :abs {
        mov eax,_3
        .ifs !( eax <= 0 || !_1 )
            GdipSetLinePresetBlend(this.nativeBrush, _1, _2, eax)
        .else
            mov eax,InvalidParameter
        .endif
        this.SetStatus()
        }
    .static GetInterpolationColors :ptr ARGB, :abs, :abs {
        mov eax,_3
        .ifs !( eax <= 0 || !_1 )
            GdipGetLinePresetBlend(this.nativeBrush, _1, _2, _3)
        .else
            mov eax,InvalidParameter
        .endif
        this.SetStatus()
        }
    .static SetBlendBellShape :abs, :abs=<1.0> {
        this.SetStatus(GdipSetLineSigmaBlend(this.nativeBrush, _1, _2))
        }
    .static SetBlendTriangularShape :abs, :abs=<1.0> {
        this.SetStatus(GdipSetLineLinearBlend(this.nativeBrush, _1, _2))
        }
    .static SetTransform :ptr Matrix {
        this.SetStatus(GdipSetLineTransform(this.nativeBrush, [_1].Matrix.nativeMatrix))
        }
    .static GetTransform :ptr Matrix {
        this.SetStatus(GdipGetLineTransform(this.nativeBrush, [_1].Matrix.nativeMatrix))
        }
    .static ResetTransform {
        this.SetStatus(GdipResetLineTransform(this.nativeBrush))
        }
    .static MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipMultiplyLineTransform(this.nativeBrush, [_1].Matrix.nativeMatrix, _2))
        }
    .static TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipTranslateLineTransform(this.nativeBrush, _1, _2, _3))
        }
    .static ScaleTransform :abs, :abs, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipScaleLineTransform(this.nativeBrush, _1, _2, _3))
        }
    .static RotateTransform :abs, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipRotateLineTransform(this.nativeBrush, _1, _2))
        }
    .static SetWrapMode :abs {
        this.SetStatus(GdipSetLineWrapMode(this.nativeBrush, _1))
        }
    .static GetWrapMode {
        this.SetStatus(GdipGetLineWrapMode(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }
    .ends


;;--------------------------------------------------------------------------
;; PathGradientBrush object is defined
;; in gdipluspath.h.
;;--------------------------------------------------------------------------

;;--------------------------------------------------------------------------
;; Hatch Brush Object
;;--------------------------------------------------------------------------

.template HatchBrush fastcall : public Brush

    ; HatchBrush(HatchStyle, foreColor:ARGB, backColor:ARGB)

    .static HatchBrush :abs, :abs, :abs {
        GdipCreateHatchBrush(_1, _2, _3, addr this.nativeBrush)
        }

    .static GetHatchStyle {
        this.SetStatus(GdipGetHatchStyle(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetForegroundColor :ptr ARGB{
        mov eax,InvalidParameter
        .if _1
            GdipGetHatchForegroundColor(this.nativeBrush, _1)
        .endif
        this.SetStatus()
        }

    .static GetBackgroundColor :ptr ARGB {
        mov eax,InvalidParameter
        .if _1
            GdipGetHatchBackgroundColor(this.nativeBrush, _1)
        .endif
        this.SetStatus()
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

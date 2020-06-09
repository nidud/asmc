ifndef _GDIPLUSBRUSH_H
_GDIPLUSBRUSH_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Abstract base class for various brush types
;;--------------------------------------------------------------------------

BRUSH_OPERATOR macro class
    .operator Release :vararg {
        GdipDeleteBrush(this.nativeBrush)
        }
    .operator SetNativeBrush :ptr Brush, :vararg {
        mov this.nativeBrush,rdx
        }
    .operator SetStatus :abs=<eax>, :vararg {
        ifdif <_1>,<eax>
            mov eax,_1
        endif
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }
    .operator GetStatus :vararg {
        mov eax,this.lastResult
        }
    .operator Clone :ptr Brush, :vararg {
        GdipCloneBrush(this.nativeBrush, &[rdx].Brush.nativeBrush)
        }
    .operator GetType :vararg {
        mov this.scratch,-1
        GdipGetBrushType(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .operator GetLastStatus :vararg {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    exitm<>
    endm

.template Brush

    nativeBrush ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    BRUSH_OPERATOR(Brush)

    .operator Brush :vararg {
        mov this.nativeBrush,NULL
        mov this.lastResult,NotImplemented
        lea rax,this
        }

    .ends
    GpBrush typedef Brush


;;--------------------------------------------------------------------------
;; Solid Fill Brush Object
;;
;; SolidBrush(ARGB)
;;
;;--------------------------------------------------------------------------

.template SolidBrush

    nativeBrush ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    BRUSH_OPERATOR(SolidBrush)

    .operator SolidBrush :abs, :vararg {
        GdipCreateSolidFill(_1, addr this.nativeBrush)
        mov this.lastResult,eax
        }

    .operator GetColor :ptr ARGB, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetSolidFillColor(this.nativeBrush, rdx)
        .endif
        GdipSetStatus(this)
        }

    .operator SetColor :abs, :vararg {
        GdipSetSolidFillColor(this.nativeBrush, _1)
        this.SetStatus()
        }
    .ends

;;--------------------------------------------------------------------------
;; Texture Brush Fill Object
;;
;; TextureBrush(Image*, WrapMode = WrapModeTile)
;; TextureBrush(Image*, WrapMode, RectF*)
;; TextureBrush(Image*, RectF*, ImageAttributes * = NULL)
;; TextureBrush(Image*, Rect*, ImageAttributes * = NULL)
;; TextureBrush(Image*, WrapMode, Rect*)
;; TextureBrush(Image*, WrapMode, REAL, REAL, REAL, REAL)
;; TextureBrush(Image*, WrapMode, INT, INT, INT, INT)
;;
;;--------------------------------------------------------------------------

.template TextureBrush

    nativeBrush ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    BRUSH_OPERATOR(TextureBrush)

    .operator TextureBrush :ptr Image, :abs=<WrapModeTile>, :abs, :vararg {
        mov this.nativeBrush,NULL
        mov rcx,rdx
        ifnb <_3>
            this.typeid(TextureBrush, _2)(rdx, _2, _3, _4)
        else
            GdipCreateTexture([rcx].Image.nativeImage, _2, addr this.nativeBrush)
        endif
        mov this.lastResult,eax
        }

    ;; When creating a texture brush from a metafile image, the dstRect
    ;; is used to specify the size that the metafile image should be
    ;; rendered at in the device units of the destination graphics.
    ;; It is NOT used to crop the metafile image, so only the width
    ;; and height values matter for metafiles.

    .operator TextureBrush?pRectF :abs, :ptr RectF, :ptr ImageAttributes, :vararg {
        xor edx,edx
        .if r9
            mov rdx,[r9].ImageAttributes.nativeImageAttr
        .endif
        GdipCreateTextureIA([rcx].Image.nativeImage, rdx,\
                            [r8].RectF.X,\
                            [r8].RectF.Y,\
                            [r8].RectF.Width,\
                            [r8].RectF.Height,\
                            addr this.nativeBrush)
        }

    .operator TextureBrush?pRect :abs, :ptr Rect, :ptr ImageAttributes, :vararg {
        xor edx,edx
        .if r9
            mov rdx,[r9].ImageAttributes.nativeImageAttr
        .endif
        GdipCreateTextureIAI([rcx].Image.nativeImage, rdx,\
                            [r8].Rect.X,\
                            [r8].Rect.Y,\
                            [r8].Rect.Width,\
                            [r8].Rect.Height,\
                            addr this.nativeBrush)
        }

    .operator TextureBrush?i32 :abs, :abs, :abs, :vararg {
        this.typeid(TextureBrush?i32, _3)(_1, _2, _3, _4)
        }
    .operator TextureBrush?r32 :abs, :abs, :abs, :vararg {
        this.typeid(TextureBrush?i32, _3)(_1, _2, _3, _4)
        }
    .operator TextureBrush?sdword :abs, :abs, :abs, :vararg {
        this.typeid(TextureBrush?i32, _3)(_1, _2, _3, _4)
        }

    .operator TextureBrush?i32?flt :abs, :vararg {
        GdipCreateTexture2([rcx].Image.nativeImage, _2, addr this.nativeBrush)
        }
    .operator TextureBrush?i32?real4 :vararg {
        this.TextureBrush?i32?flt(_1)
        }
    .operator TextureBrush?i32?r128 :vararg {
        this.TextureBrush?i32?flt(_1)
        }

    .operator TextureBrush?i32?i32 :abs, :vararg {
        GdipCreateTexture2I([rcx].Image.nativeImage, _2, addr this.nativeBrush)
        }
    .operator TextureBrush?i32?sdword :vararg {
        this.TextureBrush?i32?i32(_1)
        }
    .operator TextureBrush?i32?r32 :vararg {
        this.TextureBrush?i32?i32(_1)
        }

    .operator TextureBrush?i32?pRectF :abs, :abs, :ptr RectF, :vararg {
        GdipCreateTexture2([rcx].Image.nativeImage, _2, [r9].RectF.X, [r9].RectF.Y, [r9].RectF.Width, [r9].RectF.Height, addr this.nativeBrush)
        }
    .operator TextureBrush?i32?pRect :abs, :abs, :ptr Rect, :vararg {
        mov r10,r9
        GdipCreateTexture2I([rcx].Image.nativeImage, _2, [r10].Rect.X, [r9].Rect.Y, [r9].Rect.Width, [r9].Rect.Height, addr this.nativeBrush)
        }

    .operator SetTransform :ptr Matrix, :vararg {
        GdipSetTextureTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .operator GetTransform :ptr Matrix, :vararg {
        GdipGetTextureTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .operator ResetTransform :vararg {
        GdipResetTextureTransform(this.nativeBrush)
        GdipSetStatus(this)
        }

    .operator MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend>, :vararg {
        GdipMultiplyTextureTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix, _2)
        GdipSetStatus(this)
        }

    .operator TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipTranslateTextureTransform(this.nativeBrush, _1, _2, _3)
        GdipSetStatus(this)
        }

    .operator ScaleTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipScaleTextureTransform(this.nativeBrush, _1, _2, _3)
        GdipSetStatus(this)
        }

    .operator RotateTransform :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipRotateTextureTransform(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .operator SetWrapMode :vararg {
        GdipSetTextureWrapMode(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetWrapMode :vararg {
        GdipGetTextureWrapMode(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetImage :abs, :vararg {
        GdipGetTextureImage(this.nativeBrush, addr _1)
        GdipSetStatus(_1)
        lea rax,_1
        }
    .ends

;;--------------------------------------------------------------------------
;; Linear Gradient Brush Object
;;
;; LinearGradientBrush(PointF*, PointF*, ARGB, ARGB)
;; LinearGradientBrush(Point*, Point*, ARGB, ARGB)
;; LinearGradientBrush(RectF*, ARGB, ARGB, LinearGradientMode)
;; LinearGradientBrush(Rect*, ARGB, ARGB, LinearGradientMode)
;; LinearGradientBrush(RectF*, ARGB, ARGB, REAL, BOOL isAngleScalable = FALSE)
;; LinearGradientBrush(Rect*, ARGB, ARGB, REAL, BOOL isAngleScalable = FALSE)
;;
;;--------------------------------------------------------------------------

.template LinearGradientBrush

    nativeBrush ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    BRUSH_OPERATOR(LinearGradientBrush)

    .operator LinearGradientBrush :abs, :vararg {
        this.typeid(LinearGradientBrush, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .operator LinearGradientBrush?pPointF :ptr PointF, :ptr PointF, :ARGB, :vararg {
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        GdipCreateLineBrush(rcx, rdx, r8d, _4, WrapModeTile, addr this.nativeBrush)
        }
    .operator LinearGradientBrush?pPoint :ptr Point, :ptr Point, :ARGB, :vararg {
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        GdipCreateLineBrushI(rcx, rdx, r8d, _4, WrapModeTile, addr this.nativeBrush)
        }
    .operator LinearGradientBrush?pRectF :abs, :abs, :abs, :abs, :vararg {
        this.typeid(LinearGradientBrush?pRectF, _4)(_1, _2, _3, _4, _5)
        }
    .operator LinearGradientBrush?pRect :abs, :abs, :abs, :abs, :vararg {
        this.typeid(LinearGradientBrush?pRect, _4)(_1, _2, _3, _4, _5)
        }
    .operator LinearGradientBrush?pRectF?i32 :ptr RectF, :ARGB, :ARGB, :vararg {
        mov rcx,rdx
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_4
        GdipCreateLineBrushFromRect(rcx, edx, r8d, r9d, WrapModeTile, addr this.nativeBrush)
        }
    .operator LinearGradientBrush?pRect?i32 :ptr Rect, :ARGB, :ARGB, :vararg {
        mov rcx,rdx
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_4
        GdipCreateLineBrushFromRectI(rcx, edx, r8d, r9d, WrapModeTile, addr this.nativeBrush)
        }
    .operator LinearGradientBrush?pRectF?flt :ptr RectF, :ARGB, :ARGB, :abs, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_5
        GdipCreateLineBrushFromRectWithAngle(rcx, edx, r8d, _4, r9d, WrapModeTile, addr this.nativeBrush)
        }
    .operator LinearGradientBrush?pRect?flt :ptr Rect, :ARGB, :ARGB, :abs, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        mov edx,r8d
        mov r8d,r9d
        mov r9d,_5
        GdipCreateLineBrushFromRectWithAngleI(rcx, edx, r8d, _4, r9d, WrapModeTile, addr this.nativeBrush)
        }

    .operator SetLinearColors :vararg {
        GdipSetLineColors(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetLinearColors :ptr ARGB, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetLineColors(this.nativeBrush, rdx)
        .endif
        GdipSetStatus(this)
        }

    .operator GetRectangle :abs, :vararg {
        this.typeid(GetRectangle, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator GetRectangle?pRectF :vararg {
        GdipGetLineRect(this.nativeBrush, _1)
        }
    .operator GetRectangle?pRect :vararg {
        GdipGetLineRectI(this.nativeBrush, _1)
        }

    .operator SetGammaCorrection :vararg {
        GdipSetLineGammaCorrection(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetGammaCorrection :vararg {
        GdipGetLineGammaCorrection(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetBlendCount :vararg {
        mov this.scratch,0
        GdipGetLineBlendCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetBlend :vararg {
        GdipSetLineBlend(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetBlend :vararg {
        GdipGetLineBlend(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetInterpolationColorCount :vararg {
        mov this.scratch,0
        GdipGetLinePresetBlendCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetInterpolationColors :ptr ARGB, :abs, :int_t, :vararg {
        mov eax,InvalidParameter
        .ifs !( r9d <= 0 || !rdx )
            GdipSetLinePresetBlend(this.nativeBrush, rdx, _2, r9d)
        .endif
        GdipSetStatus(this)
        }

    .operator GetInterpolationColors :ptr ARGB, :abs, :int_t, :vararg {
        mov eax,InvalidParameter
        .ifs !( r9d <= 0 || !rdx )
            GdipGetLinePresetBlend(this.nativeBrush, rdx, _2, r9d)
        .endif
        GdipSetStatus(this)
        }

    .operator SetBlendBellShape :abs, :abs=<1.0>, :vararg {
        GdipSetLineSigmaBlend(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .operator SetBlendTriangularShape :abs, :abs=<1.0>, :vararg {
        GdipSetLineLinearBlend(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .operator SetTransform :ptr Matrix, :vararg {
        GdipSetLineTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix )
        GdipSetStatus(this)
        }

    .operator GetTransform :ptr Matrix, :vararg {
        GdipGetLineTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix )
        GdipSetStatus(this)
        }

    .operator ResetTransform :vararg {
        GdipResetLineTransform(this.nativeBrush)
        GdipSetStatus(this)
        }

    .operator MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend>, :vararg {
        GdipMultiplyLineTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix, _2)
        GdipSetStatus(this)
        }

    .operator TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipTranslateLineTransform(this.nativeBrush, _1, _2, _3)
        GdipSetStatus(this)
        }

    .operator ScaleTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipScaleLineTransform(this.nativeBrush, _1, _2, _3)
        GdipSetStatus(this)
        }

    .operator RotateTransform :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipRotateLineTransform(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .operator SetWrapMode :vararg {
        GdipSetLineWrapMode(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetWrapMode :vararg {
        GdipGetLineWrapMode(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
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

.template HatchBrush

    nativeBrush ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    BRUSH_OPERATOR(HatchBrush)

    ; HatchBrush(HatchStyle, foreColor:ARGB, backColor:ARGB)

    .operator HatchBrush :vararg {
        GdipCreateHatchBrush(_1, addr this.nativeBrush)
        GdipSetStatus(this)
        }

    .operator GetHatchStyle :vararg {
        GdipGetHatchStyle(this.nativeBrush, addr this.scratch)
        mov this.lastResult,eax
        mov eax,this.scratch
        }

    .operator GetForegroundColor :ptr ARGB, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetHatchForegroundColor(this.nativeBrush, rdx)
        .endif
        GdipSetStatus(this)
        }

    .operator GetBackgroundColor :ptr ARGB, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetHatchBackgroundColor(this.nativeBrush, rdx)
        .endif
        GdipSetStatus(this)
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

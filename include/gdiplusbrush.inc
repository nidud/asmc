ifndef _GDIPLUSBRUSH_H
define _GDIPLUSBRUSH_H
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Abstract base class for various brush types
;;--------------------------------------------------------------------------

.template Brush

    nativeBrush ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .inline Brush :vararg {
        mov this.nativeBrush,NULL
        mov this.lastResult,NotImplemented
        lea rax,this
        }
    .inline Release :vararg {
        GdipDeleteBrush(this.nativeBrush)
        }
    .inline SetNativeBrush :ptr Brush, :vararg {
        mov this.nativeBrush,rdx
        }
    .inline SetStatus :abs=<eax>, :vararg {
        ifdif <_1>,<eax>
            mov eax,_1
        endif
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }
    .inline GetStatus :vararg {
        mov eax,this.lastResult
        }
    .inline Clone :ptr Brush, :vararg {
        GdipCloneBrush(this.nativeBrush, &[rdx].Brush.nativeBrush)
        }
    .inline GetType :vararg {
        mov this.scratch,-1
        GdipGetBrushType(this.nativeBrush, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline GetLastStatus :vararg {
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

.template SolidBrush : public Brush

    .inline SolidBrush :abs, :vararg {
        GdipCreateSolidFill(_1, addr this.nativeBrush)
        mov this.lastResult,eax
        }

    .inline GetColor :ptr ARGB, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetSolidFillColor(this.nativeBrush, rdx)
        .endif
        this.SetStatus()
        }

    .inline SetColor :abs, :vararg {
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

.template TextureBrush : public Brush

    .inline TextureBrush :ptr Image, :abs=<WrapModeTile>, :abs, :vararg {
        mov this.nativeBrush,NULL
        mov rcx,rdx
        ifnb <_3>
            this.typeid(TextureBrush_, _2)(rdx, _2, _3, _4)
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

    .inline TextureBrush_ptrRectF :abs, :ptr RectF, :ptr ImageAttributes, :vararg {
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

    .inline TextureBrush_ptrRect :abs, :ptr Rect, :ptr ImageAttributes, :vararg {
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

    .inline TextureBrush_imm :abs, :abs, :abs, :vararg {
        this.typeid(TextureBrush_imm_, _3)(_1, _2, _3, _4)
        }
    .inline TextureBrush_dword :abs, :abs, :abs, :vararg {
        this.typeid(TextureBrush_imm_, _3)(_1, _2, _3, _4)
        }
    .inline TextureBrush_sdword :abs, :abs, :abs, :vararg {
        this.typeid(TextureBrush_imm_, _3)(_1, _2, _3, _4)
        }

    .inline TextureBrush_imm_flt :abs, :vararg {
        GdipCreateTexture2([rcx].Image.nativeImage, _2, addr this.nativeBrush)
        }
    .inline TextureBrush_imm_real4 :vararg {
        this.TextureBrush_imm_flt(_1)
        }
    .inline TextureBrush_imm_oword :vararg {
        this.TextureBrush_imm_flt(_1)
        }

    .inline TextureBrush_imm_imm :abs, :vararg {
        GdipCreateTexture2I([rcx].Image.nativeImage, _2, addr this.nativeBrush)
        }
    .inline TextureBrush_imm_sdword :vararg {
        this.TextureBrush_imm_imm(_1)
        }
    .inline TextureBrush_imm_dword :vararg {
        this.TextureBrush_imm_imm(_1)
        }

    .inline TextureBrush_imm_ptrRectF :abs, :abs, :ptr RectF, :vararg {
        GdipCreateTexture2([rcx].Image.nativeImage, _2, [r9].RectF.X, [r9].RectF.Y, [r9].RectF.Width, [r9].RectF.Height, addr this.nativeBrush)
        }
    .inline TextureBrush_imm_ptrRect :abs, :abs, :ptr Rect, :vararg {
        mov r10,r9
        GdipCreateTexture2I([rcx].Image.nativeImage, _2, [r10].Rect.X, [r9].Rect.Y, [r9].Rect.Width, [r9].Rect.Height, addr this.nativeBrush)
        }

    .inline SetTransform :ptr Matrix, :vararg {
        GdipSetTextureTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix)
        this.SetStatus()
        }

    .inline GetTransform :ptr Matrix, :vararg {
        GdipGetTextureTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix)
        this.SetStatus()
        }

    .inline ResetTransform :vararg {
        GdipResetTextureTransform(this.nativeBrush)
        this.SetStatus()
        }

    .inline MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend>, :vararg {
        GdipMultiplyTextureTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix, _2)
        this.SetStatus()
        }

    .inline TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipTranslateTextureTransform(this.nativeBrush, _1, _2, _3)
        this.SetStatus()
        }

    .inline ScaleTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipScaleTextureTransform(this.nativeBrush, _1, _2, _3)
        this.SetStatus()
        }

    .inline RotateTransform :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipRotateTextureTransform(this.nativeBrush, _1, _2)
        this.SetStatus()
        }

    .inline SetWrapMode :vararg {
        GdipSetTextureWrapMode(this.nativeBrush, _1)
        this.SetStatus()
        }

    .inline GetWrapMode :vararg {
        GdipGetTextureWrapMode(this.nativeBrush, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetImage :abs, :vararg {
        GdipGetTextureImage(this.nativeBrush, addr _1)
        this.SetStatus()
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

.template LinearGradientBrush : public Brush

    .inline LinearGradientBrush :abs, :vararg {
        this.typeid(LinearGradientBrush_, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .inline LinearGradientBrush_ptrPointF :ptr PointF, :ptr PointF, :ARGB, :vararg {
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        GdipCreateLineBrush(rcx, rdx, r8d, _4, WrapModeTile, addr this.nativeBrush)
        }
    .inline LinearGradientBrush_ptrPoint :ptr Point, :ptr Point, :ARGB, :vararg {
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        GdipCreateLineBrushI(rcx, rdx, r8d, _4, WrapModeTile, addr this.nativeBrush)
        }
    .inline LinearGradientBrush_ptrRectF :abs, :abs, :abs, :abs, :vararg {
        this.typeid(LinearGradientBrush_ptrRectF_, _4)(_1, _2, _3, _4, _5)
        }
    .inline LinearGradientBrush_ptrRect :abs, :abs, :abs, :abs, :vararg {
        this.typeid(LinearGradientBrush_ptrRect_, _4)(_1, _2, _3, _4, _5)
        }
    .inline LinearGradientBrush_ptrRectF_imm :ptr RectF, :ARGB, :ARGB, :vararg {
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        mov r9d,_4
        GdipCreateLineBrushFromRect(rcx, edx, r8d, r9d, WrapModeTile, addr this.nativeBrush)
        }
    .inline LinearGradientBrush_ptrRect_imm :ptr Rect, :ARGB, :ARGB, :vararg {
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        mov r9d,_4
        GdipCreateLineBrushFromRectI(rcx, edx, r8d, r9d, WrapModeTile, addr this.nativeBrush)
        }
    .inline LinearGradientBrush_ptrRectF_flt :ptr RectF, :ARGB, :ARGB, :abs, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        mov r9d,_5
        GdipCreateLineBrushFromRectWithAngle(rcx, edx, r8d, _4, r9d, WrapModeTile, addr this.nativeBrush)
        }
    .inline LinearGradientBrush_ptrRect_flt :ptr Rect, :ARGB, :ARGB, :abs, :abs=<FALSE>, :vararg {
        mov rcx,rdx
        mov rdx,r8
        mov r8d,r9d
        mov r9d,_5
        GdipCreateLineBrushFromRectWithAngleI(rcx, edx, r8d, _4, r9d, WrapModeTile, addr this.nativeBrush)
        }

    .inline SetLinearColors :vararg {
        GdipSetLineColors(this.nativeBrush, _1)
        this.SetStatus()
        }

    .inline GetLinearColors :ptr ARGB, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetLineColors(this.nativeBrush, rdx)
        .endif
        this.SetStatus()
        }

    .inline GetRectangle :abs, :vararg {
        this.typeid(GetRectangle_, _1)(_1, _2)
        this.SetStatus()
        }
    .inline GetRectangle_ptrRectF :vararg {
        GdipGetLineRect(this.nativeBrush, _1)
        }
    .inline GetRectangle_ptrRect :vararg {
        GdipGetLineRectI(this.nativeBrush, _1)
        }

    .inline SetGammaCorrection :vararg {
        GdipSetLineGammaCorrection(this.nativeBrush, _1)
        this.SetStatus()
        }

    .inline GetGammaCorrection :vararg {
        GdipGetLineGammaCorrection(this.nativeBrush, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetBlendCount :vararg {
        mov this.scratch,0
        GdipGetLineBlendCount(this.nativeBrush, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline SetBlend :vararg {
        GdipSetLineBlend(this.nativeBrush, _1)
        this.SetStatus()
        }

    .inline GetBlend :vararg {
        GdipGetLineBlend(this.nativeBrush, _1)
        this.SetStatus()
        }

    .inline GetInterpolationColorCount :vararg {
        mov this.scratch,0
        GdipGetLinePresetBlendCount(this.nativeBrush, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline SetInterpolationColors :ptr ARGB, :abs, :int_t, :vararg {
        mov eax,InvalidParameter
        .ifs !( r9d <= 0 || !rdx )
            GdipSetLinePresetBlend(this.nativeBrush, rdx, _2, r9d)
        .endif
        this.SetStatus()
        }

    .inline GetInterpolationColors :ptr ARGB, :abs, :int_t, :vararg {
        mov eax,InvalidParameter
        .ifs !( r9d <= 0 || !rdx )
            GdipGetLinePresetBlend(this.nativeBrush, rdx, _2, r9d)
        .endif
        this.SetStatus()
        }

    .inline SetBlendBellShape :abs, :abs=<1.0>, :vararg {
        GdipSetLineSigmaBlend(this.nativeBrush, _1, _2)
        this.SetStatus()
        }

    .inline SetBlendTriangularShape :abs, :abs=<1.0>, :vararg {
        GdipSetLineLinearBlend(this.nativeBrush, _1, _2)
        this.SetStatus()
        }

    .inline SetTransform :ptr Matrix, :vararg {
        GdipSetLineTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix )
        this.SetStatus()
        }

    .inline GetTransform :ptr Matrix, :vararg {
        GdipGetLineTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix )
        this.SetStatus()
        }

    .inline ResetTransform :vararg {
        GdipResetLineTransform(this.nativeBrush)
        this.SetStatus()
        }

    .inline MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend>, :vararg {
        GdipMultiplyLineTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix, _2)
        this.SetStatus()
        }

    .inline TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipTranslateLineTransform(this.nativeBrush, _1, _2, _3)
        this.SetStatus()
        }

    .inline ScaleTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipScaleLineTransform(this.nativeBrush, _1, _2, _3)
        this.SetStatus()
        }

    .inline RotateTransform :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipRotateLineTransform(this.nativeBrush, _1, _2)
        this.SetStatus()
        }

    .inline SetWrapMode :vararg {
        GdipSetLineWrapMode(this.nativeBrush, _1)
        this.SetStatus()
        }

    .inline GetWrapMode :vararg {
        GdipGetLineWrapMode(this.nativeBrush, addr this.scratch)
        this.SetStatus()
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

.template HatchBrush : public Brush

    ; HatchBrush(HatchStyle, foreColor:ARGB, backColor:ARGB)

    .inline HatchBrush :vararg {
        GdipCreateHatchBrush(_1, addr this.nativeBrush)
        this.SetStatus()
        }

    .inline GetHatchStyle :vararg {
        GdipGetHatchStyle(this.nativeBrush, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetForegroundColor :ptr ARGB, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetHatchForegroundColor(this.nativeBrush, rdx)
        .endif
        this.SetStatus()
        }

    .inline GetBackgroundColor :ptr ARGB, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetHatchBackgroundColor(this.nativeBrush, rdx)
        .endif
        this.SetStatus()
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

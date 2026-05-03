ifndef _GDIPLUSIMAGEATTRIBUTES_H
define _GDIPLUSIMAGEATTRIBUTES_H
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template ImageAttributes fastcall

    GpImageAttributes typedef ImageAttributes

    nativeImageAttr ptr_t ?
    lastResult      Status ?

    .static ImageAttributes :abs, :abs {
        mov this.nativeImageAttr,NULL
      ifb <_1>
            GdipCreateImageAttributes(addr this.nativeImageAttr)
      else
        mov this.nativeImageAttr,_1
        mov this.lastResult,_2
      endif
        mov this.lastResult,eax
        }

    .static Release {
        GdipDisposeImageAttributes(this.nativeImageAttr)
        }

    .static SetNativeImageAttr :ptr ImageAttributes {
        mov this.nativeImageAttr,_1
        }

    .static SetStatus watcall :size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static Clone {
       .new clone:ImageAttributes
        this.SetStatus(GdipCloneImageAttributes(this.nativeImageAttr, &clone))
        mov clone.lastResult,eax
        lea rax,clone
        }

    .static SetToIdentity :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesToIdentity(this.nativeImageAttr, _1))
        }
    .static Reset :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipResetImageAttributes(this.nativeImageAttr, _1))
        }
    .static SetColorMatrix :abs, :abs=<ColorMatrixFlagsDefault>, :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _3, TRUE, _1, NULL, _2))
        }
    .static ClearColorMatrix :abs=<ColorMatrixFlagsDefault> {
        this.SetStatus(GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _1, FALSE, NULL, NULL, ColorMatrixFlagsDefault))
        }
    .static SetColorMatrices :abs, :abs, :abs=<ColorAdjustTypeDefault>, :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _4, TRUE, _1, _2, _3))
        }
    .static ClearColorMatrices :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _1, FALSE, NULL, NULL, ColorMatrixFlagsDefault))
        }
    .static SetThreshold :abs, :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesThreshold(this.nativeImageAttr, _2, TRUE, _1))
        }
    .static ClearThreshold :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesThreshold(this.nativeImageAttr, _1, FALSE, 0.0))
        }
    .static SetGamma :abs, :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesGamma(this.nativeImageAttr, _2, TRUE, _1))
        }
    .static ClearGamma :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesGamma(this.nativeImageAttr, _1, FALSE, 0.0))
        }
    .static SetNoOp :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesNoOp(this.nativeImageAttr, _1, TRUE))
        }
    .static ClearNoOp :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesNoOp(this.nativeImageAttr, _1, FALSE))
        }
    .static SetColorKey :abs, :abs, :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesColorKeys(this.nativeImageAttr, _3, TRUE, _1, _2))
        }
    .static ClearColorKey :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesColorKeys(this.nativeImageAttr, _1, FALSE, NULL, NULL))
        }
    .static SetOutputChannel :abs, :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesOutputChannel(this.nativeImageAttr, _2, TRUE, _1))
        }
    .static ClearOutputChannel :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesOutputChannel(this.nativeImageAttr, _1, FALSE, ColorChannelFlagsLast))
        }
    .static SetOutputChannelColorProfile :abs, :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesOutputChannelColorProfile(this.nativeImageAttr, _2, TRUE, _1))
        }
    .static ClearOutputChannelColorProfile :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesOutputChannelColorProfile(this.nativeImageAttr, _1, FALSE, NULL))
        }
    .static SetRemapTable :abs, :abs, :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesRemapTable(this.nativeImageAttr, _3, TRUE, _1, _2))
        }
    .static ClearRemapTable :abs=<ColorAdjustTypeDefault> {
        this.SetStatus(GdipSetImageAttributesRemapTable(this.nativeImageAttr, _1, FALSE, 0, NULL))
        }
    .static SetBrushRemapTable :abs, :abs {
        this.SetRemapTable(_1, _2, ColorAdjustTypeBrush)
        }
    .static ClearBrushRemapTable {
        this.ClearRemapTable(ColorAdjustTypeBrush)
        }
    .static SetWrapMode :abs, :ptr Color, :abs=<FALSE> {
        this.SetStatus(GdipSetImageAttributesWrapMode(this.nativeImageAttr, _1, [_2].Color.Argb, _3))
        }

    ;; The flags of the palette are ignored.

    .static GetAdjustedPalette :abs, :abs {
        this.SetStatus(GdipGetImageAttributesAdjustedPalette(this.nativeImageAttr, _1, _2))
        }

    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

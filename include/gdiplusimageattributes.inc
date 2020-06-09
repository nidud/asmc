ifndef _GDIPLUSIMAGEATTRIBUTES_H
_GDIPLUSIMAGEATTRIBUTES_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template ImageAttributes

    GpImageAttributes typedef ImageAttributes

    nativeImageAttr ptr_t ?
    lastResult      Status ?

    .operator ImageAttributes :abs, :vararg {
        mov this.nativeImageAttr,NULL
        ifb <_1>
            GdipCreateImageAttributes(addr this.nativeImageAttr)
        else
            this.typeid(ImageAttributes, _1)(_1, _2)
        endif
        mov this.lastResult,eax
        }

    .operator ImageAttributes?pImageAttributes :ptr ImageAttributes, :Status, :vararg {
        mov this.nativeImageAttr,rdx
        mov this.lastResult,r8d
        }

    .operator Release {
        GdipDisposeImageAttributes([this].ImageAttributes.nativeImageAttr)
        }

    .operator SetNativeImageAttr :ptr ImageAttributes {
        mov [this].ImageAttributes.nativeImageAttr,_1
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

    .operator Clone :vararg {

        .new clone:ImageAttributes

        GdipCloneImageAttributes(this.nativeImageAttr, &clone)
        mov clone.lastResult,eax
        this.SetStatus()
        lea rax,clone
        }

    .operator SetToIdentity :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesToIdentity(this.nativeImageAttr, _1)
        this.SetStatus()
        }

    .operator Reset :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipResetImageAttributes(this.nativeImageAttr, _1)
        this.SetStatus()
        }

    .operator SetColorMatrix :abs, :abs=<ColorMatrixFlagsDefault>, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _3, TRUE, _1, NULL, _2)
        this.SetStatus()
        }

    .operator ClearColorMatrix :abs=<ColorMatrixFlagsDefault>, :vararg {
        GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _1, FALSE, NULL, NULL, ColorMatrixFlagsDefault)
        this.SetStatus()
        }

    .operator SetColorMatrices :abs, :abs, :abs=<ColorAdjustTypeDefault>, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _4, TRUE, _1, _2, _3)
        this.SetStatus()
        }

    .operator ClearColorMatrices :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _1, FALSE, NULL, NULL, ColorMatrixFlagsDefault)
        this.SetStatus()
        }

    .operator SetThreshold :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesThreshold(this.nativeImageAttr, _2, TRUE, _1)
        this.SetStatus()
        }

    .operator ClearThreshold :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesThreshold(this.nativeImageAttr, _1, FALSE, 0.0)
        this.SetStatus()
        }

    .operator SetGamma :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesGamma(this.nativeImageAttr, _2, TRUE, _1)
        this.SetStatus()
        }

    .operator ClearGamma :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesGamma(this.nativeImageAttr, _1, FALSE, 0.0)
        this.SetStatus()
        }

    .operator SetNoOp :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesNoOp(this.nativeImageAttr, _1, TRUE)
        this.SetStatus()
        }

    .operator ClearNoOp :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesNoOp(this.nativeImageAttr, _1, FALSE)
        this.SetStatus()
        }

    .operator SetColorKey :abs, :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorKeys(this.nativeImageAttr, _3, TRUE, _1, _2)
        this.SetStatus()
        }

    .operator ClearColorKey :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorKeys(this.nativeImageAttr, _1, FALSE, NULL, NULL)
        this.SetStatus()
        }

    .operator SetOutputChannel :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesOutputChannel(this.nativeImageAttr, _2, TRUE, _1)
        this.SetStatus()
        }

    .operator ClearOutputChannel :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesOutputChannel(this.nativeImageAttr, _1, FALSE, ColorChannelFlagsLast)
        this.SetStatus()
        }

    .operator SetOutputChannelColorProfile :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesOutputChannelColorProfile(this.nativeImageAttr, _2, TRUE, _1)
        this.SetStatus()
        }

    .operator ClearOutputChannelColorProfile :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesOutputChannelColorProfile(this.nativeImageAttr, _1, FALSE, NULL)
        this.SetStatus()
        }

    .operator SetRemapTable :abs, :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesRemapTable(this.nativeImageAttr, _3, TRUE, _1, _2)
        this.SetStatus()
        }

    .operator ClearRemapTable :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesRemapTable(this.nativeImageAttr, _1, FALSE, 0, NULL)
        this.SetStatus()
        }

    .operator SetBrushRemapTable :abs, :abs, :vararg {
        this.SetRemapTable(_1, _2, ColorAdjustTypeBrush)
        }

    .operator ClearBrushRemapTable :vararg {
        this.ClearRemapTable(ColorAdjustTypeBrush)
        }

    .operator SetWrapMode :abs, :ptr Color, :abs=<FALSE>, :vararg {
        GdipSetImageAttributesWrapMode(this.nativeImageAttr, _1, [r8].Color.Argb, _3)
        this.SetStatus()
        }

    ;; The flags of the palette are ignored.

    .operator GetAdjustedPalette :abs, :abs, :vararg {
        GdipGetImageAttributesAdjustedPalette(this.nativeImageAttr, _1, _2)
        this.SetStatus()
        }

    .operator GetLastStatus {
        mov eax,[this].ImageAttributes.lastResult
        mov [this].ImageAttributes.lastResult,Ok
        }

    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

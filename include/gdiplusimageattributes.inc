ifndef _GDIPLUSIMAGEATTRIBUTES_H
define _GDIPLUSIMAGEATTRIBUTES_H
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template ImageAttributes

    GpImageAttributes typedef ImageAttributes

    nativeImageAttr ptr_t ?
    lastResult      Status ?

    .inline ImageAttributes :abs, :vararg {
        mov this.nativeImageAttr,NULL
        ifb <_1>
            GdipCreateImageAttributes(addr this.nativeImageAttr)
        else
            this.typeid(ImageAttributes_, _1)(_1, _2)
        endif
        mov this.lastResult,eax
        }

    .inline ImageAttributes_ptrImageAttributes :ptr ImageAttributes, :Status, :vararg {
        mov this.nativeImageAttr,rdx
        mov this.lastResult,r8d
        }

    .inline Release {
        GdipDisposeImageAttributes([this].ImageAttributes.nativeImageAttr)
        }

    .inline SetNativeImageAttr :ptr ImageAttributes {
        mov [this].ImageAttributes.nativeImageAttr,_1
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

        .new clone:ImageAttributes

        GdipCloneImageAttributes(this.nativeImageAttr, &clone)
        mov clone.lastResult,eax
        this.SetStatus()
        lea rax,clone
        }

    .inline SetToIdentity :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesToIdentity(this.nativeImageAttr, _1)
        this.SetStatus()
        }

    .inline Reset :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipResetImageAttributes(this.nativeImageAttr, _1)
        this.SetStatus()
        }

    .inline SetColorMatrix :abs, :abs=<ColorMatrixFlagsDefault>, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _3, TRUE, _1, NULL, _2)
        this.SetStatus()
        }

    .inline ClearColorMatrix :abs=<ColorMatrixFlagsDefault>, :vararg {
        GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _1, FALSE, NULL, NULL, ColorMatrixFlagsDefault)
        this.SetStatus()
        }

    .inline SetColorMatrices :abs, :abs, :abs=<ColorAdjustTypeDefault>, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _4, TRUE, _1, _2, _3)
        this.SetStatus()
        }

    .inline ClearColorMatrices :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorMatrix(this.nativeImageAttr, _1, FALSE, NULL, NULL, ColorMatrixFlagsDefault)
        this.SetStatus()
        }

    .inline SetThreshold :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesThreshold(this.nativeImageAttr, _2, TRUE, _1)
        this.SetStatus()
        }

    .inline ClearThreshold :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesThreshold(this.nativeImageAttr, _1, FALSE, 0.0)
        this.SetStatus()
        }

    .inline SetGamma :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesGamma(this.nativeImageAttr, _2, TRUE, _1)
        this.SetStatus()
        }

    .inline ClearGamma :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesGamma(this.nativeImageAttr, _1, FALSE, 0.0)
        this.SetStatus()
        }

    .inline SetNoOp :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesNoOp(this.nativeImageAttr, _1, TRUE)
        this.SetStatus()
        }

    .inline ClearNoOp :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesNoOp(this.nativeImageAttr, _1, FALSE)
        this.SetStatus()
        }

    .inline SetColorKey :abs, :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorKeys(this.nativeImageAttr, _3, TRUE, _1, _2)
        this.SetStatus()
        }

    .inline ClearColorKey :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesColorKeys(this.nativeImageAttr, _1, FALSE, NULL, NULL)
        this.SetStatus()
        }

    .inline SetOutputChannel :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesOutputChannel(this.nativeImageAttr, _2, TRUE, _1)
        this.SetStatus()
        }

    .inline ClearOutputChannel :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesOutputChannel(this.nativeImageAttr, _1, FALSE, ColorChannelFlagsLast)
        this.SetStatus()
        }

    .inline SetOutputChannelColorProfile :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesOutputChannelColorProfile(this.nativeImageAttr, _2, TRUE, _1)
        this.SetStatus()
        }

    .inline ClearOutputChannelColorProfile :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesOutputChannelColorProfile(this.nativeImageAttr, _1, FALSE, NULL)
        this.SetStatus()
        }

    .inline SetRemapTable :abs, :abs, :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesRemapTable(this.nativeImageAttr, _3, TRUE, _1, _2)
        this.SetStatus()
        }

    .inline ClearRemapTable :abs=<ColorAdjustTypeDefault>, :vararg {
        GdipSetImageAttributesRemapTable(this.nativeImageAttr, _1, FALSE, 0, NULL)
        this.SetStatus()
        }

    .inline SetBrushRemapTable :abs, :abs, :vararg {
        this.SetRemapTable(_1, _2, ColorAdjustTypeBrush)
        }

    .inline ClearBrushRemapTable :vararg {
        this.ClearRemapTable(ColorAdjustTypeBrush)
        }

    .inline SetWrapMode :abs, :ptr Color, :abs=<FALSE>, :vararg {
        GdipSetImageAttributesWrapMode(this.nativeImageAttr, _1, [r8].Color.Argb, _3)
        this.SetStatus()
        }

    ;; The flags of the palette are ignored.

    .inline GetAdjustedPalette :abs, :abs, :vararg {
        GdipGetImageAttributesAdjustedPalette(this.nativeImageAttr, _1, _2)
        this.SetStatus()
        }

    .inline GetLastStatus {
        mov eax,[this].ImageAttributes.lastResult
        mov [this].ImageAttributes.lastResult,Ok
        }

    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

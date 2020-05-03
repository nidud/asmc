ifndef _GDIPLUSIMAGEATTRIBUTES_H
_GDIPLUSIMAGEATTRIBUTES_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template ImageAttributes ;: public GdiplusBase

    GpImageAttributes typedef ImageAttributes

    nativeImageAttr ptr_t ?
    lastResult      Status ?

    .operator new :ptr ImageAttributes, :Status {

        .new native:ptr ImageAttributes
        .new status:Status

        mov native,_1
        mov status,_2

        .if GdipAlloc(ImageAttributes)

            mov _1,native
            mov _2,status

            mov [rax].ImageAttributes.nativeImageAttr,_1
            mov [rax].ImageAttributes.lastResult,_2
        .endif
        retm <rax>
        }

    .operator delete {
        exitm<GdipFree(this)>
        }
    .operator Release {
        exitm<GdipDisposeImageAttributes([this].ImageAttributes.nativeImageAttr)>
        }

    .operator ImageAttributes {

        .new native:ptr ImageAttributes

        GdipCreateImageAttributes(&native)
        exitm<[this].ImageAttributes.new(native, eax)>
        }

    .operator SetNativeImageAttr :ptr GpImageAttributes {
        mov [this].ImageAttributes.nativeImageAttr,_1
        retm<this>
        }

    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].Brush.lastResult,eax
        .endif
        retm <eax>
        }

    .operator Clone {

        .new clone:ptr ImageAttributes
        .new native:ptr ImageAttributes

        mov native,this
        GdipCloneImageAttributes([this].ImageAttributes.nativeImageAttr, &clone)
        native.SetStatus(eax)
        exitm<native.new(clone, eax)>
        }

    .operator SetToIdentity :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesToIdentity([this].ImageAttributes.nativeImageAttr, _1)
        exitm<native.SetStatus(eax)>
        }

    .operator Reset :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipResetImageAttributes([this].ImageAttributes.nativeImageAttr, _1)
        exitm<native.SetStatus(eax)>
        }

    .operator SetColorMatrix :ptr ColorMatrix, :ColorMatrixFlags, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        mov eax,_3
        GdipSetImageAttributesColorMatrix( \
            [this].ImageAttributes.nativeImageAttr, eax, TRUE, _1, NULL, _2)
        exitm<native.SetStatus(eax)>
        }

    .operator ClearColorMatrix :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesColorMatrix([this].ImageAttributes.nativeImageAttr, \
            _1, FALSE, NULL, NULL, ColorMatrixFlagsDefault)
        exitm<native.SetStatus(eax)>
        }

    .operator SetColorMatrices :ptr ColorMatrix, :ptr ColorMatrix, :ColorMatrixFlags, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        mov rax,_1
        mov edx,_4
        GdipSetImageAttributesColorMatrix( \
                [this].ImageAttributes.nativeImageAttr, edx, TRUE, rax, _2, _3)
        exitm<native.SetStatus(eax)>
        }

    .operator ClearColorMatrices :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesColorMatrix([this].ImageAttributes.nativeImageAttr, \
                _1, FALSE, NULL, NULL, ColorMatrixFlagsDefault)
        exitm<native.SetStatus(eax)>
        }

    .operator SetThreshold :REAL, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        mov eax,_2
        GdipSetImageAttributesThreshold( \
             [this].ImageAttributes.nativeImageAttr, eax, TRUE, _1)
        exitm<native.SetStatus(eax)>
        }

    .operator ClearThreshold :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesThreshold( \
            [this].ImageAttributes.nativeImageAttr, _1, FALSE, 0.0)
        exitm<native.SetStatus(eax)>
        }

    .operator SetGamma :REAL, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        mov eax,_2
        GdipSetImageAttributesGamma( \
            [this].ImageAttributes.nativeImageAttr, eax, TRUE, _1)
        exitm<native.SetStatus(eax)>
        }

    .operator ClearGamma :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesGamma( \
            [this].ImageAttributes.nativeImageAttr, _1, FALSE, 0.0)
        exitm<native.SetStatus(eax)>
        }

    .operator SetNoOp :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesNoOp([this].ImageAttributes.nativeImageAttr, _1, TRUE)
        exitm<native.SetStatus(eax)>
        }

    .operator ClearNoOp :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesNoOp([this].ImageAttributes.nativeImageAttr, _1, FALSE)
        exitm<native.SetStatus(eax)>
        }

    .operator SetColorKey :ptr Color, :ptr Color, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        mov r9,_1
        mov edx,_3
        GdipSetImageAttributesColorKeys( \
            [this].ImageAttributes.nativeImageAttr, edx, TRUE, [r9].Color.Argb, [_2].Color.Argb )
        exitm<native.SetStatus(eax)>
        }

    .operator ClearColorKey :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesColorKeys( \
            [this].ImageAttributes.nativeImageAttr, _1, FALSE, NULL, NULL)
        exitm<native.SetStatus(eax)>
        }

    .operator SetOutputChannel :ColorChannelFlags, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        mov eax,_1
        mov edx,_2
        GdipSetImageAttributesOutputChannel( \
            [this].ImageAttributes.nativeImageAttr, edx, TRUE, eax)
        exitm<native.SetStatus(eax)>
        }

    .operator ClearOutputChannel :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesOutputChannel( \
            [this].ImageAttributes.nativeImageAttr, _1, FALSE, ColorChannelFlagsLast)
        exitm<native.SetStatus(eax)>
        }

    .operator SetOutputChannelColorProfile :ptr WCHAR, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        mov rax,_1
        mov edx,_2
        GdipSetImageAttributesOutputChannelColorProfile( \
            [this].ImageAttributes.nativeImageAttr, edx, TRUE, rax)
        exitm<native.SetStatus(eax)>
        }

    .operator ClearOutputChannelColorProfile :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesOutputChannelColorProfile( \
            [this].ImageAttributes.nativeImageAttr, _1, FALSE, NULL)
        exitm<native.SetStatus(eax)>
        }

    .operator SetRemapTable :UINT, :ptr ColorMap, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        mov eax,_3

        GdipSetImageAttributesRemapTable( \
            [this].ImageAttributes.nativeImageAttr, eax, TRUE, _1, _2)
        exitm<native.SetStatus(eax)>
        }

    .operator ClearRemapTable :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipSetImageAttributesRemapTable( \
            [this].ImageAttributes.nativeImageAttr, _1, FALSE, 0, NULL)
        exitm<native.SetStatus(eax)>
        }

    .operator SetBrushRemapTable :UINT, :ptr ColorMap {
        exitm<[this].ImageAttributes.SetRemapTable(_1, _2, ColorAdjustTypeBrush)>
        }

    .operator ClearBrushRemapTable {
        exitm<[this].ImageAttributes.ClearRemapTable(ColorAdjustTypeBrush)>
        }

    .operator SetWrapMode :WrapMode, :ptr Color, :BOOL {

        .new native:ptr ImageAttributes

        mov native,this

        GdipSetImageAttributesWrapMode( \
            [this].ImageAttributes.nativeImageAttr, _1, [_2].Color.Argb, _3)
        exitm<native.SetStatus(eax)>
        }

    ;; The flags of the palette are ignored.

    .operator GetAdjustedPalette :ptr ColorPalette, :ColorAdjustType {

        .new native:ptr ImageAttributes

        mov native,this
        GdipGetImageAttributesAdjustedPalette([this].ImageAttributes.nativeImageAttr, _1, _2)
        exitm<native.SetStatus(eax)>
        }

    .operator GetLastStatus {
        mov eax,[this].ImageAttributes.lastResult
        mov [this].ImageAttributes.lastResult,Ok
        retm<eax>
        }

    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif

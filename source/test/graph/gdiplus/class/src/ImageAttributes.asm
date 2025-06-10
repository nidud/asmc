; IMAGEATTRIBUTES.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local status:Status
    local pColorMatrix:ptr ColorMatrix
    local pColor:ptr Color
    local pWCHAR:ptr WCHAR
    local pColorMap:ptr ColorMap
    local pColorPalette:ptr ColorPalette
    local pImageAttributes:ptr ImageAttributes

    .new p:ImageAttributes()
    .new p:ImageAttributes(pImageAttributes, Ok)

    p.Release()

    p.Clone()

    p.SetToIdentity()
    p.SetToIdentity(ColorAdjustTypeDefault)

    p.Reset()
    p.Reset(ColorAdjustTypeDefault)

    p.SetColorMatrix(pColorMatrix)
    p.SetColorMatrix(pColorMatrix, ColorAdjustTypeDefault)
    p.SetColorMatrix(pColorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeDefault)

    p.ClearColorMatrix()
    p.ClearColorMatrix(ColorAdjustTypeDefault)

    p.SetColorMatrices(pColorMatrix, pColorMatrix)
    p.SetColorMatrices(pColorMatrix, pColorMatrix, ColorAdjustTypeDefault)
    p.SetColorMatrices(pColorMatrix, pColorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeDefault)

    p.ClearColorMatrices()
    p.ClearColorMatrices(ColorAdjustTypeDefault)

    p.SetThreshold(0.0)
    p.SetThreshold(0.0, ColorAdjustTypeDefault)

    p.ClearThreshold()
    p.ClearThreshold(ColorAdjustTypeDefault)

    p.SetGamma(0.0)
    p.SetGamma(0.0, ColorAdjustTypeDefault)

    p.ClearGamma()
    p.ClearGamma(ColorAdjustTypeDefault)

    p.SetNoOp()
    p.SetNoOp(ColorAdjustTypeDefault)

    p.ClearNoOp()
    p.ClearNoOp(ColorAdjustTypeDefault)

    p.SetColorKey(0, 0)
    p.SetColorKey(0, 0, ColorAdjustTypeDefault)

    p.ClearColorKey()
    p.ClearColorKey(ColorAdjustTypeDefault)

    p.SetOutputChannel(0)
    p.SetOutputChannel(0, ColorAdjustTypeDefault)

    p.ClearOutputChannel()
    p.ClearOutputChannel(ColorAdjustTypeDefault)

    p.SetOutputChannelColorProfile(pWCHAR)
    p.SetOutputChannelColorProfile(pWCHAR, ColorAdjustTypeDefault)

    p.ClearOutputChannelColorProfile()
    p.ClearOutputChannelColorProfile(ColorAdjustTypeDefault)

    p.SetRemapTable(0, pColorMap)
    p.SetRemapTable(0, pColorMap, ColorAdjustTypeDefault)

    p.ClearRemapTable()
    p.ClearRemapTable(ColorAdjustTypeDefault)

    p.SetBrushRemapTable(0, pColorMap)

    p.ClearBrushRemapTable()

    p.SetWrapMode(0, pColor)
    p.SetWrapMode(0, pColor, FALSE)

    p.GetAdjustedPalette(pColorPalette, 0)
    p.GetLastStatus()
    p.SetNativeImageAttr(pImageAttributes)
    p.SetStatus()
    p.SetStatus(0)
    ret

main endp

    end

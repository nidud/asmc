; REGION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local hRgn:HRGN
    local pRectF:ptr RectF
    local pRect:ptr Rect
    local pGraphics:ptr Graphics
    local pGraphicsPath:ptr GraphicsPath
    local pRegion:ptr Region
    local pPoint:ptr Point
    local pPointF:ptr PointF
    local pMatrix:ptr Matrix
    local pBYTE:ptr byte
    local pUINT:ptr UINT
    local pINT:ptr SINT

    local rectf:RectF
    local rect:Rect
    local point:Point
    local pointf:PointF

    .new p:Region()
    .new p:Region(rectf)
    .new p:Region(rect)
    .new p:Region(pRectF)
    .new p:Region(pRect)
    .new p:Region(pGraphicsPath)
    .new p:Region(pBYTE, 0)
    .new p:Region(hRgn)
    .new p:Region(pRegion)

    p.FromHRGN(hRgn)
    p.Release()

    p.Clone()
    p.MakeInfinite()
    p.MakeEmpty()
    p.GetDataSize()
    p.GetData(pBYTE, 0, pUINT)

    p.Intersect(rect)
    p.Intersect(rectf)
    p.Intersect(pGraphicsPath)
    p.Intersect(pRegion)

    p._Union(rect)
    p._Union(rectf)
    p._Union(pGraphicsPath)
    p._Union(pRegion)

    p._Xor(rect)
    p._Xor(rectf)
    p._Xor(pGraphicsPath)
    p._Xor(pRegion)

    p.Exclude(rect)
    p.Exclude(rectf)
    p.Exclude(pGraphicsPath)
    p.Exclude(pRegion)

    p.Complement(rect)
    p.Complement(rectf)
    p.Complement(pGraphicsPath)
    p.Complement(pRegion)

    p.Translate(0.0, 0.0)
    p.Translate(0, 0)
    p.Transform(pMatrix)
    p.GetBounds(pRect, pGraphics)
    p.GetBounds(pRectF, pGraphics)
    p.GetHRGN(pGraphics)
    p.IsEmpty(pGraphics)
    p.IsInfinite(pGraphics)

    p.IsVisible(0, 0)
    p.IsVisible(0, 0, pGraphics)
    p.IsVisible(point)
    p.IsVisible(point, pGraphics)
    p.IsVisible(0.0, 0.0)
    p.IsVisible(0.0, 0.0, pGraphics)
    p.IsVisible(pointf)
    p.IsVisible(pointf, pGraphics)
    p.IsVisible(0, 0, 0, 0, pGraphics)
    p.IsVisible(rect)
    p.IsVisible(rect, pGraphics)
    p.IsVisible(0.0, 0.0, 0.0, 0.0)
    p.IsVisible(0.0, 0.0, 0.0, 0.0, pGraphics)
    p.IsVisible(rectf)
    p.IsVisible(rectf, pGraphics)

    p.Equals(pRegion, pGraphics)
    p.GetRegionScansCount(pMatrix)
    p.GetRegionScans(pMatrix, rectf, pINT)
    p.GetRegionScans(pMatrix, rect, pINT)
    p.GetLastStatus()
    p.SetStatus()
    p.SetStatus(1)
    p.SetNativeRegion(pRegion)
    ret

main endp

    end

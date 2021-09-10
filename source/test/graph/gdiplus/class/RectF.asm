; RECTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  local i:int_t
  local u:uint_t
  local x:REAL
  local y:REAL
  local point:PointF
  local pPoint:ptr PointF
  local size:SizeF
  local pSize:ptr SizeF
  local rect:RectF
  local pRect:ptr RectF

  .new b:RectF()
  .new b:RectF(1.0)
  .new b:RectF(1.0, 2.0)
  .new b:RectF(xmm0, xmm0, xmm0, xmm0)
  .new b:RectF(i, i, i, 1)
  .new b:RectF(u, u, u, u)
  .new b:RectF(pPoint, pSize)

  .new p:ptr RectF()
  .new p:ptr RectF(1.0)
  .new p:ptr RectF(1.0, 2.0)
  .new p:ptr RectF(xmm0, xmm0, xmm0, xmm0)
  .new p:ptr RectF(i, i, i, 1)
  .new p:ptr RectF(u, u, u, u)
  .new p:ptr RectF(pPoint, pSize)

    RectF()
    RectF(1.0)
    RectF(1.0, 2.0)
    RectF(xmm0, xmm0, xmm0, xmm0)
    RectF(i, i, i, 1)
    RectF(u, u, u, u)
    RectF(pPoint, pSize)


    b.Clone()
    b.GetLocation(pPoint)
    b.GetSize(pSize)
    b.GetBounds(pRect)
    b.GetLeft()
    b.GetTop()
    b.GetRight()
    b.GetBottom()
    b.IsEmptyArea()
    b.Equals(pRect)
    b.Contains(x, y)
    b.Contains(pPoint)
    b.Contains(pRect)
    b.Inflate(x, y)
    b.Inflate(pPoint)
    b.Intersect(pRect)
    b.Intersect(pRect, pRect)
    b.IntersectsWith(pRect)
    b._Union(pRect, pRect)
    b._Offset(pPoint)
    b._Offset(x, y)

    p.Clone()
    p.GetLocation(pPoint)
    p.GetSize(pSize)
    p.GetBounds(pRect)
    p.GetLeft()
    p.GetTop()
    p.GetRight()
    p.GetBottom()
    p.IsEmptyArea()
    p.Equals(pRect)
    p.Contains(x, y)
    p.Contains(pPoint)
    p.Contains(pRect)
    p.Inflate(x, y)
    p.Inflate(pPoint)
    p.Intersect(pRect)
    p.Intersect(pRect, pRect)
    p.IntersectsWith(pRect)
    p._Union(pRect, pRect)
    p._Offset(pPoint)
    p._Offset(x, y)
    ret

main endp

    end


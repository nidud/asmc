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
  .new b:RectF(point, size)

    b.Clone()
    b.GetLocation(pPoint)
    b.GetSize(pSize)
    b.GetBounds(pRect)
    b.GetLeft()
    b.GetTop()
    b.GetRight()
    b.GetBottom()
    b.IsEmptyArea()
    b.Equals(rect)
    b.Contains(x, y)
    b.Contains(point)
    b.Inflate(x, y)
    b.Inflate(point)
    b.Intersect(rect)
    b.Intersect(rect, rect)
    b.IntersectsWith(rect)
    b._Union(rect, rect)
    b._Offset(point)
    b._Offset(x, y)
    ret

main endp

    end


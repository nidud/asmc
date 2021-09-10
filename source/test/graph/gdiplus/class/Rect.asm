; RECT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  local x:int_t
  local y:int_t
  local point:Point
  local pPoint:ptr Point
  local size:Size
  local pSize:ptr Size
  local rect:Rect
  local pRect:ptr Rect

  .new b:Rect()
  .new b:Rect(1)
  .new b:Rect(1, 2)
  .new p:ptr Rect()
  .new p:ptr Rect(1)
  .new p:ptr Rect(1, 2)

    Rect()
    Rect(1)
    Rect(1, 2, 3, 4)

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


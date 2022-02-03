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

  local r:Rect
  local a:Rect
  local b:Rect

  .new b:Rect()
  .new b:Rect(1)
  .new b:Rect(1, 2, 3, 4)
  .new b:Rect(point, size)

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
    b.Inflate(pPoint)
    b.Intersect(rect)
    b.Intersect(a, b)
    b.IntersectsWith(pRect)
    b._Union(a, b)
    b._Offset(point)
    b._Offset(x, y)
    ret

main endp

    end


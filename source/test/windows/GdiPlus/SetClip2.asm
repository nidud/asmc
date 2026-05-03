include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"SetClip2">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

    .new g:Graphics(hdc)

    ;; Create a Region object, and get its handle.

   .new rc:Rect(0, 0, 100, 100)
   .new region:Region(&rc)
   .new hRegion:HRGN
   .new b:SolidBrush(White)

    mov hRegion,region.GetHRGN(&g)

    ;; Set the clipping region with hRegion.
    g.SetClip(hRegion)

    ;; Fill a rectangle to demonstrate the clipping region.

    g.FillRectangle(&b, 0, 0, 500, 500)
    g.Release()
    ret

OnPaint endp

include Graphics.inc


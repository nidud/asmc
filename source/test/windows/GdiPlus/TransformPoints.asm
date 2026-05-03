include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"TransformPoints">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new pen:Pen(White)

    ;; Create an array of two Point objects.

   .new p2:Point(100, 50)
   .new p1:Point(0, 0)

    ;; Draw a line that connects the two points.
    ;; No transformation has been performed yet.

    g.DrawLine(&pen, p1, p2)

    ;; Set the world transformation of the Graphics object.

    g.TranslateTransform(40.0, 30.0)

    ;; Transform the points in the array from world to page coordinates.

    g.TransformPoints(CoordinateSpacePage, CoordinateSpaceWorld, &p1, 2)

    ;; It is the world transformation that takes points from world
    ;; space to page space. Because the world transformation is a
    ;; translation 40 to the right and 30 down, the
    ;; points in the array are now (40, 30) and (140, 80).

    ;; Draw a line that connects the transformed points.

    g.ResetTransform()
    g.DrawLine(&pen, p1, p2)
    g.Release()
    ret

OnPaint endp

include Graphics.inc


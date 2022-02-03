include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawCurve">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new p:Pen(Red)
   .new i6:Point(250, 150)
   .new i5:Point(350, 200)
   .new i4:Point(300, 100)
   .new i3:Point(250,  50)
   .new i2:Point(200,   5)
   .new i1:Point(100,  25)
   .new ii:Point( 50,  50)

    g.DrawLines(&p, &ii, 7)
    p.Release()

   .new p:Pen(Green)
    g.DrawCurve(&p, &ii, 7)

    p.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc


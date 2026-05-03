;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-begincontainer(inconstrectf__inconstrectf__inunit)
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"BeginContainer2">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

    ;; Define a translation and scale transformation for the container.

   .new srcRect:RectF(0.0, 0.0, 200.0, 100.0)
   .new destRect:RectF(100.0, 100.0, 200.0, 200.0)

    ;; Create a graphics container with a (100, 100) translation
    ;; and (1, 2) scale.

   .new container:GraphicsContainer

    mov container,g.BeginContainer(destRect, srcRect, UnitPixel)

    ;; Fill an ellipse in the container.

   .new c1:Color(255, 255, 0, 0)
   .new c2:Color(255, 0, 0, 255)
   .new redBrush:SolidBrush(c1)

    g.FillEllipse(&redBrush, 0, 0, 100, 60)

    ;; End the container.

    g.EndContainer(container)

    ;; Fill the same ellipse outside the container.

   .new blueBrush:SolidBrush(c2)

    g.FillEllipse(&blueBrush, 0, 0, 100, 60)

    g.Release()
    ret

OnPaint endp

include Graphics.inc


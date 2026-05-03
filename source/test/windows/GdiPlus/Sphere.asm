;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constpointf__constbrush)
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"Sphere">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new count:SINT
   .new FullTranslucent:ARGB

   ; Create a GraphicsPath object
   .new p:GraphicsPath()

   ; Add an ellipse to the path
   p.AddEllipse(200, 0, 200, 200)

   ; Create a path gradient based on the ellipse
   .new b:PathGradientBrush(&p)

   ; Set the middle color of the path
   b.SetCenterColor(ColorAlpha(Green, 180))

   ; Set the entire path boundary to Alpha Black using translucency
   mov count,1
   mov FullTranslucent,ColorAlpha(Black, 230)
   b.SetSurroundColors(&FullTranslucent, &count)

   ; Draw the ellipse, keeping the exact coords we defined for the path
   ; We use AntiAlias drawing mode.
   ; To get a better antialising we enlarge area (+2 and -4).
   g.SetSmoothingMode(SmoothingModeAntiAlias)
   g.FillEllipse(&b, 200 + 2, 0 + 2, 200 - 4, 200 - 4)

   b.Release()
   p.Release()

   ; Second Sphere

   .new p:GraphicsPath()

   p.AddEllipse(200, 100, 150, 150)

   .new b:PathGradientBrush(&p)

   b.SetCenterColor(ColorAlpha(Yellow, 180))
   mov FullTranslucent,ColorAlpha(Red, 200)
   mov count,1
   b.SetSurroundColors(&FullTranslucent, &count)
   g.FillEllipse(&b, 200 + 2, 100 + 2, 150 - 4, 150 - 4)

   b.Release()
   p.Release()
   g.Release()
   ret

OnPaint endp

include Graphics.inc


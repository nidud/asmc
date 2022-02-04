;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-getadjustedpalette
;

include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"ImageAttributes">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

    ;; Create an Image object based on a BMP file.
    ;; The image has three horizontal stripes.
    ;; The color of the top stripe has RGB components (90, 90, 20).
    ;; The color of the middle stripe has RGB components (150, 150, 150).
    ;; The color of the bottom stripe has RGB components (130, 130, 40).

   .new image:Image(L"..\\res\\ColorKeyTest.png")

    ;; Create an ImageAttributes object, and set its color key.

   .new imAtt:ImageAttributes()
   .new c1:Color(100, 95, 30)
   .new c2:Color(250, 245, 60)

    imAtt.SetColorKey(c1, c2, ColorAdjustTypeBitmap)

    ;; Draw the image. Apply the color key.
    ;; The bottom stripe of the image will be transparent because
    ;; 100 <= 130 <= 250 and
    ;; 95  <= 130 <= 245 and
    ;; 30  <= 40  <= 60.

   .new w:int_t
   .new h:int_t

    mov w,image.GetWidth()
    mov h,image.GetHeight()

   .new rc:Rect(20, 20, w, h)

    g.DrawImage(&image, rc, 0, 0, w, h, UnitPixel, &imAtt)
    g.Release()
    ret

OnPaint endp

include Graphics.inc

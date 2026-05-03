;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-setoutputchannelcolorprofile
;

include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     400
define WINHEIGHT    200

CLASSNAME equ <"ImageAttributes">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new w:UINT
   .new h:UINT

    ;; Create an Image object based on a .bmp file.
    ;; The image has one stripe with RGB components (160, 0, 0)
    ;; and one stripe with RGB components (0, 140, 0).

   .new image:Image(L"..\\res\\RedGreenThreshold.png")

    ;; Create an ImageAttributes object, and set its bitmap threshold to 0.6

   .new imAtt:ImageAttributes()
    imAtt.SetThreshold(0.6, ColorAdjustTypeBitmap)

    mov w,image.GetWidth()
    mov h,image.GetHeight()

    ;; Draw the image with no color adjustment.

    g.DrawImage(&image, 10, 10, w, h)

   .new rc:Rect(100, 10, w, h)

    ;; Draw the image with the threshold applied.
    ;; 160 > 0.6*255, so the red stripe will be changed to full intensity.
    ;; 140 < 0.6*255, so the green stripe will be changed to zero intensity.

    g.DrawImage(&image, rc, 0, 0, w, h, UnitPixel, &imAtt)

    g.Release()
    ret

OnPaint endp

include Graphics.inc

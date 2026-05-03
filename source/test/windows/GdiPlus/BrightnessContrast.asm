
include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     450
define WINHEIGHT    590

CLASSNAME equ <"EffectBrightnessContrast">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new brightnessContrast:BrightnessContrast()
   .new brightnessContrastParams:BrightnessContrastParams

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    ;; Integer in the range -255 through 255 that specifies the brightness
    ;; level. If the value is 0, the brightness remains the same. As the
    ;; value moves from 0 to 255, the brightness of the image increases. As
    ;; the value moves from 0 to -255, the brightness of the image decreases.

    mov brightnessContrastParams.brightnessLevel,-80

    ;; Integer in the range -100 through 100 that specifies the contrast
    ;; level. If the value is 0, the contrast remains the same. As the value
    ;; moves from 0 to 100, the contrast of the image increases. As the
    ;; value moves from 0 to -100, the contrast of the image

    mov brightnessContrastParams.contrastLevel,-10

    brightnessContrast.SetParameters(&brightnessContrastParams)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied Effect

    g.DrawImage(&image, &rect, &matrix, &brightnessContrast, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc


include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     450
define WINHEIGHT    590

CLASSNAME equ <"EffectBlur">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new blurParams:BlurParams
   .new blur:Blur()

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss    rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss    rect.Height,xmm0

    mov blurParams.radius,2.5
    mov blurParams.expandEdge,FALSE
    blur.SetParameters(&blurParams)

    ; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ; Draw the image with increased saturation.

    g.DrawImage(&image, &rect, &matrix, &blur, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc



include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"EffectSharpen">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new sharpenParams:SharpenParams
   .new sharpen:Sharpen()

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    ;; The radius must be in the range 0 through 255.
    ;; As the radius increases, more surrounding pixels are involved in
    ;; calculating the new value of a given pixel.

    mov sharpenParams.radius,250.0

    ;; Real number in the range 0 through 100 that specifies the amount of
    ;; sharpening to be applied. A value of 0 specifies no sharpening. As
    ;; the value of amount increases, the sharpness increases.

    mov sharpenParams.amount,100.0

    sharpen.SetParameters(&sharpenParams)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied Effect

    g.DrawImage(&image, &rect, &matrix, &sharpen, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

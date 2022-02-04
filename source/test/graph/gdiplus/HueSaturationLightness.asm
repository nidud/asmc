include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"EffectHueSaturationLightness">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new hueSaturationLightnessParams:HueSaturationLightnessParams
   .new hueSaturationLightness:HueSaturationLightness()

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    mov hueSaturationLightnessParams.hueLevel,0
    mov hueSaturationLightnessParams.lightnessLevel,0
    mov hueSaturationLightnessParams.saturationLevel,50

    hueSaturationLightness.SetParameters(&hueSaturationLightnessParams)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied effect.

    g.DrawImage(&image, &rect, &matrix, &hueSaturationLightness, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

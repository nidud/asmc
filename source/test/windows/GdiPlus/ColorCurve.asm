include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     450
define WINHEIGHT    590

CLASSNAME equ <"EffectColorCurve">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new colorCurveParams:ColorCurveParams
   .new colorCurve:ColorCurve()

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    ;; Element of the CurveAdjustments enumeration that specifies the
    ;; adjustment to be applied.

    mov colorCurveParams.adjustment,AdjustContrast

    ;; Element of the CurveChannel enumeration that specifies the color
    ;; channel to which the adjustment applies.

    mov colorCurveParams.channel,CurveChannelBlue

    ;; Integer that specifies the intensity of the adjustment. The range of
    ;; acceptable values depends on which adjustment is being applied. To
    ;; see the range of acceptable values for a particular adjustment, see
    ;; the CurveAdjustments enumeration.

    mov colorCurveParams.adjustValue,100

    colorCurve.SetParameters(&colorCurveParams)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied Effect

    g.DrawImage(&image, &rect, &matrix, &colorCurve, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

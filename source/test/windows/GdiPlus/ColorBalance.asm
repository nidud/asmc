include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     450
define WINHEIGHT    590

CLASSNAME equ <"EffectColorBalance">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new colorBalanceParams:ColorBalanceParams
   .new colorBalance:ColorBalance()

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    ;; Integer in the range -100 through 100 that specifies a change in the
    ;; amount of red in the image. If the value is 0, there is no change.

    mov colorBalanceParams.cyanRed,-60

    ;; Integer in the range -100 through 100 that specifies a change in the
    ;; amount of green in the image. If the value is 0, there is no change.

    mov colorBalanceParams.magentaGreen,40

    ;; Integer in the range -100 through 100 that specifies a change in the
    ;; amount of blue in the image. If the value is 0, there is no change.

    mov colorBalanceParams.yellowBlue,-50

    colorBalance.SetParameters(&colorBalanceParams)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied Effect

    g.DrawImage(&image, &rect, &matrix, &colorBalance, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

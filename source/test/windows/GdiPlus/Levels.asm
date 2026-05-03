include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     450
define WINHEIGHT    590

CLASSNAME equ <"EffectLevels">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new levelsParams:LevelsParams
   .new levels:Levels()

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    ;; Integer in the range 0 through 100 that specifies which pixels
    ;; should be lightened. Setting highlight to 100 specifies no change.

    mov levelsParams.highlight,60

    ;; Integer in the range -100 through 100 that specifies how much to
    ;; lighten or darken an image. A value of 0 specifies no change.

    mov levelsParams.midtone,30

    ;; Integer in the range 0 through 100 that specifies which pixels
    ;; should be darkened. Setting shadow to 0 specifies no change.

    mov levelsParams.shadow,30

    levels.SetParameters(&levelsParams)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied Effect

    g.DrawImage(&image, &rect, &matrix, &levels, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

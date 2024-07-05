include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     450
define WINHEIGHT    590

CLASSNAME equ <"EffectRedEyeCorrection">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new redEyeCorrectionParams:RedEyeCorrectionParams
   .new redEyeCorrection:RedEyeCorrection()
   .new rc:Rect(0, 0, 100, 100)

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    ;; Integer that specifies the number of RECT structures in the areas array.

    mov redEyeCorrectionParams.numberOfAreas,1

    ;; Pointer to an array of RECT structures, each of which specifies an
    ;; area of the bitmap to which red eye correction should be applied.

    mov redEyeCorrectionParams.areas,&rc

    redEyeCorrection.SetParameters(&redEyeCorrectionParams)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied Effect

    g.DrawImage(&image, &rect, &matrix, &redEyeCorrection, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

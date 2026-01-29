
include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     450
define WINHEIGHT    590

CLASSNAME equ <"EffectColorMatrixEffect">

    .data

    colorMatrix ColorMatrix { ;; Multiply red component by 1.5.
        {
            1.5,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.0,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.0,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new colorMatrixEffect:ColorMatrixEffect()

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    ;; A 5x5 color matrix is a homogeneous matrix for a 4-space
    ;; transformation. The element in the fifth row and fifth column of a
    ;; 5x5 homogeneous matrix must be 1, and all of the other elements in
    ;; the fifth column must be 0. Color matrices are used to transform
    ;; color vectors. The first four components of a color vector hold the
    ;; red, green, blue, and alpha components (in that order) of a color.
    ;; The fifth component of a color vector is always 1.

    colorMatrixEffect.SetParameters(&colorMatrix)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied Effect

    g.DrawImage(&image, &rect, &matrix, &colorMatrixEffect, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

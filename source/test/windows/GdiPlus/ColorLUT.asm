include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     450
define WINHEIGHT    590

CLASSNAME equ <"EffectColorLUT">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\Photograph.jpg")
   .new rect:RectF()
   .new matrix:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
   .new colorLUTParams:ColorLUTParams
   .new colorLUT:ColorLUT()

    image.GetWidth()
    cvtsi2ss xmm0,eax
    movss rect.Width,xmm0
    image.GetHeight()
    cvtsi2ss xmm0,eax
    movss rect.Height,xmm0

    ;; A lookup table specifies how existing color channel values should be
    ;; replaced by new values. A color channel value of j is replaced by the
    ;; jth entry in the lookup table for that channel. For example, an
    ;; existing blue channel value of 25 would be replaced by the value of
    ;; lutB[25].

    .for rdx = &colorLUTParams, ecx = 0: ecx < 256: ecx++

        lea rax,[rcx+128]
        mov [rdx+rcx+256*0],cl ; adjustment for the blue channel
        mov [rdx+rcx+256*1],cl ; adjustment for the green channel
        mov [rdx+rcx+256*2],al ; adjustment for the red channel
        mov [rdx+rcx+256*3],cl ; adjustment for the alpha channel
    .endf

    colorLUT.SetParameters(&colorLUTParams)

    ;; Draw the image with no change.

    g.DrawImage(&image, 20.0, 20.0, rect.Width, rect.Height)

    ;; Draw the image with applied Effect

    g.DrawImage(&image, &rect, &matrix, &colorLUT, NULL, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

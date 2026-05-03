;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-getadjustedpalette
;

include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     400
define WINHEIGHT    160

CLASSNAME equ <"ImageAttributes">

    .code

OnPaint proc uses rsi rdi hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

    ;; Create a palette that has four entries.

   .new p:ptr ColorPalette(4)
    mov rcx,rax
    [rcx].ColorPalette.SetPalette(0, Aqua)
    [rcx].ColorPalette.SetPalette(1, White)
    [rcx].ColorPalette.SetPalette(2, Red)
    [rcx].ColorPalette.SetPalette(3, Green)

    ;; Display the four palette colors with no adjustment.

   .new b:SolidBrush(Black)

    .for ( esi = 0: esi < 4: ++esi )

        p.GetPalette(rsi)
        b.SetColor(eax)

        imul edx,esi,30
        add  edx,20

        g.FillRectangle(&b, edx, 20, 20, 20)
    .endf

    ;; Create a remap table that converts green to blue.

   .new map:ColorMap
    mov map.oldColor,Green
    mov map.newColor,Blue

    ;; Create an ImageAttributes object, and set its bitmap remap table.

   .new imAtt:ImageAttributes()

    imAtt.SetRemapTable(1, &map, ColorAdjustTypeBitmap)

    ;; Adjust the palette.

    imAtt.GetAdjustedPalette(p, ColorAdjustTypeBitmap)

    ;; Display the four palette colors after the adjustment.

    .for ( esi = 0: esi < 4: ++esi )

        p.GetPalette(rsi)
        b.SetColor(eax)

        imul edx,esi,30
        add  edx,20

        g.FillRectangle(&b, edx, 50, 20, 20)
    .endf

    p.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

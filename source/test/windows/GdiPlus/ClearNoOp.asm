;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-clearnoop
;

include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     420
define WINHEIGHT    380

    .data
     brushMatrix ColorMatrix {{    ;; red converted to green
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 1.0
        }}
    .code

CLASSNAME equ <"ImageAttributes">

    .code

OnPaint proc uses rsi rdi hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new i:Image(L"..\\res\\TestMetafile4.emf")
   .new imAtt:ImageAttributes()

    mov esi,i.GetWidth()
    mov edi,i.GetHeight()

   .new r1:Rect(0,   0, esi, edi)
   .new r2:Rect(0,  80, esi, edi)
   .new r3:Rect(0, 160, esi, edi)

    imAtt.SetColorMatrix(&brushMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBrush)

    ;; Draw the image (metafile) using brush color adjustment.
    ;; Items filled with a brush change from red to green.

    g.DrawImage(&i, r1, 0, 0, esi, edi, UnitPixel, &imAtt)

    ;; Temporarily disable brush color adjustment.

    imAtt.SetNoOp(ColorAdjustTypeBrush)

    ;; Draw the image (metafile) without brush color adjustment.
    ;; There is no change from red to green.

    g.DrawImage(&i, r2, 0, 0, esi, edi, UnitPixel, &imAtt)

    ;; Reinstate brush color adjustment.

    imAtt.ClearNoOp(ColorAdjustTypeBrush)

    ;; Draw the image (metafile) using brush color adjustment.
    ;; Items filled with a brush change from red to green.

    g.DrawImage(&i, r3, 0, 0, esi, edi, UnitPixel, &imAtt)

    i.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

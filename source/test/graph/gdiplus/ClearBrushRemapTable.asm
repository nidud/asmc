;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-clearbrushremaptable
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"ImageAttributes">

    .code

OnPaint proc uses rsi rdi hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new image:Image(L"..\\res\\TestMetafile4.emf")
   .new imAtt:ImageAttributes()
   .new defaultMap:ColorMap
   .new brushMap:ColorMap

    mov defaultMap.oldColor,MakeARGB(255, 255, 0, 0)   ;; red converted to blue
    mov defaultMap.newColor,MakeARGB(255, 0, 0, 255)   ;;
    mov brushMap.oldColor,MakeARGB(255, 255, 0, 0)     ;; red converted to green
    mov brushMap.newColor,MakeARGB(255, 0, 255, 0)     ;;

    ;; Set the default color-remap table.

    imAtt.SetRemapTable(1, &defaultMap, ColorAdjustTypeDefault)

    mov esi,image.GetWidth()
    mov edi,image.GetHeight()

    .new r1:Rect( 0,   0, esi, edi)
    .new r2:Rect(10,  90, esi, edi)
    .new r3:Rect(10, 170, esi, edi)
    .new r4:Rect(10, 250, esi, edi)

    ;; Draw the image (metafile) using no color adjustment.

    g.DrawImage(&image, r1, 0, 0, esi, edi, UnitPixel)

    ;; Draw the image (metafile) using default color adjustment.
    ;; All red is converted to blue.

    g.DrawImage(&image, r2, 0, 0, esi, edi, UnitPixel, &imAtt)

    ;; Set the brush remap table.

    imAtt.SetBrushRemapTable(1, &brushMap)

    ;; Draw the image (metafile) using default and brush adjustment.
    ;; Red painted with a brush is converted to green.
    ;; All other red is converted to blue (default).

    g.DrawImage(&image,  r3, 0, 0, esi, edi, UnitPixel, &imAtt)

    ;; Clear the brush remap table.

    imAtt.ClearBrushRemapTable()

    ;; Draw the image (metafile) using only default color adjustment.
    ;; Red painted with a brush gets no color adjustment.
    ;; All other red is converted to blue (default).

    g.DrawImage(&image, r4, 0, 0, esi, edi, UnitPixel, &imAtt)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

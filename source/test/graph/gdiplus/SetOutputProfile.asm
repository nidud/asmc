;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-setoutputchannelcolorprofile
;

include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"ImageAttributes">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new image:Image(L"..\\res\\Mosaic.png")
   .new width:UINT
   .new height:UINT
   .new w:UINT
   .new h:UINT
   .new imAtt:ImageAttributes()

    mov width,image.GetWidth()
    add eax,20
    mov w,eax
    mov height,image.GetHeight()
    add eax,20
    mov h,eax

    ;; Draw the image unaltered.

    g.DrawImage(&image, 10, 10, width, height)

    imAtt.SetOutputChannelColorProfile(L"..\\res\\TEKPH600.ICM", ColorAdjustTypeBitmap)

   .new r1:Rect(10, h, width, height)
    imul eax,h,2
    sub eax,10
   .new r2:Rect(10, eax, width, height)
   .new r3:Rect(w, 10, width, height)
   .new r4:Rect(w, h, width, height)

    ;; Draw the image, showing the intensity of the cyan channel.

    imAtt.SetOutputChannel(ColorChannelFlagsC, ColorAdjustTypeBitmap)
    g.DrawImage(&image, r1, 0, 0, width, height, UnitPixel, &imAtt)

    ;; Draw the image, showing the intensity of the magenta channel.

    imAtt.SetOutputChannel(ColorChannelFlagsM, ColorAdjustTypeBitmap)
    g.DrawImage(&image, r2, 0, 0, width, height, UnitPixel, &imAtt)

    ;; Draw the image, showing the intensity of the yellow channel.

    imAtt.SetOutputChannel(ColorChannelFlagsY, ColorAdjustTypeBitmap)
    g.DrawImage(&image, r3, 0, 0, width, height, UnitPixel, &imAtt)

    ;; Draw the image, showing the intensity of the black channel.

    imAtt.SetOutputChannel(ColorChannelFlagsK, ColorAdjustTypeBitmap)
    g.DrawImage(&image, r4, 0, 0, width, height, UnitPixel, &imAtt)

    g.Release()
    ret

OnPaint endp

include Graphics.inc

;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-clearcolormatrices
;
include windows.inc
include gdiplus.inc
include tchar.inc

define WINWIDTH     610
define WINHEIGHT    300

    .data

    defaultColorMatrix ColorMatrix { ;; Multiply red component by 1.5.
        {
            1.5,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.0,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.0,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }
    defaultGrayMatrix ColorMatrix {  ;; Multiply green component by 1.5.
        {
            1.0,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.5,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.0,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }
    penColorMatrix ColorMatrix {     ;; Multiply blue component by 1.5.
        {
            1.0,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.0,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.5,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }
    penGrayMatrix ColorMatrix {      ;; Multiply all components by 1.5.
        {
            1.5,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.5,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.5,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }

CLASSNAME equ <"ImageAttributes">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new image:Image(L"..\\res\\TestMetafile6.emf")
   .new imAtt:ImageAttributes()
   .new rect:RectF
   .new unit:Unit

    image.GetBounds(&rect, &unit)

   .new r1:RectF(10.0,  50.0, rect.Width, rect.Height)
   .new r2:RectF(10.0,  90.0, rect.Width, rect.Height)
   .new r3:RectF(10.0, 130.0, rect.Width, rect.Height)

    ;; Set the default color- and grayscale-adjustment matrices.

    imAtt.SetColorMatrices(&defaultColorMatrix, &defaultGrayMatrix, ColorMatrixFlagsAltGray, ColorAdjustTypeDefault)
    g.DrawImage(&image, 10.0, 10.0, rect.Width, rect.Height)
    g.DrawImage(&image, r1, rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt)

    ;; Set the pen color- and grayscale-adjustment matrices.

    imAtt.SetColorMatrices(&penColorMatrix, &penGrayMatrix, ColorMatrixFlagsAltGray, ColorAdjustTypePen)
    g.DrawImage(&image, r2, rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt)
    imAtt.ClearColorMatrices(ColorAdjustTypePen)
    g.DrawImage(&image, r3, rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

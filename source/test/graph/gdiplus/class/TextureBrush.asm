; TEXTUREBRUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

;; TextureBrush(Image*, WrapMode = WrapModeTile)
;; TextureBrush(Image*, WrapMode, RectF*)
;; TextureBrush(Image*, RectF*, ImageAttributes * = NULL)
;; TextureBrush(Image*, Rect*, ImageAttributes * = NULL)
;; TextureBrush(Image*, WrapMode, Rect*)
;; TextureBrush(Image*, WrapMode, REAL, REAL, REAL, REAL)
;; TextureBrush(Image*, WrapMode, INT, INT, INT, INT)

    .code

main proc

    local image:Image
    local pImage:ptr Image
    local pGraphicsPath:ptr GraphicsPath
    local pINT:ptr int_t
    local pBOOL:ptr BOOL
    local pBYTE:ptr BYTE
    local pPointF:ptr PointF
    local pPoint:ptr Point
    local pColor:ptr Color
    local argb:ARGB
    local pREAL:ptr REAL
    local pRectF:ptr RectF
    local pRect:ptr Rect
    local pMatrix:ptr Matrix
    local pImageAttributes:ptr ImageAttributes

    .new p:TextureBrush(pImage)
    .new p:TextureBrush(pImage, 0)
    .new p:TextureBrush(pImage, 0, pRectF)
    .new p:TextureBrush(pImage, pRectF, pImageAttributes)
    .new p:TextureBrush(pImage, pRect, pImageAttributes)
    .new p:TextureBrush(pImage, 0, pRect)
    .new p:TextureBrush(pImage, 0, 0, 0, 0, 0)
    .new p:TextureBrush(pImage, 0, 0.0, 0.0, 0.0, 0.0)

    p.Release()

    p.SetTransform(NULL)
    p.GetTransform(NULL)
    p.ResetTransform()
    p.MultiplyTransform(NULL, 0)
    p.TranslateTransform(0.0, 0.0, 0)
    p.ScaleTransform(0.0, 0.0, 0)
    p.RotateTransform(0.0, 0)
    p.SetWrapMode(0)
    p.GetWrapMode()
    p.GetImage(image)
    ret

main endp


    end

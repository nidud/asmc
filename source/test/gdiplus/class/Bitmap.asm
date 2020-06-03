; BITMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include ddraw.inc
include gdiplus.inc

    .code

main proc

; Bitmap(WCHAR*, BOOL = FALSE)
; Bitmap(IStream*, BOOL = FALSE)
; Bitmap(INT, INT, INT, PixelFormat, BYTE*)
; Bitmap(INT, INT, PixelFormat = PixelFormat32bppARGB)
; Bitmap(INT, INT, Graphics*)
; Bitmap(IDirectDrawSurface7*)
; Bitmap(BITMAPINFO*, VOID*)
; Bitmap(HBITMAP, HPALETTE)
; Bitmap(HICON)
; Bitmap(HINSTANCE, WCHAR*)

    local wc:ptr word
    local pi:ptr Image
    local IS:ptr IStream
    local i:int_t
    local ID:ptr IDirectDrawSurface7
    local bi:ptr BITMAPINFO
    local hb:HBITMAP
    local hi:HICON
    local hI:HINSTANCE
    local hp:HPALETTE
    local b:Bitmap
    local rc:ptr Rect
    local rf:ptr RectF
    local pE:ptr EncoderParameters
    local sc:ptr Size
    local sf:ptr SizeF
    local pEffect:ptr Effect
    local pBitmap:ptr Bitmap

    .new p:Bitmap(wc)
    .new p:Bitmap(IS)
    .new p:Bitmap(ID)
    .new p:Bitmap(0,0,0,0,0)
    .new p:Bitmap(i,0,0,0,0)
    .new p:Bitmap(edx,r8d,r9d,0,0)
    .new p:Bitmap(hb, hp)
    .new p:Bitmap(hi)
    .new p:Bitmap(hI, wc)

    p.Release()

    p.FromFile(NULL, FALSE)
    p.FromStream(NULL, FALSE)

    p.Clone(1, 2, 3, 4, 0)
    p.Clone(1.0, 2.0, 3.0, 4.0, 0)
    p.Clone(rc, 0)
    p.Clone(rf, 0)

    p.Save(wc, NULL, 0)
    p.Save(IS, NULL, NULL)

    p.SaveAdd(pi, pE)
    p.SaveAdd(pE)

    p.GetType()
    p.GetPhysicalDimension(sf)
    p.GetBounds(NULL, NULL)
    p.GetWidth()
    p.GetHeight()
    p.GetHorizontalResolution()
    p.GetVerticalResolution()
    p.GetFlags()
    p.GetRawFormat(NULL)
    p.GetPixelFormat()
    p.GetPaletteSize()
    p.GetPalette(NULL, 0)
    p.SetPalette(NULL)
    p.GetThumbnailImage(0, 0, 0, NULL)
    p.GetFrameDimensionsCount()
    p.GetFrameDimensionsList(NULL, 0)
    p.GetFrameCount(NULL)
    p.SelectActiveFrame(NULL, 0)
    p.RotateFlip(NULL)
    p.GetPropertyCount()
    p.GetPropertyIdList(0, NULL)
    p.GetPropertyItemSize(NULL)
    p.GetPropertyItem(NULL, 0, NULL)
    p.GetPropertySize(NULL, NULL)
    p.GetAllPropertyItems(0, 0, NULL)
    p.RemovePropertyItem(NULL)
    p.SetPropertyItem(NULL)
    p.GetEncoderParameterListSize(NULL)
    p.GetEncoderParameterList(NULL, 0, NULL)
if (GDIPVER GE 0x0110)
    p.FindFirstItem(NULL)
    p.FindNextItem(NULL)
    p.GetItemData(NULL)
    p.SetAbort(NULL)
endif
    p.SetNativeImage(NULL)
    p.SetStatus(0)
    p.GetLastStatus()

    p.LockBits(NULL, 0, 0, NULL)
    p.UnlockBits(NULL)
    p.GetPixel(0, 0, NULL)
    p.SetPixel(0, 0, NULL)
    p.ConvertFormat(0, 0, 0, NULL, 0.0)
    p.InitializePalette(NULL, 0, 0, 0, NULL)


    p.ApplyEffect(pEffect, NULL)
    p.ApplyEffect(pBitmap, 0, NULL, NULL, NULL, NULL)

    p.GetHistogram(0, 0, NULL, NULL, NULL, NULL)
    p.GetHistogramSize(0, NULL)
    p.SetResolution(0.0, 0.0)
    p.GetHBITMAP(NULL, NULL)
    p.GetHICON(NULL)

    ret

main endp

    end

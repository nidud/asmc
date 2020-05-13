; BITMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:ptr Bitmap()

    Bitmap()
    p.Release()

    p.FromFile(NULL, FALSE)
    p.FromStream(NULL, FALSE)
    p.Clone()
    p.Save(NULL, NULL, NULL)
    p.Save2(NULL, NULL, NULL)
    p.SaveAdd(NULL)
    p.SaveAdd2(NULL, NULL)
    p.GetType()
    p.GetPhysicalDimension(NULL)
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

    p.FromScan0(0, 0, 0, 0, NULL)
    p.FromScan02(0, 0, 0)
    p.FromGraphics(0, 0, NULL)
    p.FromDirectDrawSurface7(NULL)
    p.FromBITMAPINFO(NULL, NULL)
    p.FromHBITMAP(NULL, NULL)
    p.FromHICON(NULL)
    p.FromResource(NULL, NULL)
    p.CloneI(0, 0, 0, 0, 0)
    p.Clone1(NULL, 0)
    p.CloneF(0.0, 0.0, 0.0, 0.0, 0)
    p.Clone2(NULL, 0)
    p.LockBits(NULL, 0, 0, NULL)
    p.UnlockBits(NULL)
    p.GetPixel(0, 0, NULL)
    p.SetPixel(0, 0, NULL)
    p.ConvertFormat(0, 0, 0, NULL, 0.0)
    p.InitializePalette(NULL, 0, 0, 0, NULL)
    p.ApplyEffect(NULL, NULL)
    p.ApplyEffect2(NULL, 0, NULL, NULL, NULL, NULL)
    p.GetHistogram(0, 0, NULL, NULL, NULL, NULL)
    p.GetHistogramSize(0, NULL)
    p.SetResolution(0.0, 0.0)
    p.GetHBITMAP(NULL, NULL)
    p.GetHICON(NULL)

    ret

main endp

    end

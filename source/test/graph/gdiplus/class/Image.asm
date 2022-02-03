; IMAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  local pWCHAR:ptr word
  local pImage:ptr Image
  local pIStream:ptr IStream
  local pRect:ptr Rect
  local pRectF:ptr RectF
  local pEncoderParameters:ptr EncoderParameters

    ; Image(WCHAR*, BOOL = FALSE)
    ; Image(IStream*, BOOL = FALSE)

   .new p:Image(pWCHAR, TRUE)
   .new p:Image(pIStream, TRUE)

    p.Release()
    p.FromFile(NULL, FALSE)
    p.FromStream(NULL, FALSE)

    p.Clone()

    p.Save(pWCHAR, NULL, 0)
    p.Save(pIStream, NULL, NULL)

    p.SaveAdd(pImage, pEncoderParameters)
    p.SaveAdd(pEncoderParameters)

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
    ret

main endp

    end

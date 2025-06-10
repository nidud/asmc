; FONT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local hdc:HDC
    local hFnt:HFONT
    local pWCHAR:ptr word
    local pFontCollection:ptr FontCollection
    local pFontFamily:ptr FontFamily
    local pLOGFONTA:ptr LOGFONTA
    local pLOGFONTW:ptr LOGFONTW
    local pGraphics:ptr Graphics

   .new p:Font(hdc)
   .new p:Font(hdc, pLOGFONTA)
   .new p:Font(hdc, pLOGFONTW)
   .new p:Font(hdc, hFnt)
   .new p:Font(pFontFamily, 0.0)
   .new p:Font(pFontFamily, 0.0, 0)
   .new p:Font(pFontFamily, 0.0, 0, 0)
   .new p:Font(pWCHAR, 0.0)
   .new p:Font(pWCHAR, 0.0, 0)
   .new p:Font(pWCHAR, 0.0, 0, 0)
   .new p:Font(pWCHAR, 0.0, 0, 0, pFontCollection)

    p.Release()
    p.GetLogFontA(pGraphics, pLOGFONTA)
    p.GetLogFontW(pGraphics, pLOGFONTW)
    p.Clone()
    p.IsAvailable()
    p.GetStyle()
    p.GetSize()
    p.GetUnit()
    p.GetLastStatus()
    p.GetHeight(pGraphics)
    p.GetHeight(0.0)
    p.GetFamily(pFontFamily)
    ret

main endp

    end

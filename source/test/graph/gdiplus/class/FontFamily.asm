; FONTFAMILY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local pWCHAR:ptr word
    local pFontCollection:ptr FontCollection
    local pFontFamily:ptr FontFamily

    .new p:FontFamily()
    .new p:FontFamily(pWCHAR)
    .new p:FontFamily(pWCHAR, pFontCollection)
    .new p:FontFamily(pFontFamily)

    p.Release()

    p.GenericSansSerif()
    p.GenericSerif()
    p.GenericMonospace()

    p.GetFamilyName(pWCHAR, 0)
    p.Clone()
    p.IsAvailable()
    p.IsStyleAvailable(0)

    p.GetEmHeight(0)
    p.GetCellAscent(0)
    p.GetCellDescent(0)
    p.GetLineSpacing(0)

    p.GetLastStatus()
    ret

main endp

    end

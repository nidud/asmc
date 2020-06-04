; FONTCOLLECTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local pINT:ptr sdword
    local pFontFamily:ptr FontFamily

    .new p:FontCollection()

    p.Release()
    p.GetFamilyCount()
    p.GetFamilies(0, pFontFamily, pINT)
    p.GetLastStatus()
    p.SetStatus()
    p.SetStatus(1)
    ret

main endp

    end

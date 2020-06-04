; PRIVATEFONTCOLLECTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local pINT:ptr sdword
    local pWCHAR:ptr word
    local pVOID:ptr
    local pFontFamily:ptr FontFamily

    .new p:PrivateFontCollection()

    p.Release()
    p.GetFamilyCount()
    p.GetFamilies(0, pFontFamily, pINT)
    p.GetLastStatus()
    p.SetStatus()
    p.SetStatus(1)

    p.AddFontFile(pWCHAR)
    p.AddMemoryFont(pVOID, 0)
    ret

main endp

    end

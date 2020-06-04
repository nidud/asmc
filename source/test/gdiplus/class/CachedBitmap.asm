; CACHEDBITMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local pGraphics:ptr Graphics
    local pBitmap:ptr Bitmap

    .new p:CachedBitmap(pBitmap, pGraphics)

    p.Release()
    p.GetLastStatus()
    ret

main endp

    end

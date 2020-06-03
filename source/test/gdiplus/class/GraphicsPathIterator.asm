; GRAPHICSPATHITERATOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local pGraphicsPath:ptr GraphicsPath
    local pINT:ptr int_t
    local pBOOL:ptr BOOL
    local pBYTE:ptr BYTE
    local pPointF:ptr PointF

    .new p:GraphicsPathIterator(pGraphicsPath)

    p.Release()
    p.SetNativeIterator(pGraphicsPath)
    p.SetStatus(1)

    p.NextSubpath(pINT, pINT, pBOOL)
    p.NextSubpath(pGraphicsPath, pBOOL)
    p.NextPathType(pBYTE, pINT, pINT)
    p.NextMarker(pINT, pINT)
    p.NextMarker(pGraphicsPath)
    p.GetCount()
    p.GetSubpathCount()
    p.HasCurve()
    p.Rewind()
    p.Enumerate(pPointF, pBYTE, 0)
    p.CopyData(pPointF, pBYTE, 0, 0)
    p.GetLastStatus()
    ret

main endp

    end


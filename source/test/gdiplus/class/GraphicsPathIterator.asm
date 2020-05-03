; GRAPHICSPATHITERATOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:ptr GraphicsPathIterator;(NULL)

    GraphicsPathIterator(NULL)
    p.GraphicsPathIterator(NULL)
    p.Release()
    p.SetNativeIterator(NULL)
    p.SetStatus(NULL)
    p.NextSubpath(NULL, NULL, NULL)
    p.NextSubpath2(NULL, NULL)
    p.NextPathType(NULL, NULL, NULL)
    p.NextMarker(NULL, NULL, NULL)
    p.NextMarker2(NULL)
    p.GetCount()
    p.GetSubpathCount()
    p.HasCurve()
    p.Rewind()
    p.Enumerate(NULL, NULL, 0)
    p.CopyData(NULL, NULL, 0, 0)
    p.GetLastStatus()
    ret

main endp

    end


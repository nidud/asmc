; CUSTOMLINECAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local pGraphicsPath:ptr GraphicsPath
    local pLineCap:ptr LineCap
    local pCustomLineCap:ptr CustomLineCap

    .new p:CustomLineCap(pGraphicsPath, pGraphicsPath, 0, 0.0)

    p.Release()
    p.Clone()
    p.SetStatus()
    p.SetStatus(1)
    p.SetNativeCap(pCustomLineCap)

    p.SetStrokeCap(0)
    p.SetStrokeCaps(0, 0)
    p.GetStrokeCaps(pLineCap, pLineCap)
    p.SetStrokeJoin(0)
    p.GetStrokeJoin()
    p.SetBaseCap(0)
    p.GetBaseCap()
    p.SetBaseInset(0.0)
    p.GetBaseInset()
    p.SetWidthScale(0.0)
    p.GetWidthScale()
    p.GetLastStatus()
    ret

main endp

    end

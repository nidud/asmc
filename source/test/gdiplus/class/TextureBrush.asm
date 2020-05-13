; TEXTUREBRUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:ptr TextureBrush()

    TextureBrush()
    p.Release()
    p.Create(NULL, 0)
    p.CreateIA(NULL, NULL, NULL)
    p.CreateIAI(NULL, NULL, NULL)
    p.Create2(NULL, 0, 0.0, 0.0, 0.0, 0.0)
    p.Create2I(NULL, 0, 0, 0, 0, 0)
    p.Create2R(NULL, 0, NULL)
    p.Create2IR(NULL, 0, NULL)
    p.SetTransform(NULL)
    p.GetTransform(NULL)
    p.ResetTransform()
    p.MultiplyTransform(NULL, 0)
    p.TranslateTransform(0.0, 0.0, 0)
    p.ScaleTransform(0.0, 0.0, 0)
    p.RotateTransform(0.0, 0)
    p.SetWrapMode(0)
    p.GetWrapMode()
    p.GetImage()
    ret

main endp


    end

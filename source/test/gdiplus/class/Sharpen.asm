; SHARPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:ptr Sharpen()

    Sharpen()
    p.Sharpen()

    p.Release()
    p.GetAuxDataSize()
    p.GetAuxData()
    p.UseAuxData(0)
    p.GetParameterSize(NULL)

    p.SetParameters(NULL)
    p.GetParameters(NULL, NULL)
    ret

main endp

    end

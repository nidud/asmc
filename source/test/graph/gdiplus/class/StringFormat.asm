; STRINGFORMAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

  .new p:StringFormat(0, 0)

    p.Release()

    p.SetFormatFlags(0)
    p.GetFormatFlags()
    p.SetAlignment(0)
    p.GetAlignment()
    p.SetLineAlignment(0)
    p.GetLineAlignment()
    p.SetHotkeyPrefix(0)
    p.GetHotkeyPrefix()
    p.SetTabStops(0.0, 0, NULL)
    p.GetTabStopCount()
    p.GetTabStops(0, NULL, NULL)
    p.SetDigitSubstitution(0, 0)
    p.GetDigitSubstitutionLanguage()
    p.GetDigitSubstitutionMethod()
    p.SetTrimming(0)
    p.GetTrimming()
    p.SetMeasurableCharacterRanges(0, NULL)
    p.GetMeasurableCharacterRangeCount()
    p.GetLastStatus()
    p.SetStatus(0)
    ret

main endp

    end

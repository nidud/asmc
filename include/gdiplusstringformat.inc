ifndef _GDIPLUSSTRINGFORMAT_H
define _GDIPLUSSTRINGFORMAT_H

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template StringFormat fastcall

    nativeFormat    ptr_t ?
    lastError       Status ?
    scratch         int_t ?

    .static StringFormat :abs=<0>, :abs=<LANG_NEUTRAL> {
        mov this.nativeFormat,NULL
        GdipCreateStringFormat(_1, _2, addr this.nativeFormat)
        mov this.lastError,eax
        }
    .static Release {
        GdipDeleteStringFormat(this.nativeFormat)
        }
    .static SetStatus watcall :size_t {
        test    eax,eax
        cmovz   eax,this.lastError
        mov     this.lastError,eax
        }
    .static SetFormatFlags :abs {
        this.SetStatus(GdipSetStringFormatFlags(this.nativeFormat, _1))
        }
    .static GetFormatFlags {
        this.SetStatus(GdipGetStringFormatFlags(this.nativeFormat, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetAlignment :abs {
        this.SetStatus(GdipSetStringFormatAlign(this.nativeFormat, _1))
        }
    .static GetAlignment {
        this.SetStatus(GdipGetStringFormatAlign(this.nativeFormat, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetLineAlignment :abs {
        this.SetStatus(GdipSetStringFormatLineAlign(this.nativeFormat, _1))
        }
    .static GetLineAlignment {
        this.SetStatus(GdipGetStringFormatLineAlign(this.nativeFormat, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetHotkeyPrefix :abs {
        this.SetStatus(GdipSetStringFormatHotkeyPrefix(this.nativeFormat, _1))
        }
    .static GetHotkeyPrefix {
        this.SetStatus(GdipGetStringFormatHotkeyPrefix(this.nativeFormat, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetTabStops :abs, :abs, :abs {
        this.SetStatus(GdipSetStringFormatTabStops(this.nativeFormat, _1, _2, _3))
        }
    .static GetTabStopCount {
        this.SetStatus(GdipGetStringFormatTabStopCount(this.nativeFormat, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetTabStops :abs, :abs, :abs {
        this.SetStatus(GdipGetStringFormatTabStops(this.nativeFormat, _1, _2, _3))
        }
    .static SetDigitSubstitution :abs, :abs {
        this.SetStatus(GdipSetStringFormatDigitSubstitution(this.nativeFormat, _1, _2))
        }
    .static GetDigitSubstitutionLanguage {
        this.SetStatus(GdipGetStringFormatDigitSubstitution(this.nativeFormat, addr this.scratch, NULL))
        mov eax,this.scratch
        }
    .static GetDigitSubstitutionMethod {
        this.SetStatus(GdipGetStringFormatDigitSubstitution(this.nativeFormat, NULL, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetTrimming :abs {
        this.SetStatus(GdipSetStringFormatTrimming(this.nativeFormat, _1))
        }
    .static GetTrimming {
        this.SetStatus(GdipGetStringFormatTrimming(this.nativeFormat, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetMeasurableCharacterRanges :abs, :abs {
        this.SetStatus(GdipSetStringFormatMeasurableCharacterRanges(this.nativeFormat, _1, _2))
        }
    .static GetMeasurableCharacterRangeCount {
        GdipGetStringFormatMeasurableCharacterRangeCount(this.nativeFormat, addr this.scratch)
        mov eax,this.scratch
        }
    .static GetLastStatus {
        mov eax,this.lastError
        mov this.lastError,Ok
        }
    .ends
    GpStringFormat typedef StringFormat

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; NOT _GDIPLUSSTRINGFORMAT_H

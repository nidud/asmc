ifndef _GDIPLUSSTRINGFORMAT_H
_GDIPLUSSTRINGFORMAT_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template StringFormat

    nativeFormat    ptr_t ?
    lastError       Status ?
    scratch         int_t ?

    .operator StringFormat :abs=<0>, :abs=<LANG_NEUTRAL>, :vararg {
        mov this.nativeFormat,NULL
        GdipCreateStringFormat(_1, _2, addr this.nativeFormat)
        mov this.lastError,eax
        }
    .operator Release {
        GdipDeleteStringFormat([this].StringFormat.nativeFormat)
        }

    .operator SetFormatFlags :abs, :vararg {
        GdipSetStringFormatFlags(this.nativeFormat, _1)
        this.SetStatus()
        }

    .operator GetFormatFlags :vararg {
        GdipGetStringFormatFlags(this.nativeFormat, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator SetAlignment :abs, :vararg {
        GdipSetStringFormatAlign(this.nativeFormat, _1)
        this.SetStatus()
        }

    .operator GetAlignment :vararg {
        GdipGetStringFormatAlign(this.nativeFormat, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator SetLineAlignment :abs, :vararg {
        GdipSetStringFormatLineAlign(this.nativeFormat, _1)
        this.SetStatus()
        }

    .operator GetLineAlignment :vararg {
        GdipGetStringFormatLineAlign(this.nativeFormat, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator SetHotkeyPrefix :abs, :vararg {
        GdipSetStringFormatHotkeyPrefix(this.nativeFormat, _1)
        this.SetStatus()
        }

    .operator GetHotkeyPrefix :vararg {
        GdipGetStringFormatHotkeyPrefix(this.nativeFormat, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator SetTabStops :abs, :abs, :abs, :vararg {
        GdipSetStringFormatTabStops(this.nativeFormat, _1, _2, _3)
        this.SetStatus()
        }

    .operator GetTabStopCount :abs, :vararg {
        GdipGetStringFormatTabStopCount(this.nativeFormat, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetTabStops :abs, :abs, :abs, :vararg {
        GdipGetStringFormatTabStops(this.nativeFormat, _1, _2, _3)
        this.SetStatus()
        }

    .operator SetDigitSubstitution :abs, :abs, :vararg {
        GdipSetStringFormatDigitSubstitution(this.nativeFormat, _1, _2)
        this.SetStatus()
        }

    .operator GetDigitSubstitutionLanguage :vararg {
        GdipGetStringFormatDigitSubstitution(this.nativeFormat, addr this.scratch, NULL)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetDigitSubstitutionMethod :vararg {
        GdipGetStringFormatDigitSubstitution(this.nativeFormat, NULL, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator SetTrimming :abs, :vararg {
        GdipSetStringFormatTrimming(this.nativeFormat, _1)
        this.SetStatus()
        }

    .operator GetTrimming :vararg {
        GdipGetStringFormatTrimming(this.nativeFormat, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator SetMeasurableCharacterRanges :abs, :abs, :vararg {
        GdipSetStringFormatMeasurableCharacterRanges(this.nativeFormat, _1, _2)
        this.SetStatus()
        }

    .operator GetMeasurableCharacterRangeCount :vararg {
        GdipGetStringFormatMeasurableCharacterRangeCount(this.nativeFormat, addr this.scratch)
        mov eax,this.scratch
        }

    .operator GetLastStatus {
        mov eax,[this].StringFormat.lastError
        mov [this].StringFormat.lastError,Ok
        }

    .operator SetStatus :vararg {
        ifnb <_1>
            ifdif <_1>,<eax>
                mov eax,_1
            endif
        endif
        test    eax,eax
        cmovz   eax,this.lastError
        mov     this.lastError,eax
        }
    .ends
    GpStringFormat typedef StringFormat

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; NOT _GDIPLUSSTRINGFORMAT_H

ifndef _GDIPLUSSTRINGFORMAT_H
_GDIPLUSSTRINGFORMAT_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template StringFormat

    nativeFormat    ptr_t ?
    lastError       Status ?
    memState        Status ?


    .operator StringFormat :abs, :abs {

        .new stringformat:ptr StringFormat

        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !GdipAlloc(StringFormat)
                mov [rax].StringFormat.memState,Ok
            .else
                mov [rax].StringFormat.memState,NotImplemented
            .endif
            mov stringformat,rax
            mov [rax].StringFormat.nativeFormat,NULL
            GdipCreateStringFormat(_1, _2, rax)
            mov edx,eax
            mov rax,stringformat
            mov [rax].StringFormat.lastError,edx
        .until 1
        retm<rax>
        }

    .operator Release {

        mov stringformat,this

        GdipDeleteStringFormat([this].StringFormat.nativeFormat)

        mov this,stringformat
        .if [this].StringFormat.memState != NotImplemented

            GdipFree(this)
        .endif
        exitm<>
        }

    .operator CloneString :ptr StringFormat {
        mov stringformat,this
        .if _1
            mov _1,[_1]
        .endif
        xchg this,_1
        GdipCloneStringFormat(this, _1)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator Clone {

        .new clonedStringFormat:ptr StringFormat

        mov stringformat,this
        mov clonedStringFormat,StringFormat(0, 0)
        .if rax
            mov this,stringformat
            GdipCloneStringFormat([this].StringFormat.nativeFormat, &[rax].StringFormat.nativeFormat)
            stringformat.SetStatus(eax)
            clonedStringFormat.SetStatus(eax)
            mov rax,clonedStringFormat
        .endif
        retm<rax>
        }

    .operator SetFormatFlags :SINT {
        mov stringformat,this
        GdipSetStringFormatFlags([this].StringFormat.nativeFormat, _1)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator GetFormatFlags {

        .new flags:SINT

        mov stringformat,this
        GdipGetStringFormatFlags([this].StringFormat.nativeFormat, &flags)
        stringformat.SetStatus(eax)

        mov eax,flags
        retm <eax>
        }


    .operator SetAlignment :StringAlignment {
        mov stringformat,this
        GdipSetStringFormatAlign([this].StringFormat.nativeFormat, _1)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator GetAlignment {

        .new alignment:StringAlignment

        mov stringformat,this
        GdipGetStringFormatAlign([this].StringFormat.nativeFormat, &alignment)
        stringformat.SetStatus(eax)

        mov eax,alignment
        retm <eax>
        }

    .operator SetLineAlignment :StringAlignment {
        mov stringformat,this
        GdipSetStringFormatLineAlign([this].StringFormat.nativeFormat, _1)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator GetLineAlignment {

        .new alignment:StringAlignment

        mov stringformat,this
        GdipGetStringFormatLineAlign([this].StringFormat.nativeFormat, &alignment)
        stringformat.SetStatus(eax)

        mov eax,alignment
        retm <eax>
        }

    .operator SetHotkeyPrefix :HotkeyPrefix {
        mov stringformat,this
        GdipSetStringFormatHotkeyPrefix([this].StringFormat.nativeFormat, _1)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator GetHotkeyPrefix {

        .new hotkeyPrefix:HotkeyPrefix

        mov stringformat,this
        GdipGetStringFormatHotkeyPrefix([this].StringFormat.nativeFormat, &hotkeyPrefix)
        stringformat.SetStatus(eax)

        mov eax,hotkeyPrefix
        retm <eax>
        }

    .operator SetTabStops :REAL, :SINT, :ptr REAL {
        mov stringformat,this
        GdipSetStringFormatTabStops([this].StringFormat.nativeFormat, _1, _2, _3)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator GetTabStopCount {

        .new count:SINT

        mov stringformat,this
        GdipGetStringFormatTabStopCount([this].StringFormat.nativeFormat, &count)
        stringformat.SetStatus(eax)

        mov eax,count
        retm <eax>
        }

    .operator GetTabStops :SINT, :ptr REAL, :ptr REAL {
        mov stringformat,this
        GdipGetStringFormatTabStops([this].StringFormat.nativeFormat, _1, _2, _3)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator SetDigitSubstitution :LANGID, :StringDigitSubstitute {
        mov stringformat,this
        GdipSetStringFormatDigitSubstitution([this].StringFormat.nativeFormat, _1, _2)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator GetDigitSubstitutionLanguage {

        .new language:LANGID

        mov stringformat,this
        GdipGetStringFormatDigitSubstitution([this].StringFormat.nativeFormat, &language, NULL)
        stringformat.SetStatus(eax)

        movzx eax,language
        retm <eax>
        }

    .operator GetDigitSubstitutionMethod {

        .new substitute:StringDigitSubstitute

        mov stringformat,this
        GdipGetStringFormatDigitSubstitution([this].StringFormat.nativeFormat, NULL, &substitute)
        stringformat.SetStatus(eax)

        mov eax,substitute
        retm <eax>
        }

    .operator SetTrimming :StringTrimming {
        mov stringformat,this
        GdipSetStringFormatTrimming([this].StringFormat.nativeFormat, _1)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator GetTrimming {

        .new trimming:StringTrimming

        mov stringformat,this
        GdipGetStringFormatTrimming([this].StringFormat.nativeFormat, &trimming)
        stringformat.SetStatus(eax)

        mov eax,trimming
        retm <eax>
        }

    .operator SetMeasurableCharacterRanges :SINT, :ptr CharacterRange {
        mov stringformat,this
        GdipSetStringFormatMeasurableCharacterRanges([this].StringFormat.nativeFormat, _1, _2)
        exitm<stringformat.SetStatus(eax)>
        }

    .operator GetMeasurableCharacterRangeCount {

        .new count:SINT

        mov stringformat,this
        GdipGetStringFormatMeasurableCharacterRangeCount([this].StringFormat.nativeFormat, &count)
        mov eax,count
        retm <eax>
        }

    .operator GetLastStatus {
        mov eax,[this].StringFormat.lastError
        mov [this].StringFormat.lastError,Ok
        retm <eax>
        }

    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].StringFormat.lastError,eax
        .endif
        retm <eax>
        }
    .ends
    GpStringFormat typedef StringFormat

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; NOT _GDIPLUSSTRINGFORMAT_H

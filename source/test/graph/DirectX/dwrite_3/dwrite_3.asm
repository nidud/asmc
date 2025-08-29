include stdio.inc
include dwrite_3.inc

.code

wmain proc

    .new dwrite_factory:ptr IDWriteFactory3
    .if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, &IID_IDWriteFactory3, &dwrite_factory)))
        .return( 1 )
    .endif

    .new font_set:ptr IDWriteFontSet
    .if (FAILED(dwrite_factory.GetSystemFontSet(&font_set)))
        .return( 1 )
    .endif

    wprintf("There is %d fonts installed, searhing for Consolas...\n", font_set.GetFontCount())

    .new property_ids[3]:DWRITE_FONT_PROPERTY_ID = {
        DWRITE_FONT_PROPERTY_ID_WIN32_FAMILY_NAME,
        DWRITE_FONT_PROPERTY_ID_FULL_NAME,
        DWRITE_FONT_PROPERTY_ID_POSTSCRIPT_NAME
        }
    .for ( ebx = 0 : ebx < lengthof(property_ids) : ebx++ )

        .new property:DWRITE_FONT_PROPERTY = { property_ids[rbx*4],  "Consolas", "" }
        .new filtered_set:ptr IDWriteFontSet
        .new hr:HRESULT = font_set.GetMatchingFonts_2(&property, 1, &filtered_set)

        .if (FAILED(hr) || !filtered_set)
            .continue
        .endif

        .new count:int_t = filtered_set.GetFontCount()
        .new values:ptr IDWriteStringList
        .if (SUCCEEDED(filtered_set.GetPropertyValues(DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FACE_NAME, &values)))

           .new buffer[256]:WCHAR
           .new names[3]:LPWSTR = { "Win32 Family", "Full", "Postscript" }
            mov count,values.GetCount()
            wprintf(" %s name(%d): ", names[rbx*LPWSTR], count)
            .for ( edi = 0 : edi < count : edi++ )
                .if (SUCCEEDED(values.GetString(edi, &buffer, 256)))
                    .if ( edi )
                        wprintf(", ")
                    .endif
                    wprintf(&buffer)
                .endif
            .endf
            wprintf("\n")
            values.Release()
        .endif
        filtered_set.Release()
    .endf
    font_set.Release()
    dwrite_factory.Release()
   .return( 0 )

wmain endp

    end

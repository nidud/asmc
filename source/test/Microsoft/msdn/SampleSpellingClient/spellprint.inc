
; Implementation of helper functions to print various spell checking information

PrintAvailableLanguages proto spellCheckerFactory:abs {

    .new enumLanguages:ptr IEnumString = nullptr
    .new hr:HRESULT = spellCheckerFactory.get_SupportedLanguages(&enumLanguages)

    .if (SUCCEEDED(hr))
        wprintf("Available languages:\n")
    .endif
    .if (SUCCEEDED(hr))
        mov hr,PrintEnumString(enumLanguages, nullptr)
    .endif
    .if ( enumLanguages != nullptr )
        enumLanguages.Release()
    .endif

    PrintErrorIfFailed("PrintAvailableLanguages", hr)
    mov eax,hr
    }

PrintSpellingError proto spellChecker:abs, :PCWSTR, :ptr ISpellingError {

    .new ptext:PCWSTR = _2
    .new spellingError:ptr ISpellingError = _3
    .new startIndex:ULONG = 0
    .new errorLength:ULONG = 0
    .new correctiveAction:CORRECTIVE_ACTION = CORRECTIVE_ACTION_NONE
    .new hr:HRESULT = spellingError.get_StartIndex(&startIndex)

    .if (SUCCEEDED(hr))

        mov hr,spellingError.get_Length(&errorLength)
    .endif

    .if(SUCCEEDED(hr))

        mov hr,spellingError.get_CorrectiveAction(&correctiveAction)
    .endif

    .if (SUCCEEDED(hr))

       .new misspelled[MAX_PATH]:wchar_t
        imul r8d,startIndex,wchar_t
        add r8,ptext
        mov hr,StringCchCopyN(&misspelled, ARRAYSIZE(misspelled), r8, errorLength)

        .if (SUCCEEDED(hr))

            mov r8d,startIndex
            add r8d,errorLength
            dec r8d
            wprintf("%s [%u, %u] is misspelled. ", &misspelled, startIndex, r8d)

            .if ( correctiveAction == CORRECTIVE_ACTION_GET_SUGGESTIONS )

                wprintf("Suggestions:\n")
               .new enumSuggestions:ptr IEnumString = nullptr
                mov hr,spellChecker.Suggest(&misspelled, &enumSuggestions)
                .if (SUCCEEDED(hr))

                    mov hr,PrintEnumString(enumSuggestions, "\t")
                    wprintf("\n")
                    enumSuggestions.Release()
                .endif

            .elseif ( correctiveAction == CORRECTIVE_ACTION_REPLACE )

                wprintf("It should be autocorrected to:\n")
               .new replacement:PWSTR = nullptr
                mov hr,spellingError.get_Replacement(&replacement)
                .if (SUCCEEDED(hr))

                    wprintf("\t%s\n\n", replacement)
                    CoTaskMemFree(replacement)
                .endif

            .elseif ( correctiveAction == CORRECTIVE_ACTION_DELETE )

                wprintf("It should be deleted.\n\n")
            .else
                wprintf("Invalid corrective action.\n\n")
            .endif
        .endif
    .endif
    PrintErrorIfFailed("PrintSpellingError", hr)
    mov eax,hr
    }

PrintSpellingErrors proto spellChecker:abs, :PCWSTR, :ptr IEnumSpellingError {

    .new ptext:PCWSTR = _2
    .new enumSpellingError:ptr IEnumSpellingError = _3
    .new hr:HRESULT = S_OK
    .new numErrors:size_t = 0

    .while ( hr == S_OK )

       .new spellingError:ptr ISpellingError = nullptr
        mov hr,enumSpellingError.Next(&spellingError)
        .if ( hr == S_OK )

            inc numErrors
            mov hr,PrintSpellingError(spellChecker, ptext, spellingError)
            spellingError.Release()
        .endif
    .endw

    .if ( numErrors == 0 )

        wprintf("No errors.\n\n")
    .endif

    PrintErrorIfFailed("PrintSpellingErrors", hr)
    mov eax,hr
    .if (SUCCEEDED(hr))
        mov eax,S_OK
    .endif
    }

PrintLanguage proto spellChecker:abs {

    .new languageTag:PWSTR = nullptr
    .new hr:HRESULT = spellChecker.get_LanguageTag(&languageTag)

    .if (SUCCEEDED(hr))
        wprintf("Language: %s\n\n", languageTag)
        CoTaskMemFree(languageTag)
    .endif

    PrintErrorIfFailed("PrintLanguage", hr)
    mov eax,hr
    }

PrintSpellCheckerIdAndName proto :ptr ISpellChecker {

    .new spellChecker:ptr ISpellChecker = _1
    .new spellCheckerId:PWSTR = nullptr
    .new localizedName:PWSTR = nullptr
    .new hr:HRESULT = spellChecker.get_Id(&spellCheckerId)

    .if (SUCCEEDED(hr))

        mov hr,spellChecker.get_LocalizedName(&localizedName)
    .endif

    .if (SUCCEEDED(hr))

        wprintf("Provider: %s (%s)\n\n", spellCheckerId, localizedName)
    .endif

    .if ( localizedName != nullptr )

        CoTaskMemFree(localizedName)
    .endif

    .if ( spellCheckerId != nullptr )

        CoTaskMemFree(spellCheckerId)
    .endif

    PrintErrorIfFailed("PrintSpellCheckerIdAndName", hr)
    mov eax,hr
    }

PrintOptionHeading proto :ptr IOptionDescription {

    .new optionDescription:ptr IOptionDescription = _1
    .new optionHeading:PWSTR = nullptr
    .new hr:HRESULT = optionDescription.get_Heading(&optionHeading)

    .if (SUCCEEDED(hr))

        .if (wcslen(optionHeading) > 0)

            wprintf("\t%s\n", optionHeading)
        .endif
        CoTaskMemFree(optionHeading)
    .endif

    PrintErrorIfFailed("PrintOptionHeading", hr)
    mov eax,hr
    }

PrintOptionDescription proto :ptr IOptionDescription {

    .new optionDescription:ptr IOptionDescription = _1
    .new description:PWSTR = nullptr
    .new hr:HRESULT = optionDescription.get_Description(&description)

    .if (SUCCEEDED(hr))

        .if (wcslen(description) > 0)

            wprintf("\t%s\n", description)
        .endif
        CoTaskMemFree(description)
    .endif

    PrintErrorIfFailed("PrintOptionDescription", hr)
    mov eax,hr
    }

PrintSingleLabel proto :ptr IEnumString, :BYTE {

    .new enumString:ptr IEnumString = _1
    .new optionValue:BYTE = _2
    .new plabel:LPOLESTR = nullptr
    .new hr:HRESULT = enumString.Next(1, &plabel, nullptr)

    .if ( hr == S_OK )
        .new optionState:PCWSTR = "off"
        .if ( optionValue == 1 )
            mov optionState,&@CStr("on")
        .endif
        wprintf("\t%s (current %s)\n", plabel, optionState)
        CoTaskMemFree(plabel)
    .endif

    PrintErrorIfFailed("PrintSingleLabel", hr)
    mov eax,hr
    .if (SUCCEEDED(hr))
        mov eax,S_OK
    .endif
    }

PrintMultipleLabels proto :ptr IEnumString, :BYTE {

    .new enumString:ptr IEnumString = _1
    .new optionValue:BYTE = _2
    .new hr:HRESULT = S_OK
    .new i:int_t

    .for ( i = 0: hr == S_OK : ++i )
       .new plabel:LPOLESTR = nullptr
        mov hr,enumString.Next(1, &plabel, nullptr)
        .if ( hr == S_OK )
            .new currentText:PCWSTR = "(current)"
            .if ( optionValue == byte ptr i)
                mov currentText, &@CStr("")
            .endif
            wprintf("\t[%d] %s %s\n", i, plabel, currentText)
            CoTaskMemFree(plabel)
        .endif
    .endf

    PrintErrorIfFailed("PrintMultipleLabels", hr)
    mov eax,hr
    .if (SUCCEEDED(hr))
        mov eax,S_OK
    .endif
    }

PrintOptionLabels proto spellChecker:abs, :PCWSTR, :ptr IOptionDescription {

    .new optionId:PCWSTR = _2
    .new optionDescription:ptr IOptionDescription = _3

    .new optionValue:BYTE
    .new hr:HRESULT = spellChecker.GetOptionValue(optionId, &optionValue)

    .if (SUCCEEDED(hr))

       .new enumLabels:ptr IEnumString = nullptr
        mov hr,optionDescription.get_Labels(&enumLabels)

        .if (SUCCEEDED(hr))

           .new hasOneLabel:BOOL
            mov hr,HasSingleString(enumLabels, &hasOneLabel)

            .if (SUCCEEDED(hr))

                .if (hasOneLabel)

                    mov hr,PrintSingleLabel(enumLabels, optionValue)

                .else

                    mov hr,PrintMultipleLabels(enumLabels, optionValue)
                .endif
            .endif

        .endif

        .if ( enumLabels != nullptr )

            enumLabels.Release()
        .endif
    .endif

    PrintErrorIfFailed("PrintOptionLabels", hr)
    mov eax,hr
    }

PrintOption proto spellChecker:abs, :PCWSTR {

    .new optionId:PCWSTR = _2

     wprintf("\t%s\n", _2)

    .new optionDescription:IOptionDescription = nullptr
    .new hr:HRESULT = spellChecker.GetOptionDescription(optionId, &optionDescription)

    .if (SUCCEEDED(hr))
        mov hr,PrintOptionHeading(optionDescription)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,PrintOptionDescription(optionDescription)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,PrintOptionLabels(spellChecker, optionId, optionDescription)
    .endif

    PrintErrorIfFailed("PrintOption", hr)
    mov eax,hr
    }

PrintSpellingOptions proto spellChecker:abs {

     wprintf("Options:\n")

    .new enumOptionIds:ptr IEnumString = nullptr
    .new hr:HRESULT = spellChecker.get_OptionIds(&enumOptionIds)

    .while ( hr == S_OK )
        .new optionId:LPOLESTR = nullptr
        mov hr,enumOptionIds.Next(1, &optionId, nullptr)
        .if ( hr == S_OK )
            mov hr,PrintOption(spellChecker, optionId)
            wprintf("\n")
            CoTaskMemFree(optionId)
        .endif
    .endw

    wprintf("\n")
    .if ( enumOptionIds != nullptr )
        enumOptionIds.Release()
    .endif
    PrintErrorIfFailed("PrintSpellingOptions", hr)
    mov eax,hr
    }


PrintInfoAndOptions proto spellChecker:abs {

    .new hr:HRESULT = PrintLanguage(spellChecker)

    .if (SUCCEEDED(hr))
        mov hr,PrintSpellCheckerIdAndName(spellChecker)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,PrintSpellingOptions(spellChecker)
    .endif

    PrintErrorIfFailed("PrintInfoAndOptions", hr)
    mov eax,hr
    }


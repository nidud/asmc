
; Implementation of commands of the interactive spell checking session

    .code

ReadSingleWord proto buffer:PCWSTR, maxWordSize:size_t, pword:PWSTR {
    .new count:int_t = swscanf_s(buffer, "%s", pword, maxWordSize)
    .new hr:HRESULT = E_FAIL
    .if ( count == 1 )
        mov hr,S_OK
    .endif
    PrintErrorIfFailed("ReadSingleWord", hr)
    mov eax,hr
    }

ReadTwoWords proto buffer:PCWSTR, maxFirstSize:size_t, first:PWSTR, maxSecondSize:size_t, second:PWSTR {
    .new count:int_t = swscanf_s(buffer, "%s %s", first, maxFirstSize, second, maxSecondSize)
    .new hr:HRESULT = E_FAIL
    .if ( count == 2 )
        mov hr,S_OK
    .endif
    PrintErrorIfFailed("ReadTwoWords", hr)
    mov eax,hr
    }

ReadInteger proto buffer:PCWSTR, integer:ptr int_t {
    .new count:int_t = swscanf_s(buffer, "%d", integer)
    .new hr:HRESULT = E_FAIL
    .if ( count == 1 )
        mov hr,S_OK
    .endif
    PrintErrorIfFailed("ReadInteger", hr)
    mov eax,hr
    }

ReadText proto buffer:PCWSTR, maxTextSize:size_t, ptext:PWSTR {
    .new count:int_t = swscanf_s(buffer, " %[^\n]", ptext, maxTextSize)
    .new hr:HRESULT = E_FAIL
    .if ( count == 1 )
        mov hr,S_OK
    .endif
    PrintErrorIfFailed("ReadText", hr)
    mov eax,hr
    }

AddCommand proto spellChecker:abs, buffer:PCWSTR {
    .new text[MAX_PATH]:wchar_t
     mov rcx,rdx
    .new hr:HRESULT = ReadSingleWord(rcx, ARRAYSIZE(text), &text)
    .if (SUCCEEDED(hr))
        mov hr,spellChecker._Add(&text)
    .endif
    PrintErrorIfFailed("AddCommand", hr)
    mov eax,hr
    }

IgnoreCommand proto spellChecker:abs, buffer:PCWSTR {
    mov rcx,buffer
    .new text[MAX_PATH]:wchar_t
    .new hr:HRESULT = ReadSingleWord(rcx, ARRAYSIZE(text), &text)
    .if (SUCCEEDED(hr))
        mov hr,spellChecker.Ignore(&text)
    .endif
    PrintErrorIfFailed("IgnoreCommand", hr)
    mov eax,hr
    }

AutoCorrectCommand proto spellChecker:abs, buffer:PCWSTR {
    mov rcx,buffer
    .new from[MAX_PATH]:wchar_t
    .new to[MAX_PATH]:wchar_t
    .new hr:HRESULT = ReadTwoWords(rcx, ARRAYSIZE(from), &from, ARRAYSIZE(to), &to)
    .if (SUCCEEDED(hr))
        mov hr,spellChecker.AutoCorrect(&from, &to)
    .endif
    PrintErrorIfFailed("AutoCorrectCommand", hr)
    mov eax,hr
    }

CheckCommand proto spellChecker:abs, buffer:PCWSTR {
    mov rcx,buffer
    .new text[MAX_PATH]:wchar_t
    .new enumSpellingError:ptr IEnumSpellingError = nullptr
    .new hr:HRESULT = ReadText(rcx, ARRAYSIZE(text), &text)
    .if (SUCCEEDED(hr))
        mov hr,spellChecker.Check(&text, &enumSpellingError)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,PrintSpellingErrors(spellChecker, &text, enumSpellingError)
        enumSpellingError.Release()
    .endif
    mov eax,hr
    }

CheckAsYouTypeCommand proto spellChecker:abs, buffer:PCWSTR {
    mov rcx,buffer
    .new text[MAX_PATH]:wchar_t
    .new enumSpellingError:ptr IEnumSpellingError = nullptr
    .new hr:HRESULT = ReadText(rcx, ARRAYSIZE(text), &text)
    .if (SUCCEEDED(hr))
        mov hr,spellChecker.ComprehensiveCheck(&text, &enumSpellingError)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,PrintSpellingErrors(spellChecker, &text, enumSpellingError)
        enumSpellingError.Release()
    .endif
    mov eax,hr
    }



; Implementation of a sample spell checking client

ifdef _LIBCMT
.pragma comment(linker,"/defaultlib:libcmtd")
.pragma comment(linker,"/defaultlib:legacy_stdio_definitions")
endif
define NTDDI_VERSION NTDDI_WIN8

include stdio.inc
include fcntl.inc
include io.inc
include strsafe.inc
include objidl.inc
include spellcheck.inc
include tchar.inc

include util.inc
include spellprint.inc
include commands.inc
include onspellcheckerchanged.inc

RunCommandLoop proc uses rsi rdi spellChecker:ptr ISpellChecker

    wprintf("Commands:\n")
    wprintf("quit - Quit\n")
    wprintf("add <word> - Add word\n")
    wprintf("ac <word> <word> - Add autocorrect pair\n")
    wprintf("ign <word> - Ignore word\n")
    wprintf("chkb <text> - Check text (batch - pasted text or file open)\n")
    wprintf("chk <text> - Check text (as you type)\n")

    .new hr:HRESULT = S_OK
    .while (SUCCEEDED(hr))

        wprintf("> ")
       .new line[MAX_PATH]:wchar_t
        lea rsi,line
        mov hr,StringCchGets(rsi, ARRAYSIZE(line))

        .if (SUCCEEDED(hr))

            .new command[MAX_PATH]:wchar_t
             lea rdi,command
            .if ( swscanf_s(rsi, "%s", rdi, ARRAYSIZE(command)) != 1 )
                mov hr,E_FAIL
            .endif
            .if (SUCCEEDED(hr))

                .new lineSize:size_t = wcslen(rsi)
                .new cmdSize:size_t = wcslen(rdi)

                .if ( cmdSize == lineSize )

                    .if ( wcscmp("quit", rdi) == 0 )

                        .break

                    .else

                        wprintf("Invalid command\n")
                    .endif

                .else

                    lea rsi,[rsi+wcslen(rdi)*2]

                    .if ( wcscmp("add", rdi) == 0 )

                        mov hr,AddCommand(spellChecker, rsi)

                    .elseif ( wcscmp("ac", rdi) == 0 )

                        mov hr,AutoCorrectCommand(spellChecker, rsi)

                    .elseif ( wcscmp("ign", rdi) == 0 )

                        mov hr,IgnoreCommand(spellChecker, rsi)

                    .elseif ( wcscmp("chkb", rdi) == 0 )

                        mov hr,CheckCommand(spellChecker, rsi)

                    .elseif ( wcscmp("chk", rdi) == 0 )

                        mov hr,CheckAsYouTypeCommand(spellChecker, rsi)

                    .else

                        wprintf("Invalid command\n")
                    .endif

                .endif
            .endif
        .endif
    .endw

    PrintErrorIfFailed("RunCommandLoop", hr)
    .return hr

RunCommandLoop endp

RunSpellCheckingLoop proc spellChecker:ptr ISpellChecker

    .new eventListener:ptr OnSpellCheckerChanged = nullptr
    .new hr:HRESULT = PrintInfoAndOptions(spellChecker)
    .if (SUCCEEDED(hr))

        mov hr,StartListeningToChangeEvents(spellChecker, &eventListener)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,RunCommandLoop(spellChecker)
    .endif

    .if ( eventListener != nullptr )

        StopListeningToChangeEvents(spellChecker, eventListener)
    .endif

    PrintErrorIfFailed("RunSpellCheckingLoop", hr)
    .return hr

RunSpellCheckingLoop endp

StartSpellCheckingSession proc spellCheckerFactory:ptr ISpellCheckerFactory, languageTag:PCWSTR

    .new isSupported:BOOL = FALSE
    .new hr:HRESULT = spellCheckerFactory.IsSupported(languageTag, &isSupported)
    .if (SUCCEEDED(hr))

        .if ( isSupported == FALSE )

            wprintf("Language tag %s is not supported.\n", languageTag)

        .else

            .new spellChecker:ptr ISpellChecker = nullptr
            mov hr,spellCheckerFactory.CreateSpellChecker(languageTag, &spellChecker)

            .if (SUCCEEDED(hr))

                mov hr,RunSpellCheckingLoop(spellChecker)
            .endif

            .if ( spellChecker != nullptr )

                spellChecker.Release()
            .endif
        .endif
    .endif

    PrintErrorIfFailed("StartSpellCheckingSession", hr)
   .return hr

StartSpellCheckingSession endp

CreateSpellCheckerFactory proc spellCheckerFactory:ptr ptr ISpellCheckerFactory

    .new hr:HRESULT = CoCreateInstance(&CLSID_SpellCheckerFactory, nullptr,
            CLSCTX_INPROC_SERVER, &IID_ISpellCheckerFactory, spellCheckerFactory)

    .if (FAILED(hr))

        mov rdx,spellCheckerFactory
        xor eax,eax
        mov [rdx],rax
    .endif
    PrintErrorIfFailed("CreateSpellCheckerFactory", hr)

   .return hr

CreateSpellCheckerFactory endp

wmain proc argc:int_t, argv:ptr PCWSTR

    .new originalOutputMode:int_t = _setmode(_fileno(stdout), _O_U16TEXT)
    .new hr:HRESULT = S_OK

    .if ( originalOutputMode == -1 )
        mov hr,E_FAIL
    .endif
    .if (SUCCEEDED(hr))

        mov hr,CoInitializeEx(nullptr, COINIT_MULTITHREADED)
    .endif

    .new WasCOMInitialized:BOOL = FALSE
    .if (SUCCEEDED(hr))
        mov WasCOMInitialized,TRUE
    .endif

    .new spellCheckerFactory:ptr ISpellCheckerFactory = nullptr
    .if (SUCCEEDED(hr))

        mov hr,CreateSpellCheckerFactory(&spellCheckerFactory)
    .endif

    .if (SUCCEEDED(hr))

        .if (argc == 1)

            mov hr,PrintAvailableLanguages(spellCheckerFactory)

        .elseif (argc == 2)

            mov rdx,argv
           .new languageTag:PCWSTR = [rdx+size_t]
            mov hr,StartSpellCheckingSession(spellCheckerFactory, languageTag)

        .else

            wprintf("Usage:\n")
            wprintf("\"SampleClient\" - lists all the available languages\n")
            wprintf("\"SampleClient <language tag>\" - "
                    "initiates an interactive spell checking session in the language, if supported\n")
        .endif
    .endif

    .if ( spellCheckerFactory != nullptr )

        spellCheckerFactory.Release()
    .endif

    .if (WasCOMInitialized)

        CoUninitialize()
    .endif

    PrintErrorIfFailed("wmain", hr)
    xor eax,eax
    .if (FAILED(hr))
        inc eax
    .endif
    ret

wmain endp

    end _tstart

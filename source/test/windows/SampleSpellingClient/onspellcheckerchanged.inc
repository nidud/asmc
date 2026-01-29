
; Implementation of the listener class for changes that may affect spell checking results

.class OnSpellCheckerChanged : public ISpellCheckerChangedEventHandler

    _count ULONG ?
    _eventCookie DWORD ?

    StartListeningToChangeEvents proto :ptr ISpellChecker, :ptr ptr OnSpellCheckerChanged {

        .new spellChecker:ptr ISpellChecker = _1
        .new eventListener:ptr ptr OnSpellCheckerChanged = _2

        .new onChanged:ptr OnSpellCheckerChanged()
        .new hr:HRESULT = S_OK
        .if ( onChanged == nullptr )
            mov hr,E_OUTOFMEMORY
        .endif

        .if (SUCCEEDED(hr))

            mov rdx,onChanged
            mov hr,spellChecker.add_SpellCheckerChanged(rdx, &[rdx].OnSpellCheckerChanged._eventCookie)
        .endif

        .if (FAILED(hr))

            onChanged.delete()
            mov onChanged,nullptr
        .endif

        mov rax,onChanged
        mov rdx,eventListener
        mov [rdx],rax
        PrintErrorIfFailed("StartListeningToChangeEvents", hr)
        mov eax,hr
    }

    StopListeningToChangeEvents proto :ptr ISpellChecker, :ptr OnSpellCheckerChanged {

        .new spellChecker:ptr ISpellChecker = _1
        .new eventHandler:ptr OnSpellCheckerChanged = _2
        .new hr:HRESULT = spellChecker.remove_SpellCheckerChanged([rdx].OnSpellCheckerChanged._eventCookie)

        eventHandler.Release()
        PrintErrorIfFailed("StopListeningToChangeEvents", hr)
    }

    OnSpellCheckerChanged proc
    delete proc
   .ends

   .data
    IID_IUnknown IID {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
    IID_ISpellCheckerFactory IID {0x8E018A9D,0x2415,0x4677,{0xBF,0x08,0x79,0x4E,0xA6,0x1F,0x94,0xBB}}
    IID_ISpellCheckerChangedEventHandler IID {0x0B83A5B0,0x792F,0x4EAB,{0x97,0x99,0xAC,0xF5,0x2C,0x5E,0xD0,0x8A}}
    CLSID_SpellCheckerFactory IID {0x7AB36653,0x1796,0x484B,{0xBD,0xFA,0xE7,0x4F,0x1D,0xB7,0xC1,0xDC}}

   .code

   assume rcx:ptr OnSpellCheckerChanged

OnSpellCheckerChanged::AddRef proc

        .return InterlockedIncrement(&[rcx]._count)

OnSpellCheckerChanged::AddRef endp

OnSpellCheckerChanged::Release proc

    .new count:ULONG = InterlockedDecrement(&[rcx]._count)
    .if ( count == 0 )

        this.delete()
    .endif
    .return count

OnSpellCheckerChanged::Release endp

OnSpellCheckerChanged::QueryInterface proc riid:REFIID, ppv:ptr ptr

    mov rax,[rdx]
    .if ( rax == qword ptr IID_IUnknown ||
          rax == qword ptr IID_ISpellCheckerChangedEventHandler )

        mov [r8],rcx
    .else
        xor eax,eax
        mov [r8],rax
       .return E_NOINTERFACE
    .endif

    inc [rcx]._count
    .return S_OK

OnSpellCheckerChanged::QueryInterface endp

OnSpellCheckerChanged::IInvoke proc sender:ptr ISpellChecker

    wprintf("Spell checker changed.\n")
   .return S_OK

OnSpellCheckerChanged::IInvoke endp

OnSpellCheckerChanged::OnSpellCheckerChanged proc

    @ComAlloc(OnSpellCheckerChanged)
    inc [rax].OnSpellCheckerChanged._count
    ret

OnSpellCheckerChanged::OnSpellCheckerChanged endp

OnSpellCheckerChanged::delete proc

    free(rcx)
    ret

OnSpellCheckerChanged::delete endp

   assume rcx:nothing


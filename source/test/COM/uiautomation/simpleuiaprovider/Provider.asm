;; Implementation of the Provider class, which implements IRawElementProviderSimple
;; and IInvokeProvider for a simple custom control.

;INITGUID equ 1

include windows.inc
include stdio.inc
include stdlib.inc
include assert.inc

include ole2.inc
include UIAutomationCore.inc
include UIAutomationCoreAPI.inc

include Provider.inc

;; Various identifiers that have to be looked up.

UiaIdentifiers      struct
NameProperty        PROPERTYID ?
ControlTypeProperty PROPERTYID ?
InvokePattern       PATTERNID ?
ButtonControlType   CONTROLTYPEID ?
UiaIdentifiers      ends

.data
inited BOOL FALSE
UiaIds UiaIdentifiers <>

.code

;; Look up identifiers.

Provider::InitIds proc

    .if (!inited)

        mov inited,TRUE
        mov UiaIds.NameProperty,        UiaLookupId(AutomationIdentifierType_Property, &Name_Property_GUID)
        mov UiaIds.ControlTypeProperty, UiaLookupId(AutomationIdentifierType_Property, &ControlType_Property_GUID)
        mov UiaIds.InvokePattern,       UiaLookupId(AutomationIdentifierType_Pattern, &Invoke_Pattern_GUID)
        mov UiaIds.ButtonControlType,   UiaLookupId(AutomationIdentifierType_ControlType, &Button_Control_GUID)
    .endif
    ret

Provider::InitIds endp

;; IUnknown implementation.

Provider::AddRef proc

    .return InterlockedIncrement(&[rcx].Provider.m_refCount)

Provider::AddRef endp

Provider::Release proc

    .ifd !InterlockedDecrement(&[rcx].Provider.m_refCount)

        HeapFree(GetProcessHeap(), 0, this)
    .endif
    ret

Provider::Release endp

Provider::QueryInterface proc riid:REFIID, ppInterface:ptr ptr

    mov rax,[rdx]
    .if rax == qword ptr IID_IUnknown
        mov [r8],rcx
    .elseif rax == qword ptr IID_IRawElementProviderSimple
        mov [r8],rcx
    .elseif rax == qword ptr IID_IInvokeProvider
        mov [r8],rcx
    .else
        mov qword ptr [r8],0
        .return E_NOINTERFACE
    .endif
    this.AddRef()
    .return S_OK

Provider::QueryInterface endp


;; IRawElementProviderSimple implementation

;; Get provider options.

Provider::get_ProviderOptions proc pRetVal:ProviderOptions

    mov ProviderOptions ptr [rdx],ProviderOptions_ServerSideProvider

    .return S_OK

Provider::get_ProviderOptions endp

;; Get the object that supports IInvokePattern.

Provider::GetPatternProvider proc patternId:PATTERNID, pRetVal:ptr ptr IUnknown

    .if (edx == UiaIds.InvokePattern)

        mov [r8],rcx
        this.AddRef()
    .else
        mov qword ptr [r8],0
    .endif

    .return S_OK

Provider::GetPatternProvider endp

;; Gets custom properties.

Provider::GetPropertyValue proc propertyId:PROPERTYID, pRetVal:ptr VARIANT

    .if edx == UiaIds.ControlTypeProperty

        mov [r8].VARIANT.vt,VT_I4
        mov [r8].VARIANT.lVal,UiaIds.ButtonControlType

    ;; The Name property comes from the Caption property of the control window, if it has one.
    ;; The Name is overridden here for the sake of illustration.

    .elseif edx == UiaIds.NameProperty

        mov [r8].VARIANT.vt,VT_BSTR
        mov [r8].VARIANT.bstrVal,SysAllocString(L"ColorButton")

    .else

        mov [r8].VARIANT.vt,VT_EMPTY
       ;; UI Automation will attempt to get the property from the host window provider.
    .endif
    .return S_OK

Provider::GetPropertyValue endp

;; Gets the UI Automation provider for the host window. This provider supplies most properties.

Provider::get_HostRawElementProvider proc pRetVal:ptr ptr IRawElementProviderSimple

    .return UiaHostProviderFromHwnd([rcx].Provider.m_controlHWnd, rdx)

Provider::get_HostRawElementProvider endp

;; IInvokeProvider implementation.

Provider::_Invoke proc

    PostMessage([rcx].Provider.m_controlHWnd,  WM_LBUTTONDOWN, NULL, NULL)
    .return S_OK

Provider::_Invoke endp

Provider::Provider proc hwnd:HWND

    .if HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Provider + ProviderVtbl)

        mov this,rax
        lea rdx,[rax+Provider]
        mov [rax],rdx
        for q,<Release,AddRef,QueryInterface,InitIds,get_ProviderOptions,GetPatternProvider,GetPropertyValue,get_HostRawElementProvider>
            lea rax,Provider_&q
            mov [rdx].ProviderVtbl.&q,rax
            endm
        mov rcx,this
        mov [rcx].Provider.m_refCount,1
        mov [rcx].Provider.m_controlHWnd,hwnd
        this.InitIds()
        mov rax,this
    .endif
    ret

Provider::Provider endp

    end

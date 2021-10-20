;
; Implementation of the Provider class, which implements
; IRawElementProviderSimple and IInvokeProvider for a simple custom control.
;

include windows.inc
include stdio.inc
include stdlib.inc
include assert.inc

include ole2.inc
include UIAutomation.inc

include Provider.inc

    .code

    assume rcx:ptr Provider

Provider::Provider proc hwnd:HWND

    mov rcx,@ComAlloc(Provider)
    mov rdx,hwnd
    mov [rcx].m_refCount,1
    mov [rcx].m_controlHWnd,rdx
    ret

Provider::Provider endp


Provider::delete proc

    free(rcx)
    ret

Provider::delete endp


; IUnknown implementation.

Provider::AddRef proc

    .return InterlockedIncrement(&[rcx].m_refCount)

Provider::AddRef endp


Provider::Release proc

    .if ( InterlockedDecrement(&[rcx].m_refCount) == 0 )

        this.delete()
        xor eax,eax
    .endif
    ret

Provider::Release endp

Provider::QueryInterface proc riid:REFIID, ppInterface:ptr ptr

    mov rax,[rdx]    ; IRawElementProviderFragment ?
    .if ( rax == qword ptr IID_IUnknown ||
          rax == qword ptr IID_IRawElementProviderSimple ||
          rax == qword ptr IID_IInvokeProvider )

        mov [r8],rcx

    .else

        xor eax,eax
        mov [r8],rax

        .return E_NOINTERFACE
    .endif

    inc [rcx].m_refCount
    .return S_OK

Provider::QueryInterface endp


; IRawElementProviderSimple implementation

; Get provider options.

Provider::get_ProviderOptions proc pRetVal:ptr ProviderOptions

    mov dword ptr [rdx],ProviderOptions_ServerSideProvider
   .return S_OK

Provider::get_ProviderOptions endp

; Get the object that supports IInvokePattern.

Provider::GetPatternProvider proc patternId:PATTERNID, pRetVal:ptr ptr IUnknown

    xor eax,eax
    .if ( edx == UIA_InvokePatternId )

        inc [rcx].m_refCount
        mov [r8],rcx
    .else
        mov [r8],rax
    .endif
    ret

Provider::GetPatternProvider endp

; Gets custom properties.

Provider::GetPropertyValue proc propertyId:PROPERTYID, pRetVal:ptr VARIANT

    .if ( edx == UIA_ControlTypePropertyId )

        mov [r8].VARIANT.vt,VT_I4
        mov [r8].VARIANT.lVal,UIA_ButtonControlTypeId


    ; The Name property comes from the Caption property of the control window, if it has one.
    ; The Name is overridden here for the sake of illustration.

    .elseif ( edx == UIA_NamePropertyId )

        SysAllocString(L"ColorButton")
        mov r8,pRetVal
        mov [r8].VARIANT.vt,VT_BSTR
        mov [r8].VARIANT.bstrVal,rax

    .else

        mov [r8].VARIANT.vt,VT_EMPTY

        ; UI Automation will attempt to get the property from the host window provider.

    .endif
    .return S_OK

Provider::GetPropertyValue endp

; Gets the UI Automation provider for the host window. This provider supplies most properties.

Provider::get_HostRawElementProvider proc pRetVal:ptr ptr IRawElementProviderSimple

   .return UiaHostProviderFromHwnd([rcx].m_controlHWnd, rdx)

Provider::get_HostRawElementProvider endp


; IInvokeProvider implementation.

Provider::_Invoke proc

    PostMessage([rcx].m_controlHWnd,  WM_LBUTTONDOWN, NULL, NULL)
   .return S_OK

Provider::_Invoke endp

    end

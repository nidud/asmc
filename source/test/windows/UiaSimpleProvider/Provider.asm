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

    assume class:rbx

Provider::Provider proc hwnd:HWND

    .if @ComAlloc(Provider)

        mov rbx,rax
        mov rdx,hwnd
        mov m_controlHWnd,rdx
    .endif
    ret
    endp


; IUnknown implementation.

Provider::AddRef proc
    InterlockedIncrement(&m_refCount)
    ret
    endp


Provider::Release proc
    .ifd ( InterlockedDecrement(&m_refCount) == 0 )
        free(rbx)
        xor eax,eax
    .endif
    ret
    endp


Provider::QueryInterface proc uses rsi rdi riid:REFIID, ppInterface:ptr ptr

    ldr rsi,riid
    ldr rdi,ppInterface

    .switch
    .case IsEqualIID(rsi, &IID_IUnknown)
    .case IsEqualIID(rsi, &IID_IRawElementProviderSimple)
    .case IsEqualIID(rsi, &IID_IInvokeProvider)
        mov [rdi],rbx
        AddRef()
       .return( S_OK )
    .endsw
    mov [rdi],rax
    mov eax,E_NOINTERFACE
    ret
    endp


; IRawElementProviderSimple implementation

; Get provider options.

Provider::get_ProviderOptions proc pRetVal:ptr ProviderOptions

    ldr rdx,pRetVal

    mov dword ptr [rdx],ProviderOptions_ServerSideProvider
    xor eax,eax
    ret
    endp

; Get the object that supports IInvokePattern.

Provider::GetPatternProvider proc patternId:PATTERNID, pRetVal:ptr ptr IUnknown

    ldr rcx,pRetVal

    xor eax,eax
    .if ( ldr(patternId) == UIA_InvokePatternId )

        inc m_refCount
        mov [rcx],rbx
    .else
        mov [rcx],rax
    .endif
    ret
    endp

; Gets custom properties.

Provider::GetPropertyValue proc uses rdi propertyId:PROPERTYID, pRetVal:ptr VARIANT

    ldr edx,propertyId
    ldr rdi,pRetVal

    .if ( edx == UIA_ControlTypePropertyId )

        mov [rdi].VARIANT.vt,VT_I4
        mov [rdi].VARIANT.lVal,UIA_ButtonControlTypeId

    ; The Name property comes from the Caption property of the control window, if it has one.
    ; The Name is overridden here for the sake of illustration.

    .elseif ( edx == UIA_NamePropertyId )

        mov [rdi].VARIANT.vt,VT_BSTR
        mov [rdi].VARIANT.bstrVal,SysAllocString(L"ColorButton")
    .else
        mov [rdi].VARIANT.vt,VT_EMPTY
        ; UI Automation will attempt to get the property from the host window provider.
    .endif
    xor eax,eax
    ret
    endp

; Gets the UI Automation provider for the host window. This provider supplies most properties.

Provider::get_HostRawElementProvider proc pRetVal:ptr ptr IRawElementProviderSimple
    UiaHostProviderFromHwnd(m_controlHWnd, ldr(pRetVal))
    ret
    endp


; IInvokeProvider implementation.

Provider::_Invoke proc
    PostMessage(m_controlHWnd,  WM_LBUTTONDOWN, NULL, NULL)
    xor eax,eax
    ret
    endp

    end

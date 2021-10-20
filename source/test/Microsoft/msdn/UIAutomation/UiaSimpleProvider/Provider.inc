;
; Declaration of the Provider class.
;
.class Provider : public IRawElementProviderSimple ;, public IInvokeProvider

    m_refCount ULONG ?      ; Ref Counter for this COM object
    m_controlHWnd HWND ?    ; The HWND for the control.

    Provider proc :HWND

    ; IUnknown methods

    ; IRawElementProviderSimple methods

    ; IInvokeProvider methods

    _Invoke proc

    delete proc

   .ends

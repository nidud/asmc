;;
;; Declaration of the Provider class.
;;

.class Provider : public IRawElementProviderSimple;, IInvokeProvider

    m_refCount      ULONG ? ;; Ref Counter for this COM object
    m_controlHWnd   HWND ?  ;; The HWND for the control.

    Provider        proc :HWND
    InitIds         proc

    ;; IInvokeProvider methods
    _Invoke         proc

    .ends

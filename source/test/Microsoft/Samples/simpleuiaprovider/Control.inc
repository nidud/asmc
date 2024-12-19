;;
;; Description: Declaration of the CustomButton class.
;;
include windows.inc
include windowsx.inc
include stdio.inc
include stdlib.inc

include ole2.inc
include UIAutomationCore.inc
include UIAutomationCoreAPI.inc

include Provider.inc

.class CustomButton

    LPIRawElementProviderSimple typedef ptr IRawElementProviderSimple

    m_buttonOn          BOOL ?
    m_InvokedEventId    SINT ?
    m_provider          LPIRawElementProviderSimple ?

    CustomButton        proc
    Release             proc
    GetUIAutomationProvider proc :HWND
    IsButtonOn          proc
    InvokeButton        proc :HWND
    .ends

CustomButton_RegisterControl proto :HINSTANCE

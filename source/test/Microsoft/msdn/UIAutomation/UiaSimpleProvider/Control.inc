;
; Declaration of the CustomButton class.
;
include windows.inc
include windowsx.inc
include stdio.inc
include stdlib.inc

include ole2.inc
include UIAutomation.inc

include Provider.inc

bool typedef LONG

define false 0
define true  1

.class CustomButton

    m_buttonOn bool ?
    m_provider ptr IRawElementProviderSimple ?

    CustomButton proc
    Release proc
    GetUIAutomationProvider proc :HWND
    IsButtonOn proc
    InvokeButton proc :HWND
   .ends

CustomButton_RegisterControl proto :HINSTANCE

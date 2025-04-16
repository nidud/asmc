; TASKDIALOG.ASM--
;
; https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-taskdialogindirect
;
; v2.36.26 - added manifest file for -pe switch
;
; The imported function TaskDialogIndirect (and TaskDialog) from Comctl32.lib needs to
; be added manually to the 64-bit library (lib/x64/def/Comctl32.def) if LINK[W] used.
;

include windows.inc
include commctrl.inc
include tchar.inc

.pragma comment(linker,
    "/manifestdependency:\""
    "type='win32' "
    "name='Microsoft.Windows.Common-Controls' "
    "version='6.0.0.0' "
    "processorArchitecture='*' "
    "publicKeyToken='6595b64144ccf1df' "
    "language='*'"
    "\""
    )

.code

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT


   .new nButtonPressed:int_t = 0
   .new config:TASKDIALOGCONFIG = {0}
   .new buttons:TASKDIALOG_BUTTON = { IDOK, L"Change password" }

    mov config.cbSize,              sizeof(config)
    mov config.hInstance,           hInstance
    mov config.dwCommonButtons,     TDCBF_CANCEL_BUTTON
    mov config.pszMainIcon,         TD_WARNING_ICON
    mov config.pszMainInstruction,  &@CStr(L"Change Password")
    mov config.pszContent,          &@CStr(L"Remember your changed password.")
    mov config.pButtons,            &buttons
    mov config.cButtons,            ARRAYSIZE(buttons)

    TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL)
    .switch (nButtonPressed)
    .case IDOK
        .endc   ; the user pressed button 0 (change password).
    .case IDCANCEL
        .endc   ; user canceled the dialog
    .default
        .endc   ; should never happen
    .endsw
    .return( 0 )

_tWinMain endp

end _tstart

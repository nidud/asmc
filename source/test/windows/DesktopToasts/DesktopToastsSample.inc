
define WINVER       0x0A00
define _WIN32_WINNT 0x0A00

include Windows.inc
include winreg.inc
include Psapi.inc
include strsafe.inc
include Shlobj.inc
include Pathcch.inc
include propvarutil.inc
include propkey.inc
include wrl.inc
include windows.ui.notifications.inc
include NotificationActivationCallback.inc
include tchar.inc

option dllimport:none

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

define AppId <L"Microsoft.Samples.DesktopToasts">
define HM_TEXTBUTTON 1

.class DesktopToastsApp

    m_hwnd      HWND ?
    m_hEdit     HWND ?
    m_cookie    DWORD ?

    DesktopToastsApp proc
    Release proc

    Initialize proc :HINSTANCE
    RunMessageLoop proc

    SetMessage proc :PCWSTR

    RegisterAppForNotificationSupport proc
    InstallShortcut proc :PCWSTR, :PCWSTR
    RegisterComServer proc :PCWSTR

    RegisterActivator proc
    UnregisterActivator proc

    WndProc proto :HWND, :UINT, :WPARAM, :LPARAM
    DisplayToast proc

    CreateToastXml proc :ptr Windows::UI::Notifications::IToastNotificationManagerStatics, :ptr ptr IXmlDocument

    CreateToast proc :ptr Windows::UI::Notifications::IToastNotificationManagerStatics, :ptr IXmlDocument

    SetImageSrc proc :PCWSTR, :ptr IXmlDocument
    SetTextValues proc :ptr PCWSTR, :UINT32, :ptr IXmlDocument
    SetNodeValueString proc :HSTRING, :ptr IXmlNode, :ptr IXmlDocument
   .ends


DEFINE_CLASS macro name, base

    .class name : public base
        m_ref LONG ?
        m_app ptr DesktopToastsApp ?
        name  proc :ptr DesktopToastsApp
       .ends

    name::AddRef proc
        InterlockedIncrement(&m_ref)
        ret
        endp
    name::Release proc
        .if ( InterlockedDecrement(&m_ref) == 0 )
            free(rbx)
            xor eax,eax
        .endif
        ret
        endp
    name::name proc app:ptr DesktopToastsApp
        ldr rbx,app
        @ComAlloc(name)
        mov [rax].name.m_app,rbx
        mov [rax].name.m_ref,1
        ret
        endp
    exitm<>
    endm


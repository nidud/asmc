
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

.class DesktopToastsApp : public INotificationActivationCallback

    m_refCount  LONG ?
    m_hwnd      HWND ?
    m_hEdit     HWND ?
    m_cookie    DWORD ?

    DesktopToastsApp proc
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


.class ToastNotification : public __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_IInspectable

    m_refCount  LONG ?
    m_app       ptr DesktopToastsApp ?

    ToastNotification proc :ptr DesktopToastsApp
   .ends

.class ToastDismissed : public __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastDismissedEventArgs

    m_refCount LONG ?
    m_app       ptr DesktopToastsApp ?

    ToastDismissed proc :ptr DesktopToastsApp
   .ends

.class ToastFailed : public __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastFailedEventArgs

    m_refCount  LONG ?
    m_app       ptr DesktopToastsApp ?

    ToastFailed proc :ptr DesktopToastsApp
   .ends


.data

;  Name:     System.AppUserModel.ToastActivatorCLSID -- PKEY_AppUserModel_ToastActivatorCLSID
;  Type:     Guid -- VT_CLSID
;  FormatID: {9F4C2855-9F79-4B39-A8D0-E1D42DE1D5F3}, 26
;
;  Used to CoCreate an INotificationActivationCallback interface to notify about toast activations.

CLSID_NotificationActivator             GUID {0x23A5B06E,0x20BB,0x4E7E,{0xA0,0xAC,0x69,0x82,0xED,0x6A,0x60,0x41}}
PKEY_AppUserModel_ToastActivatorCLSID   PROPERTYKEY {{0x9F4C2855, 0x9F79,0x4B39,{0xA8,0xD0,0xE1,0xD4,0x2D,0xE1,0xD5,0xF3}},26}
ifdef __PE__
align 8
PKEY_AppUserModel_ID                    PROPERTYKEY {{0x9F4C2855,0x9F79,0x4B39,{0xA8,0xD0,0xE1,0xD4,0x2D,0xE1,0xD5,0xF3}},5}
align 8
FOLDERID_RoamingAppData                 GUID {0x3EB685DB,0x65F9,0x4CF6,{0xA0,0x3A,0xE3,0xEF,0x65,0x72,0x9F,0x3D}}
IID_IShellLinkW                         GUID {0x000214F9,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
CLSID_ShellLink                         GUID {0x00021401,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
IID_IPropertyStore                      GUID {0x886d8eeb,0x8cf2,0x4446,{0x8d,0x02,0xcd,0xba,0x1d,0xbd,0xcf,0x99}}
IID_IPersistFile                        GUID {0x0000010b,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
IID_IToastNotificationManagerStatics    GUID {0x50AC103F,0xD235,0x4598,{0xBB,0xEF,0x98,0xFE,0x4D,0x1A,0x3A,0xD4}}
IID_IXmlNode                            GUID {0x1C741D59,0x2122,0x47D5,{0xA8,0x56,0x83,0xF3,0xD4,0x21,0x48,0x75}}
IID_IToastNotificationFactory           GUID {0x04124B20,0x82C6,0x4229,{0xB1,0x09,0xFD,0x9E,0xD4,0x66,0x2B,0x53}}
endif

    .code

; ToastNotification

ToastNotification::IInvoke proc sender:ptr Windows::UI::Notifications::IToastNotification, args:ptr IInspectable

    ; When the user clicks or taps on the toast, the registered
    ; COM object is activated, and the Activated event is raised.
    ; There is no guarantee which will happen first. If the COM
    ; object is activated first, then this message may not show.

    this.m_app.SetMessage(L"The user clicked on the toast.")

    .return S_OK

ToastNotification::IInvoke endp

ToastNotification::ToastNotification proc app:ptr DesktopToastsApp

    @ComAlloc(ToastNotification)
    mov rcx,app
    mov [rax].ToastNotification.m_app,rcx
    ret

ToastNotification::ToastNotification endp


; ToastDismissed


ToastDismissed::IInvoke proc sender:ptr Windows::UI::Notifications::IToastNotification,
                             e:ptr Windows::UI::Notifications::IToastDismissedEventArgs

    .new reason:Windows::UI::Notifications::ToastDismissalReason

    e.get_Reason(&reason)
    .if (SUCCEEDED(eax))

        .switch pascal reason
        .case Windows::UI::Notifications::ToastDismissalReason_ApplicationHidden
            lea rax,@CStr( "The application hid the toast using ToastNotifier.hide()" )
        .case Windows::UI::Notifications::ToastDismissalReason_UserCanceled
            lea rax,@CStr( "The user dismissed this toast" )
        .case Windows::UI::Notifications::ToastDismissalReason_TimedOut
            lea rax,@CStr( "The toast has timed out" )
        .default
            lea rax,@CStr( "Toast not activated" )
        .endsw
        .new outputText:PCWSTR = rax

        this.m_app.SetMessage(outputText)
    .endif
    .return S_OK

ToastDismissed::IInvoke endp

ToastDismissed::ToastDismissed proc app:ptr DesktopToastsApp

    @ComAlloc(ToastDismissed)
    mov rcx,app
    mov [rax].ToastDismissed.m_app,rcx
    ret

ToastDismissed::ToastDismissed endp


; ToastFailed

ToastNotification_Release:
ToastDismissed_Release:

ToastFailed::Release proc

    .if ( InterlockedDecrement(&[rcx].ToastFailed.m_refCount) == 0 )

        ;free(this)
        ;xor eax,eax
    .endif
    ret

ToastFailed::Release endp

ToastFailed::IInvoke proc sender:ptr Windows::UI::Notifications::IToastNotification,
                          args:ptr Windows::UI::Notifications::IToastFailedEventArgs

    this.m_app.SetMessage("The toast encountered an error.")
   .return S_OK

ToastFailed::IInvoke endp

ToastFailed::ToastFailed proc app:ptr DesktopToastsApp

    @ComAlloc(ToastFailed)
    mov rcx,app
    mov [rax].ToastFailed.m_app,rcx
    ret

ToastFailed::ToastFailed endp


; NotificationActivator

ToastNotification_QueryInterface:
ToastDismissed_QueryInterface:
ToastFailed_QueryInterface:

DesktopToastsApp::QueryInterface proc riid:REFIID, ppInterface:ptr ptr

    UNREFERENCED_PARAMETER(this)
    UNREFERENCED_PARAMETER(riid)
    UNREFERENCED_PARAMETER(ppInterface)

    .return E_NOINTERFACE

DesktopToastsApp::QueryInterface endp


ToastNotification_AddRef:
ToastDismissed_AddRef:
ToastFailed_AddRef:

DesktopToastsApp::AddRef proc

    UNREFERENCED_PARAMETER(this)

    .return InterlockedIncrement(&[rcx].DesktopToastsApp.m_refCount)

DesktopToastsApp::AddRef endp


DesktopToastsApp::Activate proc appUserModelId:LPCWSTR, invokedArgs:LPCWSTR,
        data:ptr NOTIFICATION_USER_INPUT_DATA, dataCount:ULONG

    UNREFERENCED_PARAMETER(appUserModelId)
    UNREFERENCED_PARAMETER(invokedArgs)
    UNREFERENCED_PARAMETER(data)
    UNREFERENCED_PARAMETER(dataCount)

    this.SetMessage(L"NotificationActivator - The user clicked on the toast.")
    ret

DesktopToastsApp::Activate endp


DesktopToastsApp::Release proc

    .if ( InterlockedDecrement(&[rcx].DesktopToastsApp.m_refCount) == 0 )

        this.UnregisterActivator()
    .endif
    ret

DesktopToastsApp::Release endp


; In order to display toasts, a desktop application must have a shortcut on the Start menu.
; Also, an AppUserModelID must be set on that shortcut.
;
; For the app to be activated from Action Center, it needs to register a COM server with the OS
; and register the CLSID of that COM server on the shortcut.
;
; The shortcut should be created as part of the installer. The following code shows how to create
; a shortcut and assign the AppUserModelID and ToastActivatorCLSID properties using Windows APIs.
;
; Included in this project is a wxs file that be used with the WiX toolkit
; to make an installer that creates the necessary shortcut. One or the other should be used.
;
; This sample doesn't clean up the shortcut or COM registration.

DesktopToastsApp::RegisterAppForNotificationSupport proc

    .new appData:PWSTR
    .new hr:HRESULT = SHGetKnownFolderPath(&FOLDERID_RoamingAppData, 0, NULL, &appData)

    .if (SUCCEEDED(hr))

       .new shortcutPath[MAX_PATH]:wchar_t
        mov hr,PathCchCombine(&shortcutPath, ARRAYSIZE(shortcutPath),
                appData, "Microsoft\\Windows\\Start Menu\\Programs\\Desktop Toasts App.lnk")

        .if (SUCCEEDED(hr))

            .new attributes:DWORD = GetFileAttributes(&shortcutPath)
            .new fileExists:BOOL = FALSE
            .if attributes < 0xFFFFFFF
                mov fileExists,TRUE
            .endif
            .if (!fileExists)

                .new exePath[MAX_PATH]:wchar_t
                .new charWritten:DWORD = GetModuleFileName(NULL, &exePath, ARRAYSIZE(exePath))
                mov hr,S_OK
                .if ( charWritten == 0 )
                    GetLastError()
                    mov hr,HRESULT_FROM_WIN32(eax)
                .endif
                .if (SUCCEEDED(hr))

                    mov hr,this.InstallShortcut(&shortcutPath, &exePath)
                    .if (SUCCEEDED(hr))

                        mov hr,this.RegisterComServer(&exePath)
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return hr

DesktopToastsApp::RegisterAppForNotificationSupport endp


DesktopToastsApp::InstallShortcut proc shortcutPath:PCWSTR, exePath:PCWSTR

    .new shellLink:ptr IShellLink
    .new hr:HRESULT = CoCreateInstance(&CLSID_ShellLink, NULL,
            CLSCTX_INPROC_SERVER, &IID_IShellLink, &shellLink)

    .if (SUCCEEDED(hr))

        mov hr,shellLink.SetPath(exePath)
        .if (SUCCEEDED(hr))

            .new propertyStore:ptr IPropertyStore

            mov hr,shellLink.QueryInterface(&IID_IPropertyStore, &propertyStore)

            .if (SUCCEEDED(hr))

               .new propVar:PROPVARIANT
                mov propVar.vt,VT_LPWSTR
                mov propVar.pwszVal,&@CStr(AppId) ;; for _In_ scenarios, we don't need a copy
                mov hr,propertyStore.SetValue(&PKEY_AppUserModel_ID, &propVar)
                .if (SUCCEEDED(hr))

                    mov propVar.vt,VT_CLSID
                    mov propVar.puuid,&CLSID_NotificationActivator
                    mov hr,propertyStore.SetValue(&PKEY_AppUserModel_ToastActivatorCLSID, &propVar)
                    .if (SUCCEEDED(hr))

                        mov hr,propertyStore.Commit()
                        .if (SUCCEEDED(hr))

                            .new persistFile:ptr IPersistFile
                            mov hr,shellLink.QueryInterface(&IID_IPersistFile, &persistFile)

                            .if (SUCCEEDED(hr))

                                mov hr,persistFile.Save(shortcutPath, TRUE)
                            .endif
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return hr

DesktopToastsApp::InstallShortcut endp


DesktopToastsApp::RegisterComServer proc exePath:PCWSTR

    UNREFERENCED_PARAMETER(this)

    ; We don't need to worry about overflow here as ::GetModuleFileName won't
    ; return anything bigger than the max file system path (much fewer than max of DWORD).

    lea rax,[wcslen(exePath)*2+2]
    .new dataSize:DWORD = eax

    ; In this sample, the app UI is registered to launch when the COM callback is needed.
    ; Other options might be to launch a background process instead that then decides to launch
    ; the UI if needed by that particular notification.

    RegSetKeyValue(HKEY_CURRENT_USER,
        "SOFTWARE\\Classes\\CLSID\\{23A5B06E-20BB-4E7E-A0AC-6982ED6A6041}\\LocalServer32",
        NULL, REG_SZ, exePath, dataSize)

    .return HRESULT_FROM_WIN32(eax)

DesktopToastsApp::RegisterComServer endp


; Register activator for notifications

DesktopToastsApp::RegisterActivator proc

    ; Module<OutOfProc> needs a callback registered before it can be used.
    ; Since we don't care about when it shuts down, we'll pass an empty lambda here.

    ; If a local server process only hosts the COM object then COM expects
    ; the COM server host to shutdown when the references drop to zero.
    ; Since the user might still be using the program after activating the notification,
    ; we don't want to shutdown immediately.  Incrementing the object count tells COM that
    ; we aren't done yet.

    CoRegisterClassObject(&CLSID_NotificationActivator, rcx,
        CLSCTX_LOCAL_SERVER, REGCLS_SUSPENDED, &[rcx].DesktopToastsApp.m_cookie)

   .return( S_OK )

DesktopToastsApp::RegisterActivator endp


; Unregister our activator COM object

DesktopToastsApp::UnregisterActivator proc

    UNREFERENCED_PARAMETER(this)

    CoRevokeClassObject([rcx].DesktopToastsApp.m_cookie)
    ret

DesktopToastsApp::UnregisterActivator endp


; Prepare the main window

DesktopToastsApp::Initialize proc uses rsi rdi hInstance:HINSTANCE

    .new hr:HRESULT = this.RegisterAppForNotificationSupport()
    .if (SUCCEEDED(hr))

        .new wc:WNDCLASSEX = {
            WNDCLASSEX,                     ; .cbSize
            CS_HREDRAW or CS_VREDRAW,       ; .style
            &WndProc,                       ; .lpfnWndProc
            0,                              ; .cbClsExtra
            sizeof(LONG_PTR),               ; .cbWndExtra
            hInstance,                      ; .hInstance
            LoadIcon(NULL, IDI_APPLICATION),; .hIcon
            LoadCursor(NULL, IDC_ARROW),    ; .hCursor
            GetStockObject(BLACK_BRUSH),    ; .hbrBackground
            NULL,                           ; .lpszMenuName
            "DesktopToastsApp",             ; .lpszClassName
            LoadIcon(NULL, IDI_APPLICATION) ; .hIconSm
            }

        RegisterClassEx(&wc)

        ; Create window
        CreateWindowEx(0, "DesktopToastsApp", "Desktop Toasts Demo App", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 350, 200, NULL, NULL, hInstance, this)

        mov rdi,rax
        mov rsi,this
        mov [rsi].DesktopToastsApp.m_hwnd,rax

        mov hr,E_FAIL
        .if rax != NULL
            mov hr,S_OK
        .endif

        .if (SUCCEEDED(hr))

            CreateWindowEx(0, "BUTTON", "View Text Toast", BS_PUSHBUTTON or WS_CHILD or WS_VISIBLE,
                0, 0, 150, 25, [rsi].DesktopToastsApp.m_hwnd, HM_TEXTBUTTON, hInstance, NULL)

            CreateWindowEx(0, "EDIT", "Whatever action you take on the displayed toast will be shown here.",
                ES_LEFT or ES_MULTILINE or ES_READONLY or WS_CHILD or WS_VISIBLE or WS_BORDER,
                0, 30, 300, 50, [rsi].DesktopToastsApp.m_hwnd, NULL, hInstance, NULL)

            mov [rsi].DesktopToastsApp.m_hEdit,rax

            ShowWindow(rdi, SW_SHOWNORMAL)
            UpdateWindow(rdi)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.RegisterActivator()
    .endif

    .return hr

DesktopToastsApp::Initialize endp


; Standard message loop

DesktopToastsApp::RunMessageLoop proc

    UNREFERENCED_PARAMETER(this)

    .new msg:MSG
    .while (GetMessage(&msg, NULL, 0, 0))

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret

DesktopToastsApp::RunMessageLoop endp


DesktopToastsApp::SetMessage proc message:PCWSTR

    SetForegroundWindow([rcx].DesktopToastsApp.m_hwnd)
    mov rcx,this
    SendMessage([rcx].DesktopToastsApp.m_hEdit, WM_SETTEXT, NULL, message)
   .return S_OK

DesktopToastsApp::SetMessage endp


; Display the toast using classic COM. Note that is also possible to create and
; display the toast using the new C++ /ZW options (using handles, COM wrappers, etc.)

DesktopToastsApp::DisplayToast proc

    .new string:HSTRING = NULL
    .new toastStatics:ptr Windows::UI::Notifications::IToastNotificationManagerStatics
    .new hr:HRESULT = WindowsCreateString(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager,
            wcslen(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager), &string)
    .if (SUCCEEDED(hr))

        mov hr,RoGetActivationFactory(string, &IID_IToastNotificationManagerStatics, &toastStatics)
        WindowsDeleteString(string)
    .endif

    .if (SUCCEEDED(hr))

        .new toastXml:ptr IXmlDocument = NULL
        mov hr,this.CreateToastXml(toastStatics, &toastXml)
        .if (SUCCEEDED(hr))

            mov hr,this.CreateToast(toastStatics, toastXml)
        .endif
    .endif
    .return hr

DesktopToastsApp::DisplayToast endp


; Create the toast XML from a template

DesktopToastsApp::CreateToastXml proc toastManager:ptr Windows::UI::Notifications::IToastNotificationManagerStatics, inputXml:ptr ptr IXmlDocument

    xor eax,eax
    mov rcx,inputXml
    mov [rcx],rax

    ; Retrieve the template XML

    .new hr:HRESULT = toastManager.GetTemplateContent(Windows::UI::Notifications::ToastTemplateType_ToastImageAndText04, inputXml)
    .if (SUCCEEDED(hr))

        .new imagePath:PWSTR = _wfullpath(NULL, "toastImageAndText.png", MAX_PATH)
        mov hr,HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)
        .if imagePath
            mov hr,S_OK
        .endif
        .if (SUCCEEDED(hr))

            mov rax,inputXml
            mov rdx,[rax]

            mov hr,this.SetImageSrc(imagePath, rdx)
            .if (SUCCEEDED(hr))

                .new textValues[3]:PCWSTR = { "Line 1", "Line 2", "Line 3" }

                mov r9,inputXml
                mov hr,this.SetTextValues(&textValues, ARRAYSIZE(textValues), [r9])
            .endif

            free(imagePath)
        .endif
    .endif
    .return hr

DesktopToastsApp::CreateToastXml endp


; Set the value of the "src" attribute of the "image" node

DesktopToastsApp::SetImageSrc proc imagePath:PCWSTR, toastXml:ptr Windows::Data::Xml::Dom::IXmlDocument

    .new imageSrcUri[MAX_PATH]:wchar_t
    .new size:DWORD = ARRAYSIZE(imageSrcUri)

    .new hr:HRESULT = UrlCreateFromPath(imagePath, &imageSrcUri, &size, 0)
    .if (SUCCEEDED(hr))

        .new nodeList:ptr Windows::Data::Xml::Dom::IXmlNodeList
        .new string:HSTRING
        mov hr,WindowsCreateString("image", 5, &string)
        .if (SUCCEEDED(hr))

            mov hr,toastXml.GetElementsByTagName(string, &nodeList)
            WindowsDeleteString(string)
        .endif

        .if (SUCCEEDED(hr))

            .new imageNode:ptr Windows::Data::Xml::Dom::IXmlNode = NULL
            mov hr,nodeList.Item(0, &imageNode)
            .if (SUCCEEDED(hr))

               .new attributes:ptr Windows::Data::Xml::Dom::IXmlNamedNodeMap
                mov hr,imageNode.get_Attributes(&attributes)
                .if (SUCCEEDED(hr))

                    .new srcAttribute:ptr IXmlNode
                    mov hr,WindowsCreateString("src", 3, &string)
                    .if (SUCCEEDED(hr))

                        mov hr,attributes.GetNamedItem(string, &srcAttribute)
                        WindowsDeleteString(string)
                    .endif

                    .if (SUCCEEDED(hr))

                        mov hr,WindowsCreateString(&imageSrcUri, wcslen(&imageSrcUri), &string)
                        .if (SUCCEEDED(hr))

                            mov hr,this.SetNodeValueString(string, srcAttribute, toastXml)
                            WindowsDeleteString(string)
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return hr

DesktopToastsApp::SetImageSrc endp


; Set the values of each of the text nodes

DesktopToastsApp::SetTextValues proc uses rsi rdi textValues:ptr PCWSTR, textValuesCount:UINT32, toastXml:ptr Windows::Data::Xml::Dom::IXmlDocument

    .new string:HSTRING
    .new nodeList:ptr Windows::Data::Xml::Dom::IXmlNodeList
    .new hr:HRESULT = WindowsCreateString("text", 4, &string)

    .if (SUCCEEDED(hr))

        mov hr,toastXml.GetElementsByTagName(string, &nodeList)
        WindowsDeleteString(string)
    .endif

    .if (SUCCEEDED(hr))

        .new nodeListLength:UINT32
        mov hr,nodeList.get_Length(&nodeListLength)
        .if (SUCCEEDED(hr))

            ; If a template was chosen with fewer text elements, also change the amount of strings
            ; passed to this method.

            mov hr,E_INVALIDARG
            .if textValuesCount <= nodeListLength
                mov hr,S_OK
            .endif
            .if (SUCCEEDED(hr))

                .for ( esi = 0: esi < textValuesCount: esi++ )

                    .new textNode:ptr IXmlNode
                    mov hr,nodeList.Item(esi, &textNode)
                    .if (SUCCEEDED(hr))

                        mov rax,textValues
                        mov rdi,[rax+rsi*8]
                        mov hr,WindowsCreateString(rdi, wcslen(rdi), &string)
                        .if (SUCCEEDED(hr))

                            mov hr,this.SetNodeValueString(string, textNode, toastXml)
                            WindowsDeleteString(string)
                        .endif
                    .endif
                .endf
            .endif
        .endif
    .endif
    .return( hr )

DesktopToastsApp::SetTextValues endp


DesktopToastsApp::SetNodeValueString proc inputString:HSTRING,
        node:ptr Windows::Data::Xml::Dom::IXmlNode, xml:ptr Windows::Data::Xml::Dom::IXmlDocument

    .new inputText:ptr Windows::Data::Xml::Dom::IXmlText
    .new hr:HRESULT = xml.CreateTextNode(inputString, &inputText)
    .if (SUCCEEDED(hr))

        .new inputTextNode:ptr Windows::Data::Xml::Dom::IXmlNode

        mov hr,inputText.QueryInterface(&IID_IXmlNode, &inputTextNode)
        .if (SUCCEEDED(hr))

            .new appendedChild:ptr Windows::Data::Xml::Dom::IXmlNode
            mov hr,node.AppendChild(inputTextNode, &appendedChild)
        .endif
    .endif

    .return hr

DesktopToastsApp::SetNodeValueString endp


; Create and display the toast

DesktopToastsApp::CreateToast proc toastManager:ptr Windows::UI::Notifications::IToastNotificationManagerStatics, xml:ptr IXmlDocument

    .new string:HSTRING
    .new notifier:ptr Windows::UI::Notifications::IToastNotifier = NULL
    .new hr:HRESULT = WindowsCreateString(AppId, wcslen(AppId), &string)

    .if (SUCCEEDED(hr))

        mov hr,toastManager.CreateToastNotifierWithId(string, &notifier)
        WindowsDeleteString(string)
    .endif

    .if (SUCCEEDED(hr))

       .new factory:ptr Windows::UI::Notifications::IToastNotificationFactory

       mov hr,WindowsCreateString(RuntimeClass_Windows_UI_Notifications_ToastNotification,
                wcslen(RuntimeClass_Windows_UI_Notifications_ToastNotification), &string)

        .if (SUCCEEDED(hr))

            mov hr,RoGetActivationFactory(string, &IID_IToastNotificationFactory, &factory)
            WindowsDeleteString(string)
        .endif

        .if (SUCCEEDED(hr))

           .new toast:ptr Windows::UI::Notifications::IToastNotification = NULL
            mov hr,factory.CreateToastNotification(xml, &toast)

            .if (SUCCEEDED(hr))

                ; Register the event handlers
                ;
                ; These handlers are called asynchronously.  This sample doesn't handle the
                ; the fact that these events could be raised after the app object has already
                ; been decontructed.

                .new activatedToken:EventRegistrationToken = 0
                .new dismissedToken:EventRegistrationToken = 0
                .new failedToken:EventRegistrationToken = 0
                .new toastNotification:ptr ToastNotification(this)

                mov hr,toast.add_Activated(toastNotification, &activatedToken)

                .if (SUCCEEDED(hr))

                   .new toastDismissed:ptr ToastDismissed(this)
                    mov hr,toast.add_Dismissed(toastDismissed, &dismissedToken)

                    .if (SUCCEEDED(hr))

                       .new toastFailed:ptr ToastFailed(this)
                        mov hr,toast.add_Failed(toastFailed, &failedToken)

                        .if (SUCCEEDED(hr))

                            mov hr,notifier.Show(toast)
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return( hr )

DesktopToastsApp::CreateToast endp


DesktopToastsApp::DesktopToastsApp proc

    @ComAlloc(DesktopToastsApp)
    mov [rax].DesktopToastsApp.m_refCount,1
    ret

DesktopToastsApp::DesktopToastsApp endp


; Standard window procedure

WndProc proc hwnd:HWND, message:UINT32, wParam:WPARAM, lParam:LPARAM

    .if ( message == WM_CREATE )

        mov rax,lParam
        mov rax,[rax].CREATESTRUCT.lpCreateParams
        SetWindowLongPtr(hwnd, GWLP_USERDATA, PtrToUlong(rax))

        .return( 1 )
    .endif

    .new app:ptr DesktopToastsApp = GetWindowLongPtr(hwnd, GWLP_USERDATA)

    .if( app )

        .switch message
        .case WM_COMMAND
            .if dword ptr wParam == HM_TEXTBUTTON
                app.DisplayToast()
            .endif
            .endc
        .case WM_PAINT
            .new ps:PAINTSTRUCT
             BeginPaint(hwnd, &ps)
             EndPaint(hwnd, &ps)
            .return 0
        .case WM_DESTROY
            PostQuitMessage(0)
            .return 1
        .endsw
    .endif
    .return DefWindowProc(hwnd, message, wParam, lParam)

WndProc endp


; Main function

wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, inCmdShow:int_t

    .new hr:HRESULT = RoInitialize(RO_INIT_MULTITHREADED)
    .if (SUCCEEDED(hr))

       .new app:ptr DesktopToastsApp()
        mov hr,app.Initialize(hInstance)
        .if (SUCCEEDED(hr))

            app.RunMessageLoop()
        .endif
        app.Release()
        RoUninitialize()
    .endif
    .return(hr)

wWinMain endp

    end _tstart

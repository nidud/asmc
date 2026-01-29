;
; https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/DesktopToasts/CPP
;
include DesktopToastsSample.inc


.data

;  Name:     System.AppUserModel.ToastActivatorCLSID -- PKEY_AppUserModel_ToastActivatorCLSID
;  Type:     Guid -- VT_CLSID
;  FormatID: {9F4C2855-9F79-4B39-A8D0-E1D42DE1D5F3}, 26
;
;  Used to CoCreate an INotificationActivationCallback interface to notify about toast activations.

CLSID_NotificationActivator             GUID {0x23A5B06E,0x20BB,0x4E7E,{0xA0,0xAC,0x69,0x82,0xED,0x6A,0x60,0x41}}
PKEY_AppUserModel_ToastActivatorCLSID   PROPERTYKEY {{0x9F4C2855, 0x9F79,0x4B39,{0xA8,0xD0,0xE1,0xD4,0x2D,0xE1,0xD5,0xF3}},26}
align 8
IID_IToastEventArgs                     GUID {0xab54de2d,0x97d9,0x5528,{0xb6,0xad,0x10,0x5a,0xfe,0x15,0x65,0x30}}
IID_IToastDismissedEventArgs            GUID {0x61c2402f,0x0ed0,0x5a18,{0xab,0x69,0x59,0xf4,0xaa,0x99,0xa3,0x68}}
IID_IToastFailedEventArgs               GUID {0x95e3e803,0xc969,0x5e3a,{0x97,0x53,0xea,0x2a,0xd2,0x2a,0x9a,0x33}}
PKEY_AppUserModel_ID                    PROPERTYKEY {{0x9F4C2855,0x9F79,0x4B39,{0xA8,0xD0,0xE1,0xD4,0x2D,0xE1,0xD5,0xF3}},5}
align 8
FOLDERID_RoamingAppData                 GUID {0x3EB685DB,0x65F9,0x4CF6,{0xA0,0x3A,0xE3,0xEF,0x65,0x72,0x9F,0x3D}}
IID_IUnknown                            GUID {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
IID_IClassFactory                       GUID {0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
IID_IShellLinkW                         GUID {0x000214F9,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
CLSID_ShellLink                         GUID {0x00021401,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
IID_IPropertyStore                      GUID {0x886d8eeb,0x8cf2,0x4446,{0x8d,0x02,0xcd,0xba,0x1d,0xbd,0xcf,0x99}}
IID_IPersistFile                        GUID {0x0000010b,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}}
IID_IToastNotificationManagerStatics    GUID {0x50AC103F,0xD235,0x4598,{0xBB,0xEF,0x98,0xFE,0x4D,0x1A,0x3A,0xD4}}
IID_IXmlNode                            GUID {0x1C741D59,0x2122,0x47D5,{0xA8,0x56,0x83,0xF3,0xD4,0x21,0x48,0x75}}
IID_IToastNotificationFactory           GUID {0x04124B20,0x82C6,0x4229,{0xB1,0x09,0xFD,0x9E,0xD4,0x66,0x2B,0x53}}
IID_INotificationActivationCallback     GUID {0x53E31837,0x6600,0x4A81,{0x93,0x95,0x75,0xCF,0xFE,0x74,0x6F,0x94}}


    .code

    assume class:rbx

DEFINE_CLASS(NotificationActivationCallback, INotificationActivationCallback)

NotificationActivationCallback::QueryInterface proc riid:REFIID, ppInterface:ptr ptr

    ldr rdx,riid
    ldr rcx,ppInterface

    xor eax,eax
    mov [rcx],rax
    mov rax,[rdx]
    mov rdx,[rdx+8]

    .if ( ( rax == qword ptr IID_IUnknown && rdx == qword ptr IID_IUnknown[8] ) ||
          ( rax == qword ptr IID_INotificationActivationCallback &&
            rdx == qword ptr IID_INotificationActivationCallback[8] ) )
        mov [rcx],rbx
        AddRef()
       .return( S_OK )
    .endif
    .return( E_NOINTERFACE )
    endp


NotificationActivationCallback::Activate proc appUserModelId:LPCWSTR, invokedArgs:LPCWSTR,
        data:ptr NOTIFICATION_USER_INPUT_DATA, dataCount:ULONG
    m_app.SetMessage(L"NotificationActivator - The user clicked on the toast.")
    ret
    endp


DEFINE_CLASS(ClassFactory, IClassFactory)

ClassFactory::QueryInterface proc riid:REFIID, ppv:ptr ptr

    xor eax,eax
    mov [r8],rax
    mov rax,[rdx]
    mov rdx,[rdx+8]
    .if ( rax == qword ptr IID_IClassFactory && rdx == qword ptr IID_IClassFactory[8] )

        mov [r8],rcx
        AddRef()
       .return( S_OK )
    .endif
    .return( E_NOINTERFACE )
    endp


ClassFactory::CreateInstance proc punkOuter:LPUNKNOWN, riid:REFIID, ppv:ptr ptr

    xor eax,eax
    mov [r9],rax
    .if ( rdx )
        .return CLASS_E_NOAGGREGATION
    .endif
    mov rbx,NotificationActivationCallback(m_app)
    QueryInterface(riid, ppv)
    Release()
    xor eax,eax
    ret
    endp


ClassFactory::LockServer proc fLock:BOOL
    xor eax,eax
    ret
    endp


DEFINE_CLASS(ToastNotification, __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_IInspectable)

ToastNotification::QueryInterface proc riid:REFIID, ppInterface:ptr ptr

    xor eax,eax
    mov [r8],rax
    mov rdx,[rdx]
    mov eax,E_NOINTERFACE
    .if ( rdx == qword ptr IID_IToastEventArgs )
        mov [r8],rcx
        AddRef()
        xor eax,eax
    .endif
    ret
    endp

ToastNotification::IInvoke proc sender:ptr Windows::UI::Notifications::IToastNotification, args:ptr IInspectable

    ; When the user clicks or taps on the toast, the registered
    ; COM object is activated, and the Activated event is raised.
    ; There is no guarantee which will happen first. If the COM
    ; object is activated first, then this message may not show.

    m_app.SetMessage(L"The user clicked on the toast.")
    xor eax,eax
    ret
    endp


DEFINE_CLASS(ToastDismissed, __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastDismissedEventArgs)

ToastDismissed::QueryInterface proc riid:REFIID, ppInterface:ptr ptr

    xor eax,eax
    mov [r8],rax
    mov rdx,[rdx]
    mov eax,E_NOINTERFACE
    .if ( rdx == qword ptr IID_IToastDismissedEventArgs )
        mov [r8],rcx
        AddRef()
        xor eax,eax
    .endif
    ret
    endp

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
        m_app.SetMessage(outputText)
    .endif
    xor eax,eax
    ret
    endp


DEFINE_CLASS(ToastFailed, __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastFailedEventArgs)

ToastFailed::QueryInterface proc riid:REFIID, ppInterface:ptr ptr

    xor eax,eax
    mov [r8],rax
    mov rdx,[rdx]
    mov eax,E_NOINTERFACE
    .if ( rdx == qword ptr IID_IToastFailedEventArgs )
        mov [r8],rcx
        AddRef()
        xor eax,eax
    .endif
    ret
    endp

ToastFailed::IInvoke proc sender:ptr Windows::UI::Notifications::IToastNotification,
                          args:ptr Windows::UI::Notifications::IToastFailedEventArgs

    m_app.SetMessage("The toast encountered an error.")
    xor eax,eax
    ret
    endp


; DesktopToastsApp

DesktopToastsApp::Release proc
    UnregisterActivator()
    free(rbx)
    ret
    endp

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
                    mov hr,InstallShortcut(&shortcutPath, &exePath)
                    .if (SUCCEEDED(hr))
                        mov hr,RegisterComServer(&exePath)
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return( hr )
    endp


DesktopToastsApp::InstallShortcut proc shortcutPath:PCWSTR, exePath:PCWSTR

    .new shellLink:ptr IShellLink = NULL
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

                           .new persistFile:ptr IPersistFile = NULL
                            mov hr,shellLink.QueryInterface(&IID_IPersistFile, &persistFile)
                            .if (SUCCEEDED(hr))
                                mov hr,persistFile.Save(shortcutPath, TRUE)
                                persistFile.Release()
                            .endif
                        .endif
                    .endif
                .endif
                propertyStore.Release()
            .endif
        .endif
        shellLink.Release()
    .endif
    .return hr
    endp


DesktopToastsApp::RegisterComServer proc exePath:PCWSTR

    ; We don't need to worry about overflow here as ::GetModuleFileName won't
    ; return anything bigger than the max file system path (much fewer than max of DWORD).

    lea rax,[wcslen(ldr(exePath))*2+2]
    .new dataSize:DWORD = eax

    ; In this sample, the app UI is registered to launch when the COM callback is needed.
    ; Other options might be to launch a background process instead that then decides to launch
    ; the UI if needed by that particular notification.

    RegSetKeyValue(HKEY_CURRENT_USER,
        "SOFTWARE\\Classes\\CLSID\\{23A5B06E-20BB-4E7E-A0AC-6982ED6A6041}\\LocalServer32",
        NULL, REG_SZ, exePath, dataSize)
    .return HRESULT_FROM_WIN32(eax)
    endp


; Register activator for notifications

DesktopToastsApp::RegisterActivator proc

    ; Module<OutOfProc> needs a callback registered before it can be used.
    ; Since we don't care about when it shuts down, we'll pass an empty lambda here.

    .new factory:ptr ClassFactory(rbx)

    ; If a local server process only hosts the COM object then COM expects
    ; the COM server host to shutdown when the references drop to zero.
    ; Since the user might still be using the program after activating the notification,
    ; we don't want to shutdown immediately.  Incrementing the object count tells COM that
    ; we aren't done yet.

    CoRegisterClassObject(&CLSID_NotificationActivator, factory, CLSCTX_LOCAL_SERVER,
            REGCLS_MULTIPLEUSE or REGCLS_SUSPENDED, &m_cookie)
    ret
    endp


; Unregister our activator COM object

DesktopToastsApp::UnregisterActivator proc
    CoRevokeClassObject(m_cookie)
    ret
    endp


; Prepare the main window

DesktopToastsApp::Initialize proc hInstance:HINSTANCE

    .new hr:HRESULT = RegisterAppForNotificationSupport()

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
            CW_USEDEFAULT, CW_USEDEFAULT, 350, 200, NULL, NULL, hInstance, rbx)

        mov m_hwnd,rax
        mov hr,E_FAIL
        .if rax != NULL
            mov hr,S_OK
        .endif

        .if (SUCCEEDED(hr))

            CreateWindowEx(0, "BUTTON", "View Text Toast", BS_PUSHBUTTON or WS_CHILD or WS_VISIBLE,
                0, 0, 150, 25, m_hwnd, HM_TEXTBUTTON, hInstance, NULL)

            CreateWindowEx(0, "EDIT", "Whatever action you take on the displayed toast will be shown here.",
                ES_LEFT or ES_MULTILINE or ES_READONLY or WS_CHILD or WS_VISIBLE or WS_BORDER,
                0, 30, 300, 50, m_hwnd, NULL, hInstance, NULL)

            mov m_hEdit,rax

            ShowWindow(m_hwnd, SW_SHOWNORMAL)
            UpdateWindow(m_hwnd)
        .endif
    .endif

    .if (SUCCEEDED(hr))
        mov hr,RegisterActivator()
    .endif
    .return hr
    endp


; Standard message loop

DesktopToastsApp::RunMessageLoop proc

    .new msg:MSG
    .while (GetMessage(&msg, NULL, 0, 0))

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret
    endp


DesktopToastsApp::SetMessage proc message:PCWSTR

    SetForegroundWindow(m_hwnd)
    SendMessage(m_hEdit, WM_SETTEXT, NULL, message)
    xor eax,eax
    ret
    endp


; Display the toast using classic COM. Note that is also possible to create and
; display the toast using the new C++ /ZW options (using handles, COM wrappers, etc.)

DesktopToastsApp::DisplayToast proc

    .new hshManager:HSTRING_HEADER
    .new hsManager:HSTRING = NULL
    .new toastStatics:ptr Windows::UI::Notifications::IToastNotificationManagerStatics = NULL
    .new hr:HRESULT = WindowsCreateStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager,
            lengthof(@CStr(-1))-1, &hshManager, &hsManager)

    .if (SUCCEEDED(hr))
        mov hr,RoGetActivationFactory(hsManager, &IID_IToastNotificationManagerStatics, &toastStatics)
    .endif

    .if (SUCCEEDED(hr))

       .new toastXml:ptr Windows::Data::Xml::Dom::IXmlDocument = NULL
        mov hr,CreateToastXml(toastStatics, &toastXml)
        .if (SUCCEEDED(hr))

            mov hr,CreateToast(toastStatics, toastXml)
            toastXml.Release()
        .endif
        toastStatics.Release()
    .endif
    .if ( hsManager )
        WindowsDeleteString(hsManager)
    .endif
    .return hr
    endp


; Create the toast XML from a template

DesktopToastsApp::CreateToastXml proc \
        toastManager:ptr Windows::UI::Notifications::IToastNotificationManagerStatics,
        inputXml:ptr ptr IXmlDocument

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

            mov hr,SetImageSrc(imagePath, rdx)
            .if (SUCCEEDED(hr))

               .new textValues[3]:PCWSTR = { "Line 1", "Line 2", "Line 3" }
                mov r9,inputXml
                mov hr,SetTextValues(&textValues, ARRAYSIZE(textValues), [r9])
            .endif
            free(imagePath)
        .endif
    .endif
    .return hr
    endp


; Set the value of the "src" attribute of the "image" node

DesktopToastsApp::SetImageSrc proc imagePath:PCWSTR, toastXml:ptr Windows::Data::Xml::Dom::IXmlDocument

    .new imageSrcUri[MAX_PATH]:wchar_t
    .new size:DWORD = ARRAYSIZE(imageSrcUri)
    .new hr:HRESULT = UrlCreateFromPath(imagePath, &imageSrcUri, &size, 0)

    .if (SUCCEEDED(hr))

        .new hshImage:HSTRING_HEADER
        .new hsImage:HSTRING = NULL
        .new nodeList:ptr Windows::Data::Xml::Dom::IXmlNodeList = NULL
        .new hr:HRESULT = WindowsCreateStringReference("image", 5, &hshImage, &hsImage)

        .if (SUCCEEDED(hr))
            mov hr,toastXml.GetElementsByTagName(hsImage, &nodeList)
        .endif
        .if (SUCCEEDED(hr))

           .new imageNode:ptr Windows::Data::Xml::Dom::IXmlNode = NULL
            mov hr,nodeList.Item(0, &imageNode)

            .if (SUCCEEDED(hr))

               .new attributes:ptr Windows::Data::Xml::Dom::IXmlNamedNodeMap = NULL
                mov hr,imageNode.get_Attributes(&attributes)

                .if (SUCCEEDED(hr))

                   .new srcAttribute:ptr Windows::Data::Xml::Dom::IXmlNode = NULL
                   .new hshSrc:HSTRING_HEADER
                   .new hsSrc:HSTRING = NULL
                    mov hr,WindowsCreateStringReference("src", 3, &hshSrc, &hsSrc)

                    .if (SUCCEEDED(hr))
                        mov hr,attributes.GetNamedItem(hsSrc, &srcAttribute)
                    .endif
                    .if (SUCCEEDED(hr))

                       .new hshUri:HSTRING_HEADER
                       .new hsUri:HSTRING = NULL
                        mov hr,WindowsCreateStringReference(&imageSrcUri, wcslen(&imageSrcUri), &hshUri, &hsUri)
                        .if (SUCCEEDED(hr))
                            mov hr,SetNodeValueString(hsUri, srcAttribute, toastXml)
                            WindowsDeleteString(hsUri)
                        .endif
                        srcAttribute.Release()
                    .endif
                    attributes.Release()
                    .if ( hsSrc )
                        WindowsDeleteString(hsSrc)
                    .endif
                .endif
                imageNode.Release()
            .endif
            nodeList.Release()
        .endif
        .if ( hsImage )
            WindowsDeleteString(hsImage)
        .endif
    .endif
    .return( hr )
    endp


; Set the values of each of the text nodes

DesktopToastsApp::SetTextValues proc uses rsi rdi textValues:ptr PCWSTR,
        textValuesCount:UINT32, toastXml:ptr Windows::Data::Xml::Dom::IXmlDocument

    .new hshText:HSTRING_HEADER
    .new hsText:HSTRING = NULL
    .new hr:HRESULT = WindowsCreateStringReference("text", 4, &hshText, &hsText)
    .new nodeList:ptr Windows::Data::Xml::Dom::IXmlNodeList = NULL

    .if (SUCCEEDED(hr))
        mov hr,toastXml.GetElementsByTagName(hsText, &nodeList)
    .endif

    .if (SUCCEEDED(hr))

       .new nodeListLength:UINT32
        mov hr,nodeList.get_Length(&nodeListLength)

        .if (SUCCEEDED(hr))

            ; If a template was chosen with fewer text elements, also change
            ; the amount of strings passed to this method.

            mov hr,E_INVALIDARG
            .if ( textValuesCount <= nodeListLength )
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                .new textNode:ptr Windows::Data::Xml::Dom::IXmlNode
                .new hshString:HSTRING_HEADER
                .new hsString:HSTRING

                .for ( esi = 0: esi < textValuesCount: esi++ )

                    mov hr,nodeList.Item(esi, &textNode)
                    .if (SUCCEEDED(hr))

                        mov rax,textValues
                        mov rdi,[rax+rsi*8]
                        mov hr,WindowsCreateStringReference(rdi, wcslen(rdi), &hshString, &hsString)

                        .if (SUCCEEDED(hr))

                            mov hr,SetNodeValueString(hsString, textNode, toastXml)
                            WindowsDeleteString(hsString)
                        .endif
                        textNode.Release()
                    .endif
                .endf
            .endif
        .endif
    .endif
    .if ( hsText )
        WindowsDeleteString(hsText)
    .endif
    .return( hr )
    endp


DesktopToastsApp::SetNodeValueString proc inputString:HSTRING,
        node:ptr Windows::Data::Xml::Dom::IXmlNode, xml:ptr Windows::Data::Xml::Dom::IXmlDocument

    .new inputText:ptr Windows::Data::Xml::Dom::IXmlText = NULL
    .new hr:HRESULT = xml.CreateTextNode(inputString, &inputText)
    .if (SUCCEEDED(hr))

       .new inputTextNode:ptr Windows::Data::Xml::Dom::IXmlNode = NULL
        mov hr,inputText.QueryInterface(&IID_IXmlNode, &inputTextNode)
        .if (SUCCEEDED(hr))

           .new appendedChild:ptr Windows::Data::Xml::Dom::IXmlNode = NULL
            mov hr,node.AppendChild(inputTextNode, &appendedChild)
            .if (SUCCEEDED(hr))
                ; ...
            .endif
            inputTextNode.Release()
        .endif
        inputText.Release()
    .endif
    .return hr
    endp


; Create and display the toast

DesktopToastsApp::CreateToast proc \
        toastManager:ptr Windows::UI::Notifications::IToastNotificationManagerStatics,
        xml:ptr IXmlDocument

    .new hshAppId:HSTRING_HEADER
    .new hsAppId:HSTRING = NULL
    .new notifier:ptr Windows::UI::Notifications::IToastNotifier = NULL
    .new hr:HRESULT = WindowsCreateStringReference(AppId, wcslen(AppId), &hshAppId, &hsAppId)

    .if (SUCCEEDED(hr))
        mov hr,toastManager.CreateToastNotifierWithId(hsAppId, &notifier)
    .endif

    .if (SUCCEEDED(hr))

        .new hshToastNotification:HSTRING_HEADER
        .new hsToastNotification:HSTRING = NULL
        .new factory:ptr Windows::UI::Notifications::IToastNotificationFactory = NULL

        mov hr,WindowsCreateStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotification,
                lengthof(@CStr(-1))-1, &hshToastNotification, &hsToastNotification)

        .if (SUCCEEDED(hr))

            mov hr,RoGetActivationFactory(hsToastNotification, &IID_IToastNotificationFactory, &factory)
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

               .new activatedToken:EventRegistrationToken
               .new dismissedToken:EventRegistrationToken
               .new failedToken:EventRegistrationToken
               .new toastNotification:ptr ToastNotification(rbx)

                mov hr,toast.add_Activated(toastNotification, &activatedToken)

                .if (SUCCEEDED(hr))

                   .new toastDismissed:ptr ToastDismissed(rbx)
                    mov hr,toast.add_Dismissed(toastDismissed, &dismissedToken)

                    .if (SUCCEEDED(hr))

                       .new toastFailed:ptr ToastFailed(rbx)
                        mov hr,toast.add_Failed(toastFailed, &failedToken)
                        .if (SUCCEEDED(hr))
                            mov hr,notifier.Show(toast)
                        .endif
                    .endif
                .endif
                toast.Release()
            .endif
            factory.Release()
            notifier.Release()
        .endif
        .if ( hsToastNotification )
            WindowsDeleteString(hsToastNotification)
        .endif
    .endif
    .if ( hsAppId )
        WindowsDeleteString(hsAppId)
    .endif
    .return( hr )
    endp


DesktopToastsApp::DesktopToastsApp proc
    @ComAlloc(DesktopToastsApp)
    ret
    endp


; Standard window procedure

WndProc proc hwnd:HWND, message:UINT32, wParam:WPARAM, lParam:LPARAM

    .if ( message == WM_CREATE )

        mov rax,lParam
        mov rax,[rax].CREATESTRUCT.lpCreateParams
        SetWindowLongPtr(hwnd, GWLP_USERDATA, PtrToUlong(rax))
       .return( 1 )
    .endif

    .new app:ptr DesktopToastsApp = GetWindowLongPtr(hwnd, GWLP_USERDATA)
    .if ( app )

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
    endp


; Main function

wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, inCmdShow:int_t

    .new hr:HRESULT = CoInitializeEx(NULL, COINIT_MULTITHREADED)

    .if (SUCCEEDED(hr))
        mov hr,RoInitialize(RO_INIT_MULTITHREADED)
    .endif

    .if (SUCCEEDED(hr))

       .new app:ptr DesktopToastsApp()
        mov hr,app.Initialize(hInstance)
        .if (SUCCEEDED(hr))

            app.RunMessageLoop()
        .endif
        app.Release()
        RoUninitialize()
        CoUninitialize()
    .endif
    .return(hr)
    endp

    end _tstart

;
; Testing some limits and new controls:
;
; - Resources are parsed as text items and may overflow the token buffer, so
;   the line-size is now set to 0x2000.
; - An extra WORD was emitted for controls without a "text" argument (EDITTEXT).
; - added AUTOCHECKBOX and AUTORADIOBUTTON
;
include windows.inc
include shlobj.inc
include propvarutil.inc
include stdio.inc
include tchar.inc

include res/shortcut.inc

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

.data
 DECLARE_IIDT(IShellLink)
 DECLARE_IID(IPersistFile)
 DECLARE_IID(IShellLinkDataList)
 DECLARE_IID(IPropertyStore)
 DECLARE_CLSID(ShellLink)
 DECLARE_PKEY(Console_LineSelection)
 align LPTSTR
 g_AsmcDir LPTSTR 0
 g_hInst HINSTANCE 0

 ; Standard Windows color table.

 _wincolortable COLORREF \
    0x0C0C0C,
    0xDA3700,
    0x0EA113,
    0xDD963A,
    0x1F0FC5,
    0x981788,
    0x009CC1,
    0xCCCCCC,
    0x767676,
    0xFF783B,
    0x0CC616,
    0xD6D661,
    0x5648E7,
    0x9E00B4,
    0xA5F1F9,
    0xF2F2F2

 ; The Ubuntu color table is based on the colors used in conio.

 _rgbcolortable COLORREF \
    0x211417,
    0x8B4812,
    0x69A226,
    0xB3A12A,
    0x281CC0,
    0xBA47A3,
    0x4C73A2,
    0xCCCFD0,
    0x645C5E,
    0xDE7B2A,
    0x7ADA33,
    0xDEC733,
    0x5161F6,
    0xCB61C0,
    0x0CADE9,
    0xFFFFFF

.code

CreateLink proc uses rsi rdi rbx hWnd:HWND, buffer:LPTSTR

   .new name[256]:WCHAR
   .new props:NT_CONSOLE_PROPS
   .new pShellLink:ptr IShellLink
   .new pIShellLinkDataList:ptr IShellLinkDataList = NULL
   .new pPersistFile:ptr IPersistFile
   .new pItemList:ptr = 0
   .new pPropStore:ptr IPropertyStore = 0
    ldr rsi,hWnd
    ldr rdi,buffer

    .ifd CoInitialize(NULL) == S_OK
        .ifd CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, &pShellLink) == S_OK
            pShellLink.QueryInterface(&IID_IPersistFile, &pPersistFile)
            pShellLink.QueryInterface(&IID_IShellLinkDataList, &pIShellLinkDataList)

            GetDlgItemText(rsi, IDC_NAME, &name, 512)
            pShellLink.SetDescription(&name)
            GetDlgItemText(rsi, IDC_TARGET, rdi, 512)
            pShellLink.SetPath(rdi)
            pShellLink.SetIconLocation(rdi, 0)
            GetDlgItemText(rsi, IDC_START, rdi, 512)
            pShellLink.SetWorkingDirectory(rdi)

            .if ( pIShellLinkDataList )
                pIShellLinkDataList.RemoveDataBlock(NT_CONSOLE_PROPS_SIG)

                memset(&props, 0, sizeof(props))
                mov props.dbh.cbSize,sizeof(props)
                mov props.dbh.dwSignature,NT_CONSOLE_PROPS_SIG
                mov props.wFillAttribute,0x0007
                mov props.wPopupFillAttribute,0x00F5
                GetDlgItemText(rsi, IDC_SCREEN_BUFFER_SIZE_X, rdi, 512)
                _tstol(rdi)
                mov props.dwScreenBufferSize.X,ax
                GetDlgItemText(rsi, IDC_SCREEN_BUFFER_SIZE_Y, rdi, 512)
                _tstol(rdi)
                mov props.dwScreenBufferSize.Y,ax
                GetDlgItemText(rsi, IDC_WINDOW_SIZE_X, rdi, 512)
                _tstol(rdi)
                mov props.dwWindowSize.X,ax
                GetDlgItemText(rsi, IDC_WINDOW_SIZE_Y, rdi, 512)
                _tstol(rdi)
                mov props.dwWindowSize.Y,ax
                GetDlgItemText(rsi, IDC_WINDOW_ORIGIN_X, rdi, 512)
                _tstol(rdi)
                mov props.dwWindowOrigin.X,ax
                GetDlgItemText(rsi, IDC_WINDOW_ORIGIN_Y, rdi, 512)
                _tstol(rdi)
                mov props.dwWindowOrigin.Y,ax
                mov props.nFont,0
                mov props.nInputBufferSize,0
                GetDlgItemText(rsi, IDC_FONT_X, rdi, 512)
                _tstol(rdi)
                mov props.dwFontSize.X,ax
                GetDlgItemText(rsi, IDC_FONT_Y, rdi, 512)
                _tstol(rdi)
                mov props.dwFontSize.Y,ax
                GetDlgItemText(rsi, IDC_FONT_FAMILY, rdi, 512)
                _tstol(rdi)
                mov props.uFontFamily,eax
                GetDlgItemText(rsi, IDC_FONT_WEIGHT, rdi, 512)
                _tstol(rdi)
                mov props.uFontWeight,eax
                GetDlgItemText(rsi, IDC_FONT_NAME, rdi, 512)
                _tcsncpy(&props.FaceName, rdi, LF_FACESIZE)
                GetDlgItemText(rsi, IDC_CURSIZE, rdi, 512)
                _tstol(rdi)
                mov props.uCursorSize,eax
                GetDlgItemText(rsi, IDC_HISTORY_SIZE, rdi, 512)
                _tstol(rdi)
                mov props.uHistoryBufferSize,eax
                GetDlgItemText(rsi, IDC_HISTORY_COUNT, rdi, 512)
                _tstol(rdi)
                mov props.uNumberOfHistoryBuffers,eax
                IsDlgButtonChecked(rsi, IDC_FULLSCREEN)
                cmp eax,BST_CHECKED
                mov eax,0
                sete al
                mov props.bFullScreen,eax
                IsDlgButtonChecked(rsi, IDC_QUICK_EDIT)
                cmp eax,BST_CHECKED
                mov eax,0
                sete al
                mov props.bQuickEdit,eax
                IsDlgButtonChecked(rsi, IDC_INSERT_MODE)
                cmp eax,BST_CHECKED
                mov eax,0
                sete al
                mov props.bInsertMode,eax
                IsDlgButtonChecked(rsi, IDC_AUTOPOS)
                cmp eax,BST_CHECKED
                mov eax,0
                sete al
                mov props.bAutoPosition,eax
                IsDlgButtonChecked(rsi, IDC_HISTORY_NODUP)
                cmp eax,BST_CHECKED
                mov eax,0
                sete al
                mov props.bHistoryNoDup,eax
                IsDlgButtonChecked(rsi, IDC_UBUNTU_COLOR)
                lea rdx,_wincolortable
                .if ( eax == BST_CHECKED )
                    lea rdx,_rgbcolortable
                .endif
                memcpy(&props.ColorTable, rdx, sizeof(_wincolortable))
                pIShellLinkDataList.AddDataBlock(&props)
                ;
                ; This is a hack to set the "Wrap Selection" property in the console properties.
                ; The property is not exposed through the standard console properties structure,
                ; so we need to use the IPropertyStore interface to set it directly.
                ;
                IsDlgButtonChecked(rsi, IDC_WRAP_SELECTION)
                .if ( eax != BST_CHECKED )
                    .if SUCCEEDED(pShellLink.QueryInterface(&IID_IPropertyStore, &pPropStore))
                        .new propVar:PROPVARIANT
                        .if SUCCEEDED(InitPropVariantFromBoolean(FALSE, &propVar))
                            .if SUCCEEDED(pPropStore.SetValue(&PKEY_Console_LineSelection, &propVar))
                                pPropStore.Commit()
                            .endif
                        .endif
                    .endif
                .endif
            .endif
            _tcscat(&name, ".lnk")
            pPersistFile.Save(&name, TRUE)
        .endif
        CoUninitialize()
    .endif
    .return 0
    endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    .new buffer[512]:WCHAR
    .switch ldr(uMsg)
    .case WM_INITDIALOG
       .new hIcon:HICON = LoadImage(g_hInst, IDI_ICON, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR)
        SendMessage(hWnd, WM_SETICON, ICON_SMALL, hIcon)
        _stprintf(&buffer, "Asmc-%d.%d", __ASMC__ / 100, __ASMC__ mod 100)
        SetDlgItemText(hWnd, IDC_NAME, &buffer)
        _tcscpy(&buffer, g_AsmcDir)
        SetDlgItemText(hWnd, IDC_START, &buffer)
        _tcscat(&buffer, "\\bin\\dz.exe")
        SetDlgItemText(hWnd, IDC_TARGET, &buffer)
        SetDlgItemText(hWnd, IDC_SCREEN_BUFFER_SIZE_X, "91")
        SetDlgItemText(hWnd, IDC_SCREEN_BUFFER_SIZE_Y, "28")
        SetDlgItemText(hWnd, IDC_WINDOW_SIZE_X, "90")
        SetDlgItemText(hWnd, IDC_WINDOW_SIZE_Y, "25")
        SetDlgItemText(hWnd, IDC_WINDOW_ORIGIN_X, "0")
        SetDlgItemText(hWnd, IDC_WINDOW_ORIGIN_Y, "0")
        CheckDlgButton(hWnd, IDC_AUTOPOS, BST_CHECKED)
        SetDlgItemText(hWnd, IDC_HISTORY_SIZE, "50")
        SetDlgItemText(hWnd, IDC_HISTORY_COUNT, "4")
        SetDlgItemText(hWnd, IDC_CURSIZE, "25")
        SetDlgItemText(hWnd, IDC_FONT_X, "0")
        SetDlgItemText(hWnd, IDC_FONT_Y, "28")
        ;
        ; This will also work with installed custom fonts. However,
        ; if the link is modified the font settings will then be lost.
        ;
        SetDlgItemText(hWnd, IDC_FONT_FAMILY, "54")
        SetDlgItemText(hWnd, IDC_FONT_WEIGHT, "400")
        SetDlgItemText(hWnd, IDC_FONT_NAME, "Consolas")
       .return FALSE
    .case WM_CLOSE
        EndDialog(hWnd, 0)
       .return TRUE
    .case WM_COMMAND
        movzx eax,word ptr wParam
        .gotosw(WM_CLOSE) .if ( eax == IDCANCEL )
        .if ( eax == IDOK )
            CreateLink(hWnd, &buffer)
           .gotosw(WM_CLOSE)
        .elseif ( eax == IDC_APPLY )
            CreateLink(hWnd, &buffer)
        .endif
        .endc
    .case WM_DESTROY
        .return TRUE
    .endsw
    .return FALSE
    endp

_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT
    mov g_hInst,hInstance
    mov g_AsmcDir,_tgetenv("ASMCDIR")
    .if ( rax )
        DialogBox(hInstance, MAKEINTRESOURCE(IDD_SHORTCUT), NULL, &WndProc)
    .else
        MessageBox(NULL, "Envionment variable ASMCDIR missing", "Asmc Shortcut", MB_OK)
    .endif
    .return( 0 )
    endp

.resource

 DIALOGEX 100, 50, 270, 300,
  STYLE DS_SETFONT or DS_MODALFRAME or WS_POPUP or WS_CAPTION or WS_SYSMENU,
  FONT 8, "MS Shell Dlg",
  CAPTION "Asmc Shortcut" {
    LTEXT "Name:", IDC_STATIC, 14,20,20,12,
    EDITTEXT IDC_NAME, 70,20,155,12,
    LTEXT "Target:", IDC_STATIC, 14,42,24,24,
    EDITTEXT IDC_TARGET, 70,40,155,12,
    LTEXT "Start In:", IDC_STATIC, 14,58,30,12,
    EDITTEXT IDC_START, 70,56,155,12,
    LTEXT "Screen Buffer  X", IDC_STATIC, 14,80,60,12,
    LTEXT "Y", IDC_STATIC, 61, 94, 8,12,
    EDITTEXT IDC_SCREEN_BUFFER_SIZE_X, 70,78,40,12,
    EDITTEXT IDC_SCREEN_BUFFER_SIZE_Y, 70,92,40,12,
    LTEXT "Window Size", IDC_STATIC, 14,108,50,12,
    EDITTEXT IDC_WINDOW_SIZE_X, 70,106,40,12,
    AUTOCHECKBOX "Full Screen", IDC_FULLSCREEN,114,106,80,12,
    EDITTEXT IDC_WINDOW_SIZE_Y, 70,120,40,12,
    LTEXT "Window Origin", IDC_STATIC, 14,136,50,12,
    EDITTEXT IDC_WINDOW_ORIGIN_X, 70,134,40,12,
    AUTOCHECKBOX "Auto Position Mode", IDC_AUTOPOS,114,136,80,12,
    EDITTEXT IDC_WINDOW_ORIGIN_Y, 70,148,40,12,
    LTEXT "Cursor Size", IDC_STATIC, 14,164,60,12,
    EDITTEXT IDC_CURSIZE, 70,162,40,12,
    LTEXT "History Buffer", IDC_STATIC, 14,178,60,12,
    EDITTEXT IDC_HISTORY_SIZE, 70,176,40,12,
    AUTOCHECKBOX "No Old Duplicates", IDC_HISTORY_NODUP,114,178,80,12,
    EDITTEXT IDC_HISTORY_COUNT, 70,190,40,12,
    LTEXT "Buffer Count", IDC_STATIC, 14,192,50,12,
    LTEXT "Font Size", IDC_STATIC, 14,206,50,12,
    EDITTEXT IDC_FONT_X, 70,202,40,12,
    EDITTEXT IDC_FONT_Y, 70,216,40,12,
    LTEXT "Font Family", IDC_STATIC, 14,232,50,12,
    EDITTEXT IDC_FONT_FAMILY, 70,230,40,12,
    LTEXT "Font Weight", IDC_STATIC, 14,246,50,12,
    EDITTEXT IDC_FONT_WEIGHT, 70,244,40,12,
    LTEXT "Font Face", IDC_STATIC, 14,260,50,12,
    EDITTEXT IDC_FONT_NAME, 70,258,155,12,
    GROUPBOX "Text Preferences", IDC_TEXT_PREFERENCE, 114, 190, 110, 64,
    AUTOCHECKBOX "Insert Mode", IDC_INSERT_MODE,124,200,80,12,
    AUTOCHECKBOX "Quick Edit", IDC_QUICK_EDIT,124,212,80,12,
    AUTOCHECKBOX "Wrap Selection", IDC_WRAP_SELECTION,124,224,80,12,
    AUTOCHECKBOX "Ubuntu Color", IDC_UBUNTU_COLOR,124,236,80,12,
    PUSHBUTTON "&OK", IDOK, 60,280,39,12,
    PUSHBUTTON "&Cancel", IDCANCEL, 110,280,39,12,
    PUSHBUTTON "&Apply", IDC_APPLY,160,280,39,12,
    }

 ICON ../../asmc/test/src/icon.ico

 end _tstart

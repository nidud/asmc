;
; https://github.com/microsoftarchive/msdn-code-gallery-microsoft/tree/master/OneCodeTeam/
;    CppSetDesktopWallpaper

include stdio.inc
include windows.inc
include windowsx.inc
include strsafe.inc
include shlobj.inc
include shlwapi.inc
include OleCtl.inc
include Commctrl.inc
include winreg.inc

define IDD_MAINDIALOG                  103
define IDC_EDIT_WALLPAPER              1000
define IDC_BUTTON_BROWSE               1001
define IDC_BUTTON_SETWALLPAPER         1002
define IDC_RADIO_TILE                  1003
define IDC_RADIO_CENTER                1004
define IDC_RADIO_STRETCH               1005
define IDC_RADIO_FIT                   1006
define IDC_RADIO_FILL                  1007
define IDC_STATIC_PREVIEW              1008
define IDC_STATIC                      -1

ifdef _M_IX86
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_IA64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_X64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
else
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
endif

.data
 g_szWallpaperFileName wchar_t MAX_PATH dup(0)
 g_pWallpaper LPPICTURE NULL

;; Prior to Windows Vista, only .bmp files are supported as wallpaper.
c_rgOldFileTypes COMDLG_FILTERSPEC \
    { @CStr(L"Bitmap Files"),     @CStr(L"*.bmp") }

c_rgNewFileTypes COMDLG_FILTERSPEC \
    { @CStr(L"All Supported Files"),   @CStr(L"*.bmp;*.jpg") },
    { @CStr(L"Bitmap Files"),          @CStr(L"*.bmp") },
    { @CStr(L"Jpg Files"),             @CStr(L"*.jpg") }

.code

ReportError proc pszFunction:LPCWSTR, hr:HRESULT; = E_FAIL
    .new szMessage[200]:wchar_t
    .if ( hr == E_FAIL )
        StringCchPrintf(&szMessage, 200, "%s failed", pszFunction)
        .if ( SUCCEEDED(eax) )
            MessageBox(NULL, &szMessage, L"Error", MB_ICONERROR)
        .endif
    .else
        .if ( SUCCEEDED(StringCchPrintf(&szMessage, ARRAYSIZE(szMessage),
            L"%s failed w/hr 0x%08lx", pszFunction, hr)) )
            MessageBox(NULL, &szMessage, L"Error", MB_ICONERROR)
        .endif
    .endif
    ret
    endp


SupportJpgAsWallpaper proc
   .new osVersionInfoToCompare:OSVERSIONINFOEX = { OSVERSIONINFOEX, 6, 0 }
   .new comparisonInfo:ULONGLONG = 0
   .new conditionMask:BYTE = VER_GREATER_EQUAL
    VER_SET_CONDITION(comparisonInfo, VER_MAJORVERSION, conditionMask)
    VER_SET_CONDITION(comparisonInfo, VER_MINORVERSION, conditionMask)
    VerifyVersionInfo(&osVersionInfoToCompare, VER_MAJORVERSION or VER_MINORVERSION, comparisonInfo)
    ret
    endp


SupportFitFillWallpaperStyles proc
   .new osVersionInfoToCompare:OSVERSIONINFOEX = { OSVERSIONINFOEX, 6, 1 }
   .new comparisonInfo:ULONGLONG = 0
   .new conditionMask:BYTE = VER_GREATER_EQUAL
    VER_SET_CONDITION(comparisonInfo, VER_MAJORVERSION, conditionMask)
    VER_SET_CONDITION(comparisonInfo, VER_MINORVERSION, conditionMask)
    VerifyVersionInfo(&osVersionInfoToCompare, VER_MAJORVERSION or VER_MINORVERSION, comparisonInfo)
    ret
    endp


.enum WallpaperStyle { Tile, Center, Stretch, Fit, Fill }

SetDesktopWallpaper proc pszFile:PWSTR, style:WallpaperStyle

    .new hr:HRESULT = S_OK
    .new hKey:HKEY = NULL

    RegOpenKeyEx(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_READ or KEY_WRITE, &hKey)
    mov hr,HRESULT_FROM_WIN32(eax)

    .if (SUCCEEDED(hr))

        .new pszWallpaperStyle:PWSTR
        .new pszTileWallpaper:PWSTR
        .switch (style)
        .case Tile
            mov pszWallpaperStyle,&@CStr(L"0")
            mov pszTileWallpaper,&@CStr(L"1")
           .endc
        .case Center
            mov pszWallpaperStyle,&@CStr(L"0")
            mov pszTileWallpaper,&@CStr(L"0")
           .endc
        .case Stretch
            mov pszWallpaperStyle,&@CStr(L"2")
            mov pszTileWallpaper,&@CStr(L"0")
           .endc
        .case Fit ;; (Windows 7 and later)
            mov pszWallpaperStyle,&@CStr(L"6")
            mov pszTileWallpaper,&@CStr(L"0")
           .endc
        .case Fill ;; (Windows 7 and later)
            mov pszWallpaperStyle,&@CStr(L"10")
            mov pszTileWallpaper,&@CStr(L"0")
           .endc
        .endsw
        shl lstrlen(pszWallpaperStyle),1
       .new cbData:DWORD = eax
        RegSetValueEx(hKey, L"WallpaperStyle", 0, REG_SZ, pszWallpaperStyle, cbData)
        mov hr,HRESULT_FROM_WIN32(eax)
        .if (SUCCEEDED(hr))
            shl lstrlen(pszTileWallpaper),1
            mov cbData,eax
            RegSetValueEx(hKey, L"TileWallpaper", 0, REG_SZ, pszTileWallpaper, cbData)
            mov hr,HRESULT_FROM_WIN32(eax)
        .endif
        RegCloseKey(hKey)
    .endif
    .if (SUCCEEDED(hr))
        .if ( !SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, pszFile, SPIF_UPDATEINIFILE or SPIF_SENDWININICHANGE))
            mov hr,HRESULT_FROM_WIN32(GetLastError())
        .endif
    .endif
    .return hr
    endp


PctPreviewProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM, uIdSubclass:UINT_PTR, dwRefData:DWORD_PTR

    .if ( ldr(message) == WM_PAINT ) ;; Owner-draw

        .new ps:PAINTSTRUCT
        .new hDC:HDC = BeginPaint(hWnd, &ps)
        .if ( g_pWallpaper )

            .new hmWidth:LONG
            .new hmHeight:LONG
            g_pWallpaper.get_Width(&hmWidth)
            g_pWallpaper.get_Height(&hmHeight)

            define HIMETRIC_INCH 2540
            .new nWidth:LONG = MulDiv(hmWidth, GetDeviceCaps(hDC, LOGPIXELSX), HIMETRIC_INCH)
            .new nHeight:LONG = MulDiv(hmHeight, GetDeviceCaps(hDC, LOGPIXELSY), HIMETRIC_INCH)
            .new rc:RECT
             GetClientRect(hWnd, &rc)
            .if ( nWidth < rc.right && nHeight < rc.bottom )
                mov rc.right,nWidth
                mov rc.bottom,nHeight
            .else
                cvtsi2ss xmm0,nWidth
                cvtsi2ss xmm2,nHeight
                divss    xmm0,xmm2
                cvtsi2ss xmm1,rc.right
                cvtsi2ss xmm2,rc.bottom
                divss    xmm1,xmm2
                .new wallpaperRatio: real4 = xmm0
                .new pctPreviewRatio:real4 = xmm1
                .if ( xmm0 >= xmm1 )
                    cvtsi2ss xmm1,rc.right
                    divss    xmm1,xmm0
                    cvtss2si eax,xmm1
                    mov      rc.bottom,eax
                .else
                    cvtsi2ss xmm1,rc.bottom
                    mulss    xmm1,xmm0
                    cvtss2si eax,xmm1
                    mov      rc.right,eax
                .endif
            .endif
            mov ecx,hmHeight
            neg ecx
            g_pWallpaper.Render(hDC, 0, 0, rc.right, rc.bottom, 0, hmHeight, hmWidth, ecx, &rc)
        .endif
        EndPaint(hWnd, &ps)
        xor eax,eax
    .else
        DefSubclassProc(hWnd, message, wParam, lParam)
    .endif
    ret
    endp


OnInitDialog proc hWnd:HWND, hwndFocus:HWND, lParam:LPARAM
    .if ( !SupportFitFillWallpaperStyles() )
        Button_Enable(GetDlgItem(hWnd, IDC_RADIO_FIT), FALSE)
        Button_Enable(GetDlgItem(hWnd, IDC_RADIO_FILL), FALSE)
    .endif
    Button_SetCheck(GetDlgItem(hWnd, IDC_RADIO_STRETCH), TRUE)
    .new hPctPreview:HWND = GetDlgItem(hWnd, IDC_STATIC_PREVIEW)
    .new uIdSubclass:UINT_PTR = 0
    .if ( !SetWindowSubclass(hPctPreview, &PctPreviewProc, uIdSubclass, 0) )
        ReportError(L"SetWindowSubclass", E_FAIL)
       .return FALSE
    .endif
    .return TRUE
    endp


LoadPicture proc pszFile:PCWSTR, ppPicture:ptr LPPICTURE
    .new hr:HRESULT = S_OK
    .new hFile:HANDLE = INVALID_HANDLE_VALUE
    .new hGlobal:HGLOBAL = NULL
    .new pData:PVOID = NULL
    .new pstm:LPSTREAM = NULL
    mov hFile,CreateFile(pszFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)
    .if ( hFile == INVALID_HANDLE_VALUE )
        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif
    .new dwFileSize:DWORD = GetFileSize(hFile, NULL)
    .if ( dwFileSize == INVALID_FILE_SIZE )
        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif
    mov hGlobal,GlobalAlloc(GMEM_MOVEABLE, dwFileSize)
    .if ( hGlobal == NULL )
        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif
    mov pData,GlobalLock(hGlobal)
    .if ( pData == NULL )
        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif
    .new dwBytesRead:DWORD = 0
    .if ( !ReadFile(hFile, pData, dwFileSize, &dwBytesRead, NULL) )
        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif
    mov hr,CreateStreamOnHGlobal(hGlobal, TRUE, &pstm)
    .if ( FAILED(hr) )
        jmp Error
    .endif
    mov hr,OleLoadPicture(pstm, dwFileSize, FALSE, &IID_IPicture, ppPicture)
Error:
    .if ( hFile != INVALID_HANDLE_VALUE )
        CloseHandle(hFile)
        mov hFile,INVALID_HANDLE_VALUE
    .endif
    .if ( hGlobal != NULL )
        .if ( pData != NULL )
            GlobalUnlock(hGlobal)
            mov pData,NULL
        .endif
        GlobalFree(hGlobal)
        mov hGlobal,NULL
    .endif
    .if ( pstm != NULL )
        pstm.Release()
        mov pstm,NULL
    .endif
    .return hr
    endp


OnBrowseWallpaperButtonClick proc hWnd:HWND

    .new hr:HRESULT = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)
    .if (FAILED(hr))
       .return ReportError(L"CoInitializeEx", hr)
    .endif

    .new vi:OSVERSIONINFO = { sizeof(vi) }
     GetVersionEx(&vi)

    .if ( vi.dwMajorVersion >= 6 )

       .new pfd:ptr IFileDialog = NULL
        mov hr,CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, &IID_IFileOpenDialog, &pfd)
        .if (SUCCEEDED(hr))
            mov hr,pfd.SetTitle(L"Select Wallpaper")
            .if (SUCCEEDED(hr))
                .if (SupportJpgAsWallpaper())
                    mov hr,pfd.SetFileTypes(ARRAYSIZE(c_rgNewFileTypes), &c_rgNewFileTypes)
                .else
                    mov hr,pfd.SetFileTypes(ARRAYSIZE(c_rgOldFileTypes), &c_rgOldFileTypes)
                .endif
                .if (SUCCEEDED(hr))
                    mov hr,pfd.SetFileTypeIndex(1)
                .endif
            .endif
            .if (SUCCEEDED(hr))
                mov hr,pfd.Show(hWnd)
                .if (SUCCEEDED(hr))
                    .new psiResult:ptr IShellItem = NULL
                    mov hr,pfd.GetResult(&psiResult)
                    .if (SUCCEEDED(hr))
                        .new pszFile:PWSTR = NULL
                         mov hr,psiResult.GetDisplayName(SIGDN_FILESYSPATH, &pszFile)
                        .if (SUCCEEDED(hr))
                            mov hr,StringCchCopy(&g_szWallpaperFileName, ARRAYSIZE(g_szWallpaperFileName), pszFile)
                            CoTaskMemFree(pszFile)
                        .endif
                        psiResult.Release()
                    .endif
                .endif
            .endif
            pfd.Release()
        .endif
    .else
       .new szFile[MAX_PATH]:wchar_t
       .new ofn:OPENFILENAME = { sizeof(ofn) }
        mov ofn.hwndOwner,hWnd
        mov ofn.lpstrFile,&szFile
        mov ofn.lpstrFile[0],0
        mov ofn.nMaxFile,ARRAYSIZE(szFile)
        .ifd SupportJpgAsWallpaper()
            mov ofn.lpstrFilter,&@CStr(
                L"All Supported Files (*.bmp;*.jpg)\0*.bmp;*.jpg\0"
                "Bitmap Files (*.bmp)\0*.bmp\0"
                "Jpg Files (*.jpg)\0*.jpg\0")
        .else
            mov ofn.lpstrFilter,&@CStr(L"Bitmap Files (*.bmp)\0*.bmp\0")
        .endif
        mov ofn.nFilterIndex,1
        mov ofn.lpstrFileTitle,NULL
        mov ofn.nMaxFileTitle,0
        mov ofn.lpstrInitialDir,NULL
        mov ofn.lpstrTitle,&@CStr(L"Select Wallpaper")
        mov ofn.Flags,OFN_PATHMUSTEXIST or OFN_FILEMUSTEXIST

        .if (GetOpenFileName(&ofn))
            mov hr,StringCchCopy(&g_szWallpaperFileName, ARRAYSIZE(g_szWallpaperFileName), &szFile)
        .else
            mov hr,HRESULT_FROM_WIN32(ERROR_CANCELLED)
        .endif
    .endif
    .if (SUCCEEDED(hr))

        .new hEditWallpaper:HWND = GetDlgItem(hWnd, IDC_EDIT_WALLPAPER)
         Edit_SetText(hEditWallpaper, &g_szWallpaperFileName)
        .if (g_pWallpaper)
            g_pWallpaper.Release()
            mov g_pWallpaper,NULL
        .endif
        mov hr,LoadPicture(&g_szWallpaperFileName, &g_pWallpaper)
    .endif
    .if (SUCCEEDED(hr))
        InvalidateRect(hWnd, NULL, TRUE)
    .else
        .if (hr != HRESULT_FROM_WIN32(ERROR_CANCELLED))
            ReportError(L"OnBrowseWallpaperButtonClick", hr)
        .endif
    .endif
    CoUninitialize()
    ret
    endp


GetSelectedWallpaperStyle proc hWnd:HWND
    .new style:WallpaperStyle = Stretch
    .if ( Button_GetCheck(GetDlgItem(hWnd, IDC_RADIO_TILE)) == BST_CHECKED )
        mov style,Tile
    .elseif ( Button_GetCheck(GetDlgItem(hWnd, IDC_RADIO_CENTER)) == BST_CHECKED )
        mov style,Center
    .elseif ( Button_GetCheck(GetDlgItem(hWnd, IDC_RADIO_STRETCH)) == BST_CHECKED )
        mov style,Stretch
    .elseif ( Button_GetCheck(GetDlgItem(hWnd, IDC_RADIO_FIT)) == BST_CHECKED )
        mov style,Fit
    .elseif ( Button_GetCheck(GetDlgItem(hWnd, IDC_RADIO_FILL)) == BST_CHECKED )
        mov style,Fill
    .endif
    .return style
    endp


OnSetWallpaperButtonClick proc hWnd:HWND
    .ifsd ( wcslen(&g_szWallpaperFileName) > 0 )
        .new style:WallpaperStyle = GetSelectedWallpaperStyle(hWnd)
        .new hr:HRESULT = SetDesktopWallpaper(&g_szWallpaperFileName, style)
        .if (FAILED(hr))
            ReportError(L"SetDesktopWallpaper", hr)
        .endif
    .endif
    ret
    endp


OnCommand proc hWnd:HWND, id:int_t, hwndCtl:HWND, codeNotify:UINT
    .switch ldr(id)
    .case IDC_BUTTON_BROWSE
        OnBrowseWallpaperButtonClick(ldr(hWnd))
       .endc
    .case IDC_BUTTON_SETWALLPAPER
        OnSetWallpaperButtonClick(ldr(hWnd))
       .endc
    .case IDOK
    .case IDCANCEL
        EndDialog(ldr(hWnd), 0)
       .endc
    .endsw
    ret
    endp


OnClose proc hWnd:HWND
    EndDialog(hWnd, 0)
    ret
    endp


DialogProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch ldr(message)
        HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitDialog)
        HANDLE_MSG(hWnd, WM_COMMAND, OnCommand)
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .endsw
    .return 0
    endp


wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:int_t
    .return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, &DialogProc)
    endp

    end

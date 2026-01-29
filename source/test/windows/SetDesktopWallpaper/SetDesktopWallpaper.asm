;;
;; This code sample application allows you select an image, view a preview
;; (resized smaller to fit if necessary), select a display style among Tile,
;; Center, Stretch, Fit (Windows 7 and later) and Fill (Windows 7 and later),
;; and set the image as the Desktop wallpaper.
;;

include stdio.inc
include windows.inc
include windowsx.inc
include Resource.inc

include strsafe.inc
include shlobj.inc
include shlwapi.inc

include OleCtl.inc
include Commctrl.inc

include Wallpaper.inc

;; Enable Visual Style
ifdef _M_IX86
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_IA64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_X64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
else
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
endif

.code

;;
;;   FUNCTION: ReportError(LPWSTR, DWORD)
;;
;;   PURPOSE: Display an error dialog for the failure of a certain function.
;;
;;   PARAMETERS:
;;   * pszFunction - the name of the function that failed.
;;   * hr - the HRESULT value.
;;
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
ReportError endp

.data

g_szWallpaperFileName wchar_t MAX_PATH dup(0)
g_pWallpaper LPPICTURE NULL

.code

;;
;;   FUNCTION: PctPreviewProc(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR)
;;
;;   PURPOSE:  The new procedure that processes messages for the picture
;;   preview control. Every time a message is received by the new window
;;   procedure, a subclass ID and reference data are included.
;;
PctPreviewProc proc hWnd:HWND, message:UINT, wParam:WPARAM,
                                lParam:LPARAM, uIdSubclass:UINT_PTR,
                                dwRefData:DWORD_PTR

    .switch (message)

    .case WM_PAINT ;; Owner-draw

        .new ps:PAINTSTRUCT
        .new hDC:HDC = BeginPaint(hWnd, &ps)

        ;; Do painting here...
        .if ( g_pWallpaper )

            ;; Get the width and height of the picture.
            .new hmWidth:LONG
            .new hmHeight:LONG

            g_pWallpaper.get_Width(&hmWidth)
            g_pWallpaper.get_Height(&hmHeight)

            ;; Convert himetric to pixels.
            define HIMETRIC_INCH 2540

            .new nWidth:LONG = MulDiv(hmWidth, GetDeviceCaps(hDC, LOGPIXELSX), HIMETRIC_INCH)
            .new nHeight:LONG = MulDiv(hmHeight, GetDeviceCaps(hDC, LOGPIXELSY), HIMETRIC_INCH)

            ;; Get the rect to display the image preview.
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

            ;; Display the picture using IPicture::Render.
            mov ecx,hmHeight
            neg ecx

            g_pWallpaper.Render(hDC, 0, 0, rc.right, rc.bottom,
                    0, hmHeight, hmWidth, ecx, &rc)
        .endif

        EndPaint(hWnd, &ps)
        .return 0

    .default
        .return DefSubclassProc(hWnd, message, wParam, lParam)
    .endsw
    ret
PctPreviewProc endp


;;
;;   FUNCTION: OnInitDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message.
;;
OnInitDialog proc hWnd:HWND, hwndFocus:HWND, lParam:LPARAM

    ;; If the current operating system is not Windows 7 or later, disable the
    ;; Fit and Fill wallpaper styles.
    .if ( !SupportFitFillWallpaperStyles() )

        ;; Disable the Fit and Fill wallpaper styles.

        Button_Enable(GetDlgItem(hWnd, IDC_RADIO_FIT), FALSE)
        Button_Enable(GetDlgItem(hWnd, IDC_RADIO_FILL), FALSE)
    .endif

    Button_SetCheck(GetDlgItem(hWnd, IDC_RADIO_STRETCH), TRUE)

    ;; Subclass the picture preview control.
    .new hPctPreview:HWND = GetDlgItem(hWnd, IDC_STATIC_PREVIEW)
    .new uIdSubclass:UINT_PTR = 0
    .if ( !SetWindowSubclass(hPctPreview, &PctPreviewProc, uIdSubclass, 0) )

        ReportError(L"SetWindowSubclass", E_FAIL)
       .return FALSE
    .endif
    .return TRUE

OnInitDialog endp


LoadPicture proc pszFile:PCWSTR, ppPicture:ptr LPPICTURE

    .new hr:HRESULT = S_OK
    .new hFile:HANDLE = INVALID_HANDLE_VALUE
    .new hGlobal:HGLOBAL = NULL
    .new pData:PVOID = NULL
    .new pstm:LPSTREAM = NULL

    ;; Open the file.
    mov hFile,CreateFile(pszFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)
    .if ( hFile == INVALID_HANDLE_VALUE )

        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif

    ;; Get the file size.
    .new dwFileSize:DWORD = GetFileSize(hFile, NULL)
    .if ( dwFileSize == INVALID_FILE_SIZE )

        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif

    ;; Allocate memory based on the file size using GlobalAlloc.
    mov hGlobal,GlobalAlloc(GMEM_MOVEABLE, dwFileSize)
    .if ( hGlobal == NULL )

        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif

    ;; Lock the global memory object and return a pointer to the block.
    mov pData,GlobalLock(hGlobal)
    .if ( pData == NULL )

        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif

    ;; Read the file and store the data in the global memory.
    .new dwBytesRead:DWORD = 0
    .if ( !ReadFile(hFile, pData, dwFileSize, &dwBytesRead, NULL) )

        mov hr,HRESULT_FROM_WIN32(GetLastError())
        jmp Error
    .endif

    ;; Create IStream* from the global memory.
    mov hr,CreateStreamOnHGlobal(hGlobal, TRUE, &pstm)
    .if ( FAILED(hr) )

        jmp Error
    .endif

    ;; Create IPicture from the image file.
    mov hr,OleLoadPicture(pstm, dwFileSize, FALSE, &IID_IPicture, ppPicture)

Error:
    ;; Clean up the resources in a centralized place.
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

LoadPicture endp

.data

;; Prior to Windows Vista, only .bmp files are supported as wallpaper.
c_rgOldFileTypes COMDLG_FILTERSPEC \
    { @CStr(L"Bitmap Files"),     @CStr(L"*.bmp") }


c_rgNewFileTypes COMDLG_FILTERSPEC \
    { @CStr(L"All Supported Files"),   @CStr(L"*.bmp;*.jpg") },
    { @CStr(L"Bitmap Files"),          @CStr(L"*.bmp") },
    { @CStr(L"Jpg Files"),             @CStr(L"*.jpg") }

.code

;;
;;   FUNCTION: OnBrowseWallpaperButtonClick(HWND)
;;
;;   PURPOSE: The function is invoked when the "Browse..." button is clicked.
;;
OnBrowseWallpaperButtonClick proc hWnd:HWND

    .new hr:HRESULT = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)
    .if (FAILED(hr))

        ReportError(L"CoInitializeEx", hr)
        .return
    .endif

    ;; If running under Vista or later operating system, use the new common
    ;; item dialog.
    .new vi:OSVERSIONINFO = { sizeof(vi) }
     GetVersionEx(&vi)
    .if ( vi.dwMajorVersion >= 6 )

        ;; Create and show a common open file dialog and allow users to select
        ;; an image file.

       .new pfd:ptr IFileDialog = NULL
        mov hr,CoCreateInstance(
                &CLSID_FileOpenDialog,
                NULL,
                CLSCTX_INPROC_SERVER,
                &IID_IFileOpenDialog,
                &pfd)

        .if (SUCCEEDED(hr))

            ;; Set the title of the dialog.
            mov hr,pfd.SetTitle(L"Select Wallpaper")

            ;; Specify file filters for the file dialog.
            .if (SUCCEEDED(hr))

                .if (SupportJpgAsWallpaper())

                    mov hr,pfd.SetFileTypes(ARRAYSIZE(c_rgNewFileTypes), &c_rgNewFileTypes)

                .else

                    mov hr,pfd.SetFileTypes(ARRAYSIZE(c_rgOldFileTypes), &c_rgOldFileTypes)
                .endif

                .if (SUCCEEDED(hr))

                    ;; Set the selected file type index.
                    mov hr,pfd.SetFileTypeIndex(1)
                .endif
            .endif

            ;; Show the open file dialog.
            .if (SUCCEEDED(hr))

                mov hr,pfd.Show(hWnd)
                .if (SUCCEEDED(hr))

                    ;; Get the result of the open file dialog.
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

        ;; Before Windows Vista, the common item dialogs are not supported.
        ;; Use the GetOpenFileName function from the Common Dialog Box Library.
       .new szFile[MAX_PATH]:wchar_t
       .new ofn:OPENFILENAME = { sizeof(ofn) }
        mov ofn.hwndOwner,hWnd
        mov ofn.lpstrFile,&szFile
        mov ofn.lpstrFile[0],0
        mov ofn.nMaxFile,ARRAYSIZE(szFile)
        .if (SupportJpgAsWallpaper())

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

        ;; Display the Open dialog box.
        .if (GetOpenFileName(&ofn))

            mov hr,StringCchCopy(&g_szWallpaperFileName,
                ARRAYSIZE(g_szWallpaperFileName), &szFile)

        .else

            ;; The user pressed the Cancel button.
            mov hr,HRESULT_FROM_WIN32(ERROR_CANCELLED)
        .endif
    .endif

    ;; Fill out the wallpaper file name; load the wallpaper.
    .if (SUCCEEDED(hr))

        .new hEditWallpaper:HWND = GetDlgItem(hWnd, IDC_EDIT_WALLPAPER)
         Edit_SetText(hEditWallpaper, &g_szWallpaperFileName)

        ;; Unload the original picture if any.
        .if (g_pWallpaper)

            g_pWallpaper.Release()
            mov g_pWallpaper,NULL
        .endif

        ;; Load the new picture.
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

OnBrowseWallpaperButtonClick endp


;;
;;   FUNCTION: GetSelectedWallpaperStyle(HWND)
;;
;;   PURPOSE: Get the selected wallpaper style.
;;
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
GetSelectedWallpaperStyle endp


;;
;;   FUNCTION: OnSetWallpaperButtonClick(HWND)
;;
;;   PURPOSE: The function is invoked when the "Set Wallpaper" button is
;;   clicked.
;;
OnSetWallpaperButtonClick proc hWnd:HWND

    .ifsd ( wcslen(&g_szWallpaperFileName) > 0 )

        ;; Get the selected wallpaper style.
        .new style:WallpaperStyle = GetSelectedWallpaperStyle(hWnd)
        .new hr:HRESULT = SetDesktopWallpaper(&g_szWallpaperFileName, style)
        .if (FAILED(hr))

            ReportError(L"SetDesktopWallpaper", hr)
        .endif
    .endif
    ret
OnSetWallpaperButtonClick endp


;;
;;   FUNCTION: OnCommand(HWND, int, HWND, UINT)
;;
;;   PURPOSE: Process the WM_COMMAND message
;;
OnCommand proc hWnd:HWND, id:int_t, hwndCtl:HWND, codeNotify:UINT

    .switch (id)

    .case IDC_BUTTON_BROWSE
        OnBrowseWallpaperButtonClick(hWnd)
        .endc

    .case IDC_BUTTON_SETWALLPAPER
        OnSetWallpaperButtonClick(hWnd)
        .endc

    .case IDOK
    .case IDCANCEL
        EndDialog(hWnd, 0)
        .endc
    .endsw
    ret
OnCommand endp


;;
;;   FUNCTION: OnClose(HWND)
;;
;;   PURPOSE: Process the WM_CLOSE message
;;
OnClose proc hWnd:HWND

    EndDialog(hWnd, 0)
    ret

OnClose endp


;;
;;  FUNCTION: DialogProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the main dialog.
;;
DialogProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitDialog)

        ;; Handle the WM_COMMAND message in OnCommand
        HANDLE_MSG (hWnd, WM_COMMAND, OnCommand)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE
    .endsw
    .return 0
DialogProc endp


;;
;;  FUNCTION: wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
;;
;;  PURPOSE:  The entry point of the application.
;;
wWinMain proc hInstance     : HINSTANCE,
              hPrevInstance : HINSTANCE,
              lpCmdLine     : LPWSTR,
              nCmdShow      : int_t

    .return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, &DialogProc)

wWinMain endp

    end


WINVER equ _WIN32_WINNT_WIN7

include windows.inc
include windowsx.inc
include mfplay.inc
include mferror.inc
include shobjidl.inc ;; defines IFileOpenDialog
include strsafe.inc
include winres.inc
include tchar.inc

option dllimport:none

IDR_MENU1           equ 101
ID_FILE_EXIT        equ 40002
ID_FILE_OPEN        equ 0xE101


InitializeWindow    proto :ptr HWND
PlayMediaFile       proto :HWND, :ptr WCHAR
ShowErrorMessage    proto :PCWSTR, :HRESULT

WindowProc          proto :HWND, :UINT, :WPARAM, :LPARAM

;; Window message handlers
OnClose             proto :HWND
OnPaint             proto :HWND
OnCommand           proto :HWND, :SINT, :HWND, :UINT
OnSize              proto :HWND, :UINT, :SINT, :SINT
OnKeyDown           proto :HWND, :UINT, :BOOL, :SINT, :UINT

;; Menu handlers
OnFileOpen          proto :HWND

;; MFPlay event handler functions.
OnMediaItemCreated  proto :ptr MFP_MEDIAITEM_CREATED_EVENT
OnMediaItemSet      proto :ptr MFP_MEDIAITEM_SET_EVENT

;; Constants
CLASS_NAME          equ <L"MFPlay Window Class">
WINDOW_NAME         equ <L"MFPlay Sample Application">

;;-------------------------------------------------------------------
;;
;; MediaPlayerCallback class
;;
;; Implements the callback interface for MFPlay events.
;;
;;-------------------------------------------------------------------

include Shlwapi.inc

.class MediaPlayerCallback : public IMFPMediaPlayerCallback

    m_cRef LONG ? ;; Reference count

    .inline MediaPlayerCallback {

        .if HeapAlloc(GetProcessHeap(), 0, MediaPlayerCallback + MediaPlayerCallbackVtbl)

            lea rcx,[rax+MediaPlayerCallback]
            mov [rax],rcx
            mov [rax].MediaPlayerCallback.m_cRef,1
            for q,<Release,AddRef,QueryInterface,OnMediaPlayerEvent>
                lea rdx,MediaPlayerCallback_&q
                mov [rcx].MediaPlayerCallbackVtbl.&q,rdx
                endm
        .endif
        }

    .ends
    LPMediaPlayerCallback typedef ptr MediaPlayerCallback

    .data

    ;; Global variables

    g_pPlayer LPIMFPMediaPlayer NULL        ;; The MFPlay player object.
    g_pPlayerCB LPMediaPlayerCallback NULL  ;; Application callback object.
    g_bHasVideo BOOL FALSE;
ifdef _MSVCRT
    IID_IFileOpenDialog  GUID _IID_IFileOpenDialog
    CLSID_FileOpenDialog GUID _CLSID_FileOpenDialog
endif
    .code

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, inCmdShow:int_t

  local hwnd:HWND
  local msg:MSG

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED or COINIT_DISABLE_OLE1DDE)

    .return 0 .if (FAILED(eax))

    mov hwnd,0
    .return .if !InitializeWindow(&hwnd)

    ;; Message loop

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw

    DestroyWindow(hwnd)
    CoUninitialize()

    .return 0

wWinMain endp


;;-------------------------------------------------------------------
;; WindowProc
;;
;; Main window procedure.
;;-------------------------------------------------------------------

WindowProc proc hwnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch edx

        HANDLE_MSG(hwnd, WM_CLOSE,   OnClose)
        HANDLE_MSG(hwnd, WM_KEYDOWN, OnKeyDown)
        HANDLE_MSG(hwnd, WM_PAINT,   OnPaint)
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand)
        HANDLE_MSG(hwnd, WM_SIZE,    OnSize)

    .case WM_ERASEBKGND
        .return 1

    .default
        .return DefWindowProc(rcx, edx, r8, r9)
    .endsw
    ret

WindowProc endp


;;-------------------------------------------------------------------
;; InitializeWindow
;;
;; Creates the main application window.
;;-------------------------------------------------------------------

InitializeWindow proc pHwnd:ptr HWND

  local wc:WNDCLASSEX
  local hwnd:HWND

    mov wc.cbSize,        WNDCLASSEX
    mov wc.style,         CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,   &WindowProc
    mov wc.hInstance,     GetModuleHandle(NULL)
    mov wc.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wc.lpszClassName, &@CStr(CLASS_NAME)
    mov wc.lpszMenuName,  MAKEINTRESOURCE(IDR_MENU1)
    mov wc.hIcon,         NULL
    mov wc.hIconSm,       NULL
    mov wc.cbClsExtra,    0
    mov wc.cbWndExtra,    0
    mov wc.hbrBackground, COLOR_WINDOW+1

    .if (!RegisterClassEx(&wc))

        .return FALSE
    .endif

    mov hwnd,CreateWindowEx(
        0,
        CLASS_NAME,
        WINDOW_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        wc.hInstance,
        NULL
        )

    .if (!hwnd)

        .return FALSE
    .endif

    ShowWindow(hwnd, SW_SHOWDEFAULT)
    UpdateWindow(hwnd)

    mov rcx,pHwnd
    mov rax,hwnd
    mov [rcx],rax

    .return TRUE

InitializeWindow endp

;;-------------------------------------------------------------------
;; OnClose
;;
;; Handles the WM_CLOSE message.
;;-------------------------------------------------------------------

OnClose proc hwnd:HWND

    .if (g_pPlayer)

        g_pPlayer.Shutdown()
        g_pPlayer.Release()
        mov g_pPlayer,NULL
    .endif

    .if (g_pPlayerCB)

        g_pPlayerCB.Release()
        mov g_pPlayerCB,NULL
    .endif

    PostQuitMessage(0)
    ret

OnClose endp


;;-------------------------------------------------------------------
;; OnPaint
;;
;; Handles the WM_PAINT message.
;;-------------------------------------------------------------------

OnPaint proc hwnd:HWND

  local ps:PAINTSTRUCT
  local hdc:HDC

    mov hdc,BeginPaint(hwnd, &ps)

    .if (g_pPlayer && g_bHasVideo)

        ;; Playback has started and there is video.

        ;; Do not draw the window background, because the video
        ;; frame fills the entire client area.

        g_pPlayer.UpdateVideo()

    .else

        ;; There is no video stream, or playback has not started.
        ;; Paint the entire client area.

        FillRect(hdc, &ps.rcPaint, (COLOR_WINDOW+1))
    .endif

    EndPaint(hwnd, &ps)
    ret

OnPaint endp


;;-------------------------------------------------------------------
;; OnSize
;;
;; Handles the WM_SIZE message.
;;-------------------------------------------------------------------

OnSize proc hwnd:HWND, state:UINT, x:SINT, y:SINT

    .if (state == SIZE_RESTORED)

        .if (g_pPlayer)

            ;; Resize the video.
            g_pPlayer.UpdateVideo()
        .endif
    .endif
    ret

OnSize endp


;;-------------------------------------------------------------------
;; OnKeyDown
;;
;; Handles the WM_KEYDOWN message.
;;-------------------------------------------------------------------

OnKeyDown proc hwnd:HWND, vk:UINT, fDown:BOOL, cRepeat:SINT, flags:UINT

  local hr:HRESULT

    mov hr,S_OK

    .switch (vk)

    .case VK_SPACE

        ;; Toggle between playback and paused/stopped.
        .if (g_pPlayer)

           .new state:MFP_MEDIAPLAYER_STATE
            mov state,MFP_MEDIAPLAYER_STATE_EMPTY
            mov hr,g_pPlayer.GetState(&state)

            .if (SUCCEEDED(hr))

                .if (state == MFP_MEDIAPLAYER_STATE_PAUSED || state == MFP_MEDIAPLAYER_STATE_STOPPED)

                    mov hr,g_pPlayer.Play()

                .elseif (state == MFP_MEDIAPLAYER_STATE_PLAYING)

                    mov hr,g_pPlayer._Pause()
                .endif
            .endif
        .endif
        .endc
    .endsw

    .if (FAILED(hr))

        ShowErrorMessage("Playback Error", hr)
    .endif
    ret

OnKeyDown endp


;;-------------------------------------------------------------------
;; OnCommand
;;
;; Handles the WM_COMMAND message.
;;-------------------------------------------------------------------

OnCommand proc hwnd:HWND, id:SINT, hwndCtl:HWND, codeNotify:UINT

    .switch edx
    .case ID_FILE_OPEN
        OnFileOpen(rcx)
        .endc
    .case ID_FILE_EXIT
        OnClose(rcx)
        .endc
    .endsw
    ret

OnCommand endp


;;-------------------------------------------------------------------
;; OnFileOpen
;;
;; Handles the "File Open" command.
;;-------------------------------------------------------------------

OnFileOpen proc hwnd:HWND

  local hr:HRESULT
  local pFileOpen:ptr IFileOpenDialog
  local pItem:ptr IShellItem
  local pwszFilePath:PWSTR

    mov hr,S_OK
    mov pFileOpen,NULL
    mov pItem,NULL
    mov pwszFilePath,NULL

    ;; Create the FileOpenDialog object.

    mov hr,CoCreateInstance(
        &CLSID_FileOpenDialog,
        NULL,
        CLSCTX_INPROC_SERVER,
        &IID_IFileOpenDialog,
        &pFileOpen
        )

    .repeat

        .break .if (FAILED(hr))

        mov hr,pFileOpen.SetTitle(L"Select a File to Play")

        .break .if (FAILED(hr))

        ;; Show the file-open dialog.
        mov hr,pFileOpen.Show(hwnd)

        .if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))

            ;; User cancelled.
            mov hr,S_OK
            .break
        .endif

        .break .if FAILED(hr)


        ;; Get the file name from the dialog.
        mov hr,pFileOpen.GetResult(&pItem)

        .break .if FAILED(hr)

        mov hr,pItem.GetDisplayName(SIGDN_URL, &pwszFilePath)

        .break .if FAILED(hr)

        ;; Open the media file.
        mov hr,PlayMediaFile(hwnd, pwszFilePath)

    .until 1

    .if FAILED(hr)

        ShowErrorMessage(L"Could not open file.", hr)
    .endif

    CoTaskMemFree(pwszFilePath)

    .if pItem

        pItem.Release()
    .endif
    .if pFileOpen

        pFileOpen.Release()
    .endif
    ret

OnFileOpen endp


;;-------------------------------------------------------------------
;; PlayMediaFile
;;
;; Plays a media file, using the IMFPMediaPlayer interface.
;;-------------------------------------------------------------------

PlayMediaFile proc hwnd:HWND, sURL:ptr WCHAR

    ;; Create the MFPlayer object.

    .if (g_pPlayer == NULL)

        mov g_pPlayerCB,MediaPlayerCallback()

        .if (g_pPlayerCB == NULL)

            .return E_OUTOFMEMORY
        .endif

        MFPCreateMediaPlayer(
            NULL,
            FALSE,          ;; Start playback automatically?
            0,              ;; Flags
            g_pPlayerCB,    ;; Callback pointer
            hwnd,           ;; Video window
            &g_pPlayer
            )

        .return .if (FAILED(eax))
    .endif

    ;; Create a new media item for this URL.
    g_pPlayer.CreateMediaItemFromURL(sURL, FALSE, 0, NULL)

    ;; The CreateMediaItemFromURL method completes asynchronously.
    ;; The application will receive an MFP_EVENT_TYPE_MEDIAITEM_CREATED
    ;; event. See MediaPlayerCallback::OnMediaPlayerEvent().

    ret

PlayMediaFile endp


;;-------------------------------------------------------------------
;; OnMediaPlayerEvent
;;
;; Implements IMFPMediaPlayerCallback::OnMediaPlayerEvent.
;; This callback method handles events from the MFPlay object.
;;-------------------------------------------------------------------

MediaPlayerCallback::OnMediaPlayerEvent proc pEventHeader:ptr MFP_EVENT_HEADER

    mov eax,[rdx].MFP_EVENT_HEADER.hrEvent
    .if (FAILED(eax))

        ShowErrorMessage(L"Playback error", eax)
        .return
    .endif

    mov eax,[rdx].MFP_EVENT_HEADER.eEventType

    .switch eax

    .case MFP_EVENT_TYPE_MEDIAITEM_CREATED
        OnMediaItemCreated(MFP_GET_MEDIAITEM_CREATED_EVENT(pEventHeader))
        .endc

    .case MFP_EVENT_TYPE_MEDIAITEM_SET
        OnMediaItemSet(MFP_GET_MEDIAITEM_SET_EVENT(pEventHeader))
        .endc
    .endsw
    ret

MediaPlayerCallback::OnMediaPlayerEvent endp


;;-------------------------------------------------------------------
;; OnMediaItemCreated
;;
;; Called when the IMFPMediaPlayer::CreateMediaItemFromURL method
;; completes.
;;-------------------------------------------------------------------

OnMediaItemCreated proc pEvent:ptr MFP_MEDIAITEM_CREATED_EVENT

    ;; The media item was created successfully.

    xor eax,eax
    .repeat

       .break .if g_pPlayer == rax

       .new bHasVideo:BOOL
       .new bIsSelected:BOOL

        mov bHasVideo,FALSE
        mov bIsSelected,FALSE

        ;; Check if the media item contains video.
        pEvent.pMediaItem.HasVideo(&bHasVideo, &bIsSelected)
        .break .if FAILED(eax)

        xor eax,eax
        .if bHasVideo && bIsSelected
            inc eax
        .endif
        mov g_bHasVideo,eax

        ;; Set the media item on the player. This method completes asynchronously.
        mov rcx,pEvent
        g_pPlayer.SetMediaItem([rcx].MFP_MEDIAITEM_CREATED_EVENT.pMediaItem)

    .until 1

    .if (FAILED(eax))

        ShowErrorMessage(L"Error playing this file.", eax)
    .endif
    ret

OnMediaItemCreated endp


;;-------------------------------------------------------------------
;; OnMediaItemSet
;;
;; Called when the IMFPMediaPlayer::SetMediaItem method completes.
;;-------------------------------------------------------------------

OnMediaItemSet proc pEvent:ptr MFP_MEDIAITEM_SET_EVENT

    g_pPlayer.Play()
    .if (FAILED(eax))

        ShowErrorMessage(L"IMFPMediaPlayer::Play failed.", eax)
    .endif
    ret

OnMediaItemSet endp


ShowErrorMessage proc format:PCWSTR, hrErr:HRESULT

  local hr:HRESULT
  local msg[MAX_PATH]:WCHAR

    mov hr,S_OK
ifdef _MSVCRT
    swprintf(&msg, "%s (hr=0x%X)", format, hrErr)
else
    mov hr,StringCbPrintf(msg, sizeof(msg), L"%s (hr=0x%X)", format, hrErr)
endif

    .if (SUCCEEDED(hr))

        MessageBox(NULL, &msg, L"Error", MB_ICONERROR)
    .endif
    ret

ShowErrorMessage endp

    assume rcx: ptr MediaPlayerCallback

MediaPlayerCallback::QueryInterface proc riid:REFIID, ppv:ptr ptr

    xor eax,eax
    mov [r8],rax
    mov eax,E_NOINTERFACE
    ret

MediaPlayerCallback::QueryInterface endp

MediaPlayerCallback::AddRef proc

    InterlockedIncrement(&[rcx].m_cRef)
    ret

MediaPlayerCallback::AddRef endp

MediaPlayerCallback::Release proc

    InterlockedDecrement(&[rcx].m_cRef)
    .if (eax == 0)

        HeapFree(GetProcessHeap(), 0, this)
        xor eax,eax
    .endif
    ret

MediaPlayerCallback::Release endp

    RCBEGIN
    RCTYPES 1
    RCENTRY RT_MENU
    RCENUMN 1
    RCENUMX IDR_MENU1
    RCLANGX LANGID_US
    MENUBEGIN
     MENUNAME "&File", MF_END
      MENUITEM ID_FILE_OPEN, "&Open"
      SEPARATOR
      MENUITEM ID_FILE_EXIT, "&Exit", MF_END
    MENUEND
    RCEND

    end _tstart

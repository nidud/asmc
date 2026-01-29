; COMMONCONTROLS.ASM--
;
; CommonControls contains simple examples of how to create common
; controls defined in comctl32.dll. The controls include Animation, ComboBoxEx,
; Updown, Header, MonthCal, DateTimePick, ListView, TreeView, Tab, Tooltip, IP
; Address, Statusbar, Progress Bar, Toolbar, Trackbar, and SysLink.
;
; https://github.com/microsoftarchive/msdn-code-gallery-microsoft/
;
include stdio.inc
include windows.inc
include windowsx.inc
include Resource.inc
include assert.inc

include commctrl.inc

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

.data
g_hInst HINSTANCE 0 ;; The handle to the instance of the current module

.code

;;
;;   FUNCTION: OnClose(HWND)
;;
;;   PURPOSE: Process the WM_CLOSE message
;;

OnClose proc hWnd:HWND

    EndDialog(hWnd, 0)
    ret

OnClose endp

;; MSDN: Animation Control
;; http://msdn.microsoft.com/en-us/library/bb761881.aspx

define IDC_ANIMATION 990


;;
;;   FUNCTION: OnInitAnimationDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitAnimationDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register animation control class.
    .new iccx:INITCOMMONCONTROLSEX = { sizeof(iccx) }

    mov iccx.dwICC,ICC_ANIMATE_CLASS
    .if (!InitCommonControlsEx(&iccx))

        .return FALSE
    .endif

    ;; Create the animation control.
    .new rc:RECT = { 20, 20, 280, 60 }
    .new hAnimate:HWND = CreateWindowEx(0, ANIMATE_CLASS, 0,
            ACS_TIMER or ACS_AUTOPLAY or ACS_TRANSPARENT or WS_CHILD or WS_VISIBLE,
            rc.left, rc.top, rc.right, rc.bottom,
            hWnd, IDC_ANIMATION, g_hInst, 0)

    .if (hAnimate == NULL)

        .return FALSE
    .endif

    ;; Open the AVI clip and display its first frame in the animation control.
    .if ( SendMessage(hAnimate, ACM_OPEN, 0, MAKEINTRESOURCE(IDR_UPLOAD_AVI)) == 0 )

        .return FALSE
    .endif

    ;; Plays the AVI clip in the animation control.
    .if ( SendMessage(hAnimate, ACM_PLAY, -1, MAKELONG(0, -1)) == 0 )

        .return FALSE
    .endif
    .return TRUE

OnInitAnimationDialog endp


;;
;;  FUNCTION: AnimationDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Animation control dialog.
;;

AnimationDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitAnimationDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitAnimationDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

AnimationDlgProc endp

;; MSDN: ComboBoxEx Control Reference
;; http://msdn.microsoft.com/en-us/library/bb775740.aspx

define IDC_COMBOBOXEX 1990


;;
;;   FUNCTION: OnInitComboBoxExDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitComboBoxExDialog proc uses rbx hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register ComboBoxEx control class.

    .new iccx:INITCOMMONCONTROLSEX = { sizeof(iccx) }
     mov iccx.dwICC,ICC_USEREX_CLASSES

    .if (!InitCommonControlsEx(&iccx))

        .return FALSE
    .endif

    ;; Create the ComboBoxEx control.

    .new rc:RECT = { 20, 20, 280, 100 }
    .new hComboEx:HWND = CreateWindowEx(0, WC_COMBOBOXEX, 0, CBS_DROPDOWN or WS_CHILD or WS_VISIBLE,
            rc.left, rc.top, rc.right, rc.bottom, hWnd, IDC_COMBOBOXEX, g_hInst, 0)

    .if (hComboEx == NULL)

        .return FALSE
    .endif

    ;; Create an image list to hold icons for use by the ComboBoxEx control.
    ;; The image list is destroyed in OnComboBoxExClose.

    .new lpszResID[3]:PCWSTR = { IDI_APPLICATION, IDI_INFORMATION, IDI_QUESTION }
    .new nIconCount:int_t = ARRAYSIZE(lpszResID)
    .new hImageList:HIMAGELIST = ImageList_Create(16, 16, ILC_MASK or ILC_COLOR32, nIconCount, 0)
    .if (hImageList == NULL)

        .return FALSE
    .endif

    .for (ebx = 0: ebx < nIconCount: ebx++)

        .new hIcon:HANDLE = LoadImage(NULL, lpszResID[rbx*PCWSTR], IMAGE_ICON, 0, 0, LR_SHARED)
        .if (hIcon != NULL)

            ImageList_AddIcon(hImageList, hIcon)
        .endif
    .endf

    ;; Associate the image list with the ComboBoxEx common control
    SendMessage(hComboEx, CBEM_SETIMAGELIST, 0, hImageList)

    ;; Add nIconCount items to the ComboBoxEx common control
    .new szText[200]:wchar_t
    .for (ebx = 0: ebx < nIconCount: ebx++)

       .new cbei:COMBOBOXEXITEM = {0}
        mov cbei.mask,CBEIF_IMAGE or CBEIF_TEXT or CBEIF_SELECTEDIMAGE
        mov cbei.iItem,-1
        swprintf_s(&szText, 200, L"Item  %d", ebx)
        mov cbei.pszText,&szText
        mov cbei.iImage,ebx
        mov cbei.iSelectedImage,ebx
        SendMessage(hComboEx, CBEM_INSERTITEM, 0, &cbei)
    .endf

    ;; Store the image list handle as the user data of the window so that it
    ;; can be destroyed when the window is destroyed. (See OnComboBoxExClose)

    SetWindowLongPtr(hWnd, GWLP_USERDATA, hImageList)
   .return TRUE

OnInitComboBoxExDialog endp

;;
;;   FUNCTION: OnComboBoxExClose(HWND)
;;
;;   PURPOSE: Process the WM_CLOSE message
;;

OnComboBoxExClose proc hWnd:HWND

    ;; Destroy the image list associated with the ComboBoxEx control
    ImageList_Destroy(GetWindowLongPtr(hWnd, GWLP_USERDATA))

    DestroyWindow(hWnd)
    ret

OnComboBoxExClose endp

;;
;;  FUNCTION: ComboBoxExDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the ComboBoxEx control dialog.
;;
;;

ComboBoxExDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitComboBoxExDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitComboBoxExDialog)

        ;; Handle the WM_CLOSE message in OnComboBoxExClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnComboBoxExClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

ComboBoxExDlgProc endp

;; MSDN: Up-Down Control
;; http://msdn.microsoft.com/en-us/library/bb759880.aspx

define IDC_EDIT        2990
define IDC_UPDOWN      2991

;;
;;   FUNCTION: OnInitUpdownDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitUpdownDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Updown control class
    .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_UPDOWN_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create an Edit control
    .new rc:RECT = { 20, 20, 100, 24 }
    .new hEdit:HWND = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_EDIT, g_hInst, 0)

    ;; Create the ComboBoxEx control
    SetRect(&rc, 20, 60, 180, 20)
    .new hUpdown:HWND = CreateWindowEx(0, UPDOWN_CLASS, 0,
        UDS_ALIGNRIGHT or UDS_SETBUDDYINT or UDS_WRAP or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_UPDOWN, g_hInst, 0)

    ;; Explicitly attach the Updown control to its 'buddy' edit control
    SendMessage(hUpdown, UDM_SETBUDDY, hEdit, 0)
   .return TRUE

OnInitUpdownDialog endp

;;
;;  FUNCTION: UpdownDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Updown control dialog.
;;
;;

UpdownDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitUpdownDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitUpdownDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0
UpdownDlgProc endp


;; MSDN: Header Control
;; http:;;msdn.microsoft.com/en-us/library/bb775239.aspx

define IDC_HEADER          3990

;;
;;   FUNCTION: OnHeaderSize(HWND, UINT, int, int)
;;
;;   PURPOSE: Process the WM_SIZE message
;;

OnHeaderSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t

    ;; Adjust the position and the layout of the Header control
    .new rc:RECT = { 0, 0, x, y }
    .new wp:WINDOWPOS = { 0 }
    .new hdl:HDLAYOUT = { &rc, &wp }

    ;; Get the header control handle which has been previously stored in the
    ;; user data associated with the parent window.
    .new hHeader:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)

    ;; hdl.wp retrieves information used to set the size and postion of the
    ;; header control within the target rectangle of the parent window.
    SendMessage(hHeader, HDM_LAYOUT, 0, &hdl)

    ;; Set the size and position of the header control based on hdl.wp.
    add wp.cy,8
    SetWindowPos(hHeader, wp.hwndInsertAfter, wp.x, wp.y, wp._cx, wp.cy, wp.flags)
    ret

OnHeaderSize endp

;;
;;   FUNCTION: OnInitHeaderDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitHeaderDialog proc uses rbx hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Header control class
    .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_WIN95_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the Header control
    .new rc:RECT = { 0, 0, 0, 0 }
    .new hHeader:HWND = CreateWindowEx(0, WC_HEADER, 0,
        HDS_BUTTONS or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_HEADER, g_hInst, 0)

    ;; Store the header control handle as the user data associated with the
    ;; parent window so that it can be retrieved for later use.
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hHeader)

    ;; Resize the header control
    GetClientRect(hWnd, &rc)
    OnHeaderSize(hWnd, 0, rc.right, rc.bottom)

    ;; Set the font for the header common control
    SendMessage(hHeader, WM_SETFONT, GetStockObject(DEFAULT_GUI_FONT), 0)

    ;; Add 4 Header items
    .new szText[200]:TCHAR
    .for (ebx = 0: ebx < 4: ebx++)

        .new hdi:HDITEM = {0}
        mov hdi.mask,HDI_WIDTH or HDI_FORMAT or HDI_TEXT
        mov eax,rc.right
        shr eax,2
        mov hdi.cxy,eax
        mov hdi.fmt,HDF_CENTER
        swprintf_s(&szText, 200, L"Header  %d", ebx)
        mov hdi.pszText,&szText
        mov hdi.cchTextMax,200

        SendMessage(hHeader, HDM_INSERTITEM, ebx, &hdi)
    .endf
    .return TRUE

OnInitHeaderDialog endp

;;
;;  FUNCTION: HeaderDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Header control dialog.
;;
;;

HeaderDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitHeaderDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitHeaderDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

        ;; Handle the WM_SIZE message in OnHeaderSize
        HANDLE_MSG (hWnd, WM_SIZE, OnHeaderSize)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

HeaderDlgProc endp


;; MSDN: Month Calendar Control Reference
;; http://msdn.microsoft.com/en-us/library/bb760917.aspx

define IDC_MONTHCAL        4990

;;
;;   FUNCTION: OnInitMonthCalDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitMonthCalDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register MonthCal control class
    .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_DATE_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the Month Calendar control
    .new rc:RECT = { 20, 20, 280, 200 }
    .new hMonthCal:HWND = CreateWindowEx(0, MONTHCAL_CLASS, 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_MONTHCAL, g_hInst, 0)
    .return TRUE

OnInitMonthCalDialog endp

;;
;;  FUNCTION: MonthCalDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the MonthCal control dialog.
;;
;;

MonthCalDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitMonthCalDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitMonthCalDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0
MonthCalDlgProc endp

;; MSDN: Date and Time Picker
;; http://msdn.microsoft.com/en-us/library/bb761727.aspx

define IDC_DATETIMEPICK        5990

;;
;;   FUNCTION: OnInitDateTimePickDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitDateTimePickDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register DateTimePick control class
    .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_DATE_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the DateTimePick control
    .new rc:RECT = { 20, 20, 150, 30 }
    .new hDateTimePick:HWND = CreateWindowEx(0, DATETIMEPICK_CLASS, 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_DATETIMEPICK, g_hInst, 0)

    .return TRUE

OnInitDateTimePickDialog endp

;;
;;  FUNCTION: DateTimePickDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the DateTimePick control dialog.
;;
;;

DateTimePickDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitDateTimePickDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitDateTimePickDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

DateTimePickDlgProc endp

;; MSDN: List View
;; http://msdn.microsoft.com/en-us/library/bb774737.aspx

define IDC_LISTVIEW        6990

.template LVHandles
    hListview HWND ?
    hLargeIcons HIMAGELIST ?
    hSmallIcons HIMAGELIST ?
   .ends


;;
;;   FUNCTION: OnListviewSize(HWND, UINT, int, int)
;;
;;   PURPOSE: Process the WM_SIZE message
;;

OnListviewSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t

    ;; Get the pointer to listview information which was previously stored in
    ;; the user data associated with the parent window.
    .new lvh:ptr LVHandles = GetWindowLongPtr(hWnd, GWLP_USERDATA)

    ;; Resize the listview control to fill the parent window's client area
    mov rcx,lvh
    MoveWindow([rcx].LVHandles.hListview, 0, 0, x, y, 1)

    ;; Arrange contents of listview along top of control
    mov rcx,lvh
    SendMessage([rcx].LVHandles.hListview, LVM_ARRANGE, LVA_ALIGNTOP, 0)
    ret

OnListviewSize endp

;;
;;   FUNCTION: OnInitListviewDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitListviewDialog proc uses rsi rdi rbx hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Listview control class
    .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_LISTVIEW_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create storage for struct to contain information about the listview
    ;; (window and image list handles).
    mov rsi,malloc(LVHandles)


    ;; Store that pointer as the user data associated with the parent window
    ;; so that it can be retrieved for later use.
    SetWindowLongPtr(hWnd, GWLP_USERDATA, rsi)

    ;; Create the Listview control
    .new rc:RECT
    GetClientRect(hWnd, &rc)
    mov [rsi].LVHandles.hListview,CreateWindowEx(0, WC_LISTVIEW, 0,
        LVS_ICON or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_LISTVIEW, g_hInst, 0)


    ;;
    ;; Set up and attach image lists to list view common control.
    ;;

    ;; Create the image lists
    .new lx:int_t = GetSystemMetrics(SM_CXICON)
    .new ly:int_t = GetSystemMetrics(SM_CYICON)
     mov [rsi].LVHandles.hLargeIcons,ImageList_Create(lx, ly, ILC_COLOR32 or ILC_MASK, 1, 1)
    .new sx:int_t = GetSystemMetrics(SM_CXSMICON)
    .new sy:int_t = GetSystemMetrics(SM_CYSMICON)
     mov [rsi].LVHandles.hSmallIcons,ImageList_Create(sx, sy, ILC_COLOR32 or ILC_MASK, 1, 1)

    ;; Add icons to image lists
    .new hLargeIcon:HICON
    .new hSmallIcon:HICON
    .for (ebx = IDI_ICON1: ebx <= IDI_ICON10: ebx++)

        ;; Load and add the large icon
        mov hLargeIcon,LoadImage(g_hInst, MAKEINTRESOURCE(rbx), IMAGE_ICON, lx, ly, 0)
        ImageList_AddIcon([rsi].LVHandles.hLargeIcons, hLargeIcon)
        DestroyIcon(hLargeIcon)

        ;; Load and add the small icon
        mov hSmallIcon,LoadImage(g_hInst, MAKEINTRESOURCE(rbx), IMAGE_ICON, sx, sy, 0)
        ImageList_AddIcon([rsi].LVHandles.hSmallIcons, hSmallIcon)
        DestroyIcon(hSmallIcon)
    .endf

    ;; Attach image lists to list view common control
    ListView_SetImageList([rsi].LVHandles.hListview, [rsi].LVHandles.hLargeIcons, LVSIL_NORMAL)
    ListView_SetImageList([rsi].LVHandles.hListview, [rsi].LVHandles.hSmallIcons, LVSIL_SMALL)


    ;;
    ;; Add items to the the list view common control.
    ;;

    .new lvi:LVITEM = {0}
     mov lvi.mask,LVIF_TEXT or LVIF_IMAGE
    .new szText[200]:TCHAR
    .for (ebx = 0: ebx < 10: ebx++)

        mov lvi.iItem,ebx
        swprintf_s(&szText, 200, L"Item  %d", ebx)
        mov lvi.pszText,&szText
        mov lvi.iImage,ebx

        SendMessage([rsi].LVHandles.hListview, LVM_INSERTITEM, 0, &lvi)
    .endf

    .return TRUE

OnInitListviewDialog endp

;;
;;   FUNCTION: OnListviewClose(HWND)
;;
;;   PURPOSE: Process the WM_CLOSE message
;;

OnListviewClose proc uses rsi hWnd:HWND

    ;; Free up resources

    ;; Get the information which was previously stored as the user data of
    ;; the main window
    mov rsi,GetWindowLongPtr(hWnd, GWLP_USERDATA)

    ;; Destroy the image lists
    ImageList_Destroy([rsi].LVHandles.hLargeIcons)
    ImageList_Destroy([rsi].LVHandles.hSmallIcons)
    free(rsi)

    DestroyWindow(hWnd)
    ret

OnListviewClose endp

;;
;;  FUNCTION: ListviewDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Listview control dialog.
;;
;;

ListviewDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitListviewDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitListviewDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnListviewClose)

        ;; Handle the WM_SIZE message in OnListviewSize
        HANDLE_MSG (hWnd, WM_SIZE, OnListviewSize)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

ListviewDlgProc endp


;; MSDN: Tree View
;; http://msdn.microsoft.com/en-us/library/bb759988.aspx

define IDC_TREEVIEW        7990

;;
;;   FUNCTION: OnTreeviewSize(HWND, UINT, int, int)
;;
;;   PURPOSE: Process the WM_SIZE message
;;

OnTreeviewSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t

    ;; Get the treeview control handle which was previously stored in the
    ;; user data associated with the parent window.
    .new hTreeview:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)

    ;; Resize treeview control to fill client area of its parent window
    MoveWindow(hTreeview, 0, 0, x, y, TRUE)
    ret

OnTreeviewSize endp

InsertTreeviewItem proc hTreeview:HWND, pszText:LPTSTR, htiParent:HTREEITEM

    .new tvi:TVITEM = {0}
     mov tvi.mask,TVIF_TEXT or TVIF_IMAGE or TVIF_SELECTEDIMAGE
     mov tvi.pszText,pszText
     mov tvi.cchTextMax,wcslen(pszText)
     mov tvi.iImage,0

    .new tvis:TVINSERTSTRUCT = {0}
     mov tvi.iSelectedImage,1
     mov tvis.item,&tvi
     mov tvis.hInsertAfter,0
     mov tvis.hParent,htiParent

    .return SendMessage(hTreeview, TVM_INSERTITEM, 0, &tvis)

InsertTreeviewItem endp

;;
;;   FUNCTION: OnInitTreeviewDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitTreeviewDialog proc uses rbx hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Treeview control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_TREEVIEW_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the Treeview control
    .new rc:RECT
     GetClientRect(hWnd, &rc)
    .new hTreeview:HWND = CreateWindowEx(0, WC_TREEVIEW, 0,
        TVS_HASLINES or TVS_LINESATROOT or TVS_HASBUTTONS or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_TREEVIEW, g_hInst, 0)

    ;; Store the Treeview control handle as the user data associated with the
    ;; parent window so that it can be retrieved for later use.
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hTreeview)


    ;;
    ;; Set up and attach image lists to tree view common control.
    ;;

    ;; Create an image list
    .new x:int_t = GetSystemMetrics(SM_CXSMICON)
    .new y:int_t = GetSystemMetrics(SM_CYSMICON)
    .new hImages:HIMAGELIST = ImageList_Create(x, y, ILC_COLOR32 or ILC_MASK, 1, 1)

    ;; Get an instance handle for a source of icon images
    .new hLib:HINSTANCE = LoadLibrary(L"shell32.dll")
    .if (hLib)

        .for (ebx = 4: ebx < 6: ebx++)

            ;; Because the icons are loaded from system resources (i.e. they are
            ;; shared), it is not necessary to free resources with 'DestroyIcon'.
            .new hIcon:HICON = LoadImage(hLib, MAKEINTRESOURCE(rbx), IMAGE_ICON, 0, 0, LR_SHARED)
            ImageList_AddIcon(hImages, hIcon)
        .endf

        FreeLibrary(hLib)
        mov hLib,NULL
    .endif

    ;; Attach image lists to tree view common control
    TreeView_SetImageList(hTreeview, hImages, TVSIL_NORMAL)


    ;;
    ;; Add items to the tree view common control.
    ;;

    ;; Insert the first item at root level
    .new hPrev:HTREEITEM = InsertTreeviewItem(hTreeview, L"First", TVI_ROOT)

    ;; Sub item of first item
    mov hPrev,InsertTreeviewItem(hTreeview, L"Level01", hPrev)

    ;; Sub item of 'level01' item
    mov hPrev,InsertTreeviewItem(hTreeview, L"Level02", hPrev)

    ;; Insert the second item at root level
    mov hPrev,InsertTreeviewItem(hTreeview, L"Second", TVI_ROOT)

    ;; Insert the third item at root level
    mov hPrev,InsertTreeviewItem(hTreeview, L"Third", TVI_ROOT)

    .return TRUE

OnInitTreeviewDialog endp

;;
;;   FUNCTION: OnTreeviewClose(HWND)
;;
;;   PURPOSE: Process the WM_CLOSE message
;;

OnTreeviewClose proc hWnd:HWND

    ;; Get the treeview control handle which was previously stored in the
    ;; user data associated with the parent window.
    .new hTreeview:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)

    ;; Free resources used by the treeview's image list
    .new hImages:HIMAGELIST = TreeView_GetImageList(hTreeview, TVSIL_NORMAL)
    ImageList_Destroy(hImages)

    DestroyWindow(hWnd)
    ret

OnTreeviewClose endp

;;
;;  FUNCTION: TreeviewDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Treeview control dialog.
;;
;;

TreeviewDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitTreeviewDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitTreeviewDialog)

        ;; Handle the WM_CLOSE message in OnTreeviewClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnTreeviewClose)

        ;; Handle the WM_SIZE message in OnTreeviewSize
        HANDLE_MSG (hWnd, WM_SIZE, OnTreeviewSize)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

TreeviewDlgProc endp

;; MSDN: Tab
;; http://msdn.microsoft.com/en-us/library/bb760548.aspx

define IDC_TAB         8990

;;
;;   FUNCTION: OnTabSize(HWND, UINT, int, int)
;;
;;   PURPOSE: Process the WM_SIZE message
;;

OnTabSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t

    ;; Get the Tab control handle which was previously stored in the
    ;; user data associated with the parent window.
    .new hTab:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)

    ;; Resize tab control to fill client area of its parent window
    sub x,4
    sub y,4
    MoveWindow(hTab, 2, 2, x, y, TRUE)
    ret

OnTabSize endp

InsertTabItem proc hTab:HWND, pszText:LPTSTR, iid:int_t

    .new ti:TCITEM = {0}
     mov ti.mask,TCIF_TEXT
     mov ti.pszText,pszText
     mov ti.cchTextMax,wcslen(pszText)

    .return SendMessage(hTab, TCM_INSERTITEM, iid, &ti)

InsertTabItem endp

;;
;;   FUNCTION: OnInitTabControlDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitTabControlDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Tab control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_TAB_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the Tab control
    .new rc:RECT
     GetClientRect(hWnd, &rc)
     sub rc.right,4
     sub rc.bottom,4
     add rc.left,2
     add rc.top,2
    .new hTab:HWND = CreateWindowEx(0, WC_TABCONTROL, 0,
        TCS_FIXEDWIDTH or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_TAB, g_hInst, 0)

    ;; Set the font of the tabs to a more typical system GUI font
    SendMessage(hTab, WM_SETFONT, GetStockObject(DEFAULT_GUI_FONT), 0)

    ;; Store the Tab control handle as the user data associated with the
    ;; parent window so that it can be retrieved for later use.
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hTab)


    ;;
    ;; Add items to the tab common control.
    ;;

    InsertTabItem(hTab, L"First Page", 0)
    InsertTabItem(hTab, L"Second Page", 1)
    InsertTabItem(hTab, L"Third Page", 2)
    InsertTabItem(hTab, L"Fourth Page", 3)
    InsertTabItem(hTab, L"Fifth Page", 4)

   .return TRUE

OnInitTabControlDialog endp

;;
;;  FUNCTION: TabControlDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the TabControl control dialog.
;;
;;

TabControlDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitTabControlDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitTabControlDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

        ;; Handle the WM_SIZE message in OnTabSize
        HANDLE_MSG (hWnd, WM_SIZE, OnTabSize)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

TabControlDlgProc endp


;; MSDN: ToolTip
;; http://msdn.microsoft.com/en-us/library/bb760246.aspx

define IDC_BUTTON1     9990

;;
;;   FUNCTION: OnInitTooltipDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitTooltipDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Tooltip control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_WIN95_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create a button control
    .new rc:RECT = { 20, 20, 120, 40 }
    .new hBtn:HWND = CreateWindowEx(0, L"BUTTON", L"Tooltip Target",
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_BUTTON1, g_hInst, 0)

    ;; Create a tooltip
    ;; A tooltip control should not have the WS_CHILD style, nor should it
    ;; have an id, otherwise its behavior will be adversely affected.
    .new hTooltip:HWND = CreateWindowEx(0, TOOLTIPS_CLASS, L"", TTS_ALWAYSTIP,
        0, 0, 0, 0, hWnd, 0, g_hInst, 0)

    ;; Associate the tooltip with the button control
    .new ti:TOOLINFO = {0}
     mov ti.cbSize,sizeof(ti)
     mov ti.uFlags,TTF_IDISHWND or TTF_SUBCLASS
     mov ti.uId,hBtn
     mov ti.lpszText,&@CStr(L"This is a button.")
     mov ti.hwnd,hWnd
    SendMessage(hTooltip, TTM_ADDTOOL, 0, &ti)

   .return TRUE

OnInitTooltipDialog endp

;;
;;  FUNCTION: TooltipDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Tooltip control dialog.
;;
;;

TooltipDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitTooltipDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitTooltipDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

TooltipDlgProc endp


;; MSDN: IP Address Control
;; http://msdn.microsoft.com/en-us/library/bb761374.aspx

define IDC_IPADDRESS       10990

;;
;;   FUNCTION: OnInitIPAddressDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitIPAddressDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register IPAddress control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_INTERNET_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the IPAddress control
    .new rc:RECT = { 20, 20, 180, 24 }
    .new hIPAddress:HWND = CreateWindowEx(0, WC_IPADDRESS, 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_IPADDRESS, g_hInst, 0)

    .return TRUE

OnInitIPAddressDialog endp

;;
;;  FUNCTION: IPAddressDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the IPAddress control dialog.
;;
;;

IPAddressDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitIPAddressDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitIPAddressDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

IPAddressDlgProc endp


;; MSDN: Status Bar
;; http://msdn.microsoft.com/en-us/library/bb760726.aspx

define IDC_STATUSBAR       11990

;;
;;   FUNCTION: OnStatusbarSize(HWND, UINT, int, int)
;;
;;   PURPOSE: Process the WM_SIZE message
;;

OnStatusbarSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t

    ;; Get the Statusbar control handle which was previously stored in the
    ;; user data associated with the parent window.
    .new hStatusbar:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)

    ;; Partition the statusbar here to keep the ratio of the sizes of its
    ;; parts constant. Each part is set by specifing the coordinates of the
    ;; right edge of each part. -1 signifies the rightmost part of the parent.
    mov eax,x
    shr eax,1
    .new nHalf:int_t = eax
    .new nParts[4]:int_t = { eax, eax, eax, -1 }

    mov ecx,3
    xor edx,edx
    div ecx
    add nParts[4],eax
    mov eax,nHalf
    add eax,eax
    xor edx,edx
    div ecx
    add nParts[8],eax

    SendMessage(hStatusbar, SB_SETPARTS, 4, &nParts)

    ;; Resize statusbar so it's always same width as parent's client area
    SendMessage(hStatusbar, WM_SIZE, 0, 0)
    ret

OnStatusbarSize endp

;;
;;   FUNCTION: OnInitStatusbarDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitStatusbarDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register IPAddress control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_BAR_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the status bar control
    .new rc:RECT = { 0, 0, 0, 0 }
    .new hStatusbar:HWND = CreateWindowEx(0, STATUSCLASSNAME, 0,
        SBARS_SIZEGRIP or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_STATUSBAR, g_hInst, 0)

    ;; Store the statusbar control handle as the user data associated with
    ;; the parent window so that it can be retrieved for later use.
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hStatusbar)

    ;; Establish the number of partitions or 'parts' the status bar will
    ;; have, their actual dimensions will be set in the parent window's
    ;; WM_SIZE handler.
    GetClientRect(hWnd, &rc)

    mov eax,rc.right
    shr eax,1
    .new nHalf:int_t = eax
    .new nParts[4]:int_t = { eax, eax, eax, -1 }

    mov ecx,3
    xor edx,edx
    div ecx
    add nParts[4],eax
    mov eax,nHalf
    add eax,eax
    xor edx,edx
    div ecx
    add nParts[8],eax

    SendMessage(hStatusbar, SB_SETPARTS, 4, &nParts)

    ;; Put some texts into each part of the status bar and setup each part
    SendMessage(hStatusbar, SB_SETTEXT, 0, L"Status Bar: Part 1")
    SendMessage(hStatusbar, SB_SETTEXT, 1 or SBT_POPOUT, L"Part 2")
    SendMessage(hStatusbar, SB_SETTEXT, 2 or SBT_POPOUT, L"Part 3")
    SendMessage(hStatusbar, SB_SETTEXT, 3 or SBT_POPOUT, L"Part 4")

   .return TRUE

OnInitStatusbarDialog endp

;;
;;  FUNCTION: StatusbarDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Statusbar control dialog.
;;
;;

StatusbarDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitStatusbarDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitStatusbarDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

        ;; Handle the WM_SIZE message in OnStatusbarSize
        HANDLE_MSG (hWnd, WM_SIZE, OnStatusbarSize)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0
StatusbarDlgProc endp


;; MSDN: Progress Bar
;; http://msdn.microsoft.com/en-us/library/bb760818.aspx

define IDC_PROGRESSBAR     12990

;;
;;   FUNCTION: OnInitProgressDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitProgressDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Progress control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_PROGRESS_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the progress bar control
    .new rc:RECT = { 20, 20, 250, 20 }
    .new hProgress:HWND = CreateWindowEx(0, PROGRESS_CLASS, 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_PROGRESSBAR, g_hInst, 0)

    ;; Set the progress bar position to half-way
    SendMessage(hProgress, PBM_SETPOS, 50, 0)

   .return TRUE

OnInitProgressDialog endp

;;
;;  FUNCTION: ProgressDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Progress control dialog.
;;
;;

ProgressDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitProgressDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitProgressDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0
ProgressDlgProc endp


;; MSDN: Toolbar
;; http://msdn.microsoft.com/en-us/library/bb760435.aspx

define IDC_TOOLBAR         13990

;;
;;   FUNCTION: OnInitToolbarDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitToolbarDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Toolbar control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_BAR_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the Toolbar control
    .new rc:RECT = { 0, 0, 0, 0 }
    .new hToolbar:HWND = CreateWindowEx(0, TOOLBARCLASSNAME, 0,
        TBSTYLE_FLAT or CCS_ADJUSTABLE or CCS_NODIVIDER or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_TOOLBAR, g_hInst, 0)


    ;;
    ;; Setup and add buttons to Toolbar.
    ;;

    ;; If an application uses the CreateWindowEx function to create the
    ;; toolbar, the application must send this message to the toolbar before
    ;; sending the TB_ADDBITMAP or TB_ADDBUTTONS message. The CreateToolbarEx
    ;; function automatically sends TB_BUTTONSTRUCTSIZE, and the size of the
    ;; TBBUTTON structure is a parameter of the function.
    SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0)

    ;; Add images

    .new tbAddBmp:TBADDBITMAP = {0}
     mov tbAddBmp.hInst,HINST_COMMCTRL
     mov tbAddBmp.nID,IDB_STD_SMALL_COLOR

    SendMessage(hToolbar, TB_ADDBITMAP, 0, &tbAddBmp)

    ;; Add buttons

    define numButtons 7
    .new tbButtons[numButtons]:TBBUTTON = {
        { MAKELONG(STD_FILENEW, 0), NULL, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, L"New" },
        { MAKELONG(STD_FILEOPEN, 0), NULL, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, L"Open" },
        { MAKELONG(STD_FILESAVE, 0), NULL, 0, BTNS_AUTOSIZE, {0}, 0, L"Save" },
        { MAKELONG(0, 0), NULL, 0, TBSTYLE_SEP, {0}, 0, L"" }, ;; Separator
        { MAKELONG(STD_COPY, 0), NULL, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, L"Copy" },
        { MAKELONG(STD_CUT, 0), NULL, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, L"Cut" },
        { MAKELONG(STD_PASTE, 0), NULL, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, L"Paste" }
    }

    SendMessage(hToolbar, TB_ADDBUTTONS, numButtons, &tbButtons)

    ;; Tell the toolbar to resize itself, and show it.
    SendMessage(hToolbar, TB_AUTOSIZE, 0, 0)

   .return TRUE

OnInitToolbarDialog endp

;;
;;  FUNCTION: ToolbarDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Toolbar control dialog.
;;
;;

ToolbarDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitToolbarDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitToolbarDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0
ToolbarDlgProc endp


;; MSDN: Trackbar
;; http://msdn.microsoft.com/en-us/library/bb760145.aspx

define IDC_TRACKBAR            14990

;;
;;   FUNCTION: OnInitTrackbarDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitTrackbarDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Trackbar control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_WIN95_CLASSES ;; Or ICC_PROGRESS_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the Trackbar control
    .new rc:RECT = { 20, 20, 250, 20 }
    .new hTrackbar:HWND = CreateWindowEx(0, TRACKBAR_CLASS, 0,
        TBS_AUTOTICKS or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_TRACKBAR, g_hInst, 0)

    ;; Set Trackbar range
    SendMessage(hTrackbar, TBM_SETRANGE, 0, MAKELONG(0, 20))

   .return TRUE

OnInitTrackbarDialog endp

;;
;;  FUNCTION: TrackbarDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Trackbar control dialog.
;;
;;

TrackbarDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitTrackbarDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitTrackbarDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

TrackbarDlgProc endp


;; MSDN: SysLink
;; http://msdn.microsoft.com/en-us/library/bb760704.aspx

define IDC_SYSLINK         15990

;;
;;   FUNCTION: OnInitSysLinkDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitSysLinkDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register SysLink control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_LINK_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the SysLink control
    ;; The SysLink control supports the anchor tag(<a>) along with the
    ;; attributes HREF and ID.
    .new rc:RECT = { 20, 20, 500, 100 }
    .new hLink:HWND = CreateWindowEx(0, WC_LINK,
         L"All-In-One Code Framework\n"
         "<A HREF=\"http://cfx.codeplex.com\">Home</A> "
         "and <A ID=\"idBlog\">Blog</A>",
        WS_VISIBLE or WS_CHILD or WS_TABSTOP,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_SYSLINK, g_hInst, NULL)

   .return TRUE

OnInitSysLinkDialog endp

;;
;;   FUNCTION: OnSysLinkNotify(HWND, int, PNMLINK)
;;
;;   PURPOSE: Process the WM_NOTIFY message
;;

OnSysLinkNotify proc hWnd:HWND, idCtrl:int_t, pNMHdr:LPNMHDR

    .if (idCtrl != IDC_SYSLINK)  ;; Make sure that it is the SysLink control
        .return 0
    .endif

    ;; The notifications associated with SysLink controls are NM_CLICK
    ;; (syslink) and (for links that can be activated by the Enter key)
    ;; NM_RETURN.
    mov rcx,pNMHdr
    .switch ([rcx].NMHDR.code)

    .case NM_CLICK
    .case NM_RETURN

            .new pNMLink:PNMLINK = rcx
            .new item:LITEM = [rcx].NMLINK.item

            ;; Judging by the index of the link
            .if (item.iLink == 0) ;; If it is the first link

                ShellExecute(NULL, L"open", &item.szUrl, NULL, NULL, SW_SHOW)

            ;; Judging by the ID of the link
            .elseif (wcscmp(&item.szID, L"idBlog") == 0)

                MessageBox(hWnd, L"http://blogs.msdn.com/codefx", L"All-In-One Code Framework Blog", MB_OK)
            .endif
            .endc

    .endsw
    .return 0

OnSysLinkNotify endp

;;
;;  FUNCTION: SysLinkDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the SysLink control dialog.
;;
;;

SysLinkDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitSysLinkDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitSysLinkDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

        ;; Handle the WM_NOTIFY message in OnNotify
        HANDLE_MSG (hWnd, WM_NOTIFY, OnSysLinkNotify)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

SysLinkDlgProc endp

;; MSDN: Rebar
;; http://msdn.microsoft.com/en-us/library/bb774375.aspx

define IDC_REBAR           16990

;;
;;   FUNCTION: OnInitRebarDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message
;;

OnInitRebarDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM

    ;; Load and register Rebar control class
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_COOL_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif

    ;; Create the Rebar control
    .new rc:RECT = { 0, 0, 0, 0 }
    .new hRebar:HWND = CreateWindowEx(0, REBARCLASSNAME, L"",
        WS_VISIBLE or WS_CHILD or RBS_AUTOSIZE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_REBAR, g_hInst, NULL)

    .new ri:REBARINFO = {0}
    mov ri.cbSize,sizeof(REBARINFO)
    SendMessage(hRebar, RB_SETBARINFO, 0, &ri)

    ;; Insert a image
    .new hImg:HICON = LoadImage(0, IDI_QUESTION, IMAGE_ICON, 0, 0, LR_SHARED)
    .new hwndImg:HWND = CreateWindow(L"STATIC", NULL,
        WS_CHILD or WS_VISIBLE or SS_ICON or SS_REALSIZEIMAGE or SS_NOTIFY,
        0, 0, 0, 0, hRebar, NULL, g_hInst,   NULL)

    ;; Set static control image
    SendMessage(hwndImg, STM_SETICON, hImg, NULL)

   .new rbBand:REBARBANDINFO
    mov rbBand.cbSize,sizeof(REBARBANDINFO)
    mov rbBand.fMask,RBBIM_STYLE or RBBIM_CHILDSIZE or RBBIM_CHILD or RBBIM_SIZE
    mov rbBand.fStyle,RBBS_CHILDEDGE or RBBS_NOGRIPPER
    mov rbBand.hwndChild,hwndImg
    mov rbBand.cxMinChild,0
    mov rbBand.cyMinChild,20
    mov rbBand._cx,20

    ;; Insert the img into the rebar
    SendMessage(hRebar, RB_INSERTBAND, -1, &rbBand)

    ;; Insert a blank band
    mov rbBand.cbSize,sizeof(REBARBANDINFO)
    mov rbBand.fMask,RBBIM_STYLE or RBBIM_SIZE
    mov rbBand.fStyle,RBBS_CHILDEDGE or RBBS_HIDETITLE or RBBS_NOGRIPPER
    mov rbBand._cx,1

    ;; Insert the blank band into the rebar
    SendMessage(hRebar, RB_INSERTBAND, -1, &rbBand)
   .return TRUE

OnInitRebarDialog endp

;;
;;  FUNCTION: RebarDlgProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the Rebar control dialog.
;;
;;

RebarDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_INITDIALOG message in OnInitRebarDialog
        HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitRebarDialog)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE ;; Let system deal with msg
    .endsw
    .return 0

RebarDlgProc endp

;;
;;   FUNCTION: OnInitDialog(HWND, HWND, LPARAM)
;;
;;   PURPOSE: Process the WM_INITDIALOG message.
;;

OnInitDialog proc hWnd:HWND, hwndFocus:HWND, lParam:LPARAM

    .return TRUE

OnInitDialog endp


;;
;;   FUNCTION: OnCommand(HWND, int, HWND, UINT)
;;
;;   PURPOSE: Process the WM_COMMAND message
;;

OnCommand proc hWnd:HWND, id:int_t, hWndCtl:HWND, codeNotify:UINT

    .switch (id)

    .case IDC_BUTTON_ANIMATION

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_ANIMATIONDIALOG), hWnd, &AnimationDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_COMBOBOXEX

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_COMBOBOXEXDIALOG), hWnd, &ComboBoxExDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_DATETIMEPICK

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DATETIMEPICKDIALOG), hWnd, &DateTimePickDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW);
        .endif
        .endc

    .case IDC_BUTTON_HEADER:

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_HEADERDIALOG), hWnd, &HeaderDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_IPADDRESS

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_IPADDRESSDIALOG), hWnd, &IPAddressDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_LISTVIEW

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_LISTVIEWDIALOG), hWnd, &ListviewDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW);
        .endif
        .endc

    .case IDC_BUTTON_MONTHCAL

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_MONTHCALDIALOG), hWnd, &MonthCalDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_PROGRESS

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_PROGRESSDIALOG), hWnd, &ProgressDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_SYSLINK

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SYSLINKDIALOG), hWnd, &SysLinkDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW);
        .endif
        .endc

    .case IDC_BUTTON_STATUS

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_STATUSDIALOG), hWnd, &StatusbarDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_TABCONTROL

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_TABCONTROLDIALOG), hWnd, &TabControlDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW);
        .endif
        .endc

    .case IDC_BUTTON_TOOLBAR

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_TOOLBARDIALOG), hWnd, &ToolbarDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_TOOLTIP

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_TOOLTIPDIALOG), hWnd, &TooltipDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW);
        .endif
        .endc

    .case IDC_BUTTON_TRACKBAR

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_TRACKBARDIALOG), hWnd, &TrackbarDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDC_BUTTON_TREEVIEW

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_TREEVIEWDIALOG), hWnd, &TreeviewDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW);
        .endif
        .endc

    .case IDC_BUTTON_UPDOWN

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_UPDOWNDIALOG), hWnd, &UpdownDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW);
        .endif
        .endc

    .case IDC_BUTTON_REBAR

        .new hDlg:HWND = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_REBARDIALOG), hWnd, &RebarDlgProc)
        .if (hDlg)
            ShowWindow(hDlg, SW_SHOW)
        .endif
        .endc

    .case IDOK
    .case IDCANCEL
        EndDialog(hWnd, 0)
        .endc
    .endsw
    ret

OnCommand endp


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

wWinMain proc hInstance:     HINSTANCE,
              hPrevInstance: HINSTANCE,
              lpCmdLine:     LPWSTR,
              nCmdShow:      int_t

    mov g_hInst,hInstance
   .return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, &DialogProc)
wWinMain endp

    end

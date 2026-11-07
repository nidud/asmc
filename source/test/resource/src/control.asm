include stdio.inc
include windows.inc
include windowsx.inc
include assert.inc
include commctrl.inc
include tchar.inc

ifdef _M_IX86
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_IA64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_X64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
else
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
endif

include res/control.inc

.data
 g_hInst HINSTANCE 0

.code

OnClose proc hWnd:HWND
    EndDialog(ldr(hWnd), 0)
    ret
    endp

OnInitAnimationDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX = { sizeof(iccx) }
    mov iccx.dwICC,ICC_ANIMATE_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 280, 60 }
    .new hAnimate:HWND = CreateWindowEx(0, ANIMATE_CLASS, 0,
            ACS_TIMER or ACS_AUTOPLAY or ACS_TRANSPARENT or WS_CHILD or WS_VISIBLE,
            rc.left, rc.top, rc.right, rc.bottom,
            hWnd, IDC_ANIMATION, g_hInst, 0)
    .if (hAnimate == NULL)
        .return FALSE
    .endif
    .if ( SendMessage(hAnimate, ACM_OPEN, 0, MAKEINTRESOURCE(IDR_UPLOAD_AVI)) == 0 )
        .return FALSE
    .endif
    .if ( SendMessage(hAnimate, ACM_PLAY, -1, MAKELONG(0, -1)) == 0 )
        .return FALSE
    .endif
    .return TRUE
    endp

AnimationDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitAnimationDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitComboBoxExDialog proc uses rbx hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX = { sizeof(iccx) }
     mov iccx.dwICC,ICC_USEREX_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 280, 100 }
    .new hComboEx:HWND = CreateWindowEx(0, WC_COMBOBOXEX, 0, CBS_DROPDOWN or WS_CHILD or WS_VISIBLE,
            rc.left, rc.top, rc.right, rc.bottom, hWnd, IDC_COMBOBOXEX, g_hInst, 0)
    .if (hComboEx == NULL)
        .return FALSE
    .endif
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
    SendMessage(hComboEx, CBEM_SETIMAGELIST, 0, hImageList)
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
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hImageList)
    .return TRUE
    endp

OnComboBoxExClose proc hWnd:HWND
    ImageList_Destroy(GetWindowLongPtr(hWnd, GWLP_USERDATA))
    DestroyWindow(hWnd)
    ret
    endp

ComboBoxExDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitComboBoxExDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnComboBoxExClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitUpdownDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
   .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_UPDOWN_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 100, 24 }
    .new hEdit:HWND = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_EDIT, g_hInst, 0)
    SetRect(&rc, 20, 60, 180, 20)
    .new hUpdown:HWND = CreateWindowEx(0, UPDOWN_CLASS, 0,
        UDS_ALIGNRIGHT or UDS_SETBUDDYINT or UDS_WRAP or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_UPDOWN, g_hInst, 0)
    SendMessage(hUpdown, UDM_SETBUDDY, hEdit, 0)
    .return TRUE
    endp

UpdownDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitUpdownDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnHeaderSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t
    .new rc:RECT = { 0, 0, x, y }
    .new wp:WINDOWPOS = { 0 }
    .new hdl:HDLAYOUT = { &rc, &wp }
    .new hHeader:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)
    SendMessage(hHeader, HDM_LAYOUT, 0, &hdl)
    add wp.cy,8
    SetWindowPos(hHeader, wp.hwndInsertAfter, wp.x, wp.y, wp._cx, wp.cy, wp.flags)
    ret
    endp

OnInitHeaderDialog proc uses rbx hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
   .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_WIN95_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 0, 0, 0, 0 }
    .new hHeader:HWND = CreateWindowEx(0, WC_HEADER, 0,
        HDS_BUTTONS or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_HEADER, g_hInst, 0)
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hHeader)
    GetClientRect(hWnd, &rc)
    OnHeaderSize(hWnd, 0, rc.right, rc.bottom)
    SendMessage(hHeader, WM_SETFONT, GetStockObject(DEFAULT_GUI_FONT), 0)
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
    endp

HeaderDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitHeaderDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
     HANDLE_MSG (hWnd, WM_SIZE, OnHeaderSize)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitMonthCalDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
   .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_DATE_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 280, 200 }
    .new hMonthCal:HWND = CreateWindowEx(0, MONTHCAL_CLASS, 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_MONTHCAL, g_hInst, 0)
    .return TRUE
    endp

MonthCalDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitMonthCalDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitDateTimePickDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
   .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_DATE_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 150, 30 }
    .new hDateTimePick:HWND = CreateWindowEx(0, DATETIMEPICK_CLASS, 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_DATETIMEPICK, g_hInst, 0)
    .return TRUE
    endp

DateTimePickDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
      HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitDateTimePickDialog)
      HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

.template LVHandles
    hListview HWND ?
    hLargeIcons HIMAGELIST ?
    hSmallIcons HIMAGELIST ?
   .ends

OnListviewSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t
   .new lvh:ptr LVHandles = GetWindowLongPtr(hWnd, GWLP_USERDATA)
    mov rcx,lvh
    MoveWindow([rcx].LVHandles.hListview, 0, 0, x, y, 1)
    mov rcx,lvh
    SendMessage([rcx].LVHandles.hListview, LVM_ARRANGE, LVA_ALIGNTOP, 0)
    ret
    endp

OnInitListviewDialog proc uses rsi rdi rbx hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
   .new iccx:INITCOMMONCONTROLSEX
    mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
    mov iccx.dwICC,ICC_LISTVIEW_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    mov rsi,malloc(LVHandles)
    SetWindowLongPtr(hWnd, GWLP_USERDATA, rsi)
   .new rc:RECT
    GetClientRect(hWnd, &rc)
    mov [rsi].LVHandles.hListview,CreateWindowEx(0, WC_LISTVIEW, 0,
        LVS_ICON or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_LISTVIEW, g_hInst, 0)
    .new lx:int_t = GetSystemMetrics(SM_CXICON)
    .new ly:int_t = GetSystemMetrics(SM_CYICON)
     mov [rsi].LVHandles.hLargeIcons,ImageList_Create(lx, ly, ILC_COLOR32 or ILC_MASK, 1, 1)
    .new sx:int_t = GetSystemMetrics(SM_CXSMICON)
    .new sy:int_t = GetSystemMetrics(SM_CYSMICON)
     mov [rsi].LVHandles.hSmallIcons,ImageList_Create(sx, sy, ILC_COLOR32 or ILC_MASK, 1, 1)
    .new hLargeIcon:HICON
    .new hSmallIcon:HICON
    .for ( ebx = IDI_ICON1 : ebx <= IDI_ICON10 : ebx++ )
        mov hLargeIcon,LoadImage(g_hInst, MAKEINTRESOURCE(rbx), IMAGE_ICON, lx, ly, 0)
        ImageList_AddIcon([rsi].LVHandles.hLargeIcons, hLargeIcon)
        DestroyIcon(hLargeIcon)
        mov hSmallIcon,LoadImage(g_hInst, MAKEINTRESOURCE(rbx), IMAGE_ICON, sx, sy, 0)
        ImageList_AddIcon([rsi].LVHandles.hSmallIcons, hSmallIcon)
        DestroyIcon(hSmallIcon)
    .endf
    ListView_SetImageList([rsi].LVHandles.hListview, [rsi].LVHandles.hLargeIcons, LVSIL_NORMAL)
    ListView_SetImageList([rsi].LVHandles.hListview, [rsi].LVHandles.hSmallIcons, LVSIL_SMALL)
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
    endp

OnListviewClose proc uses rsi hWnd:HWND
    mov rsi,GetWindowLongPtr(hWnd, GWLP_USERDATA)
    ImageList_Destroy([rsi].LVHandles.hLargeIcons)
    ImageList_Destroy([rsi].LVHandles.hSmallIcons)
    free(rsi)
    DestroyWindow(hWnd)
    ret
    endp

ListviewDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitListviewDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnListviewClose)
     HANDLE_MSG (hWnd, WM_SIZE, OnListviewSize)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnTreeviewSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t
   .new hTreeview:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)
    MoveWindow(hTreeview, 0, 0, x, y, TRUE)
    ret
    endp

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
    endp

OnInitTreeviewDialog proc uses rbx hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_TREEVIEW_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT
     GetClientRect(hWnd, &rc)
    .new hTreeview:HWND = CreateWindowEx(0, WC_TREEVIEW, 0,
        TVS_HASLINES or TVS_LINESATROOT or TVS_HASBUTTONS or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_TREEVIEW, g_hInst, 0)
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hTreeview)
    .new x:int_t = GetSystemMetrics(SM_CXSMICON)
    .new y:int_t = GetSystemMetrics(SM_CYSMICON)
    .new hImages:HIMAGELIST = ImageList_Create(x, y, ILC_COLOR32 or ILC_MASK, 1, 1)
    .new hLib:HINSTANCE = LoadLibrary(L"shell32.dll")
    .if (hLib)
        .for (ebx = 4: ebx < 6: ebx++)
           .new hIcon:HICON = LoadImage(hLib, MAKEINTRESOURCE(rbx), IMAGE_ICON, 0, 0, LR_SHARED)
            ImageList_AddIcon(hImages, hIcon)
        .endf
        FreeLibrary(hLib)
        mov hLib,NULL
    .endif
    TreeView_SetImageList(hTreeview, hImages, TVSIL_NORMAL)
    .new hPrev:HTREEITEM = InsertTreeviewItem(hTreeview, L"First", TVI_ROOT)
     mov hPrev,InsertTreeviewItem(hTreeview, L"Level01", hPrev)
     mov hPrev,InsertTreeviewItem(hTreeview, L"Level02", hPrev)
     mov hPrev,InsertTreeviewItem(hTreeview, L"Second", TVI_ROOT)
     mov hPrev,InsertTreeviewItem(hTreeview, L"Third", TVI_ROOT)
    .return TRUE
    endp

OnTreeviewClose proc hWnd:HWND
   .new hTreeview:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)
   .new hImages:HIMAGELIST = TreeView_GetImageList(hTreeview, TVSIL_NORMAL)
    ImageList_Destroy(hImages)
    DestroyWindow(hWnd)
    ret
    endp

TreeviewDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitTreeviewDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnTreeviewClose)
     HANDLE_MSG (hWnd, WM_SIZE, OnTreeviewSize)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnTabSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t
   .new hTab:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)
    sub x,4
    sub y,4
    MoveWindow(hTab, 2, 2, x, y, TRUE)
    ret
    endp

InsertTabItem proc hTab:HWND, pszText:LPTSTR, iid:int_t
    .new ti:TCITEM = {0}
     mov ti.mask,TCIF_TEXT
     mov ti.pszText,pszText
     mov ti.cchTextMax,wcslen(pszText)
    .return SendMessage(hTab, TCM_INSERTITEM, iid, &ti)
    endp

OnInitTabControlDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_TAB_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
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
    SendMessage(hTab, WM_SETFONT, GetStockObject(DEFAULT_GUI_FONT), 0)
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hTab)
    InsertTabItem(hTab, L"First Page", 0)
    InsertTabItem(hTab, L"Second Page", 1)
    InsertTabItem(hTab, L"Third Page", 2)
    InsertTabItem(hTab, L"Fourth Page", 3)
    InsertTabItem(hTab, L"Fifth Page", 4)
    .return TRUE
    endp

TabControlDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitTabControlDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
     HANDLE_MSG (hWnd, WM_SIZE, OnTabSize)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitTooltipDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_WIN95_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 120, 40 }
    .new hBtn:HWND = CreateWindowEx(0, L"BUTTON", L"Tooltip Target",
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_BUTTON1, g_hInst, 0)
    .new hTooltip:HWND = CreateWindowEx(0, TOOLTIPS_CLASS, L"", TTS_ALWAYSTIP,
        0, 0, 0, 0, hWnd, 0, g_hInst, 0)
    .new ti:TOOLINFO = {0}
     mov ti.cbSize,sizeof(ti)
     mov ti.uFlags,TTF_IDISHWND or TTF_SUBCLASS
     mov ti.uId,hBtn
     mov ti.lpszText,&@CStr(L"This is a button.")
     mov ti.hwnd,hWnd
    SendMessage(hTooltip, TTM_ADDTOOL, 0, &ti)
    .return TRUE
    endp

TooltipDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitTooltipDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitIPAddressDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_INTERNET_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 180, 24 }
    .new hIPAddress:HWND = CreateWindowEx(0, WC_IPADDRESS, 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_IPADDRESS, g_hInst, 0)
    .return TRUE
    endp

IPAddressDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitIPAddressDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnStatusbarSize proc hWnd:HWND, state:UINT, x:int_t, y:int_t
   .new hStatusbar:HWND = GetWindowLongPtr(hWnd, GWLP_USERDATA)
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
    SendMessage(hStatusbar, WM_SIZE, 0, 0)
    ret
    endp

OnInitStatusbarDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_BAR_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 0, 0, 0, 0 }
    .new hStatusbar:HWND = CreateWindowEx(0, STATUSCLASSNAME, 0,
        SBARS_SIZEGRIP or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_STATUSBAR, g_hInst, 0)
    SetWindowLongPtr(hWnd, GWLP_USERDATA, hStatusbar)
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
    SendMessage(hStatusbar, SB_SETTEXT, 0, L"Status Bar: Part 1")
    SendMessage(hStatusbar, SB_SETTEXT, 1 or SBT_POPOUT, L"Part 2")
    SendMessage(hStatusbar, SB_SETTEXT, 2 or SBT_POPOUT, L"Part 3")
    SendMessage(hStatusbar, SB_SETTEXT, 3 or SBT_POPOUT, L"Part 4")
    .return TRUE
    endp

StatusbarDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitStatusbarDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
     HANDLE_MSG (hWnd, WM_SIZE, OnStatusbarSize)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitProgressDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_PROGRESS_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 250, 20 }
    .new hProgress:HWND = CreateWindowEx(0, PROGRESS_CLASS, 0,
        WS_CHILD or WS_VISIBLE, rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_PROGRESSBAR, g_hInst, 0)
    SendMessage(hProgress, PBM_SETPOS, 50, 0)
    .return TRUE
    endp

ProgressDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitProgressDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitToolbarDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_BAR_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 0, 0, 0, 0 }
    .new hToolbar:HWND = CreateWindowEx(0, TOOLBARCLASSNAME, 0,
        TBSTYLE_FLAT or CCS_ADJUSTABLE or CCS_NODIVIDER or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_TOOLBAR, g_hInst, 0)
    SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0)
    .new tbAddBmp:TBADDBITMAP = {0}
     mov tbAddBmp.hInst,HINST_COMMCTRL
     mov tbAddBmp.nID,IDB_STD_SMALL_COLOR
    SendMessage(hToolbar, TB_ADDBITMAP, 0, &tbAddBmp)
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
    SendMessage(hToolbar, TB_AUTOSIZE, 0, 0)
    .return TRUE
    endp

ToolbarDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitToolbarDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitTrackbarDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_WIN95_CLASSES ;; Or ICC_PROGRESS_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 250, 20 }
    .new hTrackbar:HWND = CreateWindowEx(0, TRACKBAR_CLASS, 0,
        TBS_AUTOTICKS or WS_CHILD or WS_VISIBLE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_TRACKBAR, g_hInst, 0)
    SendMessage(hTrackbar, TBM_SETRANGE, 0, MAKELONG(0, 20))
    .return TRUE
    endp

TrackbarDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitTrackbarDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitSysLinkDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_LINK_CLASS
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 20, 20, 500, 100 }
    .new hLink:HWND = CreateWindowEx(0, WC_LINK,
         L"All-In-One Code Framework\n"
         "<A HREF=\"http://cfx.codeplex.com\">Home</A> "
         "and <A ID=\"idBlog\">Blog</A>",
        WS_VISIBLE or WS_CHILD or WS_TABSTOP,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_SYSLINK, g_hInst, NULL)
    .return TRUE
    endp

OnSysLinkNotify proc hWnd:HWND, idCtrl:int_t, pNMHdr:LPNMHDR
    .if (idCtrl != IDC_SYSLINK)
        .return 0
    .endif
    mov rcx,pNMHdr
    .switch ([rcx].NMHDR.code)
    .case NM_CLICK
    .case NM_RETURN
       .new pNMLink:PNMLINK = rcx
       .new item:LITEM = [rcx].NMLINK.item
        .if (item.iLink == 0)
            ShellExecute(NULL, L"open", &item.szUrl, NULL, NULL, SW_SHOW)
        .elseif (wcscmp(&item.szID, L"idBlog") == 0)
            MessageBox(hWnd, L"http://blogs.msdn.com/codefx", L"All-In-One Code Framework Blog", MB_OK)
        .endif
        .endc
    .endsw
    .return 0
    endp

SysLinkDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitSysLinkDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
     HANDLE_MSG (hWnd, WM_NOTIFY, OnSysLinkNotify)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitRebarDialog proc hWnd:HWND, hWndFocus:HWND, lParam:LPARAM
    .new iccx:INITCOMMONCONTROLSEX
     mov iccx.dwSize,sizeof(INITCOMMONCONTROLSEX)
     mov iccx.dwICC,ICC_COOL_CLASSES
    .if (!InitCommonControlsEx(&iccx))
        .return FALSE
    .endif
    .new rc:RECT = { 0, 0, 0, 0 }
    .new hRebar:HWND = CreateWindowEx(0, REBARCLASSNAME, L"",
        WS_VISIBLE or WS_CHILD or RBS_AUTOSIZE,
        rc.left, rc.top, rc.right, rc.bottom,
        hWnd, IDC_REBAR, g_hInst, NULL)
    .new ri:REBARINFO = {0}
    mov ri.cbSize,sizeof(REBARINFO)
    SendMessage(hRebar, RB_SETBARINFO, 0, &ri)
    .new hImg:HICON = LoadImage(0, IDI_QUESTION, IMAGE_ICON, 0, 0, LR_SHARED)
    .new hwndImg:HWND = CreateWindow(L"STATIC", NULL,
        WS_CHILD or WS_VISIBLE or SS_ICON or SS_REALSIZEIMAGE or SS_NOTIFY,
        0, 0, 0, 0, hRebar, NULL, g_hInst,   NULL)
    SendMessage(hwndImg, STM_SETICON, hImg, NULL)
   .new rbBand:REBARBANDINFO
    mov rbBand.cbSize,sizeof(REBARBANDINFO)
    mov rbBand.fMask,RBBIM_STYLE or RBBIM_CHILDSIZE or RBBIM_CHILD or RBBIM_SIZE
    mov rbBand.fStyle,RBBS_CHILDEDGE or RBBS_NOGRIPPER
    mov rbBand.hwndChild,hwndImg
    mov rbBand.cxMinChild,0
    mov rbBand.cyMinChild,20
    mov rbBand._cx,20
    SendMessage(hRebar, RB_INSERTBAND, -1, &rbBand)
    mov rbBand.cbSize,sizeof(REBARBANDINFO)
    mov rbBand.fMask,RBBIM_STYLE or RBBIM_SIZE
    mov rbBand.fStyle,RBBS_CHILDEDGE or RBBS_HIDETITLE or RBBS_NOGRIPPER
    mov rbBand._cx,1
    SendMessage(hRebar, RB_INSERTBAND, -1, &rbBand)
    .return TRUE
    endp

RebarDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitRebarDialog)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

OnInitDialog proc hWnd:HWND, hwndFocus:HWND, lParam:LPARAM
    .return TRUE
    endp

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
    endp

DialogProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
     HANDLE_MSG (hWnd, WM_INITDIALOG, OnInitDialog)
     HANDLE_MSG (hWnd, WM_COMMAND, OnCommand)
     HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .default
        .return FALSE
    .endsw
    .return 0
    endp

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:int_t
    mov g_hInst,hInstance
    .return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, &DialogProc)
    endp

    end _tstart

include windows.inc
include richedit.inc
include richole.inc
include winres.inc
include tchar.inc

option dllimport:none

CDataObjectCreate proto :ptr ptr CDataObject, :uint_t

IDM_INSOBJ      equ 1
IDM_SAVE        equ 2
IDM_EXIT        equ 3
IDR_MAINMENU    equ 100
IDR_BITMAP1     equ 101

.comdef CDataObject

    m_cRefCount     dd ?
    m_FormatEtc     FORMATETC <>
    m_StgMedium     STGMEDIUM <>
    m_cDataCount    dd ?

    QueryInterface  proc :REFIID, :ptr
    AddRef          proc
    Release         proc
    GetData         proc :ptr FORMATETC, :ptr STGMEDIUM
    GetDataHere     proc :ptr, :ptr
    QueryGetData    proc :ptr
    GetCanonicalFormatEtc proc :ptr, :ptr
    SetData         proc :ptr, :ptr, :BOOL
    EnumFormatEtc   proc :dword, :ptr ptr
    DAdvise         proc :ptr, :dword, :ptr, :ptr
    DUnadvise       proc :dword
    EnumDAdvise     proc :ptr ptr
    .ends

    .data
    hEdit           HWND 0
    hInstance       HINSTANCE 0
    OldWndProc      LONG_PTR 0
    hBitmap1        HBITMAP 0
ifdef __PE__
    IID_IOleObject  IID _IID_IOleObject
endif

    .code

SetColor proc

  local cfm:CHARFORMAT2, md:int_t

    mov md,SendMessage(hEdit, EM_GETMODIFY, 0, 0)
    mov cfm.cbSize,sizeof(cfm)
    mov cfm.crTextColor,RGB(192,192,192)
    mov cfm.dwMask,CFM_COLOR
    SendMessage(hEdit, EM_SETCHARFORMAT, SCF_ALL, &cfm)
    SendMessage(hEdit, EM_SETBKGNDCOLOR, 0, 0)
    SendMessage(hEdit, EM_SETMODIFY, md, 0)
    ret

SetColor endp

RESaveCallback proc dwCookie:DWORD_PTR, lpBuff:LPBYTE, cb:LONG, pcb:PLONG

    .return 0 .if WriteFile(rcx, rdx, r8d, r9, NULL)
    dec eax
    ret

RESaveCallback endp

SaveFile proc hwnd:HWND, lpszFileName:ptr TCHAR

  local ed:EDITSTREAM, hFile:HANDLE, fSuccess:BOOL

    mov fSuccess,FALSE

    .if CreateFile(lpszFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
            FILE_FLAG_SEQUENTIAL_SCAN, NULL) != INVALID_HANDLE_VALUE

        mov hFile,rax
        mov ed.dwCookie,rax
        mov ed.dwError,0
        lea rax,RESaveCallback
        mov ed.pfnCallback,rax
        .if SendMessage(hwnd, EM_STREAMOUT, SF_RTF, &ed) && ed.dwError == 0
            mov fSuccess,TRUE
        .endif
        CloseHandle(hFile)
    .endif
    mov eax,fSuccess
    ret

SaveFile endp

InsertBitmap proc hRichEdit:HWND, hBitmap:HBITMAP, nPosition:DWORD

  local hr              :HRESULT
  local stgm            :STGMEDIUM
  local fm              :FORMATETC
  local pRichEditOle    :LPRICHEDITOLE
  local pDataObject     :LPDATAOBJECT
  local pOleClientSite  :LPOLECLIENTSITE
  local pLockBytes      :LPLOCKBYTES
  local pStorage        :ptr IStorage
  local pOleObject      :ptr IOleObject
  local clsid           :CLSID
  local reobject        :REOBJECT

    mov stgm.tymed,TYMED_GDI
    mov stgm.u.hBitmap,rdx
    mov stgm.pUnkForRelease,NULL

    mov fm.cfFormat,CF_BITMAP
    mov fm.ptd,NULL
    mov fm.dwAspect,DVASPECT_CONTENT
    mov fm.lindex,-1
    mov fm.tymed,TYMED_GDI

    SendMessage(hRichEdit, EM_GETOLEINTERFACE, 0, &pRichEditOle)
    .return 1 .if (pRichEditOle == NULL)
    CDataObjectCreate(&pDataObject, @ReservedStack)
    pDataObject.SetData(&fm, &stgm, TRUE)
    .return 3 .if pRichEditOle.GetClientSite(&pOleClientSite)

    mov pLockBytes,rax
    mov pStorage,rax
    mov pOleObject,rax

    .ifd !CreateILockBytesOnHGlobal(NULL, TRUE, &pLockBytes) && pLockBytes

        .ifd !StgCreateDocfileOnILockBytes(pLockBytes, STGM_SHARE_EXCLUSIVE or STGM_CREATE or STGM_READWRITE, 0, &pStorage) && pStorage

            .ifd !OleCreateStaticFromData(pDataObject, &IID_IOleObject, OLERENDER_FORMAT, &fm, pOleClientSite, pStorage, &pOleObject) && pOleObject

                .ifd !pOleObject.GetUserClassID(&reobject.clsid)

                    mov reobject.cbStruct,REOBJECT
                    mov reobject.cp,nPosition
                    mov reobject.dvaspect,DVASPECT_CONTENT
                    mov reobject.poleobj,pOleObject
                    mov reobject.polesite,pOleClientSite
                    mov reobject.pstg,pStorage

                    pRichEditOle.InsertObject(&reobject)
                .endif
                pOleObject.Release()
            .endif
            pStorage.Release()
        .endif
        pLockBytes.Release()
    .endif
    pOleClientSite.Release()
    xor eax,eax
    ret

InsertBitmap endp

RichEditProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

  local result:int_t

    .switch uMsg
    .case WM_COMMAND
        .if !lParam
            movzx eax,word ptr wParam
            .switch eax
              .case IDM_EXIT
                SendMessage(hWnd, WM_CLOSE, 0, 0)
                .endc
              .case IDM_INSOBJ
                ;int 3
                InsertBitmap(hEdit, hBitmap1, REO_CP_SELECTION)
            .endsw
        .endif
        xor eax,eax
        .endc
    .case WM_PAINT
        HideCaret(hWnd)
        CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam)
        mov result,eax
        ShowCaret(hWnd)
        mov eax,result
        .endc
    .case WM_CLOSE
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, OldWndProc)
        .endc
    .default
        CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam)
    .endsw
    ret

RichEditProc endp

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch message

    .case WM_CREATE
        .if !LoadLibrary("Msftedit.dll")
            PostQuitMessage(1)
            xor eax,eax
            .endc
        .endif
        mov hEdit,CreateWindowEx(WS_EX_CLIENTEDGE, MSFTEDIT_CLASS, 0,
                ES_MULTILINE or WS_VISIBLE or WS_CHILD or WS_BORDER or WS_VSCROLL or WS_HSCROLL or ES_NOHIDESEL,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                hWnd, 0, hInstance, NULL)
        mov OldWndProc,SetWindowLongPtr(hEdit, GWLP_WNDPROC, &RichEditProc)
        SendMessage(hEdit, EM_LIMITTEXT, -1, 0)
        SetColor()
        SetFocus(hEdit)
        mov hBitmap1,LoadBitmap(hInstance, IDR_BITMAP1)
        xor eax,eax
        .endc

    .case WM_COMMAND
        .if !lParam
            movzx eax,word ptr wParam
            .switch eax
              .case IDM_EXIT
                SendMessage(hWnd, WM_CLOSE, 0, 0)
                .endc
              .case IDM_INSOBJ
                SendMessage(hEdit, WM_COMMAND, IDM_INSOBJ, 0)
                .endc
              .case IDM_SAVE
                SaveFile(hEdit, "saved.rtf")
                .endc
            .endsw
        .endif
        xor eax,eax
        .endc
    .case WM_SIZE
        mov rax,lParam
        mov edx,eax
        and eax,0xFFFF
        shr edx,16
        MoveWindow(hEdit, 0, 0, eax, edx, TRUE)
        .endc
    .case WM_DESTROY
        PostQuitMessage(0)
        xor eax,eax
        .endc
    .default
        DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    ret

WndProc endp

_tWinMain proc WINAPI hInst:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,     &WndProc
    mov wc.cbClsExtra,      0
    mov wc.cbWndExtra,      0
    mov wc.hInstance,       hInst
    mov hInstance,          hInst
    mov wc.hbrBackground,   COLOR_WINDOW+1
    mov wc.lpszMenuName,    IDR_MAINMENU
    mov wc.lpszClassName,   &@CStr("WndClass")
    mov wc.hIcon,           LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,         rax
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)
    RegisterClassEx(&wc)

    mov ecx,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0, "WndClass", "Window", WS_OVERLAPPEDWINDOW,
                            ecx, ecx, ecx, ecx, 0, 0, hInstance, 0)
    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)
    InsertBitmap(hEdit, hBitmap1, REO_CP_SELECTION)

    .while GetMessage(&msg, 0, 0, 0)
        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    mov rax,msg.wParam
    ret

_tWinMain endp

    assume rcx:ptr CDataObject

CDataObject::GetData proc pformatetcIn:ptr FORMATETC, pmedium:ptr STGMEDIUM

    .return E_HANDLE .if !OleDuplicateData([rcx].m_StgMedium.u.hBitmap, CF_BITMAP, 0)

    mov rdx,pmedium
    mov [rdx].STGMEDIUM.tymed,TYMED_GDI
    mov [rdx].STGMEDIUM.u.hBitmap,rax
    xor eax,eax
    mov [rdx].STGMEDIUM.pUnkForRelease,rax
    ret

CDataObject::GetData endp

    option win64:rsp nosave noauto

CDataObject::SetData proc uses rsi rdi pformatetc:ptr, pmedium:ptr, fRelease:BOOL

    mov rsi,rdx
    lea rdi,[rcx].m_FormatEtc
    mov ecx,FORMATETC
    rep movsb
    mov rsi,r8
    mov ecx,STGMEDIUM
    rep movsb
    mov eax,S_OK
    ret

CDataObject::SetData endp

CDataObject::Release proc
CDataObject::Release endp
CDataObject::QueryInterface proc riid:LPIID, ppvObj:ptr
CDataObject::QueryInterface endp
CDataObject::AddRef proc
CDataObject::AddRef endp
CDataObject::GetDataHere proc pFE:ptr, pSM:ptr
CDataObject::GetDataHere endp
CDataObject::QueryGetData proc pFE:ptr
CDataObject::QueryGetData endp
CDataObject::GetCanonicalFormatEtc proc pformatectIn:ptr, pformatetcOut:ptr
CDataObject::GetCanonicalFormatEtc endp
CDataObject::EnumFormatEtc proc dwDir:dword, ppEnum:ptr ptr
CDataObject::EnumFormatEtc endp
CDataObject::DAdvise proc pformatetc:ptr, advf:dword, pAdvSink:ptr, pdwConnection:ptr
CDataObject::DAdvise endp
CDataObject::DUnadvise proc dwConnection:dword
CDataObject::DUnadvise endp
CDataObject::EnumDAdvise proc ppenumAdvise:ptr ptr
    mov eax,E_NOTIMPL
    ret
CDataObject::EnumDAdvise endp

    .data
    align 16
    DataObjectVtbl CDataObjectVtbl { \
        CDataObject_QueryInterface,
        CDataObject_AddRef,
        CDataObject_Release,
        CDataObject_GetData,
        CDataObject_GetDataHere,
        CDataObject_QueryGetData,
        CDataObject_GetCanonicalFormatEtc,
        CDataObject_SetData,
        CDataObject_EnumFormatEtc,
        CDataObject_DAdvise,
        CDataObject_DUnadvise,
        CDataObject_EnumDAdvise }
    .code

CDataObjectCreate proc lpDataObject:ptr ptr CDataObject, ReservedStack:uint_t

    mov r8,[rsp]
    lea rax,[rdx+((sizeof(CDataObject)+8) and (-8))+8]
    sub rsp,rax
    lea rax,[rsp+rdx]
    mov [rcx],rax
    lea rdx,DataObjectVtbl
    mov [rax],rdx
    mov [rax].CDataObject.m_cRefCount,1
    jmp r8

CDataObjectCreate endp

;; ------ RC

RCBEGIN
    RCTYPES 2
    RCENTRY RT_BITMAP
    RCENTRY RT_MENU
    RCENUMN 1
    RCENUMX IDR_BITMAP1
    RCENUMN 1
    RCENUMX IDR_MAINMENU
    RCLANGX LANGID_US
    RCLANGX LANGID_US
    RCBITMAP bitmap.bmp
    MENUBEGIN
      MENUNAME "File", MF_END
        MENUITEM IDM_INSOBJ, "Insert Object"
        SEPARATOR
        MENUITEM IDM_SAVE, "Save File"
        SEPARATOR
        MENUITEM IDM_EXIT, "Exit", MF_END
    MENUEND
RCEND

    end _tstart

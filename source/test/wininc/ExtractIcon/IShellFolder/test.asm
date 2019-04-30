include windows.inc
include shlobj.inc
include tchar.inc
ifdef _MSVCRT
.data
ifdef _UNICODE
IID_IExtractIcon IID _IID_IExtractIconW
else
IID_IExtractIcon IID _IID_IExtractIconA
endif
IID_IShellFolder IID _IID_IShellFolder
endif
.code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps          :PAINTSTRUCT,
        hDC         :HDC,
        pDesktop    :ptr IShellFolder,
        pSubfolder  :ptr IShellFolder,
        pExtractor  :ptr IExtractIcon,
        pIDL        :LPCITEMIDLIST,
        IconFile    [_MAX_PATH]:TCHAR,
        iIndex      :int_t,
        Flags       :uint_t,
        hiconLarge  :HICON,
        hiconSmall  :HICON

    .switch message

      .case WM_PAINT
        mov hDC,BeginPaint(hWnd, &ps)
        .ifd !SHGetDesktopFolder(&pDesktop)

            .ifd !pDesktop.ParseDisplayName(NULL, NULL, L"C:\\Windows", NULL, &pIDL, NULL)

                .ifd !pDesktop.BindToObject(pIDL, NULL, &IID_IShellFolder, &pSubfolder)

                    .ifd !pSubfolder.ParseDisplayName(NULL, NULL, L"regedit.exe", NULL, &pIDL, NULL)

                        .ifd !pSubfolder.GetUIObjectOf(hWnd, 1, &pIDL, &IID_IExtractIcon, 0, &pExtractor)

                            .ifd !pExtractor.GetIconLocation(0, &IconFile, _MAX_PATH, &iIndex, &Flags)

                                .ifd !pExtractor.Extract(&IconFile, iIndex, &hiconLarge, &hiconSmall, 0x00200010)

                                    DrawIcon(hDC, 100, 75, hiconLarge)
                                    DrawIcon(hDC, 200, 75, hiconSmall)
                                .endif
                            .endif
                            pExtractor.Release()
                        .endif
                    .endif
                    pSubfolder.Release()
                .endif
            .endif
            pDesktop.Release()
        .endif
        EndPaint(hWnd, &ps)
        xor eax,eax
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

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    lea rax,WndProc
    mov wc.lpfnWndProc,rax
    mov rcx,hInstance
    xor eax,eax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov wc.hInstance,rcx
    mov wc.hbrBackground,COLOR_WINDOW+1
    mov wc.lpszMenuName,rax
    lea rax,@CStr("WndClass")
    mov wc.lpszClassName,rax
    mov wc.hIcon,LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)
    RegisterClassEx(&wc)

    mov ecx,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0, "WndClass", "Window", WS_OVERLAPPEDWINDOW,
        ecx, ecx, ecx, ecx, 0, 0, hInstance, 0)
    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)

    .while GetMessage(&msg, 0, 0, 0)
        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    mov rax,msg.wParam
    ret

_tWinMain endp

    end _tstart

; RichEdit Control
;
; https://win32assembly.programminghorizon.com/tut35.html
;
ifndef _WIN64
_CType equ <stdcall>
endif
include lang/ru.txt
include windows.inc
include richedit.inc
include winres.inc
include tchar.inc

IDR_MAINMENU        equ 100
IDM_OPEN            equ 40001
IDM_SAVE            equ 40002
IDM_CLOSE           equ 40003
IDM_SAVEAS          equ 40004
IDM_EXIT            equ 40005
IDM_COPY            equ 40006
IDM_CUT             equ 40007
IDM_PASTE           equ 40008
IDM_DELETE          equ 40009
IDM_SELECTALL       equ 40010
IDM_OPTION          equ 40011
IDM_UNDO            equ 40012
IDM_REDO            equ 40013
IDD_OPTIONDLG       equ 101
IDC_BACKCOLORBOX    equ 1000
IDC_TEXTCOLORBOX    equ 1001
IDR_MAINACCEL       equ 105
IDD_FINDDLG         equ 102
IDD_GOTODLG         equ 103
IDD_REPLACEDLG      equ 104
IDC_FINDEDIT        equ 1000
IDC_MATCHCASE       equ 1001
IDC_REPLACEEDIT     equ 1001
IDC_WHOLEWORD       equ 1002
IDC_DOWN            equ 1003
IDC_UP              equ 1004
IDC_LINENO          equ 1005
IDM_FIND            equ 40014
IDM_FINDNEXT        equ 40015
IDM_REPLACE         equ 40016
IDM_GOTOLINE        equ 40017
IDM_FINDPREV        equ 40018
RichEditID          equ 300

.data
hEdit           HWND 0
hAccel          HACCEL 0
hInstance       HINSTANCE 0
OldWndProc      LONG_PTR 0
uFlags          dd 0
hSearch         HANDLE 0    ; handle to the search/replace dialog box
BGColor         dd 0xFFFFFF ; default to white
TextColor       dd 0        ; default to black
FileOpened      dd 0
FileName        db 256 dup(0)
AltFileName     db 256 dup(0)
FindBuffer      db 256 dup(0)
ReplBuffer      db 256 dup(0)
CustomColors    dd 16 dup(0)
findtext        FINDTEXTEX <>
TextBuffer      db 1024*10 dup(0)
AppName         TCHAR "Testpad",0
ASMFilter       TCHAR "ASM Source code (*.asm)",0,"*.asm",0
                TCHAR "All Files (*.*)",0,"*.*",0,0

.code

RichEditProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local result:SINT

    .switch uMsg

      .case WM_PAINT
        HideCaret(hWnd)
        CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam)
        mov result,eax
        ShowCaret(hWnd)
        mov eax,result
        .endc

      .case WM_CLOSE
        SetWindowLongPtr(hWnd, GWL_WNDPROC, OldWndProc)
        .endc

      .default
        CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam)
    .endsw
    ret

RichEditProc endp

PrepareEditMenu proc hSubMenu:HANDLE

    local chrg:CHARRANGE
    ;
    ; Check whether there is some text in the clipboard. If so,
    ; we enable the paste menuitem
    ;
    .if !SendMessage(hEdit, EM_CANPASTE, CF_TEXT, 0)      ; no text in the clipboard
        EnableMenuItem(hSubMenu, IDM_PASTE, MF_GRAYED)
    .else
        EnableMenuItem(hSubMenu, IDM_PASTE, MF_ENABLED)
    .endif
    ;
    ; check whether the undo queue is empty
    ;
    .if !SendMessage(hEdit, EM_CANUNDO, 0, 0)
        EnableMenuItem(hSubMenu, IDM_UNDO, MF_GRAYED)
    .else
        EnableMenuItem(hSubMenu, IDM_UNDO, MF_ENABLED)
    .endif
    ;
    ; check whether the redo queue is empty
    ;
    .if !SendMessage(hEdit, EM_CANREDO, 0, 0)
        EnableMenuItem(hSubMenu, IDM_REDO, MF_GRAYED)
    .else
        EnableMenuItem(hSubMenu, IDM_REDO, MF_ENABLED)
    .endif
    ;
    ; check whether there is a current selection in the richedit control.
    ; If there is, we enable the cut/copy/delete menuitem
    ;
    SendMessage(hEdit, EM_EXGETSEL, 0, &chrg)
    mov eax,chrg.cpMin
    .if eax == chrg.cpMax     ; no current selection
        EnableMenuItem(hSubMenu, IDM_COPY, MF_GRAYED)
        EnableMenuItem(hSubMenu, IDM_CUT, MF_GRAYED)
        EnableMenuItem(hSubMenu, IDM_DELETE, MF_GRAYED)
    .else
        EnableMenuItem(hSubMenu, IDM_COPY, MF_ENABLED)
        EnableMenuItem(hSubMenu, IDM_CUT, MF_ENABLED)
        EnableMenuItem(hSubMenu, IDM_DELETE, MF_ENABLED)
    .endif
    ret

PrepareEditMenu endp

StreamInProc proc hFile:HANDLE, pBuffer:LPSTR, NumBytes:UINT, pBytesRead:LPDWORD
    ReadFile(hFile, pBuffer, NumBytes, pBytesRead, 0)
    xor eax,1
    ret
StreamInProc endp

StreamOutProc proc hFile:HANDLE, pBuffer:LPSTR, NumBytes:UINT, pBytesWritten:LPDWORD
    WriteFile(hFile, pBuffer, NumBytes, pBytesWritten, 0)
    xor eax,1
    ret
StreamOutProc endp

CheckModifyState proc uses rsi hWnd:HWND

    mov esi,1
    .if SendMessage(hEdit, EM_GETMODIFY, 0, 0)

        .if MessageBox(hWnd,
                "The data in the control is modified. Want to save it?",
                &AppName, MB_YESNOCANCEL) == IDYES
            SendMessage(hWnd, WM_COMMAND, IDM_SAVE, 0)
        .elseif eax==IDCANCEL
            dec esi
        .endif
    .endif
    mov eax,esi
    ret

CheckModifyState endp

SetColor proc

    local cfm:CHARFORMAT

    SendMessage(hEdit, EM_SETBKGNDCOLOR, 0, BGColor)
    RtlZeroMemory(&cfm, sizeof(cfm))
    mov cfm.cbSize,sizeof(cfm)
    mov cfm.dwMask,CFM_COLOR
    mov eax,TextColor
    mov cfm.crTextColor,eax
    SendMessage(hEdit, EM_SETCHARFORMAT, SCF_ALL, &cfm)
    ret

SetColor endp

OptionProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local clr:CHOOSECOLOR

    mov eax,uMsg
    .switch eax

      .case WM_INITDIALOG
        mov eax,TRUE
        .endc

      .case WM_COMMAND
        mov rax,wParam
        shr eax,16
        .if ax == BN_CLICKED
            mov rax,wParam
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax == IDC_BACKCOLORBOX
                RtlZeroMemory(&clr, sizeof(clr))
                mov  clr.lStructSize,sizeof(clr)
                push hWnd
                pop  clr.hwndOwner
                push hInstance
                pop  clr.hInstance
                mov  eax,BGColor
                mov  clr.rgbResult,eax
                lea  rax,CustomColors
                mov  clr.lpCustColors,rax
                mov  clr.Flags,CC_ANYCOLOR or CC_RGBINIT

                .if ChooseColor(&clr)
                    mov eax,clr.rgbResult
                    mov BGColor,eax
                    InvalidateRect(GetDlgItem(hWnd, IDC_BACKCOLORBOX), 0, TRUE)
                .endif
            .elseif ax==IDC_TEXTCOLORBOX
                RtlZeroMemory(&clr, sizeof(clr))
                mov  clr.lStructSize,sizeof(clr)
                push hWnd
                pop  clr.hwndOwner
                push hInstance
                pop clr.hInstance
                mov eax,TextColor
                mov clr.rgbResult,eax
                lea rax,CustomColors
                mov clr.lpCustColors,rax
                mov clr.Flags,CC_ANYCOLOR or CC_RGBINIT

                .if ChooseColor(&clr)
                    mov eax,clr.rgbResult
                    mov TextColor,eax
                    InvalidateRect(GetDlgItem(hWnd, IDC_TEXTCOLORBOX), 0, TRUE)
                .endif
            .elseif ax==IDOK
                ;
                ; Save the modify state of the richedit control because changing
                ; the text color changes the modify state of the richedit control.
                ;
                SendMessage(hEdit, EM_GETMODIFY, 0, 0)
                push rax
                SetColor()
                pop rax
                SendMessage(hEdit, EM_SETMODIFY, eax, 0)
                EndDialog(hWnd, 0)
            .endif
        .endif
        mov eax,TRUE
        .endc

      .case WM_CTLCOLORSTATIC
        .if GetDlgItem(hWnd, IDC_BACKCOLORBOX) == lParam
            CreateSolidBrush(BGColor)
        .elseif GetDlgItem(hWnd, IDC_TEXTCOLORBOX) == lParam
            CreateSolidBrush(TextColor)
        .else
            mov eax,FALSE
        .endif
        .endc

      .case WM_CLOSE
        EndDialog(hWnd, 0)
        mov eax,TRUE
        .endc

      .default
        mov eax,FALSE
        .endc
    .endsw
    ret

OptionProc endp

SearchProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov eax,uMsg
    .switch eax

      .case WM_INITDIALOG
        push hWnd
        pop  hSearch
        ;
        ; Select the default search down option
        ;
        CheckRadioButton(hWnd, IDC_DOWN, IDC_UP, IDC_DOWN)
        SendDlgItemMessage(hWnd, IDC_FINDEDIT, WM_SETTEXT, 0, &FindBuffer)
        mov eax,TRUE
        .endc

      .case WM_COMMAND
        mov rax,wParam
        shr eax,16
        .if ax==BN_CLICKED
            mov rax,wParam
            .if ax == IDOK
                mov uFlags,0
                SendMessage(hEdit, EM_EXGETSEL, 0, &findtext.chrg)

                .if GetDlgItemText(hWnd, IDC_FINDEDIT, &FindBuffer, sizeof(FindBuffer))

                    .if IsDlgButtonChecked(hWnd, IDC_DOWN) == BST_CHECKED
                        or uFlags,FR_DOWN
                        mov eax,findtext.chrg.cpMin
                        .if eax != findtext.chrg.cpMax
                            mov eax,findtext.chrg.cpMax
                            mov findtext.chrg.cpMin,eax
                        .endif
                        mov findtext.chrg.cpMax,-1
                    .else
                        mov findtext.chrg.cpMax,0
                    .endif

                    .if IsDlgButtonChecked(hWnd, IDC_MATCHCASE) == BST_CHECKED
                        or uFlags,FR_MATCHCASE
                    .endif

                    .if IsDlgButtonChecked(hWnd, IDC_WHOLEWORD) == BST_CHECKED
                        or uFlags,FR_WHOLEWORD
                    .endif
                    lea rax,FindBuffer
                    mov findtext.lpstrText,rax

                    .if SendMessage(hEdit, EM_FINDTEXTEX, uFlags, &findtext) != -1
                        SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    .endif
                .endif
            .elseif ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .else
                mov eax,FALSE
                .endc
            .endif
        .endif
        mov eax,TRUE
        .endc

      .case WM_CLOSE
        mov hSearch,0
        EndDialog(hWnd, 0)
        mov eax,TRUE
        .endc

      .default
        mov eax,FALSE
        .endc
    .endsw
    ret

SearchProc endp

ReplaceProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local settext:SETTEXTEX

    mov eax,uMsg
    .switch eax

      .case WM_INITDIALOG
        push hWnd
        pop  hSearch
        SetDlgItemText(hWnd, IDC_FINDEDIT,    &FindBuffer)
        SetDlgItemText(hWnd, IDC_REPLACEEDIT, &ReplBuffer)
        mov eax,TRUE
        .endc

      .case WM_COMMAND
        mov rax,wParam
        shr eax,16
        .if ax == BN_CLICKED
            mov rax,wParam
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax==IDOK
                GetDlgItemText(hWnd, IDC_FINDEDIT,    &FindBuffer, sizeof(FindBuffer))
                GetDlgItemText(hWnd, IDC_REPLACEEDIT, &ReplBuffer, sizeof(ReplBuffer))
                mov findtext.chrg.cpMin,0
                mov findtext.chrg.cpMax,-1
                lea rax,FindBuffer
                mov findtext.lpstrText,rax
                mov settext.flags,ST_SELECTION
                mov settext.codepage,0;CP_ACP
                .while 1
                    .break .if SendMessage(hEdit, EM_FINDTEXTEX, FR_DOWN, &findtext) == -1
                    SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    SendMessage(hEdit, EM_SETTEXTEX, &settext, &ReplBuffer)
                .endw
            .endif
        .endif
        mov eax,TRUE
        .endc

      .case WM_CLOSE
        mov hSearch,0
        EndDialog(hWnd, 0)
        mov eax,TRUE
        .endc

      .default
        mov eax,FALSE
    .endsw
    ret
ReplaceProc endp

GoToProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local LineNo:DWORD
    local chrg:CHARRANGE

    mov eax,uMsg
    .switch eax

      .case WM_INITDIALOG
        push hWnd
        pop  hSearch
        mov eax,TRUE
        .endc

      .case WM_COMMAND
        mov rax,wParam
        shr eax,16
        .if ax == BN_CLICKED
            mov rax,wParam
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax == IDOK
                GetDlgItemInt(hWnd, IDC_LINENO, NULL, FALSE)
                mov LineNo,eax
                .ifd SendMessage(hEdit, EM_GETLINECOUNT, 0, 0) > LineNo
                    SendMessage(hEdit, EM_LINEINDEX, LineNo, 0)
                    SendMessage(hEdit, EM_SETSEL, eax, eax)
                    SetFocus(hEdit)
                .endif
            .endif
        .endif
        mov eax,TRUE
        .endc

      .case WM_CLOSE
        mov hSearch,0
        EndDialog(hWnd, 0)
        mov eax,TRUE
        .endc

      .default
        mov eax,FALSE
    .endsw
    ret

GoToProc endp

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    local buffer[256]:sbyte
    local hPopup:HMENU
    local pt:POINT
    local ofn:OPENFILENAME
    local hFile:HANDLE
    local editstream:EDITSTREAM
    local chrg:CHARRANGE
    local x:SINT

    .switch message

      .case WM_CREATE

        .if !LoadLibrary("Msftedit.dll")

            PostQuitMessage(1)
            xor eax,eax
            .endc
        .endif

        mov hEdit,CreateWindowEx(
                WS_EX_CLIENTEDGE,
                MSFTEDIT_CLASS,
                0,
                ES_MULTILINE or WS_VISIBLE or WS_CHILD or WS_BORDER or WS_VSCROLL or WS_HSCROLL or ES_NOHIDESEL,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                hWnd,
                RichEditID,
                hInstance,
                NULL
        )
        SendMessage(hEdit, EM_SETTYPOGRAPHYOPTIONS, TO_SIMPLELINEBREAK, TO_SIMPLELINEBREAK)
        SendMessage(hEdit, EM_GETTYPOGRAPHYOPTIONS, 1, 1)
        SendMessage(hEdit, EM_SETEDITSTYLE, SES_EMULATESYSEDIT, SES_EMULATESYSEDIT)
        mov OldWndProc,SetWindowLongPtr(hEdit, GWL_WNDPROC, &RichEditProc)
        SendMessage(hEdit, EM_LIMITTEXT, -1, 0)
        SetColor()
        SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
        SendMessage(hEdit, EM_SETEVENTMASK, 0, ENM_MOUSEEVENTS)
        SendMessage(hEdit, EM_EMPTYUNDOBUFFER, 0, 0)
        xor eax,eax
        .endc

      .case WM_NOTIFY
        push rsi
        mov rsi,lParam
        assume rsi:ptr NMHDR
        .if [rsi].code == EN_MSGFILTER
            assume rsi:ptr MSGFILTER
            .if [rsi].msg == WM_RBUTTONDOWN

                mov hPopup,GetSubMenu(GetMenu(hWnd), 1)
                PrepareEditMenu(rax)
                mov rdx,[rsi].lParam
                mov ecx,edx
                and edx,0xFFFF
                shr ecx,16
                mov pt.x,edx
                mov pt.y,ecx
                ClientToScreen(hWnd, &pt)
                TrackPopupMenu(hPopup, TPM_LEFTALIGN or TPM_BOTTOMALIGN,
                    pt.x, pt.y, NULL, hWnd, NULL)
            .endif
        .endif
        pop rsi
        xor eax,eax
        .endc

      .case WM_INITMENUPOPUP
        movzx eax,word ptr lParam
        .switch eax
          .case 0       ; file menu
            .if FileOpened == TRUE    ; a file is already opened
                EnableMenuItem(wParam, IDM_OPEN, MF_GRAYED)
                EnableMenuItem(wParam, IDM_CLOSE, MF_ENABLED)
                EnableMenuItem(wParam, IDM_SAVE, MF_ENABLED)
                EnableMenuItem(wParam, IDM_SAVEAS, MF_ENABLED)
            .else
                EnableMenuItem(wParam, IDM_OPEN, MF_ENABLED)
                EnableMenuItem(wParam, IDM_CLOSE, MF_GRAYED)
                EnableMenuItem(wParam, IDM_SAVE, MF_GRAYED)
                EnableMenuItem(wParam, IDM_SAVEAS, MF_GRAYED)
            .endif
            .endc
          .case 1   ; edit menu
            PrepareEditMenu(wParam)
            .endc
          .case 2       ; search menu bar
            .if FileOpened==TRUE
                EnableMenuItem(wParam, IDM_FIND, MF_ENABLED)
                EnableMenuItem(wParam, IDM_FINDNEXT, MF_ENABLED)
                EnableMenuItem(wParam, IDM_FINDPREV, MF_ENABLED)
                EnableMenuItem(wParam, IDM_REPLACE, MF_ENABLED)
                EnableMenuItem(wParam, IDM_GOTOLINE, MF_ENABLED)
            .else
                EnableMenuItem(wParam, IDM_FIND, MF_GRAYED)
                EnableMenuItem(wParam, IDM_FINDNEXT, MF_GRAYED)
                EnableMenuItem(wParam, IDM_FINDPREV, MF_GRAYED)
                EnableMenuItem(wParam, IDM_REPLACE, MF_GRAYED)
                EnableMenuItem(wParam, IDM_GOTOLINE, MF_GRAYED)
            .endif
            .endc
        .endsw
        xor eax,eax
        .endc

      .case WM_COMMAND

        .if !lParam       ; menu commands

            movzx eax,word ptr wParam
            .switch eax

              .case IDM_OPEN

                RtlZeroMemory(&ofn, sizeof(ofn))
                mov  ofn.lStructSize,sizeof(ofn)
                push hWnd
                pop  ofn.hwndOwner
                push hInstance
                pop  ofn.hInstance
                lea rax,ASMFilter
                mov ofn.lpstrFilter,rax
                lea rax,FileName
                mov ofn.lpstrFile,rax
                mov word ptr [rax],0
                mov ofn.nMaxFile,sizeof FileName
                mov ofn.Flags,OFN_FILEMUSTEXIST or OFN_HIDEREADONLY or OFN_PATHMUSTEXIST

                .if GetOpenFileName(&ofn)

                    .if CreateFile(&FileName,
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            0) != INVALID_HANDLE_VALUE

                        mov hFile,rax
                        mov editstream.dwCookie,rax
                        lea rax,StreamInProc
                        mov editstream.pfnCallback,rax

                        SendMessage(hEdit, EM_STREAMIN, SF_TEXT, &editstream)
                        SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
                        CloseHandle(hFile)
                        mov FileOpened,TRUE

                    .else
                        MessageBox(hWnd, "Cannot open the file",
                            &AppName, MB_OK or MB_ICONERROR)
                    .endif
                .endif
                .endc

              .case IDM_CLOSE

                .if CheckModifyState(hWnd)
                    SetWindowText(hEdit, 0)
                    mov FileOpened,FALSE
                .endif
                .endc

              .case IDM_SAVE

                .if CreateFile(&FileName,
                        GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        0) != INVALID_HANDLE_VALUE

                    mov hFile,rax
                    mov editstream.dwCookie,rax
                    lea rax,StreamOutProc
                    mov editstream.pfnCallback,rax

                    SendMessage(hEdit, EM_STREAMOUT, SF_TEXT, &editstream)
                    SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
                    CloseHandle(hFile)
                .else
                    MessageBox(hWnd, "Cannot open the file",
                            &AppName,  MB_OK or MB_ICONERROR)
                .endif
                .endc

              .case IDM_COPY
                SendMessage(hEdit, WM_COPY, 0, 0)
                .endc

              .case IDM_CUT
                SendMessage(hEdit, WM_CUT, 0, 0)
                .endc

              .case IDM_PASTE
                SendMessage(hEdit, WM_PASTE, 0, 0)
                .endc

              .case IDM_DELETE
                SendMessage(hEdit, EM_REPLACESEL, TRUE, 0)
                .endc

              .case IDM_SELECTALL
                mov chrg.cpMin,0
                mov chrg.cpMax,-1
                SendMessage(hEdit, EM_EXSETSEL, 0, &chrg)
                .endc

              .case IDM_UNDO
                SendMessage(hEdit, EM_UNDO, 0, 0)
                .endc

              .case IDM_REDO
                SendMessage(hEdit, EM_REDO, 0, 0)
                .endc

              .case IDM_OPTION
                DialogBoxParam(hInstance, IDD_OPTIONDLG, hWnd, &OptionProc, 0)
                .endc

              .case IDM_SAVEAS
                RtlZeroMemory(&ofn, sizeof(ofn))
                mov ofn.lStructSize,sizeof(ofn)
                push hWnd
                pop ofn.hwndOwner
                push hInstance
                pop ofn.hInstance
                lea rax,ASMFilter
                mov ofn.lpstrFilter,rax
                lea rax,AltFileName
                mov ofn.lpstrFile,rax
                mov TCHAR ptr [AltFileName],0
                mov ofn.nMaxFile,sizeof AltFileName
                mov ofn.Flags,OFN_FILEMUSTEXIST or OFN_HIDEREADONLY or OFN_PATHMUSTEXIST

                .if GetSaveFileName(&ofn)
                    .if CreateFile(&AltFileName,
                        GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        0) != INVALID_HANDLE_VALUE

                        mov hFile,rax
                        mov editstream.dwCookie,rax
                        lea rax,StreamOutProc
                        mov editstream.pfnCallback,rax
                        SendMessage(hEdit, EM_STREAMOUT, SF_TEXT, &editstream)
                        SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
                        CloseHandle(hFile)
                    .endif
                .endif
                .endc

              .case IDM_FIND
                .if !hSearch
                    CreateDialogParam(hInstance, IDD_FINDDLG, hWnd, &SearchProc, 0)
                .endif
                .endc

              .case IDM_REPLACE
                .if !hSearch
                    CreateDialogParam(hInstance, IDD_REPLACEDLG, hWnd, &ReplaceProc, 0)
                .endif
                .endc

              .case IDM_GOTOLINE
                .if !hSearch
                    CreateDialogParam(hInstance, IDD_GOTODLG, hWnd, &GoToProc, 0)
                .endif
                .endc

              .case IDM_FINDNEXT
                .if FindBuffer
                    SendMessage(hEdit, EM_EXGETSEL, 0, &findtext.chrg)
                    mov eax,findtext.chrg.cpMin
                    .if eax != findtext.chrg.cpMax
                        mov eax,findtext.chrg.cpMax
                        mov findtext.chrg.cpMin,eax
                    .endif
                    mov findtext.chrg.cpMax,-1
                    lea rax,FindBuffer
                    mov findtext.lpstrText,rax

                    .if SendMessage(hEdit, EM_FINDTEXTEX, FR_DOWN, &findtext) != -1
                        SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    .endif
                .endif
                .endc

              .case IDM_FINDPREV
                .if FindBuffer
                    SendMessage(hEdit, EM_EXGETSEL, 0, &findtext.chrg)
                    mov findtext.chrg.cpMax,0
                    lea rax,FindBuffer
                    mov findtext.lpstrText,rax

                    .if SendMessage(hEdit, EM_FINDTEXTEX, 0, &findtext) != -1
                        SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    .endif
                .endif
                .endc

              .case IDM_EXIT
                SendMessage(hWnd, WM_CLOSE, 0, 0)
                .endc
            .endsw
        .endif
        xor eax,eax
        .endc

      .case WM_CLOSE

        .if CheckModifyState(hWnd)
            DestroyWindow(hWnd)
        .endif
        .endc

      .case WM_SIZE
        mov rcx,lParam
        mov edx,ecx
        and ecx,0xFFFF
        shr edx,16
        mov x,edx
        MoveWindow(hEdit, 0, 0, ecx, x, TRUE)
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

_tWinMain proc WINAPI hInst: HINSTANCE,
     hPrevInstance: HINSTANCE,
         lpCmdLine: LPTSTR,
          nShowCmd: SINT

    local wc:WNDCLASSEX
    local msg:MSG
    local hwnd:HANDLE

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    lea rax,WndProc
    mov wc.lpfnWndProc,rax

    mov rcx,hInst
    xor eax,eax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov hInstance,rcx
    mov wc.hInstance,rcx
    mov wc.hbrBackground,COLOR_WINDOW+1
    mov wc.lpszMenuName,IDR_MAINMENU

    lea rax,@CStr("WndClass")
    mov wc.lpszClassName,rax
    mov wc.hIcon,LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)

    RegisterClassEx(&wc)

    mov ecx,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0, "WndClass", "Testpad", WS_OVERLAPPEDWINDOW,
        ecx, ecx, ecx, ecx, 0, 0, hInstance, 0)

    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)
    mov hAccel,LoadAccelerators(hInstance, IDR_MAINACCEL)

    .while GetMessage(&msg, 0, 0, 0)

        .if !TranslateAccelerator(hwnd, hAccel, &msg)

            TranslateMessage(&msg)
            DispatchMessage(&msg)
        .endif
    .endw
    mov rax,msg.wParam
    ret

_tWinMain endp

RCBEGIN

    RCTYPES 3
    RCENTRY RT_MENU
    RCENTRY RT_DIALOG
    RCENTRY RT_ACCELERATOR

    RCENUMN 1
    RCENUMX IDR_MAINMENU
    RCENUMN 4
    RCENUMX IDD_OPTIONDLG
    RCENUMX IDD_FINDDLG
    RCENUMX IDD_GOTODLG
    RCENUMX IDD_REPLACEDLG
    RCENUMN 1
    RCENUMX 105
    REPEAT 6
    RCLANGX LANGUAGEID
    ENDM

    MENUBEGIN
      MENUNAME IDS_FILE
        MENUITEM IDM_OPEN,   IDS_OPEN
        MENUITEM IDM_CLOSE,  IDS_CLOSE
        MENUITEM IDM_SAVE,   IDS_SAVE
        MENUITEM IDM_SAVEAS, IDS_SAVEAS
        SEPARATOR
        MENUITEM IDM_EXIT, IDS_EXIT, MF_END
      MENUNAME IDS_EDIT
        MENUITEM IDM_UNDO,   IDS_UNDO
        MENUITEM IDM_REDO,   IDS_REDO
        MENUITEM IDM_COPY,   IDS_COPY
        MENUITEM IDM_CUT,    IDS_CUT
        MENUITEM IDM_PASTE,  IDS_PASTE
        SEPARATOR
        MENUITEM IDM_DELETE, IDS_DELETE
        SEPARATOR
        MENUITEM IDM_SELECTALL, IDS_SELECTALL, MF_END
      MENUNAME IDS_SEARCH
        MENUITEM IDM_FIND,     IDS_FIND
        MENUITEM IDM_FINDNEXT, IDS_FINDNEXT
        MENUITEM IDM_FINDPREV, IDS_FINDPREV
        MENUITEM IDM_REPLACE,  IDS_REPLACE
        SEPARATOR
        MENUITEM IDM_GOTOLINE, IDS_GOTO, MF_END
      MENUITEM IDM_OPTION, IDS_OPTIONS, MF_END
    MENUEND

    DLGFLAGS equ DS_MODALFRAME or DS_SETFONT or WS_POPUP or WS_VISIBLE or WS_CAPTION or WS_SYSMENU

    DLGBEGIN DLGFLAGS,7,0,0,196,60
     CAPTION IDS_OPTIONS
     FONT 8, "MS Sans Serif"
      DEFPUSHBUTTON   IDS_OK,IDOK,137,7,50,14;39,14
      PUSHBUTTON      IDS_CANCEL,IDCANCEL,137,25,50,14
      GROUPBOX        0,IDC_STATIC,5,0,124,49
      LTEXT           IDS_BACKGR,IDC_STATIC,20,14,60,8
      LTEXT           0,IDC_BACKCOLORBOX,85,11,28,14,SS_NOTIFY or WS_BORDER
      LTEXT           IDS_FOREGR,IDC_STATIC,20,33,35,8
      LTEXT           0,IDC_TEXTCOLORBOX,85,29,28,14,SS_NOTIFY or WS_BORDER
    DLGEND

    DLGBEGIN DLGFLAGS,9,0,0,186,54
     CAPTION IDS_FIND2
     FONT 8, "MS Sans Serif"
      EDITTEXT        IDC_FINDEDIT,42,3,94,12,ES_AUTOHSCROLL
      CONTROL         IDS_MATCHCASE,IDC_MATCHCASE,RC_BUTTON,BS_AUTOCHECKBOX or WS_TABSTOP,6,24,54,10
      CONTROL         IDS_WHOLEWORD,IDC_WHOLEWORD,RC_BUTTON,BS_AUTOCHECKBOX or WS_TABSTOP,6,37,56,10
      CONTROL         IDS_DOWN,IDC_DOWN,RC_BUTTON,BS_AUTORADIOBUTTON or WS_TABSTOP,83,27,35,10
      CONTROL         IDS_UP,IDC_UP,RC_BUTTON,BS_AUTORADIOBUTTON or WS_TABSTOP,83,38,25,10
      DEFPUSHBUTTON   IDS_OK,IDOK,141,3,39,12
      PUSHBUTTON      IDS_CANCEL,IDCANCEL,141,18,39,12
      LTEXT           IDS_FINDWHAT,IDC_STATIC,5,4,34,8
      GROUPBOX        IDS_DIRECTION,IDC_STATIC,70,18,64,32
    DLGEND

    DLGBEGIN DLGFLAGS,4,0,0,106,30,WS_EX_TOOLWINDOW
     CAPTION IDS_GOTO2
     FONT 8, "MS Sans Serif", 0, 0, 0x1
      EDITTEXT        IDC_LINENO,29,4,35,11,ES_AUTOHSCROLL or ES_NUMBER,WS_EX_CLIENTEDGE
      DEFPUSHBUTTON   IDS_OK,IDOK,70,4,31,11
      PUSHBUTTON      IDS_CANCEL,IDCANCEL,70,17,31,11
      LTEXT           IDS_LINE,IDC_STATIC,8,5,18,8
    DLGEND

    DLGBEGIN DLGFLAGS,6,0,0,186,33
     CAPTION IDS_REPLACE2
     FONT 8, "MS Sans Serif"
      EDITTEXT        IDC_FINDEDIT,51,3,84,12,ES_AUTOHSCROLL
      EDITTEXT        IDC_REPLACEEDIT,51,17,84,11,ES_AUTOHSCROLL
      DEFPUSHBUTTON   IDS_OK,IDOK,142,3,39,11
      PUSHBUTTON      IDS_CANCEL,IDCANCEL,142,17,39,11
      LTEXT           IDS_FINDWHAT,IDC_STATIC,3,4,34,8
      LTEXT           IDS_REPLACEWITH,IDC_STATIC,3,18,42,8
    DLGEND

    DLGBEGIN 0x0046000B,0x00009C4E,11,71,0x9C51,0,11
      db 70,0, 78,156,0,0, 11,0, 71,0, 81,156, 0,0
      db 11,0,82,0,80,156,0,0,3,0,114,0,79,156,0,0
      db 139,0,114,0,82,156,0,0
    DLGEND

RCEND

    end _tstart

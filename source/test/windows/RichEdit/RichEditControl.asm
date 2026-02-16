; RichEdit Control
; Unicode with Syntax Highlighting and Font Menu

include RichEditControl.inc

.data?
style           db STYLESIZE dup(?)
TextBuffer      TCHAR 1024*10 dup(?)
FileName        TCHAR 256 dup(?)
AltFileName     TCHAR 256 dup(?)
FindBuffer      TCHAR 256 dup(?)
ReplBuffer      TCHAR 256 dup(?)
Profile         TCHAR 512 dup(?)
hEdit           HWND ?
hAccel          HACCEL ?
hInstance       HINSTANCE ?
OldWndProc      LONG_PTR ?
uFlags          dd ?
hSearch         HANDLE ?    ; handle to the search/replace dialog box
FileOpened      dd ?
findtext        FINDTEXTEX <>
AppFont         LOGFONT <>

.data
debug           dd 0
TextColor       dd RGB(192,192,192) ; default to gray
BackColor       dd RGB(0,0,0)       ; default to black
SyntaxColors    dd RGB(0,0,0)
                dd RGB(0,0,128)
                dd RGB(0,128,0)
                dd RGB(0,128,128)
                dd RGB(128,0,0)
                dd RGB(116,65,65)
                dd RGB(128,128,0)
                dd RGB(192,192,192)
                dd RGB(128,128,128)
                dd RGB(0,0,255)
                dd RGB(0,255,0)
                dd RGB(0,255,255)
                dd RGB(145,0,0)
                dd RGB(255,0,255)
                dd RGB(255,255,0)
                dd RGB(255,255,255)
hFont           HANDLE 0
AppName         TCHAR "Testpad",0
ASMFilter       TCHAR "ASM Source code (*.asm)",0,"*.asm",0
                TCHAR "All Files (*.*)",0,"*.*",0,0
typech          db "aqdcswn",0

.code

; Read style

GetEntry proc file:LPTSTR, section:LPTSTR, entry:LPTSTR, buffer:LPTSTR
    .if GetPrivateProfileString(section, entry, 0, buffer, MAX_ENTRY, file)
        mov rcx,rax
        mov rax,buffer
    .endif
    ret
    endp

GetEntryID proc file:LPTSTR, section:LPTSTR, ID:SINT, buffer:LPTSTR
  local entry[2]
    xor edx,edx
    mov eax,ID ; 0..99
    .while  al > 9
        add dl,1
        sub al,10
    .endw
    .if dl
        xchg al,dl
        or dl,'0'
    .endif
    or  al,'0'
    shl edx,16
    or eax,edx
    mov entry,eax
    mov entry[4],0
    GetEntry(file, section, &entry, buffer)
    ret
    endp

ReadLabel PROC USES rsi rdi rbx file:LPTSTR, section:LPTSTR, buffer:LPTSTR, endbuf:LPTSTR

  local entry[MAX_ENTRY]:byte
  local st_type,i,p:LPTSTR,q:LPTSTR

    .return .if !GetEntryID( ldr(file), ldr(section), 0, &entry )

    mov p,rax
    mov al,[rax]
    or  al,0x20
    lea rdx,typech
    mov ecx,sizeof(typech)
    mov rdi,rdx
    repnz scasb
    .return .ifnz

    mov rax,rdi
    sub rax,rdx
    mov st_type,eax

    mov rdi,buffer
    mov rdi,[rdi]

    .return .if rdi >= endbuf

    stosb           ; store type
    mov rsi,p
    xor eax,eax
    mov i,eax

    .repeat
        add rsi,TCHAR
        mov al,[rsi]
    .until (al == 9 || al == ' ' || al == '_')

    .repeat

        lodsw
        .switch
        .case al == ' '
            mov rax,rsi
           .endc
        .case al
            .continue
        .default
            mov i,1
            .break .if !GetEntryID( file, section, 1, &entry)
        .endsw

        mov rsi,rax
        add rax,2
        mov p,rax
        mov al,[rsi]
        sub al,'0'
        .if al > 9
            sub al,7
        .endif
        stosb ; store attrib

        mov rsi,p
        .while TCHAR PTR [rsi] == ' '
            add rsi,TCHAR
        .endw
        .while 1
            .while 1
                lodsw
                .break .if !ax
                .break .if rdi >= endbuf
                cmp  al,' '
                sete dl
                dec  dl
                and  al,dl
                stosb
            .endw
            .break .if al
            stosb
            inc i
            .break .if i == 100
            .break .if !GetEntryID( file, section, i, &entry)
            mov rsi,rax
        .endw
    .until 1

    xor eax,eax
    .if [rdi-1] != al
        stosb
    .endif
    stosb
    mov rcx,buffer
    mov [rcx],rdi
    inc eax
    ret
    endp

ReadStyle proc uses rsi rdi file:ptr

  local buffer:ptr
  local endbuf:ptr
  local entry[MAX_ENTRY]:byte

    lea rax,style
    mov buffer,rax
    mov rdi,rax
    add rax,STYLESIZE-4
    mov endbuf,rax
    xor eax,eax
    mov ecx,STYLESIZE/4
    rep stosd
    xor esi,esi
    lea rdi,entry

    .while GetEntryID(file, "Style", esi, rdi)
        ReadLabel(file, rdi, &buffer, endbuf)
        inc esi
    .endw
    mov rdi,buffer
    xor eax,eax
    stosw
    inc eax
    ret
    endp


; Read Config

lxtol proc string:LPSTR
    .for ( rdx = ldr(string), eax = 0, ecx = 0 :: cl -= 0x10, eax <<= 4, eax += ecx )
        mov cl,[rdx]
        add rdx,2
        and cl,0xDF
        .break .if cl < 0x10
        .break .if cl > 'F'
        .if cl > 0x19
            .break .if cl < 'A'
            sub cl,'A' - 0x1A
        .endif
    .endf
    ret
    endp


latol proc string:LPSTR
    mov rdx,string
    movzx ecx,byte ptr [rdx]
    xor eax,eax
    .while 1
        sub ecx,'0'
        .break .ifc
        .break .if ecx > 9
        lea rcx,[rax*8+rcx]
        lea rax,[rax*2+rcx]
        add rdx,2
        movzx ecx,byte ptr [rdx]
    .endw
    ret
    endp


ReadConfig proc uses rsi rdi file:LPTSTR

  local entry[MAX_ENTRY]:char_t

    lea rdi,entry
    .if GetEntry(file, "Colors", "Text", rdi)
        mov TextColor,lxtol(rdi)
        .if GetEntry(file, "Colors", "Back", rdi)
            mov BackColor,lxtol(rdi)
        .endif
        xor esi,esi
        .while GetEntryID(file, "Colors", esi, rdi)
            lxtol(rdi)
            lea rcx,SyntaxColors
            mov [rcx+rsi*4],eax
            inc esi
        .endw
    .endif
    mov AppFont.lfHeight,24
    mov AppFont.lfWeight,FW_NORMAL
    mov AppFont.lfCharSet,DEFAULT_CHARSET
    lstrcpy(&AppFont.lfFaceName, "Courier New")
    .if GetEntry(file, "Font", "Face", rdi)
        lstrcpy(&AppFont.lfFaceName, rdi)
    .endif
    .if GetEntry(file, "Font", "Height", rdi)
        latol(rdi)
        shl eax,1
        mov AppFont.lfHeight,eax
    .endif
    ret
    endp


SetColor proc uses rbx

  local cfm:CHARFORMAT2

    mov rbx,SendMessage(hEdit, EM_GETMODIFY, 0, 0)
    mov rdx,rdi
    lea rdi,cfm
    mov ecx,sizeof(cfm)
    xor eax,eax
    rep stosb
    mov rdi,rdx
    mov cfm.cbSize,sizeof(cfm)
    mov eax,TextColor
    mov cfm.crTextColor,eax
    mov cfm.dwMask,CFM_COLOR; or CFM_BACKCOLOR
    SendMessage(hEdit, EM_SETCHARFORMAT, SCF_ALL, &cfm)
    SendMessage(hEdit, EM_SETBKGNDCOLOR, 0, BackColor)
    SendMessage(hEdit, EM_SETMODIFY, rbx, 0)
    ret
    endp

DLGSelectFont proc uses rdi hWnd:HWND

  local cfm:CHARFORMAT
  local Font:CHOOSEFONT

    lea rdi,Font
    xor eax,eax
    mov ecx,sizeof(CHOOSEFONT)
    rep stosb
    mov Font.lStructSize,sizeof(CHOOSEFONT)
    mov Font.hwndOwner,hWnd
    mov Font.lpLogFont,&AppFont
    mov Font.rgbColors,TextColor
    mov Font.Flags,CF_SCREENFONTS or CF_NOVERTFONTS or CF_INITTOLOGFONTSTRUCT
    .if ChooseFont(&Font)
        mov rdi,hFont
        mov hFont,CreateFontIndirect(&AppFont)
        SendMessage(hEdit, WM_SETFONT, rax, 1)
        .if rdi
            DeleteObject(rdi)
        .endif
        SetColor()
    .endif
    ret
    endp

ifdef _WIN64
SetStyle PROC USES rsi rdi rbx r15 hWnd:HWND
    lea r15,_ltype
else
SetStyle PROC USES rsi rdi rbx hWnd:HWND
endif
   .new endbuf:LPTSTR, string:LPTSTR
   .new ctype:byte, attrib:byte
   .new hdc:HDC
   .new firstchar:DWORD, bufsize
   .new rect:RECT
   .new txtrange:TEXTRANGE
   .new hRgn:HANDLE,hOldRgn:HANDLE
   .new buffer:LPTSTR

    mov hdc,GetDC(hWnd)
    SetBkMode(hdc, TRANSPARENT)
    SendMessage(hWnd, EM_GETRECT,0, &rect)
    SendMessage(hWnd, EM_CHARFROMPOS, 0, &rect)
    SendMessage(hWnd, EM_LINEFROMCHAR, eax, 0)
    SendMessage(hWnd, EM_LINEINDEX, eax, 0)
    mov txtrange.chrg.cpMin,eax
    mov firstchar,eax
    SendMessage(hWnd, EM_CHARFROMPOS, 0, &rect.right)
    mov txtrange.chrg.cpMax,eax
    mov hRgn,CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom)
    mov hOldRgn,SelectObject(hdc, hRgn)
    SelectObject(hdc, hFont)

    ; Get the visible text into buffer

    lea rax,TextBuffer
    mov buffer,rax
    mov txtrange.lpstrText,rax

    .repeat

        .break .if !SendMessage(hWnd, EM_GETTEXTRANGE, 0, &txtrange)

        mov bufsize,eax
        mov rcx,buffer
        add rcx,rax
        add rcx,rax
        mov endbuf,rcx
        lea rsi,style

        .while 1

            movzx eax,BYTE PTR [rsi]
            movzx ebx,BYTE PTR [rsi+1]
            add rsi,2
            mov ctype,al
            mov attrib,bl

            .break .if !eax
            .break .if eax > ST_COUNT

            mov string,rsi
            mov rdx,endbuf
            .break .if rdx <= buffer

            lea rcx,SyntaxColors
            .switch al
            .case ST_ATTRIB ; 1. A Attrib <at>
                mov eax,[rcx+rbx*4]
                .if eax != TextColor
                    mov TextColor,eax
                    SetColor()
                .endif
                .endc
            .case ST_QUOTE; 2. Q Quote - match on '"' and "'"
                SetTextColor(hdc, [rcx+rbx*4])
                .for ebx=0,esi=0,rdi=buffer: rdi < endbuf: rdi+=TCHAR
                    movzx eax,TCHAR ptr [rdi]
                    .if ( eax == '"' || eax == "'" )
                        .if !ebx
                            .if ( eax == '"' )
                                mov ebx,eax
                            .elseif rdi > buffer
                                .if !islabel0([rdi-2])
                                    mov ebx,"'"
                                .endif
                            .endif
                            mov rdx,rdi
                        .elseif bx == ax
                            xor ebx,ebx
                            mov rsi,rdx
                        .endif
                    .endif
                    .if rsi
                        mov rax,rsi
                        sub rax,buffer
                        shr eax,1
                        add eax,firstchar
                        SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                        add rdi,2
                        mov rcx,rdi
                        sub rcx,rsi
                        shr ecx,1
                        DrawText(hdc, rsi, ecx, &rect, DT_EDITCONTROL or DT_NOPREFIX)
                        mov rcx,rdi
                        sub rcx,rsi
                        mov rdi,rsi
                        xor eax,eax
                        rep stosb
                        xor esi,esi
                    .endif
                .endf
                .endc
              .case ST_NUMBER ; 3. D Digit - match on 0x 0123456789ABCDEF and Xh
                SetTextColor(hdc, [rcx+rbx*4])
                .for ebx=0,esi=0,rdi=buffer: rdi < endbuf: rdi+=TCHAR
                    movzx eax,TCHAR ptr [rdi]
                    .switch
                    .case ah
                    .case !eax
                    .case _isltypeA(eax, _CONTROL or _SPACE or _PUNCT)
                        .endc .if !rbx
                        mov rsi,rdi
                        .endc
                    .case _isldigitA(eax)
                        .endc .if rbx
                        .if rdi > buffer
                            .endc .if islabel([rdi-2])
                        .endif
                        mov rbx,rdi
                        .endc
                    .case eax == 'x'
                    .case eax == 'X'
                    .case eax == 'h'
                    .case eax == 'H'
                    .case _islxdigitA(eax)
                        .endc
                    .default
                        .endc .if !rbx
                        mov rsi,rdi
                        .endc
                    .endsw
                    .if rsi
                        mov rax,rbx
                        sub rax,buffer
                        shr eax,1
                        add eax,firstchar
                        SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                        mov rcx,rdi
                        sub rcx,rbx
                        shr ecx,1
                        DrawText(hdc, rbx, ecx, &rect, DT_EDITCONTROL or DT_NOPREFIX)
                        mov rcx,rdi
                        sub rcx,rbx
                        mov rdi,rbx
                        xor eax,eax
                        rep stosb
                        xor esi,esi
                        xor ebx,ebx
                    .endif
                .endf
                .endc
            .case ST_CHAR ; 4. C Char <at> <chars>
                mov eax,[rcx+rbx*4]
                SetTextColor(hdc, eax)
                .for rdi=buffer: rdi < endbuf: rdi+=TCHAR
                    mov ax,[rdi]
                    .if ax && !ah
                        mov rbx,rsi
                        .while byte ptr [rbx]
                            .if al == [rbx]
                                mov rax,rdi
                                sub rax,buffer
                                shr eax,1
                                add eax,firstchar
                                SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                                DrawText(hdc, rdi, 1, &rect, DT_EDITCONTROL or DT_NOPREFIX)
                                .break
                            .endif
                            inc rbx
                        .endw
                    .endif
                .endf
                .endc
            .case ST_START  ; 5. S Start - X string
                            ;    set color X from string to end of line
                SetTextColor(hdc, [rcx+rbx*4])
                .while byte ptr [rsi]
                    mov rdi,buffer
                    .while rdi < endbuf
                        _ltolowerA([rsi])
                        mov rcx,endbuf
                        sub rcx,rdi
                        shr ecx,1
                        .break .ifz
                        mov rbx,rdi
                        mov edx,ecx
                        repne scasw
                        .ifnz
                            mov ecx,edx
                            mov rdi,rbx
                            _ltoupperA([rsi])
                            repne scasw
                        .endif
                        .break .ifnz
                        lea rcx,[rdi-2]
                        .if rcx > buffer
                            .continue .if islabel([rcx-2])
                        .endif
                        mov rdx,rsi
                        mov rbx,rcx
                        .repeat
                            add rdx,1
                            add rcx,2
                            mov al,[rdx]
                            .break .if !al
                            .continue(0) .if al == [rcx]
                            mov ah,[rcx]
                            or  eax,0x2020
                            .continue(0) .if al == ah
                        .until 1
                        .continue .if al
                        .if byte ptr [rsi+1]
                            .continue .if islabel([rcx])
                        .endif

                        .while rdi < endbuf
                            mov ax,[rdi]
                            .break .if !ax
                            .break .if ax == 0x0D
                            .break .if ax == 0x0A
                            add rdi,2
                        .endw
                        mov rax,rbx
                        sub rax,buffer
                        shr eax,1
                        add eax,firstchar
                        SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                        mov rcx,rdi
                        sub rcx,rbx
                        shr ecx,1
                        DrawText(hdc, rbx, ecx, &rect, DT_EDITCONTROL or DT_NOPREFIX)
                        mov rcx,rdi
                        sub rcx,rbx
                        mov rdi,rbx
                        xor eax,eax
                        rep stosb
                    .endw
                    .repeat
                        lodsb
                    .until !al
                .endw
                .endc
            .case ST_WORD   ; 6. W Word - match on all equal words
                SetTextColor(hdc, [rcx+rbx*4])
                .while byte ptr [rsi]
                    mov rdi,buffer
                    .while rdi < endbuf
                        _ltolowerA([rsi])
                        mov rcx,endbuf
                        sub rcx,rdi
                        shr ecx,1
                        .break .ifz
                        mov rbx,rdi
                        mov edx,ecx
                        repne scasw
                        .ifnz
                            mov ecx,edx
                            mov rdi,rbx
                            _ltoupperA([rsi])
                            repne scasw
                        .endif
                        .break .ifnz
                        lea rcx,[rdi-2]
                        .if rcx > buffer
                            .continue .if islabel([rcx-2])
                        .endif
                        mov rdx,rsi
                        mov rbx,rcx
                        .repeat
                            add rdx,1
                            add rcx,2
                            mov al,[rdx]
                            .break .if !al
                            .continue(0) .if al == [rcx]
                            mov ah,[rcx]
                            or  eax,0x2020
                            .continue(0) .if al == ah
                        .until 1
                        .continue .if al
                        .continue .if islabel([rcx])
                        mov rdi,rbx
                        mov rbx,rdx
                        sub rbx,rsi
                        mov rax,rdi
                        sub rax,buffer
                        shr eax,1
                        add eax,firstchar
                        SendMessage(hWnd, EM_POSFROMCHAR, &rect, eax)
                        DrawText(hdc, rdi, ebx, &rect, DT_EDITCONTROL or DT_NOPREFIX)
                        mov ecx,ebx
                        xor eax,eax
                        rep stosw
                    .endw
                    .repeat
                        lodsb
                    .until !al
                .endw
                .endc

              .case ST_NESTED
                ;
                ; 7. N Nested -- /* */
                ;
                .endc

            .endsw

            mov rsi,string
            .repeat
                lodsb
                .continue .if al
                lodsb
            .until !al
        .endw
    .until 1
    SelectObject(hdc, hOldRgn)
    DeleteObject(hRgn)
    ReleaseDC(hWnd, hdc)
    ret
    endp


InitProfile proc uses rsi rdi rbx
    lea rdi,Profile
    GetModuleFileName(hInstance, rdi, sizeof(Profile))
    lea rdi,[rdi+rax*TCHAR-3*TCHAR]
    lstrcpy(rdi, "ini")
    ret
    endp


RichEditProc proc uses rbx hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    .switch uMsg
    .case WM_PAINT
        mov ebx,CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam)
        HideCaret(hWnd)
        SetStyle(hWnd)
        ShowCaret(hWnd)
        mov eax,ebx
       .endc
    .case WM_CLOSE
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, OldWndProc)
       .endc
    .default
        CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam)
    .endsw
    ret
    endp


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
    endp


StreamInProc proc hFile:HANDLE, pBuffer:LPSTR, NumBytes:UINT, pBytesRead:LPDWORD
    ReadFile(hFile, pBuffer, NumBytes, pBytesRead, 0)
    xor eax,1
    ret
    endp


StreamOutProc proc hFile:HANDLE, pBuffer:LPSTR, NumBytes:UINT, pBytesWritten:LPDWORD
    WriteFile(hFile, pBuffer, NumBytes, pBytesWritten, 0)
    xor eax,1
    ret
    endp


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
    endp


OptionProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

  local clr:CHOOSECOLOR

    ldr eax,uMsg
    .switch eax
    .case WM_INITDIALOG
        mov eax,TRUE
       .endc
    .case WM_COMMAND
        mov rax,ldr(wParam)
        shr eax,16
        .if ax == BN_CLICKED
            mov rax,ldr(wParam)
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax == IDC_BACKCOLORBOX
                RtlZeroMemory(&clr, sizeof(clr))
                mov clr.lStructSize,sizeof(clr)
                mov clr.hwndOwner,hWnd
                mov clr.hInstance,hInstance
                mov clr.rgbResult,BackColor
                mov clr.lpCustColors,&SyntaxColors
                mov clr.Flags,CC_ANYCOLOR or CC_RGBINIT
                .if ChooseColor(&clr)
                    mov BackColor,clr.rgbResult
                    InvalidateRect(GetDlgItem(hWnd, IDC_BACKCOLORBOX), 0, TRUE)
                .endif
            .elseif ax==IDC_TEXTCOLORBOX
                RtlZeroMemory(&clr, sizeof(clr))
                mov clr.lStructSize,sizeof(clr)
                mov clr.hwndOwner,hWnd
                mov clr.hInstance,hInstance
                mov clr.rgbResult,TextColor
                mov clr.lpCustColors,&SyntaxColors
                mov clr.Flags,CC_ANYCOLOR or CC_RGBINIT
                .if ChooseColor(&clr)
                    mov TextColor,clr.rgbResult
                    InvalidateRect(GetDlgItem(hWnd, IDC_TEXTCOLORBOX), 0, TRUE)
                .endif
            .elseif ax==IDOK
                ;
                ; Save the modify state of the richedit control because changing
                ; the text color changes the modify state of the richedit control.
                ;
                ;SendMessage(hEdit, EM_GETMODIFY, 0, 0)
                ;push eax
                SetColor()
                ;pop eax
                ;SendMessage(hEdit, EM_SETMODIFY, eax, 0)
                EndDialog(hWnd, 0)
            .endif
        .endif
        mov eax,TRUE
       .endc
    .case WM_CTLCOLORSTATIC
        .if GetDlgItem(hWnd, IDC_BACKCOLORBOX) == lParam
            CreateSolidBrush(BackColor)
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
    endp


SearchProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    ldr eax,uMsg
    .switch eax
    .case WM_INITDIALOG
        mov hSearch,hWnd
        ;
        ; Select the default search down option
        ;
        CheckRadioButton(hWnd, IDC_DOWN, IDC_UP, IDC_DOWN)
        SendDlgItemMessage(hWnd, IDC_FINDEDIT, WM_SETTEXT, 0, &FindBuffer)
        mov eax,TRUE
       .endc
      .case WM_COMMAND
        mov rax,ldr(wParam)
        shr eax,16
        .if ax==BN_CLICKED
            mov rax,ldr(wParam)
            .if ax == IDOK
                mov uFlags,0
                SendMessage(hEdit, EM_EXGETSEL, 0, &findtext.chrg)
                .if GetDlgItemText(hWnd, IDC_FINDEDIT, &FindBuffer, sizeof(FindBuffer))
                    .if IsDlgButtonChecked(hWnd, IDC_DOWN) == BST_CHECKED
                        or uFlags,FR_DOWN
                        mov eax,findtext.chrg.cpMin
                        .if eax!=findtext.chrg.cpMax
                            mov findtext.chrg.cpMin,findtext.chrg.cpMax
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
                    mov findtext.lpstrText,&FindBuffer
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
        mov eax,TRUE    ; yes..
       .endc
      .default
        mov eax,FALSE
       .endc
    .endsw
    ret
    endp

ReplaceProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

  local settext:SETTEXTEX

    ldr eax,uMsg
    .switch eax
    .case WM_INITDIALOG
        mov hSearch,hWnd
        SetDlgItemText(hWnd, IDC_FINDEDIT,    &FindBuffer)
        SetDlgItemText(hWnd, IDC_REPLACEEDIT, &ReplBuffer)
        mov eax,TRUE
       .endc
    .case WM_COMMAND
        ldr rax,wParam
        shr eax,16
        .if ax == BN_CLICKED
            ldr rax,wParam
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax==IDOK
                GetDlgItemText(hWnd, IDC_FINDEDIT,    &FindBuffer, sizeof(FindBuffer))
                GetDlgItemText(hWnd, IDC_REPLACEEDIT, &ReplBuffer, sizeof(ReplBuffer))
                mov findtext.chrg.cpMin,0
                mov findtext.chrg.cpMax,-1
                mov findtext.lpstrText,&FindBuffer
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
        mov eax,TRUE    ; ...
       .endc
      .default
        mov eax,FALSE
    .endsw
    ret
    endp

GoToProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local LineNo:DWORD
    local chrg:CHARRANGE

    ldr eax,uMsg
    .switch eax
    .case WM_INITDIALOG
        mov hSearch,hWnd
        mov eax,TRUE
       .endc
    .case WM_COMMAND
        ldr rax,wParam
        shr eax,16
        .if ax == BN_CLICKED
            ldr rax,wParam
            .if ax == IDCANCEL
                SendMessage(hWnd, WM_CLOSE, 0, 0)
            .elseif ax == IDOK
                mov LineNo,GetDlgItemInt(hWnd, IDC_LINENO, NULL, FALSE)
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
        mov eax,TRUE    ; ...
       .endc
    .default
        mov eax,FALSE
    .endsw
    ret
    endp

WndProc proc uses rsi hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local buffer[256]:sbyte
  local hPopup:HMENU
  local pt:POINT
  local ofn:OPENFILENAME
  local hFile:HANDLE
  local editstream:EDITSTREAM
  local chrg:CHARRANGE

    .switch ldr(message)
    .case WM_CREATE
        .if !LoadLibrary("Msftedit.dll")
            PostQuitMessage(1)
            xor eax,eax
           .endc
        .endif
        mov hEdit,CreateWindowEx(WS_EX_CLIENTEDGE, MSFTEDIT_CLASS, 0,
                ES_MULTILINE or WS_VISIBLE or WS_CHILD or WS_BORDER or WS_VSCROLL or WS_HSCROLL or ES_NOHIDESEL,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                hWnd, RichEditID, hInstance, NULL)
        SendMessage(hEdit, EM_SETTYPOGRAPHYOPTIONS, TO_SIMPLELINEBREAK, TO_SIMPLELINEBREAK)
        SendMessage(hEdit, EM_GETTYPOGRAPHYOPTIONS, 1, 1)
        SendMessage(hEdit, EM_SETEDITSTYLE, SES_EMULATESYSEDIT, SES_EMULATESYSEDIT)
        mov OldWndProc,SetWindowLongPtr(hEdit, GWLP_WNDPROC, &RichEditProc)
        SendMessage(hEdit, EM_LIMITTEXT, -1, 0)
        SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
        SendMessage(hEdit, EM_SETEVENTMASK, 0, ENM_MOUSEEVENTS)
        SendMessage(hEdit, EM_EMPTYUNDOBUFFER, 0, 0)
        mov hFont,CreateFontIndirect(&AppFont)
        SendMessage(hEdit, WM_SETFONT, rax, 1)
        SetColor()
        xor eax,eax
       .endc

    .case WM_NOTIFY
        ldr rsi,lParam
        .if [rsi].NMHDR.code == EN_MSGFILTER
            .if [rsi].MSGFILTER.msg == WM_RBUTTONDOWN
                mov hPopup,GetSubMenu(GetMenu(hWnd), 1)
                PrepareEditMenu(rax)
                mov rdx,[rsi].MSGFILTER.lParam
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
            ; search menu bar
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
                mov ofn.lStructSize,sizeof(ofn)
                mov ofn.hwndOwner,hWnd
                mov ofn.hInstance,hInstance
                mov ofn.lpstrFilter,&ASMFilter
                mov ofn.lpstrFile,&FileName
                mov byte ptr [FileName],0
                mov ofn.nMaxFile,sizeof FileName
                mov ofn.Flags,OFN_FILEMUSTEXIST or OFN_HIDEREADONLY or OFN_PATHMUSTEXIST
                .if GetOpenFileName(&ofn)
                    .if CreateFile(&FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL, 0) != INVALID_HANDLE_VALUE
                        mov hFile,rax
                        mov editstream.dwCookie,rax
                        mov editstream.pfnCallback,&StreamInProc
                        SendMessage(hEdit, EM_STREAMIN, SF_TEXT, &editstream)
                        SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
                        CloseHandle(hFile)
                        mov FileOpened,TRUE
                    .else
                        MessageBox(hWnd, "Cannot open the file", &AppName, MB_OK or MB_ICONERROR)
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
                    mov editstream.pfnCallback,&StreamOutProc
                    SendMessage(hEdit, EM_STREAMOUT, SF_TEXT, &editstream)
                    SendMessage(hEdit, EM_SETMODIFY, FALSE, 0)
                    CloseHandle(hFile)
                .else
                    MessageBox(hWnd, "Cannot open the file", &AppName,  MB_OK or MB_ICONERROR)
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
            .case IDM_SAVEAS
                RtlZeroMemory(&ofn, sizeof(ofn))
                mov ofn.lStructSize,sizeof(ofn)
                mov ofn.hwndOwner,hWnd
                mov ofn.hInstance,hInstance
                mov ofn.lpstrFilter,&ASMFilter
                mov ofn.lpstrFile,&AltFileName
                mov AltFileName,0
                mov ofn.nMaxFile,sizeof AltFileName
                mov ofn.Flags,OFN_FILEMUSTEXIST or OFN_HIDEREADONLY or OFN_PATHMUSTEXIST
                .if GetSaveFileName(&ofn)
                    .if CreateFile(&AltFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0) != INVALID_HANDLE_VALUE

                        mov hFile,rax
                        mov editstream.dwCookie,rax
                        mov editstream.pfnCallback,&StreamOutProc
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
                        mov findtext.chrg.cpMin,findtext.chrg.cpMax
                    .endif
                    mov findtext.chrg.cpMax,-1
                    mov findtext.lpstrText,&FindBuffer

                    .if SendMessage(hEdit, EM_FINDTEXTEX, FR_DOWN, &findtext) != -1
                        SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    .endif
                .endif
                .endc
            .case IDM_FINDPREV
                .if FindBuffer
                    SendMessage(hEdit, EM_EXGETSEL, 0, &findtext.chrg)
                    mov findtext.chrg.cpMax,0
                    mov findtext.lpstrText,&FindBuffer

                    .if SendMessage(hEdit, EM_FINDTEXTEX, 0, &findtext) != -1
                        SendMessage(hEdit, EM_EXSETSEL, 0, &findtext.chrgText)
                    .endif
                .endif
                .endc
            .case IDM_FONT
                DLGSelectFont(hWnd)
               .endc
            .case IDM_COLOR
                DialogBoxParam(hInstance, IDD_OPTIONDLG, hWnd, &OptionProc, 0)
               .endc
            .case IDM_STATUSBAR
                MessageBox(hEdit, "Status Bar", "View", MB_OK)
               .endc
            .case IDM_VIEWHELP
                MessageBox(hEdit, "View Help", "Help", MB_OK)
               .endc
            .case IDM_ABOUT
                MessageBox(hEdit, "About", "Help", MB_OK)
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
        ldr rax,lParam
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
    endp

_tWinMain proc WINAPI hInst:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX
  local msg:MSG
  local hwnd:HANDLE

    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,     &WndProc
    mov wc.cbClsExtra,      0
    mov wc.cbWndExtra,      0
    mov hInstance,          hInst
    mov wc.hInstance,       hInst
    mov wc.hbrBackground,   COLOR_WINDOW+1
    mov wc.lpszMenuName,    IDR_MAINMENU
    mov wc.lpszClassName,   &@CStr("TestClass")
    mov wc.hIcon,           LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,         rax
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)
    RegisterClassEx(&wc)
ifdef _WIN64
    lea r15,_ltype
endif
    InitProfile()
    ReadStyle(&Profile)
    ReadConfig(&Profile)
    mov ecx,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0, "TestClass", "Testpad", WS_OVERLAPPEDWINDOW,
        ecx, ecx, ecx, ecx, 0, 0, hInstance, 0)

    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)
    mov hAccel,LoadAccelerators(hInstance, IDR_MAINACCEL)
    .whiled GetMessage(&msg, 0, 0, 0)
        .ifd !TranslateAccelerator(hwnd, hAccel, &msg)
            TranslateMessage(&msg)
            DispatchMessage(&msg)
        .endif
    .endw
    mov rax,msg.wParam
    ret
    endp

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
        SEPARATOR
        MENUITEM IDM_COPY,   IDS_COPY
        MENUITEM IDM_CUT,    IDS_CUT
        MENUITEM IDM_PASTE,  IDS_PASTE
        MENUITEM IDM_DELETE, IDS_DELETE
        SEPARATOR
        MENUITEM IDM_FIND,     IDS_FIND
        MENUITEM IDM_FINDNEXT, IDS_FINDNEXT
        MENUITEM IDM_FINDPREV, IDS_FINDPREV
        MENUITEM IDM_REPLACE,  IDS_REPLACE
        MENUITEM IDM_GOTOLINE, IDS_GOTO
        SEPARATOR
        MENUITEM IDM_SELECTALL, IDS_SELECTALL, MF_END
      MENUNAME IDS_FORMAT
        MENUITEM IDM_FONT,     IDS_FONT
        MENUITEM IDM_COLOR,    IDS_COLOR, MF_END
      MENUNAME IDS_VIEW
        MENUITEM IDM_STATUSBAR,IDS_STATUSBAR, MF_END
      MENUNAME IDS_HELP, MF_END
        MENUITEM IDM_VIEWHELP, IDS_VIEWHELP
        MENUITEM IDM_ABOUT,    IDS_ABOUT, MF_END
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

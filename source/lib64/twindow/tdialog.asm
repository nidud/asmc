; TDIALOG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include twindow.inc

    .code

    assume rcx:window_t
    assume rbx:window_t

TWindow::Inside proc pos:COORD

  local rc:TRECT

    mov eax,[rcx].rc
    .if ( [rcx].Flags & W_CHILD )

        mov r10,[rcx].PrevInst
        add ax,word ptr [r10].TWindow.rc
    .endif
    mov rc,eax

    xor eax,eax
    mov dh,rc.x
    .return .if dl < dh

    add dh,rc.col
    .return .if dl >= dh

    shr edx,16
    mov dh,rc.y
    .return .if dl < dh

    add dh,rc.row
    .return .if dl >= dh

    mov al,dl
    sub al,rc.y
    inc al
    ret

TWindow::Inside endp

TWindow::PushBSet proc uses rsi rdi rbx rcx
    mov     rbx,rcx
    mov     rcx,[rcx].PrevInst
    movzx   eax,[rbx].rc.x
    add     al,[rcx].rc.x
    mov     esi,eax
    mov     al,[rbx].rc.y
    add     al,[rcx].rc.y
    mov     edi,eax
    movzx   ecx,[rbx].rc.col
    lea     rcx,[rcx+rsi-1]
    _scputc(ecx, edi, 1, 0x11)
    _scputc(esi, edi, 1, 0x10)
    mov     rcx,rbx
    ret
TWindow::PushBSet endp

TWindow::PushBClear proc uses rsi rdi rbx
    mov     rbx,rcx
    mov     rcx,[rcx].PrevInst
    movzx   eax,[rbx].rc.x
    add     al,[rcx].rc.x
    mov     esi,eax
    mov     al,[rbx].rc.y
    add     al,[rcx].rc.y
    mov     edi,eax
    movzx   ecx,[rbx].rc.col
    lea     rcx,[rcx+rsi-1]
    _scputc(ecx, edi, 1, ' ')
    _scputc(esi, edi, 1, ' ')
    mov     rcx,rbx
    ret
TWindow::PushBClear endp

TWindow::PushBSetShade proc uses rsi rdi rbx rcx

    mov     rbx,rcx
    mov     rcx,[rcx].PrevInst
    movzx   eax,[rbx].rc.x
    add     al,[rcx].rc.x
    mov     esi,eax
    mov     al,[rbx].rc.y
    add     al,[rcx].rc.y
    mov     edi,eax
    mov     al,[rbx].rc.col
    lea     rcx,[rsi+rax]
    _scputc(ecx, edi, 1, 'Ü')
    lea     rcx,[rsi+1]
    movzx   r8d,[rbx].rc.col
    inc     edi
    _scputc(ecx, edi, r8d, 'ß')
    ret

TWindow::PushBSetShade endp

TWindow::PushBClrShade proc uses rsi rdi rbx rcx

    mov     rbx,rcx
    mov     rcx,[rcx].PrevInst
    movzx   eax,[rbx].rc.x
    add     al,[rcx].rc.x
    mov     esi,eax
    mov     al,[rbx].rc.y
    add     al,[rcx].rc.y
    mov     edi,eax
    mov     al,[rbx].rc.col
    lea     rcx,[rsi+rax]
    _scputc(ecx, edi, 1, ' ')
    lea     rcx,[rsi+1]
    movzx   r8d,[rbx].rc.col
    inc     edi
    _scputc(ecx, edi, r8d, ' ')
    ret

TWindow::PushBClrShade endp

TWindow::PushBCreate proc uses rsi rdi rbx rcx rc:TRECT, id:uint_t, name:string_t

    mov     rsi,r9
    mov     rbx,[rcx].Child(edx, r8d, T_PUSHBUTTON)
    .return .if !rax

    mov     rdi,[rbx].Window()
    movzx   ecx,[rbx].rc.col
    mov     rdx,[rbx].Color
    movzx   eax,byte ptr [rdx+BGPUSHBUTTON]
    or      al,[rdx+FGTITLE]
    shl     eax,16
    mov     al,' '
    mov     r11,rdi
    rep     stosd
    mov     al,[rdi+2]
    and     eax,0xF0
    or      al,[rdx+FGPBSHADE]
    shl     eax,16
    mov     al,'Ü'
    mov     [rdi],eax
    lea     rdi,[r11+r8*4+4]
    movzx   ecx,[rbx].rc.col
    mov     al,'ß'
    rep     stosd
    lea     rdi,[r11+8]
    mov     al,byte ptr [rdx+BGPUSHBUTTON]
    mov     cl,al
    or      al,[rdx+FGTITLE]
    or      cl,[rdx+FGTITLEKEY]
    shl     eax,16
    .while 1
        lodsb
        .break .if !al
        .if al != '&'
            stosd
            .continue(0)
        .else
            lodsb
            .break .if !al
            mov [rdi],ax
            mov [rdi+2],cl
            add rdi,4
            and al,not 0x20
            mov byte ptr [rbx].SysKey,al
        .endif
    .endw
    mov eax,1
    ret

TWindow::PushBCreate endp

    assume r10:context_t

TWindow::OnLButtonDown proc uses rcx uiMsg:uint_t, wParam:size_t, lParam:ptr

    .ifd ( [rcx].Inside(r8d) == 0 )

        .return [rcx].PostQuit(0) .if !( [rcx].Flags & W_CHILD )
        .return 1
    .endif

    lea r10,[rcx].Context
    .switch [rcx].Type
      .case T_NORMAL
        .if ( eax > 1 )
            mov rcx,[rcx].Child
            .return [rcx].Send(WM_LBUTTONDOWN, r8, r9) .if rcx
            .return 1
        .endif
        mov [r10].State,1
        mov [r10].Flags,0
        mov [r10].rc.x,r8b
        sub r8b,[rcx].rc.x
        mov [r10].x,r8b
        shr r8d,16
        mov [r10].rc.y,r8b
        sub r8b,[rcx].rc.y
        mov [r10].y,r8b
        .endc .if !( [rcx].Flags & W_SHADE )
        mov [r10].Flags,1
        [rcx].ClrShade()
        and [rcx].Flags,not W_SHADE
        .endc
      .case T_PUSHBUTTON
        mov [r10].State,1
        [rcx].PushBClrShade()
        [rcx].SetFocus([rcx].Index)
        .endc
      .case T_RADIOBUTTON
      .case T_CHECKBOX
        .endc
      .case T_XCELL
        [rcx].SetFocus([rcx].Index)
        .endc
      .case T_EDIT
      .case T_MENUS
      .case T_XHTML
      .case T_MOUSE
      .case T_SCROLLUP
      .case T_SCROLLDOWN
      .case T_TEXTBUTTON
        .endc
    .endsw
    xor eax,eax
    ret

TWindow::OnLButtonDown endp

TWindow::OnLButtonUp proc uses rcx uiMsg:uint_t, wParam:size_t, lParam:ptr

    lea r10,[rcx].Context
    .switch [rcx].Type
      .case T_NORMAL
        .if ( [r10].State == 0 )
            mov rcx,[rcx].Child
            .return [rcx].Send(edx, r8, r9) .if rcx
            .return 1
        .endif
        mov [r10].State,0
        .if ( [r10].Flags )
            or [rcx].Flags,W_SHADE
            [rcx].SetShade()
        .endif
        .endc
      .case T_PUSHBUTTON
        .return 1 .if ( [r10].State == 0 )
        mov [r10].State,0
        [rcx].PushBSetShade()
        xor edx,edx
        test [rcx].Flags,O_DEXIT
        cmovz edx,[rcx].Index
        .return [rcx].PostQuit(edx)
      .case T_RADIOBUTTON
        .return 1 .if ( [r10].State == 0 )
        mov [r10].State,0
        .endc
      .case T_CHECKBOX
      .case T_XCELL
      .case T_EDIT
      .case T_MENUS
      .case T_XHTML
      .case T_MOUSE
      .case T_SCROLLUP
      .case T_SCROLLDOWN
      .case T_TEXTBUTTON
        .return 1
    .endsw
    xor eax,eax
    ret

TWindow::OnLButtonUp endp

TWindow::OnMouseMove proc uiMsg:uint_t, wParam:size_t, lParam:ptr

    lea r10,[rcx].Context
    xor eax,eax

    .return .if ( [r10].State == 0 )
    .return .if ( [rcx].Flags & W_CHILD )

    movzx edx,[r10].rc.y
    shl edx,16
    mov dl,[r10].rc.x
    .return .if ( edx == eax )

    movsx eax,[r10].x
    movzx edx,r8b
    .if edx >= eax
        sub edx,eax
    .else
        xor edx,edx
    .endif
    shr r8d,16
    movsx eax,[r10].y
    .if r8d >= eax
        sub r8d,eax
    .else
        xor r8d,r8d
    .endif
    [rcx].Move(edx, r8d)
    xor eax,eax
    ret

TWindow::OnMouseMove endp

    assume r10:nothing

TWindow::OnSetFocus proc uses rcx

    [rcx].CursorGet()
    [rcx].CursorOn()

    .switch [rcx].Type
      .case T_PUSHBUTTON
        [rcx].CursorOff()
        [rcx].PushBSet()
        .endc
      .case T_RADIOBUTTON
      .case T_CHECKBOX
        .endc
      .case T_XCELL
        mov edx,[rcx].rc
        mov rax,[rcx].PrevInst
        add dx,word ptr [rax].TWindow.rc
        mov [rcx].Window,[rcx].Open(edx, 0)
        .endc .if !rax
        mov rcx,rax
        [rcx].Read()
        or [rcx].Flags,W_VISIBLE
        mov rdx,[rcx].Color
        mov r9b,[rdx+BGINVERSE]
        shr r9b,4
        movzx eax,[rcx].rc.x
        movzx edx,[rcx].rc.y
        movzx r8d,[rcx].rc.col
        _scputbg(eax, edx, r8d, r9b)
        .endc
      .case T_EDIT
      .case T_MENUS
      .case T_XHTML
      .case T_MOUSE
      .case T_SCROLLUP
      .case T_SCROLLDOWN
      .case T_TEXTBUTTON
        .endc
    .endsw
    xor eax,eax
    ret

TWindow::OnSetFocus endp

TWindow::OnKillFocus proc uses rbx rcx

    [rcx].CursorSet()

    .switch [rcx].Type
      .case T_PUSHBUTTON
        [rcx].PushBClear()
        .endc
      .case T_RADIOBUTTON
      .case T_CHECKBOX
        .endc
      .case T_XCELL
        mov rax,[rcx].Window
        .endc .if !rax
        mov edx,[rcx].rc
        mov r10,[rcx].PrevInst
        add dx,word ptr [r10].TWindow.rc
        mov rbx,rcx
        mov rcx,rax
        mov [rcx].rc,edx
        [rcx].Release()
        xor eax,eax
        mov [rbx].Window,rax
        .endc
      .case T_EDIT
      .case T_MENUS
      .case T_XHTML
      .case T_MOUSE
      .case T_SCROLLUP
      .case T_SCROLLDOWN
      .case T_TEXTBUTTON
        .endc
    .endsw
    xor eax,eax
    ret

TWindow::OnKillFocus endp

TWindow::OnChar proc uses rcx uiMsg:uint_t, wParam:size_t, lParam:ptr

    .if ( [rcx].Flags & W_CHILD )

        .if ( r8d == VK_RETURN )

            mov rax,[rcx].PrevInst
            mov eax,[rax].TWindow.Index

            .if ( eax == [rcx].Index )

                    xor edx,edx
                   test [rcx].Flags,O_DEXIT
                  cmovz edx,eax
                .return [rcx].PostQuit(edx)
            .endif
        .endif

    .else

        .switch r8d
          .case VK_ESCAPE
            .return [rcx].PostQuit(0)
          .case VK_UP
            [rcx].PrevItem()
            .return 0
          .case VK_DOWN
          .case VK_TAB
            [rcx].NextItem()
            .return 0
        .endsw
        mov rcx,[rcx].Child
        .return [rcx].Send(edx, r8, r9) .if rcx
    .endif
    mov eax,1
    ret

TWindow::OnChar endp

TWindow::OnSysChar proc uses rcx uiMsg:uint_t, wParam:size_t, lParam:ptr

    .if ( [rcx].Flags & W_CHILD )

        .if ( r8d == [rcx].SysKey )

            [rcx].SetFocus([rcx].Index)
            .return 0
        .endif
    .else
        mov rcx,[rcx].Child
        .return [rcx].Send(edx, r8, r9) .if rcx
    .endif
    mov eax,1
    ret

TWindow::OnSysChar endp

TWindow::ItemProc proc uiMsg:uint_t, wParam:size_t, lParam:ptr
    .switch edx
      .case WM_SETFOCUS
        .return [rcx].OnSetFocus()
      .case WM_KILLFOCUS
        .return [rcx].OnKillFocus()
      .case WM_LBUTTONDOWN
        .return [rcx].OnLButtonDown(edx, r8, r9)
      .case WM_LBUTTONUP
        .return [rcx].OnLButtonUp(edx, r8, r9)
      .case WM_SYSCHAR
        .return [rcx].OnSysChar(edx, r8, r9)
      .case WM_CHAR
        .return [rcx].OnChar(edx, r8, r9)
    .endsw
    mov eax,1
    ret
TWindow::ItemProc endp

TWindow::Child proc uses rdi rbx rcx rc:TRECT, id:uint_t, type:uint_t

    mov edi,r9d
    mov ebx,r8d

    .return .if ( [rcx].Open(edx, W_CHILD or W_WNDPROC) == NULL )

    mov [rax].TWindow.Index,ebx
    mov [rax].TWindow.Type,edi
    mov rbx,rax
    lea rax,TWindow_ItemProc
    mov [rbx].WndProc,rax

    .for ( rcx = [rbx].PrevInst : [rcx].Child : rcx = [rcx].Child )

    .endf
    mov [rcx].Child,rbx
    mov rax,rbx
    ret

TWindow::Child endp

TWindow::Window proc uses rbx rdx

    mov     rbx,rcx
    test    [rcx].Flags,W_CHILD
    cmovnz  rbx,[rcx].PrevInst
    movzx   eax,[rcx].rc.y
    movzx   r8d,[rbx].rc.col
    mul     r8d
    movzx   edx,[rcx].rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rbx].Window
    ret

TWindow::Window endp

TWindow::Focus proc uses rcx

    test    [rcx].Flags,W_CHILD
    cmovnz  rcx,[rcx].PrevInst
    mov     eax,[rcx].Index

    .for ( rcx = [rcx].Child : rcx : rcx = [rcx].Child )

        .return rcx .if ( eax == [rcx].Index )
    .endf
    xor eax,eax
    ret

TWindow::Focus endp

TWindow::SetFocus proc uses rbx rcx id:uint_t

    mov ebx,edx
    [rcx].KillFocus()
    test [rcx].Flags,W_CHILD
    cmovnz rcx,[rcx].PrevInst
    mov [rcx].Index,ebx
    .if [rcx].Focus()
        mov rcx,rax
        [rcx].Send(WM_SETFOCUS, 0, 0)
    .endif
    ret

TWindow::SetFocus endp

TWindow::KillFocus proc uses rcx

    mov rcx,[rcx].Focus()
    .if rcx
        [rcx].Send(WM_KILLFOCUS, 0, 0)
    .endif
    ret

TWindow::KillFocus endp

TWindow::NextItem proc uses rcx

    .return .if ![rcx].Focus()

    mov rcx,[rax].TWindow.Child
    .if rcx == NULL
        mov rcx,[rax].TWindow.PrevInst
        mov rcx,[rcx].Child
        .return .if !rcx
    .endif
    [rcx].SetFocus([rcx].Index)
    ret

TWindow::NextItem endp

TWindow::PrevItem proc uses rbx rcx

    test    [rcx].Flags,W_CHILD
    cmovnz  rcx,[rcx].PrevInst
    mov     eax,[rcx].Index

    .for ( rbx = [rcx].Child : rbx : rcx = rbx, rbx = [rbx].Child )

        .break .if ( eax == [rbx].Index )
    .endf
    .return .if !rbx
    .if !( [rcx].Flags & W_CHILD )
        .for ( : [rcx].Child : rcx = [rcx].Child )

        .endf
    .endif
    [rcx].SetFocus([rcx].Index)
    ret

TWindow::PrevItem endp

    end

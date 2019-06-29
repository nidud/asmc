; TMESSAGEBOX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include twindow.inc

    .code

    assume rcx:window_t

WndProc proc private hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .switch edx
      .case WM_ENTERIDLE
        Sleep(4)
        .return 0
      .case WM_CREATE
        [rcx].Show()
        [rcx].SetFocus([rcx].Index)
        .return 0
      .case WM_CLOSE
        .return [rcx].Release()
      .case WM_LBUTTONDOWN
        .return [rcx].OnLButtonDown(edx, r8, r9)
      .case WM_LBUTTONUP
        .return [rcx].OnLButtonUp(edx, r8, r9)
      .case WM_MOUSEMOVE
        .return [rcx].OnMouseMove(edx, r8, r9)
      .case WM_SYSCHAR
        .return [rcx].OnSysChar(edx, r8, r9)
      .case WM_CHAR
        .return [rcx].OnChar(edx, r8, r9)
    .endsw
    mov eax,1
    ret

WndProc endp

    assume rbx:window_t

TWindow::MessageBox proc uses rsi rdi rbx rcx flags:int_t, title:string_t, format:string_t, argptr:vararg

  local width:int_t
  local line:int_t
  local size:COORD
  local rc:TRECT

    mov rbx,rcx
    mov rdi,r8
    lea rsi,_bufin
    mov line,0

    vsprintf(rsi, r9, &argptr)
    mov width,strlen(rdi)

    .if byte ptr [rsi]
        .repeat
            .break .if !strchr(rsi, 10)
            mov rdx,rax
            sub rdx,rsi
            lea rsi,[rax+1]
            .if edx >= width
                mov width,edx
            .endif
            inc line
        .until line == 17
    .endif
    .ifd strlen(rsi) >= width
        mov width,eax
    .endif

    mov size,[rbx].ConsoleSize()
    mov eax,width

    mov dl,2
    mov dh,76
    .if al && al < 70
        mov dh,al
        add dh,8
        mov dl,80
        sub dl,dh
        shr dl,1
    .endif
    .if dh < 48
        mov dl,16
        mov dh,48
    .endif

    mov rc.x,dl
    mov rc.y,7
    mov ecx,line
    add cl,6
    mov rc.row,cl
    mov rc.col,dh
    add al,7
    .if ax > size.y
        mov rc.y,1
    .endif

    mov rbx,[rbx].Open(rc, W_MOVEABLE or W_SHADE or W_COLOR)
    .return .if !rax

    mov edx,((BGDIALOG-16) shl 4) or FGDIALOG
    mov eax,flags
    and eax,0x000000F0
    .if eax == MB_ICONERROR
        mov dl,((BGERROR-16) shl 4) or FGDESKTOP
        .if ( rdi == NULL )
            lea rdi,@CStr("Error")
        .endif
    .elseif eax == MB_ICONWARNING
        mov dl,((BGERROR-16) shl 4) or FGDESKTOP
        .if ( rdi == NULL )
            lea rdi,@CStr("Warning")
        .endif
    .endif
    shl edx,16
    mov dl,' '
    [rbx].Clear(edx)
    [rbx].PutTitle(rdi)

    mov eax,[rbx].rc
    mov rc,eax
    mov al,rc.row
    mov rc.row,1
    sub al,2
    mov rc.y,al
    mov al,rc.col
    shr al,1
    mov ecx,flags
    and ecx,0x0000000F

    .switch ecx
      .case MB_OK
        sub al,4
        mov rc.x,al
        mov rc.col,6
        [rbx].PushBCreate(rc, IDOK, "&Ok")
        .endc
      .case MB_OKCANCEL
        sub al,10
        mov rc.x,al
        mov rc.col,6
        [rbx].PushBCreate(rc, IDOK, "&Ok")
        mov rc.col,10
        add rc.x,9
        [rbx].PushBCreate(rc, IDCANCEL, "&Cancel")
        .endc
      .case MB_ABORTRETRYIGNORE
        sub al,17
        mov rc.x,al
        mov rc.col,9
        [rbx].PushBCreate(rc, IDABORT, "&Abort")
        mov rc.col,9
        add rc.x,12
        [rbx].PushBCreate(rc, 0, "&Retry")
        mov rc.col,10
        add rc.x,12
        [rbx].PushBCreate(rc, IDIGNORE, "&Ignore")
        .endc
      .case MB_YESNOCANCEL
        sub al,15
        mov rc.x,al
        mov rc.col,7
        [rbx].PushBCreate(rc, IDYES, "&Yes")
        mov rc.col,6
        add rc.x,10
        [rbx].PushBCreate(rc, IDNO, "&No")
        mov rc.col,10
        add rc.x,9
        [rbx].PushBCreate(rc, IDCANCEL, "&Cancel")
        .endc
      .case MB_YESNO
        sub al,10
        mov rc.x,al
        mov rc.col,7
        [rbx].PushBCreate(rc, IDYES, "&Yes")
        mov rc.col,6
        add rc.x,10
        [rbx].PushBCreate(rc, IDNO, "&No")
        .endc
      .case MB_RETRYCANCEL
        sub al,8
        mov rc.x,al
        mov rc.col,10
        [rbx].PushBCreate(rc, IDRETRY, "&Retry")
        mov rc.col,10
        add rc.x,13
        [rbx].PushBCreate(rc, IDCANCEL, "&Cancel")
        .endc
      .case MB_CANCELTRYCONTINUE
        sub al,21
        mov rc.x,al
        mov rc.col,10
        [rbx].PushBCreate(rc, IDCANCEL, "&Cancel")
        mov rc.col,13
        add rc.x,13
        [rbx].PushBCreate(rc, IDTRYAGAIN, "&Try Again")
        mov rc.col,12
        add rc.x,16
        [rbx].PushBCreate(rc, IDCONTINUE, "C&ontinue")
        .endc
    .endsw

    mov eax,flags
    and eax,0x00000300
    mov rcx,[rbx].Child
    .switch eax
      .case MB_DEFBUTTON4 : mov rcx,[rcx].Child
      .case MB_DEFBUTTON3 : mov rcx,[rcx].Child
      .case MB_DEFBUTTON2 : mov rcx,[rcx].Child
    .endsw
    mov [rbx].Index,[rcx].Index
    lea rsi,_bufin
    mov rdi,rsi
    mov line,2
    .repeat
        .break .if !byte ptr [rsi]
        mov rsi,strchr(rdi, 10)
        .if ( rax != NULL )
            mov byte ptr [rsi],0
            inc rsi
        .endif
        movzx r9d,[rbx].rc.col
        movzx edx,[rbx].rc.x
        [rbx].PutCenter(0, line, r9d, rdi)
        mov rdi,rsi
        inc line
    .until (rdi == NULL || line == 17+2)
    [rbx].Register(&WndProc)
    ret

TWindow::MessageBox endp

    end

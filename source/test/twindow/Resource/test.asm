
include twindow.inc

extern IDD_EditColor:resource_t

    .code

    assume rcx:window_t
    assume rbx:window_t
    assume r12:window_t

OnPaint proc private uses rsi rdi rbx r12 hwnd:window_t

    local x:int_t
    local y:int_t

    .return .if ![rcx].Open([rcx].rc, W_COLOR)

    mov rbx,rcx
    mov r12,rax

    .if [rcx].GetFocus()

        mov rcx,rax
        [rcx].Send(WM_KILLFOCUS, 0, 0)
    .endif

    [r12].Load(IDD_EditColor)
    or [r12].Flags,W_VISIBLE

    mov rsi,[rbx].Color
    mov rcx,[rbx].Child

    xor eax,eax
    mov al,[rcx].rc.x
    add al,2
    mov x,eax
    mov al,[rcx].rc.y
    mov y,eax

    .for ( edi = 0 : edi < 16 : edi++ )

        movzx eax,byte ptr [rsi+rdi]
        [r12].PutString(x, y, 0, 3, "%X", eax)
        add x,5
        mov al,[rsi+rdi]
        .switch rdi
          .case 0x0
          .case 0xD
            or al,[rsi+BG_TITLE]
            .endc
          .case 0x1
          .case 0x2
          .case 0x3
          .case 0x4
          .case 0xA
          .case 0xB
            or al,[rsi+BG_PANEL]
            .endc
          .case 0x5
          .case 0x6
          .case 0x8
          .case 0x9
          .case 0xE
            or al,[rsi+BG_DIALOG]
            .endc
          .case 0x7
            or al,[rsi+BG_DESKTOP]
            .endc
          .case 0xC
          .case 0xF
            or al,[rsi+BG_MENUS]
            .endc
        .endsw
        shl eax,16
        [rcx].PutChar(x, y, 13, eax)
        add x,42
        mov eax,edi
        or  al,((BG_DIALOG-16) shl 4)
        shl eax,16
        [rcx].PutChar(x, y, 1, eax)
        sub x,47
        inc y
    .endf

    mov rcx,[rbx].GetItem(17)
    xor eax,eax
    mov al,[rcx].rc.x
    add al,2
    mov x,eax
    mov al,[rcx].rc.y
    mov y,eax

    .for ( edi = 0 : edi < 14 : edi++ )

        movzx eax,byte ptr [rsi+rdi+16]
        shr   al,4
        [r12].PutString(x, y, 0, 3, "%X", eax)
        mov al,[rsi+rdi+16]
        .switch rdi
          .case 0x0
            or al,[rsi+FG_DESKTOP]
            .endc
          .case 0x1
          .case 0x6
            or al,[rsi+FG_PANEL]
            .endc
          .case 0x2
          .case 0x4
          .case 0x7
          .case 0xA
          .case 0xB
            or al,[rsi+FG_DIALOG]
            .endc
          .case 0x3
            or al,[rsi+FG_MENUS]
            .endc
          .case 0x5
          .case 0x8
            or al,[rsi+FG_TITLE]
            .endc
          .case 0x9
            or al,[rsi+FG_FILES]
            .endc
          .case 0xC
          .case 0xE
            or al,[rsi+FG_TEXTVIEW]
            .endc
          .case 0xD
          .case 0xF
            or al,[rsi+FG_TEXTEDIT]
            .endc
        .endsw
        shl eax,16
        mov edx,x
        add edx,5
        [rcx].PutChar(edx, y, 13, eax)
        inc y
    .endf

    mov al,[rsi+FG_TEXTVIEW]
    [r12].PutString(x, y, 0, 3, "%X", eax)
    mov edx,x
    add edx,5
    mov al,[rsi+FG_TEXTVIEW]
    or  al,[rsi+BG_TEXTVIEW]
    shl eax,16
    [rcx].PutChar(edx, y, 13, eax)

    inc y
    mov al,[rsi+FG_TEXTEDIT]
    [rcx].PutString(x, y, 0, 3, "%X", eax)
    add x,5
    mov al,[rsi+FG_TEXTEDIT]
    or  al,[rsi+BG_TEXTEDIT]
    shl eax,16
    [rcx].PutChar(x, y, 13, eax)

    [rcx].Release()
    mov rcx,rbx
    [rcx].SetFocus([rcx].Index)
    xor eax,eax
    ret

OnPaint endp

    assume r12:nothing

OnPageUp proc private hwnd:window_t

    mov rdx,[rcx].Color
    mov eax,[rcx].Index
    dec eax

    .if eax < 16

        .if byte ptr [rdx+rax] < 0x0F

            inc byte ptr [rdx+rax]
        .endif

    .elseif eax < 30

        .if byte ptr [rdx+rax] < 0xF0

            add byte ptr [rdx+rax],0x10
        .endif

    .elseif eax < 32

        .if byte ptr [rdx+rax] < 0x0F

            inc byte ptr [rdx+rax]
        .endif
    .endif
    OnPaint(rcx)
    ret

OnPageUp endp

OnPageDn proc private hwnd:window_t

    mov rdx,[rcx].Color
    mov eax,[rcx].Index
    dec eax

    .if eax < 16

        .if byte ptr [rdx+rax] > 0x00

            dec byte ptr [rdx+rax]
        .endif

    .elseif eax < 30

        .if byte ptr [rdx+rax] > 0x0F

            sub byte ptr [rdx+rax],0x10
        .endif

    .elseif eax < 32

        .if byte ptr [rdx+rax] > 0x00

            dec byte ptr [rdx+rax]
        .endif
    .endif
    OnPaint(rcx)
    ret

OnPageDn endp

    assume rbx:nothing

WndProc proc private hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .switch edx
      .case WM_CHAR
        .return OnPageUp(rcx) .if ( r8d == VK_PRIOR )
        .return OnPageDn(rcx) .if ( r8d == VK_NEXT )
        .endc
      .case WM_CREATE
        [rcx].Show()
        OnPaint(rcx)
        [rcx].SetFocus(34)
        .return 0
      .case WM_CLOSE
        .if [rcx].GetFocus()
            mov rcx,rax
            [rcx].Send(WM_KILLFOCUS, 0, 0)
        .endif
        .return hwnd.Release()
    .endsw
    [rcx].DefWindowProc(edx, r8, r9)
    ret

WndProc endp


EditColor proc uses rcx hwnd:window_t

    mov rcx,[rcx].Resource(IDD_EditColor)
    [rcx].Register(&WndProc)
    ret

EditColor endp


cmain proc hwnd:window_t, argc:int_t, argv:array_t, environ:array_t

    EditColor(rcx)
    xor eax,eax
    ret

cmain endp

    end

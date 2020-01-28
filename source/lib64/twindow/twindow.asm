; TWINDOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include twindow.inc

    .data
    AttributesDefault label byte
        db 0x00,0x0F,0x0F,0x07,0x08,0x00,0x00,0x07,0x08,0x00,0x0A,0x0B,0x00,0x0F,0x0F,0x0F
        db 0x00,0x10,0x70,0x70,0x40,0x30,0x30,0x70,0x30,0x30,0x30,0x00,0x00,0x00,0x07,0x07

    .code

    assume rcx:window_t
    assume rbx:window_t

TWindow::TWindow proc uses rsi rdi rbx

  local ci: CONSOLE_SCREEN_BUFFER_INFO

    mov rdi,rcx
    mov rbx,malloc( TWindow + TClass + TWindowVtbl )
    .if rdi
        stosq
    .endif
    .return .if !rax

    mov rdi,rax
    mov ecx,(TWindow + TClass) / 8
    xor eax,eax
    rep stosq
    mov [rbx].lpVtbl,rdi
    lea rax,[rbx+TWindow]
    mov [rbx].Class,rax

    for q,<Open,Load,Resource,Release,Show,Hide,Move,Read,Write,Exchange,
           SetShade,ClrShade,Clear,PutFrame,PutChar,PutString,PutPath,PutCenter,PutTitle,
           MessageBox,CursorGet,CursorSet,CursorOn,CursorOff,CursorMove,
           Register,Send,Post,PostQuit,DefWindowProc,Child,Window,PushButton,
           GetFocus,SetFocus,GetItem,MoveConsole,SetConsole,SetMaxConsole,ConsoleSize,
           CGetChar,CPutChar,CPutString,CPutPath,CPutCenter,CPutBackground>

        lea rax,TWindow_&q
        stosq
        endm

    lea rax,AttributesDefault
    mov [rbx].Color,rax
    mov rsi,GetStdHandle(STD_OUTPUT_HANDLE)

    mov edi,0x00190050
    .if GetConsoleScreenBufferInfo(rsi, &ci)
        mov edi,ci.dwSize
    .endif

    mov     [rbx].Flags,W_ISOPEN or W_COLOR
    mov     [rbx].rc.x,0
    mov     [rbx].rc.y,0
    movzx   eax,di
    shr     edi,16
    mov     [rbx].rc.col,al
    mov     edx,edi
    mov     [rbx].rc.row,dl
    mul     edi
    mov     [rbx].Window,malloc(&[rax*4])

    .if ( rax == NULL )

        free(rbx)
        .return 0
    .endif

    mov rdi,[rbx].Class
    assume rdi:class_t

    mov [rdi].Console,rbx
    mov [rdi].Focus,1
    mov [rdi].StdIn,GetStdHandle(STD_INPUT_HANDLE)
    mov [rdi].StdOut,rsi
    mov [rdi].ErrMode,SetErrorMode(SEM_FAILCRITICALERRORS)

    GetConsoleMode([rdi].StdIn, &[rdi].ConMode)
    SetConsoleMode([rdi].StdIn, ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
    FlushConsoleInputBuffer([rdi].StdIn)
    [rbx].Read(&[rbx].rc, [rbx].Window)

    mov rax,rbx
    ret

TWindow::TWindow endp


TWindow::Release proc uses rbx

    mov rbx,rcx

    .if [rbx].Cursor

        free([rbx].Cursor)
    .endif

    xor eax,eax
    .if [rbx].Flags & W_CHILD

        .for ( rcx = [rbx].Prev : rcx && [rcx].Child != rbx : rcx = [rcx].Child )
        .endf
        .if rcx
            mov [rcx].Child,[rbx].Child
        .endif
        mov [rbx].Child,rax

    .elseif ( rax == [rbx].Prev )

        mov rax,[rbx].Class
        SetConsoleMode([rax].TClass.StdIn, [rax].TClass.ConMode)
        mov rax,[rbx].Class
        SetErrorMode([rax].TClass.ErrMode)
    .endif

    .while rbx
        .if [rbx].Flags & W_ISOPEN
            .if [rbx].Flags & W_VISIBLE
                [rbx].Hide()
            .endif
            free([rbx].Window)
        .endif
        mov rcx,rbx
        mov rbx,[rbx].Child
        free(rcx)
    .endw
    xor eax,eax
    ret

TWindow::Release endp

    end

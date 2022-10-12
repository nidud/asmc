; ASMCALC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
;
; This uses Asmc as a calculator
;

include twindow.inc
include malloc.inc
include string.inc
include io.inc
include stdio.inc
include stdlib.inc
include tchar.inc

    .enum Dialog {
        ID_TEXT,
        ID_7,
        ID_4,
        ID_1,
        ID_0,
        ID_8,
        ID_5,
        ID_2,
        ID_DOT,
        ID_9,
        ID_6,
        ID_3,
        ID_ADD,
        ID_DIV,
        ID_MUL,
        ID_SUB,
        ID_ENTER
        }

    .data

 TAttributesDefault TColor {{
        0x07,0x07,0x0F,0x07,0x08,0x08,0x07,0x06,0x08,0x07,0x0A,0x0B,0x0F,0x0B,0x0B,0x0B,
        0x00,0x00,0x00,0x10,0x30,0x10,0x30,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x07,0x07 }}

 Resource TRObject {
      0x0184,  32,     0, { 3, 3,34, 1} },
    { 0x0000,   0,   '7', { 4, 5, 5, 1} },
    { 0x0000,   0,   '4', { 4, 7, 5, 1} },
    { 0x0000,   0,   '1', { 4, 9, 5, 1} },
    { 0x0000,   0,   '0', { 4,11, 5, 1} },
    { 0x0000,   0,   '8', {13, 5, 5, 1} },
    { 0x0000,   0,   '5', {13, 7, 5, 1} },
    { 0x0000,   0,   '2', {13, 9, 5, 1} },
    { 0x0000,   0,   '.', {13,11, 5, 1} },
    { 0x0000,   0,   '9', {22, 5, 5, 1} },
    { 0x0000,   0,   '6', {22, 7, 5, 1} },
    { 0x0000,   0,   '3', {22, 9, 5, 1} },
    { 0x0000,   0,   '+', {22,11, 5, 1} },
    { 0x0000,   0,   '/', {31, 5, 5, 1} },
    { 0x0000,   0,   '*', {31, 7, 5, 1} },
    { 0x0000,   0,   '-', {31, 9, 5, 1} },
    { 0x0000,   0,   '=', {31,11, 5, 1} }


    .code

    option wstring:off

calculate proc uses rsi rdi rbx string:LPTSTR

   .new buffer:string_t = malloc(0x8000)

    mov rdi,rax
    mov rbx,rax
    lea rsi,@CStr("asmc -q -DT=\"")
    mov ecx,sizeof(@CStr(0))-1
    rep movsb
    mov rsi,string
    xor edx,edx

    .while ( TCHAR ptr [rsi] )

        movzx eax,TCHAR ptr [rsi]
        add rsi,TCHAR
        stosb

        .if ( ( eax > '9' || eax < '0' ) && ( eax != '.' ) )

            mov cl,[rdi-2]

            .if ( !edx && cl >= '0' && cl <= '9' )

                dec   rdi
                mov   cl,al
                mov   eax,'0.'
                stosw
                mov   al,cl
                stosb
            .endif
            xor edx,edx
        .elseif ( eax == '.' )
            inc edx
        .endif
    .endw
    .if ( rdi > rbx )

        mov cl,[rdi-1]
        .if ( !edx && cl >= '0' && cl <= '9' )

            mov eax,'0.'
            stosw
        .endif
    .endif
    mov eax,' "'
    stosw

    mov rsi,_pgmptr
    .if strrchr(rsi, '\')

        lea rcx,[rax+1]
        sub rcx,rsi
        rep movsb
    .endif

    lea rsi,@CStr("calculate.asm > result.txt")
    mov ecx,sizeof(@CStr(0))
    rep movsb

    mov rdi,string
    mov eax,'0'
    stosd

    xor edi,edi

    .if ( system(rbx) )

        Sleep(100)

        .if fopen("result.txt", "rt")

            mov rsi,rax
            mov edi,fread(rbx, 1, 0x8000-1, rsi)
            fclose(rsi)

            .if ( edi )

                mov ecx,edi
                mov rdi,string
                mov rsi,rbx
                xor eax,eax

                .repeat
                    movsb
                    stosb
                .untilcxz
                stosw
                sub rdi,4
                .while ( rdi > string && (
                         wchar_t ptr [rdi] == '0' ||
                         wchar_t ptr [rdi] == 0xA ||
                         wchar_t ptr [rdi] == 0xD ) )
                    mov [rdi],ax
                    sub rdi,2
                .endw
                .if ( wchar_t ptr [rdi] == '.' )
                    mov [rdi],ax
                    sub rdi,2
                .endif
            .endif
            remove("result.txt")
        .endif
    .endif
    free(rbx)

   .return(edi)

calculate endp

    option wstring:on

    assume rcx:ptr TWindow

OnPaint proc private uses rsi rdi this:ptr TWindow

   .new x:int_t
   .new y:int_t
   .new window:ptr TWindow

    mov window,this.Open([rcx].rc, W_COLOR)
   .return .if !rax

    .if this.GetFocus()
        [rax].TWindow.Send(WM_KILLFOCUS, 0, 0)
    .endif
    window.Release()

    mov rcx,this
    this.SetFocus([rcx].Index)
   .return 0

OnPaint endp


WndProc proc private uses rbx this:ptr TWindow, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .switch uiMsg

    .case WM_CHAR
        .switch word ptr wParam
        .case VK_PRIOR
        .case VK_NEXT
        .endsw
        .endc

    .case WM_CREATE
        this.Show()
        OnPaint(this)
        this.SetFocus(0)
       .return 0

    .case WM_CLOSE

        .if ( r8d )

            dec r8d
            .switch r8d
            .case ID_0
            .case ID_1
            .case ID_2
            .case ID_3
            .case ID_4
            .case ID_5
            .case ID_6
            .case ID_7
            .case ID_8
            .case ID_9
            .case ID_DIV
            .case ID_MUL
            .case ID_SUB
            .case ID_ADD
            .case ID_DOT
                imul    eax,r8d,TRObject
                lea     rdx,Resource
                movzx   r8d,[rdx+rax].TRObject.index
                shl     r8,32
                mov     rcx,[rcx].Child
                mov     rax,[rcx].Context.object
                [rax].TEdit.OnChar(rcx, r8)
               .endc

            .case ID_TEXT
            .case ID_ENTER
                mov rbx,[rcx].Child
                mov rax,[rbx].TWindow.Context.object
                calculate([rax].TEdit.base)
                mov rax,[rbx].TWindow.Context.object
                or [rax].TEdit.flags,O_MODIFIED
                [rax].TEdit.OnChar(rbx, VK_END)
               .endc
            .endsw
        .endif
        .return 0
    .endsw
    this.DefWindowProc(uiMsg, wParam, lParam)
    ret

WndProc endp

    assume rbx:ptr TWindow
    assume rsi:ptr TRObject

cmain proc uses rsi rdi rbx this:ptr TWindow, argc:int_t, argv:array_t, environ:array_t

   .new window:ptr TWindow
   .new wrect:RECT
   .new oldrc:TRect = [rcx].rc
   .new rc:TRect = { 0, 0, 42, 16 }

    GetWindowRect(GetConsoleWindow(), &wrect)

    this.MoveConsole(40, 20)
    this.SetConsole(rc.col, rc.row)

    mov window,this.Open(rc, W_COLOR)
    mov rcx,rax
    mov rax,[rcx].Color
    xor edx,edx
    xor ebx,ebx
    mov dl,[rax+BG_DIALOG]
    or  dl,[rax+FG_DIALOG]
    mov bl,[rax+BG_TEXTEDIT]
    or  bl,[rax+FG_TEXTEDIT]
    shl edx,16
    shl ebx,16
    mov bx,U_MIDDLE_DOT
    mov dl,' '
    window.Clear(edx)

    window.PutChar(Resource.rc.x, Resource.rc.y, Resource.rc.col, ebx)

    .for ( rsi = &Resource, edi = 0 : edi < lengthof(Resource) : edi++, rsi+=TRObject )

        .if ( edi == 0 )

            mov     r9w,[rsi].flags
            and     r9d,0x0F
            inc     r9d
            mov     rcx,window.Child([rsi].rc, edi, r9d)
            movzx   eax,[rsi].flags
            and     eax,0xFFF0
            shl     eax,4
            or      [rcx].Flags,eax
            movzx   r8d,[rsi].count
            shl     r8d,4

            TEdit::TEdit(0, rcx, r8d)
        .else
           .new ButtonName[2]:TCHAR = {0}

            mov ButtonName,[rsi].index
            window.PushButton([rsi].rc, edi, &ButtonName)
        .endif
    .endf

    .while window.Register(&WndProc)
    .endw
    window.Release()

    this.MoveConsole(wrect.left, wrect.top)
    mov edx,wrect.right
    sub edx,wrect.left
    inc edx
    mov ecx,wrect.top
    sub ecx,wrect.bottom
    inc ecx
    inc oldrc.col
    inc oldrc.row
    this.SetConsole(oldrc.col, oldrc.row)
   .return(0)

cmain endp

    end

; Doszip.asm--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include doszip.inc

define MOUSE_BUTTON_UP      0x0010
define MOUSE_BUTTON_DOWN    0x0020
define MOUSE_WHEEL_UP       0x0040
define MOUSE_WHEEL_DOWN     0x0080

define STARTYEAR   0
define MAXYEAR     3000

MKID macro T, I
    exitm<(I shl 16 or T)>
    endm

MKAT macro B, F, wC
ifnb <wC>
    exitm<(((B shl 4 or F) shl 16) or wC)>
else
    exitm<(B shl 4 or F)>
endif
    endm

SetClass proto watcall :PDWND {
    mov     rbx,rax
ifdef __DEBUG__
    mov     this,rax
endif
    }

GetWindowSize proto watcall :TRECT {
    mov     edx,eax
    shr     edx,24
    shr     eax,16
    movzx   eax,al
    mov     ecx,eax
    imul    eax,edx
    shl     eax,2
    }

KeyCtrl macro reg
    exitm<(reg & (RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED))>
    endm
KeyAlt macro reg
    exitm<(reg & (RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED))>
    endm
KeyShift macro reg
    exitm<reg & SHIFT_PRESSED>
    endm

.data?
 m_dz           PDWND ?
 m_B1           LPWSTR ?
 m_B2           LPWSTR ?
 m_B3           LPWSTR ?
 m_msgStack     Message MAXMESSAGE dup(<>)
 m_msgCount     dd ?
 m_dlgFocus     dd ?
 m_msButton     dd ?
 m_modeIn       dd ?
 m_idleId       dd ?

.data
 at_foreground  db 0x07,0x07,0x0F,0x07,0x08,0x08,0x07,0x07,
                   0x08,0x07,0x0A,0x0B,0x0F,0x0B,0x0B,0x0B
 at_background  db 0x00,0x00,0x00,0x10,0x30,0x10,0x30,0x70,
                   0x80,0x10,0x10,0x00,0x00,0x00,0x07,0x07
 at_Blue        db 0x00,0x0F,0x0F,0x07,0x08,0x00,0x00,0x07,
                   0x08,0x00,0x0A,0x0B,0x00,0x0F,0x0F,0x0F,
                   0x00,0x10,0x70,0x70,0x40,0x30,0x30,0x70,
                   0x80,0x30,0x30,0x30,0x10,0x10,0x07,0x06
 at_Black       db 0x07,0x07,0x0F,0x07,0x08,0x08,0x07,0x07,
                   0x08,0x07,0x0A,0x0B,0x0F,0x0B,0x0B,0x0B,
                   0x00,0x00,0x00,0x10,0x30,0x10,0x30,0x00,
                   0x10,0x10,0x00,0x00,0x00,0x00,0x07,0x07
 at_Mono        db 0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
                   0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
                   0x00,0x00,0x00,0x00,0x00,0x70,0x70,0x00,
                   0x70,0x70,0x70,0x00,0x00,0x00,0x0F,0x0F
 at_White       db 0x00,0x07,0x0F,0x07,0x08,0x07,0x00,0x07,
                   0x08,0x00,0x0A,0x0B,0x00,0x07,0x08,0x08,
                   0x00,0x10,0xF0,0xF0,0x40,0x70,0x70,0x70,
                   0x80,0x30,0x70,0x70,0x00,0x00,0x07,0x07
 at_Norton      db 0x07,0x0B,0x0B,0x0B,0x0B,0x00,0x00,0x07,
                   0x08,0x0F,0x0E,0x0B,0x0F,0x00,0x0E,0x0E,
                   0x00,0x10,0x30,0x30,0x40,0xF0,0x20,0x70,
                   0x80,0xF0,0x30,0x00,0x30,0x30,0x0F,0x0F
 cp_Month   LPWSTR @CStr(CP_JAN),
                   @CStr(CP_FEB),
                   @CStr(CP_MAR),
                   @CStr(CP_APR),
                   @CStr(CP_MAY),
                   @CStr(CP_JUN),
                   @CStr(CP_JUL),
                   @CStr(CP_AUG),
                   @CStr(CP_SEP),
                   @CStr(CP_OCT),
                   @CStr(CP_NOV),
                   @CStr(CP_DEC)
 cl_Keypos      db 1,5,9,13,17,21,25

.code

 assume class:rbx

 Doszip::WinProc proc uses rsi rdi uMsg:DWORD, wParam:WPARAM, lParam:LPARAM, vParam:VARARG

   .new u1:uint_t, u2, u3, u4
   .new rc:TRECT, r2, rl, rr
   .new Coord:COORD
   .new rect:SMALL_RECT
   .new p:LPSTR, q
   .new hwnd:PDWND
   .new Input:INPUT_RECORD
   .new msg:Message
   .new pMsg:PDMSG
   .new cu:CONSOLE_CURSOR_INFO
   .new ci:CONSOLE_SCREEN_BUFFER_INFO
   .new fp:LPFILE
   .new ft:FILETIME
   .new ts:SYSTEMTIME

    ldr edx,uMsg
    ldr rdi,wParam
    ldr rsi,lParam

    .switch jmp pascal rdx

    .case WP_CREATE

        ; wParam: COORD { Type, Id }
        ; lParam: PDWND { Base }
        ; return: PDWND

        mov Coord,edi
        mov rdi,[rbx]

        .new( Doszip, rdi )

        .if ( rax )

            mov     rdi,m_Base
            mov     rdx,m_Home
            mov     rbx,rax
            mov     m_Home,rdx
            movzx   edx,Coord.X
            movzx   ecx,Coord.Y
            mov     m_Id,ecx
            mov     m_Type,edx

            .if ( edx < CT_ITEMTYPE )

                mov m_Base,rdi
                mov Flags.Parent,1
                mov rbx,rdi
                lea rdx,m_Next
            .else
                mov m_Base,rsi
                mov Flags.Child,1
                mov rbx,rsi
                lea rdx,m_This
            .endif
            mov rcx,[rdx]
            .if ( rcx )
                .for ( rbx = rcx : m_Next : rbx = m_Next )
                .endf
                mov m_Next,rax
                mov [rax].Doszip.m_Prev,rbx
            .else
                mov [rdx],rax
            .endif
        .endif
        .return


    .case WP_DESTROY

        ; wParam: BOOL
        ; lParam: PDWND

        .if SetClass(rsi)

            mov rcx,m_Base
            mov rdx,m_Prev
            mov rsi,m_Next
            xor eax,eax
            mov m_Prev,rax
            mov m_Next,rax
            .if ( rsi )
                mov [rsi].Doszip.m_Prev,rdx
            .endif
            .if ( rdx )
                mov [rdx].Doszip.m_Next,rsi
            .endif
            .if ( rcx )
                .if ( rbx == [rcx].Doszip.m_This )
                    mov [rcx].Doszip.m_This,rsi
                .elseif ( rbx == [rcx].Doszip.m_Next )
                    mov [rcx].Doszip.m_Next,rsi
                .endif
            .endif
            .if ( Flags.Open )
                WinProc( WP_OPENWINDOW, FALSE, rbx )
            .endif
            .if ( Flags.Mybuf )
                free(m_Text)
            .endif
            .if ( m_This )
                WinProc( WP_DESTROY, TRUE, m_This )
            .endif
             free(rbx)
            .gotosw(WP_DESTROY) .if ( edi && rsi )
        .endif


    .case WP_NEW

        ; wParam: COORD { Type, Id }
        ; lParam: LPSTR { Section | Entry | Resource:PIDD }
        ; return: PDWND

        .if WinProc(WP_CREATE, edi, rbx)

            mov rbx,rax
            mov edi,m_Type

            .switch edi
            .case CT_FILE
                lea rax,Panel
                mov m_Text,rax
                mov ecx,[rsi]
                mov [rax],ecx
               .endc
            .case CT_ENTRY
            .case CT_SECTION
                mov Line.m_Count,strlen(rsi)
                inc eax
                .if ( eax > Doszip - Doszip.Panel )
                    mov Line.m_Size,eax
                    mov Flags.Mybuf,1
                    malloc(rax)
                .else
                    mov Line.m_Size,Doszip - Doszip.Panel
                    lea rax,Panel
                .endif
                .if ( rax )
                    mov m_Text,strcpy(rax, rsi)
                .endif
            .case CT_LINE
                mov     rcx,m_Home
                mov     rax,[rcx].Doszip.m_LBuf
                mov     rdx,[rcx].Doszip.m_TBuf
                mov     Line.m_LBuf,rax
                mov     Line.m_TBuf,rdx
               .endc
            .case CT_PANEL
                mov     m_Text,malloc(WMAXPATH*8)
                mov     Flags.Mybuf,1
                mov     Flags.Color,1
                mov     ecx,(WMAXPATH*8)/4
                mov     rdi,rax
                mov     Panel.m_srcPath,rax
                add     rax,WMAXPATH*2
                mov     Panel.m_arcPath,rax
                add     rax,WMAXPATH*2
                mov     Panel.m_srcMask,rax
                add     rax,WMAXPATH*2
                mov     Panel.m_arcFile,rax
                xor     eax,eax
                rep     stosd
               .endc
            .default
                .endc .if ( rsi == NULL )
                mov     m_Resource,rsi
                mov     ax,[rsi].RIDD.flags
                and     eax,W_MOVEABLE or W_SHADE or W_COLOR or W_HELP or W_TRANSPARENT
                or      eax,W_RESOURCE
                or      Flags,eax
                mov     eax,[rsi].RIDD.rc
                .switch edi
                .case CT_MENUBAR
                .case CT_TILEBAR
                    mov     rdx,m_Home
                    movzx   eax,[rdx].Doszip.m_rc.col
                    mov     ah,1
                    shl     eax,16
                   .endc
                .case CT_KEYBAR
                    mov     rdx,m_Home
                    movzx   eax,[rdx].Doszip.m_rc.col
                    mov     ah,1
                    shl     eax,16
                    mov     ah,[rdx].Doszip.m_rc.row
                    dec     ah
                .endsw
                mov m_rc,eax
            .endsw
            mov rax,rbx
        .endif
        .return


    .case WP_CURSOR

        ; wParam: BOOL

        mov cu.bVisible,edi
        mov cu.dwSize,CURSOR_NORMAL
        SetConsoleCursorInfo(_confh, &cu)


    .case WP_CURSORGET

        ; wParam: BOOL
        ; lParam: PCURSOR

        .ifd GetConsoleScreenBufferInfo(_confh, &ci)
            mov [rsi].CURSOR.x,ci.dwCursorPosition.X
            mov [rsi].CURSOR.y,ci.dwCursorPosition.Y
        .endif
        .ifd GetConsoleCursorInfo(_confh, &cu)
            mov [rsi].CURSOR.type,cu.dwSize
            mov [rsi].CURSOR.visible,cu.bVisible
        .endif
        .gotosw(WP_CURSOR)


    .case WP_CURSORSET

        ; lParam: PCURSOR

        movzx   edx,[rsi].CURSOR.y
        shl     edx,16
        mov     dl,[rsi].CURSOR.x
        SetConsoleCursorPosition(_confh, edx)
        movzx   eax,[rsi].CURSOR.type
        movzx   ecx,[rsi].CURSOR.visible
        mov     cu.dwSize,eax
        mov     cu.bVisible,ecx
        SetConsoleCursorInfo(_confh, &cu)


    .case WP_CURSORPOS

        ; wParam: BOOL
        ; lParam: COORD
        ; return: COORD

        .if ( edi )
            SetConsoleCursorPosition(_confh, esi)
        .else
            mov ci.dwCursorPosition,0
            GetConsoleScreenBufferInfo(_confh, &ci)
           mov esi,ci.dwCursorPosition
        .endif
        .return( esi )


    .case WP_SETCURSOR

        ; wParam: BOOL
        ; lParam: TRECT

        mov     ecx,esi
        add     cl,m_rc.x
        add     ch,m_rc.y
        mov     rbx,m_Base
        add     ch,m_rc.y
        add     cl,m_rc.x
        movzx   eax,cl
        movzx   ecx,ch
        shl     ecx,16
        or      ecx,eax
        SetConsoleCursorPosition(_confh, ecx)
       .gotosw(WP_CURSOR)


    .case WP_READCHARACTER

        ; wParam: TRECT
        ; return: WCHAR

        mov ecx,edi
        movzx eax,cl
        movzx edx,ch

        .if ( Flags.Child )

            add dl,m_rc.y
            add al,m_rc.x
            mov rbx,m_Base
        .endif

        .if ( Flags.Visible )

            add al,m_rc.x
            add dl,m_rc.y
            shl edx,16
            mov dl,al
            .ifd ReadConsoleOutputCharacterW(_confh, &u2, 1, edx, &u1)
                mov eax,u2
            .endif
        .else
            mov     ecx,eax
            movzx   eax,m_rc.col
            mul     edx
            add     eax,ecx
            shl     eax,2
            add     rax,m_Window
            movzx   eax,word ptr [rax]
        .endif
        .return

    .case WP_READATTRIBUTE

        ; wParam: TRECT
        ; return: WORD  { Attribute }

        mov ecx,edi
        movzx eax,cl
        movzx edx,ch

        .if ( Flags.Child )

            add dl,m_rc.y
            add al,m_rc.x
            mov rbx,m_Base
        .endif

        .if ( Flags.Visible )

            add al,m_rc.x
            add dl,m_rc.y
            shl edx,16
            mov dl,al
            .ifd ReadConsoleOutputAttribute(_confh, &u2, 1, edx, &u1)
                mov eax,u2
            .endif
        .else
            mov     ecx,eax
            movzx   eax,m_rc.col
            mul     edx
            add     eax,ecx
            shl     eax,2
            add     rax,m_Window
            movzx   eax,byte ptr [rax+2]
        .endif
        .return


    .case WP_FILLCHARACTER

        ; wParam: TRECT
        ; lParam: WCHAR { Unicode Char }
        ; return: DWORD { Number Written }

        mov     ecx,edi
        movzx   eax,cl
        movzx   edx,ch
        shr     ecx,16
        and     ecx,0xFF

        .if ( Flags.Child )

            add dl,m_rc.y
            add al,m_rc.x
            mov rbx,m_Base
        .endif

        .if ( Flags.Visible )

            add al,m_rc.x
            add dl,m_rc.y
            shl edx,16
            mov dl,al
            .ifd FillConsoleOutputCharacterW(_confh, si, ecx, edx, &u1)
                mov eax,u1
            .endif
        .else
            mov edi,eax
            mov eax,edx
            mul m_rc.col
            add eax,edi
            shl eax,2
            add rax,m_Window
            mov rdx,rax
            .for ( eax = 0 : eax < ecx : eax++, rdx+=4 )
                mov [rdx],si
            .endf
        .endif
        .return


    .case WP_FILLATTRIBUTE

        ; wParam: TRECT
        ; lParam: WORD  { Attribute }
        ; return: DWORD { Number Written }

        mov     ecx,edi
        movzx   eax,cl
        movzx   edx,ch
        shr     ecx,16
        and     ecx,0xFF

        .if ( Flags.Child )

            add dl,m_rc.y
            add al,m_rc.x
            mov rbx,m_Base
        .endif

        .if ( Flags.Color )

            mov u1,eax
            mov eax,esi
            and eax,0x0F
            shr esi,4
            lea rdi,at_foreground
            mov al,[rdi+rax]
            or  al,[rdi+rsi+16]
            mov esi,eax
            mov eax,u1
        .endif

        .if ( Flags.Visible )

            add al,m_rc.x
            add dl,m_rc.y
            shl edx,16
            mov dl,al
            .ifd FillConsoleOutputAttribute(_confh, si, ecx, edx, &u1)
                mov eax,u1
            .endif
        .else
            mov edi,eax
            mov al,m_rc.col
            mul edx
            add eax,edi
            shl eax,2
            add eax,2
            add rax,m_Window
            mov rdx,rax
            .for ( eax = 0 : eax < ecx : eax++, rdx+=4 )
                mov [rdx],si
            .endf
        .endif
        .return


    .case WP_FILLFOREGROUND

        ; wParam: TRECT
        ; lParam: WORD  { Attribute }
        ; return: DWORD { Number Written }

        mov ecx,edi

        .if ( Flags.Child )

            add ch,m_rc.y
            add cl,m_rc.x
            mov rbx,m_Base
        .endif

        .if ( Flags.Color )

            lea rax,at_foreground
            movzx esi,byte ptr [rsi+rax]
        .endif

        .if ( Flags.Visible )

            add cl,m_rc.x
            add ch,m_rc.y
            mov rc,ecx

            .for ( edi = 0 : rc.col : rc.col--, rc.x++ )

                movzx   edx,rc.y
                shl     edx,16
                mov     dl,rc.x

                .break .ifd !ReadConsoleOutputAttribute(_confh, &u2, 1, edx, &u1)

                mov     ecx,u2
                and     ecx,0xF0
                or      ecx,esi
                movzx   edx,rc.y
                shl     edx,16
                mov     dl,rc.x

                .break .ifd !FillConsoleOutputAttribute(_confh, cx, 1, edx, &u1)
                inc     edi
            .endf
            .return( edi )
        .endif

        movzx   eax,cl
        movzx   edx,ch
        shr     ecx,16
        and     ecx,0xFF
        mov     edi,eax
        mov     al,m_rc.col
        mul     edx
        add     edi,eax
        shl     edi,2
        add     edi,2
        add     rdi,m_Window

        .for ( edx = 0xF0, eax = 0 : eax < ecx : eax++, rdi+=4 )

            and [rdi],dl
            or  [rdi],si
        .endf
        .return


    .case WP_FILLBACKGROUND

        ; wParam: TRECT
        ; lParam: WORD  { Attribute }
        ; return: DWORD { Number Written }

        mov ecx,edi

        .if ( Flags.Child )

            add ch,m_rc.y
            add cl,m_rc.x
            mov rbx,m_Base
        .endif

        .if ( Flags.Color )

            lea rax,at_background
            movzx esi,byte ptr [rsi+rax]
        .endif

        .if ( Flags.Visible )

            add cl,m_rc.x
            add ch,m_rc.y
            mov rc,ecx

            .for ( edi = 0 : rc.col : rc.col--, rc.x++ )

                movzx   edx,rc.y
                shl     edx,16
                mov     dl,rc.x
                .break .ifd !ReadConsoleOutputAttribute(_confh, &u2, 1, edx, &u1)
                mov     ecx,u2
                and     ecx,0x0F
                or      ecx,esi
                movzx   edx,rc.y
                shl     edx,16
                mov     dl,rc.x
                .break .ifd !FillConsoleOutputAttribute(_confh, cx, 1, edx, &u1)
                inc     edi
            .endf
            .return( edi )
        .endif

        movzx   eax,cl
        movzx   edx,ch
        shr     ecx,16
        and     ecx,0xFF
        mov     edi,eax
        mov     al,m_rc.col
        mul     edx
        add     edi,eax
        shl     edi,2
        add     edi,2
        add     rdi,m_Window

        .for ( edx = 0x0F, eax = 0 : eax < ecx : eax++, rdi+=4 )

            and [rdi],dl
            or  [rdi],si
        .endf
        .return


    .case WP_FILLCHARINFO

        ; wParam: TRECT
        ; lParam: CHAR_INFO
        ; return: DWORD { Number Written }

        mov rc,edi
        mov edi,WinProc(WP_FILLCHARACTER, edi, rsi)
        shr esi,16
        .ifnz
            WinProc(WP_FILLATTRIBUTE, rc, rsi)
        .endif
        .return( edi )



    .case WP_WRITESTRING

        ; wParam: TRECT { X, Y, Col, Attribute }
        ; lParam: LPWSTR
        ; return: DWORD { Number Written }

        mov rc,edi
        mov r2,edi
        shr edi,8
        mov u1,0

        .if ( rsi )

            .for ( rc.col = 1 : r2.col && word ptr [rsi] : r2.col--, rc.x++, u1++ )

                mov di,[rsi]
                add rsi,2

                .if ( di == 10 )
                    inc rc.y
                    mov rc.x,r2.x
                    dec rc.x
                   .continue
                .elseif ( di == 9 )
                    add rc.x,8
                    and rc.x,-8
                    dec rc.x
                   .continue
                .endif
                WinProc(WP_FILLCHARINFO, rc, rdi)
            .endf
        .endif
        .return( u1 )


    .case WP_WRITEPATH

        ; wParam: TRECT { X, Y, Col, Attribute }
        ; lParam: LPWSTR
        ; return: DWORD { Chars Written }

        mov rc,edi
        wcslen( rsi )
        movzx ecx,rc.col
        .if ( eax > ecx )

            mov rdi,rsi
            add ecx,ecx
            add eax,eax
            add rsi,rax
            sub rsi,rcx
            mov r2,rc
            mov r2.col,1

            .if ( word ptr [rdi+2] == ':' )

                WinProc(WP_FILLCHARACTER, r2, [rdi])
                inc r2.x
                WinProc(WP_FILLCHARACTER, r2, ':')
                inc r2.x
                add rc.x,2
                sub rc.col,2
                add rsi,4
            .endif
            WinProc(WP_FILLCHARACTER, r2, '\')
            inc r2.x
            inc r2.col
            WinProc(WP_FILLCHARACTER, r2, '.')
            dec r2.col
            add r2.x,2
            WinProc(WP_FILLCHARACTER, r2, '\')
            add rsi,8
            add rc.x,4
            sub rc.col,4
        .endif
         mov edi,rc
        .gotosw(WP_WRITESTRING)


    .case WP_WRITECENTER

        ; wParam: TRECT { X, Y, Col, Attribute }
        ; lParam: LPWSTR
        ; return: DWORD { Chars Written }

        mov rc,edi
        wcslen( rsi )
        movzx ecx,rc.col
        .if ( eax > ecx )
            add ecx,ecx
            add eax,eax
            add rsi,rax
            sub rsi,rcx
        .else
            sub ecx,eax
            shr ecx,1
            add rc.x,cl
            sub rc.col,cl
        .endif
         mov edi,rc
        .gotosw(WP_WRITESTRING)


    .case WP_WRITEFORMAT

        ; wParam: TRECT { X, Y, Col, Attribute }
        ; lParam: LPWSTR
        ; vParam: VARARG
        ; return: DWORD { Chars Written }

        mov rdx,rsi
        mov rax,m_Home
        mov rsi,[rax].Doszip.m_LBuf
        vswprintf(rsi, rdx, &vParam)
       .gotosw(WP_WRITESTRING)


    .case WP_WRITETITLE

        ; lParam: LPWSTR

        movzx edi,m_rc.col
        shl edi,16
        WinProc(WP_FILLCHARINFO, edi, MKAT(BG_TITLE, FG_TITLE, ' '))
       .gotosw(WP_WRITECENTER)


    .case WP_WRITEFRAME

        ; wParam: TRECT
        ; lParam: COORD { Type, Attribute }

        mov     eax,edi
        mov     rc,eax
        mov     rr,eax
        mov     rl,eax
        inc     al
        mov     r2,eax
        shr     eax,16
        dec     al
        mov     rr.x,al
        sub     r2.col,2
        mov     rl.col,1
        mov     rr.col,1
        movzx   eax,si
        xor     si,si
        mov     edx,esi
        mov     ecx,esi
        mov     edi,esi
        or      edx,U_LIGHT_VERTICAL
        or      ecx,U_LIGHT_HORIZONTAL
        mov     u1,edx
        mov     u2,ecx
        mov     edx,esi
        mov     ecx,esi

        .switch pascal eax
        .case BOX_CLEAR
            mov eax,esi
            or  eax,' '
            mov u1,eax
            mov u2,eax
            mov edx,eax
            mov ecx,eax
            mov edi,eax
            mov esi,eax
        .case BOX_DOUBLE
            mov eax,esi
            or  eax,U_DOUBLE_VERTICAL
            mov u1,eax
            mov eax,esi
            or  eax,U_DOUBLE_HORIZONTAL
            mov u2,eax
            or  edx,U_DOUBLE_DOWN_AND_RIGHT
            or  ecx,U_DOUBLE_DOWN_AND_LEFT
            or  edi,U_DOUBLE_UP_AND_RIGHT
            or  esi,U_DOUBLE_UP_AND_LEFT
        .case BOX_SINGLE_VERTICAL
            or  edx,U_LIGHT_DOWN_AND_HORIZONTAL
            or  ecx,U_LIGHT_DOWN_AND_HORIZONTAL
            or  edi,U_LIGHT_UP_AND_HORIZONTAL
            or  esi,U_LIGHT_UP_AND_HORIZONTAL
        .case BOX_SINGLE_HORIZONTAL
            or  edx,U_LIGHT_VERTICAL_AND_RIGHT
            or  ecx,U_LIGHT_VERTICAL_AND_LEFT
            or  edi,U_LIGHT_VERTICAL_AND_RIGHT
            or  esi,U_LIGHT_VERTICAL_AND_LEFT
        .case BOX_SINGLE_ARC
            or  edx,U_LIGHT_ARC_DOWN_AND_RIGHT
            or  ecx,U_LIGHT_ARC_DOWN_AND_LEFT
            or  edi,U_LIGHT_ARC_UP_AND_RIGHT
            or  esi,U_LIGHT_ARC_UP_AND_LEFT
        .default
            or  edx,U_LIGHT_DOWN_AND_RIGHT
            or  ecx,U_LIGHT_DOWN_AND_LEFT
            or  edi,U_LIGHT_UP_AND_RIGHT
            or  esi,U_LIGHT_UP_AND_LEFT
        .endsw
        mov u3,ecx
        WinProc(WP_FILLCHARINFO, rl, edx)
        WinProc(WP_FILLCHARINFO, r2, u2)
        WinProc(WP_FILLCHARINFO, rr, u3)
        mov al,rc.row
        dec al
        add rl.y,al
        add rr.y,al
        add r2.y,al
        WinProc(WP_FILLCHARINFO, rl, edi)
        WinProc(WP_FILLCHARINFO, r2, u2)
        WinProc(WP_FILLCHARINFO, rr, esi)
        mov al,rc.row
        sub al,2
        sub rl.y,al
        sub rr.y,al
        movzx esi,al
        .for ( edi = 0 : edi < esi : edi++, rl.y++, rr.y++ )
            WinProc(WP_FILLCHARINFO, rl, u1)
            WinProc(WP_FILLCHARINFO, rr, u1)
        .endf


    .case WP_FILLWINDOW

        ; wParam: BOOL
        ; lParam: CHAR_INFO

        .if ( edi && esi & 0xFFFF0000 )

            mov     eax,esi
            shr     eax,16
            mov     ecx,eax
            and     eax,0x0F
            and     ecx,0xF0
            shr     ecx,4
            lea     rdi,at_background
            mov     cl,[rdi+rcx]
            lea     rdi,at_foreground
            mov     al,[rdi+rax]
            or      al,cl
            shl     eax,16
            and     esi,0xFF00FFFF
            or      esi,eax
        .endif
        mov     edx,m_rc
        mov     eax,edx
        shr     edx,24
        shr     eax,16
        movzx   eax,al
        mul     edx
        mov     ecx,eax
        mov     eax,esi
        mov     rdi,m_Window

        .if ( eax & 0xFFFF0000 && eax & 0x0000FFFF )
            rep  stosd
        .else
            .if ( eax & 0xFFFF0000 )
                shr eax,16
                add rdi,2
            .endif
            .for ( : ecx : ecx--, rdi+=4 )
                mov [rdi],ax
            .endf
        .endif


    .case WP_READWINDOW

        ; wParam: TRECT
        ; lParam: PCHAR_INFO
        ; return: BOOL

        mov     rc,edi
        mov     rdi,rsi
        movzx   eax,rc.col
        movzx   edx,rc.row
        movzx   ecx,rc.y
        mov     Coord.X,ax
        mov     Coord.Y,dx
        mov     rect.Top,cx
        lea     ecx,[rcx+rdx-1]
        mov     rect.Bottom,cx
        movzx   ecx,rc.x
        mov     rect.Left,cx
        lea     eax,[rcx+rax-1]
        mov     rect.Right,ax

        .ifd !ReadConsoleOutputW(_confh, rdi, Coord, 0, &rect)

            mov     rect.Bottom,rect.Top
            movzx   ebx,Coord.Y
            mov     Coord.Y,1
            movzx   esi,Coord.X
            shl     esi,2
            .repeat
                .break .ifd !ReadConsoleOutputW(_confh, rdi, Coord, 0, &rect)
                inc rect.Bottom
                inc rect.Top
                add rdi,rsi
                dec ebx
            .until !ebx
            xor eax,eax
            .if !ebx
                inc eax
            .endif
        .endif
        .return


    .case WP_WRITEWINDOW

        ; wParam: TRECT
        ; lParam: PCHAR_INFO
        ; return: BOOL

        mov     rc,edi
        mov     rdi,rsi
        movzx   eax,rc.col
        movzx   edx,rc.row
        movzx   ecx,rc.y
        mov     Coord.X,ax
        mov     Coord.Y,dx
        mov     rect.Top,cx
        lea     ecx,[rcx+rdx-1]
        mov     rect.Bottom,cx
        movzx   ecx,rc.x
        mov     rect.Left,cx
        lea     eax,[rcx+rax-1]
        mov     rect.Right,ax

        .ifd !WriteConsoleOutputW(_confh, rdi, Coord, 0, &rect)

            mov     rect.Bottom,rect.Top
            movzx   ebx,Coord.Y
            mov     Coord.Y,1
            movzx   esi,Coord.X
            shl     esi,2
            .repeat
                .break .ifd !WriteConsoleOutputW(_confh, rdi, Coord, 0, &rect)
                inc rect.Bottom
                inc rect.Top
                add rdi,rsi
                dec ebx
            .until !ebx
            xor eax,eax
            .if !ebx
                inc eax
            .endif
        .endif
        .return



    .case WP_FLIPWINDOW

        ; wParam: TRECT
        ; lParam: PCHAR_INFO
        ; return: BOOL

        mov rc,edi
        .if malloc(GetWindowSize(edi))

            mov rdi,rax
            .ifd WinProc(WP_READWINDOW, rc, rax)

                WinProc(WP_WRITEWINDOW, rc, rsi)
                movzx eax,rc.row
                mul rc.col
                mov ecx,eax
                mov rdx,rdi
                xchg rdi,rsi
                rep movsd
                mov rdi,rdx
                mov eax,1
            .endif
            mov esi,eax
            free( rdi )
            mov eax,esi
        .endif
        .return


    .case WP_SHADEWINDOW

        ; wParam: BOOL
        ; lParam: PDWND

        mov     rbx,rsi
        mov     esi,edi
        mov     edi,GetWindowSize(m_rc)
        add     rdi,m_Window
        mov     eax,m_rc
        add     al,2
        add     ah,dl
        mov     r2,eax
        mov     r2.row,1
        mov     eax,m_rc
        add     al,cl
        inc     ah
        mov     rr,eax
        mov     rr.col,2
        dec     rr.row
        mov     eax,esi
        lea     rsi,[rdi+rcx*4]

        .if ( eax )

            WinProc(WP_READWINDOW, r2, rdi)
            WinProc(WP_READWINDOW, rr, rsi)
            movzx eax,r2.x
            movzx edx,r2.y
            shl   edx,16
            mov   dl,al
            FillConsoleOutputAttribute(_confh, 8, r2.col, edx, &u1)
            movzx eax,rr.x
            movzx edi,rr.y
            shl   edi,16
            mov   di,ax
            .for ( ebx = 0 : bl < rr.row : ebx++, edi+=0x10000 )
                FillConsoleOutputAttribute(_confh, 8, 2, edi, &u1)
            .endf
        .else
            .for ( ebx = 0 : bl < r2.col : ebx++ )
                movzx eax,r2.x
                movzx edx,r2.y
                shl   edx,16
                add   eax,ebx
                mov   dx,ax
                movzx ecx,word ptr [rdi+rbx*4+2]
                FillConsoleOutputAttribute(_confh, cx, 1, edx, &u1)
            .endf
            movzx eax,rr.x
            movzx edi,rr.y
            shl   edi,16
            mov   di,ax
            .for ( ebx = 0 : bl < rr.row : ebx++, edi+=0x10000, rsi+=8 )
                movzx ecx,word ptr [rsi+2]
                FillConsoleOutputAttribute(_confh, cx, 1, edi, &u1)
                lea edx,[rdi+1]
                movzx ecx,word ptr [rsi+6]
                FillConsoleOutputAttribute(_confh, cx, 1, edx, &u1)
            .endf
        .endif


    .case WP_SHOWWINDOW

        ; wParam: BOOL
        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        xor eax,eax
        .if ( rbx && Flags.Open )
            .if ( edi )
                .if ( Flags.Visible == 0 )
                    .ifd WinProc(WP_FLIPWINDOW, m_rc, m_Window)
                        .if ( Flags.Shade )
                            WinProc(WP_SHADEWINDOW, TRUE, rbx)
                        .endif
                        mov Flags.Visible,1
                        mov eax,1
                    .endif
                .endif
            .elseif ( Flags.Visible )
                .ifd WinProc(WP_FLIPWINDOW, m_rc, m_Window)
                    .if ( Flags.Shade )
                        WinProc(WP_SHADEWINDOW, FALSE, rbx)
                    .endif
                    mov Flags.Visible,0
                    mov eax,1
                .endif
            .endif
        .endif
        .return


    .case WP_MOVEWINDOW

        ; wParam: ENUM { _DLMOVE_DIRECTION }
        ; return: BOOL

        mov rcx,m_Home
        mov rax,[rcx].Doszip.m_LBuf
        sub rax,MAXLBUF
        mov p,rax
        add rax,512
        mov q,rax
        WinProc(WP_GETRECT, &rc, rcx)
        mov eax,m_rc
        mov ecx,edi
        mov u1,edi
        mov rsi,m_Window
        mov rdi,q

        .switch ecx
        .case TW_MOVELEFT
            .if ( al == 0 )
                .return( 0 )
            .endif
            dec     al
            mov     rr,eax          ; write line right
            mov     rl,eax          ; read line left
            mov     r2,eax
            mov     rl.col,1
            mov     r2.col,1
            add     r2.x,rr.col
            dec     al
            movzx   edx,al
            .for ( ecx = 0 : cl < rr.row : ecx++ )

                mov eax,[rsi+rdx*4]
                stosd
                movzx eax,rr.col
                add edx,eax
            .endf
            .endc
        .case TW_MOVERIGHT
            movzx ecx,al
            movzx edx,m_rc.col
            add ecx,edx
            .if ( cl >= rc.col )
                .return( 0 )
            .endif
            mov rl,eax              ; read line right
            mov r2,eax              ; write line left
            mov rl.col,1
            mov r2.col,1
            inc al
            mov rr,eax
            mov rl.x,cl
            .for ( edx = 0, ecx = 0 : cl < m_rc.row : ecx++ )

                mov eax,[rsi+rdx*4]
                stosd
                movzx eax,m_rc.col
                add edx,eax
            .endf
            .endc
        .case TW_MOVEUP
            .if ( ah <= 1 )
                .return( 0 )
            .endif
            dec     ah
            mov     rr,eax          ; write last line
            mov     rl,eax          ; read line above
            mov     r2,eax
            mov     rl.row,1
            mov     r2.row,1
            add     r2.y,m_rc.row
            dec     al
            movzx   ecx,m_rc.col
            movzx   eax,al
            mul     ecx
            mov     rdx,rsi
            lea     rsi,[rsi+rax*4] ; last line
            rep     movsd
            mov     rsi,rdx
           .endc
        .case TW_MOVEDOWN
            movzx ecx,ah
            movzx edx,m_rc.row
            add ecx,edx
            .if ( rc.row <= cl )
                .return( 0 )
            .endif
            mov     rl,eax          ; write first line
            mov     r2,eax          ; read line below
            mov     rl.row,1
            mov     r2.row,1
            inc     ah
            mov     rr,eax
            add     rl.y,dl
            movzx   ecx,m_rc.col
            mov     rdx,rsi
            rep     movsd           ; first line
            mov     rsi,rdx
        .endsw

        .if malloc(GetWindowSize(m_rc))

            mov rdi,rax
            WinProc(WP_READWINDOW, rl, p)
            WinProc(WP_READWINDOW, m_rc, rdi)
            WinProc(WP_WRITEWINDOW, rr, rdi)
            WinProc(WP_WRITEWINDOW, r2, q)
            free(rdi)

            mov eax,u1
            .switch eax
            .case TW_MOVELEFT
                 std
                .for ( m_rc.x--, edx = 0 : dl < m_rc.row : edx++ )

                    movzx   eax,m_rc.col
                    mov     ecx,eax
                    imul    eax,edx
                    lea     rax,[rsi+rax*4]
                    dec     ecx
                    lea     rax,[rax+rcx*4-4]
                    lea     rdi,[rax+4]
                    xchg    rax,rsi
                    rep     movsd
                    mov     rsi,rax
                    mov     rax,p
                    mov     eax,[rax+rdx*4]
                    mov     [rdi],eax
                .endf
                 cld
                .endc
            .case TW_MOVERIGHT
                .for ( m_rc.x++, rdi = rsi, rsi+=4, edx = 0 : dl < m_rc.row : edx++ )

                    mov     rax,p
                    mov     eax,[rax+rdx*4]
                    movzx   ecx,m_rc.col
                    dec     ecx
                    rep     movsd
                    stosd
                    add     rsi,4
                .endf
                .endc
            .case TW_MOVEUP
                dec     m_rc.y
                movzx   eax,m_rc.row ; move lines down
                movzx   ecx,m_rc.col ; insert first line
                dec     eax
                mul     ecx
                mov     rdx,rsi
                lea     rsi,[rsi+rax*4-4]
                lea     rdi,[rsi+rcx*4]
                mov     ecx,eax
                std
                rep     movsd
                cld
                mov     rdi,rdx
                movzx   ecx,m_rc.col
                mov     rsi,p
                rep     movsd
               .endc
            .case TW_MOVEDOWN
                inc     m_rc.y
                movzx   eax,m_rc.row  ; move lines up
                movzx   ecx,m_rc.col  ; insert last line
                dec     eax
                mul     ecx
                mov     rdi,rsi
                lea     rsi,[rsi+rcx*4]
                xchg    eax,ecx
                rep     movsd
                mov     ecx,eax
                mov     rsi,p
                rep     movsd
               .endc
            .endsw
            .return( 1 )
        .endif


    .case WP_OPENWINDOW

        ; wParam: BOOL
        ; lParam: PDWND
        ; return: BOOL

        .if SetClass(rsi)

            .if ( edi )
                GetWindowSize(m_rc)
                .if ( Flags.Shade )
                    lea ecx,[rcx+rdx*2-2]
                    shl ecx,2
                    add eax,ecx
                .endif
                .if malloc( eax )
                    mov m_Window,rax
                    mov Flags.Open,1
                    mov eax,1
                .endif
            .elseif ( Flags.Open )
                .if ( Flags.Visible )
                    WinProc(WP_SHOWWINDOW, FALSE, rbx)
                .endif
                free(m_Window)
                mov Flags.Open,0
                xor eax,eax
                mov m_Window,rax
                inc eax
            .endif
        .endif
        .return


    .case WP_BEGINPAINT

        ; lParam: PDWND
        ; return: PCHAR_INFO

        xor eax,eax
        mov rbx,rsi

        .if ( Flags.Open && Flags.Visible )

            .if malloc( GetWindowSize(m_rc) )

                mov rdi,rax
                WinProc(WP_READWINDOW, m_rc, rdi)
                mov rax,m_Window
                mov m_Window,rdi
                mov Flags.Visible,0
            .endif
        .endif
        .return


    .case WP_ENDPAINT

        ; wParam: PCHAR_INFO
        ; lParam: PDWND

        .if ( rdi )

            mov rbx,rsi
            WinProc(WP_WRITEWINDOW, m_rc, m_Window)
            free(m_Window)
            mov m_Window,rdi
            mov Flags.Visible,1
        .endif


    .case WP_GETOBJECT

        ; wParam: DWORD { Id }
        ; lParam: PDWND
        ; return: PDWND

        .for ( rbx = rsi : rbx : rbx = m_Next )
            .break .if ( edi == m_Id )
        .endf
        .return( rbx )


    .case WP_GETINDEX

        ; wParam: DWORD { Index }
        ; lParam: PDWND
        ; return: PDWND

        .for ( rbx = rsi, rbx <> m_This : rbx : rbx = m_Next, edi-- )
            .break .if ( !edi )
        .endf
        .return( rbx )


    .case WP_GETFOCUS

        ; return: PDWND

        .if ( Flags.Child )
            mov rbx,m_Base
        .endif
        .for ( rbx = m_This : rbx : rbx = m_Next )
            .break .if ( Flags.HasFocus )
        .endf
        .return( rbx )


    .case WP_GETRECT

        ; wParam: PTRECT
        ; lParam: PDWND
        ; return: TRECT

        mov eax,[rsi].Doszip.m_rc
        .if ( rdi )
            mov [rdi],eax
        .endif
        .return


    .case WP_GETMESSAGE

        ; wParam: PDMSG
        ; lParam: PDWND
        ; return: BOOL

        mov rbx,m_Home
        mov pMsg,rdi
        mov hwnd,rsi

        .while 1

            .if ( m_msgCount )

                dec     m_msgCount
                imul    eax,m_msgCount,Message
                lea     rdx,m_msgStack
                add     rdx,rax
                mov     rcx,pMsg
                mov     [rcx].Message.wParam,[rdx].Message.wParam
                mov     [rcx].Message.lParam,[rdx].Message.lParam
                mov     [rcx].Message.uMsg,[rdx].Message.uMsg
                cmp     eax,WP_QUIT
                mov     eax,0
                setne   al
               .return
            .endif

            mov u1,0
            .ifd GetNumberOfConsoleInputEvents(_coninpfh, &u1)
                .if ( u1 )
                    ReadConsoleInputW(_coninpfh, &Input, 1, &u1)
                .endif
            .endif

            mov eax,u1
            .if ( eax == 0 )

                mov rdx,hwnd
                mov rcx,pMsg
                mov [rcx].Message.wParam,rax
                mov [rcx].Message.lParam,rdx
                mov [rcx].Message.uMsg,WP_ENTERIDLE
                inc eax
               .return
            .endif

            .switch pascal Input.EventType

            .case KEY_EVENT

                .endc .if ( m_dlgFocus == 0 )

                ;
                ; lParam
                ;
                ;  0-15 Control Key State
                ;  16   Key Char
                ;
                movzx   ecx,Input.Event.KeyEvent.wVirtualKeyCode
                movzx   edi,word ptr Input.Event.KeyEvent.dwControlKeyState
                mov     eax,ecx
                shl     eax,16
                or      edi,eax
                cmp     Input.Event.KeyEvent.bKeyDown,0
                mov     eax,WP_KEYUP
                mov     esi,WP_KEYDOWN
                cmovz   esi,eax
                ;
                ; wParam
                ;
                ; The Char or Virtual Key Code of the key
                ;
                movzx   edx,Input.Event.KeyEvent.uChar.UnicodeChar
                test    edi,ENHANCED_KEY or RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED
                cmovnz  edx,ecx
                test    edx,edx
                cmovz   edx,ecx

                PostMessage(esi, rdx, rdi)

                movzx   edx,Input.Event.KeyEvent.uChar.UnicodeChar
                .endc .if ( edx == 0 )
                .endc .if ( esi != WP_KEYDOWN )
                .endc .if ( edi & ENHANCED_KEY or RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED or RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED )

                PostMessage(WP_CHAR, rdx, rdi)

            .case MOUSE_EVENT

                .endc .if ( m_dlgFocus == 0 )

                ;
                ; lParam
                ;
                ; low-order word specifies the x-coordinate of the cursor
                ; high-order word specifies the y-coordinate of the cursor
                ;
                ; wParam
                ;
                ; 0x0008 MK_CONTROL     The CTRL key is down
                ; 0x0001 MK_LBUTTON     The left mouse button is down
                ; 0x0010 MK_MBUTTON     The middle mouse button is down
                ; 0x0002 MK_RBUTTON     The right mouse button is down
                ; 0x0004 MK_SHIFT       The SHIFT key is down
                ; 0x0020 MK_XBUTTON1    The first X button is dow
                ; 0x0040 MK_XBUTTON2    The second X button is down
                ;
                xor     ecx,ecx
                mov     edx,Input.Event.MouseEvent.dwControlKeyState
                test    edx,SHIFT_PRESSED
                mov     eax,MK_SHIFT
                cmovz   eax,ecx
                test    edx,RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED
                mov     edx,MK_CONTROL
                cmovnz  ecx,edx
                or      ecx,eax
                xor     edx,edx
                mov     eax,MK_LBUTTON
                mov     edi,Input.Event.MouseEvent.dwButtonState
                test    edi,FROM_LEFT_1ST_BUTTON_PRESSED
                cmovz   eax,edx
                or      ecx,eax
                mov     eax,MK_MBUTTON
                test    edi,FROM_LEFT_2ND_BUTTON_PRESSED
                cmovz   eax,edx
                or      ecx,eax
                mov     eax,MK_RBUTTON
                test    edi,RIGHTMOST_BUTTON_PRESSED
                cmovz   eax,edx
                or      ecx,eax
                mov     eax,edi
                and     eax,0xFFFFFF00
                or      ecx,eax
                xor     esi,esi
                mov     eax,Input.Event.MouseEvent.dwEventFlags

                .switch pascal eax
                .case MOUSE_MOVED
                    mov esi,WP_MOUSEMOVE
                .case MOUSE_HWHEELED
                    mov esi,WP_MOUSEHWHEEL
                .case MOUSE_WHEELED
                    mov esi,WP_MOUSEWHEEL
                .case DOUBLE_CLICK
                    .if ( ecx & MK_LBUTTON )
                        mov esi,WP_LBUTTONDBLCLK
                    .elseif ( ecx & MK_RBUTTON )
                        mov esi,WP_RBUTTONDBLCLK
                    .else
                        mov esi,WP_XBUTTONDBLCLK
                    .endif
                .default
                    mov eax,m_msButton
                    mov m_msButton,edi
                    .if ( eax != edi )
                        .if ( ( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) && !( edi & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                            mov esi,WP_LBUTTONUP
                        .elseif ( !( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) && ( edi & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                            mov esi,WP_LBUTTONDOWN
                        .elseif ( ( eax & FROM_LEFT_2ND_BUTTON_PRESSED ) && !( edi & FROM_LEFT_2ND_BUTTON_PRESSED ) )
                            mov esi,WP_MBUTTONUP
                        .elseif ( !( eax & FROM_LEFT_2ND_BUTTON_PRESSED ) && ( edi & FROM_LEFT_2ND_BUTTON_PRESSED ) )
                            mov esi,WP_MBUTTONDOWN
                        .elseif ( ( eax & RIGHTMOST_BUTTON_PRESSED ) && !( edi & RIGHTMOST_BUTTON_PRESSED ) )
                            mov esi,WP_RBUTTONUP
                        .elseif ( !( eax & RIGHTMOST_BUTTON_PRESSED ) && ( edi & RIGHTMOST_BUTTON_PRESSED ) )
                            mov esi,WP_RBUTTONDOWN
                        .endif
                    .elseif ( ecx & MK_LBUTTON )
                        mov esi,WP_LBUTTONDOWN
                    .elseif ( ecx & MK_RBUTTON )
                        mov esi,WP_RBUTTONDOWN
                    .elseif ( ecx & MK_MBUTTON )
                        mov esi,WP_MBUTTONDOWN
                    .endif
                .endsw
                .if ( esi )
                    mov edi,ecx
                    PostMessage(esi, rdi, Input.Event.MouseEvent.dwMousePosition)
                .endif
            .case WINDOW_BUFFER_SIZE_EVENT
                PostMessage(WP_SIZE, 0, Input.Event.WindowBufferSizeEvent.dwSize)
            .case FOCUS_EVENT
                mov m_dlgFocus,Input.Event.FocusEvent.bSetFocus
            .case MENU_EVENT
                PostMessage(Input.Event.MenuEvent.dwCommandId, 0, 0)
            .endsw
        .endw


    .case WP_UNPACKWINDOW

        ; wParam: PIDD
        ; lParam: PDWND
        ; return: void

        mov     rbx,rsi
        mov     rsi,rdi
        movzx   eax,word ptr [rsi].RIDD.rc[2]
        movzx   ecx,[rsi].RIDD.count
        lea     rsi,[rsi+rcx*RIDD+RIDD]
        mul     ah
        mov     u1,eax

        .for ( u2 = 0 : u2 < 4 : u2++ )

            mov edi,u2
            add rdi,m_Window
            mov ecx,u1
            .repeat
                lodsb
                mov dl,al
                and dl,0xF0
                .if dl == 0xF0
                    mov ah,al
                    lodsb
                    and eax,0xFFF
                    mov edx,eax
                    lodsb
                    .repeat
                        stosb
                        add rdi,3
                        dec edx
                       .break .ifz
                    .untilcxz
                    .break .if !ecx
                .else
                    stosb
                    add rdi,3
                .endif
            .untilcxz
        .endf

        .if ( Flags.Color )

            mov rbx,m_Window
            lea rdi,at_foreground
            lea rsi,at_background

            .for ( ecx = 0 : ecx < u1 : ecx++ )

                mov     al,[rbx+rcx*4+2]
                mov     ah,al
                and     eax,0x0FF0
                shr     al,4
                movzx   edx,al
                mov     al,[rsi+rdx]
                mov     dl,ah
                or      al,[rdi+rdx]
                mov     [rbx+rcx*4+2],al
            .endf
        .endif


    .case WP_OPENRESOURCE

        ; wParam: BOOL
        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        .if ( edi == FALSE )
            WinProc(WP_DESTROY, TRUE, m_This)
            WinProc(WP_OPENWINDOW, FALSE, rbx)
           .endc
        .endif
        mov rsi,m_Resource
        xor ecx,ecx
        mov cl,[rsi].RIDD.count
        mov u1,ecx
        mov cl,[rsi].RIDD.index
        mov u2,ecx

        .ifd WinProc(WP_OPENWINDOW, TRUE, rbx)

            mov ecx,m_Type
            .if ( ecx == CT_MENUBAR || ecx == CT_KEYBAR )

                mov rdx,m_Home
                mov m_rc.col,[rdx].Doszip.m_rc.col
                .if ( ecx == CT_KEYBAR )
                    mov al,[rdx].Doszip.m_rc.row
                    dec al
                    mov m_rc.y,al
                .endif
                WinProc(WP_FILLWINDOW, TRUE, MKAT(BG_TITLE, FG_TITLE, ' '))
            .endif
            WinProc(WP_UNPACKWINDOW, rsi, rbx)

            .for ( edi = 0 : edi < u1 : edi++ )

                add     rsi,ROBJ
                movzx   eax,[rsi].RIDD.index
                mov     u4,eax
                movzx   edx,[rsi].RIDD.flags
                and     edx,7
                add     edx,CT_PUSHBUTTON
                mov     eax,m_Id
                lea     eax,[rax+rdi+1]
                shl     eax,16
                or      edx,eax

                .if WinProc(WP_CREATE, edx, rbx)

                    mov     rcx,rax
                    mov     edx,[rsi].RIDD.rc
                    mov     [rcx].Doszip.m_rc,edx
                    mov     eax,m_rc
                    shr     eax,16
                    mul     dh
                    movzx   edx,dl
                    add     eax,edx
                    shl     eax,2
                    add     rax,m_Window
                    mov     [rcx].Doszip.m_Window,rax

                    movzx edx,[rsi].RIDD.flags
                    mov eax,W_RESOURCE or W_CHILD
                    .if ( edx & O_LIST )
                        or eax,W_LIST
                    .endif
                    .if ( edx & O_NOFOCUS )
                        or eax,W_NOFOCUS
                    .endif
                    .if ( edx & O_DEXIT )
                        or eax,W_AUTOEXIT
                    .endif
                    and edx,W_DISABLED
                    or  eax,edx
                    mov [rcx].Doszip.Flags,eax
                    mov [rcx].Doszip.m_SysKey,u4
                    .if ( [rcx].Doszip.m_Type == CT_TEXTINPUT )

                        mov hwnd,rbx
                        mov rbx,rcx
                        mov Edit.m_Attribute,MKAT(BG_TEDIT, FG_TEDIT, U_MIDDLE_DOT)
                        WinProc(WP_ADDLINE, 0, 0)
                        mov rbx,hwnd
                    .endif
                .endif
            .endf
            mov eax,TRUE
        .endif
        .return


    .case WP_OPENDIALOG

        ; lParam: LPWSTR
        ; return: BOOL

        .ifd WinProc(WP_OPENWINDOW, TRUE, rbx)

            .if ( Flags.Resource )
                WinProc(WP_UNPACKWINDOW, m_Resource, rbx)
            .else
                mov eax,MKAT(BG_DIALOG, FG_DIALOG, ' ')
                .if ( Flags.Transparent )
                    WinProc(WP_READWINDOW, m_rc, m_Window)
                    mov eax,MKAT(0, 8, 0)
                .elseif ( Flags.SysMenu )
                    mov eax,MKAT(BG_ERROR, 7, ' ')
                .endif
                WinProc(WP_FILLWINDOW, TRUE, rax)
                .if ( Flags.Caption )
                    WinProc(WP_WRITETITLE, 0, rsi)
                .endif
                mov eax,1
            .endif
        .endif
        .return


    .case WP_CUT
    .case WP_COPY
    .case WP_PASTE
    .case WP_CLEAR


    .case WP_GETTEXT

        ; wParam: DWORD { Line Index }
        ; lParam: PDWND { EditClass }
        ; return: PDWND { LineClass, rdx: m_LBuf, rcx: Count }

        .if WinProc(WP_GETINDEX, edi, rsi)

            mov rbx,rax
            mov rsi,m_Text
            mov rdi,Line.m_LBuf
            mov ecx,Line.m_Indent
            mov eax,' '
            rep stosw
            .repeat
                lodsb
                .if ( al == 9 )
                    mov rdx,Line.m_LBuf
                    mov rcx,rdi
                    sub rcx,rdx
                    mov eax,ecx
                    and ecx,-8
                    add ecx,8
                    sub ecx,eax
                    mov eax,' '
                    rep stosw
                .else
                    dec rsi
                    _utftow(rsi)
                    stosw
                    add rsi,rcx
                .endif
            .until !eax
            mov rdx,Line.m_LBuf
            mov rcx,rdi
            sub rcx,rdx
            sub ecx,2
            shr ecx,1
            mov rax,rbx
        .endif
        .return


    .case WP_SETTEXT

        ; CLType: Line
        ; wParam: DWORD  { Char count }
        ; lParam: LPWSTR { Unicode Text }
        ; return: BOOL

        mov edx,edi
        xor eax,eax
        mov rdi,Line.m_LBuf
        mov [rsi+rdx*2],ax
        .while edx
            mov cx,[rsi+rdx*2-2]
            .if ( cx == ' ' || cx == 9 )
                dec edx
                mov [rsi+rdx*2],ax
            .else
                .break
            .endif
        .endw
        .for ( : edx : edx-- )
            mov cx,[rsi]
            .if ( cx == ' ' )
                inc eax
            .elseif ( cx == 9 )
                and eax,-8
                add eax,8
            .else
                .break
            .endif
            add rsi,2
        .endf
        mov u1,edx
        mov Line.m_Indent,eax

        .for ( edx = 0, u2 = edx : edx < u1 : edx++ )

            lodsw
            and eax,0xFFFF
            mov ecx,u2
            mov u3,edx
            .if ( eax == ' ' || eax == 9 )
                .if ( ecx == 0 )
                    mov u4,edx
                .endif
                .if ( eax == ' ' )
                    inc ecx
                .else
                    add ecx,u4
                    add ecx,Line.m_Indent
                    and ecx,-8
                    add ecx,8
                    sub ecx,u4
                    sub ecx,Line.m_Indent
                .endif
                mov u2,ecx
            .else
                .if ( ecx )
                    mov edx,u4
                    add edx,Line.m_Indent
                    and edx,-8
                    add edx,8
                    sub edx,u4
                    sub edx,Line.m_Indent
                    mov eax,9
                    .if ( edx && edx <= ecx )
                        sub ecx,edx
                        stosb
                    .endif
                    .while ( ecx >= 8 )
                        sub ecx,8
                        stosb
                    .endw
                    mov eax,' '
                    rep stosb
                    mov u2,ecx
                .endif
                _wtoutf([rsi-2])
                mov [rdi],eax
                add rdi,rcx
            .endif
            mov edx,u3
        .endf
        mov byte ptr [rdi],0
        sub rdi,Line.m_LBuf
        .ifz
            mov Line.Flags.IsBlank,1
        .endif
        .if ( Flags.Mybuf )
            free(m_Text)
            mov Flags.Mybuf,0
        .endif
        mov Line.m_Count,edi
        inc edi
        .if ( edi > Doszip - Doszip.Panel )
            mov Line.m_Size,edi
            mov Flags.Mybuf,1
            malloc(rdi)
        .else
            mov Line.m_Size,Doszip - Doszip.Panel
            lea rax,Panel
        .endif
        .if ( rax )
            mov m_Text,strcpy(rax, Line.m_LBuf)
            mov eax,1
        .endif
        .return


    .case WP_PUTTEXT

        ; wParam: ?
        ; lParam: PDWND { EditClass }
        ; return: ?

        mov     rbx,rsi
        movzx   eax,m_rc.col
        sub     al,Edit.m_Cols
        shl     eax,16
        mov     al,Edit.m_XPos
        mov     rc,eax

        WinProc(WP_FILLCHARINFO, rc, Edit.m_Attribute)
        movzx ecx,Edit.m_YOffs
        add ecx,Edit.m_LOffs
        .if WinProc(WP_GETTEXT, ecx, rbx)
            mov eax,Edit.m_BOffs
            .if ( ecx > eax )
                lea rdx,[rdx+rax*2]
                WinProc(WP_WRITESTRING, rc, rdx)
            .endif
        .endif


    .case WP_PUTC

        ; wParam: DWORD { Char }
        ; lParam: PDWND { EditClass }
        ; return: BOOL

        .if ( edi == 13 )
            .return( 1 )
        .elseif ( edi == 10 )
            .if ( !Edit.Flags.MultiLine )
                .return( 0 )
            .endif
        .endif

        mov rbx,rsi
        movzx ecx,Edit.m_YOffs
        add ecx,Edit.m_LOffs
        .if WinProc(WP_GETTEXT, ecx, rsi)

            mov u1,edi
            mov u2,ecx
            movzx ecx,Edit.m_XOffs
            add ecx,Edit.m_BOffs
            mov u3,ecx
            mov rbx,rax
            mov rdi,Line.m_TBuf
            mov rsi,rdx
            .if ( ecx > u2 )
                mov eax,ecx
                mov ecx,u2
                sub eax,ecx
                rep movsw
                mov ecx,eax
                mov eax,' '
                rep stosw
            .else
                rep movsw
            .endif
            mov eax,u1
            stosw
            mov ecx,u2
            .if ( ecx > u3 )
                sub ecx,u3
                rep movsw
            .endif
            sub rdi,Line.m_TBuf
            shr edi,1
            .ifd WinProc(WP_SETTEXT, rdi, Line.m_TBuf)

                mov rbx,m_Base
                WinProc(WP_PUTTEXT, 0, rbx)
                movzx ecx,m_rc.col
                dec cl
                .if ( Edit.m_XOffs < cl )
                    inc Edit.m_XOffs
                .else
                    inc Edit.m_BOffs
                .endif
                mov cl,Edit.m_XOffs
                add cl,Edit.m_XPos
                WinProc(WP_SETCURSOR, TRUE, rcx)
                mov eax,1
            .endif
        .endif
        .return


    .case WP_ADDLINE

        ; wParam: DWORD
        ; lParam: LPWSTR
        ; return: BOOL

        .if WinProc(WP_NEW, MKID(CT_LINE, 0), rbx)

            mov rbx,rax
            .gotosw(WP_SETTEXT) .if ( rsi )

            mov Line.m_Size,Doszip - Doszip.Panel
            lea rax,Panel
            mov m_Text,rax
            mov eax,1
        .endif
        .return


    .case WP_GETFTIME

        ; lParam: LPWSTR
        ; return: FILETIME

        .endc .ifd ( CreateFileW(rsi, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL) == -1 )
        mov rsi,rax
        mov edi,GetFileTime(rsi, 0, 0, &ft)
        CloseHandle(rsi)
        .if ( edi )
            mov eax,ft.dwLowDateTime
            mov edx,ft.dwHighDateTime
           .return
        .endif


    .case WP_READFILE

        ; lParam: PDWND
        ; return: BOOL

        mov rbx,m_Home
        mov p,m_TBuf
        sub rax,MAXLBUF*2
        mov q,rax
        mov rbx,rsi

        WinProc( WP_DESTROY, TRUE, m_This )

        mov Edit.Flags.FileCR,0
        mov Edit.Flags.FileTab,0
        mov Edit.Flags.FileUTF8,0
        mov Edit.Flags.FileUTF16,0
        mov Edit.Flags.FileBOM,0
        mov Edit.Flags.FileBinary,0

        .ifd ( WinProc(WP_GETFTIME, 0, m_Text) == 0 )
            mov Edit.Flags.Modified,1
           .return
        .endif
        mov Edit.m_FTime,eax

        mov fp,CreateFileW(m_Text, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)
        .ifd ( ReadFile( fp, q, MAXLBUF, &u1, 0 ) == 0 )
            CloseHandle(fp)
           .return( 0 )
        .endif

        mov eax,u1
        mov rsi,q
        mov ecx,[rsi]
        and ecx,0x00FFFFFF

        .if ( eax > 2 && ecx == 0xBFBBEF )

            mov Edit.Flags.FileUTF8,1
            mov Edit.Flags.FileBOM,1
            sub eax,3
            add rsi,3

        .elseif ( eax >= 2 && cx == 0xFEFF )

            mov Edit.Flags.FileUTF16,1
            mov Edit.Flags.FileBOM,1
            sub eax,2
            add rsi,2
        .endif
        mov u2,eax
        mov u3,0
        mov u4,0
        mov rdi,p

        .while 1

            .if ( u2 == 0 )

                .break .ifd ( ReadFile( fp, q, MAXLBUF, &u1, 0 ) == 0 )
                mov u2,u1
                .break .if ( eax == 0 )
                mov rsi,q
            .endif

            movzx eax,byte ptr [rsi]
            .if ( Edit.Flags.FileUTF16 )
                mov ah,[rsi+1]
            .endif
            mov u4,eax
            .switch
            .case eax == 13
                mov Edit.Flags.FileCR,1
                inc rsi
                dec u2
                .continue .ifz
                .if ( Edit.Flags.FileUTF16 )
                    inc rsi
                    dec u2
                .endif
                .continue
            .case eax == 0
                mov Edit.Flags.FileBinary,1
            .case eax == 10
                inc rsi
                dec u2
                .ifnz
                    .if ( Edit.Flags.FileUTF16 )
                        inc rsi
                        dec u2
                    .endif
                .endif
            .case u3 == MAXLINE-1
                .break .if ( WinProc(WP_ADDLINE, u3, p) == NULL )
                mov u3,0
                mov rdi,p
               .endc
            .case eax == 9
                mov Edit.Flags.FileTab,1
            .default
                inc u3
                .if ( Edit.Flags.FileUTF16 )

                    dec u2
                    .break .ifz
                    dec u2
                    movsw

                .elseif ( Edit.Flags.FileUTF8 )

                    mov ecx,u2
                    movzx eax,byte ptr [rsi]

                    .if !( ( eax <= 0xBF || eax >= 0xF8 ) ||
                           ( ecx > 1 && eax < 0xE0 ) ||
                           ( ecx > 2 && eax < 0xF0 ) ||
                           ( ecx > 3 ) )

                        mov eax,[rsi]
                        mov rsi,q
                        mov [rsi],eax
                        add rsi,rcx
                        mov edx,MAXLBUF
                        sub edx,ecx
                        mov u1,0
                        ReadFile( fp, rsi, edx, &u1, 0 )
                        mov rsi,q
                        mov eax,u2
                        add eax,u1
                        mov u2,eax
                        mov u1,eax
                    .endif
                    _utftow(rsi)
                    stosw
                    add rsi,rcx
                    .if ( ecx <= u2 )
                        sub u2,ecx
                    .else
                        mov u2,0
                    .endif
                .else
                    .break .ifd ( MultiByteToWideChar( CP_ACP, 0, rsi, 1, rdi, 1 ) == 0 )
                    add rdi,2
                    inc rsi
                    dec u2
                .endif
            .endsw
        .endw
        CloseHandle(fp)
        .if ( u2 == 0 && u4 == 10 )
            WinProc(WP_ADDLINE, 0, NULL)
        .endif
        .return( 1 )


    .case WP_WRITEFILE

        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        mov rsi,m_Text

        .if ( Edit.Flags.CreateBackup )

            .ifd ( GetFileAttributesW( rsi ) != -1 )

                mov rdi,m_B1
                .if _wstrext(wcscpy(rdi, rsi))
                    wcscpy(rax, L".bak")
                .else
                    wcscat(rdi, L".bak")
                .endif
                .ifd ( GetFileAttributesW( rdi ) != -1 )
                    DeleteFileW( rdi )
                .endif
                MoveFile( rsi, rdi )
            .endif
        .endif

        mov fp,CreateFileW(rsi, GENERIC_WRITE, FILE_SHARE_READ or FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL)
        .if ( eax == -1 )
            .return( 0 )
        .endif

        .if ( Edit.Flags.FileBOM )

            mov eax,0xBFBBEF
            mov ecx,3
            .if ( Edit.Flags.FileUTF16 )
                mov eax,0xFEFF
                mov ecx,2
            .endif
            mov u1,eax
            .ifd ( WriteFile( fp, &u1, ecx, &u2, NULL ) == 0 )
                CloseHandle(fp)
               .return( 0 )
            .endif
        .endif

        mov eax,0x0A
        mov ecx,1
        .if ( !Edit.Flags.UnixMode )
            mov eax,0x0A0D
            mov ecx,2
        .endif
        .if ( Edit.Flags.FileUTF16 )
            mov eax,0x000A000D
            mov ecx,4
        .endif
        mov u3,eax
        mov u4,ecx

        assume rsi:PDWND

        .for ( rsi = m_This : rsi : rsi = [rsi].m_Next )

            mov rdi,m_B2
            mov ecx,[rsi].Line.m_Indent

            .if ( Edit.Flags.KeepTabs )
                .for ( eax = 9 : ecx >= 8 : ecx -= 8 )
                    .if ( Edit.Flags.FileUTF16 )
                        stosw
                    .else
                        stosb
                    .endif
                .endf
            .endif
            mov eax,' '
            .if ( Edit.Flags.FileUTF16 )
                rep stosw
            .else
                rep stosb
            .endif

            .for ( p = rsi, rsi = [rsi].m_Text : eax : )

                lodsb
                .if ( al == 9 && Edit.Flags.KeepTabs == 0 )

                    mov rdx,m_B2
                    mov rcx,rdi
                    sub rcx,rdx
                    mov eax,ecx
                    and ecx,-8
                    add ecx,8
                    sub ecx,eax
                    mov eax,' '
                    .if ( Edit.Flags.FileUTF16 )
                        rep stosw
                    .else
                        rep stosb
                    .endif

                .elseif ( Edit.Flags.FileUTF16 )

                    dec rsi
                    _utftow(rsi)
                    stosw
                    add rsi,rcx
                .else
                    stosb
                .endif
            .endf
            mov rdx,m_B2
            mov rsi,p
            sub rdi,rdx
            dec edi
            .if ( Edit.Flags.FileUTF16 )
                dec edi
            .endif
            .ifs ( edi > 0 )
               .break .ifd ( WriteFile( fp, rdx, edi, &u1, NULL ) == 0 )
            .endif
            .if ( [rsi].m_Next )
               .break .ifd ( WriteFile( fp, &u3, u4, &u1, NULL ) == 0 )
            .endif
        .endf
        assume rsi:nothing
        CloseHandle(fp)

       .return( 1 )



    .case WP_TOGGLEITEM

        mov rbx,rsi
        xor ecx,ecx
        .if ( m_Type == CT_RADIOBUTTON )
            mov edi,Flags.Checked
            .for ( rbx = m_Base, rbx = m_This : rbx : rbx = m_Next )
                .if ( m_Type == CT_RADIOBUTTON )
                    mov Flags.Checked,0
                    WinProc(WP_FILLCHARACTER, 0x01010001, ' ')
                .endif
            .endf
            mov rbx,rsi
            mov ecx,' '
            .if ( edi == 0 )
                mov Flags.Checked,1
                mov ecx,U_BULLET_OPERATOR
            .endif
        .elseif ( m_Type == CT_CHECKBOX )
            .if ( Flags.Checked == 0 )
                mov ecx,'x'
                mov Flags.Checked,1
            .else
                mov ecx,' '
                mov Flags.Checked,0
            .endif
        .endif
        .if ( ecx )
            mov esi,ecx
            mov edi,0x00010001
           .gotosw(WP_FILLCHARACTER)
        .endif


    .case WP_SETFOCUS

        ; wParam: Window that has lost focus
        ; lParam: Window that has new focus

        mov rbx,rsi
        .if ( rbx == NULL || Flags.Disabled || Flags.NoFocus )
            .endc
        .endif
        .if WinProc(WP_GETFOCUS, rax, rbx)
            WinProc(WP_KILLFOCUS, rsi, rax)
        .endif
        mov Flags.HasFocus,1
        mov eax,m_Type
        .switch eax
        .case CT_PUSHBUTTON
            WinProc(WP_CURSOR, FALSE, rbx)
            mov eax,' '
            mov esi,' '
            mov edx,U_BLACK_POINTER_RIGHT
            mov ecx,U_BLACK_POINTER_LEFT
            cmp m_State,0
            cmovz eax,edx
            cmovz esi,ecx
            WinProc(WP_FILLCHARACTER, 0x00010000, eax)
            mov ecx,0x000100FF
            add cl,m_rc.col
            mov edi,ecx
           .gotosw(1:WP_FILLCHARACTER)
        .case CT_CHECKBOX
        .case CT_RADIOBUTTON
            mov edi,TRUE
            mov esi,0x01010001
           .gotosw(1:WP_SETCURSOR)
        .case CT_XCELL
        .case CT_MENUITEM
            WinProc(WP_SETCURSOR, FALSE, 0x01010002)
            movzx edi,m_rc.col
            shl edi,16
            mov esi,BG_INVERSE
           .gotosw(1:WP_FILLBACKGROUND)
        .case CT_TEXTINPUT
            mov edi,TRUE
            mov esi,0x01010000
            movzx eax,Edit.m_XOffs
            or  esi,eax
           .gotosw(1:WP_SETCURSOR)
        .endsw


    .case WP_KILLFOCUS

        ; wParam: Window that receives the keyboard focus
        ; lParam: Window that has lost the keyboard focus

        mov rbx,rsi
        mov Flags.HasFocus,0
        mov eax,m_Type
        .switch eax
        .case CT_PUSHBUTTON
            WinProc(WP_FILLCHARACTER, 0x00010000, ' ')
            mov ecx,0x000100FF
            add cl,m_rc.col
            mov edi,ecx
            mov esi,' '
           .gotosw(1:WP_FILLCHARACTER)
        .case CT_XCELL
        .case CT_MENUITEM
            movzx edi,m_rc.col
            shl edi,16
            mov esi,BG_MENU
           .gotosw(1:WP_FILLBACKGROUND)
        .endsw


    .case WP_SETNEXTITEM

        ; wParam: BOOL
        ; lParam: PDWND
        ; return: 0

        .for ( rbx = rsi, rbx = m_Next : rbx : rbx = m_Next )

            .if ( !Flags.Disabled && !Flags.NoFocus )

                mov rdi,rsi
                mov rsi,rbx
               .gotosw(WP_SETFOCUS)
            .endif
        .endf
        .if ( edi )
            .for ( rbx = [rsi].Doszip.m_Base, rbx = m_This : rbx : rbx = m_Next )
                .if ( !Flags.Disabled && !Flags.NoFocus )
                    mov rdi,rsi
                    mov rsi,rbx
                   .gotosw(WP_SETFOCUS)
                .endif
            .endf
        .endif


    .case WP_SETPREVITEM

        ; wParam: BOOL
        ; lParam: PDWND

        .for ( rbx = rsi, rbx = m_Prev : rbx : rbx = m_Prev )

            .if ( !Flags.Disabled && !Flags.NoFocus )

                mov rdi,rsi
                mov rsi,rbx
               .gotosw(WP_SETFOCUS)
            .endif
        .endf
        .if ( edi )
            .for ( rbx = [rsi].Doszip.m_Base, rbx = m_This : m_Next : rbx = m_Next )
            .endf
            .for ( : rbx : rbx = m_Prev )
                .if ( !Flags.Disabled && !Flags.NoFocus )

                    mov rdi,rsi
                    mov rsi,rbx
                   .gotosw(WP_SETFOCUS)
                .endif
            .endf
        .endif


    .case WP_SETLEFTITEM

        ; lParam: PDWND

        mov rbx,rsi
        mov al,m_rc.y

        .for ( rbx = m_Prev : rbx : rbx = m_Prev )

            .if ( al == m_rc.y && !Flags.Disabled && !Flags.NoFocus )

                mov rsi,rbx
               .gotosw(WP_SETFOCUS)
            .endif
        .endf
        .gotosw(WP_SETPREVITEM)


    .case WP_SETRIGHTITEM

        ; lParam: PDWND

        mov rbx,rsi
        mov al,m_rc.y

        .for ( rbx = m_Next : rbx : rbx = m_Next )

            .if ( al == m_rc.y && !Flags.Disabled && !Flags.NoFocus )

                mov rsi,rbx
               .gotosw(WP_SETFOCUS)
            .endif
        .endf
        .gotosw(WP_SETNEXTITEM)


    .case WP_INITITEM

        ; wParam: LPSTR
        ; lParam: PDWND

        mov rbx,rsi
        movzx eax,m_rc.col
        shl eax,16
        mov rc,eax
        mov eax,m_Type
        .switch eax
        .case CT_PUSHBUTTON
            mov     eax,' '
            mov     ecx,U_BLACK_POINTER_RIGHT
            mov     esi,U_BLACK_POINTER_LEFT
            cmp     Flags.HasFocus,0
            cmovz   ecx,eax
            cmovz   esi,eax
            WinProc(WP_FILLCHARACTER, 0x01010000, ecx)
            mov     ecx,0x000100FF
            add     cl,rc.col
            mov     edi,ecx
           .gotosw(1:WP_FILLCHARACTER)
        .case CT_RADIOBUTTON
            mov     eax,' '
            mov     esi,U_BULLET_OPERATOR
            cmp     Flags.Checked,0
            cmovz   esi,eax
            mov     edi,0x01010001
           .gotosw(1:WP_FILLCHARACTER)
        .case CT_CHECKBOX
            mov     eax,' '
            mov     esi,'x'
            cmp     Flags.Checked,0
            cmovz   esi,eax
            mov     edi,0x01010001
           .gotosw(1:WP_FILLCHARACTER)
        .case CT_XCELL
        .case CT_MENUITEM
        .case CT_TEXTITEM
            .if ( Flags.HasFocus )
                movzx edi,m_rc.col
                shl edi,16
                mov esi,BG_INVERSE
               .gotosw(1:WP_FILLBACKGROUND)
            .endif
           .endc
        .case CT_TEXTINPUT
            WinProc(WP_FILLCHARINFO, rc, Edit.m_Attribute)
            .if ( rdi )
                WinProc(WP_WRITESTRING, rc, rdi)
            .endif
           .endc
        .endsw

    .case WP_SETDLGFLAGS

        ; wParam: DWORD { Flags }
        ; lParam: PDWND { Dialog }

        .for ( rbx = m_This : rbx && m_Id < esi : rbx = m_Next )
            shr edi,1
            .ifc
                mov Flags.Checked,1
                WinProc(WP_INITITEM, 0, rbx)
            .endif
        .endf

    .case WP_GETDLGFLAGS

        ; wParam: DWORD { Result }
        ; lParam: DWORD { Last Id }
        ; return: DWORD { eax: mask, edx: bits set }

        mov eax,edi
        .if ( eax )
            .if WinProc(WP_GETOBJECT, esi, m_This)
                .for ( rbx = rax, edx = 0, eax = 0 : rbx : rbx = m_Prev, eax <<= 1, edx <<= 1 )
                    or eax,1
                    .if ( Flags.Checked )
                        or edx,1
                    .endif
                .endf
                shr eax,1
                shr edx,1
            .endif
        .endif
        .return


    .case WP_SIZE

        ; lParam: COORD

        mov rbx,m_Home
        .if ( Flags.Open )
            mov Flags.Open,0
            free(m_Window)
        .endif

        .if GetConsoleScreenBufferInfo(_confh, &ci)

            SetConsoleCursorPosition(_confh, 0)

            mov eax,esi
            .if al > MAXCOLS
                mov al,MAXCOLS
            .elseif al < MINCOLS
                mov al,MINCOLS
            .endif
            mov m_rc.col,al
            mov eax,esi
            shr eax,16
            .if al > MAXROWS
                mov al,MAXROWS
            .elseif al < MINROWS
                mov al,MINROWS
            .endif
            mov m_rc.row,al
            movzx eax,m_rc.col
            movzx edx,m_rc.row
            dec eax
            dec edx
            .if ( ax != ci.srWindow.Right || dx != ci.srWindow.Bottom )
                mov ci.srWindow.Top,0
                mov ci.srWindow.Left,0
                mov ci.srWindow.Right,ax
                mov ci.srWindow.Bottom,dx
                SetConsoleWindowInfo(_confh, 1, &ci.srWindow)
            .endif
            movzx edx,m_rc.row
            shl edx,16
            mov dl,m_rc.col
            SetConsoleScreenBufferSize(_confh, edx)
            .if malloc(GetWindowSize(m_rc))
                mov Flags.Open,1
                mov m_Window,rax
                mov edi,m_rc
                mov rsi,rax
               .gotosw(WP_READWINDOW)
            .endif
        .endif

    .case WP_QUIT

        ; wParam: RetVal
        ; lParam: PDWND

        mov     ecx,1
        mov     eax,m_msgCount
        inc     eax
        cmp     eax,MAXMESSAGE
        cmovnb  eax,ecx
        mov     m_msgCount,eax
        dec     eax
        imul    eax,eax,Message
        lea     rcx,m_msgStack
        add     rcx,rax
        mov     [rcx].Message.uMsg,WP_QUIT
        mov     [rcx].Message.wParam,rdi
        xor     eax,eax
        mov     [rcx].Message.lParam,rsi


    .case WP_NCHITTEST

        ; wParam: PDWND
        ; lParam: COORD

        mov rbx,rdi
        .if ( !rbx || ( !Flags.Child && ( !Flags.Open || !Flags.Visible ) ) )
            .return( HTERROR )
        .endif

        mov edx,esi ; Get the window-line of pos
        mov eax,m_rc

        .if ( Flags.Child )

            mov rcx,m_Base
            add al,[rcx].Doszip.m_rc.x
            add ah,[rcx].Doszip.m_rc.y
        .endif

        mov rc,eax
        mov ecx,eax
        xor eax,eax
        mov dh,cl

        .if ( dl >= dh )

            add dh,rc.col
            .if ( dl < dh )

                shr edx,16
                mov dh,ch
                .if ( dl >= dh )

                    add dh,rc.row
                    .if ( dl < dh )

                        mov al,dl
                        sub al,ch
                        inc al
                    .endif
                .endif
            .endif
        .endif
        .if ( eax == 0 )
            .return( HTNOWHERE )
        .endif

        .if ( Flags.Child )
            mov rdx,rbx
            .if ( Flags.AutoExit )
                .return ( HTCLOSE )
            .endif
            .return ( HTSYSMENU )
        .endif
        .if ( eax == 1 && Flags.Moveable )
            .return( HTCAPTION )
        .endif

        mov edi,eax
        dec eax
        mov ch,al
        mov eax,esi
        sub al,rc.x
        mov cl,al

        .for ( rbx = m_This : rbx : rbx = m_Next )

            mov eax,m_rc
            mov edx,eax
            shr edx,16
            add dl,al
            .if ( cl >= al && cl < dl && ch == ah && !Flags.Disabled )

                mov rdx,rbx
                .if ( Flags.AutoExit )
                    .return ( HTCLOSE )
                .endif
                .return ( HTSYSMENU )
            .endif
        .endf
        mov al,rc.col
        dec al
        mov ah,rc.row
        dec ah
        .if ( ch == 0 )
            .if ( cl == 0 )
                .return( HTTOPLEFT )
            .elseif ( cl == al )
                .return( HTTOPRIGHT )
            .endif
            .return( HTTOP )
        .elseif ( ch == ah )
            .if ( cl == 0 )
                .return( HTBOTTOMLEFT )
            .elseif ( cl == al )
                .return( HTBOTTOMRIGHT )
            .endif
            .return( HTBOTTOM )
        .endif
        .if ( cl == 0 )
            .return( HTLEFT )
        .elseif ( cl == al )
            .return( HTRIGHT )
        .endif
        .return( HTCLIENT )


    .case WP_SETDIALOG

        mov rbx,rsi
        mov rsi,m_Home
        mov eax,m_Id
        .switch pascal eax

        .case ID_PANELA
            .if ( eax == ID_PANELA )
                mov m_rc.x,0
                mov ecx,CI_PANELA
            .endif
            .if WinProc(WP_GETOBJECT, ecx, m_Home)
                mov esi,[rax].Doszip.Panel.Flags
                .for ( edi = 0, rbx = m_This : edi < 6 : edi++, rbx = m_Next )
                    bt esi,edi
                    .ifc
                        WinProc(WP_FILLCHARACTER, 0x010100FF, U_RIGHT_DOUBLE_QUOTE)
                    .endif
                .endf
                xor ecx,ecx
                .if ( esi & maskof(PanelClass.Flags.NoSort) )
                    mov ecx,4
                .elseif ( esi & maskof(PanelClass.Flags.Sorttype) )
                    mov ecx,esi
                    and ecx,maskof(PanelClass.Flags.Sorttype)
                    shr ecx,PanelClass.Flags.Sorttype
                .endif
                .while ecx
                    mov rbx,m_Next
                    dec ecx
                .endw
                WinProc(WP_FILLCHARACTER, 0x010100FF, U_BULLET_OPERATOR)
            .endif
        .case ID_PANELB
            mov m_rc.x,40
            mov ecx,CI_PANELB
           .gotosw(ID_PANELA)

        .case ID_TOOLS

        .case ID_CONFIGURATION
            .if WinProc(WP_GETOBJECT, DI_CF_AUTOSAVE, m_This)
                mov rbx,rax
                mov rcx,m_Home
                .if ( [rcx].Doszip.Setup.AutoSaveSetup )
                    mov Flags.Checked,1
                .endif
                WinProc(WP_INITITEM, 0, rbx)
            .endif

        .case ID_SYSTEMOPTIONS
            mov edi,[rsi].Doszip.Setup
            shr edi,Doszip.Setup.UseBeep
            mov esi,DI_SO_OK
           .gotosw(1:WP_SETDLGFLAGS)

        .case ID_SCREENOPTIONS
            mov edi,[rsi].Doszip.Setup
            shr edi,Doszip.Setup.MenuBar
            mov esi,DI_SC_ATTRIB
           .gotosw(1:WP_SETDLGFLAGS)

        .case ID_PANELOPTIONS
            mov edi,[rsi].Doszip.Panels
            shr edi,Doszip.Panels.InsertMoves
            mov esi,DI_PO_OK
           .gotosw(1:WP_SETDLGFLAGS)

        .case ID_TEOPTIONS
            WinProc(WP_SETDLGFLAGS, [rsi].Doszip.Editor, DI_TEO_TABSIZE)
            .if WinProc(WP_GETOBJECT, DI_TEO_TABSIZE, m_This)
                mov rbx,rax
                mov ecx,[rsi].Doszip.Editor.TabSize
                mov edi,2
                shl edi,cl
                mov rbx,m_This
                mov ecx,_swprintf(Line.m_TBuf, L"%u", edi)
                WinProc(WP_SETTEXT, ecx, Line.m_TBuf)
                mov rcx,m_Text
                mov rbx,m_Base
                WinProc(WP_INITITEM, rcx, rbx)
            .endif

        .case ID_CONFIRMATIONS
            movzx edi,[rsi].Doszip.Confirm
            mov esi,DI_CN_OK
           .gotosw(1:WP_SETDLGFLAGS)

        .case ID_COMPRESSION

        .case ID_EDITCOLOR
            mov hwnd,WinProc(WP_BEGINPAINT, 0, rbx)
            WinProc(WP_UNPACKWINDOW, m_Resource, rbx)

            .for ( rbx = m_This, edi = 0 : edi < 32 : edi++, rbx = m_Next )

                movzx eax,m_rc.col
                shl   eax,16
                mov   al,2
                mov   rc,eax
                lea   rdx,at_foreground
                movzx ecx,byte ptr [rdx+rdi]
                .if ( ecx & 0xF0 )
                    shr ecx,4
                .endif
                WinProc(WP_WRITEFORMAT, rc, L"%X", rcx)
                .if ( edi < 16 || edi >= 30 )
                    mov rc.x,8
                    mov rc.col,14
                    .if ( edi >= 30 )
                        dec rc.x
                        add rc.col,4
                    .endif
                    WinProc(WP_FILLFOREGROUND, rc, rdi)
                .else
                    mov rc.x,7
                    mov rc.col,18
                    lea ecx,[rdi-16]
                    WinProc(WP_FILLBACKGROUND, rc, rcx)
                .endif
            .endf
            WinProc(WP_ENDPAINT, hwnd, m_Base)

        .case ID_CALENDAR
            mov hwnd,WinProc(WP_BEGINPAINT, 0, rbx)
            WinProc(WP_UNPACKWINDOW, m_Resource, rbx)
            GetLocalTime(&ts)
            .if ( Calendar.m_CurYear == 0 )
                movzx eax,ts.wDay
                mov Calendar.m_Day,eax
                mov Calendar.m_CurDay,eax
                mov ax,ts.wMonth
                mov Calendar.m_Month,eax
                mov Calendar.m_CurMonth,eax
                mov ax,ts.wYear
                mov Calendar.m_Year,eax
                mov Calendar.m_CurYear,eax
            .endif
            WinProc(WP_WRITEFORMAT, 0x000A0102, L"%02u:%02u:%02u", ts.wHour, ts.wMinute, ts.wSecond)
            lea rsi,cp_Month
            mov ecx,Calendar.m_CurMonth
            mov rcx,[rsi+rcx*size_t-size_t]
            WinProc(WP_WRITEFORMAT, 0x0B100302, L"%s %d", rcx, Calendar.m_CurYear)
            mov ecx,Calendar.m_Month
            mov rcx,[rsi+rcx*size_t-size_t]
            WinProc(WP_WRITEFORMAT, 0x00100504, L"%s %d", rcx, Calendar.m_Year)

            mov Calendar.m_WeekDay,GetWeekDay(Calendar.m_Year, Calendar.m_Month, 0)
            mov Calendar.m_DaysInMonth,DaysInMonth(Calendar.m_Year, Calendar.m_Month)

            .for ( rc.col = 2, esi = 0, edi = 3 : esi < Calendar.m_DaysInMonth && edi < 10 : edi++ )

                .for ( ecx = 0 : ecx < 7 : ecx++ )

                    mov eax,3 ; first line

                    .if ( ( Calendar.m_WeekDay <= ecx && edi == eax ) ||
                        ( ( Calendar.m_WeekDay > ecx || edi != eax ) && edi > eax && esi < Calendar.m_DaysInMonth ) )

                        inc esi
                        mov u1,ecx
                        mov rc.row,0
                        .if ( esi == Calendar.m_Day )
                            mov rc.row,0x06
                        .endif
                        lea rax,cl_Keypos
                        mov al,[rax+rcx]
                        add al,3
                        mov rc.x,al
                        lea eax,[rdi+6]
                        mov rc.y,al
                        WinProc(WP_WRITEFORMAT, rc, L"%2d", esi)
                        .if ( Calendar.m_CurDay == esi )
                            .if ( Calendar.m_CurMonth == Calendar.m_Month )
                                .if ( Calendar.m_CurYear == Calendar.m_Year )
                                    WinProc(WP_FILLATTRIBUTE, rc, 0x0B)
                                .endif
                            .endif
                        .endif
                        mov ecx,u1
                    .endif
                .endf
            .endf
            WinProc(WP_ENDPAINT, hwnd, rbx)
        .endsw


    .case WP_ENDDIALOG

        mov rsi,rbx
        mov eax,m_Id
        .switch eax
        .case ID_PANELA
        .case ID_FILE
        .case ID_EDIT
        .case ID_SETUP
        .case ID_TOOLS
        .case ID_HELP
        .case ID_PANELB
            .if ( edi )
                PostMessage(WP_COMMAND, rdi, rsi)
            .endif
            .endc
        .case ID_CONFIGURATION
            .endc .if ( edi == 0 )
            xor ecx,ecx
            .switch pascal edi
            .case DI_CF_SYSTEM   : mov ecx,ID_SYSTEMOPTIONS
            .case DI_CF_SCREEN   : mov ecx,ID_SCREENOPTIONS
            .case DI_CF_PANEL    : mov ecx,ID_PANELOPTIONS
            .case DI_CF_EDITOR   : mov ecx,ID_TEOPTIONS
            .case DI_CF_CONFIRM  : mov ecx,ID_CONFIRMATIONS
            .case DI_CF_COMPRESS : mov ecx,ID_COMPRESSION
            .endsw
            .if ( ecx )
                WinProc(WP_RUNDIALOG, ecx, rbx)
               .return( 1 )
            .endif
            .if WinProc(WP_GETOBJECT, DI_CF_AUTOSAVE, m_This)
                mov rbx,rax
                .if ( Flags.Checked )
                    mov rbx,m_Home
                    mov Setup.AutoSaveSetup,1
                .endif
            .endif
            .endc
        .case ID_SYSTEMOPTIONS
            .ifd WinProc(WP_GETDLGFLAGS, edi, DI_SO_ESCUSERSCREEN)
                mov rbx,[rsi].Doszip.m_Home
                shl eax,1
                shl edx,1
                not eax
                and Setup,eax
                or  Setup,edx
            .endif
            .endc
        .case ID_SCREENOPTIONS
            .endc .ifd !WinProc(WP_GETDLGFLAGS, edi, DI_SC_KEYBAR)
            mov rbx,[rsi].Doszip.m_Home
            shl eax,Doszip.Setup.MenuBar
            not eax
            shl edx,Doszip.Setup.MenuBar
            and Setup,eax
            or  Setup,edx
            mov rbx,rsi
            xor ecx,ecx
            .switch pascal edi
            .case DI_SC_ATTRIB   : mov ecx,ID_EDITCOLOR
            .case DI_SC_STANDARD : mov ecx,ID_DEFAULTCOLOR
            .case DI_SC_LOAD
            .case DI_SC_SAVE
            .endsw
            .if ( ecx )
                WinProc(WP_RUNDIALOG, ecx, rbx)
               .return( 1 )
            .endif
            .endc
        .case ID_PANELOPTIONS
            .ifd WinProc(WP_GETDLGFLAGS, edi, DI_PO_CDRDONLY)
                mov rbx,[rsi].Doszip.m_Home
                shl eax,Doszip.Panels.InsertMoves
                shl edx,Doszip.Panels.InsertMoves
                not eax
                and Panels,eax
                or  Panels,edx
            .endif
            .endc
        .case ID_TEOPTIONS
            .ifd WinProc(WP_GETDLGFLAGS, edi, DI_TEO_UNIXMODE)
                mov rbx,[rsi].Doszip.m_Home
                not eax
                and Editor,eax
                or  Editor,edx
            .endif
            .endc
        .case ID_CONFIRMATIONS
            .ifd WinProc(WP_GETDLGFLAGS, edi, DI_CN_EXIT)
                mov rbx,[rsi].Doszip.m_Home
                not eax
                and Confirm,al
                or  Confirm,dl
            .endif
            .endc
        .case ID_COMPRESSION
            .endc
        .case ID_DEFAULTCOLOR
            xor edx,edx
            .switch pascal edi
            .case DI_DC_DEFAULT : lea rdx,at_Blue
            .case DI_DC_BWBLACK : lea rdx,at_Black
            .case DI_DC_BWMONO  : lea rdx,at_Mono
            .case DI_DC_BWWHITE : lea rdx,at_White
            .case DI_DC_NORTON  : lea rdx,at_Norton
            .endsw
            .if ( rdx )
                lea  rdi,at_foreground
                mov  ecx,32
                xchg rdx,rsi
                rep  movsb
                mov  rsi,rdx
                mov  rbx,m_Home
                xor  Setup.MenuBar,1
                PostMessage(WP_COMMAND, CM_TOGGLEMENUBAR, rbx)
                .if WinProc(WP_GETOBJECT, ID_CONFIGURATION, rbx)
                    mov rbx,rax
                    .if ( Flags.Open )
                        PostMessage(WP_QUIT, 0, rbx)
                    .endif
                    PostMessage(WP_QUIT, 0, rsi)
                .endif
            .endif
            .endc
        .case ID_CALENDAR
            mov Calendar.m_CurYear,0
        .endsw
        mov rbx,rsi
        WinProc(WP_CURSORSET, 0, &m_Cursor)
        WinProc(WP_OPENRESOURCE, FALSE, rbx)


    .case WP_RUNDIALOG
        .if WinProc(WP_GETOBJECT, edi, m_Home)
            mov rbx,rax
            .ifd WinProc(WP_OPENRESOURCE, TRUE, rax)

                WinProc(WP_SETDIALOG, 0, rbx)
                WinProc(WP_CURSORGET, 0, &m_Cursor)
                mov rcx,m_Resource
                movzx eax,[rcx].RIDD.index
                .if WinProc(WP_GETINDEX, eax, rbx)
                    mov [rax].Doszip.Flags.HasFocus,1
                    WinProc(WP_INITITEM, 0, rax)
                .endif
                WinProc(WP_SHOWWINDOW, TRUE, rbx)
                .repeat
                    .whiled WinProc(WP_GETMESSAGE, &msg, rbx)
                        WinProc(msg.uMsg, msg.wParam, msg.lParam)
                    .endw
                .untild !WinProc(WP_ENDDIALOG, msg.wParam, rbx)
                mov rax,msg.wParam
            .endif
        .endif
        .return


    .case WP_INITCOMMANDLINE

        mov rbx,m_Home
        mov rbx,m_Command
        .if ( Flags.Open )

            mov rsi,Command.m_Path
            mov rdi,[rsi].Doszip.Panel.m_srcPath
            .if ( word ptr [rdi] == 0 )
                GetCurrentDirectoryW(WMAXPATH, rdi)
            .endif

            wcslen(rdi)
            inc eax
            .if eax > 51
                mov eax,51
            .endif
            or      eax,0x01000000
            movzx   ecx,m_rc.col
            sub     cl,al
            shl     ecx,16
            or      eax,ecx
            mov     rdx,m_This
            mov     [rdx].Doszip.m_rc,eax
            mov     rc,eax

            .if ( Flags.Visible )

                WinProc(WP_SETCURSOR, TRUE, eax)
                movzx ecx,rc.x
                dec rc.x
                mov rc.col,1
                shl ecx,16
                WinProc(WP_WRITEPATH, ecx, rdi)
                WinProc(WP_FILLCHARACTER, rc, '>')
            .endif
        .endif


    .case WP_SETCOMMANDLINE

        mov rbx,m_Home
        mov rbx,m_Command
        mov Command.m_Path,rsi
       .gotosw(WP_INITCOMMANDLINE)


    .case WP_SHOWCOMMANDLINE

        ; wParam: BOOL
        ; return: BOOL

        mov rbx,m_Home
        .if ( edi == FALSE )
            WinProc(WP_OPENWINDOW, FALSE, m_Command)
           .gotosw(WP_CURSOR)
        .endif

        mov rdi,m_PanelB
        .if ( ![rdi].Doszip.Flags.Visible )
            mov rdi,m_PanelA
        .endif
        mov eax,m_rc
        mov rbx,m_Command
        mov m_rc,eax
        mov m_rc.row,1
        xor eax,eax
        .if ( [rdi].Doszip.Flags.Visible )
            mov dl,[rdi].Doszip.m_rc.y
            add dl,[rdi].Doszip.m_rc.row
            .if dl > al
                mov al,dl
            .endif
        .endif
        mov rdi,rbx
        mov rbx,m_Home
        .if ( !eax && Setup.MenuBar )
            inc eax
        .endif
        .if ( al >= m_rc.row && Setup.KeyBar )
            dec eax
        .endif
        .if ( al > m_rc.row )
            mov al,m_rc.row
        .endif
        cmp Setup.CommandLine,0
        mov rbx,rdi
        mov m_rc.y,al
        .ifnz
            WinProc(WP_OPENWINDOW, TRUE, rbx)
            WinProc(WP_FLIPWINDOW, FALSE, MKAT(0, 7, ' '))
            WinProc(WP_SHOWWINDOW, TRUE, rbx)
           .gotosw(WP_INITCOMMANDLINE)
        .endif


    .case WP_OPENSCROLLBAR

        ; wParam: PDWND
        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        .if ( Flags.Open )
            WinProc(WP_OPENWINDOW, FALSE, rbx)
        .endif

        mov     rbx,rdi
        mov     eax,m_rc
        inc     ah
        add     al,m_rc.col
        dec     al
        mov     rbx,rsi
        mov     m_rc,eax
        mov     m_rc.col,1
        sub     m_rc.row,2
        movzx   ecx,ah
        shl     ecx,16
        mov     cl,al
        movzx   eax,m_rc.row
        mov     edx,1

        .if ( m_Id == CI_SCROLLE )
            add al,2
            sub al,Edit.m_Rows
        .elseif ( m_Id == CI_SCROLLP )
            mov al,Panel.m_YCells
            mov dl,Panel.m_XCells
        .endif
        mov Scroll.m_Count,edx
        mov Scroll.m_Lines,eax

        ReadConsoleOutputAttribute(_confh, &Scroll.m_Attribute, 1, ecx, &u1)

        .ifd WinProc(WP_OPENWINDOW, TRUE, rbx)

            mov     rdi,m_Window
            mov     eax,Scroll.m_Attribute
            shl     eax,16
            mov     ax,0x25B2
            stosd
            mov     ax,0x2591
            movzx   ecx,m_rc.row
            sub     ecx,2
            rep     stosd
            mov     ax,0x25BC
            stosd
            mov     eax,1
        .endif


    .case WP_SETSCROLLBAR

        ; wParam: DWORD { Position }
        ; lParam: DWORD { Count }

        cvtsi2ss    xmm1,esi
        cvtsi2ss    xmm2,Scroll.m_Count
        divss       xmm1,xmm2
        cvtsi2ss    xmm4,edi
        divss       xmm4,xmm2
        cvtsi2ss    xmm0,Scroll.m_Lines
        movss       xmm2,xmm0
        subss       xmm2,2.0        ; view - arrow
        movss       xmm3,xmm0       ; thumb = (view / content) * (view - arrow)
        divss       xmm3,xmm1       ; view / content
        mulss       xmm3,xmm2       ; * (view - arrow)
        maxss       xmm3,1.0
        minss       xmm3,xmm2
        subss       xmm1,xmm0       ; offset = pos / ((content - view) / (view - thumb))
        subss       xmm0,xmm3       ; view - thumb
        divss       xmm1,xmm0
        divss       xmm4,xmm1       ; pos / ratio
        cvtss2si    eax,xmm4
        cvtss2si    ecx,xmm3
        mov         Scroll.m_Thumb,ecx
        movzx       edx,m_rc.row
        sub         edx,2
        add         ecx,eax

        .if ( ecx > edx )
            mov eax,edx
            sub eax,Scroll.m_Thumb
        .endif
        mov Scroll.m_Offset,eax
        .if ( Flags.Open )
            xor esi,esi
            .if ( Flags.Visible )
                WinProc(WP_SHOWWINDOW, FALSE, rbx)
                inc esi
            .endif
            movzx   ecx,m_rc.row
            sub     ecx,2
            mov     rdi,m_Window
            add     rdi,4
            mov     eax,Scroll.m_Attribute
            shl     eax,16
            mov     ax,0x2591
            rep     stosd
            mov     eax,0x00872591
            mov     edx,Scroll.m_Offset
            mov     ecx,Scroll.m_Thumb
            mov     rdi,m_Window
            lea     rdi,[rdi+rdx*4+4]
            rep     stosd
            .if ( esi )
                WinProc(WP_SHOWWINDOW, TRUE, rbx)
            .endif
        .endif


    .case WP_SCROLLACTION

        ; wParam: COORD
        ; lParam: PDWND
        ; return: ScrollAction

        mov     rbx,rsi
        movzx   edx,di
        mov     eax,edi
        shr     eax,16

        .if ( dl != m_rc.x || al < m_rc.y )
            .return( ScrollNoAction )
        .endif
        mov dl,m_rc.y
        .if ( al == dl )
            .return( ScrollMoveUp )
        .endif
        add dl,m_rc.row
        dec dl
        .if ( al == dl )
            .return( ScrollMoveDown )
        .endif
        mov dl,m_rc.y
        inc dl
        add edx,Scroll.m_Offset
        .if ( al < dl )
            .return( ScrollPageUp )
        .endif
        add edx,Scroll.m_Thumb
        .if ( al >= dl )
            .return( ScrollPageDown )
        .endif
        .return( ScrollMove )


    .case WP_PANELSTATE

        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        xor eax,eax
        .if ( Flags.Open )
            ;.if ( rax != m_This )
                inc eax
            ;.endif
        .endif
        .return


    .case WP_HIDEPANEL

        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        xor eax,eax
        .if ( Panel.Flags.Hidden )
            mov Panel.Flags.Hidden,0
            mov eax,1
        .elseif ( Panel.Flags.Visible )
            mov Panel.Flags.Visible,0
            WinProc(WP_SHOWWINDOW, FALSE, rbx)
            mov eax,1
        .endif
        .return


    .case WP_CREATEPANEL

        ; wParam: BOOL
        ; lParam: PDWND
        ; return: BOOL

        .if ( edi == FALSE )

            mov rbx,rsi
            xor eax,eax
            .if ( Panel.Flags.Visible )
                WinProc(WP_HIDEPANEL, 0, rbx)
                WinProc(WP_OPENWINDOW, FALSE, rbx)
                mov eax,1
            .endif
            .return
        .endif

        WinProc(WP_SHOWCOMMANDLINE, FALSE, 0)

        mov     rbx,m_Home
        xor     edx,edx
        movzx   eax,m_rc.col
        shr     eax,1
        mov     ah,m_rc.row
        mov     ch,9
        .if ( Setup.CommandLine )
            dec ah      ; rows--
        .endif
        .if ( Setup.MenuBar )
            inc dh      ; y++
            dec ah      ; rows--
        .endif
        .if ( Setup.KeyBar )
            dec ah      ; rows--
        .endif
        .if ( Panels.Horizontal && !Panels.WideView )
            shr ah,1    ; rows / 2
            dec ch
        .endif
        mov cl,ah
        sub cl,ch       ; rows - ch (size)
        movzx edi,cl
        mov ecx,Panels.PanelSize
        .if ( edi < ecx )
            mov ecx,edi
        .endif
        mov Panels.PanelSize,ecx
        sub ah,cl
        .if ( Panels.Horizontal )
            mov al,m_rc.col ; cols = 80
            .if ( [rsi].Doszip.Panel.Flags.PanelID && !Panels.WideView )
                add dh,ah   ; y += rows
            .endif
        .elseif ( [rsi].Doszip.Panel.Flags.PanelID && !Panels.WideView )
            mov dl,m_rc.col ; x = 40
            shr dl,1
        .endif
        mov rc.x,dl
        mov rc.y,dh
        mov rc.col,al
        mov rc.row,ah
        xor ecx,ecx
        .if ( Panels.Horizontal )
            mov ecx,2
        .endif
        .if ( [rsi].Doszip.Panel.Flags.Detail )
            inc ecx
        .endif
        .if ( [rsi].Doszip.Panel.Flags.LongNames )
            add ecx,4
        .endif
        .if ( [rsi].Doszip.Panel.Flags.WideView )
            mov ecx,8
            .if ( Panels.Horizontal )
                inc ecx
            .endif
        .endif
        movzx eax,m_rc.col
        mov rbx,rsi
        mov Panel.m_celType,ecx
        mov rr,0x01260201
        mov edx,38
        .switch pascal ecx
        .case VerticalShortList
            mov edx,12
        .case HorizontalShortList
            mov edx,12
        .case HorizontalShortDetail
            mov edx,78
        .case VerticalLongList
            mov edx,18
        .case HorizontalLongList
            mov edx,18
        .case HorizontalLongDetail
            mov edx,78
        .case HorizontalWide
            mov edx,78
        .endsw
        .if ( edx != 78 )
            shr eax,1
            .if ( edx != 38 )
                .if ( edx == 18 )
                    shr eax,1
                .else
                    mov eax,14
                .endif
            .endif
        .endif
        sub eax,2
        mov rr.col,al
        mov eax,rr
        add ax,word ptr rc
        mov rl,eax
        mov Panel.m_celFirst,eax
        mov al,rc.row
        sub al,3
        mov Panel.m_YCells,al
        movzx eax,rc.col
        dec al
        mov cl,rl.col
        inc cl
        div cl
        mov Panel.m_XCells,al
        WinProc(WP_OPENWINDOW, FALSE, rbx)
        mov m_rc,rc
        WinProc(WP_OPENWINDOW, TRUE, rbx)
        WinProc(WP_FILLWINDOW, TRUE, MKAT(BG_PANEL, FG_PANEL, ' '))
        mov rc.x,0
        mov rc.y,0
        .if ( Panel.Flags.MiniStatus )
            mov al,2
            sub rc.row,al
            sub Panel.m_YCells,al
            .if ( Panel.Flags.DriveInfo )
                inc al
                sub rc.row,al
                sub Panel.m_YCells,al
                mov rbx,m_Home
                .if ( Panels.Horizontal )
                    dec rc.row
                    dec Panel.m_YCells
                .endif
                mov rbx,rsi
            .endif
            WinProc(WP_WRITEFRAME, rc, MKAT(BG_PANEL, FG_FRAME, BOX_SINGLE))
        .endif
        mov rl,rc
        mov al,rr.col
        add al,2
        mov rl.col,al
        mov eax,Panel.m_celType
        .switch eax
        .case VerticalShortList
        .case HorizontalShortList
        .case VerticalLongList
        .case HorizontalLongList
        .case VerticalWide
        .case HorizontalWide
            WinProc(WP_WRITEFRAME, rl, MKAT(BG_PANEL, FG_FRAME, BOX_SINGLE_VERTICAL))
            mov     ecx,rl
            and     ecx,0x00FFFFFF
            inc     ch
            WinProc(WP_WRITECENTER, rcx, L"Name")
            movzx   eax,rr.col
            inc     eax
            movzx   ecx,rl.x
            add     ecx,eax
            .endc   .if ch
            add     rl.x,al
            add     eax,ecx
            .endc   .if ah
            movzx   ecx,rl.col
            add     eax,ecx
            .endc   .if ah
            .gotosw(HorizontalWide) .if ( al <= rc.col )
            mov al,rr.col
            add al,2
            .if al != rc.col
                WinProc(WP_WRITEFRAME, rl, MKAT(BG_PANEL, FG_FRAME, BOX_SINGLE_VERTICAL))
                inc rl.y
                mov rl.row,0
                WinProc(WP_WRITECENTER, rl, L"Name")
            .endif
            .endc
        .case VerticalShortDetail
        .case HorizontalShortDetail
        .case HorizontalLongDetail
            sub rl.col,6
            WinProc(WP_WRITEFRAME, rl, MKAT(BG_PANEL, FG_FRAME, BOX_SINGLE_VERTICAL))
            sub rl.col,9
            WinProc(WP_WRITEFRAME, rl, MKAT(BG_PANEL, FG_FRAME, BOX_SINGLE_VERTICAL))
            sub rl.col,11
            WinProc(WP_WRITEFRAME, rl, MKAT(BG_PANEL, FG_FRAME, BOX_SINGLE_VERTICAL))
            inc rl.y
            mov rl.row,0
            WinProc(WP_WRITECENTER, rl, L"Name")
            mov al,rl.col
            mov rl.x,al
            mov rl.col,11
            WinProc(WP_WRITECENTER, rl, L"Size")
            add rl.x,11
            mov rl.col,9
            WinProc(WP_WRITECENTER, rl, L"Date")
            add rl.x,9
            mov rl.col,6
            WinProc(WP_WRITECENTER, rl, L"Time")
           .endc
        .case VerticalLongDetail
            sub rl.col,9
            WinProc(WP_WRITEFRAME, rl, MKAT(BG_PANEL, FG_FRAME, BOX_SINGLE_VERTICAL))
            sub rl.col,11
            WinProc(WP_WRITEFRAME, rl, MKAT(BG_PANEL, FG_FRAME, BOX_SINGLE_VERTICAL))
            inc rl.y
            mov rl.row,0
            WinProc(WP_WRITECENTER, rl, L"Name")
            mov al,rl.col
            mov rl.x,al
            mov rl.col,11
            WinProc(WP_WRITECENTER, rl, L"Size")
            add rl.x,11
            mov rl.col,9
            WinProc(WP_WRITECENTER, rl, L"Time")
        .endsw
        WinProc(WP_FILLCHARINFO, 0x01010102, ':')
        WinProc(WP_FILLCHARINFO, 0x01010103, 0x2193)
        mov ecx,m_rc
        xor cx,cx
        WinProc(WP_WRITEFRAME, rcx, MKAT(BG_PANEL, FG_FRAME, BOX_DOUBLE))
        .if ( !Panel.Flags.MiniStatus )
            mov ecx,0x0101FFFD
            add cl,m_rc.col
            add ch,m_rc.row
            mov edx,U_BLACK_TRIANGLE_UP
        .elseif ( Panel.Flags.DriveInfo )
            mov ecx,0x0101FA02
            add ch,m_rc.row
            mov edx,U_BLACK_TRIANGLE_DOWN
        .else
            mov ecx,0x0101FD02
            add ch,m_rc.row
            WinProc(WP_FILLCHARINFO, rcx, U_BULLET_OPERATOR)
            mov ecx,0x0101FDFD
            add cl,m_rc.col
            add ch,m_rc.row
            mov edx,U_BLACK_TRIANGLE_DOWN
        .endif
        WinProc(WP_FILLCHARINFO, rcx, rdx)
        mov rcx,m_Home
        .if ( ![rcx].Doszip.Panels.WideView || rbx == [rcx].Doszip.m_CPanel )
            WinProc(WP_SHOWWINDOW, TRUE, rbx)
            mov Panel.Flags.Visible,1
            mov Panel.Flags.Hidden,0
        .else
            mov Panel.Flags.Hidden,1
        .endif
        WinProc(WP_SHOWCOMMANDLINE, TRUE, 0)


    .case WP_SHOWPANELCELL

        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        mov eax,1

       .return


    .case WP_PANELMSG

    .case WP_PANELINFO

    .case WP_READPANEL

        ; lParam: PDWND
        ; return: DWORD { Read count }

        mov rbx,rsi
        WinProc(WP_PANELMSG, 0, rbx)
        mov rax,Panel.m_srcPath
        .if ( word ptr [rax] && Panel.Flags.RootDir )
            ReadRootdir(rbx)
            mov Panel.m_celIndex,edx
        .else
            ReadSubdir(rbx)
        .endif
        mov Panel.m_fcbCount,eax
        .if ( eax <= Panel.m_fcbIndex )
            .if eax
                dec eax
                mov Panel.m_fcbIndex,eax
                inc eax
            .else
                mov Panel.m_fcbIndex,eax
            .endif
        .endif
        .return


    .case WP_REREADPANEL

        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        xor eax,eax
        .if ( Panel.Flags.Visible )

            WinProc(WP_READPANEL, 0, rbx)
            WinProc(WP_PANELINFO, 0, rbx)
            mov eax,1
        .endif
        .return


    .case WP_ACTIVATEPANEL

        .gotosw(WP_SETCOMMANDLINE)

    .case WP_OPENPANEL

        ; wParam: BOOL
        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi

        .if ( edi == FALSE )

            .ifd WinProc(WP_PANELSTATE, 0, rbx)

                WinProc(WP_DESTROY, TRUE, m_This)
                WinProc(WP_CREATEPANEL, FALSE, rbx)
            .endif
            .endc
        .endif

        mov Panel.m_celCount,0
        mov rcx,m_Home
        mov rdi,[rcx].Doszip.m_CPanel

        .if ( rbx == rdi )

            mov rax,Panel.m_srcPath
            mov word ptr [rax],0
            WinProc(WP_SETCOMMANDLINE, 0, rbx)

            .if ( Panel.Flags.Archive )
            .endif
        .endif

        xor eax,eax
        .if ( Panel.Flags.Visible )
            WinProc(WP_REREADPANEL, 0, rbx)
            .if ( rbx == rdi )
                WinProc(WP_ACTIVATEPANEL, TRUE, rbx)
            .endif
            mov eax,1
        .endif
        .return


    .case WP_REDRAWPANEL

        ; wParam: BOOL
        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        .if ( edi )
            mov Panel.Flags.Visible,1
        .endif
        xor eax,eax
        .if ( Panel.Flags.Visible )

            WinProc(WP_CREATEPANEL, TRUE, rbx)
            WinProc(WP_PANELINFO, 0, rbx)
            mov rbx,m_Home
            mov eax,1
            .if ( rsi == m_CPanel )
                .gotosw(WP_SHOWPANELCELL)
            .endif
        .endif

    .case WP_REDRAWPANELS

        mov rbx,m_Home
        mov edi,WinProc(WP_HIDEPANEL, 0, m_PanelB)
        .ifd WinProc(WP_HIDEPANEL, 0, m_PanelA)
            WinProc(WP_REDRAWPANEL, TRUE, m_PanelA)
        .endif
        .if ( edi )
            mov rsi,m_PanelB
           .gotosw(WP_REDRAWPANEL)
        .endif


    .case WP_UPDATEPANEL

        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        .if ( Panel.Flags.Visible )

            WinProc(WP_READPANEL, 0, rbx)
            xor edi,edi
           .gotosw(WP_REDRAWPANEL)
        .endif

    .case WP_SHOWPANEL

        ; wParam: BOOL
        ; lParam: PDWND
        ; return: BOOL

        mov rbx,rsi
        .if ( edi )
            mov Panel.Flags.Visible,1
           .gotosw(WP_UPDATEPANEL)
        .endif
        WinProc(WP_DESTROY, TRUE, m_This)
       .gotosw(WP_CREATEPANEL)


    .case WP_REREADPANELS

        ; return: BOOL

        mov rbx,m_Home
        mov rsi,m_PanelB
        .ifd WinProc(WP_PANELSTATE, 0, m_PanelA)
            WinProc(WP_REREADPANEL, 0, m_PanelA)
        .endif
        .ifd WinProc(WP_PANELSTATE, 0, rsi)
            .gotosw(WP_REREADPANEL)
        .endif

    .case WP_TOGGLEPANEL

        ; lParam: PDWND

        mov rbx,m_Home
        mov rcx,m_CPanel
        mov rdi,m_PanelA
        .if ( rdi == rcx )
            mov rdi,m_PanelB
        .endif
        mov rbx,rsi
        mov rsi,rcx
        .if ( Flags.Visible )
            WinProc(WP_PANELSTATE, 0, rdi)
            .if ( eax && rbx == rsi )
                WinProc(WP_ACTIVATEPANEL, 0, rdi)
            .endif
            .if ( Flags.Visible )
                xor edi,edi
                mov rsi,rbx
               .gotosw(WP_SHOWPANEL)
            .endif
        .else
            WinProc(WP_SHOWPANEL, TRUE, rbx)
            .if ( [rsi].Doszip.Flags.Visible == 0 )
                mov rsi,rbx
               .gotosw(WP_ACTIVATEPANEL)
            .endif
        .endif


    .case WP_UPDATE

        WinProc(WP_SHOW, FALSE, 0)
        mov edi,TRUE
       .gotosw(WP_SHOW)


    .case WP_COMMAND

        xor eax,eax
        mov rbx,m_Home
        .if ( edi >= CM_ALONG && edi <= CM_ACHDRV )
            mov rbx,WinProc(WP_GETOBJECT, CI_PANELA, rbx)
            mov eax,1
        .elseif ( edi >= CM_BLONG && edi <= CM_BCHDRV )
            mov rbx,WinProc(WP_GETOBJECT, CI_PANELB, rbx)
            mov eax,2
        .elseif ( edi >= CM_CLONG && edi <= CM_CCHDRV )
            mov rbx,m_CPanel
            mov eax,3
        .endif
        .if ( eax )
            mov rsi,rbx
            .switch edi
            .case CM_ALONG
            .case CM_BLONG
            .case CM_CLONG
                xor Panel.Flags.LongNames,1
               .endc
            .case CM_ADETAIL
            .case CM_BDETAIL
            .case CM_CDETAIL
                xor Panel.Flags.Detail,1
               .endc
            .case CM_AWIDE
            .case CM_BWIDE
            .case CM_CWIDE
                xor Panel.Flags.WideView,1
               .endc
            .case CM_AHIDDEN
            .case CM_BHIDDEN
            .case CM_CHIDDEN
                xor Panel.Flags.HiddenFiles,1
               .endc
            .case CM_AMINI
            .case CM_BMINI
            .case CM_CMINI
                xor Panel.Flags.MiniStatus,1
               .endc
            .case CM_AVOLINFO
            .case CM_BVOLINFO
            .case CM_CVOLINFO
                xor Panel.Flags.DriveInfo,1
               .endc
            .case CM_ASORTNAME
            .case CM_BSORTNAME
            .case CM_CSORTNAME
                mov Panel.Flags.NoSort,0
                mov Panel.Flags.Sorttype,SortName
               .endc
            .case CM_ASORTTYPE
            .case CM_BSORTTYPE
            .case CM_CSORTTYPE
                mov Panel.Flags.NoSort,0
                mov Panel.Flags.Sorttype,SortType
               .endc
            .case CM_ASORTDATE
            .case CM_BSORTDATE
            .case CM_CSORTDATE
                mov Panel.Flags.NoSort,0
                mov Panel.Flags.Sorttype,SortDate
               .endc
            .case CM_ASORTSIZE
            .case CM_BSORTSIZE
            .case CM_CSORTSIZE
                mov Panel.Flags.NoSort,0
                mov Panel.Flags.Sorttype,SortSize
               .endc
            .case CM_ANOSORT
            .case CM_BNOSORT
            .case CM_CNOSORT
                mov Panel.Flags.NoSort,1
               .endc
            .case CM_ATOGGLE
                mov rsi,m_PanelA
               .gotosw(1:WP_TOGGLEPANEL)
            .case CM_BTOGGLE
                mov rsi,m_PanelB
               .gotosw(1:WP_TOGGLEPANEL)
            .case CM_CTOGGLE
                mov rsi,m_CPanel
               .gotosw(1:WP_TOGGLEPANEL)
            .case CM_AFILTER
            .case CM_BFILTER
            .case CM_CFILTER
               .endc
            .case CM_ASUBINFO
            .case CM_BSUBINFO
            .case CM_CSUBINFO
               .endc
            .case CM_AHISTORY
            .case CM_BHISTORY
            .case CM_CHISTORY
               .endc
            .case CM_AREREAD
            .case CM_BREREAD
            .case CM_CREREAD
               .endc
            .case CM_ACHDRV
            .case CM_BCHDRV
            .case CM_CCHDRV
               .endc
            .endsw
            .gotosw(WP_UPDATEPANEL)
        .endif

        .switch edi
        .case CM_PANELSIZEUP
            mov rdx,m_PanelA
            mov al,9
            .if ( Panels.Horizontal )
                dec al
            .endif
            .if ( [rdx].Doszip.m_rc.y != al )
                mov eax,Panels.PanelSize
                inc eax
                mov Panels.PanelSize,eax
               .gotosw(1:WP_REDRAWPANELS)
            .endif
            .endc
        .case CM_PANELSIZEDN
            .if ( Panels.PanelSize )
                mov eax,Panels.PanelSize
                dec eax
                mov Panels.PanelSize,eax
               .gotosw(1:WP_REDRAWPANELS)
            .endif
            .endc

        .case CM_RENAME
        .case CM_VIEW
        .case CM_EDIT
        .case CM_COPY
        .case CM_MOVE
        .case CM_MKDIR
        .case CM_DELETE
        .case CM_ATTRIBUTES
        .case CM_HEXEDIT
        .case CM_COMPRESS
        .case CM_DECOMPRESS
        .case CM_NEWZIP
        .case CM_SEARCH
        .case CM_HISTORY
        .case CM_SYSTEMINFO
            MessageBox( L"File", L"CM:%3d, State %04X", MB_OK, edi, esi )
           .endc

        .case CM_EXIT
            .if ( Confirm.Exit )
                .endc .ifd ( MessageBox( CP_EXIT, CP_EXITPROGRAM, MB_OKCANCEL ) != IDOK )
            .endif
            xor edi,edi
            mov rsi,rbx
           .gotosw(1:WP_QUIT)

        .case CM_SELECT
        .case CM_DESELECT
        .case CM_INVERT
        .case CM_CMPPANELS
        .case CM_CMPSUBDIR
        .case CM_MAKELIST
        .case CM_EDITENV
        .case CM_QUICSEARCH
        .case CM_ACTIVATEEDIT
            MessageBox( L"Edit", L"CM:%3d, State %04X", MB_OK, edi, esi )
           .endc

        .case CM_TOGGLEMENUBAR
            xor Setup.MenuBar,1
           .gotosw(1:WP_UPDATE)
        .case CM_TOGGLEPANELS
            mov esi,WinProc(WP_PANELSTATE, 0, m_PanelA)
            mov edi,WinProc(WP_PANELSTATE, 0, m_PanelB)
            .if ( !edi && esi )
                mov edi,CM_ATOGGLE
               .gotosw(1:WP_COMMAND)
            .elseif ( edi && !esi )
                mov edi,CM_BTOGGLE
               .gotosw(1:WP_COMMAND)
            .elseif ( edi )
                mov rsi,m_CPanel
                mov rdi,m_PanelA
                .if rsi == rdi
                    mov rdi,m_PanelB
                .endif
                WinProc(WP_SHOWPANEL, FALSE, rsi)
                WinProc(WP_SHOWPANEL, FALSE, rdi)
            .else
                WinProc(WP_SHOWCOMMANDLINE, FALSE, 0)
                mov rsi,m_CPanel
                mov rdi,m_PanelA
                .if rsi == rdi
                    mov rdi,m_PanelB
                .endif
                WinProc(WP_SHOWPANEL, TRUE, rdi)
                WinProc(WP_SHOWPANEL, TRUE, rsi)
                WinProc(WP_ACTIVATEPANEL, TRUE, rsi)
            .endif
            .endc

        .case CM_TOGGLEPANELSIZE
            xor eax,eax
            mov ecx,Panels.PanelSize
            .if ( eax == ecx )
                mov al,m_rc.row
                shr eax,1
                dec eax
            .endif
            mov Panels.PanelSize,eax
           .gotosw(1:WP_REDRAWPANELS)

        .case CM_TOGGLEHORIZONTAL
            mov eax,Panels.PanelSize
            .if ( Panels.WideView && Panels.Horizontal )
                mov Panels.WideView,0
                shl al,1
            .elseif ( Panels.Horizontal )
                mov Panels.Horizontal,0
                shl al,1
            .else
                mov Panels.WideView,1
                mov Panels.Horizontal,1
            .endif
            mov Panels.PanelSize,eax
           .gotosw(1:WP_REDRAWPANELS)

        .case CM_TOGGLECMD
            xor Setup.CommandLine,1
           .gotosw(1:WP_UPDATE)

        .case CM_TOGGLEKEYBAR
            xor Setup.KeyBar,1
           .gotosw(1:WP_UPDATE)

        .case CM_TOGGLEDESKTOPSIZE
        .case CM_DESKTOPSIZE
        .case CM_SWAPPANELS
            MessageBox( L"Setup", L"CM:%3d, State %04X", MB_OK, edi, esi )
           .endc
        .case CM_CONFIRMATION
            mov edi,ID_CONFIRMATIONS
           .gotosw(1:WP_RUNDIALOG)
        .case CM_PANELOPTIONS
            mov edi,ID_PANELOPTIONS
           .gotosw(1:WP_RUNDIALOG)
        .case CM_COMPRESSOPTIONS
            mov edi,ID_COMPRESSION
           .gotosw(1:WP_RUNDIALOG)
        .case CM_EDITOPTIONS
            mov edi,ID_TEOPTIONS
           .gotosw(1:WP_RUNDIALOG)
        .case CM_SCREENOPTIONS
            mov edi,ID_SCREENOPTIONS
           .gotosw(1:WP_RUNDIALOG)
        .case CM_SYSTEMOPTIONS
            mov edi,ID_SYSTEMOPTIONS
           .gotosw(1:WP_RUNDIALOG)
        .case CM_CONFIGURATION
            mov edi,ID_CONFIGURATION
           .gotosw(1:WP_RUNDIALOG)

        .case CM_HELP
            MessageBox( L"Help", L"CM:%3d, State %04X", MB_OK or MB_USERICON, edi, esi )
           .endc
        .case CM_ABOUT
            mov edi,ID_ABOUT
           .gotosw(1:WP_RUNDIALOG)

        .case CM_USERSCREEN
            mov rbx,m_Home
            WinProc(WP_SHOWWINDOW, FALSE, rbx)
            .whiled WinProc(WP_GETMESSAGE, &msg, rbx)
                .break .if ( msg.uMsg == WP_CHAR )
            .endw
            WinProc(WP_SHOWWINDOW, TRUE, rbx)
           .endc
        .case CM_CALENDAR
            mov edi,ID_CALENDAR
           .gotosw(1:WP_RUNDIALOG)
        .case CM_DIRECTORYINFO
            MessageBox( L"CM_DIRECTORYINFO", L"CM:%3d, State %04X", MB_OK, edi, esi )
           .endc
        .case CM_QUICKSEARCH
            MessageBox( L"CM_QUICKSEARCH", L"CM:%3d, State %04X", MB_OK, edi, esi )
           .endc

        .endsw

    .case WP_MENUCOMMAND

        ; lParam: PDWND { ID_MENUBAR->Item }

        mov rbx,rsi
        mov eax,m_Id
        xor edi,edi
        .switch pascal eax
        .case DI_MPANELA : mov edi,ID_PANELA
        .case DI_MFILE   : mov edi,ID_FILE
        .case DI_MEDIT   : mov edi,ID_EDIT
        .case DI_MSETUP  : mov edi,ID_SETUP
        .case DI_MTOOLS  : mov edi,ID_TOOLS
        .case DI_MHELP   : mov edi,ID_HELP
        .case DI_MPANELB : mov edi,ID_PANELB
        .endsw
        .endc .if ( !edi )

        WinProc(WP_READWINDOW, m_rc, &ts)
        mov rc,m_rc
        mov rc.x,0
        mov rc.y,0
        WinProc(WP_FILLATTRIBUTE, rc, MKAT(0, 15))
        mov edi,WinProc(WP_RUNDIALOG, edi, 0)
        WinProc(WP_WRITEWINDOW, m_rc, &ts)
        .if ( edi == PREV_MENU )
            mov rsi,m_Prev
            .if ( rsi == NULL )
                .for ( : m_Next : rbx = m_Next )
                .endf
                mov rsi,rbx
            .endif
            .gotosw( WP_MENUCOMMAND )
        .elseif ( edi == NEXT_MENU )
            mov rsi,m_Next
            .if ( rsi == NULL )
                mov rbx,m_Base
                mov rsi,m_This
            .endif
            .gotosw( WP_MENUCOMMAND )
        .endif

    .case WP_KEYUP


    .case WP_KEYDOWN

        ; wParam: The Char or Virtual Key Code of the key
        ; lParam: 0-15 Control Key State, 16 Virtual Key Code

        xor eax,eax
        mov ecx,m_Type
        mov edx,esi
        shr edx,16

        .if ( edx == 'X' && KeyAlt(esi) )

            .if ( ecx == CT_DESKTOP )
                mov edi,CM_EXIT
               .gotosw(WP_COMMAND)
            .elseif ( ecx == CT_DIALOG || ecx == CT_MENUDLG )
                xor edi,edi
                mov rsi,rbx
               .gotosw(WP_QUIT)
            .endif
            .endc
        .endif

        .switch ecx
        .case CT_DESKTOP

            .if ( KeyAlt(esi) && Setup.MenuBar )

                .switch edx
                .case 'A','F','E','S','T','H','B'
                    mov esi,edx
                    mov rbx,m_MenuBar
                    .if ( Flags.Open && Flags.Visible )
                        .for ( rbx = m_This : rbx : rbx = m_Next )
                            .if ( esi == m_SysKey )
                                mov rsi,rbx
                               .gotosw(2:WP_MENUCOMMAND)
                            .endif
                        .endf
                    .endif
                    .return
                .endsw
            .endif

            .if ( KeyCtrl(esi) && edx >= 'A' && edx <= 'Z' )

                .switch pascal edx
                .case 'A' : mov edi,CM_ATTRIBUTES
                .case 'B' : mov edi,CM_USERSCREEN
                .case 'C' : mov edi,CM_CMPPANELS
                .case 'D' : mov edi,CM_CSORTDATE
                .case 'E' : mov edi,CM_CSORTTYPE
                .case 'F' : mov edi,CM_CONFIRMATION
                .case 'G' : mov edi,CM_CALENDAR
                .case 'H' : mov edi,CM_CHIDDEN
                .case 'I' : mov edi,CM_DIRECTORYINFO
                .case 'J' : mov edi,CM_COMPRESSOPTIONS
                .case 'K' : mov edi,CM_TOGGLEKEYBAR
                .case 'L' : mov edi,CM_CLONG
                .case 'M' : mov edi,CM_CMINI
                .case 'N' : mov edi,CM_CSORTNAME
                .case 'O' : mov edi,CM_TOGGLEPANELS
                .case 'P' : mov edi,CM_PANELOPTIONS
                .case 'Q' : mov edi,CM_QUICKSEARCH
                .case 'R' : mov edi,CM_CREREAD
                .case 'S' : mov edi,CM_SEARCH
                .case 'T' : mov edi,CM_CDETAIL
                .case 'U' : mov edi,CM_CNOSORT
                .case 'V' : mov edi,CM_CVOLINFO
                .case 'W' : mov edi,CM_SWAPPANELS
                .case 'X' : mov edi,CM_TOGGLEMENUBAR
                .case 'Y' : mov edi,CM_TOGGLEMENUBAR ; ..
                .case 'Z' : mov edi,CM_CSORTSIZE
                .endsw
                .gotosw(1:WP_COMMAND)
            .endif

            .switch pascal edx
            .case VK_UP
                .if KeyAlt(esi)
                    mov edi,CM_PANELSIZEUP
                   .gotosw(2:WP_COMMAND)
                .endif
                .return
            .case VK_DOWN
                .if KeyAlt(esi)
                    mov edi,CM_PANELSIZEDN
                   .gotosw(2:WP_COMMAND)
                .endif
                .return
            .case VK_F1
                mov edi,CM_HELP
                .if KeyCtrl(esi)
                    mov edi,CM_ATOGGLE
                .endif
            .case VK_F2
                mov edi,CM_RENAME
                .if KeyCtrl(esi)
                    mov edi,CM_BTOGGLE
                .endif
            .case VK_F3 : mov edi,CM_VIEW
            .case VK_F4 : mov edi,CM_EDIT
            .case VK_F5 : mov edi,CM_COPY
            .case VK_F6 : mov edi,CM_MOVE
            .case VK_F7 : mov edi,CM_MKDIR
            .case VK_F8 : mov edi,CM_DELETE
            .case VK_F9
                mov edi,CM_ACTIVATEEDIT
                .if KeyCtrl(esi)
                    mov edi,CM_CONFIGURATION
                .endif
            .case VK_F10 : mov edi,CM_EXIT
            .case VK_F11 : mov edi,CM_TOGGLEPANELSIZE
            .case VK_F12 : mov edi,CM_TOGGLEHORIZONTAL
            .default
                .return
            .endsw
            .gotosw(1:WP_COMMAND)

        .case CT_DIALOG

            .if ( m_Id == ID_CALENDAR && !KeyAlt(esi) )

                .switch edx
                .case VK_HOME
                    mov Calendar.m_Day,Calendar.m_CurDay
                    mov Calendar.m_Month,Calendar.m_CurMonth
                    mov Calendar.m_Year,Calendar.m_CurYear
                   .endc
                .case VK_UP
                    mov eax,7
                    .if ( Calendar.m_Day > eax )
                        sub Calendar.m_Day,eax
                       .endc
                    .endif
                .case VK_LEFT
                    .if ( Calendar.m_Day > 1 )
                        dec Calendar.m_Day
                    .else
                        .if ( Calendar.m_Month > 1 )
                            dec Calendar.m_Month
                        .else
                            mov Calendar.m_Month,12
                            .if ( Calendar.m_Year )
                                dec Calendar.m_Year
                            .else
                                mov Calendar.m_Year,MAXYEAR
                            .endif
                        .endif
                        mov Calendar.m_Day,DaysInMonth(Calendar.m_Year, Calendar.m_Month)
                    .endif
                    .endc
                .case VK_DOWN
                    mov eax,Calendar.m_Day
                    add eax,7
                    .if ( eax <= Calendar.m_DaysInMonth )
                        mov Calendar.m_Day,eax
                       .endc
                    .endif
                .case VK_RIGHT
                    mov eax,Calendar.m_Day
                    inc eax
                    .if ( eax <= Calendar.m_DaysInMonth )
                        mov Calendar.m_Day,eax
                       .endc
                    .endif
                .case VK_NEXT
                    .if ( KeyCtrl(esi) || Calendar.m_Month >= 12 )
                        mov Calendar.m_Day,1
                        mov Calendar.m_Month,1
                        .if ( Calendar.m_Year < MAXYEAR )
                            inc Calendar.m_Year
                        .else
                            mov Calendar.m_Year,STARTYEAR
                        .endif
                        .endc
                    .endif
                    inc Calendar.m_Month
                    mov Calendar.m_Day,1
                   .endc
                .case VK_PRIOR
                    mov Calendar.m_Day,1
                    .if ( KeyCtrl(esi) )
                        mov Calendar.m_Month,1
                        .if ( Calendar.m_Year )
                            dec Calendar.m_Year
                        .else
                            mov Calendar.m_Year,MAXYEAR
                        .endif
                    .elseif ( Calendar.m_Month > 1 )
                        dec Calendar.m_Month
                    .else
                        mov Calendar.m_Month,12
                        .if ( Calendar.m_Year )
                            dec Calendar.m_Year
                        .else
                            mov Calendar.m_Year,MAXYEAR
                        .endif
                    .endif
                    .endc
                .default
                    .return
                .endsw
                 mov rsi,rbx
                .gotosw(1:WP_SETDIALOG)
            .endif

        .case CT_MENUDLG

            .switch edx
            .case VK_UP
            .case VK_DOWN
            .case VK_LEFT
            .case VK_RIGHT
                .if ( Flags.Moveable && esi & RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED )
                    sub edi,VK_LEFT
                    mov rsi,rbx
                    .if ( Flags.Shade )
                        WinProc(WP_SHADEWINDOW, FALSE, rbx)
                    .endif
                    WinProc(WP_MOVEWINDOW, rdi, rsi)
                    .if ( Flags.Shade )
                        WinProc(WP_SHADEWINDOW, TRUE, rbx)
                    .endif
                    .return
                .endif
            .case VK_NEXT
            .case VK_PRIOR
                .for ( rbx = m_This : rbx : rbx = m_Next )
                    .break .if ( Flags.HasFocus )
                .endf
                .endc .if ( rbx )
            .default
                .return
            .endsw

            .switch edx
            .case VK_PRIOR
                mov eax,m_Id
                .if ( eax >= DI_FG_TITLE && eax <= DI_FG_EDIT )
                    sub eax,DI_FG_TITLE
                    lea rdx,at_foreground
                    mov cl,[rdx+rax]
                    .if ( eax < 16 || eax >= 30 )
                        .endc .if ( cl >= 0x0F )
                        inc cl
                    .else
                        .endc .if ( cl >= 0xF0 )
                        add cl,0x10
                    .endif
                    mov [rdx+rax],cl
                    WinProc(WP_SETDIALOG, 0, m_Base)
                    mov rsi,rbx
                   .gotosw(2:WP_SETFOCUS)
                .endif
                .endc
            .case VK_NEXT
                mov eax,m_Id
                .if ( eax >= DI_FG_TITLE && eax <= DI_FG_EDIT )
                    sub eax,DI_FG_TITLE
                    lea rdx,at_foreground
                    mov cl,[rdx+rax]
                    .if ( eax < 16 || eax >= 30 )
                        .endc .if !( cl & 0x0F )
                        dec cl
                    .else
                        .endc .if !( cl & 0xF0 )
                        sub cl,0x10
                    .endif
                    mov [rdx+rax],cl
                    WinProc(WP_SETDIALOG, 0, m_Base)
                    mov rsi,rbx
                   .gotosw(2:WP_SETFOCUS)
                .endif
                .endc
            .case VK_LEFT
                .if ( ecx == CT_MENUDLG )
                    mov edi,PREV_MENU
                    mov rsi,rbx
                   .gotosw(2:WP_QUIT)
                .endif
                .if ( m_Type == CT_TEXTINPUT )
                    .if ( Edit.m_XOffs )
                        dec Edit.m_XOffs
                    .endif
                    mov edi,TRUE
                    mov eax,0x01010000
                    mov al,Edit.m_XOffs
                    mov esi,eax
                   .gotosw(2:WP_SETCURSOR)
                .endif
                 mov rsi,rbx
                .gotosw(2:WP_SETLEFTITEM)
            .case VK_UP
                mov edi,TRUE
                mov rsi,rbx
               .gotosw(2:WP_SETPREVITEM)
            .case VK_RIGHT
                .if ( ecx == CT_MENUDLG )
                    mov edi,NEXT_MENU
                    mov rsi,rbx
                   .gotosw(2:WP_QUIT)
                .endif
                .if ( m_Type == CT_TEXTINPUT )
                    mov al,m_rc.col
                    dec al
                    .if ( Edit.m_XOffs < al )
                        inc Edit.m_XOffs
                    .endif
                    mov edi,TRUE
                    mov eax,0x01010000
                    mov al,Edit.m_XOffs
                    mov esi,eax
                   .gotosw(2:WP_SETCURSOR)
                .endif
                 mov rsi,rbx
                .gotosw(2:WP_SETRIGHTITEM)
            .case VK_DOWN
                mov edi,TRUE
                mov rsi,rbx
               .gotosw(2:WP_SETNEXTITEM)
            .endsw
            .endc
        .case CT_VIEW
        .case CT_EDIT
        .case CT_HEXEDIT
        .endsw


    .case WP_CHAR

        ; lParam: 0-15 Control Key State
        ; wParam: Char

        xor eax,eax
        mov ecx,m_Type
        .switch ecx
        .case CT_DESKTOP
            .switch pascal edi
            .case VK_TAB
            .endsw
            .endc
        .case CT_DIALOG
        .case CT_MENUDLG
            .if ( edi == VK_ESCAPE )
                xor edi,edi
               .gotosw(1:WP_QUIT)
            .endif
            .for ( rbx = m_This : rbx : rbx = m_Next )
                .break .if ( Flags.HasFocus )
            .endf
            .endc .if ( !rbx )
            mov ecx,m_Type
            .switch edi
            .case VK_TAB
                .if ( !Flags.TabStop )
                    mov edi,TRUE
                    mov rsi,rbx
                   .gotosw(2:WP_SETNEXTITEM)
                .endif
                .endc
            .case VK_SPACE
                .if ( ecx == CT_RADIOBUTTON || ecx == CT_CHECKBOX )
                    mov rsi,rbx
                   .gotosw(2:WP_TOGGLEITEM)
                .endif
                .endc
            .case VK_RETURN
                mov edi,m_Id
                mov rsi,m_Base
                .if ( Flags.AutoExit )
                    xor edi,edi
                .endif
                .gotosw(2:WP_QUIT)
            .endsw
            .if ( ecx == CT_TEXTINPUT )
                WinProc(WP_PUTC, edi, rbx)
            .endif
            .endc
        .case CT_VIEW
        .case CT_EDIT
        .case CT_HEXEDIT
        .endsw

    .case WP_ENTERIDLE

        ; lParam: PDWND

        mov rbx,m_Home
        mov edx,[rsi].Doszip.m_Id
        .if ( edx == ID_CALENDAR || ( Setup.MenuBar && ( Setup.UseDate || Setup.UseTime ) ) )

            mov eax,[rsi].Doszip.m_Type
            add m_idleId,IDLETIME
            mov ecx,300*60
            .if ( edx == ID_CALENDAR || Setup.UseLongTime )
                mov ecx,300
            .endif
            .if ( m_idleId > ecx && eax != CT_VIEW && eax != CT_EDIT && eax != CT_HEXEDIT )

                mov m_idleId,0
                GetLocalTime(&ts)

                .if ( Setup.MenuBar && ( Setup.UseDate || Setup.UseTime ) )

                    movzx ecx,m_rc.col
                    mov rc,ecx
                    mov rc.col,10

                    .if ( Setup.UseTime )

                        sub rc.x,9
                        lea rcx,@CStr(L"%02u:%02u:%02u")
                        .if ( Setup.UseLongTime == 0 )
                            add rc.x,3
                            add rcx,5*2
                        .endif
                        WinProc(WP_WRITEFORMAT, rc, rcx, ts.wHour, ts.wMinute, ts.wSecond)
                    .endif

                    .if ( Setup.UseDate )

                        sub rc.x,10
                        .if ( Setup.UseTime )
                            dec rc.x
                        .endif
                        .if ( Setup.UseLongDate == 0 )
                            add rc.x,2
                            sub ts.wYear,2000
                        .endif
                        WinProc(WP_WRITEFORMAT, rc, L"%2u.%02u.%u", ts.wDay, ts.wMonth, ts.wYear)
                    .endif
                .endif

                .if ( [rsi].Doszip.m_Id == ID_CALENDAR )

                    mov rbx,rsi
                    mov eax,0x000A0102
                    mov rc,eax
                    WinProc(WP_WRITEFORMAT, rc, L"%02u:%02u:%02u", ts.wHour, ts.wMinute, ts.wSecond)
                .endif
            .endif
        .endif
        Sleep(IDLETIME)

    .case WP_MOUSEMOVE

        ; wParam: Indicates whether various virtual keys are down.
        ; lParam: COORD

        .endc .if ( !Flags.Moveable || m_State == 0 )

        WinProc(WP_CURSORGET, FALSE, &u1)
        .for ( Coord = esi, esi = 1 : esi : )

            xor esi,esi
            movzx eax,Coord.X
            movzx ecx,m_rc.x
            add cl,byte ptr m_State[2]
            .if ( ecx < eax )
                mov esi,WinProc(WP_MOVEWINDOW, TW_MOVERIGHT, rbx)
            .elseif ( ecx > eax )
                mov esi,WinProc(WP_MOVEWINDOW, TW_MOVELEFT, rbx)
            .endif
            movzx eax,Coord.Y
            movzx ecx,m_rc.y
            .if ( ecx < eax )
                add esi,WinProc(WP_MOVEWINDOW, TW_MOVEDOWN, rbx)
            .elseif ( ecx > eax )
                add esi,WinProc(WP_MOVEWINDOW, TW_MOVEUP, rbx)
            .endif
        .endf
        WinProc(WP_CURSORSET, 0, &u1)

    .case WP_LBUTTONDOWN

        ; wParam: Indicates whether various virtual keys are down.
        ; lParam: COORD

        WinProc(WP_NCHITTEST, rbx, rsi)
        mov ecx,m_Type
        .switch ecx
        .case CT_DESKTOP
            .switch eax
            .case HTTOP
            .case HTTOPLEFT
            .case HTTOPRIGHT
                .ifsd ( WinProc(WP_NCHITTEST, m_MenuBar, rsi) > 0 )
                    mov rbx,m_MenuBar
                    .if ( eax == HTSYSMENU )
                        mov rsi,rdx
                       .gotosw(2:WP_MENUCOMMAND)
                    .endif
                    .if ( eax == HTTOP )
                        mov al,m_rc.col
                        sub al,18
                        .if ( si > ax )
                            mov edi,CM_CALENDAR
                           .gotosw(2:WP_COMMAND)
                        .endif
                    .endif
                    .endc
                .endif
            .case HTBOTTOM
            .case HTBOTTOMLEFT
            .case HTBOTTOMRIGHT
                .ifsd ( WinProc(WP_NCHITTEST, m_KeyBar, rsi) > 0 )
                    mov rbx,m_KeyBar
                    .if ( eax == HTSYSMENU )
                        mov eax,[rdx].Doszip.m_Id
                        .switch pascal eax
                        .case DI_KBHELP   : mov edi,CM_HELP
                        .case DI_KBRENAME : mov edi,CM_RENAME
                        .case DI_KBVIEW   : mov edi,CM_VIEW
                        .case DI_KBEDIT   : mov edi,CM_EDIT
                        .case DI_KBCOPY   : mov edi,CM_COPY
                        .case DI_KBMOVE   : mov edi,CM_MOVE
                        .case DI_KBMKDIR  : mov edi,CM_MKDIR
                        .case DI_KBDELETE : mov edi,CM_DELETE
                        .case DI_KBEXIT   : mov edi,CM_EXIT
                        .endsw
                        .gotosw(2:WP_COMMAND)
                    .endif
                    .endc
                .endif
            .case HTLEFT
            .case HTRIGHT
            .case HTCLIENT
                mov rdi,rbx
                .ifsd ( WinProc(WP_NCHITTEST, m_PanelA, rsi) > 0 )
                    mov rbx,m_PanelA
                .elseifsd ( WinProc(WP_NCHITTEST, m_PanelB, rsi) > 0 )
                    mov rbx,m_PanelB
                .endif
                .ifs ( eax > 0 )

                    mov rdx,rdi
                    mov ecx,esi
                    movzx eax,si
                    shr ecx,16
                    mov ah,cl
                    sub al,m_rc.x
                    sub ah,m_rc.y
                    .if ( eax == 0x0101 )
                        mov edi,CM_ACHDRV
                        .if ( rbx == [rdx].Doszip.m_PanelB )
                            mov edi,CM_BCHDRV
                        .endif
                        .gotosw(2:WP_COMMAND)
                    .endif
                    .if ( eax == 0x0103 )
                        mov edi,CM_HISTORY
                       .gotosw(2:WP_COMMAND)
                    .endif
                    xor ecx,ecx
                    mov ch,m_rc.row
                    dec ch
                    mov cl,m_rc.col
                    sub cl,3
                    .if ( Panel.Flags.MiniStatus == 0 )
                        .if ( ah == ch )
                            .if ( eax == ecx )
                                mov edi,CM_AMINI
                                .if ( rbx == [rdx].Doszip.m_PanelB )
                                    mov edi,CM_BMINI
                                .endif
                                .gotosw(2:WP_COMMAND)
                            .endif
                            .endc
                        .endif
                    .else
                        sub ch,2
                        .if ( Panel.Flags.DriveInfo )
                            mov cl,2
                            sub ch,2
                            .if ( [rdx].Doszip.Panels.Horizontal == 0 )
                                dec ch
                            .endif
                            .if ( eax == ecx )
                                mov edi,CM_AVOLINFO
                                .if ( rbx == [rdx].Doszip.m_PanelB )
                                    mov edi,CM_BVOLINFO
                                .endif
                                .gotosw(2:WP_COMMAND)
                            .endif
                            .endc
                        .else
                            .if ( eax == ecx )
                                mov edi,CM_AMINI
                                .if ( rbx == [rdx].Doszip.m_PanelB )
                                    mov edi,CM_BMINI
                                .endif
                                .gotosw(2:WP_COMMAND)
                            .endif
                            mov cl,2
                            .if ( eax == ecx )
                                mov edi,CM_AVOLINFO
                                .if ( rbx == [rdx].Doszip.m_PanelB )
                                    mov edi,CM_BVOLINFO
                                .endif
                                .gotosw(2:WP_COMMAND)
                            .endif
                            .endc
                        .endif
                    .endif
                .endif
            .endsw
            .endc
        .case CT_DIALOG
        .case CT_MENUDLG
            .switch eax
            .case HTNOWHERE
                .if ( ecx == CT_MENUDLG || Flags.AutoExit )
                    .if ( ecx == CT_MENUDLG )
                        PostMessage(WP_LBUTTONDOWN, rdi, rsi)
                    .endif
                    xor edi,edi
                    mov rsi,rbx
                   .gotosw(2:WP_QUIT)
                .endif
                .endc
            .case HTCAPTION
                movzx eax,si
                sub al,m_rc.x
                shl eax,16
                inc al
                mov m_State,eax
                .if ( Flags.Shade )
                    WinProc(WP_SHADEWINDOW, FALSE, rbx)
                .endif
                .endc
            .case HTCLOSE
            .case HTSYSMENU
                mov rbx,rdx
                .if ( !Flags.HasFocus )
                    WinProc(WP_SETFOCUS, 0, rbx)
                .endif
                .endc .if ( !Flags.HasFocus )
                mov eax,m_Type
                .switch eax
                .case CT_PUSHBUTTON
                    .if ( m_State == 0 )
                        mov m_State,1
                        WinProc(WP_FILLCHARACTER, 0x00010000, ' ')
                        mov ecx,0x000200FF
                        add cl,m_rc.col
                        WinProc(WP_FILLCHARACTER, ecx, ' ')
                        movzx ecx,m_rc.col
                        shl ecx,16
                        mov cx,0x0101
                        WinProc(WP_FILLCHARACTER, ecx, ' ')
                    .endif
                    .endc
                .case CT_CHECKBOX
                .case CT_RADIOBUTTON
                    mov rsi,rbx
                   .gotosw(3:WP_TOGGLEITEM)
                .case CT_MENUITEM
                .case CT_TEXTITEM
                    PostMessage(WP_COMMAND, m_Id, m_Home)
                    PostMessage(WP_QUIT, 0, m_Base)
                   .endc
                .endsw
            .endsw
        .endsw


    .case WP_LBUTTONUP

        ; wParam: Indicates whether various virtual keys are down.
        ; lParam: COORD

        mov ecx,m_Type
        .switch pascal ecx
        .case CT_DESKTOP
        .case CT_DIALOG
            .if ( m_State )
                mov m_State,0
                .if ( Flags.Shade )
                    WinProc(WP_SHADEWINDOW, TRUE, rbx)
                .endif
            .endif
            .if WinProc(WP_GETFOCUS, 0, rbx)

                mov rbx,rax
                mov rsi,rax
                xor edi,edi

                .if ( m_Type == CT_PUSHBUTTON && m_State )

                    mov m_State,0
                    mov ecx,0x00010000
                    mov cl,m_rc.col
                    WinProc(WP_FILLCHARACTER, ecx, U_LOWER_HALF_BLOCK)
                    movzx ecx,m_rc.col
                    shl ecx,16
                    mov cx,0x0101
                    WinProc(WP_FILLCHARACTER, ecx, U_UPPER_HALF_BLOCK)
                    .if ( !Flags.AutoExit )
                        mov edi,m_Id
                    .endif
                   .gotosw(1:WP_QUIT)
                .endif
                .gotosw(1:WP_SETFOCUS)
            .endif
        .endsw


    .case WP_LBUTTONDBLCLK
        .gotosw(WP_LBUTTONDOWN)

    .case WP_RBUTTONDOWN
    .case WP_RBUTTONUP
    .case WP_RBUTTONDBLCLK
    .case WP_MBUTTONDOWN
    .case WP_MBUTTONUP
    .case WP_MBUTTONDBLCLK
    .case WP_XBUTTONDBLCLK

    .case WP_MOUSEHWHEEL

    .case WP_MOUSEWHEEL
        mov ecx,ENHANCED_KEY or (VK_UP shl 16)
        .if ( m_Id == ID_EDITCOLOR )
            mov ecx,ENHANCED_KEY or (VK_PRIOR shl 16)
        .endif
        .ifs ( edi <= 0 )
            mov ecx,ENHANCED_KEY or (VK_DOWN shl 16)
            .if ( m_Id == ID_EDITCOLOR )
                mov ecx,ENHANCED_KEY or (VK_NEXT shl 16)
            .endif
        .endif
        PostMessage(WP_KEYDOWN, VK_UP, ecx)

    .case WP_OPENCONSOLE

        ; wParam: BOOL
        ; return: 0

        mov rbx,m_Home
        .if ( edi )

            GetConsoleMode(_coninpfh, &m_modeIn)

            .if GetConsoleScreenBufferInfo(_confh, &ci)

                movzx   edx,ci.srWindow.Right
                sub     dx,ci.srWindow.Left
                inc     edx
                movzx   eax,ci.srWindow.Bottom
                sub     ax,ci.srWindow.Top
                inc     eax
                mov     m_rc.col,dl
                mov     m_rc.row,al

                .if malloc(GetWindowSize(m_rc))

                    mov Flags.Open,1
                    mov Flags.Visible,1
                    mov m_Window,rax
                    WinProc(WP_READWINDOW, m_rc, rax)
                .endif
            .endif
        .else
            SetConsoleMode(_coninpfh, m_modeIn)
        .endif

    .case WP_SETCONSOLE

        ; wParam: BOOL
        ; return: 0

        mov edx,ENABLE_WINDOW_INPUT
        .if ( edi )
            or edx,ENABLE_MOUSE_INPUT
        .endif
        SetConsoleMode(_coninpfh, edx)


    .case WP_PEEKMESSAGE

        ; wParam:
        ; lParam: PDMSG
        ; return: BOOL

        mov eax,m_msgCount
        .if ( eax )

            dec     eax
            imul    eax,eax,Message
            lea     rcx,m_msgStack
            add     rcx,rax
            mov     [rsi].Message.wParam,[rcx].Message.wParam
            mov     [rsi].Message.lParam,[rcx].Message.lParam
            mov     [rsi].Message.uMsg,[rcx].Message.uMsg
        .endif
        .return


    ; -- Config --

    .case WP_GETSECTION

        ; lParam: LPSTR
        ; return: PDWND

        .for ( rbx = m_Home : rbx : rbx = m_Next )
            .if ( m_Type == CT_SECTION  )
                .break .ifd !strcmp(rsi, m_Text)
            .endif
        .endf
        .return( rbx )


    .case WP_GETENTRY

        ; wParam: LPSTR
        ; lParam: PDWND
        ; return: PDWND

        .for ( rbx = rsi, rbx = m_This : rbx : rbx = m_Next )
            .break .ifd !strcmp(rdi, m_Text)
        .endf
        .return( rbx )


    .case WP_ADDSECTION

        ; lParam: LPSTR
        ; return: PDWND

        .if !WinProc(WP_GETSECTION, 0, rsi)

            mov edi,MKID(CT_SECTION, ID_CONFIG)
           .gotosw(WP_NEW)
        .endif
        .return

    .case WP_DELSECTION

        ; wParam: LPSTR

        .if WinProc(WP_GETSECTION, 0, rdi)

            xor edi,edi
            mov rsi,rax
           .gotosw(WP_DESTROY)
        .endif


    .case WP_DELKEY

        ; wParam: LPSTR
        ; lParam: PDWND

        .if WinProc(WP_GETENTRY, rdi, rsi)

            xor edi,edi
            mov rsi,rax
           .gotosw(WP_DESTROY)
        .endif


    .case WP_PARSEINILINE

        ; wParam: LPSTR
        ; return: rax length, rdx start

        mov rsi,rdi
        .while islspace([rsi])
            inc rsi
        .endw
        movzx eax,byte ptr [rsi]
        .if ( eax )

            .if ( eax == ';' )
                .endc
            .elseif ( eax == '[' )
                inc rsi
                .while islspace([rsi])
                    inc rsi
                .endw
            .endif
            .while 1
                lodsb
                .switch al
                .case ']'
                    mov eax,1
                    mov [rdi],ah
                .case 0
                    .return
                .case '='
                    .break
                .case ' '
                .case 9
                    .continue
                .endsw
                stosb
            .endw
            mov rdx,rdi
            stosb
            .while islspace([rsi])
                inc rsi
            .endw
            .repeat
                lodsb
                stosb
            .until al == 0
            .for ( rdi -= 2 : rdi > rdx : rdi-- )
                .break .if !islspace([rdi])
                mov [rdi],ah
            .endf
            mov eax,2
        .endif
        .return


    .case WP_GETKEY

        ; wParam: LPSTR
        ; lParam: PDWND
        ; return: DWORD { count }

        mov rbx,rsi
        mov rsi,Section.m_LBuf

        .for ( edx = 0 : edx < MAXLBUF : edx++, rdi++ )
            mov al,[rdi]
            .break .if ( al == 0 || al == '=' )
            mov [rsi+rdx],al
        .endf
        .return( 0 ) .if ( al != '=' )

        xor eax,eax
        mov u1,eax
        mov [rsi+rdx],al
        inc rdi

        .if WinProc(WP_GETENTRY, rsi, rbx)

            mov esi,[rax].Doszip.Entry.m_Offset
            add rsi,[rax].Doszip.m_Text
        .else
            .return
        .endif

        .while ( byte ptr [rsi] )

            movzx eax,byte ptr [rdi]
            .break .if ( !eax )
            .while ( eax == ' ' )
                inc rdi
                mov al,[rdi]
            .endw
            .break .if ( al != '%' )

            inc rdi
            mov al,[rdi]
            mov u2,4

            .switch eax
            .case 'X'
            .case 'x'
                inc rdi
                xor ecx,ecx
                xor edx,edx
                .while 1
                    mov al,[rsi]
                    .break .if ( eax < '0' )
                    .if ( eax > '9' )
                        and eax,not ('a' - 'A')
                        sub eax,'A'
                        add eax,10 + '0'
                    .endif
                    sub eax,'0'
                    shld edx,ecx,4
                    shl ecx,4
                    or  ecx,eax
                    inc rsi
                .endw
                mov u4,ecx
                lea rax,vParam
                mov ecx,u1
                inc u1
                mov rcx,[rax+rcx*size_t]
                mov eax,u4
                .if ( u2 == 1 )
                    mov [rcx],al
                .else
                    mov [rcx],eax
                    .if ( u2 == 8 )
                        mov [rcx+4],edx
                    .endif
                .endif
                .endc
            .case 'l'
                inc rdi
                mov al,[rdi]
                mov u2,8
               .gotosw
            .case 'h'
                inc rdi
                mov al,[rdi]
                mov u2,1
               .gotosw
            .case 'S'
                lea rdx,vParam
                mov eax,u1
                mov rdi,[rdx+rax*size_t]
                .while ( byte ptr [rsi] )
                    _utftow(rsi)
                    add rsi,rcx
                    stosw
                .endw
                inc u1
                xor eax,eax
                stosw
            .default
                .break
            .endsw
            movzx eax,byte ptr [rsi]
            .while ( eax == ' ' )
                inc rsi
                mov al,[rsi]
            .endw
        .endw
        .return( u1 )


    .case WP_READCONFIG

        ; return: BOOL

        mov rbx,m_Home
        .if _wfopen(m_Text, L"rt")

            .for ( fp = rax, rsi = m_LBuf, edi = 0 : fgets(rsi, MAXLINE*2, fp) : )
                .ifd ( WinProc(WP_PARSEINILINE, rsi, rbx) == 1 )
                    .break .if !WinProc(WP_ADDSECTION, 0, rsi)
                    mov rdi,rax
                .elseif ( rdi && eax == 2 )
                    WinProc(WP_SETKEY, "%s", rdi, rsi)
                .endif
            .endf
            fclose(fp)
            mov eax,1
        .endif
        .return


    .case WP_WRITECONFIG

        ; return: BOOL

        mov rbx,m_Home
        .if _wfopen(m_Text, L"wt")

            .for ( rsi = rax : rbx : rbx = m_Next )

                .if ( m_Type == CT_SECTION )

                    fprintf(rsi, "[%s]\n", m_Text)
                    .for ( rdi = rbx, rbx = m_This : rbx : rbx = m_Next )

                        mov rcx,m_Text
                        mov edx,Entry.m_Offset
                        add rdx,rcx
                        fprintf(rsi, "%s=%s\n", rcx, rdx)
                    .endf
                    mov rbx,rdi
                .endif
            .endf
            fclose(rsi)
            mov eax,1
        .endif
        .return


    .case WP_SETKEY

        ; wParam: LPSTR
        ; lParam: PDWND
        ; return: PDWND

        mov rbx,rsi
        mov rsi,Line.m_TBuf

        .ifd vsprintf(rsi, rdi, &vParam)

            .ifd ( WinProc(WP_PARSEINILINE, rsi, rbx) == 2 )

                mov rdi,rdx
                mov byte ptr [rdi],0
                .if ( byte ptr [rsi+1] != 0 )
                    WinProc(WP_DELKEY, rsi, rbx)
                .endif
                mov byte ptr [rdi],'='

                .if WinProc(WP_NEW, MKID(CT_ENTRY, ID_CONFIG), rsi)

                    mov rbx,rax
                    sub rdi,rsi
                    inc edi
                    mov Entry.m_Offset,edi
                    add rdi,m_Text
                    mov byte ptr [rdi-1],0
                    mov rax,rbx
                .endif
            .endif
        .endif
        .return


    .case WP_PROGRESSOPEN

        ; wParam: LPWSTR
        ; lParam: LPWSTR
        ; return: BOOL

        .if WinProc(WP_CREATE, MKID(CT_DIALOG, ID_PROGRESS), m_Home)

            mov rbx,rax
            mov Flags,W_MOVEABLE or W_SHADE or W_TRANSPARENT or W_CAPTION
            mov m_rc,0x06480904
            mov Progress.m_XPos,4
            mov Progress.m_Name,rdi
            .if ( rsi )
                mov Progress.m_XPos,9
            .endif
            WinProc(WP_OPENDIALOG, 0, rdi)
            .if ( rsi )

                ;mov dl,at_background[B_Dialog]
                ;or  dl,at_foreground[F_DialogKey]
                mov eax,m_rc
                add eax,0x0204
                and eax,0x00FFFFFF
                mov rc,eax
                WinProc(WP_WRITEFORMAT, rc, L"%s\n  to", rsi)
            .endif
            WinProc(WP_FILLCHARACTER, 0x01400404, U_LIGHT_SHADE)
            mov edi,TRUE
            mov rsi,rbx
           .gotosw(WP_SHOWWINDOW)
        .endif

    .case WP_PROGRESSCLOSE

        .if WinProc(WP_GETOBJECT, ID_PROGRESS, m_Home)

            xor edi,edi
            mov rsi,rax
           .gotosw(WP_DESTROY)
        .endif

    .case WP_PROGRESSSET

        ; wParam: LPWSTR
        ; lParam: LPWSTR
        ; vParam: QWORD
        ; return: BOOL

        .if WinProc(WP_GETOBJECT, ID_PROGRESS, m_Home)

            SetClass(rax)
        .endif

    .case WP_PROGRESSUPDATE

        ; lParam: QWORD
        ; return: BOOL

        .if WinProc(WP_GETOBJECT, ID_PROGRESS, m_Home)

            SetClass(rax)
        .endif


    .case WP_SAVESETUP

        mov rbx,m_Home

        .if ( Setup.AutoSaveSetup )

            .if WinProc(WP_ADDSECTION, 0, "Configuration")

                mov rsi,rax
                lea rdi,at_foreground
                assume rdi:ptr qword
                WinProc(WP_SETKEY, "setup=%X", rsi, Setup)
                WinProc(WP_SETKEY, "panels=%X", rsi, Panels)
                WinProc(WP_SETKEY, "confirm=%X", rsi, Confirm)
                WinProc(WP_SETKEY, "search=%X", rsi, Search)
                WinProc(WP_SETKEY, "view=%X", rsi, Viewer)
                WinProc(WP_SETKEY, "edit=%X", rsi, Editor)
                WinProc(WP_SETKEY, "fore=%llX %llX", rsi, [rdi], [rdi+8] )
                WinProc(WP_SETKEY, "back=%llX %llX", rsi, [rdi+16], [rdi+24] )
                assume rdi:nothing
            .endif
            mov rbx,m_PanelA
            .if WinProc(WP_ADDSECTION, 0, "PanelA")
                mov rsi,rax
                WinProc(WP_SETKEY, "flag=%X", rsi, Panel.Flags)
                WinProc(WP_SETKEY, "cell=%X", rsi, Panel.m_celIndex)
                WinProc(WP_SETKEY, "offs=%X", rsi, Panel.m_fcbIndex)
                WinProc(WP_SETKEY, "mask=%S", rsi, Panel.m_srcMask)
                WinProc(WP_SETKEY, "file=%S", rsi, Panel.m_arcFile)
                WinProc(WP_SETKEY, "arch=%S", rsi, Panel.m_arcPath)
                WinProc(WP_SETKEY, "path=%S", rsi, Panel.m_srcPath)
            .endif
            mov rbx,m_Home
            mov rbx,m_PanelB
            .if WinProc(WP_ADDSECTION, 0, "PanelB")
                mov rsi,rax
                WinProc(WP_SETKEY, "flag=%X", rsi, Panel.Flags)
                WinProc(WP_SETKEY, "cell=%X", rsi, Panel.m_celIndex)
                WinProc(WP_SETKEY, "offs=%X", rsi, Panel.m_fcbIndex)
                WinProc(WP_SETKEY, "mask=%S", rsi, Panel.m_srcMask)
                WinProc(WP_SETKEY, "file=%S", rsi, Panel.m_arcFile)
                WinProc(WP_SETKEY, "arch=%S", rsi, Panel.m_arcPath)
                WinProc(WP_SETKEY, "path=%S", rsi, Panel.m_srcPath)
            .endif
            .gotosw(WP_WRITECONFIG)
        .endif


    .case WP_SHOW

        ; wParam: BOOL

        mov rbx,m_Home
        .if ( edi )
            .if ( Setup.MenuBar )
                WinProc(WP_OPENRESOURCE, TRUE, m_MenuBar)
                WinProc(WP_SHOWWINDOW, TRUE, m_MenuBar)
            .endif
            .if ( Setup.KeyBar )
                WinProc(WP_OPENRESOURCE, TRUE, m_KeyBar)
                WinProc(WP_SHOWWINDOW, TRUE, m_KeyBar)
            .endif
            mov rbx,m_PanelA
            .if ( Panel.Flags.Visible )
                WinProc(WP_CREATEPANEL, TRUE, rbx)
            .endif
            mov rbx,m_Home
            mov rbx,m_PanelB
            .if ( Panel.Flags.Visible )
                WinProc(WP_CREATEPANEL, TRUE, rbx)
            .endif
            mov rbx,m_Home
            .if ( Setup.CommandLine )
                WinProc(WP_SHOWCOMMANDLINE, TRUE, 0)
            .endif
            .endc
        .endif
        WinProc(WP_SAVESETUP, 0, 0)
        WinProc(WP_OPENRESOURCE, FALSE, m_MenuBar)
        WinProc(WP_OPENRESOURCE, FALSE, m_KeyBar)
        WinProc(WP_SHOWCOMMANDLINE, FALSE, 0)
        WinProc(WP_OPENWINDOW, FALSE, m_PanelA)
        WinProc(WP_OPENWINDOW, FALSE, m_PanelB)

    .endsw
    .return( 0 )

    endp


 Doszip::PostMessage proc uMsg:DWORD, wParam:WPARAM, lParam:LPARAM

    mov     ecx,1
    mov     eax,m_msgCount
    inc     eax
    cmp     eax,MAXMESSAGE
    cmovnb  eax,ecx
    mov     m_msgCount,eax
    dec     eax
    imul    eax,eax,Message
    lea     rcx,m_msgStack
    add     rcx,rax
    mov     [rcx].Message.uMsg,ldr(uMsg)
    mov     [rcx].Message.wParam,ldr(wParam)
    mov     [rcx].Message.lParam,ldr(lParam)
    xor     eax,eax
    ret

    endp


 Doszip::MessageBox proc uses rsi rdi title:LPWSTR, format:LPWSTR, flags:DWORD, argptr:VARARG

   .new rc:TRECT, r2, size
   .new width:SDWORD, line
   .new pb_width:DWORD
   .new pb_count:DWORD
   .new pb_col[3]:DWORD
   .new pb_id[3]:DWORD
   .new pb_dw[3]:PDWND
   .new hwnd:PDWND
   .new text:LPWSTR
   .new attrib:dword = 0
   .new msg:Message
   .new Cursor:CURSOR

    mov rbx,m_Home
    mov text,m_LBuf
    ldr rdx,format
    vswprintf( m_LBuf, rdx, &argptr )
    WinProc(WP_GETRECT, &size, rbx)

    mov rbx,WinProc(WP_CREATE, MKID(CT_DIALOG, ID_MSGBOX), rbx)
    or  Flags,W_MOVEABLE or W_SHADE or W_COLOR or W_AUTOEXIT or W_CAPTION
    WinProc(WP_CURSORGET, FALSE, &Cursor)

    mov eax,flags
    and eax,7
    xor ecx,ecx
    xor edx,edx
    mov esi,IDOK
    mov edi,IDCANCEL

    .switch pascal eax
    .case MB_OK
        lea rax,@CStr(CP_OK)
    .case MB_OKCANCEL
        lea rax,@CStr(CP_OK)
        lea rdx,@CStr(CP_CANCEL)
    .case MB_ABORTRETRYIGNORE
        mov esi,IDABORT
        mov edi,IDRETRY
        mov pb_id[2*4],IDIGNORE
        lea rax,@CStr(CP_ABORT)
        lea rdx,@CStr(CP_RETRY)
        lea rcx,@CStr(CP_IGNORE)
    .case MB_YESNOCANCEL
        mov esi,IDYES
        mov edi,IDNO
        mov pb_id[2*4],IDCANCEL
        lea rax,@CStr(CP_YES)
        lea rdx,@CStr(CP_NO)
        lea rcx,@CStr(CP_CANCEL)
    .case MB_YESNO
        mov esi,IDYES
        mov edi,IDNO
        lea rax,@CStr(CP_YES)
        lea rdx,@CStr(CP_NO)
    .case MB_RETRYCANCEL
        mov esi,IDRETRY
        lea rax,@CStr(CP_RETRY)
        lea rdx,@CStr(CP_CANCEL)
    .case MB_CANCELTRYCONTINUE
        mov esi,IDCANCEL
        mov edi,IDTRYAGAIN
        mov pb_id[2*4],IDCONTINUE
        lea rax,@CStr(CP_CANCEL)
        lea rdx,@CStr(CP_TRYAGAIN)
        lea rcx,@CStr(CP_CONTINUE)
    .endsw
    .new pb_name[3]:LPWSTR = { rax, rdx, rcx }

    mov pb_id[0*4],esi
    mov pb_id[1*4],edi
    mov eax,1
    .if ( rdx )
        inc eax
    .endif
    .if ( rcx )
        inc eax
    .endif
    mov pb_count,eax

    .for ( pb_width = 0, edi = 0 : edi < pb_count : edi++ )

        inc wcslen(pb_name[rdi*LPWSTR])
        mov pb_col[rdi*4],eax
        add eax,5
        add pb_width,eax
    .endf

    mov rcx,title
    .if ( rcx == NULL )

        mov edx,flags
        and edx,MB_ICONERROR or MB_ICONQUESTION or MB_ICONWARNING
        .if ( edx == MB_ICONERROR )
            lea rcx,@CStr(CP_ERROR)
        .elseif ( edx == MB_ICONWARNING )
            lea rcx,@CStr(CP_WARNING)
        .else
            lea rcx,@CStr(L"")
        .endif
    .endif
    mov title,rcx
    mov width,wcslen(rcx)
    mov line,0
    mov rdi,text

    .if wchar_t ptr [rdi]
        .repeat
            .break .if !wcschr(rdi, 10)
            mov rdx,rax
            sub rdx,rdi
            shr edx,1
            lea rdi,[rax+wchar_t]
            .if edx >= width
                mov width,edx
            .endif
            inc line
        .until line == 17
    .endif
    .ifd wcslen(rdi) >= width
        mov width,eax
    .endif

    mov eax,width
    .if ( eax < pb_width )
        mov eax,pb_width
    .endif
    mov dl,2
    mov dh,76
    .if ( al < 70 )
        mov dh,al
        add dh,8
        mov dl,80
        sub dl,dh
        shr dl,1
    .endif
    .if ( dh < 38 )
        mov dl,16
        mov dh,38
    .endif

    mov m_rc.x,dl
    mov m_rc.y,7
    mov ecx,line
    add cl,6
    mov m_rc.row,cl
    mov m_rc.col,dh
    shr eax,16
    add al,7
    .if ( al > size.row )
        mov m_rc.y,1
    .endif

    mov edx,flags
    .if ( edx & MB_USERICON )
        mov Flags.Transparent,1
    .else
        and edx,0x70
        .if ( edx == MB_ICONERROR || edx == MB_ICONWARNING )
            mov Flags.SysMenu,1
        .endif
    .endif
    WinProc(WP_OPENDIALOG, 0, title)

    mov rc,m_rc
    mov al,rc.row
    mov rc.row,1
    sub al,2
    mov rc.y,al
    mov al,rc.col
    shr al,1
    mov rc.x,al

    .for ( edx = 0, ecx = 0 : ecx < pb_count : ecx++ )

        add edx,pb_col[rcx*4]
        add edx,2
    .endf
    dec  ecx
    imul eax,ecx,3
    add  eax,edx
    shr  eax,1
    sub  rc.x,al

    .for ( hwnd = rbx, edi = 0 : edi < pb_count : edi++ )

        mov     eax,pb_col[rdi*4]
        add     eax,2
        mov     rc.col,al
        mov     edx,pb_id[rdi*4]
        shl     edx,16
        or      edx,CT_PUSHBUTTON

        .break .if !WinProc(WP_CREATE, edx, rbx)

        mov     rsi,rbx
        mov     rbx,rax
        mov     pb_dw[rdi*PDWND],rax

        mov     edx,rc
        mov     m_rc,edx
        mov     eax,[rsi].Doszip.m_rc
        shr     eax,16
        mul     dh
        movzx   edx,dl
        add     eax,edx
        shl     eax,2
        add     rax,[rsi].Doszip.m_Window
        mov     m_Window,rax

        mov     eax,rc
        xor     ax,ax
        mov     r2,eax
        WinProc(WP_FILLCHARACTER, eax, ' ')
        WinProc(WP_FILLATTRIBUTE, r2, MKAT(BG_PBUTTON, FG_TITLE))
        inc     r2.x
        inc     r2.y
        WinProc(WP_FILLCHARACTER, r2, U_UPPER_HALF_BLOCK)
        WinProc(WP_FILLFOREGROUND, r2, FG_PBSHADE)
        dec     r2.y
        mov     al,rc.col
        dec     al
        add     r2.x,al
        mov     r2.col,1
        WinProc(WP_FILLCHARACTER, r2, U_LOWER_HALF_BLOCK)
        WinProc(WP_FILLFOREGROUND, r2, FG_PBSHADE)
        mov     eax,rc
        sub     eax,0x00040000
        mov     ax,2
        mov     r2,eax

        .for ( rsi = pb_name[rdi*LPWSTR] : r2.col : r2.col--, r2.x++ )

            movzx eax,word ptr [rsi]
            add rsi,2
            .if ( eax == '&' )
                mov ax,[rsi]
                and eax,not 0x20
                mov m_SysKey,eax
                movzx ecx,word ptr r2
                or ecx,0x01010000
                WinProc(WP_FILLATTRIBUTE, ecx, MKAT(BG_PBUTTON, FG_TITLEKEY))
                movzx eax,word ptr [rsi]
                add rsi,2
            .endif
            .break .if ( eax == 0 )
            movzx ecx,word ptr r2
            or ecx,0x01010000
            WinProc(WP_FILLCHARACTER, ecx, rax)
        .endf
        mov rbx,hwnd
        mov al,rc.col
        add al,3
        add rc.x,al
    .endf

    mov rc,m_rc
    mov rc.y,2
    mov rc.x,2
    sub rc.col,4
    xor eax,eax
    .if ( Flags.Transparent )
        mov al,0x07
    .endif
    mov rc.row,al

    .for ( rsi = text : rsi && word ptr [rsi] && rc.y < 17+2  : rc.y++ )

        .if ( wcschr(rsi, 10) != NULL )

            mov word ptr [rax],0
            add rax,word
        .endif
        mov rdi,rax
        WinProc(WP_WRITECENTER, rc, rsi)
        mov rsi,rdi
    .endf
    WinProc(WP_SHOWWINDOW, TRUE, rbx)
    mov eax,flags
    and eax,0x300
    mov rcx,pb_dw[0*PDWND]
    .if ( eax == MB_DEFBUTTON3 )
        mov rcx,pb_dw[2*PDWND]
    .elseif ( eax == MB_DEFBUTTON2 )
        mov rcx,pb_dw[1*PDWND]
    .endif
    WinProc(WP_SETFOCUS, rbx, rcx)
    .whiled WinProc(WP_GETMESSAGE, &msg, rbx)
        WinProc(msg.uMsg, msg.wParam, msg.lParam)
    .endw
    WinProc(WP_CURSORSET, 0, &Cursor)
    WinProc(WP_DESTROY, 0, rbx)
    mov rax,msg.wParam
    ret
    endp


 Doszip::Doszip proc uses rsi rdi argc:int_t, argv:warray_t

    .new noLogo:DWORD = 0
    .new cmdMode:DWORD = 0
    .new cfgPath:LPWSTR = NULL
    .new fileName:LPWSTR = NULL
    .new key:DWORD

     ldr ebx,argc
     ldr rsi,argv

    .for ( edi = 1 : edi < ebx : edi++ )

        mov rdx,[rsi+rdi*LPWSTR]
        movzx eax,word ptr [rdx]
        movzx ecx,word ptr [rdx+2]

        .switch eax
        .case '?'
            printf(
                "The Doszip Commander Version %d.%02d.beta, Copyright (C) 2025 Doszip Developers\n\n"
                "Command line switches\n"
                " The following switches may be used in the command line:\n\n"
                "  -C<config_path> - Read/Write setup from/to <config_path>\n\n"
                "  -cmd - Start DZ and show only command prompt.\n\n"
                "  -E:<file> - Save environment block to <file>.\n\n"
                "  -nologo - Suppress copyright message.\n\n"
                "  DZ <filename> command starts DZ and forces it to show <filename>\n"
                "contents if it is an archive or show folder contents if <filename>\n"
                "is a folder.\n", VERSION / 100, VERSION mod 100 )
           .return( 0 )
        .case '-'
        .case '/'
            add rdx,2
            mov eax,ecx
            movzx ecx,word ptr [rdx+2]
            .switch eax
                ;
                ; @3.42 - save environment block to file
                ;
                ; Note: This is called inside a child process
                ;
            .case 'E'
                .gotosw(1: '?') .if ( ecx != ':' )
                add rdx,4
                ;SaveEnvironment(rdx)
               .return( 0 )
            .case 'n'
                .gotosw(1: '?') .if ecx != 'o'
                mov noLogo,1
               .endc
            .case 'C'
                add rdx,2
                mov cfgPath,rdx
               .endc
            .case 'c'
                .gotosw(1: '?') .if ( ecx != 'm' )
                mov cmdMode,1
               .endc
            .default
                .gotosw(1: '?')
            .endsw
            .endc
        .default
            mov fileName,rdx
        .endsw
    .endf

    .if ( !noLogo )
        printf(
            "The Doszip Commander Version %d.%02d.beta, Copyright (C) 2014-2025 Doszip Developers\n\n",
            VERSION / 100, VERSION mod 100  )
    .endif
    .return .if ( @ComAlloc(Doszip, MAXLBUF*3+WMAXPATH*2) == NULL )


    mov rbx,rax
    mov m_dz,rax
    mov m_Home,rax
    mov m_Base,rax
    add rax,Doszip+DoszipVtbl+15
    and al,-16
    mov m_B1,rax
    add rax,MAXLBUF
    mov m_B2,rax
    mov m_LBuf,rax
    add rax,MAXLBUF
    mov m_B3,rax
    mov m_TBuf,rax
    add rax,MAXLBUF
    mov m_Text,rax

    GetModuleFileNameW(0, rax, WMAXPATH)
    mov rdi,_wstrfn(m_Text)
    xor edx,edx
    mov [rax-2],dx
    mov rsi,m_Text
    _wstrfxcat(_wstrfcat(rsi, cfgPath, rdi), L".ini")

    lea rcx,_ltype
    xor eax,eax
    mov m_msButton,eax
    mov m_msgCount,eax
    mov m_modeIn,eax
    inc eax
    mov m_dlgFocus,eax
    mov m_idleId,60000
    mov Flags.Parent,1

    WinProc(WP_CURSORGET, TRUE, &m_Cursor)
    WinProc(WP_OPENCONSOLE, TRUE, 0)
    WinProc(WP_READCONFIG, 0, rbx)

    mov m_MenuBar, WinProc(WP_NEW, MKID(CT_MENUBAR, ID_MENUBAR), IDD_Menusline)
    mov m_KeyBar,  WinProc(WP_NEW, MKID(CT_KEYBAR,  ID_KEYBAR),  IDD_Statusline)
    mov m_PanelA,  WinProc(WP_NEW, MKID(CT_PANEL,   CI_PANELA), 0)
    mov m_PanelB,  WinProc(WP_NEW, MKID(CT_PANEL,   CI_PANELB), 0)
    .if WinProc(WP_NEW, MKID(CT_COMMAND, ID_COMMAND), 0)
        mov m_Command,rax
        .if WinProc(WP_CREATE, MKID(CT_TEXTINPUT, DI_COMMAND), rax)
            mov rbx,rax
            mov Edit.m_Attribute,MKAT(0, 7, ' ')
            WinProc(WP_ADDLINE, 0, 0)
            mov rbx,m_Home
        .endif
    .endif

    WinProc(WP_NEW, MKID(CT_MENUDLG, ID_PANELA),  IDD_DZMenuPanel)
    WinProc(WP_NEW, MKID(CT_MENUDLG, ID_FILE),    IDD_DZMenuFile)
    WinProc(WP_NEW, MKID(CT_MENUDLG, ID_EDIT),    IDD_DZMenuEdit)
    WinProc(WP_NEW, MKID(CT_MENUDLG, ID_SETUP),   IDD_DZMenuSetup)
    WinProc(WP_NEW, MKID(CT_MENUDLG, ID_TOOLS),   IDD_DZMenuTools)
    WinProc(WP_NEW, MKID(CT_MENUDLG, ID_HELP),    IDD_DZMenuHelp)
    WinProc(WP_NEW, MKID(CT_MENUDLG, ID_PANELB),  IDD_DZMenuPanel)

    WinProc(WP_NEW, MKID(CT_DIALOG, ID_CALENDAR), IDD_Calendar)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_CALENDARHELP), IDD_CalHelp)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_COMPAREOPTIONS), IDD_CompareOptions)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_CONFIRMADDFILES), IDD_ConfirmAddFiles)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_CONFIRMCONTINUE), IDD_ConfirmContinue)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_CONFIRMDELETE), IDD_ConfirmDelete)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_CONSOLESIZE), IDD_ConsoleSize)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_DEFLATE64), IDD_Deflate64)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_DRIVENOTREADY), IDD_DriveNotReady)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_COMPAREDIRECTORIES), IDD_DZCompareDirectories)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_COMPRESSION), IDD_DZCompression)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_CONFIGURATION), IDD_DZConfiguration)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_CONFIRMATIONS), IDD_DZConfirmations)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_DZCOPY), IDD_DZCopy)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_DECOMPRESS), IDD_DZDecompress)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_DEFAULTCOLOR), IDD_DZDefaultColor)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_ENVIRON), IDD_DZEnviron)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_FINDFILE), IDD_DZFindFile)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_FINDFILEHELP), IDD_DZFFHelp)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_FILEATTRIBUTES), IDD_DZFileAttributes)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_DZHELP), IDD_DZHelp)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_ABOUT), IDD_About)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_HISTORY), IDD_DZHistory)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_MAKELIST), IDD_DZMKList)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_DZMOVE), IDD_DZMove)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_PANELFILTER), IDD_DZPanelFilter)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_PANELOPTIONS), IDD_DZPanelOptions)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_RECURSIVECOMPARE), IDD_DZRecursiveCompare)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_SAVESETUP), IDD_DZSaveSetup)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_SCREENOPTIONS), IDD_DZScreenOptions)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_SUBINFO), IDD_DZSubInfo)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_SYSTEMINFO), IDD_DZSystemInfo)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_SYSTEMOPTIONS), IDD_DZSystemOptions)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TRANSFER), IDD_DZTransfer)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_ZIPATTRIBUTES), IDD_DZZipAttributes)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_EDITCOLOR), IDD_EditColor)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_FFREPLACE), IDD_FFReplace)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_HEFORMAT), IDD_HEFormat)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_HELINE), IDD_HELine)
    WinProc(WP_NEW, MKID(CT_KEYBAR, ID_HEKEYBAR), IDD_HEStatusline)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_OPERATIONFILTER), IDD_OperationFilters)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_REPLACE), IDD_Replace)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_REPLACEPROMPT), IDD_ReplacePrompt)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_SAVESCREEN), IDD_SaveScreen)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_SEARCH), IDD_Search)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TEOPTIONS), IDD_TEOptions)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TEQUICKMENU), IDD_TEQuickMenu)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TERELOAD), IDD_TEReload)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TERELOAD2), IDD_TEReload2)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TESAVE), IDD_TESave)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TESEEK), IDD_TESeek)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TEWINDOWS), IDD_TEWindows)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TVCOPY), IDD_TVCopy)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TVHELP), IDD_TVHelp)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TVQUICKMENU), IDD_TVQuickMenu)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_TVSEEK), IDD_TVSeek)
    WinProc(WP_NEW, MKID(CT_KEYBAR, ID_TVKEYBAR), IDD_TVStatusline)
    WinProc(WP_NEW, MKID(CT_DIALOG, ID_UNZIPCRCERROR), IDD_UnzipCRCError)


    assume rsi:PDWND

    mov Setup,   Doszip.Setup   {}
    mov Panels,  Doszip.Panels  {}
    mov Confirm, Doszip.Confirm {}
    mov Search,  Doszip.Search  {}
    mov Viewer,  Doszip.Viewer  {}
    mov Editor,  Doszip.Editor  {}

    .if WinProc(WP_GETSECTION, 0, "Configuration")

        mov rsi,rax
        WinProc(WP_GETKEY, "setup=%X",       rsi, &Setup)
        WinProc(WP_GETKEY, "panels=%X",      rsi, &Panels)
        WinProc(WP_GETKEY, "confirm=%hX",    rsi, &Confirm)
        WinProc(WP_GETKEY, "search=%hX",     rsi, &Search)
        WinProc(WP_GETKEY, "view=%hX",       rsi, &Viewer)
        WinProc(WP_GETKEY, "edit=%X",        rsi, &Editor)
        WinProc(WP_GETKEY, "fore=%llX %llX", rsi, &at_foreground, &at_foreground[8] )
        WinProc(WP_GETKEY, "back=%llX %llX", rsi, &at_background, &at_background[8] )
    .endif
    mov ecx,Setup.UseMouse
    WinProc(WP_SETCONSOLE, rcx, 0)
    .if ( cmdMode )
        mov Setup.KeyBar,0
        mov Setup.MenuBar,0
    .endif
    mov rax,m_PanelA
    .if ( Panels.PanelID )
        mov rax,m_PanelB
    .endif
    mov m_CPanel,rax
    mov rdi,rbx
    mov rbx,m_Command
    mov Command.m_Path,rax
    mov rbx,rdi
    mov rbx,m_PanelA

    GetCurrentDirectoryW(WMAXPATH, Panel.m_srcPath)
    wcscpy(Panel.m_srcMask, L"*.*")
    mov Panel.Flags,PanelClass.Flags {}
    .if WinProc(WP_GETSECTION, 0, "PanelA")
        mov rsi,rax
        WinProc(WP_GETKEY, "flag=%X", rsi, &Panel.Flags)
        WinProc(WP_GETKEY, "cell=%X", rsi, &Panel.m_celIndex)
        WinProc(WP_GETKEY, "offs=%X", rsi, &Panel.m_fcbIndex)
        WinProc(WP_GETKEY, "mask=%S", rsi, Panel.m_srcMask)
        WinProc(WP_GETKEY, "file=%S", rsi, Panel.m_arcFile)
        WinProc(WP_GETKEY, "arch=%S", rsi, Panel.m_arcPath)
        WinProc(WP_GETKEY, "path=%S", rsi, Panel.m_srcPath)
    .endif
    mov Panel.Flags.RootDir,1

    mov rbx,rdi
    mov rbx,m_PanelB
    GetCurrentDirectoryW(WMAXPATH, Panel.m_srcPath)
    wcscpy(Panel.m_srcMask, L"*.*")
    mov Panel.Flags,PanelClass.Flags {}
    mov Panel.Flags.PanelID,1
    .if WinProc(WP_GETSECTION, 0, "PanelB")
        mov rsi,rax
        WinProc(WP_GETKEY, "flag=%X", rsi, &Panel.Flags)
        WinProc(WP_GETKEY, "cell=%X", rsi, &Panel.m_celIndex)
        WinProc(WP_GETKEY, "offs=%X", rsi, &Panel.m_fcbIndex)
        WinProc(WP_GETKEY, "mask=%S", rsi, Panel.m_srcMask)
        WinProc(WP_GETKEY, "file=%S", rsi, Panel.m_arcFile)
        WinProc(WP_GETKEY, "arch=%S", rsi, Panel.m_arcPath)
        WinProc(WP_GETKEY, "path=%S", rsi, Panel.m_srcPath)
    .endif
    mov rbx,rdi
    WinProc(WP_SHOW, TRUE, 0)

    mov rdi,m_PanelA
    mov rsi,m_PanelB
    .ifd WinProc(WP_OPENPANEL, TRUE, m_CPanel)
        .if ( rsi == m_CPanel )
            mov rsi,rdi
        .endif
    .endif
    WinProc(WP_OPENPANEL, TRUE, rsi)
    mov rax,rbx
    ret
    endp


 Doszip::Release proc uses rsi rdi

    mov rbx,m_Home
    WinProc(WP_OPENCONSOLE, FALSE, 0)
    WinProc(WP_SAVESETUP, 0, 0)
    .for ( rsi = m_Home, ebx = 0 : rsi != rbx : )
        .for ( rbx = rsi : m_Next : rbx = m_Next )
        .endf
        WinProc(WP_DESTROY, 0, rbx)
    .endf
    ret
    endp


 Doszip::ReadRootdir proc uses rsi rdi pPanel:PDWND

   .new count:DWORD = 0
   .new path[4]:WCHAR

    ldr rbx,pPanel

    WinProc(WP_DESTROY, TRUE, m_This)
    mov Panel.Flags.Archive,0
    mov Panel.Flags.DriveNetwork,0
    mov Panel.Flags.RootDir,1
    mov eax,':' shl 16
    mov edx,'\'
    mov dword ptr path,eax
    mov dword ptr path[4],edx
    mov edi,GetLogicalDrives()

    .for ( esi = 0 : esi < MAXDRIVES : esi++ )

        bt  edi,esi
        .ifc

            lea eax,[rsi+'A']
            mov path,ax
            .ifd ( GetDriveTypeW(&path) > 1 )
                mov ecx,esi
                shl ecx,16
                mov cx,CT_FILE
                .if WinProc(WP_NEW, ecx, &path)
                    inc count
                    mov [rax].Doszip.File.Flags.RootDir,1
                    mov [rax].Doszip.File.m_Attributes,_A_VOLID
                .endif
            .endif
        .endif
    .endf
    .return( count )
    endp


 Doszip::ReadSubdir proc pPanel:PDWND

    ldr rbx,pPanel

    WinProc(WP_DESTROY, TRUE, m_This)
    mov Panel.Flags.RootDir,0
    ret
    endp

 Doszip::Run proc

    .new msg:Message

    .whiled WinProc(WP_GETMESSAGE, &msg, rbx)
        WinProc(msg.uMsg, msg.wParam, msg.lParam)
    .endw
    ret
    endp


 wmain proc argc:int_t, argv:warray_t

    .new status:int_t
    .new app:ptr Doszip(ldr(argc), ldr(argv))
    .if ( rax )
        mov status,app.Run()
        app.Release()
        mov eax,status
    .endif
    ret
    endp

    end

; _CONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include crtl.inc
include malloc.inc

  .data
   _console PCONSOLE 0
   _cursor  CURSOR { -1, -1, CURSOR_DEFAULT, 1 }

   _rgbcolortable COLORREF \
    0x00211417,
    0x008B4812,
    0x0069A226,
    0x00B3A12A,
    0x00281CC0,
    0x00BA47A3,
    0x004C73A2,
    0x00CCCFD0,
    0x00645C5E,
    0x00DE7B2A,
    0x007ADA33,
    0x00DEC733,
    0x005161F6,
    0x00CB61C0,
    0x000CADE9,
    0x00FFFFFF

   _terminalcolorid db \
    TC_BLACK,
    TC_BLUE,
    TC_GREEN,
    TC_CYAN,
    TC_RED,
    TC_MAGENTA,
    TC_BROWN,
    TC_LIGHTGRAY,
    TC_DARKGRAY,
    TC_LIGHTBLUE,
    TC_LIGHTGREEN,
    TC_LIGHTCYAN,
    TC_LIGHTRED,
    TC_LIGHTMAGENTA,
    TC_YELLOW,
    TC_WHITE

    .code

_cursoron proc

    mov _cursor.visible,1
    _cwrite(ESC "[?25h")
    ret

_cursoron endp


_cursoroff proc

    mov _cursor.visible,0
    _cwrite(ESC "[?25l")
    ret

_cursoroff endp


_gotoxy proc x:uint_t, y:uint_t

    mov ecx,x
    mov eax,y
    mov _cursor.x,cl
    mov _cursor.y,al
    inc ecx ; zero based..
    inc eax

    _cwrite("\e[%d;%dH", eax, ecx)
    ret

_gotoxy endp


_cursortype proc type:int_t

    mov edx,type
    .if ( _cursor.type != dl )

        mov _cursor.type,dl

        _cwrite(ESC "[%d q", edx)
    .endif
    ret

_cursortype endp


_getcursor proc uses rbx p:PCURSOR

    mov rbx,p
    mov eax,_cursor
    mov [rbx],eax

    _cursorxy()
    movzx ecx,ax
    shr eax,16
    mov _cursor.x,cl
    mov _cursor.y,al
    mov [rbx].CURSOR.x,cl
    mov [rbx].CURSOR.y,al
    ret

_getcursor endp


_writeline proc private uses rbx x:BYTE, y:BYTE, l:BYTE, p:PCHAR_INFO

   .new c:int_t
   .new a:int_t = 0
   .new f:byte = 0
   .new b:byte = 0

    mov rbx,p

    inc x ; zero based..
    inc y

    _cwrite(CSI "%d;%dH", y, x)

    .for ( : l : l--, rbx+=4 )

        movzx eax,byte ptr [rbx+2]
        mov ecx,eax
        and eax,0x0F
        shr ecx,4

        .if ( al != f || cl != b )

            mov a,1
            mov f,al
            mov b,cl

            lea rdx,_terminalcolorid
            mov al,[rdx+rax]
            mov cl,[rdx+rcx]

            _cwrite(CSI "38;5;%dm\e[48;5;%dm", eax, ecx)
        .endif
        mov c,_wtoutf([rbx])
        _write(_conout, &c, ecx)
    .endf
    .if ( a )
        _cwrite(CSI "m")
    .endif
    ret

_writeline endp


_conpaint proc uses rbx

   .new rc:TRECT
   .new x:byte
   .new y:byte
   .new c:byte
   .new k:byte

    _cwrite("\e7\e[?25l")

    mov rcx,_console
    mov rc,[rcx].TCONSOLE.rc
    mov rbx,[rcx].TCONSOLE.window

    .for ( y = 0 : y < rc.row : y++ )

        .for ( c = 0, x = 0 : x < rc.col : x++, rbx+=4 )

            mov rdx,rbx
            mov rax,_console
            sub rdx,[rax].TCONSOLE.window
            add rdx,[rax].TCONSOLE.buffer
            mov eax,[rdx]

            .if ( eax != [rbx] )

                mov   [rbx],eax
                cmp   c,0
                cmovz rcx,rdx
                inc   c

            .elseif ( c )

                mov al,x
                sub al,c
                mov k,al
                _writeline(k, y, c, rcx)
                mov c,0
            .endif
        .endf
        .if ( c )

            mov al,x
            sub al,c
            mov k,al
            _writeline(k, y, c, rcx)
            mov c,0
        .endif
    .endf
    _cwrite("\e8")
    .if ( _cursor.visible )
        _cwrite("\e[?25h")
    .endif
    ret

_conpaint endp


_cbeginpaint proc

    mov rax,_console
    dec [rax].TCONSOLE.paint
    ret

_cbeginpaint endp


_cendpaint proc

    mov rax,_console
    inc [rax].TCONSOLE.paint
    .if ( [rax].TCONSOLE.paint > 0 )

        _conpaint()
    .endif
    ret

_cendpaint endp

    assume rcx:PCONSOLE

_rcread proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

    mov     rcx,_console
    movzx   eax,[rcx].rc.col
    mul     rc.y
    movzx   edx,rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rcx].buffer
    mov     rdi,p
    mov     rsi,rax
    movzx   ebx,word ptr rc[2]
    mov     dh,[rcx].rc.col

    add dl,bl
    .if ( dl > dh )

        mov bl,dh
        sub bl,rc.x
    .endif

    mov al,bh
    add al,rc.y
    .if ( al > [rcx].rc.row )

        mov al,[rcx].rc.row
        mov bh,al
        sub bh,rc.y
    .endif

    .for ( dl = 0 : dl < bh : dl++ )

        mov   rax,rsi
        movzx ecx,bl
        rep   movsd
        mov   cl,dh
        lea   rsi,[rax+rcx*4]
    .endf
    .return( p )

_rcread endp


_rcwrite proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

    mov     rcx,_console
    movzx   eax,[rcx].rc.col
    mul     rc.y
    movzx   edx,rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rcx].buffer
    mov     rdi,rax
    mov     rsi,p
    movzx   ebx,word ptr rc[2]
    mov     dh,[rcx].rc.col
    add     dl,bl

    .if ( dl > dh )

        mov bl,dh
        sub bl,rc.x
    .endif

    mov al,bh
    add al,rc.y
    .if ( al > [rcx].rc.row )

        mov al,[rcx].rc.row
        mov bh,al
        sub bh,rc.y
    .endif

    .for ( dl = 0 : dl < bh : dl++ )

        mov   rax,rdi
        movzx ecx,bl
        rep   movsd
        mov   cl,dh
        lea   rdi,[rax+rcx*4]
    .endf
    mov rcx,_console
    .if ( [rcx].paint > 0 )

        _conpaint()
    .endif
    .return( p )

_rcwrite endp


_scgetp proc x:BYTE, y:BYTE, l:BYTE

    mov     rcx,_console
    movzx   eax,[rcx].rc.col
    mul     y
    movzx   edx,x
    add     eax,edx
    shl     eax,2
    add     rax,[rcx].buffer
    mov     dl,l
    mov     dh,[rcx].rc.col
    mov     rcx,rax
    mov     al,x
    add     al,dl

    .if ( al > dh )

        mov dl,dh
        sub dl,x
    .endif
    ret

_scgetp endp


_scputa proc x:BYTE, y:BYTE, l:BYTE, a:WORD

    _scgetp(x, y, l)
    mov ax,a
    .for ( : dl : dl--, rcx+=4 )
        mov [rcx+2],ax
    .endf
    mov rcx,_console
    .if ( [rcx].paint > 0 )
        _conpaint()
    .endif
    ret

_scputa endp


_scputbg proc x:BYTE, y:BYTE, l:BYTE, a:BYTE

    _scgetp(x, y, l)
    mov dh,a
    shl dh,4
    .for ( : dl : dl--, rcx+=4 )

        mov al,[rcx+2]
        and eax,0x0F
        or  al,dh
        mov [rcx+2],ax
    .endf
    mov rcx,_console
    .if ( [rcx].paint > 0 )
        _conpaint()
    .endif
    ret

_scputbg endp

_scputfg proc x:BYTE, y:BYTE, l:BYTE, a:BYTE

    _scgetp(x, y, l)
    mov dh,a
    .for ( : dl : dl--, rcx+=4 )

        mov al,[rcx+2]
        and eax,0xF0
        or  al,dh
        mov [rcx+2],ax
    .endf
    mov rcx,_console
    .if ( [rcx].paint > 0 )
        _conpaint()
    .endif
    ret

_scputfg endp


_scputc proc x:BYTE, y:BYTE, l:BYTE, a:WORD

    _scgetp(x, y, l)
    mov ax,a
    .for ( : dl : dl--, rcx+=4 )
        mov [rcx],ax
    .endf
    mov rcx,_console
    .if ( [rcx].paint > 0 )
        _conpaint()
    .endif
    ret

_scputc endp


_scputw proc uses rdi x:BYTE, y:BYTE, l:BYTE, ci:CHAR_INFO

    _scgetp(x, y, l)
    mov eax,ci
    mov rdi,rcx
    movzx ecx,dl
    .if ( eax & 0xFFFF0000 )
        rep stosd
    .else
        .for ( : ecx : ecx--, rdi+=4 )
            mov [rdi],ax
        .endf
    .endif
    mov rcx,_console
    .if ( [rcx].paint > 0 )
        _conpaint()
    .endif
    ret

_scputw endp

    assume rcx:PCONSOLE

_scgetw proc x:BYTE, y:BYTE

    mov     rcx,_console
    movzx   eax,[rcx].rc.col
    mul     y
    movzx   edx,x
    add     edx,eax
    shl     edx,2
    add     rdx,[rcx].buffer
    mov     eax,[rdx]
    ret

_scgetw endp


_scgetc proc x:BYTE, y:BYTE

    _scgetw(x, y)
    and eax,0xFFFF
    ret

_scgetc endp


_scgeta proc x:BYTE, y:BYTE

    _scgetw(x, y)
    shr eax,16
    ret

_scgeta endp


    assume rcx:THWND

_conslink proc hwnd:THWND

    mov rax,hwnd
    mov rcx,_console
    .if ( rcx )
        .while ( [rcx].next )
            mov rcx,[rcx].next
        .endw
        mov [rax].TCLASS.prev,rcx
        mov [rcx].TCLASS.next,rax
    .endif
    ret

_conslink endp


_consunlink proc hwnd:THWND

    mov rax,hwnd
    mov rcx,[rax].TCLASS.prev
    mov rdx,[rax].TCLASS.next
    .if ( rcx )
        mov [rcx].TCLASS.next,rdx
    .endif
    .if ( rdx )
        mov [rdx].TCLASS.prev,rcx
    .endif
    ret

_consunlink endp

__inticonsole proc uses rdi rbx

   .new rc:TRECT = {0}
   .new w:int_t
   .new h:int_t

    _consetmode( _conin,  TERMINAL_INPUT )
    _consetmode( _conout, TERMINAL_OUTPUT )

    _cwrite(CSI "?1049h" ) ; push screen

    _cwrite(ESC "7")  ; push cursor
    _cwrite(CSI "256;256H")
    _cursorxy()

    add eax,0x00010001
    movzx ecx,ax
    shr eax,16
    mov w,ecx
    mov h,eax
    _cwrite(ESC "8" ) ; pop cursor

    mov rc.col,w
    mov rc.row,h
    .if ( h == 0 || w == 0 )
        .return 0
    .endif

    mov w,_rcmemsize(rc, 0)
    lea ecx,[rax*2+TCONSOLE]
    mov rbx,malloc(ecx)
    .if ( rax == NULL )
        .return
    .endif
    assume rbx:PCONSOLE

    mov rdi,rax
    mov ecx,TCONSOLE
    xor eax,eax
    rep stosb

    mov ecx,w
    lea rax,[rbx+TCONSOLE]
    mov [rbx].window,rax
    add rax,rcx
    mov [rbx].buffer,rax
    mov rax,_console
    mov [rbx].prev,rax
    mov _console,rbx
    mov [rbx].flags,W_ISOPEN or W_CONSOLE
    mov [rbx].rc,rc
    inc [rbx].paint

    mov rdi,[rbx].window
    shr ecx,1
    mov eax,0x00070020
    rep stosd

    _cwrite(
        "\e]4;0;rgb:00/00/00\e\\"
        "\e]4;7;rgb:AA/AA/AA\e\\"
        )
    _cwrite("\e[48;5;0m")
    _cwrite("\e[38;5;7m")

    lea rcx,_rgbcolortable
    mov [rbx].color,rcx
    mov [rbx].conmax.X,rc.col
    mov [rbx].conmax.Y,rc.row

    ;_congetmode( _conin, &[rbx].modein )
    ;_congetmode( _conout, &[rbx].modeout )
    _gotoxy(0, 0)
    ret

__inticonsole endp

__termconsole proc uses rbx

    mov rbx,_console
    .if ( rbx )

        ;_consetmode( _conin, [rbx].modein )
        ;_consetmode( _conout, [rbx].modeout )
        mov _console,[rbx].prev
        free(rbx)
        _cwrite(CSI "?1049l" ) ; pop screen
    .endif
    ret

__termconsole endp

.pragma(init(__inticonsole, 100))
.pragma(exit(__termconsole, 2))

    end

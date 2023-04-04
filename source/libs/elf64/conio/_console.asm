; _DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include crtl.inc
include malloc.inc

  .data
   _console PCONSOLE 0
   UbuntuColorTable COLORREF \
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
   colorid db \
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

_cbeginpaint proc

    mov rax,_console
    dec [rax].TCONSOLE.paint
    ret

_cbeginpaint endp


_writeline proc private uses rbx _x:BYTE, _y:BYTE, _l:BYTE, p:PCHAR_INFO

   .new x:BYTE = _x
   .new y:BYTE = _y
   .new l:BYTE = _l
   .new bg:int_t = 0
   .new fg:int_t = 0
   .new c:int_t
   .new count:int_t

    mov rbx,p
    _cout("\e7") ; push cursor
    _cursoroff()
    _gotoxy(x, y)

    .for ( : l : l--, rbx+=4 )

        mov eax,[rbx]
        shr eax,16
        mov cl,ah
        and eax,0x0F
        shr ecx,4
        and ecx,0x0F
        lea rsi,colorid
        mov al,[rsi+rax]
        mov cl,[rsi+rcx]

        .if ( eax != fg || ecx != bg )

            mov fg,eax
            mov bg,ecx
            _cout("\e[38;5;%dm\e[48;5;%dm", fg, bg)
        .endif

        mov c,_wtoutf([rbx])
        mov count,ecx

        .for ( : count : count-- )

            _cout("%c", c)
            shr c,8
        .endf
    .endf
    _cout(CSI "38;5;7m" CSI "48;5;0m" ESC "8") ; pop cursor
    ret

_writeline endp


_conpaint proc uses rbx

   .new rc:TRECT
   .new dc:SMALL_RECT

    mov rcx,_console
    mov rsi,[rcx].TCONSOLE.buffer
    mov rdi,[rcx].TCONSOLE.window
    mov rc,[rcx].TCONSOLE.rc

    .for ( bl = 0 : bl < rc.row : bl++ )

        .for ( ecx = 0, bh = 0 : bh < rc.col : bh++, rsi += 4, rdi += 4 )

            mov eax,[rsi]
            .if ( eax != [rdi] )

                mov   [rdi],eax
                test  ecx,ecx
                cmovz rdx,rsi
                inc   ecx

            .elseif ( ecx )

                push rsi
                push rdi
                xchg rdx,rcx
                mov al,bh
                _writeline(al, bl, dl, rcx)
                xor ecx,ecx
                pop rdi
                pop rsi
            .endif
        .endf
        .if ( ecx )

            push rsi
            push rdi
            xchg rdx,rcx
            mov al,bh
            _writeline(al, bl, dl, rcx)
            xor ecx,ecx
            pop rdi
            pop rsi
        .endif
    .endf
    ret

_conpaint endp


_cendpaint proc

    mov rax,_console
    inc [rax].TCONSOLE.paint
    .if ( [rax].TCONSOLE.paint > 0 )

        _conpaint()
    .endif
    ret

_cendpaint endp


_rcread proc uses rbx _rc:TRECT, _p:PCHAR_INFO

   .new     dc:TRECT
   .new     rc:TRECT = _rc
   .new     p:PCHAR_INFO = _p

    mov     rcx,_console
    mov     dc,[rcx].TCONSOLE.rc
    movzx   eax,dc.col
    mul     rc.y
    movzx   edx,rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rcx].TCONSOLE.buffer
    mov     rdi,p
    mov     rsi,rax
    movzx   ebx,word ptr rc[2]

    add dl,bl
    .if ( dl > dc.col )

        mov bl,dc.col
        sub bl,rc.x
    .endif

    mov al,bh
    add al,rc.y
    .if ( al > dc.row )

        mov bh,dc.row
        sub bh,rc.y
    .endif

    .for ( edx = 0 : dl < bh : dl++ )

        mov   rax,rsi
        movzx ecx,bl
        rep   movsd
        mov   cl,dc.col
        lea   rsi,[rax+rcx*4]
    .endf
    .return( p )

_rcread endp


_rcwrite proc uses rbx _rc:TRECT, _p:PCHAR_INFO

   .new     dc:TRECT
   .new     rc:TRECT = _rc
   .new     p:PCHAR_INFO = _p

    mov     rcx,_console
    mov     dc,[rcx].TCONSOLE.rc
    movzx   eax,dc.col
    mul     rc.y
    movzx   edx,rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rcx].TCONSOLE.buffer
    mov     rsi,p
    mov     rdi,rax
    movzx   ebx,word ptr rc[2]

    add dl,bl
    .if ( dl > dc.col )

        mov bl,dc.col
        sub bl,rc.x
    .endif

    mov al,bh
    add al,rc.y
    .if ( al > dc.row )

        mov bh,dc.row
        sub bh,rc.y
    .endif

    .for ( edx = 0 : dl < bh : dl++ )

        mov   rax,rdi
        movzx ecx,bl
        rep   movsd
        mov   cl,dc.col
        lea   rdi,[rax+rcx*4]
    .endf

    mov rax,_console
    .if ( [rax].TCONSOLE.paint > 0 )

        _conpaint()
    .endif
    .return( p )

_rcwrite endp


_scputa proc x:BYTE, y:BYTE, _l:BYTE, _a:WORD

   .new     rc:TRECT
   .new     l:BYTE = _l
   .new     a:WORD = _a

    mov     rcx,_console
    mov     rc,[rcx].TCONSOLE.rc
    movzx   eax,rc.col
    mul     y
    movzx   edx,x
    add     edx,eax
    shl     edx,2
    add     edx,2
    add     rdx,[rcx].TCONSOLE.buffer
    movzx   ecx,l
    mov     al,x
    add     al,cl

    .if ( al > rc.col )
        mov cl,rc.col
        sub cl,x
    .endif
    .for ( ax = a : ecx : ecx--, rdx += 4 )

        mov [rdx],ax
    .endf
    mov rax,_console
    .if ( [rax].TCONSOLE.paint > 0 )

        _conpaint()
    .endif
    ret

_scputa endp


_scputc proc x:BYTE, y:BYTE, _l:BYTE, _a:WORD

   .new     rc:TRECT
   .new     l:BYTE = _l
   .new     a:WORD = _a

    mov     rcx,_console
    mov     rc,[rcx].TCONSOLE.rc
    movzx   eax,rc.col
    mul     y
    movzx   edx,x
    add     edx,eax
    shl     edx,2
    add     rdx,[rcx].TCONSOLE.buffer
    movzx   ecx,l
    mov     al,x
    add     al,cl

    .if ( al > rc.col )
        mov cl,rc.col
        sub cl,x
    .endif
    .for ( ax = a : ecx : ecx--, rdx += 4 )

        mov [rdx],ax
    .endf
    mov rax,_console
    .if ( [rax].TCONSOLE.paint > 0 )

        _conpaint()
    .endif
    ret

_scputc endp


_scputw proc _x:BYTE, _y:BYTE, _l:BYTE, _ci:CHAR_INFO

   .new x:BYTE = _x
   .new y:BYTE = _y
   .new l:BYTE = _l
   .new ci:CHAR_INFO = _ci

    _cbeginpaint()
    .if ( ci.Attributes )
        _scputa( x, y, l, ci.Attributes )
    .endif
    _scputc( x, y, l, ci.Char.UnicodeChar )
    _cendpaint()
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

__inticonsole proc uses rbx

   .new rc:TRECT = {0}
   .new w:int_t
   .new h:int_t

    _cout(
        ESC "7"
        CSI "500;500H"
        CSI "6n" )
    _getcsi2(&h, &w)
    _cout(ESC "8" ) ; pop cursor

    mov rc.col,w
    mov rc.row,h
    .if ( h == 0 || w == 0 )
        .return 0
    .endif

    mov w,_rcmemsize(rc, 0)
    lea edi,[rax*2+TCONSOLE]
    mov rbx,malloc(edi)
    .if ( rax == NULL )
        .return
    .endif
    assume rbx:PCONSOLE

    mov rdi,rax
    mov ecx,TCONSOLE
    xor eax,eax
    rep stosb

    mov esi,w
    lea rax,[rbx+TCONSOLE]
    mov [rbx].window,rax
    add rax,rsi
    mov [rbx].buffer,rax
    mov rax,_console
    mov [rbx].prev,rax
    mov _console,rbx
    mov [rbx].flags,W_ISOPEN or W_CONSOLE
    mov [rbx].rc,rc
    inc [rbx].paint

    mov rdi,[rbx].window
    mov ecx,esi
    shr ecx,1
    mov eax,0x00070020
    rep stosd

    lea rsi,UbuntuColorTable
    mov [rbx].color,rsi
    mov [rbx].conmax.X,rc.col
    mov [rbx].conmax.Y,rc.row
    _cout(CSI "?1049h" ) ; push screen
    ret

__inticonsole endp

    assume rsi:THWND

__termconsole proc

    mov rsi,_console
    .if ( rsi )

        mov _console,[rsi].prev
        free(rsi)
        _cout(CSI "?1049l" ) ; pop screen
    .endif
    ret

__termconsole endp

.pragma(init(__inticonsole, 100))
.pragma(exit(__termconsole, 2))

    end

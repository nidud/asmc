; _DLOPEN.ASM--
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

_cbeginpaint proc

    mov rax,_console
    dec [rax].TCONSOLE.paint
    ret

_cbeginpaint endp


_writeline proc private uses rbx x:BYTE, y:BYTE, l:BYTE, p:PCHAR_INFO

   .new c:int_t
   .new a:int_t = 0
   .new f:byte = -1
   .new b:byte = -1

    mov rbx,rcx

    _gotoxy(dil, sil)

    .for ( : l : l--, rbx+=4 )

        movzx eax,byte ptr [rbx+2]
        mov ecx,eax
        and eax,0x0F
        shr ecx,4

        .if ( al != f || cl != b )

            mov a,1
            mov f,al
            mov b,cl

            lea rsi,_terminalcolorid
            mov al,[rsi+rax]
            mov cl,[rsi+rcx]

            _cout("\e[38;5;%dm\e[48;5;%dm", eax, ecx)
        .endif

        mov c,_wtoutf([rbx])
        write(_confh, &c, ecx)
    .endf
    .if ( a )
        _cout(CSI "m")
    .endif
    ret

_writeline endp


_conpaint proc uses rbx r12 r13

   .new rc:TRECT
   .new dc:SMALL_RECT
   .new cursor:CURSOR

    _getcursor(&cursor)
    _cursoroff()

    mov rcx,_console
    mov r12,[rcx].TCONSOLE.buffer
    mov r13,[rcx].TCONSOLE.window
    mov rc,[rcx].TCONSOLE.rc

    .for ( bl = 0 : bl < rc.row : bl++ )

        .for ( edx = 0, bh = 0 : bh < rc.col : bh++, r12+=4, r13+=4 )

            mov eax,[r12]
            .if ( eax != [r13] )

                mov   [r13],eax
                test  edx,edx
                cmovz rcx,r12
                inc   edx

            .elseif ( edx )

                mov al,bh
                sub al,dl
                _writeline(al, bl, dl, rcx)
                xor edx,edx
            .endif
        .endf
        .if ( edx )

            mov al,bh
            sub al,dl
            _writeline(al, bl, dl, rcx)
            xor edx,edx
        .endif
    .endf
    _setcursor(&cursor)
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

    assume r10:PCONSOLE

_rcread proc uses rbx rc:TRECT, p:PCHAR_INFO

    mov     r11,rsi
    mov     r10,_console
    movzx   eax,[r10].rc.col
    mov     r8b,al
    mul     rc.y
    movzx   edx,rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[r10].buffer
    mov     rdi,r11
    mov     rsi,rax
    movzx   ebx,word ptr rc[2]

    add dl,bl
    .if ( dl > r8b )

        mov bl,[r10].rc.col
        sub bl,rc.x
    .endif

    mov al,bh
    add al,rc.y
    .if ( al > [r10].rc.row )

        mov al,[r10].rc.row
        mov bh,al
        sub bh,rc.y
    .endif

    .for ( edx = 0 : dl < bh : dl++ )

        mov   rax,rsi
        movzx ecx,bl
        rep   movsd
        mov   cl,r8b
        lea   rsi,[rax+rcx*4]
    .endf
    .return( r11 )

_rcread endp


_rcwrite proc uses rbx rc:TRECT, p:PCHAR_INFO

    mov     r11,rsi
    mov     r10,_console
    movzx   eax,[r10].rc.col
    mul     rc.y
    movzx   edx,rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[r10].buffer
    mov     rdi,rax
    movzx   ebx,word ptr rc[2]
    add     dl,bl

    .if ( dl > [r10].rc.col )

        mov bl,[r10].rc.col
        sub bl,rc.x
    .endif

    mov al,bh
    add al,rc.y
    .if ( al > [r10].rc.row )

        mov al,[r10].rc.row
        mov bh,al
        sub bh,rc.y
    .endif

    .for ( edx = 0 : dl < bh : dl++ )

        mov   rax,rdi
        movzx ecx,bl
        rep   movsd
        mov   cl,[r10].rc.col
        lea   rdi,[rax+rcx*4]
    .endf
    mov rbx,r11
    .if ( [r10].paint > 0 )

        _conpaint()
    .endif
    .return( rbx )

_rcwrite endp


_scgetp proc x:BYTE, y:BYTE, l:BYTE

    mov     r10,_console
    movzx   eax,[r10].rc.col
    mov     r8d,eax
    mul     sil
    and     edi,0xFF
    add     eax,edi
    shl     eax,2
    add     rax,[r10].buffer
    mov     rsi,rax
    mov     al,dil
    add     al,dl

    .if ( al > r8b )

        mov dl,r8b
        sub dl,dil
    .endif
    ret

_scgetp endp


_scputa proc x:BYTE, y:BYTE, l:BYTE, a:WORD

    _scgetp(dil, sil, dl)
    .for ( : dl : dl--, rsi+=4 )
        mov [rsi+2],cx
    .endf
    .if ( [r10].paint > 0 )
        _conpaint()
    .endif
    ret

_scputa endp


_scputbg proc x:BYTE, y:BYTE, l:BYTE, a:BYTE

    _scgetp(dil, sil, dl)
    shl cl,4
    .for ( : dl : dl--, rsi+=4 )

        mov al,[rsi+2]
        and eax,0x0F
        or  al,cl
        mov [rsi+2],ax
    .endf
    .if ( [r10].paint > 0 )
        _conpaint()
    .endif
    ret

_scputbg endp

_scputfg proc x:BYTE, y:BYTE, l:BYTE, a:BYTE

    _scgetp(dil, sil, dl)

    .for ( : dl : dl--, rsi+=4 )

        mov al,[rsi+2]
        and eax,0xF0
        or  al,cl
        mov [rsi+2],ax
    .endf
    .if ( [r10].paint > 0 )
        _conpaint()
    .endif
    ret

_scputfg endp


_scputc proc x:BYTE, y:BYTE, l:BYTE, a:WORD

    _scgetp(dil, sil, dl)
    .for ( : dl : dl--, rsi+=4 )
        mov [rsi],cx
    .endf
    .if ( [r10].paint > 0 )
        _conpaint()
    .endif
    ret

_scputc endp


_scputw proc x:BYTE, y:BYTE, l:BYTE, ci:CHAR_INFO

    _scgetp(dil, sil, dl)

    mov eax,ecx
    mov rdi,rsi
    movzx ecx,dl
    .if ( eax & 0xFFFF0000 )
        rep stosd
    .else
        .for ( : ecx : ecx--, rdi+=4 )
            mov [rdi],ax
        .endf
    .endif
    .if ( [r10].paint > 0 )
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

    _scgetw(dil, sil)
    and eax,0xFFFF
    ret

_scgetc endp


_scgeta proc x:BYTE, y:BYTE

    _scgetw(dil, sil)
    shr eax,16
    ret

_scgeta endp


    assume rcx:THWND

_conslink proc hwnd:THWND

    mov rax,rdi
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

    mov rax,rdi
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

    _cout(
        "\e]4;0;rgb:00/00/00\e\\"
        "\e]4;7;rgb:AA/AA/AA\e\\"
        )
    _cout("\e[48;5;0m")
    _cout("\e[38;5;7m")

    _cout(CSI "?1049h" ) ; push screen
    _gotoxy(0, 0)
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

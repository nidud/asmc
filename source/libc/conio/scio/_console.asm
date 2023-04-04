; _DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc


    .data
     _console PCONSOLE 0

    .code

_cbeginpaint proc

    mov rax,_console
    dec [rax].TCONSOLE.paint
    ret

_cbeginpaint endp


_conpaint proc uses rsi rdi rbx

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

                movzx eax,bl
                mov   dc.Top,ax
                mov   dc.Bottom,ax
                movzx eax,bh
                sub   eax,ecx
                mov   dc.Left,ax
                lea   eax,[rcx+rax-1]
                mov   dc.Right,ax
                add   ecx,0x00010000
                WriteConsoleOutputW(_confh, rdx, ecx, 0, &dc)
                xor   ecx,ecx
            .endif
        .endf
        .if ( ecx )

            movzx eax,bl
            mov   dc.Top,ax
            mov   dc.Bottom,ax
            movzx eax,bh
            sub   eax,ecx
            mov   dc.Left,ax
            lea   eax,[rcx+rax-1]
            mov   dc.Right,ax
            add   ecx,0x00010000
            WriteConsoleOutputW(_confh, rdx, ecx, 0, &dc)
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


_rcread proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new     dc:TRECT
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


_rcwrite proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new     dc:TRECT
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


_scputa proc x:BYTE, y:BYTE, l:BYTE, a:WORD

   .new     rc:TRECT
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


_scputc proc x:BYTE, y:BYTE, l:BYTE, a:WORD

   .new     rc:TRECT
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


_scputw proc x:BYTE, y:BYTE, l:BYTE, ci:CHAR_INFO

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


__inticonsole proc uses rsi rdi rbx

   .new bz:COORD
   .new oz:COORD
   .new wc:RECT
   .new rc:TRECT
   .new dc:SMALL_RECT
   .new ci:CONSOLE_SCREEN_BUFFER_INFOEX = {CONSOLE_SCREEN_BUFFER_INFOEX}
   .return .ifd !GetConsoleScreenBufferInfoEx(_confh, &ci)

    mov rcx,GetConsoleWindow()
    GetWindowRect(rcx, &wc)

    mov oz,ci.dwSize
    movzx eax,ci.dwSize.Y
    movzx ecx,ci.dwSize.X
    .if ( ax > ci.dwMaximumWindowSize.Y )
        mov ax,ci.dwMaximumWindowSize.Y
    .endif
    .if ( cx > ci.dwMaximumWindowSize.X )
        mov cx,ci.dwMaximumWindowSize.X
    .endif
    .if ( eax > 240 )
        mov eax,240
    .endif
    .if ( ecx > 240 )
        mov ecx,240
    .endif

    mov rc.x,0
    mov rc.y,0
    mov rc.col,cl
    mov rc.row,al

    .if ( ax != ci.dwSize.Y || cx != ci.dwSize.X )

        mov bz.X,cx
        mov bz.Y,ax
        mov dc.Top,0
        mov dc.Left,0
        mov edx,ecx
        dec edx
        mov dc.Right,dx
        mov edx,eax
        dec edx
        mov dc.Bottom,dx

        .if ( ax == ci.dwMaximumWindowSize.Y &&
              cx == ci.dwMaximumWindowSize.X )

            SetWindowPos(GetConsoleWindow(),0,0,0,0,0,SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER)
        .endif
        SetConsoleWindowInfo(_confh, 1, &dc)
        SetConsoleScreenBufferSize(_confh, bz)
        SetConsoleWindowInfo(_confh, 1, &dc)
        .ifd GetConsoleScreenBufferInfoEx(_confh, &ci)

            mov rc.col,ci.dwSize.X
            mov rc.row,ci.dwSize.Y
        .endif
    .endif

    mov esi,_rcmemsize(rc, 0)
    lea ecx,[rsi*2+TCONSOLE]
    mov rbx,malloc(ecx)
    .if ( rax == NULL )
        .return
    .endif
    assume rbx:PCONSOLE

    mov rdi,rax
    mov ecx,TCONSOLE
    xor eax,eax
    rep stosb

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

    mov dc.Top,0
    mov dc.Left,0
    mov ax,ci.dwSize.X
    dec ax
    mov dc.Right,ax
    mov ax,ci.dwSize.Y
    dec ax
    mov dc.Bottom,ax
    mov rdi,[rbx].window

    .ifd !ReadConsoleOutputW(_confh, rdi, ci.dwSize, 0, &dc)

        mov ecx,esi
        shr ecx,2
        mov eax,0x00070020
        rep stosd
    .endif
    mov ecx,esi
    shr ecx,2
    mov rsi,[rbx].window
    mov rdi,[rbx].buffer
    rep movsd
    lea rsi,ci.ColorTable
    lea rdi,[rbx].color
    mov ecx,16
    rep movsd
    mov [rbx].winpos.X,wc.left
    mov [rbx].winpos.Y,wc.top
    mov [rbx].consize,oz
    mov [rbx].conmax,ci.dwMaximumWindowSize
    GetConsoleMode(_confh, &[rbx].modeout)
    GetConsoleMode(_coninpfh, &[rbx].modein)
    SetConsoleMode(_coninpfh, ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
    FlushConsoleInputBuffer(_coninpfh)
    ret

__inticonsole endp

    assume rsi:THWND

__termconsole proc uses rsi rbx

    mov rbx,_console
    .if ( rbx )

        SetConsoleMode(_confh, [rbx].modeout)
        SetConsoleMode(_coninpfh, [rbx].modein)

        mov rsi,[rbx].next
        .while ( rsi && [rsi].next )
            mov rsi,[rsi].next
        .endw
        .while ( rsi && rsi != rbx )
            mov rcx,rsi
            mov rsi,[rsi].prev
            _dlclose(rcx)
        .endw
        mov rsi,[rbx].prev
        mov _console,rsi
        .if ( rsi )
            mov [rsi].next,NULL
        .endif

       .new rc:SMALL_RECT
        mov rc.Top,0
        mov rc.Left,0
        mov ax,[rbx].consize.X
        dec ax
        mov rc.Right,ax
        mov ax,[rbx].consize.Y
        dec ax
        mov rc.Bottom,ax

        SetConsoleWindowInfo(_confh, 1, &rc)
        SetConsoleScreenBufferSize(_confh, [rbx].consize)
        SetConsoleWindowInfo(_confh, 1, &rc)
        mov rcx,GetConsoleWindow()
        SetWindowPos( rcx, 0,
            [rbx].winpos.X, [rbx].winpos.Y, 0, 0, SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER )
        free(rbx)
    .endif
    ret

__termconsole endp

.pragma(init(__inticonsole, 100))
.pragma(exit(__termconsole, 2))

    end

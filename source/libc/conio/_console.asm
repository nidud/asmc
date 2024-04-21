; _CONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include stdlib.inc
include malloc.inc

    .data
    _console PCONSOLE 0

    .code

__initconsole proc uses rsi rdi rbx

   .new rc:TRECT = {0}
   .new w:int_t = 0
   .new h:int_t = 0

ifndef __TTY__

   .new bz:COORD
   .new sr:SMALL_RECT
   .new ci:CONSOLE_SCREEN_BUFFER_INFOEX = {CONSOLE_SCREEN_BUFFER_INFOEX}

    .if GetConsoleScreenBufferInfoEx(_confh, &ci)

        SetConsoleCursorPosition(_confh, 0)

        movzx eax,ci.srWindow.Right
        sub ax,ci.srWindow.Left
        inc eax
        .if eax > MAXCOLS
            mov eax,MAXCOLS
        .elseif eax < MINCOLS
            mov eax,MINCOLS
        .endif
        mov w,eax
        movzx eax,ci.srWindow.Bottom
        sub ax,ci.srWindow.Top
        inc eax
        .if eax > MAXROWS
            mov eax,MAXROWS
        .elseif eax < MINROWS
            mov eax,MINROWS
        .endif
        mov h,eax

        lea rdi,_rgbcolortable
        lea rsi,ci.ColorTable
        mov ecx,16
        rep movsd

        mov eax,w
        dec eax
        mov edx,h
        dec edx

        .if ( dx != ci.srWindow.Right || ax != ci.srWindow.Bottom )

            mov ci.srWindow.Top,0
            mov ci.srWindow.Left,0
            mov ci.srWindow.Right,dx
            mov ci.srWindow.Bottom,ax
            SetConsoleWindowInfo(_confh, 1, &ci.srWindow)
        .endif
        mov edx,h
        shl edx,16
        mov dx,word ptr w
        SetConsoleScreenBufferSize(_confh, edx)
    .endif

else

    _cout(CSI "?1049h" )  ; push screen
    _cout(ESC "7")        ; push cursor
    _cout(CSI "256;256H")
    _cursorxy()

    add eax,0x00010001
    movzx ecx,ax
    shr eax,16
    mov w,ecx
    mov h,eax
    _cout(ESC "8" ) ; pop cursor

endif

    mov rc.col,w
    mov rc.row,h
    .if ( h == 0 || w == 0 )
        .return 0
    .endif

    mov w,_rcmemsize(rc, W_UTF16)
    lea ecx,[rax*2+TCONSOLE+MESSAGE*MAXMSGCNT]
    .if ( malloc(ecx) == NULL )

        .return
    .endif

    assume rbx:PCONSOLE

    mov rbx,rax
    mov rdi,rax
    mov ecx,TCONSOLE
    xor eax,eax
    rep stosb

    mov ecx,w
    lea rax,[rbx+TCONSOLE]
    mov [rbx].window,rax
    add rax,rcx
    mov [rbx].buffer,rax
    add rax,rcx
    mov [rbx].msgptr,rax
    mov [rbx].prev,_console
    mov _console,rbx
    mov [rbx].flags,W_ISOPEN or W_CONSOLE
    mov [rbx].rc,rc

    mov rdi,[rbx].window
    shr ecx,1
    mov eax,0x00070020
    rep stosd
    mov ecx,( ( MESSAGE * MAXMSGCNT ) / 4 )
    xor eax,eax
    rep stosd

    ; circular buffer for the message loop..

    .for ( rdx = [rbx].msgptr : ecx < MAXMSGCNT : ecx++, rdx+=MESSAGE )

        lea rax,[rdx+MESSAGE]
        lea rdi,[rdx-MESSAGE]
        mov [rdx].MESSAGE.next,rax
        mov [rdx].MESSAGE.prev,rdi
    .endf
    sub rdx,MESSAGE
    mov [rdx].MESSAGE.next,[rbx].msgptr
    mov [rax].MESSAGE.prev,rdx
    mov [rbx].focus,1

ifdef __TTY__

    _cout("\e]4;0;rgb:00/00/00\e\\\e]4;7;rgb:AA/AA/AA\e\\")
    _cout("\e[48;5;0m")
    _cout("\e[38;5;7m")

else

    movzx   eax,rc.col
    movzx   edx,rc.row
    movzx   ecx,rc.y
    mov     bz.X,ax
    mov     bz.Y,dx
    mov     sr.Top,cx
    lea     ecx,[rcx+rdx-1]
    mov     sr.Bottom,cx
    movzx   ecx,rc.x
    mov     sr.Left,cx
    lea     eax,[rcx+rax-1]
    mov     sr.Right,ax

    .ifd ReadConsoleOutputW(_confh, [rbx].window, bz, 0, &sr)

        mov rsi,[rbx].window
        mov rdi,[rbx].buffer
        mov ecx,w
        rep movsb
    .endif

endif

    lea rcx,_rgbcolortable
    mov [rbx].color,rcx
    mov [rbx].conmax.X,rc.col
    mov [rbx].conmax.Y,rc.row
    _gotoxy(0, 0)
    ret

__initconsole endp

__termconsole proc uses rbx

    mov rbx,_console
    .if ( rbx )

        mov _console,[rbx].prev
        free(rbx)
ifdef __TTY__
        _cout(CSI "?1049l" ) ; pop screen
endif
    .endif
    ret

__termconsole endp

.pragma(init(__initconsole, 100))
.pragma(exit(__termconsole, 2))

    end

include malloc.inc
include tdialog.inc

    .data
    Console LPTCONSOLE 0

    .code

    assume rcx: ptr TConsole

TConsole::Read proc uses rsi rdi rbx

  local co:COORD, rc:SMALL_RECT

    mov rax,[rcx].rect
    mov rc,rax
    mov ax,rc.Right
    sub ax,rc.Left
    inc ax
    mov co.x,ax
    mov ax,rc.Bottom
    sub ax,rc.Top
    inc ax
    mov co.y,ax
    mov rsi,[rcx].backgr

    .if !ReadConsoleOutput(hStdOutput, rsi, co, 0, &rc)

        movzx ebx,co.y
        movzx edi,co.x
        shl   edi,2

        .for( ax=rc.Top, rc.Bottom=ax, co.y=1,
            : ebx, ReadConsoleOutput(hStdOutput, rsi, co, 0, &rc),
            : rc.Bottom++, rc.Top++, rsi+=rdi, ebx-- )
        .endf

        xor eax,eax
        cmp ebx,1
        adc eax,0
    .endif
    mov rcx,_this
    ret

TConsole::Read endp

TConsole::Write proc uses rsi rdi rbx buffer:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    mov   rsi,rdx
    mov   rax,[rcx].rect
    mov   rc,rax
    mov   ax,rc.Right
    sub   ax,rc.Left
    inc   ax
    mov   co.x,ax
    movzx edi,ax
    shl   edi,2
    mov   ax,rc.Bottom
    sub   ax,rc.Top
    inc   ax
    mov   co.y,ax
    movzx ebx,ax
    .for( ax=rc.Top, rc.Bottom=ax, co.y=1,
        : ebx, WriteConsoleOutput(hStdOutput, rsi, co, 0, &rc),
        : rc.Bottom++, rc.Top++, rsi+=rdi, ebx-- )
    .endf
    xor eax,eax
    cmp ebx,1
    adc eax,0
    mov rcx,_this
    ret

TConsole::Write endp

TConsole::Show proc

    .if [rcx].flags & _TW_ISOPEN

        or [rcx].flags,_TW_VISIBLE
        [rcx].Write( [rcx].window )
    .endif
    ret

TConsole::Show endp

TConsole::Hide proc

    .if [rcx].flags & _TW_ISOPEN

        and [rcx].flags,not _TW_VISIBLE
        [rcx].Write( [rcx].backgr )
    .endif
    ret

TConsole::Hide endp

TConsole::IsInsideX proc x:SINT

    xor eax,eax
    .if dx <= [rcx].rect.Right && dx >= [rcx].rect.Left

        mov eax,edx
        sub ax,[rcx].rect.Left
        inc eax
    .endif
    ret

TConsole::IsInsideX endp

TConsole::IsInsideY proc y:SINT

    xor eax,eax
    .if dx <= [rcx].rect.Bottom && dx >= [rcx].rect.Top

        mov eax,edx
        sub ax,[rcx].rect.Top
        inc eax
    .endif
    ret

TConsole::IsInsideY endp

TConsole::IsInsideXY proc x:SINT, y:SINT

    .if [rcx].IsInsideX(edx)
        [rcx].IsInsideY(r8d)
    .endif
    ret

TConsole::IsInsideXY endp

TConsole::GetChar proc x:SINT, y:SINT

    .if [rcx].IsInsideX(edx)

        lea r9d,[eax-1]

        .if [rcx].IsInsideY(r8d)

            dec eax

            movzx edx,[rcx].rect.Right
            sub dx,[rcx].rect.Left
            inc edx
            mul edx
            add eax,r9d
            shl eax,2
            add rax,[rcx].window
            mov eax,[rax]
        .endif
    .endif
    ret

TConsole::GetChar endp

TConsole::PutChar proc x:SINT, y:SINT, w:UINT

    .if [rcx].IsInsideX(edx)

        lea r10d,[eax-1]

        .if [rcx].IsInsideY(r8d)

            dec eax

            movzx edx,[rcx].rect.Right
            sub dx,[rcx].rect.Left
            inc edx
            mul edx
            add eax,r10d
            shl eax,2
            add rax,[rcx].window
            mov [rax],r9d
        .endif
    .endif
    ret

TConsole::PutChar endp

TConsole::SetConsoleSize proc uses rsi rdi cols:UINT, rows:UINT

  local bz:COORD
  local rc:SMALL_RECT
  local ci:CONSOLE_SCREEN_BUFFER_INFO

    .ifd GetConsoleScreenBufferInfo(hStdOutput, &ci)

        mov rc.Left,0
        mov rc.Top,0
        mov eax,cols
        mov bz.x,ax
        dec eax
        mov rc.Right,ax
        mov eax,rows
        mov bz.y,ax
        dec eax
        mov rc.Bottom,ax

        SetConsoleWindowInfo(hStdOutput, 1, &rc)
        SetConsoleScreenBufferSize( hStdOutput, bz)
        SetConsoleWindowInfo(hStdOutput, 1, &rc)

        .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

            assume rsi:ptr TConsole

            mov rsi,_this
            mov eax,ci.dwSize

            movzx edx,ax
            shr eax,16
            lea ecx,[eax-1]
            mov [rsi].rect.Bottom,cx
            lea ecx,[edx-1]
            mov [rsi].rect.Right,cx

            mul edx
            lea edi,[eax*4]
            lea ecx,[edi*2]

            .if malloc(rcx)

                mov rcx,[rsi].window
                mov [rsi].window,rax
                free(rcx)

                mov rax,[rsi].window
                add rax,rdi
                mov [rsi].backgr,rax
                mov [rsi].flags,_TW_ISOPEN
                [rsi].Read()

                mov rax,rsi
                mov rdi,[rsi].window
                mov rsi,[rsi].backgr
                mov rcx,rsi
                sub rcx,rdi
                rep movsb
                mov rcx,rax
            .endif
            assume rsi:nothing
        .endif
    .endif
    ret

TConsole::SetConsoleSize endp

TConsole::SetMaxConsole proc

    SetWindowPos(GetConsoleWindow(),0,0,0,0,0,SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER)
    mov edx,GetLargestConsoleWindowSize(hStdOutput)
    shr eax,16
    movzx edx,dx
    .if ecx < 80 || eax < 16
        mov edx,80
        mov eax,25
    .elseif edx > 255 || eax > 255
        .if edx > 255
            mov edx,240
        .endif
        .if eax > 255
            mov eax,240
        .endif
    .endif
    _this.SetConsoleSize(edx, eax)
    ret

TConsole::SetMaxConsole endp

TConsole::Release proc

    free( [rcx].window )
    free( _this )
    ret

TConsole::Release endp

TConsole::TConsole proc uses rsi rdi

  local ci: CONSOLE_SCREEN_BUFFER_INFO

    .if malloc( sizeof(TConsole) + sizeof(TConsoleVtbl) )

        assume rsi:ptr TConsole

        mov rsi,rax
        lea rdi,[rax+sizeof(TConsole)]
        mov [rsi].lpVtbl,rdi
        for x,<Release,Show,Hide,Read,Write,GetChar,PutChar,IsInsideX,IsInsideY,IsInsideXY,SetMaxConsole,SetConsoleSize>
            lea rax,TConsole_&x&
            stosq
        endm
        xor eax,eax
        mov [rsi].flags,eax
        mov [rsi].rect,rax
        mov [rsi].window,rax
        mov edi,0x00190050
        .if GetConsoleScreenBufferInfo( hStdOutput, &ci )

            mov edi,ci.dwSize
        .endif
        movzx eax,di
        shr edi,16
        lea ecx,[eax-1]
        mov [rsi].rect.Right,cx
        lea ecx,[edi-1]
        mov [rsi].rect.Bottom,cx
        mul di
        lea edi,[eax*4]
        lea eax,[edi*2]
        .if malloc(eax)
            mov [rsi].window,rax
            add rax,rdi
            mov [rsi].backgr,rax
            mov [rsi].flags,_TW_ISOPEN
            [rsi].Read()
            mov rax,rsi
            mov rdi,[rsi].window
            mov rsi,[rsi].backgr
            mov rcx,rsi
            sub rcx,rdi
            rep movsb
            mov rcx,rax
        .endif
    .endif
    ret

TConsole::TConsole endp

Install proc private

    mov Console,TConsole::TConsole(0)
    ret
Install endp

.pragma(init(Install, 50))

    end

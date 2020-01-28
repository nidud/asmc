; TCONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include stdio.inc
include twindow.inc

    .code

TWindow::MoveConsole proc uses rcx x:int_t, y:int_t

    SetWindowPos( GetConsoleWindow(), 0, x, y, 0, 0, SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER )
    ret

TWindow::MoveConsole endp

    assume rcx:window_t
    assume rbx:window_t
    assume rsi:class_t

TWindow::SetConsole proc uses rsi rbx rcx cols:int_t, rows:int_t

  local bz:COORD
  local rc:SMALL_RECT
  local ci:CONSOLE_SCREEN_BUFFER_INFO

    mov rsi,[rcx].Class
    mov rcx,[rsi].Console

    movzx   eax,[rcx].rc.x
    mov     bz.x,dx
    mov     bz.y,r8w
    mov     rc.Left,ax
    add     eax,edx
    dec     eax
    mov     rc.Right,ax
    movzx   eax,[rcx].rc.y
    add     eax,r8d
    dec     eax
    mov     rc.Bottom,ax

    .ifd GetConsoleScreenBufferInfo([rsi].StdOut, &ci)

        SetConsoleWindowInfo([rsi].StdOut, 1, &rc)
        SetConsoleScreenBufferSize([rsi].StdOut, bz)
        SetConsoleWindowInfo([rsi].StdOut, 1, &rc)

        .if GetConsoleScreenBufferInfo([rsi].StdOut, &ci)

            mov     rbx,[rsi].Console
            movzx   eax,ci.dwSize.y
            mov     [rbx].rc.row,al
            movzx   ecx,ci.dwSize.x
            mov     [rbx].rc.col,cl
            mul     ecx

            .if malloc(&[rax*4])

                mov rcx,[rbx].Window
                mov [rbx].Window,rax
                free(rcx)
                or [rbx].Flags,W_ISOPEN
                [rbx].Read(&[rbx].rc, [rbx].Window)
                mov eax,1
            .endif
        .endif
    .endif
    ret

TWindow::SetConsole endp

TWindow::SetMaxConsole proc uses rsi rcx

    mov rsi,[rcx].Class
    mov rcx,[rsi].Console

    [rcx].MoveConsole(0, 0)
    GetLargestConsoleWindowSize([rsi].StdOut)
    mov rcx,[rsi].Console

    mov edx,eax
    shr eax,16
    and edx,0xFFFF

    .if ( edx < 80 || eax < 16 )
        mov edx,80
        mov eax,25
    .elseif ( edx > 255 || eax > 255 )
        .if ( edx > 255 )
            mov edx,240
        .endif
        .if ( eax > 255 )
            mov eax,240
        .endif
    .endif
    [rcx].SetConsole(edx, eax)
    ret

TWindow::SetMaxConsole endp

TWindow::ConsoleSize proc uses rcx

    mov     rax,[rcx].Class
    mov     rcx,[rax].TClass.Console
    movzx   edx,[rcx].rc.row
    mov     eax,edx
    shl     eax,16
    mov     al,[rcx].rc.col
    ret

TWindow::ConsoleSize endp

TWindow::CGetChar proc uses rsi rdi rcx x:int_t, y:int_t

  local ci:CHAR_INFO
  local NumberOfAttrsRead:dword

    mov     ci.Attributes,0
    mov     ci.UnicodeChar,0

    mov     rsi,[rcx].Class
    movzx   edi,r8b
    shl     edi,16
    mov     di,dx

    ReadConsoleOutputAttribute( [rsi].StdOut, &ci.Attributes,  1, edi, &NumberOfAttrsRead )
    ReadConsoleOutputCharacter( [rsi].StdOut, &ci.UnicodeChar, 1, edi, &NumberOfAttrsRead )

    mov eax,0x00FFFFFF
    and eax,ci
    ret

TWindow::CGetChar endp

TWindow::CPutChar proc uses rsi rdi rbx rcx x:int_t, y:int_t, count:int_t, ci:CHAR_INFO

  local NumberWritten:dword

    mov     rsi,[rcx].Class
    movzx   edi,r8b
    shl     edi,16
    mov     di,dx
    mov     ebx,r9d

    .if ci.Attributes
        FillConsoleOutputAttribute( [rsi].StdOut, ci.Attributes,  ebx, edi, &NumberWritten )
    .endif
    .if ci.UnicodeChar
        FillConsoleOutputCharacter( [rsi].StdOut, ci.UnicodeChar, ebx, edi, &NumberWritten )
    .endif
    ret

TWindow::CPutChar endp

TWindow::CPutString proc uses rsi rdi rbx rcx x:int_t, y:int_t, at:ushort_t, max:int_t, format:string_t, argptr:vararg

  local buffer[4096]:char_t
  local ci:CHAR_INFO
  local retval:int_t
  local sx:int_t
  local highat:byte

    mov     eax,r9d
    mov     highat,ah
    mov     sx,edx
    mov     rsi,[rcx].Class
    mov     rbx,[rsi].Console
    movzx   eax,al
    shl     eax,16
    mov     ci,eax
    mov     retval,vsprintf(&buffer, format, &argptr)

    .if max == 0

        movzx eax,[rbx].rc.col
        sub eax,x
        mov max,eax
    .endif

    .for ( rsi = &buffer : byte ptr [rsi] && max : rsi++, max-- )

        mov eax,ci
        mov al,[rsi]

        .switch
        .case al == 10
            inc     y
            mov     sx,x
            movzx   ecx,[rbx].rc.col
            sub     ecx,eax
            mov     max,ecx
            .endc
        .case al == 9
            add     sx,4
            .endc
        .case al == '&' && highat
            inc     rsi
            movzx   eax,highat
            shl     eax,16
            mov     al,[rsi]
        .default
            [rbx].CPutChar( sx, y, 1, eax )
            inc     sx
        .endsw
    .endf
    mov eax,retval
    ret

TWindow::CPutString endp

TWindow::CPutPath proc uses rsi rdi rbx rcx x:int_t, y:int_t, max:int_t, path:string_t

  local pre[16]:char_t

    mov rsi,[rcx].Class
    mov rbx,[rsi].Console

    mov rsi,path
    mov edi,r9d

    .ifd strlen(rsi) > edi

        lea rcx,pre

        mov edx,[rsi]
        add rsi,rax
        sub rsi,rdi
        mov eax,4

        .if dh == ':'
            mov [rcx],dx
            shr edx,8
            mov dl,'.'
            add rcx,2
            add eax,2
        .else
            mov dx,'/.'
        .endif

        add rsi,rax
        sub edi,eax
        mov [rcx],dh
        mov [rcx+1],dl
        mov [rcx+2],dx
        mov byte ptr [rcx+4],0
        mov edx,x
        add x,eax
        [rbx].CPutString(edx, y, 0, 6, &pre)
    .endif
    [rbx].CPutString(x, y, 0, edi, rsi)
    ret

TWindow::CPutPath endp

TWindow::CPutCenter proc uses rsi rdi rbx x:int_t, y:int_t, l:int_t, string:string_t

    mov rsi,[rcx].Class
    mov rbx,[rsi].Console
    mov rsi,string
    mov edi,r9d
    .return [rbx].CPutPath(x, y, edi, rsi) .ifd strlen(rsi) > edi

    sub edi,eax
    shr edi,1
    add x,edi
    [rbx].CPutString(x, y, 0, eax, rsi)
    ret

TWindow::CPutCenter endp

TWindow::CPutBackground proc uses rsi rdi rbx rcx x:int_t, y:int_t, count:int_t, bg:uchar_t

  local NumberOfAttrsRead:dword
  local at[MAXSCRLINE]:word
  local pos:COORD

    mov pos.x,dx
    mov pos.y,r8w
    mov ebx,r9d
    .if ebx > MAXSCRLINE
        mov ebx,MAXSCRLINE
    .endif
    mov rsi,[rcx].Class
    .if ReadConsoleOutputAttribute( [rsi].StdOut, &at, ebx, pos, &NumberOfAttrsRead )

        .for rdi = &at, ebx = NumberOfAttrsRead : ebx : ebx--, rdi+=2, pos.x++

            movzx edx,bg
            shl dl,4
            mov al,[rdi]
            and al,0x0F
            or  dl,al

            FillConsoleOutputAttribute( [rsi].StdOut, dx, 1, pos, &NumberOfAttrsRead )
        .endf

    .endif
    ret

TWindow::CPutBackground endp

    end

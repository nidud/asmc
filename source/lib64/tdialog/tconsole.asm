include malloc.inc
include stdio.inc
include tdialog.inc

    .data
    Console LPTCONSOLE 0
    virtual_table label qword
        dq TConsole_Release
        dq TConsole_Update
        dq TConsole_Hide
        dq TConsole_Read
        dq TConsole_Write
        dq TConsole_Getchar
        dq TConsole_Putchar
        dq TConsole_Putattrib
        dq TConsole_Getattrib
        dq TConsole_Setattrib
        dq TConsole_Clrconsole
        dq TConsole_CPrintf
        dq TConsole_CPuta
        dq TConsole_Getrectptr
        dq TConsole_Insidex
        dq TConsole_Insidey
        dq TConsole_Inside
        dq TConsole_Maxconsole
        dq TConsole_Setconsole
        dq TConsole_Moveconsole
        dq TConsole_Readevent
        dq TConsole_Getevent
        dq TConsole_Getch
        dq TConsole_Shiftstate
        dq TConsole_Mousepress
        dq TConsole_Getmousex
        dq TConsole_Getmousey
        dq TConsole_Pushevent
        dq TConsole_Popevent
        dq TConsole_Setkeystate
        dq TConsole_ClipFree
        dq TConsole_ClipCopy
        dq TConsole_ClipPaste
        dq TConsole_CursorOn
        dq TConsole_CursorOff
        dq TConsole_CursorGet
        dq TConsole_CursorSet

    .code

    assume rcx: ptr TConsole

TConsole::Release proc

    [rcx].ClipFree()
    free( [rcx].window )
    free( _this )
    ret

TConsole::Release endp

TConsole::TConsole proc uses rsi rdi

  local ci: CONSOLE_SCREEN_BUFFER_INFO

    assume rsi:ptr TConsole

    .if malloc( sizeof(TConsole) )

        mov rsi,rax
        mov rdi,rax
        xor eax,eax
        mov ecx,sizeof(TConsole)
        rep stosb
        lea rax,virtual_table
        mov [rsi],rax
        lea rdi,[rsi].foreground
        mov rax,0x07000008070F0F00
        stosq
        mov rax,0x0F0F0F000B0A0008
        stosq
        mov rax,0x7030304070701000
        stosq
        mov rax,0x0707000000303030
        stosq
        mov edi,0x00190050
        .if GetConsoleScreenBufferInfo( hStdOutput, &ci )

            mov edi,ci.dwSize
        .endif
        movzx eax,di
        shr edi,16
        mov [rsi].rc.col,al
        mov edx,edi
        mov [rsi].rc.row,dl
        mul edi
        lea rdi,[rax*4]
        lea rcx,[rdi*2]

        .if malloc( rcx )

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
    assume rsi:nothing

    mov r8,_this
    .if r8
        mov [r8],rax
    .endif
    ret

TConsole::TConsole endp

TConsole::Read proc uses rsi rdi rbx

  local co:COORD, rc:SMALL_RECT

    xor eax,eax
    mov rc,rax
    mov al,[rcx].rc.col
    mov co.x,ax
    dec al
    mov rc.Right,ax
    mov al,[rcx].rc.row
    mov co.y,ax
    dec al
    mov rc.Bottom,ax

    mov rsi,[rcx].backgr

    .if !ReadConsoleOutput(hStdOutput, rsi, co, 0, &rc)

        movzx ebx,co.y
        movzx edi,co.x
        shl   edi,2
        mov   ax,rc.Top
        mov   rc.Bottom,ax
        mov   co.y,1

        .repeat
            .break .if !ReadConsoleOutput(hStdOutput, rsi, co, 0, &rc)
            inc rc.Bottom
            inc rc.Top
            add rsi,rdi
            dec ebx
        .until !ebx

        xor eax,eax
        cmp ebx,1
        adc eax,0
    .endif
    mov rcx,_this
    ret

TConsole::Read endp

TConsole::Write proc uses rsi rdi rbx buffer:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    xor eax,eax
    mov rc,rax
    mov al,[rcx].rc.col
    mov co.x,ax
    dec al
    mov rc.Right,ax
    mov al,[rcx].rc.row
    mov co.y,ax
    dec al
    mov rc.Bottom,ax
    mov rsi,rdx

    .ifd !WriteConsoleOutput(hStdOutput, rdx, co, 0, &rc)

        movzx edi,co.x
        movzx ebx,co.y
        shl edi,2
        mov rc.Bottom,0
        mov co.y,1
        .for : ebx, WriteConsoleOutput(hStdOutput, rsi, co, 0, &rc) : ebx--,
            rc.Bottom++, rc.Top++, rsi+=rdi
        .endf
    .endif
    xor eax,eax
    cmp ebx,1
    adc eax,0
    mov rcx,_this
    ret

TConsole::Write endp

TConsole::Update proc

    .if [rcx].flags & _TW_ISOPEN

        or [rcx].flags,_TW_VISIBLE
        [rcx].Write( [rcx].window )
    .endif
    ret

TConsole::Update endp

TConsole::Hide proc

    .if [rcx].flags & _TW_ISOPEN

        and [rcx].flags,not _TW_VISIBLE
        [rcx].Write( [rcx].backgr )
    .endif
    ret

TConsole::Hide endp

    option win64:rsp nosave noauto

TConsole::Insidex proc x:SINT

    xor eax,eax
    .if dl < [rcx].rc.col

        lea rax,[rdx+1]
    .endif
    ret

TConsole::Insidex endp

TConsole::Insidey proc y:SINT

    xor eax,eax
    .if dl < [rcx].rc.row

        lea rax,[rdx+1]
    .endif
    ret

TConsole::Insidey endp

    option win64:rbp nosave auto

TConsole::Inside proc x:SINT, y:SINT

    .if [rcx].Insidex(edx)
        [rcx].Insidey(r8d)
    .endif
    ret

TConsole::Inside endp

TConsole::Getchar proc x:SINT, y:SINT

    .if [rcx].Insidex(edx)

        lea r9,[rax-1]

        .if [rcx].Insidey(r8d)

            dec eax

            movzx edx,[rcx].rc.col
            mul edx
            add eax,r9d
            shl eax,2
            add rax,[rcx].window
            mov eax,[rax]
        .endif
    .endif
    ret

TConsole::Getchar endp

TConsole::Getrectptr proc rc:TRECT

    movzx r8d,rc.y
    movzx edx,rc.x

    .if [rcx].Insidex(edx)

        lea r9,[rax-1]

        .if [rcx].Insidey(r8d)

            dec eax

            movzx edx,[rcx].rc.col
            mul edx
            add eax,r9d
            shl eax,2
            add rax,[rcx].window
        .endif
    .endif
    ret

TConsole::Getrectptr endp

TConsole::Putchar proc x:SINT, y:SINT, w:UINT

    .if [rcx].Insidex(edx)

        lea r10,[rax-1]

        .if [rcx].Insidey(r8d)

            dec eax

            movzx edx,[rcx].rc.col
            mul edx
            add eax,r10d
            shl eax,2
            add rax,[rcx].window
            mov [rax],r9w
        .endif
    .endif
    ret

TConsole::Putchar endp

TConsole::Putattrib proc x:SINT, y:SINT, w:UINT

    .if [rcx].Insidex(edx)

        lea r10,[rax-1]

        .if [rcx].Insidey(r8d)

            dec eax

            movzx edx,[rcx].rc.col
            mul edx
            add eax,r10d
            shl eax,2
            add rax,[rcx].window
            mov [rax+2],r9w
        .endif
    .endif
    ret

TConsole::Putattrib endp

    option win64:rsp nosave noauto

TConsole::Setattrib proc attrib:BYTE

    mov al,dl
    and al,0x0F
    mov [rcx].foreground[F_Desktop],al
    and dl,0xF0
    mov [rcx].background[B_Desktop],dl
    ret

TConsole::Setattrib endp

TConsole::Getattrib proc f_id:UINT, b_id:UINT

    movzx eax,[rcx].foreground[rdx]
    or    al,[rcx].background[r8]
    ret

TConsole::Getattrib endp

TConsole::Clrconsole proc uses rdi rcx

    movzx   eax,[rcx].foreground[F_Desktop]
    or      al,[rcx].background[B_Desktop]
    shl     eax,16
    mov     al,' '
    mov     rdi,[rcx].window
    movzx   edx,[rcx].rc.col
    movzx   ecx,[rcx].rc.row
    imul    ecx,edx
    rep     stosd
    ret

TConsole::Clrconsole endp

    option win64:rbp save auto

TConsole::CPrintf proc uses rsi rdi rbx x:SINT, y:SINT, format:LPSTR, argptr:VARARG

  local o:_iobuf

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,_INTIOBUF
    mov _bufin,0
    lea rax,_bufin
    mov o._ptr,rax
    mov o._base,rax
    _output(&o, format, &argptr)
    mov rdx,o._ptr
    mov byte ptr [rdx],0
    .for rsi=&_bufin, ebx=eax, edi=x, rcx=_this: ebx: ebx--, edi++
        lodsb
        .if al == 10
            mov edi,x
            dec edi
            inc y
        .else
            movzx r9d,al
            [rcx].Putchar(edi, y, r9d)
        .endif
    .endf
    ret

TConsole::CPrintf endp

TConsole::CPuta proc uses rsi rdi x:SINT, y:SINT, l:SINT, a:BYTE

    .for edi=edx, esi=r9d, r9b=a : esi: esi--, edi++
        [rcx].Putattrib(edi, r8d, r9d)
    .endf
    ret

TConsole::CPuta endp

TConsole::Setconsole proc uses rsi rdi rcx cols:UINT, rows:UINT

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
            mov [rsi].rc.row,al
            mov [rsi].rc.col,dl

            mul edx
            lea rdi,[rax*4]
            lea rcx,[rdi*2]

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

TConsole::Setconsole endp

TConsole::Maxconsole proc

    [rcx].Moveconsole(0, 0)
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
    _this.Setconsole(edx, eax)
    ret

TConsole::Maxconsole endp

TConsole::Moveconsole proc uses rcx x:UINT, y:UINT

    SetWindowPos( GetConsoleWindow(), 0, x, y, 0, 0, SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER )
    ret

TConsole::Moveconsole endp


    assume rbx:ptr INPUT_RECORD

TConsole::Readevent proc uses rsi rdi rbx

  local Count:dword, Event:INPUT_RECORD

    xor edi,edi
    lea rbx,Event

    .if GetNumberOfConsoleInputEvents(hStdInput, &Count)

        mov esi,Count
        .while esi

            ReadConsoleInput(hStdInput, rbx, 1, &Count)
            .break .if !Count

            mov rcx,_this
            movzx eax,[rbx].EventType
            .if eax == KEY_EVENT

                xor r8d,r8d
                movzx eax,[rbx].KeyEvent.wVirtualKeyCode
                mov [rcx].keybcode,al
                mov al,byte ptr [rbx].KeyEvent.wVirtualScanCode
                mov [rcx].keybscan,al
                movzx r9d,al
                mov al,byte ptr [rbx].KeyEvent.AsciiChar
                mov [rcx].keybchar,al
                mov edx,[rcx].keyshift
                mov eax,[rbx].KeyEvent.dwControlKeyState
                and edx,not (SHIFT_SCROLL or SHIFT_NUMLOCK or SHIFT_CAPSLOCK \
                        or SHIFT_ENHANCED or SHIFT_KEYSPRESSED)

                .if eax & SHIFT_PRESSED
                    or edx,SHIFT_KEYSPRESSED
                .else
                    and edx,not (SHIFT_LEFT or SHIFT_RIGHT)
                .endif
                .if eax & SCROLLLOCK_ON
                    or edx,SHIFT_SCROLL
                .endif
                .if eax & NUMLOCK_ON
                    or edx,SHIFT_NUMLOCK
                .endif
                .if eax & CAPSLOCK_ON
                    or edx,SHIFT_CAPSLOCK
                .endif
                .if eax & ENHANCED_KEY
                    or edx,SHIFT_ENHANCED
                .endif
                xchg edx,eax

                .if [rbx].KeyEvent.bKeyDown

                    mov [rcx].keybstate,1
                    or  eax,SHIFT_RELEASEKEY

                    .switch r9d
                      .case 2Ah
                        .if eax & SHIFT_KEYSPRESSED
                            or eax,SHIFT_LEFT
                        .endif
                        .endc
                      .case 36h
                        .if eax & SHIFT_KEYSPRESSED
                            or eax,SHIFT_RIGHT
                        .endif
                        .endc
                      .case 38h
                        .if edx & RIGHT_ALT_PRESSED
                            or eax,SHIFT_ALT
                        .else
                            or eax,SHIFT_ALTLEFT or SHIFT_ALT
                        .endif
                        .endc
                      .case 1Dh
                        .if edx & RIGHT_CTRL_PRESSED
                            or eax,SHIFT_CTRL
                        .else
                            or eax,SHIFT_CTRLLEFT or SHIFT_CTRL
                        .endif
                        .endc
                      .case 46h
                        or eax,SHIFT_SCROLLKEY
                        .endc
                      .case 3Ah
                        or eax,SHIFT_CAPSLOCKKEY
                        .endc
                      .case 45h
                        or eax,SHIFT_NUMLOCKKEY
                        .endc
                      .case 57h
                        mov r8d,8500h   ; F11
                        .endc
                      .case 58h
                        mov r8d,8600h   ; F12
                        .endc
                      .default
                        .if r9b == 52h && [rcx].keybcode == 2Dh
                            or  eax,SHIFT_INSERTKEY
                            xor eax,SHIFT_INSERTSTATE
                            mov r8d,5200h
                        .else
                            mov dl,r9b
                            mov dh,dl
                            mov dl,[rcx].keybchar
                            and edx,0xFFFF
                            mov r8d,edx
                        .endif
                    .endsw
                .else
                    mov [rcx].keybstate,0
                    and eax,not SHIFT_RELEASEKEY
                    .switch r9d
                      .case 2Ah
                        .if eax & SHIFT_KEYSPRESSED
                            and eax,not SHIFT_LEFT
                        .endif
                        .endc
                      .case 36h
                        .if eax & SHIFT_KEYSPRESSED
                            and eax,not SHIFT_RIGHT
                        .endif
                        .endc
                      .case 38h
                        and eax,not (SHIFT_ALT or SHIFT_ALTLEFT)
                        .endc
                      .case 1Dh
                        and eax,not (SHIFT_CTRL or SHIFT_CTRLLEFT)
                        .endc
                      .case 46h
                        and eax,not SHIFT_SCROLLKEY
                        .endc
                      .case 3Ah
                        and eax,not SHIFT_CAPSLOCKKEY
                        .endc
                      .case 45h
                        and eax,not SHIFT_NUMLOCKKEY
                        .endc
                      .case 52h
                        and eax,not SHIFT_INSERTKEY
                    .endsw
                .endif

                mov [rcx].keyshift,eax

                .if r8d
                    mov edi,r8d
                .endif

            .elseif eax == MOUSE_EVENT

                movzx eax,[rbx].MouseEvent.dwMousePosition.x
                mov [rcx].keybmouse_x,eax
                mov ax,[rbx].MouseEvent.dwMousePosition.y
                mov [rcx].keybmouse_y,eax
                mov r8d,[rcx].keyshift
                and r8d,not SHIFT_MOUSEFLAGS
                mov eax,[rbx].MouseEvent.dwButtonState
                mov r9d,eax
                and eax,3h
                shl eax,16
                or  eax,r8d
                mov [rcx].keyshift,eax

                .if [rbx].MouseEvent.dwEventFlags == MOUSE_WHEELED

                    mov eax,KEY_MOUSEUP
                    .ifs r9d <= 0

                        mov eax,KEY_MOUSEDN
                    .endif
                    [rcx].Pushevent(eax)
                .endif
            .endif
            dec esi
        .endw
    .endif

    mov rcx,_this
    mov edx,[rcx].keyshift
    mov eax,edi
    .if edx & SHIFT_ALTLEFT
        mov al,0
    .endif

    .if ah && !al

        xor edi,edi
        .if edx & SHIFT_RIGHT or SHIFT_LEFT
            lea rdi,@CStr("\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B"
                          "\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D"
                          "\x47\x48\x49\x4B\x4D\x4F\x50\x51\x52\x53"
                          "\x0F\x9E\x9F")
        .elseif edx & SHIFT_CTRL or SHIFT_CTRLLEFT
            lea rdi,@CStr("\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B"
                          "\x5E\x5F\x60\x61\x62\x63\x64\x65\x66\x67"
                          "\x77\x8D\x84\x73\x74\x75\x91\x76\x92\x93"
                          "\x94\xA8\xA9")
        .elseif edx & SHIFT_ALT or SHIFT_ALTLEFT
            lea rdi,@CStr("\x78\x79\x7A\x7B\x7C\x7D\x7E\x7F\x80\x81"
                          "\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F\x70\x71"
                          "\x47\x98\x49\x9B\x9D\x4F\xA0\x51\x52\x53"
                          "\x0F\xB2\xB3")
        .endif

        .if rdi
            lea rsi,@CStr("\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B"
                          "\x3B\x3C\x3D\x3E\x3F\x40\x41\x42\x43\x44"
                          "\x47\x48\x49\x4B\x4D\x4F\x50\x51\x52\x53"
                          "\x0F\x85\x86")
            mov r8,rsi
            .while 1

                lodsb
                .break .if !al

                .if ah == al
                    sub rsi,r8
                    mov ah,[rsi+rdi-1]
                    mov al,0
                    .break
                .endif
            .endw
        .endif
    .elseif ah
        .if edx & SHIFT_ALT or SHIFT_ALTLEFT
            mov ah,0
        .endif
    .endif
    .if eax
        [rcx].Pushevent(eax)
    .endif
    ret

TConsole::Readevent endp

    assume rbx:nothing

TConsole::Setkeystate proc uses rsi rdi

    mov rdi,rcx
    mov esi,[rcx].keyshift
    and esi,not 0x01FF030F
    .ifd ( GetKeyState(VK_LSHIFT) ) & 0x80
        or esi,SHIFT_LEFT or SHIFT_KEYSPRESSED
    .endif
    .if ( GetKeyState(VK_RSHIFT) & 0x80 )
        or esi,SHIFT_RIGHT or SHIFT_KEYSPRESSED
    .endif
    .ifd ( GetKeyState(VK_LCONTROL) & 0x80 )
        or esi,SHIFT_CTRLLEFT
    .endif
    .ifd ( GetKeyState(VK_RCONTROL) & 0x80 )
        or esi,SHIFT_CTRL
    .endif
    mov [rdi].TConsole.keyshift,esi
    mov rcx,rdi
    ret

TConsole::Setkeystate endp

TConsole::Getevent proc

    [rcx].Readevent()
    [rcx].Popevent()
    ret

TConsole::Getevent endp

TConsole::Getch proc

    .whiled ![rcx].Getevent()
    .endw
    ret

TConsole::Getch endp

TConsole::Mousepress proc

    [rcx].Readevent()

    mov eax,edx
    shr eax,16
    and eax,3
    ret

TConsole::Mousepress endp

    option win64:rsp nosave noauto

TConsole::Getmousex proc

    mov eax,[rcx].keybmouse_x
    ret

TConsole::Getmousex endp

TConsole::Getmousey proc

    mov eax,[rcx].keybmouse_y
    ret

TConsole::Getmousey endp

TConsole::Pushevent proc event:UINT

    mov eax,[rcx].keybcount
    .if eax < MAXKEYSTACK-1

        inc [rcx].keybcount
        mov [rcx].keybstack[rax*4],edx
    .endif
    ret

TConsole::Pushevent endp

TConsole::Popevent proc

    mov edx,[rcx].keyshift
    xor eax,eax
    .if eax != [rcx].keybcount

        dec [rcx].keybcount
        mov eax,[rcx].keybcount
        mov eax,[rcx].keybstack[rax*4]
    .endif
    ret

TConsole::Popevent endp

TConsole::Shiftstate proc

    mov eax,[rcx].keyshift
    and eax,SHIFT_KEYSPRESSED or SHIFT_LEFT or SHIFT_RIGHT
    ret

TConsole::Shiftstate endp

    option win64:rbp nosave auto

TConsole::ClipFree proc uses rcx
    xor eax,eax
    mov rdx,[rcx].clipboard
    mov [rcx].clipboard,rax
    mov [rcx].clipbsize,eax
    free(rdx)
    ret
TConsole::ClipFree endp

    option win64:save

TConsole::ClipCopy proc uses rsi rdi rbx string:LPSTR, l:UINT

    mov edi,r8d
    mov rbx,rdx

    [rcx].ClipFree()
    .ifd OpenClipboard(0)

        EmptyClipboard()
        inc edi

        .if GlobalAlloc( GMEM_MOVEABLE or GMEM_DDESHARE, edi )

            dec edi
            mov rsi,rax
            mov rbx,memcpy( GlobalLock(rax), rbx, edi )
            mov byte ptr [rbx+rdi],0
            GlobalUnlock( rsi )
            SetClipboardData( CF_TEXT, rbx )
            mov rax,rdi
        .endif
        mov rdi,rax
        CloseClipboard()
        mov rax,rdi
    .endif
    mov rcx,_this
    ret

TConsole::ClipCopy endp

TConsole::ClipPaste proc uses rsi rbx

    assume rbx:ptr TConsole

    mov rbx,rcx

    .ifd IsClipboardFormatAvailable(CF_TEXT)

        .if OpenClipboard(0)

            xor esi,esi
            .if GetClipboardData(CF_TEXT)

                mov rsi,rax
                .if strlen(rax)

                    mov [rbx].clipbsize,eax
                    inc eax
                    .if malloc(rax)

                        strcpy(rax, rsi)
                        mov [rbx].clipboard,rax
                    .endif
                .endif
                mov rsi,rax
            .endif
            CloseClipboard()
            mov rax,rsi
        .endif
    .endif
    mov rcx,rbx
    ret

TConsole::ClipPaste endp

    assume rbx:nothing

TConsole::CursorOn proc uses rcx

  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,1
    SetConsoleCursorInfo(hStdOutput, &cu)
    ret

TConsole::CursorOn endp

TConsole::CursorOff proc uses rcx

  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,0
    SetConsoleCursorInfo(hStdOutput, &cu)
    ret

TConsole::CursorOff endp

TConsole::CursorGet proc uses rbx rcx cursor:PCURSOR

  local ci:CONSOLE_SCREEN_BUFFER_INFO

    mov rbx,rdx

    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

        mov eax,ci.dwCursorPosition
        mov dword ptr [rbx].CURSOR.x,eax
    .endif

    GetConsoleCursorInfo(hStdOutput, rbx)
    mov eax,[rbx].CURSOR.bVisible
    ret

TConsole::CursorGet endp

TConsole::CursorSet proc uses rax rcx cursor:PCURSOR

    mov eax,dword ptr [rdx].CURSOR.x
    SetConsoleCursorPosition(hStdOutput, eax)
    SetConsoleCursorInfo(hStdOutput, cursor)
    ret

TConsole::CursorSet endp

Install proc private
    TConsole::TConsole( &Console )
    ret
Install endp

.pragma(init(Install, 50))

    end

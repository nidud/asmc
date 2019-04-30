; TCONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include stdio.inc
include conio.inc
include tconsole.inc

    .code

    assume rcx: ptr tconsole

tconsole::Release proc

    [rcx].clipfree()
    free( [rcx].window )
    free( _this )
    ret

tconsole::Release endp

tconsole::read proc uses rsi rdi rbx buffer:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    xor eax,eax
    mov al,[rcx].rc.col
    mov co.x,ax
    dec al
    add al,[rcx].rc.x
    mov rc.Right,ax
    mov al,[rcx].rc.row
    mov co.y,ax
    dec al
    mov rc.Bottom,ax
    mov al,[rcx].rc.x
    mov rc.Left,ax
    mov al,[rcx].rc.y
    mov rc.Top,ax
    mov rsi,rdx

    .ifd !ReadConsoleOutput(hStdOutput, rsi, co, 0, &rc)

        movzx ebx,co.y
        movzx edi,co.x

        .for ( edi <<= 2, ax = rc.Top, rc.Bottom = ax, co.y = 1,
               : ebx && ReadConsoleOutput(hStdOutput, rsi, co, 0, &rc),
               : ebx--, rc.Bottom++, rc.Top++, rsi += rdi )
        .endf

        xor eax,eax
        cmp ebx,1
        adc eax,0

    .endif

    mov rcx,_this
    ret

tconsole::read endp

tconsole::write proc uses rsi rdi rbx buffer:PCHAR_INFO

  local co:COORD, rc:SMALL_RECT

    xor eax,eax
    mov al,[rcx].rc.col
    mov co.x,ax
    dec al
    add al,[rcx].rc.x
    mov rc.Right,ax
    mov al,[rcx].rc.row
    mov co.y,ax
    dec al
    mov rc.Bottom,ax
    mov al,[rcx].rc.x
    mov rc.Left,ax
    mov al,[rcx].rc.y
    mov rc.Top,ax
    mov rsi,rdx

    .ifd !WriteConsoleOutput(hStdOutput, rdx, co, 0, &rc)

        movzx edi,co.x
        movzx ebx,co.y
        shl edi,2
        mov ax,rc.Top
        mov rc.Bottom,ax
        mov co.y,1

        .for ( : ebx,
                 WriteConsoleOutput(hStdOutput, rsi, co, 0, &rc),
               : ebx--,
                 rc.Bottom++,
                 rc.Top++,
                 rsi += rdi )
        .endf

    .endif

    xor eax,eax
    cmp ebx,1
    adc eax,0
    mov rcx,_this
    ret

tconsole::write endp

tconsole::show proc

    .if ( [rcx].flags & _TW_ISOPEN )

        or [rcx].flags,_TW_VISIBLE

        [rcx].write( [rcx].window )

    .endif
    ret

tconsole::show endp

tconsole::hide proc

    .if ( [rcx].flags & _TW_ISOPEN )

        and [rcx].flags,not _TW_VISIBLE

        [rcx].write( [rcx].backgr )

    .endif
    ret

tconsole::hide endp

    option win64:rsp nosave noauto

tconsole::inside_x proc x:int_t

    xor eax,eax
    .if dl < [rcx].rc.col

        lea rax,[rdx+1]
    .endif
    ret

tconsole::inside_x endp

tconsole::inside_y proc y:int_t

    xor eax,eax
    .if dl < [rcx].rc.row

        lea rax,[rdx+1]
    .endif
    ret

tconsole::inside_y endp

    option win64:rbp nosave auto

tconsole::insidexy proc x:int_t, y:int_t

    .ifd [rcx].inside_x(edx)

        [rcx].inside_y(r8d)

    .endif
    ret

tconsole::insidexy endp

tconsole::getat proc f_id:uint_t, b_id:uint_t

    movzx eax,[rcx].foreground[rdx]
    or    al,[rcx].background[r8]
    ret

tconsole::getat endp

    option win64:rsp nosave noauto

tconsole::getrcp proc rc:TRECT

    movzx eax,dh ; rc.y
    movzx edx,dl ; rc.x

    mov r8d,eax

tconsole::getrcp endp

    option win64:auto

tconsole::getxyp proc uses r9 x:int_t, y:int_t

    .ifd [rcx].inside_x(edx)

        lea r9,[rax-1]

        .ifd [rcx].inside_y(r8d)

            dec eax

            movzx edx,[rcx].rc.col
            mul edx
            add eax,r9d
            shl eax,2
            add rax,[rcx].window

        .endif
    .endif
    ret

tconsole::getxyp endp

tconsole::getxyw proc x:int_t, y:int_t

    .if [rcx].getxyp(edx, r8d)

        mov eax,[rax]
    .endif
    ret

tconsole::getxyw endp

tconsole::getxyc proc x:int_t, y:int_t

    .if [rcx].getxyp(edx, r8d)

        movzx eax,word ptr [rax]
    .endif
    ret

tconsole::getxyc endp

tconsole::getxya proc x:int_t, y:int_t

    .if [rcx].getxyp(edx, r8d)

        movzx eax,byte ptr [rax+2]
    .endif
    ret

tconsole::getxya endp

tconsole::putxyw proc x:int_t, y:int_t, l:int_t, w:uint_t

    .if [rcx].getxyp(edx, r8d)

        .for ( edx = w : r9d : r9d--, rax += 4 )

            mov [rax],edx
        .endf
    .endif
    ret

tconsole::putxyw endp

tconsole::putxyc proc x:int_t, y:int_t, l:int_t, w:wchar_t

    .if [rcx].getxyp(edx, r8d)

        .for ( dx = w : r9d : r9d--, rax += 4 )

            mov [rax],dx
        .endf
    .endif
    ret

tconsole::putxyc endp

tconsole::putxya proc x:int_t, y:int_t, l:int_t, a:uchar_t

    .if [rcx].getxyp(edx, r8d)

        .for ( dl = a : r9d : r9d--, rax += 4 )

            mov [rax+2],dl
        .endf
    .endif
    ret

tconsole::putxya endp

    option win64:noauto

tconsole::SetConsoleAttrib proc attrib:uchar_t

    mov al,dl
    and al,0x0F
    mov [rcx].foreground[F_Desktop],al
    and dl,0xF0
    mov [rcx].background[B_Desktop],dl
    ret

tconsole::SetConsoleAttrib endp

tconsole::ClearConsole proc uses rdi rcx

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

tconsole::ClearConsole endp

    option win64:rbp save auto

tconsole::putxyf proc uses rsi rdi rbx x:int_t, y:int_t, format:string_t, argptr:VARARG

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

    .for ( rsi = &_bufin,
           ebx = eax,
           edi = x,
           rcx = _this : ebx : ebx--, edi++ )

        lodsb

        .if ( al == 10 )

            mov edi,x
            dec edi
            inc y

        .else

            movzx eax,al
            [rcx].putxyc(edi, y, 1, ax)

        .endif

    .endf
    ret

tconsole::putxyf endp

    assume rsi:ptr tconsole

tconsole::SetConsoleSize proc uses rsi rdi rcx cols:uint_t, rows:uint_t

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
                [rsi].read(rax)

                mov rax,rsi
                mov rdi,[rsi].window
                mov rsi,[rsi].backgr
                mov rcx,rsi
                sub rcx,rdi
                rep movsb
                mov rcx,rax

            .endif
        .endif
    .endif
    ret

tconsole::SetConsoleSize endp

    assume rsi:nothing

tconsole::SetMaxConsoleSize proc

    [rcx].MoveConsole(0, 0)

    GetLargestConsoleWindowSize(hStdOutput)

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

    _this.SetConsoleSize(edx, eax)
    ret

tconsole::SetMaxConsoleSize endp

tconsole::MoveConsole proc uses rcx x:uint_t, y:uint_t

    SetWindowPos( GetConsoleWindow(), 0, x, y, 0, 0, SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER )
    ret

tconsole::MoveConsole endp


    assume rbx:ptr INPUT_RECORD

tconsole::readevent proc uses rsi rdi rbx

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

                xor     r8d,r8d
                movzx   eax,[rbx].KeyEvent.wVirtualKeyCode
                mov     [rcx].keybcode,al
                mov     al,byte ptr [rbx].KeyEvent.wVirtualScanCode
                mov     [rcx].keybscan,al
                movzx   r9d,al
                mov     al,byte ptr [rbx].KeyEvent.AsciiChar
                mov     [rcx].keybchar,al
                mov     edx,[rcx].keyshift
                mov     eax,[rbx].KeyEvent.dwControlKeyState
                and     edx,not ( SHIFT_SCROLL or SHIFT_NUMLOCK or SHIFT_CAPSLOCK \
                            or SHIFT_ENHANCED or SHIFT_KEYSPRESSED )

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


                    option switch:pascal
                    .switch r9d
                      .case 0x2A
                        .if eax & SHIFT_KEYSPRESSED
                            or eax,SHIFT_LEFT
                        .endif
                      .case 0x36
                        .if eax & SHIFT_KEYSPRESSED
                            or eax,SHIFT_RIGHT
                        .endif
                      .case 0x38
                        .if edx & RIGHT_ALT_PRESSED
                            or eax,SHIFT_ALT
                        .else
                            or eax,SHIFT_ALTLEFT or SHIFT_ALT
                        .endif
                      .case 0x1D
                        .if edx & RIGHT_CTRL_PRESSED
                            or eax,SHIFT_CTRL
                        .else
                            or eax,SHIFT_CTRLLEFT or SHIFT_CTRL
                        .endif
                      .case 0x46: or eax,SHIFT_SCROLLKEY
                      .case 0x3A: or eax,SHIFT_CAPSLOCKKEY
                      .case 0x45: or eax,SHIFT_NUMLOCKKEY
                      .case 0x57: mov r8d,0x8500 ; F11
                      .case 0x58: mov r8d,0x8600 ; F12

                      .default

                        .if ( r9b == 0x52 && [rcx].keybcode == 0x2D )

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
                      .case 0x2A
                        .if eax & SHIFT_KEYSPRESSED
                            and eax,not SHIFT_LEFT
                        .endif
                      .case 0x36
                        .if eax & SHIFT_KEYSPRESSED
                            and eax,not SHIFT_RIGHT
                        .endif
                      .case 0x38: and eax,not (SHIFT_ALT or SHIFT_ALTLEFT)
                      .case 0x1D: and eax,not (SHIFT_CTRL or SHIFT_CTRLLEFT)
                      .case 0x46: and eax,not SHIFT_SCROLLKEY
                      .case 0x3A: and eax,not SHIFT_CAPSLOCKKEY
                      .case 0x45: and eax,not SHIFT_NUMLOCKKEY
                      .case 0x52: and eax,not SHIFT_INSERTKEY
                    .endsw

                .endif

                mov [rcx].keyshift,eax

                .if r8d
                    mov edi,r8d
                .endif

            .elseif eax == MOUSE_EVENT

                movzx   eax,[rbx].MouseEvent.dwMousePosition.x
                mov     [rcx].keybmouse_x,eax
                mov     ax,[rbx].MouseEvent.dwMousePosition.y
                mov     [rcx].keybmouse_y,eax
                mov     r8d,[rcx].keyshift
                and     r8d,not SHIFT_MOUSEFLAGS
                mov     eax,[rbx].MouseEvent.dwButtonState
                mov     r9d,eax
                and     eax,0x03
                shl     eax,16
                or      eax,r8d
                mov     [rcx].keyshift,eax

                .if [rbx].MouseEvent.dwEventFlags == MOUSE_WHEELED

                    mov eax,KEY_MOUSEUP
                    .ifs r9d <= 0

                        mov eax,KEY_MOUSEDN
                    .endif
                    [rcx].pushevent(eax)

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

        [rcx].pushevent(eax)
    .endif
    ret

tconsole::readevent endp

    assume rbx:nothing

tconsole::setkeystate proc uses rsi rdi

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

    mov [rdi].tconsole.keyshift,esi
    mov rcx,rdi
    ret

tconsole::setkeystate endp

tconsole::getevent proc

    [rcx].readevent()
    [rcx].popevent()
    ret

tconsole::getevent endp

tconsole::getch proc

    .whiled ![rcx].getevent()
    .endw
    ret

tconsole::getch endp

tconsole::mousepress proc

    [rcx].readevent()

    mov eax,edx
    shr eax,16
    and eax,3
    ret

tconsole::mousepress endp

    option win64:rsp nosave noauto

tconsole::getmousex proc

    mov eax,[rcx].keybmouse_x
    ret

tconsole::getmousex endp

tconsole::getmousey proc

    mov eax,[rcx].keybmouse_y
    ret

tconsole::getmousey endp

tconsole::pushevent proc event:uint_t

    mov eax,[rcx].keybcount
    .if eax < MAXKEYSTACK-1

        inc [rcx].keybcount
        mov [rcx].keybstack[rax*4],edx
    .endif
    ret

tconsole::pushevent endp

tconsole::popevent proc

    mov edx,[rcx].keyshift
    xor eax,eax
    .if eax != [rcx].keybcount

        dec [rcx].keybcount
        mov eax,[rcx].keybcount
        mov eax,[rcx].keybstack[rax*4]
    .endif
    ret

tconsole::popevent endp

tconsole::shiftstate proc

    mov eax,[rcx].keyshift
    and eax,SHIFT_KEYSPRESSED or SHIFT_LEFT or SHIFT_RIGHT
    ret

tconsole::shiftstate endp

    option win64:rbp nosave auto

tconsole::clipfree proc uses rcx

    xor eax,eax
    mov rdx,[rcx].clipboard
    mov [rcx].clipboard,rax
    mov [rcx].clipbsize,eax

    free(rdx)
    ret

tconsole::clipfree endp

    option win64:save

tconsole::clipcopy proc uses rsi rdi rbx string:string_t, l:uint_t

    mov edi,r8d
    mov rbx,rdx

    [rcx].clipfree()

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

tconsole::clipcopy endp

tconsole::clippaste proc uses rsi rbx

    assume rbx:ptr tconsole

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

tconsole::clippaste endp

    assume rbx:nothing

tconsole::cursoron proc uses rcx

  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,1
    SetConsoleCursorInfo(hStdOutput, &cu)
    ret

tconsole::cursoron endp

tconsole::cursoroff proc uses rcx

  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,0
    SetConsoleCursorInfo(hStdOutput, &cu)
    ret

tconsole::cursoroff endp

tconsole::cursorget proc uses rbx rcx cursor:PCURSOR

  local ci:CONSOLE_SCREEN_BUFFER_INFO

    mov rbx,rdx

    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

        mov eax,ci.dwCursorPosition
        mov dword ptr [rbx].CURSOR.x,eax
    .endif

    GetConsoleCursorInfo(hStdOutput, rbx)
    mov eax,[rbx].CURSOR.bVisible
    ret

tconsole::cursorget endp

tconsole::cursorset proc uses rax rcx cursor:PCURSOR

    mov eax,dword ptr [rdx].CURSOR.x
    SetConsoleCursorPosition(hStdOutput, eax)
    SetConsoleCursorInfo(hStdOutput, cursor)
    ret

tconsole::cursorset endp

    assume rsi:ptr tconsole

tconsole::tconsole proc uses rsi rdi

  local ci: CONSOLE_SCREEN_BUFFER_INFO

    .if malloc( sizeof(tconsole) + sizeof(tconsoleVtbl) )

        mov rsi,rax
        mov rdi,rax
        xor eax,eax
        mov ecx,sizeof(tconsole)
        rep stosb

        lea rdi,[rsi].foreground
        mov rax,0x07000008070F0F00
        stosq
        mov rax,0x0F0F0F000B0A0008
        stosq
        mov rax,0x7030304070701000
        stosq
        mov rax,0x0707000000303030
        stosq

        lea rdi,[rsi+sizeof(tconsole)]
        mov [rsi],rdi
        _method macro entry
            lea rax,tconsole_&entry
            exitm<stosq>
            endm
            _method(Release)
            _method(show)
            _method(hide)
            _method(read)
            _method(write)
            _method(getat)
            _method(getrcp)
            _method(getxyp)
            _method(getxyw)
            _method(getxyc)
            _method(getxya)
            _method(putxyw)
            _method(putxyc)
            _method(putxya)
            _method(putxyf)
            _method(inside_x)
            _method(inside_y)
            _method(insidexy)
            _method(readevent)
            _method(getevent)
            _method(getch)
            _method(shiftstate)
            _method(mousepress)
            _method(getmousex)
            _method(getmousey)
            _method(pushevent)
            _method(popevent)
            _method(setkeystate)
            _method(clipfree)
            _method(clipcopy)
            _method(clippaste)
            _method(cursoron)
            _method(cursoroff)
            _method(cursorget)
            _method(cursorset)
            _method(ClearConsole)
            _method(SetConsoleAttrib)
            _method(SetMaxConsoleSize)
            _method(SetConsoleSize)
            _method(MoveConsole)

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
            [rsi].read(rax)
            mov rax,rsi
            mov rdi,[rsi].window
            mov rsi,[rsi].backgr
            mov rcx,rsi
            sub rcx,rdi
            rep movsb
            mov rcx,rax
        .endif
    .endif

    mov r8,_this
    .if r8
        mov [r8],rax
    .endif
    ret

tconsole::tconsole endp

    assume rsi:nothing

    end

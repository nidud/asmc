; TWINDOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include stdio.inc
include strlib.inc
include twindow.inc

TWindow::Resource       proto :idd_t
TWindow::Show           proto
TWindow::Hide           proto
TWindow::Move           proto :int_t, :int_t
TWindow::Read           proto
TWindow::Write          proto
TWindow::SetShade       proto
TWindow::ClrShade       proto

TWindow::Clear          proto :CHAR_INFO
TWindow::PutChar        proto :int_t, :int_t, :int_t, :CHAR_INFO
TWindow::PutString      proto :int_t, :int_t, :ushort_t, :int_t, :string_t, :vararg
TWindow::PutPath        proto :int_t, :int_t, :int_t, :string_t
TWindow::PutCenter      proto :int_t, :int_t, :int_t, :string_t
TWindow::PutTitle       proto :string_t
TWindow::MessageBox     proto :int_t, :string_t, :string_t, :vararg

TWindow::CursorGet      proto
TWindow::CursorSet      proto
TWindow::CursorOn       proto
TWindow::CursorOff      proto
TWindow::CursorMove     proto :int_t, :int_t

TWindow::Register       proto :tproc_t
TWindow::Send           proto :uint_t, :size_t, :ptr
TWindow::Post           proto :uint_t, :size_t, :ptr
TWindow::PostQuit       proto :int_t
TWindow::Dispatch       proto :msg_t
TWindow::Translate      proto :msg_t

TWindow::Child          proto :TRECT, :uint_t, :uint_t
TWindow::Window         proto
TWindow::Focus          proto
TWindow::SetFocus       proto :uint_t
TWindow::KillFocus      proto
TWindow::NextItem       proto
TWindow::PrevItem       proto

TWindow::PushButton     proto :uint_t, :size_t, :ptr
TWindow::PushBCreate    proto :TRECT, :uint_t, :string_t
TWindow::PushBSet       proto
TWindow::PushBClear     proto
TWindow::PushBSetShade  proto
TWindow::PushBClrShade  proto

TWindow::Inside         proto :COORD

TWindow::OnLButtonDown  proto :uint_t, :size_t, :ptr
TWindow::OnMouseMove    proto :uint_t, :size_t, :ptr
TWindow::OnLButtonUp    proto :uint_t, :size_t, :ptr
TWindow::OnSetFocus     proto
TWindow::OnKillFocus    proto
TWindow::OnChar         proto :uint_t, :size_t, :ptr
TWindow::OnSysChar      proto :uint_t, :size_t, :ptr

TWindow::MoveConsole    proto :int_t, :int_t
TWindow::SetConsole     proto :int_t, :int_t
TWindow::SetMaxConsole  proto
TWindow::ConsoleSize    proto

    .code

    assume rcx:window_t

TWindow::Show proc

    mov eax,[rcx].Flags
    and eax,W_ISOPEN or W_VISIBLE
    .return .ifz

    .if !( eax & W_VISIBLE )

        _scxchg([rcx].rc, [rcx].Window)
        mov rcx,this

        .if [rcx].Flags & W_SHADE

            [rcx].SetShade()
        .endif
        or [rcx].Flags,W_VISIBLE
    .endif
    mov eax,1
    ret
TWindow::Show endp

TWindow::Hide proc

    xor eax,eax
    mov edx,[rcx].Flags
    .return .if !( edx & W_ISOPEN )

    .if edx & W_VISIBLE

        _scxchg([rcx].rc, [rcx].Window)
        mov rcx,this

        .if [rcx].Flags & W_SHADE

            [rcx].ClrShade()
        .endif
        and [rcx].Flags,not W_VISIBLE
    .endif
    mov eax,1
    ret
TWindow::Hide endp

    assume rbx:window_t

TWindow::Move proc uses rsi rdi rbx r12 rcx x:int_t, y:int_t

  local lx, ly, l, col, row, sccol, scrow
  local wp:ptr, lp:ptr, size, count, Direction

    mov rbx,rcx
    [rcx].ConsoleSize()
    movzx edx,ax
    mov sccol,edx
    shr eax,16
    mov scrow,eax
    mov al,[rbx].rc.col
    mov col,eax
    mov al,[rbx].rc.row
    mov row,eax
    add eax,y
    mov edx,scrow
    .if eax > edx
        sub edx,row
        mov y,edx
    .endif
    .if y == 0
        inc y
    .endif
    mov eax,col
    add eax,x
    mov edx,sccol
    .if eax > edx
        sub edx,col
        mov x,edx
    .endif

    movzx ecx,[rbx].rc.x
    movzx edx,[rbx].rc.y
    xor eax,eax
    .if ecx > x
        sub ecx,x
        mov eax,ecx
    .else
        mov eax,x
        sub eax,ecx
    .endif
    .if edx > y
        sub edx,y
        add eax,edx
    .else
        mov ecx,y
        sub ecx,edx
        add eax,ecx
    .endif
    .return .if !eax
    mov count,eax

    mov eax,col
    mul row
    shl eax,2
    mov wp,malloc(eax)
    .return .if !rax

    .for ( Direction = 0 : count : count-- )

        movzx esi,[rbx].rc.x
        movzx edi,[rbx].rc.y
        .break .if ( esi == x && edi == y )
        _scread([rbx].rc, wp)

        .switch
          .case <Right> esi < x
            mov eax,Direction
            mov Direction,1
            .if ( eax == 1 )
                .if ( edi > y )
                    jmp Up
                .elseif ( edi < y )
                    jmp Down
                .endif
            .endif
            mov lx,esi
            mov ly,edi
            mov ecx,esi
            add ecx,col
            mov r8d,row
            not r8d
            mov r9,_screadl(ecx, edi, r8d)
            inc [rbx].rc.x
            .for ( edx = row,
                   rsi = [rbx].Window,
                   rdi = rax : edx : edx--, rdi += 4 )
                mov eax,[rsi]
                mov r8d,[rdi]
                mov [rdi],eax
                mov ecx,col
                dec ecx
                mov r10,rdi
                mov rdi,rsi
                add rsi,4
                rep movsd
                mov rdi,r10
                mov [rsi-4],r8d
            .endf
            mov r8d,row
            not r8d
            _scwritel(lx, ly, r8d, r9)
            .endc

          .case <Left> esi > x
            mov eax,Direction
            mov Direction,2
            .if ( eax == 2 )
                .if ( edi > y )
                    jmp Up
                .elseif ( edi < y )
                    jmp Down
                .endif
            .endif
            mov lx,esi
            mov ly,edi
            lea rdi,[rsi-1]
            mov esi,row
            mov eax,esi
            not eax
            mov l,eax
            mov r12,_screadl(edi, ly, eax)
            dec [rbx].rc.x
            mov r8d,col
            lea rax,[r8-1]
            shl r8d,3
            mov edx,esi
            shl eax,2
            mov rsi,[rbx].Window
            add rsi,rax
            mov rdi,r12
            std
            .repeat
                mov eax,[rsi]
                mov r9d,[rdi]
                mov [rdi],eax
                mov ecx,col
                dec ecx
                mov r10,rdi
                mov rdi,rsi
                sub rsi,4
                rep movsd
                mov rdi,r10
                mov [rsi+4],r9d
                add rsi,r8
                add rdi,4
                dec edx
            .until !edx
            cld
            mov ecx,col
            add ecx,lx
            dec ecx
            _scwritel(ecx, ly, l, r12)
            .endc

          .case <Up> edi > y
            mov Direction,3
            mov lx,esi
            mov esi,row
            dec edi
            add esi,edi
            mov rcx,_screadl(lx, edi, col)
            dec [rbx].rc.y
            mov r12d,col
            shl r12d,2
            mov eax,row
            dec eax
            mul r12d
            mov rdi,[rbx].Window
            add rdi,rax
            _scwritel(lx, esi, col, memxchg(rcx, rdi, r12))
            mov rax,rdi
            sub rax,r12
            mov esi,row
            dec esi
            .while esi
                memxchg(rax, rdi, r12)
                sub rdi,r12
                sub rax,r12
                dec esi
            .endw
            .endc

          .case <Down> edi < y
            mov Direction,3
            mov edx,edi
            add edx,row
            _screadl(esi, edx, col)
            inc [rbx].rc.y
            mov r12d,col
            shl r12d,2
            _scwritel(esi, edi, col, memxchg(rax, [rbx].Window, r12))
            .for ( esi = row, esi--, rdi = [rbx].Window : esi : esi--, rdi += r12 )
                memxchg(rdi, &[rdi+r12], r12)
            .endf
            .endc
        .endsw
        _scwrite([rbx].rc, wp)
    .endf
    free(wp)
    ret

TWindow::Move endp

    assume rbx:nothing

TWindow::Read proc uses rcx

    _scread([rcx].rc, [rcx].Window)
    ret

TWindow::Read endp

TWindow::Write proc uses rcx

    _scwrite([rcx].rc, [rcx].Window)
    ret

TWindow::Write endp

TWindow::SetShade proc uses rdi rcx

  local rc_b:TRECT
  local rc_r:TRECT

    .return .if !( [rcx].Flags & W_SHADE )

    mov     rc_b,[rcx].rc
    mov     rc_r,eax
    shr     eax,16
    mov     rc_r.col,2
    dec     rc_r.row
    inc     rc_r.y
    add     rc_r.x,al
    add     rc_b.y,ah
    mov     rc_b.row,1
    add     rc_b.x,2
    movzx   eax,[rcx].rc.col
    mul     [rcx].rc.row
    lea     rdi,[rax*4]
    add     rdi,[rcx].Window

    _scread(rc_b, rdi)

    movzx eax,rc_b.col
    _scread(rc_r, &[rdi+rax*4])

    movzx ecx,rc_b.col
    add cl,rc_r.row
    add cl,rc_r.row
    .for ( rax = rdi : ecx : ecx--, rax += 4 )
        mov byte ptr [rax+2],0x08
    .endf
    _scxchg(rc_b, rdi)

    movzx eax,rc_b.col
    _scxchg(rc_r, &[rdi+rax*4])
    ret

TWindow::SetShade endp

TWindow::ClrShade proc uses rsi rcx

  local rc_b:TRECT
  local rc_r:TRECT

    .return .if !( [rcx].Flags & W_SHADE )

    mov     rc_b,[rcx].rc
    mov     rc_r,eax
    shr     eax,16
    mov     rc_r.col,2
    dec     rc_r.row
    inc     rc_r.y
    add     rc_r.x,al
    add     rc_b.y,ah
    mov     rc_b.row,1
    add     rc_b.x,2
    movzx   eax,[rcx].rc.col
    mul     [rcx].rc.row
    lea     rsi,[rax*4]
    add     rsi,[rcx].Window

    _scxchg(rc_b, rsi)

    movzx eax,rc_b.col
    _scxchg(rc_r, &[rsi+rax*4])
    ret

TWindow::ClrShade endp

TWindow::Clear proc uses rdi rcx at:CHAR_INFO

    mov eax,edx

    .if [rcx].Flags & W_COLOR

        shr eax,16
        mov rdi,[rcx].Color
        mov r8d,eax
        and eax,0x0F
        shr r8d,4
        mov al,[rdi+rax]
        or  al,[rdi+r8+16]
        shl eax,16
        mov ax,dx
    .endif

    mov   rdi,[rcx].Window
    movzx edx,[rcx].rc.row
    movzx ecx,[rcx].rc.col
    imul  ecx,edx

    .if ( ( eax & 0x00FF0000 ) && ( eax & 0x0000FFFF ) )

        rep stosd
    .else
        .if ( eax & 0x00FF0000 )
            add rdi,2
            shr eax,16
        .endif
        .repeat
            mov [rdi],ax
            add rdi,4
        .untilcxz
    .endif
    ret

TWindow::Clear endp

TWindow::PutChar proc uses rdi x:int_t, y:int_t, count:int_t, w:CHAR_INFO

    movzx edi,[rcx].rc.col
    imul  edi,r8d
    add   edi,edx
    shl   edi,2
    add   rdi,[rcx].Window
    mov   eax,w

    .if ( ( eax & 0x00FF0000 ) && ( [rcx].Flags & W_COLOR ) )

        mov rdx,[rcx].Color
        mov r8d,eax
        and eax,0x0F
        shr r8d,4
        mov al,[rdx+rax]
        or  al,[rdx+r8+16]
        mov w.Attributes,ax
        mov eax,w
    .endif

    xchg rcx,r9
    .if ( ( eax & 0x00FF0000 ) && ( eax & 0x0000FFFF ) )
        rep stosd
    .else
        .if ( eax & 0x00FF0000 )
            add rdi,2
            shr eax,16
        .endif
        .repeat
            mov [rdi],ax
            add rdi,4
        .untilcxz
    .endif
    mov rcx,r9
    ret

TWindow::PutChar endp

TWindow::PutString proc x:int_t, y:int_t, at:ushort_t, max:int_t, format:string_t, argptr:vararg

  local w:ptr_t
  local highat:byte
  local attrib:byte

    mov eax,r9d
    mov attrib,al
    mov highat,ah

    movzx eax,[rcx].rc.col
    imul eax,r8d
    add eax,edx
    lea rax,[rax*4]
    add rax,[rcx].Window
    mov w,rax

    vsprintf(&_bufin, format, &argptr)

    mov rcx,this
    movzx eax,attrib
    .if eax && [rcx].Flags & W_COLOR
        mov rdx,[rcx].Color
        mov r8d,eax
        and eax,0x0F
        shr r8d,4
        mov al,[rdx+rax]
        or  al,[rdx+r8+16]
    .endif
    mov attrib,al

    mov al,highat
    .if eax && [rcx].Flags & W_COLOR
        mov rdx,[rcx].Color
        mov r8d,eax
        and eax,0x0F
        shr r8d,4
        mov al,[rdx+rax]
        or  al,[rdx+r8+16]
    .endif
    mov highat,al

    mov r11d,max
    .if !r11d

        mov r11b,[rcx].rc.col
        sub r11d,x
    .endif

    .for ( rdx = w,
           r8  = &_bufin,
           r9d = 0,
           r9b = [rcx].rc.col,
           r9d <<= 2,
           r10 = rdx,
           ah  = attrib,
           al  = [r8] : al, r11d : r8++, al = [r8], r11d-- )

        .if al == 10

            add r10,r9
            mov rdx,r10
        .elseif al == 9

            add rdx,4*4
        .elseif al == '&' && highat

            inc r8
            mov al,highat
            mov [rdx+2],al
            mov al,[r8]
            mov [rdx],al
            add rdx,4
        .else

            mov [rdx],al
            .if ah

                mov [rdx+2],ah
            .endif
            add rdx,4
        .endif
    .endf
    ret

TWindow::PutString endp

TWindow::PutPath proc uses rsi rdi rbx x:int_t, y:int_t, max:int_t, path:string_t

    movzx   eax,[rcx].rc.col
    imul    eax,r8d
    add     eax,edx
    lea     rdi,[rax*4]
    add     rdi,[rcx].Window
    mov     rsi,path
    mov     rbx,r9

    .ifd strlen(rsi) > ebx

        mov edx,[rsi]
        add rsi,rax
        mov eax,ebx
        sub rsi,rax
        add rsi,4
        .if dh == ':'
            mov [rdi],dl
            mov [rdi+4],dh
            shr edx,8
            mov dl,'.'
            add rdi,8
            add rsi,2
            sub eax,2
        .else
            mov dx,'/.'
        .endif
        mov [rdi],dh
        mov [rdi+4],dl
        mov [rdi+8],dl
        mov [rdi+12],dh
        add rdi,16
        sub eax,4
    .endif
    .while eax
        movsb
        add rdi,3
        dec eax
    .endw
    mov rcx,this
    ret

TWindow::PutPath endp

TWindow::PutCenter proc uses rsi rdi rbx x:int_t, y:int_t, l:int_t, string:string_t

    mov   rsi,string
    mov   rbx,r9
    movzx eax,[rcx].rc.col
    imul  eax,r8d
    add   edx,eax
    lea   rdi,[rdx*4]
    add   rdi,[rcx].Window

    strlen(rsi)
    mov r8,rdi
    .if eax > ebx
        mov edx,[rsi]
        add rsi,rax
        mov eax,ebx
        sub rsi,rax
        add rsi,4
        .if dh == ':'
            mov [rdi],dl
            mov [rdi+4],dh
            shr edx,8
            mov dl,'.'
            add rdi,8
            add rsi,2
            sub eax,2
        .else
            mov dx,'/.'
        .endif
        mov [rdi],dh
        mov [rdi+4],dl
        mov [rdi+8],dl
        mov [rdi+12],dh
        add rdi,16
        sub eax,4
    .endif
    .if eax
        .if rdi == r8
            sub ebx,eax
            shr ebx,2
            lea rdi,[rdi+rbx*8]
        .endif
        .repeat
            movsb
            add rdi,3
            dec eax
        .untilz
    .endif
    mov rcx,this
    ret

TWindow::PutCenter endp

TWindow::PutTitle proc string:string_t

    mov     r8,[rcx].Color
    movzx   eax,byte ptr [r8+FGTITLE]
    or      al, byte ptr [r8+BGTITLE]
    shl     eax,16
    mov     al,' '
    mov     r8,rcx
    mov     r9,[rcx].Window
    xchg    rdi,r9
    movzx   ecx,[rcx].rc.col
    rep     stosd
    mov     rcx,r8
    mov     rdi,r9
    movzx   r9d,[rcx].rc.col
    mov     rax,rdx

    [rcx].PutCenter(0, 0, r9d, rax)
    ret

TWindow::PutTitle endp

    assume rbx:window_t

TWindow::Open proc uses rsi rdi rbx rcx rc:TRECT, flags:uint_t

    mov rbx,rcx
    mov edi,edx
    mov esi,r8d

    .return .if !malloc( sizeof(TWindow) )

    mov r8d,edi
    mov rdx,rax
    mov rdi,rax
    mov ecx,sizeof(TWindow)/8
    xor eax,eax
    rep stosq

    mov rcx,rdx
    mov [rcx].lpVtbl,[rbx].lpVtbl
    mov [rcx].Class,[rbx].Class
    mov [rcx].Color,[rbx].Color
    mov [rcx].rc,r8d
    mov [rcx].Flags,esi
    mov [rcx].PrevInst,rbx

    .return rcx .if ( [rcx].Flags & W_CHILD )

    mov     rbx,rcx
    movzx   eax,[rcx].rc.col
    movzx   edx,[rcx].rc.row
    mov     r8d,eax
    mul     dl
    lea     rax,[rax*4]

    .if [rcx].Flags & W_SHADE
        lea rdx,[r8+rdx*2-2]
        lea rax,[rax+rdx*4]
    .endif
    .if malloc(eax)
        mov rcx,rbx
        mov [rcx].Window,rax
        or  [rcx].Flags,W_ISOPEN
        mov rax,rcx
    .else
        free(rbx)
    .endif
    ret

TWindow::Open endp

TWindow::TWindow proc uses rsi rdi rbx

  local ci: CONSOLE_SCREEN_BUFFER_INFO

    mov rdi,rcx
    mov rbx,malloc( sizeof(TWindow) + sizeof(APPINFO) + sizeof(TWindowVtbl) + 32 )
    .if rdi
        stosq
    .endif
    .return .if !rax

    mov rdi,rax
    mov ecx,(sizeof(TWindow) + sizeof(APPINFO)) / 8
    xor eax,eax
    rep stosq
    mov [rbx].lpVtbl,rdi
    lea rax,[rbx+sizeof(TWindow)]
    mov [rbx].Class,rax

    for q,<TWindow_Open,
           TWindow_Resource,
           TWindow_Release,
           TWindow_Show,
           TWindow_Hide,
           TWindow_Move,
           TWindow_Read,
           TWindow_Write,
           TWindow_SetShade,
           TWindow_ClrShade,
           TWindow_Clear,
           TWindow_PutChar,
           TWindow_PutString,
           TWindow_PutPath,
           TWindow_PutCenter,
           TWindow_PutTitle,
           TWindow_MessageBox,
           TWindow_CursorGet,
           TWindow_CursorSet,
           TWindow_CursorOn,
           TWindow_CursorOff,
           TWindow_CursorMove,
           TWindow_Register,
           TWindow_Send,
           TWindow_Post,
           TWindow_PostQuit,
           TWindow_Dispatch,
           TWindow_Translate,
           TWindow_Child,
           TWindow_Window,
           TWindow_Focus,
           TWindow_SetFocus,
           TWindow_KillFocus,
           TWindow_NextItem,
           TWindow_PrevItem,
           TWindow_PushBCreate,
           TWindow_PushBSet,
           TWindow_PushBClear,
           TWindow_PushBSetShade,
           TWindow_PushBClrShade,
           TWindow_Inside,
           TWindow_OnLButtonDown,
           TWindow_OnMouseMove,
           TWindow_OnLButtonUp,
           TWindow_OnSetFocus,
           TWindow_OnKillFocus,
           TWindow_OnChar,
           TWindow_OnSysChar,
           TWindow_MoveConsole,
           TWindow_SetConsole,
           TWindow_SetMaxConsole,
           TWindow_ConsoleSize>

        lea rax,q
        stosq
        endm

    mov [rbx].Color,rdi
if 0
    for q,<0x07000008070F0F00,
           0x0F0F0F000B0A0008,
           0x7030304070701000,
           0x0707000000303030>
        mov rax,q
        stosq
        endm
else
    for q,<0x07000708070F0700,
           0x080807000B0A0008,
           0x70707040F0F01000,
           0x0707000070703080>
        mov rax,q
        stosq
        endm
endif

    mov edi,0x00190050
    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

        mov edi,ci.dwSize
    .endif

    mov     [rbx].Flags,W_ISOPEN ;or _W__VISIBLE
    mov     [rbx].rc.x,0
    mov     [rbx].rc.y,0
    movzx   eax,di
    shr     edi,16
    mov     [rbx].rc.col,al
    mov     edx,edi
    mov     [rbx].rc.row,dl
    mul     edi
    mov     [rbx].Window,malloc(&[rax*4])

    .if ( rax == NULL )

        free(rbx)
        .return 0
    .endif

    mov rdi,[rbx].Class
  assume rdi:class_t
    mov [rdi].Console,rbx
    mov [rdi].Focus,1
    mov [rdi].StdIn,GetStdHandle(STD_INPUT_HANDLE)
    mov [rdi].StdOut,GetStdHandle(STD_OUTPUT_HANDLE)
    mov [rdi].ErrMode,SetErrorMode(SEM_FAILCRITICALERRORS)

    GetConsoleMode([rdi].StdIn, &[rdi].ConMode)
    SetConsoleMode([rdi].StdIn, ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
    FlushConsoleInputBuffer([rdi].StdIn)

    [rbx].Read()

    mov rax,rbx
    ret

TWindow::TWindow endp

TWindow::Release proc uses rbx

    mov rbx,rcx

    .if [rbx].Cursor

        free([rbx].Cursor)
    .endif

    xor eax,eax
    .if [rbx].Flags & W_CHILD

        .for ( rcx = [rbx].PrevInst : rcx && [rcx].Child != rbx : rcx = [rcx].Child )
        .endw
        .if rcx
            mov [rcx].Child,[rbx].Child
        .endif
        mov [rbx].Child,rax

    .elseif ( rax == [rbx].PrevInst )

        mov rax,[rbx].Class
        SetConsoleMode([rax].APPINFO.StdIn, [rax].APPINFO.ConMode)
        mov rax,[rbx].Class
        SetErrorMode([rax].APPINFO.ErrMode)
    .endif

    .while rbx
        .if [rbx].Flags & W_ISOPEN
            .if [rbx].Flags & W_VISIBLE
                [rbx].Hide()
            .endif
            free([rbx].Window)
        .endif
        mov rcx,rbx
        mov rbx,[rbx].Child
        free(rcx)
    .endw
    xor eax,eax
    ret

TWindow::Release endp

    end

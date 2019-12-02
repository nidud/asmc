; TWINDOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include stdio.inc
include crtl.inc
include twindow.inc

TWindow::Load           proto :idd_t
TWindow::Resource       proto :idd_t
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
TWindow::DefWindowProc  proto :uint_t, :size_t, :ptr
TWindow::GetFocus       proto
TWindow::SetFocus       proto :uint_t
TWindow::GetItem        proto :uint_t
TWindow::MoveConsole    proto :int_t, :int_t
TWindow::SetConsole     proto :int_t, :int_t
TWindow::SetMaxConsole  proto
TWindow::ConsoleSize    proto


    .data
    AttributesDefault label byte
        db 0x00,0x0F,0x0F,0x07,0x08,0x00,0x00,0x07,0x08,0x00,0x0A,0x0B,0x00,0x0F,0x0F,0x0F
        db 0x00,0x10,0x70,0x70,0x40,0x30,0x30,0x70,0x30,0x30,0x30,0x00,0x00,0x00,0x07,0x07
    AttributesTransparent label byte
        db 0x07,0x07,0x0F,0x07,0x08,0x07,0x07,0x07,0x08,0x0F,0x0A,0x0B,0x0F,0x0B,0x0B,0x0B
        db 0x00,0x00,0x00,0x10,0x30,0x10,0x10,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x07,0x07


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

        .if ( [rbx].Flags & W_TRANSPARENT )
            mov rdi,[rbx].Window
            mov rsi,wp
            mov eax,col
            mul row
            .for ( ecx = eax, edx = 0 : edx < ecx : edx++ )
                .if ( byte ptr [rsi+rdx*4+2] == 0x08 )
                    mov ax,[rdi+rdx*4]
                    mov [rsi+rdx*4],ax
                .endif
            .endf
        .endif
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

TWindow::PutChar proc uses rdi x:int_t, y:int_t, count:int_t, w:CHAR_INFO

    movzx edi,[rcx].rc.col
    imul  edi,r8d
    add   edi,edx
    shl   edi,2
    add   rdi,[rcx].Window
    mov   eax,w
    xchg  rcx,r9

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
    xor eax,eax
    ret

TWindow::PutChar endp

TWindow::Clear proc at:CHAR_INFO

    movzx eax,[rcx].rc.row
    mul [rcx].rc.col
    mov r9d,eax
    [rcx].PutChar(0, 0, r9d, edx)
    ret

TWindow::Clear endp

frame_type  struct 1
BottomRight db ?
BottomLeft  db ?
Vertical    db ?
TopRight    db ?
Horizontal  db ?
TopLeft     db ?
Cols        db ?
Rows        db ?
frame_type  ends

TWindow::PutFrame proc uses rsi rdi rcx rc:TRECT, type:int_t, Attrib:uchar_t

  local ft:frame_type

    .switch pascal r8
      .case 0 : mov rax,'ÚÄ¿³ÀÙ'
      .case 1 : mov rax,'ÉÍ»ºÈ¼'
      .case 2 : mov rax,'ÂÄÂ³ÁÁ'
      .case 3 : mov rax,'ÃÄ´³Ã´'
      .default
        .return 0
    .endsw

    mov     ft,rax
    movzx   eax,[rcx].rc.col
    mul     dh
    mov     edi,eax
    movzx   eax,dl
    add     edi,eax
    shl     edi,2
    add     rdi,[rcx].Window
    shr     edx,16
    sub     edx,0x0202
    mov     ft.Cols,dl
    mov     ft.Rows,dh
    movzx   eax,r9b
    movzx   edx,[rcx].rc.col
    shl     edx,2
    lea     r8,[rdi+rdx]
    shl     eax,16
    mov     al,ft.TopLeft
    movzx   r9d,ft.Cols

    .ifnz

        stosd
        mov     al,ft.Horizontal
        movzx   ecx,ft.Cols
        rep     stosd
        mov     al,ft.TopRight
        stosd
        mov     al,ft.Vertical

        .for ( ecx = 0 : cl < ft.Rows : ecx++ )

            mov     rdi,r8
            add     r8,rdx
            stosd
            mov     [rdi+r9*4],eax
        .endf

        mov     rdi,r8
        mov     al,ft.BottomLeft
        stosd
        mov     al,ft.Horizontal
        movzx   ecx,ft.Cols
        rep     stosd
        mov     al,ft.BottomRight
        stosd

    .else

        mov [rdi],al
        mov al,ft.Horizontal
        add rdi,4
        .for ( ecx = 0 : ecx < r9d : ecx++, rdi += 4 )
            mov [rdi],al
        .endf
        mov al,ft.TopRight
        mov [rdi],al
        mov al,ft.Vertical
        .for ( ecx = 0 : cl < ft.Rows : ecx++ )
            mov rdi,r8
            add r8,rdx
            mov [rdi],al
            mov [rdi+r9*4+4],al
        .endf
        mov rdi,r8
        mov al,ft.BottomLeft
        mov [rdi],al
        add rdi,4
        mov al,ft.Horizontal
        .for ( ecx = 0 : ecx < r9d : ecx++, rdi += 4 )
            mov [rdi],al
        .endf
        mov al,ft.BottomRight
        mov [rdi],al
    .endif
    ret

TWindow::PutFrame endp

TWindow::PutString proc x:int_t, y:int_t, at:ushort_t, max:int_t, format:string_t, argptr:vararg

  local w:ptr_t
  local highat:byte
  local attrib:byte
  local buffer[4096]:char_t
  local retval:int_t

    mov eax,r9d
    mov attrib,al
    mov highat,ah

    .if ( eax == 0 && r8d && [rcx].Flags & W_TRANSPARENT )

        mov r9,[rcx].Color
        mov al,[r9+BG_DIALOG]
        or  al,[r9+FG_DIALOG]
        mov attrib,al
        mov al,[r9+BG_DIALOG]
        or  al,[r9+FG_DIALOGKEY]
        mov highat,al
    .endif

    movzx   eax,[rcx].rc.col
    imul    eax,r8d
    add     eax,edx
    lea     rax,[rax*4]
    add     rax,[rcx].Window
    mov     w,rax
    mov     retval,vsprintf(&buffer, format, &argptr)
    mov     rcx,this
    mov     r11d,max

    .if !r11d

        mov r11b,[rcx].rc.col
        sub r11d,x
    .endif

    .for ( rdx = w,
           r8  = &buffer,
           r9d = 0,
           r9b = [rcx].rc.col,
           r9d <<= 2,
           r10 = rdx,
           ah  = attrib,
           al  = [r8] : al, r11d : r8++, al = [r8], r11d-- )

        .if al == 10

            add r10,r9
            mov rdx,r10
            mov r11b,[rcx].rc.col
            sub r11d,x

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

            ;.if !( al == ' ' && [rcx].Flags & W_TRANSPARENT )
                mov [rdx],al
                .if ah
                    mov [rdx+2],ah
                .endif
            ;.endif
            add rdx,4
        .endif
    .endf
    mov eax,retval
    ret

TWindow::PutString endp

TWindow::PutPath proc uses rsi rdi rbx x:int_t, y:int_t, max:int_t, path:string_t

  local pre[16]:char_t

    mov rsi,path
    mov ebx,r9d

    .ifd strlen(rsi) > ebx
        lea rcx,pre
        mov edx,[rsi]
        add rsi,rax
        sub rsi,rbx
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
        sub ebx,eax
        mov [rcx],dh
        mov [rcx+1],dl
        mov [rcx+2],dx
        mov byte ptr [rcx+4],0
        mov rcx,this
        mov edx,x
        add x,eax
        [rcx].PutString(x, y, 0, 6, &pre)
    .endif
    mov rcx,this
    [rcx].PutString(x, y, 0, ebx, rsi)
    ret

TWindow::PutPath endp


    assume rbx:window_t

TWindow::PutCenter proc uses rsi rdi rbx x:int_t, y:int_t, l:int_t, string:string_t

    mov rbx,rcx
    mov rsi,string
    mov edi,r9d
    .return [rbx].PutPath(x, y, edi, rsi) .ifd strlen(rsi) > edi
    sub edi,eax
    shr edi,1
    add x,edi
    [rbx].PutString(x, y, 0, eax, rsi)
    ret

TWindow::PutCenter endp


TWindow::PutTitle proc string:string_t

    movzx   r9d,[rcx].rc.col
    mov     rdx,[rcx].Color
    movzx   eax,byte ptr [rdx+BG_TITLE]
    or      al,[rdx+FG_TITLE]
    shl     eax,16
    mov     al,' '

    [rcx].PutChar(0, 0, r9d, eax)
    movzx r9d,[rcx].rc.col
    [rcx].PutCenter(0, 0, r9d, string)
    ret

TWindow::PutTitle endp


TWindow::Window proc uses rbx rdx

    mov     rbx,rcx
    test    [rcx].Flags,W_CHILD
    cmovnz  rbx,[rcx].PrevInst
    movzx   eax,[rcx].rc.y
    movzx   r8d,[rbx].rc.col
    mul     r8d
    movzx   edx,[rcx].rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rbx].Window
    ret

TWindow::Window endp


TWindow::PushButton proc uses rsi rdi rbx rcx rc:TRECT, id:uint_t, title:string_t

    mov     rsi,r9
    mov     rbx,[rcx].Child(edx, r8d, T_PUSHBUTTON)
    .return .if !rax

    mov     rdi,[rbx].Window()
    movzx   ecx,[rbx].rc.col
    mov     rdx,[rbx].Color
    movzx   eax,byte ptr [rdx+BG_PUSHBUTTON]
    or      al,[rdx+FG_TITLE]
    shl     eax,16
    mov     al,' '
    mov     r11,rdi
    rep     stosd
    mov     al,[rdi+2]
    and     eax,0xF0
    or      al,[rdx+FG_PBSHADE]
    shl     eax,16
    mov     al,'Ü'
    mov     [rdi],eax
    lea     rdi,[r11+r8*4+4]
    movzx   ecx,[rbx].rc.col
    mov     al,'ß'
    rep     stosd
    lea     rdi,[r11+8]
    mov     al,byte ptr [rdx+BG_PUSHBUTTON]
    mov     cl,al
    or      al,[rdx+FG_TITLE]
    or      cl,[rdx+FG_TITLEKEY]
    shl     eax,16

    .while 1

        lodsb
        .break .if !al

        .if al != '&'

            stosd
            .continue(0)

        .else

            lodsb
            .break .if !al

            mov [rdi],ax
            mov [rdi+2],cl
            add rdi,4
            and al,not 0x20
            mov byte ptr [rbx].SysKey,al
        .endif
    .endw

    mov eax,1
    ret

TWindow::PushButton endp


TWindow::Open proc uses rsi rdi rbx rcx rc:TRECT, flags:uint_t

    mov rbx,rcx
    mov edi,edx
    mov esi,r8d

    .return .if !malloc(TWindow)

    mov r8d,edi
    mov rdx,rax
    mov rdi,rax
    mov ecx,TWindow/8
    xor eax,eax
    rep stosq

    mov rcx,rdx
    mov [rcx].lpVtbl,[rbx].lpVtbl
    mov [rcx].Class,[rbx].Class
    mov [rcx].Color,[rbx].Color
    mov [rcx].rc,r8d
    mov [rcx].Flags,esi
    mov [rcx].PrevInst,rbx

    .if ( [rcx].Flags & W_TRANSPARENT )

        lea rax,AttributesTransparent
        mov [rcx].Color,rax
    .endif

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

        mov [rbx].Window,rax
        or  [rbx].Flags,W_ISOPEN

        .if ( [rbx].Flags & W_TRANSPARENT )

            [rbx].Read()
            [rbx].Clear(0x00080000)
        .endif
        mov rax,rbx
    .else
        free(rbx)
    .endif
    ret

TWindow::Open endp


TWindow::Child proc uses rdi rbx rcx rc:TRECT, id:uint_t, type:uint_t

    mov edi,r9d
    mov ebx,r8d

    .return .if ( [rcx].Open(edx, W_CHILD or W_WNDPROC) == NULL )

    mov [rax].TWindow.Index,ebx
    mov [rax].TWindow.Type,edi
    mov rbx,rax
    lea rax,TWindow_DefWindowProc
    mov [rbx].WndProc,rax

    .for ( rcx = [rbx].PrevInst : [rcx].Child : rcx = [rcx].Child )

    .endf
    mov [rcx].Child,rbx
    mov rax,rbx
    ret

TWindow::Child endp


TWindow::TWindow proc uses rsi rdi rbx

  local ci: CONSOLE_SCREEN_BUFFER_INFO

    mov rdi,rcx
    mov rbx,malloc( TWindow + APPINFO + TWindowVtbl )
    .if rdi
        stosq
    .endif
    .return .if !rax

    mov rdi,rax
    mov ecx,(TWindow + APPINFO) / 8
    xor eax,eax
    rep stosq
    mov [rbx].lpVtbl,rdi
    lea rax,[rbx+TWindow]
    mov [rbx].Class,rax

    for q,<TWindow_Open,
           TWindow_Load,
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
           TWindow_PutFrame,
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
           TWindow_DefWindowProc,
           TWindow_Child,
           TWindow_Window,
           TWindow_PushButton,
           TWindow_GetFocus,
           TWindow_SetFocus,
           TWindow_GetItem,
           TWindow_MoveConsole,
           TWindow_SetConsole,
           TWindow_SetMaxConsole,
           TWindow_ConsoleSize>

        lea rax,q
        stosq
        endm

    lea rax,AttributesDefault
    mov [rbx].Color,rax
    mov edi,0x00190050
    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)
        mov edi,ci.dwSize
    .endif

    mov     [rbx].Flags,W_ISOPEN or W_COLOR
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

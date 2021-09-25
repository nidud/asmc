; TWINDOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
include crtl.inc
include twindow.inc

    .data
    AttributesDefault label byte
        db 0x00,0x0F,0x0F,0x07,0x08,0x00,0x00,0x07,0x08,0x00,0x0A,0x0B,0x00,0x0F,0x0F,0x0F
        db 0x00,0x10,0x70,0x70,0x40,0x30,0x30,0x70,0x30,0x30,0x30,0x00,0x00,0x00,0x07,0x07
    AttributesTransparent label byte
        db 0x07,0x07,0x0F,0x07,0x08,0x07,0x07,0x07,0x08,0x0F,0x0A,0x0B,0x0F,0x0B,0x0B,0x0B
        db 0x00,0x00,0x00,0x10,0x30,0x10,0x10,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x07,0x07


    .code

    option proc:private

    assume rcx:window_t
    assume rbx:window_t

TWindow::CursorGet proc

    mov rax,[rcx].Cursor

    .if ( rax == NULL )

        mov rax,[rcx].Class

        .new TCursor()

        mov rcx,this
        mov [rcx].Cursor,rax
    .endif
    ret

TWindow::CursorGet endp

TWindow::CursorSet proc

    mov rax,[rcx].Cursor

    .if ( rax != NULL )

        [rax].TCursor.Release()

        mov rcx,this
        xor eax,eax
        mov [rcx].Cursor,rax
    .endif
    ret

TWindow::CursorSet endp

TWindow::CursorOn proc

    .if [rcx].CursorGet()

        [rax].TCursor.Show()
        mov rcx,this
    .endif
    ret

TWindow::CursorOn endp

TWindow::CursorOff proc

    .if [rcx].CursorGet()

        [rax].TCursor.Hide()
        mov rcx,this
    .endif
    ret

TWindow::CursorOff endp

TWindow::CursorMove proc x:int_t, y:int_t

    .if [rcx].CursorGet()

        [rax].TCursor.Move(x, y)
        mov rcx,this
    .endif
    ret

TWindow::CursorMove endp

TWindow::Clear proc at:CHAR_INFO

    movzx   eax,[rcx].rc.row
    mul     [rcx].rc.col

    [rcx].PutChar(0, 0, eax, edx)
    ret

TWindow::Clear endp

TWindow::SetShade proc uses rdi

  local rc[2]:TRect

    .return .if !( [rcx].Flags & W_SHADE )

    mov     rc,[rcx].rc
    mov     rc[4],eax
    shr     eax,16
    mov     rc[4].col,2
    dec     rc[4].row
    inc     rc[4].y
    add     rc[4].x,al
    add     rc.y,ah
    mov     rc.row,1
    add     rc.x,2
    movzx   eax,[rcx].rc.col
    mul     [rcx].rc.row
    lea     rdi,[rax*4]
    add     rdi,[rcx].Window
    [rcx].Read(&rc, rdi)
    movzx   eax,rc.col
    [rcx].Read(&rc[4], &[rdi+rax*4])
    movzx   edx,rc.col
    add     dl,rc[4].row
    add     dl,rc[4].row
    .for rax = rdi : edx : edx--, rax += 4
        mov byte ptr [rax+2],0x08
    .endf
    [rcx].Exchange(&rc, rdi)
    movzx   eax,rc.col
    [rcx].Exchange(&rc[4], &[rdi+rax*4])
    ret

TWindow::SetShade endp


TWindow::ClrShade proc uses rsi

  local rc[2]:TRect

    .return .if !( [rcx].Flags & W_SHADE )

    mov     rc,[rcx].rc
    mov     rc[4],eax
    shr     eax,16
    mov     rc[4].col,2
    dec     rc[4].row
    inc     rc[4].y
    add     rc[4].x,al
    add     rc.y,ah
    mov     rc.row,1
    add     rc.x,2
    movzx   eax,[rcx].rc.col
    mul     [rcx].rc.row
    lea     rsi,[rax*4]
    add     rsi,[rcx].Window
    [rcx].Exchange(&rc[0], rsi)
    movzx   eax,rc.col
    [rcx].Exchange(&rc[4], &[rsi+rax*4])
    ret

TWindow::ClrShade endp

TWindow::Show proc

    mov eax,[rcx].Flags
    and eax,W_ISOPEN or W_VISIBLE
    .return .ifz

    .if !( eax & W_VISIBLE )

        [rcx].Exchange(&[rcx].rc, [rcx].Window)

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

        [rcx].Exchange(&[rcx].rc, [rcx].Window)

        .if [rcx].Flags & W_SHADE

            [rcx].ClrShade()
        .endif
        and [rcx].Flags,not W_VISIBLE
    .endif
    mov eax,1
    ret

TWindow::Hide endp

TWindow::Window proc uses rbx rdx

    mov     rbx,rcx
    test    [rcx].Flags,W_CHILD
    cmovnz  rbx,[rcx].Prev
    movzx   eax,[rcx].rc.y
    movzx   r8d,[rbx].rc.col
    mul     r8d
    movzx   edx,[rcx].rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rbx].Window
    ret

TWindow::Window endp

TWindow::Open proc uses rsi rdi rbx rcx rc:TRect, flags:uint_t

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
    mov [rcx].Prev,rbx

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

            [rbx].Read(&[rbx].rc, rax)
            [rbx].Clear(0x00080000)
        .endif
        mov rax,rbx
    .else
        free(rbx)
    .endif
    ret

TWindow::Open endp

TWindow::Child proc uses rdi rbx rcx rc:TRect, id:uint_t, type:uint_t

    mov edi,r9d
    mov ebx,r8d

    .return .if ( [rcx].Open(edx, W_CHILD or W_WNDPROC) == NULL )

    mov [rax].TWindow.Index,ebx
    mov [rax].TWindow.Type,edi
    mov rbx,rax
    mov [rbx].WndProc,&TWindow::DefWindowProc

    .for ( rcx = [rbx].Prev : [rcx].Child : rcx = [rcx].Child )
    .endf
    mov [rcx].Child,rbx
    mov rax,rbx
    ret

TWindow::Child endp


UnzipChar:
    movzx eax,[rbx].rc.col
    mul [rbx].rc.row
    mov ecx,eax
    xor eax,eax
    .repeat
        mov al,[rsi]
        mov dl,[rsi]
        add rsi,1
        and dl,0xF0
        .if dl == 0xF0
            mov dh,al
            mov dl,[rsi]
            mov al,[rsi+1]
            add rsi,2
            and edx,0x0FFF
            .repeat
                mov [rdi],ax
                add rdi,4
                dec edx
                .break .ifz
            .untilcxz
            .break .if !ecx
        .else
            mov [rdi],ax
            add rdi,4
        .endif
    .untilcxz
    ret

UnzipAttrib:
    movzx eax,[rbx].rc.col
    mul [rbx].rc.row
    mov ecx,eax
    xor eax,eax
    .repeat
        mov al,[rsi]
        mov r9b,al
        add rsi,1
        and r9b,0xF0
        xor edx,edx
        .if r9b == 0xF0
            mov dh,al
            mov dl,[rsi]
            mov al,[rsi+1]
            add rsi,2
            and edx,0x0FFF
        .endif
        mov r8d,eax
        and eax,0xF0
        shr eax,4
        and r8d,0x0F
        mov al,[r10+rax+16]
        or  al,[r10+r8]
        .if r9b == 0xF0
            .repeat
                mov [rdi],ax
                add rdi,4
                dec edx
                .break .ifz
            .untilcxz
            .break .if !ecx
        .else
            mov [rdi],ax
            add rdi,4
        .endif
    .untilcxz
    ret

TWindow::Read proc rect:trect_t, pc:PCHAR_INFO

    mov rax,[rcx].Class
    mov rcx,rdx

    TRect::Read(rcx, [rax].TClass.StdOut, r8)
    mov rcx,this
    ret

TWindow::Read endp

TWindow::Write proc rect:trect_t, pc:PCHAR_INFO

    mov rax,[rcx].Class
    mov rcx,rdx

    TRect::Write(rcx, [rax].TClass.StdOut, r8)
    mov rcx,this
    ret

TWindow::Write endp

TWindow::Exchange proc rc:trect_t, pc:PCHAR_INFO

    mov rax,[rcx].Class
    mov rcx,rdx

    TRect::Exchange(rcx, [rax].TClass.StdOut, r8)
    mov rcx,this
    ret

TWindow::Exchange endp

    assume rsi:robject_t

TWindow::Resource proc uses rsi rdi rbx r12 rcx p:resource_t

    lea     rsi,[rdx].TResource.dialog
    movzx   r8d,[rsi].flags
    and     r8d,W_MOVEABLE or W_SHADE or W_COLOR
    mov     rbx,[rcx].Open([rsi].rc, r8d)
    .return .if !rax

    [rbx].Load(&[rsi-2])
    movzx   edi,[rsi].count
    movzx   eax,[rsi].index
    lea     rsi,[rsi+TRObject]
    inc     eax
    mov     [rbx].Index,eax

    .for ( r12d = 1 : edi : edi--, rsi += TRObject, r12d++ )

        mov     r9w,[rsi].flags
        and     r9d,0x0F
        inc     r9d
        mov     rcx,[rbx].Child([rsi].rc, r12d, r9d)
        movzx   eax,[rsi].flags
        and     eax,0xFFF0
        shl     eax,4
        or      [rcx].Flags,eax
    .endf
    mov rax,rbx
    ret

TWindow::Resource endp

TWindow::Load proc uses rsi rdi rbx p:resource_t

    xor eax,eax
    mov rbx,rcx
    lea rsi,[rdx].TResource.dialog
    mov al,[rsi].count
    lea rsi,[rsi+rax*8+8]
    mov r10,[rbx].Color
    mov rdi,[rbx].Window
    add rdi,2
    .if ( [rbx].Flags & W_COLOR )
        UnzipAttrib()
    .else
        UnzipChar()
    .endif
    mov rdi,[rbx].Window
    UnzipChar()
    mov rcx,rbx
    ret

TWindow::Load endp

    assume rsi:nothing

TWindow::PutChar proc uses rdi x:int_t, y:int_t, count:int_t, w:CHAR_INFO

    movzx   edi,[rcx].rc.col
    imul    edi,r8d
    add     edi,edx
    shl     edi,2
    add     rdi,[rcx].Window
    mov     eax,w
    xchg    rcx,r9

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
            mov [rdx],al
            .if ah
                mov [rdx+2],ah
            .endif
            add rdx,4
        .endif
    .endf
    mov eax,retval
    ret

TWindow::PutString endp

TWindow::PutTitle proc string:string_t

    movzx   r9d,[rcx].rc.col
    mov     rdx,[rcx].Color
    movzx   eax,byte ptr [rdx+BG_TITLE]
    or      al,[rdx+FG_TITLE]
    shl     eax,16
    mov     al,' '

    [rcx].PutChar(0, 0, r9d, eax)

    movzx   r9d,[rcx].rc.col

    [rcx].PutCenter(0, 0, r9d, string)
    ret

TWindow::PutTitle endp

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

TWindow::PutFrame proc uses rsi rdi rcx rc:TRect, type:int_t, Attrib:uchar_t

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

TWindow::PutCenter proc uses rsi rdi rbx x:int_t, y:int_t, l:int_t, string:string_t

    mov     rbx,rcx
    mov     rsi,string
    mov     edi,r9d
    .return [rbx].PutPath(x, y, edi, rsi) .ifd strlen(rsi) > edi

    sub     edi,eax
    shr     edi,1
    add     x,edi
    [rbx].PutString(x, y, 0, eax, rsi)
    ret

TWindow::PutCenter endp

    assume rsi:class_t

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

TWindow::PushButton proc uses rsi rdi rbx rcx rc:TRect, id:uint_t, title:string_t

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

TWReadLine proc private uses rsi rdi rbx this:window_t, x:int_t, y:int_t, l:int_t

  local rc:SMALL_RECT

    mov     rbx,rcx

    movzx   eax,dl
    movzx   edx,r8b
    mov     rc.Left,ax
    mov     rc.Top,dx
    mov     ecx,r9d
    mov     esi,ecx

    .ifs esi < 0

        not esi
        mov ecx,esi
        add edx,esi
        dec edx
        shl esi,16
        mov si,1
    .else
        add eax,esi
        add esi,0x10000
    .endif

    mov rc.Right,ax
    mov rc.Bottom,dx
    shl ecx,2

    .if malloc(ecx)

        mov rdx,[rbx].Class
        mov rcx,[rdx].TClass.StdOut
        mov r8d,esi
        mov rsi,rax
        ReadConsoleOutput(rcx, rsi, r8d, 0, &rc)
        mov rax,rsi
    .endif

    mov rcx,rbx
    ret

TWReadLine endp

TWWriteLine proc private uses rbx this:window_t, x:int_t, y:int_t, l:int_t, p:PCHAR_INFO

  local rc:SMALL_RECT

    mov     rbx,rcx

    movzx   eax,dl
    mov     ecx,r9d
    movzx   edx,r8b
    mov     rc.Top,dx
    mov     rc.Left,ax

    .ifs ecx < 0

        not ecx
        not r9d

        add edx,ecx
        dec edx
        shl ecx,16
        mov cx,1
    .else
        add eax,ecx
        add ecx,0x10000
    .endif

    mov rc.Right,ax
    mov rc.Bottom,dx

    mov r8d,ecx
    mov rax,[rbx].Class
    mov rcx,[rax].TClass.StdOut
    WriteConsoleOutput(rcx, p, r8d, 0, &rc)
    free(p)

    mov rcx,rbx
    ret

TWWriteLine endp

TWindow::Move proc uses rsi rdi rbx r12 x:int_t, y:int_t

  local lx          :int_t,
        ly          :int_t,
        l           :int_t,
        Cols        :int_t,
        Rows        :int_t,
        Screen      :COORD,
        wp          :PCHAR_INFO,
        lp          :PCHAR_INFO,
        size        :int_t,
        count       :int_t,
        Direction   :int_t

    mov rbx,rcx
    mov Screen,[rcx].ConsoleSize()
    movzx eax,[rcx].rc.col
    mov Cols,eax
    mov al,[rcx].rc.row
    mov Rows,eax
    add eax,y
    movzx edx,Screen.y

    .if eax > edx
        sub edx,Rows
        mov y,edx
    .endif
    .if y == 0
        inc y
    .endif

    mov eax,Cols
    add eax,x
    movzx edx,Screen.x
    .if eax > edx
        sub edx,Cols
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
    mov eax,Cols
    mul Rows
    shl eax,2
    mov wp,malloc(eax)

    .return .if !rax

    .for Direction = 0 : count : count--

        movzx esi,[rbx].rc.x
        movzx edi,[rbx].rc.y

        .break .if esi == x && edi == y

        [rbx].Read(&[rbx].rc, wp)

        .switch
          .case <Right> esi < x
            mov eax,Direction
            mov Direction,1
            .if eax == 1
                .if edi > y
                    jmp Up
                .elseif edi < y
                    jmp Down
                .endif
            .endif
            mov lx,esi
            mov ly,edi
            mov ecx,esi
            add ecx,Cols
            mov r8d,Rows
            not r8d
            mov r9,TWReadLine(rbx, ecx, edi, r8d)
            inc [rbx].rc.x
            .for edx=Rows, rsi=[rbx].Window, rdi=rax : edx : edx--, rdi+=4
                mov eax,[rsi]
                mov r8d,[rdi]
                mov [rdi],eax
                mov ecx,Cols
                dec ecx
                mov r10,rdi
                mov rdi,rsi
                add rsi,4
                rep movsd
                mov rdi,r10
                mov [rsi-4],r8d
            .endf
            mov r8d,Rows
            not r8d
            TWWriteLine(rbx, lx, ly, r8d, r9)
            .endc

          .case <Left> esi > x
            mov eax,Direction
            mov Direction,2
            .if eax == 2
                .if edi > y
                    jmp Up
                .elseif edi < y
                    jmp Down
                .endif
            .endif
            mov lx,esi
            mov ly,edi
            lea rdi,[rsi-1]
            mov esi,Rows
            mov eax,esi
            not eax
            mov l,eax
            mov r12,TWReadLine(rbx, edi, ly, eax)
            dec [rbx].rc.x
            mov r8d,Cols
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
                mov ecx,Cols
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
            mov ecx,Cols
            add ecx,lx
            dec ecx
            TWWriteLine(rbx, ecx, ly, l, r12)
            .endc

          .case <Up> edi > y
            mov Direction,3
            mov lx,esi
            mov esi,Rows
            dec edi
            add esi,edi
            mov rcx,TWReadLine(rbx, lx, edi, Cols)
            dec [rbx].rc.y
            mov r12d,Cols
            shl r12d,2
            mov eax,Rows
            dec eax
            mul r12d
            mov rdi,[rbx].Window
            add rdi,rax
            TWWriteLine(rbx, lx, esi, Cols, memxchg(rcx, rdi, r12))
            mov rax,rdi
            sub rax,r12
            mov esi,Rows
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
            add edx,Rows
            TWReadLine(rbx, esi, edx, Cols)
            inc [rbx].rc.y
            mov r12d,Cols
            shl r12d,2
            TWWriteLine(rbx, esi, edi, Cols, memxchg(rax, [rbx].Window, r12))
            .for esi=Rows, esi--, rdi=[rbx].Window : esi : esi--, rdi+=r12
                memxchg(rdi, &[rdi+r12], r12)
            .endf
            .endc
        .endsw

        .if [rbx].Flags & W_TRANSPARENT
            mov rdi,[rbx].Window
            mov rsi,wp
            mov eax,Cols
            mul Rows
            .for ( ecx = eax, edx = 0 : edx < ecx : edx++ )
                .if ( byte ptr [rsi+rdx*4+2] == 0x08 )
                    mov ax,[rdi+rdx*4]
                    mov [rsi+rdx*4],ax
                .endif
            .endf
        .endif
        [rbx].Write(&[rbx].rc, wp)
    .endf
    free(wp)
    mov rcx,rbx
    ret

TWindow::Move endp

GetItemRect proto hwnd:window_t {
    mov     rax,[hwnd].Prev
    movzx   eax,word ptr [rax].TWindow.rc
    add     eax,[hwnd].rc
    }

ContextRect proto hwnd:window_t {
    mov     [hwnd].Context.rc,GetItemRect(hwnd)
    }

OnEnterIdle proc uses rcx hwnd:window_t

    Sleep(4)
    xor eax,eax
    ret

OnEnterIdle endp

Inside proc hwnd:window_t, pos:COORD

  local rc:TRect

    mov eax,[rcx].rc
    .if ( [rcx].Flags & W_CHILD )
        mov r10,[rcx].Prev
        add ax,word ptr [r10].TWindow.rc
    .endif
    mov rc,eax
    xor eax,eax
    mov dh,rc.x
    .if dl >= dh
        add dh,rc.col
        .if dl < dh
            shr edx,16
            mov dh,rc.y
            .if dl >= dh
                add dh,rc.row
                .if dl < dh
                    mov al,dl
                    sub al,rc.y
                    inc al
                .endif
            .endif
        .endif
    .endif
    ret

Inside endp

    assume rbx:window_t
    assume rsi:context_t

OnLButtonDown proc uses rsi rdi rbx rcx hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .ifd Inside(rcx, r8d) == 0

        .return [rcx].PostQuit(0) .if !( [rcx].Flags & W_CHILD )
        .return TRUE
    .endif
    lea rsi,[rcx].Context
    .switch [rcx].Type
      .case T_NORMAL
        .if ( eax > 1 )
            mov rcx,[rcx].Child
            .return [rcx].Send(WM_LBUTTONDOWN, r8, r9) .if rcx
            .return TRUE
        .endif
        mov [rsi].State,1
        mov [rsi].Flags,0
        mov [rsi].rc.x,r8b
        sub r8b,[rcx].rc.x
        mov [rsi].x,r8b
        shr r8d,16
        mov [rsi].rc.y,r8b
        sub r8b,[rcx].rc.y
        mov [rsi].y,r8b
        [rcx].CursorOff()
        .endc .if !( [rcx].Flags & W_SHADE )
        mov [rsi].Flags,1
        [rcx].ClrShade()
        and [rcx].Flags,not W_SHADE
        .endc
      .case T_PUSHBUTTON
        mov [rsi].State,1
        ContextRect(rcx)
        movzx ebx,al
        movzx edi,ah
        [rcx].CPutChar( ebx, edi, 1, ' ' )
        add bl,[rcx].rc.col
        dec bl
        [rcx].CPutChar( ebx, edi, 2, ' ' )
        movzx edx,[rcx].Context.rc.x
        inc edx
        inc edi
        [rcx].CPutChar( edx, edi, [rsi].rc.col, ' ' )
        [rcx].SetFocus( [rcx].Index )
        .endc
      .case T_RADIOBUTTON
      .case T_CHECKBOX
        [rcx].SetFocus( [rcx].Index )
        .endc
      .case T_XCELL
        [rcx].SetFocus([rcx].Index)
        .endc
      .case T_EDIT
      .case T_MENU
      .case T_XHTML
      .case T_MOUSE
      .case T_SCROLLUP
      .case T_SCROLLDOWN
      .case T_TEXTBUTTON
        .endc
    .endsw
    xor eax,eax
    ret

OnLButtonDown endp

OnLButtonUp proc uses rsi rdi rbx rcx hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    lea rsi,[rcx].Context
    .switch [rcx].Type
      .case T_NORMAL
        .if ( [rsi].State == 0 )
            mov rcx,[rcx].Child
            .return [rcx].Send(edx, r8, r9) .if rcx
            .return 1
        .endif
        mov [rsi].State,0
        .if ( [rsi].Flags )
            or [rcx].Flags,W_SHADE
            [rcx].SetShade()
        .endif
        [rcx].SetFocus( [rcx].Index )
        .endc
      .case T_PUSHBUTTON
        .return 1 .if ( [rsi].State == 0 )
        mov [rsi].State,0
        ContextRect(rcx)
        movzx edi,ah
        movzx edx,al
        inc edx
        [rcx].CPutChar( edx, edi, 1, 'Ü' )
        movzx edx,[rsi].rc.x
        inc edx
        inc edi
        [rcx].CPutChar( edx, edi, [rsi].rc.col, 'ß' )
        xor edx,edx
        test [rcx].Flags,O_DEXIT
        cmovz edx,[rcx].Index
        .return [rcx].PostQuit(edx)
      .case T_RADIOBUTTON
        .return 1 .if ( [rsi].State == 0 )
        mov [rsi].State,0
        .endc
      .case T_CHECKBOX
      .case T_XCELL
        ;[rcx].SetFocus( [rcx].Index )
        ;.endc
      .case T_EDIT
      .case T_MENU
      .case T_XHTML
      .case T_MOUSE
      .case T_SCROLLUP
      .case T_SCROLLDOWN
      .case T_TEXTBUTTON
        .return 1
    .endsw
    xor eax,eax
    ret

OnLButtonUp endp


OnMouseMove proc uses rsi hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    lea rsi,[rcx].Context
    xor eax,eax
    .return .if [rsi].State == 0
    .return .if [rcx].Flags & W_CHILD
    movzx edx,[rsi].rc.y
    shl edx,16
    mov dl,[rsi].rc.x
    .return .if edx == eax
    movsx eax,[rsi].x
    movzx edx,r8b
    .if edx >= eax
        sub edx,eax
    .else
        xor edx,edx
    .endif
    shr r8d,16
    movsx eax,[rsi].y
    .if r8d >= eax
        sub r8d,eax
    .else
        xor r8d,r8d
    .endif
    [rcx].Move(edx, r8d)
    xor eax,eax
    ret

OnMouseMove endp

    assume rsi:nothing


OnSetFocus proc uses rsi rdi rbx rcx hwnd:window_t

    [rcx].CursorGet()
    [rcx].CursorOn()

    .switch [rcx].Type
      .case T_PUSHBUTTON
        [rcx].CursorOff()
        ContextRect(rcx)
        movzx edi,ah
        movzx edx,al
        mov ebx,' '
        .if [rcx].Context.State == 0
            mov ebx,0x10
        .endif
        [rcx].CPutChar(edx, edi, 1, ebx)
        .if [rcx].Context.State == 0
            mov ebx,0x11
        .endif
        movzx edx,[rcx].Context.rc.x
        add dl,[rcx].Context.rc.col
        dec dl
        [rcx].CPutChar(edx, edi, 1, ebx)
        .endc
      .case T_RADIOBUTTON
      .case T_CHECKBOX
        ContextRect(rcx)
        movzx edx,al
        movzx eax,ah
        inc edx
        [rcx].CursorMove(edx, eax)
        .endc
      .case T_XCELL
        mov edx,[rcx].rc
        mov rax,[rcx].Prev
        add dx,word ptr [rax].TWindow.rc
        mov [rcx].Window,[rcx].Open(edx, 0)
        .endc .if !rax
        mov rcx,rax
        [rcx].Read(&[rcx].rc, [rcx].Window)
        or [rcx].Flags,W_VISIBLE
        mov rdx,[rcx].Color
        mov al,[rdx+BG_INVERSE]
        shr al,4
        movzx edx,[rcx].rc.x
        movzx r8d,[rcx].rc.y
        movzx r9d,[rcx].rc.col
        [rcx].CPutBackground(edx, r8d, r9d, al)
        .endc
      .case T_EDIT
      .case T_MENU
      .case T_XHTML
      .case T_MOUSE
      .case T_SCROLLUP
      .case T_SCROLLDOWN
      .case T_TEXTBUTTON
        .endc
    .endsw

    xor eax,eax
    ret

OnSetFocus endp


OnKillFocus proc uses rsi rdi rbx rcx hwnd:window_t

    [rcx].CursorSet()

    .switch [rcx].Type
      .case T_PUSHBUTTON
        ContextRect(rcx)
        movzx edi,ah
        movzx esi,al
        movzx edx,[rcx].rc.col
        lea rdx,[rdx+rsi-1]
        [rcx].CPutChar(edx, edi, 1, ' ')
        [rcx].CPutChar(esi, edi, 1, ' ')
        .endc
      .case T_RADIOBUTTON
      .case T_CHECKBOX
        .endc
      .case T_XCELL
        mov rax,[rcx].Window
        .endc .if !rax
        mov edx,[rcx].rc
        mov r10,[rcx].Prev
        add dx,word ptr [r10].TWindow.rc
        mov rbx,rcx
        mov rcx,rax
        mov [rcx].rc,edx
        [rcx].Release()
        xor eax,eax
        mov [rbx].Window,rax
        .endc
      .case T_EDIT
      .case T_MENU
      .case T_XHTML
      .case T_MOUSE
      .case T_SCROLLUP
      .case T_SCROLLDOWN
      .case T_TEXTBUTTON
        .endc
    .endsw

    xor eax,eax
    ret

OnKillFocus endp


NextItem proc uses rcx hwnd:window_t

    .return .if ![rcx].GetFocus()
    mov rcx,[rax].TWindow.Child
    .if rcx == NULL
        mov rcx,[rax].TWindow.Prev
        mov rcx,[rcx].Child
        .return .if !rcx
    .endif
    [rcx].SetFocus([rcx].Index)
    ret

NextItem endp


PrevItem proc uses rbx rcx hwnd:window_t

    test [rcx].Flags,W_CHILD
    cmovnz rcx,[rcx].Prev
    mov eax,[rcx].Index
    .for ( rbx = [rcx].Child : rbx : rcx = rbx, rbx = [rbx].Child )
        .break .if ( eax == [rbx].Index )
    .endf
    .if rbx
        .if !( [rcx].Flags & W_CHILD )
            .for : [rcx].Child : rcx = [rcx].Child
            .endf
        .endif
        [rcx].SetFocus([rcx].Index)
    .endif
    ret

PrevItem endp


ItemRight proc uses rcx hwnd:window_t

    .if [rcx].GetFocus()
        mov rcx,rax
        mov edx,[rcx].rc
        .while 1
            .for ( rax = [rcx].Child : rax : rax = [rax].TWindow.Child )
                .break .if !( [rax].TWindow.Flags & O_STATE )
            .endf
            .break .if !rax
            mov rcx,rax
            .if ( dl < [rcx].rc.x && dh == [rcx].rc.y )
                [rcx].SetFocus([rcx].Index)
                .return 0
            .endif
        .endw
    .endif
    mov eax,1
    ret

ItemRight endp


ItemLeft proc uses rcx hwnd:window_t

    .if [rcx].GetFocus()
        mov rcx,rax
        mov edx,[rcx].rc
        .while 1
            xor eax,eax
            mov r11,[rcx].Prev
            mov r11,[r11].TWindow.Child
            .for ( : r11 && rcx != r11 : r11 = [r11].TWindow.Child )
                .if !( [r11].TWindow.Flags & O_STATE )
                    mov rax,r11
                .endif
            .endf
            .break .if !rax
            mov rcx,rax
            .if ( dl > [rcx].rc.x && dh == [rcx].rc.y )
                [rcx].SetFocus([rcx].Index)
                .return 0
            .endif
        .endw
    .endif
    mov eax,1
    ret

ItemLeft endp


OnChar proc uses rbx rcx hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .if ( [rcx].Flags & W_CHILD )
        mov rax,[rcx].Prev
        mov eax,[rax].TWindow.Index
        .if ( eax == [rcx].Index )
            .switch [rcx].Type
            .case T_EDIT
                .return 1
            .case T_RADIOBUTTON
                .if r8d == VK_SPACE
                    mov rcx,[rcx].Prev
                    .for ( rcx = [rcx].Child : rcx : rcx = [rcx].Child )
                        .if [rcx].Flags & O_RADIO
                            GetItemRect(rcx)
                            movzx edx,al
                            movzx eax,ah
                            inc edx
                            and [rcx].Flags,not O_RADIO
                            [rcx].CPutChar(edx, eax, 1, ' ')
                            .break
                        .endif
                    .endf
                    GetItemRect(hwnd)
                    movzx edx,al
                    movzx eax,ah
                    inc edx
                    or  [rcx].Flags,O_RADIO
                    [rcx].CPutChar(edx, eax, 1, 7)
                    .return 0
                .endif
                .endc
            .case T_CHECKBOX
                .if r8d == VK_SPACE
                    GetItemRect(rcx)
                    movzx edx,al
                    movzx eax,ah
                    inc edx
                    xor [rcx].Flags,O_CHECK
                    mov r8d,' '
                    .if [rcx].Flags & O_CHECK
                        mov r8d,'x'
                    .endif
                    [rcx].CPutChar(edx, eax, 1, r8d)
                    .return 0
                .endif
                .endc
            .case T_PUSHBUTTON
            .case T_XCELL
            .case T_MENU
            .case T_XHTML
            .case T_MOUSE
            .case T_SCROLLUP
            .case T_SCROLLDOWN
            .case T_TEXTBUTTON
                .endc
            .endsw
            .if r8d == VK_RETURN
                xor     edx,edx
                test    [rcx].Flags,O_DEXIT
                cmovz   edx,eax
                .return [rcx].PostQuit(edx)
            .endif
        .endif
        .return 1
    .endif
    .switch r8d
      .case VK_UP     : .return PrevItem(rcx)
      .case VK_DOWN
      .case VK_TAB    : .return NextItem(rcx)
      .case VK_LEFT   : .return ItemLeft(rcx)
      .case VK_RIGHT  : .return ItemRight(rcx)
      .case VK_ESCAPE : .return [rcx].PostQuit(0)
    .endsw
    mov rcx,[rcx].Child
    .return [rcx].Send(edx, r8, r9) .if rcx
    ret

OnChar endp


OnSysChar proc uses rcx hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .if ( [rcx].Flags & W_CHILD )
        .if ( r8d == [rcx].SysKey )
            [rcx].SetFocus([rcx].Index)
            .return 0
        .endif
    .else
        mov rcx,[rcx].Child
        .return [rcx].Send(edx, r8, r9) .if rcx
    .endif
    mov eax,1
    ret

OnSysChar endp

TWindow::GetFocus proc uses rcx

    test [rcx].Flags,W_CHILD
    cmovnz rcx,[rcx].Prev
    mov eax,[rcx].Index
    .for ( rcx = [rcx].Child : rcx : rcx = [rcx].Child )
        .return rcx .if ( eax == [rcx].Index )
    .endf
    xor eax,eax
    ret

TWindow::GetFocus endp


TWindow::SetFocus proc uses rbx id:uint_t

    mov rbx,rcx
    .if [rcx].GetFocus()
        mov rcx,rax
        [rcx].Send(WM_KILLFOCUS, 0, 0)
        mov rcx,rbx
    .endif
    test [rcx].Flags,W_CHILD
    cmovnz rcx,[rcx].Prev
    mov [rcx].Index,id
    .if [rcx].GetFocus()
        mov rcx,rax
        [rcx].Send(WM_SETFOCUS, 0, 0)
    .endif
    mov rcx,rbx
    xor eax,eax
    ret

TWindow::SetFocus endp


TWindow::GetItem proc uses rcx id:uint_t

    test  [rcx].Flags,W_CHILD
    cmovnz rcx,[rcx].Prev
    .for ( rcx = [rcx].Child : rcx : rcx = [rcx].Child )
        .return rcx .if ( edx == [rcx].Index )
    .endf
    xor eax,eax
    ret

TWindow::GetItem endp


TWindow::DefWindowProc proc uiMsg:uint_t, wParam:size_t, lParam:ptr

    mov eax,1
    .switch pascal edx
      .case WM_ENTERIDLE:   OnEnterIdle(rcx)
      .case WM_SETFOCUS:    OnSetFocus(rcx)
      .case WM_KILLFOCUS:   OnKillFocus(rcx)
      .case WM_LBUTTONDOWN: OnLButtonDown(rcx, edx, r8, r9)
      .case WM_LBUTTONUP:   OnLButtonUp(rcx, edx, r8, r9)
      .case WM_MOUSEMOVE:   OnMouseMove(rcx, edx, r8, r9)
      .case WM_SYSCHAR:     OnSysChar(rcx, edx, r8, r9)
      .case WM_CHAR:        OnChar(rcx, edx, r8, r9)
    .endsw
    ret

TWindow::DefWindowProc endp

    assume rdx:message_t
    assume rcx:nothing

Dispatch proc uses rcx hwnd:window_t, msg:message_t

    mov rcx,[rcx].TWindow.Class
    mov r8,[rdx].Next
    mov rax,[rcx].TClass.Message

    .if ( rax == rdx )
        mov [rcx].TClass.Message,r8
    .elseif rax
        .while ( rax && rdx != [rax].TMessage.Next )
            mov rax,[rax].TMessage.Next
        .endw
        .if ( rax && rdx == [rax].TMessage.Next )
            mov [rax].TMessage.Next,r8
        .endif
    .endif
    free(rdx)
    ret

Dispatch endp


    assume rcx:window_t

Translate proc private uses rdi rcx hwnd:window_t, msg:message_t

    mov edi,[rdx].Message
    mov [rdx].Message,WM_NULL

    [rcx].Send(edi, [rdx].wParam, [rdx].lParam)

    mov rcx,hwnd
    .return .if ( edi != WM_KEYDOWN )

    mov rdx,msg
    mov r8,[rdx].wParam
    mov r9,[rdx].lParam
    mov edx,WM_CHAR
    .if ( r9d & RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED )
        mov edx,WM_SYSCHAR
    .endif
    [rcx].Send(edx, r8, r9)
    ret

Translate endp


TWindow::Send proc uses rcx uiMsg:uint_t, wParam:size_t, lParam:ptr

    .for ( eax = 1 : rcx : )

        .if ( [rcx].Flags & W_WNDPROC )

            .break .ifd ( [rcx].WndProc(rcx, edx, r8, r9) != 1 )

            mov rcx,this
            mov edx,uiMsg
            mov r8,wParam
            mov r9,lParam
        .endif
        .if ( [rcx].Flags & W_CHILD )
            mov rcx,[rcx].Child
        .else
            mov rcx,[rcx].Prev
        .endif
        mov this,rcx
    .endf
    ret

TWindow::Send endp


    assume r10:class_t

TWindow::Post proc uiMsg:uint_t, wParam:size_t, lParam:ptr

    .return .if !malloc(TMessage)

    mov rdx,rax
    mov [rdx].Next,0
    mov [rdx].Message,uiMsg
    mov [rdx].wParam,wParam
    mov [rdx].lParam,lParam
    mov rcx,this
    mov r10,[rcx].Class
    mov rax,rdx

    mov rdx,[r10].Message
    .for ( : rdx && [rdx].Next : rdx = [rdx].Next )

    .endf
    .if rdx
        mov [rdx].Next,rax
    .else
        mov [r10].Message,rax
    .endif
    ret

TWindow::Post endp


    assume r10:nothing

TWindow::PostQuit proc uses rcx retval:int_t

    test [rcx].Flags,W_CHILD
    cmovnz rcx,[rcx].Prev
    [rcx].Post(WM_QUIT, retval, 0)
    xor eax,eax
    ret

TWindow::PostQuit endp


    assume rdx:nothing
    assume rsi:class_t

TWindow::Register proc uses rsi rdi rbx tproc:tproc_t

  local Count:dword
  local Event:INPUT_RECORD
  local hPrev:window_t
  local IdleCount:dword
  local EventCount:dword

    mov [rcx].WndProc,rdx
    or  [rcx].Flags,W_WNDPROC
    mov IdleCount,0
    mov rsi,[rcx].Class
    mov hPrev,[rsi].Instance
    mov [rsi].Instance,rcx
    [rcx].WndProc(rcx, WM_CREATE, 0, 0)

    .while 1

        assume rdi:ptr INPUT_RECORD

        lea rdi,Event
        .if GetNumberOfConsoleInputEvents([rsi].StdIn, &EventCount)

            .while EventCount

                ReadConsoleInput([rsi].StdIn, rdi, 1, &Count)

                .break .if !Count

                .switch pascal [rdi].EventType

                  .case KEY_EVENT

                    mov edx,WM_KEYUP
                    .if [rdi].KeyEvent.bKeyDown

                        mov edx,WM_KEYDOWN
                    .endif

                    movzx   r8d,[rdi].KeyEvent.wVirtualKeyCode
                    movzx   eax,[rdi].KeyEvent.AsciiChar
                    shl     rax,56
                    or      r8,rax
                    mov     r9d,[rdi].KeyEvent.dwControlKeyState
                    movzx   eax,[rdi].KeyEvent.wVirtualScanCode
                    shl     rax,56
                    or      r9,rax
                    mov     rcx,[rsi].Instance

                    [rcx].Post(edx, r8, r9)

                  .case MOUSE_EVENT

                    mov eax,[rdi].MouseEvent.dwMousePosition
                    mov r8d,[rdi].MouseEvent.dwControlKeyState
                    shl r8,32
                    or  r8,rax

                    mov ecx,[rsi].Buttons
                    mov eax,[rdi].MouseEvent.dwButtonState
                    xor edx,edx

                    .if ( eax != ecx )
                        .if ( ( ecx & FROM_LEFT_1ST_BUTTON_PRESSED ) && \
                             !( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                            mov edx,WM_LBUTTONUP
                        .elseif ( !( ecx & FROM_LEFT_1ST_BUTTON_PRESSED ) && \
                                   ( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                            mov edx,WM_LBUTTONDOWN
                        .elseif ( ( ecx & RIGHTMOST_BUTTON_PRESSED ) && \
                                 !( eax & RIGHTMOST_BUTTON_PRESSED ) )
                            mov edx,WM_RBUTTONUP
                        .elseif ( !( ecx & RIGHTMOST_BUTTON_PRESSED ) && \
                                   ( eax & RIGHTMOST_BUTTON_PRESSED ) )
                            mov edx,WM_RBUTTONDOWN
                        .endif
                        mov [rsi].Buttons,[rdi].MouseEvent.dwButtonState
                    .else
                        .switch pascal [rdi].MouseEvent.dwEventFlags
                          .case MOUSE_MOVED    : mov edx,WM_MOUSEMOVE
                          .case MOUSE_HWHEELED : mov edx,WM_MOUSEHWHEEL
                          .case MOUSE_WHEELED  : mov edx,WM_MOUSEWHEEL
                          .case DOUBLE_CLICK
                            .if ( eax == FROM_LEFT_1ST_BUTTON_PRESSED )
                                mov edx,WM_LBUTTONDBLCLK
                            .elseif ( eax == RIGHTMOST_BUTTON_PRESSED )
                                mov edx,WM_RBUTTONDBLCLK
                            .else
                                mov edx,WM_XBUTTONDBLCLK
                            .endif
                        .endsw
                    .endif
                    .if edx
                        mov rcx,[rsi].Instance
                        mov r9d,[rsi].Buttons
                        [rcx].Post(edx, r8, r9)
                    .endif

                  .case WINDOW_BUFFER_SIZE_EVENT
                    mov rcx,[rsi].Instance
                    [rcx].Post(WM_SIZE, 0, 0)
                  .case FOCUS_EVENT
                    mov [rsi].Focus,[rdi].FocusEvent.bSetFocus
                  .case MENU_EVENT
                    mov rcx,[rsi].Instance
                    [rcx].Post([rdi].MenuEvent.dwCommandId, 0, 0)
                .endsw
                dec EventCount
            .endw
        .endif

        assume rdi:nothing

        mov rcx,[rsi].Instance
        mov rdi,[rsi].Message

        .if ( rdi == NULL || [rsi].Focus == 0 )

            inc IdleCount
            .if IdleCount >= 100

                mov IdleCount,0
                [rcx].Send(WM_ENTERIDLE, 0, 0)
            .endif
            .continue
        .endif
        mov IdleCount,0

        .break .if ( [rdi].TMessage.Message == WM_QUIT )

        Translate(rcx, rdi)
        Dispatch(rcx, rdi)
    .endw
    mov rbx,[rdi].TMessage.wParam
    Dispatch(rcx, rdi)
    [rcx].Send(WM_CLOSE, 0, 0)
    mov rcx,hPrev
    mov [rsi].Instance,rcx
    mov rax,rbx
    ret

TWindow::Register endp

WndProc proc hwnd:window_t, uiMsg:uint_t, wParam:size_t, lParam:ptr

    .switch edx
      .case WM_CREATE
        [rcx].Show()
        [rcx].SetFocus([rcx].Index)
        .return 0
      .case WM_CLOSE
        .return [rcx].Release()
    .endsw
    [rcx].DefWindowProc(edx, r8, r9)
    ret

WndProc endp

TWindow::MessageBox proc uses rsi rdi rbx rcx flags:int_t, title:string_t, format:string_t, argptr:vararg

  local width:int_t
  local line:int_t
  local size:COORD
  local rc:TRect
  local buffer[4096]:char_t

    mov rbx,rcx
    mov rdi,r8
    .if rdi == NULL
        and edx,0x00000070
        .if edx == MB_ICONERROR
            lea rdi,@CStr("Error")
        .elseif edx == MB_ICONWARNING
            lea rdi,@CStr("Warning")
        .else
            lea rdi,@CStr("")
        .endif
    .endif
    lea rsi,buffer
    mov line,0

    vsprintf(rsi, r9, &argptr)
    mov width,strlen(rdi)

    .if byte ptr [rsi]
        .repeat
            .break .if !strchr(rsi, 10)
            mov rdx,rax
            sub rdx,rsi
            lea rsi,[rax+1]
            .if edx >= width
                mov width,edx
            .endif
            inc line
        .until line == 17
    .endif
    .ifd strlen(rsi) >= width
        mov width,eax
    .endif

    mov size,[rbx].ConsoleSize()
    mov eax,width

    mov dl,2
    mov dh,76
    .if al && al < 70
        mov dh,al
        add dh,8
        mov dl,80
        sub dl,dh
        shr dl,1
    .endif
    .if dh < 48
        mov dl,16
        mov dh,48
    .endif

    mov rc.x,dl
    mov rc.y,7
    mov ecx,line
    add cl,6
    mov rc.row,cl
    mov rc.col,dh
    shr eax,16
    add al,7
    .if ax > size.y
        mov rc.y,1
    .endif

    mov r8d,W_MOVEABLE or W_COLOR or W_TRANSPARENT
    .if !( flags & MB_USERICON )
        mov r8d,W_MOVEABLE or W_COLOR or W_SHADE
    .endif
    mov rbx,[rbx].Open(rc, r8d)
    .return .if !rax

    mov rsi,[rbx].Color
    xor edx,edx
    mov dl,[rsi+BG_DIALOG]
    or  dl,[rsi+FG_DIALOG]
    mov eax,flags
    and eax,0x00000070
    .if ( eax == MB_ICONERROR || eax == MB_ICONWARNING )
        mov dl,[rsi+BG_ERROR]
        or  dl,[rsi+FG_DESKTOP]
    .endif
    .if !( [rbx].Flags & W_TRANSPARENT )
        shl edx,16
        mov dl,' '
        [rbx].Clear(edx)
    .endif
    [rbx].PutTitle(rdi)

    mov eax,[rbx].rc
    mov rc,eax
    mov al,rc.row
    mov rc.row,1
    sub al,2
    mov rc.y,al
    mov al,rc.col
    shr al,1
    mov ecx,flags
    and ecx,0x0000000F

    .switch ecx
      .case MB_OK
        sub al,4
        mov rc.x,al
        mov rc.col,6
        [rbx].PushButton(rc, IDOK, "&Ok")
        .endc
      .case MB_OKCANCEL
        sub al,10
        mov rc.x,al
        mov rc.col,6
        [rbx].PushButton(rc, IDOK, "&Ok")
        mov rc.col,10
        add rc.x,9
        [rbx].PushButton(rc, IDCANCEL, "&Cancel")
        .endc
      .case MB_ABORTRETRYIGNORE
        sub al,17
        mov rc.x,al
        mov rc.col,9
        [rbx].PushButton(rc, IDABORT, "&Abort")
        mov rc.col,9
        add rc.x,12
        [rbx].PushButton(rc, 0, "&Retry")
        mov rc.col,10
        add rc.x,12
        [rbx].PushButton(rc, IDIGNORE, "&Ignore")
        .endc
      .case MB_YESNOCANCEL
        sub al,15
        mov rc.x,al
        mov rc.col,7
        [rbx].PushButton(rc, IDYES, "&Yes")
        mov rc.col,6
        add rc.x,10
        [rbx].PushButton(rc, IDNO, "&No")
        mov rc.col,10
        add rc.x,9
        [rbx].PushButton(rc, IDCANCEL, "&Cancel")
        .endc
      .case MB_YESNO
        sub al,10
        mov rc.x,al
        mov rc.col,7
        [rbx].PushButton(rc, IDYES, "&Yes")
        mov rc.col,6
        add rc.x,10
        [rbx].PushButton(rc, IDNO, "&No")
        .endc
      .case MB_RETRYCANCEL
        sub al,8
        mov rc.x,al
        mov rc.col,10
        [rbx].PushButton(rc, IDRETRY, "&Retry")
        mov rc.col,10
        add rc.x,13
        [rbx].PushButton(rc, IDCANCEL, "&Cancel")
        .endc
      .case MB_CANCELTRYCONTINUE
        sub al,21
        mov rc.x,al
        mov rc.col,10
        [rbx].PushButton(rc, IDCANCEL, "&Cancel")
        mov rc.col,13
        add rc.x,13
        [rbx].PushButton(rc, IDTRYAGAIN, "&Try Again")
        mov rc.col,12
        add rc.x,16
        [rbx].PushButton(rc, IDCONTINUE, "C&ontinue")
        .endc
    .endsw

    mov eax,flags
    and eax,0x00000300
    mov rcx,[rbx].Child
    .switch eax
      .case MB_DEFBUTTON4 : mov rcx,[rcx].Child
      .case MB_DEFBUTTON3 : mov rcx,[rcx].Child
      .case MB_DEFBUTTON2 : mov rcx,[rcx].Child
    .endsw
    mov [rbx].Index,[rcx].Index

    lea rsi,buffer
    mov rdi,rsi
    mov line,2

    .repeat

        .break .if !byte ptr [rsi]

        mov rsi,strchr(rdi, 10)
        .if ( rax != NULL )
            mov byte ptr [rsi],0
            inc rsi
        .endif

        movzx r9d,[rbx].rc.col
        movzx edx,[rbx].rc.x
        [rbx].PutCenter(0, line, r9d, rdi)
        mov rdi,rsi
        inc line

    .until (rdi == NULL || line == 17+2)

    [rbx].Register(&WndProc)
    ret

TWindow::MessageBox endp

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

TWindow::TWindow proc public uses rsi rdi rbx

  local ci: CONSOLE_SCREEN_BUFFER_INFO

    mov rdi,rcx
    mov rbx,@ComAlloc(TWindow)
    .if rdi
        stosq
    .endif
    .return .if !rax
    mov [rbx].Class,malloc(TClass)
    mov rdi,rax
    mov ecx,TClass / 8
    xor eax,eax
    rep stosq

    lea rax,AttributesDefault
    mov [rbx].Color,rax
    mov rsi,GetStdHandle(STD_OUTPUT_HANDLE)

    mov edi,0x00190050
    .if GetConsoleScreenBufferInfo(rsi, &ci)
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
    mov [rdi].StdOut,rsi
    mov [rdi].ErrMode,SetErrorMode(SEM_FAILCRITICALERRORS)

    GetConsoleMode([rdi].StdIn, &[rdi].ConMode)
    SetConsoleMode([rdi].StdIn, ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
    FlushConsoleInputBuffer([rdi].StdIn)
    [rbx].Read(&[rbx].rc, [rbx].Window)

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

        .for ( rcx = [rbx].Prev : rcx && [rcx].Child != rbx : rcx = [rcx].Child )
        .endf
        .if rcx
            mov [rcx].Child,[rbx].Child
        .endif
        mov [rbx].Child,rax

    .elseif ( rax == [rbx].Prev )

        mov rax,[rbx].Class
        SetConsoleMode([rax].TClass.StdIn, [rax].TClass.ConMode)
        mov rax,[rbx].Class
        SetErrorMode([rax].TClass.ErrMode)
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

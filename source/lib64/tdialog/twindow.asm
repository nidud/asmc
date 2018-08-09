include malloc.inc
include tdialog.inc

    .data

    virtual_table label qword
        dq TWindow_Release
        dq TWindow_Show
        dq TWindow_Hide
        dq TWindow_Move
        dq TWindow_Read
        dq TWindow_Write
        dq TWindow_Exchange
        dq TWindow_Setshade
        dq TWindow_Clearshade
        dq TWindow_Getshadeptr
        dq TWindow_Readshade
        dq TWindow_Alloc
        dq TWindow_Windowsize
        dq TWindow_Xyrow
        dq TWindow_Inside
        dq TWindow_Winoffset
        dq TWindow_OPutw
        dq TWindow_OPutfg
        dq TWindow_OPutbg
        dq TWindow_OPuts
        dq TWindow_OPutsEx
        dq TWindow_OPath
        dq TWindow_OCenter

    .code

    assume rcx: ptr TWindow

TWindow::TWindow proc

    .if malloc( sizeof(TWindow) )

        mov rcx,rax
        lea rdx,virtual_table
        mov [rcx],rdx
        xor edx,edx
        mov [rcx].flags,_TW_ISOPEN
        mov [rcx].rc,edx
        mov [rcx].window,rdx
    .endif
    mov r8,_this
    .if r8
        mov [r8],rax
    .endif
    ret

TWindow::TWindow endp

TWindow::Release proc

    .if [rcx].flags & _TW_ISOPEN

        .if [rcx].flags & _TW_VISIBLE

            [rcx].Hide()
        .endif
        free( [rcx].window )
    .endif
    free(_this)
    ret

TWindow::Release endp

TWindow::Windowsize proc

    movzx   eax,[rcx].rc.col
    movzx   edx,[rcx].rc.row
    mov     r8d,eax
    mul     dl
    lea     eax,[eax*4]

    .if [rcx].flags & _TW_USESHADE

        lea r8d,[r8d+edx*4-4]
        add eax,r8d
    .endif
    ret

TWindow::Windowsize endp

TWindow::Alloc proc

    malloc([rcx].Windowsize())
    mov rcx,_this
    mov [rcx].window,rax
    ret

TWindow::Alloc endp

TWindow::Read proc uses rsi rdi

  local rc:TRECT

    mov eax,[rcx].rc
    mov rc,eax
    lea rdi,[rcx].window

    .for : rc.row : rc.row--, rc.y++

        mov rsi,Console.Getrectptr(rc)
        movzx ecx,rc.col
        rep movsd
    .endf
    mov rcx,_this
    ret

TWindow::Read endp

TWindow::Write proc uses rsi rdi

  local rc:TRECT

    mov eax,[rcx].rc
    mov rc,eax
    lea rsi,[rcx].window

    .for : rc.row : rc.row--, rc.y++

        mov rdi,Console.Getrectptr(rc)
        movzx ecx,rc.col
        rep movsd
    .endf
    mov rcx,_this
    ret

TWindow::Write endp

TWindow::Exchange proc uses rsi rdi

  local rc:TRECT

    mov eax,[rcx].rc
    mov rc,eax
    lea rsi,[rcx].window

    .for : rc.row : rc.row--, rc.y++

        mov rdi,Console.Getrectptr(rc)
        movzx ecx,rc.col
        .repeat
            mov eax,[rdi]
            movsd
            mov [rsi-4],eax
        .untilcxz
    .endf
    mov rcx,_this
    ret

TWindow::Exchange endp

TWindow::Getshadeptr proc

    movzx eax,[rcx].rc.col
    mul [rcx].rc.row
    lea rax,[rax*4]
    add rax,[rcx].window
    ret

TWindow::Getshadeptr endp

TWindow::Readshade proc uses rsi rdi

  local rc:TRECT

    mov eax,[rcx].rc
    mov rc,eax
    mov al,rc.col
    add rc.x,al
    inc rc.y

    .for rdi=[rcx].Getshadeptr() : rc.row : rc.row--, rc.y++

        mov rsi,Console.Getrectptr(rc)
        movsq
    .endf
    movzx ecx,rc.col
    lea eax,[ecx*4]
    sub rsi,rax
    sub ecx,2
    rep movsd
    mov rcx,_this
    ret

TWindow::Readshade endp

TWindow::Setshade proc

  local rc:TRECT

    [rcx].Readshade()

    mov eax,[rcx].rc
    mov rc,eax
    mov al,rc.col
    add rc.x,al
    inc rc.y

    .for : rc.row : rc.row--, rc.y++
        Console.Getrectptr(rc)
        mov byte ptr [rax+3],0x8
        mov byte ptr [rax+7],0x8
    .endf

    movzx ecx,rc.col
    lea rdx,[rcx*4]
    sub rax,rdx

    .for( rax+=3, ecx-=2 : ecx : ecx--, rax+=4 )
        mov byte ptr [rax],0x8
    .endf
    mov rcx,_this
    ret

TWindow::Setshade endp

TWindow::Clearshade proc uses rsi rdi

  local rc:TRECT

    mov eax,[rcx].rc
    mov rc,eax
    mov al,rc.col
    add rc.x,al
    inc rc.y

    .for rsi=[rcx].Getshadeptr() : rc.row : rc.row--, rc.y++

        mov rdi,Console.Getrectptr(rc)
        movsq
    .endf
    movzx ecx,rc.col
    lea eax,[ecx*4]
    sub rdi,rax
    sub ecx,2
    rep movsd
    mov rcx,_this
    ret

TWindow::Clearshade endp

TWindow::Show proc

    .repeat

        mov eax,[rcx].flags
        and eax,_TW_ISOPEN or _TW_VISIBLE
        .break .ifz

        .if !( eax & _TW_VISIBLE )

            [rcx].Exchange()
            .if [rcx].flags & _TW_USESHADE

                [rcx].Setshade()
            .endif
            or [rcx].flags,_TW_VISIBLE
        .endif
        mov eax,1
    .until 1
    ret

TWindow::Show endp

TWindow::Hide proc

    .repeat

        mov eax,[rcx].flags
        and eax,_TW_ISOPEN or _TW_VISIBLE
        .break .ifz

        .if eax & _TW_VISIBLE

            [rcx].Exchange()
            .if [rcx].flags & _TW_USESHADE

                [rcx].Clearshade()
            .endif
            and [rcx].flags,not _TW_VISIBLE
        .endif
        mov eax,1
    .until 1
    ret

TWindow::Hide endp

TWindow::Move proc x:SINT, y:SINT

    .ifd [rcx].Hide()

        mov al,byte ptr x
        mov [rcx].rc.x,al
        mov al,byte ptr y
        mov [rcx].rc.y,al
        [rcx].Show()
        mov eax,1
    .endif
    ret

TWindow::Move endp

TWindow::Xyrow proc x:SINT, y:SINT

    mov al,r8b
    mov ah,dl
    mov dl,[rcx].rc.x
    mov dh,[rcx].rc.y
    .repeat
        .if ah >= dl && al >= dh
            add dl,[rcx].rc.col
            .if ah < dl
                mov ah,dh
                add dh,[rcx].rc.row
                .if al < dh
                    sub al,ah
                    inc al
                    movzx eax,al
                    .break
                .endif
            .endif
        .endif
        xor eax,eax
    .until 1
    ret

TWindow::Xyrow endp

TWindow::Inside proc rc:TRECT

    xor r8d,r8d
    mov ax,word ptr [rcx].rc[2]
    mov dx,word ptr rc[2]
    .if dh > ah || dl > al
        mov r8d,5
    .else
        add ax,word ptr [rcx].rc
        add dx,word ptr rc
        .if ah < dh
            inc r8d
        .elseif al < dl
            mov r8d,4
        .else
            mov ax,word ptr [rcx].rc
            mov dx,word ptr rc
            .if ah > dh
                mov r8d,2
            .elseif al > dl
                mov r8d,3
            .endif
        .endif
    .endif
    mov eax,r8d
    ret

TWindow::Inside endp

TWindow::Winoffset proc x:SINT, y:SINT

    movzx eax,[rcx].rc.col
    imul  eax,r8d
    add   eax,edx
    ret

TWindow::Winoffset endp

TWindow::OPutw proc uses rdi o:UINT, l:UINT, w:UINT

    lea edi,[edx*4]
    add rdi,[rcx].window
    mov eax,r9d
    mov r10,rcx
    mov ecx,r8d
    .if eax & 0xFFFF0000
        rep stosw
    .else
        .repeat
            stosw
            add rdi,2
        .untilcxz
    .endif
    mov rcx,r10
    ret

TWindow::OPutw endp

TWindow::OPutfg proc o:UINT, l:UINT, a:BYTE

    lea r11,[rdx*4]
    add r11,[rcx].window
    add r11,2
    .repeat
        and byte ptr [r11],0xF0
        or  byte ptr [r11],r9b
        add r11,4
        dec r8d
    .until !r8d
    ret

TWindow::OPutfg endp

TWindow::OPutbg proc o:UINT, l:UINT, a:BYTE

    lea r11,[rdx*4]
    add r11,[rcx].window
    add r11,2
    .repeat
        and byte ptr [r11],0x0F
        or  byte ptr [r11],r9b
        add r11,4
        dec r8d
    .until !r8d
    ret

TWindow::OPutbg endp

TWindow::OPuts proc uses rsi rdi rbx o:UINT, l:UINT, string:LPSTR

    lea rdi,[rdx*4]
    add rdi,[rcx].window
    mov rsi,r9
    .if !r8d
        dec r8d
    .endif

    movzx edx,[rcx].rc.col
    lea rdx,[rdx*4]
    mov rbx,rdi

    .while 1

        lodsb
        .switch al
          .case 0
            .break
          .case 10
            add rbx,rdx
            mov rdi,rbx
            .continue
          .case 9
            add rdi,4*4
            .continue
        .endsw
        mov [rdi],al
        add rdi,4
        dec r8d
        .break .ifz
    .endw
    ret

TWindow::OPuts endp

TWindow::OPutsEx proc uses rsi rdi rbx o:UINT, l:UINT, Attrib:BYTE, HighColor:BYTE, string:LPSTR

    lea rdi,[rdx*4]
    add rdi,[rcx].window
    mov rsi,string
    .if !r8d
        dec r8d
    .endif

    movzx edx,[rcx].rc.col
    lea rdx,[rdx*4]
    mov rbx,rdi
    mov ah,HighColor

    .while 1

        lodsb
        .switch al
          .case 0
            .break
          .case 10
            add rbx,rdx
            mov rdi,rbx
            .continue
          .case 9
            add rdi,4*4
            .continue
          .case '&'
            .if ah
                lodsb
                mov [rdi],al
                mov [rdi+2],ah
                add rdi,4
                .endc
            .endif
          .default
            mov [rdi],al
            .if r9b
                mov [rdi+2],r9b
            .endif
            add rdi,4
        .endsw
        dec r8d
        .break .ifz
    .endw
    ret

TWindow::OPutsEx endp

TWindow::OPath proc uses rsi rdi rbx o:UINT, l:UINT, string:LPSTR

    mov rsi,r9
    mov rbx,r8
    lea rdi,[rdx*4]
    add rdi,[rcx].window

    strlen(rsi)
    .repeat

        .break .if eax <= ebx

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
    .until 1
    .while eax
        movsb
        add rdi,3
        dec eax
    .endw
    mov rcx,_this
    ret

TWindow::OPath endp

TWindow::OCenter proc uses rsi rdi rbx o:UINT, l:UINT, string:LPSTR

    mov rsi,r9
    mov rbx,r8
    lea rdi,[rdx*4]
    add rdi,[rcx].window

    strlen(rsi)
    mov r8,rdi

    .repeat

        .break .if eax <= ebx

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
    .until 1
    .if eax
        .if rdi == r8
            sub ebx,eax
            shr ebx,2
            lea rdi,[rdi+rbx*8]
        .endif
        .repeat
            movsb
            add rdi,3
        .untilaxz
    .endif
    mov rcx,_this
    ret

TWindow::OCenter endp

    end

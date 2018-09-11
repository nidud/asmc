include Balls.inc
include malloc.inc
include stdlib.inc
include winbase.inc

    .data

    virtual_table label qword
        dq Graphics_Release
        dq Graphics_Setsize
        dq Graphics_Update
        dq Graphics_Getmaxx
        dq Graphics_Getmaxy
        dq Graphics_Setrgb
        dq Graphics_Initpal
        dq Graphics_Circle
        dq Graphics_Initballs
        dq Graphics_Moveballs
        dq Graphics_Hideballs
        dq Graphics_Suspend
        dq Graphics_Resume

    .code

RAND_MAX equ 0x7FFF

random proc base:UINT

    rand()
    mul base
    mov ecx,RAND_MAX+1
    xor edx,edx
    div ecx
    ret

random endp

    assume rcx:LPGRAPHICS
    option win64:rsp nosave noauto

Graphics::Update proc
    or [rcx].flags,_G_UPDATE
    ret
Graphics::Update endp

Graphics::Suspend proc
    or [rcx].flags,_G_SUSPENDED
    Sleep(8)
    ret
Graphics::Suspend endp

Graphics::Resume proc
    and [rcx].flags,not _G_SUSPENDED
    ret
Graphics::Resume endp

Graphics::Getmaxx proc
    mov eax,[rcx].bmi.bmiHeader.biWidth
    ret
Graphics::Getmaxx endp

Graphics::Getmaxy proc
    mov eax,[rcx].bmi.bmiHeader.biHeight
    neg eax
    ret
Graphics::Getmaxy endp

Graphics::Setrgb proc x:UINT, y:UINT, id:UINT

    .repeat
        xor eax,eax
        mov r11d,[rcx].bmi.bmiHeader.biWidth
        mov r10d,[rcx].bmi.bmiHeader.biHeight
        neg r10d
        .break .if edx >= r11d
        .break .if r8d >= r10d
        mov r10d,edx
        mov eax,r11d
        mul r8d
        add eax,r10d
        lea r10,[rax+rax*2]
        add r10,[rcx].winptr
        mov eax,[rcx].palett[r9*4]
        mov [r10],ax
        shr eax,16
        mov [r10+2],al
    .until 1
    ret
Graphics::Setrgb endp

Graphics::Initpal proc
    xor r8d,r8d
    lea r9,[rcx].palett
    assume r9:LPRGBQUAD
    .repeat
        imul eax,r8d,2+5
        mov [r9].rgbRed,0       ; blue
        mov [r9].rgbGreen,0
        mov [r9].rgbBlue,al
        lea rdx,[r8+30]
        imul eax,edx,2-56       ; read
        mov [r9+30*4].rgbRed,al
        mov [r9+30*4].rgbGreen,0
        mov [r9+30*4].rgbBlue,0
        lea rdx,[r8+60]
        imul eax,edx,2-56
        mov [r9+60*4].rgbRed,0   ; green
        mov [r9+60*4].rgbGreen,al
        mov [r9+60*4].rgbBlue,0
        lea rdx,[r8+90]
        imul eax,edx,2-47
        mov [r9+90*4].rgbRed,al
        mov [r9+90*4].rgbGreen,al
        mov [r9+90*4].rgbBlue,0
        lea rdx,[r8+120]
        imul eax,edx,2-45
        mov [r9+120*4].rgbRed,al
        mov [r9+120*4].rgbGreen,0
        mov [r9+120*4].rgbBlue,al
        lea rdx,[r8+150]
        imul eax,edx,2-40
        mov [r9+150*4].rgbRed,0
        mov [r9+150*4].rgbGreen,al
        mov [r9+150*4].rgbBlue,al
        lea rdx,[r8+180]
        imul eax,edx,2-40
        mov [r9+180*4].rgbRed,al
        mov [r9+180*4].rgbGreen,0
        mov [r9+180*4].rgbBlue,0
        add r9,sizeof(RGBQUAD)
        inc r8d
    .until r8d == 30
    assume r9:nothing
    ret
Graphics::Initpal endp

    assume rsi:LPGRAPHICS
    option win64:rbp

    asp_ratio equ 11

Graphics::DrawDelta proc uses rsi rdi rbx x_centre:UINT, y_centre:UINT, colour:UINT,
  x:UINT, y:UINT, delta:SINT

  local startx:UINT, endx:UINT, starty:UINT, endy:UINT

    mov rsi,rcx
    mov ebx,y
    mov eax,asp_ratio
    mul ebx
    sub edx,edx
    mov ecx,10
    div ecx
    mov starty,eax
    inc ebx
    mov eax,asp_ratio
    mul ebx
    sub edx,edx
    div ecx
    mov endy,eax
    mov eax,asp_ratio
    mov ebx,x
    mul ebx
    sub edx,edx
    div ecx
    mov startx,eax
    inc ebx
    mov eax,asp_ratio
    mul ebx
    sub edx,edx
    div ecx
    mov endx,eax
    mov edi,startx
    mov ebx,colour

    .while edi < endx

        inc edi

        mov edx,edi
        add edx,x_centre
        mov r8d,y
        add r8d,y_centre
        [rsi].Setrgb(edx, r8d, ebx)
        mov edx,edi
        add edx,x_centre
        mov r8d,y_centre
        sub r8d,y
        [rsi].Setrgb(edx, r8d, ebx)
        mov edx,x_centre
        sub edx,edi
        mov r8d,y_centre
        sub r8d,y
        [rsi].Setrgb(edx, r8d, ebx)
        mov edx,x_centre
        sub edx,edi
        mov r8d,y_centre
        add r8d,y
        [rsi].Setrgb(edx, r8d, ebx)
    .endw

    mov edi,starty
    .while edi < endy

        inc edi

        mov edx,edi
        add edx,x_centre
        mov r8d,x
        add r8d,y_centre
        [rsi].Setrgb(edx, r8d, ebx)
        mov edx,edi
        add edx,x_centre
        mov r8d,y_centre
        sub r8d,x
        [rsi].Setrgb(edx, r8d, ebx)
        mov edx,x_centre
        sub edx,edi
        mov r8d,y_centre
        sub r8d,x
        [rsi].Setrgb(edx, r8d, ebx)
        mov edx,x_centre
        sub edx,edi
        mov r8d,y_centre
        add r8d,x
        [rsi].Setrgb(edx, r8d, ebx)
    .endw
    ret

Graphics::DrawDelta endp

Graphics::Circle proc uses rsi rdi rbx r12 x_centre:UINT, y_centre:UINT, radius:UINT, colour:UINT

    mov rsi,rcx
    mov eax,r9d    ; radius
    mov edi,r9d
    add eax,eax
    mov ebx,3
    sub ebx,eax
    xor r12d,r12d

    .while r12d < edi

        Graphics::DrawDelta(rsi, x_centre, y_centre, colour, r12d, edi, ebx)
        .ifs ebx < 0
            lea rax,[r12*4+6]
            add ebx,eax
        .else
            mov eax,r12d
            sub eax,edi
            lea rbx,[rbx+rax*4+10]
            dec edi
        .endif
        inc r12d
    .endw
    .if edi

        Graphics::DrawDelta(rsi, x_centre, y_centre, colour, r12d, edi, ebx)
    .endif
    ret

Graphics::Circle endp

Graphics::Setsize proc uses rsi rdi max_x:UINT, max_y:UINT

    and r8d,-4
    and edx,-4
    mov eax,r8d
    mov [rcx].bmi.bmiHeader.biWidth,edx
    neg r8d
    mov [rcx].bmi.bmiHeader.biHeight,r8d
    mov rsi,rcx
    mul edx
    lea rdi,[rax+rax*2]
    realloc([rcx].winptr, rdi)
    mov [rsi].winptr,rax
    mov ecx,edi
    mov rdi,rax
    xor eax,eax
    rep stosb
    [rsi].Initballs()
    mov rax,rsi
    ret

Graphics::Setsize endp

Graphics::Initballs proc uses rsi rdi rbx r12 r13

    mov rsi,rcx
    lea rbx,[rcx].balls
    mov rax,[rbx]

    .if !rax

        .for edi = 0: edi < MAXBALLS: edi++, rbx += size_t

            Balls::Balls( rbx )
        .endf
        lea rbx,[rsi].balls
    .endif

    mov r12d,[rsi].bmi.bmiHeader.biWidth
    mov r13d,[rsi].bmi.bmiHeader.biHeight
    neg r13d

    .for edi = 0: edi < MAXBALLS: edi++

        assume r8:ptr Balls
        mov r8,[rbx+rdi*8]
        mov [r8].sx,6
        mov [r8].sy,6
        mov [r8].prevx,6
        mov [r8].prevy,6
        lea rax,[r12-6]
        mov [r8].ex,eax
        lea rax,[r13-3]
        mov [r8].ey,eax
        random(r12d)
        add eax,60
        mov r8,[rbx+rdi*8]
        mov [r8].xpos,eax
        random(r13d)
        add eax,50
        mov r8,[rbx+rdi*8]
        mov [r8].ypos,eax
        mov ecx,r13d
        shr ecx,4
        random(ecx)
        add eax,6
        mov r8,[rbx+rdi*8]
        mov [r8].rad,eax
        random(160)
        add eax,2
        mov r8,[rbx+rdi*8]
        mov [r8].color,eax
        random(4)
        mov r8,[rbx+rdi*8]
        mov [r8].speed,eax

    .endf
    mov rax,rsi
    ret

Graphics::Initballs endp

Graphics::Moveballs proc uses rsi rdi rbx

    mov rsi,rcx
    lea rbx,[rcx].balls
    mov rax,[rbx]
    .if rax

        .for edi = 0: edi < MAXBALLS: edi++

            mov r8,[rbx+rdi*8]
            [r8].Move()
        .endf
    .endif
    ret

Graphics::Moveballs endp

Graphics::Hideballs proc uses rsi rdi rbx

    mov rsi,rcx
    lea rbx,[rcx].balls
    mov rax,[rbx]
    .if rax

        .for edi = 0: edi < MAXBALLS: edi++

            mov r8,[rbx+rdi*8]
            [r8].Hide()
        .endf
    .endif
    ret

Graphics::Hideballs endp

    assume r8:nothing

Graphics::Graphics proc uses rsi rdi rbx

    .repeat
        mov rbx,rcx
        .break .if !malloc( sizeof(Graphics) )
        mov rcx,rax
        mov rsi,rcx
        mov rdi,rcx
        mov ecx,sizeof(Graphics)
        xor eax,eax
        rep stosb
        lea rax,virtual_table
        mov [rsi].lpVtbl,rax
        mov [rsi].bmi.bmiHeader.biSize,40
        mov [rsi].bmi.bmiHeader.biPlanes,1
        mov [rsi].bmi.bmiHeader.biBitCount,24
        [rsi].Initpal()
        mov rax,rsi
        .if rbx
            mov [rbx],rax
        .endif
    .until 1
    ret

Graphics::Graphics endp

Graphics::Release proc uses rsi
    mov rsi,rcx
    free([rcx].winptr)
    free(rsi)
    ret
Graphics::Release endp

    end

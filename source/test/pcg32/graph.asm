WIN32_LEAN_AND_MEAN equ 1
include windows.inc
include malloc.inc
include graph.inc
include stdlib.inc

    .data
    g LPGRAPHICS 0

    virtual_table GraphicsVtbl { \
        Graphics_Release,
        Graphics_Setsize,
        Graphics_Update,
        Graphics_Getmaxx,
        Graphics_Getmaxy,
        Graphics_Setrgb,
        Graphics_Initpal,
        Graphics_Suspend,
        Graphics_Resume,
        Graphics_Line,
        Graphics_InitObjects,
        Graphics_MoveObjects,
        Graphics_HideObjects }

    .code

    option win64:rsp nosave noauto

    assume rcx:LPGRAPHICS

Graphics::Update proc

    lock or [rcx].flags,_G_UPDATE
    ret

Graphics::Update endp


Graphics::Suspend proc

    lock or [rcx].flags,_G_SUSPENDED
    Sleep(8)
    ret

Graphics::Suspend endp


Graphics::Resume proc

    lock and [rcx].flags,not _G_SUSPENDED
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

Graphics::Line proc uses rsi rdi rbx x:UINT, y:UINT, x2:UINT, y2:UINT, rgb:UINT

  local u       :SINT,
        v       :SINT,
        d1x     :SINT,
        d1y     :SINT,
        d2x     :SINT,
        d2y     :SINT,
        m       :SINT,
        n       :SINT,
        s       :REAL8

    mov rsi,rcx

    mov eax,y2
    sub eax,y
    mov v,eax

    mov eax,x2
    sub eax,x
    mov u,eax

    .if !eax

        mov d1x,eax
        mov m,eax

    .else

        mov     ecx,eax
        neg     eax
        test    ecx,ecx
        cmovns  eax,ecx
        mov     m,eax

        .if (u < 0)

            mov d1x,-1

        .elseif (u > 0)

            mov d1x,1

        .endif
    .endif

    mov eax,v
    .if !eax

        mov d1y,eax
        mov n,eax

    .else

        mov     ecx,eax
        neg     eax
        test    ecx,ecx
        cmovns  eax,ecx
        mov     n,eax

        .if (v < 0)

            mov d1y,-1

        .elseif (v > 0)

            mov d1y,1

        .endif
    .endif

    mov eax,n

    .if ( m > eax )

        mov eax,d1x
        mov d2x,eax
        mov d2y,0

    .else

        mov d2x,0
        mov m,eax
        mov eax,d1y
        mov d2y,eax

        mov     eax,u
        mov     ecx,eax
        neg     eax
        test    ecx,ecx
        cmovns  eax,ecx
        mov     n,eax

    .endif

    mov     eax,m
    cvtsi2sd xmm0,rax
    mov     rax,2.0
    movq    xmm1,rax
    divsd   xmm0,xmm1
    movsd   s,xmm0


    .for (ebx = 0: ebx <= m: ebx++)

        [rsi].Setrgb(x, y, rgb)

        movsd   xmm0,s
        mov     eax,n
        cvtsi2sd xmm1,rax
        addsd   xmm0,xmm1
        movsd   s,xmm0
        mov     eax,m
        cvtsi2sd xmm1,rax
        comisd  xmm0,xmm1

        .ifnb

            subsd xmm0,xmm1
            movsd s,xmm0

            mov eax,d1x
            add x,eax
            mov eax,d1y
            add y,eax

        .else

            mov eax,d2x
            add x,eax
            mov eax,d2y
            add y,eax

        .endif
    .endf
    ret

Graphics::Line endp

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
    [rsi].InitObjects()
    mov rax,rsi
    ret

Graphics::Setsize endp

Graphics::InitObjects proc uses rsi rdi rbx r12 r13 r14

    mov rsi,rcx
    lea rbx,[rcx].object
    mov rax,[rbx]

    .if !rax

        .for ( edi = 0: edi < MAXOBJECTS: edi++, rbx += size_t )

            Object_Object( rbx )
        .endf
        lea rbx,[rsi].object
    .endif

    mov rax,[rbx]
    [rax].Object.random(MAXOBJECTS)
    mov [rsi].bcount,eax

    .for ( edi = 0: edi < [rsi].bcount: edi++ )

        mov edx,[rsi].bmi.bmiHeader.biWidth
        mov r8d,[rsi].bmi.bmiHeader.biHeight
        neg r8d
        mov rcx,[rbx+rdi*8]
        [rcx].Object.Init(edx, r8d)

    .endf
    mov rax,rsi
    ret

Graphics::InitObjects endp

Graphics::MoveObjects proc uses rsi rdi rbx

    mov rsi,rcx
    lea rbx,[rcx].object
    mov rax,[rbx]
    .if rax

        .for edi = 0: edi < [rsi].bcount: edi++

            mov rcx,[rbx+rdi*8]
            [rcx].Object.Move()
        .endf
    .endif
    ret

Graphics::MoveObjects endp


Graphics::HideObjects proc uses rsi rdi rbx

    mov rsi,rcx
    lea rbx,[rcx].object
    mov rax,[rbx]
    .if rax

        .for edi = 0: edi < [rsi].bcount: edi++

            mov rcx,[rbx+rdi*8]
            [rcx].Object.Hide()
        .endf
    .endif
    ret

Graphics::HideObjects endp


Graphics::Graphics proc uses rsi rdi rbx

    .repeat

        mov rbx,rcx

        .break .if !malloc( sizeof(Graphics) )

        mov rsi,rax
        mov rdi,rax

        mov ecx,sizeof(Graphics)/8
        xor eax,eax
        rep stosq

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


Graphics::Release proc uses rsi rdi rbx

    mov rsi,rcx
    lea rbx,[rcx].object
    mov rax,[rbx]
    .if rax

        .for ( edi = 0: edi < [rsi].bcount: edi++ )

            mov r8,[rbx+rdi*8]
            [r8].Object.Release()
        .endf
    .endif

    free( [rsi].winptr )
    free( rsi )
    ret

Graphics::Release endp

    end

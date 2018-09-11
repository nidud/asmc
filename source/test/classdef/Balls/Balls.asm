include Balls.inc
include malloc.inc

    .data

    virtual_table label qword
        dq Balls_Release
        dq Balls_Hide
        dq Balls_Show
        dq Balls_Move

    .code

    option win64:nosave
    assume rcx:LPBALLS
    assume rsi:LPBALLS

Balls::Hide proc uses rsi rdi

    .for ( rsi=rcx, edi=[rcx].rad: edi: edi-- )

        g.Circle([rsi].xpos, [rsi].ypos, edi, 0)
        mov edx,[rsi].xpos
        inc edx
        g.Circle(edx, [rsi].ypos, edi, 0)
        mov edx,[rsi].xpos
        dec edx
        g.Circle(edx, [rsi].ypos, edi, 0)
    .endf
    ret

Balls::Hide endp

Balls::Show proc uses rsi rdi rbx

    .for ( rsi=rcx, edi=[rcx].rad, ebx=[rsi].color: edi: edi-- )

        g.Circle([rsi].xpos, [rsi].ypos, edi, ebx)
        mov edx,[rsi].xpos
        inc edx
        g.Circle(edx, [rsi].ypos, edi, ebx)
        mov edx,[rsi].xpos
        dec edx
        g.Circle(edx, [rsi].ypos, edi, ebx)
    .endf
    ret

Balls::Show endp

Balls::Move proc uses rsi rdi rbx

    mov rsi,rcx

    [rcx].Hide()

    mov ecx,[rsi].speed
    mov eax,[rsi].xpos
    mov edx,[rsi].prevx
    mov r8d,[rsi].ypos
    mov r9d,[rsi].prevy
    inc ecx

    .if edx > eax
        mov edx,eax
        sub eax,ecx
    .endif
    .if edx < eax
        mov edx,eax
        add eax,ecx
    .endif
    .if r9d > r8d
        mov r9d,r8d
        sub r8d,ecx
    .endif
    .if r9d < r8d
        mov r9d,r8d
        add r8d,ecx
    .endif

    mov [rsi].xpos,eax
    mov [rsi].ypos,r8d
    mov ebx,[rsi].rad
    add eax,ebx
    add r8d,ebx
    .if eax >= [rsi].ex
        add edx,ecx
    .endif
    .if r8d >= [rsi].ey
        add r9d,ecx
    .endif
    add ebx,ebx
    sub eax,ebx
    sub r8d,ebx
    .if eax <= [rsi].sx
        sub edx,ecx
    .endif
    .if r8d <= [rsi].sy
        sub r9d,ecx
        inc [rsi].setcolor
    .endif
    mov [rsi].prevx,edx
    mov [rsi].prevy,r9d

    .if [rsi].setcolor == 7
        inc [rsi].color
        .if [rsi].color > 250
            mov [rsi].color,2
        .endif
        mov [rsi].setcolor,0
    .endif
    mov eax,[rsi].xpos
    .if eax <= [rsi].sx || eax >= [rsi].ex
        mov eax,[rsi].sx
        add eax,[rsi].rad
        mov [rsi].xpos,eax
    .endif
    mov eax,[rsi].ypos
    .if eax <= [rsi].sy || eax >= [rsi].ey
        mov eax,[rsi].sy
        add eax,[rsi].rad
        mov [rsi].ypos,eax
    .endif
    [rsi].Show()
    ret
Balls::Move endp

Balls::Balls proc uses rdi rbx

    .repeat
        mov rbx,rcx
        .break .if !malloc( sizeof(Balls) )
        mov rdx,rax
        mov rdi,rax
        mov ecx,sizeof(Balls)
        xor eax,eax
        rep stosb
        mov rcx,rdx
        lea rax,virtual_table
        mov [rcx].lpVtbl,rax
        mov rax,rcx
        .if rbx
            mov [rbx],rax
        .endif
    .until 1
    ret

Balls::Balls endp

Balls::Release proc
    free(rcx)
    ret
Balls::Release endp

    end

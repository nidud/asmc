include malloc.inc
include wingdi.inc
include graph.inc
include pcg_basic.inc

    .data
    vtable ObjectVtbl { free, Object_Hide, Object_Show, Object_Move, Object_Init, Object_Draw }

    .code

    option win64:nosave
    assume rcx:ptr Object

Object::Object proc uses rdi rbx

    .repeat

        mov rbx,rcx

        .break .if !malloc( sizeof(Object) )

        mov rdx,rax
        mov rdi,rax
        mov ecx,sizeof(Object)/8
        xor eax,eax
        rep stosq

        mov rcx,rdx
        lea rax,vtable
        mov [rcx].lpVtbl,rax
        lea rax,pcg32_boundedrand
        mov [rcx].random,rax
        mov rax,rcx
        .if rbx
            mov [rbx],rax
        .endif
    .until 1
    ret

Object::Object endp

    assume rbx:ptr Object

Object::Init proc uses rsi rdi rbx xWidth:UINT, Height:UINT

    mov rbx,rcx

    mov [rbx].rc.left,6
    mov [rbx].rc.top,6
    lea rax,[rdx-6]
    mov [rbx].rc.right,eax
    lea rax,[r8-3]
    mov [rbx].rc.bottom,eax

    mov esi,edx
    mov edi,r8d

    lea rax,[[rbx].random(esi)+60]
    mov [rbx].pos.x,eax
    lea rax,[[rbx].random(edi)+50]
    mov [rbx].pos.y,eax

    [rbx].random(edi)
    mov [rbx].old.y,eax
    [rbx].random(esi)
    mov [rbx].old.x,eax

    mov ecx,edi
    shr ecx,4
    lea rax,[[rbx].random(ecx)+6]
    mov [rbx].radius,eax

    lea rax,[[rbx].random(160)+2]
    mov [rbx].color,eax

    [rbx].random(8)
    mov [rbx].speed,eax

    mov rax,rbx
    ret

Object::Init endp

    option win64:save

Object::Draw proc uses rsi rdi rbx color:UINT

  local x           :UINT,
        y           :UINT,
        x_start     :UINT,
        y_start     :UINT,
        x_end       :UINT,
        y_end       :UINT,
        delta       :SINT

    mov rbx,rcx
    mov eax,[rbx].radius
    mov y,eax
    add eax,eax
    mov edx,3
    sub edx,eax
    mov delta,edx

    xor eax,eax
    mov x,eax

    .while eax < y

        asp_ratio equ 11

        mov r8d,y
        mov ecx,10
        mov eax,asp_ratio
        mul r8d
        xor edx,edx
        div ecx
        mov y_start,eax

        inc r8d
        mov eax,asp_ratio
        mul r8d
        xor edx,edx
        div ecx
        mov y_end,eax

        mov eax,asp_ratio
        mov r8d,x
        mul r8d
        xor edx,edx
        div ecx
        mov x_start,eax

        inc r8d
        mov eax,asp_ratio
        mul r8d
        xor edx,edx
        div ecx
        mov x_end,eax

        mov edi,x_start

        .while edi < x_end

            inc edi

            mov edx,edi
            add edx,[rbx].pos.x
            mov r9d,[rbx].pos.x
            sub r9d,edi
            mov r8d,[rbx].pos.y
            add r8d,y
            g.Line(edx, r8d, r9d, r8d, color)

            mov edx,[rbx].pos.x
            sub edx,edi
            mov r9d,edi
            add r9d,[rbx].pos.x
            mov r8d,[rbx].pos.y
            sub r8d,y
            g.Line(edx, r8d, r9d, r8d, color)
        .endw

        mov edx,[rbx].pos.x
        sub edx,edi
        mov r9d,edi
        add r9d,[rbx].pos.x
        mov r8d,[rbx].pos.y
        sub r8d,y
        inc r8d
        g.Line(edx, r8d, r9d, r8d, color)

        mov edx,edi
        add edx,[rbx].pos.x
        mov r9d,[rbx].pos.x
        sub r9d,edi
        mov r8d,[rbx].pos.y
        add r8d,y
        dec r8d
        g.Line(edx, r8d, r9d, r8d, color)

        mov edi,y_start

        .while edi < y_end

            inc edi
            mov edx,edi
            add edx,[rbx].pos.x
            mov r8d,x
            add r8d,[rbx].pos.y
            mov r9d,[rbx].pos.x
            sub r9d,edi
            mov ecx,[rbx].pos.y
            add ecx,x
            g.Line(edx, r8d, r9d, ecx, color)

            mov edx,[rbx].pos.x
            sub edx,edi
            mov r8d,[rbx].pos.y
            sub r8d,x
            mov r9d,edi
            add r9d,[rbx].pos.x
            mov ecx,[rbx].pos.y
            sub ecx,x
            g.Line(edx, r8d, r9d, ecx, color)

        .endw

        mov eax,x

        .if delta < 0

            lea edx,[eax*4+6]
            add delta,edx

        .else

            mov ecx,x
            mov edx,delta
            sub ecx,y
            lea edx,[edx+ecx*4+10]
            mov delta,edx
            dec y

        .endif

        inc eax
        mov x,eax

    .endw
    mov rcx,rbx
    mov rax,rbx
    ret

Object::Draw endp

    assume rbx:nothing

Object::Hide proc

    [rcx].Draw(0)
    ret

Object::Hide endp


Object::Show proc

    [rcx].Draw([rcx].color)
    ret

Object::Show endp


    assume rsi:ptr Object

Object::Move proc uses rsi rdi rbx

    mov rsi,rcx

    [rcx].Hide()

    mov ecx,[rsi].speed
    mov eax,[rsi].pos.x
    mov edx,[rsi].old.x
    mov r8d,[rsi].pos.y
    mov r9d,[rsi].old.y
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

    mov [rsi].pos.x,eax
    mov [rsi].pos.y,r8d

    mov ebx,[rsi].radius
    add eax,ebx
    add r8d,ebx
    .if eax >= [rsi].rc.right
        add edx,ecx
    .endif
    .if r8d >= [rsi].rc.bottom
        add r9d,ecx
    .endif
    add ebx,ebx
    sub eax,ebx
    sub r8d,ebx
    .if eax <= [rsi].rc.left
        sub edx,ecx
    .endif
    .if r8d <= [rsi].rc.top
        sub r9d,ecx
        inc [rsi].count
    .endif
    mov [rsi].old.x,edx
    mov [rsi].old.y,r9d

    .if ( [rsi].count == 7 )

        inc [rsi].color
        .if ( [rsi].color > 250 )

            mov [rsi].color,2
        .endif
        mov [rsi].count,0
    .endif

    mov eax,[rsi].pos.x
    .if ( eax <= [rsi].rc.left || eax >= [rsi].rc.right )

        mov eax,[rsi].rc.left
        add eax,[rsi].radius
        mov [rsi].pos.x,eax

    .endif

    mov eax,[rsi].pos.y
    .if ( eax <= [rsi].rc.top || eax >= [rsi].rc.bottom )

        mov eax,[rsi].rc.top
        add eax,[rsi].radius
        mov [rsi].pos.y,eax

    .endif

    [rsi].Show()
    ret

Object::Move endp

    end

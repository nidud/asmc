; TWINMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include crtl.inc
include twindow.inc

    .code

    assume rcx:window_t
    assume rbx:window_t

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

    end

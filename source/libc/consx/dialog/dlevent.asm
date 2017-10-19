include consx.inc
include crtl.inc

.data
tdialog PVOID 0
tdllist PVOID 0
thelp   PVOID 0

result  dd 0

_scancodes label byte   ;  A - Z
    db 1Eh,30h,2Eh,20h,12h,21h,22h,23h,17h,24h,25h,26h,32h
    db 31h,18h,19h,10h,13h,1Fh,14h,16h,2Fh,11h,2Dh,15h,2Ch

    .code

PrevItem proc private uses esi

    mov   esi,tdialog
    movzx eax,[esi].S_DOBJ.dl_count
    movzx ecx,[esi].S_DOBJ.dl_index
    mov   edx,ecx
    shl   edx,4
    add   edx,[esi].S_DOBJ.dl_object

    .repeat

        .if ecx

            sub edx,sizeof(S_TOBJ)
            .repeat

                .if !([edx].S_TOBJ.to_flag & _O_DEACT)

                    dec ecx
                    mov [esi].S_DOBJ.dl_index,cl
                    mov eax,1
                    .break(1)
                .endif
                sub edx,sizeof(S_TOBJ)
            .untilcxz
            xor ecx,ecx
        .endif

        add cl,[esi].S_DOBJ.dl_count
        .ifnz

            movzx  eax,[esi].S_DOBJ.dl_index
            lea    edx,[ecx-1]
            shl    edx,4
            add    edx,[esi].S_DOBJ.dl_object

            .repeat

                .break .if eax > ecx

                .if !([edx].S_TOBJ.to_flag & _O_DEACT)

                    dec ecx
                    mov [esi].S_DOBJ.dl_index,cl
                    mov eax,1
                    .break(1)
                .endif

                sub edx,sizeof(S_TOBJ)
            .untilcxz
        .endif
        xor eax,eax

    .until 1
    mov result,eax
    ret

PrevItem endp

NextItem proc private uses esi

    mov     esi,tdialog
    movzx   eax,[esi].S_DOBJ.dl_count
    movzx   ecx,[esi].S_DOBJ.dl_index
    lea     edx,[ecx+1]
    shl     edx,4
    add     edx,[esi].S_DOBJ.dl_object
    add     ecx,2

    .repeat

        .while ecx <= eax

            .if !([edx].S_TOBJ.to_flag & _O_DEACT)

                dec ecx
                mov [esi].S_DOBJ.dl_index,cl
                mov eax,1
                .break(1)
            .endif

            inc ecx
            add edx,SIZE S_TOBJ
        .endw

        mov     edx,[esi].S_DOBJ.dl_object
        movzx   eax,[esi].S_DOBJ.dl_index
        inc     eax
        mov     ecx,1
        .while  ecx <= eax

            .if !([edx].S_TOBJ.to_flag & _O_DEACT)

                dec ecx
                mov [esi].S_DOBJ.dl_index,cl
                mov eax,1
                .break(1)
            .endif

            inc ecx
            add edx,SIZE S_TOBJ
        .endw
        xor eax,eax
    .until 1
    mov result,eax
    ret

NextItem endp

MouseDelay proc private

    .if mousep()

        scroll_delay()
        scroll_delay()
        or eax,1
    .endif
    ret

MouseDelay endp

test_event proc private uses esi edi ebx cmd, extended

  local x,x2,y,l,row,flag,c1,c2,c3,c4

    mov esi,tdialog
    xor edi,edi
    xor ebx,ebx

    .if [esi].S_DOBJ.dl_count
        mov ecx,[esi].S_DOBJ.dl_object
        mov bl,[esi].S_DOBJ.dl_index
        shl ebx,4
        add ebx,ecx
        movzx edi,[ebx].S_TOBJ.to_flag
    .endif

    .repeat

        mov eax,cmd
        .switch eax

          .case KEY_ESC
          .case KEY_ALTX
            mov result,_C_ESCAPE
            .break

          .case KEY_ALTUP
          .case KEY_ALTDN
          .case KEY_ALTLEFT
          .case KEY_ALTRIGHT

            movzx ecx,[esi].S_DOBJ.dl_flag
            .if ecx & _D_DMOVE
                mov edi,[esi].S_DOBJ.dl_wp
                mov ebx,[esi].S_DOBJ.dl_rect
                .if ecx & _D_SHADE
                    rcclrshade(ebx, edi)
                .endif
                mov eax,cmd
                movzx ecx,[esi].S_DOBJ.dl_flag
                .switch eax
                  .case KEY_ALTUP: rcmoveup(ebx, edi, ecx): .endc
                  .case KEY_ALTDN: rcmovedn(ebx, edi, ecx): .endc
                  .case KEY_ALTLEFT: rcmoveleft(ebx, edi, ecx): .endc
                  .case KEY_ALTRIGHT: rcmoveright(ebx, edi, ecx): .endc
                .endsw
                mov bx,ax
                mov word ptr [esi].S_DOBJ.dl_rect,ax
                .if [esi].S_DOBJ.dl_flag & _D_SHADE
                    rcsetshade(ebx, edi)
                .endif
            .endif
            xor eax,eax
            .break

          .case KEY_ENTER
          .case KEY_KPENTER
            mov eax,_C_RETURN
            .if edi & _O_CHILD
                mov eax,[ebx].S_TOBJ.to_proc
                .if eax
                    call eax
                    mov edi,eax
                    .if eax == _C_REOPEN
                        mov al,[esi].S_DOBJ.dl_index
                        push eax
                        dlinit(esi)
                        pop eax
                        mov [esi].S_DOBJ.dl_index,al
                    .endif
                    mov eax,edi
                .endif
            .endif
            mov result,eax
            .break

          .case MOUSECMD

            mov ecx,mousex()
            mov result,_C_NORMAL
            mov edx,[esi].S_DOBJ.dl_rect

            .if !rcxyrow(edx, ecx, mousey())

                mov result,_C_ESCAPE
                .break
            .endif

            mov row,eax

            mov   edi,[esi].S_DOBJ.dl_rect
            movzx ebx,[esi].S_DOBJ.dl_count
            mov   edx,[esi].S_DOBJ.dl_object

            .while ebx

                mov eax,[edx].S_TOBJ.to_rect
                add ax,di

                .if rcxyrow(eax, ecx, keybmouse_y)

                    sub eax,eax
                    mov row,eax

                    mov al,[esi].S_DOBJ.dl_count
                    sub eax,ebx
                    mov ebx,eax
                    shl eax,4
                    add eax,[esi].S_DOBJ.dl_object
                    mov edi,eax
                    mov ax,[edi].S_TOBJ.to_flag
                    mov flag,eax

                    .if !(eax & _O_DEACT)

                        mov [esi].S_DOBJ.dl_index,bl

                        and eax,0Fh
                        .if al == _O_TBUTT || al == _O_PBUTT

                            mov al,[esi].S_DOBJ.dl_rect.rc_x
                            add al,[edi].S_TOBJ.to_rect.rc_x
                            mov x,eax

                            mov al,[esi].S_DOBJ.dl_rect.rc_y
                            add al,[edi].S_TOBJ.to_rect.rc_y
                            mov y,eax

                            mov al,[edi].S_TOBJ.to_rect.rc_col
                            mov l,eax

                            add eax,x
                            dec eax
                            mov x2,eax
                            mov ebx,eax

                            mov c1,getxyc(x, y)
                            mov c2,getxyc(ebx, y)
                            scputc(x, y, 1, ' ')
                            scputc(x2, y, 1, ' ')

                            inc ebx
                            mov c3,getxyc(ebx, y)
                            sub ebx,l
                            inc ebx
                            mov eax,y
                            inc eax
                            mov c4,getxyc(ebx, eax)
                            mov eax,flag
                            and eax,0x0F
                            push eax
                            .ifz
                                mov eax,y
                                inc eax
                                scputc(ebx, eax, l, ' ')
                                add ebx,l
                                dec ebx
                                scputc(ebx, y, 1, ' ')
                            .endif
                            msloop()
                            scputc(x, y, 1, c1)
                            scputc(x2, y, 1, c2)
                            pop edx
                            .if !edx
                                mov ebx,x
                                inc ebx
                                mov edx,y
                                inc edx
                                scputc(ebx, edx, l, c4)
                                add ebx,l
                                dec ebx
                                scputc(ebx, y, 1, c3)
                            .endif
                        .endif

                        mov eax,flag
                        .if eax & _O_DEXIT
                            mov result,_C_ESCAPE
                        .endif
                        .if eax & _O_CHILD
                            mov eax,[edi].S_TOBJ.to_proc
                            .if eax
                                call eax
                                mov result,eax
                                .if eax == _C_REOPEN
                                    mov al,[esi].S_DOBJ.dl_index
                                    push eax
                                    dlinit(esi)
                                    pop eax
                                    mov [esi].S_DOBJ.dl_index,al
                                .endif
                            .endif
                        .else
                            and eax,000Fh
                            .if al == _O_TBUTT || al == _O_PBUTT || \
                                al == _O_MENUS || al == _O_XHTML
                                mov result,_C_RETURN
                            .endif
                        .endif
                    .else
                        and eax,0Fh
                        .if al == _O_LLMSU
                            mov edx,tdllist
                            sub eax,eax
                            .repeat
                                .if eax != [edx].S_LOBJ.ll_count
                                    mov [edx].S_LOBJ.ll_celoff,eax
                                    mov eax,[edx].S_LOBJ.ll_dlgoff
                                    cmp al,[esi].S_DOBJ.dl_index
                                    mov [esi].S_DOBJ.dl_index,al
                                    .break .ifnz
                                    .while test_event(KEY_UP, 1)

                                        .break .if !MouseDelay()
                                    .endw
                                .endif
                                msloop()
                                mov eax,_C_NORMAL
                            .until 1
                        .elseif al == _O_LLMSD
                            mov edx,tdllist
                            sub eax,eax
                            .repeat
                                .if eax != [edx].S_LOBJ.ll_count
                                    mov [edx].S_LOBJ.ll_celoff,eax
                                    mov eax,[edx].S_LOBJ.ll_dlgoff
                                    cmp al,[esi].S_DOBJ.dl_index
                                    mov [esi].S_DOBJ.dl_index,al
                                    .break .ifnz
                                    .while test_event(KEY_DOWN, 1)

                                        .break .if !MouseDelay()
                                    .endw
                                .endif
                                msloop()
                                mov eax,_C_NORMAL
                            .until 1
                        .elseif al == _O_MOUSE
                            .if ecx & _O_CHILD
                                mov eax,[edi].S_TOBJ.to_proc
                                .if eax
                                    call eax
                                    mov result,eax
                                    .if eax == _C_REOPEN
                                        mov al,[esi].S_DOBJ.dl_index
                                        push eax
                                        dlinit(esi)
                                        pop eax
                                        mov [esi].S_DOBJ.dl_index,al
                                    .endif
                                .endif
                            .endif
                        .endif
                    .endif
                    .break
                .endif
                add edx,SIZE S_TOBJ
                dec ebx
            .endw

            mov eax,row
            .if eax == 1
                dlmove(esi)
            .elseif eax
                msloop()
            .endif
            .break

        .endsw

        .if extended

            .switch eax

              .case KEY_LEFT

                .if edi & _O_LLIST

                    .gotosw(KEY_PGUP)
                .endif

                mov eax,edi
                and eax,0x0F
                .if al == _O_MENUS
                    mov result,0
                    .break
                .endif

                movzx ecx,[esi].S_DOBJ.dl_index
                .if !ecx
                    mov result,ecx
                    .break
                .endif

                mov edx,esi
                mov eax,[edx].S_TOBJ.to_rect
                sub edx,sizeof(S_TOBJ) ; prev object
                .repeat
                    .if ah == [edx+5] && al > [edx+4]

                        .if !([edx].S_TOBJ.to_flag & _O_DEACT)
                            dec ecx
                            mov [esi].S_DOBJ.dl_index,cl
                            mov result,1
                            .break(1)
                        .endif
                    .endif
                    sub edx,sizeof(S_TOBJ)
                .untilcxz

              .case KEY_UP

                .if ebx

                    .if edi & _O_LLIST

                        xor eax,eax
                        mov edx,tdllist

                        .if eax == [edx].S_LOBJ.ll_celoff

                            .if eax != [edx].S_LOBJ.ll_index

                                mov ecx,[edx].S_LOBJ.ll_dlgoff

                                .if [esi].S_DOBJ.dl_index == cl

                                    dec [edx].S_LOBJ.ll_index
                                    mov eax,esi
                                    call [edx].S_LOBJ.ll_proc
                                    .break
                                .endif

                                mov [edx].S_DOBJ.dl_index,cl
                                inc eax
                            .endif
                            .break
                        .endif
                    .endif
                    PrevItem()
                .endif
                .break

              .case KEY_RIGHT

                mov result,0
                .if edi & _O_LLIST

                    .gotosw(KEY_PGDN)
                .endif

                mov eax,edi
                and eax,0x0F
                .break .if al == _O_MENUS
                .break .if !ebx

                inc    result
                lea    edx,[ebx+16]
                movzx  ecx,[esi].S_DOBJ.dl_index
                inc    ecx
                mov    eax,[ebx].S_TOBJ.to_rect

                .while cl < [esi].S_DOBJ.dl_count

                    .if ah == [edx].S_TOBJ.to_rect.rc_y && al < [edx].S_TOBJ.to_rect.rc_x

                        .if !([edx].S_TOBJ.to_flag & _O_DEACT)

                            mov [esi].S_DOBJ.dl_index,cl
                            .break(1)
                        .endif
                    .endif
                    inc ecx
                    add edx,16
                .endw

              .case KEY_DOWN

                .if !(edi & _O_LLIST)

                    NextItem()
                    .break
                .endif

                mov edx,tdllist
                mov eax,[edx].S_LOBJ.ll_dcount
                mov ecx,[edx].S_LOBJ.ll_celoff
                dec eax
                .if eax != ecx
                    mov eax,ecx
                    add eax,[edx].S_LOBJ.ll_index
                    inc eax
                    .if eax < [edx].S_LOBJ.ll_count

                        NextItem()
                        .break
                    .endif
                .endif

                mov eax,[edx].S_LOBJ.ll_dlgoff
                add eax,ecx
                mov ah,[esi].S_DOBJ.dl_index
                mov [esi].S_DOBJ.dl_index,al
                .if al != ah

                    mov result,_C_NORMAL
                    .break
                .endif

                mov eax,[edx].S_LOBJ.ll_count
                sub eax,[edx].S_LOBJ.ll_index
                sub eax,[edx].S_LOBJ.ll_dcount
                .ifng

                    mov result,0
                    .break
                .endif

                inc [edx].S_LOBJ.ll_index
                mov eax,esi
                call [edx].S_LOBJ.ll_proc
                mov result,eax
                .break

              .case KEY_HOME

                mov result,_C_NORMAL
                xor eax,eax
                .if !(edi & _O_LLIST)

                    mov ecx,edi
                    and ecx,0x0F
                    .break .if cl != _O_MENUS
                .endif
                .ifnz
                    mov  edx,tdllist
                    mov  [edx].S_LOBJ.ll_index,eax
                    mov  [edx].S_LOBJ.ll_celoff,eax
                    push [edx].S_LOBJ.ll_dlgoff
                    mov  eax,esi
                    call [edx].S_LOBJ.ll_proc
                    pop eax
                .endif
                mov [esi].S_DOBJ.dl_index,al
                NextItem()
                PrevItem()
                .break

              .case KEY_END

                mov result,_C_NORMAL
                .if !(edi & _O_LLIST)

                    mov eax,edi
                    and eax,0x0F
                    .break .if al != _O_MENUS

                    mov al,[esi].S_DOBJ.dl_count
                    dec al
                    mov [esi].S_DOBJ.dl_index,al
                    PrevItem()
                    NextItem()
                    .break
                .endif

                mov edx,tdllist
                mov eax,[edx].S_LOBJ.ll_count
                .if eax < [edx].S_LOBJ.ll_dcount
                    mov eax,[edx].S_LOBJ.ll_numcel
                    dec eax
                    mov [edx].S_LOBJ.ll_celoff,eax
                    add eax,[edx].S_LOBJ.ll_dlgoff
                    mov [esi].S_DOBJ.dl_index,al
                    .break
                .endif

                mov result,0
                sub eax,[edx].S_LOBJ.ll_dcount
                .break .if eax == [edx].S_LOBJ.ll_index

                mov [edx].S_LOBJ.ll_index,eax
                mov eax,[edx].S_LOBJ.ll_dcount
                dec eax
                mov [edx].S_LOBJ.ll_celoff,eax
                add eax,[edx].S_LOBJ.ll_dlgoff

                mov [esi].S_DOBJ.dl_index,al
                mov eax,esi
                call [edx].S_LOBJ.ll_proc
                mov result,eax
                .break

              .case KEY_TAB

                .if edi & _O_LLIST

                    mov edx,tdllist
                    mov eax,[edx].S_LOBJ.ll_dlgoff
                    add eax,[edx].S_LOBJ.ll_dcount
                    mov [esi].S_DOBJ.dl_index,al
                    mov result,_C_NORMAL
                    .break
                .endif
                NextItem()
                .break

              .case KEY_PGUP

                .if !(edi & _O_LLIST)

                    mov eax,edi
                    and eax,0x0F
                    .if al != _O_MENUS
                        mov result,_C_NORMAL
                        .break
                    .endif
                .endif

                mov edx,tdllist
                xor eax,eax
                .if eax == [edx].S_LOBJ.ll_celoff
                    .if eax != [edx].S_LOBJ.ll_index
                        mov eax,[edx].S_LOBJ.ll_dcount
                        .if eax > [edx].S_LOBJ.ll_index
                            .gotosw(KEY_HOME)
                        .endif
                        sub [edx].S_LOBJ.ll_index,eax
                        mov eax,esi
                        call [edx].S_LOBJ.ll_proc
                        mov result,eax
                        .break
                    .endif
                .else
                    mov [edx].S_LOBJ.ll_celoff,eax
                    mov eax,[edx].S_LOBJ.ll_dlgoff
                    mov edx,tdialog
                    mov [edx].S_DOBJ.dl_index,al
                .endif
                mov result,_C_NORMAL
                .break

              .case KEY_PGDN

                .if !(edi & _O_LLIST)

                    mov eax,edi
                    and eax,0x0F
                    .if al != _O_MENUS
                        mov result,_C_NORMAL
                        .break
                    .endif
                .endif

                mov edx,tdllist
                mov eax,[edx].S_LOBJ.ll_dcount
                dec eax
                .if eax != [edx].S_LOBJ.ll_celoff
                    mov eax,[edx].S_LOBJ.ll_numcel
                    add eax,[edx].S_LOBJ.ll_dlgoff
                    dec eax
                    mov [esi].S_DOBJ.dl_index,al
                    mov result,_C_NORMAL
                    .break
                .endif

                add eax,[edx].S_LOBJ.ll_celoff
                add eax,[edx].S_LOBJ.ll_index
                inc eax
                .if eax >= [edx].S_LOBJ.ll_count
                    .gotosw(KEY_END)
                .endif
                mov eax,[edx].S_LOBJ.ll_dcount
                add [edx].S_LOBJ.ll_index,eax
                mov eax,esi
                call [edx].S_LOBJ.ll_proc
                mov result,eax
                .break
            .endsw
        .endif

        .repeat

            .break .if !eax

            mov edx,tdialog
            movzx ecx,[edx].S_DOBJ.dl_count
            mov edx,[edx].S_DOBJ.dl_object

            .if eax == KEY_F1
                xor eax,eax
                mov edx,tdialog
                .if [edx].S_DOBJ.dl_flag & _D_DHELP
                    .if thelp != eax
                        call thelp
                        mov eax,_C_NORMAL
                    .endif
                .endif
                .break
            .endif

            .if !ecx
                xor eax,eax
                .break
            .endif

            xor ebx,ebx
            xor esi,esi

            .repeat

                .if [edx].S_TOBJ.to_flag & _O_GLCMD

                    mov ebx,[edx].S_TOBJ.to_data
                .endif

                push eax
                .if [edx].S_TOBJ.to_flag & _O_DEACT || [edx].S_TOBJ.to_ascii == 0
                        xor eax,eax
                .else
                    and al,0DFh
                    .if [edx].S_TOBJ.to_ascii == al
                        or al,1
                    .else
                        mov al,[edx].S_TOBJ.to_ascii
                        and al,0DFh
                        sub al,'A'
                        push edx
                        movzx edx,al
                        cmp ah,_scancodes[edx]
                        pop edx
                        setz al
                        test al,al
                    .endif
                .endif
                pop eax

                .ifnz
                    test [edx].S_TOBJ.to_flag,_O_PBKEY
                    mov eax,esi
                    mov edx,tdialog
                    mov [edx].S_DOBJ.dl_index,al
                    mov eax,_C_RETURN
                    .break(1) .ifnz
                    mov eax,_C_NORMAL
                    .break(1)
                .endif

                add edx,16
                inc esi

            .untilcxz

            .if ebx
                mov edx,ebx
                .while  [edx].S_GLCMD.gl_key
                    .if [edx].S_GLCMD.gl_key == eax
                        call [edx].S_GLCMD.gl_proc
                        .break(1)
                    .endif
                    add edx,SIZE S_GLCMD
                .endw
            .endif
            xor eax,eax
        .until 1
        mov result,eax
    .until 1
    ret

test_event endp

dlpbuttevent proc uses esi edi ebx

    local cursor:S_CURSOR
    local x,x2

    CursorGet(&cursor)
    CursorOn()

    mov   esi,tdialog
    movzx edi,[esi].S_DOBJ.dl_index
    shl   edi,4
    add   edi,[esi].S_DOBJ.dl_object
    movzx eax,[esi].S_DOBJ.dl_rect.rc_x
    add   al,[edi].S_TOBJ.to_rect.rc_x
    mov   x,eax
    add   al,[edi].S_TOBJ.to_rect.rc_col
    dec   eax
    mov   x2,eax
    mov   al,[esi].S_DOBJ.dl_rect.rc_y
    add   al,[edi].S_TOBJ.to_rect.rc_y
    mov   esi,eax
    _gotoxy(x, eax)
    mov al,byte ptr [edi].S_TOBJ.to_flag
    and al,0x0F
    .if al != _O_TBUTT
        CursorOff()
    .endif
    getxyc(x, esi)
    mov bl,al
    getxyc(x2, esi)
    movzx edi,al
    mov al,ASCII_RIGHT
    scputc(x, esi, 1, eax)
    mov al,ASCII_LEFT
    scputc(x2, esi, 1, eax)
    tgetevent()
    push eax
    scputc(x, esi, 1, ebx)
    scputc(x2, esi, 1, edi)
    CursorSet(&cursor)
    pop eax
    ret
dlpbuttevent endp

dlradioevent proc uses esi edi

    local cursor:S_CURSOR
    local x,y

    CursorGet(&cursor)
    CursorOn()

    mov   esi,tdialog
    movzx edi,[esi].S_DOBJ.dl_index
    shl   edi,4
    add   edi,[esi].S_DOBJ.dl_object
    movzx eax,[esi].S_DOBJ.dl_rect.rc_x
    add   al,[edi].S_TOBJ.to_rect.rc_x
    inc   eax
    mov   x,eax
    mov   al,[esi].S_DOBJ.dl_rect.rc_y
    add   al,[edi].S_TOBJ.to_rect.rc_y
    mov   y,eax
    _gotoxy(x, eax)

    .repeat

        .repeat

            .if tgetevent() == MOUSECMD

                mousey()
                .break(1) .if eax != y
                mousex()
                mov edx,x
                dec edx
                .break(1) .if eax < edx
                add edx,2
                .break(1) .if eax > edx

            .elseif eax != KEY_SPACE

                .break(1)
            .endif

            mov ax,[edi].S_TOBJ.to_flag
            and eax,_O_RADIO
            .repeat
                .ifz
                    movzx ecx,[esi].S_DOBJ.dl_count
                    .break .if !ecx

                    mov edx,[esi].S_DOBJ.dl_object
                    .repeat
                        .break .if [edx].S_TOBJ.to_flag & _O_RADIO
                        add edx,16
                    .untilcxz
                    .break .ifz
                    and [edx].S_TOBJ.to_flag,not _O_RADIO
                    or  [edi].S_TOBJ.to_flag,_O_RADIO
                    mov cx,[edx+4]
                    add cx,[esi+4]
                    mov dl,ch
                    inc ecx
                    scputc(ecx, edx, 1, ' ')
                    mov al,ASCII_RADIO
                    scputc(x, y, 1, eax)
                .endif
                msloop()
            .until 1
        .until [edi].S_TOBJ.to_flag & _O_EVENT
        mov eax,KEY_SPACE
    .until 1
    push eax
    CursorSet(&cursor)
    pop eax
    ret

dlradioevent endp

dlcheckevent proc uses esi edi

    local cursor:S_CURSOR
    local x,y

    CursorGet(&cursor)
    CursorOn()

    mov   esi,tdialog
    movzx edi,[esi].S_DOBJ.dl_index
    shl   edi,4
    add   edi,[esi].S_DOBJ.dl_object
    movzx eax,[esi].S_DOBJ.dl_rect.rc_x
    add   al,[edi].S_TOBJ.to_rect.rc_x
    inc   eax
    mov   x,eax
    mov   al,[esi].S_DOBJ.dl_rect.rc_y
    add   al,[edi].S_TOBJ.to_rect.rc_y
    mov   y,eax
    _gotoxy(x, eax)

    .repeat
        .repeat
            .if tgetevent() == MOUSECMD

                mousey()
                .break(1) .if eax != y
                mousex()
                mov edx,x
                dec edx
                .break(1) .if eax < edx
                add edx,2
                .break(1) .if eax > edx

            .elseif eax != KEY_SPACE

                .break(1)
            .endif

            xor [edi].S_TOBJ.to_flag,_O_FLAGB
            mov eax,' '
            .if [edi].S_TOBJ.to_flag & _O_FLAGB
                mov eax,'x'
            .endif
            scputc(x, y, 1, eax)
            msloop()
        .until [edi].S_TOBJ.to_flag & _O_EVENT
        mov eax,KEY_SPACE
    .until 1
    push eax
    CursorSet(&cursor)
    pop eax
    ret

dlcheckevent endp

dlxcellevent proc uses esi edi ebx

    local xlbuf[256]:word

    mov   esi,tdialog
    movzx edi,[esi].S_DOBJ.dl_index
    shl   edi,4
    add   edi,[esi].S_DOBJ.dl_object

    .if [esi].S_DOBJ.dl_count

        CursorOff()
    .endif

    .if [edi].S_TOBJ.to_flag & _O_LLIST

        movzx eax,[esi].S_DOBJ.dl_index
        mov edx,tdllist

        .if eax >= [edx].S_LOBJ.ll_dlgoff
            sub eax,[edx].S_LOBJ.ll_dlgoff
            .if eax < [edx].S_LOBJ.ll_numcel
                mov [edx].S_LOBJ.ll_celoff,eax
            .endif
        .endif
    .endif

    mov ebx,[edi].S_TOBJ.to_rect
    add bx,word ptr [esi].S_DOBJ.dl_rect
    rcread(ebx, &xlbuf)
    mov al,at_background[B_Inverse]
    movzx ecx,[edi].S_TOBJ.to_rect.rc_col
    wcputbg(&xlbuf, ecx, eax)
    rcxchg(ebx, &xlbuf)

    .repeat

        .switch tgetevent()

          .case KEY_MOUSEUP
            mov eax,KEY_UP
            .if [edi].S_TOBJ.to_flag & _O_LLIST

                PushEvent(eax)
                PushEvent(eax)
            .endif
            .endc

          .case KEY_MOUSEDN
            mov eax,KEY_DOWN
            .if [edi].S_TOBJ.to_flag & _O_LLIST

                PushEvent(eax)
                PushEvent(eax)
            .endif
            .endc

          .case MOUSECMD

            mov edx,mousey()
            .if rcxyrow(ebx, mousex(), edx)

                mov al,[edi].S_TOBJ.to_rect.rc_col
                mov cl,bh
                mousewait(ebx, ecx, eax)

                movzx eax,[edi].S_TOBJ.to_flag
                and eax,0x0F
                cmp eax,_O_XHTML
                mov eax,KEY_ENTER
                .ifnz

                    mov esi,10
                    .repeat
                        Sleep(16)
                        .break .if mousep()
                        dec esi
                    .untilz

                    .if mousep()

                        mov edx,mousey()
                        .continue(0) .if !rcxyrow(ebx, mousex(), edx)
                        mov eax,KEY_ENTER
                    .endif
                .endif
            .else
                mov eax,MOUSECMD
            .endif

          .default
            .continue(0) .if !eax
            .endc
        .endsw
    .until 1
    push eax
    rcwrite(ebx, &xlbuf)
    pop eax
    ret

dlxcellevent endp

dlteditevent proc uses esi ebx

    mov   ecx,tdialog
    mov   si,[ecx+4]
    movzx edx,[ecx].S_DOBJ.dl_index
    shl   edx,4
    add   edx,[ecx].S_DOBJ.dl_object
    mov   eax,[edx].S_TOBJ.to_rect
    add   ax,si
    movzx ebx,[edx].S_TOBJ.to_flag
    movzx ecx,[edx].S_TOBJ.to_count
    shl   ecx,4
    dledit([edx].S_TOBJ.to_data, eax, ecx, ebx)
    ret

dlteditevent endp

dlmenusevent proc uses esi edi ebx

    local cursor:S_CURSOR
    local xlbuf[256]:word

    CursorGet(&cursor)
    CursorOff()

    mov esi,tdialog
    movzx edi,[esi].S_DOBJ.dl_index
    shl edi,4
    add edi,[esi].S_DOBJ.dl_object
    .if [edi].S_TOBJ.to_data
        mov al,' '
        mov ah,at_background[B_Menus]
        or  ah,at_foreground[F_KeyBar]
        mov ecx,_scrrow
        scputw(20, ecx, 60, eax)
        scputs(20, ecx, 0, 60, [edi].S_TOBJ.to_data)
    .endif

    mov ebx,[edi].S_TOBJ.to_rect
    add bx,word ptr [esi].S_DOBJ.dl_rect
    rcread(ebx, &xlbuf)
    mov al,at_background[B_InvMenus]
    movzx ecx,[edi].S_TOBJ.to_rect.rc_col
    wcputbg(&xlbuf, ecx, eax)
    rcxchg(ebx, &xlbuf)

    .if tgetevent() == KEY_MOUSEUP
        mov eax,KEY_UP
    .elseif eax == KEY_MOUSEDN
        mov eax,KEY_DOWN
    .endif
    push eax
    rcwrite(ebx, &xlbuf)
    CursorSet(&cursor)
    pop eax
    ret

dlmenusevent endp

dlevent proc uses esi edi ebx dialog:ptr S_DOBJ

    local prevdlg:dword   ; init tdialog
    local cursor:S_CURSOR ; init cursor
    local event, dlexit


    mov eax,tdialog
    mov prevdlg,eax
    mov eax,dialog
    mov tdialog,eax
    mov ebx,tdialog
    movzx esi,[ebx].S_DOBJ.dl_flag

    .repeat

        .if !(esi & _D_ONSCR)

            .break .if !dlshow(dialog)
        .endif

        CursorGet(&cursor)
        CursorOff()

        movzx eax,[ebx].S_DOBJ.dl_count
        .if eax

            mov al,[ebx].S_DOBJ.dl_index
            shl eax,4
            add eax,[ebx].S_DOBJ.dl_object

            .if [eax].S_TOBJ.to_flag & _O_DEACT

                NextItem()
            .endif
            mov eax,1
        .endif

        .if !eax
            .while 1
                test_event(tgetevent(), 0)
                mov eax,result
                .break .if eax == _C_ESCAPE
                .break .if eax == _C_RETURN
            .endw
        .else

            msloop()
            xor edi,edi

            .repeat
                xor eax,eax
                mov result,eax

                mov al,[ebx].S_DOBJ.dl_index
                shl eax,4
                add eax,[ebx].S_DOBJ.dl_object

                .if [eax].S_TOBJ.to_flag & _O_EVENT

                    call [eax].S_TOBJ.to_proc
                .else
                    mov al,[eax]
                    and eax,0Fh
                    .switch eax
                      .case _O_TBUTT
                      .case _O_PBUTT: dlpbuttevent(): .endc
                      .case _O_RBUTT: dlradioevent(): .endc
                      .case _O_CHBOX: dlcheckevent(): .endc
                      .case _O_XCELL: dlxcellevent(): .endc
                      .case _O_TEDIT: dlteditevent(): .endc
                      .case _O_MENUS: dlmenusevent(): .endc
                      .case _O_XHTML: dlxcellevent(): .endc
                      .default
                        mov eax,KEY_ESC
                        .endc
                    .endsw
                .endif

                mov dlexit,eax
                mov event,eax
                mov ecx,test_event(eax, 1)
                mov eax,result
                .if eax == _C_ESCAPE
                    mov event,0
                    .break
                .elseif eax == _C_RETURN
                    xor eax,eax

                    mov al,[ebx].S_DOBJ.dl_index
                    shl eax,4
                    add eax,[ebx].S_DOBJ.dl_object

                    .if [eax].S_TOBJ.to_flag & _O_DEXIT

                        mov event,0
                    .else
                        mov edx,tdialog
                        movzx eax,[edx].S_DOBJ.dl_index
                        inc eax
                        mov event,eax
                    .endif
                    .break
                .elseif ecx == _O_MENUS && (event == KEY_LEFT || event == KEY_RIGHT)
                    inc edi
                .endif
            .until edi
        .endif

        CursorSet(&cursor)
        mov eax,event
    .until 1

    mov edx,eax
    mov eax,prevdlg
    mov tdialog,eax
    mov eax,edx
    mov ecx,dlexit
    test eax,eax
    ret
dlevent endp

Install:
    mov eax,getevent
    mov tgetevent,eax
    ret

pragma_init Install,32

    END

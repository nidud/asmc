; DLEVENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

public tdialog

define KEY_ALTUP        (KEY_ALT or KEY_UP)
define KEY_ALTDN        (KEY_ALT or KEY_DOWN)
define KEY_ALTLEFT      (KEY_ALT or KEY_LEFT)
define KEY_ALTRIGHT     (KEY_ALT or KEY_RIGHT)
define KEY_ALTX         (KEY_ALT or 'x')

.data
 tdialog    PDOBJ NULL
 tdllist    PLOBJ NULL
 dlresult   int_t 0
 _scancodes byte \  ;  A - Z
    1Eh,30h,2Eh,20h,12h,21h,22h,23h,17h,24h,25h,26h,32h,
    31h,18h,19h,10h,13h,1Fh,14h,16h,2Fh,11h,2Dh,15h,2Ch

.code

PrevItem proc private uses rsi

    mov   rsi,tdialog
    movzx eax,[rsi].DOBJ.count
    movzx ecx,[rsi].DOBJ.index
    mov   edx,ecx
    imul  edx,edx,TOBJ
    add   rdx,[rsi].DOBJ.object

    .repeat

        .if ecx

            sub rdx,TOBJ
            .repeat

                .if !( [rdx].TOBJ.flag & O_STATE )

                    dec ecx
                    mov [rsi].DOBJ.index,cl
                    mov eax,1
                    .break(1)
                .endif
                sub rdx,TOBJ
            .untilcxz
            xor ecx,ecx
        .endif

        add cl,[rsi].DOBJ.count
        .ifnz

            movzx  eax,[rsi].DOBJ.index
            lea    edx,[rcx-1]
            imul   edx,edx,TOBJ
            add    rdx,[rsi].DOBJ.object

            .repeat

                .break .if eax > ecx

                .if !( [rdx].TOBJ.flag & O_STATE )

                    dec ecx
                    mov [rsi].DOBJ.index,cl
                    mov eax,1
                   .break( 1 )
                .endif
                sub rdx,TOBJ
            .untilcxz
        .endif
        xor eax,eax
    .until 1
    mov dlresult,eax
    ret

PrevItem endp

NextItem proc private uses rsi

    mov     rsi,tdialog
    movzx   eax,[rsi].DOBJ.count
    movzx   ecx,[rsi].DOBJ.index
    lea     edx,[rcx+1]
    imul    edx,edx,TOBJ
    add     rdx,[rsi].DOBJ.object
    add     ecx,2

    .repeat

        .while ecx <= eax

            .if !( [rdx].TOBJ.flag & O_STATE )

                dec ecx
                mov [rsi].DOBJ.index,cl
                mov eax,1
               .break( 1 )
            .endif
            inc ecx
            add rdx,TOBJ
        .endw

        mov     rdx,[rsi].DOBJ.object
        movzx   eax,[rsi].DOBJ.index
        inc     eax
        mov     ecx,1

        .while ecx <= eax

            .if !( [rdx].TOBJ.flag & O_STATE )

                dec ecx
                mov [rsi].DOBJ.index,cl
                mov eax,1
               .break( 1 )
            .endif
            inc ecx
            add rdx,TOBJ
        .endw
        xor eax,eax
    .until 1
    mov dlresult,eax
    ret

NextItem endp

scroll_delay proc private

    _tupdate()
    Sleep(2)
    ret

scroll_delay endp

MouseDelay proc private

    .if mousep()

        scroll_delay()
        scroll_delay()
        or eax,1
    .endif
    ret

MouseDelay endp

test_event proc private uses rsi rdi rbx cmd, extended

  local mx,my,n,i,x,x2,y,l,row,flag,c1,c2,c3,c4

    mov rsi,tdialog
    xor edi,edi
    xor ebx,ebx

    .if ( [rsi].DOBJ.count )

        mov     rcx,[rsi].DOBJ.object
        mov     bl,[rsi].DOBJ.index
        imul    ebx,ebx,TOBJ
        add     rbx,rcx
        movzx   edi,[rbx].TOBJ.flag
    .endif

    mov eax,cmd
    .switch eax
    .case KEY_ESC
    .case KEY_ALTX
        mov dlresult,_C_ESCAPE
       .return

    .case KEY_ALTUP
    .case KEY_ALTDN
    .case KEY_ALTLEFT
    .case KEY_ALTRIGHT
        movzx ecx,[rsi].DOBJ.flag
        .if ( ecx & W_MOVEABLE )

            mov rdi,[rsi].DOBJ.wp
            mov ebx,[rsi].DOBJ.rc

            .if ( ecx & W_SHADE )

                _rcshade(ebx, rdi, 0)
            .endif

            mov eax,cmd
            .switch pascal eax
            .case KEY_ALTUP:    _rcmoveu(ebx, rdi)
            .case KEY_ALTDN:    _rcmoved(ebx, rdi)
            .case KEY_ALTLEFT:  _rcmovel(ebx, rdi)
            .case KEY_ALTRIGHT: _rcmover(ebx, rdi)
            .endsw

            mov bx,ax
            mov word ptr [rsi].DOBJ.rc,ax
            .if [rsi].DOBJ.flag & W_SHADE
                _rcshade(ebx, rdi, 1)
            .endif
        .endif
        .return(0)

    .case KEY_RETURN
    .case KEY_KPRETURN
        mov eax,_C_RETURN
        .if ( edi & O_CHILD )

            mov rax,[rbx].TOBJ.tproc
            .if rax

                call rax
                mov edi,eax

                .if ( eax == _C_REOPEN )

                    mov bl,[rsi].DOBJ.index
                    dlinit(rsi)
                    mov [rsi].DOBJ.index,bl
                .endif
                mov eax,edi
            .endif
        .endif
        mov dlresult,eax
       .return

    .case MOUSECMD

        mov mx,mousex()
        mov my,mousey()
        mov dlresult,_C_NORMAL

        .if !rcxyrow([rsi].DOBJ.rc, mx, my)

            mov dlresult,_C_ESCAPE
           .return
        .endif

        mov   row,eax
        mov   edi,[rsi].DOBJ.rc
        movzx eax,[rsi].DOBJ.count
        mov   rbx,[rsi].DOBJ.object
        mov   i,eax

        .while i

            mov eax,[rbx].TOBJ.rc
            add ax,di

            .if rcxyrow(eax, mx, my)

                xor eax,eax
                mov row,eax
                mov al,[rsi].DOBJ.count
                sub eax,i
                mov ebx,eax
                imul eax,eax,TOBJ
                add rax,[rsi].DOBJ.object
                mov rdi,rax
                mov ax,[rdi].TOBJ.flag
                mov flag,eax

                .if !( eax & O_STATE )

                    mov [rsi].DOBJ.index,bl
                    and eax,0x0F

                    .if ( al == _O_TBUTT || al == _O_PBUTT )

                        mov al,[rsi].DOBJ.rc.x
                        add al,[rdi].TOBJ.rc.x
                        mov x,eax

                        mov al,[rsi].DOBJ.rc.y
                        add al,[rdi].TOBJ.rc.y
                        mov y,eax

                        mov al,[rdi].TOBJ.rc.col
                        mov l,eax

                        add eax,x
                        dec eax
                        mov x2,eax
                        mov ebx,eax

                        mov c1,_scgetc(byte ptr x, byte ptr y)
                        mov c2,_scgetc(bl, byte ptr y)
                        _scputc(byte ptr x, byte ptr y, 1, ' ')
                        _scputc(byte ptr x2, byte ptr y, 1, ' ')

                        inc ebx
                        mov c3,_scgetc(bl, byte ptr y)
                        sub ebx,l
                        inc ebx
                        mov eax,y
                        inc eax
                        mov c4,_scgetc(bl, al)
                        mov eax,flag
                        and eax,0x0F
                        mov n,eax

                        .ifz

                            mov edx,y
                            inc edx
                            _scputc(bl, dl, byte ptr l, ' ')

                            add ebx,l
                            dec ebx
                            _scputc(bl, byte ptr y, 1, ' ')
                        .endif

                        msloop()

                        _scputc(byte ptr x, byte ptr y, 1, c1)
                        _scputc(byte ptr x2, byte ptr y, 1, c2)

                        .if ( n == 0 )

                            mov ebx,x
                            inc ebx
                            mov edx,y
                            inc edx
                            _scputc(bl, dl, byte ptr l, c4)

                            add ebx,l
                            dec ebx
                            _scputc(bl, byte ptr y, 1, c3)
                        .endif
                    .endif

                    mov eax,flag
                    .if ( eax & O_DEXIT )
                        mov dlresult,_C_ESCAPE
                    .endif

                    .if ( eax & O_CHILD )

                        mov rax,[rdi].TOBJ.tproc
                        .if rax

                            call rax
                            mov dlresult,eax

                            .if ( eax == _C_REOPEN )

                                mov bl,[rsi].DOBJ.index
                                dlinit(rsi)
                                mov [rsi].DOBJ.index,bl
                            .endif
                        .endif

                    .else

                        and eax,0x0F
                        .if ( al == _O_TBUTT ||
                              al == _O_PBUTT ||
                              al == _O_MENUS ||
                              al == _O_XHTML )

                            mov dlresult,_C_RETURN
                        .endif
                    .endif

                .else

                    and eax,0x0F
                    .if ( al == _O_LLMSU )

                        mov rdx,tdllist
                        xor eax,eax

                        .repeat

                            .if ( eax != [rdx].LOBJ.count )

                                mov [rdx].LOBJ.celoff,eax
                                mov eax,[rdx].LOBJ.dlgoff
                                cmp al,[rsi].DOBJ.index
                                mov [rsi].DOBJ.index,al

                                .break .ifnz
                                .while test_event(KEY_UP, 1)
                                    .break .if !MouseDelay()
                                .endw
                            .endif
                            msloop()
                            mov eax,_C_NORMAL
                        .until 1

                    .elseif ( al == _O_LLMSD )

                        mov rdx,tdllist
                        xor eax,eax

                        .repeat

                            .if ( eax != [rdx].LOBJ.count )

                                mov [rdx].LOBJ.celoff,eax
                                mov eax,[rdx].LOBJ.dlgoff
                                cmp al,[rsi].DOBJ.index
                                mov [rsi].DOBJ.index,al

                                .break .ifnz
                                .while test_event(KEY_DOWN, 1)
                                    .break .if !MouseDelay()
                                .endw
                            .endif
                            msloop()
                            mov eax,_C_NORMAL
                        .until 1

                    .elseif ( al == _O_MOUSE )

                        .if ( flag & O_CHILD )

                            mov rax,[rdi].TOBJ.tproc
                            .if rax

                                call rax
                                mov dlresult,eax

                                .if eax == _C_REOPEN

                                    mov bl,[rsi].DOBJ.index
                                    dlinit(rsi)
                                    mov [rsi].DOBJ.index,bl
                                .endif
                            .endif
                        .endif
                    .endif
                .endif

                .break

            .endif

            add rbx,TOBJ
            dec i
        .endw

        mov eax,row
        .if eax == 1
            dlmove(rsi)
        .elseif eax
            msloop()
        .endif
        .return
    .endsw

    .if extended

        .switch eax
        .case KEY_LEFT
            .if ( edi & O_LIST )
                .gotosw(KEY_PGUP)
            .endif

            mov eax,edi
            and eax,0x0F
            .if ( al == _O_MENUS )

                mov dlresult,0
               .return
            .endif

            movzx ecx,[rsi].DOBJ.index
            .if !ecx

                mov dlresult,ecx
               .return
            .endif

            mov rdx,rbx
            mov eax,[rdx].TOBJ.rc
            sub rdx,TOBJ ; prev object

            .repeat

                .if ( ah == [rdx].TOBJ.rc.y && al > [rdx].TOBJ.rc.x )

                    .if !( [rdx].TOBJ.flag & O_STATE)

                        dec ecx
                        mov [rsi].DOBJ.index,cl
                        mov dlresult,1
                       .return
                    .endif
                .endif
                sub rdx,TOBJ
            .untilcxz

        .case KEY_UP

            .if ebx

                .if ( edi & O_LIST )

                    xor eax,eax
                    mov rdx,tdllist

                    .if ( eax == [rdx].LOBJ.celoff )

                        .if ( eax != [rdx].LOBJ.index )

                            mov ecx,[rdx].LOBJ.dlgoff
                            .if [rsi].DOBJ.index == cl

                                dec [rdx].LOBJ.index
                                mov rax,rsi
                                call [rdx].LOBJ.lproc
                               .return
                            .endif

                            mov [rdx].DOBJ.index,cl
                            inc eax
                        .endif
                        .return
                    .endif
                .endif
                PrevItem()
            .endif
            .return

        .case KEY_RIGHT

            mov dlresult,0
            .if ( edi & O_LIST )
                .gotosw(KEY_PGDN)
            .endif

            mov eax,edi
            and eax,0x0F

            .return .if al == _O_MENUS
            .return .if !ebx

            inc    dlresult
            lea    rdx,[rbx+TOBJ]
            movzx  ecx,[rsi].DOBJ.index
            inc    ecx
            mov    eax,[rbx].TOBJ.rc

            .while ( cl < [rsi].DOBJ.count )

                .if ( ah == [rdx].TOBJ.rc.y && al < [rdx].TOBJ.rc.x )

                    .if !( [rdx].TOBJ.flag & O_STATE )

                        mov [rsi].DOBJ.index,cl
                       .return
                    .endif
                .endif
                inc ecx
                add rdx,TOBJ
            .endw

        .case KEY_DOWN

            .if !( edi & O_LIST )

                NextItem()
               .return
            .endif

            mov rdx,tdllist
            mov eax,[rdx].LOBJ.dcount
            mov ecx,[rdx].LOBJ.celoff
            dec eax

            .if ( eax != ecx )

                mov eax,ecx
                add eax,[rdx].LOBJ.index
                inc eax

                .if ( eax < [rdx].LOBJ.count )

                    NextItem()
                   .return
                .endif
            .endif

            mov eax,[rdx].LOBJ.dlgoff
            add eax,ecx
            mov ah,[rsi].DOBJ.index
            mov [rsi].DOBJ.index,al

            .if ( al != ah )

                mov dlresult,_C_NORMAL
               .return
            .endif

            mov eax,[rdx].LOBJ.count
            sub eax,[rdx].LOBJ.index
            sub eax,[rdx].LOBJ.dcount

            .ifng

                mov dlresult,0
               .return
            .endif

            inc [rdx].LOBJ.index
            mov rax,rsi
            call [rdx].LOBJ.lproc
            mov dlresult,eax
           .return

        .case KEY_HOME

            mov dlresult,_C_NORMAL
            xor eax,eax

            .if !( edi & O_LIST )

                mov ecx,edi
                and ecx,0x0F
               .return .if ( cl != _O_MENUS )
            .endif

            .ifnz

                mov  rdx,tdllist
                mov  [rdx].LOBJ.index,eax
                mov  [rdx].LOBJ.celoff,eax
                mov  ebx,[rdx].LOBJ.dlgoff
                mov  rax,rsi
                call [rdx].LOBJ.lproc
                mov eax,ebx
            .endif
            mov [rsi].DOBJ.index,al
            NextItem()
            PrevItem()
           .return

        .case KEY_END

            mov dlresult,_C_NORMAL
            .if !( edi & O_LIST )

                mov eax,edi
                and eax,0x0F

                .if ( al == _O_MENUS )

                    mov al,[rsi].DOBJ.count
                    dec al
                    mov [rsi].DOBJ.index,al
                    PrevItem()
                    NextItem()
                .endif
                .return
            .endif

            mov rdx,tdllist
            mov eax,[rdx].LOBJ.count

            .if ( eax < [rdx].LOBJ.dcount )

                mov eax,[rdx].LOBJ.numcel
                dec eax
                mov [rdx].LOBJ.celoff,eax
                add eax,[rdx].LOBJ.dlgoff
                mov [rsi].DOBJ.index,al
               .return
            .endif

            mov dlresult,0
            sub eax,[rdx].LOBJ.dcount

            .if ( eax != [rdx].LOBJ.index )

                mov [rdx].LOBJ.index,eax
                mov eax,[rdx].LOBJ.dcount
                dec eax
                mov [rdx].LOBJ.celoff,eax
                add eax,[rdx].LOBJ.dlgoff

                mov [rsi].DOBJ.index,al
                mov rax,rsi
                call [rdx].LOBJ.lproc
                mov dlresult,eax
            .endif
            .return

        .case KEY_TAB

            .if ( edi & O_LIST )

                mov rdx,tdllist
                mov eax,[rdx].LOBJ.dlgoff
                add eax,[rdx].LOBJ.dcount
                mov [rsi].DOBJ.index,al
                mov dlresult,_C_NORMAL
               .return
            .endif
            NextItem()
           .return

        .case KEY_PGUP

            .if !( edi & O_LIST )

                mov eax,edi
                and eax,0x0F

                .if ( al != _O_MENUS )

                    mov dlresult,_C_NORMAL
                   .return
                .endif
            .endif

            mov rdx,tdllist
            xor eax,eax

            .if ( eax == [rdx].LOBJ.celoff )

                .if ( eax != [rdx].LOBJ.index )

                    mov eax,[rdx].LOBJ.dcount
                    .if ( eax > [rdx].LOBJ.index )
                        .gotosw(KEY_HOME)
                    .endif
                    sub [rdx].LOBJ.index,eax
                    mov rax,rsi
                    call [rdx].LOBJ.lproc
                    mov dlresult,eax
                   .return
                .endif
            .else

                mov [rdx].LOBJ.celoff,eax
                mov eax,[rdx].LOBJ.dlgoff
                mov rdx,tdialog
                mov [rdx].DOBJ.index,al
            .endif
            mov dlresult,_C_NORMAL
           .return

        .case KEY_PGDN

            .if !( edi & O_LIST )

                mov eax,edi
                and eax,0x0F
                .if ( al != _O_MENUS )

                    mov dlresult,_C_NORMAL
                   .return
                .endif
            .endif

            mov rdx,tdllist
            mov eax,[rdx].LOBJ.dcount
            dec eax

            .if ( eax != [rdx].LOBJ.celoff )

                mov eax,[rdx].LOBJ.numcel
                add eax,[rdx].LOBJ.dlgoff
                dec eax
                mov [rsi].DOBJ.index,al
                mov dlresult,_C_NORMAL
               .return
            .endif

            add eax,[rdx].LOBJ.celoff
            add eax,[rdx].LOBJ.index
            inc eax

            .if ( eax >= [rdx].LOBJ.count )
                .gotosw(KEY_END)
            .endif

            mov eax,[rdx].LOBJ.dcount
            add [rdx].LOBJ.index,eax
            mov rax,rsi
            call [rdx].LOBJ.lproc
            mov dlresult,eax
           .return
        .endsw
    .endif

    .repeat

        .break .if !eax

        mov     rdx,tdialog
        movzx   ecx,[rdx].DOBJ.count
        mov     rdx,[rdx].DOBJ.object

        .if ( eax == KEY_F1 )

            xor eax,eax
            mov rdx,tdialog

            .if ( [rdx].DOBJ.flag & W_DHELP )

                _thelp()
                mov eax,_C_NORMAL
            .endif
            .break
        .endif

        .if ( ecx == 0 )

            xor eax,eax
           .break
        .endif

        xor ebx,ebx
        xor esi,esi

        .repeat

            .if ( [rdx].TOBJ.flag & O_GLOBAL )

                mov rbx,[rdx].TOBJ.data
            .endif

            push rax

            .if ( [rdx].TOBJ.flag & O_STATE || [rdx].TOBJ.ascii == 0 )

                xor eax,eax
            .else

                and al,0xDF
                .if ( [rdx].TOBJ.ascii == al )

                    or al,1
                .else

                    mov     al,[rdx].TOBJ.ascii
                    and     al,0xDF
                    sub     al,'A'
                    push    rdx
                    push    rbx
                    lea     rbx,_scancodes
                    movzx   edx,al
                    cmp     ah,[rbx+rdx]
                    pop     rbx
                    pop     rdx
                    setz    al
                    test    al,al
                .endif
            .endif

            pop rax

            .ifnz

                test    [rdx].TOBJ.flag,O_PBKEY
                mov     eax,esi
                mov     rdx,tdialog
                mov     [rdx].DOBJ.index,al
                mov     eax,_C_RETURN
                .break( 1 ) .ifnz
                mov     eax,_C_NORMAL
                .break( 1 )
            .endif

            add rdx,TOBJ
            inc esi

        .untilcxz

        .if rbx

            mov rdx,rbx
            .while ( [rdx].GLCMD.key )

                .if ( [rdx].GLCMD.key == eax )

                    [rdx].GLCMD.cmd()
                   .break( 1 )
                .endif
                add rdx,GLCMD
            .endw
        .endif
        xor eax,eax
    .until 1
    mov dlresult,eax
    ret

test_event endp

dlpbuttevent proc private uses rsi rdi rbx

   .new cursor:CURSOR
   .new x:uint_t, y:uint_t, x2:uint_t

    _getcursor(&cursor)
    _cursoron()

    mov   rsi,tdialog
    movzx eax,[rsi].DOBJ.index
    imul  edi,eax,TOBJ
    add   rdi,[rsi].DOBJ.object
    movzx eax,[rsi].DOBJ.rc.x
    add   al,[rdi].TOBJ.rc.x
    mov   x,eax
    add   al,[rdi].TOBJ.rc.col
    dec   eax
    mov   x2,eax
    mov   al,[rsi].DOBJ.rc.y
    add   al,[rdi].TOBJ.rc.y
    mov   y,eax

    mov al,byte ptr [rdi].TOBJ.flag
    and al,0x0F
    .if al != _O_TBUTT
        _cursoroff()
    .else
        mov eax,x
        inc eax
        _gotoxy(eax, y)
    .endif
    mov ebx,_scgetc(byte ptr x, byte ptr y)
    mov edi,_scgetc(byte ptr x2, byte ptr y)
    _scputc(byte ptr x, byte ptr y, 1, U_BLACK_POINTER_RIGHT)
    _scputc(byte ptr x2, byte ptr y, 1,U_BLACK_POINTER_LEFT)
    mov esi,tgetevent()
    _scputc(byte ptr x, byte ptr y, 1, ebx)
    _scputc(byte ptr x2, byte ptr y, 1, edi)
    _setcursor(&cursor)
    mov eax,esi
    ret

dlpbuttevent endp

dlradioevent proc private uses rsi rdi

    local cursor:CURSOR
    local x,y

    _getcursor(&cursor)
    _cursoron()

    mov   rsi,tdialog
    movzx eax,[rsi].DOBJ.index
    imul  edi,eax,TOBJ
    add   rdi,[rsi].DOBJ.object
    movzx eax,[rsi].DOBJ.rc.x
    add   al,[rdi].TOBJ.rc.x
    inc   eax
    mov   x,eax
    mov   al,[rsi].DOBJ.rc.y
    add   al,[rdi].TOBJ.rc.y
    mov   y,eax

    _gotoxy(x, eax)
    .repeat

        .repeat

            .ifd tgetevent() == MOUSECMD

                .ifd mousey() != y
                    mov eax,MOUSECMD
                    .break(1)
                .endif
                mousex()
                mov edx,x
                dec edx
                .if eax < edx
                    mov eax,MOUSECMD
                    .break(1)
                .endif
                add edx,2
                .if eax > edx
                    mov eax,MOUSECMD
                    .break(1)
                .endif
            .elseif eax != KEY_SPACE

                .break(1)
            .endif

            mov ax,[rdi].TOBJ.flag
            and eax,O_RADIO
            .repeat
                .ifz
                    movzx ecx,[rsi].DOBJ.count
                    .break .if !ecx

                    mov rdx,[rsi].DOBJ.object
                    .repeat
                        .break .if [rdx].TOBJ.flag & O_RADIO
                        add rdx,TOBJ
                    .untilcxz
                    .break .ifz
                    and [rdx].TOBJ.flag,not O_RADIO
                    or  [rdi].TOBJ.flag,O_RADIO
                    mov cx,[rdx+4]
                    add cx,[rsi+4]
                    mov dl,ch
                    inc ecx
                    _scputc(cl, dl, 1, ' ')
                    _scputc(byte ptr x, byte ptr y, 1, U_BULLET_OPERATOR)
                .endif
                msloop()
            .until 1
        .until [rdi].TOBJ.flag & O_EVENT
        mov eax,KEY_SPACE
    .until 1
    mov esi,eax
    _setcursor(&cursor)
    mov eax,esi
    ret

dlradioevent endp

dlcheckevent proc uses rsi rdi

    local cursor:CURSOR
    local x,y

    _getcursor(&cursor)
    _cursoron()

    mov   rsi,tdialog
    movzx eax,[rsi].DOBJ.index
    imul  edi,eax,TOBJ
    add   rdi,[rsi].DOBJ.object
    movzx eax,[rsi].DOBJ.rc.x
    add   al,[rdi].TOBJ.rc.x
    inc   eax
    mov   x,eax
    mov   al,[rsi].DOBJ.rc.y
    add   al,[rdi].TOBJ.rc.y
    mov   y,eax
    _gotoxy(x, eax)

    .repeat
        .repeat
            mov esi,tgetevent()
            .if esi == MOUSECMD

                mousey()
                .break(1) .if eax != y
                mousex()
                mov edx,x
                dec edx
                .break(1) .if eax < edx
                add edx,2
                .break(1) .if eax > edx

            .elseif esi != KEY_SPACE

                .break(1)
            .endif

            xor [rdi].TOBJ.flag,O_CHECK
            mov eax,' '
            .if [rdi].TOBJ.flag & O_CHECK
                mov eax,'x'
            .endif
            _scputc(byte ptr x, byte ptr y, 1, eax)
            msloop()
        .until [rdi].TOBJ.flag & O_EVENT
        mov esi,KEY_SPACE
    .until 1
    _setcursor(&cursor)
    mov eax,esi
    ret

dlcheckevent endp

dlxcellevent proc uses rsi rdi rbx

    local xlbuf[MAXCOLS]:CHAR_INFO

    mov   rsi,tdialog
    movzx eax,[rsi].DOBJ.index
    imul  edi,eax,TOBJ
    add   rdi,[rsi].DOBJ.object

    .if [rsi].DOBJ.count

        _cursoroff()
    .endif

    .if [rdi].TOBJ.flag & O_LIST

        movzx eax,[rsi].DOBJ.index
        mov rdx,tdllist

        .if eax >= [rdx].LOBJ.dlgoff
            sub eax,[rdx].LOBJ.dlgoff
            .if eax < [rdx].LOBJ.numcel
                mov [rdx].LOBJ.celoff,eax
            .endif
        .endif
    .endif

    mov ebx,[rdi].TOBJ.rc
    add bx,word ptr [rsi].DOBJ.rc
    _rcread(ebx, &xlbuf)
    mov al,at_background[BG_INVERSE]
    movzx ecx,[rdi].TOBJ.rc.col
    wcputbg(&xlbuf, ecx, eax)
    _rcxchg(ebx, &xlbuf)

    .repeat

        tgetevent()
        .switch eax

          .case KEY_MOUSEUP
            mov eax,KEY_UP
            .if [rdi].TOBJ.flag & O_LIST
                _postmessage(0, WM_KEYDOWN, VK_UP, ENHANCED_KEY)
            .endif
            .endc

          .case KEY_MOUSEDN
            mov eax,KEY_DOWN
            .if [rdi].TOBJ.flag & O_LIST
                _postmessage(0, WM_KEYDOWN, VK_DOWN, ENHANCED_KEY)
            .endif
            .endc

          .case MOUSECMD

            mov edx,mousey()
            .if rcxyrow(ebx, mousex(), edx)

                mov al,[rdi].TOBJ.rc.col
                mov cl,bh
                mousewait(ebx, ecx, eax)

                movzx eax,[rdi].TOBJ.flag
                and eax,0x0F
                cmp eax,_O_XHTML
                mov eax,KEY_RETURN
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
                        mov eax,KEY_RETURN
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
    mov esi,eax
    _rcwrite(ebx, &xlbuf)
    mov eax,esi
    ret

dlxcellevent endp

dlteditevent proc private uses rsi rbx

    mov     rdx,tdialog
    mov     si,[rdx+4]
    movzx   eax,[rdx].DOBJ.index
    imul    ecx,eax,TOBJ
    add     rcx,[rdx].DOBJ.object
    mov     eax,[rcx].TOBJ.rc
    add     ax,si
    movzx   ebx,[rcx].TOBJ.flag
    movzx   edx,[rcx].TOBJ.count
    shl     edx,4
    dledit([rcx].TOBJ.data, eax, edx, ebx)
    ret

dlteditevent endp

dlmenusevent proc private uses rsi rdi rbx

    local cursor:CURSOR
    local xlbuf[MAXCOLS]:CHAR_INFO

    _getcursor(&cursor)
    _cursoroff()

    mov   rsi,tdialog
    movzx eax,[rsi].DOBJ.index
    imul  edi,eax,TOBJ
    add   rdi,[rsi].DOBJ.object

    .if [rdi].TOBJ.data

        mov al,at_background[BG_MENU]
        or  al,at_foreground[FG_KEYBAR]
        shl eax,16
        mov al,' '
        mov rdx,_console
        movzx ebx,[rdx].TCONSOLE.rc.row
        dec ebx
        _scputw(20, bl, 60, eax)
        scputs(20, ebx, 0, 60, [rdi].TOBJ.data)
    .endif

    mov ebx,[rdi].TOBJ.rc
    add bx,word ptr [rsi].DOBJ.rc
    _rcread(ebx, &xlbuf)
    movzx eax,at_background[BG_INVMENU]
    movzx ecx,[rdi].TOBJ.rc.col
    wcputbg(&xlbuf, ecx, eax)
    _rcxchg(ebx, &xlbuf)

    .ifd tgetevent() == KEY_MOUSEUP
        mov eax,KEY_UP
    .elseif eax == KEY_MOUSEDN
        mov eax,KEY_DOWN
    .endif
    mov esi,eax
    _rcwrite(ebx, &xlbuf)
    _setcursor(&cursor)
    mov eax,esi
    ret

dlmenusevent endp

dlevent proc uses rsi rdi rbx dialog:PDOBJ

  local prevdlg:PDOBJ     ; init tdialog
  local cursor:CURSOR     ; init cursor
  local event, dlexit

    mov prevdlg,tdialog
    mov tdialog,dialog
    mov rbx,tdialog
    movzx esi,[rbx].DOBJ.flag

    .repeat

        .if !( esi & W_VISIBLE )

            .break .if !dlshow(dialog)
        .endif

        _getcursor(&cursor)
        _cursoroff()

        movzx eax,[rbx].DOBJ.count
        .if eax

            mov  al,[rbx].DOBJ.index
            imul eax,eax,TOBJ
            add  rax,[rbx].DOBJ.object

            .if [rax].TOBJ.flag & O_STATE

                NextItem()
            .endif
            mov eax,1
        .endif

        .if !eax
            .while 1
                tgetevent()
                test_event(eax, 0)
                mov eax,dlresult
                .break .if eax == _C_ESCAPE
                .break .if eax == _C_RETURN
            .endw
        .else

            msloop()
            xor edi,edi

            .repeat
                xor eax,eax
                mov dlresult,eax

                mov al,[rbx].DOBJ.index
                imul eax,eax,TOBJ
                add rax,[rbx].DOBJ.object

                .if [rax].TOBJ.flag & O_EVENT

                    call [rax].TOBJ.tproc
                .else
                    mov al,[rax]
                    and eax,0x0F
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
                mov eax,dlresult
                .if eax == _C_ESCAPE
                    mov event,0
                    .break
                .elseif eax == _C_RETURN
                    xor eax,eax

                    mov al,[rbx].DOBJ.index
                    imul eax,eax,TOBJ
                    add rax,[rbx].DOBJ.object

                    .if [rax].TOBJ.flag & O_DEXIT

                        mov event,0
                    .else
                        mov rdx,tdialog
                        movzx eax,[rdx].DOBJ.index
                        inc eax
                        mov event,eax
                    .endif
                    .break
                .elseif ecx == _O_MENUS && (event == KEY_LEFT || event == KEY_RIGHT)
                    inc edi
                .endif
            .until edi
        .endif

        _setcursor(&cursor)
        mov eax,event
    .until 1

    mov edx,eax
    mov tdialog,prevdlg
    mov eax,edx
    mov ecx,dlexit
    ret

dlevent endp

dllevent proc uses rbx ldlg:PDOBJ, listp:ptr LOBJ

    mov rbx,tdllist
    mov tdllist,listp
    dlevent(ldlg)
    mov tdllist,rbx
    ret

dllevent endp

    end

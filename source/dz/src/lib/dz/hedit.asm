; HEDIT.ASM--
; Copyright (C) 2017 Doszip Developers -- see LICENSE.TXT
;
include alloc.inc
include string.inc
include stdio.inc
include io.inc
include iost.inc
include direct.inc
include consx.inc
include tview.inc
include dzlib.inc
include ltype.inc

externdef   tvflag: byte
externdef   fsflag: byte
externdef   IDD_TVSeek:dword
externdef   IDD_TVHelp:dword
externdef   CP_ENOMEM:byte
externdef   searchstring:byte

cmsearchidd     proto :dword
continuesearch  proto :ptr
putscreenb      proto :dword, :dword, :ptr
SaveChanges     proto :LPSTR

.data

;******** Resource begin HEStatusline *
;   { 0x0054,   0,   0, { 0,24,80, 1} },
;******** Resource data  *******************
Statusline_RC   dw 0200h,0054h,0000h
                db 0
Statusline_Y    db 24
Statusline_C0   db 80,1
                db 0x3C,0x3F,0x3F,0xF0,7,0x3C,0x3F,0x3F,0xF0,7,0x3C,0x3F,0x3F,0xF0
                db 9,0x3C,0x3F,0x3F,0xF0,7,0x3C,0xF0,32,0x3C,0x3F,0x3F,0x3F,0xF0
Statusline_C1   db 6,0x3C
                db ' F1 Help  F2 Save  F3 Search  F4 Goto',0xF0,34,' Esc Quit '
                db 0xF0
Statusline_C2   db 1,' '
IDD_Statusline  dd Statusline_RC

;******** Resource begin HEMenusline *
;   { 0x0050,   0,   0, { 0, 0,80, 1} },
;******** Resource data  *******************
Menusline_RC    dw 0200h,0050h,0000h,0000h
Menusline_C0    db 80,1,0F0h
Menusline_C1    db 80,3Ch,0F0h
Menusline_C2    db 80,' '
IDD_Menusline   dd Menusline_RC

x_cpos  db 12, 15, 18, 21, 24, 27, 30, 33
        db 38, 41, 44, 47, 50, 53, 56, 59

    .code

savefile proc private uses esi edi ebx file:LPSTR

  local path[_MAX_PATH]:byte
  local flags:dword

    lea edi,path

    .repeat

        .if getfattr(strcpy(edi, file)) == -1

            xor eax,eax
            .break
        .endif

        mov flags,eax
        .if eax & _A_RDONLY

            ermsg(0, "The file is Read-Only")
        .endif

        .ifs ogetouth(setfext(edi, ".$$$"), M_WRONLY) <= 0

            xor eax,eax
            .break
        .endif
        mov esi,eax
        mov ebx,dword ptr STDI.ios_fsize
        .if oswrite(esi, STDI.ios_bp, ebx) != ebx

            xor ebx,ebx
        .endif
        _close(esi)
        .if ebx
            remove(file)
            rename(edi, file)
            mov eax,1
        .else
            mov eax,ebx
        .endif
    .until 1
    ret

savefile endp

tview_update proc private
    xor eax,eax
    ret
tview_update endp

hedit proc uses esi edi ebx file:LPSTR, offs:DWORD

  local loffs       :dword
  local dlgobj      :S_DOBJ   ; main dialog
  local dialog      :dword    ; main dialog pointer
  local rowcnt      :dword    ; screen lines
  local lcount      :dword    ; lines on screen
  local scount      :dword    ; bytes on screen
  local screen      :dword    ; screen buffer
  local menusline   :dword
  local statusline  :dword
  local cursor      :S_CURSOR ; cursor (old)
  local bsize       :dword    ; buffer size
  local x,y,index   :dword
  local linetable[256]:dword  ; line offset in file
  local rsrows      :byte
  local modified    :byte

    mov STDI.ios_flag,0
    mov eax,_scrcol
    mov Statusline_C0,al
    mov Menusline_C0,al
    mov Menusline_C1,al
    mov Menusline_C2,al
    mov Statusline_C1,6
    mov Statusline_C2,1
    sub al,80
    add Statusline_C1,al
    add Statusline_C2,al

    lea edi,linetable
    xor eax,eax
    mov modified,al
    mov ecx,256+16
    rep stosd
    mov x,12
    mov y,0
    mov eax,offs
    mov loffs,eax
    mov eax,_scrrow
    mov ebx,IDD_Statusline
    mov [ebx+7],al
    inc al
    mov rsrows,al
    .if tvflag & _TV_USEMLINE
        dec al
        inc y
    .endif
    .if tvflag & _TV_USESLINE
        dec al
    .endif
    mov rowcnt,eax ; adapt to current screen size
    add eax,2
    mul _scrcol

    .repeat

        .break .if !malloc(eax)
        mov screen,eax

        .ifs ioopen(&STDI, file, M_RDONLY, OO_MEM64K) > 0

            _filelength(STDI.ios_file)
            .if (!eax && !edx) || edx
                .if edx
                    ermsg(0, &CP_ENOMEM)
                .endif
                ioclose(&STDI)
                free(screen)
                xor eax,eax
                .break
            .endif

            mov ebx,eax
            mov dword ptr STDI.ios_fsize,eax
            mov dword ptr STDI.ios_fsize[4],edx
            .if !malloc(ebx)
                ermsg(0, &CP_ENOMEM)
                ioclose(&STDI)
                free(screen)
                xor eax,eax
                .break
            .endif
            mov ecx,STDI.ios_bp
            mov STDI.ios_bp,eax
            mov STDI.ios_size,ebx
            free(ecx)
            ioread(&STDI)
            or STDI.ios_flag,IO_MEMBUF
            _close(STDI.ios_file)
            mov STDI.ios_file,-1
        .else
            free(screen)
            xor eax,eax
            .break
        .endif

        mov al,at_background[B_TextView]
        or  al,at_foreground[F_TextView]
        .if dlscreen(&dlgobj, eax)

            mov dialog,eax
            dlshow(eax)
            mov menusline,rsopen(IDD_Menusline)
            dlshow(eax)
            mov statusline,rsopen(IDD_Statusline)
            .if tvflag & _TV_USESLINE
                dlshow(eax)
            .endif
            scpath(1, 0, 41, file)
            mov eax,_scrcol
            sub eax,38
            mov edx,dword ptr STDI.ios_fsize
            scputf(eax, 0, 0, 0, "%12u byte", edx)
            mov edx,_scrcol
            sub edx,5
            scputs(edx, 0, 0, 0, "100%")

            .if !(tvflag & _TV_USEMLINE)

                dlhide(menusline)
            .endif

            CursorGet(&cursor)
            CursorOn()

            push tupdate
            mov tupdate,tview_update

            msloop()
            ;
            ; offset of first <MAXLINES> lines
            ;
            xor eax,eax
            mov offs,eax
            xor edx,edx
            ioseek(&STDI, edx::eax, SEEK_SET)


            mov esi,1
            .while 1

                .if esi

                    _gotoxy(x, y)
                    mov scount,0

                    .repeat

                        mov lcount,1
                        mov eax,loffs
                        mov linetable,eax
                        mov offs,eax

                        .repeat

                            xor edx,edx
                            ioseek(&STDI, edx::eax, SEEK_SET)
                            .break .ifz
                            xor ecx,ecx
                            .while 1

                                mov eax,offs
                                add eax,16
                                mov offs,eax
                                .if eax > dword ptr STDI.ios_fsize
                                    mov eax,dword ptr STDI.ios_fsize
                                    mov offs,eax
                                    .break
                                .endif
                                mov eax,lcount
                                inc lcount
                                lea edx,linetable[eax*4]
                                mov eax,offs
                                mov [edx],eax
                                inc ecx
                                .break .if ecx >= rowcnt
                            .endw

                            mov eax,lcount
                            lea edx,linetable[eax*4]
                            mov eax,offs
                            mov [edx],eax
                            mov [edx+4],eax
                            or  eax,1
                        .until 1

                        .ifnz
                            mov eax,_scrcol
                            mul rowcnt
                            mov ecx,eax
                            mov edi,screen
                            mov eax,0x20
                            rep stosb
                            mov eax,loffs
                            mov offs,eax
                            xor edx,edx
                            ioseek(&STDI, edx::eax, SEEK_SET)
                        .endif
                        .break .ifz

                        ogetc()
                        .break .ifz

                        dec STDI.ios_i
                        push STDI.ios_c
                        mov eax,rowcnt
                        shl eax,4
                        .if eax <= STDI.ios_c
                            mov STDI.ios_c,eax
                        .endif
                        mov eax,STDI.ios_c
                        xor ecx,ecx
                        mov scount,eax
                        mov esi,screen

                        .repeat

                            mov edi,esi
                            lea ebx,linetable[ecx*4+3]

                            .for edx=4: edx: edx--, ebx--

                                mov al,[ebx]
                                mov ah,al
                                and eax,0x0FF0
                                shr al,4
                                or  eax,0x3030
                                .if ah > 0x39
                                    add ah,7
                                .endif
                                .if al > 0x39
                                    add al,7
                                .endif
                                stosw
                            .endf
                            inc edi

                            mov edx,STDI.ios_c
                            mov eax,16
                            add edi,3
                            .if edx >= eax
                                mov edx,eax
                            .endif
                            .break .if !edx
                            sub STDI.ios_c,edx
                            mov ebx,edi
                            add ebx,51
                            push ecx
                            mov ecx,edx
                            xor edx,edx
                            .repeat
                                .if edx == 8
                                    mov al,179
                                    stosb
                                    inc edi
                                .endif
                                mov eax,STDI.ios_i
                                .break .if eax >= dword ptr STDI.ios_fsize
                                add eax,STDI.ios_bp
                                mov al,[eax]
                                inc STDI.ios_i
                                mov [ebx],al
                                .if !al
                                    mov byte ptr [ebx],' '
                                .endif
                                mov ah,al
                                and eax,0x0FF0
                                shr al,4
                                or  eax,0x3030
                                .if ah > 0x39
                                    add ah,7
                                .endif
                                .if al > 0x39
                                    add al,7
                                .endif
                                stosw
                                inc edi
                                inc ebx
                                inc edx
                            .untilcxz
                            pop ecx
                            add esi,_scrcol
                            inc ecx
                        .until ecx >= lcount
                        pop eax
                        mov STDI.ios_c,eax
                        mov eax,1
                    .until 1

                    .if eax
                        .if tvflag & _TV_USEMLINE
                            mov eax,scount
                            add eax,loffs
                            .ifz
                                mov eax,100
                            .else
                                mov ecx,100
                                mul ecx
                                mov ecx,dword ptr STDI.ios_fsize
                                div ecx
                                and eax,0x7F
                                .if eax > 100
                                    mov eax,100
                                .endif
                            .endif
                            mov edx,_scrcol
                            sub edx,5
                            scputf(edx, 0, 0, 0, "%3d", eax)
                            .if modified
                                scputc(0, 0, 1, '*')
                            .else
                                scputc(0, 0, 1, ' ')
                            .endif
                        .endif
                        mov eax,dword ptr STDI.ios_fsize
                        .if eax
                            xor eax,eax
                            .if tvflag & _TV_USEMLINE
                                inc eax
                            .endif
                            putscreenb(eax, rowcnt, screen)
                        .endif
                    .endif
                    xor esi,esi
                .endif

                .switch tgetevent()

                  .case MOUSECMD

                    .endc .if mousep() == 2
                    .endc .if !eax
                    mousey()
                    inc eax
                    .endc .if !(tvflag & _TV_USESLINE) || al != rsrows
                    msloop()
                    mousex()
                    .if al && al <= 7
                        .gotosw(KEY_F1)
                    .endif
                    .if al >= 10 && al <= 16
                        .gotosw(KEY_F2)
                    .endif
                    .if al >= 19 && al <= 27
                        .gotosw(KEY_F3)
                    .endif
                    .if al >= 30 && al <= 36
                        .gotosw(KEY_F4)
                    .endif
                    .if al >= 71 && al <= 78
                        .gotosw(KEY_F10)
                    .endif
                    msloop()
                    .endc

                  .case KEY_F1
                    rsmodal(IDD_TVHelp)
                    .endc

                  .case KEY_F2
                    .if savefile(file)
                        mov modified,0
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_F3
                    and STDI.ios_flag,not IO_SEARCHMASK
                    mov al,fsflag
                    and eax,IO_SEARCHMASK
                    or  STDI.ios_flag,eax
                    xor eax,eax
                    .if dword ptr STDI.ios_fsize >= 16
                        .if cmsearchidd(STDI.ios_flag)
                            mov STDI.ios_flag,edx
                            and edx,IO_SEARCHCUR or IO_SEARCHSET
                            push edx
                            continuesearch(&loffs)
                            pop edx
                            or  STDI.ios_flag,edx
                        .endif
                    .endif
                    push eax
                    and fsflag,not IO_SEARCHMASK
                    mov eax,STDI.ios_flag
                    and STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
                    and al,IO_SEARCHMASK
                    or  fsflag,al
                    pop eax
                    .if eax
                        inc esi
                    .endif
                    .endc

                  .case KEY_F4
                    .if rsopen(IDD_TVSeek)
                        mov ebx,eax
                        mov edx,loffs
                        sprintf([ebx+24], "%08Xh", edx)
                        dlinit(ebx)
                        rsevent(IDD_TVSeek, ebx)
                        push eax
                        strtolx([ebx+24])
                        dlclose(ebx)
                        pop eax
                        .if eax && edx <= dword ptr STDI.ios_fsize
                            mov loffs,edx
                            mov esi,1
                        .endif
                    .endif
                    .endc

                  .case KEY_F10
                  .case KEY_ESC
                  .case KEY_ALTX
                    .if modified
                        .if SaveChanges(file)
                            savefile(file)
                        .endif
                    .endif
                    .break

                  .case KEY_ALTF5
                  .case KEY_CTRLB
                    dlhide(dialog)
                    .while !getkey()
                    .endw
                    dlshow(dialog)
                    .endc

                  .case KEY_CTRLM
                    xor tvflag,_TV_USEMLINE
                    .if tvflag & _TV_USEMLINE
                        dlshow(menusline)
                        dec rowcnt
                        inc y
                    .else
                        dlhide(menusline)
                        inc rowcnt
                        dec y
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_CTRLS
                    xor tvflag,_TV_USESLINE
                    .if tvflag & _TV_USESLINE
                        dlshow(statusline)
                        dec rowcnt
                        mov edx,statusline
                        movzx eax,[edx].S_DOBJ.dl_rect.rc_y
                        .if eax == y
                            dec y
                        .endif
                    .else
                        dlhide(statusline)
                        inc rowcnt
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_F11
                    .if !(tvflag & _TV_USESLINE or _TV_USEMLINE)
                        PushEvent(KEY_CTRLS)
                        .gotosw(KEY_CTRLM)
                    .endif
                    .if tvflag & _TV_USEMLINE
                        PushEvent(KEY_CTRLM)
                    .endif
                    .if tvflag & _TV_USESLINE
                        .gotosw(KEY_CTRLS)
                    .endif
                    .endc

                  ;--

                  .case KEY_CTRLE
                  .case KEY_UP
                    xor eax,eax
                    .if tvflag & _TV_USEMLINE
                        inc eax
                    .endif
                    .if eax == y
                        mov eax,loffs
                        mov offs,eax
                        .if eax
                            .if eax > dword ptr STDI.ios_fsize
                                mov eax,dword ptr STDI.ios_fsize
                            .else
                                .if eax <= 16
                                    xor eax,eax
                                .else
                                    sub eax,16
                                .endif
                            .endif
                        .endif
                        .if eax != loffs
                            mov loffs,eax
                            mov esi,1
                        .endif
                    .else
                        dec y
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_TAB
                    mov eax,index
                    mov edx,x
                    .if eax < 15
                        inc eax
                        mov dl,x_cpos[eax]
                        mov index,eax
                        mov x,edx
                        mov esi,1
                        .endc
                    .endif
                    mov dl,x_cpos
                    mov x,edx
                    mov index,0

                  .case KEY_CTRLX
                  .case KEY_DOWN
                    mov eax,scount
                    add eax,loffs
                    inc eax
                    .endc .if eax >= dword ptr STDI.ios_fsize
                    add eax,15
                    .if eax >= dword ptr STDI.ios_fsize
                        .gotosw(KEY_END)
                    .endif
                    mov eax,y
                    inc eax
                    mov edx,statusline
                    movzx edx,[edx].S_DOBJ.dl_rect.rc_y
                    .if !(tvflag & _TV_USESLINE)
                        inc edx
                    .endif
                    .if eax == edx
                        add loffs,16
                    .else
                        mov y,eax
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_CTRLR
                  .case KEY_PGUP
                    mov eax,loffs
                    .endc .if !eax
                    mov eax,rowcnt
                    shl eax,4
                    .if eax < loffs
                        sub loffs,eax
                    .else
                        xor eax,eax
                        mov loffs,eax
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_CTRLC
                  .case KEY_PGDN
                    mov eax,scount
                    add eax,loffs
                    inc eax
                    .endc .if eax >= dword ptr STDI.ios_fsize
                    mov ebx,eax
                    mov eax,rowcnt
                    shl eax,4
                    add ebx,eax
                    .if ebx >= dword ptr STDI.ios_fsize
                        .gotosw(KEY_END)
                    .endif
                    add loffs,eax
                    mov esi,1
                    .endc

                  .case KEY_LEFT
                    mov eax,index
                    mov edx,x
                    .if eax
                        movzx ecx,x_cpos[eax]
                        .if ecx == edx
                            dec eax
                            mov dl,x_cpos[eax]
                        .else
                            dec edx
                        .endif
                        mov index,eax
                        mov x,edx
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_RIGHT
                    mov eax,index
                    mov edx,x
                    .if eax <= 15
                        movzx ecx,x_cpos[eax]
                        .if ecx != edx
                            .if eax != 15
                                inc eax
                                mov dl,x_cpos[eax]
                            .endif
                        .else
                            inc edx
                        .endif
                        mov ecx,y
                        .if tvflag & _TV_USEMLINE
                            dec ecx
                        .endif
                        shl ecx,4
                        add ecx,eax
                        add ecx,loffs
                        .endc .if ecx >= dword ptr STDI.ios_fsize
                        mov index,eax
                        mov x,edx
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_HOME
                    sub eax,eax
                    mov loffs,eax
                    mov index,eax
                    .if tvflag & _TV_USEMLINE
                        inc eax
                    .endif
                    mov y,eax
                    mov al,x_cpos
                    mov x,eax
                    mov esi,1
                    .endc

                  .case KEY_END
                    mov ecx,dword ptr STDI.ios_fsize
                    mov edx,rowcnt
                    mov eax,edx
                    shl eax,4
                    inc eax
                    .if eax < ecx
                        sub eax,ecx
                        not eax
                        add eax,18
                        and eax,-16
                        mov loffs,eax
                    .endif
                    sub ecx,eax
                    mov eax,ecx
                    shr ecx,4
                    .if tvflag & _TV_USEMLINE
                        inc ecx
                    .endif
                    and eax,15
                    .ifnz
                        dec eax
                    .else
                        mov eax,15
                        dec ecx
                    .endif
                    mov index,eax
                    mov al,x_cpos[eax]
                    mov x,eax
                    mov y,ecx
                    mov esi,1
                    .endc

                  .case KEY_MOUSEUP
                    PushEvent(KEY_UP)
                    PushEvent(KEY_UP)
                    PushEvent(KEY_UP)
                    .endc

                  .case KEY_MOUSEDN
                    PushEvent(KEY_DOWN)
                    PushEvent(KEY_DOWN)
                    PushEvent(KEY_DOWN)
                    .endc

                  .case KEY_SHIFTF3
                  .case KEY_CTRLL
                    .if continuesearch(&loffs)
                        .gotosw(KEY_CTRLHOME)
                    .endif
                    .endc

                  .default
                    movzx eax,al
                    mov ebx,eax
                    .endc .if !(_ltype[eax+1] & _HEX)
                    mov eax,y
                    .if tvflag & _TV_USEMLINE
                        dec eax
                    .endif
                    shl eax,4
                    add eax,index
                    add eax,loffs
                    .endc .if eax > dword ptr STDI.ios_fsize
                    add eax,STDI.ios_bp
                    mov edx,eax
                    .if bl > '9'
                        or bl,0x20
                        sub bl,'a'-10
                    .else
                        sub bl,'0'
                    .endif
                    mov ecx,index
                    mov cl,x_cpos[ecx]
                    mov al,[edx]
                    .if ecx == x
                        shl bl,4
                        and al,0x0F
                    .else
                        and al,0xF0
                    .endif
                    or  al,bl
                    mov [edx],al
                    mov modified,1
                    mov esi,1
                    .gotosw(KEY_RIGHT)
                .endsw
            .endw

            ioclose(&STDI)
            free(screen)
            dlclose(statusline)
            dlclose(menusline)
            dlclose(dialog)
            CursorSet(&cursor)
            pop eax
            mov tupdate,eax
            xor eax,eax
            mov STDI.ios_flag,eax
        .else
            free(screen)
            ioclose(&STDI)
            mov eax,1
        .endif
    .until 1
    ret

hedit endp

    END

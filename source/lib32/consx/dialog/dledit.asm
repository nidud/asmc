include consx.inc
include string.inc
include ltype.inc

ticontinue  proto
tiretevent  proto
tinocando   proto
tidecx      proto :dword
tiincx      proto :dword
tistripend  proto :dword

    .data
    TI dd 0

    .code

    option proc: private
    assume edx: ptr TEDIT

getline proc uses esi edi
    mov edx,TI
    mov eax,[edx].ti_bp
    .if eax
        mov esi,eax
        mov edi,eax
        mov ecx,[edx].ti_bcol   ; terminate line
        xor eax,eax     ; set length of line
        mov [edi+ecx-1],al
        mov ecx,-1
        repne scasb
        not ecx
        dec ecx
        dec edi
        mov [edx].ti_bcnt,ecx
        sub ecx,[edx].ti_bcol   ; clear rest of line
        neg ecx
        rep stosb
        mov ecx,[edx].ti_bcnt
        mov eax,[edx].ti_bp
    .endif
    ret
getline endp

curlptr proc
    .if getline()
        add eax,[edx].ti_boff
        add eax,[edx].ti_xoff
    .endif
    ret
curlptr endp

needline proc
    .if !getline()
        pop eax              ; pop caller off the stack
        mov eax,_TE_CMFAILED ; operation fail (end of line/buffer)
    .endif
    ret
needline endp

event_home proc
    needline()
    xor eax,eax
    mov [edx].ti_boff,eax
    mov [edx].ti_xoff,eax
    ret
event_home endp

event_toend proc
    event_home()
    needline()
    tistripend(eax)
    .if ecx
        mov eax,[edx].ti_cols
        dec eax
        .ifs ecx <= eax
            mov eax,ecx
        .endif
        mov [edx].ti_xoff,eax
        mov ecx,[edx].ti_bcnt
        sub ecx,[edx].ti_cols
        inc ecx
        xor eax,eax
        .ifs eax <= ecx
            mov eax,ecx
        .endif
        mov [edx].ti_boff,eax
        add eax,[edx].ti_xoff
        .if eax > [edx].ti_bcnt
            dec [edx].ti_boff
        .endif
    .endif
    xor eax,eax
    ret
event_toend endp

event_left proc
    xor eax,eax
    .if eax != [edx].ti_xoff
        dec [edx].ti_xoff
    .elseif eax != [edx].ti_boff
        dec [edx].ti_boff
    .else
        mov eax,_TE_CMFAILED
        .if [edx].ti_flag & _TE_DLEDIT
            mov eax,_TE_RETEVENT
        .endif
    .endif
    ret
event_left endp

event_right proc
    mov ecx,curlptr()
    mov al,[eax]
    sub ecx,[edx].ti_xoff
    .if al
        mov eax,[edx].ti_cols
        dec eax
        .if eax > [edx].ti_xoff
            inc [edx].ti_xoff
            xor eax,eax
            ret
        .endif
    .endif
    .if strlen(ecx) >= [edx].ti_cols
        inc [edx].ti_boff
        xor eax,eax
        ret
    .endif
    mov eax,_TE_CMFAILED
    .if [edx].ti_flag & _TE_DLEDIT
        mov eax,_TE_RETEVENT
    .endif
    ret
event_right endp

event_delete proc
    .if curlptr()
        tistripend(eax)
        curlptr()
        .if ecx && byte ptr [eax]
            dec [edx].ti_bcnt
            mov ecx,eax
            strcpy(ecx, &[eax+1])
            or  [edx].ti_flag,_TE_MODIFIED
            mov eax,_TE_CONTINUE
            ret
        .endif
    .endif
    tinocando()
    ret
event_delete endp

event_backsp proc
    .if getline()
        mov eax,[edx].ti_xoff
        add eax,[edx].ti_boff
        .if !eax || !ecx
            tinocando()
        .else
            event_left()
            curlptr()
            .if tistripend(eax)

                event_delete()
            .endif
        .endif
    .endif
    ret
event_backsp endp

event_add proc uses ebx

    mov ebx,eax
    .repeat

        .if !getline()
            tinocando()
            .break
        .endif

        movzx eax,bl
        .if _ltype[eax+1] & _CONTROL

            .if !eax || !([edx].ti_flag & _TE_USECONTROL)
                mov eax,_TE_RETEVENT
                .break
            .endif
        .endif
        mov eax,[edx].ti_bcnt
        inc eax
        .if eax < [edx].ti_bcol
            tiincx(edx)
            .ifnz
                inc [edx].ti_bcnt
                .if getline()
                    or  [edx].ti_flag,_TE_MODIFIED
                    mov eax,[edx].ti_bp
                    add eax,[edx].ti_boff
                    add eax,[edx].ti_xoff
                    dec eax
                    strshr(eax, ebx)
                    xor eax,eax
                    .break
                .endif
            .endif
        .endif
        mov eax,[edx].ti_bcol
        dec eax
        mov [edx].ti_bcnt,eax
        tinocando()
    .until 1
    ret
event_add endp

_setcursor proc
  local cursor:S_CURSOR
    mov edx,TI
    mov eax,[edx].ti_xpos
    add eax,[edx].ti_xoff
    mov ecx,[edx].ti_ypos
    mov cursor.x,ax
    mov cursor.y,cx
    mov cursor.bVisible,1
    mov cursor.dwSize,CURSOR_NORMAL
    CursorSet(&cursor)
    ret
_setcursor endp

tievent proc

    mov edx,TI
    mov ecx,[edx].ti_flag

    .switch eax

      .case _TE_CONTINUE
        xor eax,eax ; _TI_CONTINUE - continue edit
        .endc

      .case KEY_CTRLRIGHT

        .endc .if !curlptr()

        mov edx,eax     ; to end of word
        mov ecx,eax
        xor eax,eax
        .repeat
            mov al,[ecx]
            inc ecx
        .until !(_ltype[eax+1] & _LABEL or _DIGIT)
        .endc .if !al
        .repeat         ; to start of word
            mov al,[ecx]
            inc ecx
            .endc .if !al
        .until _ltype[eax+1] & _LABEL or _DIGIT

        dec ecx
        sub ecx,edx
        mov edx,TI
        mov eax,[edx].ti_boff
        add eax,[edx].ti_xoff
        add eax,ecx
        .endc .if eax > [edx].ti_bcnt

        sub eax,[edx].ti_boff
        mov ecx,[edx].ti_cols
        .if eax >= ecx
            dec ecx
            sub eax,ecx
            add [edx].ti_boff,eax
            mov [edx].ti_xoff,ecx
        .else
            mov [edx].ti_xoff,eax
        .endif
        mov eax,_TE_CONTINUE
        .endc

      .case KEY_CTRLLEFT

        .endc .if !getline()

        mov ecx,eax
        mov eax,[edx].ti_boff
        add eax,[edx].ti_xoff
        .endc .ifz

        lea edx,[eax+ecx-1]
        movzx eax,byte ptr [edx]
        .while ecx < edx && !( _ltype[eax+1] & _LABEL or _DIGIT )
            sub edx,1
            mov al,[edx]
        .endw
        .while ecx < edx && _ltype[eax+1] & _LABEL or _DIGIT
            sub edx,1
            mov al,[edx]
        .endw
        .if !( _ltype[eax+1] & _LABEL or _DIGIT )

            mov al,[edx+1]
            .if _ltype[eax+1] & _LABEL or _DIGIT

                add edx,1
            .endif
        .endif
        mov eax,TI
        xchg eax,edx
        add ecx,[edx].ti_boff
        add ecx,[edx].ti_xoff
        sub ecx,eax
        .if ecx > [edx].ti_xoff

            sub ecx,[edx].ti_xoff
            mov [edx].ti_xoff,0
            sub [edx].ti_boff,ecx
        .else
            sub [edx].ti_xoff,ecx
        .endif
        mov eax,_TE_CONTINUE
        .endc

      .case KEY_LEFT
        event_left()
        .endc

      .case KEY_RIGHT
        event_right()
        .endc
      .case KEY_HOME
        event_home()
        .endc
      .case KEY_END
        event_toend()
        .endc
      .case KEY_BKSP
        event_backsp()
        .endc

      .case KEY_DEL
        event_delete()
        .endc

      .case MOUSECMD
        mov ecx,keybmouse_x
        mov eax,[edx].ti_xpos
        .if ecx >= eax
            add eax,[edx].ti_cols
            .if ecx < eax
                mov eax,[edx].ti_ypos
                .if eax == keybmouse_y
                    push ecx
                    getline()
                    .ifnz
                        strlen(eax)
                    .endif
                    pop ecx
                    sub ecx,[edx].ti_xpos
                    .ifs ecx <= eax
                        mov eax,ecx
                    .endif
                    mov [edx].ti_xoff,eax
                    _setcursor()
                    msloop()
                    sub eax,eax
                    .endc
                .endif
            .endif
        .endif

      .case KEY_UP
      .case KEY_DOWN
      .case KEY_PGUP
      .case KEY_PGDN
      .case KEY_CTRLPGUP
      .case KEY_CTRLPGDN
      .case KEY_CTRLHOME
      .case KEY_CTRLEND
      .case KEY_CTRLUP
      .case KEY_CTRLDN
      .case KEY_MOUSEUP
      .case KEY_MOUSEDN
      .case KEY_ENTER
      .case KEY_KPENTER
      .case KEY_ESC
        mov eax,_TE_RETEVENT ; return current event (keystroke)
        .endc
      .case KEY_TAB
        .if !(ecx & _TE_USECONTROL)

            mov eax,_TE_RETEVENT ; return current event (keystroke)
            .endc
        .endif
        mov eax,9
      .default
        event_add()
        .endc
    .endsw
    ret
tievent endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ClipIsSelected proc
    mov edx,TI
    mov eax,[edx].ti_cleo
    sub eax,[edx].ti_clso
    ret
ClipIsSelected endp

ClipSet proc
    mov edx,TI
    mov eax,[edx].ti_xoff
    add eax,[edx].ti_boff
    mov [edx].ti_clso,eax
    mov [edx].ti_cleo,eax
    ret
ClipSet endp

ClipDelete proc
    .if ClipIsSelected()
        mov eax,[edx].ti_clso
        mov ecx,[edx].ti_xoff
        add ecx,[edx].ti_boff
        .if ecx < eax
            .repeat
                tiincx( edx )
                .break .if ZERO?
                inc ecx
            .until  eax == ecx
            inc ecx
        .elseif ecx > eax
            .repeat
                tidecx( edx )
                .break .if ZERO?
                dec ecx
            .until  eax == ecx
            inc ecx
        .endif
        mov eax,[edx].ti_bp
        or  [edx].ti_flag,_TE_MODIFIED
        mov ecx,eax
        add eax,[edx].ti_clso
        add ecx,[edx].ti_cleo
        strcpy(eax, ecx)
        getline()
        ClipSet()
        xor eax,eax
        inc eax
    .endif
    ret
ClipDelete endp

ClipCopy proc
    xor eax,eax
    jmp ClipCC
ClipCopy endp

ClipCut proc
    mov eax,1
ClipCut endp

ClipCC proc uses esi edi
    mov esi,TI
    mov edi,eax      ; AX: Copy == 0, Cut == 1
    .repeat
        ClipIsSelected() ; get size of selection
        .ifnz
            mov edx,TI
            mov eax,[edx].ti_bp
            add eax,[edx].ti_clso
            mov ecx,[edx].ti_cleo
            sub ecx,[edx].ti_clso
            .break .if !ClipboardCopy(eax, ecx)
            .if edi
                ClipDelete()
            .endif
        .endif
        ClipSet()
    .until 1
    xor eax,eax
    ret
ClipCC endp

ClipPaste proc uses esi edi ebx
    mov edx,TI
    mov eax,[edx].ti_flag
    .if eax & _TE_OVERWRITE
        ClipDelete()
    .else
        ClipSet()
    .endif
    ClipboardPaste()
    .ifnz
        mov edx,TI
        push [edx].ti_xoff
        push [edx].ti_boff
        mov edi,eax
        mov esi,ecx ; clipbsize
        .repeat
            mov al,[edi]
            .break .if !al
            inc edi
            .break .if event_add() != _TE_CONTINUE
            dec esi
        .untilz
        ClipboardFree()
        mov edx,TI
        pop eax
        mov [edx].ti_boff,eax
        pop eax
        mov [edx].ti_xoff,eax
    .endif
    ClipSet()
    xor eax,eax
    ret
ClipPaste endp

ClipEvent proc uses esi edi ebx
    mov esi,eax
    ClipIsSelected()
    .ifz
        ClipSet()       ; reset clipboard if not selected
    .endif
    .repeat
        .switch esi
          .case KEY_CTRLINS
          .case KEY_CTRLC
            ClipCopy()
            .endc
          .case KEY_CTRLV
            ClipPaste()
            .endc
          .case KEY_CTRLDEL
            ClipCut()
            .endc
          .default
            mov eax,keyshift
            mov eax,[eax]
            .if eax & SHIFT_KEYSPRESSED
                .switch esi
                  .case KEY_INS     ; Shift-Insert -- Paste()
                    .gotosw1(KEY_CTRLV)
                  .case KEY_DEL     ; Shift-Del -- Cut()
                    .gotosw1(KEY_CTRLDEL)
                  .case KEY_HOME
                  .case KEY_LEFT
                  .case KEY_RIGHT
                  .case KEY_END
                    mov eax,esi     ; consume event, return null
                    tievent()
                    .if eax == _TE_CMFAILED || eax == _TE_RETEVENT
                        xor eax,eax
                        .break
                    .endif
                    mov ebx,TI
                    mov eax,[ebx].TEDIT.ti_boff
                    add eax,[ebx].TEDIT.ti_xoff
                    .if eax >= [ebx].TEDIT.ti_clso
                        .if esi == KEY_RIGHT
                            mov edx,eax
                            dec edx
                            .if edx == [ebx].TEDIT.ti_clso
                                .if edx != [ebx].TEDIT.ti_cleo
                                    mov [ebx].TEDIT.ti_clso,eax
                                    xor eax,eax
                                    .break
                                .endif
                            .endif
                        .endif
                        mov [ebx].TEDIT.ti_cleo,eax
                        xor eax,eax
                        .break
                    .endif
                    mov [ebx].TEDIT.ti_clso,eax
                    xor eax,eax
                    .break
                .endsw
            .endif
            .if esi == KEY_DEL     ; Delete selected text ?
                ClipDelete()
                .ifz
                    ClipSet()      ; set clipboard to cursor
                    mov eax,esi    ; return event
                    .endc
                .endif
                xor eax,eax
                .endc
            .endif
            xor ecx,ecx
            .switch esi
              .case KEY_ESC
              .case MOUSECMD
              .case KEY_BKSP
              .case KEY_ENTER
              .case KEY_KPENTER
              .case KEY_TAB
                inc ecx
              .default
                mov eax,esi
                .if !al
                    inc ecx
                .endif
                .endc
            .endsw
            .if !ecx
                ClipDelete()
            .endif
            ClipSet()           ; set clipboard to cursor
            mov eax,esi         ; return event
        .endsw
    .until 1
    ret
ClipEvent endp

putline proc uses esi edi ebx
local ci[256]:dword, bz:COORD, rc:SMALL_RECT

    _setcursor()

    lea edi,ci
    mov edx,TI
    mov ebx,[edx].ti_cols
    mov eax,[edx].ti_clat
    mov cl,al
    mov al,0
    shl eax,8
    mov al,cl
    mov ecx,ebx
    rep stosd

    mov esi,[edx].ti_bp
    .if strlen(esi) > [edx].ti_boff

        add esi,[edx].ti_boff
        mov ecx,ebx
        lea edi,ci

        .repeat
            mov al,[esi]
            .break .if !al
            mov [edi],al
            inc esi
            add edi,4
        .untilcxz
    .endif

    mov edi,[edx].ti_boff
    mov ecx,[edx].ti_cleo

    .if edi < ecx

        sub ecx,edi
        xor eax,eax
        .if ecx >= ebx

            mov ecx,ebx
        .endif
        .if [edx].ti_clso >= edi

            mov eax,[edx].ti_clso
            sub eax,edi
            .if eax <= ecx
                sub ecx,eax
            .else
                xor ecx,ecx
            .endif
        .endif
        .if ecx

            lea edi,ci
            lea edi,[edi+eax*4+2]
            mov al,at_background[B_Inverse]
            .repeat
                mov [edi],al
                add edi,4
            .untilcxz
        .endif
    .endif

    mov ecx,ebx
    mov bz.x,cx
    mov eax,[edx].ti_xpos
    mov rc.Left,ax
    add eax,ecx
    dec eax
    mov rc.Right,ax
    mov eax,[edx].ti_ypos
    mov rc.Top,ax
    mov rc.Bottom,ax
    mov bz.y,1
    WriteConsoleOutput(hStdOutput, &ci, bz, 0, &rc)
    ret
putline endp

modal proc uses esi edi
    xor esi,esi
    .repeat
        .if !esi
            getline()
            putline()
        .endif
        tgetevent()
        mov edi,ClipEvent()
        mov esi,tievent()
    .until  eax == _TE_RETEVENT
    getline()
    mov eax,edi ; return current event (keystroke)
    ret
modal endp

;-------------------------------------------------------------------------------
    option proc: PUBLIC
;-------------------------------------------------------------------------------

dledit proc uses edi b:LPSTR, rc, bz, oflag
  local t:TEDIT
  local cursor:S_CURSOR

    CursorGet(&cursor)

    lea edi,t
    xor eax,eax
    mov ecx,SIZE TEDIT
    rep stosb
    mov edi,TI
    lea eax,t
    mov TI,eax

    movzx eax,rc.S_RECT.rc_x
    mov t.ti_xpos,eax
    mov al,rc.S_RECT.rc_y
    mov t.ti_ypos,eax
    mov al,rc.S_RECT.rc_col
    mov t.ti_cols,eax
    mov eax,bz
    mov t.ti_bcol,eax
    mov eax,b
    mov t.ti_bp,eax
    mov eax,oflag
    and eax,_O_CONTR or _O_DLGED
    or  eax,_TE_OVERWRITE
    mov t.ti_flag,eax
    _setcursor()
    getxya(t.ti_xpos, t.ti_ypos)
    shl eax,8
    mov al,tclrascii
    mov t.ti_clat,eax  ; save text color
    .if oflag & _O_DTEXT
        event_toend()
        mov eax,t.ti_xoff
        add eax,t.ti_boff
        mov t.ti_cleo,eax
    .endif
    modal()
    push eax
    putline()
    CursorSet(&cursor)
    pop eax
    mov TI,edi
    ret
dledit endp

dledite proc uses edi t:PVOID, event
    mov edi,TI
    mov eax,t
    mov TI,eax
    getline()
    putline()
    mov eax,event
    .if !eax
        tgetevent()
        mov event,eax
    .endif
    ClipEvent()
    tievent()
    push eax
    getline()
    putline()
    pop edx
    xor eax,eax
    .if edx == _TE_RETEVENT
        mov eax,event
    .endif
    mov TI,edi
    ret
dledite endp

    END

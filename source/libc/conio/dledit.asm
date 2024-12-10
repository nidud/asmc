; DLEDIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __UNIX__
include winuser.inc
endif
include conio.inc
include tchar.inc
include ltype.inc

define _TE_CONTINUE     1 ; continue edit
define _TE_RETEVENT     2 ; return current event (keystroke)

    .code

    option proc:private

ClipIsSelected proto fastcall :PTEDIT {
    mov eax,[rcx].clip_eo
    sub eax,[rcx].clip_so
    }

ClipSet proto fastcall :PTEDIT {
    mov eax,[rcx].boffs
    add eax,[rcx].xoffs
    mov [rcx].clip_so,eax
    mov [rcx].clip_eo,eax
    }


    assume rcx:PTEDIT

IncreaseX proc fastcall ti:PTEDIT

    mov eax,[rcx].boffs
    add eax,[rcx].xoffs
    inc eax
    .if eax >= [rcx].bcols
        xor eax,eax
    .else
        mov edx,[rcx].boffs
        mov eax,[rcx].xoffs
        inc eax
        .if eax >= [rcx].scols
            mov eax,[rcx].scols
            dec eax
            inc edx
        .endif
        mov [rcx].xoffs,eax
        mov [rcx].boffs,edx
    .endif
    ret

IncreaseX endp


tinocando proc fastcall ti:PTEDIT

    .if ( [rcx].flags & TE_USEBEEP )
ifdef __UNIX__
        _cout("\x7")
else
        MessageBeep(MB_ICONERROR)
endif
    .endif
    .return( 0 ) ; operation fail (end of line/buffer)

tinocando endp


tistripend proc fastcall uses rbx string:LPTSTR

    mov rbx,rcx
    .ifd _tcsclen(rcx)

        mov ecx,eax
        lea rbx,[rbx+rax*TCHAR]
        .repeat

            sub rbx,TCHAR
            movzx eax,TCHAR ptr [rbx]
            .break .if ( eax != ' ' && eax != 9 )
            mov TCHAR ptr [rbx],0
        .untilcxz
        mov rax,rcx
    .endif
    ret

tistripend endp


    assume rbx:PTEDIT

getline proc fastcall uses rdi rbx ti:PTEDIT

    mov rax,[rcx].base
    .if rax
        mov     rbx,rcx
        mov     rdi,rax
        mov     edx,[rcx].bcols     ; terminate line
        xor     eax,eax             ; set length of line
        mov     ecx,-1
        mov     [rdi+rdx*TCHAR-TCHAR],_tal
        repne   _tscasb
        not     ecx
        dec     ecx
        sub     rdi,TCHAR
        mov     [rbx].bcount,ecx
        sub     ecx,[rbx].bcols     ; clear rest of line
        neg     ecx
        rep     _tstosb
        mov     rcx,rbx
        mov     edx,[rcx].bcount
        mov     rax,[rcx].base
    .endif
    ret

getline endp


curlptr proc fastcall ti:PTEDIT

    .if getline(rcx)

        mov edx,[rcx].boffs
        add edx,[rcx].xoffs
        lea rax,[rax+rdx*TCHAR]
    .endif
    ret

curlptr endp


event_home proc fastcall ti:PTEDIT

    .if getline(rcx)

        xor eax,eax
        mov [rcx].boffs,eax
        mov [rcx].xoffs,eax
        inc eax
    .endif
    ret

event_home endp


event_toend proc fastcall uses rbx ti:PTEDIT

    mov rbx,rcx
    event_home(rcx)

    .if getline(rcx)

        tistripend(rax)

        .if ecx

            mov eax,[rbx].scols
            dec eax
            .ifs ecx <= eax
                mov eax,ecx
            .endif
            mov [rbx].xoffs,eax
            mov ecx,[rbx].bcount
            sub ecx,[rbx].scols
            inc ecx
            xor eax,eax
            .ifs eax <= ecx
                mov eax,ecx
            .endif
            mov [rbx].boffs,eax
            add eax,[rbx].xoffs
            .if eax > [rbx].bcount
                dec [rbx].boffs
            .endif
        .endif
        mov rcx,rbx
        mov eax,1
    .endif
    ret

event_toend endp


event_left proc fastcall ti:PTEDIT

    .if ( [rcx].xoffs )

        dec [rcx].xoffs
       .return( 1 )
    .endif

    .if ( [rcx].boffs )

        dec [rcx].boffs
       .return( 1 )
    .endif
    .return( 0 )

event_left endp


event_right proc fastcall uses rbx ti:PTEDIT

    mov rbx,rcx
    .if curlptr(rcx)

        mov rcx,rax
        movzx eax,TCHAR ptr [rax]
        mov edx,[rbx].xoffs
        shl edx,1
        sub rcx,rdx
        .if eax

            mov eax,[rbx].scols
            dec eax
            .if eax > [rbx].xoffs
                inc [rbx].xoffs
               .return( 1 )
            .endif
        .endif

        _tcsclen(rcx)
        .if eax >= [rbx].scols
            inc [rbx].boffs
           .return( 1 )
        .endif
        xor eax,eax
    .endif
    ret

event_right endp


event_delete proc fastcall uses rbx ti:PTEDIT

    mov rbx,rcx
    .if curlptr(rcx)

        tistripend(rax)
        .if ( ecx )

            curlptr(rbx)
            .if TCHAR ptr [rax]
                dec [rbx].bcount
                mov rcx,rax
                _tcscpy(rcx, &[rax+TCHAR])
                or  [rbx].flags,TE_MODIFIED
               .return( 1 )
            .endif
        .endif
    .endif
    .return(tinocando(rbx))

event_delete endp


event_back proc fastcall uses rbx ti:PTEDIT

    mov rbx,rcx

    .if getline(rcx)

        mov eax,[rbx].xoffs
        add eax,[rbx].boffs

        .if ( !eax || ![rbx].bcount )

            tinocando()

        .else

            event_left(rbx)
            .if tistripend(curlptr(rbx))

                event_delete(rbx)
            .endif
        .endif
    .endif
    ret

event_back endp


event_add proc fastcall uses rsi rdi rbx ti:PTEDIT, c:int_t

    mov rbx,rcx
    movzx esi,dx

    .if ( esi == 0 || esi == 10 || esi == 13 )

        .return( 0 )
    .endif
    .if ( _tdl == 0 )
        .return( _TE_RETEVENT )
    .endif

    .if ( getline(rcx) == NULL )

        .return
    .endif

    lea rcx,_ltype
    mov eax,esi

    .if ( !ah && byte ptr [rcx+rax] & _CONTROL )
        .if ( !( [rbx].flags & TE_CONTROL ) )
            .return( _TE_RETEVENT )
        .endif
    .endif

    mov eax,[rbx].bcount
    inc eax

    .if ( eax < [rbx].bcols )

        .ifd IncreaseX(rbx)

            inc [rbx].bcount
            .if getline(rbx)

                or      [rbx].flags,TE_MODIFIED
                mov     eax,[rbx].boffs
                add     eax,[rbx].xoffs
                mov     rcx,[rbx].base
                lea     rdi,[rcx+rax*TCHAR-TCHAR]
                mov     edx,esi
                mov     ecx,-1
                xor     eax,eax
                repnz   _tscasb
                not     ecx
                inc     ecx
                mov     rsi,rdi
                add     rdi,TCHAR
                std
                rep     _tmovsb
                mov     [rdi],_tdl
                cld

               .return( 1 )
            .endif
        .endif
    .endif

    mov eax,[rbx].bcols
    dec eax
    mov [rbx].bcount,eax
   .return(tinocando(rbx))

event_add endp


event_nextword proc fastcall uses rsi rbx ti:PTEDIT

    mov rbx,rcx
   .return .if !curlptr(rcx)

    lea rsi,_ltype
    mov rdx,rax
    mov rcx,rax
    movzx eax,TCHAR ptr [rcx]

    .while ( ah || byte ptr [rsi+rax] & _LABEL )

        add rcx,TCHAR
        movzx eax,TCHAR ptr [rcx]
    .endw

    .while ( eax && !ah && !( byte ptr [rsi+rax] & _LABEL ) )

        add rcx,TCHAR
        movzx eax,TCHAR ptr [rcx]
    .endw

   .return .ifd !eax

    sub rcx,rdx
    shr ecx,TCHAR-1

    mov eax,[rbx].boffs
    add eax,[rbx].xoffs
    add eax,ecx
   .return( 0 ) .if ( eax > [rbx].bcount )

    sub eax,[rbx].boffs
    mov ecx,[rbx].scols
    .if ( eax >= ecx )
        dec ecx
        sub eax,ecx
        add [rbx].boffs,eax
        mov [rbx].xoffs,ecx
    .else
        mov [rbx].xoffs,eax
    .endif
    .return( 1 )

event_nextword endp


event_prevword proc fastcall uses rsi rbx ti:PTEDIT

    mov rbx,rcx
   .return .if !curlptr(rcx)

    mov rcx,rax
    mov eax,[rbx].boffs
    add eax,[rbx].xoffs
   .return .ifz

    lea rsi,_ltype
    movzx eax,TCHAR ptr [rcx]

    .if ( ah || byte ptr [rsi+rax] & _LABEL )

        sub rcx,TCHAR
    .endif

    mov rdx,[rbx].base
    movzx eax,TCHAR ptr [rcx]

    .while ( rcx > rdx && !( ah || byte ptr [rsi+rax] & _LABEL ) )

        sub rcx,TCHAR
        movzx eax,TCHAR ptr [rcx]
    .endw

    .while ( rcx > rdx && ( ah || byte ptr [rsi+rax] & _LABEL ) )

        sub rcx,TCHAR
        movzx eax,TCHAR ptr [rcx]
    .endw

    .if ( !( ah || byte ptr [rsi+rax] & _LABEL ) )

        movzx eax,TCHAR ptr [rcx+TCHAR]
        .if ( ah || byte ptr [rsi+rax] & _LABEL )
            add rcx,TCHAR
        .endif
        movzx eax,TCHAR ptr [rcx]
    .endif

    sub rcx,[rbx].base
    shr ecx,TCHAR-1

    .if ( ecx > [rbx].xoffs )

        sub ecx,[rbx].xoffs
        mov [rbx].xoffs,0
        mov [rbx].boffs,ecx
    .else
        mov [rbx].xoffs,ecx
    .endif
    .return( 1 )

event_prevword endp


ClipDelete proc fastcall uses rsi rdi ti:PTEDIT

    .if ClipIsSelected(rcx)

        mov edi,[rcx].clip_so
        mov esi,[rcx].xoffs
        add esi,[rcx].boffs

        .if ( esi < edi )

            .repeat
               .break .ifd !IncreaseX(rcx)
                inc esi
            .until ( edi == esi )

        .elseif ( esi > edi )

            .repeat
                .if [rcx].xoffs
                    dec [rcx].xoffs
                .elseif [rcx].boffs
                    dec [rcx].boffs
                .else
                    .break
                .endif
                dec esi
            .until ( edi == esi )
        .endif

        or  [rcx].flags,TE_MODIFIED
        mov rdi,[rcx].base
        mov eax,[rcx].clip_so
        mov edx,[rcx].clip_eo
        lea rax,[rdi+rax*TCHAR]
        lea rdx,[rdi+rdx*TCHAR]
        mov rsi,rcx

        _tcscpy(rax, rdx)
        getline(rsi)
        ClipSet(rcx)
        mov eax,1
    .endif
    ret

ClipDelete endp


ClipCopy proc uses rbx ti:PTEDIT, Cut:BOOL

    ldr rbx,ti
    .if ClipIsSelected(rbx) ; get size of selection

        mov edx,eax
        mov eax,[rbx].clip_so
        mov rcx,[rbx].base
        lea rcx,[rcx+rax*TCHAR]

        .if _clipset(rcx, edx)
            .if Cut
                ClipDelete(rbx)
            .endif
        .endif
        ClipSet(rbx)
    .endif
    .return( 1 )

ClipCopy endp


ClipPaste proc fastcall uses rbx ti:PTEDIT

   .new bo:int_t
   .new xo:int_t
   .new n:int_t
   .new p:string_t

    mov rbx,rcx
    .if [rcx].flags & TE_OVERWRITE
        ClipDelete(rcx)
    .else
        ClipSet(rcx)
    .endif

    .if _clipget()

        mov p,rax
        mov eax,[rbx].xoffs
        mov ecx,[rbx].boffs
        mov edx,[rbx].bcols
        sub edx,ecx
        mov n,edx
        mov xo,eax
        mov bo,ecx

        .for ( : n > 0 : n-- )

            mov rax,p
            movzx edx,TCHAR ptr [rax]
            add p,TCHAR
            .break .if !event_add(rbx, edx)
        .endf
        mov [rbx].boffs,bo
        mov [rbx].xoffs,xo
    .endif
    ClipSet(rbx)
   .return( 1 )

ClipPaste endp

setcursor proc fastcall ti:PTEDIT

  local cursor:CURSOR

    mov eax,[rcx].xpos
    add eax,[rcx].xoffs
    mov edx,[rcx].ypos
    mov cursor.x,al
    mov cursor.y,dl
    mov cursor.visible,1
    mov cursor.type,CURSOR_DEFAULT
    _setcursor(&cursor)
    ret

setcursor endp

putline proc uses rsi rdi rbx ti:PTEDIT

   .new ci[MAXSCRLINE]:CHAR_INFO
   .new i:int_t
   .new x:byte

    ldr rbx,ti

    setcursor(rbx)
    lea rdi,ci
    mov ecx,[rbx].scols
    mov eax,[rbx].clrattrib
    rep stosd

    _tcslen([rbx].base)
    mov rsi,[rbx].base

    .if ( eax > [rbx].boffs )

        mov eax,[rbx].boffs
        lea rsi,[rsi+rax*TCHAR]
        mov ecx,[rbx].scols
        lea rdi,ci

        .repeat
            movzx eax,TCHAR ptr [rsi]
            .break .if !eax
            mov [rdi],ax
            add rsi,TCHAR
            add rdi,4
        .untilcxz
    .endif

    mov edi,[rbx].boffs
    mov ecx,[rbx].clip_eo

    .if ( edi < ecx )

        sub ecx,edi
        xor eax,eax
        .if ( ecx >= [rbx].scols )

            mov ecx,[rbx].scols
        .endif
        .if ( [rbx].clip_so >= edi )

            mov eax,[rbx].clip_so
            sub eax,edi
            .if eax <= ecx
                sub ecx,eax
            .else
                xor ecx,ecx
            .endif
        .endif
        .if ecx

            lea rdi,ci
            lea rdi,[rdi+rax*4+2]
            mov al,[rdi]
            and al,0x0F
            or  al,at_background[BG_INVERSE]
            .repeat
                mov [rdi],al
                add rdi,4
            .untilcxz
        .endif
    .endif

    .for ( i = 0 : i < [rbx].scols : i++ )

        mov ecx,i
        mov eax,[rbx].xpos
        add eax,ecx
        mov x,al
        _scputw(x, byte ptr [rbx].ypos, 1, ci[rcx*4])
    .endf
    .return( 0 )

putline endp


ti_event proc uses rsi rdi rbx ti:PTEDIT, event:uint_t

    ldr rbx,ti
    ldr eax,event

    mov ecx,[rbx].flags

    .switch eax
    .case _TE_CONTINUE
        mov eax,1 ; _TI_CONTINUE - continue edit
       .endc
    .case KEY_CTRL or KEY_RIGHT
        event_nextword(rbx)
       .endc
    .case KEY_CTRL or KEY_LEFT
        event_prevword(rbx)
       .endc
    .case KEY_LEFT
        event_left(rbx)
       .endc
    .case KEY_RIGHT
        event_right(rbx)
       .endc
    .case KEY_HOME
        event_home(rbx)
       .endc
    .case KEY_END
        event_toend(rbx)
       .endc
    .case KEY_BKSP
        event_back(rbx)
       .endc
    .case KEY_DELETE
        event_delete(rbx)
       .endc
    .case MOUSECMD
        mov edx,mousey()
        mov ecx,mousex()
        mov eax,[rbx].xpos

        .if ecx >= eax

            add eax,[rbx].scols
            .if ecx < eax

                mov eax,[rbx].ypos
                .if eax == edx

                    .if getline(rbx)
                        _tcslen(rax)
                    .endif
                    mov edx,eax
                    mov ecx,mousex()
                    sub ecx,[rbx].xpos
                    .ifs ecx <= edx
                        mov edx,ecx
                    .endif
                    mov [rbx].xoffs,edx
                    setcursor(rbx)
                    msloop()
                    mov eax,1
                   .endc
                .endif
            .endif
        .endif

    .case KEY_UP
    .case KEY_DOWN
    .case KEY_PGUP
    .case KEY_PGDN
    .case KEY_CTRL or KEY_PGUP
    .case KEY_CTRL or KEY_PGDN
    .case KEY_CTRL or KEY_HOME
    .case KEY_CTRL or KEY_END
    .case KEY_CTRL or KEY_UP
    .case KEY_CTRL or KEY_DOWN
    .case KEY_MOUSEUP
    .case KEY_MOUSEDN
    .case KEY_RETURN
    .case KEY_KPRETURN
    .case KEY_ESC
        mov eax,_TE_RETEVENT ; return current event (keystroke)
       .endc
    .case KEY_TAB
        .if !( ecx & TE_CONTROL )

            mov eax,_TE_RETEVENT ; return current event (keystroke)
           .endc
        .endif
        mov eax,9
    .default
        event_add(rbx, eax)
       .endc
    .endsw
    ret

ti_event endp


ClipEvent proc uses rbx ti:PTEDIT, event:uint_t

    ldr rbx,ti

    .ifd !ClipIsSelected(rbx)

        ClipSet(rbx) ; reset clipboard if not selected
    .endif

    mov eax,event
    .switch eax
    .case KEY_CTRLINS
    .case KEY_CTRLC
        ClipCopy(rbx, 0)
       .endc
    .case KEY_CTRLV
        ClipPaste(rbx)
       .endc
    .case KEY_CTRLDEL
        ClipCopy(rbx, 1)
       .endc
    .default

        .if eax & KEY_SHIFT

            and eax,not KEY_SHIFT
            .switch eax
            .case KEY_INSERT            ; Shift-Insert -- Paste()
                .gotosw(1:KEY_CTRLV)
            .case KEY_DELETE            ; Shift-Del -- Cut()
                .gotosw(1:KEY_CTRLDEL)
            .case KEY_HOME
            .case KEY_LEFT
            .case KEY_RIGHT
            .case KEY_END

                mov event,eax
                ti_event(rbx, eax)      ; consume event, return null
                .if ( eax == 0 || eax == _TE_RETEVENT )

                    .return( 1 )
                .endif

                mov eax,[rbx].boffs
                add eax,[rbx].xoffs

                .if ( eax >= [rbx].clip_so )

                    .if ( event == KEY_RIGHT )

                        mov edx,eax
                        dec edx
                        .if ( edx == [rbx].clip_so )

                            .if ( edx != [rbx].clip_eo )

                                mov [rbx].clip_so,eax
                               .return( 1 )
                            .endif
                        .endif
                    .endif
                    mov [rbx].clip_eo,eax
                   .return( 1 )
                .endif
                mov [rbx].clip_so,eax
               .return( 1 )
            .endsw
        .endif

        mov eax,event
        .if eax == KEY_DELETE       ; Delete selected text ?

            .if !ClipDelete(rbx)

                ClipSet(rbx)        ; set clipboard to cursor
                mov eax,KEY_DELETE  ; return event
               .endc
            .endif
            xor eax,eax
           .endc
        .endif

        xor ecx,ecx
        .switch eax
        .case KEY_ESC
        .case MOUSECMD
        .case KEY_BKSP
        .case KEY_RETURN
        .case KEY_KPRETURN
        .case KEY_TAB
            inc ecx
        .default
            .if !al
                inc ecx
            .endif
            .endc
        .endsw
        .if !ecx
            ClipDelete(rbx)
        .endif
        ClipSet(rbx)            ; set clipboard to cursor
        mov eax,event           ; return event
    .endsw
    ret

ClipEvent endp


modal proc fastcall uses rbx ti:PTEDIT

   .new state:int_t = 1
   .new event:int_t

    mov rbx,rcx
    .repeat

        .if ( state == 1 )

            getline(rbx)
            putline(rbx)
        .endif

        mov event,ClipEvent(rbx, tgetevent())
        mov state,ti_event(rbx, event)
    .until eax == _TE_RETEVENT
    getline(rbx)
    mov eax,event ; return current event (keystroke)
    ret

modal endp

    option proc:public

define tclrascii 0xB7

dledit proc uses rdi rbx b:LPSTR, rc:TRECT, bz:int_t, oflag:uint_t

  local t:TEDIT
  local cursor:CURSOR

    _getcursor(&cursor)

    lea rbx,t
    mov rdx,rdi
    mov rdi,rbx
    xor eax,eax
    mov ecx,TEDIT
    rep stosb
    mov rdi,rdx

    movzx eax,rc.x
    mov t.xpos,eax
    mov al,rc.y
    mov t.ypos,eax
    mov al,rc.col
    mov t.scols,eax
    mov eax,bz
    mov t.bcols,eax
    mov rax,b
    mov t.base,rax
    mov eax,oflag
    ;and eax,TE_CONTROL ;or O_DLGED
    or  eax,TE_OVERWRITE
    mov t.flags,eax
    setcursor(rbx)
    .ifd !_scgeta(byte ptr t.xpos, byte ptr t.ypos)
        mov eax,0x07
    .endif
    shl eax,16
    mov ax,U_MIDDLE_DOT
    mov t.clrattrib,eax  ; save text color
    .if oflag & TE_AUTOSELECT
        event_toend(rbx)
        mov eax,t.xoffs
        add eax,t.boffs
        mov t.clip_eo,eax
    .endif
    modal(rbx)
    xchg rbx,rax
    putline(rax)
    _setcursor(&cursor)
    mov eax,ebx
    ret

dledit endp

    end

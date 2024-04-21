; _TIPROC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc
include ltype.inc
include tchar.inc

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

    .if ( [rcx].flags & O_USEBEEP )
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
                or  [rbx].flags,O_MODIFIED
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
            .return( 0 )
        .endif

        event_left(rbx)
        .if tistripend(curlptr(rbx))

            event_delete(rbx)
        .endif
    .endif
    ret

event_back endp


event_add proc fastcall uses rsi rdi rbx ti:PTEDIT, c:int_t

    mov rbx,rcx
    movzx esi,dx

    .if ( edx == 0 || edx == 10 || edx == 13 )

        .return( 0 )
    .endif

    .if ( getline(rcx) == NULL )

        .return( 0 )
    .endif

    lea rcx,_ltype
    mov eax,esi

    .if ( !ah && byte ptr [rcx+rax] & _CONTROL )
        .if ( !( [rbx].flags & O_CONTROL ) )
            .return( 0 )
        .endif
    .endif

    mov eax,[rbx].bcount
    inc eax

    .if ( eax < [rbx].bcols )

        .ifd IncreaseX(rbx)

            inc [rbx].bcount
            .if getline(rbx)

                or      [rbx].flags,O_MODIFIED
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

        or  [rcx].flags,O_MODIFIED
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
    .return( 0 )

ClipCopy endp


ClipPaste proc fastcall uses rbx ti:PTEDIT

   .new bo:int_t
   .new xo:int_t
   .new n:int_t
   .new p:string_t

    mov rbx,rcx
    .if [rcx].flags & O_OVERWRITE
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
   .return( 0 )

ClipPaste endp


_tiputs proc public uses rsi rdi rbx ti:PTEDIT

   .new ci[MAXSCRLINE]:CHAR_INFO
   .new i:int_t
   .new x:byte

    ldr rbx,ti
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

_tiputs endp


define VK_SETCLIP 0x07

wm_char proc uses rbx hwnd:THWND, wParam:UINT, lParam:UINT

   .new clip_clear:char_t = true
   .new clip_delete:char_t = false
   .new add_char:char_t = false

    ldr rax,hwnd
    mov rbx,[rax].TCLASS.context.tedit

    .ifd !ClipIsSelected(rbx)

        ClipSet(rbx) ; reset clipboard if not selected
    .endif

    ; Shift-Insert  -- Paste
    ; Shift-Delete  -- Cut
    ; Ctrl-Insert   -- Copy
    ; Ctrl-C        -- Copy
    ; Ctrl-V        -- Paste
    ; Ctrl-X        -- Cut

    xor edx,edx
    mov ecx,lParam
    mov eax,wParam
    .if ( ecx & SHIFT_PRESSED )
        mov edx,VK_SHIFT
    .elseif ( ecx & ( RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED ) )
        mov edx,VK_CONTROL
    .endif

    .if ( ecx & ENHANCED_KEY )

        .switch eax
        .case VK_UP
        .case VK_DOWN
            ClipSet(rbx)
           .return( 1 ) ; return current event

        .case <vk_delete> VK_DELETE
            .if ( edx == VK_SHIFT )
                ClipCopy(rbx, 1)
               .endc
            .endif
            .endc .ifd ClipDelete(rbx)
             event_delete(rbx)
            .endc

        .case <vk_insert> VK_INSERT
            .if ( edx == VK_CONTROL )
                ClipCopy(rbx, 0)
               .endc
            .endif
            .if ( edx == VK_SHIFT )
                ClipPaste(rbx)
               .endc
            .endif
            .gotosw(VK_UP)

        .case VK_SETCLIP
            .if ( eax && edx == VK_SHIFT )

                mov clip_clear,false
                mov eax,[rbx].boffs
                add eax,[rbx].xoffs

                .if ( eax >= [rbx].clip_so )

                    mov [rbx].clip_eo,eax
                   .endc
                .endif
                mov [rbx].clip_so,eax
            .endif
           .endc

        .case VK_LEFT
            .if ( edx == VK_CONTROL )
                event_prevword(rbx)
               .endc
            .endif
            .gotosw(VK_UP) .ifd !event_left(rbx)
            .gotosw(VK_SETCLIP)

        .case VK_RIGHT
            .if ( edx == VK_CONTROL )
                event_nextword(rbx)
               .endc
            .endif
            .gotosw(VK_UP) .ifd !event_right(rbx)

            .if ( edx == VK_SHIFT )

                mov clip_clear,false
                mov eax,[rbx].boffs
                add eax,[rbx].xoffs

                .if ( eax >= [rbx].clip_so )

                    mov edx,eax
                    dec edx
                    .if ( edx == [rbx].clip_so )
                        .if ( edx != [rbx].clip_eo )
                            mov [rbx].clip_so,eax
                           .endc
                        .endif
                    .endif
                    mov [rbx].clip_eo,eax
                   .endc
                .endif
                mov [rbx].clip_so,eax
            .endif
            .endc

        .case VK_HOME
            event_home(rbx)
           .gotosw(VK_SETCLIP)
        .case VK_END
            event_toend(rbx)
           .gotosw(VK_SETCLIP)
        .endsw

    .else

        .switch eax
        .case VK_ESCAPE
        .case VK_RETURN
            ClipSet(rbx)
           .return( 1 )
        .case VK_BACK
            event_back(rbx)
           .endc
        .case VK_TAB
            .gotosw(VK_RETURN) .if !( [rbx].flags & O_CONTROL )
        .default
            .if ( edx == VK_CONTROL )

                .if ( cx == 'C' ) ; Copy
                    jmp vk_insert
                .endif
                 mov edx,VK_SHIFT
                .if ( cx == 'V' ) ; Paste
                    jmp vk_insert
                .endif
                .if ( cx == 'X' ) ; Cut
                    jmp vk_delete
                .endif
                .gotosw(VK_RETURN)
            .endif
            mov add_char,true
            mov clip_delete,true
           .endc
        .endsw
    .endif

    .if ( clip_delete )
        ClipDelete(rbx)
    .elseif ( clip_clear )
        ClipSet(rbx)
    .endif

    .if ( add_char )

        event_add(rbx, wParam)
    .endif

    mov ecx,[rbx].xpos
    add ecx,[rbx].xoffs
    _gotoxy(ecx, [rbx].ypos)
   .return(_tiputs(rbx))

wm_char endp

    assume rcx:THWND

_tiproc proc public uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    ldr rax,lParam
    ldr rcx,hwnd
    ldr rdx,wParam
    mov rbx,[rcx].context.tedit

    .switch uiMsg
    .case WM_SETFOCUS
        xor eax,eax
        mov [rbx].xoffs,eax
        mov [rbx].boffs,eax
        mov [rbx].clip_so,eax
        mov [rbx].clip_eo,eax
        mov rdx,[rcx].prev
        mov al,[rcx].rc.y
        add al,[rdx].TCLASS.rc.y
        mov [rbx].ypos,eax
        movzx ecx,[rcx].rc.x
        add cl,[rdx].TCLASS.rc.x
        mov [rbx].xpos,ecx
        add ecx,[rbx].xoffs
        _gotoxy(ecx, eax)
        _cursoron()
        .if ( [rbx].flags & O_SELECT )
            mov [rbx].clip_eo,_tcslen([rbx].base)
        .endif
        .return( _tiputs(rbx) )
    .case WM_KILLFOCUS
        xor eax,eax
        mov [rbx].xoffs,eax
        mov [rbx].boffs,eax
        mov [rbx].clip_so,eax
        mov [rbx].clip_eo,eax
        mov rdx,[rcx].prev
        mov al,[rcx].rc.y
        add al,[rdx].TCLASS.rc.y
        mov [rbx].ypos,eax
        mov al,[rcx].rc.x
        add al,[rdx].TCLASS.rc.x
        mov [rbx].xpos,eax
       .return( _tiputs(rbx) )
    .case WM_LBUTTONDOWN
        .endc

    .case WM_CHAR
        .if ( edx )

            mov ebx,edx

            ; inserting char needs focus..

            mov rdx,[rcx].prev
            mov dl,[rdx].TCLASS.index
           .endc .if dl != [rcx].index

           .return wm_char(rcx, ebx, eax)
        .endif
        .endc

    .case WM_KEYDOWN
        .endc .if !( eax & ENHANCED_KEY )
        .switch edx
        .case VK_UP
        .case VK_DOWN
;       .case VK_RETURN
        .case VK_INSERT
        .case VK_DELETE
        .case VK_HOME
        .case VK_END
        .case VK_LEFT
        .case VK_RIGHT
        .gotosw(1:WM_CHAR)
        .endsw
    .endsw
    .return( 1 )
    ret

_tiproc endp

    end

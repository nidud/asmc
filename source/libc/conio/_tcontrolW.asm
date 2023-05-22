; _TCONTROLW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void _tcontrolW( THWND hwnd, UINT count, wchar_t * string);
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
        _cwrite("\x7")
else
        MessageBeep(MB_ICONERROR)
endif
    .endif
    .return( 0 ) ; operation fail (end of line/buffer)

tinocando endp


tistripend proc fastcall uses rbx string:LPWSTR

    mov rbx,rcx
    .ifd wcslen(rcx)

        mov ecx,eax
        lea rbx,[rbx+rax*wchar_t]
        .repeat

            sub rbx,wchar_t
            mov ax,[rbx]
            .break .if ( ax != ' ' && ax != 9 )
            mov wchar_t ptr [rbx],0
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
        mov     [rdi+rdx*wchar_t-wchar_t],ax
        mov     ecx,-1
        repne   scasw
        not     ecx
        dec     ecx
        sub     rdi,wchar_t
        mov     [rbx].bcount,ecx
        sub     ecx,[rbx].bcols     ; clear rest of line
        neg     ecx
        rep     stosw
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
        lea rax,[rax+rdx*wchar_t]
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
        mov ax,[rax]
        mov edx,[rbx].xoffs
        shl edx,1
        sub rcx,rdx
        .if ax

            mov eax,[rbx].scols
            dec eax
            .if eax > [rbx].xoffs
                inc [rbx].xoffs
               .return( 1 )
            .endif
        .endif

        wcslen(rcx)
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
            .if wchar_t ptr [rax]
                dec [rbx].bcount
                mov rcx,rax
                wcscpy(rcx, &[rax+wchar_t])
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


event_add proc fastcall uses rsi rdi rbx ti:PTEDIT, wc:wchar_t

    mov rbx,rcx
    movzx esi,dx

    .if ( edx == 0 || edx == 10 || edx == 13 )

        .return( 0 )
    .endif

    .if ( getline(rcx) == NULL )

        .return( 0 )
    .endif

    lea rcx,_ltype[1]
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
                lea     rdi,[rcx+rax*wchar_t-wchar_t]
                mov     edx,esi
                mov     ecx,-1
                xor     eax,eax
                repnz   scasw
                not     ecx
                inc     ecx
                mov     rsi,rdi
                add     rdi,2
                std
                rep     movsw
                cld
                mov     [rdi],dx

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

    lea rsi,_ltype[1]
    mov rdx,rax
    mov rcx,rax
    movzx eax,wchar_t ptr [rcx]

    .while ( ah || byte ptr [rsi+rax] & _LABEL )

        add rcx,wchar_t
        mov ax,[rcx]
    .endw

    .while ( eax && !ah && !( byte ptr [rsi+rax] & _LABEL ) )

        add rcx,wchar_t
        mov ax,[rcx]
    .endw

   .return .ifd !eax

    sub rcx,rdx
    shr ecx,1

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

    lea rsi,_ltype[1]
    movzx eax,wchar_t ptr [rcx]

    .if ( ah || byte ptr [rsi+rax] & _LABEL )

        sub rcx,wchar_t
    .endif

    mov rdx,[rbx].base
    mov ax,[rcx]

    .while ( rcx > rdx && !( ah || byte ptr [rsi+rax] & _LABEL ) )

        sub rcx,wchar_t
        mov ax,[rcx]
    .endw

    .while ( rcx > rdx && ( ah || byte ptr [rsi+rax] & _LABEL ) )

        sub rcx,wchar_t
        mov ax,[rcx]
    .endw

    .if ( !( ah || byte ptr [rsi+rax] & _LABEL ) )

        mov ax,[rcx+wchar_t]
        .if ( ah || byte ptr [rsi+rax] & _LABEL )
            add rcx,wchar_t
        .endif
        movzx eax,wchar_t ptr [rcx]
    .endif

    sub rcx,[rbx].base
    shr ecx,1

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
        lea rax,[rdi+rax*wchar_t]
        lea rdx,[rdi+rdx*wchar_t]
        mov rsi,rcx

        wcscpy(rax, rdx)
        getline(rsi)
        ClipSet(rcx)
        mov eax,1
    .endif
    ret

ClipDelete endp


ClipCopy proc uses rbx ti:PTEDIT, Cut:BOOL

    mov rbx,ti
    .if ClipIsSelected(rbx) ; get size of selection

        mov edx,eax
        mov eax,[rbx].clip_so
        mov rcx,[rbx].base
        lea rcx,[rcx+rax*wchar_t]

        .if _clipsetW(rcx, edx)
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

    .if _clipgetW()

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
            movzx edx,wchar_t ptr [rax]
            add p,wchar_t
            .break .if !event_add(rbx, dx)
        .endf
        mov [rbx].boffs,bo
        mov [rbx].xoffs,xo
    .endif
    ClipSet(rbx)
   .return( 0 )

ClipPaste endp


PrintString proc fastcall uses rsi rdi rbx ti:PTEDIT

   .new ci[MAXSCRLINE]:CHAR_INFO
   .new i:int_t
   .new x:byte

    mov rbx,rcx
    lea rdi,ci
    mov ecx,[rbx].scols
    mov eax,[rbx].clrattrib
    rep stosd

    wcslen([rbx].base)
    mov rsi,[rbx].base

    .if ( eax > [rbx].boffs )

        mov eax,[rbx].boffs
        lea rsi,[rsi+rax*wchar_t]
        mov ecx,[rbx].scols
        lea rdi,ci

        .repeat
            movzx eax,wchar_t ptr [rsi]
            .break .if !eax
            mov [rdi],ax
            add rsi,wchar_t
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
            mov al,BG_INVERSE shl 4
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

PrintString endp


define VK_SETCLIP 0x07

wm_char proc uses rbx hwnd:THWND, wParam:UINT, lParam:UINT

   .new clip_clear:char_t = true
   .new clip_delete:char_t = false
   .new add_char:char_t = false

    mov rax,hwnd
    mov rbx,[rax].TCLASS.context.object

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
    .if ( ecx & SHIFTKEY_DOWN )
        mov edx,VK_SHIFT
    .elseif ( ecx & CTRLKEY_DOWN )
        mov edx,VK_CONTROL
    .endif

    .if ( ecx & KEY_EXTENDED )

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

        mov eax,wParam
        event_add(rbx, ax)
    .endif

    mov ecx,[rbx].xpos
    add ecx,[rbx].xoffs
    _gotoxy(ecx, [rbx].ypos)
   .return(PrintString(rbx))

wm_char endp

    assume rcx:THWND

wndproc proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:UINT, lParam:UINT

    mov edx,wParam
    mov eax,lParam
    mov rcx,hwnd
    mov rbx,[rcx].context.object

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
            mov [rbx].clip_eo,wcslen([rbx].base)
        .endif
        .return(PrintString(rbx))
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
       .return( PrintString(rbx) )
    .case WM_LBUTTONDOWN
        .endc
    .case WM_CHAR
        .if ( edx )
            mov ebx,edx
            .return wm_char(rcx, ebx, eax)
        .endif
        .endc
    .case WM_KEYDOWN
        .endc .if !( eax & KEY_EXTENDED )
        .switch edx
        .case VK_UP
        .case VK_DOWN
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

wndproc endp

    assume rdx:THWND

_tcontrolW proc public uses rbx hwnd:THWND, count:UINT, char:WORD, string:LPWSTR

    mov rdx,hwnd
    mov rbx,[rdx].context.object
    mov rcx,[rdx].prev

    .if ( !rbx )

        mov rbx,[rcx].buffer
        mov [rdx].context.object,rbx
        add [rcx].buffer,TEDIT
        mov [rdx].buffer,[rcx].buffer
        mov [rbx].base,rax
        mov [rbx].bcols,count
        add eax,eax
        add [rcx].buffer,rax
        shr eax,4
        mov [rdx].count,al
    .endif

    mov [rdx].winproc,&wndproc
    mov [rbx].flags,[rdx].flags
    mov [rbx].scols,[rdx].rc.col
    mov eax,_getattrib(BG_EDIT, FG_EDIT)
    mov ax,char
    .if ( ax == 0 )
        mov ax,U_MIDDLE_DOT
    .endif
    mov [rbx].clrattrib,eax

    mov rcx,[rdx].prev
    movzx eax,[rdx].rc.y
    add al,[rcx].rc.y
    mov [rbx].ypos,eax
    mov al,[rdx].rc.x
    add al,[rcx].rc.x
    mov [rbx].xpos,eax
    mov rax,string
    .if ( rax )
        wcsncpy([rbx].base, rax, [rbx].bcols)
    .endif
    mov rdx,hwnd
    mov rcx,[rdx].prev
    .if ( [rcx].flags & W_VISIBLE )
        PrintString(rbx)
    .endif
    .return(rbx)

_tcontrolW endp

    end

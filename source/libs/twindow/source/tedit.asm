; TEDIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc
include malloc.inc
include ltype.inc
include tchar.inc

    .code

strshr proc string:LPTSTR, c:int_t

    UNREFERENCED_PARAMETER(string)
    UNREFERENCED_PARAMETER(c)

    mov rax,rcx
ifdef _UNICODE
    mov r8,[rcx]
    shl r8,16
    mov r8w,dx

    .while 1

        mov rdx,[rcx+6]
        mov [rcx],r8

        shld r9,r8,32

        .break .if !(r8d & 0x0000FFFF)
        .break .if !(r8d & 0xFFFF0000)
        .break .if !(r9d & 0x0000FFFF)
        .break .if !(r9d & 0xFFFF0000)

        mov r8,rdx
        add rcx,8
    .endw
else
    mov r8d,[rcx]
    shl r8d,8
    mov r8b,dl

    .while 1

        mov edx,[rcx+3]
        mov [rcx],r8d

        .break .if !(r8d & 0x000000FF)
        .break .if !(r8d & 0x0000FF00)
        .break .if !(r8d & 0x00FF0000)
        .break .if !(r8d & 0xFF000000)

        mov r8d,edx
        add rcx,4
    .endw
endif
    ret

strshr endp


ClipboardCopy proc uses rsi rdi rbx string:LPTSTR, len:UINT

    UNREFERENCED_PARAMETER(string)
    UNREFERENCED_PARAMETER(len)

    mov rbx,rcx
    lea edi,[rdx*TCHAR]

    .if OpenClipboard(0)

        EmptyClipboard()
        add edi,TCHAR

        .if GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE, edi)

            mov rsi,rax
            mov rbx,memcpy(GlobalLock(rax), rbx, edi)
            GlobalUnlock(rsi)
            SetClipboardData(CFTEXT, rbx)
        .endif
        CloseClipboard()
    .endif
    ret

ClipboardCopy endp


ClipboardPaste proc uses rsi

    .if OpenClipboard(0)

        mov rsi,GetClipboardData(CFTEXT)
        CloseClipboard()
        mov rax,rsi
    .endif
    ret

ClipboardPaste endp


    assume rcx:tedit_t
    assume rbx:tedit_t


ClipIsSelected proto :ptr TEdit {
    mov eax,[rcx].clip_eo
    sub eax,[rcx].clip_so
    }


ClipSet proto :ptr TEdit {
    mov eax,[rcx].boffs
    add eax,[rcx].xoffs
    mov [rcx].clip_so,eax
    mov [rcx].clip_eo,eax
    }


tiincx proc ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

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

tiincx endp


tidecx proc ti:ptr TEdit

    mov eax,[rcx].boffs
    add eax,[rcx].xoffs
    .ifnz
        xor eax,eax
        mov edx,[rcx].boffs
        mov r8d,[rcx].xoffs
        .if r8d
            dec r8d
            inc eax
        .else
            dec edx
            dec eax
        .endif
        mov [rcx].xoffs,r8d
        mov [rcx].boffs,edx
    .endif
    ret

tidecx endp


tinocando proc ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    .if ( [rcx].flags & O_USEBEEP )

        Beep(9, 1)
    .endif
    .return(0) ; operation fail (end of line/buffer)

tinocando endp


tistripend proc uses rsi r15 string:LPTSTR

    UNREFERENCED_PARAMETER(string)

    mov rsi,rcx
    .ifd _tcslen(rcx)

        mov ecx,eax
        lea rsi,[rsi+rax*TCHAR]
        lea r15,_ltype

        .repeat

            sub rsi,TCHAR
            .break .if !islspace( [rsi] )
            mov TCHAR ptr [rsi],0
        .untilcxz
        mov rax,rcx
    .endif
    ret

tistripend endp


getline proc private uses rdi rbx ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    mov rax,[rcx].base
    .if rax
        mov     rbx,rcx
        mov     rdi,rax
        mov     edx,[rcx].boffs     ; terminate line
        xor     eax,eax             ; set length of line
        mov     [rdi+rdx*TCHAR-TCHAR],_tal
        mov     ecx,-1
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


curlptr proc private ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    .if getline(rcx)

        mov edx,[rcx].boffs
        add edx,[rcx].xoffs
        lea rax,[rax+rdx*TCHAR]
    .endif
    ret

curlptr endp


event_home proc private ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    .if getline(rcx)
        xor eax,eax
        mov [rcx].boffs,eax
        mov [rcx].xoffs,eax
        inc eax
    .endif
    ret

event_home endp


event_toend proc private uses rbx ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

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


event_left proc private ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    .if [rcx].xoffs
        dec [rcx].xoffs
       .return(1)
    .endif
    .if [rcx].boffs
        dec [rcx].boffs
       .return(1)
    .endif
    .return(0)

event_left endp


event_right proc private uses rbx ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    mov rbx,rcx
    .if curlptr(rcx)

        mov rcx,rax
        mov _tal,[rax]
        mov edx,[rbx].xoffs
        _tshl edx
        sub rcx,rdx
        .if _tal

            mov eax,[rbx].scols
            dec eax
            .if eax > [rbx].xoffs
                inc [rbx].xoffs
               .return(1)
            .endif
        .endif

        _tcslen(rcx)
        .if eax >= [rbx].scols
            inc [rbx].boffs
           .return(1)
        .endif
        xor eax,eax
    .endif
    ret

event_right endp


event_delete proc private uses rbx ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

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
               .return(1)
            .endif
        .endif
    .endif
    .return(tinocando(rbx))

event_delete endp


event_back proc private uses rbx ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    mov rbx,rcx
    .if getline(rcx)

        mov eax,[rcx].xoffs
        add eax,[rcx].boffs
        .if ( !eax || ![rcx].bcount )
            .return(0)
        .endif

        event_left(rcx)
        .if tistripend(curlptr(rbx))

            event_delete(rbx)
        .endif
    .endif
    ret

event_back endp


event_add proc private uses rsi rbx r15 ti:ptr TEdit, c:int_t

    UNREFERENCED_PARAMETER(ti)
    UNREFERENCED_PARAMETER(c)

    mov rbx,rcx
    mov esi,edx

    .if ( edx == 0 || edx == 10 || edx == 13 )

        .return(0)
    .endif

    .if ( getline(rcx) == NULL )

        .return(0)
    .endif

    lea r15,_ltype
    .if ( islcntrl(esi) )
        .if ( !( [rbx].flags & O_CONTROL ) )
            .return(0)
        .endif
    .endif

    mov eax,[rbx].bcount
    inc eax

    .if ( eax < [rbx].bcols )

        .ifd tiincx(rbx)

            inc [rbx].bcount
            .if getline(rbx)

                or  [rbx].flags,O_MODIFIED
                mov eax,[rbx].boffs
                add eax,[rbx].xoffs
                mov rcx,[rbx].base
                lea rcx,[rcx+rax*TCHAR-TCHAR]
                strshr(rcx, esi)
               .return(1)
            .endif
        .endif
    .endif

    mov eax,[rbx].bcols
    dec eax
    mov [rbx].bcount,eax
   .return(tinocando(rbx))

event_add endp


event_nextword proc private uses rbx r15 ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    mov rbx,rcx
   .return .if !curlptr(rcx)

    lea r15,_ltype
    mov rdx,rax
   .return .ifd !lnexttokc(rax)

    sub rcx,rdx
    _tshr ecx

    mov eax,[rbx].boffs
    add eax,[rbx].xoffs
    add eax,ecx
   .return(0) .if ( eax > [rbx].bcount )

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
    .return(1)

event_nextword endp


event_prevword proc private uses rbx r15 ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    mov rbx,rcx
   .return .if !curlptr(rcx)

    mov rcx,rax
    mov eax,[rbx].boffs
    add eax,[rbx].xoffs
   .return .ifz

    lea r15,_ltype
    .if ( islabel([rcx]) )
        sub rcx,TCHAR
    .endif
    lprevtokc(rcx, [rbx].base)
    sub rcx,[rbx].base
    _tshr ecx

    .if ( ecx > [rbx].xoffs )
        sub ecx,[rbx].xoffs
        mov [rbx].xoffs,0
        mov [rbx].boffs,ecx
    .else
        mov [rbx].xoffs,ecx
    .endif
    .return(1)

event_prevword endp


    assume rsi:ptr TWindow


TEdit::Release proc

    free(rcx)
    ret

TEdit::Release endp


TEdit::OnSetFocus proc hwnd:ptr TWindow

    UNREFERENCED_PARAMETER(hwnd)

    mov     r10,[rdx].TWindow.Prev
    movzx   eax,[rdx].TWindow.rc.y
    add     al,[r10].TWindow.rc.y
    mov     [rcx].ypos,eax
    mov     al,[rdx].TWindow.rc.x
    add     al,[r10].TWindow.rc.x
    mov     [rcx].xpos,eax
    add     eax,[rcx].xoffs
    mov     r8d,[rcx].ypos
    mov     rcx,rdx
    ret

TEdit::OnSetFocus endp


TEdit::OnLBDown proc uses rsi rdi rbx hwnd:ptr TWindow

    UNREFERENCED_PARAMETER(hwnd)

    mov rsi,rdx
    mov rbx,rcx

    [rsi].CursorOn()
    [rbx].OnSetFocus(rsi)
    [rsi].CursorMove(eax, r8d)
    ret

TEdit::OnLBDown endp


ClipDelete proc uses rsi rdi ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    .if ClipIsSelected(rcx)

        mov edi,[rcx].clip_so
        mov esi,[rcx].xoffs
        add esi,[rcx].boffs

        .if esi < edi

            .repeat
               .break .ifd !tiincx(rcx)
                inc esi
            .until edi == esi

        .elseif esi > edi

            .repeat
                .break .ifd !tidecx(rcx)
                dec esi
            .until edi == esi
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


ClipCopy proc private uses rdi rbx ti:ptr TEdit, Cut:BOOL

    UNREFERENCED_PARAMETER(ti)
    UNREFERENCED_PARAMETER(Cut)

    mov rbx,rcx
    mov edi,edx

    .if ClipIsSelected(rcx) ; get size of selection

        mov edx,eax
        mov eax,[rbx].clip_so
        mov rcx,[rbx].base
        lea rcx,[rcx+rax*TCHAR]

        .if ClipboardCopy(rcx, edx)
            .if edi
                ClipDelete(rbx)
            .endif
        .endif
        ClipSet(rbx)
    .endif
    .return(0)

ClipCopy endp


ClipPaste proc uses rsi rdi rbx r12 r13 ti:ptr TEdit

    UNREFERENCED_PARAMETER(ti)

    mov rbx,rcx
    .if [rcx].flags & O_OVERWRITE
        ClipDelete(rcx)
    .else
        ClipSet(rcx)
    .endif

    .if ClipboardPaste()

        mov rsi,rax
        mov r13d,[rbx].xoffs
        mov r12d,[rbx].boffs
        mov edi,[rbx].bcols
        sub edi,r12d

        .fors ( : edi > 0 : edi-- )

            movzx edx,TCHAR ptr [rsi]
            add rsi,TCHAR
            .break .if !event_add(rbx, edx)
        .endf
        mov [rbx].boffs,r12d
        mov [rbx].xoffs,r13d
    .endif
    ClipSet(rbx)
   .return(0)

ClipPaste endp


TEdit::OnChar proc uses rsi rdi rbx hwnd:ptr TWindow, key:WPARAM

   .new clip_clear:char_t = true
   .new clip_delete:char_t = false

    UNREFERENCED_PARAMETER(this)
    UNREFERENCED_PARAMETER(hwnd)
    UNREFERENCED_PARAMETER(key)

    mov rsi,[rdx].TWindow.Prev
    mov rbx,rcx
    mov edi,r8d
    shr edi,16

    .ifd !ClipIsSelected(rcx)

        ClipSet(rcx) ; reset clipboard if not selected
    .endif

    ; Shift-Insert  -- Paste
    ; Shift-Delete  -- Cut
    ; Ctrl-Insert   -- Copy
    ; Ctrl-C        -- Copy
    ; Ctrl-V        -- Paste
    ; Ctrl-X        -- Cut

    .switch r8w

    .case VK_UP
    .case VK_DOWN
    .case VK_ESCAPE
    .case VK_RETURN
        ClipSet(rcx)
       .return(1) ; return current event

    .case VK_DELETE
        .if ( edi == VK_SHIFT )
            ClipCopy(rcx, 1)
           .endc
        .endif
        .endc .ifd ClipDelete(rcx)
         event_delete(rcx)
        .endc

    .case VK_INSERT
        .if ( edi == VK_CONTROL )
            ClipCopy(rcx, 0)
           .endc
        .endif
        .if ( edi == VK_SHIFT )
            ClipPaste(rcx)
           .endc
        .endif
        .gotosw(VK_UP)

    .case VK_LEFT
        .if ( edi == VK_CONTROL )
            event_prevword(rcx)
           .endc
        .endif
        .gotosw(VK_UP) .ifd !event_left(rcx)
        jmp set_clip

    .case VK_RIGHT
        .if ( edi == VK_CONTROL )
            event_nextword(rcx)
           .endc
        .endif
        .gotosw(VK_UP) .ifd !event_right(rcx)
        .if ( edi == VK_SHIFT )
            mov clip_clear,false
            mov eax,[rbx].boffs
            add eax,[rbx].xoffs
            .if eax >= [rbx].clip_so
                mov edx,eax
                dec edx
                .if edx == [rbx].clip_so
                    .if edx != [rbx].clip_eo
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
        event_home(rcx)
        jmp set_clip

    .case VK_END
        event_toend(rcx)

     set_clip:
        .if ( eax && edi == VK_SHIFT )
            mov clip_clear,false
            mov eax,[rbx].boffs
            add eax,[rbx].xoffs
            .if eax >= [rbx].clip_so
                mov [rbx].clip_eo,eax
               .endc
            .endif
            mov [rbx].clip_so,eax
        .endif
       .endc

    .case VK_BACK
        event_back(rcx)
       .endc

    .case VK_TAB
        .gotosw(VK_UP) .if !( [rcx].flags & O_CONTROL )

    .default

        .if ( edi == VK_CONTROL )
            .if ( r8w == 'C' )
               .gotosw(VK_INSERT) ; Copy
            .endif
            mov edi,VK_SHIFT
            .if ( r8w == 'V' )
               .gotosw(VK_INSERT) ; Paste
            .endif
            .if ( r8w == 'X' )
               .gotosw(VK_DELETE) ; Cut
            .endif
            .gotosw(VK_UP)
        .endif
        shr r8,32
        event_add(rcx, r8d)
       .endc
    .endsw

    .if ( clip_delete )
        ClipDelete(rbx)
    .elseif ( clip_clear )
        ClipSet(rbx)
    .endif

    mov edx,[rbx].xpos
    add edx,[rbx].xoffs
    [rsi].CursorMove(edx, [rbx].ypos)

   .new ci[256]:CHAR_INFO

    lea rdi,ci
    mov ecx,[rbx].scols
    mov eax,[rbx].clrattrib
    rep stosd

    mov rsi,[rbx].base
    _tcslen(rsi)

    .if eax > [rbx].boffs

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

    .if edi < ecx

        sub ecx,edi
        xor eax,eax
        .if ecx >= [rbx].scols

            mov ecx,[rbx].scols
        .endif
        .if [rbx].clip_so >= edi

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

            mov rax,hwnd
            mov rdx,[rax].TWindow.Prev
            mov rdx,[rdx].TWindow.Color
            mov al,[rdx+BG_INVERSE]
            .repeat
                mov [rdi],al
                add rdi,4
            .untilcxz
        .endif
    .endif

    .for ( rsi = &ci, edi = 0 : edi < [rbx].scols : edi++, rsi+=4 )

        mov edx,[rbx].xpos
        add edx,edi
        hwnd.CPutChar(edx, [rbx].ypos, 1, [rsi])
    .endf
    .return(0)

TEdit::OnChar endp


    .data
     vtable TEditVtbl {
        TEdit_Release,
        TEdit_OnSetFocus,
        TEdit_OnLBDown,
        TEdit_OnChar
        }
    .code


TEdit::TEdit proc uses rsi rdi rbx hwnd:ptr TWindow, bsize:uint_t

    UNREFERENCED_PARAMETER(hwnd)
    UNREFERENCED_PARAMETER(bsize)

    mov     rsi,rdx
    mov     ebx,r8d
    lea     ecx,[rbx*TCHAR+TEdit]
    mov     [rsi].Context.object,malloc(rcx)

    .return .if !rax

    mov     edx,ebx
    mov     rdi,rax
    mov     rbx,rax
    lea     ecx,[rdx*TCHAR+TEdit]
    xor     eax,eax
    rep     stosb

    mov     [rbx].lpVtbl,&vtable
    mov     [rbx].base,&[rbx+TEdit]
    mov     [rbx].bcols,edx

    movzx   eax,[rsi].rc.col
    mov     [rbx].scols,eax

    movzx   edx,[rsi].rc.x
    movzx   eax,[rsi].rc.y
    mov     rcx,[rsi].Prev

    assume  rcx:ptr TWindow

    add     dl,[rcx].rc.x
    add     al,[rcx].rc.y
    mov     [rbx].xpos,edx
    mov     [rbx].ypos,eax
    movzx   edx,[rsi].rc.x
    movzx   r8d,[rsi].rc.y
    shr     [rcx].GetChar(edx, r8d),16
    mov     [rbx].clrattrib.Attributes,ax
    mov     [rbx].clrattrib.UnicodeChar,U_MIDDLE_DOT
    mov     [rbx].flags,[rsi].Flags
    ret

TEdit::TEdit endp

    end

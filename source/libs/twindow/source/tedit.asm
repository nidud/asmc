; TEDIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc
include malloc.inc

    .data
    .code

    assume rcx:ptr TEdit

TEdit::IsSelected proc
    mov eax,[rcx].clip_eo
    sub eax,[rcx].clip_so
    ret
TEdit::IsSelected endp

TEdit::ClipSet proc
    mov eax,[rcx].boffs
    add eax,[rcx].xoffs
    mov [rcx].clip_so,eax
    mov [rcx].clip_eo,eax
    ret
TEdit::ClipSet endp

TEdit::ClipDel proc
    ret
TEdit::ClipDel endp

TEdit::ClipCut proc x:uint_t
    ret
TEdit::ClipCut endp

TEdit::ClipPaste proc
    ret
TEdit::ClipPaste endp

TEdit::SetWinPos proc dialog:ptr TRect, item:ptr TRect
    mov     eax,[rdx]
    add     eax,[r8]
    movzx   edx,ah
    movzx   eax,al
    mov     [rcx].xpos,eax
    mov     [rcx].ypos,edx
    ret
TEdit::SetWinPos endp

TEdit::SetCursor proc
    .new TCursor()
    mov rcx,this
    mov edx,[rcx].xpos
    add edx,[rcx].xoffs
    mov [rax].TCursor.Position.x,dx
    mov edx,[rcx].ypos
    mov [rax].TCursor.Position.y,dx
    mov [rax].TCursor.CursorInfo.bVisible,1
    mov [rax].TCursor.CursorInfo.dwSize,CURSOR_NORMAL
    [rax].TCursor.Release()
    mov rcx,this
    ret
TEdit::SetCursor endp

    assume rbx:ptr TEdit

TEdit::GetLine proc uses rdi rbx
    mov rax,[rcx].base
    .if rax
        mov     rbx,rcx
        mov     rdi,rax
        mov     edx,[rcx].boffs     ; terminate line
        xor     eax,eax             ; set length of line
        mov     [rdi+rdx-1],al
        mov     ecx,-1
        repne   scasb
        not     ecx
        dec     ecx
        dec     rdi
        mov     [rbx].bcount,ecx
        sub     ecx,[rbx].bcols     ; clear rest of line
        neg     ecx
        rep     stosb
        mov     rcx,rbx
        mov     edx,[rcx].bcount
        mov     rax,[rcx].base
    .endif
    ret
TEdit::GetLine endp

TEdit::Release proc
    free(rcx)
    ret
TEdit::Release endp

    .data
    vtable TEditVtbl {
        TEdit_Release,
        TEdit_IsSelected,
        TEdit_ClipSet,
        TEdit_ClipDel,
        TEdit_ClipCut,
        TEdit_ClipPaste,
        TEdit_GetLine,
        TEdit_SetWinPos,
        TEdit_SetCursor
    }
    .code

TEdit::TEdit proc uses rsi rdi

    .if rcx == NULL

        .return .if !malloc( TEdit )

        mov rcx,rax
    .endif

    xor eax,eax
    mov rdx,rcx
    mov rdi,rcx
    mov ecx,TEdit/8
    rep stosq
    mov rcx,rdx
    lea rax,vtable
    mov [rcx],rax
    mov rax,rdx
    ret

TEdit::TEdit endp

    end

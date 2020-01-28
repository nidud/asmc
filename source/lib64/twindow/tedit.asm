; TEDIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc
include malloc.inc

    .data
    .code

    assume rcx:tedit_t

TEdit::ClipIsSelected proc

    mov eax,[rcx].clipend
    sub eax,[rcx].clipstart
    ret

TEdit::ClipIsSelected endp

TEdit::ClipSet proc

    mov eax,[rcx].index
    add eax,[rcx].x
    mov [rcx].clipstart,eax
    mov [rcx].clipend,eax
    ret

TEdit::ClipSet endp

TEdit::SetWinPos proc dialog:trect_t, item:trect_t

    mov     eax,[rdx]
    add     eax,[r8]
    movzx   edx,ah
    movzx   eax,al
    mov     [rcx].winx,eax
    mov     [rcx].winy,edx
    ret

TEdit::SetWinPos endp

TEdit::SetCursor proc

    .new TCursor()

    mov rcx,this
    mov edx,[rcx].winx
    add edx,[rcx].x
    mov [rax].TCursor.Position.x,dx
    mov edx,[rcx].winy
    mov [rax].TCursor.Position.y,dx
    mov [rax].TCursor.CursorInfo.bVisible,1
    mov [rax].TCursor.CursorInfo.dwSize,CURSOR_NORMAL

    [rax].TCursor.Release()
    mov rcx,this
    ret

TEdit::SetCursor endp

    assume rbx:tedit_t

TEdit::GetLine proc uses rdi rbx

    mov rax,[rcx].base
    .if rax
        mov     rbx,rcx
        mov     rdi,rax
        mov     edx,[rcx].index     ; terminate line
        xor     eax,eax             ; set length of line
        mov     [rdi+rdx-1],al
        mov     ecx,-1
        repne   scasb
        not     ecx
        dec     ecx
        dec     rdi
        mov     [rbx].count,ecx
        sub     ecx,[rbx].size      ; clear rest of line
        neg     ecx
        rep     stosb
        mov     rcx,rbx
        mov     edx,[rcx].count
        mov     rax,[rcx].base
    .endif
    ret

TEdit::GetLine endp

TEdit::Release proc

    free(rcx)
    ret

TEdit::Release endp

TEdit::TEdit proc uses rsi rdi

    .return .if !malloc( TEdit + TEditVtbl )
    mov rcx,rax
    lea rdi,[rax+TEdit]
    mov [rcx],rdi
    for q,<Release,
           GetLine,
           SetWinPos,
           ClipSet,
           ClipIsSelected>
        lea rax,TEdit_&q
        stosq
        endm
    xor eax,eax
    mov rdx,rcx
    lea rdi,[rcx+8]
    mov ecx,(TEdit-8)/8
    rep stosq
    mov rcx,rdx
    mov rax,rdx
    ret

TEdit::TEdit endp

    end

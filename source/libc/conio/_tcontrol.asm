; _TCONTROL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void _tcontrol( THWND hwnd, UINT count, TCHAR *string);
;

include conio.inc
include string.inc
include tchar.inc

    .code

    assume rdx:THWND
    assume rcx:THWND
    assume rbx:PTEDIT

_tcontrol proc uses rbx hwnd:THWND, count:uint_t, string:tstring_t

    ldr rcx,hwnd

    mov rdx,rcx
    mov rbx,[rcx].tedit
    mov rcx,[rcx].prev

    .if ( !rbx )

        mov rbx,[rcx].buffer
        mov [rdx].tedit,rbx
        add [rcx].buffer,TEDIT
        .if ( [rdx].flags & O_MYBUF )
            mov [rdx].buffer,string
        .else
            mov [rdx].buffer,[rcx].buffer
        .endif

        mov [rbx].base,rax
        mov [rbx].bcols,count
ifdef _UNICODE
        add eax,eax
endif
        .if !( [rdx].flags & O_MYBUF )
            add [rcx].buffer,rax
        .endif
        shr eax,3+tchar_t
        mov [rdx].count,al
    .endif

    mov     [rdx].winproc,&_tiproc
    movzx   eax,[rdx].flags
    and     eax,O_USEBEEP or O_MYBUF or O_CONTROL or O_AUTOSELECT
    mov     [rbx].flags,eax
    mov     [rbx].scols,[rdx].rc.col
    movzx   eax,[rdx].rc.y
    add     al,[rcx].rc.y
    mov     [rbx].ypos,eax
    mov     al,[rdx].rc.x
    add     al,[rcx].rc.x
    mov     [rbx].xpos,eax

    .if ( [rcx].flags & W_VISIBLE )

        .while !( [rcx].flags & W_CONSOLE )
            mov rcx,[rcx].prev
        .endw
        mov eax,[rbx].ypos
        mul [rcx].rc.col
        add eax,[rbx].xpos
        shl eax,2
        add rax,[rcx].window
    .else
        mov rax,[rdx].window
    .endif
    mov eax,[rax]
    mov [rbx].clrattrib,eax

    mov rax,string
    .if ( rax && !( [rbx].flags & TE_MYBUF ) )
        _tcsncpy([rbx].base, rax, [rbx].bcols)
    .endif

    mov rdx,hwnd
    mov rcx,[rdx].prev
    .if ( [rcx].flags & W_VISIBLE )
        _tiputs(rbx)
    .endif
    .return(rbx)

_tcontrol endp

    end

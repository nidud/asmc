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

_tcontrol proc uses rbx hwnd:THWND, count:UINT, char:WORD, string:LPTSTR

    mov rdx,hwnd
    mov rbx,[rdx].context.tedit
    mov rcx,[rdx].prev

    .if ( !rbx )

        mov rbx,[rcx].buffer
        mov [rdx].context.tedit,rbx
        add [rcx].buffer,TEDIT
        mov [rdx].buffer,[rcx].buffer
        mov [rbx].base,rax
        mov [rbx].bcols,count
        shl eax,TCHAR-1
        add [rcx].buffer,rax
        shr eax,3+TCHAR
        mov [rdx].count,al
    .endif

    mov [rdx].winproc,&_tiproc
    mov [rbx].flags,[rdx].flags
    mov [rbx].scols,[rdx].rc.col
    mov rax,[rdx].window
    mov eax,[rax]
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

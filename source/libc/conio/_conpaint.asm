; _CONPAINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

.code

_conpaint proc uses rbx

   .new sr:SMALL_RECT
   .new p:size_t
   .new rc:TRECT
   .new x:byte
   .new y:byte
   .new l:byte

ifdef __UNIX__
   .new ci:CONSOLE_CURSOR_INFO
    GetConsoleCursorInfo(NULL, &ci)
    fprintf(_confh, ESC "7")
endif
    mov rcx,_console
    mov rc,[rcx].TCONSOLE.rc
    mov rbx,[rcx].TCONSOLE.window
    mov rax,[rcx].TCONSOLE.buffer
    sub rax,rbx
    mov p,rax
ifdef __UNIX__
    .if ( ci.bVisible )
        fprintf(_confh, CSI "?25l")
    .endif
endif

    .for ( y = 0 : y < rc.row : y++ )

        .for ( l = 0, x = 0 : x < rc.col : x++, rbx+=4 )

            mov rdx,rbx
            add rdx,p
            mov eax,[rdx]
            .if ( eax != [rbx] )
                mov     [rbx],eax
                cmp     l,0
                cmovz   rcx,rdx
                inc     l
            .elseif ( l )
                movzx   eax,x
                sub     al,l
                movzx   edx,y
                mov     sr.Top,dx
                mov     sr.Bottom,dx
                mov     sr.Left,ax
                mov     dl,l
                add     eax,edx
                add     edx,0x10000
                mov     sr.Right,ax
                mov     l,0
                WriteConsoleOutputW(_confh, rcx, edx, 0, &sr)
            .endif
        .endf
        .if ( l )
            movzx   eax,x
            sub     al,l
            movzx   edx,y
            mov     sr.Top,dx
            mov     sr.Bottom,dx
            mov     sr.Left,ax
            mov     dl,l
            add     eax,edx
            add     edx,0x10000
            mov     sr.Right,ax
            mov     l,0
            WriteConsoleOutputW(_confh, rcx, edx, 0, &sr)
        .endif
    .endf
ifdef __UNIX__
    fprintf(_confh, ESC "8")
    .if ( ci.bVisible )
        fprintf(_confh, CSI "?25h")
    .endif
    fflush(_confh)
endif
    ret
    endp

    end

; TCURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include twindow.inc

    .data
    vtable TCursorVtbl { TCursor_Hide, TCursor_Show, TCursor_Move, TCursor_Release }

    .code

    assume rcx:cursor_t

TCursor::Show proc

  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,1
    SetConsoleCursorInfo([rcx].Handle, &cu)
    ret

TCursor::Show endp

TCursor::Hide proc

  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,0
    SetConsoleCursorInfo([rcx].Handle, &cu)
    ret

TCursor::Hide endp

TCursor::Move proc x:int_t, y:int_t

    shl r8d,16
    or  edx,r8d
    SetConsoleCursorPosition([rcx].Handle, edx)
    ret

TCursor::Move endp

    assume rbx:cursor_t

TCursor::Release proc uses rbx

    mov rbx,rcx
    SetConsoleCursorPosition([rbx].Handle, [rbx].Position)
    SetConsoleCursorInfo([rbx].Handle, &[rbx].CursorInfo)
    free(rbx)
    ret

TCursor::Release endp

TCursor::TCursor proc uses rsi rbx

  local ci:CONSOLE_SCREEN_BUFFER_INFO

    mov rax,rcx
    .if rax == NULL
        .return .if !malloc( TCursor )
    .endif
    mov rbx,rax
    mov rsi,GetStdHandle(STD_OUTPUT_HANDLE)
    lea rdx,vtable
    mov [rbx].lpVtbl,rdx
    mov [rbx].Position,0
    mov [rbx].Handle,rsi

    .if GetConsoleScreenBufferInfo(rsi, &ci)

        mov [rbx].Position,ci.dwCursorPosition
    .endif
    GetConsoleCursorInfo(rsi, &[rbx].CursorInfo)
    mov rax,rbx
    ret

TCursor::TCursor endp

    end

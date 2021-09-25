
    ; 2.32.64 - @ComAlloc()

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    option win64:3

define MessageBox <MessageBoxW>

.class TWindow
    MessageBox proc
    CursorGet  proc
   .ends
   .code

malloc proc n:dword
    ret
malloc endp

TWindow::MessageBox proc
    ret
TWindow::MessageBox endp

TWindow::CursorGet proc
    ret
TWindow::CursorGet endp

main proc

    mov rbx,@ComAlloc(TWindow)

    assume rcx:ptr TWindow

    [rcx].MessageBox() ; MessageBoxW()

    ret

main endp

    end


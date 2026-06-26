
    ; 2.32.64 - @ComAlloc()

    option win64:3

define MessageBox <MessageBoxW>

.class TWindow
    MessageBox proc
    CursorGet  proc
   .ends
   .code

malloc proc n:dword
    ret
    endp

TWindow::MessageBox proc
    ret
    endp

TWindow::CursorGet proc
    ret
    endp

main proc

    mov rbx,@ComAlloc(TWindow)

    assume rcx:ptr TWindow

    [rcx].MessageBox() ; MessageBoxW()

    ret
    endp

    end


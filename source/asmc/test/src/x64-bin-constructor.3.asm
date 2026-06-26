;
; v2.36.20 - Default constructor if not defined
;

.code

option win64:3

.comdef IUnknown

    QueryInterface  proc
    AddRef          proc
    Release         proc
   .ends

   .code

malloc proc z:dword
    ret
    endp
IUnknown::QueryInterface:
IUnknown::AddRef:
IUnknown::Release:
    ret

foo proc

   .new p:ptr IUnknown()

    mov rbx,IUnknown()
    malloc(IUnknown())
    ret
    endp

    end


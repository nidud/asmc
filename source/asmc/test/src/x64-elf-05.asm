;
; v2.30 - stack param
;
    .code

    option win64:auto

foo proc a:ptr, b:ptr, c:ptr, d:ptr, e:ptr, f:ptr, g:ptr, h:word

    mov rax,g
    mov ax,h
    ret
foo endp

bar proc

  local p:ptr,x:word

    foo(1,2,3,4,5,6,7,8)
    foo(1,2,3,4,5,6,p,x)
    ret

bar endp

    end

;
; v2.34.26 assume reg
;
ifndef __ASMC64__
    .x64
    .model flat
endif

.template foo
 x db ?
 y db ?
 z db ?
.ends

    .data
     z word ?

    .code

fcc proc fastcall x:byte, y:byte
    ret
fcc endp

bar proc

  local x:dword

    assume rbx:ptr foo
    .if ( .x == .y )

        mov edx,fcc(.x, .y)

        assume rax:ptr byte
        mov [rax],1
        assume rdx:ptr word
        mov [rdx],1
        assume rcx:ptr foo
        mov .x,x
        assume rcx:nothing
        assume rdx:nothing
        assume rax:nothing
        mov .y,.z
        mov al,.y
        mov .z,al
    .endif
    assume rbx:nothing
    ret

bar endp

    end


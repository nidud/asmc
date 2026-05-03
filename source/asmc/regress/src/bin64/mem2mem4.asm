
    ; 2.33.67 - mem2mem / type ptr

ifndef __ASMC64__
    .x64
    .model flat
endif

    s1 struct
    o oword ?
    s1 ends

    .code

main proc

  local t:s1

    mov [rcx],t

    mov [rcx],byte ptr t
    mov [rcx],word ptr t
    mov [rcx],dword ptr t
    mov [rcx],qword ptr t

    mov [rcx],byte ptr t.o
    mov [rcx],word ptr t.o
    mov [rcx],dword ptr t.o
    mov [rcx],qword ptr t.o
    ret

main endp

    end

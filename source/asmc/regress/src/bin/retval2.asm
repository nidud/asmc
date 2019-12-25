;
; v2.31.04: [reg].type.id / dword ptr [reg]
;
    .x64
    .model flat, fastcall
    .code

    option win64:auto

    vr struc
    z1 db ?
    z2 dw ?
    z4 dd ?
    z8 dq ?
    vr ends

foo proc
    ret
foo endp

main proc

    mov byte ptr [rbx],  foo()
    mov word ptr [rbx],  foo()
    mov dword ptr [rbx], foo()

    mov [rbx].vr.z1, foo()
    mov [rbx].vr.z2, foo()
    mov [rbx].vr.z4, foo()
    mov [rbx].vr.z8, foo()
    ret

main endp

    end

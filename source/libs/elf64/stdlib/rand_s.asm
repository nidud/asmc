include stdlib.inc

    .code

rand_s proc uses rbx _RandomValue:ptr UINT

    mov rbx,rdi
    rand()
    mov [rbx],eax
    mov eax,1
    ret

rand_s endp

    end

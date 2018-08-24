include stdlib.inc

    .code

rand_s proc _RandomValue:ptr UINT

    rand()
    mov rcx,_RandomValue
    mov [rcx],eax
    mov eax,1
    ret

rand_s endp

    end

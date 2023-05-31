include stdlib.inc

    .code

rand_s proc uses rbx _RandomValue:ptr uint_t

    ldr rbx,_RandomValue
    rand()
    mov [rbx],eax
    mov eax,1
    ret

rand_s endp

    end

include stdlib.inc

    .data
    A dd 9,8,7,6,5,4,3,2,1,0
    B dd 0,1,2,3,4,5,6,7,8,9
    .code

compare proc private a:ptr, b:ptr

    mov rax,a
    mov rdx,b
    mov eax,[rax]
    mov edx,[rdx]

    .if eax > edx
        mov eax,1
    .elseif eax < edx
        mov eax,-1
    .else
        xor eax,eax
    .endif
    ret

compare endp


main proc

    .assert( atol("") == 0 )
    .assert( atol("1") == 1 )
    .assert( atol("-1") == -1 )
    .assert( atol("00999") == 999 )
    .assert( _atoi64("0") == 0 )
    .assert( _atoi64("1") == 1 )
    .assert( _atoi64("-1") == -1 )
    .assert( _atoi64("00999") == 999 )

    qsort (&A, 10, 4, &compare)

    xor eax,eax
    lea rsi,A
    lea rdi,B
    mov ecx,10
    repe cmpsd
    setnz al
    ret

main endp

    end

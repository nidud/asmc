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
    .assertd( atol("-2147483648") == 0x80000000 )
    .assertd( atol("2147483647") == 0x7FFFFFFF )
    .assertd( atol("4294967295") == -1 )

    mov rdi,0x7FFFFFFFFFFFFFFF
    mov rbx,0x8000000000000000
    .assert( _atoi64("0") == 0 )
    .assert( _atoi64("1") == 1 )
    .assert( _atoi64("-1") == -1 )
    .assert( _atoi64("00999") == 999 )
    .assertd( _atoi64("-2147483648") == 0x80000000 )
    .assertd( _atoi64("2147483647") == 0x7FFFFFFF )
    .assertd( _atoi64("4294967295") == -1 )
    .assert( _atoi64("18446744073709551615") == -1 )
    .assert( _atoi64("9223372036854775807") == rdi )
    .assert( _atoi64("-9223372036854775808") == rbx )

__SIZEOF_INT128__   equ 128
__CHAR_BIT__        equ 8
    .assert( _atoi128("0") == 0 )
    .assert( _atoi128("1") == 1 )
    .assert( _atoi128("-1") == -1 )
    .assert( _atoi128("00999") == 999 )
INT128_MAX equ (( 1 shl ((__SIZEOF_INT128__ * __CHAR_BIT__) - 1)) - 1)
    .assert( _atoi128("170141183460469231731687303715884105727") == -1 && rdx == rdi )
INT128_MIN equ (-INT128_MAX - 1)
    .assert( _atoi128("-170141183460469231731687303715884105728") == 0 && rdx == rbx )
UINT128_MAX equ ((2 * INT128_MAX) + 1)
    .assert( _atoi128("340282366920938463463374607431768211455") == -1 && rdx == -1 )

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

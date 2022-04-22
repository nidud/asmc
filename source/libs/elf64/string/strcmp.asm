; STRCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strcmp proc a:string_t, b:string_t

    xor rax,rax
@@:
    xor al,[rdi]
    jz	zero_0
    sub al,[rsi]
    jnz done
    xor al,[rdi+1]
    jz	zero_1
    sub al,[rsi+1]
    jnz done
    xor al,[rdi+2]
    jz	zero_2
    sub al,[rsi+2]
    jnz done
    xor al,[rdi+3]
    jz	zero_3
    sub al,[rsi+3]
    jnz done
    lea rdi,[rdi+4]
    lea rsi,[rsi+4]
    jmp @B
done:
    sbb al,al
    sbb al,-1
    movsx rax,al
    ret
zero_3:
    add rsi,1
zero_2:
    add rsi,1
zero_1:
    add rsi,1
zero_0:
    sub al,[rsi]
    jnz done
    ret

strcmp endp

    end

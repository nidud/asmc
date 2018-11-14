; STRCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

strcmp::

    xor rax,rax
@@:
    xor al,[rcx]
    jz	zero_0
    sub al,[rdx]
    jnz done
    xor al,[rcx+1]
    jz	zero_1
    sub al,[rdx+1]
    jnz done
    xor al,[rcx+2]
    jz	zero_2
    sub al,[rdx+2]
    jnz done
    xor al,[rcx+3]
    jz	zero_3
    sub al,[rdx+3]
    jnz done
    lea rcx,[rcx+4]
    lea rdx,[rdx+4]
    jmp @B
done:
    sbb al,al
    sbb al,-1
    movsx rax,al
    ret
zero_3:
    add rdx,1
zero_2:
    add rdx,1
zero_1:
    add rdx,1
zero_0:
    sub al,[rdx]
    jnz done
    ret

    END

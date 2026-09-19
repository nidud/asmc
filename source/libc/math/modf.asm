; MODF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

ifdef _WIN64

modf proc x:double, y:ptr double

    ldr rdx,y
    movq r8,xmm0
    mov rax,r8
    mov rcx,0x4340000000000000
    shl rax,1
    shr rax,1
    .if ( rax >= rcx )
        mov rcx,0x7FF0000000000000
        mov [rdx],r8
        .if ( rax > rcx )
            addsd xmm0,xmm0
        .else
            mov rax,0x8000000000000000
            and rax,r8
            movq xmm0,rax
        .endif
    .else
        mov rcx,0x3FF0000000000000
        .if ( rax < rcx )
            mov rax,0x8000000000000000
            and rax,r8
            mov [rdx],rax
        .else
            mov rax,r8
            mov ecx,51
            shr rax,52
            sub cl,al
            mov eax,1
            shl rax,cl
            dec rax
            not rax
            and rax,r8
            movq xmm1,rax
            subsd xmm0,xmm1
            movsd [rdx],xmm1
        .endif
    .endif
    ret
    endp
endif
    end

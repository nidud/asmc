
    .code

memmove::

    mov rax,rcx

    .switch
      .case !r8
        ret
      .case r8 == 1
        mov cl,[rdx]
        mov [rax],cl
        ret
      .case r8 < 4
        mov cx,[rdx]
        mov dx,[rdx+r8-2]
        mov [rax+r8-2],dx
        mov [rax],cx
        ret
      .case r8 < 8
        mov ecx,[rdx]
        mov edx,[rdx+r8-4]
        mov [rax+r8-4],edx
        mov [rax],ecx
        ret
      .case r8 < 16
        movq xmm2,[rdx]
        movq xmm1,[rdx+r8-8]
        movq [rax],xmm2
        movq [rax+r8-8],xmm1
        ret
        db 6 dup(0x90)
    .endsw

    movdqu xmm3,[rdx]
    movdqu xmm5,[rdx+r8-16]

    .if r8 >= 32

        movdqu xmm4,[rdx+16]
        movdqu xmm6,[rdx+r8-32]

        .if r8 >= 64

            mov ecx,eax
            neg ecx
            and ecx,32-1
            add rdx,rcx
            mov r9,r8
            sub r9,rcx
            add rcx,rax
            and r9b,-32

            .if rcx > rdx

                .repeat
                    sub r9,32
                    movups xmm1,[rdx+r9]
                    movups xmm2,[rdx+r9+16]
                    movaps [rcx+r9],xmm1
                    movaps [rcx+r9+16],xmm2
                .untilz
                movups [rax],xmm3
                movups [rax+16],xmm4
                movups [rax+r8-16],xmm5
                movups [rax+r8-32],xmm6
                ret
                db 5 dup(0x90)
            .endif

            lea rcx,[rcx+r9]
            lea rdx,[rdx+r9]
            neg r9
            .repeat
                movups xmm1,[rdx+r9]
                movups xmm2,[rdx+r9+16]
                movaps [rcx+r9],xmm1
                movaps [rcx+r9+16],xmm2
                add r9,32
            .untilz
            movups [rax],xmm3
            movups [rax+16],xmm4
            movups [rax+r8-16],xmm5
            movups [rax+r8-32],xmm6
            ret
        .endif
        movups [rax+16],xmm4
        movups [rax+r8-32],xmm6
    .endif
    movups [rax],xmm3
    movups [rax+r8-16],xmm5
    ret

    end

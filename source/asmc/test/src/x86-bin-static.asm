
    ; 2.32.27 - .static 32-bit

    .486
    .model flat, c

.template ft fastcall

    atom byte ?

    .static ft {
        mov this.atom,0
        }
    .static b {
        mov this.atom,1
        }
    .ends

    .code

main proc

  .new f:ft()

    f.b()
    ret

main endp

    end

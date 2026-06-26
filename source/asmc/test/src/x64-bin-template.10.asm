
    ; 2.32.28 - .static 64-bit

.template ft
    atom byte ?
    .static ft { mov this.atom,0 }
    .static b  { mov this.atom,1 }
    .ends

.code

main proc
  .new f:ft()
    f.b()
    ret
    endp

    end

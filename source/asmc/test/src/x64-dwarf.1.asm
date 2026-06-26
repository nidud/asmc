; DWARF.ASM--
;
; v2.37.51: DWARF line number (-Zd)
;

externdef val:byte

bar proto

.code

foo proc

    nop
    nop
    nop
    nop
    org $ - 4

    mov eax,1
    call bar
    movzx eax,val
    mov eax,PASS
    .if ( eax )
        db 200 dup(90h)
    .endif
    ret

foo endp

PASS equ 2

end

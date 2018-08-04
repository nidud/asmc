
    .code

__chkstk::
___chkstk_ms::
__alloca_probe::

    lea r11,[rsp+8]
    mov r10,rax
@@:
    cmp r10,1000h   ; probe pages
    jb  @F
    sub r11,1000h
    test [r11],al
    sub r10,1000h
    jmp @B
@@:
    sub r11,r10
    test [r11],al   ; probe page
    ret

    end

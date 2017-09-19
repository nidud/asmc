include io.inc
include time.inc
include wsub.inc

    .code

fbupdir proc flag
    clock()
    mov ecx,flag
    or	ecx,_FB_UPDIR or _A_SUBDIR
    fballoc(addr cp_dotdot, eax, 0, ecx)
    ret
fbupdir endp

    END

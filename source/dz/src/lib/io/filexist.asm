include io.inc

    .code

filexist proc file:LPSTR
    getfattr(file)
    inc eax
    .ifnz
        dec eax             ; 1 = file
        and eax,_A_SUBDIR   ; 2 = subdir
        shr eax,4
        inc eax
    .endif
    ret
filexist endp

    END


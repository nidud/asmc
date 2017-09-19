include consx.inc

    .code

GetScreenRect proc

    mov eax,_scrcol
    mov ah,byte ptr _scrrow
    shl eax,16
    ret

GetScreenRect endp

    END

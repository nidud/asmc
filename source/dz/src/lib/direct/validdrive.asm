include direct.inc
include winbase.inc

    .code

validdrive proc drive:SINT
    GetLogicalDrives()
    mov ecx,drive
    dec ecx
    shr eax,cl
    sbb eax,eax
    and eax,1
    ret
validdrive endp

    END

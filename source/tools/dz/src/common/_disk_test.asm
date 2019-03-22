include direct.inc
include consx.inc
include errno.inc
include dzlib.inc

externdef IDD_DriveNotReady:dword

    .code

_disk_retry proc private uses edi disk
    .if rsopen(IDD_DriveNotReady)
        mov edi,eax
        dlshow(eax)
        movzx   edx,[edi].S_DOBJ.dl_rect.rc_x
        add dl,25
        movzx   ecx,[edi].S_DOBJ.dl_rect.rc_y
        add cl,2
        mov eax,disk
        add al,'A' - 1
        scputc(edx, ecx, 1, eax)
        sub edx,22
        add ecx,2
        mov eax,errno
        scputs(edx, ecx, 0, 29, _sys_errlist[eax*4])
        dlmodal(edi)
        test   eax,eax
    .endif
    ret
_disk_retry endp

_disk_test proc disk
    .if _disk_ready(disk)
        .if _disk_type(disk) < 2
            .repeat
                .if _disk_retry(disk)
                    _disk_ready(disk)
                .endif
            .until  eax
        .else
            mov eax,1
        .endif
    .endif
    ret
_disk_test endp

    END

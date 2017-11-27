include direct.inc
include time.inc
include crtl.inc
include wsub.inc
include winbase.inc
include io.inc
include dzlib.inc

PUBLIC  drvinfo

    .data
    drvinfo S_DISK MAXDRIVES dup(<?>)

    .code

_disk_read proc uses esi edi ebx

    mov esi,clock()
    mov edi,GetLogicalDrives()
    lea ebx,drvinfo
    mov ecx,1
    .repeat
        sub eax,eax
        mov [ebx].S_DISK.di_flag,eax
        shr edi,1
        .ifc
            .if _disk_type(ecx) > 1
                mov edx,_FB_ROOTDIR or _A_VOLID
                .if eax == DRIVE_CDROM
                    or edx,_FB_CDROOM
                .endif
                mov [ebx].S_DISK.di_flag,edx
            .endif
            mov [ebx].S_DISK.di_time,esi
        .endif
        add ebx,SIZE S_DISK
        inc ecx
    .until ecx == MAXDRIVES+1
    ret

_disk_read endp

InitDisk:
    lea edx,drvinfo
    mov ecx,1
    mov eax,':A'
    .repeat
        mov dword ptr [edx].S_DISK.di_name,eax
        mov dword ptr [edx].S_DISK.di_size,ecx
        inc eax
        add edx,SIZE S_DISK
        inc ecx
    .until ecx == MAXDRIVES+1
    _disk_read()
    ret

pragma_init InitDisk, 11

    END

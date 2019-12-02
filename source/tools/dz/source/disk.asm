include time.inc
include io.inc
include direct.inc
include consx.inc
include errno.inc
include dzlib.inc
include wsub.inc

extern IDD_DriveNotReady:dword
public _diskflag
PUBLIC drvinfo

    .data
    _diskflag dd 0
    drvinfo S_DISK MAXDRIVES dup(<?>)
    push_button db "&A",0

    .code

_disk_type proc uses edx ecx disk

  local path[2]:dword

    mov eax,'\: '
    mov al,byte ptr disk
    add al,'A'-1
    mov path,eax
    xor eax,eax
    mov path[4],eax
    GetDriveType(&path)
    ret

_disk_type endp

_disk_init proc uses edi disk

    mov edi,disk
    .if !_disk_test(edi)

    .if _disk_select("Select disk")

        _disk_init(eax)
        mov edi,eax
    .endif
    .endif
    mov eax,edi
    ret

_disk_init endp

_disk_exist proc uses edx disk

    mov eax,S_DISK
    mov edx,disk
    dec edx
    mul edx
    lea edx,drvinfo[eax]
    xor eax,eax
    .if [edx].S_DISK.di_flag != eax
        mov eax,edx
    .endif
    ret

_disk_exist endp

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
        test eax,eax
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

_disk_ready proc disk

  local MaximumComponentLength:dword,
    FileSystemFlags:dword,
    RootPathName[2]:dword,
    FileSystemNameBuffer[32]:word

    mov eax,disk
    inc eax
    .if validdrive(eax)
        mov eax,'\: '
        mov al,byte ptr disk
        add al,'A' - 1
        mov RootPathName,eax
        GetVolumeInformation(
            &RootPathName,
            0,
            0,
            0,
            &MaximumComponentLength,
            &FileSystemFlags,
            &FileSystemNameBuffer,
            32)
        test eax,eax
    .endif
    ret

_disk_ready endp

_disk_select proc uses esi edi ebx msg:LPSTR

  local dobj:S_DOBJ
  local tobj[MAXDRIVES]:S_TOBJ

    mov ebx,_getdrive()
    _disk_read()
    mov dword ptr dobj.dl_flag,_D_STDDLG
    mov dobj.dl_rect,0x003F0908
    lea edi,tobj
    mov dobj.dl_object,edi
    mov esi,1

    .repeat

        .if _disk_exist(esi)

            movzx eax,dobj.dl_count
            inc dobj.dl_count
            mov [edi].S_TOBJ.to_flag,_O_PBKEY
            mov ecx,eax
            .if esi == ebx

                mov al,dobj.dl_count
                dec al
                mov dobj.dl_index,al
            .endif

            mov eax,esi
            add al,'@'
            mov [edi].S_TOBJ.to_ascii,al
            mov eax,0x01050000
            mov al,cl
            shr al,3
            shl al,1
            add al,2
            mov ah,al
            and cl,7
            mov al,cl
            shl al,3
            sub al,cl
            add al,4
            mov [edi].S_TOBJ.to_rect,eax
            add edi,16
        .endif

        inc esi

    .until esi > MAXDRIVES

    movzx eax,dobj.dl_count
    dec eax
    mov ebx,eax
    shr eax,3
    shl eax,1
    add al,5
    mov dobj.dl_rect.rc_row,al
    mov eax,ebx

    .if eax <= 7
        shl eax,3
        sub eax,ebx
        add eax,14
        mov dobj.dl_rect.rc_col,al
        mov cl,byte ptr _scrcol
        sub cl,al
        shr cl,1
        mov dobj.dl_rect.rc_x,cl
    .endif

    xor edi,edi
    mov bl,at_foreground[F_Dialog]
    or  bl,at_background[B_Dialog]

    .if dlopen(&dobj, ebx, msg)

        lea esi,tobj
        mov bl,[esi].S_TOBJ.to_rect.rc_col

        .while 1

            movzx eax,dobj.dl_count
            .break .if edi >= eax
            mov al,[esi].S_TOBJ.to_ascii
            mov push_button[1],al
            mov al,dobj.dl_rect.rc_col
            rcbprc([esi].S_TOBJ.to_rect, dobj.dl_wp, eax)
            movzx ecx,dobj.dl_rect.rc_col
            wcpbutt(eax, ecx, ebx, &push_button)
            inc edi
            add esi,sizeof(S_TOBJ)
        .endw

        mov edi,dlmodal(&dobj)
    .endif

    xor eax,eax
    .if edi
        or  al,dobj.dl_index
        shl eax,4
        add eax,dobj.dl_object
        movzx eax,[eax].S_TOBJ.to_ascii
        sub al,'@'
    .endif
    ret

_disk_select endp

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
        add ebx,sizeof(S_DISK)
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
        add edx,sizeof(S_DISK)
        inc ecx
    .until ecx == MAXDRIVES+1
    _disk_read()
    ret

.pragma init(InitDisk, 70)

    END

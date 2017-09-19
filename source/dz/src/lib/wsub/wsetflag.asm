include io.inc
include direct.inc
include wsub.inc
include dzlib.inc

    .code

    assume esi:ptr S_WSUB

wssetflag proc uses esi edi wsub:ptr S_WSUB

    mov esi,wsub
    mov edi,[esi].ws_flag
    and edi,not _W_NETWORK
    mov [esi].ws_flag,edi
    mov eax,[esi].ws_path
    mov eax,[eax]
    .repeat
        .if ah == '\'
            mov eax,3
            or  edi,_W_NETWORK
            .break
        .endif
        .if ah != ':'
            xor eax,eax
            .break
        .endif
        or  al,20h
        sub al,'a' - 1
        movzx eax,al
        .switch _disk_type(eax)
          .case _DISK_SUBST
            mov eax,2
          .case DRIVE_CDROM
            or edi,_W_CDROOM
            .break
          .case DRIVE_REMOVABLE
            or edi,_W_REMOVABLE
            .break
          .case DRIVE_REMOTE
            or  edi,_W_NETWORK or _W_CDROOM
            mov eax,3
            .break
        .endsw
        and eax,1
    .until 1
    mov [esi].ws_flag,edi
    ret

wssetflag endp

    END

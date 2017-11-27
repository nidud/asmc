include direct.inc
include malloc.inc
include string.inc
include errno.inc
include ltype.inc
include winbase.inc

.code

_fullpath proc uses esi edi ebx buf:LPSTR, path:LPSTR, maxlen:UINT

  local drive:byte
  local dchar:byte

    .repeat

        mov esi,path
        .if !esi || byte ptr [esi] == 0

            _getcwd(buf, maxlen)
            .break
        .endif

        mov edi,buf
        .if !edi

            .if !malloc( _MAX_PATH )

                mov errno,ENOMEM
                .break
            .endif

            mov edi,eax
            mov maxlen,_MAX_PATH

        .elseif maxlen < _MAX_DRIVE+1

            mov errno,ERANGE
            xor eax,eax
            .break
        .endif

        mov ebx,edi
        mov edx,'\/'
        mov eax,[esi]
        .if ((al == dl || al == dh) && (ah == dl || ah == dh))

            mov ecx,ebx
            add ecx,maxlen
            dec ecx
            xor eax,eax

            .repeat

                lodsb
                mov [edi],al
                .break .if !al

                .if edi >= ecx

                    mov errno,ERANGE
                    xor eax,eax
                    .break
                .endif

                .if (al == dl || al == dh)

                    mov [edi],dl
                    inc ah

                    .if ((ah == 2 && byte ptr [esi] == 0) || \
                         (ah >= 3 && byte ptr [edi-1] == '\'))

                        mov errno,EINVAL
                        xor eax,eax
                        .break
                    .endif
                .endif

                inc edi
            .until ah == 4

            mov [edi],dl
            mov ecx,edi

        .else

            mov   drive,0
            push  eax
            movzx eax,al
            test  byte ptr _ltype[eax+1],_UPPER or _LOWER
            pop   eax

            .if !ZERO? && ah == ':'

                mov [edi],ax
                add edi,2
                add esi,2
                sub al,'A' + 1
                and al,1Fh
                mov drive,al
                GetLogicalDrives()
                movzx ecx,drive
                dec ecx
                shr eax,cl
                sbb eax,eax
                and eax,1

                .ifz
                    mov errno,EACCES
                    mov oserrno,ERROR_INVALID_DRIVE
                    .break
                .endif
            .endif

            mov al,[esi]
            .if al == '\' || al == '/'

                .if drive == 0

                    _getdrive()
                    add al,'A'- 1
                    stosb
                    mov al,':'
                    stosb
                .endif
                inc esi

            .else

                .if drive

                    mov al,[esi-2]
                    mov dchar,al
                .endif

                movzx eax,drive
                .break .if !_getdcwd(eax, ebx, maxlen)

                strlen(ebx)
                add eax,ebx
                mov edi,eax

                .if drive

                    mov al,dchar
                    mov [ebx],al
                .endif

                mov al,[edi-1]
                .if al == '\' || al == '/'

                    dec edi
                .endif
            .endif

            mov byte ptr [edi],'\'
            lea ecx,[ebx+2]
        .endif

        .while byte ptr [esi] != 0

            mov ax,[esi]
            mov dl,[esi+2]
            .if (al == '.' && ah == '.' && (!dl || dl == '\' || dl == '/'))

                .repeat
                    dec edi
                    mov al,[edi]
                .until (al == '\' || al == '/' || edi <= ecx)

                .if edi < ecx

                    mov errno,EACCES
                    xor eax,eax
                    .break(1)
                .endif

                add esi,2
                .if byte ptr [esi] != 0

                    inc esi
                .endif

            .elseif (al == '.' && ((ah == '\' || ah == '/') || !ah))

                inc esi
                .if byte ptr [esi] != 0

                    inc esi
                .endif
            .else

                mov edx,edi
                mov al,[esi]

                .while (al && !(al == '\' || al == '/') && edi < ecx)

                    lodsb
                    inc edi
                    mov [edi],al
                .endw

                .if edi >= ecx

                    mov errno,ERANGE
                    xor eax,eax
                    .break
                .endif

                .if edi == edx

                    mov errno,EINVAL
                    xor eax,eax
                    .break(1)
                .endif

                inc edi
                mov byte ptr [edi],'\'
                mov al,[esi]
                .if al == '\' || al == '/'

                    inc esi
                .endif
            .endif
        .endw

        .if byte ptr [edi-1] == ':'
            inc edi
        .endif

        mov byte ptr [edi],0
        mov eax,ebx

    .until 1

    .if !eax

        .if eax == buf
            free(ebx)
        .endif
        xor eax,eax
    .endif
    ret

_fullpath endp

    END


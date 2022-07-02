; _WFULLPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include malloc.inc
include string.inc
include errno.inc
include winbase.inc

.code

_wfullpath proc uses rsi rdi rbx buf:LPWSTR, path:LPWSTR, maxlen:UINT

  local drive:byte
  local dchar:byte

    .repeat

        mov rsi,path
        .if ( !rsi || word ptr [rsi] == 0 )

            _wgetcwd(buf, maxlen)
            .break
        .endif

        mov rdi,buf
        .if ( !rdi )

            .if !malloc( _MAX_PATH*2 )

                _set_errno(ENOMEM)
                .return(0)
            .endif

            mov rdi,rax
            mov maxlen,_MAX_PATH

        .elseif ( maxlen < _MAX_DRIVE+1 )

            _set_errno(ERANGE)
            .return(0)
        .endif

        mov rbx,rdi
        mov edx,'\'
        mov eax,'/'

        .if ( ( [rdi] == dx || [rdi] == ax ) && ( [rdi+2] == dx || [rdi+2] == ax ) )

            mov eax,maxlen
            lea rcx,[rbx+rax*2-2]
            xor eax,eax
            xor edx,edx

            .repeat

                lodsw
                mov [rdi],ax
                .break .if !ax

                .if ( rdi >= rcx )

                    _set_errno(ERANGE)
                    xor eax,eax
                    .break
                .endif

                .if ( ax == '\' || ax == '/' )

                    mov word ptr [rdi],'\'
                    inc edx

                    .if ( ( edx == 2 && word ptr [rsi] == 0 ) ||
                          ( edx >= 3 && word ptr [rdi-2] == '\' ) )

                        _set_errno(EINVAL)
                        xor eax,eax
                        .break
                    .endif
                .endif

                add rdi,2
            .until ( edx == 4 )

            mov word ptr [rdi],'\'
            mov rcx,rdi

        .else

            mov drive,0
            mov cx,[rsi]
            or  cl,0x20

            .if ( cx >= 'a' && cx <= 'z' && word ptr [rsi+2] == ':' )

                movsd

                sub cl,'a' + 1
                and cl,1Fh
                mov drive,cl

                GetLogicalDrives()

                movzx ecx,drive
                dec ecx
                shr eax,cl
                sbb eax,eax
                and eax,1

                .ifz
                    _set_errno(EACCES)
                    _set_doserrno(ERROR_INVALID_DRIVE)
                    xor eax,eax
                    .break
                .endif
            .endif

            mov ax,[rsi]
            .if ( ax == '\' || ax == '/' )

                .if ( drive == 0 )

                    _getdrive()
                    add al,'A'- 1
                    stosw
                    mov al,':'
                    stosw
                .endif
                add rsi,2

            .else

                .if ( drive )

                    mov al,[rsi-4]
                    mov dchar,al
                .endif

                movzx eax,drive
                .break .if ( !_wgetdcwd( eax, rbx, maxlen ) )

                wcslen( rbx )
                lea rdi,[rbx+rax*2]
                xor eax,eax

                .if ( drive )

                    mov al,dchar
                    mov [rbx],ax
                .endif

                mov ax,[rdi-2]
                .if ( ax == '\' || ax == '/' )

                    sub rdi,2
                .endif
            .endif

            mov word ptr [rdi],'\'
            lea rcx,[rbx+4]
        .endif

        .while word ptr [rsi] != 0

            mov ax,[rsi+4]
            mov dx,[rsi+2]

            .if ( word ptr [rsi] == '.' && dx == '.' && ( !ax || ax == '\' || ax == '/' ) )

                .repeat
                    sub rdi,2
                    mov ax,[rdi]
                .until ( ax == '\' || ax == '/' || rdi <= rcx )

                .if rdi < rcx

                    _set_errno(EACCES)
                    xor eax,eax
                    .break(1)
                .endif

                add rsi,4
                .if word ptr [rsi] != 0

                    add rsi,2
                .endif

            .elseif ( word ptr [rsi] == '.' && ( ( dx == '\' || dx == '/' ) || !dx ) )

                add rsi,2
                .if word ptr [rsi] != 0

                    add rsi,2
                .endif
            .else

                mov rdx,rdi
                mov ax,[rsi]

                .while ( ax && !( ax == '\' || ax == '/' ) && rdi < rcx )

                    lodsw
                    add rdi,2
                    mov [rdi],ax
                .endw

                .if ( rdi >= rcx )

                    _set_errno(ERANGE)
                    xor eax,eax
                    .break
                .endif

                .if ( rdi == rdx )

                    _set_errno(EINVAL)
                    xor eax,eax
                    .break(1)
                .endif

                add rdi,2
                mov word ptr [rdi],'\'
                mov ax,[rsi]
                .if ax == '\' || ax == '/'

                    add rsi,2
                .endif
            .endif
        .endw

        .if word ptr [rdi-2] == ':'
            add rdi,2
        .endif

        mov word ptr [rdi],0
        mov rax,rbx

    .until 1

    .if !rax

        .if rax == buf
            free(rbx)
        .endif
        xor eax,eax
    .endif
    ret

_wfullpath endp

    end


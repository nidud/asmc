; _TFULLPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include malloc.inc
include string.inc
include errno.inc
include winbase.inc
include tchar.inc

.code

_tfullpath proc uses rsi rdi rbx buf:LPTSTR, path:LPTSTR, maxlen:int_t

ifdef __UNIX__

    int 3

else

  local drive:byte
  local dchar:byte

    .repeat

        mov rsi,path
        .if ( !rsi || TCHAR ptr [rsi] == 0 )

            _tgetcwd(buf, maxlen)
            .break
        .endif

        mov rdi,buf
        .if ( !rdi )

            .if !malloc( _MAX_PATH*TCHAR )

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

        .if ( ( [rdi] == _tdl || [rdi] == _tal ) &&
              ( [rdi+TCHAR] == _tdl || [rdi+TCHAR] == _tal ) )

            mov eax,maxlen
            lea rcx,[rbx+rax*TCHAR-TCHAR]
            xor eax,eax
            xor edx,edx

            .repeat

                _tlodsb
                mov [rdi],_tal
                .break .if !_tal

                .if ( rdi >= rcx )

                    _set_errno(ERANGE)
                    xor eax,eax
                   .break
                .endif

                .if ( _tal == '\' || _tal == '/' )

                    mov TCHAR ptr [rdi],'\'
                    inc edx

                    .if ( ( edx == 2 && TCHAR ptr [rsi] == 0 ) ||
                          ( edx >= 3 && TCHAR ptr [rdi-TCHAR] == '\' ) )

                        _set_errno(EINVAL)
                        xor eax,eax
                       .break
                    .endif
                .endif

                add rdi,TCHAR
            .until ( edx == 4 )

            mov TCHAR ptr [rdi],'\'
            mov rcx,rdi

        .else

            mov drive,0
            mov _tcl,[rsi]
            or  cl,0x20

            .if ( _tcl >= 'a' && _tcl <= 'z' && TCHAR ptr [rsi+TCHAR] == ':' )

                _tmovsb
                _tmovsb
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

            mov _tal,[rsi]
            .if ( _tal == '\' || _tal == '/' )

                .if ( drive == 0 )

                    _getdrive()
                    add al,'A'- 1
                    _tstosb
                    mov al,':'
                    _tstosb
                .endif
                add rsi,TCHAR

            .else

                .if ( drive )

                    mov al,[rsi-2*TCHAR]
                    mov dchar,al
                .endif

                movzx eax,drive
                .break .if ( !_tgetdcwd( eax, rbx, maxlen ) )

                _tcslen( rbx )
                lea rdi,[rbx+rax*TCHAR]
                xor eax,eax

                .if ( drive )

                    mov al,dchar
                    mov [rbx],_tal
                .endif

                mov _tal,[rdi-TCHAR]
                .if ( _tal == '\' || _tal == '/' )

                    sub rdi,TCHAR
                .endif
            .endif

            mov TCHAR ptr [rdi],'\'
            lea rcx,[rbx+2*TCHAR]
        .endif

        .while TCHAR ptr [rsi] != 0

            mov _tal,[rsi+2*TCHAR]
            mov _tdl,[rsi+TCHAR]

            .if ( TCHAR ptr [rsi] == '.' && _tdl == '.' && ( !_tal || _tal == '\' || _tal == '/' ) )

                .repeat
                    sub rdi,TCHAR
                    mov _tal,[rdi]
                .until ( _tal == '\' || _tal == '/' || rdi <= rcx )

                .if rdi < rcx

                    _set_errno(EACCES)
                    xor eax,eax
                   .break(1)
                .endif

                add rsi,2*TCHAR
                .if TCHAR ptr [rsi] != 0

                    add rsi,TCHAR
                .endif

            .elseif ( TCHAR ptr [rsi] == '.' && ( ( _tdl == '\' || _tdl == '/' ) || !_tdl ) )

                add rsi,TCHAR
                .if TCHAR ptr [rsi] != 0

                    add rsi,TCHAR
                .endif
            .else

                mov rdx,rdi
                mov _tal,[rsi]

                .while ( _tal && !( _tal == '\' || _tal == '/' ) && rdi < rcx )

                    _tlodsb
                    add rdi,TCHAR
                    mov [rdi],_tal
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

                add rdi,TCHAR
                mov TCHAR ptr [rdi],'\'
                mov _tal,[rsi]
                .if _tal == '\' || _tal == '/'

                    add rsi,TCHAR
                .endif
            .endif
        .endw

        .if ( TCHAR ptr [rdi-TCHAR] == ':' )
            add rdi,TCHAR
        .endif

        mov TCHAR ptr [rdi],0
        mov rax,rbx
    .until 1

    .if ( rax == NULL )

        .if ( rax == buf )
            free(rbx)
        .endif
        xor eax,eax
    .endif
endif
    ret

_tfullpath endp

    end


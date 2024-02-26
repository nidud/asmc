; _FULLPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Contains the function _fullpath which makes an absolute path out
; of a relative path. i.e.  ..\pop\..\main.c => c:\src\main.c if the
; current directory is c:\src\src
;
; char *_fullpath( char *buf, const char *path, maxlen );
;

include direct.inc
include malloc.inc
include string.inc
include errno.inc
include winbase.inc

.code

ifdef __UNIX__

_fullpath proc buf:LPSTR, path:LPSTR, maxlen:UINT

    xor eax,eax
    ret

else

_fullpath proc uses rsi rdi rbx buf:LPSTR, path:LPSTR, maxlen:UINT

    .new drive:byte
    .new dchar:byte

    ldr rdi,buf
    ldr rsi,path

    .if ( !rsi || byte ptr [rsi] == 0 )

       .return( _getcwd(rdi, maxlen) )
    .endif

    .if ( !rdi )

        .if !malloc( _MAX_PATH )

            _set_errno(ENOMEM)
            .return( 0 )
        .endif

        mov rdi,rax
        mov maxlen,_MAX_PATH

    .elseif ( maxlen < _MAX_DRIVE+1 )

        _set_errno(ERANGE)
        .return( 0 )
    .endif

    .repeat

        mov rbx,rdi
        mov edx,'\/'
        mov eax,[rsi]

        .if ( ( al == dl || al == dh ) && ( ah == dl || ah == dh ) )

            mov ecx,maxlen
            add rcx,rbx
            dec rcx
            xor eax,eax

            .repeat

                lodsb
                mov [rdi],al
                .break .if !al

                .if ( rdi >= rcx )

                    _set_errno(ERANGE)
                    xor eax,eax
                   .break
                .endif

                .if ( al == dl || al == dh )

                    mov [rdi],dl
                    inc ah

                    .if ( ( ah == 2 && byte ptr [rsi] == 0) ||
                          ( ah >= 3 && byte ptr [rdi-1] == '\' ) )

                        _set_errno(EINVAL)
                        xor eax,eax
                       .break
                    .endif
                .endif

                inc rdi
            .until ( ah == 4 )

            mov [rdi],dl
            mov rcx,rdi

        .else

            mov drive,0
            mov cl,al
            or  cl,0x20

            .if ( cl >= 'a' && cl <= 'z' && ah == ':' )

                mov [rdi],ax
                add rdi,2
                add rsi,2
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

            mov al,[rsi]
            .if ( al == '\' || al == '/' )

                .if ( drive == 0 )

                    _getdrive()
                    add al,'A'- 1
                    stosb
                    mov al,':'
                    stosb
                .endif
                inc rsi

            .else

                .if ( drive )

                    mov al,[rsi-2]
                    mov dchar,al
                .endif

                movzx eax,drive
                .break .if ( !_getdcwd( eax, rbx, maxlen ) )

                strlen(rbx)
                add rax,rbx
                mov rdi,rax

                .if ( drive )

                    mov al,dchar
                    mov [rbx],al
                .endif

                mov al,[rdi-1]
                .if ( al == '\' || al == '/' )

                    dec rdi
                .endif
            .endif

            mov byte ptr [rdi],'\'
            lea rcx,[rbx+2]
        .endif

        .while ( byte ptr [rsi] != 0 )

            mov ax,[rsi]
            mov dl,[rsi+2]

            .if ( al == '.' && ah == '.' && ( !dl || dl == '\' || dl == '/' ) )

                .repeat
                    dec rdi
                    mov al,[rdi]
                .until ( al == '\' || al == '/' || rdi <= rcx )

                .if ( rdi < rcx )

                    _set_errno(EACCES)
                    xor eax,eax
                   .break( 1 )
                .endif

                add rsi,2
                .if ( byte ptr [rsi] != 0 )

                    inc rsi
                .endif

            .elseif ( al == '.' && ( ( ah == '\' || ah == '/' ) || !ah ) )

                inc rsi
                .if ( byte ptr [rsi] != 0 )

                    inc rsi
                .endif
            .else

                mov rdx,rdi
                mov al,[rsi]

                .while ( al && !( al == '\' || al == '/' ) && rdi < rcx )

                    lodsb
                    inc rdi
                    mov [rdi],al
                .endw

                .if ( rdi >= rcx )

                    _set_errno(ERANGE)
                    xor eax,eax
                   .break
                .endif

                .if ( rdi == rdx )

                    _set_errno(EINVAL)
                    xor eax,eax
                   .break( 1 )
                .endif

                inc rdi
                mov byte ptr [rdi],'\'
                mov al,[rsi]

                .if ( al == '\' || al == '/' )

                    inc rsi
                .endif
            .endif
        .endw

        .if ( byte ptr [rdi-1] == ':' )
            inc rdi
        .endif

        mov byte ptr [rdi],0
        mov rax,rbx
    .until 1

    .if ( rax == NULL )

        .if ( rax == buf )
            free(rbx)
        .endif
        xor eax,eax
    .endif
    ret

endif

_fullpath endp

    end


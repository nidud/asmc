include io.inc
include share.inc
include stdio.inc
include fcntl.inc
include stat.inc
include errno.inc
include winbase.inc

extrn _fmode:DWORD
extrn _umaskval:DWORD

    .code

;    option win64:nosave

_sopen proc uses rsi rdi rbx path:LPSTR, oflag:UINT, shflag:UINT, args:VARARG

    local SecurityAttributes:SECURITY_ATTRIBUTES
    local _ch:BYTE

    xor eax,eax
    xor ebx,ebx
    mov SecurityAttributes.nLength,sizeof(SECURITY_ATTRIBUTES)
    mov SecurityAttributes.bInheritHandle,eax
    mov SecurityAttributes.lpSecurityDescriptor,rax
    mov eax,edx
    .if eax & O_NOINHERIT
        mov bl,FH_NOINHERIT
    .else
        inc SecurityAttributes.bInheritHandle
    .endif

    ;
    ; figure out binary/text mode
    ;
    .if !(eax & O_BINARY)
        .if eax & O_TEXT
            or bl,FH_TEXT
        .elseif _fmode != O_BINARY  ; check default mode
            or bl,FH_TEXT
        .endif
    .endif

    ;
    ; decode the access flags
    ;
    and eax,O_RDONLY or O_WRONLY or O_RDWR
    mov edi,GENERIC_READ        ; read access
    .if eax != O_RDONLY
        mov edi,GENERIC_WRITE   ; write access
        .if eax != O_WRONLY
            mov edi,GENERIC_READ or GENERIC_WRITE
            .if eax != O_RDWR
                jmp error_inval
            .endif
        .endif
    .endif
    ;
    ; decode sharing flags
    ;
    mov eax,r8d                     ; shflag
    .switch eax
      .case SH_DENYNO               ; share read and write access
        mov r8d,FILE_SHARE_READ or FILE_SHARE_WRITE
        .endc
      .case SH_DENYWR
        mov r8d,FILE_SHARE_READ     ; share read access
        .endc
      .case SH_DENYRD
        mov r8d,FILE_SHARE_WRITE    ; share write access
        .endc
      .default
        xor r8d,r8d                 ; exclusive access
        .if eax != SH_DENYRW
            jmp error_inval
        .endif
    .endsw
    ;
    ; decode open/create method flags
    ;
    mov eax,edx
    and eax,O_CREAT or O_EXCL or O_TRUNC
    .switch eax
      .case 0
      .case O_EXCL
        mov eax,OPEN_EXISTING
        .endc
      .case O_CREAT
        mov eax,OPEN_ALWAYS
        .endc
      .case O_CREAT or O_EXCL
      .case O_CREAT or O_EXCL or O_TRUNC
        mov eax,CREATE_NEW
        .endc
      .case O_CREAT or O_TRUNC
        mov eax,CREATE_ALWAYS
        .endc
      .case O_TRUNC
      .case O_TRUNC or O_EXCL
        mov eax,TRUNCATE_EXISTING
        .endc
      .default
        jmp error_inval
    .endsw

    mov r10d,FILE_ATTRIBUTE_NORMAL
    .if edx & O_CREAT
        mov r11d,_umaskval
        not r11d
        and r9d,r11d
        .if !(r9d & S_IWRITE)
            mov r10d,FILE_ATTRIBUTE_READONLY
        .endif
    .endif

    .if edx & O_TEMPORARY
        or r10d,FILE_FLAG_DELETE_ON_CLOSE
        or edi,M_DELETE
    .endif
    .if edx & O_SHORT_LIVED
        or r10d,FILE_ATTRIBUTE_TEMPORARY
    .endif
    .if edx & O_SEQUENTIAL
        or r10d,FILE_FLAG_SEQUENTIAL_SCAN
    .elseif edx & O_RANDOM
        or r10d,FILE_FLAG_RANDOM_ACCESS
    .endif

    xor esi,esi
    lea r11,_osfile
    .while byte ptr [r11+rsi] & FH_OPEN
        inc esi
        .if esi == _nfile
            xor eax,eax
            mov oserrno,eax ; no OS error
            mov errno,EBADF
            dec rax
            jmp toend
        .endif
    .endw
    xchg edi,edx
    .ifd CreateFileA(rcx, edx, r8d, &SecurityAttributes, eax, r10d, NULL) != -1

        lea rcx,_osfhnd
        mov [rcx+rsi*8],rax
        lea rcx,_osfile
        or  BYTE PTR [rcx+rsi],FH_OPEN

        .ifd GetFileType(rax) == FILE_TYPE_UNKNOWN
            jmp error
        .elseif eax == FILE_TYPE_CHAR
            or bl,FH_DEVICE
        .elseif eax == FILE_TYPE_PIPE
            or bl,FH_PIPE
        .endif
        lea rax,_osfile
        or [rax+rsi],bl

        .if !(bl & FH_DEVICE or FH_PIPE) && bl & FH_TEXT && edi & O_RDWR

            .ifd _lseek(esi, -1, SEEK_END) != -1

                mov rbx,rax
                mov _ch,0
                .ifd !_read(esi, &_ch, 1)
                    .if _ch == 26
                        .ifd _chsize(esi, rbx) == -1
                            jmp error
                        .endif
                    .endif
                .endif
                .ifd _lseek(esi, 0, SEEK_SET) == -1
                    jmp error
                .endif
            .elseif oserrno != ERROR_NEGATIVE_SEEK
                jmp error
            .endif
        .endif

        lea rax,_osfile
        add rax,rsi
        .if !(byte ptr [rax] & FH_DEVICE or FH_PIPE) && edi & O_APPEND

            or byte ptr [rax],FH_APPEND
        .endif
        mov eax,esi
    .endif
toend:
    ret
error:
    _close(esi)
    mov eax,-1
    jmp toend
error_inval:
    mov errno,EINVAL
    xor eax,eax
    mov oserrno,eax
    dec eax
    jmp toend
_sopen endp

    END

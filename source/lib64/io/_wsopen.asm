; _WSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include fcntl.inc
include stat.inc
include errno.inc
include winbase.inc
include winnt.inc

extrn _fmode:DWORD
extrn _umaskval:DWORD

.code

_wsopen proc uses rsi rdi rbx path:LPWSTR, oflag:SINT, shflag:SINT, args:VARARG

  local sa:SECURITY_ATTRIBUTES, fileflags:BYTE, eof:BYTE

    xor eax,eax
    mov sa.bInheritHandle,eax
    mov sa.lpSecurityDescriptor,rax
    mov fileflags,al
    mov eax,oflag
    mov sa.nLength,sizeof(SECURITY_ATTRIBUTES)

    .if eax & O_NOINHERIT
        mov fileflags,FH_NOINHERIT
    .else
        inc sa.bInheritHandle
    .endif
    ;
    ; figure out binary/text mode
    ;
    .if !( eax & O_BINARY )
        .if eax & O_TEXT
            or fileflags,FH_TEXT
        .elseif _fmode != O_BINARY  ; check default mode
            or fileflags,FH_TEXT
        .endif
    .endif

    .repeat
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
                    mov errno,EINVAL
                    xor eax,eax
                    mov _doserrno,eax
                    dec rax
                    .break
                .endif
            .endif
        .endif
        ;
        ; decode sharing flags
        ;
        mov eax,shflag
        .switch eax
          .case SH_DENYNO           ; share read and write access
            mov ebx,FILE_SHARE_READ or FILE_SHARE_WRITE
            .endc
          .case SH_DENYWR
            mov ebx,FILE_SHARE_READ     ; share read access
            .endc
          .case SH_DENYRD
            mov ebx,FILE_SHARE_WRITE    ; share write access
            .endc
          .default
            xor ebx,ebx         ; exclusive access
            .if eax != SH_DENYRW
                mov errno,EINVAL
                xor eax,eax
                mov _doserrno,eax
                dec rax
                .break
            .endif
        .endsw
        ;
        ; decode open/create method flags
        ;
        mov eax,oflag
        and eax,O_CREAT or O_EXCL or O_TRUNC
        .switch eax
          .case 0
          .case O_EXCL
            mov ecx,OPEN_EXISTING
            .endc
          .case O_CREAT
            mov ecx,OPEN_ALWAYS
            .endc
          .case O_CREAT or O_EXCL
          .case O_CREAT or O_EXCL or O_TRUNC
            mov ecx,CREATE_NEW
            .endc
          .case O_CREAT or O_TRUNC
            mov ecx,CREATE_ALWAYS
            .endc
          .case O_TRUNC
          .case O_TRUNC or O_EXCL
            mov ecx,TRUNCATE_EXISTING
            .endc
          .default
            mov errno,EINVAL
            xor eax,eax
            mov _doserrno,eax
            dec rax
            .break
        .endsw

        mov eax,ecx
        mov ecx,FILE_ATTRIBUTE_NORMAL
        mov edx,oflag
        .if edx & O_CREAT

            push rax
            lea  rax,args
            mov  eax,[rax]      ; fopen(0284h)
            mov  edx,_umaskval  ; 0
            not  edx            ; -1
            and  eax,edx        ; 0284h
            mov  edx,oflag
            and  eax,S_IWRITE   ; 0080h
            pop  rax
            .ifz
                mov ecx,FILE_ATTRIBUTE_READONLY
            .endif
        .endif

        .if edx & O_TEMPORARY
            or ecx,FILE_FLAG_DELETE_ON_CLOSE
            or edi,M_DELETE
        .endif
        .if edx & O_SHORT_LIVED
            or ecx,FILE_ATTRIBUTE_TEMPORARY
        .endif
        .if edx & O_SEQUENTIAL
            or ecx,FILE_FLAG_SEQUENTIAL_SCAN
        .elseif edx & O_RANDOM
            or ecx,FILE_FLAG_RANDOM_ACCESS
        .endif

        mov r10d,ecx
        .if _osopenW(path, edi, ebx, &sa, eax, r10d) != -1

            mov esi,eax
            mov bl,fileflags
            lea r8,_osfhnd
            mov rcx,[r8+rsi*8]
            .if GetFileType(rcx) == FILE_TYPE_UNKNOWN
                _close(esi)
                mov eax,-1
                .break
            .elseif eax == FILE_TYPE_CHAR
                or bl,FH_DEVICE
            .elseif eax == FILE_TYPE_PIPE
                or bl,FH_PIPE
            .endif
            lea r8,_osfile
            or [r8+rsi],bl

            .if !(bl & FH_DEVICE or FH_PIPE) && bl & FH_TEXT && oflag & O_RDWR

                .if _lseek(esi, -1, SEEK_END) != -1

                    mov ebx,eax
                    mov eof,0
                    osread(esi, &eof, 1)
                    .if !eax && eof == 26

                        .if _chsize(esi, ebx) == -1
                            _close(esi)
                            mov eax,-1
                            .break
                        .endif
                    .endif

                    .if _lseek(esi, 0, SEEK_SET) == -1
                        _close(esi)
                        mov eax,-1
                        .break
                    .endif
                .elseif _doserrno != ERROR_NEGATIVE_SEEK
                    _close(esi)
                    mov eax,-1
                    .break
                .endif
            .endif
            lea r8,_osfile
            mov al,[r8+rsi]
            .if ( !( al & FH_DEVICE or FH_PIPE ) && oflag & O_APPEND )
                or byte ptr [r8+rsi],FH_APPEND
            .endif
            mov eax,esi
        .endif
    .until 1
    ret
_wsopen endp

    end

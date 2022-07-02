; _SOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include stdio.inc
include fcntl.inc
include sys/stat.inc
include errno.inc
include winbase.inc

externdef _fmode:uint_t
externdef _umaskval:uint_t

.code

_sopen proc uses rsi rdi rbx path:string_t, oflag:int_t, shflag:int_t, args:vararg

   .new SecurityAttributes:SECURITY_ATTRIBUTES = { SECURITY_ATTRIBUTES, NULL, 0 }

ifndef _WIN64
    mov edx,oflag
endif
    xor ebx,ebx
    .if ( edx & O_NOINHERIT )
        mov bl,FH_NOINHERIT
    .else
        inc SecurityAttributes.bInheritHandle
    .endif
    ;
    ; figure out binary/text mode
    ;
    .if !( edx & O_BINARY )
        .if ( edx & O_TEXT )
            or bl,FH_TEXT
        .elseif ( _fmode != O_BINARY ) ; check default mode
            or bl,FH_TEXT
        .endif
    .endif

    ;
    ; decode the access flags
    ;
    mov eax,edx
    and eax,O_RDONLY or O_WRONLY or O_RDWR
    .switch pascal eax
    .case O_RDONLY  ; read access
        mov ecx,GENERIC_READ
    .case O_WRONLY  ; write access
        mov ecx,GENERIC_WRITE
        .if ( ( edx & O_APPEND ) && ( edx & ( _O_WTEXT or _O_U16TEXT or _O_U8TEXT ) ) )
            or ecx,GENERIC_READ
        .endif
    .case O_RDWR    ; read and write access
        mov ecx,GENERIC_READ or GENERIC_WRITE
    .default
        _set_errno(EINVAL)
        _set_doserrno(0)
        .return -1
    .endsw
    .new fileaccess:uint_t = ecx

    ;
    ; decode sharing flags
    ;
    mov eax,shflag
    .switch eax
    .case SH_SECURE ; share read access only if read-only
        .if ( ecx == GENERIC_READ )
            mov ecx,FILE_SHARE_READ
        .else
            xor ecx,ecx
        .endif
        .endc
    .case SH_DENYNO               ; share read and write access
        mov ecx,FILE_SHARE_READ or FILE_SHARE_WRITE
       .endc
    .case SH_DENYWR
        mov ecx,FILE_SHARE_READ     ; share read access
       .endc
    .case SH_DENYRD
        mov ecx,FILE_SHARE_WRITE    ; share write access
       .endc
    .case SH_DENYRW
        xor ecx,ecx                 ; exclusive access
       .endc
    .default
        _set_errno(EINVAL)
        _set_doserrno(0)
        .return -1
    .endsw
    .new fileshare:uint_t = ecx
    ;
    ; decode open/create method flags
    ;
    mov eax,edx
    and eax,O_CREAT or O_EXCL or O_TRUNC
    .switch pascal eax
    .case 0
    .case O_EXCL
        mov ecx,OPEN_EXISTING
    .case O_CREAT
        mov ecx,OPEN_ALWAYS
    .case O_CREAT or O_EXCL
    .case O_CREAT or O_EXCL or O_TRUNC
        mov ecx,CREATE_NEW
    .case O_CREAT or O_TRUNC
        mov ecx,CREATE_ALWAYS
    .case O_TRUNC
    .case O_TRUNC or O_EXCL
        mov ecx,TRUNCATE_EXISTING
    .default
        _set_errno(EINVAL)
        _set_doserrno(0)
        .return -1
    .endsw
    .new filecreate:uint_t = ecx

    mov ecx,FILE_ATTRIBUTE_NORMAL
    .if ( edx & O_CREAT )

        mov eax,_umaskval
        not eax
        lea rcx,args
        and eax,[rcx]
        mov ecx,FILE_ATTRIBUTE_NORMAL

        .if !( eax & _S_IWRITE )

            mov ecx,FILE_ATTRIBUTE_READONLY
        .endif
    .endif

    xor eax,eax
    .if ( edx & O_TEMPORARY )
        or eax,FILE_FLAG_DELETE_ON_CLOSE
        or edi,M_DELETE
        or fileshare,FILE_SHARE_DELETE
    .endif
    .if ( edx & _O_OBTAIN_DIR )
        or eax,FILE_FLAG_BACKUP_SEMANTICS
    .endif
    .if ( edx & O_SHORT_LIVED )
        or ecx,FILE_ATTRIBUTE_TEMPORARY
    .endif
    .if ( edx & O_SEQUENTIAL )
        or eax,FILE_FLAG_SEQUENTIAL_SCAN
    .elseif ( edx & O_RANDOM )
        or eax,FILE_FLAG_RANDOM_ACCESS
    .endif
    or ecx,eax

    .new fileattrib:uint_t = ecx

    xor esi,esi
    lea rcx,_osfile
    .while ( byte ptr [rcx+rsi] & FH_OPEN )

        inc esi
        .if ( esi == _nfile  )

            _set_doserrno(0) ; no OS error
            _set_errno(EBADF)
            .return -1
        .endif
    .endw

    mov edi,edx
    .ifd ( CreateFileA( path, fileaccess, fileshare, &SecurityAttributes,
            filecreate, fileattrib, NULL ) == -1 )

        mov eax,fileaccess
        and eax,GENERIC_READ or GENERIC_WRITE
        .if ( eax == ( GENERIC_READ or GENERIC_WRITE ) && ( edi & _O_WRONLY ) )

            ;
            ; We just failed on CreateFile(), because we might be trying
            ; open something for read while it cannot be read (eg. pipes or devices).
            ; So try again with GENERIC_WRITE and we will have to use the default
            ; encoding.  We won't be able to determine the encoding from reading
            ; the BOM.
            ;
            and fileaccess,NOT GENERIC_READ
            .ifd ( CreateFileA( path, fileaccess, fileshare, &SecurityAttributes,
                    filecreate, fileattrib, NULL ) == -1 )

                .return _dosmaperr( GetLastError() )
            .endif
        .else
            .return _dosmaperr( GetLastError() )
        .endif
    .endif

    lea rcx,_osfhnd
    mov [rcx+rsi*size_t],rax
    lea rcx,_osfile
    or  byte ptr [rcx+rsi],FH_OPEN

    .while 1

        .break .ifd ( GetFileType( rax ) == FILE_TYPE_UNKNOWN )

        .if ( eax == FILE_TYPE_CHAR )
            or bl,FH_DEVICE
        .elseif ( eax == FILE_TYPE_PIPE )
            or bl,FH_PIPE
        .endif
        lea rax,_osfile
        or  [rax+rsi],bl

        .if ( !( bl & FH_DEVICE or FH_PIPE ) && bl & FH_TEXT && edi & O_RDWR )

            .ifd ( _lseek( esi, -1, SEEK_END ) != -1 )

               .new eof:byte = 0
                mov rbx,rax

                .ifd ( osread( esi, &eof, 1 ) == 0 )

                    .if ( eof == 26 )

                        .break .ifd ( _chsize( esi, rbx ) == -1 )
                    .endif
                .endif
                .break .ifd ( _lseek( esi, 0, SEEK_SET ) == -1 )

            .elseif ( _get_doserrno( 0 ) != ERROR_NEGATIVE_SEEK )

                .break
            .endif
        .endif

        lea rax,_osfile
        add rax,rsi
        .if ( !( byte ptr [rax] & FH_DEVICE or FH_PIPE ) && edi & O_APPEND )
            or byte ptr [rax],FH_APPEND
        .endif
        .return esi
    .endw
    _close( esi )
    .return( -1 )

_sopen endp

    end

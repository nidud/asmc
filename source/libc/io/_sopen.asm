; _SOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include stdio.inc
include stdlib.inc
include fcntl.inc
include sys/stat.inc
include errno.inc
ifdef __UNIX__
include linux/kernel.inc

    option win64:noauto ; skip the vararg stack
else
include winbase.inc

define BOM_WRITE        1
define BOM_CHECK        2
define UTF16LE_BOM      0xFEFF      ; UTF16 Little Endian Byte Order Mark
define UTF16BE_BOM      0xFFFE      ; UTF16 Big Endian Byte Order Mark
define BOM_MASK         0xFFFF      ; Mask for testing Byte Order Mark
define UTF8_BOM         0xBFBBEF    ; UTF8 Byte Order Mark
define UTF16_BOMLEN     2           ; No of Bytes in a UTF16 BOM
define UTF8_BOMLEN      3           ; No of Bytes in a UTF8 BOM

externdef _umaskval:uint_t

endif

.code

ifdef __UNIX__

_sopen proc uses rsi rdi rbx path:string_t, oflag:int_t, shflag:int_t, args:vararg

   .new mode:uint_t
   .new share:uint_t
   .new access:uint_t
   .new fh:uint_t

    ldr rdi,path
    ldr esi,oflag
    ldr edx,shflag
ifndef _WIN64
    mov ecx,args
endif

    mov eax,esi
    and eax,O_RDONLY or O_WRONLY or O_RDWR

    .switch pascal eax
    .case O_RDONLY  ; read access
        mov eax,S_IRUSR
    .case O_WRONLY  ; write access
        mov eax,S_IWUSR
        .if ( ( esi & O_APPEND ) && ( esi & ( _O_WTEXT or _O_U16TEXT or _O_U8TEXT ) ) )
            or eax,S_IRUSR
        .endif
    .case O_RDWR    ; read and write access
        mov eax,S_IRUSR or S_IWUSR
    .default
        _set_errno(EINVAL)
        .return -1
    .endsw
    mov access,eax

    ; decode sharing flags

    .switch edx
    .case SH_SECURE ; share read access only if read-only
        .if ( eax == S_IRUSR )
            mov eax,S_IROTH
        .else
            xor eax,eax
        .endif
        .endc
    .case SH_DENYNO         ; share read and write access
        mov eax,S_IROTH or S_IWOTH
       .endc
    .case SH_DENYWR
        mov eax,S_IROTH     ; share read access
       .endc
    .case SH_DENYRD
        mov eax,S_IWOTH     ; share write access
       .endc
    .case SH_DENYRW
        xor eax,eax         ; exclusive access
       .endc
    .default
        _set_errno(EINVAL)
        .return -1
    .endsw
    or access,eax

    mov eax,FOPEN

    ; figure out binary/text mode

    .if !( esi & O_BINARY )
        .if ( esi & O_TEXT )
            or eax,FTEXT
        .elseif ( _fmode != O_BINARY ) ; check default mode
            or eax,FTEXT
        .endif
    .endif
    .if ( esi & O_APPEND )
        or eax,FAPPEND
    .endif
    mov fh,eax

    mov edx,access
    .if ( esi & O_CREAT )

        or edx,ecx
        .if ( esi & O_APPEND )
            mov rbx,rdi
            mov access,edx
            .ifsd ( sys_open(rdi, esi, edx) < 0 )
                sys_creat(rbx, access)
            .endif
        .else
            sys_creat(rdi, edx)
        .endif
    .else
        sys_open(rdi, esi, edx)
    .endif
    .ifs ( eax < 0 )

        neg eax
        _set_errno(eax)
        .return -1
    .endif
    mov ecx,eax
    mov edx,fh
    mov _osfile(ecx),dl
    mov eax,ecx
    ret

else

_sopen proc uses rsi rdi rbx path:string_t, oflag:int_t, shflag:int_t, args:vararg

    .new osfh:HANDLE                ; OS handle of opened file
    .new fmode:int_t = 0
    .new fileaccess:DWORD           ; OS file access (requested)
    .new fileshare:DWORD            ; OS file sharing mode
    .new filecreate:DWORD = 0       ; OS method of opening/creating
    .new fileattrib:DWORD           ; OS file attributes
    .new SecurityAttributes:SECURITY_ATTRIBUTES = { SECURITY_ATTRIBUTES, NULL, 0 }
    .new bom:uint_t
    .new eof:int_t
    .new dwLastError:int_t
    .new fh:int_t
    .new tmode:char_t = __IOINFO_TM_ANSI ; textmode - ANSI/UTF-8/UTF-16
    .new fileflags:char_t = 0       ; _osfile flags

    ldr edi,oflag

    _set_doserrno(0)
    _get_fmode(&fmode)

    .if ( edi & O_NOINHERIT )
        mov fileflags,FNOINHERIT
    .else
        inc SecurityAttributes.bInheritHandle
    .endif
    ;
    ; figure out binary/text mode
    ;
    .if !( edi & O_BINARY )
        .if ( edi & O_TEXT )
            or fileflags,FTEXT
        .elseif ( fmode != O_BINARY ) ; check default mode
            or fileflags,FTEXT
        .endif
    .endif


    ; decode the access flags

    mov eax,edi
    and eax,O_RDONLY or O_WRONLY or O_RDWR
    .switch pascal eax
    .case O_RDONLY  ; read access
        mov ecx,GENERIC_READ
    .case O_WRONLY  ; write access
        mov ecx,GENERIC_WRITE
        .if ( ( edi & O_APPEND ) && ( edi & ( _O_WTEXT or _O_U16TEXT or _O_U8TEXT ) ) )
            or ecx,GENERIC_READ
        .endif
    .case O_RDWR    ; read and write access
        mov ecx,GENERIC_READ or GENERIC_WRITE
    .default
        _set_errno(EINVAL)
        .return(-1)
    .endsw
    mov fileaccess,ecx


    ; decode sharing flags

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
        .return(-1)
    .endsw
    mov fileshare,ecx

    ; decode open/create method flags

    mov eax,edi
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
        .return(-1)
    .endsw
    mov filecreate,ecx

    mov ecx,FILE_ATTRIBUTE_NORMAL
    .if ( edi & O_CREAT )

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
    .if ( edi & O_TEMPORARY )
        or eax,FILE_FLAG_DELETE_ON_CLOSE
        or fileaccess,M_DELETE
        or fileshare,FILE_SHARE_DELETE
    .endif
    .if ( edi & _O_OBTAIN_DIR )
        or eax,FILE_FLAG_BACKUP_SEMANTICS
    .endif
    .if ( edi & O_SHORT_LIVED )
        or ecx,FILE_ATTRIBUTE_TEMPORARY
    .endif
    .if ( edi & O_SEQUENTIAL )
        or eax,FILE_FLAG_SEQUENTIAL_SCAN
    .elseif ( edi & O_RANDOM )
        or eax,FILE_FLAG_RANDOM_ACCESS
    .endif
    or ecx,eax
    mov fileattrib,ecx

    .ifd ( _alloc_osfhnd() == -1 )

        _set_errno(EMFILE)
        .return(-1)
    .endif

    mov fh,eax
    mov rsi,rcx

    assume rsi:pioinfo

    ; Beyond this do not set *pfh = -1 on errors for MT.
    ; Because the caller needs to release the lock on the handle

    .if ( CreateFileA( path, fileaccess, fileshare, &SecurityAttributes,
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

                _dosmaperr( GetLastError() )
                .return(-1)
            .endif
        .else
            _dosmaperr( GetLastError() )
            .return(-1)
        .endif
    .endif

    mov osfh,rax

    .ifd ( GetFileType( rax ) == FILE_TYPE_UNKNOWN )

        mov dwLastError,GetLastError()
        _dosmaperr(dwLastError)
        CloseHandle(osfh)
        .if ( dwLastError == ERROR_SUCCESS )

            ;
            ; If GetFileType returns FILE_TYPE_UNKNOWN but doesn't fail,
            ; GetLastError returns ERROR_SUCCESS.
            ; This function is not designed to deal with unknown types of files
            ; and must return an error.
            ;
            _set_errno(EACCES)
        .endif
        .return(-1)
    .endif

    .if ( eax == FILE_TYPE_CHAR )
        or fileflags,FDEV
    .elseif ( eax == FILE_TYPE_PIPE )
        or fileflags,FPIPE
    .endif

    mov al,fileflags
    or  al,FOPEN
    or  [rsi].osfile,al
    mov rdx,osfh
    mov [rsi].osfhnd,rdx

    .if ( !( al & FDEV or FPIPE ) && al & FTEXT && edi & O_RDWR )

        ; We have a text mode file.  If it ends in CTRL-Z, we wish to
        ; remove the CTRL-Z character, so that appending will work.
        ; We do this by seeking to the end of file, reading the last
        ; byte, and shortening the file if it is a CTRL-Z.

        .if ( _lseeki64( fh, -1, SEEK_END ) != -1 )

            mov eof,0
            mov rbx,rax

            .if ( _read( fh, &eof, 1 ) == 0 )

                .if ( eof == 26 )

                    .if ( _chsize( fh, rbx ) == -1 )

                        jmp error
                    .endif
                .endif
            .endif
            .if ( _lseeki64( fh, 0, SEEK_SET ) == -1 )

                jmp error
            .endif

        .elseif ( _get_doserrno( 0 ) != ERROR_NEGATIVE_SEEK )

            jmp error
        .endif
    .endif

    mov eax,edi
    and eax,(_O_TEXT or _O_WTEXT or _O_U16TEXT or _O_U8TEXT)

    .if ( fileflags & FTEXT )

        .switch eax
        .case _O_WTEXT
        .case _O_WTEXT or _O_TEXT
            mov eax,edi
            and eax,(_O_WRONLY or _O_CREAT or _O_TRUNC)
            .if ( eax == (_O_WRONLY or _O_CREAT or _O_TRUNC) )
                mov tmode,__IOINFO_TM_UTF16LE
            .endif
            .endc
        .case _O_U16TEXT
        .case _O_U16TEXT or _O_TEXT
            mov tmode,__IOINFO_TM_UTF16LE
           .endc
        .case _O_U8TEXT
        .case _O_U8TEXT or _O_TEXT
            mov tmode,__IOINFO_TM_UTF8
           .endc
        .endsw

        ; If the file hasn't been opened with the UNICODE flags then we
        ; have nothing to do - textmode's already set to default specified in oflag

        .if ( edi & (_O_WTEXT or _O_U16TEXT or _O_U8TEXT) )

            mov bom,0
            xor ebx,ebx

            .if ( !( fileflags & FDEV ) )

                mov eax,fileaccess
                and eax,(GENERIC_READ or GENERIC_WRITE)

                .switch eax
                .case GENERIC_READ
                    or ebx,BOM_CHECK
                   .endc
                .case GENERIC_WRITE
                    mov eax,filecreate
                    .switch eax
                    ;
                    ; Write BOM if empty file
                    ;
                    .case OPEN_EXISTING
                    .case OPEN_ALWAYS

                        ; Check if the file contains at least one byte
                        ; Fall through otherwise

                        .if ( _lseeki64(fh, 0, SEEK_END) != 0 )

                            .if ( _lseeki64(fh, 0, SEEK_SET) == -1 )

                                jmp error
                            .endif
                        .endif

                    ; New or truncated file. Always write BOM

                    .case CREATE_NEW
                    .case CREATE_ALWAYS
                    .case TRUNCATE_EXISTING
                        or ebx,BOM_WRITE
                       .endc
                    .endsw
                    .endc
                .case GENERIC_READ or GENERIC_WRITE

                    mov eax,filecreate
                    .switch eax

                    ; Check for existing BOM, Write BOM if empty file

                    .case OPEN_EXISTING
                    .case OPEN_ALWAYS

                        ; Check if the file contains at least one byte
                        ; Fall through otherwise

                        .if ( _lseeki64(fh, 0, SEEK_END) != 0 )
                            .if (_lseeki64(fh, 0, SEEK_SET) == -1 )
                                jmp error
                            .endif
                            or ebx,BOM_CHECK
                        .else
                            or ebx,BOM_WRITE ; reset if file is not zero size
                        .endif
                        .endc

                    ; New or truncated file. Always write BOM

                    .case CREATE_NEW
                    .case TRUNCATE_EXISTING
                    .case CREATE_ALWAYS
                        or ebx,BOM_WRITE
                       .endc
                    .endsw
                    .endc
                .endsw

                .if ( ebx & BOM_CHECK )

                    _read(fh, &bom, UTF8_BOMLEN)

                    ;
                    ; Internal Validation.
                    ; This branch should never be taken if bWriteBom is 1 and count > 0
                    ;

                    .ifs ( eax > 0 && ebx & BOM_WRITE )

                        ;_ASSERTE(0 && "Internal Error");
                        and ebx,not BOM_WRITE
                    .endif

                    mov ecx,bom

                    .switch eax
                    .case -1
                        jmp error
                    .case UTF8_BOMLEN
                        .if( ecx == UTF8_BOM )
                            mov tmode,__IOINFO_TM_UTF8
                           .endc
                        .endif
                    .case UTF16_BOMLEN
                        mov eax,ecx
                        and eax,BOM_MASK
                        .if ( eax == UTF16BE_BOM )
                            jmp error
                        .endif
                        .if ( eax == UTF16LE_BOM )

                            ; We have read 3 bytes, so we should seek back 1 byte

                            .if ( _lseeki64(fh, UTF16_BOMLEN, SEEK_SET) == -1 )
                                jmp error
                            .endif
                            mov tmode,__IOINFO_TM_UTF16LE
                           .endc
                        .endif

                        ; Fall through to default case to lseek to beginning of file

                    .default
                        .if ( _lseeki64(fh, 0, SEEK_SET) == -1 )

                            ; No BOM, so we should seek back to the beginning of the file

                            jmp error
                        .endif
                        .endc
                    .endsw
                .endif

                .if ( ebx & BOM_WRITE )

                    xor edi,edi
                    xor ebx,ebx
                    mov bom,ebx

                    ; If we are creating a new file, we write a UTF-16LE or UTF8 BOM

                    .if ( tmode == __IOINFO_TM_UTF16LE )

                        mov bom,UTF16LE_BOM
                        mov ebx,UTF16_BOMLEN

                    .elseif ( tmode == __IOINFO_TM_UTF8 )

                        mov bom,UTF8_BOM
                        mov ebx,UTF8_BOMLEN
                    .endif

                    .while ( ebx > edi )

                        ;
                        ; Note that write may write less than bomlen characters, but not really fail.
                        ; Retry till write fails or till we wrote all the characters.
                        ;
                        lea rdx,bom
                        add rdx,rdi
                        mov ecx,ebx
                        sub ecx,edi
                        .ifd ( _write(fh, rdx, ecx) == -1 )
                            jmp error
                        .endif
                        add edi,eax
                    .endw
                .endif
            .endif
        .endif
    .endif

    mov [rsi].textmode,tmode

    .if ( !( fileflags & FDEV or FPIPE ) && edi & O_APPEND )

        or [rsi].osfile,FAPPEND
    .endif

    ;
    ; re-open the file with write access only if we opened the file
    ; with read access to read the BOM before
    ;
    mov eax,fileaccess
    and eax,(GENERIC_READ or GENERIC_WRITE)
    .if ( eax == (GENERIC_READ or GENERIC_WRITE) && (edi & _O_WRONLY))

        ; we will have to reopen the file again with the write access (but not read)

        CloseHandle(osfh)
        and fileaccess,not GENERIC_READ

        ; we want to use OPEN_EXISTING here, because the user can open the an non-existing
        ; file for append with _O_EXCL flag

        .if ( CreateFileA( path, fileaccess, fileshare, &SecurityAttributes,
                OPEN_EXISTING, fileattrib, NULL ) == -1 )

            ;
            ; OS call to open/create file failed! map the error, release
            ; the lock, and return -1. Note that it's *necessary* to
            ; call _free_osfhnd (unlike the situation before), because we have
            ; already set the file handle in the _ioinfo structure
            ;
            _dosmaperr(GetLastError())

            mov [rsi].osfile,0
           .return(-1)
        .else

            ; We were able to open the file successfully, set the file
            ; handle in the _ioinfo structure, then we are done.  All
            ; the fileflags should have been set properly already.

            mov [rsi].osfhnd,rax
        .endif
    .endif
    .return(fh)

error:
    _close(fh)
    .return(-1)
endif
_sopen endp

    end

include io.inc
include time.inc
include direct.inc
include errno.inc
include stat.inc
include string.inc
include stdlib.inc
include alloc.inc
include crtl.inc
include winbase.inc

A_D equ 10h

.code

_lk_getltime proc private ft
local SystemTime:SYSTEMTIME
local LocalFTime:FILETIME
    .if FileTimeToLocalFileTime(ft, &LocalFTime)
        .if FileTimeToSystemTime(&LocalFTime, &SystemTime)
            _loctotime_t(
                SystemTime.wYear,
                SystemTime.wMonth,
                SystemTime.wDay,
                SystemTime.wHour,
                SystemTime.wMinute,
                SystemTime.wSecond
            )
        .endif
    .endif
    ret
_lk_getltime ENDP

_stat proc uses esi edi ebx fname:LPSTR, buf:PVOID

local path, drive, ff:WIN32_FIND_DATA, pathbuf[_MAX_PATH]:BYTE

    mov esi,fname
    mov edi,buf
    _mbspbrk(esi, "?*")
    test eax,eax
    jnz error_1

    mov eax,[esi]
    .if ah == ':'
        test eax,00FF0000h
        jz error_1
        or al,20h
        sub al,'a' - 1
        movzx eax,al
    .else
        _getdrive()
    .endif
    mov drive,eax

    .if FindFirstFileA(esi, addr ff) == -1

        _mbspbrk(esi, "\\./")
        test eax,eax
        jnz error_1
        mov path,_getdcwd(0, addr pathbuf, _MAX_PATH)
        test eax,eax
        jz  error_1
        cmp strlen(eax),3
        jne error_1
        cmp GetDriveType(path),1
        jna error_1
        xor eax,eax
        mov ff.dwFileAttributes,A_D
        mov ff.nFileSizeHigh,eax
        mov ff.nFileSizeLow,eax
        mov ff.cFileName,al
        _loctotime_t(80, 1, 1, eax, eax, eax)
        mov [edi].S_STAT.st_mtime,eax
        mov [edi].S_STAT.st_atime,eax
        mov [edi].S_STAT.st_ctime,eax
    .else
        FindClose(eax)
        _lk_getltime(addr ff.ftLastWriteTime)
        test eax,eax
        jz error_2
        mov [edi].S_STAT.st_mtime,eax
        .if !_lk_getltime( addr ff.ftLastAccessTime )
        mov eax,[edi].S_STAT.st_mtime
        .endif
        mov [edi].S_STAT.st_atime,eax
        .if !_lk_getltime( addr ff.ftCreationTime )
        mov eax,[edi].S_STAT.st_mtime
        .endif
        mov [edi].S_STAT.st_ctime,eax
    .endif

    mov eax,[esi]
    mov edx,ff.dwFileAttributes
    mov ecx,S_IFDIR or S_IEXEC
    mov ebx,S_IREAD
    .if ah == ':'
        add esi,2
        shr eax,16
    .endif
    .if (al && !(dl & A_D)) && (ah || (al != '\' && al != '/'))
        mov ecx,S_IFREG
    .endif
    .if !(dl & A_D)
        mov ebx,S_IREAD or S_IWRITE
    .endif
    or ebx,ecx
    .if __isexec(esi)
        or ebx,S_IEXEC
    .endif

    mov ecx,ebx
    and ecx,01C0h
    mov eax,ecx
    shr ecx,3
    or  ebx,ecx
    shr eax,6
    or  eax,ebx
    mov [edi].S_STAT.st_mode,ax
    mov [edi].S_STAT.st_nlink,1
    mov eax,ff.nFileSizeLow
    mov [edi].S_STAT.st_size,eax
    xor eax,eax
    mov [edi].S_STAT.st_uid,ax
    mov [edi].S_STAT.st_ino,ax
    mov [edi].S_STAT.st_gid,eax
    mov eax,drive
    dec eax
    mov [edi].S_STAT.st_dev,eax
    mov [edi].S_STAT.st_rdev,eax
    xor eax,eax
toend:
    ret
error_1:
    mov errno,ENOENT
    mov oserrno,ERROR_PATH_NOT_FOUND
    mov eax,-1
    jmp toend
error_2:
    osmaperr()
    mov eax,-1
    jmp toend
_stat endp

    end

; _STAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include time.inc
include direct.inc
include errno.inc
include stat.inc
include string.inc
include stdlib.inc
include malloc.inc
include crtl.inc
include winbase.inc

A_D equ 10h

    .code

_lk_getltime proc private ft:PVOID

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

_lk_getltime endp

_stat proc uses rsi rdi rbx fname:LPSTR, buf:PVOID

  local path:LPSTR, drive, ff:WIN32_FIND_DATA, pathbuf[_MAX_PATH]:byte

    mov rsi,fname
    mov rdi,buf

    .repeat

        .break .if strchr(rsi, '?')
        .break .if strchr(rsi, '*')

        mov eax,[rsi]
        .if ah == ':'

            .break .if !( eax & 0x00FF0000 )

            or  al,20h
            sub al,'a' - 1
            movzx eax,al
        .else
            _getdrive()
        .endif
        mov drive,eax

        .ifd FindFirstFileA(rsi, &ff) == -1

            .if !strchr(rsi, '.')
                .if !strchr(rsi, '\')
                    .break .if !strchr(rsi, '/')
                .endif
            .endif

            .break .if !_getcwd(&pathbuf, _MAX_PATH)
            mov path,rax
            .break .ifd strlen(rax) != 3
            .break .if GetDriveType(path) < 2

            xor eax,eax
            mov ff.dwFileAttributes,A_D
            mov ff.nFileSizeHigh,eax
            mov ff.nFileSizeLow,eax
            mov ff.cFileName,0
            _loctotime_t(80, 1, 1, 0, 0, 0)
            mov [rdi].S_STAT.st_mtime,eax
            mov [rdi].S_STAT.st_atime,eax
            mov [rdi].S_STAT.st_ctime,eax
        .else

            FindClose(rax)
            .ifd !_lk_getltime(&ff.ftLastWriteTime)
                .return _dosmaperr(GetLastError())
            .endif
            mov [rdi].S_STAT.st_mtime,eax
            .ifd !_lk_getltime(&ff.ftLastAccessTime)
                mov eax,[rdi].S_STAT.st_mtime
            .endif
            mov [rdi].S_STAT.st_atime,eax
            .ifd !_lk_getltime(&ff.ftCreationTime)
                mov eax,[rdi].S_STAT.st_mtime
            .endif
            mov [rdi].S_STAT.st_ctime,eax
        .endif

        mov eax,[rsi]
        mov edx,ff.dwFileAttributes
        mov ecx,S_IFDIR or S_IEXEC
        mov ebx,S_IREAD

        .if ah == ':'
            add esi,2
            shr eax,16
        .endif
        .if al && !(dl & A_D)
            .if ah || al != '\' && al != '/'
                mov ecx,S_IFREG
            .endif
        .endif
        .if !(dl & A_D)
            mov ebx,S_IREAD or S_IWRITE
        .endif
        or  ebx,ecx
        .if __isexec(rsi)
            or ebx,S_IEXEC
        .endif
        mov ecx,ebx
        and ecx,01C0h
        mov eax,ecx
        shr ecx,3
        or  ebx,ecx
        shr eax,6
        or  eax,ebx
        mov [rdi].S_STAT.st_mode,ax
        mov [rdi].S_STAT.st_nlink,1
        mov eax,ff.nFileSizeLow
        mov [rdi].S_STAT.st_size,eax
        xor eax,eax
        mov [rdi].S_STAT.st_uid,ax
        mov [rdi].S_STAT.st_ino,ax
        mov [rdi].S_STAT.st_gid,eax
        mov eax,drive
        dec eax
        mov [rdi].S_STAT.st_dev,eax
        mov [rdi].S_STAT.st_rdev,eax
        .return 0
    .until 1
    _set_errno(ENOENT)
    _set_doserrno(ERROR_PATH_NOT_FOUND)
    mov eax,-1
    ret

_stat endp

    END

; _FUTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; int _futime(int fh, struct utimbuf *times);
; int _futime32(int fh, struct __utimbuf32 *times);
; int _futime64(int fh, struct __utimbuf64 *times);
;

include io.inc
include time.inc
include errno.inc
include sys/utime.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
ifdef _WIN64
undef _futime64
ALIAS <_futime64>=<_futime>
else
undef _futime32
ALIAS <_futime32>=<_futime>
endif
endif

.code

_futime proc uses rbx fh:int_t, utimp:ptr utimbuf
ifdef __UNIX__
   _set_errno( ENOSYS )
else
   .new tmb:tm
   .new deftimes:utimbuf
   .new SystemTime:SYSTEMTIME
   .new LastWriteTime:FILETIME
   .new LastAccessTime:FILETIME
   .new LocalFileTime:FILETIME

    ldr ebx,fh
    ldr rdx,utimp

    .ifs ( ebx < 0 || ebx < _nfile || !(_osfile(ebx) & FOPEN) )
        .return( _set_errno(EBADF) )
    .endif
    .if ( rdx == NULL )
        time(&deftimes.modtime)
        mov deftimes.actime,deftimes.modtime
        lea edx,deftimes
        mov utimp,rdx
    .endif
    .ifd _localtime_s(&tmb, &[rdx].utimbuf.modtime)
        .return( _set_errno(EINVAL) )
    .endif

    mov eax,tmb.tm_year
    add eax,1900
    mov edx,tmb.tm_mon
    inc edx
    mov SystemTime.wYear,ax
    mov SystemTime.wMonth,dx
    mov SystemTime.wDay,tmb.tm_mday
    mov SystemTime.wHour,tmb.tm_hour
    mov SystemTime.wMinute,tmb.tm_min
    mov SystemTime.wSecond,tmb.tm_sec
    mov SystemTime.wMilliseconds,0

    .ifd SystemTimeToFileTime( &SystemTime, &LocalFileTime )
        LocalFileTimeToFileTime( &LocalFileTime, &LastWriteTime )
    .endif
    .if ( eax == 0 )
        .return( _set_errno(EINVAL) )
    .endif
    mov rdx,utimp
    .ifd _localtime_s(&tmb, &[rdx].utimbuf.actime)
        .return( _set_errno(EINVAL) )
    .endif
    mov eax,tmb.tm_year
    add eax,1900
    mov edx,tmb.tm_mon
    inc edx
    mov SystemTime.wYear,ax
    mov SystemTime.wMonth,dx
    mov SystemTime.wDay,tmb.tm_mday
    mov SystemTime.wHour,tmb.tm_hour
    mov SystemTime.wMinute,tmb.tm_min
    mov SystemTime.wSecond,tmb.tm_sec
    mov SystemTime.wMilliseconds,0
    .ifd SystemTimeToFileTime( &SystemTime, &LocalFileTime )
        LocalFileTimeToFileTime( &LocalFileTime, &LastAccessTime )
    .endif
    .if ( eax == 0 )
        .return( _set_errno(EINVAL) )
    .endif
    mov rcx,_get_osfhandle(ebx)
    .ifd !SetFileTime(rcx, NULL, &LastAccessTime, &LastWriteTime)
        .return( _set_errno(EINVAL) )
    .endif
    xor eax,eax
endif
    ret
    endp

    end

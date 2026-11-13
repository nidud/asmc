; __TIMET_FROM_FT.asm--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

define NSEC_PER_SEC 1000000000

.code

__timet_from_ft proc ft:LPFILETIME
ifdef __UNIX__
    ldr rcx,ft
    .if ( !rcx )
        .return( -1 )
    .endif
    mov rax,[rcx]
 ifdef _WIN64
    mov ecx,NSEC_PER_SEC
    cqo
 else
    mov edx,[ecx+4]
    mov ecx,NSEC_PER_SEC
 endif
    idiv rcx
    .ifs ( rdx < 0 )
        dec rax
    .endif
else
    .new s:SYSTEMTIME
    .new u:SYSTEMTIME
    .ifd FileTimeToSystemTime(ldr(ft), &u)
        .ifd SystemTimeToTzSpecificLocalTime(NULL, &u, &s)
            .return _loctotime_t( s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond, -1 )
        .endif
    .endif
    dec rax
endif
    ret
    endp

    end

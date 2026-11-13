; SETFILETIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include sys/stat.inc

define NSEC_PER_SEC 1000000000

.code

 SetFileTime proc WINAPI hFile:HANDLE, cTime:LPFILETIME, aTime:LPFILETIME, mTime:LPFILETIME
   .new ts[2]:timespec = { { 0, UTIME_OMIT }, { 0, UTIME_OMIT } }
    mov rcx,aTime
    .if ( rcx )
        mov rax,[rcx]
ifdef _WIN64
        mov ecx,NSEC_PER_SEC
        xor edx,edx
else
        mov edx,[ecx+4]
        .if ( eax || edx )
            mov ecx,NSEC_PER_SEC
endif
            div rcx
            mov ts.tv_sec,rax
            mov ts.tv_nsec,rdx
ifndef _WIN64
        .endif
endif
    .endif
    mov rcx,mTime
    .if ( rcx )
        mov rax,[rcx]
ifdef _WIN64
        mov ecx,NSEC_PER_SEC
        xor edx,edx
else
        mov edx,[ecx+4]
        .if ( eax || edx )
            mov ecx,NSEC_PER_SEC
endif
            div rcx
            mov ts[timespec].tv_sec,rax
            mov ts[timespec].tv_nsec,rdx
ifndef _WIN64
        .endif
endif
    .endif
    mov rcx,hFile
    .ifd futimens(ecx, &ts)
        .return( FALSE )
    .endif
    .return( TRUE )
    endp

    end

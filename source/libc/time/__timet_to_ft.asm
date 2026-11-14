; __TIMET_TO_FT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

define NSEC_PER_SEC 1000000000

.code

__timet_to_ft proc Time:time_t, lpFileTime:ptr FILETIME
ifdef __UNIX__
    ldr rax,Time
    ldr rcx,lpFileTime
    .if ( !rcx )
        .return( rcx )
    .endif
  ifdef _WIN64
    imul rax,rax,NSEC_PER_SEC
    mov [rcx],rax
  else
    mov edx,NSEC_PER_SEC
    imul edx
    mov [ecx],eax
    mov [ecx+4],edx
  endif
    .return( rcx )
else
  local SystemTime:SYSTEMTIME
    SystemTimeToFileTime(__timet_to_st(Time, &SystemTime), lpFileTime)
    LocalFileTimeToFileTime(lpFileTime, lpFileTime)
    .return(lpFileTime)
endif
    endp

    END

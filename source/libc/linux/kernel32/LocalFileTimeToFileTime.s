; LOCALFILETIMETOFILETIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include fileapi.inc

define NSEC_PER_SEC 1000000000

.code

 LocalFileTimeToFileTime proc WINAPI uses rbx lpLocalFileTime:LPFILETIME, lpFileTime:LPFILETIME
    ldr rcx,lpLocalFileTime
    ldr rbx,lpFileTime
    .if ( !rcx || !rbx )
        .return( FALSE )
    .endif
  ifdef _WIN64
    mov     rax,[rcx]
    push    rax
    mov     ecx,NSEC_PER_SEC
    cqo
    idiv    rcx
    invoke  __tz_lookup,rax     ; eax = signed UTC offset in seconds
    movsxd  rax,eax
    imul    rax,rax,NSEC_PER_SEC
    pop     rcx
    sub     rcx,rax
    mov     [rbx],rcx
  else
    mov     eax,[ecx]
    mov     edx,[ecx+4]
    push    edx
    push    eax
    mov     ecx,NSEC_PER_SEC
    idiv    ecx                 ; eax = local time_t seconds
    invoke  __tz_lookup,eax     ; eax = signed UTC offset in seconds
    mov     ecx,NSEC_PER_SEC
    imul    ecx                 ; edx:eax = offset in nanoseconds (signed 64-bit)
    pop     ecx                 ; low dword of local FILETIME
    sub     ecx,eax
    mov     [ebx],ecx
    pop     ecx                 ; high dword of local FILETIME
    sbb     ecx,edx
    mov     [ebx+4],ecx
  endif
    .return( TRUE )
    ret
    endp

    end

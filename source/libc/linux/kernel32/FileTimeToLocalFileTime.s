; FILETIMETOLOCALFILETIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include fileapi.inc

define NSEC_PER_SEC 1000000000

.code

 FileTimeToLocalFileTime proc WINAPI uses rbx lpFileTime:LPFILETIME, lpLocalFileTime:LPFILETIME
    ldr rcx,lpFileTime
    ldr rbx,lpLocalFileTime
    .if ( !rcx || !rbx )
        .return( FALSE )
    .endif
  ifdef _WIN64
    mov     rax,[rcx]
    push    rax
    mov     ecx,NSEC_PER_SEC
    cqo
    idiv    rcx
    __tz_lookup(rax)            ; eax = signed UTC offset in seconds
    movsxd  rax,eax
    imul    rax,rax,NSEC_PER_SEC
    pop     rcx
    add     rcx,rax
    mov     [rbx],rcx
  else
    mov     eax,[ecx]
    mov     edx,[ecx+4]
    push    edx
    push    eax
    mov     ecx,NSEC_PER_SEC
    idiv    ecx                 ; eax = UTC time_t seconds
    __tz_lookup(eax)            ; eax = signed UTC offset in seconds
    mov     ecx,NSEC_PER_SEC
    imul    ecx                 ; edx:eax = offset in nanoseconds (signed 64-bit)
    pop     ecx                 ; low dword of original FILETIME
    add     eax,ecx
    pop     ecx                 ; high dword of original FILETIME
    adc     edx,ecx
    mov     [ebx],eax
    mov     [ebx+4],edx
  endif
    .return( TRUE )
    ret
    endp

    end

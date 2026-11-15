; QUERYPERFORMANCEFREQUENCY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include profileapi.inc

define NSEC_PER_SEC 1000000000

.code

 QueryPerformanceFrequency proc WINAPI lpFrequency:PLARGE_INTEGER
    ldr rcx,lpFrequency
    .if ( !rcx )
        .return( FALSE )
    .endif
    mov eax,NSEC_PER_SEC
    mov [rcx],rax
  ifndef _WIN64
    mov dword ptr [ecx+4],0
  endif
    .return( TRUE )
    endp

    end

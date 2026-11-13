; __TIMESPEC_TO_FT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include tchar.inc

.code

 __timespec_to_ft proc fastcall ts:ptr timespec, ft:ptr FILETIME
    .if ( rdx )
ifdef _WIN64
        imul    rax,[rcx].timespec.tv_sec,1000000000
        add     rax,[rcx].timespec.tv_nsec
        mov     [rdx],rax
else
        push    edx
        push    ecx
        mov     eax,[rcx].timespec.tv_sec
        mov     ecx,1000000000
        imul    ecx
        pop     ecx
        add     eax,[ecx].timespec.tv_nsec
        adc     edx,0
        pop     ecx
        mov     [ecx],eax
        mov     [ecx+4],edx
endif
    .endif
    ret
    endp

    end

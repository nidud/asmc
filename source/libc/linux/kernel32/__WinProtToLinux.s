; __WINPROTTOLINUX.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/mman.inc
include memoryapi.inc

.code

 __WinProtToLinux proc fastcall flProtect:DWORD
    .if ( ecx & PAGE_GUARD or PAGE_NOACCESS )
        .return( PROT_NONE )
    .endif
    movzx ecx,cl
    mov eax,PROT_READ or PROT_WRITE
    .switch ecx
    .case PAGE_READONLY
        mov eax,PROT_READ
       .endc
    .case PAGE_EXECUTE
        mov eax,PROT_EXEC
       .endc
    .case PAGE_EXECUTE_READ
        mov eax,PROT_READ or PROT_EXEC
       .endc
    .case PAGE_EXECUTE_READWRITE
    .case PAGE_EXECUTE_WRITECOPY
        mov eax,PROT_READ or PROT_WRITE or PROT_EXEC
    .endsw
    ret
    endp

    end

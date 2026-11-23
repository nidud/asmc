; GETFILEATTRIBUTESA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fileapi.inc
include sys/stat.inc
include sys/syscall.inc
include errno.inc

.code

 GetFileAttributesA proc WINAPI lpFileName:LPCSTR
    .new s:_stat32
    .ifsd ( sys_newstat( ldr(lpFileName), &s ) < 0 )
        dec _sys_maperr(eax)
    .else
      ifdef _WIN64
        mov eax,s.st_mode
      else
        movzx eax,s.st_mode
      endif
    .endif
    ret
    endp

    end

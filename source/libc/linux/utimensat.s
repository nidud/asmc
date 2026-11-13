; UTIMENSAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc
include fcntl.inc
include sys/stat.inc
include sys/syscall.inc

.code
 utimensat proc fd:int_t, path:string_t, ts:ptr timespec, flags:int_t
if sizeof(timespec) eq 8
   .new ts64[2]:timespec64 = {0}
    mov edx,ts
    mov eax,[edx].timespec.tv_sec
    mov dword ptr ts64.tv_sec,eax
    mov eax,[edx].timespec.tv_nsec
    mov dword ptr ts64.tv_nsec,eax
    mov eax,[edx+timespec].timespec.tv_sec
    mov dword ptr ts64[timespec].tv_sec,eax
    mov eax,[edx+timespec].timespec.tv_nsec
    mov dword ptr ts64[timespec].tv_nsec,eax
    lea eax,ts64
    .ifsd ( sys_utimensat( fd, path, eax, flags ) < 0 )
else
    .ifsd ( sys_utimensat( ldr(fd), ldr(path), ldr(ts), ldr(flags) ) < 0 )
endif
        neg eax
        _set_errno( eax )
    .endif
    ret
    endp

    end

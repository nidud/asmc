; SYS_MMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include linux/kernel.inc

.code

sys_mmap proc adr:ptr, len:size_t, prot:size_t, flags:size_t, fd:size_t, off:size_t

    add rsi,_GRANULARITY-1
    and sil,-(_GRANULARITY)
    mov r10,rcx
    mov rcx,rsi
    mov eax,SYS_MMAP
    syscall
    ret

sys_mmap endp

    end

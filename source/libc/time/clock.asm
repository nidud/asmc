; CLOCK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include sys/timeb.inc
include winbase.inc

    .data
     __itimeb _timeb { 0, 0, 0, 0 }

    .code

clock proc

  local now:_timeb

    ; Calculate the difference between the initial time and now.

    _ftime(&now)
    mov rax,now.time
    sub rax,__itimeb.time
    imul rax,rax,CLOCKS_PER_SEC
    movzx ecx,now.millitm
    movzx edx,__itimeb.millitm
    sub ecx,edx
    add rax,rcx
    ret

clock endp

__inittime proc

    _ftime(&__itimeb)
    ret

__inittime endp

.pragma init(__inittime, 20)

    end

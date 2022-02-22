; CLOCK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc
include time.inc
include sys/timeb.inc

    .data
     __itimeb _timeb { 0, 0, 0, 0 }

    .code

clock proc

  local now:_timeb
  local elapsed:clock_t

    ; Calculate the difference between the initial time and now.

    _ftime(&now)
    mov eax,now.time
    sub eax,__itimeb.time
    imul eax,eax,CLOCKS_PER_SEC
    movzx ecx,now.millitm
    movzx edx,__itimeb.millitm
    sub ecx,edx
    add eax,ecx
    ret

clock endp

__inittime proc

    _ftime(&__itimeb)
    ret

__inittime endp

.pragma init(__inittime, 8)

    END

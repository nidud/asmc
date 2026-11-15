; __TIMET_FROM_FT.asm--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

define NSEC_PER_SEC     1000000000
define WIN_TICK_PER_SEC 10000000
define WIN_EPOCH_OFFSET 116444736000000000

.code

__timet_from_ft proc ft:LPFILETIME
    ldr rcx,ft
    .if ( !rcx )
        .return( -1 )
    .endif
ifdef __UNIX__
    mov rax,[rcx]
  ifdef _WIN64
    mov ecx,NSEC_PER_SEC
    cqo
  else
    mov edx,[ecx+4]
    mov ecx,NSEC_PER_SEC
  endif
    idiv rcx
    .ifs ( rdx < 0 )
        dec rax
    .endif
else
  ifdef _WIN64
    mov rax,[rcx]
    mov rdx,WIN_EPOCH_OFFSET
    sub rax,rdx
    mov ecx,WIN_TICK_PER_SEC
    cqo
    idiv rcx
  else
    mov eax,[ecx]
    mov edx,[ecx+4]
    sub eax,low32(WIN_EPOCH_OFFSET)
    sbb edx,high32(WIN_EPOCH_OFFSET)
    mov ecx,WIN_TICK_PER_SEC
    idiv ecx
  endif
endif
    ret
    endp

    end

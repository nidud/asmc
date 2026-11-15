; __TIMET_TO_FT.ASM--
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

__timet_to_ft proc t:time_t, ft:ptr FILETIME
    ldr rax,t
    ldr rcx,ft
    .if ( !rcx )
        .return( rcx )
    .endif
ifdef __UNIX__
  ifdef _WIN64
    imul rax,rax,NSEC_PER_SEC
    mov  [rcx],rax
  else
    mov  edx,NSEC_PER_SEC
    imul edx
    mov  [ecx],eax
    mov  [ecx+4],edx
  endif
else
  ifdef _WIN64
    imul rax,rax,WIN_TICK_PER_SEC
    mov  rdx,WIN_EPOCH_OFFSET
    add  rax,rdx
    mov  [rcx],rax
  else
    mov  edx,WIN_TICK_PER_SEC
    imul edx
    add  eax,low32(WIN_EPOCH_OFFSET)
    adc  edx,high32(WIN_EPOCH_OFFSET)
    mov  [ecx],eax
    mov  [ecx+4],edx
  endif
endif
    mov rax,rcx
    ret
    endp

    END

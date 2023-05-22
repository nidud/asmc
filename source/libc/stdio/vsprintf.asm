; VSPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc

    .code

vsprintf proc string:string_t, format:string_t, argptr:ptr

  local o:_iobuf

    ldr rcx,string
    ldr rdx,format

    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rcx
    mov o._base,rcx
    _output(addr o, rdx, argptr)
    mov rcx,o._ptr
    mov byte ptr [rcx],0
    ret

vsprintf endp

    end

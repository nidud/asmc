; _TVSNPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include limits.inc
include tchar.inc

    .code

_vsntprintf proc string:tstring_t, count:size_t, format:tstring_t, args:ptr

  local o:_iobuf

    ldr rcx,string
    ldr rdx,count

    mov o._flag,_IOWRT or _IOSTRG or _IOSNPRINTF
ifdef _UNICODE
    add edx,edx
endif
    mov o._cnt,edx
    mov o._ptr,rcx
    mov o._base,rcx
    _toutput(&o, format, args)

    mov rcx,o._ptr
    .if ( o._cnt <= 0 )
        .if ( rcx > o._base )
            mov tchar_t ptr [rcx-tchar_t],0
        .endif
    .else
        mov tchar_t ptr [rcx],0
    .endif
    ret

_vsntprintf endp

    end

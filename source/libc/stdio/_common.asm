; _COMMON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include locale.inc
include stdarg.inc
include limits.inc
include tchar.inc

.code

__stdio_common_vfprintf proc uses rbx Options:uint64_t, Stream:LPFILE, Format:string_t, Locale:_locale_t, ArgList:va_list
    mov rbx,_stbuf( ldr(Stream) )
    _toutput(Stream, Format, ArgList)
    mov rcx,rbx
    mov rbx,rax
    _ftbuf(ecx, Stream)
    mov rax,rbx
    ret
    endp


__stdio_common_vsprintf proc Options:uint64_t, Buffer:string_t, BufferCount:size_t, Format:string_t, Locale:_locale_t, ArgList:va_list
  local o:_iobuf
    ldr rcx,Buffer
    ldr rax,Format
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,INT_MAX
    mov o._ptr,rcx
    mov o._base,rcx
    _toutput(&o, rax, ArgList)
    mov rcx,o._ptr
    mov tchar_t PTR [rcx],0
    ret
    endp
    end

    end

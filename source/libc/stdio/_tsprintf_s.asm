; _TSPRINTF_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc
include errno.inc
include tchar.inc

    .code

_stprintf_s proc string:tstring_t, sizeInWords:size_t, format:tstring_t, argptr:vararg

  local o:_iobuf

    ldr rcx,string
    ldr rax,format
    ldr rdx,sizeInWords

    .if ( rax == NULL || ( rcx == NULL && rdx > 0 ) )
        .return( _set_errno( EINVAL ) )
    .endif
    mov o._flag,_IOWRT or _IOSTRG
    mov o._ptr,rcx
    mov o._base,rcx
    .if ( rdx > INT_MAX )
        mov edx,INT_MAX
    .endif
ifdef _UNICODE
    add edx,edx
endif
    mov o._cnt,edx
    _toutput(&o, format, &argptr)
    .if ( string != NULL )
        mov rcx,o._ptr
        mov tchar_t ptr [rcx],0
    .endif
    ret

_stprintf_s endp

    end

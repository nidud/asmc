; SWPRINTF_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc
include errno.inc

    .code

swprintf_s proc string:wstring_t, sizeInWords:size_t, format:wstring_t, argptr:vararg

  local o:_iobuf

    ldr rcx,string
    ldr rdx,sizeInWords

    .if ( !( rcx != NULL || rdx == 0 ) || format == NULL )

        _set_errno(EINVAL)
        .return -1
    .endif

    mov o._flag,_IOWRT or _IOSTRG
    mov o._ptr,rcx
    mov o._base,rcx
    mov o._cnt,INT_MAX

    .if ( rdx <= INT_MAX/2 )

        lea eax,[rdx*2]
        mov o._cnt,eax
    .endif

    _woutput(&o, format, &argptr)

    .return .if ( string == NULL )

    mov rcx,o._ptr
    mov word ptr [rcx],0
    ret

swprintf_s endp

    end

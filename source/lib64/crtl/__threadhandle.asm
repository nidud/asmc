; __THREADHANDLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

    .code

__threadhandle proc frame

    GetCurrentThread()
    ret

__threadhandle endp

    end

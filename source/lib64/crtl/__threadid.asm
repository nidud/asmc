; __THREADID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

    .code

__threadid proc frame

    GetCurrentThreadId()
    ret

__threadid endp

    end

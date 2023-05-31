; __ARGC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

ifdef   _UNICODE
extern  __wargv:warray_t
else
extern  __argv:array_t
endif
    .data
    __argc int_t 0

    end

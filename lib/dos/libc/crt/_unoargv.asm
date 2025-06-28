; _NOARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

externdef c noargv:int_t

.data
noargv      label int_t
_argvused   int_t 0
end

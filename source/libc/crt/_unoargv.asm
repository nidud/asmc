; _NOARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

public _noargv
.data
_noargv     label int_t
_argvusedA  label int_t
_argvusedW  int_t 0
end

; _EXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include linux/kernel.inc

    .code

_exit proc retval:int_t

    sys_exit(edi)

_exit endp

    end

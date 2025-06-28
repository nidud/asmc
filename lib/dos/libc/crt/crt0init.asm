; CRT0INIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

public __xi_a ; init
public __xi_z
public __xt_a ; terminators
public __xt_z

.CRT$XI0 SEGMENT WORD PUBLIC 'CONST'
__xi_a dq 0
.CRT$XI0 ENDS
.CRT$XIA SEGMENT WORD PUBLIC 'CONST'
       dq 0
.CRT$XIA ENDS
.CRT$XIZ SEGMENT WORD PUBLIC 'CONST'
__xi_z dq 0
.CRT$XIZ ENDS

.CRT$XT0 SEGMENT WORD PUBLIC 'CONST'
__xt_a dq 0
.CRT$XT0 ENDS
.CRT$XTA SEGMENT WORD PUBLIC 'CONST'
       dq 0
.CRT$XTA ENDS
.CRT$XTZ SEGMENT WORD PUBLIC 'CONST'
__xt_z dq 0
.CRT$XTZ ENDS

    end

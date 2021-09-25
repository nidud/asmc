; NAMESPACE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include iostream
include tchar.inc

.data

.namespace box1
    box_side int_t 4
.endn

.namespace box2
    box_side int_t 12
.endn

.code

_tmain proc

   .new box_side:int_t = 42

    cout << box1::box_side << endl  ; Outputs 4.
    cout << box2::box_side << endl  ; Outputs 12.
    cout << box_side << endl        ; Outputs 42.
    ret

_tmain endp

    end _tstart

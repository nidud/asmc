; FLOAT.ASM--
;
; v2.35: default type for vararg is double precision
; - memory (float) values converted
; - imm value to double precision
;

include stdio.inc
include tchar.inc

.code

_tmain proc

    .new d1:real8 = 1.0
    .new f1:real4 = 2.0

    _tprintf( "duoble = %f, float = %f, imm = %f\n", d1, f1, 3.0 )
    .return( 0 )

_tmain endp

    end _tstart

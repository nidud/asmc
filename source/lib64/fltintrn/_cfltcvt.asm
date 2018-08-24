include fltintrn.inc
include quadmath.inc

.code

_cldcvt proc fp:LPLONGDOUBLE, buffer:LPSTR, ch_type:SINT, precision:SINT, capexp:SINT

    _dcvt(fp, buffer, ch_type, precision, capexp)
    ret

_cldcvt endp

_cfltcvt proc fp:LPDOUBLE, buffer:LPSTR, ch_type:SINT, precision:SINT, capexp:SINT

    _dcvt(fp, buffer, ch_type, precision, capexp)
    ret

_cfltcvt endp

    END

; LINNUM.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; internal line number information used if -Zd or -Zi is set
;
ifndef __LINNUM_INC
define __LINNUM_INC

.template line_num_info
    next            ptr line_num_info ?
    number          dd ? ; source line number, v2.06: changed to 32-bit
    union
     offs           dd ?
     line_number    dd ? ; is set if sym is != NULL ( COFF only ) :20, file:12;
    ends
    union
     srcfile        dd ?
     sym            ptr asym ? ; used if number is 0 ( COFF only )
    ends
   .ends

LinnumInit          proto __ccall
LinnumFini          proto __ccall
QueueDeleteLinnum   proto __ccall :qdesc_t

endif


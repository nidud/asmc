.pragma list(push, 0)
ifndef __LINNUM_INC
__LINNUM_INC equ <>

;; internal line number information used if -Zd or -Zi is set

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

LinnumInit      proto
LinnumFini      proto
QueueDeleteLinnum proto :qdesc_t

endif
.pragma list(pop)

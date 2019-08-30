.pragma list(push, 0)
ifndef __LINNUM_INC
__LINNUM_INC equ <>

;; internal line number information used if -Zd or -Zi is set

line_num_info   struct
next            ptr_t ?     ; line_num_info *
number          uint_t ?    ; source line number, v2.06: changed to 32-bit
union
 _offset        uint_t ?
                            ; is set if sym is != NULL ( COFF only )
 line_number    uint_t ?    ; :20, file:12;
ends
union
    srcfile     uint_t ?
    sym         asym_t ?    ; used if number is 0 ( COFF only )
ends
line_num_info   ends

LinnumInit      proto
LinnumFini      proto
QueueDeleteLinnum proto :qdesc_t

endif
.pragma list(pop)

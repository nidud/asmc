.pragma list(push, 0)
ifndef __BIN_INC
__BIN_INC equ <>

;; header for BIN output format

bin_init proto :ptr module_info
pe_create_PE_header proto

endif
.pragma list(pop)

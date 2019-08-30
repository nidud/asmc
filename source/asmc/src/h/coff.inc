.pragma list(push, 0)
ifndef __COFF_INC
__COFF_INC equ <>

;; prototypes of functions defined in coff.asm

qditem      struct
next        ptr_t ?
size        uint_t ?
qditem      ends

coff_init   proto :ptr module_info

endif
.pragma list(pop)

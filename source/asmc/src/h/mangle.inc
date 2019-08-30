.pragma list(push, 0)
ifndef __MANGLE_INC
__MANGLE_INC equ <>

;; Declaration for mangler routines (=name decoration)

Mangle      proto :asym_t, :string_t
SetMangler  proto :asym_t, :int_t, :string_t

endif
.pragma list(pop)

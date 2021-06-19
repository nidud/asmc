.pragma list(push, 0)
ifndef __ATOFLOAT_INC
__ATOFLOAT_INC equ <>

atofloat    proto :ptr, :string_t, :uint_t, :int_t, :uchar_t
quad_resize proto :expr_t, :int_t

endif
.pragma list(pop)

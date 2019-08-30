.pragma list(push, 0)
ifndef __CONTEXT_INC
__CONTEXT_INC equ <>

;; PUSHCONTEXT/POPCONTEXT interface

ContextInit proto :int_t
ContextFini proto

endif
.pragma list(pop)

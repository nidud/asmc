.pragma list(push, 0)
ifndef __EQUATE_INC
__EQUATE_INC equ <>

;; EQU and '=' directives interface

CreateConstant proto :ptr asm_tok
CreateVariable proto :string_t, :int_t

endif
.pragma list(pop)

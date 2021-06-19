.pragma list(push, 0)
ifndef __PREPROC_INC
__PREPROC_INC equ <>

;; v2.11: preprocessor functions moved from input.c to preproc.asm

PreprocessLine proto :token_t
WriteCodeLabel proto :string_t, :token_t

endif
.pragma list(pop)

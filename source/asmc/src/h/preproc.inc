.pragma list(push, 0)
ifndef __PREPROC_INC
__PREPROC_INC equ <>

;; v2.11: preprocessor functions moved from input.c to preproc.asm

PreprocessLine proto :string_t, :tok_t
WriteCodeLabel proto :string_t, :tok_t

endif
.pragma list(pop)

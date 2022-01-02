; PREPROC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; v2.11: preprocessor functions moved from input.asm to preproc.asm
;
ifndef __PREPROC_INC
define __PREPROC_INC

PreprocessLine proto __ccall :ptr asm_tok
WriteCodeLabel proto __ccall :string_t, :ptr asm_tok

endif

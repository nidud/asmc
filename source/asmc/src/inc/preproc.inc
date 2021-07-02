; PREPROC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; v2.11: preprocessor functions moved from input.asm to preproc.asm
;
ifndef __PREPROC_INC
define __PREPROC_INC

PreprocessLine proto :ptr asm_tok
WriteCodeLabel proto :string_t, :ptr asm_tok

endif

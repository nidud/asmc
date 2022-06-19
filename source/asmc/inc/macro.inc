; MACRO.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; prototypes for macro stuff
;
ifndef __MACRO_INC
define __MACRO_INC

PLACEHOLDER_CHAR	equ 10	 ; "escape" char for macro placeholders

MF_LABEL		equ 0x01 ; a label exists at pos 0
MF_NOSAVE		equ 0x02 ; no need to save/restore input status
MF_IGNARGS		equ 0x04 ; ignore additional arguments (for FOR directive)

; functions in expans.asm

GetLiteralValue		proto __ccall :string_t, :string_t
RunMacro		proto __ccall :ptr dsym, :int_t, :ptr asm_tok, :string_t, :int_t, :ptr int_t
ExpandText		proto __ccall :string_t, :ptr asm_tok, :uint_t
ExpandLineItems		proto __ccall :string_t, :int_t, :ptr asm_tok, :int_t, :int_t
ExpandLine		proto __ccall :string_t, :ptr asm_tok
ExpandLiterals		proto __ccall :int_t, :ptr asm_tok

; functions in macro.asm

CreateMacro		proto fastcall :string_t ; create a macro symbol
ReleaseMacroData	proto fastcall :dsym_t
fill_placeholders	proto __ccall :string_t, :string_t, :uint_t, :uint_t, :array_t
SkipCurrentQueue	proto __ccall :ptr asm_tok
StoreMacro		proto __ccall :ptr dsym, :int_t, :ptr asm_tok, :int_t ;; store macro content
MacroInit		proto __ccall :int_t

; functions in string.asm

SetTextMacro		proto __ccall :token_t, :asym_t, :string_t, :string_t ;; EQU for texts
AddPredefinedText	proto __ccall :string_t, :string_t
TextItemError		proto __ccall :token_t

StringInit		proto __ccall
MacroLineQueue		proto __ccall

endif

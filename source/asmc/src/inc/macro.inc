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

GetLiteralValue		proto :string_t, :string_t
RunMacro		proto :ptr dsym, :int_t, :ptr asm_tok, :string_t, :int_t, :ptr int_t
ExpandText		proto :string_t, :ptr asm_tok, :uint_t
ExpandLineItems		proto :string_t, :int_t, :ptr asm_tok, :int_t, :int_t
ExpandLine		proto :string_t, :ptr asm_tok
ExpandLiterals		proto :int_t, :ptr asm_tok
LabelMacro		proto :uint_t

; functions in macro.asm

CreateMacro		proto :string_t ; create a macro symbol
ReleaseMacroData	proto :ptr dsym
fill_placeholders	proto :string_t, :string_t, :uint_t, :uint_t, :array_t
SkipCurrentQueue	proto :ptr asm_tok
StoreMacro		proto :ptr dsym, :int_t, :ptr asm_tok, :int_t ;; store macro content
MacroInit		proto :int_t

; functions in string.asm

SetTextMacro		proto :token_t, :asym_t, :string_t, :string_t ;; EQU for texts
AddPredefinedText	proto :string_t, :string_t
TextItemError		proto :token_t

StringInit		proto
MacroLineQueue		proto

endif

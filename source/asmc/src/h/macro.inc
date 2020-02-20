.pragma list(push, 0)
ifndef __MACRO_INC
__MACRO_INC equ <>

;; prototypes for macro stuff

PLACEHOLDER_CHAR	equ 10	 ;; "escape" char for macro placeholders

MF_LABEL		equ 0x01 ;; a label exists at pos 0
MF_NOSAVE		equ 0x02 ;; no need to save/restore input status
MF_IGNARGS		equ 0x04 ;; ignore additional arguments (for FOR directive)

;; functions in expans.asm

GetLiteralValue		proto :string_t, :string_t
RunMacro		proto :dsym_t, :int_t, :tok_t, :string_t, :int_t, :ptr int_t
ExpandText		proto :string_t, :tok_t, :uint_t
ExpandLineItems		proto :string_t, :int_t, :tok_t, :int_t, :int_t
ExpandLine		proto :string_t, :tok_t
ExpandLiterals		proto :int_t, :tok_t
LabelMacro		proto :uint_t

;; functions in macro.asm

CreateMacro		proto :string_t ;; create a macro symbol
ReleaseMacroData	proto :dsym_t
fill_placeholders	proto :string_t, :string_t, :uint_t, :uint_t, :array_t
SkipCurrentQueue	proto :tok_t
StoreMacro		proto :dsym_t, :int_t, :tok_t, :int_t ;; store macro content
MacroInit		proto :int_t

;; functions in string.asm

SetTextMacro		proto :tok_t, :asym_t, :string_t, :string_t ;; EQU for texts
AddPredefinedText	proto :string_t, :string_t
TextItemError		proto :tok_t

StringInit		proto
MacroLineQueue		proto

endif
.pragma list(pop)

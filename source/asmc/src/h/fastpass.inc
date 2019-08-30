.pragma list(push, 0)
ifndef __FASTPASS_INC
__FASTPASS_INC equ <>

equ_t		typedef ptr equ_item
line_t		typedef ptr line_item

equ_item	struct
next		equ_t ?
sym		asym_t ?
lvalue		int_t ?
hvalue		int_t ?
mem_type	uchar_t ?
isdefined	uchar_t ?
equ_item	ends

line_item	struct
next		line_t ?
prev		line_t ?
lineno		uint_t ? ; 20:12 = srcfile
srcfile		uint_t ?
macro_level	uint_t ?
list_pos	uint_t ? ; position .LST file
line		char_t 1 dup(?)
line_item	ends

externdef LineStoreCurr:line_t
externdef NoLineStore:int_t

;; mod_state: used to store the module state within SaveState()

mod_state	struct
init		int_t ? ; is this struct initialized?
head		equ_t ? ; the list of modified assembly time variables
tail		equ_t ?
modinfo		uchar_t sizeof(module_info) - sizeof(module_vars) dup(?)
mod_state	ends

;; source lines start to be "stored" when one of the following is detected:
;; - an instruction
;; - a data item (but not a struct field)
;; - directives which "generate source": PROC, INVOKE, .IF, .WHILE, .REPEAT
;; - directives ALIGN and ORG (which emit bytes and/or change $)
;; - directive END (to ensure that there is at least 1 line)
;; - directive ASSUME if operand is a forward reference

externdef StoreState:int_t ;; is 1 if states are to be stored in pass one

;; UseSavedState: is TRUE if preprocessed lines are to be read in pass 2,3,...
;; Currently, this flag is set DURING pass one! That's bad,
;; because it means that the flag itself doesn't tell whether
;; (preprocessed) lines are read.
;; the fix proposal is: set the flag - conditionally - AFTER pass one.
;; Also, rename the flag (perhaps UseSavedLines )!

externdef UseSavedState:int_t

FastpassInit		proto
SegmentSaveState	proto
AssumeSaveState		proto
ContextSaveState	proto
StoreLine		proto :string_t, :int_t, :uint_t
SkipSavedState		proto
RestoreState		proto
SaveVariableState	proto :asym_t
FreeLineStore		proto

FStoreLine macro flags
    .if ( Parse_Pass == PASS_1 )
	StoreLine( CurrSource, flags, 0 )
    .endif
    exitm<>
    endm

endif
.pragma list(pop)

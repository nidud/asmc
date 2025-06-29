; FASTPASS.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
.pragma list(push, 0)
ifndef __FASTPASS_INC
define __FASTPASS_INC

include input.inc

.template equ_item
    next            ptr equ_item ?
    sym             asym_t ?
    lvalue          int_t ?
    hvalue          int_t ?
    mem_type        uchar_t ?
    isdefined       uchar_t ?
   .ends

.template line_item
    next            ptr line_item ?
    prev            ptr line_item ?
    lineno          uint_t ? ; 20:12 = srcfile
    srcfile         uint_t ?
    macro_level     uint_t ?
    list_pos        uint_t ? ; position .LST file
    line            char_t 1 dup(?)
   .ends

externdef LineStoreCurr:ptr line_item
externdef NoLineStore:int_t

; mod_state: used to store the module state within SaveState()

.template mod_state
    init        int_t ?         ; is this struct initialized?
    head        ptr equ_item ?  ; the list of modified assembly time variables
    tail        ptr equ_item ?
    state       InputState <>
    modinfo     uchar_t module_info.tokenarray dup(?)
   .ends

; source lines start to be "stored" when one of the following is detected:
; - an instruction
; - a data item (but not a struct field)
; - directives which "generate source": PROC, INVOKE, .IF, .WHILE, .REPEAT
; - directives ALIGN and ORG (which emit bytes and/or change $)
; - directive END (to ensure that there is at least 1 line)
; - directive ASSUME if operand is a forward reference

externdef StoreState:int_t ;; is 1 if states are to be stored in pass one

; UseSavedState: is TRUE if preprocessed lines are to be read in pass 2,3,...
; Currently, this flag is set DURING pass one! That's bad,
; because it means that the flag itself doesn't tell whether
; (preprocessed) lines are read.
; the fix proposal is: set the flag - conditionally - AFTER pass one.
; Also, rename the flag (perhaps UseSavedLines )!

externdef UseSavedState:int_t

FastpassInit            proto
SegmentSaveState        proto
AssumeSaveState         proto
ContextSaveState        proto
StoreLine               proto __ccall :string_t
DefSavedState           proto
SkipSavedState          proto
RestoreState            proto
SaveVariableState       proto fastcall :asym_t
FreeLineStore           proto

FStoreLine proto fastcall flags:abs {
    .if ( Parse_Pass == PASS_1 )
        StoreLine( CurrSource )
    .endif
    }

endif
.pragma list(pop)

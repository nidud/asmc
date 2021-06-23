; FASTPASS.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __FASTPASS_INC
define __FASTPASS_INC

.template equ_item
    next            ptr equ_item ?
    sym             ptr asym ?
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

    .inline get_pos fastcall {
        mov eax,[this].line_item.list_pos
        }
    .inline get_line fastcall {
        lea eax,[this].line_item.line
        }
   .ends

externdef LineStoreCurr:ptr line_item
externdef NoLineStore:int_t

; mod_state: used to store the module state within SaveState()

.template mod_state
    init        int_t ?         ; is this struct initialized?
    head        ptr equ_item ?  ; the list of modified assembly time variables
    tail        ptr equ_item ?
    modinfo     uchar_t sizeof(module_info) - sizeof(module_vars) dup(?)
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
StoreLine               proto :string_t, :int_t, :uint_t
SkipSavedState          proto
RestoreState            proto
SaveVariableState       proto :ptr asym
FreeLineStore           proto

FStoreLine proto fastcall flags:abs {
    .if ( Parse_Pass == PASS_1 )
        StoreLine( CurrSource, flags, 0 )
    .endif
    }

endif

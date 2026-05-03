; INPUT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
.pragma list(push, 0)
ifndef __INPUT_INC
define __INPUT_INC

; prototypes for input queueing/processing procedures

macro_instance  struct
currline        srcline_t ?
startline       srcline_t ?
localstart      uint_t ?
parm_array      array_t ?
_macro          asym_t ?
parmcnt         uint_t ?
macro_instance  ends

; for line numbers, the source files have to be stored
; in a list in the very same order as they appear in
; the input stream.

fileseq_t       typedef ptr file_seq
file_seq        struct
next            fileseq_t ?
file            ushort_t ?  ; index of file in FNames
file_seq        ends

.template InputState
    scr_pos     uint_t ?    ; The size changes..
    arr_pos     uint_t ?
    str_pos     uint_t ?
    end_off     uint_t ?
   .ends

.template input_status : public InputState
    tok_cnt     uint_t ?
    flags       char_t ?    ; v2.08: added
    currcomment string_t ?
   .ends

GetInputState       proto __ccall :ptr InputState
SetInputState       proto __ccall :ptr InputState

GetLineNumber       proto __ccall
GetFNamePart        proto fastcall :string_t
GetExtPart          proto fastcall :string_t
SearchFile          proto __ccall :string_t, :int_t
GetTextLine         proto __ccall :string_t
PushMacro           proto fastcall :ptr macro_instance
SetLineNumber       proto fastcall :uint_t
AddStringToIncludePath  proto __ccall :string_t
InputInit           proto __ccall
InputPassInit       proto __ccall
InputFini           proto __ccall
InputExtend         proto __ccall :ptr line_status
PushInputStatus     proto __ccall :ptr input_status
PopInputStatus      proto __ccall :ptr input_status
ClearSrcStack       proto __ccall
get_curr_srcfile    proto __ccall
set_curr_srcfile    proto fastcall :uint_t, :uint_t
GetFName        proto fastcall :uint_t

GetAlignedPointer proto watcall p:ptr, size:int_t {
    add edx,size_t
    and edx,not ( size_t - 1 )
    add rax,rdx
    }

endif
.pragma list(pop)

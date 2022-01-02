; INPUT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __INPUT_INC
define __INPUT_INC

; prototypes for input queueing/processing procedures

macro_instance	struct
currline	srcline_t ?
startline	srcline_t ?
localstart	uint_t ?
parm_array	array_t ?
_macro		asym_t ?
parmcnt		uint_t ?
macro_instance	ends

; for line numbers, the source files have to be stored
; in a list in the very same order as they appear in
; the input stream.

fileseq_t	typedef ptr file_seq
file_seq	struct
next		fileseq_t ?
file		ushort_t ? ; index of file in FNames
file_seq	ends

input_status	struct
token_stringbuf string_t ?
currsource	string_t ?
CurrComment	string_t ?
token_count	int_t ?
line_flags	char_t ? ; v2.08: added
input_status	ends
input_t		typedef ptr input_status

GetLineNumber		proto __ccall
GetFNamePart		proto __ccall :string_t
GetExtPart		proto __ccall :string_t
SearchFile		proto __ccall :string_t, :int_t
GetTextLine		proto __ccall :string_t
PushMacro		proto __ccall :ptr macro_instance
SetLineNumber		proto __ccall :uint_t
AddStringToIncludePath	proto __ccall :string_t
InputInit		proto __ccall
InputPassInit		proto __ccall
InputFini		proto __ccall
InputExtend		proto __ccall :ptr line_status
PushInputStatus		proto __ccall :input_t
PopInputStatus		proto __ccall :input_t
ClearSrcStack		proto __ccall
get_curr_srcfile	proto __ccall
set_curr_srcfile	proto __ccall :uint_t, :uint_t
GetFName		proto __ccall :uint_t

GetAlignedPointer proto watcall p:ptr, size:int_t {
    add edx,size_t
    and edx,not ( size_t - 1 )
    add rax,rdx
    }

SkipSpace macro reg, base
    movzx reg,byte ptr [base]
    .while byte ptr _ltype[reg+1] & _SPACE
	add base,1
	ifidni <reg>,<eax>
	    mov al,[base]
	else
	  ifidni <reg>,<ecx>
	    mov cl,[base]
	  else
	    movzx reg,byte ptr [base]
	  endif
	endif
    .endw
    retm<reg>
    endm

SkipSpaceR macro reg, base
    movzx reg,byte ptr [base]
    .while byte ptr _ltype[reg+1] & _SPACE
	sub base,1
      ifidni <reg>,<eax>
	mov al,[base]
      else
       ifidni <reg>,<ecx>
	mov cl,[base]
       else
	movzx reg,byte ptr [base]
       endif
      endif
    .endw
    retm<reg>
    endm

endif

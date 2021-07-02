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

GetLineNumber		proto
GetFNamePart		proto :string_t
GetExtPart		proto :string_t
SearchFile		proto :string_t, :int_t
GetTextLine		proto :string_t
PushMacro		proto :ptr macro_instance
SetLineNumber		proto :uint_t
AddStringToIncludePath	proto :string_t
InputInit		proto
InputPassInit		proto
InputFini		proto
InputExtend		proto :ptr line_status
PushInputStatus		proto :input_t
PopInputStatus		proto :input_t
ClearSrcStack		proto
get_curr_srcfile	proto
set_curr_srcfile	proto :uint_t, :uint_t
GetFName		proto :uint_t

GetAlignedPointer macro x, size
  ifdif <size>,<eax>
    mov eax,size
  endif
    add eax,size_t
    and eax,not ( size_t - 1 )
    add eax,x
    retm<eax>
    endm

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

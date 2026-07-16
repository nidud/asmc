; RESWORDS.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; interface to instruction hash table.
;
.pragma list(push, 0)
ifndef __RESWORDS_INC
define __RESWORDS_INC

RWF_DISABLED	equ 0x01 ; keyword disabled
RWF_IA32	equ 0x02 ; keyword specific to IA32 mode
RWF_X64		equ 0x04 ; keyword specific to IA32+ mode
RWF_VEX		equ 0x08 ; keyword triggers VEX encoding
RWF_EVEX	equ 0x10 ; keyword triggers EVEX encoding
RWF_EVEXW	equ 0x80 ; EVEX encoding: W=1

; structure of items in the "reserved names" table ResWordTable[]

ReservedWord	struct
next		dw ?		; index next entry (used for hash table)
len		db ?		; length of reserved word, i.e. 'AX' = 2
flags		db ?		; see enum reservedword_flags
hash		dd ?		; 32-bit hash of reserved word
ReservedWord	ends

; operand classes. this table is defined in reswords.c.
; index into this array is member opclsidx in instr_item.
; v2.06: data removed from struct instr_item.

opnd_class	STRUC
opnd_type	dd 2 dup(?)
;opnd_type_3rd	db ?  ;moved --> opnd_clstab3
opnd_class	ENDS

externdef	ResWordTable:ReservedWord
externdef	ResWordNames:string_t
externdef	resw_table:word
externdef	opnd_clstab:opnd_class
externdef	opnd_clstab3:byte
externdef	vex_flags:byte
externdef	max_resw_len:int_t

FindResWord	proto fastcall :string_t, :uint_t
RemoveResWord	proto fastcall :int_t
GetResWName	proto fastcall :uint_t, :string_t
IsKeywordDisabled proto fastcall :string_t, :int_t
EnableKeyword	proto fastcall :uint_t
DisableKeyword	proto fastcall :uint_t
RenameKeyword	proto __ccall :uint_t, :string_t, :uchar_t
Set64Bit	proto __ccall :int_t
ResWordsInit	proto
ResWordsFini	proto
SetMasmKeywords proto fastcall :int_t

endif
.pragma list(pop)

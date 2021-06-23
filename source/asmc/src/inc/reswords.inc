; RESWORDS.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; interface to instruction hash table.
;
ifndef __RESWORDS_INC
define __RESWORDS_INC

RWF_DISABLED	equ 0x01 ; keyword disabled
RWF_IA32	equ 0x02 ; keyword specific to IA32 mode
RWF_X64		equ 0x04 ; keyword specific to IA32+ mode
RWF_VEX		equ 0x08 ; keyword triggers VEX encoding
RWF_EVEX	equ 0x10 ; keyword triggers EVEX encoding
RWF_QVM		equ 0x20
RWF_OVM		equ 0x40
RWF_HVM		equ 0x60
RWF_T1S		equ 0x80 ; +Tuple1 Fixed (T1F)
RWF_T2		equ 0xA0
RWF_T4		equ 0xC0
RWF_M128	equ 0xE0
RWF_MASK	equ 0xE0 ; TupleType


; structure of items in the "reserved names" table ResWordTable[]

ReservedWord	struct
next		dw ?		; index next entry (used for hash table)
len		db ?		; length of reserved word, i.e. 'AX' = 2
flags		db ?		; see enum reservedword_flags
name		string_t ?	; reserved word (char[])
ReservedWord	ends

FindResWord		proto fastcall :string_t, :uint_t
MasmFindResWord		proto :string_t, :uint_t
GetResWName		proto :uint_t, :string_t
IsKeywordDisabled	proto :string_t, :int_t
DisableKeyword		proto :uint_t
RenameKeyword		proto :uint_t, :string_t, :uchar_t
Set64Bit		proto :int_t
ResWordsInit		proto
ResWordsFini		proto

endif

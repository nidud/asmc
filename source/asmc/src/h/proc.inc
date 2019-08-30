.pragma list(push, 0)
ifndef __PROC_INC
__PROC_INC equ <>

;; interface to PROC.ASM routines

externdef CurrProc:dsym_t		; current procedure
externdef sym_ReservedStack:asym_t	; max stack space required by INVOKE

;; v2.11: proc status flags

PRST_INSIDE_PROLOGUE   equ 0x01
PRST_INSIDE_EPILOGUE   equ 0x02
PRST_FPO	       equ 0x04
PRST_PROLOGUE_NOT_DONE equ 0x80


ParseProc	proto :dsym_t, :int_t, :tok_t, :int_t, :uchar_t
CreateProc	proto :asym_t, :string_t, :int_t
DeleteProc	proto :dsym_t

CopyPrototype	proto :dsym_t, :dsym_t
RetInstr	proto :int_t, :tok_t, :int_t ; handle RET/IRET within procedures
write_prologue	proto :tok_t
ProcInit	proto

ProcCheckOpen	proto

endif
.pragma list(pop)

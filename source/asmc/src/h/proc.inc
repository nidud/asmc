.pragma list(push, 0)
ifndef __PROC_INC
__PROC_INC equ <>

;; interface to PROC.ASM routines

externdef CurrProc:dsym_t		; current procedure
externdef sym_ReservedStack:asym_t	; max stack space required by INVOKE

;; v2.11: proc status flags
.enum proc_status {
    PRST_INSIDE_PROLOGUE   = 0x01,
    PRST_INSIDE_EPILOGUE   = 0x02,
    PRST_FPO		   = 0x04,
    PRST_PROLOGUE_NOT_DONE = 0x80
    }

ParseProc	proto :ptr esym, :int_t, :token_t, :int_t, :uchar_t
CreateProc	proto :asym_t, :string_t, :int_t
DeleteProc	proto :ptr esym

CopyPrototype	proto :ptr esym, :ptr esym
RetInstr	proto :int_t, :token_t, :int_t ; handle RET/IRET within procedures
write_prologue	proto :token_t
ProcInit	proto

ProcCheckOpen	proto

endif
.pragma list(pop)

; PROC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __PROC_INC
define __PROC_INC

; interface to PROC.ASM routines

externdef CurrProc:ptr dsym		; current procedure
externdef sym_ReservedStack:ptr asym	; max stack space required by INVOKE

; v2.11: proc status flags
.enum proc_status {
    PRST_INSIDE_PROLOGUE   = 0x01,
    PRST_INSIDE_EPILOGUE   = 0x02,
    PRST_FPO		   = 0x04,
    PRST_PROLOGUE_NOT_DONE = 0x80
    }

ParseProc	proto :ptr dsym, :int_t, :ptr asm_tok, :int_t, :uchar_t
CreateProc	proto :ptr asym, :string_t, :int_t
DeleteProc	proto :ptr dsym

CopyPrototype	proto :ptr dsym, :ptr dsym
RetInstr	proto :int_t, :token_t, :int_t ; handle RET/IRET within procedures
write_prologue	proto :ptr asm_tok
ProcInit	proto

ProcCheckOpen	proto

endif

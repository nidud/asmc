; PROC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __PROC_INC
define __PROC_INC

; interface to PROC.ASM routines

; v2.34.64 - new language info

define _P_FASTCALL	0x01	; has register params
define _P_REGPARAM	0x02	; use register params (TMACRO)
define _P_CLEANUP	0x04	; local stack cleanup
define _P_LEFT		0x08	; push/assign arguments left-to-right
define _P_RESSTACK	0x10	; use reserved stack
define _P_SYSTEMV	0x20	; return SIMD count ( for vararg )

.template fc_regs

    gpr_db	db 8 dup(?)	; General purpose registers
    gpr_dw	db 8 dup(?)
    gpr_dd	db 8 dup(?)
    gpr_dq	db 8 dup(?)
   .ends
    fcregs_t	typedef ptr fc_regs

.template fc_info

    maxgpr	db ?		; 0..8
    maxxmm	db ?		; 0..16
    expsize	db ?		; extend regs to this size
    maxint	db ?		; sizeof(reg::reg[::reg::reg])
    regmask	dd ?		; mask bits: [xmm:16][gpr:16]
    regpack	fcregs_t ?
    flags	db ?
   .ends

; v2.11: proc status flags

.enum proc_status {
    PRST_INSIDE_PROLOGUE   = 0x01,
    PRST_INSIDE_EPILOGUE   = 0x02,
    PRST_FPO		   = 0x04,
    PRST_PROLOGUE_NOT_DONE = 0x80
    }

ROUND_UP proto watcall i:uint_t, r:uint_t {
    dec edx
    add eax,edx
    not edx
    and eax,edx
    }

externdef	CurrProc:ptr dsym		; current procedure
externdef	sym_ReservedStack:ptr asym	; max stack space required by INVOKE

ParseProc	proto __ccall :ptr dsym, :int_t, :ptr asm_tok, :int_t, :uchar_t
CreateProc	proto __ccall :ptr asym, :string_t, :int_t
DeleteProc	proto __ccall :ptr dsym
CopyPrototype	proto __ccall :ptr dsym, :ptr dsym
RetInstr	proto __ccall :int_t, :token_t, :int_t ; handle RET/IRET within procedures
write_prologue	proto __ccall :ptr asm_tok
ProcInit	proto __ccall
ProcCheckOpen	proto __ccall
get_regname	proto __ccall :int_t, :int_t
get_register	proto __ccall :int_t, :int_t
get_fasttype	proto fastcall :int_t, :int_t
MacroInline	proto __ccall :string_t, :int_t, :string_t, :string_t, :int_t

endif

; PROC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __PROC_INC
define __PROC_INC

; interface to PROC.ASM routines
;
; v2.34.64 - new fastcall info
;
define FC_FIXED	    0x01    ; registers is equal to param index
define FC_LOCAL	    0x02    ; local stack cleanup
define FC_RESERVED  0x04    ; use reserved stack
define FC_TMACRO    0x08    ; add TMACRO register-param name
define FC_SYSTEMV   0x10    ; return SIMD count ( for vararg )

.template fc_info
    gpr_db	db 8 dup(?) ; General purpose registers
    gpr_dw	db 8 dup(?)
    gpr_dd	db 8 dup(?) ; mask bits
    gpr_dq	db 8 dup(?) ; 0	 1  2  3  6  7	8  9
    gpr_mask	dd ?	    ; AX CX DX BX SI DI R8 R9
    max_reg	db ?	    ; 0..14
    max_gpr	db ?	    ; 0..6
    max_xmm	db ?	    ; 0..8
    max_int	db ?	    ; sizeof(reg::reg[::reg::reg])
    stk_size	db ?	    ; word size or 16 for vectorcall
    exp_size	db ?	    ; extend regs to exp_size
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
externdef	size_vararg:int_t		; size of :VARARG arguments

ParseProc	proto __ccall :ptr dsym, :int_t, :ptr asm_tok, :int_t, :uchar_t
CreateProc	proto __ccall :ptr asym, :string_t, :int_t
DeleteProc	proto __ccall :ptr dsym

CopyPrototype	proto __ccall :ptr dsym, :ptr dsym
RetInstr	proto __ccall :int_t, :token_t, :int_t ; handle RET/IRET within procedures
write_prologue	proto __ccall :ptr asm_tok
ProcInit	proto __ccall

ProcCheckOpen	proto __ccall

GetFastcallId	proto fastcall :int_t
GetParamDirection proto fastcall :dsym_t
get_regname	proto __ccall :int_t, :int_t
get_register	proto __ccall :int_t, :int_t
get_fasttype	proto fastcall :int_t, :int_t

fastcall_init	proto __ccall
fast_pcheck	proto __ccall :dsym_t, :dsym_t, :ptr int_t
fast_fcstart	proto __ccall :dsym_t, :int_t, :int_t, :token_t, :ptr int_t
fast_param	proto __ccall :dsym_t, :int_t, :dsym_t, :int_t, :ptr expr, :string_t, :ptr byte
fast_return	proto __ccall :dsym_t, :string_t
fast_fcend	proto __ccall :dsym_t, :int_t, :int_t

endif

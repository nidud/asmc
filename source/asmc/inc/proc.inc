; PROC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __PROC_INC
define __PROC_INC

; interface to PROC.ASM routines

; v2.34.64 - new language info

define _P_REGPARAM	0x01	; use register params (TMACRO)
define _P_CLEANUP	0x02	; local stack cleanup
define _P_LEFT		0x04	; push/assign arguments left-to-right
define _P_EXTEND	0x08	; extend regs to 2/4
define _P_RESSTACK	0x10	; use reserved stack
define _P_SYSTEMV	0x20	; System V
define _P_CSTACK	0x40	; USES register outside stack-frame (-Cs)

define _P_FASTCALL	(_P_REGPARAM or _P_RESSTACK or _P_SYSTEMV)

.enum reg_used_flags {

    R0_USED	  = 0x01,	; register contents of AX/EAX/RAX is destroyed
    R0_H_CLEARED  = 0x02,	; 16bit: high byte of R0 (=AH) has been set to 0
    R0_X_CLEARED  = 0x04,	; 16bit: register R0 (=AX) has been set to 0
    R2_USED	  = 0x08,	; contents of DX is destroyed ( via CWD ); cpu < 80386 only

    ; fc_info.regmask bits: [mask:8]:[vector:12]:[gpr:12]

    ; total register assignments for invoke is 8
    ; from 10 GPR's + 8 KMASK + 12 vectors: aux(K7, R11, ..
    ; this should be extended to APX (8:32:32)

    VSHIFT_USED = 12,
    KSHIFT_USED = 24,
    RMASK_USED	= 0x00000FFF,
    VMASK_USED	= 0x00FFF000,
    KMASK_USED	= 0xFF000000,

    AX_USED	= 0x00000001,	; GPR
    CX_USED	= 0x00000002,
    DX_USED	= 0x00000004,
    BX_USED	= 0x00000008,
    SP_USED	= 0x00000010,
    BP_USED	= 0x00000020,
    SI_USED	= 0x00000040,
    DI_USED	= 0x00000080,
    R8_USED	= 0x00000100,
    R9_USED	= 0x00000200,
    R10_USED	= 0x00000400,
    R11_USED	= 0x00000800,

    V0_USED	= 0x00001000,	; vector X|Y|ZMM
    V1_USED	= 0x00002000,
    V2_USED	= 0x00003000,
    V3_USED	= 0x00004000,
    V4_USED	= 0x00010000,
    V5_USED	= 0x00020000,
    V6_USED	= 0x00030000,
    V7_USED	= 0x00040000,

    K0_USED	= 0x01000000,	; mask register
    K1_USED	= 0x02000000,
    K2_USED	= 0x03000000,
    K3_USED	= 0x04000000,
    K4_USED	= 0x10000000,
    K5_USED	= 0x20000000,
    K6_USED	= 0x30000000,
    K7_USED	= 0x40000000,
    }

.template fc_regs
    gpr_db	db 8 dup(?)	; General purpose registers
    gpr_dw	db 8 dup(?)
    gpr_dd	db 8 dup(?)
    gpr_dq	db 8 dup(?)
   .ends
    fcregs_t	typedef ptr fc_regs

.template fc_info
    regpack	fcregs_t ?
    regmask	dd ?		; mask bits
    maxgpr	db ?		; 0..8
    maxxmm	db ?		; 0..16
    maxint	db ?		; sizeof(reg::reg[::reg::reg])
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

externdef	ProcStatus:proc_status
externdef	CurrProc:asym_t		 ; current procedure
externdef	sym_ReservedStack:asym_t ; max stack space required by INVOKE

ParseProc	proto __ccall :asym_t, :int_t, :token_t, :int_t, :uchar_t
CreateProc	proto __ccall :asym_t, :string_t, :int_t
DeleteProc	proto __ccall :asym_t
CopyPrototype	proto __ccall :asym_t, :asym_t
RetInstr	proto __ccall :int_t, :token_t, :int_t ; handle RET/IRET within procedures
write_prologue	proto __ccall :token_t
ProcInit	proto __ccall
ProcCheckOpen	proto __ccall
get_regname	proto __ccall :int_t, :int_t
get_register	proto __ccall :int_t, :int_t
get_fasttype	proto fastcall :int_t, :int_t
MacroInline	proto __ccall :string_t, :int_t, :string_t, :string_t, :int_t
SetLocalOffsets proto __ccall :proc_t
UpdateStackBase proto fastcall :asym_t, :ptr expr
UpdateProcStatus proto fastcall :asym_t, :ptr expr

endif

; PROC.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __PROC_INC
define __PROC_INC

; interface to PROC.ASM routines

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

fastcall_conv	struct
invokestart	proc __ccall :ptr dsym, :int_t, :int_t, :ptr asm_tok, :ptr int_t
invokeend	proc __ccall :ptr dsym, :int_t, :int_t
handleparam	proc __ccall :ptr dsym, :int_t, :ptr dsym, :int_t, :ptr expr, :string_t, :ptr uint_8
paramcheck	proc __ccall :ptr dsym, :ptr dsym, :ptr int_t
handlereturn	proc __ccall :ptr dsym, :string_t
fastcall_conv	ends

externdef	fastcall_tab:fastcall_conv
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

GetSegmentPart	proto __ccall :ptr expr, :string_t, :string_t
fastcall_init	proto __ccall
GetFastcallId	proto fastcall :int_t
get_regname	proto __ccall :int_t, :int_t

endif

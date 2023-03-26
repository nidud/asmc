; ASSUME.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __ASSUME_INC
define __ASSUME_INC

; flags for error field, used for GPR's ASSUME:ERROR|NOTHING

.enum err_flags {
    RL_ERROR	= 0x01,
    RX_ERROR	= 0x02,
    ERX_ERROR	= 0x04,
    RRX_ERROR	= 0x08,
    RH_ERROR	= 0x10
    }


assume_info	struct
symbol		asym_t ? ; segment, group or type that is to be associated with the register
error		db ?	 ; register assumed to ERROR
is_flat		db ?	 ; register assumed to FLAT
assume_info	ends

; v2.05: introduced
stdassume_typeinfo struct
type		asym_t ?
target_type	asym_t ?
mem_type	db ?
ptr_memtype	db ?
is_ptr		db ?
stdassume_typeinfo ends

; segment assume table is sorted by seg reg number: ES,CS,SS,DS,FS,GS.
; see enum assume_segreg in globals.h.

externdef	SegAssumeTable:assume_info

; standard register assume table; contains 8/16 entries for the GPRs
externdef	StdAssumeTable:assume_info

define NUM_SEGREGS 6

AssumeInit	proto fastcall :int_t ; init assume tables

search_assume	proto __ccall :asym_t, :int_t, :int_t
GetAssume	proto __ccall :asym_t, :asym_t, :int_t, :asym_t

GetOverrideAssume proto fastcall :int_t
GetStdAssume	proto fastcall :int_t
GetStdAssumeEx	proto watcall :int_t

ModelAssumeInit proto
SetSegAssumeTable proto fastcall :ptr
GetSegAssumeTable proto fastcall :ptr
SetStdAssumeTable proto fastcall :ptr, :ptr stdassume_typeinfo
GetStdAssumeTable proto fastcall :ptr, :ptr stdassume_typeinfo
GetLastAssumedReg proto

endif

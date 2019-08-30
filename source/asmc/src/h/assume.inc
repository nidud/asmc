.pragma list(push, 0)
ifndef __ASSUME_INC
__ASSUME_INC equ <>

;; flags for error field, used for GPR's ASSUME:ERROR|NOTHING

err_flags	typedef int_t
RL_ERROR	equ 0x01
RX_ERROR	equ 0x02
ERX_ERROR	equ 0x04
RRX_ERROR	equ 0x08
RH_ERROR	equ 0x10


assume_info	struct
symbol		asym_t ? ; segment, group or type that is to be associated with the register
error		db ?	 ; register assumed to ERROR
is_flat		db ?	 ; register assumed to FLAT
assume_info	ends

;; v2.05: introduced
stdassume_typeinfo struct
type		asym_t ?
target_type	asym_t ?
mem_type	db ?
ptr_memtype	db ?
is_ptr		db ?
stdassume_typeinfo ends

;; segment assume table is sorted by seg reg number: ES,CS,SS,DS,FS,GS.
;; see enum assume_segreg in globals.h.
;;
externdef	SegAssumeTable:assume_info

;; standard register assume table; contains 8/16 entries for the GPRs
externdef	StdAssumeTable:assume_info

NUM_SEGREGS	equ 6

AssumeInit	proto :int_t ;init assume tables

search_assume	proto :asym_t, :int_t, :int_t
GetAssume	proto :asym_t, :asym_t, :int_t, :asym_t

GetOverrideAssume proto :int_t
GetStdAssume	proto :int_t
GetStdAssumeEx	proto :int_t

ModelAssumeInit proto
SetSegAssumeTable proto :ptr
GetSegAssumeTable proto :ptr
SetStdAssumeTable proto :ptr, :ptr stdassume_typeinfo
GetStdAssumeTable proto :ptr, :ptr stdassume_typeinfo

endif
.pragma list(pop)

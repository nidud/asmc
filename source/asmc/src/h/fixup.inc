.pragma list(push, 0)

;; fixup related variables and routines

ifndef __FIXUP_inc
__FIXUP_inc equ <>

;; RELOFF8 - RELOFF32 must be consecutive

fixup_types		typedef int_t

FIX_VOID		equ  0 ;;  0, fixup is to be ignored
FIX_RELOFF8		equ  1 ;;  1, 1 byte
FIX_RELOFF16		equ  2 ;;  2, 2 byte
FIX_RELOFF32		equ  3 ;;  3, 4 byte
FIX_OFF8		equ  4 ;;  4, 1 byte, OMF, BIN + GNU-ELF only
FIX_OFF16		equ  5 ;;  5, 2 byte
FIX_OFF32		equ  6 ;;  6, 4 byte
FIX_OFF64		equ  7 ;;  7, 8 byte, COFF64, ELF64 + BIN only
FIX_SEG			equ  8 ;;  8, 2 byte
FIX_PTR16		equ  9 ;;  9, 4 byte, OMF+BIN-MZ only
FIX_PTR32		equ 10 ;; 10, 6 byte, OMF+BIN-MZ only
FIX_HIBYTE		equ 11 ;; 11, 1 byte, OMF+BIN-MZ only
FIX_OFF32_IMGREL	equ 12 ;; 12, 4 byte, COFF+ELF only
FIX_OFF32_SECREL	equ 13 ;; 13, 4 byte, COFF+ELF only
FIX_LAST		equ 14


;;  OMF: nothing (7, 12, 13 can't happen)
;; COFF: set bit 1, 4, 9, 10, 11
;;  ELF: set bit 8, 9, 10, 11
;;
BIN_DISALLOWED		equ 0x0000
OMF_DISALLOWED		equ 0x0000
COFF32_DISALLOWED	equ 0x0E12 ;; exclude RELOFF8, OFF8, PTR16, PTR32, HIBYTE
COFF64_DISALLOWED	equ 0x0E12 ;; exclude RELOFF8, OFF8, PTR16, PTR32, HIBYTE
ELF32_DISALLOWED	equ 0x0F00 ;; exclude SEG, PTR16, PTR32, HIBYTE
ELF64_DISALLOWED	equ 0x0F00 ;; exclude SEG, PTR16, PTR32, HIBYTE

;; fixups are also used for backpatching of forward references in pass one.
;; the instructions which depend on the distance are CALL, JMP, PUSH <imm>.
;; OPTJ_EXPLICIT: JMP SHORT <label> or Jcc SHORT <label>, size cannot change
;; OPTJ_EXTEND:	  Jcc <label> for cpu < 80386, size may change (2 -> 5/7 or 8/10)
;; OPTJ_JXX:	  Jcc <label> for cpu >= 80386, size may change (2 -> 5 )
;; OPTJ_CALL:	  call <label>, may become push cs, call NEAR or call FAR
;; OPTJ_PUSH:	  push <label>, assumed byte, may become variable or label.
;;

fixup_options		typedef int_t
OPTJ_NONE		equ 0 ;; normal jump
OPTJ_EXPLICIT		equ 1
OPTJ_EXTEND		equ 2
OPTJ_JXX		equ 3
OPTJ_CALL		equ 4
OPTJ_PUSH		equ 5 ;; PUSH

FX_ORGOCCURED		equ 0x0200
FX_LOADER_RESOLVED	equ 0x0100

fixup_t			typedef ptr fixup

fixup struct
    nextbp		fixup_t ?	;; PASS 1: linked list backpatch
    nextrlc		fixup_t ?	;; PASS >1: linked list relocs
    offs		dd ?		;; symbol's offset
    locofs		dd ?		;; location of fixup
    type		db ?
    options		db ?
    union
	flags		dw ?
	struct
	    ;; the IP relative addressing needs to know where the instruction ends.
	    ;; the result <end of instruction> - <fixup location> is stored here.
	    ;;
	    addbytes	db ?
	    loader_resolved db ?;:1 ;; operator LROFFSET
	    ;orgoccured uchar_t :1	;; v2.04 ORG occured behind this fix
	ends
    ends
    union
	struct
	    frame_type	char_t ?	;; frame specifier (SEG=0,GRP=1,,...)
	    frame_datum ushort_t ?	;; additional data, usually index
	ends
	segment_var	asym_t ?	;; symbol's segment if assembly time var
    ends
    def_seg		dsym_t ?	;; segment the fixup is in - pass 1 only
    sym			asym_t ?
fixup ends

CreateFixup	proto :asym_t, :fixup_types, :fixup_options
SetFixupFrame	proto :asym_t, :char_t
FreeFixup	proto :fixup_t
store_fixup	proto :fixup_t, :dsym_t, :ptr int_t
BackPatch	proto :asym_t

endif
.pragma list(pop)
.pragma list(push, 0)

;; definitions for code generator interface

ifndef __CODEGEN_INC
__CODEGEN_INC equ <>

BIT_012		equ 0x07
BIT_345		equ 0x38
BIT_67		equ 0xC0
NOT_BIT_012	equ 0xF8
NOT_BIT_345	equ 0xC7 ;; mask to filter Mod- and R/M-bits for ModRM-byte
NOT_BIT_67	equ 0x3F

MOD_00		equ 0x00
MOD_01		equ 0x40
MOD_10		equ 0x80
MOD_11		equ 0xC0

;; opcode bits:
;; 0: w/ide bit, operand size BYTE <-> D/WORD
;; 1: s/ign bit, sign extended immediate
;; 1: d/irection bit
;;

W_BIT		equ 0x01
NOT_W_BIT	equ 0xFE

ADRSIZ		equ 0x67
OPSIZ		equ 0x66
OP_WAIT		equ 0x9B
EXTENDED_OPCODE equ 0x0F
OP_NOP		equ 0x90

RM_BX_SI	equ 0x00
RM_BX_DI	equ 0x01
RM_BP_SI	equ 0x02
RM_BP_DI	equ 0x03
RM_SI		equ 0x04
RM_DI		equ 0x05
RM_BP		equ 0x06
RM_BX		equ 0x07

RM_SIB		equ 0x04
RM_D32		equ 0x05  ;; direct 32
RM_D16		equ 0x06  ;; direct 16

SCALE_FACTOR_1	equ 0x00
SCALE_FACTOR_2	equ 0x40
SCALE_FACTOR_4	equ 0x80
SCALE_FACTOR_8	equ 0xC0

FPE_MIN		equ 0xD8
FPE_MAX		equ 0xDF

IS_MEM_TYPE macro op, typ
    exitm<( (op) == MT_&typ& || (op) == MT_S&typ& )>
    endm
IS_MEMTYPE_SIZ macro op, siz
  ifdif <op>,<al>
    mov al,op
  endif
    mov ah,al
    and al,MT_SPECIAL_MASK
    and ah,MT_SIZE_MASK
    exitm<( al !< MT_SPECIAL && ( ah == ( siz - 1 ) ) )>
    endm

;;
;; values for <byte1_info>
;; 000	: the first byte is opcode, follow by rm_byte
;; F_16 : the first byte is OPSIZ prefix if in use32 segment
;; F_32 : the first byte is OPSIZ prefix if in use16 segment
;; F_0F : the first byte is 0x0F, follow by opcode and rm_byte
;; the entries must be sorted related to F_0F prefix:
;; entries < F_0F emit NO 0F prefix, entries >= F_0F emit one.
;; v2.06: magnitude of this field extended to 8 (previously 4).
;; the entries with 38/3A must be last in the 0F group!
;;
;enum byte1_info {
F_16		equ 1	;; 16bit variant, 66h switches
F_32		equ 2	;; 32bit variant, 66h switches
F_16A		equ 3	;; 16bit variant, 67h switches
F_32A		equ 4	;; 32bit variant, 67h switches
F_F3		equ 5	;; F3 prefix (pause: F3 90)
F_48		equ 6	;; REX.W prefix
F_0F		equ 16	;; 0F escape
F_C5L		equ 17	;; VEX.L1.0F.C4.L
F_0F0F		equ 18	;; AMD 3DNow "prefix"
F_660F		equ 19	;; SSEx prefix 1
F_C5LP0		equ 20	;; VEX.L1.66.0F.C4.L.P0
F_F20F		equ 21	;; SSEx prefix 2
F_F30F		equ 22	;; SSEx prefix 3
F_0FNO66	equ 23	;; 0F escape, no size prefix
F_480F		equ 24	;; REX.W + 0F prefix ( cmpxchg16b )
F_0F38		equ 25	;; must be first of 38/3A variants
F_0F3A		equ 26
F_660F38	equ 27
F_660F3A	equ 28
F_F20F38	equ 29
F_F30F38	equ 30
F_F20F3A	equ 31
F_C4M0		equ 32	;; VEX.L1.0F.C5.M0
F_C4M0P0	equ 33	;; VEX.L1.66.0F.C5.M0.P0
F_C4M0L		equ 34	;; VEX.L1.0F.C5.M0.L
F_C4M0P0L	equ 35	;; VEX.L1.66.0F.C5.M0.L.P0


;; VX_NND is only needed if instruction has more than 2 operands

;enum vex_info {
VX_L		equ 0x01 ;; VEX.L supported
VX_NND		equ 0x02 ;; VEX.NDS/NDD not supported
VX_DST		equ 0x04 ;; VEX.NDD (if op3 is an immediate)
VX_IMM		equ 0x08 ;; no VEX.NDS if op3 is an immediate
VX_NMEM		equ 0x10 ;; no VEX.NDS if op1 is a mem ref (vmovs[d|s], vmov[h|l]p[d|s] )
VX_HALF		equ 0x20 ;; op2 is half-sized
VX_RW0		equ 0x40 ;; no REX.W bit
VX_RW1		equ 0x80 ;; set REX.W bit

codegen proto :ptr code_info, :uint_t

endif
.pragma list(pop)
; CODEGEN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; definitions for code generator interface
;
ifndef __CODEGEN_INC
define __CODEGEN_INC

define BIT_012          0x07
define BIT_345          0x38
define BIT_67           0xC0
define NOT_BIT_012      0xF8
define NOT_BIT_345      0xC7 ; mask to filter Mod- and R/M-bits for ModRM-byte
define NOT_BIT_67       0x3F

define MOD_00           0x00
define MOD_01           0x40
define MOD_10           0x80
define MOD_11           0xC0

; opcode bits:
; 0: w/ide bit, operand size BYTE <-> D/WORD
; 1: s/ign bit, sign extended immediate
; 1: d/irection bit

define W_BIT            0x01
define NOT_W_BIT        0xFE

define ADRSIZ           0x67
define OPSIZ            0x66
define OP_WAIT          0x9B
define EXTENDED_OPCODE  0x0F
define OP_NOP           0x90

define RM_BX_SI         0x00
define RM_BX_DI         0x01
define RM_BP_SI         0x02
define RM_BP_DI         0x03
define RM_SI            0x04
define RM_DI            0x05
define RM_BP            0x06
define RM_BX            0x07

define RM_SIB           0x04
define RM_D32           0x05  ; direct 32
define RM_D16           0x06  ; direct 16

define SCALE_FACTOR_1   0x00
define SCALE_FACTOR_2   0x40
define SCALE_FACTOR_4   0x80
define SCALE_FACTOR_8   0xC0

define FPE_MIN          0xD8
define FPE_MAX          0xDF

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

;
; values for <byte1_info>
; 000   : the first byte is opcode, follow by rm_byte
; F_16 : the first byte is OPSIZ prefix if in use32 segment
; F_32 : the first byte is OPSIZ prefix if in use16 segment
; F_0F : the first byte is 0x0F, follow by opcode and rm_byte
; the entries must be sorted related to F_0F prefix:
; entries < F_0F emit NO 0F prefix, entries >= F_0F emit one.
; v2.06: magnitude of this field extended to 8 (previously 4).
; the entries with 38/3A must be last in the 0F group!
;
.enum byte1_info {
    F_16            = 1,   ; 16bit variant, 66h switches
    F_32            = 2,   ; 32bit variant, 66h switches
    F_16A           = 3,   ; 16bit variant, 67h switches
    F_32A           = 4,   ; 32bit variant, 67h switches
    F_F3            = 5,   ; F3 prefix (pause: F3 90)
    F_48            = 6,   ; REX.W prefix
    F_0F            = 16,  ; 0F escape
    F_C5L           = 17,  ; VEX.L1.0F.C4.L
    F_0F0F          = 18,  ; AMD 3DNow "prefix"
    F_660F          = 19,  ; SSEx prefix 1
    F_C5LP0         = 20,  ; VEX.L1.66.0F.C4.L.P0
    F_F20F          = 21,  ; SSEx prefix 2
    F_F30F          = 22,  ; SSEx prefix 3
    F_0FNO66        = 23,  ; 0F escape, no size prefix
    F_480F          = 24,  ; REX.W + 0F prefix ( cmpxchg16b )
    F_0F38          = 25,  ; must be first of 38/3A variants
    F_0F3A          = 26,
    F_660F38        = 27,
    F_660F3A        = 28,
    F_F20F38        = 29,
    F_F30F38        = 30,
    F_F20F3A        = 31,
    F_C4M0          = 32,  ; VEX.L1.0F.C5.M0
    F_C4M0P0        = 33,  ; VEX.L1.66.0F.C5.M0.P0
    F_C4M0L         = 34,  ; VEX.L1.0F.C5.M0.L
    F_C4M0P0L       = 35,  ; VEX.L1.66.0F.C5.M0.L.P0
    F_F30F3A        = 36,
    }


; VX_NND is only needed if instruction has more than 2 operands

.enum vex_info {
    VX_L            = 0x01, ; VEX.L supported
    VX_NND          = 0x02, ; VEX.NDS/NDD not supported
    VX_DST          = 0x04, ; VEX.NDD (if op3 is an immediate)
    VX_IMM          = 0x08, ; no VEX.NDS if op3 is an immediate
    VX_NMEM         = 0x10, ; no VEX.NDS if op1 is a mem ref (vmovs[d|s], vmov[h|l]p[d|s] )
    VX_HALF         = 0x20, ; op2 is half-sized
    VX_RW0          = 0x40, ; no REX.W bit
    VX_RW1          = 0x80  ; set REX.W bit
    }

codegen proto __ccall :ptr code_info, :uint_t

endif

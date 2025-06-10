; EXPREVAL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; interface to expression evaluator
;
.pragma list(push, 0)
ifndef __EXPREVAL_INC
define __EXPREVAL_INC

; v2.11: EXPR_UNDEF changed to EXPR_ERROR, value -1

.enum exprtype {
    EXPR_EMPTY = EMPTY,
    EXPR_ERROR = ERROR, ; undefined type when error occures or result is undefined
    EXPR_CONST = 0,	; constant; note that "label1 - label2" -> constant
    EXPR_ADDR,		; e.g. "foo", "seg foo" and "offset foo", also indirect mem ops
    EXPR_REG,		; register
    EXPR_FLOAT		; v2.05: float
    }

; argument types accepted by unary operators

.enum oparg_types {
    AT_TYPE	= 0x01, ; type
    AT_LABEL	= 0x02, ; label (direct memory)
    AT_IND	= 0x04, ; indirect memory
    AT_REG	= 0x08, ; register
    AT_FIELD	= 0x10, ; struct field
    AT_NUM	= 0x20, ; number
    AT_BF	= 0x40, ; bitfield and record types
    AT_UNDEF	= 0x80, ; undefined label
    AT_FLOAT	= 0x100,; float constant

    AT_CONST	= AT_TYPE or AT_NUM,
    AT_CONSTF	= AT_TYPE or AT_NUM or AT_FLOAT,
    AT_TL	= AT_TYPE or AT_LABEL,
    AT_TLN	= AT_TYPE or AT_LABEL or AT_NUM,
    AT_TLNF	= AT_TYPE or AT_LABEL or AT_NUM or AT_FLOAT,
    AT_TLF	= AT_TYPE or AT_LABEL or AT_FIELD,
    AT_TLFN	= AT_TYPE or AT_LABEL or AT_FIELD or AT_NUM,
    AT_TBF	= AT_TYPE or AT_BF,
    AT_TBFF	= AT_TYPE or AT_BF or AT_FIELD, ; added for MASKOF and WIDTHOF
    AT_LF	= AT_LABEL or AT_FIELD,
    AT_LIF	= AT_LABEL or AT_IND or AT_FIELD,
    AT_LFN	= AT_LABEL or AT_FIELD or AT_NUM,
    AT_TLR	= AT_TYPE or AT_LABEL or AT_REG,
    AT_ALL	= AT_TYPE or AT_LABEL or AT_IND or AT_REG or AT_FIELD or AT_NUM or AT_UNDEF or AT_BF or AT_FLOAT
    }

; expression, returned by expression evaluator

expr		struct
union		; value of expression
 struct
  value		int_t ?
  hvalue	int_t ?
 ends
 struct
  union
   llvalue	uint64_t ?
   struct
    l64_l	uint_t ?
    l64_h	uint_t ?
   ends
  ends
  union
   hlvalue	uint64_t ?
   struct
    h64_l	uint_t ?
    h64_h	uint_t ?
   ends
  ends
 ends
 uvalue		uint_t ?
 value64	int64_t ?
 dvalue		real8 ?
 fvalue		real4 ?
 st_idx		int_t ?		; EXPR_REG: index if reg is ST
 chararray	uchar_t 16 dup(?)
ends
union
 quoted_string	token_t ?	; for EXPR_CONST + quoted strings only
 float_tok	token_t ?	; for EXPR_FLOAT only
ends
base_reg	token_t ?	; EXPR_ADDR: base register token, EXPR_REG: register token
idx_reg		token_t ?	; EXPR_ADDR: index register token
union
 label_tok	token_t ?	; token holding the label (EXPR_ADDR, used for overrides, inside expreval only)
 type_tok	token_t ?	; v2.10: token if target type of a label (SYM_STACK, MT_PTR) is to be stored
ends
override	token_t ?	; EXPR_ADDR: token holding the override label or segment register
inst		int_t ?		; operator token
kind		int_t ?		; Type of expression
mem_type	uchar_t ?
scale		uchar_t ?	; EXPR_ADDR: scaling factor 1, 2, 4, or 8 - 386 code only
Ofssize		uchar_t ?	; 16,32,64 bit if MT_NEAR, MT_FAR
union
 flags		uchar_t ?	; bit-flag
 record
  indirect	uchar_t : 1 ?	; indirect addressing used
  explicit	uchar_t : 1 ?	; Whether expression type explicitly given (to be removed!)
  is_abs	uchar_t : 1 ?	; external ABS
  is_type	uchar_t : 1 ?	; constant is a type
  is_opattr	uchar_t : 1 ?	; current operator is OPATTR
  negative	uchar_t : 1 ?	; for EXPR_FLOAT only
  assumecheck	uchar_t : 1 ?	; v2.07: for ASSUMEd std registers
  is_dot	uchar_t : 1 ?	; v2.10: see regression test dotop5.asm
 ends
ends
op		ptr opinfo ?
sym		asym_t ?	; label used
mbr		asym_t ?	; struct member
type		asym_t ?	; for DOT operator. Must be last (see TokenAssign)!
expr		ends
expr_t		typedef ptr expr

; flags for last argument of EvalOperand()

.enum expr_flags {
    EXPF_NOERRMSG  = 1,	 ; suppress error messages
    EXPF_NOUNDEF   = 2,	 ; don't accept or create undefined symbols
    EXPF_ONEOPND   = 4,	 ; private flag, used inside expreval.c only
    EXPF_IN_SQBR   = 8	 ; private flag, used inside expreval.c only
    }

EvalOperand	proto __ccall :ptr int_t, :ptr asm_tok, :int_t, :ptr expr, :uchar_t
ExprEvalInit	proto
EmitConstError	proto

endif
.pragma list(pop)

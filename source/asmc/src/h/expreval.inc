.pragma list(push, 0)

;; interface to expression evaluator

ifndef __EXPREVAL_INC
__EXPREVAL_INC equ <>

;; v2.11: EXPR_UNDEF changed to EXPR_ERROR, value -1

EXPR_EMPTY	equ EMPTY
EXPR_ERROR	equ ERROR ; undefined type when error occures or result is undefined
EXPR_CONST	equ 0	  ; constant; note that "label1 - label2" -> constant
EXPR_ADDR	equ 1	  ; e.g. "foo", "seg foo" and "offset foo", also indirect mem ops
EXPR_REG	equ 2	  ; register
EXPR_FLOAT	equ 3	  ; v2.05: float

;; argument types accepted by unary operators

AT_TYPE		equ 0x01  ; type
AT_LABEL	equ 0x02  ; label (direct memory)
AT_IND		equ 0x04  ; indirect memory
AT_REG		equ 0x08  ; register
AT_FIELD	equ 0x10  ; struct field
AT_NUM		equ 0x20  ; number
AT_BF		equ 0x40  ; bitfield and record types
AT_UNDEF	equ 0x80  ; undefined label
AT_FLOAT	equ 0x100 ; float constant

AT_CONST	equ AT_TYPE  or AT_NUM
AT_TL		equ AT_TYPE  or AT_LABEL
AT_TLN		equ AT_TYPE  or AT_LABEL or AT_NUM
AT_TLF		equ AT_TYPE  or AT_LABEL or AT_FIELD
AT_TLFN		equ AT_TYPE  or AT_LABEL or AT_FIELD or AT_NUM
AT_TBF		equ AT_TYPE  or AT_BF
AT_LF		equ AT_LABEL or AT_FIELD
AT_LIF		equ AT_LABEL or AT_IND or AT_FIELD
AT_LFN		equ AT_LABEL or AT_FIELD or AT_NUM
AT_TLR		equ AT_TYPE  or AT_LABEL or AT_REG
AT_ALL		equ AT_TYPE  or AT_LABEL or AT_IND or \
		    AT_REG   or AT_FIELD or AT_NUM or \
		    AT_UNDEF or AT_BF or AT_FLOAT

;; expression, returned by expression evaluator

E_INDIRECT	equ 0x01 ; indirect addressing used
E_EXPLICIT	equ 0x02 ; Whether expression type explicitly given (to be removed!)
E_IS_ABS	equ 0x04 ; external ABS
E_IS_TYPE	equ 0x08 ; constant is a type
E_IS_OPEATTR	equ 0x10 ; current operator is OPATTR
E_NEGATIVE	equ 0x20 ; for EXPR_FLOAT only
E_ASSUMECHECK	equ 0x40 ; v2.07: for ASSUMEd std registers
E_IS_DOT	equ 0x80 ; v2.10: see regression test dotop5.asm

expr		struct
union		; value of expression
 struct
  value		int_t ?
  hvalue	int_t ?
 ends
 struct
  llvalue	uint64_t ?
  hlvalue	uint64_t ?
 ends
 uvalue		uint_t ?
 value64	int64_t ?
 dvalue		real8 ?
 fvalue		real4 ?
 st_idx		int_t ?	  ; EXPR_REG: index if reg is ST
 chararray	uchar_t 16 dup(?)
ends
union
 quoted_string	tok_t ?	  ; for EXPR_CONST + quoted strings only
 float_tok	tok_t ?	  ; for EXPR_FLOAT only
ends
base_reg	tok_t ?	  ; EXPR_ADDR: base register token, EXPR_REG: register token
idx_reg		tok_t ?	  ; EXPR_ADDR: index register token
union
 label_tok	tok_t ?	  ; token holding the label (EXPR_ADDR, used for overrides, inside expreval only)
 type_tok	tok_t ?	  ; v2.10: token if target type of a label (SYM_STACK, MT_PTR) is to be stored
ends
override	tok_t ?	  ; EXPR_ADDR: token holding the override label or segment register
inst		int_t ?	  ; operator token
kind		int_t ?	  ; Type of expression
mem_type	uchar_t ?
scale		uchar_t ? ; EXPR_ADDR: scaling factor 1, 2, 4, or 8 - 386 code only
Ofssize		uchar_t ? ; 16,32,64 bit if MT_NEAR, MT_FAR
flags		uchar_t ? ; bit-flag
sym		asym_t ?  ; label used
mbr		asym_t ?  ; struct member
type		asym_t ?  ; for DOT operator. Must be last (see TokenAssign)!
expr		ends
expr_t		typedef ptr expr


;; flags for last argument of EvalOperand()

EXPF_NOERRMSG	equ 1	  ; suppress error messages
EXPF_NOUNDEF	equ 2	  ; don't accept or create undefined symbols
EXPF_ONEOPND	equ 4	  ; private flag, used inside expreval.c only
EXPF_IN_SQBR	equ 8	  ; private flag, used inside expreval.c only


EvalOperand	proto :ptr int_t, :tok_t, :int_t, :expr_t, :uchar_t
ExprEvalInit	proto
EmitConstError	proto :expr_t

endif
.pragma list(pop)

ifndef __HLL_INC
__HLL_INC equ <>

MIN_JTABLE	equ 8
MAX_JTABLE	equ 32

LABELSGLOBAL	equ 0	; make the generated labels global
;LABELFMT	equ <"@C%04X">
;
; v2.10: static variables moved to ModuleInfo
;
EOLCHAR		equ 10	; line termination char in generated source
NULLC		equ 0

;
; values for struct hll_item.cmd
;
HLL_IF		equ 0
HLL_WHILE	equ 1
HLL_REPEAT	equ 2
HLL_BREAK	equ 3	; .IF behind .BREAK or .CONTINUE
HLL_SWITCH	equ 4
HLL_RETURN	equ 5

;
; index values for struct hll_item.labels[]
;
LTEST		equ 0 ; test (loop) condition
LEXIT		equ 1 ; block exit
LSTART		equ 2 ; loop start
LSTARTSW	equ 3 ; start of switch

;
; values for struct hll_item.flags
;
HLLF_ELSEOCCUR	equ 0x01
HLLF_ELSEIF	equ 0x02
HLLF_WHILE	equ 0x04
HLLF_EXPRESSION equ 0x08
HLLF_DEFAULT	equ 0x10
HLLF_DELAYED	equ 0x20	; set by DelayExpand()
;
; .SWITCH <arg_type>
;
HLLF_NOTEST	equ 0x40	; direct jump..
HLLF_ARGREG	equ 0x80	; register 16/32/64-bit size_t
HLLF_ARGMEM	equ 0x0100	; memory if set, else register
HLLF_ARG16	equ 0x0200	; size: 8/16/32/64
HLLF_ARG32	equ 0x0400
HLLF_ARG64	equ 0x0800
HLLF_ARG3264	equ 0x1000	; .switch exx in 64-bit extended to rxx
;
; .CASE flags
;
HLLF_NUM	equ 0x2000	; .case arg is const
HLLF_TABLE	equ 0x4000	; .case is in jump table
HLLF_ENDCOCCUR	equ 0x8000	; jmp exit in .case omitted
;
; Return type
;
HLLF_IFB	equ 0x00010000	; .ifb proc() --> al
HLLF_IFW	equ 0x00020000	; .ifw proc() --> ax
HLLF_IFD	equ 0x00040000	; .ifd proc() --> eax
HLLF_IFS	equ 0x00080000	; Signed compare --> CMP REG,val

HLLF_PASCAL	equ 0x00100000	; option switch:pascal | .switch pascal <args>
HLLF_JTABLE	equ 0x00200000	; if HLLF_NOTEST direct .case jump
HLLF_JTDATA	equ 0x00400000	; Jump table in data segment -- HLLF_NOTEST

;
; item for .IF, .WHILE, .REPEAT, ...
;
hll_item	STRUC
next		dd ?		; hll_item *
caselist	dd ?		; hll_item *
labels		dd 4 dup(?)	; labels for LTEST, LEXIT, LSTART
condlines	LPSTR ?		; .WHILE/ELSEIF/CASE-blocks only: lines to add after 'test' label
cmd		dd ?		; start cmd (IF, WHILE, REPEAT)
flags		dd ?		; v2.08: added
hll_item	ENDS

;
; v2.08: struct added
;
hll_opnd	STRUC
lastjmp		dd ?
lasttruelabel	dd ?		; v2.08: new member
hll_opnd	ENDS

if LABELSGLOBAL
LABELQUAL	equ <"::">
else
LABELQUAL	equ <":">
endif

; in Masm, there's a nesting level limit of 20. In JWasm, there's
; currently no limit.

GetHllLabel	MACRO
	inc	ModuleInfo.hll_label
	mov	eax,ModuleInfo.hll_label
	exitm	<eax>
	ENDM

ExpandLine	proto :LPSTR, :PTR asmtok
ExpandCStrings	proto :ptr asmtok
ExpandHllProc	proto :LPSTR, :SINT, :ptr asmtok

GenerateCString proto :SINT, :PTR asmtok
EvalOperand	proto :SINT, :PTR asmtok, :SINT, :PTR expr, :SINT

GetCurrOffset	proto
QueueTestLines	proto :LPSTR
GetLabelStr	proto :SINT, :LPSTR
AddLineQueue	proto :LPSTR
InvertJump	proto fastcall :LPSTR
EmitConstError	proto :ptr expr
GetResWName	proto :UINT, :LPSTR

EvaluateHllExpression proto \
		   hll: ptr hll_item,
		     i: ptr SINT,
	    tokenarray: ptr asmtok,
		ilabel: SINT,
	       is_true: SINT,
		buffer: LPSTR

ExpandHllExpression proto \
		   hll: ptr hll_item,
		     i: ptr SINT,
	    tokenarray: ptr asmtok,
		ilabel: SINT,
	       is_true: SINT,
		buffer: LPSTR

GetExpression	proto \
		      : ptr hll_item,
		      : ptr SINT,
		      : ptr asmtok,
		      : SINT,
		      : UINT,
		      : LPSTR,
		      : ptr hll_opnd

ForDirective	proto :SINT, :ptr asmtok

endif ; __HLL_INC

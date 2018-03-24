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

;
; index values for struct hll_item.labels[]
;
LTEST		equ 0 ; test (loop) condition
LEXIT		equ 1 ; block exit
LSTART		equ 2 ; loop start

;
; values for struct hll_item.flags
;
HLLF_ELSEOCCUR	equ 01h
HLLF_ELSEIF	equ 02h
HLLF_WHILE	equ 04h
HLLF_EXPRESSION equ 08h
HLLF_DEFAULT	equ 10h
HLLF_DELAYED	equ 20h		; set by DelayExpand()
;
; .SWITCH <arg_type>
;
HLLF_NOTEST	equ 40h		; direct jump..
HLLF_ARGREG	equ 80h		; register 16/32/64-bit size_t
HLLF_ARGMEM	equ 0100h	; memory if set, else register
HLLF_ARG16	equ 0200h	; size: 8/16/32/64
HLLF_ARG32	equ 0400h
HLLF_ARG64	equ 0800h
HLLF_ARG3264	equ 1000h	; .switch exx in 64-bit extended to rxx
;
; .CASE flags
;
HLLF_NUM	equ 2000h	; .case arg is const
HLLF_TABLE	equ 4000h	; .case is in jump table
HLLF_ENDCOCCUR	equ 8000h	; jmp exit in .case omitted
;
; Return type
;
HLLF_IFB	equ 0x00010000	; .ifb proc() --> al
HLLF_IFW	equ 0x00020000	; .ifw proc() --> ax
HLLF_IFD	equ 0x00040000	; .ifd proc() --> eax
HLLF_IFS	equ 0x00080000	; Signed compare --> CMP REG,val
HLLF_CONT0	equ 0x00100000	; .continue(0) [.if]

;
; item for .IF, .WHILE, .REPEAT, ...
;
hll_item	STRUC
next		dd ?		; hll_item *
caselist	dd ?		; hll_item *
labels		dd 3 dup(?)	; labels for LTEST, LEXIT, LSTART
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

ExpandLine	proto :LPSTR, :PTR asm_tok
ExpandCStrings	proto :ptr asm_tok
ExpandHllProc	proto :LPSTR, :SINT, :ptr asm_tok

GenerateCString proto :SINT, :PTR asm_tok
EvalOperand	proto :SINT, :PTR asm_tok, :SINT, :PTR expr, :SINT

GetCurrOffset	proto
QueueTestLines	proto :LPSTR
GetLabelStr	proto fastcall :SINT, :LPSTR
AddLineQueue	proto :LPSTR
InvertJump	proto fastcall :LPSTR
EmitConstError	proto :ptr expr
GetResWName	proto :UINT, :LPSTR

EvaluateHllExpression proto \
		   hll: ptr hll_item,
		     i: ptr SINT,
	    tokenarray: ptr asm_tok,
		ilabel: SINT,
	       is_true: SINT,
		buffer: LPSTR

ExpandHllExpression proto \
		   hll: ptr hll_item,
		     i: ptr SINT,
	    tokenarray: ptr asm_tok,
		ilabel: SINT,
	       is_true: SINT,
		buffer: LPSTR

GetExpression	proto \
		      : ptr hll_item,
		      : ptr SINT,
		      : ptr asm_tok,
		      : SINT,
		      : UINT,
		      : LPSTR,
		      : ptr hll_opnd

ForDirective	proto :SINT, :ptr asm_tok

endif ; __HLL_INC

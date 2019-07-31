; ASMC.INC--
; Doszip Macro Assembler

include version.inc
include ltype.inc
include asmtok.inc

	.xlist
	.pragma warning(disable: 7007)
	option fieldalign: size_t

OLDKEYWORDS		equ 1			; NAME, SIZE, ..
CHEXPREFIX		equ 1			; 0x prefix

MAX_LINE_LEN		equ 2048		; no restriction for this number
MAX_STRING_LEN		equ MAX_LINE_LEN - 32	; must be < MAX_LINE_LEN
MAX_ID_LEN		equ 247			; must be < MAX_LINE_LEN
MAX_TOKEN		equ MAX_LINE_LEN / 4	; max tokens in one line
MAX_STRUCT_ALIGN	equ 32
MAX_SEGMENT_ALIGN	equ 4096

EMPTY			equ -2			; function return values
ERROR			equ -1
NOT_ERROR		equ 0
STRING_EXPANDED		equ 1

PASS_1			equ 0
PASS_2			equ 1

;-------------------------------------------------------------------------------
; Asmc flags
;-------------------------------------------------------------------------------

;.aflag

_AF_CSTACK		equ 0x02
_AF_WSTRING		equ 0x04 ; convert "string" to unicode
_AF_LSTRING		equ 0x08 ; L"Unicode" used --> allow dw "string"

_AF_PASCAL		equ 0x10 ; auto insert break after cases
_AF_NOTABLE		equ 0x20 ; no indexed jump table
_AF_REGAX		equ 0x40 ; use [R|E]AX to render jump-code

;.xflag

_XF_ASSERT		equ 0x01 ; Generate .assert code
_XF_PUSHF		equ 0x02 ; Push/Pop flags

;-------------------------------------------------------------------------------
; enumerations
;-------------------------------------------------------------------------------
;
; output formats. Order must match formatoptions[] in assemble.asm
;
OFORMAT_BIN		equ 0	; used by -bin, -mz and -pe
OFORMAT_OMF		equ 1
OFORMAT_COFF		equ 2	; used by -coff, -djgpp and -win64
OFORMAT_ELF		equ 3	; used by -elf and elf64

SFORMAT_NONE		equ 0
SFORMAT_MZ		equ 1	; MZ binary
SFORMAT_PE		equ 2	; PE (32- or 64-bit) binary
SFORMAT_64BIT		equ 3	; 64bit COFF or ELF

FPO_NO_EMULATION	equ 0	; -FPi87 (default)
FPO_EMULATION		equ 1	; -FPi

LANG_NONE		equ 0	; language vaules.
LANG_C			equ 1	; the order cannot be changed, it's
LANG_SYSCALL		equ 2	; returned by OPATTR and used in user-defined
LANG_STDCALL		equ 3	; prologue/epilogue.
LANG_PASCAL		equ 4
LANG_FORTRAN		equ 5
LANG_BASIC		equ 6
LANG_FASTCALL		equ 7
LANG_VECTORCALL		equ 8

MODEL_NONE		equ 0	; Memory model type.
MODEL_TINY		equ 1	; the order cannot be changed, it's
MODEL_SMALL		equ 2	; the value of the predefined @Model symbol.
MODEL_COMPACT		equ 3
MODEL_MEDIUM		equ 4
MODEL_LARGE		equ 5
MODEL_HUGE		equ 6
MODEL_FLAT		equ 7

SEGORDER_SEQ		equ 0	; .SEQ (default)
SEGORDER_DOSSEG		equ 1	; .DOSSEG
SEGORDER_ALPHA		equ 2	; .ALPHA

LM_NOLISTMACRO		equ 0	; .NOLISTMACRO, .LISTMACRO and .LISTMACROALL
LM_LISTMACRO		equ 1	; directives setting
LM_LISTMACROALL		equ 2

; assume values are used as index in codegen.c / invoke.c.
; Order must match the one in special.h. Don't change!
;
ASSUME_NOTHING		equ EMPTY
ASSUME_ES		equ 0
ASSUME_CS		equ 1
ASSUME_SS		equ 2
ASSUME_DS		equ 3
ASSUME_FS		equ 4
ASSUME_GS		equ 5

; bit count from left:
; bit 0-2:	  Math coprocessor
; bit 3:	  privileged?
; bit 4-7:	  cpu type
; bit 8-15;  extension set
;
P_NO87			equ 0001h		; no FPU
P_87			equ 0002h		; 8087
P_287			equ 0003h		; 80287
P_387			equ 0004h		; 80387
P_PM			equ 0008h		; privileged opcode
P_86			equ 0000h		; 8086, default
P_186			equ 0010h		; 80186
P_286			equ 0020h		; 80286
P_386			equ 0030h		; 80386
P_486			equ 0040h		; 80486
P_586			equ 0050h		; pentium
P_686			equ 0060h		; ppro
P_64			equ 0070h		; x64 cpu
P_286p			equ P_286 or P_PM	; 286, priv mode
P_386p			equ P_386 or P_PM	; 386, priv mode
P_486p			equ P_486 or P_PM	; 486, priv mode
P_586p			equ P_586 or P_PM	; 586, priv mode
P_686p			equ P_686 or P_PM	; 686, priv mode
P_64p			equ P_64 or P_PM	; x64, priv mode
P_MMX			equ 0100h		; MMX extension instructions
P_K3D			equ 0200h		; 3DNow extension instructions
P_SSE1			equ 0400h		; SSE1 extension instructions
P_SSE2			equ 0800h		; SSE2 extension instructions
P_SSE3			equ 1000h		; SSE3 extension instructions
P_SSSE3			equ 2000h		; SSSE3 extension instructions
P_SSE4			equ 4000h		; SSE4 extension instructions
P_AVX			equ 8000h		; AVX extension instructions

P_SSEALL		equ P_SSE1 or P_SSE2 or P_SSE3 or P_SSSE3 or P_SSE4 or P_AVX
NO_OPPRFX		equ P_MMX or P_SSEALL
P_FPU_MASK		equ 0007h
P_CPU_MASK		equ 00F0h
P_EXT_MASK		equ P_MMX or P_K3D or P_SSEALL
P_EXT_ALL		equ P_MMX or P_K3D or P_SSEALL

; the MASM compatible @CPU value flags:
;
M_8086			equ 0001h	; 8086
M_186			equ 0002h	; 186
M_286			equ 0004h	; 286
M_386			equ 0008h	; 386
M_486			equ 0010h	; 486
M_586			equ 0020h	; Pentium
M_686			equ 0040h	; PPro
M_CPUMSK		equ 007Fh	;
M_PROT			equ 0080h	; protected instructions ok
M_8087			equ 0100h	; 8087
M_287			equ 0400h	; 287
M_387			equ 0800h	; 387

USE_EMPTY		equ 0FEh	; don't change values of USE16,USE32,USE64!
USE16			equ 0
USE32			equ 1
USE64			equ 2

; fastcall types. if order is to be changed or entries
; added, also adjust tables in proc.c, mangle.c and probably invoke.c!
;
FCT_MSC			equ 0	; MS 16-/32-bit fastcall (ax,dx,cx / ecx,edx)
FCT_WATCOMC		equ 1	; OW register calling convention (eax, ebx, ecx, edx)
FCT_WIN64		equ 2	; Win64 fastcall convention (rcx, rdx, r8, r9)
FCT_ELF64		equ 3	; Linux 64 syscall
FCT_VEC32		equ 4
FCT_VEC64		equ 5

STDCALL_FULL		equ 0
STDCALL_NONE		equ 1
STDCALL_HALF		equ 2

; file extensions. Order must match first entries in enum opt_names!
;
ASM			equ 0	; must be first; see SetFilenames() in assembly.asm
OBJ			equ 1
LST			equ 2
ERR			equ 3
NUM_FILE_TYPES		equ 4

OPTN_ASM_FN		equ 0	; first 4 entries must match enum file_extensions!
OPTN_OBJ_FN		equ 1	; -Fo option
OPTN_LST_FN		equ 2	; -Fl option
OPTN_ERR_FN		equ 3	; -Fr option
OPTN_LNKDEF_FN		equ 4	; -Fd option
OPTN_MODULE_NAME	equ 5	; -nm option
OPTN_TEXT_SEG		equ 6	; -nt option
OPTN_DATA_SEG		equ 7	; -nd option
OPTN_CODE_CLASS		equ 8	; -nc option
OPTN_LAST		equ 9

; queues to store multiple cmdline switch values
;
OPTQ_FINCLUDE		equ 0	; -Fi option values
OPTQ_MACRO		equ 1	; -D option values
OPTQ_INCPATH		equ 2	; -I option values
OPTQ_LAST		equ 3

PEM_DEFAULT		equ 0	; must be value 0
PEM_MACRO		equ 1
PEM_NONE		equ 2

STACK_NEAR		equ 0	; Stack distance
STACK_FAR		equ 1

OPSYS_DOS		equ 0	; Type of operating system
OPSYS_OS2		equ 1

OT_GROUP		equ 0	; OFFSET:GROUP (default, must be 0)
OT_FLAT			equ 1	; OFFSET:FLAT
OT_SEGMENT		equ 2	; OFFSET:SEGMENT

LOF_LISTED		equ 1	; line written to .LST file
LOF_SKIPPOS		equ 2	; suppress setting list_pos

; flags for win64_flags
;
W64F_SAVEREGPARAMS	equ 1	; 1=save register params in shadow space on proc entry
W64F_AUTOSTACKSP	equ 2	; 1=calculate required stack space for arguments of INVOKE
W64F_STACKALIGN16	equ 4	; 1=stack variables are 16-byte aligned; added in v2.12
W64F_ALL		equ W64F_SAVEREGPARAMS or W64F_AUTOSTACKSP or W64F_STACKALIGN16

; codeview debug info extend
;
CVEX_MIN		equ 0	; globals
CVEX_REDUCED		equ 1	; globals and locals
CVEX_NORMAL		equ 2	; globals, locals and types
CVEX_MAX		equ 3	; globals, locals, types and constants

CVO_STATICTLS		equ 1	; option flags: handle static tls

SEGTYPE_UNDEF		equ 0
SEGTYPE_CODE		equ 1
SEGTYPE_DATA		equ 2
SEGTYPE_BSS		equ 3
SEGTYPE_STACK		equ 4
SEGTYPE_ABS		equ 5
SEGTYPE_HDR		equ 6	; only used in bin.c for better sorting
SEGTYPE_CDATA		equ 7	; "
SEGTYPE_RELOC		equ 8	; "
SEGTYPE_RSRC		equ 9	; "
SEGTYPE_ERROR		equ 10	; must be last - an "impossible" segment type

OP_NONE			equ 0x00000000
OP_R8			equ 0x00000001
OP_R16			equ 0x00000002
OP_R32			equ 0x00000004
OP_R64			equ 0x00000008
OP_XMM			equ 0x00000010
OP_YMM			equ 0x00000020
OP_ZMM			equ 0x00000040
OP_A			equ 0x00000080
OP_M08			equ 0x00000100
OP_M16			equ 0x00000200
OP_M32			equ 0x00000400
OP_M64			equ 0x00000800
OP_M128			equ 0x00001000
OP_M256			equ 0x00002000
OP_M512			equ 0x00004000
OP_MMX			equ 0x00008000
OP_I8			equ 0x00010000
OP_I16			equ 0x00020000
OP_I32			equ 0x00040000
OP_I64			equ 0x00080000
OP_K			equ 0x00100000
OP_M48			equ 0x00200000
OP_M80			equ 0x00400000
OP_CL_ONLY		equ 0x00800000
OP_DX_ONLY		equ 0x01000000
OP_RSPEC		equ 0x02000000
OP_SR86			equ 0x04000000
OP_SR386		equ 0x08000000
OP_ST			equ 0x10000000
OP_ST_REG		equ 0x20000000
OP_I48			equ 0x40000000

OP_AL			equ OP_A or OP_R8
OP_AX			equ OP_A or OP_R16
OP_EAX			equ OP_A or OP_R32
OP_RAX			equ OP_A or OP_R64
OP_CL			equ OP_CL_ONLY or OP_R8
OP_DX			equ OP_DX_ONLY or OP_R16
OP_RGT8			equ OP_R16 or OP_R32 or OP_R64
OP_RGT16		equ OP_R32 or OP_R64
OP_R			equ OP_R8 or OP_R16 or OP_R32 or OP_R64
OP_SR			equ OP_SR86 or OP_SR386
OP_STI			equ OP_ST or OP_ST_REG
OP_I_1			equ 00200000h or OP_I8
OP_I_3			equ 00400000h or OP_I8
OP_I8_U			equ 00800000h or OP_I8 or OP_I16 or OP_I32
OP_I			equ OP_I8 or OP_I16 or OP_I32
OP_IGE8			equ OP_I8 or OP_I16 or OP_I32
OP_IGE16		equ OP_I16 or OP_I32
OP_I_ANY		equ OP_I or OP_I64 or OP_I48
OP_MGT8			equ OP_M16 or OP_M32 or OP_M64
OP_MGT16		equ OP_M32 or OP_M64
OP_MFPTR		equ OP_M32 or OP_M48 or OP_M80
OP_M_ANY		equ OP_M08 or OP_M16 or OP_M32 or OP_M64 or OP_M128 or OP_M256 or OP_M48 or OP_M80
OP_M			equ OP_M08 or OP_M16 or OP_M32 or OP_M64 or OP_M80 or OP_M128
OP_MS			equ OP_M08 or OP_M16 or OP_M32 or OP_M64

OP3_NONE		equ 0
OP3_CL			equ 1
OP3_I8_U		equ 2
OP3_XMM0		equ 3
OP3_I			equ 4
OP3_HID			equ 5
OP3_XMM			equ OP3_XMM0
OP3_YMM			equ OP3_XMM0

SYM_UNDEFINED		equ 0
SYM_INTERNAL		equ 1
SYM_EXTERNAL		equ 2
SYM_SEG			equ 3
SYM_GRP			equ 4
SYM_STACK		equ 5
SYM_STRUCT_FIELD	equ 6
SYM_TYPE		equ 7
SYM_ALIAS		equ 8
SYM_MACRO		equ 9
SYM_TMACRO		equ 10
SYM_CLASS_LNAME		equ 11

MT_SIZE_MASK		equ 1Fh
MT_FLOAT		equ 20h
MT_SIGNED		equ 40h
MT_BYTE			equ 1 - 1
MT_SBYTE		equ MT_BYTE or MT_SIGNED
MT_WORD			equ 2 - 1
MT_SWORD		equ MT_WORD or MT_SIGNED
MT_REAL2		equ MT_WORD or MT_FLOAT
MT_DWORD		equ 4 - 1
MT_SDWORD		equ MT_DWORD or MT_SIGNED
MT_REAL4		equ MT_DWORD or MT_FLOAT
MT_FWORD		equ 6 - 1
MT_QWORD		equ 8 - 1
MT_SQWORD		equ MT_QWORD or MT_SIGNED
MT_REAL8		equ MT_QWORD or MT_FLOAT
MT_TBYTE		equ 10 - 1
MT_REAL10		equ MT_TBYTE or MT_FLOAT
MT_OWORD		equ 16 - 1
MT_REAL16		equ MT_OWORD or MT_FLOAT
MT_YWORD		equ 32 - 1
MT_ZWORD		equ 64 - 1
MT_YMMWORD		equ 32 - 1
MT_ZMMWORD		equ 64 - 1
MT_PROC			equ 080h
MT_NEAR			equ 081h
MT_FAR			equ 082h
MT_EMPTY		equ 0C0h
MT_BITS			equ 0C1h
MT_PTR			equ 0C3h
MT_TYPE			equ 0C4h
MT_SPECIAL		equ 080h
MT_SPECIAL_MASK		equ 0C0h
MT_ADDRESS		equ 080h

IS_SIGNED macro x
    mov al,x
    and al,MT_SPECIAL_MASK
    .if al == MT_SIGNED
	mov eax,1
    .else
	xor eax,eax
    .endif
    exitm<eax>
    endm

TYPE_NONE		equ 0
TYPE_STRUCT		equ 1
TYPE_UNION		equ 2
TYPE_TYPEDEF		equ 3
TYPE_RECORD		equ 4

TAB_UNDEF		equ 0
TAB_EXT			equ 1
TAB_SEG			equ 2
TAB_GRP			equ 3
TAB_PROC		equ 4
TAB_ALIAS		equ 5
TAB_LAST		equ 6

no_RM			equ 1
no_WDS			equ 2
R_in_OP			equ 3

AP_LOCK			equ 1
AP_REP			equ 2
AP_REPxx		equ 3
AP_FWAIT		equ 4
AP_NO_FWAIT		equ 5

RWT_REG			equ 2
RWT_DIRECTIVE		equ 3
RWT_UNARY_OP		equ 4
RWT_BINARY_OP		equ 5
RWT_STYPE		equ 6
RWT_RES_ID		equ 7

SFR_SIZMSK		equ 1Fh
SFR_IREG		equ 20h
SFR_SSBASED		equ 40h

REX_B			equ 1
REX_X			equ 2
REX_R			equ 4
REX_W			equ 8

DF_CEXPR		equ 01h
DF_STRPARM		equ 02h
DF_NOEXPAND		equ 04h
DF_LABEL		equ 08h
DF_NOSTRUC		equ 10h
DF_NOCONCAT		equ 20h
DF_PROC			equ 40h
DF_STORE		equ 80h
DF_CGEN			equ 100h

DRT_CONDDIR		equ 0
DRT_LOOPDIR		equ 1
DRT_PURGE		equ 2
DRT_INCLUDE		equ 3
DRT_MACRO		equ 4
DRT_CATSTR		equ 5
DRT_SUBSTR		equ 6
DRT_MACINT		equ 7
DRT_DATADIR		equ 8
DRT_END			equ 9
DRT_ERRDIR		equ 10
ifndef __ASMC64__
DRT_CPU			equ 11
DRT_LISTING		equ 12
DRT_LISTMAC		equ 13
DRT_SEGORDER		equ 14
DRT_SIMSEG		equ 15
DRT_HLLSTART		equ 16
DRT_HLLEXIT		equ 17
DRT_HLLEND		equ 18
DRT_STARTEXIT		equ 19
DRT_MODEL		equ 20
DRT_RADIX		equ 21
DRT_SAFESEH		equ 22
DRT_INSTR		equ 23
DRT_SIZESTR		equ 24
DRT_EXCFRAME		equ 25
DRT_STRUCT		equ 26
DRT_TYPEDEF		equ 27
DRT_RECORD		equ 28
DRT_COMM		equ 29
DRT_EXTERN		equ 30
DRT_EXTERNDEF		equ 31
DRT_PROTO		equ 32
DRT_PUBLIC		equ 33
DRT_PROC		equ 34
DRT_ENDP		equ 35
DRT_LOCAL		equ 36
DRT_INVOKE		equ 37
DRT_ORG			equ 38
DRT_ALIGN		equ 39
DRT_SEGMENT		equ 40
DRT_ENDS		equ 41
DRT_GROUP		equ 42
DRT_ASSUME		equ 43
DRT_LABEL		equ 44
DRT_ALIAS		equ 45
DRT_ECHO		equ 46
DRT_EQU			equ 47
DRT_EQUALSGN		equ 48
DRT_INCBIN		equ 49
DRT_INCLIB		equ 50
DRT_NAME		equ 51
DRT_OPTION		equ 52
DRT_CONTEXT		equ 53
DRT_HLLFOR		equ 54
DRT_SWITCH		equ 55
DRT_ASSERT		equ 56
DRT_UNDEF		equ 57
DRT_CLASSDEF		equ 58
DRT_PRAGMA		equ 59
else
DRT_LISTING		equ 11
DRT_LISTMAC		equ 12
DRT_SEGORDER		equ 13
DRT_SIMSEG		equ 14
DRT_HLLSTART		equ 15
DRT_HLLEXIT		equ 16
DRT_HLLEND		equ 17
DRT_RADIX		equ 18
DRT_SAFESEH		equ 19
DRT_INSTR		equ 20
DRT_SIZESTR		equ 21
DRT_EXCFRAME		equ 22
DRT_STRUCT		equ 23
DRT_TYPEDEF		equ 24
DRT_RECORD		equ 25
DRT_COMM		equ 26
DRT_EXTERN		equ 27
DRT_EXTERNDEF		equ 28
DRT_PROTO		equ 29
DRT_PUBLIC		equ 30
DRT_PROC		equ 31
DRT_ENDP		equ 32
DRT_LOCAL		equ 33
DRT_INVOKE		equ 34
DRT_ORG			equ 35
DRT_ALIGN		equ 36
DRT_SEGMENT		equ 37
DRT_ENDS		equ 38
DRT_GROUP		equ 39
DRT_ASSUME		equ 40
DRT_LABEL		equ 41
DRT_ALIAS		equ 42
DRT_ECHO		equ 43
DRT_EQU			equ 44
DRT_EQUALSGN		equ 45
DRT_INCBIN		equ 46
DRT_INCLIB		equ 47
DRT_NAME		equ 48
DRT_OPTION		equ 49
DRT_CONTEXT		equ 50
DRT_HLLFOR		equ 51
DRT_SWITCH		equ 52
DRT_ASSERT		equ 53
DRT_UNDEF		equ 54
DRT_CLASSDEF		equ 55
DRT_PRAGMA		equ 56
endif

CSF_GRPCHK		equ 1

CSI_TEXT		equ 0
CSI_DATA		equ 1
CSI_CONST		equ 2
CSI_BSS			equ 3

BLOCK_ACTIVE		equ 0
BLOCK_INACTIVE		equ 1
BLOCK_DONE		equ 2

SIT_FILE		equ 0
SIT_MACRO		equ 1
if 1
input_status		STRUC
token_stringbuf		string_t ?
currsource		string_t ?
CurrComment		string_t ?
token_count		int_t ?
line_flags		char_t ? ; v2.08: added
input_status		ENDS
LPINPUT			TYPEDEF PTR input_status

PushInputStatus		proto :LPINPUT
PopInputStatus		proto :LPINPUT
endif
qditem			STRUC
next			ptr_t ?
size			uint_t ?
qditem			ends

dll_desc		STRUC
next			ptr_t ?
cnt			int_t ?
dname			db ?
dll_desc		ENDS

qnode			STRUC
next			ptr_t ?
union
    elmt		ptr_t ?
    sym			ptr_t ?
ends
qnode			ENDS

qitem			STRUC
next			ptr_t ?
value			db ?
qitem			ENDS

qdesc			STRUC
head			ptr_t ?
tail			ptr_t ?
qdesc			ENDS

src_item		STRUC
next			ptr_t ?
type			dw ?	; item type ( see enum src_item_type )
srcfile			dw ?	; index of file in ModuleInfo.FNames
union
    content		ptr_t ? ; generic
    file		ptr_t ? ; if item is a file
    mi			ptr_t ? ; if item is a macro
ends
line_num		uint_t ? ; current line #
src_item		ENDS

format_options		STRUC
init			ptr_t ?
invalid_fixup_type	dw ?
formatname		db 6 dup(?)
format_options		ENDS

debug_info		STRUC
start_line		dd ?
end_line		dd ?
ln_fileofs		dd ?
line_numbers		dw ?
file			dw ?
next_proc		dd ?
next_file		dd ?
debug_info		ENDS

asym_t			typedef ptr asym
func_ptr_t		typedef proto :ptr macro_instance, :string_t, :tok_t
func_ptr_p		typedef ptr func_ptr_t
internal_func_t		typedef proto :asym_t, :ptr_t
internal_func		typedef ptr internal_func_t

asym_r0 record \
    asym_method:1,	; v2.27: ptr is a class method
    asym_included:1,	; COFF: static symbol added to public queue. ELF:symbol added to symbol table (SYM_INTERNAL)
    asym_fwdref:1,	; symbol was forward referenced
    asym_issaved:1,	; assembly-time variables only: symbol has been saved
    asym_isproc:1,	; symbol is PROC or PROTO; has proc_info extension
    asym_isdata:1,	; field first_size is valid
    asym_isarray:1,	; symbol is an array (total_length is valid)
    asym_list:1,	; symbol is to be listed
    asym_ispublic:1,	; symbol has been added to the publics queue
    asym_variable:1,	; symbol is variable (defined by '=' directive)
    asym_predefined:1,	; symbol is predefined
    asym_isequate:1,	; symbol has been defined with EQU
    asym_iat_used:1,	; v2.07: IAT entry of symbol used (SYM_EXTERNAL + isproc==1 only)
    asym_scoped:1,	; symbol is local label or SYM_STACK
    asym_isdefined:1,	; symbol is "defined" in this pass
    asym_used:1		; symbol has been referenced

asym_r1 record \
    asym_is_vararg:1,	; SYM_STACK, VARARG param
    asym_isfar:1,	; SYM_EXTERNAL, SYM_TYPE, SYM_STACK
    asym_weak:1,	; 1 if an unused "externdef"
    asym_iscomm:1,	; is communal
    asym_seg_ofssize:2	; SYM_EXTERNAL only

asym_r2 record \
    asym_purged:1,	; macro has been PURGEd
    asym_mac_multiline:1,; v2.11: vararg arguments may be on multiple lines
    asym_label:1,	; macro is "label-aware"
    asym_isfunc:1,	; it's a macro function
    asym_mac_vararg:1	; accept additional params

asym struct

 ;; v2.11: name changed from 'next' to 'nextitem'

 nextitem		asym_t ?	; next symbol in hash line
 name			string_t ?	; symbol name
 union
    _offset		int_t ?		; used by SYM_INTERNAL (labels), SYM_TYPE,
					; SYM_STACK, v2.11: SYM_SEG
    value		int_t ?		; used by SYM_INTERNAL (equates)
    uvalue		uint_t ?	; v2.01: equates (they are 33-bit!)
    string_ptr		string_t ?	; used by SYM_TMACRO
    substitute		asym_t ?	; v2.04b: used by SYM_ALIAS
    func_ptr		func_ptr_p ?	; used by SYM_MACRO if predefined==1
    class_lname_idx	int_t ?		; used by SYM_CLASS_LNAME
 ends
 _segment		asym_t ?
 state			db ?
 mem_type		db ?
 union
  r0			asym_r0 <>
  SFL_USED		equ 0x0001
  SFL_ISDEFINED		equ 0x0002
  SFL_SCOPED		equ 0x0004
  SFL_IAT_USED		equ 0x0008
  SFL_ISEQUATE		equ 0x0010
  SFL_PREDEFINED	equ 0x0020
  SFL_VARIABLE		equ 0x0040
  SFL_ISPUBLIC		equ 0x0080
  SFL_LIST		equ 0x0100
  SFL_ISARRAY		equ 0x0200
  SFL_ISDATA		equ 0x0400
  SFL_ISPROC		equ 0x0800
  SFL_ISSAVED		equ 0x1000
  SFL_FWDREF		equ 0x2000
  SFL_INCLUDED		equ 0x4000
  SFL_METHOD		equ 0x8000
  flag			dw ?	; bitfield
 ends
 union
    first_size		dd ?
    struct
	Ofssize		db ?
	is_ptr		db ?
	union
	    ptr_memtype db ?
	    asmpass	db ?
	ends
	union
	 r1		asym_r1 <>
	 SINT_SEGOFSSIZE equ 03h
	 SINT_ISCOM	equ 04h
	 SINT_WEAK	equ 08h
	 SINT_ISFAR	equ 10h
	 SINT_ISVARARG	equ 20h
	 sint_flag	db ?
	ends
    ends
    union
     r2			asym_r2 <>
     SMAC_ISVARARG	equ 01h
     SMAC_ISFUNC	equ 02h
     SMAC_ALABEL	equ 04h
     SMAC_MULTILINE	equ 08h
     SMAC_PURGED	equ 10h
     mac_flag		dd ?	; --byte
    ends
 ends
 union
    first_length	dword ?
    max_mbr_size	dword ?
    target_type		asym_t ?
 ends
    regist		dw 2 dup(?)
 union
    total_size		dword ?
    value3264		int_t ?
    dll			ptr_t ? ; struct dll_desc *
    max_offset		int_t ?
 ends
 union
    total_length	dd ?
    altname		asym_t ? ; SYM_EXTERNAL (comm==0): alternative name
    debuginfo		ptr_t ?
    sfunc_ptr		internal_func ?
    struct
	cvtyperef	dw ?
	typekind	dw ?
    ends
 ends
 name_size		dw ?
 langtype		dw ?
 type			asym_t ?
 union
    bp_fixup		ptr_t ? ; fixup *
    ext_idx		dd ?
    struct
	ext_idx1	dw ?
	ext_idx2	dw ?
    ends
 ends
asym			ENDS

_asym_state macro reg:=<eax>
    exitm<[reg].asym.state>
    endm
_asym_name macro reg:=<eax>
    exitm<[reg].asym.name>
    endm
_asym_mem_type macro reg:=<eax>
    exitm<[reg].asym.mem_type>
    endm
_asym_type macro reg:=<eax>
    exitm<[reg].asym.type>
    endm
_asym_target_type macro reg:=<eax>
    exitm<[reg].asym.target_type>
    endm
_asym_typekind macro reg:=<eax>
    exitm<[reg].asym.typekind>
    endm

seg_item		STRUC
 next			ptr_t ?
 iseg			ptr_t ?
seg_item		ENDS

grp_info		STRUC
 seglist		ptr_t ?
 grp_idx		dd ?
 lname_idx		dd ?
 numseg			dd ?
grp_info		ENDS
grp_t			typedef ptr grp_info

seg_info		STRUC
 sgroup			asym_t ?
 start_loc		dd ?
 union
    current_loc		dd ?
    reloc_offset	dd ?
    start_offset	dd ?
 ends
 CodeBuffer		ptr_t ?
 bytes_written		dd ?
 union
    label_list		asym_t ?
    flushfunc		ptr_t ?
 ends
 struct
    head		ptr_t ?
    tail		ptr_t ?
 ends
 union
    LinnumQueue		ptr_t ?
    fileoffset		dd ?
    num_linnums		dd ?
 ends
 num_relocs		dd ?
 seg_idx		dd ?
 segtype		dd ?
 lname_idx		dd ?
 clsym			asym_t ?
 union
    abs_frame		dd ?
    comdat_number	dd ?
    comdat_idx		dd ?
 ends
 union
    abs_offset		dd ?
    aliasname		string_t ?
 ends
 Ofssize		db ?
 characteristics	db ?
 alignment		db ?
 readonly		db ?
 info			db ?
 force32		db ?
 data_in_code		db ?
 internal		db ?
 written		db ?
 linnum_init		db ?
 combine		db ?
 comdat_selection	db ?
seg_info		ENDS
seg_t			typedef ptr seg_info

mparm_list		STRUC
 deflt			string_t ?
 required		db ?
mparm_list		ENDS

srcline			STRUC
 next			ptr_t ?
 ph_count		db ?
 line1			db ?
srcline			ENDS

macro_info		STRUC
 parmcnt		dw ?
 union
    localcnt		dw ?
    autoexp		dw ?
 ends
 parmlist		ptr_t ?
 datap			ptr_t ?
 srcfile		dd ?
macro_info		ENDS
macro_t			typedef ptr macro_info

sfield			STRUC
 sym			asym <>
 next			ptr_t ?
 ivalue			db ?
sfield			ENDS
LPSFIELD		typedef ptr sfield

struct_info		STRUC
 head			LPSFIELD ?
 tail			LPSFIELD ?
 alignment		db ?
 flags			db ?
 STINF_ISINLINE		equ 1
 STINF_ISOPEN		equ 2
 STINF_ORGINSIDE	equ 4
struct_info		ENDS
struct_t		typedef ptr struct_info

dsym_t			typedef ptr dsym

proc_info_r0		record	fpo:1,
				isframe:1,
				stackparam:1,
				loadds:1,
				forceframe:1,
				isexport:1,
				pe_type:1,
				has_vararg:1

proc_info		STRUC
 regslist		LPWORD ?
 paralist		dsym_t ?
 locallist		dsym_t ?
 labellist		dsym_t ?
 parasize		dd ?
 localsize		dd ?
 prologuearg		string_t ?
 exc_handler		asym_t ?
 ReservedStack		int_t ?
 prolog_list_pos	uint_t ?
 union
  flags			db ?
  PINF_HAS_VARARG	equ 01h
  PINF_PE_TYPE		equ 01h
  PINF_ISEXPORT		equ 02h
  PINF_FORCEFRAME	equ 04h
  PINF_LOADDS		equ 08h
  PINF_STACKPARAM	equ 10h
  PINF_ISFRAME		equ 20h
  PINF_FPO		equ 40h
  r0			proc_info_r0 <>
 ends
 size_prolog		db ?
 basereg		dw ?
proc_info		ENDS
proc_t			typedef ptr proc_info

dsym			STRUC
 sym			asym <>
 union
  seginfo		seg_t ?
  grpinfo		grp_t ?
  procinfo		proc_t ?
  structinfo		struct_t ?
  macroinfo		macro_t ?
  nextll		dsym_t ?
 ends
 next			dsym_t ?
 union
  prev			dsym_t ?
  nextproc		dsym_t ?
  nextlocal		dsym_t ?
  nextparam		dsym_t ?
 ends
dsym			ENDS

symbol_queue		STRUC
 head			ptr_t ?
 tail			ptr_t ?
symbol_queue		ENDS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EXPR_EMPTY	equ EMPTY
EXPR_ERROR	equ ERROR	; undefined type when error occures or result is undefined
EXPR_CONST	equ 0		; constant; note that "label1 - label2" -> constant
EXPR_ADDR	equ 1		; e.g. "foo", "seg foo" and "offset foo", also indirect mem ops
EXPR_REG	equ 2		; register
EXPR_FLOAT	equ 3		; v2.05: float

EXPF_NOERRMSG	equ 1		; suppress error messages
EXPF_NOUNDEF	equ 2		; don't accept or create undefined symbols
EXPF_ONEOPND	equ 4		; private flag, used inside expreval.c only
EXPF_IN_SQBR	equ 8		; private flag, used inside expreval.c only

expr_r0 record	is_dot:1,	; v2.10: see regression test dotop5.asm
		assumecheck:1,	; v2.07: for ASSUMEd std registers
		negative:1,	; for EXPR_FLOAT only
		is_opattr:1,	; current operator is OPATTR
		is_type:1,	; constant is a type
		is_abs:1,	; external ABS
		explicit:1,	; Whether expression type explicitly given (to be removed!)
		indirect:1	; indirect addressing used

expr			STRUC
 union				; value of expression
    struct
     value		int_t ?
     hvalue		int_t ?
    ends
    struct
     llvalue		dq ?
     hlvalue		dq ?
    ends
    uvalue		dword ?
    value64		sqword ?
    dvalue		REAL8 ?
    fvalue		REAL4 ?
    st_idx		int_t ? ; EXPR_REG: index if reg is ST
    chararray		db 16 dup(?)
 ends
 union
    quoted_string	tok_t ? ; for EXPR_CONST + quoted strings only
    float_tok		tok_t ? ; for EXPR_FLOAT only
 ends
 base_reg		tok_t ? ; EXPR_ADDR: base register token
				; EXPR_REG: register token
 idx_reg		tok_t ? ; EXPR_ADDR: index register token
 union
    label_tok		tok_t ? ; token holding the label (EXPR_ADDR, used for overrides, inside expreval only)
    type_tok		tok_t ? ; v2.10: token if target type of a label (SYM_STACK, MT_PTR) is to be stored
 ends
 override		tok_t ? ; EXPR_ADDR: token holding the override label or segment register
 inst			int_t ? ; operator token
 kind			int_t ? ; Type of expression
 mem_type		db ?	;
 scale			db ?	; EXPR_ADDR: scaling factor 1, 2, 4, or 8 - 386 code only
 Ofssize		db ?	; 16,32,64 bit if MT_NEAR, MT_FAR
 union
  flags1		db ?	; bit-flag
  EXF_INDIRECT		equ 01h ; indirect addressing used
  EXF_EXPLICIT		equ 02h ; Whether expression type explicitly given (to be removed!)
  EXF_IS_ABS		equ 04h ; external ABS
  EXF_IS_TYPE		equ 08h ; constant is a type
  EXF_IS_OPEATTR	equ 10h ; current operator is OPATTR
  EXF_NEGATIVE		equ 20h ; for EXPR_FLOAT only
  EXF_ASSUMECHECK	equ 40h ; v2.07: for ASSUMEd std registers
  EXF_IS_DOT		equ 80h ; v2.10: see regression test dotop5.asm
  r0			expr_r0 <>
 ends
 sym			asym_t ?; label used
 mbr			asym_t ?; struct member
 type			asym_t ?; for DOT operator. Must be last (see TokenAssign)!
expr			ENDS
expr_t			typedef ptr expr

; special_item is the structure used to store directives and
; other reserved words in SpecialTable (special.h).

special_item		STRUC
value			dd ?
sflags			dd ?
cpu			dw ?
bytval			db ?
type			db ?
special_item		ENDS
externdef		SpecialTable:special_item

GetRegNo macro x
	 imul eax,x,sizeof(special_item)
	 exitm<SpecialTable[eax].bytval>
	 endm
GetSflagsSp macro x
	 imul eax,x,sizeof(special_item)
	 exitm<SpecialTable[eax].sflags>
	 endm
GetValueSp macro x
	 imul eax,x,sizeof(special_item)
	 exitm<SpecialTable[eax].value>
	 endm
GetMemtypeSp macro x
	 imul eax,x,sizeof(special_item)
	 exitm<SpecialTable[eax].bytval>
	 endm
GetCpuSp macro x
	 imul eax,x,sizeof(special_item)
	 exitm<SpecialTable[eax].cpu>
	 endm

global_options		STRUC
quiet			db ?	; -q option
line_numbers		db ?	; -Zd option
debug_symbols		db ?	; -Zi option
debug_ext		db ?	; -Zi option numeric argument
floating_point		dd ?	; -FPi, -FPi87
error_limit		dd ?	; -e option
no_error_disp		db ?	; -eq option
warning_level		db ?	; -Wn option
warning_error		db ?	; -WX option
process_subdir		db ?	; -r option
names			string_t OPTN_LAST dup(?) ; char *  4
queues			ptr_t OPTQ_LAST dup(?)	; qitem * 4
no_comment_in_code_rec	db ?	; -zlc option
no_opt_farcall		db ?	; -zld option
no_file_entry		db ?	; -zlf option
no_static_procs		db ?	; -zlp option
no_section_aux_entry	db ?	; -zls option
no_cdecl_decoration	db ?	; -zcw & -zcm option
stdcall_decoration	db ?	; -zt<0|1|2> option
no_export_decoration	db ?	; -zze option
entry_decorated		db ?	; -zzs option
write_listing		db ?	; -Fl option
write_impdef		db ?	; -Fd option
case_sensitive		db ?	; -C<p|x|u> options
convert_uppercase	db ?	; -C<p|x|u> options
preprocessor_stdout	db ?	; -EP option
masm51_compat		db ?	; -Zm option
strict_masm_compat	db ?	; -Zne option
masm_compat_gencode	db ?	; -Zg option
masm8_proc_visibility	db ?	; -Zv8 option
listif			db ?	; -Sx, -Sa option
list_generated_code	db ?	; -Sg, -Sa option
list_macro		dd ?	; -Sa option
no_symbol_listing	db ?	; -Sn option
first_pass_listing	db ?	; -Sf option
all_symbols_public	db ?	; -Zf option
safeseh			db ?	; -safeseh option
output_format		dd ?	; -bin, -omf, -coff, -elf options
sub_format		dd ?	; -mz, -pe, -win64, -elf64 options
langtype		dd ?	; -Gc|d|z option
_model			dd ?	; -mt|s|m|c|l|h|f option
cpu			dd ?	; -0|1|2|3|4|5|6 & -fp{0|2|3|5|6|c} option
fctype			dd ?	; -zf0 & -zf1 option
codepage		dd ?	; Unicode code page
ignore_include		db ?	; -X option
fieldalign		db ?	; -Zp option
syntax_check_only	db ?	; -Zs option
aflag			db ?	; asmc option
xflag			db ?	; extended option
loopalign		db ?	; OPTION:LOOPALIGN setting
casealign		db ?	; OPTION:CASEALIGN setting
epilogueflags		db ?	; OPTION EPILOGUE: FLAGS
segmentalign		db ?	; -Sp[n] Set segment alignment
pe_subsystem		db ?	; -cui, -gui
win64_flags		db ?	; -homeparams, -autostack, -stackalign
chkstack		db ?	; _chkstk()
nolib			db ?	; skip includelib directives
global_options		ENDS

PLPSTR			typedef PTR string_t
M_MODULEVARS		MACRO
error_count		dd ?		; total of errors so far
warning_count		dd ?		; total of warnings so far
num_segs		dd ?		; number of segments in module
PubQueue		qdesc <>	; PUBLIC items
Lnam			qdesc <>	; LNAME items (segments, groups and classes)
SafeSEHQueue		qdesc <>	; list of safeseh handlers
LibQueue		qdesc <>	; includelibs
DllQueue		ptr_t ?		; dlls of OPTION DLLIMPORT
imp_prefix		string_t ?		;
curr_file		ptr_t NUM_FILE_TYPES dup(?) ; ASM, ERR, OBJ and LST
curr_fname		string_t NUM_FILE_TYPES dup(?)
FNames			ptr_t ?		; array of input files
cnt_fnames		dd ?		; items in FNames array
IncludePath		string_t ?		;
line_queue		qdesc <>	; line queue
src_stack		ptr_t ?		; source item (files & macros) stack
union
 start_fixup		ptr_t ?		; OMF only
 start_label		ptr_t ?		; non-OMF only: start label
ends
start_displ		dd ?		; OMF only, optional displ for start label
StrStack		ptr_t ?		; v2.20 String stack
HllStack		ptr_t ?		; for .WHILE, .IF, .REPEAT
HllFree			ptr_t ?		; v2.06: stack of free <struct hll>-items
ComStack		ptr_t ?		; v2.27: .CLASSDEF, .COMDEF, .ENDS
RetStack		ptr_t ?		; v2.30: .return info
ContextStack		ptr_t ?
ContextFree		ptr_t ?		; v2.10: "free items" heap implemented.
SavedContexts		ptr_t ?
cntSavedContexts	dd ?
anonymous_label		dd ?		; "anonymous label" counter
StackBase		ptr_t ?
ProcStatus		ptr_t ?
WriteModule		ptr_t ?		; (*WriteModule)( struct module_info * );
EndDirHook		ptr_t ?		; (*EndDirHook) ( struct module_info * );
Pass1Checks		ptr_t ?		; (*Pass1Checks)( struct module_info * );
pe_flags		dd ?		; for PE
			ENDM

module_vars		STRUC
M_MODULEVARS
module_vars		ENDS

module_info		STRUC SIZE_T
M_MODULEVARS
proc_prologue		string_t ? ; prologue macro if PEM_MACRO
proc_epilogue		string_t ? ; epilogue macro if PEM_MACRO
CurrDll			ptr_t ? ; OPTION DLLIMPORT dll
fmtopt			ptr_t ? ; v2.07: added
hll_label		dd ?	; hll directive label counter
distance		db ?	; stack distance
_model			db ?	; memory model
langtype		db ?	; language
ostype			db ?	; operating system
sub_format		db ?	; sub-output format
fctype			db ?	; fastcall type
segorder		db ?	; .alpha, .seq, .dosseg
offsettype		db ?	; OFFSET:GROUP|FLAT|SEGMENT
cpu			dd ?	; cpu setting (value @cpu symbol);
curr_cpu		dd ?	; cpu setting (OW stylex);
radix			db ?	; current .RADIX setting
fieldalign		db ?	; -Zp, OPTION:FIELDALIGN setting
line_flags		db ?	; current line has been printed
procalign		db ?	; current OPTION:PROCALIGN setting
list_macro		dd ?	; current .LISTMACRO setting
Ofssize			db ?	; current offset size (USE16,USE32,USE64)
defOfssize		db ?	; default segment offset size (16,32 [,64]-bit)
wordsize		db ?	; current word size (2,4,8)
inside_comment		db ?	; v2.10: moved from tokenize.c
case_sensitive		db ?	; option casemap
convert_uppercase	db ?	; option casemap
procs_private		db ?	; option proc:private
procs_export		db ?	; option proc:export
dotname			db ?	; option dotname
ljmp			db ?	; option ljmp
m510			db ?	; option m510
scoped			db ?	; option scoped
oldstructs		db ?	; option oldstructs
emulator		db ?	; option emulator
setif2			db ?	; option setif2
list			db ?	; .list/.nolist
cref			db ?	; .cref/.nocref
listif			db ?	; .listif/.nolistif
list_generated_code	db ?	; .listall, -Sa, -Sg
StartupDirectiveFound	db ?	;
EndDirFound		db ?	;
frame_auto		db ?	; win64 only
NoSignExtend		db ?	; option nosignextend
aflag			db ?	; asmc option
union
 struct
  elf_osabi		db ?	; for ELF
  win64_flags		db ?	; for WIN64 + PE(32+)
 ends
 struct
  mz_ofs_fixups		dw ?	; for MZ
  mz_alignment		dw ?
  mz_heapmin		dw ?
  mz_heapmax		dw ?
 ends
ends
simseg_init		db ?	; simplified segm dir flags
simseg_defd		db ?	; v2.09: flag if seg was defined before simseg dir
PhaseError		db ?	; phase error flag
CommentDataInCode	db ?	; OMF: emit coment records about data in code segs
prologuemode		db ?	; current PEM_ enum value for OPTION PROLOGUE
epiloguemode		db ?	; current PEM_ enum value for OPTION EPILOGUE
invoke_exprparm		db ?	; flag: forward refs for INVOKE params ok?
cv_opt			db ?	; option codeview
srcfile			dd ?	; main source file - is an index for FNames[]
currseg			ptr_t ? ; currently active segment - dsym *
flat_grp		ptr_t ? ; magic FLAT group - dsym *
pCodeBuff		ptr_t ? ;
GeneratedCode		dd ?	; nesting level generated code
currsource		string_t ? ; current source line
CurrComment		string_t ? ; current comment
tokenarray		ptr_t ? ; start token buffer
stringbufferend		string_t ? ; start free space in string buffer
token_count		dd ?	; number of tokens in curr line
basereg			dd 3 dup(?)	; stack base register (16-, 32-, 64-bit
name			db 260 dup(?)	; name of module
xflag			db ?	; extended option
loopalign		db ?	; OPTION:LOOPALIGN setting
casealign		db ?	; OPTION:CASEALIGN setting
epilogueflags		db ?	; OPTION EPILOGUE: FLAGS
assert_proc		ptr_t ? ; .assert:<proc/macro name>
codepage		dd ?	;
class_label		dd ?	;
strict_masm_compat	db ?	; -Zne option
module_info		ENDS

Token_Count		equ <ModuleInfo.token_count>

equ_item		STRUC
next			ptr_t ?
sym			ptr_t ? ; asym *
lvalue			dd ?
hvalue			dd ?
mem_type		db ?
isdefined		db ?
equ_item		ENDS

line_t			typedef ptr line_item
line_item		STRUC
next			line_t ?
prev			line_t ?
lineno			int_t ? ; 20:12 = srcfile
srcfile			int_t ?
macro_level		int_t ?
list_pos		int_t ?
line			char_t 1 dup(?)
line_item		ENDS

mod_state		STRUC
init			dd ?
head			ptr_t ? ; equ_item *
tail			ptr_t ?
modinfo			db sizeof(module_info) - sizeof(module_vars) dup(?)
mod_state		ENDS

externdef		Parse_Pass	: DWORD
externdef		StoreState	: DWORD
externdef		UseSavedState	: DWORD
externdef		LineStoreCurr	: line_t
externdef		LineStore	: qdesc
externdef		NoLineStore	: DWORD
externdef		ModuleInfo	: module_info
externdef		Options		: global_options
externdef		write_to_file	: DWORD
externdef		SymTables	: symbol_queue	; * TAB_LAST
externdef		DefaultDir	: string_t		; * NUM_FILE_TYPES
externdef		MacroLevel	: DWORD
externdef		LinnumQueue	: qdesc
externdef		ModelToken	: string_t
externdef		LastCodeBufSize : DWORD
externdef		banner_printed	: DWORD
externdef		sym_ReservedStack:asym_t
externdef		stackreg	: dword
externdef		regax		: dword
externdef		CurrProc	: ptr
externdef		CurrStruct	: dsym_t

asmerr			proto :DWORD, :VARARG
DelayExpand		proto fastcall :DWORD ; :tok_t
AsmcKeywords		proto :int_t
GetStdAssume		proto :int_t
atofloat		proto :ptr, :ptr, :uint_t, :int_t, :byte

write_logo		proto
WriteError		proto

LclAlloc		proto fastcall :DWORD
MemAlloc		proto fastcall :DWORD

FastpassInit		proto
SegmentSaveState	proto
AssumeSaveState		proto
ContextSaveState	proto
StoreLine		proto :DWORD, :DWORD, :DWORD
SkipSavedState		proto
RestoreState		proto
SaveVariableState	proto :DWORD
FreeLineStore		proto

MemInit			proto
SymInit			proto
InputInit		proto
CondInit		proto
ExprEvalInit		proto
LstInit			proto
ResWordsInit		proto
InputPassInit		proto
LabelInit		proto
ProcInit		proto
TypesInit		proto
LinnumInit		proto

SegmentFini		proto
ResWordsFini		proto
InputFini		proto
LinnumFini		proto
MemFini			proto

HllCheckOpen		proto
CondCheckOpen		proto
SymSetCmpFunc		proto

SetCPU			proto :DWORD
AddLineQueueX		proto :DWORD, :VARARG
AddStringToIncludePath	proto :DWORD
SymFind			proto fastcall :string_t
SymCreate		proto :string_t
FindResWord		proto fastcall :string_t, :int_t

DisableKeyword		proto :DWORD
ParseLine		proto :DWORD
SearchFile		proto :DWORD, :DWORD
ProcessFile		proto :DWORD
ClearSrcStack		proto
PreprocessLine		proto :string_t, :tok_t

SymPassInit		proto :DWORD
SegmentInit		proto :DWORD
ContextInit		proto :DWORD
HllInit			proto :DWORD
ClassInit		proto
PragmaInit		proto
ClassCheckOpen		proto
PragmaCheckOpen		proto
MacroInit		proto :DWORD
AssumeInit		proto :DWORD
RunLineQueue		proto
set_curr_srcfile	proto :DWORD, :DWORD
SymMakeAllSymbolsPublic proto
sym_remove_table	proto :DWORD, :DWORD

store_fixup		proto :DWORD, :DWORD, :DWORD
Mangle			proto :DWORD, :DWORD
SetMangle		proto :DWORD, :DWORD, :DWORD

omf_FlushCurrSeg	proto
omf_OutSelect		proto :DWORD
omf_init		proto :DWORD
omf_set_filepos		proto

elf_init		proto :ptr	; module_info *
bin_init		proto :ptr	; module_info *
pe_create_PE_header	proto

coff_init		proto :ptr	; module_info *
GetLineNumber		proto

;-------------------------------------------------------------------------------
; list
;-------------------------------------------------------------------------------

LSTTYPE_DATA		equ 0
LSTTYPE_CODE		equ 1
LSTTYPE_EQUATE		equ 2
LSTTYPE_TMACRO		equ 3
LSTTYPE_DIRECTIVE	equ 4
LSTTYPE_MACRO		equ 5
LSTTYPE_STRUCT		equ 6
LSTTYPE_LABEL		equ 7
LSTTYPE_MACROLINE	equ 8

LstInit			proto
LstWriteSrcLine		proto
LstWriteCRef		proto
LstPrintf		proto _CDecl :DWORD, :VARARG
LstSetPosition		proto
LstNL			proto
LstWrite		proto :DWORD, :DWORD, :DWORD

;-------------------------------------------------------------------------------
; line_num
;-------------------------------------------------------------------------------

line_num_info		STRUC
next			ptr_t ? ; line_num_info *
number			dd ?	;
union
    _offset		dd ?
    line_number		dd ?	; :20, file:12;
ends
union
    srcfile		dd ?
    sym			asym_t ?
ends
line_num_info		ENDS

LinnumInit		proto
LinnumFini		proto
QueueDeleteLinnum	proto :DWORD	; qdesc *

_atoow			proto :string_t, :string_t, :int_t, :int_t

SizeFromMemtype		proto :BYTE, :int_t, :asym_t
GetSymOfssize		proto :asym_t
SizeFromRegister	proto :int_t

SearchNameInStruct	proto :asym_t, :string_t, :ptr int_t, :int_t
GetResWName		proto :uint_t, :string_t
CurrWordSize		equ <ModuleInfo.wordsize>

;-------------------------------------------------------------------------------
; Text macros
;-------------------------------------------------------------------------------

strlabel	proto :string_t, :uint_t
GetFNamePart	proto :string_t
GetExtPart	proto :string_t

M_SKIP_SPACE MACRO reg, base
	movzx reg,BYTE PTR [base]
	.while BYTE PTR _ltype[reg+1] & _SPACE
		add   base,1
		ifidni <reg>,<eax>
			mov   al,[base]
		else
		    ifidni <reg>,<ecx>
			mov   cl,[base]
		    else
			movzx reg,BYTE PTR [base]
		    endif
		endif
	.endw
	ENDM

M_SKIP_SPACE_R MACRO reg, base
	movzx reg,BYTE PTR [base]
	.while BYTE PTR _ltype[reg+1] & _SPACE
		sub   base,1
	    ifidni <reg>,<eax>
		mov   al,[base]
	    else
	     ifidni <reg>,<ecx>
		mov   cl,[base]
	     else
		movzx reg,BYTE PTR [base]
	     endif
	    endif
	.endw
	ENDM

M_EAT_SPACE MACRO reg, base
	M_SKIP_SPACE reg, base
	EXITM<reg>
	ENDM

M_EAT_SPACE_R MACRO reg, base
	M_SKIP_SPACE_R reg, base
	EXITM<reg>
	ENDM

cmprm macro src
    .if edx == dword ptr src[4]
	cmp eax,dword ptr src
    .endif
    endm

cmpmm macro des,src
    mov edx,dword ptr des[4]
    mov eax,dword ptr des
    cmprm src
    endm


.list

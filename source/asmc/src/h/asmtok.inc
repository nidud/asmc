ifndef __ASMTOK_INC
__ASMTOK_INC equ <>

; T_INSTRUCTION - T_RES_ID are reserved words.
; T_REG - T_RES_ID match RWT_REG - RWT_RES_ID

T_FINAL             equ 0
T_INSTRUCTION       equ 1
T_REG               equ 2
T_DIRECTIVE         equ 3
T_UNARY_OPERATOR    equ 4
T_BINARY_OPERATOR   equ 5
T_STYPE             equ 6
T_RES_ID            equ 7
T_ID                equ 8
T_STRING            equ 9
T_NUM               equ 10
T_FLOAT             equ 11
T_BAD_NUM           equ 12
T_DBL_COLON         equ 13
T_OP_BRACKET        equ '('
T_OP_SQ_BRACKET     equ '['
T_CL_BRACKET        equ ')'
T_CL_SQ_BRACKET     equ ']'
T_COMMA             equ ','
T_COLON             equ ':'
T_DOT               equ '.'
T_QUESTION_MARK     equ '?'
T_PERCENT           equ '%'

T_HLL_DELAY         equ 0x01    ; [0]: ELSEIF/WHILE/CASE
T_HLL_MACRO         equ 0x02    ; -- macro(args)
T_HLL_PROC          equ 0x04    ; -- proc(args)
T_HLL_DELAYED       equ 0x08    ; [0]: delayed
T_EVEX_OPT          equ 0x10    ; {T_STRING} -- {k1}{z}..
T_HLL_DBLCOLON      equ 0x20

TOK_DEFAULT         equ 0       ; default mode - handle conditional assembly
TOK_RESCAN          equ 1       ; retokenize after expansion - ignore conditional assembly
TOK_NOCURLBRACES    equ 2       ; don't handle {}-literals
TOK_LINE            equ 4       ; full line is retokenized

TF3_ISCONCAT        equ 1       ; line was concatenated
TF3_EXPANSION       equ 2       ; expansion operator % at pos 0

line_status         struc
input               LPSTR ?
output              LPSTR ?     ; free space in token string buffer
start               LPSTR ?     ; start of line
index               dd ?        ; index token array
flags               db ?        ; v2.08: added
flags2              db ?        ; v2.08: was global var g_flags
flags3              db ?        ; v2.08: added
line_status         ends

asmtok              struc
token               db ?
union
 dirtype            db ?        ; T_DIRECTIVE: type
 bytval             db ?        ; T_STYPE: memtype
 precedence         db ?        ; T_UNARY_OPERATOR/T_BINARY_OPERATOR
 string_delim       db ?        ; T_STRING: string delimiter
 floattype          db ?        ; T_FLOAT: 0 or 'r'
 numbase            db ?        ; T_NUM: number base
 specval            db ?        ; 1-byte special tokens: flags
ends
hll_flags           db ?        ; xx( if xx == macro/proc/label()
hll_index           db ?
union
    tokval          SINT ?      ; index if token is a reserved word
    stringlen       SINT ?      ; T_STRING: size
    idarg           SINT ?      ; T_ID: currently not used
    itemlen         SINT ?      ; T_NUM: size
    lastidx         SINT ?      ; T_FINAL: last index (used in RunMacro())
ends
string_ptr          LPSTR ?
tokpos              LPSTR ?     ; points to item in CurrSource
asmtok              ends
PTOKEN              typedef ptr asmtok

GetToken proto fastcall :ptr asmtok, :ptr line_status
Tokenize proto :LPSTR, :UINT, :ptr asmtok, :UINT

_tok_token macro reg:=<ebx>, id:=<0>
    exitm<[reg+(id)*16].asmtok.token>
    endm

_tok_dirtype macro reg:=<ebx>, id:=<0>
    exitm<[reg+(id)*16].asmtok.dirtype>
    endm

_tok_flags macro reg:=<ebx>, id:=<0>
    exitm<[reg+(id)*16].asmtok.hll_flags>
    endm

_tok_tokval macro reg:=<ebx>, id:=<0>
    exitm<[reg+(id)*16].asmtok.tokval>
    endm

_tok_string macro reg:=<ebx>, id:=<0>
    exitm<[reg+(id)*16].asmtok.string_ptr>
    endm

_tok_tokpos macro reg:=<ebx>, id:=<0>
    exitm<[reg+(id)*16].asmtok.tokpos>
    endm

endif
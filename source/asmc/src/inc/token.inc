; TOKEN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __TOKEN_INC
define __TOKEN_INC

; T_INSTRUCTION - T_RES_ID are reserved words.
; T_REG - T_RES_ID match RWT_REG - RWT_RES_ID

T_FINAL             equ 0
T_INSTRUCTION       equ 1       ; 1
T_REG               equ 2       ; 2 (==RWT_REG)
T_DIRECTIVE         equ 3       ; 3 (==RWT_DIRECTIVE)
T_UNARY_OPERATOR    equ 4       ; 4 (==RWT_UNARY_OP)
T_BINARY_OPERATOR   equ 5       ; 5 (==RWT_BINARY_OP)
T_STYPE             equ 6       ; 6 (==RWT_STYPE)
T_RES_ID            equ 7       ; 7 (==RWT_RES_ID)
T_ID                equ 8       ; 8
T_STRING            equ 9       ; 9
T_NUM               equ 10      ; A
T_FLOAT             equ 11      ; B
T_BAD_NUM           equ 12      ; C
T_DBL_COLON         equ 13      ; D

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

.template asm_tok watcall
    token               uchar_t ?
    union
     dirtype            uchar_t ?   ; T_DIRECTIVE: type
     bytval             uchar_t ?   ; T_STYPE: memtype
     precedence         uchar_t ?   ; T_UNARY_OPERATOR/T_BINARY_OPERATOR
     string_delim       char_t ?    ; T_STRING: string delimiter
     floattype          char_t ?    ; T_FLOAT: 0 or 'r'
     numbase            char_t ?    ; T_NUM: number base
     specval            char_t ?    ; 1-byte special tokens: flags
    ends
    hll_flags           uchar_t ?   ; xx( if xx == macro/proc/label()
    hll_index           uchar_t ?
    union
     tokval             uint_t ?    ; index if token is a reserved word
     stringlen          uint_t ?    ; T_STRING: size
     idarg              uint_t ?    ; T_ID: currently not used
     itemlen            uint_t ?    ; T_NUM: size
     lastidx            uint_t ?    ; T_FINAL: last index (used in RunMacro())
    ends
    string_ptr          string_t ?
    tokpos              string_t ?  ; points to item in CurrSource

   .inline tokptr :int_t {
        imul    edx,edx,asm_tok
        add     eax,edx
        }
   .ends
    token_t typedef ptr asm_tok

endif

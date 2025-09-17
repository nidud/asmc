; TOKEN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __TOKEN_INC
define __TOKEN_INC

; T_INSTRUCTION - T_RES_ID are reserved words.
; T_REG - T_RES_ID match RWT_REG - RWT_RES_ID

.enum tok_type {

    T_FINAL,
    T_INSTRUCTION,      ; 1
    T_REG,              ; 2 (==RWT_REG)
    T_DIRECTIVE,        ; 3 (==RWT_DIRECTIVE)
    T_UNARY_OPERATOR,   ; 4 (==RWT_UNARY_OP)
    T_BINARY_OPERATOR,  ; 5 (==RWT_BINARY_OP)
    T_STYPE,            ; 6 (==RWT_STYPE)
    T_RES_ID,           ; 7 (==RWT_RES_ID)
    T_ID,               ; 8
    T_STRING,           ; 9
    T_NUM,              ; A
    T_FLOAT,            ; B
    T_BAD_NUM,          ; C
    T_DBL_COLON,        ; D

    T_OP_BRACKET    = '(',
    T_OP_SQ_BRACKET = '[',
    T_CL_BRACKET    = ')',
    T_CL_SQ_BRACKET = ']',
    T_COMMA         = ',',
    T_COLON         = ':',
    T_DOT           = '.',
    T_QUESTION_MARK = '?',
    T_PERCENT       = '%',
    }

.template asm_tok
    token           uchar_t ?
    union
     dirtype        uchar_t ?   ; T_DIRECTIVE: type
     bytval         uchar_t ?   ; T_STYPE: memtype
     precedence     uchar_t ?   ; T_UNARY_OPERATOR/T_BINARY_OPERATOR
     string_delim   char_t ?    ; T_STRING: string delimiter
     floattype      char_t ?    ; T_FLOAT: 0 or 'r'
     numbase        char_t ?    ; T_NUM: number base
     specval        char_t ?    ; 1-byte special tokens: flags
    ends
    union
     flags          db ?        ; HLL flags
     record
      HllCode       db : 1 ?    ; Set in first token for HLL directives
      Delayed       db : 1 ?    ; Set in first token if expansion is delayed
      IsFunc        db : 1 ?    ; Macro()
      IsProc        db : 1 ?    ; Proc()
      Modifier      db : 1 ?    ; {k1}{z}..
      Operator      db : 1 ?    ; Operator expression
      Expand        db : 1 ?    ; class::proc()
      AtLabel       db : 1 ?    ; @label
     ends
    ends
    union
     tokval         uint_t ?    ; index if token is a reserved word
     stringlen      uint_t ?    ; T_STRING: size
     idarg          uint_t ?    ; T_ID: currently not used
     itemlen        uint_t ?    ; T_NUM: size
     lastidx        uint_t ?    ; T_FINAL: last index (used in RunMacro())
    ends
    string_ptr      string_t ?
    tokpos          string_t ?  ; points to item in CurrSource
   .ends
    token_t         typedef ptr asm_tok

tokptr proto fastcall :abs {
    imul ebx,_1,asm_tok
    add  rbx,tokenarray
    }

endif

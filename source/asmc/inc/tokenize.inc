; TOKENIZE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __TOKENIZE_INC
define __TOKENIZE_INC

; prototypes for tokenizer

line_status	    struc
input		    string_t ?
output		    string_t ?	; free space in token string buffer
start		    string_t ?	; start of line
index		    uint_t ?	; index token array
flags		    char_t ?	; v2.08: added
flags2		    char_t ?	; v2.08: was global var g_flags
flags3		    char_t ?	; v2.08: added
brachets	    char_t ?	; v2.32: added
tokenarray	    token_t ?	; v2.32: input to Tokenize() -- may change!
outbuf		    string_t ?	; v2.32: output start -- may change!
cstring		    char_t ?	; v2.32: added
line_status	    ends

TOK_DEFAULT	    equ 0x00	; default mode - handle conditional assembly
TOK_RESCAN	    equ 0x01	; retokenize after expansion - ignore conditional assembly
TOK_NOCURLBRACES    equ 0x02	; don't handle {}-literals
TOK_LINE	    equ 0x04	; full line is retokenized

TF3_ISCONCAT	    equ 0x01	; line was concatenated
TF3_EXPANSION	    equ 0x02	; expansion operator % at pos 0

GetToken proto fastcall :token_t, :ptr line_status
Tokenize proto __ccall :string_t, :uint_t, :token_t, :uint_t

endif

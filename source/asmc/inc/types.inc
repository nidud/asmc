; TYPES.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __TYPES_INC
define __TYPES_INC

; qualified_type us used for parsing a qualified type.

.template qualified_type
    size		int_t ?
    symtype		ptr asym ?
    mem_type		db ?
    is_ptr		db ?	; contains level of indirection
    is_far		db ?
    Ofssize		db ?
    ptr_memtype		db ?
   .ends

externdef CurrStruct:ptr dsym	; start of current STRUCT list

CreateType		proto __ccall :int_t, :token_t, :string_t, :ptr ptr asym
CreateTypeSymbol	proto __ccall :ptr asym, :string_t, :int_t
SearchNameInStruct	proto __ccall :ptr asym, :string_t, :ptr uint_t, :int_t
GetQualifiedType	proto __ccall :ptr int_t, :ptr asm_tok, :ptr qualified_type
CreateStructField	proto __ccall :int_t, :ptr asm_tok, :string_t, :uchar_t, :ptr asym, :uint_t
UpdateStructSize	proto fastcall :ptr asym
SetStructCurrentOffset	proto fastcall :int_t
AlignInStruct		proto fastcall :int_t
TypesInit		proto
StructDirective		proto __ccall :int_t, :ptr asm_tok
EndstructDirective	proto __ccall :int_t, :ptr asm_tok

DeleteType macro t
    endm

endif

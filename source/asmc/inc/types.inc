; TYPES.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
.pragma list(push, 0)
ifndef __TYPES_INC
define __TYPES_INC

; qualified_type us used for parsing a qualified type.

.template qualified_type
    size		int_t ?
    symtype		asym_t ?
    mem_type		db ?
    is_ptr		db ?	; contains level of indirection
    is_far		db ?
    Ofssize		db ?
    ptr_memtype		db ?
   .ends

externdef CurrStruct:asym_t ; start of current STRUCT list

CreateType		proto __ccall :int_t, :token_t, :string_t, :ptr asym_t
CreateTypeSymbol	proto __ccall :asym_t, :string_t, :int_t
SearchNameInStruct	proto __ccall :asym_t, :string_t, :ptr uint_t, :int_t
GetQualifiedType	proto __ccall :ptr int_t, :token_t, :ptr qualified_type
CreateStructField	proto __ccall :int_t, :token_t, :string_t, :uchar_t, :asym_t, :uint_t
UpdateStructSize	proto fastcall :asym_t
SetStructCurrentOffset	proto fastcall :int_t
AlignInStruct		proto fastcall :int_t
TypesInit		proto
StructDirective		proto __ccall :int_t, :token_t
EndstructDirective	proto __ccall :int_t, :token_t

DeleteType macro t
    endm

endif
.pragma list(pop)

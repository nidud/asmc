.pragma list(push, 0)

;; prototypes of TYPES.ASM

ifndef __TYPES_INC
__TYPES_INC equ <>

;; qualified_type us used for parsing a qualified type.

qualified_type		struct
    size		int_t ?
    symtype		asym_t ?
    mem_type		db ?
    is_ptr		db ?	;; contains level of indirection
    is_far		db ?
    Ofssize		db ?
    ptr_memtype		db ?
qualified_type		ends

externdef CurrStruct:dsym_t	;; start of current STRUCT list

CreateType		proto :int_t, :tok_t, :string_t, :ptr ptr asym
CreateTypeSymbol	proto :asym_t, :string_t, :int_t
SearchNameInStruct	proto :asym_t, :string_t, :ptr uint_t, :int_t
GetQualifiedType	proto :ptr int_t, :tok_t, :ptr qualified_type
CreateStructField	proto :int_t, :tok_t, :string_t, :uchar_t, :asym_t, :int_t
UpdateStructSize	proto :asym_t
SetStructCurrentOffset	proto :int_t
AlignInStruct		proto :int_t
TypesInit		proto
DeleteType macro t
    endm
endif
.pragma list(pop)
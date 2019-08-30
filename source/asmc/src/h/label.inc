.pragma list(push, 0)
ifndef __LABEL_INC
__LABEL_INC equ <>

;;label routines prototypes

LabelInit proto
GetAnonymousLabel proto :string_t, :int_t
CreateLabel proto :string_t, :uchar_t, :ptr qualified_type, :int_t

endif
.pragma list(pop)
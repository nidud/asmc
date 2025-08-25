ifndef FTMM_H_
define FTMM_H_

include freetype/t1tables.inc

FT_MM_Axis		STRUC
name			ptr FT_String ?
minimum			FT_Long ?
maximum			FT_Long ?
FT_MM_Axis		ENDS

FT_Multi_Master		STRUC
num_axis		FT_UInt ?
num_designs		FT_UInt ?
axis			FT_MM_Axis T1_MAX_MM_AXIS dup(<>)
FT_Multi_Master		ENDS

FT_Var_Axis		STRUC
name			ptr FT_String ?
minimum			FT_Fixed ?
def			FT_Fixed ?
maximum			FT_Fixed ?
tag			FT_ULong ?
strid			FT_UInt ?
FT_Var_Axis		ENDS

FT_Var_Named_Style	STRUC
coords			ptr FT_Fixed ?
strid			FT_UInt ?
psid			FT_UInt ?
FT_Var_Named_Style	ENDS

FT_MM_Var		STRUC
num_axis		FT_UInt ?
num_designs		FT_UInt ?
num_namedstyles		FT_UInt ?
axis			ptr FT_Var_Axis ?
namedstyle		ptr FT_Var_Named_Style ?
FT_MM_Var		ENDS

FT_Get_Multi_Master proto :FT_Face, :ptr
FT_Get_MM_Var proto :FT_Face, :ptr
FT_Done_MM_Var proto :FT_Library, :ptr
FT_Set_MM_Design_Coordinates proto :FT_Face, :FT_UInt, :ptr
FT_Set_Var_Design_Coordinates proto :FT_Face, :FT_UInt, :ptr
FT_Get_Var_Design_Coordinates proto :FT_Face, :FT_UInt, :ptr
FT_Set_MM_Blend_Coordinates proto :FT_Face, :FT_UInt, :ptr
FT_Get_MM_Blend_Coordinates proto :FT_Face, :FT_UInt, :ptr
FT_Set_Var_Blend_Coordinates proto :FT_Face, :FT_UInt, :ptr
FT_Get_Var_Blend_Coordinates proto :FT_Face, :FT_UInt, :ptr
FT_Set_MM_WeightVector proto :FT_Face, :FT_UInt, :ptr
FT_Get_MM_WeightVector proto :FT_Face, :ptr, :ptr

define FT_VAR_AXIS_FLAG_HIDDEN	1

FT_Get_Var_Axis_Flags proto :ptr, :FT_UInt, :ptr
FT_Set_Named_Instance proto :FT_Face, :FT_UInt

endif

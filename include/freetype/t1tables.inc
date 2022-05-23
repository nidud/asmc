ifndef T1TABLES_H_
define T1TABLES_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

PS_FontInfoRec		STRUC
version			ptr FT_String ?
notice			ptr FT_String ?
full_name		ptr FT_String ?
family_name		ptr FT_String ?
weight			ptr FT_String ?
italic_angle		FT_Long ?
is_fixed_pitch		FT_Bool ?
underline_position	FT_Short ?
underline_thickness	FT_UShort ?
PS_FontInfoRec		ENDS
PS_FontInfo		typedef ptr PS_FontInfoRec
T1_FontInfo		typedef PS_FontInfoRec


PS_PrivateRec		STRUC
unique_id		FT_Int ?
lenIV			FT_Int ?
num_blue_values		FT_Byte ?
num_other_blues		FT_Byte ?
num_family_blues	FT_Byte ?
num_family_other_blues	FT_Byte ?
blue_values		FT_Short 14 dup(?)
other_blues		FT_Short 10 dup(?)
family_blues		FT_Short 14 dup(?)
family_other_blues	FT_Short 10 dup(?)
blue_scale		FT_Fixed ?
blue_shift		FT_Int ?
blue_fuzz		FT_Int ?
standard_width		FT_UShort 1 dup(?)
standard_height		FT_UShort 1 dup(?)
num_snap_widths		FT_Byte ?
num_snap_heights	FT_Byte ?
force_bold		FT_Bool ?
round_stem_up		FT_Bool ?
snap_widths		FT_Short 13 dup(?)
snap_heights		FT_Short 13 dup(?)
expansion_factor	FT_Fixed ?
language_group		FT_Long ?
password		FT_Long ?
min_feature		FT_Short 2 dup(?)
PS_PrivateRec		ENDS
PS_Private		typedef ptr PS_PrivateRec
T1_Private		typedef PS_PrivateRec


.enum T1_Blend_Flags {
    T1_BLEND_UNDERLINE_POSITION = 0,
    T1_BLEND_UNDERLINE_THICKNESS,
    T1_BLEND_ITALIC_ANGLE,
    T1_BLEND_BLUE_VALUES,
    T1_BLEND_OTHER_BLUES,
    T1_BLEND_STANDARD_WIDTH,
    T1_BLEND_STANDARD_HEIGHT,
    T1_BLEND_STEM_SNAP_WIDTHS,
    T1_BLEND_STEM_SNAP_HEIGHTS,
    T1_BLEND_BLUE_SCALE,
    T1_BLEND_BLUE_SHIFT,
    T1_BLEND_FAMILY_BLUES,
    T1_BLEND_FAMILY_OTHER_BLUES,
    T1_BLEND_FORCE_BOLD,
    T1_BLEND_MAX
    }

define t1_blend_underline_position   T1_BLEND_UNDERLINE_POSITION
define t1_blend_underline_thickness  T1_BLEND_UNDERLINE_THICKNESS
define t1_blend_italic_angle	     T1_BLEND_ITALIC_ANGLE
define t1_blend_blue_values	     T1_BLEND_BLUE_VALUES
define t1_blend_other_blues	     T1_BLEND_OTHER_BLUES
define t1_blend_standard_widths	     T1_BLEND_STANDARD_WIDTH
define t1_blend_standard_height	     T1_BLEND_STANDARD_HEIGHT
define t1_blend_stem_snap_widths     T1_BLEND_STEM_SNAP_WIDTHS
define t1_blend_stem_snap_heights    T1_BLEND_STEM_SNAP_HEIGHTS
define t1_blend_blue_scale	     T1_BLEND_BLUE_SCALE
define t1_blend_blue_shift	     T1_BLEND_BLUE_SHIFT
define t1_blend_family_blues	     T1_BLEND_FAMILY_BLUES
define t1_blend_family_other_blues   T1_BLEND_FAMILY_OTHER_BLUES
define t1_blend_force_bold	     T1_BLEND_FORCE_BOLD
define t1_blend_max		     T1_BLEND_MAX

define T1_MAX_MM_DESIGNS     16
define T1_MAX_MM_AXIS	     4
define T1_MAX_MM_MAP_POINTS  20

PS_DesignMapRec		STRUC
num_points		FT_Byte ?
design_points		ptr FT_Long ?
blend_points		ptr FT_Fixed ?
PS_DesignMapRec		ENDS
PS_DesignMap		typedef ptr PS_DesignMapRec
T1_DesignMap		typedef PS_DesignMapRec

PS_BlendRec		STRUC
num_designs		FT_UInt ?
num_axis		FT_UInt ?
axis_names		ptr FT_String T1_MAX_MM_AXIS dup(?)
design_pos		ptr FT_Fixed T1_MAX_MM_DESIGNS dup(?)
design_map		PS_DesignMapRec T1_MAX_MM_AXIS dup(<>)
weight_vector		ptr FT_Fixed ?
default_weight_vector	ptr FT_Fixed ?
font_infos		PS_FontInfo T1_MAX_MM_DESIGNS + 1 dup(?)
privates		PS_Private T1_MAX_MM_DESIGNS + 1 dup(?)
blend_bitflags		FT_ULong ?
bboxes			ptr FT_BBox T1_MAX_MM_DESIGNS + 1 dup(?)
default_design_vector	FT_UInt T1_MAX_MM_DESIGNS dup(?)
num_default_design_vector FT_UInt ?
PS_BlendRec		ENDS
PS_Blend		typedef ptr PS_BlendRec
T1_Blend		typedef PS_BlendRec

CID_FaceDictRec		STRUC
private_dict		PS_PrivateRec <>
len_buildchar		FT_UInt ?
forcebold_threshold	FT_Fixed ?
stroke_width		FT_Pos ?
expansion_factor	FT_Fixed ?
paint_type		FT_Byte ?
font_type		FT_Byte ?
font_matrix		FT_Matrix <>
font_offset		FT_Vector <>
num_subrs		FT_UInt ?
subrmap_offset		FT_ULong ?
sd_bytes		FT_UInt ?
CID_FaceDictRec		ENDS
CID_FaceDict		typedef ptr CID_FaceDictRec
CID_FontDict		typedef CID_FaceDictRec

CID_FaceInfoRec		STRUC
cid_font_name		ptr FT_String ?
cid_version		FT_Fixed ?
cid_font_type		FT_Int ?
registry		ptr FT_String ?
ordering		ptr FT_String ?
supplement		FT_Int ?
font_info		PS_FontInfoRec <>
font_bbox		FT_BBox <>
uid_base		FT_ULong ?
num_xuid		FT_Int ?
xuid			FT_ULong 16 dup(?)
cidmap_offset		FT_ULong ?
fd_bytes		FT_UInt ?
gd_bytes		FT_UInt ?
cid_count		FT_ULong ?
num_dicts		FT_UInt ?
font_dicts		CID_FaceDict ?
data_offset		FT_ULong ?
CID_FaceInfoRec		ENDS
CID_FaceInfo		typedef ptr CID_FaceInfoRec
CID_Info		typedef CID_FaceInfoRec

FT_Has_PS_Glyph_Names proto \
		  face: FT_Face

FT_Get_PS_Font_Info proto \
		  face: FT_Face,
	    afont_info: PS_FontInfo

FT_Get_PS_Font_Private proto \
		  face: FT_Face,
	 afont_private: PS_Private

.enum T1_EncodingType {
    T1_ENCODING_TYPE_NONE = 0,
    T1_ENCODING_TYPE_ARRAY,
    T1_ENCODING_TYPE_STANDARD,
    T1_ENCODING_TYPE_ISOLATIN1,
    T1_ENCODING_TYPE_EXPERT
    }

.enum PS_Dict_Keys {
    PS_DICT_FONT_TYPE,
    PS_DICT_FONT_MATRIX,
    PS_DICT_FONT_BBOX,
    PS_DICT_PAINT_TYPE,
    PS_DICT_FONT_NAME,
    PS_DICT_UNIQUE_ID,
    PS_DICT_NUM_CHAR_STRINGS,
    PS_DICT_CHAR_STRING_KEY,
    PS_DICT_CHAR_STRING,
    PS_DICT_ENCODING_TYPE,
    PS_DICT_ENCODING_ENTRY,
    PS_DICT_NUM_SUBRS,
    PS_DICT_SUBR,
    PS_DICT_STD_HW,
    PS_DICT_STD_VW,
    PS_DICT_NUM_BLUE_VALUES,
    PS_DICT_BLUE_VALUE,
    PS_DICT_BLUE_FUZZ,
    PS_DICT_NUM_OTHER_BLUES,
    PS_DICT_OTHER_BLUE,
    PS_DICT_NUM_FAMILY_BLUES,
    PS_DICT_FAMILY_BLUE,
    PS_DICT_NUM_FAMILY_OTHER_BLUES,
    PS_DICT_FAMILY_OTHER_BLUE,
    PS_DICT_BLUE_SCALE,
    PS_DICT_BLUE_SHIFT,
    PS_DICT_NUM_STEM_SNAP_H,
    PS_DICT_STEM_SNAP_H,
    PS_DICT_NUM_STEM_SNAP_V,
    PS_DICT_STEM_SNAP_V,
    PS_DICT_FORCE_BOLD,
    PS_DICT_RND_STEM_UP,
    PS_DICT_MIN_FEATURE,
    PS_DICT_LEN_IV,
    PS_DICT_PASSWORD,
    PS_DICT_LANGUAGE_GROUP,
    PS_DICT_VERSION,
    PS_DICT_NOTICE,
    PS_DICT_FULL_NAME,
    PS_DICT_FAMILY_NAME,
    PS_DICT_WEIGHT,
    PS_DICT_IS_FIXED_PITCH,
    PS_DICT_UNDERLINE_POSITION,
    PS_DICT_UNDERLINE_THICKNESS,
    PS_DICT_FS_TYPE,
    PS_DICT_ITALIC_ANGLE,
    PS_DICT_MAX = PS_DICT_ITALIC_ANGLE
    }


FT_Get_PS_Font_Value proto \
		  face: FT_Face,
		   key: PS_Dict_Keys,
		   idx: FT_UInt,
		 value: ptr void,
	     value_len: FT_Long

endif

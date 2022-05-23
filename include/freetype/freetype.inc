ifndef FREETYPE_H_
define FREETYPE_H_

include ft2build.inc
%include FT_CONFIG_CONFIG_H
include freetype/fttypes.inc
include freetype/fterrors.inc

FT_BEGIN_HEADER

FT_Glyph_Metrics	STRUC
width			FT_Pos ?
height			FT_Pos ?
horiBearingX		FT_Pos ?
horiBearingY		FT_Pos ?
horiAdvance		FT_Pos ?
vertBearingX		FT_Pos ?
vertBearingY		FT_Pos ?
vertAdvance		FT_Pos ?
FT_Glyph_Metrics	ENDS

FT_Bitmap_Size		STRUC
height			FT_Short ?
width			FT_Short ?
size			FT_Pos ?
x_ppem			FT_Pos ?
y_ppem			FT_Pos ?
FT_Bitmap_Size		ENDS

FT_Library		typedef ptr FT_LibraryRec
FT_Module		typedef ptr FT_ModuleRec
FT_Driver		typedef ptr FT_DriverRec
FT_Renderer		typedef ptr FT_RendererRec
FT_Face			typedef ptr FT_FaceRec
FT_Size			typedef ptr FT_SizeRec
FT_GlyphSlot		typedef ptr FT_GlyphSlotRec
FT_CharMap		typedef ptr FT_CharMapRec

ifndef FT_ENC_TAG
FT_ENC_TAG macro value, a, b, c, d
	exitm<value = (((a) shl 24) or ((b) shl 16) or ((c) shl 8) or (d))>
	endm
endif

.enum  FT_Encoding {
    FT_ENC_TAG( FT_ENCODING_NONE, 0, 0, 0, 0 ),
    FT_ENC_TAG( FT_ENCODING_MS_SYMBOL, 's', 'y', 'm', 'b' ),
    FT_ENC_TAG( FT_ENCODING_UNICODE,   'u', 'n', 'i', 'c' ),
    FT_ENC_TAG( FT_ENCODING_SJIS,    's', 'j', 'i', 's' ),
    FT_ENC_TAG( FT_ENCODING_PRC,     'g', 'b', ' ', ' ' ),
    FT_ENC_TAG( FT_ENCODING_BIG5,    'b', 'i', 'g', '5' ),
    FT_ENC_TAG( FT_ENCODING_WANSUNG, 'w', 'a', 'n', 's' ),
    FT_ENC_TAG( FT_ENCODING_JOHAB,   'j', 'o', 'h', 'a' ),
    FT_ENCODING_GB2312	   = FT_ENCODING_PRC,
    FT_ENCODING_MS_SJIS	   = FT_ENCODING_SJIS,
    FT_ENCODING_MS_GB2312  = FT_ENCODING_PRC,
    FT_ENCODING_MS_BIG5	   = FT_ENCODING_BIG5,
    FT_ENCODING_MS_WANSUNG = FT_ENCODING_WANSUNG,
    FT_ENCODING_MS_JOHAB   = FT_ENCODING_JOHAB,
    FT_ENC_TAG( FT_ENCODING_ADOBE_STANDARD, 'A', 'D', 'O', 'B' ),
    FT_ENC_TAG( FT_ENCODING_ADOBE_EXPERT,   'A', 'D', 'B', 'E' ),
    FT_ENC_TAG( FT_ENCODING_ADOBE_CUSTOM,   'A', 'D', 'B', 'C' ),
    FT_ENC_TAG( FT_ENCODING_ADOBE_LATIN_1,  'l', 'a', 't', '1' ),
    FT_ENC_TAG( FT_ENCODING_OLD_LATIN_2, 'l', 'a', 't', '2' ),
    FT_ENC_TAG( FT_ENCODING_APPLE_ROMAN, 'a', 'r', 'm', 'n' )
    }


define ft_encoding_none		   FT_ENCODING_NONE
define ft_encoding_unicode	   FT_ENCODING_UNICODE
define ft_encoding_symbol	   FT_ENCODING_MS_SYMBOL
define ft_encoding_latin_1	   FT_ENCODING_ADOBE_LATIN_1
define ft_encoding_latin_2	   FT_ENCODING_OLD_LATIN_2
define ft_encoding_sjis		   FT_ENCODING_SJIS
define ft_encoding_gb2312	   FT_ENCODING_PRC
define ft_encoding_big5		   FT_ENCODING_BIG5
define ft_encoding_wansung	   FT_ENCODING_WANSUNG
define ft_encoding_johab	   FT_ENCODING_JOHAB

define ft_encoding_adobe_standard  FT_ENCODING_ADOBE_STANDARD
define ft_encoding_adobe_expert	   FT_ENCODING_ADOBE_EXPERT
define ft_encoding_adobe_custom	   FT_ENCODING_ADOBE_CUSTOM
define ft_encoding_apple_roman	   FT_ENCODING_APPLE_ROMAN

FT_CharMapRec		STRUC
face			FT_Face ?
encoding		FT_Encoding ?
platform_id		FT_UShort ?
encoding_id		FT_UShort ?
FT_CharMapRec		ENDS

FT_Face_Internal	typedef ptr FT_Face_InternalRec

FT_FaceRec		STRUC
num_faces		FT_Long ?
face_index		FT_Long ?
face_flags		FT_Long ?
style_flags		FT_Long ?
num_glyphs		FT_Long ?
family_name		ptr FT_String ?
style_name		ptr FT_String ?
num_fixed_sizes		FT_Int ?
available_sizes		ptr FT_Bitmap_Size ?
num_charmaps		FT_Int ?
charmaps		ptr FT_CharMap ?
generic			FT_Generic <>
bbox			FT_BBox <>
units_per_EM		FT_UShort ?
ascender		FT_Short ?
descender		FT_Short ?
height			FT_Short ?
max_advance_width	FT_Short ?
max_advance_height	FT_Short ?
underline_position	FT_Short ?
underline_thickness	FT_Short ?
glyph			FT_GlyphSlot ?
size			FT_Size ?
charmap			FT_CharMap ?
driver			FT_Driver ?
memory			FT_Memory ?
stream			FT_Stream ?
sizes_list		FT_ListRec <>
autohint		FT_Generic <>
extensions		ptr ?
internal		FT_Face_Internal ?
FT_FaceRec		ENDS


FT_FACE_FLAG_SCALABLE	equ ( 1 SHL 0 )
FT_FACE_FLAG_FIXED_SIZES equ ( 1 SHL 1 )
FT_FACE_FLAG_FIXED_WIDTH equ ( 1 SHL 2 )
FT_FACE_FLAG_SFNT	equ ( 1 SHL 3 )
FT_FACE_FLAG_HORIZONTAL equ ( 1 SHL 4 )
FT_FACE_FLAG_VERTICAL	equ ( 1 SHL 5 )
FT_FACE_FLAG_KERNING	equ ( 1 SHL 6 )
FT_FACE_FLAG_FAST_GLYPHS equ ( 1 SHL 7 )
FT_FACE_FLAG_MULTIPLE_MASTERS equ ( 1 SHL 8 )
FT_FACE_FLAG_GLYPH_NAMES equ ( 1 SHL 9 )
FT_FACE_FLAG_EXTERNAL_STREAM equ ( 1 SHL 10 )
FT_FACE_FLAG_HINTER	equ ( 1 SHL 11 )
FT_FACE_FLAG_CID_KEYED	equ ( 1 SHL 12 )
FT_FACE_FLAG_TRICKY	equ ( 1 SHL 13 )
FT_FACE_FLAG_COLOR	equ ( 1 SHL 14 )
FT_FACE_FLAG_VARIATION	equ ( 1 SHL 15 )
FT_FACE_FLAG_SVG	equ ( 1 SHL 16 )
FT_FACE_FLAG_SBIX	equ ( 1 SHL 17 )
FT_FACE_FLAG_SBIX_OVERLAY equ ( 1 SHL 18 )


FT_HAS_HORIZONTAL macro face
	exitm<(!!( face.face_flags & FT_FACE_FLAG_HORIZONTAL ) )>
	endm

FT_HAS_VERTICAL macro face
	exitm<(!!( face.face_flags & FT_FACE_FLAG_VERTICAL ) )>
	endm

FT_HAS_KERNING macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_KERNING ) )>
	endm

FT_IS_SCALABLE macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_SCALABLE ) )>
	endm

FT_IS_SFNT macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_SFNT ) )>
	endm

FT_IS_FIXED_WIDTH macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_FIXED_WIDTH ) )>
	endm

FT_HAS_FIXED_SIZES macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_FIXED_SIZES ) )>
	endm

FT_HAS_FAST_GLYPHS macro face
	exitm<0>
	endm

FT_HAS_GLYPH_NAMES macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_GLYPH_NAMES ) )>
	endm

FT_HAS_MULTIPLE_MASTERS macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_MULTIPLE_MASTERS ) )>
	endm

FT_IS_NAMED_INSTANCE macro face
	exitm<(!!( (face)->face_index & 0x7FFF0000L ) )>
	endm

FT_IS_VARIATION macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_VARIATION ) )>
	endm

FT_IS_CID_KEYED macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_CID_KEYED ) )>
	endm

FT_IS_TRICKY macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_TRICKY ) )>
	endm

FT_HAS_COLOR macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_COLOR ) )>
	endm

FT_HAS_SVG macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_SVG ) )>
	endm

FT_HAS_SBIX macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_SBIX ) )>
	endm

FT_HAS_SBIX_OVERLAY macro face
	exitm<(!!( (face)->face_flags & FT_FACE_FLAG_SBIX_OVERLAY ) )>
	endm

FT_STYLE_FLAG_ITALIC	equ ( 1 SHL 0 )
FT_STYLE_FLAG_BOLD	equ ( 1 SHL 1 )

FT_Size_Internal	typedef ptr FT_Size_InternalRec


FT_Size_Metrics		STRUC
x_ppem			FT_UShort ?
y_ppem			FT_UShort ?
x_scale			FT_Fixed ?
y_scale			FT_Fixed ?
ascender		FT_Pos ?
descender		FT_Pos ?
height			FT_Pos ?
max_advance		FT_Pos ?
FT_Size_Metrics		ENDS

FT_SizeRec		STRUC
face			FT_Face ?
generic			FT_Generic <>
metrics			FT_Size_Metrics <>
internal		FT_Size_Internal ?
FT_SizeRec		ENDS
FT_SubGlyph		typedef ptr FT_SubGlyphRec
FT_Slot_Internal	typedef ptr FT_Slot_InternalRec

FT_GlyphSlotRec		STRUC
library			FT_Library ?
face			FT_Face ?
next			FT_GlyphSlot ?
glyph_index		FT_UInt ?
generic			FT_Generic <>
metrics			FT_Glyph_Metrics <>
linearHoriAdvance	FT_Fixed ?
linearVertAdvance	FT_Fixed ?
advance			FT_Vector <>
format			FT_Glyph_Format ?
bitmap			FT_Bitmap <>
bitmap_left		FT_Int ?
bitmap_top		FT_Int ?
outline			FT_Outline <>
num_subglyphs		FT_UInt ?
subglyphs		FT_SubGlyph ?
control_data		ptr ?
control_len		SDWORD ?
lsb_delta		FT_Pos ?
rsb_delta		FT_Pos ?
other			ptr ?
internal		FT_Slot_Internal ?
FT_GlyphSlotRec		ENDS

FT_Init_FreeType proto :ptr FT_Library
FT_Done_FreeType proto :ptr FT_Library

define FT_OPEN_MEMORY	 0x1
define FT_OPEN_STREAM	 0x2
define FT_OPEN_PATHNAME	 0x4
define FT_OPEN_DRIVER	 0x8
define FT_OPEN_PARAMS	 0x10

define ft_open_memory	 FT_OPEN_MEMORY
define ft_open_stream	 FT_OPEN_STREAM
define ft_open_pathname	 FT_OPEN_PATHNAME
define ft_open_driver	 FT_OPEN_DRIVER
define ft_open_params	 FT_OPEN_PARAMS

FT_Parameter		STRUC
tag			FT_ULong ?
data			FT_Pointer ?
FT_Parameter		ENDS

FT_Open_Args		STRUC
flags			FT_UInt ?
memory_base		ptr FT_Byte ?
memory_size		FT_Long ?
pathname		ptr FT_String ?
stream			FT_Stream ?
driver			FT_Module ?
num_params		FT_Int ?
params			ptr FT_Parameter ?
FT_Open_Args		ENDS


FT_New_Face		proto :FT_Library, :ptr, :FT_Long, :ptr FT_Face
FT_New_Memory_Face	proto :FT_Library, :ptr FT_Byte, :FT_Long, :FT_Long, :ptr FT_Face
FT_Open_Face		proto :FT_Library, :ptr FT_Open_Args, :FT_Long, :ptr FT_Face
FT_Attach_File		proto :FT_Face, :ptr
FT_Attach_Stream	proto :FT_Face, :ptr FT_Open_Args
FT_Reference_Face	proto :FT_Face
FT_Done_Face		proto :FT_Face
FT_Select_Size		proto :FT_Face, :FT_Int


.enum FT_Size_Request_Type {
    FT_SIZE_REQUEST_TYPE_NOMINAL,
    FT_SIZE_REQUEST_TYPE_REAL_DIM,
    FT_SIZE_REQUEST_TYPE_BBOX,
    FT_SIZE_REQUEST_TYPE_CELL,
    FT_SIZE_REQUEST_TYPE_SCALES,
    FT_SIZE_REQUEST_TYPE_MAX
    }


FT_Size_RequestRec	STRUC
type			FT_Size_Request_Type ?
width			FT_Long ?
height			FT_Long ?
horiResolution		FT_UInt ?
vertResolution		FT_UInt ?
FT_Size_RequestRec	ENDS
FT_Size_Request		typedef ptr FT_Size_RequestRec


FT_Request_Size		proto :FT_Face, :FT_Size_Request
FT_Set_Char_Size	proto :FT_Face, :FT_F26Dot6, :FT_F26Dot6, :FT_UInt, :FT_UInt
FT_Set_Pixel_Sizes	proto :FT_Face, :FT_UInt, :FT_UInt
FT_Load_Glyph		proto :FT_Face, :FT_UInt, :FT_Int32
FT_Load_Char		proto :FT_Face, :FT_ULong, :FT_Int32


define FT_LOAD_DEFAULT	0x0
FT_LOAD_NO_SCALE	equ ( 1 SHL 0	)
FT_LOAD_NO_HINTING	equ ( 1 SHL 1	)
FT_LOAD_RENDER		equ ( 1 SHL 2	)
FT_LOAD_NO_BITMAP	equ ( 1 SHL 3	)
FT_LOAD_VERTICAL_LAYOUT equ ( 1 SHL 4	)
FT_LOAD_FORCE_AUTOHINT	equ ( 1 SHL 5	)
FT_LOAD_CROP_BITMAP	equ ( 1 SHL 6	)
FT_LOAD_PEDANTIC	equ ( 1 SHL 7	)
FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH equ ( 1 SHL 9  )
FT_LOAD_NO_RECURSE	equ ( 1 SHL 10 )
FT_LOAD_IGNORE_TRANSFORM equ ( 1 SHL 11 )
FT_LOAD_MONOCHROME	equ ( 1 SHL 12 )
FT_LOAD_LINEAR_DESIGN	equ ( 1 SHL 13 )
FT_LOAD_SBITS_ONLY	equ ( 1 SHL 14 )
FT_LOAD_NO_AUTOHINT	equ ( 1 SHL 15 )
FT_LOAD_COLOR		equ ( 1 SHL 20 )
FT_LOAD_COMPUTE_METRICS equ ( 1 SHL 21 )
FT_LOAD_BITMAP_METRICS_ONLY equ ( 1 SHL 22 )


FT_LOAD_ADVANCE_ONLY	equ ( 1 SHL 8	)
FT_LOAD_SVG_ONLY	equ ( 1 SHL 23 )


FT_LOAD_TARGET_ macro x
	exitm<( FT_STATIC_CAST( FT_Int32, (x) AND 15 ) SHL 16 )>
	endm

FT_LOAD_TARGET_NORMAL	equ FT_LOAD_TARGET_( FT_RENDER_MODE_NORMAL )
FT_LOAD_TARGET_LIGHT	equ FT_LOAD_TARGET_( FT_RENDER_MODE_LIGHT  )
FT_LOAD_TARGET_MONO	equ FT_LOAD_TARGET_( FT_RENDER_MODE_MONO   )
FT_LOAD_TARGET_LCD	equ FT_LOAD_TARGET_( FT_RENDER_MODE_LCD	   )
FT_LOAD_TARGET_LCD_V	equ FT_LOAD_TARGET_( FT_RENDER_MODE_LCD_V  )


FT_LOAD_TARGET_MODE macro x
	exitm<FT_STATIC_CAST( FT_Render_Mode, ( (x) shr 16 ) and 15 )>
	endm

FT_Set_Transform	proto :FT_Face, :ptr FT_Matrix, :ptr FT_Vector
FT_Get_Transform	proto :FT_Face, :ptr FT_Matrix, :ptr FT_Vector

.enum FT_Render_Mode {
    FT_RENDER_MODE_NORMAL = 0,
    FT_RENDER_MODE_LIGHT,
    FT_RENDER_MODE_MONO,
    FT_RENDER_MODE_LCD,
    FT_RENDER_MODE_LCD_V,
    FT_RENDER_MODE_SDF,
    FT_RENDER_MODE_MAX
    }


define ft_render_mode_normal  FT_RENDER_MODE_NORMAL
define ft_render_mode_mono    FT_RENDER_MODE_MONO


FT_Render_Glyph		proto :FT_GlyphSlot, :FT_Render_Mode


.enum FT_Kerning_Mode {
    FT_KERNING_DEFAULT = 0,
    FT_KERNING_UNFITTED,
    FT_KERNING_UNSCALED
    }


define ft_kerning_default   FT_KERNING_DEFAULT
define ft_kerning_unfitted  FT_KERNING_UNFITTED
define ft_kerning_unscaled  FT_KERNING_UNSCALED


FT_Get_Kerning		proto :FT_Face, :FT_UInt, :FT_UInt, :FT_UInt, :ptr FT_Vector
FT_Get_Track_Kerning	proto :FT_Face, :FT_Fixed, :FT_Int, :ptr FT_Fixed
FT_Get_Glyph_Name	proto :FT_Face, :FT_UInt, :FT_Pointer, :FT_UInt
FT_Get_Postscript_Name	proto :FT_Face
FT_Select_Charmap	proto :FT_Face, :FT_Encoding
FT_Set_Charmap		proto :FT_Face, :FT_CharMap
FT_Get_Charmap_Index	proto :FT_CharMap
FT_Get_Char_Index	proto :FT_Face, :FT_ULong
FT_Get_First_Char	proto :FT_Face, :ptr FT_UInt

FT_Get_Next_Char	proto :FT_Face, :FT_ULong, :ptr FT_UInt
FT_Face_Properties	proto :FT_Face, :FT_UInt, :ptr FT_Parameter
FT_Get_Name_Index	proto :FT_Face, :ptr FT_String

define FT_SUBGLYPH_FLAG_ARGS_ARE_WORDS		1
define FT_SUBGLYPH_FLAG_ARGS_ARE_XY_VALUES	2
define FT_SUBGLYPH_FLAG_ROUND_XY_TO_GRID	4
define FT_SUBGLYPH_FLAG_SCALE			8
define FT_SUBGLYPH_FLAG_XY_SCALE	     0x40
define FT_SUBGLYPH_FLAG_2X2		     0x80
define FT_SUBGLYPH_FLAG_USE_MY_METRICS	    0x200

FT_Get_SubGlyph_Info	proto :FT_GlyphSlot, :FT_UInt, :ptr FT_Int, :ptr FT_UInt, :ptr FT_Int, :ptr FT_Int, :ptr FT_Matrix

define FT_FSTYPE_INSTALLABLE_EMBEDDING	       0x0000
define FT_FSTYPE_RESTRICTED_LICENSE_EMBEDDING  0x0002
define FT_FSTYPE_PREVIEW_AND_PRINT_EMBEDDING   0x0004
define FT_FSTYPE_EDITABLE_EMBEDDING	       0x0008
define FT_FSTYPE_NO_SUBSETTING		       0x0100
define FT_FSTYPE_BITMAP_EMBEDDING_ONLY	       0x0200

FT_Get_FSType_Flags	proto :FT_Face
FT_Face_GetCharVariantIndex proto :FT_Face, :FT_ULong, :FT_ULong
FT_Face_GetCharVariantIsDefault proto :FT_Face, :FT_ULong, :FT_ULong
FT_Face_GetVariantSelectors proto :FT_Face
FT_Face_GetVariantsOfChar proto :FT_Face, :FT_ULong
FT_Face_GetCharsOfVariant proto :FT_Face, :FT_ULong
FT_MulDiv		proto :FT_Long, :FT_Long, :FT_Long
FT_MulFix		proto :FT_Long, :FT_Long
FT_DivFix		proto :FT_Long, :FT_Long
FT_RoundFix		proto :FT_Fixed
FT_CeilFix		proto :FT_Fixed
FT_FloorFix		proto :FT_Fixed
FT_Vector_Transform	proto :ptr FT_Vector, :ptr FT_Matrix

define FREETYPE_MAJOR  2
define FREETYPE_MINOR  12
define FREETYPE_PATCH  1

FT_Library_Version	proto :FT_Library, :ptr FT_Int, :ptr FT_Int, :ptr FT_Int
FT_Face_CheckTrueTypePatents proto :FT_Face
FT_Face_SetUnpatentedHinting proto :FT_Face, :FT_Bool

FT_END_HEADER

endif

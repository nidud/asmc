ifndef FTGLYPH_H_
define FTGLYPH_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

;FT_Glyph_Class		typedef FT_Glyph_Class_
FT_Glyph		typedef ptr FT_GlyphRec

FT_GlyphRec		STRUC
library			FT_Library ?
clazz			ptr FT_Glyph_Class ?
format			FT_Glyph_Format ?
advance			FT_Vector <>
FT_GlyphRec		ENDS
FT_BitmapGlyph		typedef ptr FT_BitmapGlyphRec

FT_BitmapGlyphRec	STRUC
root			FT_GlyphRec <>
left			FT_Int ?
top			FT_Int ?
bitmap			FT_Bitmap <>
FT_BitmapGlyphRec	ENDS

FT_OutlineGlyph		typedef ptr FT_OutlineGlyphRec

FT_OutlineGlyphRec	STRUC
root			FT_GlyphRec <>
outline			FT_Outline <>
FT_OutlineGlyphRec	ENDS

FT_SvgGlyph		typedef ptr FT_SvgGlyphRec

FT_SvgGlyphRec		STRUC
root			FT_GlyphRec <>
svg_document		ptr FT_Byte ?
svg_document_length	FT_ULong ?
glyph_index		FT_UInt ?
metrics			FT_Size_Metrics <>
units_per_EM		FT_UShort ?
start_glyph_id		FT_UShort ?
end_glyph_id		FT_UShort ?
transform		FT_Matrix <>
delta			FT_Vector <>
FT_SvgGlyphRec		ENDS


FT_New_Glyph proto \
	       library: FT_Library,
		format: FT_Glyph_Format,
		aglyph: ptr FT_Glyph

FT_Get_Glyph proto \
		  slot: FT_GlyphSlot,
		aglyph: ptr FT_Glyph

FT_Glyph_Copy proto \
		source: FT_Glyph,
		target: ptr FT_Glyph

FT_Glyph_Transform proto \
		 glyph: FT_Glyph,
		matrix: ptr FT_Matrix,
		 delta: ptr FT_Vector

.enum FT_Glyph_BBox_Mode {
    FT_GLYPH_BBOX_UNSCALED  = 0,
    FT_GLYPH_BBOX_SUBPIXELS = 0,
    FT_GLYPH_BBOX_GRIDFIT   = 1,
    FT_GLYPH_BBOX_TRUNCATE  = 2,
    FT_GLYPH_BBOX_PIXELS    = 3
    }


define ft_glyph_bbox_unscaled	FT_GLYPH_BBOX_UNSCALED
define ft_glyph_bbox_subpixels	FT_GLYPH_BBOX_SUBPIXELS
define ft_glyph_bbox_gridfit	FT_GLYPH_BBOX_GRIDFIT
define ft_glyph_bbox_truncate	FT_GLYPH_BBOX_TRUNCATE
define ft_glyph_bbox_pixels	FT_GLYPH_BBOX_PIXELS


FT_Glyph_Get_CBox proto \
		 glyph: FT_Glyph,
	     bbox_mode: FT_UInt,
		 acbox: ptr FT_BBox

FT_Glyph_To_Bitmap proto \
	     the_glyph: ptr FT_Glyph,
	   render_mode: FT_Render_Mode,
		origin: ptr FT_Vector,
	       destroy: FT_Bool

FT_Done_Glyph proto \
		 glyph: FT_Glyph

FT_Matrix_Multiply proto \
		     a: ptr FT_Matrix,
		     b: ptr FT_Matrix

FT_Matrix_Invert proto \
		matrix: ptr FT_Matrix

endif

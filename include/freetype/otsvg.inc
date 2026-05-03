ifndef OTSVG_H_
define OTSVG_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

CALLBACKC(SVG_Lib_Init_Func, :ptr FT_Pointer)
CALLBACKC(SVG_Lib_Free_Func, :ptr FT_Pointer)
CALLBACKC(SVG_Lib_Render_Func, :FT_GlyphSlot, :ptr FT_Pointer)
CALLBACKC(SVG_Lib_Preset_Slot_Func, :FT_GlyphSlot, :FT_Bool, :ptr FT_Pointer)

SVG_RendererHooks	STRUC
init_svg		SVG_Lib_Init_Func ?
free_svg		SVG_Lib_Free_Func ?
render_svg		SVG_Lib_Render_Func ?
preset_slot		SVG_Lib_Preset_Slot_Func ?
SVG_RendererHooks	ENDS

FT_SVG_DocumentRec	STRUC
svg_document		ptr FT_Byte ?
svg_document_length	FT_ULong ?
metrics			FT_Size_Metrics <>
units_per_EM		FT_UShort ?
start_glyph_id		FT_UShort ?
end_glyph_id		FT_UShort ?
transform		FT_Matrix <>
delta			FT_Vector <>
FT_SVG_DocumentRec	ENDS
FT_SVG_Document		typedef ptr FT_SVG_DocumentRec

endif

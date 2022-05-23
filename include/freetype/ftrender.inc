ifndef FTRENDER_H_
define FTRENDER_H_

include freetype/ftmodapi.inc
include freetype/ftglyph.inc

CALLBACKC(FT_Glyph_InitFunc, :FT_Glyph, :FT_GlyphSlot)
CALLBACKC(FT_Glyph_DoneFunc, :FT_Glyph)
CALLBACKC(FT_Glyph_TransformFunc, :FT_Glyph, :ptr FT_Matrix, :ptr FT_Vector)
CALLBACKC(FT_Glyph_GetBBoxFunc, :FT_Glyph, :ptr FT_BBox)
CALLBACKC(FT_Glyph_CopyFunc, :FT_Glyph, :FT_Glyph)
CALLBACKC(FT_Glyph_PrepareFunc, :FT_Glyph, :FT_GlyphSlot)

define FT_Glyph_Init_Func	<FT_Glyph_InitFunc>
define FT_Glyph_Done_Func	<FT_Glyph_DoneFunc>
define FT_Glyph_Transform_Func	<FT_Glyph_TransformFunc>
define FT_Glyph_BBox_Func	<FT_Glyph_GetBBoxFunc>
define FT_Glyph_Copy_Func	<FT_Glyph_CopyFunc>
define FT_Glyph_Prepare_Func	<FT_Glyph_PrepareFunc>

FT_Glyph_Class		STRUC
glyph_size		FT_Long ?
glyph_format		FT_Glyph_Format ?
glyph_init		FT_Glyph_InitFunc ?
glyph_done		FT_Glyph_DoneFunc ?
glyph_copy		FT_Glyph_CopyFunc ?
glyph_transform		FT_Glyph_TransformFunc ?
glyph_bbox		FT_Glyph_GetBBoxFunc ?
glyph_prepare		FT_Glyph_PrepareFunc ?
FT_Glyph_Class		ENDS

CALLBACKC(FT_Renderer_RenderFunc, :FT_Renderer, :FT_GlyphSlot, :FT_Render_Mode, :ptr FT_Vector)
CALLBACKC(FT_Renderer_TransformFunc, :FT_Renderer, :FT_GlyphSlot, :ptr FT_Matrix, :ptr FT_Vector)
CALLBACKC(FT_Renderer_GetCBoxFunc, :FT_Renderer, :FT_GlyphSlot, :ptr FT_BBox)
CALLBACKC(FT_Renderer_SetModeFunc, :FT_Renderer, :FT_ULong, :FT_Pointer)

define FTRenderer_render	<FT_Renderer_RenderFunc>
define FTRenderer_transform	<FT_Renderer_TransformFunc>
define FTRenderer_getCBox	<FT_Renderer_GetCBoxFunc>
define FTRenderer_setMode	<FT_Renderer_SetModeFunc>


FT_Renderer_Class	STRUC
root			FT_Module_Class <>
glyph_format		FT_Glyph_Format ?
render_glyph		FT_Renderer_RenderFunc ?
transform_glyph		FT_Renderer_TransformFunc ?
get_glyph_cbox		FT_Renderer_GetCBoxFunc ?
set_mode		FT_Renderer_SetModeFunc ?
raster_class		ptr FT_Raster_Funcs ?
FT_Renderer_Class	ENDS

FT_Get_Renderer proto \
	       library: FT_Library,
		format: FT_Glyph_Format

FT_Set_Renderer proto \
	       library: FT_Library,
	      renderer: FT_Renderer,
	    num_params: FT_UInt,
	    parameters: ptr FT_Parameter

endif

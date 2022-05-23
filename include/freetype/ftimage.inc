ifndef FTIMAGE_H_
define FTIMAGE_H_

FT_BEGIN_HEADER

FT_Pos			typedef sdword

FT_Vector		STRUC
x			FT_Pos ?
y			FT_Pos ?
FT_Vector		ENDS

FT_BBox			STRUC
xMin			FT_Pos ?
yMin			FT_Pos ?
xMax			FT_Pos ?
yMax			FT_Pos ?
FT_BBox			ENDS

.enum FT_Pixel_Mode {
    FT_PIXEL_MODE_NONE = 0,
    FT_PIXEL_MODE_MONO,
    FT_PIXEL_MODE_GRAY,
    FT_PIXEL_MODE_GRAY2,
    FT_PIXEL_MODE_GRAY4,
    FT_PIXEL_MODE_LCD,
    FT_PIXEL_MODE_LCD_V,
    FT_PIXEL_MODE_BGRA,
    FT_PIXEL_MODE_MAX
    }

define ft_pixel_mode_none   FT_PIXEL_MODE_NONE
define ft_pixel_mode_mono   FT_PIXEL_MODE_MONO
define ft_pixel_mode_grays  FT_PIXEL_MODE_GRAY
define ft_pixel_mode_pal2   FT_PIXEL_MODE_GRAY2
define ft_pixel_mode_pal4   FT_PIXEL_MODE_GRAY4

FT_Bitmap		STRUC
rows			dd ?
width			dd ?
pitch			SINT ?
buffer			ptr byte ?
num_grays		dw ?
pixel_mode		db ?
palette_mode		db ?
palette			ptr ?
FT_Bitmap		ENDS

FT_Outline		STRUC
n_contours		sword ?
n_points		sword ?
points			ptr FT_Vector ?
tags			ptr sbyte ?
contours		ptr sword ?
flags			SINT ?
FT_Outline		ENDS

define FT_OUTLINE_CONTOURS_MAX	SHRT_MAX
define FT_OUTLINE_POINTS_MAX	SHRT_MAX

define FT_OUTLINE_NONE		   0x0
define FT_OUTLINE_OWNER		   0x1
define FT_OUTLINE_EVEN_ODD_FILL	   0x2
define FT_OUTLINE_REVERSE_FILL	   0x4
define FT_OUTLINE_IGNORE_DROPOUTS  0x8
define FT_OUTLINE_SMART_DROPOUTS   0x10
define FT_OUTLINE_INCLUDE_STUBS	   0x20
define FT_OUTLINE_OVERLAP	   0x40

define FT_OUTLINE_HIGH_PRECISION   0x100
define FT_OUTLINE_SINGLE_PASS	   0x200

define ft_outline_none		   FT_OUTLINE_NONE
define ft_outline_owner		   FT_OUTLINE_OWNER
define ft_outline_even_odd_fill	   FT_OUTLINE_EVEN_ODD_FILL
define ft_outline_reverse_fill	   FT_OUTLINE_REVERSE_FILL
define ft_outline_ignore_dropouts  FT_OUTLINE_IGNORE_DROPOUTS
define ft_outline_high_precision   FT_OUTLINE_HIGH_PRECISION
define ft_outline_single_pass	   FT_OUTLINE_SINGLE_PASS


FT_CURVE_TAG macro flag
	exitm<( flag AND 0x03 )>
	endm

define FT_CURVE_TAG_ON		  0x01
define FT_CURVE_TAG_CONIC	  0x00
define FT_CURVE_TAG_CUBIC	  0x02

define FT_CURVE_TAG_HAS_SCANMODE  0x04

define FT_CURVE_TAG_TOUCH_X	  0x08
define FT_CURVE_TAG_TOUCH_Y	  0x10

FT_CURVE_TAG_TOUCH_BOTH equ ( FT_CURVE_TAG_TOUCH_X OR FT_CURVE_TAG_TOUCH_Y )


define FT_Curve_Tag_On	     FT_CURVE_TAG_ON
define FT_Curve_Tag_Conic    FT_CURVE_TAG_CONIC
define FT_Curve_Tag_Cubic    FT_CURVE_TAG_CUBIC
define FT_Curve_Tag_Touch_X  FT_CURVE_TAG_TOUCH_X
define FT_Curve_Tag_Touch_Y  FT_CURVE_TAG_TOUCH_Y


CALLBACKC(FT_Outline_MoveToFunc, :ptr FT_Vector, :ptr)

define FT_Outline_MoveTo_Func  <FT_Outline_MoveToFunc>

CALLBACKC(FT_Outline_LineToFunc, :ptr FT_Vector, :ptr)

define FT_Outline_LineTo_Func  <FT_Outline_LineToFunc>

CALLBACKC(FT_Outline_ConicToFunc, :ptr FT_Vector, :ptr FT_Vector, :ptr)

define FT_Outline_ConicTo_Func	<FT_Outline_ConicToFunc>

CALLBACKC(FT_Outline_CubicToFunc, :ptr FT_Vector, :ptr FT_Vector, :ptr FT_Vector, :ptr)

define FT_Outline_CubicTo_Func	<FT_Outline_CubicToFunc>


FT_Outline_Funcs	STRUC
move_to			FT_Outline_MoveToFunc ?
line_to			FT_Outline_LineToFunc ?
conic_to		FT_Outline_ConicToFunc ?
cubic_to		FT_Outline_CubicToFunc ?
shift			SINT ?
delta			FT_Pos ?
FT_Outline_Funcs	ENDS

ifndef FT_IMAGE_TAG
FT_IMAGE_TAG macro value, _x1, _x2, _x3, _x4
	exitm<value = (((_x1) shl 24) or ((_x2) shl 16) or ((_x3) shl 8) or (_x4))>
	endm
endif


.enum FT_Glyph_Format {
    FT_IMAGE_TAG( FT_GLYPH_FORMAT_NONE, 0, 0, 0, 0 ),
    FT_IMAGE_TAG( FT_GLYPH_FORMAT_COMPOSITE, 'c', 'o', 'm', 'p' ),
    FT_IMAGE_TAG( FT_GLYPH_FORMAT_BITMAP,    'b', 'i', 't', 's' ),
    FT_IMAGE_TAG( FT_GLYPH_FORMAT_OUTLINE,   'o', 'u', 't', 'l' ),
    FT_IMAGE_TAG( FT_GLYPH_FORMAT_PLOTTER,   'p', 'l', 'o', 't' ),
    FT_IMAGE_TAG( FT_GLYPH_FORMAT_SVG,	     'S', 'V', 'G', ' ' )
    }

define ft_glyph_format_none	  FT_GLYPH_FORMAT_NONE
define ft_glyph_format_composite  FT_GLYPH_FORMAT_COMPOSITE
define ft_glyph_format_bitmap	  FT_GLYPH_FORMAT_BITMAP
define ft_glyph_format_outline	  FT_GLYPH_FORMAT_OUTLINE
define ft_glyph_format_plotter	  FT_GLYPH_FORMAT_PLOTTER

FT_Span			STRUC
x			sword ?
len			dw ?
coverage		db ?
FT_Span			ENDS


CALLBACKC(FT_SpanFunc, :int_t, :int_t, :ptr FT_Span, :ptr)

define FT_Raster_Span_Func  <FT_SpanFunc>

CALLBACKC(FT_Raster_BitTest_Func, :int_t, :int_t, :ptr)
CALLBACKC(FT_Raster_BitSet_Func, :int_t, :int_t, :ptr)

define FT_RASTER_FLAG_DEFAULT  0x0
define FT_RASTER_FLAG_AA       0x1
define FT_RASTER_FLAG_DIRECT   0x2
define FT_RASTER_FLAG_CLIP     0x4
define FT_RASTER_FLAG_SDF      0x8

define ft_raster_flag_default  FT_RASTER_FLAG_DEFAULT
define ft_raster_flag_aa       FT_RASTER_FLAG_AA
define ft_raster_flag_direct   FT_RASTER_FLAG_DIRECT
define ft_raster_flag_clip     FT_RASTER_FLAG_CLIP


FT_Raster_Params	STRUC
target			ptr FT_Bitmap ?
source			ptr ?
flags			SINT ?
gray_spans		FT_SpanFunc ?
black_spans		FT_SpanFunc ?
bit_test		FT_Raster_BitTest_Func ?
bit_set			FT_Raster_BitSet_Func ?
user			ptr ?
clip_box		FT_BBox <>
FT_Raster_Params	ENDS

FT_Raster		typedef ptr FT_RasterRec

CALLBACKC(FT_Raster_NewFunc, :ptr, :ptr FT_Raster)

define FT_Raster_New_Func  <FT_Raster_NewFunc>

CALLBACKC(FT_Raster_DoneFunc, :FT_Raster)

define FT_Raster_Done_Func  <FT_Raster_DoneFunc>

CALLBACKC(FT_Raster_ResetFunc, :FT_Raster, :ptr, :dword)

define FT_Raster_Reset_Func  <FT_Raster_ResetFunc>

CALLBACKC(FT_Raster_SetModeFunc, :FT_Raster, :dword, :ptr)

define FT_Raster_Set_Mode_Func	<FT_Raster_SetModeFunc>

CALLBACKC(FT_Raster_RenderFunc, :FT_Raster, :ptr FT_Raster_Params)

define FT_Raster_Render_Func  <FT_Raster_RenderFunc>


FT_Raster_Funcs		STRUC
glyph_format		FT_Glyph_Format ?
raster_new		FT_Raster_NewFunc ?
raster_reset		FT_Raster_ResetFunc ?
raster_set_mode		FT_Raster_SetModeFunc ?
raster_render		FT_Raster_RenderFunc ?
raster_done		FT_Raster_DoneFunc ?
FT_Raster_Funcs		ENDS

FT_END_HEADER

endif









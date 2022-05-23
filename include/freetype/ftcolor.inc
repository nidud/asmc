ifndef FTCOLOR_H_
define FTCOLOR_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Color		STRUC
blue			FT_Byte ?
green			FT_Byte ?
red			FT_Byte ?
alpha			FT_Byte ?
FT_Color		ENDS

define FT_PALETTE_FOR_LIGHT_BACKGROUND	0x01
define FT_PALETTE_FOR_DARK_BACKGROUND	0x02

FT_Palette_Data		STRUC
num_palettes		FT_UShort ?
palette_name_ids	ptr FT_UShort ?
palette_flags		ptr FT_UShort ?
num_palette_entries	FT_UShort ?
palette_entry_name_ids	ptr FT_UShort ?
FT_Palette_Data		ENDS


FT_Palette_Data_Get proto \
		  face: FT_Face,
	      apalette: ptr FT_Palette_Data

FT_Palette_Select proto \
		  face: FT_Face,
	 palette_index: FT_UShort,
	      apalette: ptr FT_Color

FT_Palette_Set_Foreground_Color proto \
		  face: FT_Face,
      foreground_color: FT_Color


FT_LayerIterator	STRUC
num_layers		FT_UInt ?
layer			FT_UInt ?
p			ptr FT_Byte ?
FT_LayerIterator	ENDS

FT_Get_Color_Glyph_Layer proto \
		  face: FT_Face,
	    base_glyph: FT_UInt,
	  aglyph_index: ptr FT_UInt,
	  acolor_index: ptr FT_UInt,
	      iterator: ptr FT_LayerIterator


.enum FT_PaintFormat {
    FT_COLR_PAINTFORMAT_COLR_LAYERS	= 1,
    FT_COLR_PAINTFORMAT_SOLID		= 2,
    FT_COLR_PAINTFORMAT_LINEAR_GRADIENT = 4,
    FT_COLR_PAINTFORMAT_RADIAL_GRADIENT = 6,
    FT_COLR_PAINTFORMAT_SWEEP_GRADIENT	= 8,
    FT_COLR_PAINTFORMAT_GLYPH		= 10,
    FT_COLR_PAINTFORMAT_COLR_GLYPH	= 11,
    FT_COLR_PAINTFORMAT_TRANSFORM	= 12,
    FT_COLR_PAINTFORMAT_TRANSLATE	= 14,
    FT_COLR_PAINTFORMAT_SCALE		= 16,
    FT_COLR_PAINTFORMAT_ROTATE		= 24,
    FT_COLR_PAINTFORMAT_SKEW		= 28,
    FT_COLR_PAINTFORMAT_COMPOSITE	= 32,
    FT_COLR_PAINT_FORMAT_MAX		= 33,
    FT_COLR_PAINTFORMAT_UNSUPPORTED	= 255
    }


FT_ColorStopIterator	STRUC
num_color_stops		FT_UInt ?
current_color_stop	FT_UInt ?
p			ptr FT_Byte ?
FT_ColorStopIterator	ENDS

FT_ColorIndex		STRUC
palette_index		FT_UInt16 ?
alpha			FT_F2Dot14 ?
FT_ColorIndex		ENDS

FT_ColorStop		STRUC
stop_offset		FT_F2Dot14 ?
color			FT_ColorIndex <>
FT_ColorStop		ENDS


.enum FT_PaintExtend {
    FT_COLR_PAINT_EXTEND_PAD	 = 0,
    FT_COLR_PAINT_EXTEND_REPEAT	 = 1,
    FT_COLR_PAINT_EXTEND_REFLECT = 2
    }

FT_ColorLine		STRUC
extend			FT_PaintExtend ?
color_stop_iterator	FT_ColorStopIterator <>
FT_ColorLine		ENDS

FT_Affine23		STRUC
xx			FT_Fixed ?
xy			FT_Fixed ?
_dx			FT_Fixed ?
yx			FT_Fixed ?
yy			FT_Fixed ?
dy			FT_Fixed ?
FT_Affine23		ENDS

.enum FT_Composite_Mode {
    FT_COLR_COMPOSITE_CLEAR	     = 0,
    FT_COLR_COMPOSITE_SRC	     = 1,
    FT_COLR_COMPOSITE_DEST	     = 2,
    FT_COLR_COMPOSITE_SRC_OVER	     = 3,
    FT_COLR_COMPOSITE_DEST_OVER	     = 4,
    FT_COLR_COMPOSITE_SRC_IN	     = 5,
    FT_COLR_COMPOSITE_DEST_IN	     = 6,
    FT_COLR_COMPOSITE_SRC_OUT	     = 7,
    FT_COLR_COMPOSITE_DEST_OUT	     = 8,
    FT_COLR_COMPOSITE_SRC_ATOP	     = 9,
    FT_COLR_COMPOSITE_DEST_ATOP	     = 10,
    FT_COLR_COMPOSITE_XOR	     = 11,
    FT_COLR_COMPOSITE_PLUS	     = 12,
    FT_COLR_COMPOSITE_SCREEN	     = 13,
    FT_COLR_COMPOSITE_OVERLAY	     = 14,
    FT_COLR_COMPOSITE_DARKEN	     = 15,
    FT_COLR_COMPOSITE_LIGHTEN	     = 16,
    FT_COLR_COMPOSITE_COLOR_DODGE    = 17,
    FT_COLR_COMPOSITE_COLOR_BURN     = 18,
    FT_COLR_COMPOSITE_HARD_LIGHT     = 19,
    FT_COLR_COMPOSITE_SOFT_LIGHT     = 20,
    FT_COLR_COMPOSITE_DIFFERENCE     = 21,
    FT_COLR_COMPOSITE_EXCLUSION	     = 22,
    FT_COLR_COMPOSITE_MULTIPLY	     = 23,
    FT_COLR_COMPOSITE_HSL_HUE	     = 24,
    FT_COLR_COMPOSITE_HSL_SATURATION = 25,
    FT_COLR_COMPOSITE_HSL_COLOR	     = 26,
    FT_COLR_COMPOSITE_HSL_LUMINOSITY = 27,
    FT_COLR_COMPOSITE_MAX	     = 28
    }


FT_OpaquePaint		STRUC
p			ptr FT_Byte ?
insert_root_transform	FT_Bool ?
FT_OpaquePaint		ENDS

FT_PaintColrLayers	STRUC
layer_iterator		FT_LayerIterator <>
FT_PaintColrLayers	ENDS

FT_PaintSolid		STRUC
color			FT_ColorIndex <>
FT_PaintSolid		ENDS

FT_PaintLinearGradient	STRUC
colorline		FT_ColorLine <>
p0			FT_Vector <>
p1			FT_Vector <>
p2			FT_Vector <>
FT_PaintLinearGradient	ENDS

FT_PaintRadialGradient	STRUC
colorline		FT_ColorLine <>
c0			FT_Vector <>
r0			FT_Pos ?
c1			FT_Vector <>
r1			FT_Pos ?
FT_PaintRadialGradient	ENDS

FT_PaintSweepGradient	STRUC
colorline		FT_ColorLine <>
center			FT_Vector <>
start_angle		FT_Fixed ?
end_angle		FT_Fixed ?
FT_PaintSweepGradient	ENDS

FT_PaintGlyph		STRUC
paint			FT_OpaquePaint <>
glyphID			FT_UInt ?
FT_PaintGlyph		ENDS

FT_PaintColrGlyph	STRUC
glyphID			FT_UInt ?
FT_PaintColrGlyph	ENDS

FT_PaintTransform	STRUC
paint			FT_OpaquePaint <>
affine			FT_Affine23 <>
FT_PaintTransform	ENDS


FT_PaintTranslate	STRUC
paint			FT_OpaquePaint <>
_dx			FT_Fixed ?
dy			FT_Fixed ?
FT_PaintTranslate	ENDS

FT_PaintScale		STRUC
paint			FT_OpaquePaint <>
scale_x			FT_Fixed ?
scale_y			FT_Fixed ?
center_x		FT_Fixed ?
center_y		FT_Fixed ?
FT_PaintScale		ENDS

FT_PaintRotate		STRUC
paint			FT_OpaquePaint <>
angle			FT_Fixed ?
center_x		FT_Fixed ?
center_y		FT_Fixed ?
FT_PaintRotate		ENDS

FT_PaintSkew		STRUC
paint			FT_OpaquePaint <>
x_skew_angle		FT_Fixed ?
y_skew_angle		FT_Fixed ?
center_x		FT_Fixed ?
center_y		FT_Fixed ?
FT_PaintSkew		ENDS

FT_PaintComposite	STRUC
source_paint		FT_OpaquePaint <>
composite_mode		FT_Composite_Mode ?
backdrop_paint		FT_OpaquePaint <>
FT_PaintComposite	ENDS

FT_COLR_Paint		STRUC
format			FT_PaintFormat ?
UNION u
colr_layers		FT_PaintColrLayers <>
glyph			FT_PaintGlyph <>
solid			FT_PaintSolid <>
linear_gradient		FT_PaintLinearGradient <>
radial_gradient		FT_PaintRadialGradient <>
sweep_gradient		FT_PaintSweepGradient <>
transform		FT_PaintTransform <>
translate		FT_PaintTranslate <>
scale			FT_PaintScale <>
rotate			FT_PaintRotate <>
skew			FT_PaintSkew <>
composite		FT_PaintComposite <>
colr_glyph		FT_PaintColrGlyph <>
ENDS
FT_COLR_Paint		ENDS


.enum FT_Color_Root_Transform {
    FT_COLOR_INCLUDE_ROOT_TRANSFORM,
    FT_COLOR_NO_ROOT_TRANSFORM,
    FT_COLOR_ROOT_TRANSFORM_MAX
    }


FT_ClipBox		STRUC
bottom_left		FT_Vector <>
top_left		FT_Vector <>
top_right		FT_Vector <>
bottom_right		FT_Vector <>
FT_ClipBox		ENDS


FT_Get_Color_Glyph_Paint proto \
		  face: FT_Face,
	    base_glyph: FT_UInt,
	root_transform: FT_Color_Root_Transform,
		 paint: ptr FT_OpaquePaint

FT_Get_Color_Glyph_ClipBox proto \
		  face: FT_Face,
	    base_glyph: FT_UInt,
	      clip_box: ptr FT_ClipBox

FT_Get_Paint_Layers proto \
		  face: FT_Face,
	      iterator: ptr FT_LayerIterator,
		 paint: ptr FT_OpaquePaint

FT_Get_Colorline_Stops proto \
		  face: FT_Face,
	    color_stop: ptr FT_ColorStop,
	      iterator: ptr FT_ColorStopIterator

FT_Get_Paint proto \
		  face: FT_Face,
	  opaque_paint: FT_OpaquePaint,
		 paint: ptr FT_COLR_Paint

endif

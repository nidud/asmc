ifndef __PANGOCAIRO_H__
define __PANGOCAIRO_H__

include pango/pango.inc
include cairo.inc

ifdef __GI_SCANNER__
define PANGO_CAIRO_TYPE_FONT <pango_cairo_font_get_type ()>
PANGO_CAIRO_FONT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), PANGO_CAIRO_TYPE_FONT, PangoCairoFont))>
	endm
PANGO_CAIRO_IS_FONT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), PANGO_CAIRO_TYPE_FONT))>
	endm
else
define PANGO_TYPE_CAIRO_FONT <pango_cairo_font_get_type ()>
PANGO_CAIRO_FONT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_CAIRO_FONT, PangoCairoFont))>
	endm
PANGO_IS_CAIRO_FONT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_CAIRO_FONT))>
	endm
endif

ifdef __GI_SCANNER__
define PANGO_CAIRO_TYPE_FONT_MAP <pango_cairo_font_map_get_type ()>
PANGO_CAIRO_FONT_MAP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), PANGO_CAIRO_TYPE_FONT_MAP, PangoCairoFontMap))>
	endm
PANGO_CAIRO_IS_FONT_MAP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), PANGO_CAIRO_TYPE_FONT_MAP))>
	endm
else
define PANGO_TYPE_CAIRO_FONT_MAP <pango_cairo_font_map_get_type ()>
PANGO_CAIRO_FONT_MAP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_CAIRO_FONT_MAP, PangoCairoFontMap))>
	endm
PANGO_IS_CAIRO_FONT_MAP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_CAIRO_FONT_MAP))>
	endm
endif

CALLBACKC(PangoCairoShapeRendererFunc, :ptr, :ptr, :gboolean, :gpointer)

pango_cairo_font_map_get_type proto __cdecl
pango_cairo_font_map_new proto __cdecl
pango_cairo_font_map_new_for_font_type proto __cdecl :cairo_font_type_t
pango_cairo_font_map_get_default proto __cdecl
pango_cairo_font_map_set_default proto __cdecl :ptr
pango_cairo_font_map_get_font_type proto __cdecl :ptr
pango_cairo_font_map_set_resolution proto __cdecl :ptr, :double
pango_cairo_font_map_get_resolution proto __cdecl :ptr

ifndef PANGO_DISABLE_DEPRECATED
pango_cairo_font_map_create_context proto __cdecl :ptr
endif

pango_cairo_font_get_type proto __cdecl
pango_cairo_font_get_scaled_font proto __cdecl :ptr
pango_cairo_update_context proto __cdecl :ptr, :ptr
pango_cairo_context_set_font_options proto __cdecl :ptr, :ptr
pango_cairo_context_get_font_options proto __cdecl :ptr
pango_cairo_context_set_resolution proto __cdecl :ptr, :double
pango_cairo_context_get_resolution proto __cdecl :ptr
pango_cairo_context_set_shape_renderer proto __cdecl :ptr, :PangoCairoShapeRendererFunc, :gpointer, :GDestroyNotify
pango_cairo_context_get_shape_renderer proto __cdecl :ptr, :ptr
pango_cairo_create_context proto __cdecl :ptr
pango_cairo_create_layout proto __cdecl :ptr
pango_cairo_update_layout proto __cdecl :ptr, :ptr
pango_cairo_show_glyph_string proto __cdecl :ptr, :ptr, :ptr
pango_cairo_show_glyph_item proto __cdecl :ptr, :ptr, :ptr
pango_cairo_show_layout_line proto __cdecl :ptr, :ptr
pango_cairo_show_layout proto __cdecl :ptr, :ptr
pango_cairo_show_error_underline proto __cdecl :ptr, :double, :double, :double, :double
pango_cairo_glyph_string_path proto __cdecl :ptr, :ptr, :ptr
pango_cairo_layout_line_path proto __cdecl :ptr, :ptr
pango_cairo_layout_path proto __cdecl :ptr, :ptr
pango_cairo_error_underline_path proto __cdecl :ptr, :double, :double, :double, :double

endif

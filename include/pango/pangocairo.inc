ifndef __PANGOCAIRO_H__
define __PANGOCAIRO_H__

include pango/pango.inc
include cairo.inc

ifdef __GI_SCANNER__
PANGO_CAIRO_TYPE_FONT equ <pango_cairo_font_get_type>
PANGO_CAIRO_FONT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), PANGO_CAIRO_TYPE_FONT, PangoCairoFont))>
	endm
PANGO_CAIRO_IS_FONT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), PANGO_CAIRO_TYPE_FONT))>
	endm
else
PANGO_TYPE_CAIRO_FONT equ <pango_cairo_font_get_type>
PANGO_CAIRO_FONT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_CAIRO_FONT, PangoCairoFont))>
	endm
PANGO_IS_CAIRO_FONT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_CAIRO_FONT))>
	endm
endif

ifdef __GI_SCANNER__
PANGO_CAIRO_TYPE_FONT_MAP equ <pango_cairo_font_map_get_type>
PANGO_CAIRO_FONT_MAP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), PANGO_CAIRO_TYPE_FONT_MAP, PangoCairoFontMap))>
	endm
PANGO_CAIRO_IS_FONT_MAP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), PANGO_CAIRO_TYPE_FONT_MAP))>
	endm
else
PANGO_TYPE_CAIRO_FONT_MAP equ <pango_cairo_font_map_get_type>
PANGO_CAIRO_FONT_MAP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_CAIRO_FONT_MAP, PangoCairoFontMap))>
	endm
PANGO_IS_CAIRO_FONT_MAP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_CAIRO_FONT_MAP))>
	endm
endif

CALLBACKC(PangoCairoShapeRendererFunc, :ptr cairo_t, :ptr PangoAttrShape, :gboolean, :gpointer)

pango_cairo_font_map_get_type proto __cdecl

pango_cairo_font_map_new proto __cdecl

pango_cairo_font_map_new_for_font_type proto __cdecl \
	      fonttype: cairo_font_type_t

pango_cairo_font_map_get_default proto __cdecl

;void
pango_cairo_font_map_set_default proto __cdecl \
	       fontmap: ptr PangoCairoFontMap


pango_cairo_font_map_get_font_type proto __cdecl \
	       fontmap: ptr PangoCairoFontMap

;void
pango_cairo_font_map_set_resolution proto __cdecl \
	       fontmap: ptr PangoCairoFontMap,
		   dpi: double


pango_cairo_font_map_get_resolution proto __cdecl \
	       fontmap: ptr PangoCairoFontMap

ifndef PANGO_DISABLE_DEPRECATED
pango_cairo_font_map_create_context proto __cdecl \
	       fontmap: ptr PangoCairoFontMap
endif

pango_cairo_font_get_type proto __cdecl

pango_cairo_font_get_scaled_font proto __cdecl \
		  font: ptr PangoCairoFont

;void
pango_cairo_update_context proto __cdecl \
		    cr: ptr cairo_t,
	       context: ptr PangoContext

;void
pango_cairo_context_set_font_options proto __cdecl \
	       context: ptr PangoContext,
	       options: ptr cairo_font_options_t


pango_cairo_context_get_font_options proto __cdecl \
	       context: ptr PangoContext

;void
pango_cairo_context_set_resolution proto __cdecl \
	       context: ptr PangoContext,
		   dpi: double

pango_cairo_context_get_resolution proto __cdecl \
	       context: ptr PangoContext

;void
pango_cairo_context_set_shape_renderer proto __cdecl \
	       context: ptr PangoContext,
		  func: PangoCairoShapeRendererFunc,
		  data: gpointer,
	       dnotify: GDestroyNotify

pango_cairo_context_get_shape_renderer proto __cdecl \
	       context: ptr PangoContext,
		  data: ptr gpointer

pango_cairo_create_context proto __cdecl \
		    cr: ptr cairo_t

pango_cairo_create_layout proto __cdecl \
		    cr: ptr cairo_t

;void
pango_cairo_update_layout proto __cdecl \
		    cr: ptr cairo_t,
		layout: ptr PangoLayout

;void
pango_cairo_show_glyph_string proto __cdecl \
		    cr: ptr cairo_t,
		  font: ptr PangoFont,
		glyphs: ptr PangoGlyphString

;void
pango_cairo_show_glyph_item proto __cdecl \
		    cr: ptr cairo_t,
		  text: ptr char_t,
	    glyph_item: ptr PangoGlyphItem

;void
pango_cairo_show_layout_line proto __cdecl \
		    cr: ptr cairo_t,
		  line: ptr PangoLayoutLine

;void
pango_cairo_show_layout proto __cdecl \
		    cr: ptr cairo_t,
		layout: ptr PangoLayout

;void
pango_cairo_show_error_underline proto __cdecl \
		    cr: ptr cairo_t,
		     x: double,
		     y: double,
		 width: double,
		height: double

;void
pango_cairo_glyph_string_path proto __cdecl \
		    cr: ptr cairo_t,
		  font: ptr PangoFont,
		glyphs: ptr PangoGlyphString

;void
pango_cairo_layout_line_path proto __cdecl \
		    cr: ptr cairo_t,
		  line: ptr PangoLayoutLine

;void
pango_cairo_layout_path proto __cdecl \
		    cr: ptr cairo_t,
		layout: ptr PangoLayout

;void
pango_cairo_error_underline_path proto __cdecl \
		    cr: ptr cairo_t,
		     x: double,
		     y: double,
		 width: double,
		height: double

endif

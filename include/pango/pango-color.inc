ifndef __PANGO_COLOR_H__
define __PANGO_COLOR_H__

include pango/pango-types.inc
include glib-object.inc

PangoColor		STRUC
red			guint16 ?
green			guint16 ?
blue			guint16 ?
PangoColor		ENDS

PANGO_TYPE_COLOR	equ <pango_color_get_type>

pango_color_get_type proto __cdecl

pango_color_copy proto __cdecl \
		 color: ptr PangoColor

pango_color_free proto __cdecl \
		 color: ptr PangoColor

pango_color_parse proto __cdecl \
		 color: ptr PangoColor,
		  spec: ptr char_t

pango_color_parse_with_alpha proto __cdecl
pango_color_to_string proto __cdecl :ptr PangoColor

endif

ifndef __PANGO_TYPES_H__
define __PANGO_TYPES_H__

include glib.inc
include glib-object.inc

include pango/pango-version-macros.inc

PangoGlyph typedef guint32

define PANGO_SCALE 1024

;int
pango_units_from_double proto __cdecl \
		     d: double

pango_units_to_double proto __cdecl \
		     i: int_t

_PangoRectangle		STRUC
x			SINT ?
y			SINT ?
width			SINT ?
height			SINT ?
_PangoRectangle		ENDS
PangoRectangle		typedef _PangoRectangle

;void
pango_extents_to_pixels proto __cdecl \
	     inclusive: ptr PangoRectangle,
	       nearest: ptr PangoRectangle

include pango/pango-gravity.inc
include pango/pango-language.inc
include pango/pango-matrix.inc
include pango/pango-script.inc
include pango/pango-bidi-type.inc

endif

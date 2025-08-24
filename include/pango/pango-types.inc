ifndef __PANGO_TYPES_H__
define __PANGO_TYPES_H__

include glib.inc
include glib-object.inc

include pango/pango-version-macros.inc

PangoGlyph typedef guint32

define PANGO_SCALE 1024

pango_units_from_double proto __cdecl :double
pango_units_to_double proto __cdecl :int_t

PangoRectangle		STRUC
x			SINT ?
y			SINT ?
width			SINT ?
height			SINT ?
PangoRectangle		ENDS

pango_extents_to_pixels proto __cdecl :ptr, :ptr

include pango/pango-gravity.inc
include pango/pango-language.inc
include pango/pango-matrix.inc
include pango/pango-script.inc
include pango/pango-bidi-type.inc

endif

ifndef __PANGO_GLYPH_H__
define __PANGO_GLYPH_H__

include pango/pango-types.inc
include pango/pango-item.inc
include pango/pango-break.inc

PangoGlyphUnit		typedef gint32

PangoGlyphGeometry	struct
width			PangoGlyphUnit ?
x_offset		PangoGlyphUnit ?
y_offset		PangoGlyphUnit ?
PangoGlyphGeometry	ends

PangoGlyphVisAttr	struct
record
is_cluster_start	guint :	 1 ?
is_color		guint :	 1 ?
ends
PangoGlyphVisAttr	ends

PangoGlyphInfo		struct
glyph			PangoGlyph ?
geometry		PangoGlyphGeometry <>
attr			PangoGlyphVisAttr <>
PangoGlyphInfo		ends

PangoGlyphString	struct
num_glyphs		sdword ?
glyphs			ptr PangoGlyphInfo ?
log_clusters		ptr sdword ?
space			sdword ?
PangoGlyphString	ends

define PANGO_TYPE_GLYPH_STRING <pango_glyph_string_get_type ()>

pango_glyph_string_get_type proto
pango_glyph_string_new proto
pango_glyph_string_set_size proto :ptr, :sdword
pango_glyph_string_copy proto :ptr
pango_glyph_string_free proto :ptr
pango_glyph_string_extents proto :ptr, :ptr, :ptr, :ptr
pango_glyph_string_get_width proto :ptr
pango_glyph_string_extents_range proto :ptr, :sdword, :sdword, :ptr, :ptr, :ptr
pango_glyph_string_get_logical_widths proto :ptr, :ptr, :sdword, :sdword, :ptr
pango_glyph_string_index_to_x proto :ptr, :ptr, :sdword, :ptr, :sdword, :gboolean, :ptr
pango_glyph_string_x_to_index proto :ptr, :ptr, :sdword, :ptr, :sdword, :ptr, :ptr
pango_glyph_string_index_to_x_full proto :ptr, :ptr, :sdword, :ptr, :ptr, :sdword, :gboolean, :ptr

.enum PangoShapeFlags {
  PANGO_SHAPE_NONE	      = 0,
  PANGO_SHAPE_ROUND_POSITIONS = 1 shl 0,
}

pango_shape proto :ptr, :sdword, :ptr, :ptr
pango_shape_full proto :ptr, :sdword, :ptr, :sdword, :ptr, :ptr
pango_shape_with_flags proto :ptr, :sdword, :ptr, :sdword, :ptr, :ptr, :PangoShapeFlags
pango_shape_item proto :ptr, :ptr, :sdword, :ptr, :ptr, :PangoShapeFlags

endif

ifndef __PANGO_GLYPH_ITEM_H__
define __PANGO_GLYPH_ITEM_H__

include pango/pango-attributes.inc
include pango/pango-break.inc
include pango/pango-item.inc
include pango/pango-glyph.inc

_PangoGlyphItem         struct
item                    ptr PangoItem ?
glyphs                  ptr PangoGlyphString ?
y_offset                sdword ?
start_x_offset          sdword ?
end_x_offset            sdword ?
_PangoGlyphItem         ends
PangoGlyphItem          typedef _PangoGlyphItem

define PANGO_TYPE_GLYPH_ITEM <pango_glyph_item_get_type ()>

pango_glyph_item_get_type proto

pango_glyph_item_split proto :ptr, :ptr, :sdword
pango_glyph_item_copy proto :ptr
pango_glyph_item_free proto :ptr
pango_glyph_item_apply_attrs proto :ptr, :ptr, :ptr
pango_glyph_item_letter_space proto :ptr, :ptr, :ptr, :sdword
pango_glyph_item_get_logical_widths proto :ptr, :ptr, :ptr

_PangoGlyphItemIter     struct
glyph_item              ptr PangoGlyphItem ?
text                    ptr gchar ?
start_glyph             sdword ?
start_index             sdword ?
start_char              sdword ?
end_glyph               sdword ?
end_index               sdword ?
end_char                sdword ?
_PangoGlyphItemIter     ends
PangoGlyphItemIter      typedef _PangoGlyphItemIter

define PANGO_TYPE_GLYPH_ITEM_ITER <pango_glyph_item_iter_get_type ()>

pango_glyph_item_iter_get_type proto
pango_glyph_item_iter_copy proto :ptr
pango_glyph_item_iter_free proto :ptr

pango_glyph_item_iter_init_start proto :ptr, :ptr, :ptr
pango_glyph_item_iter_init_end proto :ptr, :ptr, :ptr
pango_glyph_item_iter_next_cluster proto :ptr
pango_glyph_item_iter_prev_cluster proto :ptr

endif

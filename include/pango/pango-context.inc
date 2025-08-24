ifndef __PANGO_CONTEXT_H__
define __PANGO_CONTEXT_H__

include pango/pango-types.inc
include pango/pango-font.inc
include pango/pango-fontmap.inc
include pango/pango-attributes.inc
include pango/pango-direction.inc


define PANGO_TYPE_CONTEXT <pango_context_get_type ()>
PANGO_CONTEXT macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_CONTEXT, PangoContext))>
  endm
PANGO_CONTEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_CONTEXT, PangoContextClass))>
  endm
PANGO_IS_CONTEXT macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_CONTEXT))>
  endm
PANGO_IS_CONTEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_CONTEXT))>
  endm
PANGO_CONTEXT_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_CONTEXT, PangoContextClass))>
  endm

pango_context_get_type proto
pango_context_new proto
pango_context_changed proto :ptr
pango_context_set_font_map proto :ptr, :ptr
pango_context_get_font_map proto :ptr
pango_context_get_serial proto :ptr
pango_context_list_families proto :ptr, :ptr, :ptr
pango_context_load_font proto :ptr, :ptr
pango_context_load_fontset proto :ptr, :ptr, :ptr
pango_context_get_metrics proto :ptr, :ptr, :ptr
pango_context_set_font_description proto :ptr, :ptr
pango_context_get_font_description proto :ptr
pango_context_get_language proto :ptr
pango_context_set_language proto :ptr, :ptr
pango_context_set_base_dir proto :ptr, :PangoDirection
pango_context_get_base_dir proto :ptr
pango_context_set_base_gravity proto :ptr, :PangoGravity
pango_context_get_base_gravity proto :ptr
pango_context_get_gravity proto :ptr
pango_context_set_gravity_hint proto :ptr, :PangoGravityHint
pango_context_get_gravity_hint proto :ptr
pango_context_set_matrix proto :ptr, :ptr
pango_context_get_matrix proto :ptr
pango_context_set_round_glyph_positions proto :ptr, :gboolean
pango_context_get_round_glyph_positions proto :ptr

endif

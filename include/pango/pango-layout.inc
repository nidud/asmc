ifndef __PANGO_LAYOUT_H__
define __PANGO_LAYOUT_H__

include pango/pango-attributes.inc
include pango/pango-context.inc
include pango/pango-glyph-item.inc
include pango/pango-tabs.inc

;PangoLayout             typedef _PangoLayout
;PangoLayoutClass        typedef _PangoLayoutClass
;PangoLayoutLine         typedef _PangoLayoutLine

PangoLayoutRun          typedef PangoGlyphItem

.enum PangoAlignment {
  PANGO_ALIGN_LEFT,
  PANGO_ALIGN_CENTER,
  PANGO_ALIGN_RIGHT
}

.enum PangoWrapMode {
  PANGO_WRAP_WORD,
  PANGO_WRAP_CHAR,
  PANGO_WRAP_WORD_CHAR
}

.enum PangoEllipsizeMode {
  PANGO_ELLIPSIZE_NONE,
  PANGO_ELLIPSIZE_START,
  PANGO_ELLIPSIZE_MIDDLE,
  PANGO_ELLIPSIZE_END
}


_PangoLayoutLine        struct
layout                  ptr PangoLayout ?
start_index             gint ?
length                  gint ?
runs                    ptr GSList ?
RECORD
 is_paragraph_start     guint :  1 ?
 resolved_dir           guint :  3 ?
ENDS
_PangoLayoutLine        ends

define PANGO_TYPE_LAYOUT <pango_layout_get_type>
PANGO_LAYOUT macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_LAYOUT, PangoLayout))>
  endm
PANGO_LAYOUT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_LAYOUT, PangoLayoutClass))>
  endm
PANGO_IS_LAYOUT macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_LAYOUT))>
  endm
PANGO_IS_LAYOUT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_LAYOUT))>
  endm
PANGO_LAYOUT_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_LAYOUT, PangoLayoutClass))>
  endm

pango_layout_get_type proto
pango_layout_new proto :ptr
pango_layout_copy proto :ptr

pango_layout_get_context proto :ptr

pango_layout_set_attributes proto :ptr, :ptr
pango_layout_get_attributes proto :ptr

pango_layout_set_text proto :ptr, :ptr, :sdword
pango_layout_get_text proto :ptr

pango_layout_get_character_count proto :ptr

pango_layout_set_markup proto :ptr, :ptr, :sdword

pango_layout_set_markup_with_accel proto :ptr, :ptr, :sdword, :gunichar, :ptr

pango_layout_set_font_description proto :ptr, :ptr

pango_layout_get_font_description proto :ptr

pango_layout_set_width proto :ptr, :sdword
pango_layout_get_width proto :ptr
pango_layout_set_height proto :ptr, :sdword
pango_layout_get_height proto :ptr
pango_layout_set_wrap proto :ptr, :PangoWrapMode
pango_layout_get_wrap proto :ptr
pango_layout_is_wrapped proto :ptr
pango_layout_set_indent proto :ptr, :sdword
pango_layout_get_indent proto :ptr
pango_layout_set_spacing proto :ptr, :sdword
pango_layout_get_spacing proto :ptr
pango_layout_set_line_spacing proto :ptr, :real4
pango_layout_get_line_spacing proto :ptr
pango_layout_set_justify proto :ptr, :gboolean
pango_layout_get_justify proto :ptr
pango_layout_set_justify_last_line proto :ptr, :gboolean
pango_layout_get_justify_last_line proto :ptr
pango_layout_set_auto_dir proto :ptr, :gboolean
pango_layout_get_auto_dir proto :ptr
pango_layout_set_alignment proto :ptr, :PangoAlignment
pango_layout_get_alignment proto :ptr

pango_layout_set_tabs proto :ptr, :ptr
pango_layout_get_tabs proto :ptr

pango_layout_set_single_paragraph_mode proto :ptr, :gboolean
pango_layout_get_single_paragraph_mode proto :ptr

pango_layout_set_ellipsize proto :ptr, :PangoEllipsizeMode
pango_layout_get_ellipsize proto :ptr
pango_layout_is_ellipsized proto :ptr

pango_layout_get_unknown_glyphs_count proto :ptr

pango_layout_get_direction proto :ptr, :sdword

pango_layout_context_changed proto :ptr
pango_layout_get_serial proto :ptr

pango_layout_get_log_attrs proto :ptr, :ptr, :ptr

pango_layout_get_log_attrs_readonly proto :ptr, :ptr

pango_layout_index_to_pos proto :ptr, :sdword, :ptr
pango_layout_index_to_line_x proto :ptr, :sdword, :gboolean, :ptr, :ptr
pango_layout_get_cursor_pos proto :ptr, :sdword, :ptr, :ptr

pango_layout_get_caret_pos proto :ptr, :sdword, :ptr, :ptr

pango_layout_move_cursor_visually proto :ptr, :gboolean, :sdword, :sdword, :sdword, :ptr, :ptr
pango_layout_xy_to_index proto :ptr, :sdword, :sdword, :ptr, :ptr
pango_layout_get_extents proto :ptr, :ptr, :ptr
pango_layout_get_pixel_extents proto :ptr, :ptr, :ptr
pango_layout_get_size proto :ptr, :ptr, :ptr
pango_layout_get_pixel_size proto :ptr, :ptr, :ptr
pango_layout_get_baseline proto :ptr

pango_layout_get_line_count proto :ptr
pango_layout_get_line proto :ptr, :sdword
pango_layout_get_line_readonly proto :ptr, :sdword
pango_layout_get_lines proto :ptr
pango_layout_get_lines_readonly proto :ptr


.enum PangoLayoutSerializeFlags {
  PANGO_LAYOUT_SERIALIZE_DEFAULT = 0,
  PANGO_LAYOUT_SERIALIZE_CONTEXT = 1 shl 0,
  PANGO_LAYOUT_SERIALIZE_OUTPUT = 1 shl 1,
}

pango_layout_serialize proto :ptr, :PangoLayoutSerializeFlags
pango_layout_write_to_file proto :ptr, :PangoLayoutSerializeFlags, :ptr, :ptr

define PANGO_LAYOUT_DESERIALIZE_ERROR <pango_layout_deserialize_error_quark>

.enum PangoLayoutDeserializeError {
  PANGO_LAYOUT_DESERIALIZE_INVALID,
  PANGO_LAYOUT_DESERIALIZE_INVALID_VALUE,
  PANGO_LAYOUT_DESERIALIZE_MISSING_VALUE,
}

pango_layout_deserialize_error_quark proto


.enum PangoLayoutDeserializeFlags {
  PANGO_LAYOUT_DESERIALIZE_DEFAULT = 0,
  PANGO_LAYOUT_DESERIALIZE_CONTEXT = 1 shl 0,
}

pango_layout_deserialize proto :ptr, :ptr, :PangoLayoutDeserializeFlags, :ptr


define PANGO_TYPE_LAYOUT_LINE <pango_layout_line_get_type>

pango_layout_line_get_type proto

pango_layout_line_ref proto :ptr
pango_layout_line_unref proto :ptr

pango_layout_line_get_start_index proto :ptr
pango_layout_line_get_length proto :ptr
pango_layout_line_is_paragraph_start proto :ptr
pango_layout_line_get_resolved_direction proto :ptr

pango_layout_line_x_to_index proto :ptr, :sdword, :ptr, :ptr
pango_layout_line_index_to_x proto :ptr, :sdword, :gboolean, :ptr
pango_layout_line_get_x_ranges proto :ptr, :sdword, :sdword, :ptr, :ptr
pango_layout_line_get_extents proto :ptr, :ptr, :ptr
pango_layout_line_get_height proto :ptr, :ptr

pango_layout_line_get_pixel_extents proto :ptr, :ptr, :ptr

;PangoLayoutIter         typedef _PangoLayoutIter

define PANGO_TYPE_LAYOUT_ITER         <pango_layout_iter_get_type>

pango_layout_iter_get_type proto

pango_layout_get_iter proto :ptr
pango_layout_iter_copy proto :ptr
pango_layout_iter_free proto :ptr

pango_layout_iter_get_index proto :ptr
pango_layout_iter_get_run proto :ptr
pango_layout_iter_get_run_readonly proto :ptr
pango_layout_iter_get_line proto :ptr
pango_layout_iter_get_line_readonly proto :ptr
pango_layout_iter_at_last_line proto :ptr
pango_layout_iter_get_layout proto :ptr

pango_layout_iter_next_char proto :ptr
pango_layout_iter_next_cluster proto :ptr
pango_layout_iter_next_run proto :ptr
pango_layout_iter_next_line proto :ptr

pango_layout_iter_get_char_extents proto :ptr, :ptr
pango_layout_iter_get_cluster_extents proto :ptr, :ptr, :ptr
pango_layout_iter_get_run_extents proto :ptr, :ptr, :ptr
pango_layout_iter_get_line_extents proto :ptr, :ptr, :ptr

pango_layout_iter_get_line_yrange proto :ptr, :ptr, :ptr
pango_layout_iter_get_layout_extents proto :ptr, :ptr, :ptr
pango_layout_iter_get_baseline proto :ptr
pango_layout_iter_get_run_baseline proto :ptr

endif


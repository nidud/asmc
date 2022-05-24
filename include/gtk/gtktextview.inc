ifndef __GTK_TEXT_VIEW_H__
define __GTK_TEXT_VIEW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkimcontext.inc
include gtk/gtktextbuffer.inc

define GTK_TYPE_TEXT_VIEW <gtk_text_view_get_type ()>
GTK_TEXT_VIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TEXT_VIEW, GtkTextView))>
  endm
GTK_TEXT_VIEW_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_VIEW, GtkTextViewClass))>
  endm
GTK_IS_TEXT_VIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TEXT_VIEW))>
  endm
GTK_IS_TEXT_VIEW_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_VIEW))>
  endm
GTK_TEXT_VIEW_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_VIEW, GtkTextViewClass))>
  endm


.enum GtkTextWindowType {
  GTK_TEXT_WINDOW_WIDGET = 1,
  GTK_TEXT_WINDOW_TEXT,
  GTK_TEXT_WINDOW_LEFT,
  GTK_TEXT_WINDOW_RIGHT,
  GTK_TEXT_WINDOW_TOP,
  GTK_TEXT_WINDOW_BOTTOM
}


.enum GtkTextViewLayer {
  GTK_TEXT_VIEW_LAYER_BELOW_TEXT,
  GTK_TEXT_VIEW_LAYER_ABOVE_TEXT
}


.enum GtkTextExtendSelection {
  GTK_TEXT_EXTEND_SELECTION_WORD,
  GTK_TEXT_EXTEND_SELECTION_LINE
}


define GTK_TEXT_VIEW_PRIORITY_VALIDATE (GDK_PRIORITY_REDRAW + 5)

;GtkTextViewPrivate      typedef _GtkTextViewPrivate

_GtkTextView            struct
parent_instance         GtkWidget <>
priv                    ptr GtkTextViewPrivate ?
_GtkTextView            ends
GtkTextView             typedef _GtkTextView

_GtkTextViewClass       struct
parent_class            GtkWidgetClass <>
move_cursor             proc :ptr, :GtkMovementStep, :sdword, :gboolean
set_anchor              proc :ptr
insert_at_cursor        proc :ptr, :ptr
delete_from_cursor      proc :ptr, :GtkDeleteType, :sdword
backspace               proc :ptr
cut_clipboard           proc :ptr
copy_clipboard          proc :ptr
paste_clipboard         proc :ptr
toggle_overwrite        proc :ptr
create_buffer           proc :ptr
snapshot_layer          proc :ptr, :GtkTextViewLayer, :ptr
extend_selection        proc :ptr, :GtkTextExtendSelection, :ptr, :ptr, :ptr
insert_emoji            proc :ptr
padding                 gpointer 8 dup(?)
_GtkTextViewClass       ends
GtkTextViewClass        typedef _GtkTextViewClass

gtk_text_view_get_type proto
gtk_text_view_new proto
gtk_text_view_new_with_buffer proto :ptr
gtk_text_view_set_buffer proto :ptr, :ptr
gtk_text_view_get_buffer proto :ptr
gtk_text_view_scroll_to_iter proto :ptr, :ptr, :real8, :gboolean, :real8, :real8
gtk_text_view_scroll_to_mark proto :ptr, :ptr, :real8, :gboolean, :real8, :real8
gtk_text_view_scroll_mark_onscreen proto :ptr, :ptr
gtk_text_view_move_mark_onscreen proto :ptr, :ptr
gtk_text_view_place_cursor_onscreen proto :ptr

gtk_text_view_get_visible_rect proto :ptr, :ptr
gtk_text_view_set_cursor_visible proto :ptr, :gboolean
gtk_text_view_get_cursor_visible proto :ptr

gtk_text_view_reset_cursor_blink proto :ptr

gtk_text_view_get_cursor_locations proto :ptr, :ptr, :ptr, :ptr
gtk_text_view_get_iter_location proto :ptr, :ptr, :ptr
gtk_text_view_get_iter_at_location proto :ptr, :ptr, :sdword, :sdword
gtk_text_view_get_iter_at_position proto :ptr, :ptr, :ptr, :sdword, :sdword
gtk_text_view_get_line_yrange proto :ptr, :ptr, :ptr, :ptr

gtk_text_view_get_line_at_y proto :ptr, :ptr, :sdword, :ptr

gtk_text_view_buffer_to_window_coords proto :ptr, :GtkTextWindowType, :sdword, :sdword, :ptr, :ptr
gtk_text_view_window_to_buffer_coords proto :ptr, :GtkTextWindowType, :sdword, :sdword, :ptr, :ptr

gtk_text_view_forward_display_line proto :ptr, :ptr
gtk_text_view_backward_display_line proto :ptr, :ptr
gtk_text_view_forward_display_line_end proto :ptr, :ptr
gtk_text_view_backward_display_line_start proto :ptr, :ptr
gtk_text_view_starts_display_line proto :ptr, :ptr
gtk_text_view_move_visually proto :ptr, :ptr, :sdword

gtk_text_view_im_context_filter_keypress proto :ptr, :ptr
gtk_text_view_reset_im_context proto :ptr


gtk_text_view_get_gutter proto :ptr, :GtkTextWindowType
gtk_text_view_set_gutter proto :ptr, :GtkTextWindowType, :ptr
gtk_text_view_add_child_at_anchor proto :ptr, :ptr, :ptr

gtk_text_view_add_overlay proto :ptr, :ptr, :sdword, :sdword

gtk_text_view_move_overlay proto :ptr, :ptr, :sdword, :sdword

gtk_text_view_remove proto :ptr, :ptr



gtk_text_view_set_wrap_mode proto :ptr, :GtkWrapMode
gtk_text_view_get_wrap_mode proto :ptr
gtk_text_view_set_editable proto :ptr, :gboolean
gtk_text_view_get_editable proto :ptr
gtk_text_view_set_overwrite proto :ptr, :gboolean
gtk_text_view_get_overwrite proto :ptr
gtk_text_view_set_accepts_tab proto :ptr, :gboolean
gtk_text_view_get_accepts_tab proto :ptr
gtk_text_view_set_pixels_above_lines proto :ptr, :sdword
gtk_text_view_get_pixels_above_lines proto :ptr
gtk_text_view_set_pixels_below_lines proto :ptr, :sdword
gtk_text_view_get_pixels_below_lines proto :ptr
gtk_text_view_set_pixels_inside_wrap proto :ptr, :sdword
gtk_text_view_get_pixels_inside_wrap proto :ptr
gtk_text_view_set_justification proto :ptr, :GtkJustification
gtk_text_view_get_justification proto :ptr
gtk_text_view_set_left_margin proto :ptr, :sdword
gtk_text_view_get_left_margin proto :ptr
gtk_text_view_set_right_margin proto :ptr, :sdword
gtk_text_view_get_right_margin proto :ptr
gtk_text_view_set_top_margin proto :ptr, :sdword
gtk_text_view_get_top_margin proto :ptr
gtk_text_view_set_bottom_margin proto :ptr, :sdword
gtk_text_view_get_bottom_margin proto :ptr
gtk_text_view_set_indent proto :ptr, :sdword
gtk_text_view_get_indent proto :ptr
gtk_text_view_set_tabs proto :ptr, :ptr
gtk_text_view_get_tabs proto :ptr

gtk_text_view_set_input_purpose proto :ptr, :GtkInputPurpose
gtk_text_view_get_input_purpose proto :ptr

gtk_text_view_set_input_hints proto :ptr, :GtkInputHints
gtk_text_view_get_input_hints proto :ptr

gtk_text_view_set_monospace proto :ptr, :gboolean
gtk_text_view_get_monospace proto :ptr

gtk_text_view_set_extra_menu proto :ptr, :ptr
gtk_text_view_get_extra_menu proto :ptr
gtk_text_view_get_rtl_context proto :ptr
gtk_text_view_get_ltr_context proto :ptr

endif

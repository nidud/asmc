ifndef __GTK_TEXT_ITER_H__
define __GTK_TEXT_ITER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktextchild.inc
include gtk/gtktexttag.inc

.enum GtkTextSearchFlags {
  GTK_TEXT_SEARCH_VISIBLE_ONLY     = 1 shl 0,
  GTK_TEXT_SEARCH_TEXT_ONLY        = 1 shl 1,
  GTK_TEXT_SEARCH_CASE_INSENSITIVE = 1 shl 2
  }

;GtkTextBuffer           typedef _GtkTextBuffer

define GTK_TYPE_TEXT_ITER <gtk_text_iter_get_type ()>

_GtkTextIter            struct
dummy1                  gpointer ?
dummy2                  gpointer ?
dummy3                  sdword ?
dummy4                  sdword ?
dummy5                  sdword ?
dummy6                  sdword ?
dummy7                  sdword ?
dummy8                  sdword ?
dummy9                  gpointer ?
dummy10                 gpointer ?
dummy11                 sdword ?
dummy12                 sdword ?
dummy13                 sdword ?
dummy14                 gpointer ?
_GtkTextIter            ends

gtk_text_iter_get_buffer proto :ptr
gtk_text_iter_copy proto :ptr
gtk_text_iter_free proto :ptr
gtk_text_iter_assign proto :ptr, :ptr
gtk_text_iter_get_type proto
gtk_text_iter_get_offset proto :ptr
gtk_text_iter_get_line proto :ptr
gtk_text_iter_get_line_offset proto :ptr
gtk_text_iter_get_line_index proto :ptr
gtk_text_iter_get_visible_line_offset proto :ptr
gtk_text_iter_get_visible_line_index proto :ptr
gtk_text_iter_get_char proto :ptr
gtk_text_iter_get_slice proto :ptr, :ptr
gtk_text_iter_get_text proto :ptr, :ptr
gtk_text_iter_get_visible_slice proto :ptr, :ptr
gtk_text_iter_get_visible_text proto :ptr, :ptr
gtk_text_iter_get_paintable proto :ptr
gtk_text_iter_get_marks proto :ptr
gtk_text_iter_get_child_anchor proto :ptr
gtk_text_iter_get_toggled_tags proto :ptr, :gboolean
gtk_text_iter_starts_tag proto :ptr, :ptr
gtk_text_iter_ends_tag proto :ptr, :ptr
gtk_text_iter_toggles_tag proto :ptr, :ptr
gtk_text_iter_has_tag proto :ptr, :ptr
gtk_text_iter_get_tags proto :ptr
gtk_text_iter_editable proto :ptr, :gboolean
gtk_text_iter_can_insert proto :ptr, :gboolean
gtk_text_iter_starts_word proto :ptr
gtk_text_iter_ends_word proto :ptr
gtk_text_iter_inside_word proto :ptr
gtk_text_iter_starts_sentence proto :ptr
gtk_text_iter_ends_sentence proto :ptr
gtk_text_iter_inside_sentence proto :ptr
gtk_text_iter_starts_line proto :ptr
gtk_text_iter_ends_line proto :ptr
gtk_text_iter_is_cursor_position proto :ptr
gtk_text_iter_get_chars_in_line proto :ptr
gtk_text_iter_get_bytes_in_line proto :ptr
gtk_text_iter_get_language proto :ptr
gtk_text_iter_is_end proto :ptr
gtk_text_iter_is_start proto :ptr
gtk_text_iter_forward_char proto :ptr
gtk_text_iter_backward_char proto :ptr
gtk_text_iter_forward_chars proto :ptr, :sdword
gtk_text_iter_backward_chars proto :ptr, :sdword
gtk_text_iter_forward_line proto :ptr
gtk_text_iter_backward_line proto :ptr
gtk_text_iter_forward_lines proto :ptr, :sdword
gtk_text_iter_backward_lines proto :ptr, :sdword
gtk_text_iter_forward_word_end proto :ptr
gtk_text_iter_backward_word_start proto :ptr
gtk_text_iter_forward_word_ends proto :ptr, :sdword
gtk_text_iter_backward_word_starts proto :ptr, :sdword

gtk_text_iter_forward_visible_line proto :ptr
gtk_text_iter_backward_visible_line proto :ptr
gtk_text_iter_forward_visible_lines proto :ptr, :sdword
gtk_text_iter_backward_visible_lines proto :ptr, :sdword

gtk_text_iter_forward_visible_word_end proto :ptr
gtk_text_iter_backward_visible_word_start proto :ptr
gtk_text_iter_forward_visible_word_ends proto :ptr, :sdword
gtk_text_iter_backward_visible_word_starts proto :ptr, :sdword

gtk_text_iter_forward_sentence_end proto :ptr
gtk_text_iter_backward_sentence_start proto :ptr
gtk_text_iter_forward_sentence_ends proto :ptr, :sdword
gtk_text_iter_backward_sentence_starts proto :ptr, :sdword

gtk_text_iter_forward_cursor_position proto :ptr
gtk_text_iter_backward_cursor_position proto :ptr
gtk_text_iter_forward_cursor_positions proto :ptr, :sdword
gtk_text_iter_backward_cursor_positions proto :ptr, :sdword

gtk_text_iter_forward_visible_cursor_position proto :ptr
gtk_text_iter_backward_visible_cursor_position proto :ptr
gtk_text_iter_forward_visible_cursor_positions proto :ptr, :sdword
gtk_text_iter_backward_visible_cursor_positions proto :ptr, :sdword

gtk_text_iter_set_offset proto :ptr, :sdword
gtk_text_iter_set_line proto :ptr, :sdword
gtk_text_iter_set_line_offset proto :ptr, :sdword
gtk_text_iter_set_line_index proto :ptr, :sdword
gtk_text_iter_forward_to_end proto :ptr
gtk_text_iter_forward_to_line_end proto :ptr

gtk_text_iter_set_visible_line_offset proto :ptr, :sdword
gtk_text_iter_set_visible_line_index proto :ptr, :sdword

gtk_text_iter_forward_to_tag_toggle proto :ptr, :ptr
gtk_text_iter_backward_to_tag_toggle proto :ptr, :ptr


CALLBACK(GtkTextCharPredicate, :gunichar, :gpointer)

gtk_text_iter_forward_find_char proto :ptr, :GtkTextCharPredicate, :gpointer, :ptr
gtk_text_iter_backward_find_char proto :ptr, :GtkTextCharPredicate, :gpointer, :ptr
gtk_text_iter_forward_search proto :ptr, :ptr, :GtkTextSearchFlags, :ptr, :ptr, :ptr
gtk_text_iter_backward_search proto :ptr, :ptr, :GtkTextSearchFlags, :ptr, :ptr, :ptr
gtk_text_iter_equal proto :ptr, :ptr
gtk_text_iter_compare proto :ptr, :ptr
gtk_text_iter_in_range proto :ptr, :ptr, :ptr


gtk_text_iter_order proto :ptr, :ptr

endif

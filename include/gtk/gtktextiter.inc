ifndef __GTK_TEXT_ITER_H__
__GTK_TEXT_ITER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktextattributes.inc
include gtk/gtktextchild.inc
include gtk/gtktexttag.inc

.enum GtkTextSearchFlags {
    GTK_TEXT_SEARCH_VISIBLE_ONLY     = 1 shl 0,
    GTK_TEXT_SEARCH_TEXT_ONLY	     = 1 shl 1,
    GTK_TEXT_SEARCH_CASE_INSENSITIVE = 1 shl 2
}

GTK_TYPE_TEXT_ITER	equ <gtk_text_iter_get_type>

GtkTextIter		STRUC
dummy1			gpointer ?
dummy2			gpointer ?
dummy3			gint ?
dummy4			gint ?
dummy5			gint ?
dummy6			gint ?
dummy7			gint ?
dummy8			gint ?
dummy9			gpointer ?
dummy10			gpointer ?
dummy11			gint ?
dummy12			gint ?
dummy13			gint ?
dummy14			gpointer ?
GtkTextIter		ENDS

;GtkTextBuffer
gtk_text_iter_get_buffer proto __cdecl \
		  iter: ptr GtkTextIter

;GtkTextIter
gtk_text_iter_copy proto __cdecl \
		  iter: ptr GtkTextIter

;void
gtk_text_iter_free proto __cdecl \
		  iter: ptr GtkTextIter

;void
gtk_text_iter_assign proto __cdecl \
		  iter: ptr GtkTextIter,
		 other: ptr GtkTextIter

;GType
gtk_text_iter_get_type proto __cdecl


;gint
gtk_text_iter_get_offset proto __cdecl \
		  iter: ptr GtkTextIter

;gint
gtk_text_iter_get_line proto __cdecl \
		  iter: ptr GtkTextIter

;gint
gtk_text_iter_get_line_offset proto __cdecl \
		  iter: ptr GtkTextIter

;gint
gtk_text_iter_get_line_index proto __cdecl \
		  iter: ptr GtkTextIter


;gint
gtk_text_iter_get_visible_line_offset proto __cdecl \
		  iter: ptr GtkTextIter

;gint
gtk_text_iter_get_visible_line_index proto __cdecl \
		  iter: ptr GtkTextIter

;gunichar
gtk_text_iter_get_char proto __cdecl \
		  iter: ptr GtkTextIter
;gchar
gtk_text_iter_get_slice proto __cdecl \
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter
;gchar
gtk_text_iter_get_text proto __cdecl \
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;gchar
gtk_text_iter_get_visible_slice proto __cdecl \
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;gchar
gtk_text_iter_get_visible_text proto __cdecl \
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter


;GdkPixbuf*
gtk_text_iter_get_pixbuf proto __cdecl \
		  iter: ptr GtkTextIter

;GSList
gtk_text_iter_get_marks proto __cdecl \
		  iter: ptr GtkTextIter


;GtkTextChildAnchor*
gtk_text_iter_get_child_anchor proto __cdecl \
		  iter: ptr GtkTextIter


;GSList
gtk_text_iter_get_toggled_tags proto __cdecl \
		  iter: ptr GtkTextIter,
	    toggled_on: gboolean


;gboolean
gtk_text_iter_begins_tag proto __cdecl \
		  iter: ptr GtkTextIter,
		   tag: ptr GtkTextTag


;gboolean
gtk_text_iter_ends_tag proto __cdecl \
		  iter: ptr GtkTextIter,
		   tag: ptr GtkTextTag


;gboolean
gtk_text_iter_toggles_tag proto __cdecl \
		  iter: ptr GtkTextIter,
		   tag: ptr GtkTextTag


;gboolean
gtk_text_iter_has_tag proto __cdecl \
		  iter: ptr GtkTextIter,
		   tag: ptr GtkTextTag

;GSList
gtk_text_iter_get_tags proto __cdecl \
		  iter: ptr GtkTextIter


;gboolean
gtk_text_iter_editable proto __cdecl \
		  iter: ptr GtkTextIter,
       default_setting: gboolean

;gboolean
gtk_text_iter_can_insert proto __cdecl \
		  iter: ptr GtkTextIter,
   default_editability: gboolean


;gboolean
gtk_text_iter_starts_word proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_ends_word proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_inside_word proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_starts_sentence proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_ends_sentence proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_inside_sentence proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_starts_line proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_ends_line proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_is_cursor_position proto __cdecl \
		  iter: ptr GtkTextIter


;gint
gtk_text_iter_get_chars_in_line proto __cdecl \
		  iter: ptr GtkTextIter

;gint
gtk_text_iter_get_bytes_in_line proto __cdecl \
		  iter: ptr GtkTextIter


;gboolean
gtk_text_iter_get_attributes proto __cdecl \
		  iter: ptr GtkTextIter,
		values: ptr GtkTextAttributes

;PangoLanguage*
gtk_text_iter_get_language proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_is_end proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_is_start proto __cdecl \
		  iter: ptr GtkTextIter



;gboolean
gtk_text_iter_forward_char proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_char proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_chars proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_backward_chars proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_forward_line proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_line proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_lines proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_backward_lines proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_forward_word_end proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_word_start proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_word_ends proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_backward_word_starts proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint


;gboolean
gtk_text_iter_forward_visible_line proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_visible_line proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_visible_lines proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_backward_visible_lines proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint


;gboolean
gtk_text_iter_forward_visible_word_end proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_visible_word_start proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_visible_word_ends proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_backward_visible_word_starts proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint


;gboolean
gtk_text_iter_forward_sentence_end proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_sentence_start proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_sentence_ends proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_backward_sentence_starts proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_forward_cursor_position proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_cursor_position proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_cursor_positions proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_backward_cursor_positions proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint


;gboolean
gtk_text_iter_forward_visible_cursor_position proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_visible_cursor_position proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_visible_cursor_positions proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;gboolean
gtk_text_iter_backward_visible_cursor_positions proto __cdecl \
		  iter: ptr GtkTextIter,
		 count: gint

;void
gtk_text_iter_set_offset proto __cdecl \
		  iter: ptr GtkTextIter,
	   char_offset: gint

;void
gtk_text_iter_set_line proto __cdecl \
		  iter: ptr GtkTextIter,
	   line_number: gint

;void
gtk_text_iter_set_line_offset proto __cdecl \
		  iter: ptr GtkTextIter,
	  char_on_line: gint

;void
gtk_text_iter_set_line_index proto __cdecl \
		  iter: ptr GtkTextIter,
	  byte_on_line: gint

;void
gtk_text_iter_forward_to_end proto __cdecl \
		  iter: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_to_line_end proto __cdecl \
		  iter: ptr GtkTextIter


;void
gtk_text_iter_set_visible_line_offset proto __cdecl \
		  iter: ptr GtkTextIter,
	  char_on_line: gint

;void
gtk_text_iter_set_visible_line_index proto __cdecl \
		  iter: ptr GtkTextIter,
	  byte_on_line: gint


;gboolean
gtk_text_iter_forward_to_tag_toggle proto __cdecl \
		  iter: ptr GtkTextIter,
		   tag: ptr GtkTextTag


;gboolean
gtk_text_iter_backward_to_tag_toggle proto __cdecl \
		  iter: ptr GtkTextIter,
		   tag: ptr GtkTextTag


CALLBACKC(GtkTextCharPredicate, :gunichar, :gpointer)

;gboolean
gtk_text_iter_forward_find_char proto __cdecl \
		  iter: ptr GtkTextIter,
		  pred: GtkTextCharPredicate,
	     user_data: gpointer,
		 limit: ptr GtkTextIter

;gboolean
gtk_text_iter_backward_find_char proto __cdecl \
		  iter: ptr GtkTextIter,
		  pred: GtkTextCharPredicate,
	     user_data: gpointer,
		 limit: ptr GtkTextIter

;gboolean
gtk_text_iter_forward_search proto __cdecl \
		  iter: ptr GtkTextIter,
		  _str: ptr gchar,
		 flags: GtkTextSearchFlags,
	   match_start: ptr GtkTextIter,
	     match_end: ptr GtkTextIter,
		 limit: ptr GtkTextIter


;gboolean
gtk_text_iter_backward_search proto __cdecl \
		  iter: ptr GtkTextIter,
		  _str: ptr gchar,
		 flags: GtkTextSearchFlags,
	   match_start: ptr GtkTextIter,
	     match_end: ptr GtkTextIter,
		 limit: ptr GtkTextIter

;gboolean
gtk_text_iter_equal proto __cdecl \
		   lhs: ptr GtkTextIter,
		   rhs: ptr GtkTextIter

;gint
gtk_text_iter_compare proto __cdecl \
		   lhs: ptr GtkTextIter,
		   rhs: ptr GtkTextIter

;gboolean
gtk_text_iter_in_range proto __cdecl \
		  iter: ptr GtkTextIter,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;void
gtk_text_iter_order proto __cdecl \
		 first: ptr GtkTextIter,
		second: ptr GtkTextIter

endif

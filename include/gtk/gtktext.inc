ifndef __GTK_TEXT_H__
define __GTK_TEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkeditable.inc
include gtk/gtkentrybuffer.inc

define GTK_TYPE_TEXT <gtk_text_get_type>
GTK_TEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TEXT, GtkText))>
  endm
GTK_IS_TEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TEXT))>
  endm

_GtkText                struct
parent_instance         GtkWidget <>
_GtkText                ends
GtkText                 typedef _GtkText

gtk_text_get_type proto
gtk_text_new proto
gtk_text_new_with_buffer proto :ptr
gtk_text_get_buffer proto :ptr
gtk_text_set_buffer proto :ptr, :ptr
gtk_text_set_visibility proto :ptr, :gboolean
gtk_text_get_visibility proto :ptr
gtk_text_set_invisible_char proto :ptr, :gunichar
gtk_text_get_invisible_char proto :ptr
gtk_text_unset_invisible_char proto :ptr
gtk_text_set_overwrite_mode proto :ptr, :gboolean
gtk_text_get_overwrite_mode proto :ptr
gtk_text_set_max_length proto :ptr, :sdword
gtk_text_get_max_length proto :ptr
gtk_text_get_text_length proto :ptr
gtk_text_set_activates_default proto :ptr, :gboolean
gtk_text_get_activates_default proto :ptr
gtk_text_get_placeholder_text proto :ptr
gtk_text_set_placeholder_text proto :ptr, :ptr
gtk_text_set_input_purpose proto :ptr, :GtkInputPurpose
gtk_text_get_input_purpose proto :ptr
gtk_text_set_input_hints proto :ptr, :GtkInputHints
gtk_text_get_input_hints proto :ptr
gtk_text_set_attributes proto :ptr, :ptr
gtk_text_get_attributes proto :ptr
gtk_text_set_tabs proto :ptr, :ptr
gtk_text_get_tabs proto :ptr
gtk_text_grab_focus_without_selecting proto :ptr
gtk_text_set_extra_menu proto :ptr, :ptr
gtk_text_get_extra_menu proto :ptr
gtk_text_set_enable_emoji_completion proto :ptr, :gboolean
gtk_text_get_enable_emoji_completion proto :ptr
gtk_text_set_propagate_text_width proto :ptr, :gboolean
gtk_text_get_propagate_text_width proto :ptr
gtk_text_set_truncate_multiline proto :ptr, :gboolean
gtk_text_get_truncate_multiline proto :ptr
gtk_text_compute_cursor_extents proto :ptr, :gsize, :ptr, :ptr

endif

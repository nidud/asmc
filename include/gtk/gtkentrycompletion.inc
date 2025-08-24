ifndef __GTK_ENTRY_COMPLETION_H__
define __GTK_ENTRY_COMPLETION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktreemodel.inc
include gtk/gtkliststore.inc
include gtk/gtkcellarea.inc
include gtk/gtktreeviewcolumn.inc
include gtk/gtktreemodelfilter.inc

define GTK_TYPE_ENTRY_COMPLETION <gtk_entry_completion_get_type ()>
GTK_ENTRY_COMPLETION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ENTRY_COMPLETION, GtkEntryCompletion))>
  endm
GTK_IS_ENTRY_COMPLETION macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ENTRY_COMPLETION))>
  endm

CALLBACK(GtkEntryCompletionMatchFunc, :ptr, :ptr, :ptr, :gpointer)

gtk_entry_completion_get_type proto
gtk_entry_completion_new proto
gtk_entry_completion_new_with_area proto :ptr
gtk_entry_completion_get_entry proto :ptr
gtk_entry_completion_set_model proto :ptr, :ptr
gtk_entry_completion_get_model proto :ptr
gtk_entry_completion_set_match_func proto :ptr, :GtkEntryCompletionMatchFunc, :gpointer, :GDestroyNotify
gtk_entry_completion_set_minimum_key_length proto :ptr, :sdword
gtk_entry_completion_get_minimum_key_length proto :ptr
gtk_entry_completion_compute_prefix proto :ptr, :ptr
gtk_entry_completion_complete proto :ptr
gtk_entry_completion_insert_prefix proto :ptr
gtk_entry_completion_set_inline_completion proto :ptr, :gboolean
gtk_entry_completion_get_inline_completion proto :ptr
gtk_entry_completion_set_inline_selection proto :ptr, :gboolean
gtk_entry_completion_get_inline_selection proto :ptr
gtk_entry_completion_set_popup_completion proto :ptr, :gboolean
gtk_entry_completion_get_popup_completion proto :ptr
gtk_entry_completion_set_popup_set_width proto :ptr, :gboolean
gtk_entry_completion_get_popup_set_width proto :ptr
gtk_entry_completion_set_popup_single_match proto :ptr, :gboolean
gtk_entry_completion_get_popup_single_match proto :ptr
gtk_entry_completion_get_completion_prefix proto :ptr
gtk_entry_completion_set_text_column proto :ptr, :sdword
gtk_entry_completion_get_text_column proto :ptr

endif

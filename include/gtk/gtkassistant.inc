ifndef __GTK_ASSISTANT_H__
define __GTK_ASSISTANT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

define GTK_TYPE_ASSISTANT <gtk_assistant_get_type ()>
GTK_ASSISTANT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_ASSISTANT, GtkAssistant))>
  endm
GTK_IS_ASSISTANT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_ASSISTANT))>
  endm

.enum GtkAssistantPageType {
  GTK_ASSISTANT_PAGE_CONTENT,
  GTK_ASSISTANT_PAGE_INTRO,
  GTK_ASSISTANT_PAGE_CONFIRM,
  GTK_ASSISTANT_PAGE_SUMMARY,
  GTK_ASSISTANT_PAGE_PROGRESS,
  GTK_ASSISTANT_PAGE_CUSTOM
}

;GtkAssistant            typedef _GtkAssistant

define GTK_TYPE_ASSISTANT_PAGE <gtk_assistant_page_get_type ()>
GTK_ASSISTANT_PAGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ASSISTANT_PAGE, GtkAssistantPage))>
  endm
GTK_IS_ASSISTANT_PAGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ASSISTANT_PAGE))>
  endm

;GtkAssistantPage        typedef _GtkAssistantPage

CALLBACK(GtkAssistantPageFunc, :sdword, :gpointer)

gtk_assistant_page_get_type proto
gtk_assistant_get_type proto
gtk_assistant_new proto
gtk_assistant_next_page proto :ptr
gtk_assistant_previous_page proto :ptr
gtk_assistant_get_current_page proto :ptr
gtk_assistant_set_current_page proto :ptr, :sdword
gtk_assistant_get_n_pages proto :ptr
gtk_assistant_get_nth_page proto :ptr, :sdword
gtk_assistant_prepend_page proto :ptr, :ptr
gtk_assistant_append_page proto :ptr, :ptr
gtk_assistant_insert_page proto :ptr, :ptr, :sdword
gtk_assistant_remove_page proto :ptr, :sdword
gtk_assistant_set_forward_page_func proto :ptr, :GtkAssistantPageFunc, :gpointer, :GDestroyNotify
gtk_assistant_set_page_type proto :ptr, :ptr, :GtkAssistantPageType
gtk_assistant_get_page_type proto :ptr, :ptr
gtk_assistant_set_page_title proto :ptr, :ptr, :ptr
gtk_assistant_get_page_title proto :ptr, :ptr

gtk_assistant_set_page_complete proto :ptr, :ptr, :gboolean
gtk_assistant_get_page_complete proto :ptr, :ptr
gtk_assistant_add_action_widget proto :ptr, :ptr
gtk_assistant_remove_action_widget proto :ptr, :ptr

gtk_assistant_update_buttons_state proto :ptr
gtk_assistant_commit proto :ptr

gtk_assistant_get_page proto :ptr, :ptr
gtk_assistant_page_get_child proto :ptr

gtk_assistant_get_pages proto :ptr

endif

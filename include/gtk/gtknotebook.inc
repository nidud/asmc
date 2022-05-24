ifndef __GTK_NOTEBOOK_H__
define __GTK_NOTEBOOK_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_NOTEBOOK <gtk_notebook_get_type ()>
GTK_NOTEBOOK macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_NOTEBOOK, GtkNotebook))>
  endm
GTK_IS_NOTEBOOK macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_NOTEBOOK))>
  endm

define GTK_TYPE_NOTEBOOK_PAGE <gtk_notebook_page_get_type ()>
GTK_NOTEBOOK_PAGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_NOTEBOOK_PAGE, GtkNotebookPage))>
  endm
GTK_IS_NOTEBOOK_PAGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_NOTEBOOK_PAGE))>
  endm

;GtkNotebookPage         typedef _GtkNotebookPage

.enum GtkNotebookTab {
  GTK_NOTEBOOK_TAB_FIRST,
  GTK_NOTEBOOK_TAB_LAST
}

;GtkNotebook             typedef _GtkNotebook

gtk_notebook_get_type proto
gtk_notebook_new proto
gtk_notebook_append_page proto :ptr, :ptr, :ptr
gtk_notebook_append_page_menu proto :ptr, :ptr, :ptr, :ptr
gtk_notebook_prepend_page proto :ptr, :ptr, :ptr
gtk_notebook_prepend_page_menu proto :ptr, :ptr, :ptr, :ptr
gtk_notebook_insert_page proto :ptr, :ptr, :ptr, :sdword
gtk_notebook_insert_page_menu proto :ptr, :ptr, :ptr, :ptr, :sdword
gtk_notebook_remove_page proto :ptr, :sdword

gtk_notebook_set_group_name proto :ptr, :ptr
gtk_notebook_get_group_name proto :ptr

gtk_notebook_get_current_page proto :ptr
gtk_notebook_get_nth_page proto :ptr, :sdword
gtk_notebook_get_n_pages proto :ptr
gtk_notebook_page_num proto :ptr, :ptr
gtk_notebook_set_current_page proto :ptr, :sdword
gtk_notebook_next_page proto :ptr
gtk_notebook_prev_page proto :ptr

gtk_notebook_set_show_border proto :ptr, :gboolean
gtk_notebook_get_show_border proto :ptr
gtk_notebook_set_show_tabs proto :ptr, :gboolean
gtk_notebook_get_show_tabs proto :ptr
gtk_notebook_set_tab_pos proto :ptr, :GtkPositionType
gtk_notebook_get_tab_pos proto :ptr
gtk_notebook_set_scrollable proto :ptr, :gboolean
gtk_notebook_get_scrollable proto :ptr

gtk_notebook_popup_enable proto :ptr
gtk_notebook_popup_disable proto :ptr

gtk_notebook_get_tab_label proto :ptr, :ptr
gtk_notebook_set_tab_label proto :ptr, :ptr, :ptr
gtk_notebook_set_tab_label_text proto :ptr, :ptr, :ptr
gtk_notebook_get_tab_label_text proto :ptr, :ptr
gtk_notebook_get_menu_label proto :ptr, :ptr
gtk_notebook_set_menu_label proto :ptr, :ptr, :ptr
gtk_notebook_set_menu_label_text proto :ptr, :ptr, :ptr
gtk_notebook_get_menu_label_text proto :ptr, :ptr
gtk_notebook_reorder_child proto :ptr, :ptr, :sdword
gtk_notebook_get_tab_reorderable proto :ptr, :ptr
gtk_notebook_set_tab_reorderable proto :ptr, :ptr, :gboolean
gtk_notebook_get_tab_detachable proto :ptr, :ptr
gtk_notebook_set_tab_detachable proto :ptr, :ptr, :gboolean
gtk_notebook_detach_tab proto :ptr, :ptr

gtk_notebook_get_action_widget proto :ptr, :GtkPackType
gtk_notebook_set_action_widget proto :ptr, :ptr, :GtkPackType

gtk_notebook_page_get_type proto

gtk_notebook_get_page proto :ptr, :ptr
gtk_notebook_page_get_child proto :ptr
gtk_notebook_get_pages proto :ptr

endif

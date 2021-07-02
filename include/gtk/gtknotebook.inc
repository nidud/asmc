ifndef __GTK_NOTEBOOK_H__
__GTK_NOTEBOOK_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_NOTEBOOK equ <gtk_notebook_get_type>
GTK_NOTEBOOK macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_NOTEBOOK, GtkNotebook))>
	endm
GTK_NOTEBOOK_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_NOTEBOOK, GtkNotebookClass))>
	endm
GTK_IS_NOTEBOOK macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_NOTEBOOK))>
	endm
GTK_IS_NOTEBOOK_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_NOTEBOOK))>
	endm
GTK_NOTEBOOK_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_NOTEBOOK, GtkNotebookClass))>
	endm

.enum GtkNotebookTab {
  GTK_NOTEBOOK_TAB_FIRST,
  GTK_NOTEBOOK_TAB_LAST
}

GtkNotebook		STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkNotebook		ENDS

GtkNotebookClass	STRUC
parent_class		GtkContainerClass <>
switch_page		proc :ptr GtkNotebook, :ptr GtkWidget, :guint
select_page		proc :ptr GtkNotebook, :gboolean
focus_tab		proc :ptr GtkNotebook, :GtkNotebookTab
change_current_page	proc :ptr GtkNotebook, :gint
move_focus_out		proc :ptr GtkNotebook, :GtkDirectionType
reorder_tab		proc :ptr GtkNotebook, :GtkDirectionType, :gboolean
insert_page		proc :ptr GtkNotebook, :ptr GtkWidget, :ptr GtkWidget, :ptr GtkWidget, :gint
create_window		proc :ptr GtkNotebook, :ptr GtkWidget, :gint, :gint
page_reordered		proc :ptr GtkNotebook, :ptr GtkWidget, :guint
page_removed		proc :ptr GtkNotebook, :ptr GtkWidget, :guint
page_added		proc :ptr GtkNotebook, :ptr GtkWidget, :guint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkNotebookClass	ENDS


;GType
gtk_notebook_get_type proto __cdecl
;GtkWidget
gtk_notebook_new proto __cdecl
;gint
gtk_notebook_append_page proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	     tab_label: ptr GtkWidget

;gint
gtk_notebook_append_page_menu proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	     tab_label: ptr GtkWidget,
	    menu_label: ptr GtkWidget

;gint
gtk_notebook_prepend_page proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	     tab_label: ptr GtkWidget

;gint
gtk_notebook_prepend_page_menu proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	     tab_label: ptr GtkWidget,
	    menu_label: ptr GtkWidget

;gint
gtk_notebook_insert_page proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	     tab_label: ptr GtkWidget,
	      position: gint

;gint
gtk_notebook_insert_page_menu proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	     tab_label: ptr GtkWidget,
	    menu_label: ptr GtkWidget,
	      position: gint

;void
gtk_notebook_remove_page proto __cdecl \
	      notebook: ptr GtkNotebook,
	      page_num: gint



;void
gtk_notebook_set_group_name proto __cdecl \
	      notebook: ptr GtkNotebook,
	    group_name: ptr gchar

;const
gtk_notebook_get_group_name proto __cdecl \
	      notebook: ptr GtkNotebook





;gint
gtk_notebook_get_current_page proto __cdecl \
	      notebook: ptr GtkNotebook

;GtkWidget*
gtk_notebook_get_nth_page proto __cdecl \
	      notebook: ptr GtkNotebook,
	      page_num: gint

;gint
gtk_notebook_get_n_pages proto __cdecl \
	      notebook: ptr GtkNotebook

;gint
gtk_notebook_page_num proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget

;void
gtk_notebook_set_current_page proto __cdecl \
	      notebook: ptr GtkNotebook,
	      page_num: gint

;void
gtk_notebook_next_page proto __cdecl \
	      notebook: ptr GtkNotebook

;void
gtk_notebook_prev_page proto __cdecl \
	      notebook: ptr GtkNotebook



;void
gtk_notebook_set_show_border proto __cdecl \
	      notebook: ptr GtkNotebook,
	   show_border: gboolean

;gboolean
gtk_notebook_get_show_border proto __cdecl \
	      notebook: ptr GtkNotebook

;void
gtk_notebook_set_show_tabs proto __cdecl \
	      notebook: ptr GtkNotebook,
	     show_tabs: gboolean

;gboolean
gtk_notebook_get_show_tabs proto __cdecl \
	      notebook: ptr GtkNotebook

;void
gtk_notebook_set_tab_pos proto __cdecl \
	      notebook: ptr GtkNotebook,
		   pos: GtkPositionType

;GtkPositionType
gtk_notebook_get_tab_pos proto __cdecl \
	      notebook: ptr GtkNotebook

;void
gtk_notebook_set_scrollable proto __cdecl \
	      notebook: ptr GtkNotebook,
	    scrollable: gboolean

;gboolean
gtk_notebook_get_scrollable proto __cdecl \
	      notebook: ptr GtkNotebook

;guint16
gtk_notebook_get_tab_hborder proto __cdecl \
	      notebook: ptr GtkNotebook

;guint16
gtk_notebook_get_tab_vborder proto __cdecl \
	      notebook: ptr GtkNotebook



;void
gtk_notebook_popup_enable proto __cdecl \
	      notebook: ptr GtkNotebook

;void
gtk_notebook_popup_disable proto __cdecl \
	      notebook: ptr GtkNotebook



;GtkWidget
gtk_notebook_get_tab_label proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget

;void
gtk_notebook_set_tab_label proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	     tab_label: ptr GtkWidget

;void
gtk_notebook_set_tab_label_text proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	      tab_text: ptr gchar

;const
gtk_notebook_get_tab_label_text proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget

;GtkWidget
gtk_notebook_get_menu_label proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget

;void
gtk_notebook_set_menu_label proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	    menu_label: ptr GtkWidget

;void
gtk_notebook_set_menu_label_text proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	     menu_text: ptr gchar

;const
gtk_notebook_get_menu_label_text proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget

;void
gtk_notebook_reorder_child proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	      position: gint

;gboolean
gtk_notebook_get_tab_reorderable proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget

;void
gtk_notebook_set_tab_reorderable proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	   reorderable: gboolean

;gboolean
gtk_notebook_get_tab_detachable proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget

;void
gtk_notebook_set_tab_detachable proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget,
	    detachable: gboolean

;void
gtk_notebook_detach_tab proto __cdecl \
	      notebook: ptr GtkNotebook,
		 child: ptr GtkWidget


;GtkWidget*
gtk_notebook_get_action_widget proto __cdecl \
	      notebook: ptr GtkNotebook,
	     pack_type: GtkPackType

;void
gtk_notebook_set_action_widget proto __cdecl \
	      notebook: ptr GtkNotebook,
		widget: ptr GtkWidget,
	     pack_type: GtkPackType

G_END_DECLS

endif

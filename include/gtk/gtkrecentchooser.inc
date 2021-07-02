ifndef __GTK_RECENT_CHOOSER_H__
__GTK_RECENT_CHOOSER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkrecentmanager.inc
include gtk/gtkrecentfilter.inc

G_BEGIN_DECLS

GTK_TYPE_RECENT_CHOOSER equ <gtk_recent_chooser_get_type>
GTK_RECENT_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RECENT_CHOOSER, GtkRecentChooser))>
	endm
GTK_IS_RECENT_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RECENT_CHOOSER))>
	endm
GTK_RECENT_CHOOSER_GET_IFACE macro inst
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_RECENT_CHOOSER, GtkRecentChooserIface))>
	endm

.enum GtkRecentSortType {
  GTK_RECENT_SORT_NONE = 0,
  GTK_RECENT_SORT_MRU,
  GTK_RECENT_SORT_LRU,
  GTK_RECENT_SORT_CUSTOM
}

CALLBACKC(GtkRecentSortFunc, :ptr GtkRecentInfo, :ptr GtkRecentInfo, :gpointer)

GTK_RECENT_CHOOSER_ERROR equ <gtk_recent_chooser_error_quark>

GTK_RECENT_CHOOSER_ERROR_NOT_FOUND equ 0
GTK_RECENT_CHOOSER_ERROR_INVALID_URI equ 1

;GQuark
gtk_recent_chooser_error_quark proto __cdecl


GtkRecentChooserIface	STRUC
base_iface		GTypeInterface <>
set_current_uri		proc :ptr GtkRecentChooser, :ptr gchar, :ptr GError
get_current_uri		proc :ptr GtkRecentChooser
select_uri		proc :ptr GtkRecentChooser, :ptr gchar, :ptr GError
unselect_uri		proc :ptr GtkRecentChooser, :ptr gchar
select_all		proc :ptr GtkRecentChooser
unselect_all		proc :ptr GtkRecentChooser
get_items		proc :ptr GtkRecentChooser
get_recent_manager	proc :ptr GtkRecentChooser
add_filter		proc :ptr GtkRecentChooser, :ptr GtkRecentFilter
remove_filter		proc :ptr GtkRecentChooser, :ptr GtkRecentFilter
list_filters		proc :ptr GtkRecentChooser
set_sort_func		proc :ptr GtkRecentChooser, :GtkRecentSortFunc, :gpointer, :GDestroyNotify
item_activated		proc :ptr GtkRecentChooser
selection_changed	proc :ptr GtkRecentChooser
GtkRecentChooserIface	ENDS

;GType
gtk_recent_chooser_get_type proto __cdecl

;void
gtk_recent_chooser_set_show_private proto __cdecl \
	       chooser: ptr GtkRecentChooser,
	  show_private: gboolean

;gboolean
gtk_recent_chooser_get_show_private proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_show_not_found proto __cdecl \
	       chooser: ptr GtkRecentChooser,
	show_not_found: gboolean

;gboolean
gtk_recent_chooser_get_show_not_found proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_select_multiple proto __cdecl \
	       chooser: ptr GtkRecentChooser,
       select_multiple: gboolean

;gboolean
gtk_recent_chooser_get_select_multiple proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_limit proto __cdecl \
	       chooser: ptr GtkRecentChooser,
		 limit: gint

;gint
gtk_recent_chooser_get_limit proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_local_only proto __cdecl \
	       chooser: ptr GtkRecentChooser,
	    local_only: gboolean

;gboolean
gtk_recent_chooser_get_local_only proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_show_tips proto __cdecl \
	       chooser: ptr GtkRecentChooser,
	     show_tips: gboolean

;gboolean
gtk_recent_chooser_get_show_tips proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_show_icons proto __cdecl \
	       chooser: ptr GtkRecentChooser,
	    show_icons: gboolean

;gboolean
gtk_recent_chooser_get_show_icons proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_sort_type proto __cdecl \
	       chooser: ptr GtkRecentChooser,
	     sort_type: GtkRecentSortType

;GtkRecentSortType
gtk_recent_chooser_get_sort_type proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_sort_func proto __cdecl \
	       chooser: ptr GtkRecentChooser,
	     sort_func: GtkRecentSortFunc,
	     sort_data: gpointer,
	  data_destroy: GDestroyNotify


;gboolean
gtk_recent_chooser_set_current_uri proto __cdecl \
	       chooser: ptr GtkRecentChooser,
		   uri: ptr gchar,
		 error: ptr GError

;gchar
gtk_recent_chooser_get_current_uri proto __cdecl \
	       chooser: ptr GtkRecentChooser

;GtkRecentInfo
gtk_recent_chooser_get_current_item proto __cdecl \
	       chooser: ptr GtkRecentChooser

;gboolean
gtk_recent_chooser_select_uri proto __cdecl \
	       chooser: ptr GtkRecentChooser,
		   uri: ptr gchar,
		 error: ptr GError

;void
gtk_recent_chooser_unselect_uri proto __cdecl \
	       chooser: ptr GtkRecentChooser,
		   uri: ptr gchar

;void
gtk_recent_chooser_select_all proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_unselect_all proto __cdecl \
	       chooser: ptr GtkRecentChooser

;GList
gtk_recent_chooser_get_items proto __cdecl \
	       chooser: ptr GtkRecentChooser

;gchar
gtk_recent_chooser_get_uris proto __cdecl \
	       chooser: ptr GtkRecentChooser,
		length: ptr gsize


;void
gtk_recent_chooser_add_filter proto __cdecl \
	       chooser: ptr GtkRecentChooser,
		filter: ptr GtkRecentFilter

;void
gtk_recent_chooser_remove_filter proto __cdecl \
	       chooser: ptr GtkRecentChooser,
		filter: ptr GtkRecentFilter

;GSList
gtk_recent_chooser_list_filters proto __cdecl \
	       chooser: ptr GtkRecentChooser

;void
gtk_recent_chooser_set_filter proto __cdecl \
	       chooser: ptr GtkRecentChooser,
		filter: ptr GtkRecentFilter

;GtkRecentFilter
gtk_recent_chooser_get_filter proto __cdecl \
	       chooser: ptr GtkRecentChooser

G_END_DECLS

endif

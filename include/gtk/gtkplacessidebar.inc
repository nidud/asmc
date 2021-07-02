ifndef __GTK_PLACES_SIDEBAR_H__
__GTK_PLACES_SIDEBAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_PLACES_SIDEBAR equ <gtk_places_sidebar_get_type>
GTK_PLACES_SIDEBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PLACES_SIDEBAR, GtkPlacesSidebar))>
	endm
GTK_PLACES_SIDEBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_PLACES_SIDEBAR, GtkPlacesSidebarClass))>
	endm
GTK_IS_PLACES_SIDEBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PLACES_SIDEBAR))>
	endm
GTK_IS_PLACES_SIDEBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_PLACES_SIDEBAR))>
	endm
GTK_PLACES_SIDEBAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_PLACES_SIDEBAR, GtkPlacesSidebarClass))>
	endm

.enum GtkPlacesOpenFlags {
  GTK_PLACES_OPEN_NORMAL	= 1 shl 0,
  GTK_PLACES_OPEN_NEW_TAB	= 1 shl 1,
  GTK_PLACES_OPEN_NEW_WINDOW	= 1 shl 2
}

;GType
gtk_places_sidebar_get_type proto __cdecl
;GtkWidget
gtk_places_sidebar_new proto __cdecl

;GtkPlacesOpenFlags
gtk_places_sidebar_get_open_flags proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar

;void
gtk_places_sidebar_set_open_flags proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
		 flags: GtkPlacesOpenFlags


;GFile
gtk_places_sidebar_get_location proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar

;void
gtk_places_sidebar_set_location proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
	      location: ptr GFile


;gboolean
gtk_places_sidebar_get_show_recent proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar

;void
gtk_places_sidebar_set_show_recent proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
	   show_recent: gboolean


;gboolean
gtk_places_sidebar_get_show_desktop proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar

;void
gtk_places_sidebar_set_show_desktop proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
	  show_desktop: gboolean


;gboolean
gtk_places_sidebar_get_show_connect_to_server proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar

;void
gtk_places_sidebar_set_show_connect_to_server proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
show_connect_to_server: gboolean

;gboolean
gtk_places_sidebar_get_show_enter_location proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar

;void
gtk_places_sidebar_set_show_enter_location proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
   show_enter_location: gboolean


;void
gtk_places_sidebar_set_local_only proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
	    local_only: gboolean

;gboolean
gtk_places_sidebar_get_local_only proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar



;void
gtk_places_sidebar_add_shortcut proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
	      location: ptr GFile

;void
gtk_places_sidebar_remove_shortcut proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
	      location: ptr GFile

;GSList
gtk_places_sidebar_list_shortcuts proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar


;GFile
gtk_places_sidebar_get_nth_bookmark proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
		     n: gint

;void
gtk_places_sidebar_set_drop_targets_visible proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
	       visible: gboolean,
	       context: ptr GdkDragContext

;gboolean
gtk_places_sidebar_get_show_trash proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar

;void
gtk_places_sidebar_set_show_trash proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
	    show_trash: gboolean


;void
gtk_places_sidebar_set_show_other_locations proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar,
  show_other_locations: gboolean

;gboolean
gtk_places_sidebar_get_show_other_locations proto __cdecl \
	       sidebar: ptr GtkPlacesSidebar


G_END_DECLS

endif

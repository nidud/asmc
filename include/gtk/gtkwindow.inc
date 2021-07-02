ifndef __GTK_WINDOW_H__
__GTK_WINDOW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkapplication.inc
include gtk/gtkaccelgroup.inc
include gtk/gtkbin.inc

GTK_TYPE_WINDOW equ <gtk_window_get_type>
GTK_WINDOW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_WINDOW, GtkWindow))>
	endm
GTK_WINDOW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_WINDOW, GtkWindowClass))>
	endm
GTK_IS_WINDOW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_WINDOW))>
	endm
GTK_IS_WINDOW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WINDOW))>
	endm
GTK_WINDOW_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_WINDOW, GtkWindowClass))>
	endm

GtkWindow		STRUC
bin			GtkBin <>
priv			ptr_t ?
GtkWindow		ENDS

GtkWindowClass		STRUC
parent_class		GtkBinClass <>
set_focus		proc :ptr GtkWindow, :ptr GtkWidget
activate_focus		proc :ptr GtkWindow
activate_default	proc :ptr GtkWindow
keys_changed		proc :ptr GtkWindow
enable_debugging	proc :ptr GtkWindow, :gboolean
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
GtkWindowClass		ENDS

.enum GtkWindowType {
  GTK_WINDOW_TOPLEVEL,
  GTK_WINDOW_POPUP
}

.enum GtkWindowPosition {
  GTK_WIN_POS_NONE,
  GTK_WIN_POS_CENTER,
  GTK_WIN_POS_MOUSE,
  GTK_WIN_POS_CENTER_ALWAYS,
  GTK_WIN_POS_CENTER_ON_PARENT
}

;GType
gtk_window_get_type proto __cdecl
;GtkWidget*
gtk_window_new proto __cdecl \
		  type: GtkWindowType

;void
gtk_window_set_title proto __cdecl \
		window: ptr GtkWindow,
		 title: ptr gchar

;const
gtk_window_get_title proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_wmclass proto __cdecl \
		window: ptr GtkWindow,
	  wmclass_name: ptr gchar,
	 wmclass_class: ptr gchar

;void
gtk_window_set_role proto __cdecl \
		window: ptr GtkWindow,
		  role: ptr gchar

;void
gtk_window_set_startup_id proto __cdecl \
		window: ptr GtkWindow,
	    startup_id: ptr gchar

;const
gtk_window_get_role proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_add_accel_group proto __cdecl \
		window: ptr GtkWindow,
	   accel_group: ptr GtkAccelGroup

;void
gtk_window_remove_accel_group proto __cdecl \
		window: ptr GtkWindow,
	   accel_group: ptr GtkAccelGroup

;void
gtk_window_set_position proto __cdecl \
		window: ptr GtkWindow,
	      position: GtkWindowPosition

;gboolean
gtk_window_activate_focus proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_focus proto __cdecl \
		window: ptr GtkWindow,
		 focus: ptr GtkWidget

;GtkWidget
gtk_window_get_focus proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_default proto __cdecl \
		window: ptr GtkWindow,
	default_widget: ptr GtkWidget

;GtkWidget
gtk_window_get_default_widget proto __cdecl \
		window: ptr GtkWindow

;gboolean
gtk_window_activate_default proto __cdecl \
		window: ptr GtkWindow


;void
gtk_window_set_transient_for proto __cdecl \
		window: ptr GtkWindow,
		parent: ptr GtkWindow

;GtkWindow
gtk_window_get_transient_for proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_attached_to proto __cdecl \
		window: ptr GtkWindow,
	 attach_widget: ptr GtkWidget

;GtkWidget
gtk_window_get_attached_to proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_opacity proto __cdecl \
		window: ptr GtkWindow,
	       opacity: gdouble

;gdouble
gtk_window_get_opacity proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_type_hint proto __cdecl \
		window: ptr GtkWindow,
		  hint: GdkWindowTypeHint

;GdkWindowTypeHint
gtk_window_get_type_hint proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_skip_taskbar_hint proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_skip_taskbar_hint proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_skip_pager_hint proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_skip_pager_hint proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_urgency_hint proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_urgency_hint proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_accept_focus proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_accept_focus proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_focus_on_map proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_focus_on_map proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_destroy_with_parent proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_destroy_with_parent proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_hide_titlebar_when_maximized proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_hide_titlebar_when_maximized proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_mnemonics_visible proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_mnemonics_visible proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_focus_visible proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_focus_visible proto __cdecl \
		window: ptr GtkWindow


;void
gtk_window_set_resizable proto __cdecl \
		window: ptr GtkWindow,
	     resizable: gboolean

;gboolean
gtk_window_get_resizable proto __cdecl \
		window: ptr GtkWindow


;void
gtk_window_set_gravity proto __cdecl \
		window: ptr GtkWindow,
	       gravity: GdkGravity

;GdkGravity
gtk_window_get_gravity proto __cdecl \
		window: ptr GtkWindow



;void
gtk_window_set_geometry_hints proto __cdecl \
		window: ptr GtkWindow,
       geometry_widget: ptr GtkWidget,
	      geometry: ptr GdkGeometry,
	     geom_mask: GdkWindowHints


;void
gtk_window_set_screen proto __cdecl \
		window: ptr GtkWindow,
		screen: ptr GdkScreen

;GdkScreen*
gtk_window_get_screen proto __cdecl \
		window: ptr GtkWindow


;gboolean
gtk_window_is_active proto __cdecl \
		window: ptr GtkWindow

;gboolean
gtk_window_has_toplevel_focus proto __cdecl \
		window: ptr GtkWindow


;void
gtk_window_set_decorated proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_decorated proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_deletable proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;gboolean
gtk_window_get_deletable proto __cdecl \
		window: ptr GtkWindow


;void
gtk_window_set_icon_list proto __cdecl \
		window: ptr GtkWindow,
		  list: ptr GList

;GList*
gtk_window_get_icon_list proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_icon proto __cdecl \
		window: ptr GtkWindow,
		  icon: ptr GdkPixbuf

;void
gtk_window_set_icon_name proto __cdecl \
		window: ptr GtkWindow,
		  name: ptr gchar

;gboolean
gtk_window_set_icon_from_file proto __cdecl \
		window: ptr GtkWindow,
	      filename: ptr gchar,
		   err: ptr GError

;GdkPixbuf*
gtk_window_get_icon proto __cdecl \
		window: ptr GtkWindow

;const
gtk_window_get_icon_name proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_default_icon_list proto __cdecl \
		  list: ptr GList

;GList*
gtk_window_get_default_icon_list proto __cdecl
;void
gtk_window_set_default_icon proto __cdecl \
		  icon: ptr GdkPixbuf

;void
gtk_window_set_default_icon_name proto __cdecl \
		  name: ptr gchar

;const
gtk_window_get_default_icon_name proto __cdecl
;gboolean
gtk_window_set_default_icon_from_file proto __cdecl \
	      filename: ptr gchar,
		   err: ptr GError


;void
gtk_window_set_auto_startup_notification proto __cdecl \
	       setting: gboolean


;void
gtk_window_set_modal proto __cdecl \
		window: ptr GtkWindow,
		 modal: gboolean

;gboolean
gtk_window_get_modal proto __cdecl \
		window: ptr GtkWindow

;GList*
gtk_window_list_toplevels proto __cdecl
;void
gtk_window_set_has_user_ref_count proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean


;void
gtk_window_add_mnemonic proto __cdecl \
		window: ptr GtkWindow,
		keyval: guint,
		target: ptr GtkWidget

;void
gtk_window_remove_mnemonic proto __cdecl \
		window: ptr GtkWindow,
		keyval: guint,
		target: ptr GtkWidget

;gboolean
gtk_window_mnemonic_activate proto __cdecl \
		window: ptr GtkWindow,
		keyval: guint,
	      modifier: GdkModifierType

;void
gtk_window_set_mnemonic_modifier proto __cdecl \
		window: ptr GtkWindow,
	      modifier: GdkModifierType

;GdkModifierType
gtk_window_get_mnemonic_modifier proto __cdecl \
		window: ptr GtkWindow


;gboolean
gtk_window_activate_key proto __cdecl \
		window: ptr GtkWindow,
		 event: ptr GdkEventKey

;gboolean
gtk_window_propagate_key_event proto __cdecl \
		window: ptr GtkWindow,
		 event: ptr GdkEventKey


;void
gtk_window_present proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_present_with_time proto __cdecl \
		window: ptr GtkWindow,
	     timestamp: guint32

;void
gtk_window_iconify proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_deiconify proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_stick proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_unstick proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_maximize proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_unmaximize proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_fullscreen proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_unfullscreen proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_fullscreen_on_monitor proto __cdecl \
		window: ptr GtkWindow,
		screen: ptr GdkScreen,
	      _monitor: gint

;void
gtk_window_close proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_keep_above proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean

;void
gtk_window_set_keep_below proto __cdecl \
		window: ptr GtkWindow,
	       setting: gboolean


;void
gtk_window_begin_resize_drag proto __cdecl \
		window: ptr GtkWindow,
		  edge: GdkWindowEdge,
		button: gint,
		root_x: gint,
		root_y: gint,
	     timestamp: guint32

;void
gtk_window_begin_move_drag proto __cdecl \
		window: ptr GtkWindow,
		button: gint,
		root_x: gint,
		root_y: gint,
	     timestamp: guint32


;void
gtk_window_set_default_size proto __cdecl \
		window: ptr GtkWindow,
		 width: gint,
		height: gint

;void
gtk_window_get_default_size proto __cdecl \
		window: ptr GtkWindow,
		 width: ptr gint,
		height: ptr gint

;void
gtk_window_resize proto __cdecl \
		window: ptr GtkWindow,
		 width: gint,
		height: gint

;void
gtk_window_get_size proto __cdecl \
		window: ptr GtkWindow,
		 width: ptr gint,
		height: ptr gint

;void
gtk_window_move proto __cdecl \
		window: ptr GtkWindow,
		     x: gint,
		     y: gint

;void
gtk_window_get_position proto __cdecl \
		window: ptr GtkWindow,
		root_x: ptr gint,
		root_y: ptr gint

;gboolean
gtk_window_parse_geometry proto __cdecl \
		window: ptr GtkWindow,
	      geometry: ptr gchar


;void
gtk_window_set_default_geometry proto __cdecl \
		window: ptr GtkWindow,
		 width: gint,
		height: gint

;void
gtk_window_resize_to_geometry proto __cdecl \
		window: ptr GtkWindow,
		 width: gint,
		height: gint


;GtkWindowGroup
gtk_window_get_group proto __cdecl \
		window: ptr GtkWindow

;gboolean
gtk_window_has_group proto __cdecl \
		window: ptr GtkWindow


;void
gtk_window_reshow_with_initial_size proto __cdecl \
		window: ptr GtkWindow


;GtkWindowType
gtk_window_get_window_type proto __cdecl \
		window: ptr GtkWindow



;GtkApplication
gtk_window_get_application proto __cdecl \
		window: ptr GtkWindow

;void
gtk_window_set_application proto __cdecl \
		window: ptr GtkWindow,
	   application: ptr GtkApplication



;void
gtk_window_set_has_resize_grip proto __cdecl \
		window: ptr GtkWindow,
		 value: gboolean

;gboolean
gtk_window_get_has_resize_grip proto __cdecl \
		window: ptr GtkWindow

;gboolean
gtk_window_resize_grip_is_visible proto __cdecl \
		window: ptr GtkWindow

;gboolean
gtk_window_get_resize_grip_area proto __cdecl \
		window: ptr GtkWindow,
		  rect: ptr GdkRectangle


;void
gtk_window_set_titlebar proto __cdecl \
		window: ptr GtkWindow,
	      titlebar: ptr GtkWidget

;GtkWidget
gtk_window_get_titlebar proto __cdecl \
		window: ptr GtkWindow


;gboolean
gtk_window_is_maximized proto __cdecl \
		window: ptr GtkWindow


;void
gtk_window_set_interactive_debugging proto __cdecl \
		enable: gboolean

endif

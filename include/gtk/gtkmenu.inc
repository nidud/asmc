ifndef __GTK_MENU_H__
__GTK_MENU_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkaccelgroup.inc
include gtk/gtkmenushell.inc


G_BEGIN_DECLS

GTK_TYPE_MENU equ <gtk_menu_get_type>
GTK_MENU macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MENU, GtkMenu))>
	endm
GTK_MENU_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MENU, GtkMenuClass))>
	endm
GTK_IS_MENU macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MENU))>
	endm
GTK_IS_MENU_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MENU))>
	endm
GTK_MENU_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MENU, GtkMenuClass))>
	endm

.enum GtkArrowPlacement {
  GTK_ARROWS_BOTH,
  GTK_ARROWS_START,
  GTK_ARROWS_END
}


CALLBACKC(GtkMenuPositionFunc, :ptr GtkMenu, :ptr gint, :ptr gint, :ptr gboolean, :gpointer)
CALLBACKC(GtkMenuDetachFunc, :ptr GtkWidget, :ptr GtkMenu)

GtkMenu			STRUC
menu_shell		GtkMenuShell <>
priv			ptr_t ?
GtkMenu			ENDS

GtkMenuClass		STRUC
parent_class		GtkMenuShellClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMenuClass		ENDS


;GType
gtk_menu_get_type proto __cdecl
;GtkWidget*
gtk_menu_new proto __cdecl
;GtkWidget*
gtk_menu_new_from_model proto __cdecl \
		 model: ptr GMenuModel


;void
gtk_menu_popup proto __cdecl \
		  menu: ptr GtkMenu,
     parent_menu_shell: ptr GtkWidget,
      parent_menu_item: ptr GtkWidget,
		  func: GtkMenuPositionFunc,
		  data: gpointer,
		button: guint,
	 activate_time: guint32

;void
gtk_menu_popup_for_device proto __cdecl \
		  menu: ptr GtkMenu,
		device: ptr GdkDevice,
     parent_menu_shell: ptr GtkWidget,
      parent_menu_item: ptr GtkWidget,
		  func: GtkMenuPositionFunc,
		  data: gpointer,
	       destroy: GDestroyNotify,
		button: guint,
	 activate_time: guint32


;void
gtk_menu_reposition proto __cdecl \
		  menu: ptr GtkMenu


;void
gtk_menu_popdown proto __cdecl \
		  menu: ptr GtkMenu


;GtkWidget*
gtk_menu_get_active proto __cdecl \
		  menu: ptr GtkMenu

;void
gtk_menu_set_active proto __cdecl \
		  menu: ptr GtkMenu,
		 index: guint


;void
gtk_menu_set_accel_group proto __cdecl \
		  menu: ptr GtkMenu,
	   accel_group: ptr GtkAccelGroup

;GtkAccelGroup*
gtk_menu_get_accel_group proto __cdecl \
		  menu: ptr GtkMenu

;void
gtk_menu_set_accel_path proto __cdecl \
		  menu: ptr GtkMenu,
	    accel_path: ptr gchar

;const
gtk_menu_get_accel_path proto __cdecl \
		  menu: ptr GtkMenu


;void
gtk_menu_attach_to_widget proto __cdecl \
		  menu: ptr GtkMenu,
	 attach_widget: ptr GtkWidget,
	      detacher: GtkMenuDetachFunc

;void
gtk_menu_detach proto __cdecl \
		  menu: ptr GtkMenu


;GtkWidget*
gtk_menu_get_attach_widget proto __cdecl \
		  menu: ptr GtkMenu


;void
gtk_menu_set_tearoff_state proto __cdecl \
		  menu: ptr GtkMenu,
	      torn_off: gboolean

;gboolean
gtk_menu_get_tearoff_state proto __cdecl \
		  menu: ptr GtkMenu


;void
gtk_menu_set_title proto __cdecl \
		  menu: ptr GtkMenu,
		 title: ptr gchar

;const
gtk_menu_get_title proto __cdecl \
		  menu: ptr GtkMenu


;void
gtk_menu_reorder_child proto __cdecl \
		  menu: ptr GtkMenu,
		 child: ptr GtkWidget,
	      position: gint


;void
gtk_menu_set_screen proto __cdecl \
		  menu: ptr GtkMenu,
		screen: ptr GdkScreen


;void
gtk_menu_attach proto __cdecl \
		  menu: ptr GtkMenu,
		 child: ptr GtkWidget,
	   left_attach: guint,
	  right_attach: guint,
	    top_attach: guint,
	 bottom_attach: guint


;void
gtk_menu_set_monitor proto __cdecl \
		  menu: ptr GtkMenu,
	   monitor_num: gint

;gint
gtk_menu_get_monitor proto __cdecl \
		  menu: ptr GtkMenu

;GList*
gtk_menu_get_for_attach_widget proto __cdecl \
		widget: ptr GtkWidget

gtk_menu_set_reserve_toggle_size proto __cdecl \
		  menu: ptr GtkMenu,
   reserve_toggle_size: gboolean

;gboolean
gtk_menu_get_reserve_toggle_size proto __cdecl \
		  menu: ptr GtkMenu

G_END_DECLS

endif
